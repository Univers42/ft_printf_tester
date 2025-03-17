# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 10:00:00 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/17 20:08:14 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Name of the output libraries
NAME = libtester.a
LIBPRINTF_PATH = ../
LIBPRINTF = $(LIBPRINTF_PATH)/libftprintf.a
LIBFT_PATH = ../libft
LIBFT = $(LIBFT_PATH)/libft.a

# Directory paths
SRC_DIR = .
OBJ_DIR = obj
HEADERS_DIR = headers
SRCS_DIR = srcs
UTILS_DIR = utils
PROGRAM_DIR = program
BIN_DIR = $(PROGRAM_DIR)/bin
TESTS_DIR = $(PROGRAM_DIR)/tests

# Find all .c files recursively in directories (excluding program dir if it exists)
SRCS = $(shell find $(UTILS_DIR) -name "*.c" -type f) \
       $(shell find $(SRCS_DIR) -name "*.c" -type f -not -path "*/$(PROGRAM_DIR)/*")

# Object files (automatically generated from source files)
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Test programs to build
TEST_PROGRAMS = mandatory_test char_tests_extended string_tests_extended int_tests_extended \
                unsigned_tests_extended hex_tests_extended ptr_tests_extended \
                flag_combinations_tester special_flags_tester debug_tester_simple \
                ft_printf_stress_tester

# Controller program
CONTROLLER = ft_printf_ultimate_controller

# Include directories for header files
INCLUDES = -I$(HEADERS_DIR) -I./includes -I$(LIBPRINTF_PATH) -I$(LIBFT_PATH)

# Default target
all: $(NAME) programs controller

# Rule to compile all libraries and programs
programs: make_libft make_libprintf $(NAME) prepare_dirs $(TEST_PROGRAMS)

# Create program directories with better organization
prepare_dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(TESTS_DIR)
	@mkdir -p $(PROGRAM_DIR)/utils/stress
	@echo "\033[32mProgram directories created\033[0m"

# Rule to compile libft using its Makefile
make_libft:
	@echo "\033[34mCompiling libft...\033[0m"
	@$(MAKE) -C $(LIBFT_PATH)

# Rule to compile libprintf using its Makefile
make_libprintf:
	@echo "\033[34mCompiling libftprintf...\033[0m"
	@$(MAKE) -C $(LIBPRINTF_PATH)

# Rule to create the tester library
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "\033[32mLibrary $(NAME) created successfully\033[0m"

# Rule to compile each source file to an object file
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rules to build each test program
mandatory_test: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling mandatory test...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/ft_printf_$@ $(SRCS_DIR)/tests/ft_printf_mandatory_test.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

char_tests_extended: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/char_tests_extended.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

string_tests_extended: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/string_tests_extended.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

int_tests_extended: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/int_tests_extended.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

unsigned_tests_extended: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/unsigned_tests_extended.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

hex_tests_extended: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/hex_tests_extended.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

ptr_tests_extended: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/ptr_tests_extended.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

flag_combinations_tester: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/flag_combinations_tester.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

special_flags_tester: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/special_flags_tester.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

debug_tester_simple: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/ft_printf_$@ $(SRCS_DIR)/tests/ft_printf_debug_tester_simple.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

# For stress tester, prepare directories for stress-specific utility files
ft_printf_stress_tester: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $@...\033[0m"
	@cp $(UTILS_DIR)/ft_printf_stress_*.c $(PROGRAM_DIR)/utils/stress/ 2>/dev/null || :
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/ft_printf_stress_tester.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@echo "\033[32m$@ created successfully\033[0m"

# Compile the ultimate controller
controller: prepare_dirs $(NAME) make_libft make_libprintf
	@echo "\033[34mCompiling $(CONTROLLER)...\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(CONTROLLER) $(SRCS_DIR)/ft_printf_ultimate_controller.c $(NAME) $(LIBPRINTF) $(LIBFT)
	@ln -sf $(BIN_DIR)/$(CONTROLLER) ./tester
	@echo "\033[32mController compiled and symlink 'tester' created\033[0m"

# Run the controller directly
run: controller programs
	@echo "\033[34mRunning Ultimate FT_PRINTF Controller...\033[0m"
	@./tester

# Clean object files
clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(LIBPRINTF_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "\033[33mObject files removed\033[0m"

# Clean object files and the libraries
fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(MAKE) -C $(LIBPRINTF_PATH) fclean
	@rm -f $(NAME)
	@rm -f tester
	@rm -rf $(PROGRAM_DIR)
	@echo "\033[31mLibraries and programs removed\033[0m"

# Rebuild the project
re: fclean all

# Ensure that these rules are not interpreted as files
.PHONY: all clean fclean re programs make_libft make_libprintf controller run prepare_dirs $(TEST_PROGRAMS)

# Print all source files found (useful for debugging)
print_sources:
	@echo "Source files:"
	@echo $(SRCS) | tr ' ' '\n'

# Run make ensure_testers to compile all test programs
ensure_testers: programs controller
	@echo "\033[32mAll test programs compiled successfully\033[0m"
