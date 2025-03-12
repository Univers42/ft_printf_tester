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

# Generate object file paths with preserved directory structure
TESTER_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(TESTER_SRCS))
PRINTF_OBJS = $(patsubst $(PRINTF_DIR)/%.c,$(OBJ_DIR)/printf/%.o,$(PRINTF_SRCS))

# All object files
ALL_OBJS = $(TESTER_OBJS) $(PRINTF_OBJS)

# Identify utility files and executables dynamically - more specific patterns
UTILITY_PATTERNS = "*_utils.c" "*_ft_printf.c" "ft_printf_test_utils.c" "simple_ft_printf.c"
UTILITY_FILES = $(shell find $(TESTER_DIR) -type f \( -name "*_utils.c" -o -name "*_ft_printf.c" -o -name "ft_printf_test_utils.c" -o -name "simple_ft_printf.c" \))
UTILITY_BASES = $(notdir $(basename $(UTILITY_FILES)))
UTILITY_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(UTILITY_FILES))

# Extract test names for executables (excluding utilities)
TEST_NAMES = $(patsubst $(TESTER_DIR)/%.c,%,$(TESTER_SRCS))
TEST_EXECUTABLES = $(filter-out $(UTILITY_BASES),$(TEST_NAMES))

# Define explicit list of testers for the program directory
TESTERS = $(addprefix $(PROGRAM_DIR)/,$(TEST_EXECUTABLES))

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
