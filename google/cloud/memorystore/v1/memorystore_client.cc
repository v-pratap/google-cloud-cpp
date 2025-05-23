// Copyright 2025 Google LLC
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

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/memorystore/v1/memorystore.proto

#include "google/cloud/memorystore/v1/memorystore_client.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace memorystore_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

MemorystoreClient::MemorystoreClient(
    std::shared_ptr<MemorystoreConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
MemorystoreClient::~MemorystoreClient() = default;

StreamRange<google::cloud::memorystore::v1::Instance>
MemorystoreClient::ListInstances(std::string const& parent, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::ListInstancesRequest request;
  request.set_parent(parent);
  return connection_->ListInstances(request);
}

StreamRange<google::cloud::memorystore::v1::Instance>
MemorystoreClient::ListInstances(
    google::cloud::memorystore::v1::ListInstancesRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListInstances(std::move(request));
}

StatusOr<google::cloud::memorystore::v1::Instance>
MemorystoreClient::GetInstance(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::GetInstanceRequest request;
  request.set_name(name);
  return connection_->GetInstance(request);
}

StatusOr<google::cloud::memorystore::v1::Instance>
MemorystoreClient::GetInstance(
    google::cloud::memorystore::v1::GetInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetInstance(request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::CreateInstance(
    std::string const& parent,
    google::cloud::memorystore::v1::Instance const& instance,
    std::string const& instance_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::CreateInstanceRequest request;
  request.set_parent(parent);
  *request.mutable_instance() = instance;
  request.set_instance_id(instance_id);
  return connection_->CreateInstance(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::CreateInstance(
    NoAwaitTag, std::string const& parent,
    google::cloud::memorystore::v1::Instance const& instance,
    std::string const& instance_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::CreateInstanceRequest request;
  request.set_parent(parent);
  *request.mutable_instance() = instance;
  request.set_instance_id(instance_id);
  return connection_->CreateInstance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::CreateInstance(
    google::cloud::memorystore::v1::CreateInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateInstance(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::CreateInstance(
    NoAwaitTag,
    google::cloud::memorystore::v1::CreateInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateInstance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::CreateInstance(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateInstance(operation);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::UpdateInstance(
    google::cloud::memorystore::v1::Instance const& instance,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::UpdateInstanceRequest request;
  *request.mutable_instance() = instance;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateInstance(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::UpdateInstance(
    NoAwaitTag, google::cloud::memorystore::v1::Instance const& instance,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::UpdateInstanceRequest request;
  *request.mutable_instance() = instance;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateInstance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::UpdateInstance(
    google::cloud::memorystore::v1::UpdateInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateInstance(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::UpdateInstance(
    NoAwaitTag,
    google::cloud::memorystore::v1::UpdateInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateInstance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::UpdateInstance(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateInstance(operation);
}

future<StatusOr<google::cloud::memorystore::v1::OperationMetadata>>
MemorystoreClient::DeleteInstance(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::DeleteInstanceRequest request;
  request.set_name(name);
  return connection_->DeleteInstance(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::DeleteInstance(
    NoAwaitTag, std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::DeleteInstanceRequest request;
  request.set_name(name);
  return connection_->DeleteInstance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::OperationMetadata>>
MemorystoreClient::DeleteInstance(
    google::cloud::memorystore::v1::DeleteInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteInstance(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::DeleteInstance(
    NoAwaitTag,
    google::cloud::memorystore::v1::DeleteInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteInstance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::OperationMetadata>>
MemorystoreClient::DeleteInstance(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteInstance(operation);
}

StatusOr<google::cloud::memorystore::v1::CertificateAuthority>
MemorystoreClient::GetCertificateAuthority(std::string const& name,
                                           Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::GetCertificateAuthorityRequest request;
  request.set_name(name);
  return connection_->GetCertificateAuthority(request);
}

StatusOr<google::cloud::memorystore::v1::CertificateAuthority>
MemorystoreClient::GetCertificateAuthority(
    google::cloud::memorystore::v1::GetCertificateAuthorityRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetCertificateAuthority(request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::RescheduleMaintenance(
    std::string const& name,
    google::cloud::memorystore::v1::RescheduleMaintenanceRequest::RescheduleType
        reschedule_type,
    google::protobuf::Timestamp const& schedule_time, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::RescheduleMaintenanceRequest request;
  request.set_name(name);
  request.set_reschedule_type(reschedule_type);
  *request.mutable_schedule_time() = schedule_time;
  return connection_->RescheduleMaintenance(request);
}

StatusOr<google::longrunning::Operation>
MemorystoreClient::RescheduleMaintenance(
    NoAwaitTag, std::string const& name,
    google::cloud::memorystore::v1::RescheduleMaintenanceRequest::RescheduleType
        reschedule_type,
    google::protobuf::Timestamp const& schedule_time, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::RescheduleMaintenanceRequest request;
  request.set_name(name);
  request.set_reschedule_type(reschedule_type);
  *request.mutable_schedule_time() = schedule_time;
  return connection_->RescheduleMaintenance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::RescheduleMaintenance(
    google::cloud::memorystore::v1::RescheduleMaintenanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->RescheduleMaintenance(request);
}

StatusOr<google::longrunning::Operation>
MemorystoreClient::RescheduleMaintenance(
    NoAwaitTag,
    google::cloud::memorystore::v1::RescheduleMaintenanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->RescheduleMaintenance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::RescheduleMaintenance(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->RescheduleMaintenance(operation);
}

StreamRange<google::cloud::memorystore::v1::BackupCollection>
MemorystoreClient::ListBackupCollections(std::string const& parent,
                                         Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::ListBackupCollectionsRequest request;
  request.set_parent(parent);
  return connection_->ListBackupCollections(request);
}

StreamRange<google::cloud::memorystore::v1::BackupCollection>
MemorystoreClient::ListBackupCollections(
    google::cloud::memorystore::v1::ListBackupCollectionsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListBackupCollections(std::move(request));
}

StatusOr<google::cloud::memorystore::v1::BackupCollection>
MemorystoreClient::GetBackupCollection(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::GetBackupCollectionRequest request;
  request.set_name(name);
  return connection_->GetBackupCollection(request);
}

StatusOr<google::cloud::memorystore::v1::BackupCollection>
MemorystoreClient::GetBackupCollection(
    google::cloud::memorystore::v1::GetBackupCollectionRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetBackupCollection(request);
}

StreamRange<google::cloud::memorystore::v1::Backup>
MemorystoreClient::ListBackups(std::string const& parent, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::ListBackupsRequest request;
  request.set_parent(parent);
  return connection_->ListBackups(request);
}

StreamRange<google::cloud::memorystore::v1::Backup>
MemorystoreClient::ListBackups(
    google::cloud::memorystore::v1::ListBackupsRequest request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListBackups(std::move(request));
}

StatusOr<google::cloud::memorystore::v1::Backup> MemorystoreClient::GetBackup(
    std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::GetBackupRequest request;
  request.set_name(name);
  return connection_->GetBackup(request);
}

StatusOr<google::cloud::memorystore::v1::Backup> MemorystoreClient::GetBackup(
    google::cloud::memorystore::v1::GetBackupRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetBackup(request);
}

future<StatusOr<google::cloud::memorystore::v1::OperationMetadata>>
MemorystoreClient::DeleteBackup(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::DeleteBackupRequest request;
  request.set_name(name);
  return connection_->DeleteBackup(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::DeleteBackup(
    NoAwaitTag, std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::DeleteBackupRequest request;
  request.set_name(name);
  return connection_->DeleteBackup(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::OperationMetadata>>
MemorystoreClient::DeleteBackup(
    google::cloud::memorystore::v1::DeleteBackupRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteBackup(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::DeleteBackup(
    NoAwaitTag,
    google::cloud::memorystore::v1::DeleteBackupRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteBackup(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::OperationMetadata>>
MemorystoreClient::DeleteBackup(google::longrunning::Operation const& operation,
                                Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteBackup(operation);
}

future<StatusOr<google::cloud::memorystore::v1::Backup>>
MemorystoreClient::ExportBackup(
    google::cloud::memorystore::v1::ExportBackupRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ExportBackup(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::ExportBackup(
    NoAwaitTag,
    google::cloud::memorystore::v1::ExportBackupRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ExportBackup(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Backup>>
MemorystoreClient::ExportBackup(google::longrunning::Operation const& operation,
                                Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ExportBackup(operation);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::BackupInstance(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::BackupInstanceRequest request;
  request.set_name(name);
  return connection_->BackupInstance(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::BackupInstance(
    NoAwaitTag, std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::memorystore::v1::BackupInstanceRequest request;
  request.set_name(name);
  return connection_->BackupInstance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::BackupInstance(
    google::cloud::memorystore::v1::BackupInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->BackupInstance(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::BackupInstance(
    NoAwaitTag,
    google::cloud::memorystore::v1::BackupInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->BackupInstance(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::memorystore::v1::Instance>>
MemorystoreClient::BackupInstance(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->BackupInstance(operation);
}

StreamRange<google::cloud::location::Location> MemorystoreClient::ListLocations(
    google::cloud::location::ListLocationsRequest request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListLocations(std::move(request));
}

StatusOr<google::cloud::location::Location> MemorystoreClient::GetLocation(
    google::cloud::location::GetLocationRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetLocation(request);
}

StreamRange<google::longrunning::Operation> MemorystoreClient::ListOperations(
    std::string const& name, std::string const& filter, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::longrunning::ListOperationsRequest request;
  request.set_name(name);
  request.set_filter(filter);
  return connection_->ListOperations(request);
}

StreamRange<google::longrunning::Operation> MemorystoreClient::ListOperations(
    google::longrunning::ListOperationsRequest request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListOperations(std::move(request));
}

StatusOr<google::longrunning::Operation> MemorystoreClient::GetOperation(
    std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::longrunning::GetOperationRequest request;
  request.set_name(name);
  return connection_->GetOperation(request);
}

StatusOr<google::longrunning::Operation> MemorystoreClient::GetOperation(
    google::longrunning::GetOperationRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetOperation(request);
}

Status MemorystoreClient::DeleteOperation(std::string const& name,
                                          Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::longrunning::DeleteOperationRequest request;
  request.set_name(name);
  return connection_->DeleteOperation(request);
}

Status MemorystoreClient::DeleteOperation(
    google::longrunning::DeleteOperationRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteOperation(request);
}

Status MemorystoreClient::CancelOperation(std::string const& name,
                                          Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::longrunning::CancelOperationRequest request;
  request.set_name(name);
  return connection_->CancelOperation(request);
}

Status MemorystoreClient::CancelOperation(
    google::longrunning::CancelOperationRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CancelOperation(request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace memorystore_v1
}  // namespace cloud
}  // namespace google
