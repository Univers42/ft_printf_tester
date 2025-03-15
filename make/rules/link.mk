# Function to handle conditional linking with error handling
# $(1): Target file
# $(2): Main object file
define link_with_libs
	@mkdir -p $(dir $(1))
	@MODULAR_UTILS=$$(find $(OBJ_DIR)/tester/utils -type f -name "*.o" 2>/dev/null || echo ""); \
	if [ -n "$$MODULAR_UTILS" ]; then \
		MODULES="$$MODULAR_UTILS"; \
		if [ "$(notdir $(1))" = "ft_printf_stress_tester" ]; then \
			echo "$(YELLOW)⚠ Special case: Including only necessary modules for ft_printf_stress_tester$(RESET)"; \
			MODULES="$(OBJ_DIR)/tester/utils/ft_printf_test_globals.o \
					 $(OBJ_DIR)/tester/utils/ft_printf_test_runner.o \
					 $(OBJ_DIR)/tester/utils/ft_printf_general_tests.o \
					 $(OBJ_DIR)/tester/utils/ft_printf_output_format.o \
					 $(OBJ_DIR)/tester/utils/ft_printf_capture.o \
					 $(OBJ_DIR)/tester/utils/ft_printf_str_char_tests.o \
					 $(OBJ_DIR)/tester/utils/ft_printf_num_tests.o \
					 $(OBJ_DIR)/tester/utils/ft_printf_ptr_tests.o"; \
		else \
			MODULES="$$MODULES $$(find $(OBJ_DIR)/tester -maxdepth 1 -type f -name "*_ft_printf.o")"; \
		fi; \
		MODULES=$$(echo "$$MODULES" | tr ' ' '\n' | grep -v "^$(2)$$" | tr '\n' ' '); \
		echo "$(CYAN)➤ Using modular utils: Found $$(echo $$MODULES | wc -w) modules$(RESET)"; \
	else \
		UTILS="$$(find $(OBJ_DIR)/tester -maxdepth 1 -type f -name "*_utils.o" -o -name "*_ft_printf.o")"; \
		UTILS="$$(echo "$$UTILS" | tr ' ' '\n' | grep -v "^$(2)$$" | tr '\n' ' ')"; \
		MODULES="$$UTILS"; \
		echo "$(CYAN)➤ Using monolithic utils: Found $$(echo $$MODULES | wc -w) modules$(RESET)"; \
	fi; \
	\
	LINK_CMD=""; \
	HAS_LIBFT=$$([ -f "$(LIBFT_DIR)/libft.a" ] && [ -s "$(LIBFT_DIR)/libft.a" ] && echo "true" || echo "false"); \
	HAS_SUPP=$$([ -f "$(PRINTF_DIR)/libftprintf_supp.a" ] && echo "true" || echo "false"); \
	\
	if [ "$$HAS_SUPP" = "true" ]; then \
		if [ "$$HAS_LIBFT" = "true" ]; then \
			echo "$(GREEN)➤ Linking with: libftprintf + libftprintf_supp + libft$(RESET)"; \
			LINK_CMD="$(CC) $(CFLAGS) -o $(1) $(2) $$MODULES -L$(PRINTF_DIR) -lftprintf -lftprintf_supp -L$(LIBFT_DIR) -lft"; \
		else \
			echo "$(YELLOW)➤ Linking with: libftprintf + libftprintf_supp (no libft)$(RESET)"; \
			LINK_CMD="$(CC) $(CFLAGS) -o $(1) $(2) $$MODULES -L$(PRINTF_DIR) -lftprintf -lftprintf_supp"; \
		fi; \
	else \
		if [ "$$HAS_LIBFT" = "true" ]; then \
			echo "$(GREEN)➤ Linking with: libftprintf + libft$(RESET)"; \
			LINK_CMD="$(CC) $(CFLAGS) -o $(1) $(2) $$MODULES -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft"; \
		else \
			echo "$(YELLOW)➤ Linking with: libftprintf only (no libft)$(RESET)"; \
			LINK_CMD="$(CC) $(CFLAGS) -o $(1) $(2) $$MODULES -L$(PRINTF_DIR) -lftprintf"; \
		fi; \
	fi; \
	\
	if ! eval $$LINK_CMD 2>/tmp/ft_printf_error.log; then \
		printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $(1))$(RESET)\n"; \
		echo "$(RED)Link error details:$(RESET)"; \
		cat /tmp/ft_printf_error.log; \
		echo "$(YELLOW)Debug information:$(RESET)"; \
		echo "  - Main object: $(2)"; \
		echo "  - Module objects: $$MODULES"; \
		echo "  - Link command: $$LINK_CMD"; \
		echo "  - Library status:"; \
		ls -la $(PRINTF_DIR)/libftprintf.a 2>/dev/null; \
		if [ "$$HAS_SUPP" = "true" ]; then ls -la $(PRINTF_DIR)/libftprintf_supp.a 2>/dev/null; fi; \
		if [ "$$HAS_LIBFT" = "true" ]; then ls -la $(LIBFT_DIR)/libft.a 2>/dev/null; fi; \
		echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
		exit 1; \
	fi
