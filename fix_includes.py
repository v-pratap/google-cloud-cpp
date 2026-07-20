with open("google/cloud/storage/internal/hash_function.h", "r") as f:
    content = f.read()

content = content.replace("#include \"google/cloud/storage/options.h\"\n", "")
content = content.replace("#include \"google/cloud/storage/hashing_options.h\"\n", "#include \"google/cloud/storage/hashing_options.h\"\n#include \"google/cloud/storage/options.h\"\n")

with open("google/cloud/storage/internal/hash_function.h", "w") as f:
    f.write(content)
print("done")
