// Copyright 2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/storage/internal/async/object_descriptor_impl.h"
#include "google/cloud/storage/async/options.h"
#include "google/cloud/storage/internal/async/handle_redirect_error.h"
#include "google/cloud/storage/internal/async/object_descriptor_reader_tracing.h"
#include "google/cloud/storage/internal/hash_function.h"
#include "google/cloud/storage/internal/hash_function_impl.h"
#include "google/cloud/grpc_error_delegate.h"
#include "google/cloud/internal/opentelemetry.h"
#include <google/rpc/status.pb.h>
#include <iterator>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace storage_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

ObjectDescriptorImpl::ObjectDescriptorImpl(
    std::unique_ptr<storage_experimental::ResumePolicy> resume_policy,
    OpenStreamFactory make_stream,
    google::storage::v2::BidiReadObjectSpec read_object_spec,
    std::shared_ptr<OpenStream> stream, Options options)
    : resume_policy_prototype_(std::move(resume_policy)),
      make_stream_(std::move(make_stream)),
      read_object_spec_(std::move(read_object_spec)),
      options_(std::move(options)) {
  streams_.push_back(
      Stream{std::move(stream), {}, resume_policy_prototype_->clone()});
}

ObjectDescriptorImpl::~ObjectDescriptorImpl() { Cancel(); }

void ObjectDescriptorImpl::Start(
    google::storage::v2::BidiReadObjectResponse first_response) {
  OnRead(streams_.begin(), std::move(first_response));
  std::unique_lock<std::mutex> lk(mu_);
  AssurePendingStreamQueued();  // Queue the first background stream creation.
}

void ObjectDescriptorImpl::Cancel() {
  std::unique_lock<std::mutex> lk(mu_);
  cancelled_ = true;
  for (auto const& stream : streams_) {
    stream.stream->Cancel();
  }
}

absl::optional<google::storage::v2::Object> ObjectDescriptorImpl::metadata()
    const {
  std::unique_lock<std::mutex> lk(mu_);
  return metadata_;
}

void ObjectDescriptorImpl::AssurePendingStreamQueued() {
  if (pending_stream_.valid()) return;
  auto request = google::storage::v2::BidiReadObjectRequest{};
  *request.mutable_read_object_spec() = read_object_spec_;
  pending_stream_ = make_stream_(std::move(request));
}

void ObjectDescriptorImpl::MakeSubsequentStream() {
  std::unique_lock<std::mutex> lk(mu_);
  // If there is an idle stream, move it to the back of the list and reuse it.
  // An idle stream is one that is not processing any ranges and has no
  // pending writes.
  for (auto it = streams_.begin(); it != streams_.end(); ++it) {
    if (it->active_ranges.empty() && !it->write_pending) {
      if (std::next(it) != streams_.end()) {
        streams_.splice(streams_.end(), streams_, it);
      }
      return;
    }
  }

  AssurePendingStreamQueued();  // Ensure a stream is being created if not already.
  auto stream_future = std::move(pending_stream_);
  lk.unlock();

  auto stream_result = stream_future.get();
  if (!stream_result) {
    // Stream creation failed. We cannot create a subsequent stream.
    // Log or trace the error, but allow existing streams to continue.
    // The next call to AssurePendingStreamQueued will retry creation.
    return;
  }

  lk.lock();
  streams_.push_back(Stream{
      std::move(stream_result->stream), {}, resume_policy_prototype_->clone()});
  // Now that we consumed pending_stream_, queue the next one.
  AssurePendingStreamQueued();
  auto new_it = std::prev(streams_.end());
  lk.unlock();
  OnRead(new_it, std::move(stream_result->first_response));
}

