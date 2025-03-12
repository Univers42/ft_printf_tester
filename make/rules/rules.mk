# Generic rule to prevent utilities from being built as executables
$(UTILITY_BASES):
	@echo "$(YELLOW)⚠ $@ is a utility module, not an executable target$(RESET)"
