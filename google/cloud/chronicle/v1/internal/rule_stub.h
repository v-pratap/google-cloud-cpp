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
// source: google/cloud/chronicle/v1/rule.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CHRONICLE_V1_INTERNAL_RULE_STUB_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CHRONICLE_V1_INTERNAL_RULE_STUB_H

#include "google/cloud/completion_queue.h"
#include "google/cloud/future.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/cloud/chronicle/v1/rule.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace chronicle_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class RuleServiceStub {
 public:
  virtual ~RuleServiceStub() = 0;

  virtual StatusOr<google::cloud::chronicle::v1::Rule> CreateRule(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::CreateRuleRequest const& request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::Rule> GetRule(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::GetRuleRequest const& request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::ListRulesResponse> ListRules(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::ListRulesRequest const& request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::Rule> UpdateRule(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::UpdateRuleRequest const& request) = 0;

  virtual Status DeleteRule(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::DeleteRuleRequest const& request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::ListRuleRevisionsResponse>
  ListRuleRevisions(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::ListRuleRevisionsRequest const&
          request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncCreateRetrohunt(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::chronicle::v1::CreateRetrohuntRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> CreateRetrohunt(
      grpc::ClientContext& context, Options options,
      google::cloud::chronicle::v1::CreateRetrohuntRequest const& request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::Retrohunt> GetRetrohunt(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::GetRetrohuntRequest const& request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::ListRetrohuntsResponse>
  ListRetrohunts(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::ListRetrohuntsRequest const& request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::RuleDeployment>
  GetRuleDeployment(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::GetRuleDeploymentRequest const&
          request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::ListRuleDeploymentsResponse>
  ListRuleDeployments(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::ListRuleDeploymentsRequest const&
          request) = 0;

  virtual StatusOr<google::cloud::chronicle::v1::RuleDeployment>
  UpdateRuleDeployment(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::UpdateRuleDeploymentRequest const&
          request) = 0;

  virtual StatusOr<google::longrunning::ListOperationsResponse> ListOperations(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::ListOperationsRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> GetOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::GetOperationRequest const& request) = 0;

  virtual Status DeleteOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::DeleteOperationRequest const& request) = 0;

  virtual Status CancelOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::CancelOperationRequest const& request) = 0;

  virtual future<StatusOr<google::longrunning::Operation>> AsyncGetOperation(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::longrunning::GetOperationRequest const& request) = 0;

  virtual future<Status> AsyncCancelOperation(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::longrunning::CancelOperationRequest const& request) = 0;
};

class DefaultRuleServiceStub : public RuleServiceStub {
 public:
  DefaultRuleServiceStub(
      std::unique_ptr<google::cloud::chronicle::v1::RuleService::StubInterface>
          grpc_stub,
      std::unique_ptr<google::longrunning::Operations::StubInterface>
          operations_stub)
      : grpc_stub_(std::move(grpc_stub)),
        operations_stub_(std::move(operations_stub)) {}

  StatusOr<google::cloud::chronicle::v1::Rule> CreateRule(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::CreateRuleRequest const& request) override;

  StatusOr<google::cloud::chronicle::v1::Rule> GetRule(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::GetRuleRequest const& request) override;

  StatusOr<google::cloud::chronicle::v1::ListRulesResponse> ListRules(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::ListRulesRequest const& request) override;

  StatusOr<google::cloud::chronicle::v1::Rule> UpdateRule(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::UpdateRuleRequest const& request) override;

  Status DeleteRule(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::DeleteRuleRequest const& request) override;

  StatusOr<google::cloud::chronicle::v1::ListRuleRevisionsResponse>
  ListRuleRevisions(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::ListRuleRevisionsRequest const& request)
      override;

  future<StatusOr<google::longrunning::Operation>> AsyncCreateRetrohunt(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::cloud::chronicle::v1::CreateRetrohuntRequest const& request)
      override;

  StatusOr<google::longrunning::Operation> CreateRetrohunt(
      grpc::ClientContext& context, Options options,
      google::cloud::chronicle::v1::CreateRetrohuntRequest const& request)
      override;

  StatusOr<google::cloud::chronicle::v1::Retrohunt> GetRetrohunt(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::GetRetrohuntRequest const& request)
      override;

  StatusOr<google::cloud::chronicle::v1::ListRetrohuntsResponse> ListRetrohunts(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::ListRetrohuntsRequest const& request)
      override;

  StatusOr<google::cloud::chronicle::v1::RuleDeployment> GetRuleDeployment(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::GetRuleDeploymentRequest const& request)
      override;

  StatusOr<google::cloud::chronicle::v1::ListRuleDeploymentsResponse>
  ListRuleDeployments(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::ListRuleDeploymentsRequest const& request)
      override;

  StatusOr<google::cloud::chronicle::v1::RuleDeployment> UpdateRuleDeployment(
      grpc::ClientContext& context, Options const& options,
      google::cloud::chronicle::v1::UpdateRuleDeploymentRequest const& request)
      override;

  StatusOr<google::longrunning::ListOperationsResponse> ListOperations(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::ListOperationsRequest const& request) override;

  StatusOr<google::longrunning::Operation> GetOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::GetOperationRequest const& request) override;

  Status DeleteOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::DeleteOperationRequest const& request) override;

  Status CancelOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::CancelOperationRequest const& request) override;

  future<StatusOr<google::longrunning::Operation>> AsyncGetOperation(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::longrunning::GetOperationRequest const& request) override;

  future<Status> AsyncCancelOperation(
      google::cloud::CompletionQueue& cq,
      std::shared_ptr<grpc::ClientContext> context,
      google::cloud::internal::ImmutableOptions options,
      google::longrunning::CancelOperationRequest const& request) override;

 private:
  std::unique_ptr<google::cloud::chronicle::v1::RuleService::StubInterface>
      grpc_stub_;
  std::unique_ptr<google::longrunning::Operations::StubInterface>
      operations_stub_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace chronicle_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_CHRONICLE_V1_INTERNAL_RULE_STUB_H
