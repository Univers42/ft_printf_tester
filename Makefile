# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 01:17:50 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/02 01:57:52 by dyl-syzygy       ###   ########.fr        #
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
TEST_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))
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

# Colors and styles
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[1;37m
ORANGE = \033[38;5;208m
PINK = \033[38;5;206m
LIME = \033[38;5;118m
RESET = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
HIDDEN = \033[8m
BG_GREEN = \033[48;5;22m
BG_BLUE = \033[48;5;18m

# Default target - ensure we build all testers first
all: header_all make_dirs $(LIBFT) $(addprefix $(PROGRAM_DIR)/,$(TESTERS)) footer_all

# Display header for all target
header_all:
	@clear
	@echo "$(CYAN)"
	@echo "╔══════════════════════════════════════════════════════════════════════╗"
	@echo "║ $(BOLD)$(ORANGE)    _____ _____    ____  ____  ___ _   _ _____ _____    _____      $(CYAN) ║"
	@echo "║ $(BOLD)$(ORANGE)   |  ___|_   _|  |  _ \\|  _ \\|_ _| \\ | |_   _|  ___|  |_   _|     $(CYAN) ║"
	@echo "║ $(BOLD)$(ORANGE)   | |_    | |    | |_) | |_) || ||  \\| | | | | |_      | |       $(CYAN) ║"
	@echo "║ $(BOLD)$(ORANGE)   |  _|   | |    |  __/|  _ < | || |\\  | | | |  _|     | |       $(CYAN) ║"
	@echo "║ $(BOLD)$(ORANGE)   |_|     |_|    |_|   |_| \\_\\___|_| \\_| |_| |_|       |_|       $(CYAN) ║"
	@echo "║                                                                      ║"
	@echo "║ $(YELLOW)                    T  E  S  T     S  U  I  T  E                    $(CYAN) ║"
	@echo "╚══════════════════════════════════════════════════════════════════════╝$(RESET)"
	@printf "$(BOLD)$(BLUE)╔═════════════════════════════════════════════════════════════════════╗\n$(RESET)"
	@printf "$(BOLD)$(BLUE)║ $(LIME)⚡ Building ft_printf test suite$(BLUE)                                  ║\n$(RESET)"
	@printf "$(BOLD)$(BLUE)╚═════════════════════════════════════════════════════════════════════╝\n\n$(RESET)"

# Display footer for all target
footer_all:
	@printf "\n$(BOLD)$(BLUE)╔═══════════════════════════════════════════════════════════════════════╗\n$(RESET)"
	@printf "$(BOLD)$(BLUE)║ $(GREEN)✓ All test programs compiled successfully!$(BLUE)                         ║\n$(RESET)"
	@printf "$(BOLD)$(BLUE)╚═══════════════════════════════════════════════════════════════════════╝\n$(RESET)"
	@echo ""
	@echo "$(PURPLE)┌─────────────────────────────────────────────────────────────────┐$(RESET)"
	@echo "$(PURPLE)│$(YELLOW) Use $(CYAN)'make controller'$(YELLOW) to run the comprehensive test controller $(PURPLE)│$(RESET)"
	@echo "$(PURPLE)└─────────────────────────────────────────────────────────────────┘$(RESET)"
	@sleep 0.5
	@echo ""
	@echo "$(BOLD)$(CYAN)Available test targets:$(RESET)"
	@echo "$(GREEN)➤ $(YELLOW)make simple$(RESET)    - Run simple debug test"
	@echo "$(GREEN)➤ $(YELLOW)make debug$(RESET)     - Run debug test"
	@echo "$(GREEN)➤ $(YELLOW)make stress$(RESET)    - Run stress test"
	@echo "$(GREEN)➤ $(YELLOW)make flags$(RESET)     - Run flag combinations test"
	@echo "$(GREEN)➤ $(YELLOW)make char$(RESET)      - Run character tests"
	@echo "$(GREEN)➤ $(YELLOW)make chars_ex$(RESET)  - Run extended character tests"
	@echo "$(GREEN)➤ $(YELLOW)make ultimate$(RESET)  - Run ultimate test"
	@echo "$(GREEN)➤ $(YELLOW)make test$(RESET)      - Run all tests with summary"

# Create directories
make_dirs:
	@echo "$(YELLOW)⚙ Setting up build environment...$(RESET)"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(PROGRAM_DIR)
	@for i in 1 2 3; do \
		printf "$(YELLOW)  ⇒ Creating build structure $(CYAN)["; \
		for j in 1 2 3 4 5; do \
			printf "▓"; \
			sleep 0.01; \
		done; \
		printf "]$(RESET)\r"; \
		sleep 0.1; \
	done
	@echo "$(GREEN)  ✓ Build directories ready!        $(RESET)"

# Build libft
$(LIBFT):
	@printf "$(BLUE)╔════════════════════════════════════╗\n$(RESET)"
	@printf "$(BLUE)║ $(YELLOW)Building libft dependencies...$(BLUE)    ║\n$(RESET)"
	@printf "$(BLUE)╚════════════════════════════════════╝\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)  ✓ Libft built successfully!$(RESET)"

# Compile ft_printf source files
$(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c
	@if [ ! -f $(OBJ_DIR)/.header_printed ]; then \
		printf "$(BLUE)╔════════════════════════════════════╗\n$(RESET)"; \
		printf "$(BLUE)║ $(PURPLE)Compiling Source Files...$(BLUE)         ║\n$(RESET)"; \
		printf "$(BLUE)╚════════════════════════════════════╝\n$(RESET)"; \
		touch $(OBJ_DIR)/.header_printed; \
	fi
	@printf "  $(CYAN)%-30s $(YELLOW)→ $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile test source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -f $(OBJ_DIR)/.test_header_printed ]; then \
		printf "$(BLUE)╔════════════════════════════════════╗\n$(RESET)"; \
		printf "$(BLUE)║ $(PURPLE)Building Test Components...$(BLUE)        ║\n$(RESET)"; \
		printf "$(BLUE)╚════════════════════════════════════╝\n$(RESET)"; \
		touch $(OBJ_DIR)/.test_header_printed; \
	fi
	@printf "  $(CYAN)%-30s $(YELLOW)→ $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build tester executables
$(PROGRAM_DIR)/%: $(OBJ_DIR)/%.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	@if [ ! -f $(OBJ_DIR)/.link_header_printed ]; then \
		printf "$(BLUE)╔════════════════════════════════════╗\n$(RESET)"; \
		printf "$(BLUE)║ $(LIME)Building Test Executables...$(BLUE)       ║\n$(RESET)"; \
		printf "$(BLUE)╚════════════════════════════════════╝\n$(RESET)"; \
		touch $(OBJ_DIR)/.link_header_printed; \
	fi
	@printf "  $(PURPLE)%-30s $(YELLOW)→ $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@sleep 0.05

# Special rule for ultimate_tester_extended
$(PROGRAM_DIR)/ultimate_tester_extended: $(OBJ_DIR)/ft_printf_ultimate_controller.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	@printf "  $(PURPLE)%-30s $(YELLOW)→ $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@sleep 0.05

# Clean targets
clean:
	@printf "$(BG_BLUE)$(BOLD)$(WHITE) CLEANING $(RESET)\n"
	@printf "$(YELLOW)⚙ Removing object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@for i in $(shell seq 1 50); do \
		printf "$(YELLOW)[$(GREEN)%-50s$(YELLOW)]$(RESET)\r" "$$(printf '%*s' $$i '' | tr ' ' '=')" ; \
		sleep 0.01; \
	done
	@echo "$(GREEN)✓ Clean complete!$(RESET)"

fclean: clean
	@printf "$(YELLOW)⚙ Removing executables...$(RESET)\n"
	@rm -rf $(PROGRAM_DIR)
	@for i in $(shell seq 1 50); do \
		printf "$(YELLOW)[$(GREEN)%-50s$(YELLOW)]$(RESET)\r" "$$(printf '%*s' $$i '' | tr ' ' '=')" ; \
		sleep 0.01; \
	done
	@echo "$(GREEN)✓ Full clean complete!$(RESET)"

re: fclean all

# Test command display header
define test_header
	@echo ""
	@echo "$(BG_GREEN)$(BOLD)$(WHITE) RUNNING TEST: $(UNDERLINE)$(1)$(RESET)$(BG_GREEN)$(BOLD)$(WHITE) $(RESET)"
	@echo "$(CYAN)╭───────────────────────────────────────────────────────────╮$(RESET)"
	@echo "$(CYAN)│$(RESET) $(BOLD)$(YELLOW)Test Starting...$(RESET)                                         $(CYAN)│$(RESET)"
	@echo "$(CYAN)╰───────────────────────────────────────────────────────────╯$(RESET)"
	@sleep 0.3
endef

# Specific test commands
simple: $(PROGRAM_DIR)/ft_printf_debug_tester_simple
	$(call test_header,SIMPLE DEBUG TEST)
	@$(PROGRAM_DIR)/ft_printf_debug_tester_simple

debug: $(PROGRAM_DIR)/ft_printf_debug_tester
	$(call test_header,DEBUG TEST)
	@$(PROGRAM_DIR)/ft_printf_debug_tester

stress: $(PROGRAM_DIR)/ft_printf_stress_tester
	$(call test_header,STRESS TEST)
	@$(PROGRAM_DIR)/ft_printf_stress_tester

flags: $(PROGRAM_DIR)/flag_combinations_tester
	$(call test_header,FLAG COMBINATIONS TEST)
	@$(PROGRAM_DIR)/flag_combinations_tester

char: $(PROGRAM_DIR)/char_tests
	$(call test_header,CHARACTER TESTS)
	@$(PROGRAM_DIR)/char_tests

chars_ex: $(PROGRAM_DIR)/char_tests_extended
	$(call test_header,EXTENDED CHARACTER TESTS)
	@$(PROGRAM_DIR)/char_tests_extended

ultimate: $(PROGRAM_DIR)/ultimate_tester
	$(call test_header,ULTIMATE TEST)
	@$(PROGRAM_DIR)/ultimate_tester

# Run controller
controller: $(PROGRAM_DIR)/ultimate_tester_extended
	@clear
	@echo "$(CYAN)╔══════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║ $(BOLD)$(PINK)    F T _ P R I N T F   T E S T   C O N T R O L L E R    $(RESET)$(CYAN)         ║$(RESET)"
	@echo "$(CYAN)╚══════════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(YELLOW)⚙ Launching comprehensive test suite...$(RESET)"
	@echo ""
	@sleep 0.5
	@$(PROGRAM_DIR)/ultimate_tester_extended

# Extended controller (same as controller)
extended: controller

# Run all tests
test: $(addprefix $(PROGRAM_DIR)/,$(TESTERS))
	@clear
	@echo "$(BG_BLUE)$(BOLD)$(WHITE) FT_PRINTF COMPLETE TEST SUITE $(RESET)"
	@echo ""
	@echo "$(CYAN)╭───────────────────────────────────────────────────────────╮$(RESET)"
	@echo "$(CYAN)│$(RESET) $(BOLD)$(YELLOW)Running all tests sequentially...$(RESET)                        $(CYAN)│$(RESET)"
	@echo "$(CYAN)╰───────────────────────────────────────────────────────────╯$(RESET)"
	@echo ""
	@sleep 0.3
	
	@total=0; passed=0; failed=0; \
	for tester in $(TESTERS); do \
		total=$$((total+1)); \
		printf "$(YELLOW)▶ %-30s$(RESET) " "$$tester"; \
		for i in $(shell seq 1 10); do \
			printf "."; \
			sleep 0.03; \
		done; \
		printf " "; \
		if $(PROGRAM_DIR)/$$tester >/dev/null 2>&1; then \
			printf "$(GREEN)[PASS]$(RESET)\n"; \
			passed=$$((passed+1)); \
		else \
			printf "$(RED)[FAIL]$(RESET)\n"; \
			failed=$$((failed+1)); \
		fi; \
	done; \
	echo ""; \
	printf "$(BOLD)$(BLUE)╔═════════════════════════════════════════╗\n$(RESET)"; \
	printf "$(BOLD)$(BLUE)║ $(WHITE)         TEST SUMMARY              $(BLUE) ║\n$(RESET)"; \
	printf "$(BOLD)$(BLUE)╠═════════════════════════════════════════╣\n$(RESET)"; \
	printf "$(BOLD)$(BLUE)║ $(CYAN)Total tests:  $(WHITE)%-22d$(BLUE) ║\n$(RESET)" $$total; \
	printf "$(BOLD)$(BLUE)║ $(GREEN)Tests passed: $(WHITE)%-22d$(BLUE) ║\n$(RESET)" $$passed; \
	printf "$(BOLD)$(BLUE)║ $(RED)Tests failed: $(WHITE)%-22d$(BLUE) ║\n$(RESET)" $$failed; \
	printf "$(BOLD)$(BLUE)╠═════════════════════════════════════════╣\n$(RESET)"; \
	percentage=$$((passed * 100 / total)); \
	printf "$(BOLD)$(BLUE)║ $(WHITE)Success rate: $(YELLOW)%d%%$(WHITE)                  $(BLUE) ║\n$(RESET)" $$percentage; \
	printf "$(BOLD)$(BLUE)╚═════════════════════════════════════════╝\n$(RESET)"; \
	if [ $$failed -eq 0 ]; then \
		echo "$(GREEN)All tests passed! Your implementation looks good.$(RESET)"; \
	else \
		echo "$(YELLOW)Some tests failed. More work needed.$(RESET)"; \
	fi

.PHONY: all header_all footer_all make_dirs clean fclean re simple debug stress flags char chars_ex ultimate controller extended test