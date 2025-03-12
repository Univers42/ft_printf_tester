# Controller setup with fancy header
controller: $(PROGRAM_DIR)/ft_printf_ultimate_controller
	$(call display_controller_header)
	$(call setup_controller_indicator)
	@echo "$(YELLOW)⚙ Launching comprehensive test suite...$(RESET)"
	@echo ""
	@sleep 0.5
	@# Run the actual test controller
	@$(PROGRAM_DIR)/ft_printf_ultimate_controller;
	$(call cleanup_controller_indicator)

# Add the actual test targets using our new macro
$(eval $(call define_test_target,simple,ft_printf_debug_tester_simple,SIMPLE DEBUG TEST))
$(eval $(call define_test_target,debug,ft_printf_debug_tester,DEBUG TEST))
$(eval $(call define_test_target,flags,flag_combinations_tester,FLAG COMBINATIONS TEST))
$(eval $(call define_test_target,char,char_tests,CHARACTER TEST))
$(eval $(call define_test_target,chars_ex,char_tests_extended,EXTENDED CHARACTER TEST))
$(eval $(call define_test_target,ultimate,ft_printf_ultimate_tester,ULTIMATE TEST))
$(eval $(call define_test_target,test,ft_printf_tester,COMPREHENSIVE TEST SUITE))

# 3. Stress test - handled separately due to different format
stress: header_stress $(STRESS_TEST) footer_test
	@printf "$(GREEN)▶ Running ft_printf stress tester...$(RESET)\n"
	@$(STRESS_TEST)

# Extended controller (same as controller)
extended: controller