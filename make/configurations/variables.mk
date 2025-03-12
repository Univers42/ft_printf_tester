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

# Source files - completely dynamic discovery in any directory
# Exclude specific system directories and object directories
EXCLUDE_DIRS = -path "*/\.*" -o -path "*/libft/*" -o -path "*/Object*" -o -path "*/program/*" -o -path "*/framework_test/*"
TESTER_C_FILES = $(shell find $(TESTER_DIR) -type f -name "*.c" ! \( $(EXCLUDE_DIRS) \) 2>/dev/null)
TESTER_H_FILES = $(shell find $(TESTER_DIR) -type f -name "*.h" ! \( $(EXCLUDE_DIRS) \) 2>/dev/null)

PRINTF_SRCS = $(shell find $(PRINTF_DIR) -type f -name "*.c" \
                ! -path "$(PRINTF_DIR)/ft_printf_tester/*" \
                ! -path "$(PRINTF_DIR)/framework_test/*" \
                ! -path "$(PRINTF_DIR)/libft/*" \
                ! -path "$(PRINTF_DIR)/Object*/*" \
                ! -path "$(PRINTF_DIR)/program/*")

# Identify utility files and main executable files more accurately
UTILITY_FILES = $(shell find $(TESTER_DIR) -type f -name "*.c" | grep -E '(_utils\.c|_ft_printf\.c|helper.*\.c|common.*\.c|globals.*\.c)$$')
UTILITY_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(UTILITY_FILES))

# Add globals file explicitly if it exists
GLOBALS_FILE = $(shell find $(TESTER_DIR) -name "ft_printf_test_globals.c")
ifneq ($(GLOBALS_FILE),)
    UTILITY_FILES += $(GLOBALS_FILE)
endif

# Find all executable files (with main function) across the entire project
MAIN_FILES = $(shell find $(TESTER_DIR) -type f -name "*.c" | xargs grep -l "int main" 2>/dev/null || echo "")

# Transform paths for object files
MAIN_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(MAIN_FILES))
TEST_EXECUTABLES = $(patsubst $(OBJ_DIR)/tester/%.o,%,$(MAIN_OBJS))

# Other files that aren't utilities and don't have main functions are modules
MODULE_FILES = $(filter-out $(MAIN_FILES) $(UTILITY_FILES),$(TESTER_C_FILES))
MODULE_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(MODULE_FILES))

# Generate object file paths with preserved directory structure
TESTER_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(TESTER_C_FILES))
PRINTF_OBJS = $(patsubst $(PRINTF_DIR)/%.c,$(OBJ_DIR)/printf/%.o,$(PRINTF_SRCS))

# All object files
ALL_OBJS = $(TESTER_OBJS) $(PRINTF_OBJS)

# For executables, flatten the structure in the program directory
FLAT_EXECUTABLES = $(notdir $(TEST_EXECUTABLES))
FLAT_TESTERS = $(addprefix $(PROGRAM_DIR)/,$(FLAT_EXECUTABLES))

# Original structure for special executables
TESTERS = $(patsubst %,$(PROGRAM_DIR)/%,$(TEST_EXECUTABLES))

# Debug information
$(info Total source files: $(words $(TESTER_C_FILES)))
$(info Total header files: $(words $(TESTER_H_FILES)))
$(info Utility files: $(words $(UTILITY_FILES)))
$(info Main files: $(words $(MAIN_FILES)))
$(info Module files: $(words $(MODULE_FILES)))
$(info Executable names: $(FLAT_EXECUTABLES))
$(info Source directories: $(sort $(dir $(TESTER_C_FILES))))

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
