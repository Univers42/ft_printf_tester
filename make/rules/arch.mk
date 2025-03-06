# Create directories with cleaner animation
make_dirs:
	@printf "$(BOLD_CYAN)╔════════════════════════════════════════╗$(RESET)\n"
	@printf "$(BOLD_CYAN)║$(RESET) $(BOLD_YELLOW)SYSTEM ENVIRONMENT PREPARATION$(RESET)$(BOLD_CYAN)         ║$(RESET)\n"
	@printf "$(BOLD_CYAN)╚════════════════════════════════════════╝$(RESET)\n"
	@echo ""
	@printf "$(YELLOW)$(GEAR) Creating system directories:$(RESET)\n"
	
	@printf "  $(CYAN)➤ Initializing obj/ directory...$(RESET)"
	@mkdir -p $(OBJ_DIR)
	@for i in 1 2 3 4 5; do \
		printf "\r  $(CYAN)➤ Initializing obj/ directory...   $(RESET)" ; \
		sleep 0.1 ; \
		printf "\r  $(CYAN)➤ Initializing obj/ directory.     $(RESET)" ; \
		sleep 0.1 ; \
	done
	@printf "\r  $(CYAN)➤ Initializing obj/ directory $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"

	@printf "  $(CYAN)➤ Initializing program/ directory...$(RESET)"
	@mkdir -p $(PROGRAM_DIR)
	@for i in 1 2 3 4 5; do \
		printf "\r  $(CYAN)➤ Initializing program/ directory...   $(RESET)" ; \
		sleep 0.1 ; \
		printf "\r  $(CYAN)➤ Initializing program/ directory.     $(RESET)" ; \
		sleep 0.1 ; \
	done
	@printf "\r  $(CYAN)➤ Initializing program/ directory $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"
	
	@echo ""
	@echo "$(GREEN)$(CHECK) Build environment ready!$(RESET)"
	@echo ""
