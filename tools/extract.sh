#!/bin/sh

END_MARKER="*\/"

# Ensure build/docs directory exists
mkdir -p build/docs

# List all C header and source files
IN_FILES=$(find . -type f -name '*.h'  -o -name '*.c')

for FILE in $IN_FILES; do
    # List all documentation tags in FILE
    TAGS=$(grep '%type:\|%func:\|%const:\|%macro:\|%test:' "$FILE" \
        | tr -d '/*'                                               \
        | tr -d '[:blank:]')

    for TAG in $TAGS; do
        # Generate m4 documentation snippet file path for TAG
        OUT_FILE="build/docs/$(echo "$TAG" | tr ':' '_' | tr -d '%').m4"

        # Prepare pattern to extract documentation for TAG
        DOC_PAT="/$TAG/,/$END_MARKER/{/$TAG/!{/$END_MARKER/!p;};}"

        # Extract documentation into snippet files
        sed -n "$DOC_PAT" "$FILE" | cut -c 4- > "$OUT_FILE"
    done
done
