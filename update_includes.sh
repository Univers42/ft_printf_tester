#!/bin/bash

# Colors for better output
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
CYAN="\033[0;36m"
RESET="\033[0m"

# Check if correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo -e "${RED}Error: Incorrect number of arguments.${RESET}"
    echo -e "Usage: $0 ${CYAN}\"#include <old_path>\"${RESET} ${CYAN}\"#include <new_path>\"${RESET}"
    echo -e "Example: $0 ${CYAN}\"#include \\\"ft_printf.h\\\"\"${RESET} ${CYAN}\"#include \\\"../include/ft_printf.h\\\"\"${RESET}"
    exit 1
fi

OLD_INCLUDE="$1"
NEW_INCLUDE="$2"

# Verify arguments look like includes
if [[ ! "$OLD_INCLUDE" =~ ^#include ]]; then
    echo -e "${RED}Error: First argument doesn't look like an include statement.${RESET}"
    echo -e "It should start with ${CYAN}#include${RESET}"
    exit 1
fi

if [[ ! "$NEW_INCLUDE" =~ ^#include ]]; then
    echo -e "${RED}Error: Second argument doesn't look like an include statement.${RESET}"
    echo -e "It should start with ${CYAN}#include${RESET}"
    exit 1
fi

# Display header
echo -e "${CYAN}╔════════════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}║${RESET} ${YELLOW}Include Path Updater${RESET}                        ${CYAN}║${RESET}"
echo -e "${CYAN}╚════════════════════════════════════════════════╝${RESET}"
echo ""
echo -e "${YELLOW}Searching for files with include statement:${RESET} ${OLD_INCLUDE}"
echo -e "${YELLOW}Will replace with:${RESET} ${NEW_INCLUDE}"
echo ""

# Escape special characters for grep and sed
OLD_INCLUDE_GREP=$(echo "$OLD_INCLUDE" | sed 's/[\/&]/\\&/g')
OLD_INCLUDE_SED=$(echo "$OLD_INCLUDE" | sed 's/[\/&]/\\&/g')
NEW_INCLUDE_SED=$(echo "$NEW_INCLUDE" | sed 's/[\/&]/\\&/g')

# Find C/C++ files recursively
echo -e "${YELLOW}Scanning project files...${RESET}"
FILES=$(find . -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \) | sort)

# Count total files
TOTAL_FILES=$(echo "$FILES" | wc -l)
CHANGED_FILES=0
UNCHANGED_FILES=0

# Process each file
echo -e "${YELLOW}Processing files:${RESET}"
echo ""

for FILE in $FILES; do
    # Check if the file contains the old include
    if grep -q "$OLD_INCLUDE_GREP" "$FILE"; then
        # Count occurrences before change
        OCCURRENCES=$(grep -c "$OLD_INCLUDE_GREP" "$FILE")
        
        # Make a backup
        cp "$FILE" "${FILE}.bak"
        
        # Perform the replacement
        sed -i "s/$OLD_INCLUDE_SED/$NEW_INCLUDE_SED/g" "$FILE"
        
        # Verify the change
        if diff -q "$FILE" "${FILE}.bak" > /dev/null; then
            echo -e "  ${YELLOW}⚠️  No changes in:${RESET} $FILE (strange, grep found a match)"
            UNCHANGED_FILES=$((UNCHANGED_FILES + 1))
            rm "${FILE}.bak"
        else
            echo -e "  ${GREEN}✓ Updated:${RESET} $FILE ${CYAN}($OCCURRENCES occurrences)${RESET}"
            CHANGED_FILES=$((CHANGED_FILES + 1))
            # Keep backup for safety, can be removed later
        fi
    else
        UNCHANGED_FILES=$((UNCHANGED_FILES + 1))
    fi
done

echo ""
echo -e "${CYAN}╔════════════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}║${RESET} ${YELLOW}Summary${RESET}                                     ${CYAN}║${RESET}"
echo -e "${CYAN}╚════════════════════════════════════════════════╝${RESET}"
echo -e "${GREEN}✓ Files updated:${RESET} $CHANGED_FILES"
echo -e "${YELLOW}⚠️  Files unchanged:${RESET} $UNCHANGED_FILES"
echo -e "${CYAN}ℹ️  Total files checked:${RESET} $TOTAL_FILES"

if [ $CHANGED_FILES -gt 0 ]; then
    echo ""
    echo -e "${YELLOW}Note:${RESET} Backup files (.bak) were created for changed files."
    echo -e "You can remove them after verifying the changes with:"
    echo -e "  ${CYAN}find . -name \"*.bak\" -delete${RESET}"
fi

echo ""
echo -e "${GREEN}Include path update complete!${RESET}"
