// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#if GOOGLE_CLOUD_CPP_STORAGE_HAVE_GRPC

#include "google/cloud/storage/async/bucket_name.h"
#include "google/cloud/storage/async/client.h"
#include "google/cloud/storage/async/idempotency_policy.h"
#include "google/cloud/opentelemetry/configure_basic_tracing.h"
#include "google/cloud/storage/async/read_all.h"
#include "google/cloud/opentelemetry_options.h"
#include "google/cloud/storage/grpc_plugin.h"
#include "google/cloud/storage/testing/storage_integration_test.h"
#include "google/cloud/grpc_options.h"
#include "google/cloud/internal/getenv.h"
#include "google/cloud/testing_util/is_proto_equal.h"
#include "google/cloud/testing_util/status_matchers.h"
#include <gmock/gmock.h>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace google {
namespace cloud {
namespace storage_experimental {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

using ::google::cloud::internal::GetEnv;
using ::google::cloud::testing_util::IsOk;
using ::google::cloud::testing_util::IsProtoEqual;
using ::google::cloud::testing_util::StatusIs;
using ::testing::IsEmpty;
using ::testing::Le;
using ::testing::Not;
using ::testing::Optional;
using ::testing::VariantWith;

class AsyncClientIntegrationTest
    : public google::cloud::storage::testing::StorageIntegrationTest {
protected:

  using google::cloud::storage::testing::StorageIntegrationTest::
      ScheduleForDelete;
  void ScheduleForDelete(google::storage::v2::Object const& object) {
    ScheduleForDelete(storage::ObjectMetadata{}
                          .set_bucket(MakeBucketName(object.bucket())->name())
                          .set_name(object.name())
                          .set_generation(object.generation()));
  }

private:
  std::string bucket_name_;
};

namespace gcs = ::google::cloud::storage;

auto AlwaysRetry() {
  return google::cloud::Options{}.set<google::cloud::storage_experimental::IdempotencyPolicyOption>(
      MakeAlwaysRetryIdempotencyPolicy);
}

google::cloud::Options MakeOptions(google::cloud::Options opts) {
  auto fallback = google::cloud::Options{};
  if (auto v = google::cloud::internal::GetEnv("GOOGLE_CLOUD_CPP_STORAGE_TEST_GRPC_ENDPOINT")) {
    fallback.set<google::cloud::EndpointOption>(*v);
  }
  if (auto v = google::cloud::internal::GetEnv("GOOGLE_CLOUD_CPP_STORAGE_TEST_JSON_ENDPOINT")) {
    fallback.set<google::cloud::storage::RestEndpointOption>(*v);
  }
  if (auto v = google::cloud::internal::GetEnv("GOOGLE_CLOUD_CPP_STORAGE_TEST_AUTHORITY")) {
    fallback.set<google::cloud::AuthorityOption>(*v);
  }
  if (auto v = google::cloud::internal::GetEnv("GOOGLE_CLOUD_CPP_STORAGE_TEST_TARGET_API_VERSION")) {
    fallback.set<google::cloud::storage::internal::TargetApiVersionOption>(*v);
  }
  fallback.set<google::cloud::storage_experimental::EnableGrpcMetricsOption>(false);
  return google::cloud::internal::MergeOptions(std::move(opts), fallback);
}

storage::Client MakeRestClient(std::string project_id) {
  auto opts = MakeOptions(google::cloud::Options{}
                      .set<google::cloud::storage::ProjectIdOption>(project_id));
  return storage::Client(std::move(opts));
}

google::cloud::storage::Client MakeGrpcClient(std::string project_id) {
  auto options = MakeOptions(google::cloud::Options{}
                      .set<gcs::ProjectIdOption>(project_id));
  return google::cloud::storage::MakeGrpcClient(std::move(options));
}

google::cloud::storage_experimental::AsyncClient MakeAsyncClient(std::string project_id) {
  auto options = MakeOptions(google::cloud::Options{}
                          .set<gcs::ProjectIdOption>(project_id)
                          .set<google::cloud::LoggingComponentsOption>({"rpc"})
                          .set<google::cloud::OpenTelemetryTracingOption>(true));
  return google::cloud::storage_experimental::AsyncClient(options);
}

TEST_F(AsyncClientIntegrationTest, StartAppendableUploadEmpty) {
  auto project_id = "vaibhavpratap-sdk-test";
  auto const kproject = google::cloud::Project(project_id);
  auto const tracing = google::cloud::otel::ConfigureBasicTracing(kproject);

  auto client = MakeGrpcClient(project_id);

  auto bucket_name = std::string{"vaibhavpratap-zb-3"};
  auto object_name = "vaibhav-test-11";
  auto placement = gcs::BucketCustomPlacementConfig{{"us-west4-a"}};
  auto hns = gcs::BucketHierarchicalNamespace{true};
  auto ubla = gcs::BucketIamConfiguration{gcs::UniformBucketLevelAccess{true, {}}, absl::nullopt};

  // auto create = client.CreateBucket(
  //     bucket_name, storage::BucketMetadata{}.set_location("us-west4")
  //                                           .set_storage_class("RAPID")
  //                                           .set_custom_placement_config(placement)
  //                                           .set_hierarchical_namespace(hns)
  //                                           .set_iam_configuration(ubla));
  // if (!create && create.status().code() != StatusCode::kAlreadyExists) {
  //   GTEST_FAIL() << "cannot create bucket: " << create.status();
  // } else {
  //   std::cout << "Bucket successfully created." << std::endl;
  // }

  auto bucket_metadata = client.GetBucketMetadata(bucket_name);
  std::cout << "Bucket name is " << bucket_metadata->name() << std::endl;

  auto constexpr kBlockSize = 20 * 1024;
  auto constexpr kBlockCount = 3;
  auto const block = MakeRandomData(kBlockSize);
  auto const block2 = MakeRandomData(kBlockSize);

  auto async = MakeAsyncClient(project_id);
  // auto w = async.StartAppendableObjectUpload(BucketName(bucket_name), object_name)
  //               .get();
  // ASSERT_STATUS_OK(w);

  // AsyncWriter writer;
  // AsyncToken token;
  // std::tie(writer, token) = *std::move(w);
  // for (int i = 0; i < kBlockCount; ++i) {
  //   std::cout << "Writing data iteration #" << i << std::endl;
  //   auto p = writer.Write(std::move(token), WritePayload(block)).get();
  //   ASSERT_STATUS_OK(p);
  //   token = *std::move(p);
  // }
  
  // auto metadata1 = writer.Finalize(std::move(token)).get();
  // std::cout << "Request metadata: " << metadata1->generation() << std::endl;

  // auto close = writer.Close();

  auto object_metadata = client.GetObjectMetadata(bucket_name, object_name);
  auto m = *object_metadata;
  auto generation = m.generation();
  std::cout << "Object metadata: " << m << std::endl;
  EXPECT_EQ("ddd", "Sdf");

  auto w1 = async.ResumeAppendableObjectUpload(BucketName(bucket_name), object_name, generation)
                .get();

  ASSERT_STATUS_OK(w1);

  AsyncWriter writer1;
  AsyncToken token1;
  std::tie(writer1, token1) = *std::move(w1);
  for (int i = 0; i < kBlockCount; ++i) {
    std::cout << "Writing data iteration #" << i << std::endl;
    auto p = writer1.Write(std::move(token1), WritePayload(block2)).get();
    ASSERT_STATUS_OK(p);
    token1 = *std::move(p);
  }

  auto object_metadata1 = client.GetObjectMetadata(bucket_name, object_name);
  auto m1 = *object_metadata1;
  auto generation1 = m1.generation();
  std::cout << "Object metadata1: " << m << std::endl;
  EXPECT_EQ("dddd", "Sdfs");
  // auto metadata = writer1.Finalize(std::move(token1)).get();
  // ASSERT_STATUS_OK(metadata);
  // ScheduleForDelete(*metadata);

  // EXPECT_EQ(metadata->bucket(), BucketName(bucket_name).FullName());
  // EXPECT_EQ(metadata->name()," object_name");
  // EXPECT_EQ(metadata->size(), kBlockCount * kBlockSize);


  // auto spec = google::storage::v2::BidiReadObjectSpec{};
  // spec.set_bucket(metadata->bucket());
  // spec.set_object(object_name);
  // auto options = MakeOptions(google::cloud::Options{}
  //                         .set<gcs::ProjectIdOption>(project_id)
  //                         .set<google::cloud::LoggingComponentsOption>({"rpc"})
  //                         .set<google::cloud::OpenTelemetryTracingOption>(true));

  // auto descriptor = async.Open(spec,options).get();
  // ASSERT_STATUS_OK(descriptor);

  // auto constexpr kSize = 10 * 1024;
  // auto constexpr kStride = 2 * kSize;

  // AsyncReader r0;
  // AsyncReader r1;
  // AsyncReader r2;
  // AsyncToken t0;
  // AsyncToken t1;
  // AsyncToken t2;
  // std::tie(r1, t1) = descriptor->Read(1 * kStride, kSize);
  // std::tie(r2, t2) = descriptor->Read(1 * kStride, kSize);
  // auto actual0 = std::string{};
  // std::tie(r0, t0) = descriptor->Read(0 * kStride, kSize);
  // while (t0.valid()) {
  //   auto read = r0.Read(std::move(t0)).get();
  //   ASSERT_STATUS_OK(read);
  //   ReadPayload p;
  //   AsyncToken t;
  //   std::tie(p, t) = *std::move(read);
  //   for (auto sv : p.contents()) actual0 += std::string(sv);
  //   t0 = std::move(t);
  // }
  // auto ans = block + block + block;

  // EXPECT_EQ(actual0.size(), ans.size());
  // client.DeleteObject(bucket_name(), object_name,
  //                     storage::Generation(os.metadata()->generation()));

  std::cout << "Test completed successfully" << std::endl;
  // client.DeleteObject(bucket_name, object_name);
}

}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace storage_experimental
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_STORAGE_HAVE_GRPC