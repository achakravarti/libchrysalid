#!/bin/sh


# Create build subdirectories
mkdir -p build/docs/units/ext
mkdir -p build/docs/units/heap
mkdir -p build/docs/components


# Find m4 documentation templates
__units=$(find docs/units -type f -name "*.m4")
__components=$(find docs/components -type f -name "*.m4")


# Build man 3 documentation from units m4 templates
for x in $__units; do 
	__filename=$(echo "$x" | sed "s/.*\///" | cut -d '.' -f 1)
	printf '%s\n' "$__filename"

	m4 -DMAN -I docs/ "$x" > "build/$x.md"
	sed -i '/./,$!d' "build/$x.md" # remove blank lines from beginning

	pandoc "build/$x.md" 								\
		--bibliography=docs/references.bib 				\
		--citeproc 										\
		-s 												\
		-t man 											\
		-o "build/docs/units/ext/libchrysalis:$__filename.3"

	gzip -f "build/docs/units/ext/libchrysalis:$__filename.3"
done


# Build man 7 documentation from components m4 templates
for x in $__components; do 
	__filename=$(echo "$x" | sed "s/.*\///" | cut -d '.' -f 1)
	printf '%s\n' "$__filename"

	m4 -DMAN -I docs/ "$x" > "build/$x.md"
	sed -i '/./,$!d' "build/$x.md" # remove blank lines from beginning

	pandoc "build/$x.md" 							\
		--bibliography=docs/references.bib 				\
		--citeproc 							\
		-s 								\
		-t man 								\
		-o "build/docs/components/libchrysalis:$__filename.7"

	gzip -f "build/docs/components/libchrysalis:$__filename.7"
done

