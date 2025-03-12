# Create directories with cleaner animation
make_dirs:
	@printf "$(BOLD_CYAN)╔════════════════════════════════════════╗$(RESET)\n"
	@printf "$(BOLD_CYAN)║$(RESET) $(BOLD_YELLOW)SYSTEM ENVIRONMENT PREPARATION$(RESET)$(BOLD_CYAN)         ║$(RESET)\n"
	@printf "$(BOLD_CYAN)╚════════════════════════════════════════╝$(RESET)\n"
	@echo ""
	@printf "$(YELLOW)$(GEAR) Creating system directories:$(RESET)\n"
	
	@# Create obj directory with animation
	@$(call create_dir_with_animation,$(OBJ_DIR),"obj/")
	
	@# Create program directory with animation
	@$(call create_dir_with_animation,$(PROGRAM_DIR),"program/")
	
	@echo ""
	@echo "$(GREEN)$(CHECK) Build environment ready!$(RESET)"
	@echo ""

# Function to create directory with animation
# $(1): Directory path
# $(2): Directory name for display
define create_dir_with_animation
	@printf "  $(CYAN)➤ Initializing $(2) directory...$(RESET)"
	@mkdir -p $(1)
	@for i in 1 2 3 4 5; do \
		printf "\r  $(CYAN)➤ Initializing $(2) directory...   $(RESET)" ; \
		sleep 0.1 ; \
		printf "\r  $(CYAN)➤ Initializing $(2) directory.     $(RESET)" ; \
		sleep 0.1 ; \
	done
	@printf "\r  $(CYAN)➤ Initializing $(2) directory $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"
endef
