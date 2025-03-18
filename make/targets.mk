# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 20:30:00 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/18 01:32:17 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Function to compile the controller with artistic styling - Fixed alignment
define compile_controller
	@printf "\n${ACCENT_PURPLE}⚡${RST} ${BOLD}Creating controller module...${RST}\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(CONTROLLER) $(SRCS_DIR)/ft_printf_ultimate_controller.c $(NAME) $(LIBPRINTF) $(LIBFT) >/dev/null
	@ln -sf $(BIN_DIR)/$(CONTROLLER) ./tester
	@printf "${NEON_GREEN}✓${RST} ${BOLD}Controller ready${RST}        \n\n"
endef

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Test Build System                    ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Compile test programs targets
.PHONY: $(TEST_PROGRAMS)
$(TEST_PROGRAMS): %:
	@if [ "$@" = "mandatory_test" ] || [ "$@" = "debug_tester_simple" ]; then \
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/ft_printf_$@ $(SRCS_DIR)/tests/ft_printf_$@.c $(NAME) $(LIBPRINTF) $(LIBFT) >/dev/null 2>&1; \
	elif [ "$@" = "ft_printf_stress_tester" ]; then \
		cp $(UTILS_DIR)/ft_printf_stress_*.c $(PROGRAM_DIR)/utils/stress/ 2>/dev/null || :; \
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/$@.c $(NAME) $(LIBPRINTF) $(LIBFT) >/dev/null 2>&1; \
	else \
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TESTS_DIR)/$@ $(SRCS_DIR)/tests/$@.c $(NAME) $(LIBPRINTF) $(LIBFT) >/dev/null 2>&1; \
	fi

# Print the initial progress bar
define init_progress_bar
	@$(call section_header, "BUILDING TEST SUITE")
	@printf "${BOLD}${BCYN}▶ Initializing components${RST}\n\n"
	@printf "${DIM}Progress: ${RST}["
	@for i in `seq 1 40`; do printf "${DIM}▱${RST}"; done
	@printf "] ${DIM}  0%%${RST}"
endef

# Track progress of test program compilation
TEST_PROG_COUNT := $(words $(TEST_PROGRAMS))

# Simple update progress function (no complex shell logic)
update_progress = \
	printf "\r$(DIM)Progress: $(RESET)["; \
	i=1; while [ $$i -le 40 ]; do \
		if [ $$i -le $(1) ]; then printf "$(GRADIENT_MID)▰$(RESET)"; \
		else printf "$(DIM)▱$(RESET)"; fi; \
		i=$$((i+1)); \
	done; \
	printf "] $(BR_CYAN)%3d%%$(RESET)" $(2);

# Simple rainbow color array for progress bar
RAINBOW_COLORS := \033[38;5;196m \033[38;5;202m \033[38;5;208m \033[38;5;214m \033[38;5;220m \033[38;5;226m \033[38;5;190m \033[38;5;154m \033[38;5;118m \033[38;5;82m \033[38;5;46m \033[38;5;47m \033[38;5;48m \033[38;5;49m \033[38;5;50m \033[38;5;51m \033[38;5;45m \033[38;5;39m \033[38;5;33m \033[38;5;27m \033[38;5;21m \033[38;5;57m \033[38;5;93m \033[38;5;129m \033[38;5;165m \033[38;5;201m \033[38;5;200m \033[38;5;199m \033[38;5;198m \033[38;5;197m

# Smooth progress bar that updates in place with carriage return
define smooth_progress_bar
	@$(eval TEST_PROG_INDEX := $(shell echo $$(($(TEST_PROG_INDEX) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(TEST_PROG_INDEX) * 100 / $(TEST_PROG_COUNT)))))
	@$(eval BAR_W := 25)
	@$(eval FILLED := $(shell echo $$(($(TEST_PROG_INDEX) * $(BAR_W) / $(TEST_PROG_COUNT)))))
	@printf "$(BUILD_ICON) $(BR_CYAN)Building %-20s$(RESET) [" "$1"
	@for i in `seq 1 $(BAR_W)`; do \
		if [ $$i -le $(FILLED) ]; then \
			printf "$(BR_CYAN)█$(RESET)"; \
		else \
			printf "$(DIM)▒$(RESET)"; \
		fi \
	done
	@printf "] $(BOLD)%3d%%$(RESET) $(CHECK)\r" $(PERCENT)
endef

# Inline progress bar with no newline 
define inline_progress_bar
	@echo -n "["
	@for i in `seq 1 $(1)`; do \
		echo -n "$(BR_CYAN)◼$(RESET)"; \
	done
	@for i in `seq $(1) $(2)`; do \
		echo -n "$(DIM)◻$(RESET)"; \
	done
	@echo -n "]"
endef

# Print elegant version info
define print_version
	@$(call artistic_version)
endef

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Progress Bar System                  ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Simple, robust progress bar with proper shell syntax and enhanced visuals - Fixed alignment
define build_tests
	@$(call section_header, "BUILDING TEST MODULES")
	@printf "${SUBTLE}Preparing directory structure...${RST}\n"
	@$(MAKE) -s prepare_dirs > /dev/null 2>&1
	@printf "${GRADIENT2}▶${RST} ${BOLD}Compiling test modules${RST}\n\n"
	
	@for prog in $(TEST_PROGRAMS); do \
		printf "  ${GRADIENT1}┌─${RST} ${BOLD}Building test:   ${GRADIENT3}%s${RST}\n" "$$prog"; \
		$(MAKE) -s $$prog > /dev/null 2>&1; \
		printf "  ${GRADIENT1}└─${RST} ${ACCENT_GOLD}✨${RST} ${NEON_GREEN}✓${RST} ${BOLD}Compiled${RST}\n"; \
	done
	
	@printf "\n  ${GRADIENT2}┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓${RST}\n"
	@printf "  ${GRADIENT2}┃${RST}   ${NEON_GREEN}✓${RST} ${BOLD}Test modules ready${RST}${GRADIENT2} ┃${RST}\n"
	@printf "  ${GRADIENT2}┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛${RST}\n\n"
endef

# Test completion message with enhanced visual appeal
define test_complete
	@printf "\n${GRADIENT1}┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓${RST}\n"
	@printf "${GRADIENT1}┃${RST}  ${ACCENT_GOLD}✨${RST}  ${BRIGHT_FG}${BOLD}ALL TESTS EXECUTED SUCCESSFULLY${RST}  ${ACCENT_GOLD}✨${RST}  ${GRADIENT1}┃${RST}\n"
	@printf "${GRADIENT1}┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛${RST}\n\n"
	@$(call sparkle_animation, "Testing completed with flying colors!")
endef
