

# Simplified test target display without using variables in format string
define display_test_target
	@echo "$(BG_DARK_BLUE)$(BOLD_WHITE) $(1) $(RESET) $(GREEN)➤$(RESET) $(YELLOW)make $(3)$(RESET)   $(MINT)$(2)$(RESET)"
endef

