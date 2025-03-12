# Function to print compilation header once
define print_compilation_header
	@if [ ! -f $(OBJ_DIR)/.$(1)_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(2)$(BLUE)            ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.$(1)_header_printed; \
	fi
endef

# Check for function duplication before building
utils-check:
	@if [ -f "$(TESTER_DIR)/ft_printf_test_utils.c" ] && [ -d "$(TESTER_DIR)/utils" ]; then \
		echo "$(YELLOW)Warning: Both ft_printf_test_utils.c and utils/ directory exist.$(RESET)"; \
		echo "$(YELLOW)Checking for duplicate functions...$(RESET)"; \
		FUNCS_IN_MONOLITH=$$(grep -o "^[a-z_]* [a-z_0-9]*(" "$(TESTER_DIR)/ft_printf_test_utils.c" | sed 's/(.*//' | sort); \
		FUNCS_IN_UTILS=""; \
		for util_file in $$(find "$(TESTER_DIR)/utils" -name "*.c"); do \
			FUNCS_IN_UTILS="$$FUNCS_IN_UTILS $$(grep -o "^[a-z_]* [a-z_0-9]*(" "$$util_file" | sed 's/(.*//' | sort)"; \
		done; \
		echo "$(CYAN)Modular utility files will take precedence over monolithic file.$(RESET)"; \
	fi

# Universal compilation rule for all tester source files
$(OBJ_DIR)/tester/%.o: $(TESTER_DIR)/%.c
	$(call print_compilation_header,test,$(PINK)TEST COMPONENTS COMPILATION)
	@if [ -d "$(TESTER_DIR)/utils" ] && echo "$<" | grep -q "ft_printf_test_utils.c" && \
	   find "$(TESTER_DIR)/utils" -name "*.c" | grep -q "." ; then \
		echo "$(YELLOW)⚠ Skipping monolithic $(notdir $<) since modular files exist$(RESET)"; \
		mkdir -p $(dir $@); \
		echo "// Empty placeholder - modular files used instead" > $(dir $@)/empty_placeholder.c; \
		$(CC) $(CFLAGS) $(INCLUDES) -c $(dir $@)/empty_placeholder.c -o $@; \
		rm -f $(dir $@)/empty_placeholder.c; \
	else \
		mkdir -p $(dir $@); \
		printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-40s$(RESET) " "$(subst $(TESTER_DIR)/,,$<)"; \
		$(CC) $(CFLAGS) $(INCLUDES) -I. -I$(TESTER_DIR) -I$(dir $(GLOBALS_FILE)) -c $< -o $@ || \
			{ printf "$(RED)Failed to compile %s$(RESET)\n" "$<"; exit 1; }; \
		printf "$(GREEN)$(CHECK)$(RESET)\n"; \
	fi

# Special rule for files requiring additional include paths
$(OBJ_DIR)/tester/%/%.o:
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-40s$(RESET) " "$(subst $(OBJ_DIR)/tester/,,$@)"
	@$(CC) $(CFLAGS) $(INCLUDES) -I. -I$(TESTER_DIR) -I$(dir $(GLOBALS_FILE)) -c $(subst $(OBJ_DIR)/tester/,$(TESTER_DIR)/,$(patsubst %.o,%.c,$@)) -o $@ || \
		{ printf "$(RED)Failed to compile %s$(RESET)\n" "$<"; exit 1; }
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

# Explicitly handle files in srcs/ directory
$(OBJ_DIR)/tester/srcs/%.o: $(TESTER_DIR)/srcs/%.c
	$(call print_compilation_header,src,$(PINK)SOURCE COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building:$(RESET) $(YELLOW)%-40s$(RESET) " "srcs/$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -I. -I$(TESTER_DIR) -I$(TESTER_DIR)/utils -c $< -o $@ || \
		{ printf "$(RED)Failed to compile %s$(RESET)\n" "$<"; exit 1; }
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

# Special rule for controller and tester objects - handle direct linkage of srcs/ executables
$(OBJ_DIR)/tester/%.o: $(TESTER_DIR)/srcs/%.c
	$(call print_compilation_header,src,$(PINK)EXECUTABLE COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(BOLD_CYAN)▶ Building Root Executable:$(RESET) $(YELLOW)%-40s$(RESET) " "srcs/$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -I. -I$(TESTER_DIR) -I$(TESTER_DIR)/utils -c $< -o $@ || \
		{ printf "$(RED)Failed to compile %s$(RESET)\n" "$<"; exit 1; }
	@printf "$(GREEN)$(CHECK)$(RESET)\n"

# Compile ft_printf source files
$(OBJ_DIR)/printf/%.o: $(PRINTF_DIR)/%.c
	$(call print_compilation_header,printf,$(MAGENTA)CORE COMPONENTS COMPILATION)
	@mkdir -p $(dir $@)
	@printf "  $(CYAN)%-40s$(RESET) " "$(notdir $<) $(GRAY)($(shell dirname $(subst $(PRINTF_DIR)/,,$<)))$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || \
		{ printf "$(RED)Failed to compile %s$(RESET)\n" "$<"; exit 1; }
	@printf "$(GREEN)$(CHECK) Compiled$(RESET)\n"

.PHONY: utils-check

