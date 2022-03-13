#!/bin/sh

mkdir -p build/docs/units/ext

__units=$(find docs/units -type f -name "*.m4")

for x in $__units; do 
	__filename="$($x | sed 's#.*/##')"
	printf '%s\n' "$__filename"
	m4 -DMAN -I docs/ "$x" > "build/$x.md"
done

