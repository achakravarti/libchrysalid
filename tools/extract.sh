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
        M4="build/docs/$(echo "$TAG" | tr ':' '_' | tr -d '%').m4"
        MD="build/docs/$(echo "$TAG" | tr ':' '_' | tr -d '%').md"

        # Add directive to include custom m4 macros
        echo "include(\`macros.m4')" > "$M4"

        # Extract documentation context from TAG
        DOC_CTX=$(echo "$TAG" | cut -d ':' -f 2)

        # Prepare pattern to extract documentation for TAG
        DOC_PAT="/$TAG/,/$END_MARKER/{/$TAG/!{/$END_MARKER/!p;};}"

        # Extract documentation into snippet files
        sed -n "$DOC_PAT" "$FILE" | cut -c 4- >> "$M4"

        # Expand dcoumentation markers into macros
        sed -i "s/__NAME__/__NAME__(<<<$DOC_CTX>>>)/g" "$M4"
        sed -i "s/__SYNOPSIS__/__SYNOPSIS__(<<<$DOC_CTX>>>)/g" "$M4"
        sed -i "s/__DESCRIPTION__/__DESCRIPTION__(<<<$DOC_CTX>>>)/g" "$M4"
        sed -i "s/__NOTES__/__NOTES__(<<<$DOC_CTX>>>)/g" "$M4"
        sed -i "s/__RETURN__/__RETURN__(<<<$DOC_CTX>>>)/g" "$M4"
        sed -i "s/__SCENARIO__/__SCENARIO__(<<<$DOC_CTX>>>)/g" "$M4"
        sed -i "s/__GIVEN__/__GIVEN__(<<<$DOC_CTX>>>)/g" "$M4"
        sed -i "s/__WHEN__/__WHEN__(<<<$DOC_CTX>>>)/g" "$M4"
        sed -i "s/__THEN__/__THEN__(<<<$DOC_CTX>>>)/g" "$M4"

        # Expand macros to generate markdown file
        m4 -DMAN -I docs/ "$M4" > "$MD"

        # Remove blank lines from top of MD
        sed -i '/./,$!d' "$MD"

        # Remove intermediate m4 file
        rm -f "$M4"
    done
done
