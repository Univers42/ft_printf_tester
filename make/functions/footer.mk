# Main footer function with all components
define footer_all
	@echo ""
	@for i in 1 2 3; do \
		printf "\r\033[1m\033[32m✨ BUILD SUCCESSFUL! ✨\033[0m" ; \
		sleep 0.15 ; \
		printf "\r\033[1m\033[33m✨ BUILD SUCCESSFUL! ✨\033[0m" ; \
		sleep 0.15 ; \
	done
	@printf "\r\033[1m\033[32m✨ BUILD SUCCESSFUL! ✨\033[0m\n\n"
	
	$(call display_success_banner)
	@echo ""
	$(call animate_controller_prompt)
	@sleep 0.5
	@echo ""
	
	@echo "$(BOLD)$(UNDERLINE)$(SKY)AVAILABLE TEST TARGETS:$(RESET)"
	@echo ""
	$(call display_test_target,"1","Run simple debug test","simple")
	$(call display_test_target,"2","Run debug test","debug")
	$(call display_test_target,"3","Run stress test","stress")
	$(call display_test_target,"4","Run flag combinations test","flags")
	$(call display_test_target,"5","Run character tests","char")
	$(call display_test_target,"6","Run extended character tests","chars_ex")
	$(call display_test_target,"7","Run ultimate test","ultimate")
	$(call display_test_target,"8","Run all tests with summary","test")
	@echo ""
	@sleep 0.2
	
	@echo "$(BOLD)$(TEAL)Command History:$(RESET)"
	@echo "$(GRAY)$ make all$(RESET)  $(GREEN)✓ Finished$(RESET)\n"
endef

footer_all:
	$(call footer_all)