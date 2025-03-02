# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 01:17:50 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/02 02:48:43 by dyl-syzygy       ###   ########.fr        #
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

# ★彡 ULTRA COLOR PALETTE AND STYLES 彡★
# Basic Colors
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
GRAY = \033[0;90m

# Bold Colors
BOLD_BLACK = \033[1;30m
BOLD_RED = \033[1;31m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
BOLD_BLUE = \033[1;34m
BOLD_PURPLE = \033[1;35m
BOLD_CYAN = \033[1;36m
BOLD_WHITE = \033[1;37m
BOLD_GRAY = \033[1;90m

# Special Colors 
PINK = \033[38;5;206m
ORANGE = \033[38;5;208m
LIME = \033[38;5;118m
SKY = \033[38;5;39m
GOLD = \033[38;5;220m
TEAL = \033[38;5;6m
LAVENDER = \033[38;5;147m
PEACH = \033[38;5;215m
MINT = \033[38;5;84m
SALMON = \033[38;5;209m
INDIGO = \033[38;5;62m
TURQUOISE = \033[38;5;80m
MAGENTA = \033[38;5;201m
OLIVE = \033[38;5;142m

# Background Colors
BG_BLACK = \033[40m
BG_RED = \033[41m
BG_GREEN = \033[42m
BG_YELLOW = \033[43m
BG_BLUE = \033[44m
BG_PURPLE = \033[45m
BG_CYAN = \033[46m
BG_WHITE = \033[47m
BG_GRAY = \033[100m

# Special Background Colors
BG_PINK = \033[48;5;206m
BG_ORANGE = \033[48;5;208m
BG_LIME = \033[48;5;118m
BG_SKY = \033[48;5;39m
BG_GOLD = \033[48;5;220m
BG_DARK_BLUE = \033[48;5;18m
BG_DARK_GREEN = \033[48;5;22m
BG_DARK_RED = \033[48;5;52m
BG_DARK_PURPLE = \033[48;5;54m

# Text Styles
BOLD = \033[1m
FAINT = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
HIDDEN = \033[8m
STRIKE = \033[9m

# Reset
RESET = \033[0m

# Special Characters and Glyphs
CHECK = ✓
CROSS = ✗
STAR = ★
SPARKLE = ✨
ARROW_RIGHT = →
ARROW_LEFT = ←
ARROW_UP = ↑
ARROW_DOWN = ↓
LIGHTNING = ⚡
HAMMER = 🔨
GEAR = ⚙
WARN = ⚠
INFO = ℹ
OK = ✓
FIRE = 🔥
ROCKET = 🚀
LIGHT = 💡
CLOCK = 🕒
DIAMOND = ♦
HEART = ♥
CLUB = ♣
SPADE = ♠
SMILE = 😊
THINK = 🤔
COOL = 😎

# ⚡ Master Versions ⚡
SUCCESS = $(BOLD_GREEN)$(CHECK) 
ERROR = $(BOLD_RED)$(CROSS) 
WARNING = $(BOLD_YELLOW)$(WARN) 
INFO_MARK = $(BOLD_BLUE)$(INFO) 
WORKING = $(BOLD_CYAN)$(GEAR) 
FLAME = $(BOLD_ORANGE)$(FIRE) 
BEAM = $(BOLD_CYAN)$(LIGHT) 
BLAST = $(BOLD_YELLOW)$(ROCKET) 
TIME = $(BOLD_PURPLE)$(CLOCK) 

# Default target - ensure we build all testers first
all: intro header_all make_dirs $(LIBFT) $(addprefix $(PROGRAM_DIR)/,$(TESTERS)) footer_all

# Amazing intro animation
intro:
	@clear
	@echo ""
	@for i in 1 2 3 ; do \
		printf "\r$(BLUE)$(BOLD)Initializing$(RESET)" ; \
		sleep 0.1 ; \
		printf "\r$(BLUE)$(BOLD)Initializing.$(RESET)" ; \
		sleep 0.1 ; \
		printf "\r$(BLUE)$(BOLD)Initializing..$(RESET)" ; \
		sleep 0.1 ; \
		printf "\r$(BLUE)$(BOLD)Initializing...$(RESET)" ; \
		sleep 0.1 ; \
	done
	@clear
	@echo ""
	@echo "$(BLUE)╭─────────────────────────────────────────────────────────╮"
	@sleep 0.05
	@echo "│                                                         │"
	@sleep 0.05
	@echo "│$(BOLD_YELLOW)                  SYSTEM INITIALIZATION                  $(BLUE)│"
	@sleep 0.05
	@echo "│                                                         │"
	@sleep 0.05
	@echo "╰─────────────────────────────────────────────────────────╯$(RESET)"
	@echo ""
	@for i in $(shell seq 1 50); do \
		if [ $$i -le 20 ]; then \
			printf "$(CYAN)$(BOLD)▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓$(RESET)\r"; \
		elif [ $$i -le 40 ]; then \
			printf "$(YELLOW)$(BOLD)▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓$(RESET)\r"; \
		else \
			printf "$(GREEN)$(BOLD)▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓$(RESET)\r"; \
		fi; \
		sleep 0.02; \
	done
	@printf "\n\n"
	@echo "$(BOLD)$(GREEN)SYSTEM READY$(RESET)"
	@sleep 0.5
	@clear

# Display header for all target with improved design (no dark background)
header_all:
	@echo ""
	@echo "$(TEAL)╔═════════════════════════════════════════════════════════════════════════════╗"
	@echo "║ $(BG_DARK_BLUE)$(BOLD)                                                                           $(RESET) ║"
	@echo "║ $(BG_DARK_BLUE)$(BOLD_CYAN)    ███████╗████████╗    ██████╗ ██████╗ ██╗███╗   ██╗████████╗███████╗    $(RESET)$(TEAL) ║"
	@echo "║ $(BG_DARK_BLUE)$(BOLD_CYAN)    ██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██║████╗  ██║╚══██╔══╝██╔════╝    $(RESET)$(TEAL) ║"
	@echo "║ $(BG_DARK_BLUE)$(BOLD_SKY)    █████╗     ██║       ██████╔╝██████╔╝██║██╔██╗ ██║   ██║   █████╗      $(RESET)$(TEAL) ║"
	@echo "║ $(BG_DARK_BLUE)$(BOLD_SKY)    ██╔══╝     ██║       ██╔═══╝ ██╔══██╗██║██║╚██╗██║   ██║   ██╔══╝      $(RESET)$(TEAL) ║"
	@echo "║ $(BG_DARK_BLUE)$(BOLD_CYAN)    ██║        ██║       ██║     ██║  ██║██║██║ ╚████║   ██║   ██║         $(RESET)$(TEAL) ║"
	@echo "║ $(BG_DARK_BLUE)$(BOLD_CYAN)    ╚═╝        ╚═╝       ╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝         $(RESET)$(TEAL) ║"
	@echo "║ $(BG_DARK_BLUE)$(BOLD)                                                                           $(RESET)$(TEAL) ║"
	@echo "║ $(BG_DARK_BLUE)$(TURQUOISE)                          T E S T   S U I T E                              $(RESET)$(TEAL) ║"
	@echo "║ $(BG_DARK_BLUE)$(BOLD)                                                                           $(RESET)$(TEAL) ║"
	@echo "╚═════════════════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(CYAN)╭───────────────────────────────────────────────────────────────────╮"
	@echo "│$(REVERSE)$(BOLD) FT_PRINTF TEST SUITE COMPILATION SYSTEM v1.0 $(RESET)$(CYAN)                     │"
	@echo "╰───────────────────────────────────────────────────────────────────╯$(RESET)"
	@printf "\n$(BOLD_PURPLE)$(SPARKLE) $(ITALIC)Initiating compilation sequence... $(SPARKLE)$(RESET)\n\n"
	@sleep 0.5

# Display footer for all target with pulse effect
footer_all:
	@echo ""
	@for i in 1 2 3; do \
		printf "\r$(BOLD)$(GREEN)$(SPARKLE) BUILD SUCCESSFUL! $(SPARKLE)$(RESET)" ; \
		sleep 0.15 ; \
		printf "\r$(BOLD)$(YELLOW)$(SPARKLE) BUILD SUCCESSFUL! $(SPARKLE)$(RESET)" ; \
		sleep 0.15 ; \
	done
	@printf "\r$(BOLD)$(GREEN)$(SPARKLE) BUILD SUCCESSFUL! $(SPARKLE)$(RESET)\n\n"
	@echo "$(GOLD)╔═══════════════════════════════════════════════════════════════════╗$(RESET)"
	@printf "$(GOLD)║$(RESET)$(BOLD)$(GREEN)✓$(RESET)$(CYAN)All test programs compiled successfully!$(RESET)%26s$(GOLD)║$(RESET)\n" " "
	@echo "$(GOLD)╚═══════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(PURPLE)┌─────────────────────────────────────────────────────────────────┐$(RESET)"
	@echo "$(PURPLE)│$(RESET) $(YELLOW)Use $(RESET)$(BOLD_CYAN)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)"
	@echo -n "$(PURPLE)│$(RESET) $(YELLOW)Use '$(RESET)"
	@for i in 1 2 3; do \
		printf "$(BOLD_CYAN)make controller$(RESET)$(YELLOW)' to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(BOLD_MAGENTA)make controller$(RESET)$(YELLOW)' to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(BOLD_GREEN)make controller$(RESET)$(YELLOW)' to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(BOLD_GOLD)make controller$(RESET)$(YELLOW)' to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo "$(PURPLE)│$(RESET) $(YELLOW)Use $(BOLD_CYAN)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)"
	@echo "$(PURPLE)└─────────────────────────────────────────────────────────────────┘$(RESET)"
	@sleep 0.5
	@echo ""
	@echo "$(BOLD)$(UNDERLINE)$(SKY)AVAILABLE TEST TARGETS:$(RESET)"
	@echo ""
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 1 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run simple debug test$(RESET)\n" "make simple"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 2 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run debug test$(RESET)\n" "make debug"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 3 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run stress test$(RESET)\n" "make stress"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 4 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run flag combinations test$(RESET)\n" "make flags"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 5 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run character tests$(RESET)\n" "make char"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 6 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run extended character tests$(RESET)\n" "make chars_ex"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 7 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run ultimate test$(RESET)\n" "make ultimate"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 8 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run all tests with summary$(RESET)\n" "make test"
	@echo ""
	@sleep 0.2
	@echo "$(BOLD)$(TEAL)Command History:$(RESET)"
	@echo "$(GRAY)$ make all$(RESET)  $(GREEN)✓ Finished$(RESET)\n"

# Create directories with cleaner animation
make_dirs:
	@printf "$(BOLD_CYAN)╔════════════════════════════════════════╗$(RESET)\n"
	@printf "$(BOLD_CYAN)║$(RESET) $(BOLD_YELLOW)SYSTEM ENVIRONMENT PREPARATION$(RESET)$(BOLD_CYAN)         ║$(RESET)\n"
	@printf "$(BOLD_CYAN)╚════════════════════════════════════════╝$(RESET)\n"
	@echo ""
	@printf "$(YELLOW)$(GEAR) Creating system directories:$(RESET)\n"
	
	@printf "  $(CYAN)➤ Initializing obj/ directory...$(RESET)"
	@mkdir -p $(OBJ_DIR)
	@for i in 1 2 3 4 5; do \
		printf "\r  $(CYAN)➤ Initializing obj/ directory...   $(RESET)" ; \
		sleep 0.1 ; \
		printf "\r  $(CYAN)➤ Initializing obj/ directory.     $(RESET)" ; \
		sleep 0.1 ; \
	done
	@printf "\r  $(CYAN)➤ Initializing obj/ directory $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"

	@printf "  $(CYAN)➤ Initializing program/ directory...$(RESET)"
	@mkdir -p $(PROGRAM_DIR)
	@for i in 1 2 3 4 5; do \
		printf "\r  $(CYAN)➤ Initializing program/ directory...   $(RESET)" ; \
		sleep 0.1 ; \
		printf "\r  $(CYAN)➤ Initializing program/ directory.     $(RESET)" ; \
		sleep 0.1 ; \
	done
	@printf "\r  $(CYAN)➤ Initializing program/ directory $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"
	
	@echo ""
	@echo "$(GREEN)$(CHECK) Build environment ready!$(RESET)"
	@echo ""

# Build libft with animated status
$(LIBFT):
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) LIBFT $(RESET) $(BOLD_YELLOW)Importing dependency...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo ""
	@echo -n "$(BOLD_YELLOW)Library status: $(RESET)"
	@for i in 1 2 3; do \
		printf "$(YELLOW)⬤$(RESET) " ; \
		sleep 0.1 ; \
	done
	@echo "$(BOLD_GREEN)LINKED$(RESET)"
	@echo ""

# Master function for a progress bar
define progress_bar
	@for k in $(shell seq 1 $(1)); do \
		perl -e 'select(undef, undef, undef, 0.01)'; \
		count=$$(($(2) * k / $(1))); \
		printf "\r  $(YELLOW)%-25s [$(GREEN)" "$(3)"; \
		for i in $$(seq 1 $$count); do printf "▓"; done; \
		for i in $$(seq 1 $$(( $(2) - $$count ))); do printf "$(GRAY)·"; done; \
		printf "$(YELLOW)] %3d%% $(RESET)" $$(( 100 * k / $(1) )); \
	done; \
	printf "\n"
endef

# Compile ft_printf source files with fancy loader
$(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c
	@if [ ! -f $(OBJ_DIR)/.header_printed ]; then \
		printf "$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(MAGENTA)CORE COMPONENTS COMPILATION$(BLUE)            ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n"; \
		touch $(OBJ_DIR)/.header_printed; \
	fi
	@printf "  $(CYAN)%-25s$(RESET) " "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN)$(CHECK) Compiled$(RESET)\n"

# Compile test source files with shimmer effect
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -f $(OBJ_DIR)/.test_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(PINK)TEST COMPONENTS COMPILATION$(BLUE)            ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.test_header_printed; \
	fi
	@printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-25s$(RESET) " "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

# Build tester executables with fancy spinning animation
$(PROGRAM_DIR)/%: $(OBJ_DIR)/%.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	@if [ ! -f $(OBJ_DIR)/.link_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(LIME)LINKING TEST EXECUTABLES$(BLUE)               ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.link_header_printed; \
	fi
	@printf "  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s " "$@"
	@for c in "/" "-" "\\" "|"; do \
		printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(YELLOW)[$$c]$(RESET)" "$@" ; \
		sleep 0.05; \
	done
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n" "$@"
	@sleep 0.05

# Special rule for ultimate_tester_extended with enhanced animation
$(PROGRAM_DIR)/ultimate_tester_extended: $(OBJ_DIR)/ft_printf_ultimate_controller.o $(OBJ_UTILS) $(PRINTF_OBJS) $(LIBFT)
	@printf "  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s " "$@"
	@for i in 1 2 3 4; do \
		for c in "🔄" "🔁" "♻️" "⚙️"; do \
			printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(YELLOW)[$$c]$(RESET)" "$@" ; \
			sleep 0.05; \
		done; \
	done
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n" "$@"
	@sleep 0.05

# Clean targets with completely silent file removal
clean:
	@clear
	@printf "$(BG_BLUE)$(BOLD_WHITE) SYSTEM MAINTENANCE: CLEANING OPERATION $(RESET)\n\n"
	@printf "$(YELLOW)$(GEAR) Removing object files...$(RESET)\n\n"
	
	@# Display scanning animation
	@for i in $(shell seq 1 3); do \
		printf "  $(CYAN)Scanning for temporary files...$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning for temporary files$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning for temporary files$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning for temporary files$(RESET).$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo ""
	
	@# Show wipe animation with progress bar
	@echo "  $(YELLOW)Wiping object directory:$(RESET)"
	$(call progress_bar,20,30,"Removing build artifacts")
	@rm -rf $(OBJ_DIR) > /dev/null 2>&1
	
	@echo ""
	@printf "$(GREEN)$(BOLD)$(CHECK) Clean operation complete!$(RESET)\n"
	@printf "$(GRAY)$ make clean$(RESET)  $(GREEN)✓ Finished$(RESET)\n"

fclean:
	@clear
	@printf "$(BG_BLUE)$(BOLD_WHITE) SYSTEM MAINTENANCE: FULL CLEANING OPERATION $(RESET)\n\n"
	@printf "$(YELLOW)$(GEAR) Removing object files...$(RESET)\n\n"
	
	@# Display scanning animation for objects
	@for i in $(shell seq 1 2); do \
		printf "  $(CYAN)Scanning objects...$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning objects$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning objects$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning objects$(RESET).$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo ""
	
	@# Show wipe animation with progress bar for objects
	@echo "  $(YELLOW)Wiping object directory:$(RESET)"
	$(call progress_bar,15,30,"Removing build artifacts")
	@rm -rf $(OBJ_DIR) > /dev/null 2>&1
	
	@printf "$(YELLOW)$(GEAR) Removing program files...$(RESET)\n\n"
	
	@# Display scanning animation for programs
	@for i in $(shell seq 1 2); do \
		printf "  $(CYAN)Scanning executables...$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning executables$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning executables$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning executables$(RESET).$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo ""
	
	@# Show wipe animation with progress bar for programs
	@echo "  $(YELLOW)Wiping program directory:$(RESET)"
	$(call progress_bar,15,30,"Removing executables")
	@rm -rf $(PROGRAM_DIR) > /dev/null 2>&1
	
	@echo ""
	@printf "$(GREEN)$(BOLD)$(CHECK) Full clean operation complete!$(RESET)\n"
	@printf "$(GRAY)$ make fclean$(RESET)  $(GREEN)✓ Finished$(RESET)\n\n"

re: fclean all

# Test command display header with ultra-modern design
define test_header
	@clear
	@echo ""
	@echo "$(TEAL)╭───────────────────────────────────────────────────────────────────╮"
	@echo "│$(BG_DARK_BLUE)$(BOLD_WHITE) RUNNING TEST: $(UNDERLINE)$(1)$(RESET)$(TEAL)                                           │"
	@echo "╰───────────────────────────────────────────────────────────────────╯"
	@echo ""
	@echo "$(LAVENDER)┌─────────────────────────────────────────────────────────────────┐"
	@echo "│$(RESET) $(BOLD_YELLOW)$(CLOCK) Test preparation in progress...$(RESET)                             $(LAVENDER)│"
	@echo "└─────────────────────────────────────────────────────────────────┘$(RESET)"
	@echo ""
	@for i in 1 2 3; do \
		for c in "⣾" "⣽" "⣻" "⢿" "⡿" "⣟" "⣯" "⣷"; do \
			printf "$(YELLOW)  %s $(CYAN)Initializing test environment...$(RESET)\r" "$$c"; \
			sleep 0.05; \
		done; \
	done
	@echo "$(GREEN)✓ Test environment ready! Starting test...$(RESET)"
	@sleep 0.5
	@echo ""
endef

# Test command display header with ultra-modern design
define test_header
	@clear
	@echo ""
	@echo "$(TEAL)╭───────────────────────────────────────────────────────────────────╮"
	@echo "│$(BG_DARK_BLUE)$(BOLD_WHITE) RUNNING TEST: $(UNDERLINE)$(1)$(RESET)$(TEAL)                                           │"
	@echo "╰───────────────────────────────────────────────────────────────────╯"
	@echo ""
	@echo "$(LAVENDER)┌─────────────────────────────────────────────────────────────────┐"
	@echo "│$(RESET) $(BOLD_YELLOW)$(CLOCK) Test preparation in progress...$(RESET)                             $(LAVENDER)│"
	@echo "└─────────────────────────────────────────────────────────────────┘$(RESET)"
	@echo ""
	@for i in 1 2 3; do \
		for c in "⣾" "⣽" "⣻" "⢿" "⡿" "⣟" "⣯" "⣷"; do \
			printf "$(YELLOW)  %s $(CYAN)Initializing test environment...$(RESET)\r" "$$c"; \
			sleep 0.05; \
		done; \
	done
	@echo "$(GREEN)✓ Test environment ready! Starting test...$(RESET)"
	@sleep 0.5
	@echo ""
endef

# Run controller with attention-grabbing blinking effect
controller: $(PROGRAM_DIR)/ultimate_tester_extended
	@clear
	@echo "$(CYAN)╔══════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║ $(BOLD)$(PINK)    F T _ P R I N T F   T E S T   C O N T R O L L E R    $(RESET)$(CYAN)         ║$(RESET)"
	@echo "$(CYAN)╚══════════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@# Create and launch the blinking notification in a persistent way
	@printf "#!/bin/bash\n\
	while true; do\n\
		printf \"\\r\$(BOLD_MAGENTA)⚡ CONTROLLER ACTIVE ⚡\$(RESET)\";\n\
		sleep 0.5;\n\
		printf \"\\r\$(BOLD_CYAN)⚡ CONTROLLER ACTIVE ⚡\$(RESET)\";\n\
		sleep 0.5;\n\
		printf \"\\r\$(BOLD_GREEN)⚡ CONTROLLER ACTIVE ⚡\$(RESET)\";\n\
		sleep 0.5;\n\
		printf \"\\r\$(BOLD_GOLD)⚡ CONTROLLER ACTIVE ⚡\$(RESET)\";\n\
		sleep 0.5;\n\
	done" > /tmp/ft_printf_blinker.sh 2>/dev/null
	@chmod +x /tmp/ft_printf_blinker.sh 2>/dev/null
	@# Launch blinking indicator in background, will terminate when test completes
	@(nohup bash /tmp/ft_printf_blinker.sh > /dev/null 2>&1 & echo $$! > /tmp/ft_printf_blinker.pid) 2>/dev/null
	@echo "$(YELLOW)⚙ Launching comprehensive test suite...$(RESET)"
	@echo ""
	@sleep 0.5
	@# Run the actual test controller
	@$(PROGRAM_DIR)/ultimate_tester_extended; \
	if [ -f /tmp/ft_printf_blinker.pid ]; then \
		kill -9 $$(cat /tmp/ft_printf_blinker.pid) > /dev/null 2>&1 || true; \
		rm -f /tmp/ft_printf_blinker.pid /tmp/ft_printf_blinker.sh > /dev/null 2>&1; \
	fi

# Create notification box with perpetual blinking highlight
define create_notification
	@echo ""
	@echo "$(MAGENTA)┌──────────────────────────────────────────────────────────────────┐$(RESET)"
	@echo "$(MAGENTA)│$(RESET) $(BOLD_YELLOW)                                                               $(RESET)$(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET) $(BOLD_YELLOW)$(1)$(RESET)$(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET) $(BOLD_YELLOW)                                                               $(RESET)$(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)└──────────────────────────────────────────────────────────────────┘$(RESET)"
	@echo ""
endef

# Add a fully animated landing page for the controller
controllerx: $(PROGRAM_DIR)/ultimate_tester_extended
	@clear
	@echo "$(BOLD_CYAN)╔════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BOLD_CYAN)║$(BOLD_WHITE)                                                                $(RESET)$(BOLD_CYAN)║$(RESET)"
	@echo "$(BOLD_CYAN)║$(BOLD_WHITE)                FT_PRINTF ULTIMATE CONTROLLER                   $(RESET)$(BOLD_CYAN)║$(RESET)"
	@echo "$(BOLD_CYAN)║$(BOLD_WHITE)                                                                $(RESET)$(BOLD_CYAN)║$(RESET)"
	@echo "$(BOLD_CYAN)╚════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@sleep 0.5
	
	@# Create and launch the blinking notification in background
	@rm -f /tmp/ft_printf_blink_flag
	@printf "#!/bin/bash\n\
	while [ ! -f /tmp/ft_printf_blink_flag ]; do\n\
		tput civis;\n\
		printf \"\$(PURPLE)┌────────────────────────────────────────────────────────────┐\$(RESET)\n\";\n\
		printf \"\$(PURPLE)│\$(BOLD_MAGENTA) ★  CONTROLLER STARTING - PLEASE WAIT FOR INITIALIZATION  ★ \$(RESET)\$(PURPLE)│\$(RESET)\n\";\n\
		printf \"\$(PURPLE)└────────────────────────────────────────────────────────────┘\$(RESET)\n\";\n\
		sleep 0.3;\n\
		clear;\n\
		printf \"\$(CYAN)┌────────────────────────────────────────────────────────────┐\$(RESET)\n\";\n\
		printf \"\$(CYAN)│\$(BOLD_CYAN) ★  CONTROLLER STARTING - PLEASE WAIT FOR INITIALIZATION  ★ \$(RESET)\$(CYAN)│\$(RESET)\n\";\n\
		printf \"\$(CYAN)└────────────────────────────────────────────────────────────┘\$(RESET)\n\";\n\
		sleep 0.3;\n\
		clear;\n\
		printf \"\$(GREEN)┌────────────────────────────────────────────────────────────┐\$(RESET)\n\";\n\
		printf \"\$(GREEN)│\$(BOLD_GREEN) ★  CONTROLLER STARTING - PLEASE WAIT FOR INITIALIZATION  ★ \$(RESET)\$(GREEN)│\$(RESET)\n\";\n\
		printf \"\$(GREEN)└────────────────────────────────────────────────────────────┘\$(RESET)\n\";\n\
		sleep 0.3;\n\
		clear;\n\
	done\n\
	tput cnorm;\n\
	" > /tmp/ft_printf_controller_blinker.sh
	@chmod +x /tmp/ft_printf_controller_blinker.sh
	@(bash /tmp/ft_printf_controller_blinker.sh) &
	@sleep 2
	@touch /tmp/ft_printf_blink_flag
	@rm -f /tmp/ft_printf_controller_blinker.sh /tmp/ft_printf_blink_flag
	
	@# Run the controller
	@$(PROGRAM_DIR)/ultimate_tester_extended

# Extended controller (same as controller)
extended: controller