import os
import re

def process_file(filepath, replacements):
    with open(filepath, 'r') as f:
        content = f.read()
    original = content
    for pattern, repl in replacements:
        content = re.sub(pattern, repl, content)
    if content != original:
        with open(filepath, 'w') as f:
            f.write(content)
        print(f"Modified {filepath}")


replacements_client_h = [
    (r'`DisableCrc32cChecksum`, `DisableMD5Hash`', r'`UploadChecksumValidationOption`, `DownloadChecksumValidationOption`'),
    (r'`DisableCrc32cChecksum`,\s*\n\s*\*\s*`DisableMD5Hash`', r'`UploadChecksumValidationOption`, `DownloadChecksumValidationOption`'),
]
process_file("/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/client.h", replacements_client_h)

# internal/async/checksum_helpers.h
replacements_checksum_helpers = [
    (r'  if \(options\.has<storage::DownloadChecksumValidationOption>\(\)\) \{\n    auto const algo = options\.get<storage::DownloadChecksumValidationOption>\(\);\n    return \{algo == storage::ChecksumAlgorithm::kCrc32c,\n            algo == storage::ChecksumAlgorithm::kMD5\};\n  \}\n  return \{options\.get<storage::EnableCrc32cValidationOption>\(\),\n          options\.get<storage::EnableMD5ValidationOption>\(\)\};',
     r'  auto const algo = options.get<storage::DownloadChecksumValidationOption>();\n  return {algo == storage::ChecksumAlgorithm::kCrc32c,\n          algo == storage::ChecksumAlgorithm::kMD5};'),
    (r'#include "google/cloud/internal/disable_deprecation_warnings.inc"\n', r''),
    (r'#include "google/cloud/internal/diagnostics_pop.inc"\n', r''),
]
process_file("/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/async/checksum_helpers.h", replacements_checksum_helpers)

# internal/async/connection_impl.cc
replacements_connection_impl = [
    (r'  if \(options\.has<storage::UploadChecksumValidationOption>\(\)\) \{\n    auto const algo = options\.get<storage::UploadChecksumValidationOption>\(\);\n    enable_crc32c = algo == storage::ChecksumAlgorithm::kCrc32c;\n    enable_md5 = algo == storage::ChecksumAlgorithm::kMD5;\n  \} else \{\n    enable_crc32c = options\.get<storage::EnableCrc32cValidationOption>\(\);\n    enable_md5 = options\.get<storage::EnableMD5ValidationOption>\(\);\n  \}',
     r'  auto const algo = options.get<storage::UploadChecksumValidationOption>();\n  enable_crc32c = algo == storage::ChecksumAlgorithm::kCrc32c;\n  enable_md5 = algo == storage::ChecksumAlgorithm::kMD5;')
]
process_file("/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/async/connection_impl.cc", replacements_connection_impl)

# internal/async/default_options.cc
replacements_default_options = [
    (r'      \.set<storage::EnableCrc32cValidationOption>\(true\)\n', r''),
    (r'      \.set<storage::EnableMD5ValidationOption>\(false\)\n', r''),
]
process_file("/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/async/default_options.cc", replacements_default_options)

# internal/async/default_options_test.cc
replacements_default_options_test = [
    (r'// TODO: Remove this when EnableMD5ValidationOption and\n// EnableCrc32cValidationOption are removed\.\n#if defined\(__GNUC__\) && !defined\(__clang__\)\n#pragma GCC diagnostic push\n#pragma GCC diagnostic ignored "-Wdeprecated-declarations"\n#elif defined\(__clang__\)\n#pragma clang diagnostic push\n#pragma clang diagnostic ignored "-Wdeprecated-declarations"\n#endif\n\n', r''),
    (r'\n#if defined\(__GNUC__\) && !defined\(__clang__\)\n#pragma GCC diagnostic pop\n#elif defined\(__clang__\)\n#pragma clang diagnostic pop\n#endif\n', r''),
    (r'  EXPECT_TRUE\(options\.get<storage::EnableCrc32cValidationOption>\(\)\);\n  EXPECT_FALSE\(options\.get<storage::EnableMD5ValidationOption>\(\)\);\n', r''),
]
process_file("/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/async/default_options_test.cc", replacements_default_options_test)

# internal/async/connection_impl_read_hash_test.cc, connection_impl_upload_hash_test.cc, object_descriptor_impl_test.cc
test_files = [
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/async/connection_impl_read_hash_test.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/async/connection_impl_upload_hash_test.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/async/object_descriptor_impl_test.cc"
]

for f in test_files:
    replacements = [
        (r'// TODO: Remove this when EnableMD5ValidationOption and\n// EnableCrc32cValidationOption are removed\.\n#if defined\(__GNUC__\) && !defined\(__clang__\)\n#pragma GCC diagnostic push\n#pragma GCC diagnostic ignored "-Wdeprecated-declarations"\n#elif defined\(__clang__\)\n#pragma clang diagnostic push\n#pragma clang diagnostic ignored "-Wdeprecated-declarations"\n#endif\n\n', r''),
        (r'\n#if defined\(__GNUC__\) && !defined\(__clang__\)\n#pragma GCC diagnostic pop\n#elif defined\(__clang__\)\n#pragma clang diagnostic pop\n#endif\n', r''),
        # connection tests
        (r'           lhs\.options\.get<storage::EnableCrc32cValidationOption>\(\) ==\n               rhs\.options\.get<storage::EnableCrc32cValidationOption>\(\) &&\n', r''),
        (r'           lhs\.options\.get<storage::EnableMD5ValidationOption>\(\) ==\n               rhs\.options\.get<storage::EnableMD5ValidationOption>\(\) &&\n', r''),
        (r'       << rhs\.options\.get<storage::EnableCrc32cValidationOption>\(\);\n', r''),
        (r'       << rhs\.options\.get<storage::EnableMD5ValidationOption>\(\);\n', r''),
        (r'\s*\.set<storage::EnableCrc32cValidationOption>\(true\)\n\s*\.set<storage::EnableMD5ValidationOption>\(true\),', r','),
        # object_descriptor tests
        (r'  options\.set<storage::EnableCrc32cValidationOption>\(true\);\n', r''),
        (r'  options\.set<storage::EnableMD5ValidationOption>\(true\);\n', r''),
        (r'  options\.set<storage::EnableCrc32cValidationOption>\(false\);\n', r''),
        (r'  options\.set<storage::EnableMD5ValidationOption>\(false\);\n', r''),
    ]
    process_file(f, replacements)