std::unique_ptr<storage_experimental::AsyncReaderConnection>
ObjectDescriptorImpl::Read(ReadParams p) {
  std::shared_ptr<storage::internal::HashFunction> hash_function =
      std::shared_ptr<storage::internal::HashFunction>(
          storage::internal::CreateNullHashFunction());
  if (options_.has<storage_experimental::EnableCrc32cValidationOption>()) {
    hash_function =
        std::make_shared<storage::internal::Crc32cMessageHashFunction>(
            storage::internal::CreateNullHashFunction());
  }
  auto range = std::make_shared<ReadRange>(p.start, p.length, hash_function);

  std::unique_lock<std::mutex> lk(mu_);
  if (streams_.empty()) {
    lk.unlock();
    range->OnFinish(Status(StatusCode::kFailedPrecondition,
                           "Cannot read object, all streams failed"));
    if (!internal::TracingEnabled(options_)) {
      return std::unique_ptr<storage_experimental::AsyncReaderConnection>(
          std::make_unique<ObjectDescriptorReader>(std::move(range)));
    }
    return MakeTracingObjectDescriptorReader(std::move(range));
  }
  auto it = std::prev(streams_.end());
  auto const id = ++read_id_generator_;
  it->active_ranges.emplace(id, range);
  auto& read_range = *it->next_request.add_read_ranges();
  read_range.set_read_id(id);
  read_range.set_read_offset(p.start);
  read_range.set_read_length(p.length);
  Flush(std::move(lk), it);

  if (!internal::TracingEnabled(options_)) {
    return std::unique_ptr<storage_experimental::AsyncReaderConnection>(
        std::make_unique<ObjectDescriptorReader>(std::move(range)));
  }

  return MakeTracingObjectDescriptorReader(std::move(range));
}

void ObjectDescriptorImpl::Flush(std::unique_lock<std::mutex> lk,
                                 typename std::list<Stream>::iterator it) {
  if (it->write_pending || it->next_request.read_ranges().empty()) {
    return;
  }
  it->write_pending = true;
  google::storage::v2::BidiReadObjectRequest request;
  request.Swap(&it->next_request);

  lk.unlock();
  it->stream->Write(std::move(request)).then([w = WeakFromThis(), it](auto f) {
    if (auto self = w.lock()) self->OnWrite(it, f.get());
  });
}

void ObjectDescriptorImpl::OnWrite(typename std::list<Stream>::iterator it,
                                   bool ok) {
  std::unique_lock<std::mutex> lk(mu_);
  if (!ok) return DoFinish(std::move(lk), it);
  it->write_pending = false;
  Flush(std::move(lk), it);
}

void ObjectDescriptorImpl::DoRead(std::unique_lock<std::mutex> lk,
                                  typename std::list<Stream>::iterator it) {
  lk.unlock();
  it->stream->Read().then([w = WeakFromThis(), it](auto f) {
    if (auto self = w.lock()) self->OnRead(it, f.get());
  });
}

void ObjectDescriptorImpl::OnRead(
    typename std::list<Stream>::iterator it,
    absl::optional<google::storage::v2::BidiReadObjectResponse> response) {
  std::unique_lock<std::mutex> lk(mu_);
  if (!response) return DoFinish(std::move(lk), it);
  if (response->has_metadata()) {
    metadata_ = std::move(*response->mutable_metadata());
  }
  if (response->has_read_handle()) {
    *read_object_spec_.mutable_read_handle() =
        std::move(*response->mutable_read_handle());
  }
  auto copy = it->active_ranges;
  // Release the lock while notifying the ranges. The notifications may trigger
  // application code, and that code may callback on this class.
  lk.unlock();
  for (auto& range_data : *response->mutable_object_data_ranges()) {
    auto id = range_data.read_range().read_id();
    auto const l = copy.find(id);
    if (l == copy.end()) continue;
    // TODO(#15104) - Consider returning if the range is done, and then
    // skipping CleanupDoneRanges().
    l->second->OnRead(std::move(range_data));
  }
  lk.lock();
  CleanupDoneRanges(lk, it);
  DoRead(std::move(lk), it);
}

