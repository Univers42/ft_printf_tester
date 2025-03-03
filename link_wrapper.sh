#!/bin/bash

# Set the working directory to the main project root
cd ..

# Colors for output
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
CYAN="\033[0;36m"
RESET="\033[0m"

echo -e "${CYAN}=== Finding Missing Object Files ===${RESET}"

# Look for the missing functions in source files
echo -e "${YELLOW}Looking for missing functions...${RESET}"

MISSING_FUNCTIONS=(
    "ft_print_width"
    "ft_flags_init"
    "ft_isflag"
    "ft_istype"
)

# Find files where these functions are defined
declare -A FUNCTION_FILES

# Search in src directory and all subdirectories (exclude ft_printf_tester)
for func in "${MISSING_FUNCTIONS[@]}"; do
    echo -ne "${YELLOW}Looking for $func...${RESET}"
    # Find files containing function definition
    FILES=$(grep -l "^[^/]*$func" --include="*.c" -r src/ 2>/dev/null || echo "")
    
    if [ -z "$FILES" ]; then
        echo -e "${RED}Not found!${RESET}"
    else
        FUNCTION_FILES[$func]="$FILES"
        echo -e "${GREEN}Found in: ${CYAN}$FILES${RESET}"
    fi
done

# Compile any files with missing functions if they don't have object files
mkdir -p obj
echo ""
echo -e "${CYAN}=== Compiling Missing Functions ===${RESET}"
for func in "${!FUNCTION_FILES[@]}"; do
    for file in ${FUNCTION_FILES[$func]}; do
        # Extract base file name and directory
        BASE_FILE=$(basename "$file" .c)
        DIR_NAME=$(dirname "$file" | sed 's|^src/||')
        OBJ_PATH="obj/$DIR_NAME"
        
        # Create directory if needed
        mkdir -p "$OBJ_PATH" 2>/dev/null
        
        # Check if we need to compile this file
        if [ ! -f "$OBJ_PATH/$BASE_FILE.o" ]; then
            echo -e "${YELLOW}Compiling $file for $func...${RESET}"
            gcc -Wall -Wextra -Werror -I. -I./include -c "$file" -o "$OBJ_PATH/$BASE_FILE.o"
            if [ $? -eq 0 ]; then
                echo -e "${GREEN}Successfully compiled $file${RESET}"
            else
                echo -e "${RED}Failed to compile $file${RESET}"
            fi
        else
            echo -e "${GREEN}Already compiled: $file${RESET}"
        fi
    done
done

# Create a supplemental archive with the missing functions
echo ""
echo -e "${CYAN}=== Creating Supplemental Archive ===${RESET}"
SUPP_OBJECTS=""
for func in "${!FUNCTION_FILES[@]}"; do
    for file in ${FUNCTION_FILES[$func]}; do
        BASE_FILE=$(basename "$file" .c)
        DIR_NAME=$(dirname "$file" | sed 's|^src/||')
        OBJ_PATH="obj/$DIR_NAME/$BASE_FILE.o"
        if [ -f "$OBJ_PATH" ]; then
            SUPP_OBJECTS="$SUPP_OBJECTS $OBJ_PATH"
        fi
    done
done

if [ -n "$SUPP_OBJECTS" ]; then
    # Create the supplemental archive
    ar rcs libftprintf_supp.a $SUPP_OBJECTS
    echo -e "${GREEN}Created supplemental archive with missing functions${RESET}"
else
    echo -e "${YELLOW}No supplemental objects to archive${RESET}"
fi

# Return to the tester directory
cd ft_printf_tester
echo -e "${GREEN}Done! Now run make again.${RESET}"
