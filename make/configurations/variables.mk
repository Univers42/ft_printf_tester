# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I../include -I../

# Directories
OBJ_DIR = Objects
PROGRAM_DIR = program
TESTER_DIR = .
PRINTF_DIR = ..
LIBFT_DIR = ../libft
ROOT_OBJ_DIR = ../Object
MK_DIR = make

# Source files - using enhanced find to explicitly discover all .c files with better debug output
# Filter out files in src/ directory, as they're meant for inclusion only
TESTER_SRCS = $(shell find $(TESTER_DIR) -type f -name "*.c" ! -path "*/src/*")
PRINTF_SRCS = $(shell find $(PRINTF_DIR) -type f -name "*.c" \
                ! -path "$(PRINTF_DIR)/ft_printf_tester/*" \
                ! -path "$(PRINTF_DIR)/framework_test/*" \
                ! -path "$(PRINTF_DIR)/libft/*")

# Identify utility files and main executable files more accurately
UTILITY_PATTERN = '.*_utils\.c\|.*_ft_printf\.c\|.*helper.*\.c\|.*common.*\.c\|.*globals.*\.c'
UTILITY_FILES = $(shell find $(TESTER_DIR) -type f -name "*.c" | grep -E '(_utils\.c|_ft_printf\.c|helper.*\.c|common.*\.c|globals.*\.c)$$')
UTILITY_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(UTILITY_FILES))

# Add globals file explicitly if it exists
GLOBALS_FILE = $(TESTER_DIR)/utils/ft_printf_test_globals.c
ifneq ($(wildcard $(GLOBALS_FILE)),)
    UTILITY_FILES += $(GLOBALS_FILE)
endif

# Extract test files with main functions (executables)
# We assume any file that's not a utility file and contains "int main" is an executable
MAIN_FILES = $(shell find $(TESTER_DIR) -type f -name "*.c" ! -path "*/src/*" | xargs grep -l "int main" 2>/dev/null || echo "")
MAIN_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(MAIN_FILES))
TEST_EXECUTABLES = $(patsubst $(OBJ_DIR)/tester/%.o,%,$(MAIN_OBJS))

# Other files that aren't utilities and don't have main functions are modules
MODULE_FILES = $(filter-out $(MAIN_FILES) $(UTILITY_FILES),$(TESTER_SRCS))
MODULE_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(MODULE_FILES))

# Generate object file paths with preserved directory structure
TESTER_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(TESTER_SRCS))
PRINTF_OBJS = $(patsubst $(PRINTF_DIR)/%.c,$(OBJ_DIR)/printf/%.o,$(PRINTF_SRCS))

# All object files
ALL_OBJS = $(TESTER_OBJS) $(PRINTF_OBJS)

# Define explicit list of testers for the program directory - preserving directory structure
TESTERS = $(patsubst %,$(PROGRAM_DIR)/%,$(TEST_EXECUTABLES))

# Debug information
$(info Total source files: $(words $(TESTER_SRCS)))
$(info Utility files: $(words $(UTILITY_FILES)))
$(info Main files: $(words $(MAIN_FILES)))
$(info Module files: $(words $(MODULE_FILES)))

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
