# Display controller header
define display_controller_header
	@clear
	@echo "$(CYAN)╔══════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║ $(BOLD)$(PINK)    F T _ P R I N T F   T E S T   C O N T R O L L E R    $(RESET)$(CYAN)         ║$(RESET)"
	@echo "$(CYAN)╚══════════════════════════════════════════════════════════════════════╝$(RESET)"
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
	$(call test_preparation_animation)
endef
# Helper function to display a success banner
define display_success_banner
	@echo "$(GOLD)╔═══════════════════════════════════════════════════════════════════╗$(RESET)"
	@printf "$(GOLD)║$(RESET)$(BOLD)$(GREEN)✓$(RESET)$(CYAN)All test programs compiled successfully!$(RESET)%26s$(GOLD)║$(RESET)\n" " "
	@echo "$(GOLD)╚═══════════════════════════════════════════════════════════════════╝$(RESET)"
endef

# Print linking header once
define print_link_header
	@if [ ! -f $(OBJ_DIR)/.link_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(LIME)LINKING TEST EXECUTABLES$(BLUE)               ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.link_header_printed; \
	fi
endef