endef

# Function to handle generic linking with animations
# $(1): Target file
# $(2): Main object file
define link_with_animation
	$(call print_link_header)
	$(call display_animation,"Linking",$(notdir $(1)),1)
	$(call link_with_libs,$(1),$(2))
	@printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n" "$(notdir $(1))"
	@sleep 0.05
endef

# Generic linking rule for test executables - now handles both flat and structured paths
$(PROGRAM_DIR)/%: $(OBJ_DIR)/tester/%.o
	$(call link_with_animation,$@,$<)

# Recursive subdirectory linking rule
define link_recursive_rules
$(PROGRAM_DIR)/$(1)/%: $(OBJ_DIR)/tester/$(1)/%.o
	@mkdir -p $$(dir $$@)
	$$(call link_with_animation,$$@,$$<)
endef

# Create linking rules for all subdirectories
SUBDIRS := $(sort $(dir $(shell find $(TESTER_DIR) -mindepth 2 -type f -name "*.c" | sed -e 's|$(TESTER_DIR)/||' -e 's|/[^/]*$$|/|')))
$(foreach dir,$(SUBDIRS),$(eval $(call link_recursive_rules,$(patsubst %/,%,$(dir)))))

# Special rule for flattening directory structure for executables
define flatten_executable_rule
$(PROGRAM_DIR)/$(notdir $(1)): $(OBJ_DIR)/tester/$(1).o
	$$(call link_with_animation,$$@,$$<)
endef

# Apply the flattening rule to each executable that's in a subdirectory
$(foreach exec,$(filter-out $(notdir $(TEST_EXECUTABLES)),$(TEST_EXECUTABLES)),\
	$(eval $(call flatten_executable_rule,$(exec))))

# Special linking rule for ultimate tester with extra animations
$(PROGRAM_DIR)/ft_printf_ultimate_tester: $(OBJ_DIR)/tester/ft_printf_ultimate_tester.o
	$(call print_link_header)
	$(call display_emoji_animation,"Linking",$(notdir $@),4)
	$(call link_with_libs,$@,$<)
	@printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n" "$(notdir $@)"
	@sleep 0.05

# Special linking for the controller
$(PROGRAM_DIR)/ft_printf_ultimate_controller: $(OBJ_DIR)/tester/ft_printf_ultimate_controller.o
	@mkdir -p $(PROGRAM_DIR)
	$(call print_link_header)
	$(call display_controller_animation,$(notdir $@),4)
	$(call link_with_libs,$@,$<)
	@printf "\r  $(BOLD_PURPLE)▶ Linking Controller:$(RESET) $(WHITE)%-25s $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n" "$(notdir $@)"
	@sleep 0.05

# Add special targets for executables in srcs/ directory
controller: $(PROGRAM_DIR)/ft_printf_ultimate_controller
	@echo "$(GREEN)$(CHECK) Controller built successfully!$(RESET)"

tester: $(PROGRAM_DIR)/ft_printf_ultimate_tester
	@echo "$(GREEN)$(CHECK) Tester built successfully!$(RESET)"

# Make these targets phony so they always run
.PHONY: controller tester
