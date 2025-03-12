# Function to print compilation header once
define print_compilation_header
	@if [ ! -f $(OBJ_DIR)/.$(1)_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(2)$(BLUE)            ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.$(1)_header_printed; \
	fi
endef

# Ensure utility files are compiled with priority
$(OBJ_DIR)/tester/%_utils.o $(OBJ_DIR)/tester/%_ft_printf.o: $(TESTER_DIR)/%.c
	$(call print_compilation_header,test,$(PINK)UTILITY COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building Utility:$(RESET) $(YELLOW)%-25s$(RESET) " "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -I. -c $< -o $@
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

# Generic compilation rule for all source files in tester directory
$(OBJ_DIR)/tester/%.o: $(TESTER_DIR)/%.c
	$(call print_compilation_header,test,$(PINK)TEST COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-25s$(RESET) " "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -I. -c $< -o $@
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

# Generic utility and source detection for compilation
$(OBJ_DIR)/tester/%/%.o: $(TESTER_DIR)/%/%.c
	$(call print_compilation_header,test,$(PINK)TEST COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-25s$(RESET) " "$(notdir $<) ($(shell dirname $(subst $(TESTER_DIR)/,,$<)))"
	@$(CC) $(CFLAGS) $(INCLUDES) -I. -c $< -o $@
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

# Compile ft_printf source files
$(OBJ_DIR)/printf/%.o: $(PRINTF_DIR)/%.c
	$(call print_compilation_header,printf,$(MAGENTA)CORE COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(CYAN)%-40s$(RESET) " "$(notdir $<) $(GRAY)($(shell dirname $(subst $(PRINTF_DIR)/,,$<)))$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || \
		{ printf "$(RED)Failed to compile %s$(RESET)\n" "$<"; exit 1; }
	@printf "$(GREEN)$(CHECK) Compiled$(RESET)\n"

