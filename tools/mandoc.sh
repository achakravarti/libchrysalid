#!/bin/sh

tools/extract.sh

mkdir -p build/docs/man

m4 -DMAN -I docs/ -I build/docs/ docs/heap.m4 > "build/docs/man/heap.md"

# Remove blank lines from top of markdown file
sed -i '/./,$!d' "build/docs/man/heap.md"

pandoc "build/docs/man/heap.md" \
    --bibliography=docs/references.bib \
    --citeproc \
    -s \
    -f markdown \
    -t man \
    -o "build/docs/man/libchrysalid:heap.3"

gzip -f "build/docs/man/libchrysalid:heap.3"
