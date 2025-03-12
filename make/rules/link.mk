# Function to handle conditional linking with error handling
# $(1): Target file
# $(2): Main object file
define link_with_libs
	@mkdir -p $(dir $(1))
	@# Get all utility objects with proper grouping for find command
	@UTIL_OBJECTS=$$(find $(OBJ_DIR)/tester -type f \( -name "*_utils.o" -o -name "*_ft_printf.o" -o -name "ft_printf_test_utils.o" -o -name "simple_ft_printf.o" \)); \
	echo "Found utility objects: $$UTIL_OBJECTS"; \
	if [ -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
		if ! $(CC) $(CFLAGS) -o $(1) $(2) $$UTIL_OBJECTS -L$(PRINTF_DIR) -lftprintf -lftprintf_supp -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $(1))$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Main object: $(2)"; \
			echo "  - Utility objects: $$UTIL_OBJECTS"; \
			echo "  - Printf libraries: $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			echo "  - Library status:"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	else \
		if ! $(CC) $(CFLAGS) -o $(1) $(2) $$UTIL_OBJECTS -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $(1))$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Main object: $(2)"; \
			echo "  - Utility objects: $$UTIL_OBJECTS"; \
			echo "  - Printf library: $(PRINTF_DIR)/libftprintf.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			echo "  - Library status:"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
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

# Generic linking rule for test executables
$(PROGRAM_DIR)/%: $(OBJ_DIR)/tester/%.o
	$(call link_with_animation,$@,$<)

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
