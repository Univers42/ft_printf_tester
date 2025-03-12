define intro
	@clear
	@echo ""
	$(call init_dots_animation,"$(BLUE)$(BOLD)Initializing", 3, "$(RESET)")
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
endef

define header_all
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
endef

# Display completion message
define display_completion
	@echo ""
	@printf "$(GREEN)$(BOLD)$(CHECK) $(1) complete!$(RESET)\n"
	@printf "$(GRAY)$ make $(2)$(RESET)  $(GREEN)✓ Finished$(RESET)$(3)\n"
endef

# Display header for maintenance operations
define display_maintenance_header
	@clear
	@printf "$(BG_BLUE)$(BOLD_WHITE) SYSTEM MAINTENANCE: $(1) $(RESET)\n\n"
endef



header_all:
	$(call header_all)