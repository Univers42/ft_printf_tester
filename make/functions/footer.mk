define footer_all
	@echo ""
	@for i in 1 2 3; do \
		printf "\r$(BOLD)$(GREEN)$(SPARKLE) BUILD SUCCESSFUL! $(SPARKLE)$(RESET)" ; \
		sleep 0.15 ; \
		printf "\r$(BOLD)$(YELLOW)$(SPARKLE) BUILD SUCCESSFUL! $(SPARKLE)$(RESET)" ; \
		sleep 0.15 ; \
	done
	@printf "\r$(BOLD)$(GREEN)$(SPARKLE) BUILD SUCCESSFUL! $(SPARKLE)$(RESET)\n\n"
	@echo "$(GOLD)╔═══════════════════════════════════════════════════════════════════╗$(RESET)"
	@printf "$(GOLD)║$(RESET)$(BOLD)$(GREEN)✓$(RESET)$(CYAN)All test programs compiled successfully!$(RESET)%26s$(GOLD)║$(RESET)\n" " "
	@echo "$(GOLD)╚═══════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(PURPLE)┌─────────────────────────────────────────────────────────────────┐$(RESET)"
	@echo "$(PURPLE)│$(RESET) $(YELLOW)Use $(RESET)$(BOLD_CYAN)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)"
	@echo -n "$(PURPLE)│$(RESET) $(YELLOW)Use '$(RESET)"
	@for i in 1 2 3; do \
		printf "$(BOLD_CYAN)make controller$(RESET)$(YELLOW)' to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(BOLD_MAGENTA)make controller$(RESET)$(YELLOW)' to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(BOLD_GREEN)make controller$(RESET)$(YELLOW)' to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
		printf "$(BOLD_GOLD)make controller$(RESET)$(YELLOW)' to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo "$(PURPLE)│$(RESET) $(YELLOW)Use $(BOLD_CYAN)'make controller'$(RESET)$(YELLOW) to run the comprehensive test controller$(RESET) $(PURPLE) │$(RESET)"
	@echo "$(PURPLE)└─────────────────────────────────────────────────────────────────┘$(RESET)"
	@sleep 0.5
	@echo ""
	@echo "$(BOLD)$(UNDERLINE)$(SKY)AVAILABLE TEST TARGETS:$(RESET)"
	@echo ""
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 1 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run simple debug test$(RESET)\n" "make simple"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 2 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run debug test$(RESET)\n" "make debug"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 3 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run stress test$(RESET)\n" "make stress"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 4 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run flag combinations test$(RESET)\n" "make flags"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 5 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run character tests$(RESET)\n" "make char"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 6 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run extended character tests$(RESET)\n" "make chars_ex"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 7 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run ultimate test$(RESET)\n" "make ultimate"
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) 8 $(RESET) $(GREEN)➤ $(YELLOW)%-12s$(RESET) $(MINT)Run all tests with summary$(RESET)\n" "make test"
	@echo ""
	@sleep 0.2
	@echo "$(BOLD)$(TEAL)Command History:$(RESET)"
	@echo "$(GRAY)$ make all$(RESET)  $(GREEN)✓ Finished$(RESET)\n"
endef

footer_all:
	$(footer_all)