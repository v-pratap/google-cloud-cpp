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

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/parallelstore/v1/parallelstore.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PARALLELSTORE_V1_PARALLELSTORE_OPTIONS_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PARALLELSTORE_V1_PARALLELSTORE_OPTIONS_H

#include "google/cloud/parallelstore/v1/parallelstore_connection.h"
#include "google/cloud/parallelstore/v1/parallelstore_connection_idempotency_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace parallelstore_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * Use with `google::cloud::Options` to configure the retry policy.
 *
 * @ingroup google-cloud-parallelstore-options
 */
struct ParallelstoreRetryPolicyOption {
  using Type = std::shared_ptr<ParallelstoreRetryPolicy>;
};

/**
 * Use with `google::cloud::Options` to configure the backoff policy.
 *
 * @ingroup google-cloud-parallelstore-options
 */
struct ParallelstoreBackoffPolicyOption {
  using Type = std::shared_ptr<BackoffPolicy>;
};

/**
 * Use with `google::cloud::Options` to configure which operations are retried.
 *
 * @ingroup google-cloud-parallelstore-options
 */
struct ParallelstoreConnectionIdempotencyPolicyOption {
  using Type = std::shared_ptr<ParallelstoreConnectionIdempotencyPolicy>;
};

/**
 * Use with `google::cloud::Options` to configure the long-running operations
 * polling policy.
 *
 * @ingroup google-cloud-parallelstore-options
 */
struct ParallelstorePollingPolicyOption {
  using Type = std::shared_ptr<PollingPolicy>;
};

/**
 * The options applicable to Parallelstore.
 *
 * @ingroup google-cloud-parallelstore-options
 */
using ParallelstorePolicyOptionList =
    OptionList<ParallelstoreRetryPolicyOption, ParallelstoreBackoffPolicyOption,
               ParallelstorePollingPolicyOption,
               ParallelstoreConnectionIdempotencyPolicyOption>;

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace parallelstore_v1
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PARALLELSTORE_V1_PARALLELSTORE_OPTIONS_H
