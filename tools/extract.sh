#!/bin/sh


# Extract section documentation into own body and heading files
# Heading file is created only if body file is not empty
# Documentation is between /* __XXX__ and the next * __ markers
# $1 is section name, such as NAME, SYNOPSIS, DESCRIPTION, NOTES, etc.
# $2 is temporary documentation file
extract_section()
{
        START_MARK="/* __$1__"
        END_MARK="/* __"
        EXTRACT_PAT="$START_MARK/,$END_MARK/{$START_MARK/!{$END_MARK/!p;};}"
        EXTRACT_FILE="$2.$(echo "$1" | tr '[:upper:]' '[:lower:]')"

        if [ "$1" = "SYNOPSIS" ]; then
                echo '    ```' > "$EXTRACT_FILE"
                sed -n "$EXTRACT_PAT" "$2" | cut -c 3- >> "$EXTRACT_FILE"
                echo '    ```' >> "$EXTRACT_FILE"
        elif [ "$1" = "GIVEN" ]; then
                echo "    Given the following pre-conditions:" > "$EXTRACT_FILE"
                echo "" >> "$EXTRACT_FILE"
                sed -n "$EXTRACT_PAT" "$2" | cut -c 3- >> "$EXTRACT_FILE"
        elif [ "$1" = "WHEN" ]; then
                echo "    When the following occur:" > "$EXTRACT_FILE"
                echo "" >> "$EXTRACT_FILE"
                sed -n "$EXTRACT_PAT" "$2" | cut -c 3- >> "$EXTRACT_FILE"
        elif [ "$1" = "THEN" ]; then
                echo "    Then the following are expected:" > "$EXTRACT_FILE"
                echo "" >> "$EXTRACT_FILE"
                sed -n "$EXTRACT_PAT" "$2" | cut -c 3- >> "$EXTRACT_FILE"
        else
                sed -n "$EXTRACT_PAT" "$2" | cut -c 3- > "$EXTRACT_FILE"
        fi

        if [ -s "$EXTRACT_FILE" ]; then
                echo "*$1*" > "$EXTRACT_FILE.head"
        fi
}


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
        TMP="build/docs/$(echo "$TAG" | tr ':' '_' | tr -d '%')"
        #MD="build/docs/$(echo "$TAG" | tr ':' '_' | tr -d '%').md"

        # Add directive to include custom m4 macros
        #echo "include(\`macros.m4')" > "$M4"

        # Extract documentation context from TAG
        #DOC_CTX=$(echo "$TAG" | cut -d ':' -f 2)

        # Prepare pattern to extract documentation for TAG
        DOC_PAT="/$TAG/,/$END_MARKER/{/$TAG/!{/$END_MARKER/!p;};}"

        # Extract documentation into snippet files
        #sed -n "$DOC_PAT" "$FILE" | cut -c 4- >> "$M4"
        sed -n "$DOC_PAT" "$FILE" | cut -c 2- > "$TMP"

        # Mark end of documentation
        echo "* __" >> "$TMP"

        # Extract sections in $TMP to own head and body files
        extract_section "NAME" "$TMP"
        extract_section "SYNOPSIS" "$TMP"
        extract_section "DESCRIPTION" "$TMP"
        extract_section "RETURN" "$TMP"
        extract_section "NOTES" "$TMP"
        extract_section "SCENARIO" "$TMP"
        extract_section "GIVEN" "$TMP"
        extract_section "WHEN" "$TMP"
        extract_section "THEN" "$TMP"

        # Expand dcoumentation markers into macros
        #sed -i "s/__NAME__/__NAME__(<<<$DOC_CTX>>>)/g" "$M4"
        #sed -i "s/__SYNOPSIS__/__SYNOPSIS__(<<<$DOC_CTX>>>)/g" "$M4"
        #sed -i "s/__DESCRIPTION__/__DESCRIPTION__(<<<$DOC_CTX>>>)/g" "$M4"
        #sed -i "s/__NOTES__/__NOTES__(<<<$DOC_CTX>>>)/g" "$M4"
        #sed -i "s/__RETURN__/__RETURN__(<<<$DOC_CTX>>>)/g" "$M4"
        #sed -i "s/__SCENARIO__/__SCENARIO__(<<<$DOC_CTX>>>)/g" "$M4"
        #sed -i "s/__GIVEN__/__GIVEN__(<<<$DOC_CTX>>>)/g" "$M4"
        #sed -i "s/__WHEN__/__WHEN__(<<<$DOC_CTX>>>)/g" "$M4"
        #sed -i "s/__THEN__/__THEN__(<<<$DOC_CTX>>>)/g" "$M4"

        # Expand macros to generate markdown file
        #m4 -DMAN -I docs/ "$M4" > "$MD"

        # Remove blank lines from top of MD
        #sed -i '/./,$!d' "$MD"

        # Remove intermediate m4 file
        rm -f "$TMP" > /dev/null

        # Remove empty files
        find build/docs -type f -empty -print -delete > /dev/null
    done
done
