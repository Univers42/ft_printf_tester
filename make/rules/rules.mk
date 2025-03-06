
# Empty rule to prevent attempting to build ft_printf_test_utils as an executable
$(TEST_UTILS):
	@echo "$(YELLOW)⚠ $(TEST_UTILS) is not an executable target$(RESET)"

# Empty rule to prevent attempting to build simple_ft_printf as an executable
$(SIMPLE_PRINTF):
	@echo "$(YELLOW)⚠ $(SIMPLE_PRINTF) is not an executable target$(RESET)"
