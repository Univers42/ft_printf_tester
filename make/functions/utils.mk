define print_found_files
	@echo "$(YELLOW)Found source files:$(RESET)"
	@for file in $(1); do \
		echo "  $(CYAN)$$file$(RESET)"; \
	done
endef

# Define a reusable function for the blinking controller indicator
define setup_controller_indicator
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
endef

# Define a function to clean up the controller indicator
define cleanup_controller_indicator
	@if [ -f /tmp/ft_printf_blinker.pid ]; then \
		kill -9 $$(cat /tmp/ft_printf_blinker.pid) > /dev/null 2>&1 || true; \
		rm -f /tmp/ft_printf_blinker.pid /tmp/ft_printf_blinker.sh > /dev/null 2>&1; \
	fi
endef

# Define a function to run a test program with proper header
define run_test_program
	@$(call test_header,"$(2)")
	@$(PROGRAM_DIR)/$(1)
endef

# Define macro to create a standard test target
define define_test_target
$(1): $(PROGRAM_DIR)/$(2)
	$$(call run_test_program,$(2),"$(3)")
endef





# Rainbow animation for the controller prompt - completely redesigned to avoid duplication
define animate_controller_prompt
	@echo "$(PURPLE)┌─────────────────────────────────────────────────────────────────┐$(RESET)"
	@for i in 1 2 3; do \
		printf "$(PURPLE)│$(RESET) $(YELLOW)Use $(BOLD_MAGENTA)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(PURPLE)│$(RESET) $(YELLOW)Use $(BOLD_CYAN)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(PURPLE)│$(RESET) $(YELLOW)Use $(BOLD_GREEN)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(PURPLE)│$(RESET) $(YELLOW)Use $(BOLD_GOLD)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
	done
	@printf "$(PURPLE)│$(RESET) $(YELLOW)Use $(BOLD_CYAN)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\n"
	@echo "$(PURPLE)└─────────────────────────────────────────────────────────────────┘$(RESET)"
endef
