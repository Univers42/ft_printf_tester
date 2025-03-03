# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 01:40:56 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/03 20:57:35 by dyl-syzygy       ###   ########.fr        #
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
LIBFT_DIR = ../libft
ROOT_OBJ_DIR = ../Object

# Source files - using enhanced find to explicitly discover all .c files with better debug output
TESTER_SRCS = $(shell find $(TESTER_DIR) -type f -name "*.c")
PRINTF_SRCS = $(shell find $(PRINTF_DIR) -type f -name "*.c" \
                ! -path "$(PRINTF_DIR)/ft_printf_tester/*" \
                ! -path "$(PRINTF_DIR)/framework_test/*" \
                ! -path "$(PRINTF_DIR)/libft/*")

# Enhanced debug output for source file discovery
define print_found_files
	@echo "$(YELLOW)Found source files:$(RESET)"
	@for file in $(1); do \
		echo "  $(CYAN)$$file$(RESET)"; \
	done
endef

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
all: intro header_all build_root_project make_dirs $(LIBFT) $(TESTERS) footer_all

# Build the root project first - robust subdirectory handling with deduplication
build_root_project:
	@printf "$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"
	@printf "$(BOLD_BLUE)║$(RESET) $(BOLD_GREEN)BUILDING ROOT PROJECT$(RESET)$(BOLD_BLUE)                 ║$(RESET)\n"
	@printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n"
	@echo ""
	@printf "$(YELLOW)$(GEAR) Building ft_printf in parent directory...$(RESET)\n"
	@for i in 1 2 3 ; do \
		printf "  $(CYAN)Running make in root directory...$(RESET)\r" ; \
		sleep 0.2 ; \
	done
	
	@# Build with better error handling
	@if ! $(MAKE) -C $(PRINTF_DIR) > /tmp/ft_printf_make.log 2>&1; then \
		echo "$(RED)$(CROSS) Root project build failed. Error log:$(RESET)"; \
		cat /tmp/ft_printf_make.log; \
		exit 1; \
	fi
	@printf "  $(CYAN)Root project build $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n\n"
	
	@# Check for the libftprintf.a library
	@if [ -f "$(PRINTF_DIR)/libftprintf.a" ]; then \
		printf "  $(GREEN)Found libftprintf.a in root directory$(RESET)\n"; \
	else \
		printf "  $(RED)Error: libftprintf.a not found in root directory$(RESET)\n"; \
		exit 1; \
	fi
	
	@# Generate supplemental library with potentially missing functions
	@printf "$(YELLOW)$(GEAR) Running link wrapper to ensure all functions are available...$(RESET)\n"
	@if [ ! -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
		if [ -x "./link_wrapper.sh" ]; then \
			./link_wrapper.sh > /tmp/link_wrapper.log 2>&1; \
		else \
			chmod +x ./link_wrapper.sh && ./link_wrapper.sh > /tmp/link_wrapper.log 2>&1; \
		fi; \
	fi
	
	@if [ -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
		printf "  $(GREEN)Supplemental library generated successfully$(RESET)\n"; \
	else \
		printf "  $(YELLOW)Warning: Supplemental library not found, linking may fail$(RESET)\n"; \
	fi
	
	@# Build libft with better error handling
	@printf "$(YELLOW)$(GEAR) Ensuring libft is built...$(RESET)\n"
	@if ! $(MAKE) -C $(LIBFT_DIR) > /tmp/ft_printf_libft.log 2>&1; then \
		echo "$(RED)$(CROSS) Libft build failed. Error log:$(RESET)"; \
		cat /tmp/ft_printf_libft.log; \
		exit 1; \
	fi
	@printf "  $(CYAN)Libft build $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n\n"
	
	@# Recursive directory structure syncing
	@echo "$(YELLOW)$(GEAR) Locating source files in project directory...$(RESET)"
	$(call print_found_files, $(PRINTF_SRCS))
	
	@# Clean up any previous objects first to prevent duplicates
	@rm -rf $(OBJ_DIR)/printf
	
	@if [ -d "$(ROOT_OBJ_DIR)" ]; then \
		printf "\n$(YELLOW)$(GEAR) Synchronizing object files...$(RESET)\n"; \
		mkdir -p $(OBJ_DIR)/printf; \
		find $(ROOT_OBJ_DIR) -type f -name "*.o" ! -path "*/libft/*" | sort | uniq | while read src; do \
			filename=$$(basename $$src); \
			if [ ! -f "$(OBJ_DIR)/printf/$$filename" ]; then \
				rel_path=$$(echo $$src | sed 's|$(ROOT_OBJ_DIR)/||'); \
				dst_dir=$(OBJ_DIR)/printf/$$(dirname $$rel_path); \
				printf "  $(CYAN)Syncing: %s$(RESET)\n" "$$rel_path"; \
				mkdir -p $$dst_dir 2>/dev/null || true; \
				cp $$src $$dst_dir/ 2>/dev/null || true; \
			fi \
		done; \
		printf "  $(CYAN)Object synchronization $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"; \
	else \
		printf "  $(YELLOW)Warning: Root Object directory not found. Creating objects locally.$(RESET)\n"; \
		for src in $(PRINTF_SRCS); do \
			rel_path=$$(echo $$src | sed 's|$(PRINTF_DIR)/||'); \
			obj_path=$(OBJ_DIR)/printf/$$(dirname $$rel_path); \
			printf "  $(CYAN)Will compile: %s -> %s$(RESET)\n" "$$rel_path" "$$obj_path"; \
			mkdir -p $$obj_path; \
		done; \
	fi
	@echo ""

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

# Compile ft_printf source files with enhanced pattern rule for all subdirectories
$(OBJ_DIR)/printf/%.o: $(PRINTF_DIR)/%.c
	@if [ ! -f $(OBJ_DIR)/.printf_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(MAGENTA)CORE COMPONENTS COMPILATION$(BLUE)            ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.printf_header_printed; \
	fi
	@mkdir -p $(dir $@)
	@printf "  $(CYAN)%-40s$(RESET) " "$(notdir $<) $(GRAY)($(shell dirname $(subst $(PRINTF_DIR)/,,$<)))$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || \
		{ printf "$(RED)Failed to compile %s$(RESET)\n" "$<"; exit 1; }
	@printf "$(GREEN)$(CHECK) Compiled$(RESET)\n"

# Compile test source files with shimmer effect
$(OBJ_DIR)/tester/%.o: $(TESTER_DIR)/%.c
	@if [ ! -f $(OBJ_DIR)/.test_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(PINK)TEST COMPONENTS COMPILATION$(BLUE)            ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.test_header_printed; \
	fi
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-25s$(RESET) " "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

# Error handling function to be used for graceful error display
define handle_error
	@printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)%s$(RESET)\n" "$(1)"
	@echo "$(RED)$(CROSS) Build failed. See error message above.$(RESET)"
	@-rm -f $(2) 2>/dev/null
	@exit 1
endef

# Build tester executables with improved diagnostics
$(PROGRAM_DIR)/%: $(OBJ_DIR)/tester/%.o $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ)
	@if [ ! -f $(OBJ_DIR)/.link_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(LIME)LINKING TEST EXECUTABLES$(BLUE)               ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.link_header_printed; \
	fi
	@mkdir -p $(PROGRAM_DIR)
	@printf "  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s " "$(notdir $@)"
	@for c in "/" "-" "\\" "|"; do \
		printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(YELLOW)[$$c]$(RESET)" "$(notdir $@)" ; \
		sleep 0.05; \
	done
	
	@# Use conditional linking to include supplemental library if it exists
	@if [ -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
		if ! $(CC) $(CFLAGS) -o $@ $< $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ) -L$(PRINTF_DIR) -lftprintf -lftprintf_supp -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $@)$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Main object: $<"; \
			echo "  - Test utils: $(TEST_UTILS_OBJ)"; \
			echo "  - Simple printf: $(SIMPLE_PRINTF_OBJ)"; \
			echo "  - Printf libraries: $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			echo "  - Library status:"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	else \
		if ! $(CC) $(CFLAGS) -o $@ $< $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ) -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $@)$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Main object: $<"; \
			echo "  - Test utils: $(TEST_UTILS_OBJ)"; \
			echo "  - Simple printf: $(SIMPLE_PRINTF_OBJ)"; \
			echo "  - Printf library: $(PRINTF_DIR)/libftprintf.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			echo "  - Library status:"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	fi
	@printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n" "$(notdir $@)"
	@sleep 0.05

