
define handle_error
	@printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)%s$(RESET)\n" "$(1)"
	@echo "$(RED)$(CROSS) Build failed. See error message above.$(RESET)"
	@-rm -f $(2) 2>/dev/null
	@exit 1
endef