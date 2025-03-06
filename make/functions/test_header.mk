# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_header.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 15:35:45 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/06 14:25:05 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
