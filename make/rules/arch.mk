# Create directories with cleaner animation
make_dirs:
	@printf "$(BOLD_CYAN)╔════════════════════════════════════════╗$(RESET)\n"
	@printf "$(BOLD_CYAN)║$(RESET) $(BOLD_YELLOW)SYSTEM ENVIRONMENT PREPARATION$(RESET)$(BOLD_CYAN)         ║$(RESET)\n"
	@printf "$(BOLD_CYAN)╚════════════════════════════════════════╝$(RESET)\n"
	@echo ""
	@printf "$(YELLOW)$(GEAR) Creating system directories:$(RESET)\n"
	
	@# Create obj directory with animation
	@$(call create_dir_with_animation,$(OBJ_DIR),"obj/")
	@$(call create_dir_with_animation,$(OBJ_DIR)/tester,"obj/tester/")
	@$(call create_dir_with_animation,$(OBJ_DIR)/printf,"obj/printf/")
	
	@# Create program directory with animation
	@$(call create_dir_with_animation,$(PROGRAM_DIR),"program/")
	
	@# Create subdirectories matching source structure
	@find $(TESTER_DIR) -mindepth 1 -type d | grep -v "src" | sort | while read dir; do \
		rel_dir=$$(echo $$dir | sed 's|$(TESTER_DIR)/||'); \
		mkdir -p "$(OBJ_DIR)/tester/$$rel_dir"; \
		printf "  $(CYAN)➤ Creating obj/tester/$$rel_dir $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"; \
		mkdir -p "$(PROGRAM_DIR)/$$rel_dir"; \
		printf "  $(CYAN)➤ Creating program/$$rel_dir $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"; \
	done
	
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
	done
	@printf "\r  $(CYAN)➤ Initializing $(2) directory $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"
endef
