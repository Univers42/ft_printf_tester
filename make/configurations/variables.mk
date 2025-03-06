# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    variables.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 13:51:20 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/06 15:01:20 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I../include -I../

# Directories
OBJ_DIR = Objects
PROGRAM_DIR = program
TESTER_DIR = .
PRINTF_DIR = ..
LIBFT_DIR = /home/dyl-syzygy/goinfre/ft_printf2/libft
ROOT_OBJ_DIR = ../Object
MK_DIR = make

# Source files - using enhanced find to explicitly discover all .c files with better debug output
TESTER_SRCS = $(shell find $(TESTER_DIR) -type f -name "*.c")
PRINTF_SRCS = $(shell find $(PRINTF_DIR) -type f -name "*.c" \
                ! -path "$(PRINTF_DIR)/ft_printf_tester/*" \
                ! -path "$(PRINTF_DIR)/framework_test/*" \
                ! -path "$(PRINTF_DIR)/libft/*")

# Generate object file paths with preserved directory structure
TESTER_OBJS = $(patsubst $(TESTER_DIR)/%.c,$(OBJ_DIR)/tester/%.o,$(TESTER_SRCS))
PRINTF_OBJS = $(patsubst $(PRINTF_DIR)/%.c,$(OBJ_DIR)/printf/%.o,$(PRINTF_SRCS))

# All object files
ALL_OBJS = $(TESTER_OBJS) $(PRINTF_OBJS)

# Extract test names for executables
TEST_NAMES = $(patsubst $(TESTER_DIR)/%.c,%,$(TESTER_SRCS))
TEST_UTILS = ft_printf_test_utils
SIMPLE_PRINTF = simple_ft_printf
TEST_UTILS_OBJ = $(OBJ_DIR)/tester/$(TEST_UTILS).o
SIMPLE_PRINTF_OBJ = $(OBJ_DIR)/tester/$(SIMPLE_PRINTF).o
# Properly exclude the test utils from executables
TEST_EXECUTABLES = $(filter-out $(TEST_UTILS) $(SIMPLE_PRINTF),$(TEST_NAMES))

# Define explicit list of testers for the program directory
TESTERS = $(addprefix $(PROGRAM_DIR)/,$(TEST_EXECUTABLES))

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
