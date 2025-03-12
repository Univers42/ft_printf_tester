# Function to print compilation header once
define print_compilation_header
	@if [ ! -f $(OBJ_DIR)/.$(1)_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(2)$(BLUE)            ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.$(1)_header_printed; \
	fi
endef

# Compilation rule to include source directory in includes
$(OBJ_DIR)/tester/ft_printf_test_utils.o: ft_printf_test_utils.c
	$(call print_compilation_header,test,$(PINK)TEST COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-25s$(RESET) " "$(notdir $<)"
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

# Compile other test source files (excluding the special ft_printf_test_utils.c)
$(OBJ_DIR)/tester/%.o: $(TESTER_DIR)/%.c
	$(call print_compilation_header,test,$(PINK)TEST COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-25s$(RESET) " "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