# Special rule for ultimate_tester_extended with enhanced animation - FIXED LINKING
$(PROGRAM_DIR)/ft_printf_ultimate_tester: $(OBJ_DIR)/tester/ft_printf_ultimate_tester.o $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ)
	@printf "  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s " "$@"
	@for i in 1 2 3 4; do \
		for c in "🔄" "🔁" "♻️" "⚙️"; do \
			printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(YELLOW)[$$c]$(RESET)" "$@" ; \
			sleep 0.05; \
		done; \
	done
	@mkdir -p $(PROGRAM_DIR)
	
	@# Also add conditional linking here
	@if [ -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
		if ! $(CC) $(CFLAGS) -o $@ $< $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ) -L$(PRINTF_DIR) -lftprintf -lftprintf_supp -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $@)$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Printf libraries: $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	else \
		if ! $(CC) $(CFLAGS) -o $@ $< $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ) -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $@)$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Printf library: $(PRINTF_DIR)/libftprintf.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	fi
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
	$(RM) $
	@# Show wipe animation with progress bar
	@echo "  $(YELLOW)Wiping object directory:$(RESET)"
	$(call progress_bar,20,30,"Removing build artifacts")
	@-rm -rf $(OBJ_DIR) 2>/dev/null
	@-rm -f $(OBJ_DIR)/.*.printed 2>/dev/null
	@-rm -f /tmp/ft_printf_error.log 2>/dev/null
	
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
	@rm -rf ../obj > /dev/null 2>&1
	@rm -f ../libftprintf_supp.a > /dev/null 2>&1
	@rm -f ../libftprintf.a > /dev/null 2>&1
	@rm -rf ../libft/*.o > /dev/null 2>&1
	@rm -rf obj > /dev/null 2>&1
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

# Run controller with attention-grabbing blinking effect - updated to use ft_printf_ultimate_controller
controller: $(PROGRAM_DIR)/ft_printf_ultimate_controller
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
	@$(PROGRAM_DIR)/ft_printf_ultimate_controller; \
	if [ -f /tmp/ft_printf_blinker.pid ]; then \
		kill -9 $$(cat /tmp/ft_printf_blinker.pid) > /dev/null 2>&1 || true; \
		rm -f /tmp/ft_printf_blinker.pid /tmp/ft_printf_blinker.sh > /dev/null 2>&1; \
	fi

# Add the actual test targets
# 1. Simple debug test
simple: $(PROGRAM_DIR)/ft_printf_debug_tester_simple
	@$(call test_header,"SIMPLE DEBUG TEST")
	@$(PROGRAM_DIR)/ft_printf_debug_tester_simple

# 2. Debug test
debug: $(PROGRAM_DIR)/ft_printf_debug_tester
	@$(call test_header,"DEBUG TEST")
	@$(PROGRAM_DIR)/ft_printf_debug_tester

# 3. Stress test
stress: $(PROGRAM_DIR)/ft_printf_stress_tester
	@$(call test_header,"STRESS TEST")
	@$(PROGRAM_DIR)/ft_printf_stress_tester

# 4. Flag combinations test
flags: $(PROGRAM_DIR)/flag_combinations_tester
	@$(call test_header,"FLAG COMBINATIONS TEST")
	@$(PROGRAM_DIR)/flag_combinations_tester

# 5. Character tests
char: $(PROGRAM_DIR)/char_tests
	@$(call test_header,"CHARACTER TEST")
	@$(PROGRAM_DIR)/char_tests

# 6. Extended character tests
chars_ex: $(PROGRAM_DIR)/char_tests_extended
	@$(call test_header,"EXTENDED CHARACTER TEST")
	@$(PROGRAM_DIR)/char_tests_extended

# 7. Ultimate test
ultimate: $(PROGRAM_DIR)/ft_printf_ultimate_tester
	@$(call test_header,"ULTIMATE TEST")
	@$(PROGRAM_DIR)/ft_printf_ultimate_tester

# 8. All tests with summary
test: $(PROGRAM_DIR)/ft_printf_tester
	@$(call test_header,"COMPREHENSIVE TEST SUITE")
	@$(PROGRAM_DIR)/ft_printf_tester

# Extended controller (same as controller)
extended: controller

# List of all available test programs
list:
	@echo "$(BOLD_CYAN)Available test executables:$(RESET)"
	@for test in $(TEST_EXECUTABLES); do \
		echo "  $(YELLOW)$$test$(RESET)"; \
	done

# Show help information
help:
	@echo "$(BOLD_CYAN)FT_PRINTF TESTER - Available commands:$(RESET)"
	@echo "  $(YELLOW)make$(RESET)           - Build all test programs"
	@echo "  $(YELLOW)make test$(RESET)      - Run standard test"
	@echo "  $(YELLOW)make debug$(RESET)     - Run debug test"
	@echo "  $(YELLOW)make simple$(RESET)    - Run simple test"
	@echo "  $(YELLOW)make stress$(RESET)    - Run stress test"
	@echo "  $(YELLOW)make flags$(RESET)     - Run flag tests"
	@echo "  $(YELLOW)make char$(RESET)      - Run character tests"
	@echo "  $(YELLOW)make chars_ex$(RESET)  - Run extended character tests"
	@echo "  $(YELLOW)make ultimate$(RESET)  - Run ultimate test"
	@echo "  $(YELLOW)make controller$(RESET) - Run test controller"
	@echo "  $(YELLOW)make list$(RESET)      - List all available test programs"
	@echo "  $(YELLOW)make clean$(RESET)     - Remove object files"
	@echo "  $(YELLOW)make fclean$(RESET)    - Remove objects and executables"
	@echo "  $(YELLOW)make re$(RESET)        - Rebuild everything"

.PHONY: all intro header_all build_root_project make_dirs clean fclean re \
        test debug simple stress flags char chars_ex ultimate controller list help $(TEST_UTILS) $(SIMPLE_PRINTF) FORCE

# Empty rule to prevent attempting to build ft_printf_test_utils as an executable
$(TEST_UTILS):
	@echo "$(YELLOW)⚠ $(TEST_UTILS) is not an executable target$(RESET)"

# Empty rule to prevent attempting to build simple_ft_printf as an executable
$(SIMPLE_PRINTF):
	@echo "$(YELLOW)⚠ $(SIMPLE_PRINTF) is not an executable target$(RESET)"
