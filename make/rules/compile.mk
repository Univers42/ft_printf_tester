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

