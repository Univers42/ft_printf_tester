
# Build tester executables with improved diagnostics
$(PROGRAM_DIR)/%: $(OBJ_DIR)/tester/%.o $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ)
	@if [ ! -f $(OBJ_DIR)/.link_header_printed ]; then \
		printf "\n$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"; \
		printf "$(BOLD_BLUE)║ $(LIME)LINKING TEST EXECUTABLES$(BLUE)               ║$(RESET)\n"; \
		printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n\n"; \
		touch $(OBJ_DIR)/.link_header_printed; \
	fi
	@mkdir -p $(PROGRAM_DIR)
	@printf "  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s " "$(notdir $@)"
	@for c in "/" "-" "\\" "|"; do \
		printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(YELLOW)[$$c]$(RESET)" "$(notdir $@)" ; \
		sleep 0.05; \
	done
	
	@# Use conditional linking to include supplemental library if it exists
	@if [ -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
		if ! $(CC) $(CFLAGS) -o $@ $< $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ) -L$(PRINTF_DIR) -lftprintf -lftprintf_supp -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $@)$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Main object: $<"; \
			echo "  - Test utils: $(TEST_UTILS_OBJ)"; \
			echo "  - Simple printf: $(SIMPLE_PRINTF_OBJ)"; \
			echo "  - Printf libraries: $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			echo "  - Library status:"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	else \
		if ! $(CC) $(CFLAGS) -o $@ $< $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ) -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $@)$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Main object: $<"; \
			echo "  - Test utils: $(TEST_UTILS_OBJ)"; \
			echo "  - Simple printf: $(SIMPLE_PRINTF_OBJ)"; \
			echo "  - Printf library: $(PRINTF_DIR)/libftprintf.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			echo "  - Library status:"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	fi
	@printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n" "$(notdir $@)"
	@sleep 0.05


# Special rule for ultimate_tester_extended with enhanced animation - FIXED LINKING
$(PROGRAM_DIR)/ft_printf_ultimate_tester: $(OBJ_DIR)/tester/ft_printf_ultimate_tester.o $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ)
	@printf "  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s " "$@"
	@for i in 1 2 3 4; do \
		for c in "🔄" "🔁" "♻️" "⚙️"; do \
			printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(YELLOW)[$$c]$(RESET)" "$@" ; \
			sleep 0.05; \
		done; \
	done
	@mkdir -p $(PROGRAM_DIR)
	
	@# Also add conditional linking here
	@if [ -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
		if ! $(CC) $(CFLAGS) -o $@ $< $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ) -L$(PRINTF_DIR) -lftprintf -lftprintf_supp -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $@)$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Printf libraries: $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(PRINTF_DIR)/libftprintf_supp.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	else \
		if ! $(CC) $(CFLAGS) -o $@ $< $(TEST_UTILS_OBJ) $(SIMPLE_PRINTF_OBJ) -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft 2>/tmp/ft_printf_error.log; then \
			printf "\r$(BOLD_RED)▶ Error:$(RESET) $(RED)Linking failed for $(notdir $@)$(RESET)\n"; \
			echo "$(RED)Link error details:$(RESET)"; \
			cat /tmp/ft_printf_error.log; \
			echo "$(YELLOW)Debug information:$(RESET)"; \
			echo "  - Printf library: $(PRINTF_DIR)/libftprintf.a"; \
			echo "  - Libft library: $(LIBFT_DIR)/libft.a"; \
			ls -la $(PRINTF_DIR)/libftprintf.a $(LIBFT_DIR)/libft.a 2>/dev/null || echo "  $(RED)ERROR: libraries not found!$(RESET)"; \
			echo "$(RED)$(CROSS) Build failed.$(RESET)"; \
			exit 1; \
		fi; \
	fi
	@printf "\r  $(BOLD_PURPLE)▶ Linking:$(RESET) $(WHITE)%-25s $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n" "$@"
	@sleep 0.05
