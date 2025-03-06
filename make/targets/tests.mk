controller: $(PROGRAM_DIR)/ft_printf_ultimate_controller
	@clear
	@echo "$(CYAN)╔══════════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║ $(BOLD)$(PINK)    F T _ P R I N T F   T E S T   C O N T R O L L E R    $(RESET)$(CYAN)         ║$(RESET)"
	@echo "$(CYAN)╚══════════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@# Create and launch the blinking notification in a persistent way
	@printf "#!/bin/bash\n\
	while true; do\n\
		printf \"\\r\$(BOLD_MAGENTA)⚡ CONTROLLER ACTIVE ⚡\$(RESET)\";\n\
		sleep 0.5;\n\
		printf \"\\r\$(BOLD_CYAN)⚡ CONTROLLER ACTIVE ⚡\$(RESET)\";\n\
		sleep 0.5;\n\
		printf \"\\r\$(BOLD_GREEN)⚡ CONTROLLER ACTIVE ⚡\$(RESET)\";\n\
		sleep 0.5;\n\
		printf \"\\r\$(BOLD_GOLD)⚡ CONTROLLER ACTIVE ⚡\$(RESET)\";\n\
		sleep 0.5;\n\
	done" > /tmp/ft_printf_blinker.sh 2>/dev/null
	@chmod +x /tmp/ft_printf_blinker.sh 2>/dev/null
	@# Launch blinking indicator in background, will terminate when test completes
	@(nohup bash /tmp/ft_printf_blinker.sh > /dev/null 2>&1 & echo $$! > /tmp/ft_printf_blinker.pid) 2>/dev/null
	@echo "$(YELLOW)⚙ Launching comprehensive test suite...$(RESET)"
	@echo ""
	@sleep 0.5
	@# Run the actual test controller
	@$(PROGRAM_DIR)/ft_printf_ultimate_controller; \
	if [ -f /tmp/ft_printf_blinker.pid ]; then \
		kill -9 $$(cat /tmp/ft_printf_blinker.pid) > /dev/null 2>&1 || true; \
		rm -f /tmp/ft_printf_blinker.pid /tmp/ft_printf_blinker.sh > /dev/null 2>&1; \
	fi

# Add the actual test targets
# 1. Simple debug test
simple: $(PROGRAM_DIR)/ft_printf_debug_tester_simple
	@$(call test_header,"SIMPLE DEBUG TEST")
	@$(PROGRAM_DIR)/ft_printf_debug_tester_simple

# 2. Debug test
debug: $(PROGRAM_DIR)/ft_printf_debug_tester
	@$(call test_header,"DEBUG TEST")
	@$(PROGRAM_DIR)/ft_printf_debug_tester

# 3. Stress test
stress: header_stress $(STRESS_TEST) footer_test
	@printf "$(GREEN)▶ Running ft_printf stress tester...$(RESET)\n"
	@$(STRESS_TEST)

# 4. Flag combinations test
flags: $(PROGRAM_DIR)/flag_combinations_tester
	@$(call test_header,"FLAG COMBINATIONS TEST")
	@$(PROGRAM_DIR)/flag_combinations_tester

# 5. Character tests
char: $(PROGRAM_DIR)/char_tests
	@$(call test_header,"CHARACTER TEST")
	@$(PROGRAM_DIR)/char_tests

# 6. Extended character tests
chars_ex: $(PROGRAM_DIR)/char_tests_extended
	@$(call test_header,"EXTENDED CHARACTER TEST")
	@$(PROGRAM_DIR)/char_tests_extended

# 7. Ultimate test
ultimate: $(PROGRAM_DIR)/ft_printf_ultimate_tester
	@$(call test_header,"ULTIMATE TEST")
	@$(PROGRAM_DIR)/ft_printf_ultimate_tester

# 8. All tests with summary
test: $(PROGRAM_DIR)/ft_printf_tester
	@$(call test_header,"COMPREHENSIVE TEST SUITE")
	@$(PROGRAM_DIR)/ft_printf_tester

# Extended controller (same as controller)
extended: controller