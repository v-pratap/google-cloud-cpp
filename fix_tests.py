import sys

files = [
    "google/cloud/storage/internal/async/connection_impl_read_hash_test.cc",
    "google/cloud/storage/internal/async/connection_impl_upload_hash_test.cc",
    "google/cloud/storage/internal/async/default_options_test.cc",
    "google/cloud/storage/internal/async/object_descriptor_impl_test.cc"
]

header_insert = """// TODO(v-pratap): Remove this when EnableMD5ValidationOption and
// EnableCrc32cValidationOption are removed.
#include "google/cloud/internal/disable_deprecation_warnings.inc"
"""

footer_insert = """
#include "google/cloud/internal/diagnostics_pop.inc"
"""

for fpath in files:
    with open(fpath, "r") as f:
        content = f.read()
    
    # insert after the first include
    lines = content.split('\n')
    out_lines = []
    inserted_header = False
    for line in lines:
        out_lines.append(line)
        if not inserted_header and line.startswith("#include "):
            out_lines.append("")
            out_lines.extend(header_insert.strip('\n').split('\n'))
            inserted_header = True
            
    # append footer at the end
    out_content = '\n'.join(out_lines)
    if out_content.endswith('\n'):
        out_content = out_content[:-1]
    out_content += footer_insert
    
    with open(fpath, "w") as f:
        f.write(out_content)

print("done")
