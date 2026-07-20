with open("google/cloud/storage/internal/hash_function.h", "r") as f:
    content = f.read()

content = content.replace("struct DownloadChecksumValidationOption;\nstruct UploadChecksumValidationOption;\nenum class ChecksumAlgorithm;\n", "")
content = content.replace("GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN\n", "GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN\n\nstruct DownloadChecksumValidationOption;\nstruct UploadChecksumValidationOption;\nenum class ChecksumAlgorithm;\n")

with open("google/cloud/storage/internal/hash_function.h", "w") as f:
    f.write(content)
print("done")
