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
// source: google/cloud/chronicle/v1/data_access_control.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CHRONICLE_V1_INTERNAL_DATA_ACCESS_CONTROL_TRACING_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CHRONICLE_V1_INTERNAL_DATA_ACCESS_CONTROL_TRACING_CONNECTION_H

#include "google/cloud/chronicle/v1/data_access_control_connection.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace chronicle_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

class DataAccessControlServiceTracingConnection
    : public chronicle_v1::DataAccessControlServiceConnection {
 public:
  ~DataAccessControlServiceTracingConnection() override = default;

  explicit DataAccessControlServiceTracingConnection(
      std::shared_ptr<chronicle_v1::DataAccessControlServiceConnection> child);

  Options options() override { return child_->options(); }

  StatusOr<google::cloud::chronicle::v1::DataAccessLabel> CreateDataAccessLabel(
      google::cloud::chronicle::v1::CreateDataAccessLabelRequest const& request)
      override;

  StatusOr<google::cloud::chronicle::v1::DataAccessLabel> GetDataAccessLabel(
      google::cloud::chronicle::v1::GetDataAccessLabelRequest const& request)
      override;

  StreamRange<google::cloud::chronicle::v1::DataAccessLabel>
  ListDataAccessLabels(google::cloud::chronicle::v1::ListDataAccessLabelsRequest
                           request) override;

  StatusOr<google::cloud::chronicle::v1::DataAccessLabel> UpdateDataAccessLabel(
      google::cloud::chronicle::v1::UpdateDataAccessLabelRequest const& request)
      override;

  Status DeleteDataAccessLabel(
      google::cloud::chronicle::v1::DeleteDataAccessLabelRequest const& request)
      override;

  StatusOr<google::cloud::chronicle::v1::DataAccessScope> CreateDataAccessScope(
      google::cloud::chronicle::v1::CreateDataAccessScopeRequest const& request)
      override;

  StatusOr<google::cloud::chronicle::v1::DataAccessScope> GetDataAccessScope(
      google::cloud::chronicle::v1::GetDataAccessScopeRequest const& request)
      override;

  StreamRange<google::cloud::chronicle::v1::DataAccessScope>
  ListDataAccessScopes(google::cloud::chronicle::v1::ListDataAccessScopesRequest
                           request) override;

  StatusOr<google::cloud::chronicle::v1::DataAccessScope> UpdateDataAccessScope(
      google::cloud::chronicle::v1::UpdateDataAccessScopeRequest const& request)
      override;

  Status DeleteDataAccessScope(
      google::cloud::chronicle::v1::DeleteDataAccessScopeRequest const& request)
      override;

  StreamRange<google::longrunning::Operation> ListOperations(
      google::longrunning::ListOperationsRequest request) override;

  StatusOr<google::longrunning::Operation> GetOperation(
      google::longrunning::GetOperationRequest const& request) override;

  Status DeleteOperation(
      google::longrunning::DeleteOperationRequest const& request) override;

  Status CancelOperation(
      google::longrunning::CancelOperationRequest const& request) override;

 private:
  std::shared_ptr<chronicle_v1::DataAccessControlServiceConnection> child_;
};

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

/**
 * Conditionally applies the tracing decorator to the given connection.
 *
 * The connection is only decorated if tracing is enabled (as determined by the
 * connection's options).
 */
std::shared_ptr<chronicle_v1::DataAccessControlServiceConnection>
MakeDataAccessControlServiceTracingConnection(
    std::shared_ptr<chronicle_v1::DataAccessControlServiceConnection> conn);

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace chronicle_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CHRONICLE_V1_INTERNAL_DATA_ACCESS_CONTROL_TRACING_CONNECTION_H
