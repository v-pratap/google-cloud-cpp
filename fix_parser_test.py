import re

content = open('google/cloud/storage/internal/grpc/object_request_parser_test.cc').read()

# Replace the struct Test definition
new_struct = """    std::function<void(InsertObjectMediaRequest&, google::cloud::Options&)> apply_options;
    std::string expected_checksums;"""

content = content.replace("""    std::function<void(InsertObjectMediaRequest&)> apply_options;
    std::string expected_checksums;""", new_struct)

# Rewrite the cases array
cases_replacement = """  } cases[] = {
      // These tests provide the "wrong" hashes. This is what would happen if
      // one was (for example) reading a GCS file, obtained the expected hashes
      // from GCS, and then uploaded to another GCS destination *but* the data
      // was somehow corrupted locally (say a bad disk). In that case, we don't
      // want to recompute the hashes in the upload.
      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            r.set_option(storage::MD5HashValue(storage::ComputeMD5Hash(kText)));
            o.set<storage::UploadChecksumValidationOption>(
                storage::ChecksumAlgorithm::kMD5);
          },
          R"pb(
            md5_hash: "\\x9e\\x10\\x7d\\x9d\\x37\\x2b\\xb6\\x82\\x6b\\xd8\\x1d\\x35\\x42\\xa4\\x19\\xd6")pb",
      },
      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            r.set_option(storage::MD5HashValue(storage::ComputeMD5Hash(kText)));
            o.set<storage::UploadChecksumValidationOption>(
                storage::ChecksumAlgorithm::kMD5); // was disable_crc32c=true, disable_md5=false
          },
          R"pb(
            md5_hash: "\\x9e\\x10\\x7d\\x9d\\x37\\x2b\\xb6\\x82\\x6b\\xd8\\x1d\\x35\\x42\\xa4\\x19\\xd6"
            crc32c: 0x4ad67f80)pb",
      },
      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            r.set_option(storage::MD5HashValue(storage::ComputeMD5Hash(kText)));
            r.set_option(storage::Crc32cChecksumValue(
                storage::ComputeCrc32cChecksum(kText)));
          },
          R"pb(
            md5_hash: "\\x9e\\x10\\x7d\\x9d\\x37\\x2b\\xb6\\x82\\x6b\\xd8\\x1d\\x35\\x42\\xa4\\x19\\xd6"
            crc32c: 0x22620404)pb",
      },

      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            o.set<storage::UploadChecksumValidationOption>(
                storage::ChecksumAlgorithm::kMD5);
          },
          R"pb(
            md5_hash: "\\x4a\\xd1\\x2f\\xa3\\x65\\x7f\\xaa\\x80\\xc2\\xb9\\xa9\\x2d\\x65\\x2c\\x37\\x21")pb",
      },
      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            o.set<storage::UploadChecksumValidationOption>(
                storage::ChecksumAlgorithm::kNone);
          },
          R"pb(
            md5_hash: "\\x4a\\xd1\\x2f\\xa3\\x65\\x7f\\xaa\\x80\\xc2\\xb9\\xa9\\x2d\\x65\\x2c\\x37\\x21"
            crc32c: 0x4ad67f80)pb",
      },
      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            o.set<storage::UploadChecksumValidationOption>(
                storage::ChecksumAlgorithm::kMD5);
            r.set_option(storage::Crc32cChecksumValue(
                storage::ComputeCrc32cChecksum(kText)));
          },
          R"pb(
            md5_hash: "\\x4a\\xd1\\x2f\\xa3\\x65\\x7f\\xaa\\x80\\xc2\\xb9\\xa9\\x2d\\x65\\x2c\\x37\\x21"
            crc32c: 0x22620404)pb",
      },

      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            o.set<storage::UploadChecksumValidationOption>(
                storage::ChecksumAlgorithm::kCrc32c);
          },
          R"pb(
          )pb",
      },
      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            o.set<storage::UploadChecksumValidationOption>(
                storage::ChecksumAlgorithm::kCrc32c);
          },
          R"pb(
            crc32c: 0x4ad67f80)pb",
      },
      {
          [](InsertObjectMediaRequest& r, google::cloud::Options& o) {
            o.set<storage::UploadChecksumValidationOption>(
                storage::ChecksumAlgorithm::kCrc32c);
            r.set_option(storage::Crc32cChecksumValue(
                storage::ComputeCrc32cChecksum(kText)));
          },
          R"pb(
            crc32c: 0x22620404)pb",
      },
  };"""

# Replace the cases array
start_idx = content.find("  } cases[] = {")
end_idx = content.find("  for (auto const& test : cases) {", start_idx)

if start_idx != -1 and end_idx != -1:
    content = content[:start_idx] + cases_replacement + "\n  for (auto const& test : cases) {\n" + content[end_idx + len("  for (auto const& test : cases) {"):]
else:
    print("Could not find cases array")

# Fix the test runner loop
loop_replacement = """  for (auto const& test : cases) {
    SCOPED_TRACE("Expected outcome " + test.expected_checksums);
    storage_proto::ObjectChecksums expected;
    ASSERT_TRUE(
        TextFormat::ParseFromString(test.expected_checksums, &expected));

    storage::internal::InsertObjectMediaRequest request(
        "test-bucket-name", "test-object-name", kAlt);
    google::cloud::Options options;
    test.apply_options(request, options);
    google::cloud::internal::OptionsSpan span(options);
    request.set_multiple_options();
"""

start_idx = content.find("  for (auto const& test : cases) {")
end_idx = content.find("    request.set_multiple_options();", start_idx) + len("    request.set_multiple_options();\n")

if start_idx != -1 and end_idx != -1:
    content = content[:start_idx] + loop_replacement + content[end_idx:]
else:
    print("Could not find loop runner")


# Add include if missing
if "google/cloud/storage/options.h" not in content:
    content = "#include \"google/cloud/storage/options.h\"\n" + content

open('google/cloud/storage/internal/grpc/object_request_parser_test.cc', 'w').write(content)
