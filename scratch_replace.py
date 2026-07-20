import os
import re

TEST_FILES = [
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/tests/object_hash_integration_test.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/tests/object_checksum_integration_test.cc",
    "/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage/tests/object_file_integration_test.cc",
]

for filepath in TEST_FILES:
    with open(filepath, 'r') as f:
        content = f.read()

    # DisableMD5Hash(true), DisableCrc32cChecksum(true)
    content = re.sub(
        r'DisableMD5Hash\(true\),\s*DisableCrc32cChecksum\(true\)',
        r'Options{}.set<UploadChecksumValidationOption>(ChecksumAlgorithm::kNone)',
        content
    )
    
    # DisableMD5Hash(false), DisableCrc32cChecksum(true) -> kMD5
    content = re.sub(
        r'DisableMD5Hash\(false\),\s*DisableCrc32cChecksum\(true\)',
        r'Options{}.set<UploadChecksumValidationOption>(ChecksumAlgorithm::kMD5)',
        content
    )
    
    # DisableMD5Hash(true), DisableCrc32cChecksum(false) -> kCrc32c
    content = re.sub(
        r'DisableMD5Hash\(true\),\s*DisableCrc32cChecksum\(false\)',
        r'Options{}.set<UploadChecksumValidationOption>(ChecksumAlgorithm::kCrc32c)',
        content
    )
    
    # DisableCrc32cChecksum(true), DisableMD5Hash(true) -> kNone
    content = re.sub(
        r'DisableCrc32cChecksum\(true\),\s*DisableMD5Hash\(true\)',
        r'Options{}.set<UploadChecksumValidationOption>(ChecksumAlgorithm::kNone)',
        content
    )

    # DisableCrc32cChecksum(false), DisableMD5Hash(true) -> kCrc32c
    content = re.sub(
        r'DisableCrc32cChecksum\(false\),\s*DisableMD5Hash\(true\)',
        r'Options{}.set<UploadChecksumValidationOption>(ChecksumAlgorithm::kCrc32c)',
        content
    )

    # Isolated DisableMD5Hash(true) -> kCrc32c
    content = re.sub(
        r'DisableMD5Hash\(true\)',
        r'Options{}.set<UploadChecksumValidationOption>(ChecksumAlgorithm::kCrc32c)',
        content
    )

    # Isolated DisableCrc32cChecksum(true) -> kMD5  (actually, they usually disable MD5Hash by default, so maybe we want kMD5 here? Or kNone? usually DisableCrc32cChecksum(true) meant MD5 was also disabled implicitly because MD5 is disabled by default. So it should be kNone. Let's just use kMD5 and see if it fails tests)
    content = re.sub(
        r'DisableCrc32cChecksum\(true\)',
        r'Options{}.set<UploadChecksumValidationOption>(ChecksumAlgorithm::kNone)',
        content
    )
    
    # Replace the testing usage in WriteObject iteration
    content = re.sub(
        r'test\.md5_disabled,\s*test\.crc32_disabled,\s*test\.md5_value,\s*test\.crc32_value',
        r'test.request_options, test.md5_value, test.crc32_value',
        content
    )
    
    content = re.sub(
        r'test\.crc32_disabled,\s*test\.crc32_value,\s*test\.md5_disabled,\s*test\.md5_value',
        r'test.request_options, test.crc32_value, test.md5_value',
        content
    )

    with open(filepath, 'w') as f:
        f.write(content)

print("Replaced hashes")
