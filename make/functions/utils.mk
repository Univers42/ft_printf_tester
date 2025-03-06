define print_found_files
	@echo "$(YELLOW)Found source files:$(RESET)"
	@for file in $(1); do \
		echo "  $(CYAN)$$file$(RESET)"; \
	done
endef
