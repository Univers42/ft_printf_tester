# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    build.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 14:02:45 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/12 15:50:37 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

build_root_project:
	@printf "$(BOLD_BLUE)╔════════════════════════════════════════╗$(RESET)\n"
	@printf "$(BOLD_BLUE)║$(RESET) $(BOLD_GREEN)BUILDING ROOT PROJECT$(RESET)$(BOLD_BLUE)                 ║$(RESET)\n"
	@printf "$(BOLD_BLUE)╚════════════════════════════════════════╝$(RESET)\n"
	@echo ""
	@printf "$(YELLOW)$(GEAR) Building ft_printf in parent directory...$(RESET)\n"
	@for i in 1 2 3 ; do \
		printf "  $(CYAN)Running make in root directory...$(RESET)\r" ; \
		sleep 0.2 ; \
	done
	
	@# Build with better error handling
	@if ! $(MAKE) -C $(PRINTF_DIR) > /tmp/ft_printf_make.log 2>&1; then \
		echo "$(RED)$(CROSS) Root project build failed. Error log:$(RESET)"; \
		cat /tmp/ft_printf_make.log; \
		exit 1; \
	fi
	@printf "  $(CYAN)Root project build $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n\n"
	
	@# Check for the libftprintf.a library
	@if [ -f "$(PRINTF_DIR)/libftprintf.a" ]; then \
		printf "  $(GREEN)Found libftprintf.a in root directory$(RESET)\n"; \
	else \
		printf "  $(RED)Error: libftprintf.a not found in root directory$(RESET)\n"; \
		exit 1; \
	fi
	
	@# Generate supplemental library with potentially missing functions
	@printf "$(YELLOW)$(GEAR) Checking for missing functions...$(RESET)\n"
	@# Create a directory to store supplemental objects in parent directory
	@mkdir -p $(PRINTF_DIR)/obj
	
	@printf "$(CYAN)=== Finding Missing Object Files ===$(RESET)\n"
	@printf "$(YELLOW)Looking for missing functions...$(RESET)\n"
	
	@# Define missing functions to search for
	@missing_found=0; \
	cd $(PRINTF_DIR) && \
	for func in "ft_print_width" "ft_flags_init" "ft_isflag" "ft_istype"; do \
		printf "$(YELLOW)Looking for $$func...$(RESET)"; \
		files=$$(grep -l "^[^/]*$$func" --include="*.c" -r src/ 2>/dev/null || echo ""); \
		if [ -z "$$files" ]; then \
			printf "$(RED)Not found!$(RESET)\n"; \
		else \
			printf "$(GREEN)Found in: $(CYAN)$$files$(RESET)\n"; \
			for file in $$files; do \
				base_file=$$(basename "$$file" .c); \
				dir_name=$$(dirname "$$file" | sed 's|^src/||'); \
				obj_path="obj/$$dir_name"; \
				mkdir -p "$$obj_path" 2>/dev/null; \
				if [ ! -f "$$obj_path/$$base_file.o" ]; then \
					printf "$(YELLOW)Compiling $$file for $$func...$(RESET)\n"; \
					gcc -Wall -Wextra -Werror -I. -I./include -c "$$file" -o "$$obj_path/$$base_file.o"; \
					if [ $$? -eq 0 ]; then \
						printf "$(GREEN)Successfully compiled $$file$(RESET)\n"; \
						missing_found=1; \
					else \
						printf "$(RED)Failed to compile $$file$(RESET)\n"; \
					fi; \
				else \
					printf "$(GREEN)Already compiled: $$file$(RESET)\n"; \
					missing_found=1; \
				fi; \
			done; \
		fi; \
	done; \
	\
	printf "\n$(CYAN)=== Creating Supplemental Archive ===$(RESET)\n"; \
	if [ $$missing_found -eq 1 ]; then \
		find obj -type f -name "*.o" -print0 | xargs -0 ar rcs libftprintf_supp.a; \
		printf "$(GREEN)Created supplemental archive with missing functions$(RESET)\n"; \
	else \
		printf "$(YELLOW)No supplemental objects to archive$(RESET)\n"; \
	fi
	
	@if [ -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
		printf "  $(GREEN)Supplemental library generated successfully$(RESET)\n"; \
	else \
		printf "  $(YELLOW)Warning: Supplemental library not found, linking may fail$(RESET)\n"; \
	fi
	
	@# Check if libft directory exists
	@if [ -d "$(LIBFT_DIR)" ]; then \
		printf "$(YELLOW)$(GEAR) Building libft...$(RESET)\n"; \
		if ! $(MAKE) -C $(LIBFT_DIR) > /tmp/ft_printf_libft.log 2>&1; then \
			echo "$(RED)$(CROSS) Libft build failed. Error log:$(RESET)"; \
			cat /tmp/ft_printf_libft.log; \
			exit 1; \
		fi; \
		printf "  $(CYAN)Libft build $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n\n"; \
	else \
		printf "$(YELLOW)$(WARN) Libft directory not found at $(LIBFT_DIR)$(RESET)\n"; \
		printf "$(YELLOW)$(GEAR) Creating libft stub directory...$(RESET)\n"; \
		mkdir -p $(LIBFT_DIR); \
		printf "  $(CYAN)Libft directory created $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n\n"; \
		printf "$(YELLOW)$(GEAR) Creating empty libft.a...$(RESET)\n"; \
		touch $(LIBFT); \
		printf "  $(CYAN)Empty libft.a created $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n\n"; \
		printf "$(YELLOW)$(INFO) Note: You may need to provide a real libft.a file later$(RESET)\n\n"; \
	fi
	
	@# Recursive directory structure syncing
	@echo "$(YELLOW)$(GEAR) Locating source files in project directory...$(RESET)"
	$(call print_found_files, $(PRINTF_SRCS))
	
	@# Clean up any previous objects first to prevent duplicates
	@rm -rf $(OBJ_DIR)/printf
	
	@if [ -d "$(ROOT_OBJ_DIR)" ]; then \
		printf "\n$(YELLOW)$(GEAR) Synchronizing object files...$(RESET)\n"; \
		mkdir -p $(OBJ_DIR)/printf; \
		find $(ROOT_OBJ_DIR) -type f -name "*.o" ! -path "*/libft/*" | sort | uniq | while read src; do \
			filename=$$(basename $$src); \
			if [ ! -f "$(OBJ_DIR)/printf/$$filename" ]; then \
				rel_path=$$(echo $$src | sed 's|$(ROOT_OBJ_DIR)/||'); \
				dst_dir=$(OBJ_DIR)/printf/$$(dirname $$rel_path); \
				printf "  $(CYAN)Syncing: %s$(RESET)\n" "$$rel_path"; \
				mkdir -p $$dst_dir 2>/dev/null || true; \
				cp $$src $$dst_dir/ 2>/dev/null || true; \
			fi \
		done; \
		printf "  $(CYAN)Object synchronization $(GREEN)[$(BOLD)✓$(RESET)$(GREEN)]$(RESET)\n"; \
	else \
		printf "  $(YELLOW)Warning: Root Object directory not found. Creating objects locally.$(RESET)\n"; \
		for src in $(PRINTF_SRCS); do \
			rel_path=$$(echo $$src | sed 's|$(PRINTF_DIR)/||'); \
			obj_path=$(OBJ_DIR)/printf/$$(dirname $$rel_path); \
			printf "  $(CYAN)Will compile: %s -> %s$(RESET)\n" "$$rel_path" "$$obj_path"; \
			mkdir -p $$obj_path; \
		done; \
	fi
	@echo ""
# Build libft project with animations
$(LIBFT):
	@printf "$(BG_DARK_BLUE)$(BOLD_WHITE) LIBFT $(RESET) $(BOLD_YELLOW)Importing dependency...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo ""
	@echo -n "$(BOLD_YELLOW)Library status: $(RESET)"
	@for i in 1 2 3; do \
		printf "$(YELLOW)⬤$(RESET) " ; \
		sleep 0.1 ; \
	done
	@echo "$(BOLD_GREEN)LINKED$(RESET)"
	@echo ""

