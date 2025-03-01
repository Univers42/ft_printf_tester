# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 12:00:00 by syzygy            #+#    #+#              #
#    Updated: 2024/05/20 12:00:00 by syzygy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I../

# Directories
OBJ_DIR = obj
PROGRAM_DIR = program
SRC_DIR = .
PRINTF_DIR = ..
LIBFT_DIR = ../libft

# Source files for ft_printf
PRINTF_SRCS = $(PRINTF_DIR)/ft_printf.c \
              $(PRINTF_DIR)/ft_print_char.c \
              $(PRINTF_DIR)/ft_print_str.c \
              $(PRINTF_DIR)/ft_print_hex.c \
              $(PRINTF_DIR)/ft_print_int.c \
              $(PRINTF_DIR)/ft_print_ptr.c \
              $(PRINTF_DIR)/ft_print_unsigned.c \
              $(PRINTF_DIR)/ft_nbr_len.c \
              $(PRINTF_DIR)/ft_flags.c \
              $(PRINTF_DIR)/ft_flags_utils.c \
              $(PRINTF_DIR)/ft_print_flag.c \
              $(PRINTF_DIR)/ft_printf_itoa.c \
              $(PRINTF_DIR)/ft_printf_utoa.c \
              $(PRINTF_DIR)/ft_printf_xtoa.c \
              $(PRINTF_DIR)/ft_print_width.c \
              $(PRINTF_DIR)/ft_print_nbr.c

# Source files for testers
TEST_SRCS = ft_printf_test_utils.c \
            ft_printf_tester.c \
            ft_printf_debug_tester.c \
            ft_printf_debug_tester_simple.c \
            ft_printf_stress_tester.c \
            flag_combinations_tester.c \
            char_tests.c \
            char_tests_extended.c \
            string_tests_extended.c \
            int_tests_extended.c \
            ptr_tests_extended.c \
            unsigned_tests_extended.c \
            hex_tests_extended.c \
            special_flags_tester.c \
            basic_test.c \
            ultimate_tester.c \
            ft_printf_ultimate_controller.c

# Object files
PRINTF_OBJS = $(patsubst $(PRINTF_DIR)/%.c,$(OBJ_DIR)/%.o,$(PRINTF_SRCS))
OBJ_UTILS = $(OBJ_DIR)/ft_printf_test_utils.o

# Testing executables
TESTERS = ft_printf_tester \
          ft_printf_debug_tester \
          ft_printf_debug_tester_simple \
          ft_printf_stress_tester \
          flag_combinations_tester \
          char_tests \
          char_tests_extended \
          string_tests_extended \
          int_tests_extended \
          ptr_tests_extended \
          unsigned_tests_extended \
          hex_tests_extended \
          special_flags_tester \
          basic_test \
          ultimate_tester \
          ultimate_tester_extended

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

# Default target - ensure we build all testers first
all: $(OBJ_DIR) $(PROGRAM_DIR) $(LIBFT) $(TESTERS)
	@echo "All test programs have been compiled. Use 'make controller' to run the test controller."

# Create obj directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Create program directory
$(PROGRAM_DIR):
	@mkdir -p $(PROGRAM_DIR)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile ft_printf source files
$(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile test source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean targets
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(PROGRAM_DIR)

re: fclean all

# Individual test runners with explicit rules to preserve target logic

# Basic tester
ft_printf_tester: $(OBJ_DIR)/ft_printf_tester.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Debug tester
ft_printf_debug_tester: $(OBJ_DIR)/ft_printf_debug_tester.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Simple debug tester
ft_printf_debug_tester_simple: $(OBJ_DIR)/ft_printf_debug_tester_simple.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Stress tester
ft_printf_stress_tester: $(OBJ_DIR)/ft_printf_stress_tester.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Character tests
char_tests: $(OBJ_DIR)/char_tests.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Extended character tests
char_tests_extended: $(OBJ_DIR)/char_tests_extended.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# String tests
string_tests_extended: $(OBJ_DIR)/string_tests_extended.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Integer tests
int_tests_extended: $(OBJ_DIR)/int_tests_extended.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Pointer extended tests
ptr_tests_extended: $(OBJ_DIR)/ptr_tests_extended.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Unsigned integer tests
unsigned_tests_extended: $(OBJ_DIR)/unsigned_tests_extended.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Hexadecimal tests
hex_tests_extended: $(OBJ_DIR)/hex_tests_extended.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Flag combinations tester
flag_combinations_tester: $(OBJ_DIR)/flag_combinations_tester.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Special flags tester
special_flags_tester: $(OBJ_DIR)/special_flags_tester.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Basic test
basic_test: $(OBJ_DIR)/basic_test.o $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Rule for the ultimate tester
ultimate_tester: $(OBJ_DIR)/ultimate_tester.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Rule for the ultimate_tester_extended (controller)
ultimate_tester_extended: $(OBJ_DIR)/ft_printf_ultimate_controller.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(PROGRAM_DIR)/$@ $^ $(LIBFT)

# Run tests with shortcut commands
simple: ft_printf_debug_tester_simple
	./$(PROGRAM_DIR)/ft_printf_debug_tester_simple

debug: ft_printf_debug_tester
	./$(PROGRAM_DIR)/ft_printf_debug_tester

stress: ft_printf_stress_tester
	./$(PROGRAM_DIR)/ft_printf_stress_tester

flags: flag_combinations_tester
	./$(PROGRAM_DIR)/flag_combinations_tester

char: char_tests
	./$(PROGRAM_DIR)/char_tests

chars_ex: char_tests_extended
	./$(PROGRAM_DIR)/char_tests_extended

ultimate: ultimate_tester
	./$(PROGRAM_DIR)/ultimate_tester

# Add shortcut command to run the controller
extended: ensure_testers ultimate_tester_extended
	./$(PROGRAM_DIR)/ultimate_tester_extended

# Another alias for the controller
controller: ensure_testers ultimate_tester_extended
	./$(PROGRAM_DIR)/ultimate_tester_extended

# Add explicit targets for each test program to ensure they're built
# This prevents the controller from trying to run programs that don't exist
ensure_testers: $(TESTERS)
	@echo "All test programs built successfully."
	@ls -la $(PROGRAM_DIR)

# Run all tests
test: $(TESTERS)
	@echo "Running all tests..."
	@for tester in $(TESTERS); do \
		echo "\n===== Running $$tester ====="; \
		./$(PROGRAM_DIR)/$$tester || true; \
	done

.PHONY: all clean fclean re simple debug stress flags char chars_ex ultimate test extended controller