# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    progress.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 14:37:35 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/12 18:06:17 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========== PROGRESS BAR FUNCTIONS ==========

# Standard progress bar with customizable length, message and colors
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

# ========== ANIMATION FUNCTIONS ==========

# Multi-purpose loading spinner - iterations, color, message
define loading_spinner
	@for i in $(shell seq 1 $(1)); do \
		for c in "⣾" "⣽" "⣻" "⢿" "⡿" "⣟" "⣯" "⣷"; do \
			printf "$(2)  %s $(3)$(RESET)\r" "$$c"; \
			sleep 0.05; \
		done; \
	done
endef

# Initialization dots animation with customizable message, iterations, and color
define init_dots_animation
	@for i in $(shell seq 1 $(2)) ; do \
		printf "\r$(1)$(3)" ; \
		sleep 0.1 ; \
		printf "\r$(1).$(3)" ; \
		sleep 0.1 ; \
		printf "\r$(1)..$(3)" ; \
		sleep 0.1 ; \
		printf "\r$(1)...$(3)" ; \
		sleep 0.1 ; \
	done
	@echo ""
endef

# Color alternating pulse text - color1, color2, text, iterations
define pulse_text
	@for i in $(shell seq 1 $(4)); do \
		printf "\r%s%s\033[0m" "$(1)" "$(3)"; \
		sleep 0.15; \
		printf "\r%s%s\033[0m" "$(2)" "$(3)"; \
		sleep 0.15; \
	done
	@printf "\r%s%s\033[0m\n" "$(1)" "$(3)"
endef

# Blinking text effect with message
define blink_text
	@for i in 1 2 3; do \
		printf "$(3)"; \
		sleep 0.2; \
		printf "\r%*s\r" $${#3} ""; \
		sleep 0.2; \
	done
	@printf "$(3)\n"
endef

# Multi-color blinking effect for important messages
define rainbow_blink
	@for i in $(shell seq 1 $(2)); do \
		printf "\r\033[1m\033[35m%s\033[0m" "$(1)"; \
		sleep 0.2; \
		printf "\r\033[1m\033[36m%s\033[0m" "$(1)"; \
		sleep 0.2; \
		printf "\r\033[1m\033[32m%s\033[0m" "$(1)"; \
		sleep 0.2; \
		printf "\r\033[1m\033[33m%s\033[0m" "$(1)"; \
		sleep 0.2; \
	done
	@printf "\r%s%s\033[0m\n" "$(3)" "$(1)"
endef

# ========== OPERATIONAL FUNCTIONS ==========

# Display wipe operation with progress bar
define display_wipe_operation
	@echo "  $(YELLOW)Wiping $(1):$(RESET)"
	$(call progress_bar,$(2),30,"$(3)")
endef

# Display scanning animation for files
define display_scanning_animation
	@printf "$(YELLOW)$(GEAR) $(1)...$(RESET)\n\n"
	@for i in $(shell seq 1 $(2)); do \
		printf "  $(CYAN)Scanning $(3)...$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning $(3)$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning $(3)$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning $(3)$(RESET).$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo ""
endef

# Test environment preparation animation
define test_preparation_animation
	@echo "$(LAVENDER)┌─────────────────────────────────────────────────────────────────┐"
	@echo "│$(RESET) $(BOLD_YELLOW)$(CLOCK) Test preparation in progress...$(RESET)                             $(LAVENDER)│"
	@echo "└─────────────────────────────────────────────────────────────────┘$(RESET)"
	@echo ""
	$(call loading_spinner,3,"$(YELLOW)","$(CYAN)Initializing test environment...")
	@echo "$(GREEN)✓ Test environment ready! Starting test...$(RESET)"
	@sleep 0.5
	@echo ""
endef


# Function to display animation during linking
# $(1): Label (e.g. "Linking" or "Linking Controller")
# $(2): Target name
# $(3): Number of iterations (defaults to 1)
define display_animation
	@printf "  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s " "$(2)"
	@for i in $$(seq 1 $(or $(3), 1)); do \
		printf "\r  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s $(YELLOW)[/]$(RESET)" "$(2)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s $(YELLOW)[|]$(RESET)" "$(2)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s $(YELLOW)[-]$(RESET)" "$(2)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s $(YELLOW)[\\]$(RESET)" "$(2)" ; \
		sleep 0.05; \
	done
endef

# Function to display emoji animation during linking
# $(1): Label (e.g. "Linking")
# $(2): Target name
# $(3): Number of iterations
define display_controller_animation
	@printf "  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s " "$(2)"
	@for i in $$(seq 1 $(or $(3), 4)); do \
		printf "\r  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s $(YELLOW)[🔄]$(RESET)" "$(2)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s $(YELLOW)[🔁]$(RESET)" "$(2)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s $(YELLOW)[♻️]$(RESET)" "$(2)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ $(1):$(RESET) $(WHITE)%-25s $(YELLOW)[⚙️]$(RESET)" "$(2)" ; \
		sleep 0.05; \
	done
endef

# Function to display controller animation during linking
# $(1): Target name
# $(2): Number of iterations
define display_emoji_animation
	@printf "  $(BOLD_PURPLE)▶ Linking Controller:$(RESET) $(WHITE)%-25s " "$(1)"
	@for i in $$(seq 1 $(or $(2), 4)); do \
		printf "\r  $(BOLD_PURPLE)▶ Linking Controller:$(RESET) $(WHITE)%-25s $(YELLOW)[😊]$(RESET)" "$(1)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ Linking Controller:$(RESET) $(WHITE)%-25s $(YELLOW)[😁]$(RESET)" "$(1)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ Linking Controller:$(RESET) $(WHITE)%-25s $(YELLOW)[🎩]$(RESET)" "$(1)" ; \
		sleep 0.05; \
		printf "\r  $(BOLD_PURPLE)▶ Linking Controller:$(RESET) $(WHITE)%-25s $(YELLOW)[🤠]$(RESET)" "$(1)" ; \
		sleep 0.05; \
	done
endef