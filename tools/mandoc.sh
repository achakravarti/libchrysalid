#!/bin/sh

tools/extract.sh

mkdir -p build/docs/man

m4 -DMAN -I docs/ -I build/docs/ docs/heap.m4 > "build/docs/man/heap.md"

# Remove blank lines from top of markdown file
sed -i '/./,$!d' "build/docs/man/heap.md"

# Replace code tags in markdown file
sed -i 's/{{/`/g' "build/docs/man/heap.md"
sed -i 's/}}/`/g' "build/docs/man/heap.md"

# Replace vestigial lines containing single colon and space as a result
# of processing empty body files
sed -i '/^: $/d' "build/docs/man/heap.md"

# Generate man page
pandoc "build/docs/man/heap.md" \
    --bibliography=docs/references.bib \
    --citeproc \
    -s \
    -f markdown \
    -t man \
    -o "build/docs/man/libchrysalid:heap.3"

# Compress man page
gzip -f "build/docs/man/libchrysalid:heap.3"
