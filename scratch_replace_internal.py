import os
import re

files_to_fix = [
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/object_requests.h",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/rest/stub.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/connection_impl.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/grpc/object_request_parser_test.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/object_requests_test.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/hash_validator_test.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/hash_function_impl_test.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/internal/object_write_streambuf_test.cc"
]

for filepath in files_to_fix:
    with open(filepath, 'r') as f:
        content = f.read()
    original = content

    # object_requests.h
    content = re.sub(r'DisableCrc32cChecksum,\s*DisableMD5Hash,\s*', r'', content)
    
    # rest/stub.cc
    content = re.sub(
        r'// uploads\. `DisableMD5Hash` and `DisableCrc32cChecksum` should not be\n\s*// included\n\s*if \(!request\.GetOption<DisableMD5Hash>\(\)\.value_or\(false\) \|\|\n\s*!request\.GetOption<DisableCrc32cChecksum>\(\)\.value_or\(false\) \|\|',
        r'// uploads. \n  if (',
        content
    )

    # connection_impl.cc
    content = re.sub(
        r'integrity checks using the DisableMD5Hash\(\) and DisableCrc32cChecksum\(\) options\.',
        r'integrity checks using the UploadChecksumValidationOption() and DownloadChecksumValidationOption() options.',
        content
    )
    
    # object_requests_test.cc
    content = re.sub(r'  EXPECT_TRUE\(DisableMD5Hash\(\)\.has_value\(\)\);\n  EXPECT_FALSE\(DisableMD5Hash\(false\)\.has_value\(\)\);\n  EXPECT_FALSE\(DisableCrc32cChecksum\(\)\.has_value\(\)\);\n', '', content)
    content = re.sub(r'  EXPECT_TRUE\(DisableMD5Hash\(\)\.has_value\(\)\);\n', '', content)
    content = re.sub(r'  EXPECT_FALSE\(DisableCrc32cChecksum\(\)\.has_value\(\)\);\n', '', content)

    # hash tests
    content = re.sub(
        r'DisableCrc32cChecksum crc32_disabled;\n\s*DisableMD5Hash md5_disabled;\n',
        r'bool disable_crc32c = false;\n    bool disable_md5 = false;\n',
        content
    )
    content = re.sub(
        r'DisableCrc32cChecksum\(true\),\s*DisableMD5Hash\(true\)',
        r'true, true',
        content
    )
    content = re.sub(
        r'DisableCrc32cChecksum\(false\),\s*DisableMD5Hash\(true\)',
        r'false, true',
        content
    )
    content = re.sub(
        r'DisableCrc32cChecksum\(true\),\s*DisableMD5Hash\(false\)',
        r'true, false',
        content
    )
    content = re.sub(
        r'DisableCrc32cChecksum\(false\),\s*DisableMD5Hash\(false\)',
        r'false, false',
        content
    )
    content = re.sub(
        r'DisableCrc32cChecksum\(false\)',
        r'false',
        content
    )
    content = re.sub(
        r'DisableMD5Hash\(false\)',
        r'false',
        content
    )

    # grpc test
    content = re.sub(
        r'r\.set_option\(storage::DisableCrc32cChecksum\(true\)\);',
        r'google::cloud::internal::CurrentOptions().set<storage::UploadChecksumValidationOption>(storage::ChecksumAlgorithm::kMD5);',
        content
    )
    content = re.sub(
        r'r\.set_option\(storage::DisableCrc32cChecksum\(false\)\);',
        r'google::cloud::internal::CurrentOptions().set<storage::UploadChecksumValidationOption>(storage::ChecksumAlgorithm::kCrc32c);',
        content
    )
    content = re.sub(
        r'r\.set_option\(storage::DisableMD5Hash\(true\)\);',
        r'google::cloud::internal::CurrentOptions().set<storage::UploadChecksumValidationOption>(storage::ChecksumAlgorithm::kCrc32c);',
        content
    )
    content = re.sub(
        r'r\.set_option\(storage::DisableMD5Hash\(false\)\);',
        r'google::cloud::internal::CurrentOptions().set<storage::UploadChecksumValidationOption>(storage::ChecksumAlgorithm::kMD5);',
        content
    )

    if content != original:
        with open(filepath, 'w') as f:
            f.write(content)
        print(f"Modified {filepath}")

