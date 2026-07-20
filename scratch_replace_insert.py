import os
import re
import glob

def find_files(directory, pattern):
    return glob.glob(os.path.join(directory, pattern), recursive=True)

files = []
files.extend(find_files("/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage", "**/*.cc"))
files.extend(find_files("/usr/local/google/home/vaibhavpratap/google-cloud-cpp/google/cloud/storage", "**/*.h"))

for filepath in files:
    with open(filepath, 'r') as f:
        content = f.read()

    original = content

    # DisableMD5Hash
    content = re.sub(
        r'gcs::DisableCrc32cChecksum\(!config.enable_crc32c\),\s*gcs::DisableMD5Hash\(!config.enable_md5\)',
        r'google::cloud::Options{}.set<gcs::UploadChecksumValidationOption>('
        r'config.enable_crc32c && config.enable_md5 ? gcs::ChecksumAlgorithm::kCrc32c : '
        r'config.enable_crc32c ? gcs::ChecksumAlgorithm::kCrc32c : '
        r'config.enable_md5 ? gcs::ChecksumAlgorithm::kMD5 : gcs::ChecksumAlgorithm::kNone)',
        content
    )
    
    content = re.sub(
        r'DisableCrc32cChecksum\(true\),\s*DisableMD5Hash\(true\)',
        r'Options{}.set<UploadChecksumValidationOption>(ChecksumAlgorithm::kNone)',
        content
    )

    if content != original:
        with open(filepath, 'w') as f:
            f.write(content)
        print(f"Modified {filepath}")

