# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 20:30:00 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/17 22:41:53 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Core Configuration                   ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Compiler configuration
CC := gcc
CFLAGS := -Wall -Wextra -Werror

# Name of the output library
NAME := libtester.a

# External libraries configurations
LIBPRINTF_PATH := ../
LIBPRINTF := $(LIBPRINTF_PATH)/libftprintf.a
LIBFT_PATH := ../libft
LIBFT := $(LIBFT_PATH)/libft.a

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Directory Structure                  ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Directory paths
SRC_DIR := .
OBJ_DIR := obj
HEADERS_DIR := headers
SRCS_DIR := srcs
UTILS_DIR := utils
PROGRAM_DIR := program
BIN_DIR := $(PROGRAM_DIR)/bin
TESTS_DIR := $(PROGRAM_DIR)/tests

# Controller program name
CONTROLLER := ft_printf_ultimate_controller

# Include directories for header files
INCLUDES := -I$(HEADERS_DIR) -I./includes -I$(LIBPRINTF_PATH) -I$(LIBFT_PATH)

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Test Suite Definition                ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Test programs to build
TEST_PROGRAMS := mandatory_test \
                 char_tests_extended \
                 string_tests_extended \
                 int_tests_extended \
                 unsigned_tests_extended \
                 hex_tests_extended \
                 ptr_tests_extended \
                 flag_combinations_tester \
                 special_flags_tester \
                 debug_tester_simple \
                 ft_printf_stress_tester