void ObjectDescriptorImpl::CleanupDoneRanges(
    std::unique_lock<std::mutex> const&, typename std::list<Stream>::iterator it) {
  auto& active_ranges = it->active_ranges;
  for (auto i = active_ranges.begin(); i != active_ranges.end();) {
    if (i->second->IsDone()) {
      i = active_ranges.erase(i);
    } else {
      ++i;
    }
  }
}

void ObjectDescriptorImpl::DoFinish(std::unique_lock<std::mutex> lk,
                                    typename std::list<Stream>::iterator it) {
  lk.unlock();
  auto pending = it->stream->Finish();
  if (!pending.valid()) return;
  pending.then([w = WeakFromThis(), it](auto f) {
    if (auto self = w.lock()) self->OnFinish(it, f.get());
  });
}

void ObjectDescriptorImpl::OnFinish(typename std::list<Stream>::iterator it,
                                    Status const& status) {
  auto proto_status = ExtractGrpcStatus(status);

  if (IsResumable(it, status, proto_status)) return Resume(it, proto_status);
  // If we are here, the stream has failed and is not resumable.
  // We must notify its ranges and remove it from the list.
  std::unique_lock<std::mutex> lk(mu_);
  auto copy = std::move(it->active_ranges);
  streams_.erase(it);
  lk.unlock();
  for (auto const& kv : copy) {
    kv.second->OnFinish(status);
  }
}

void ObjectDescriptorImpl::Resume(typename std::list<Stream>::iterator it,
                                  google::rpc::Status const& proto_status) {
  std::unique_lock<std::mutex> lk(mu_);
  // This call needs to happen inside the lock, as it may modify
  // `read_object_spec_`.
  ApplyRedirectErrors(read_object_spec_, proto_status);
  auto request = google::storage::v2::BidiReadObjectRequest{};
  *request.mutable_read_object_spec() = read_object_spec_;
  for (auto const& kv : it->active_ranges) {
    auto range = kv.second->RangeForResume(kv.first);
    if (!range) continue;
    *request.add_read_ranges() = *std::move(range);
  }
  lk.unlock();
  make_stream_(std::move(request)).then([w = WeakFromThis(), it](auto f) {
    if (auto self = w.lock()) self->OnResume(it, f.get());
  });
}

void ObjectDescriptorImpl::OnResume(typename std::list<Stream>::iterator it,
                                    StatusOr<OpenStreamResult> result) {
  if (!result) return OnFinish(it, std::move(result).status());
  std::unique_lock<std::mutex> lk(mu_);
  if (cancelled_) return;
  streams_.push_back(
      Stream{std::move(result->stream), {}, resume_policy_prototype_->clone()});
  auto new_it = std::prev(streams_.end());
  new_it->active_ranges = std::move(it->active_ranges);
  streams_.erase(it);
  // TODO(#15105) - this should be done without release the lock.
  Flush(std::move(lk), new_it);
  OnRead(new_it, std::move(result->first_response));
}

bool ObjectDescriptorImpl::IsResumable(
    typename std::list<Stream>::iterator it, Status const& status,
    google::rpc::Status const& proto_status) {
  std::unique_lock<std::mutex> lk(mu_);
  for (auto const& any : proto_status.details()) {
    auto error = google::storage::v2::BidiReadObjectError{};
    if (!any.UnpackTo(&error)) continue;

    std::vector<std::pair<std::int64_t, Status>> to_notify;
    for (auto const& range_error : error.read_range_errors()) {
      if (it->active_ranges.count(range_error.read_id())) {
        to_notify.emplace_back(
            range_error.read_id(),
            MakeStatusFromRpcError(range_error.status()));
      }
    }
    if (to_notify.empty()) continue;

    auto copy = it->active_ranges;
    lk.unlock();
    for (auto const& p : to_notify) {
      auto l = copy.find(p.first);
      if (l != copy.end()) l->second->OnFinish(p.second);
    }
    lk.lock();
    CleanupDoneRanges(lk, it);
    return true;
  }
  return it->resume_policy->OnFinish(status) ==
         storage_experimental::ResumePolicy::kContinue;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage_internal
}  // namespace cloud
}  // namespace google
