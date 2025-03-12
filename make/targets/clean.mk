# Clean targets with completely silent file removal
clean:
	$(call display_maintenance_header,CLEANING OPERATION)
	$(call display_scanning_animation,Removing object files,3,for temporary files)
	
	$(call display_wipe_operation,object directory,20,Removing build artifacts)
	@-rm -rf $(OBJ_DIR) 2>/dev/null
	@-rm -f $(OBJ_DIR)/.*.printed 2>/dev/null
	@-rm -f /tmp/ft_printf_error.log 2>/dev/null
	
	$(call display_completion,Clean operation,clean,)

fclean:
	$(call display_maintenance_header,FULL CLEANING OPERATION)
	$(call display_scanning_animation,Removing object files,2,objects)
	
	$(call display_wipe_operation,object directory,15,Removing build artifacts)
	@rm -rf $(OBJ_DIR) > /dev/null 2>&1
	@rm -rf ../obj > /dev/null 2>&1
	@rm -f ../libftprintf_supp.a > /dev/null 2>&1
	@rm -f ../libftprintf.a > /dev/null 2>&1
	@rm -rf ../libft/*.o > /dev/null 2>&1
	@rm -rf obj > /dev/null 2>&1
	
	$(call display_scanning_animation,Removing program files,2,executables)
	
	$(call display_wipe_operation,program directory,15,Removing executables)
	@rm -rf $(PROGRAM_DIR) > /dev/null 2>&1
	
	$(call display_completion,Full clean operation,fclean,\n)

re: fclean all
