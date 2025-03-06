# Clean targets with completely silent file removal
clean:
	@clear
	@printf "$(BG_BLUE)$(BOLD_WHITE) SYSTEM MAINTENANCE: CLEANING OPERATION $(RESET)\n\n"
	@printf "$(YELLOW)$(GEAR) Removing object files...$(RESET)\n\n"
	
	@# Display scanning animation
	@for i in $(shell seq 1 3); do \
		printf "  $(CYAN)Scanning for temporary files...$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning for temporary files$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning for temporary files$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning for temporary files$(RESET).$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo ""
	$(RM) $
	@# Show wipe animation with progress bar
	@echo "  $(YELLOW)Wiping object directory:$(RESET)"
	$(call progress_bar,20,30,"Removing build artifacts")
	@-rm -rf $(OBJ_DIR) 2>/dev/null
	@-rm -f $(OBJ_DIR)/.*.printed 2>/dev/null
	@-rm -f /tmp/ft_printf_error.log 2>/dev/null
	
	@echo ""
	@printf "$(GREEN)$(BOLD)$(CHECK) Clean operation complete!$(RESET)\n"
	@printf "$(GRAY)$ make clean$(RESET)  $(GREEN)✓ Finished$(RESET)\n"

fclean:
	@clear
	@printf "$(BG_BLUE)$(BOLD_WHITE) SYSTEM MAINTENANCE: FULL CLEANING OPERATION $(RESET)\n\n"
	@printf "$(YELLOW)$(GEAR) Removing object files...$(RESET)\n\n"
	
	@# Display scanning animation for objects
	@for i in $(shell seq 1 2); do \
		printf "  $(CYAN)Scanning objects...$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning objects$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning objects$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning objects$(RESET).$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo ""
	
	@# Show wipe animation with progress bar for objects
	@echo "  $(YELLOW)Wiping object directory:$(RESET)"
	$(call progress_bar,15,30,"Removing build artifacts")
	@rm -rf $(OBJ_DIR) > /dev/null 2>&1
	@rm -rf ../obj > /dev/null 2>&1
	@rm -f ../libftprintf_supp.a > /dev/null 2>&1
	@rm -f ../libftprintf.a > /dev/null 2>&1
	@rm -rf ../libft/*.o > /dev/null 2>&1
	@rm -rf obj > /dev/null 2>&1
	@printf "$(YELLOW)$(GEAR) Removing program files...$(RESET)\n\n"
	
	@# Display scanning animation for programs
	@for i in $(shell seq 1 2); do \
		printf "  $(CYAN)Scanning executables...$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning executables$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning executables$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
		printf "  $(CYAN)Scanning executables$(RESET).$(RESET).$(RESET).$(RESET)\r"; \
		sleep 0.2; \
	done
	@echo ""
	
	@# Show wipe animation with progress bar for programs
	@echo "  $(YELLOW)Wiping program directory:$(RESET)"
	$(call progress_bar,15,30,"Removing executables")
	@rm -rf $(PROGRAM_DIR) > /dev/null 2>&1
	
	@echo ""
	@printf "$(GREEN)$(BOLD)$(CHECK) Full clean operation complete!$(RESET)\n"
	@printf "$(GRAY)$ make fclean$(RESET)  $(GREEN)✓ Finished$(RESET)\n\n"


re: fclean all
