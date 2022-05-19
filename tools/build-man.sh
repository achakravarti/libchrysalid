#!/bin/sh

mkdir -p build/docs/units/ext

__units=$(find docs/units -type f -name "*.m4")

for x in $__units; do 
	__filename=$(echo "$x" | sed "s/.*\///" | cut -d '.' -f 1)
	printf '%s\n' "$__filename"
	m4 -DMAN -I docs/ "$x" > "build/$x.md"
	sed -i '/./,$!d' "build/$x.md" # remove blank lines from beginning
	pandoc "build/$x.md" \
		--bibliography=docs/references.bib \
		--citeproc \
		-s \
		-t man \
		-o "build/docs/units/ext/libchrysalid:$__filename.3"
	gzip -f "build/docs/units/ext/libchrysalid:$__filename.3"
done

