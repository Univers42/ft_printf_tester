# Simplified formatting functions
define print_msg
	@printf "%b%b%b\n" "$(2)" "$(1)" "$(RESET)"
endef

define print_status
	@printf "  %b%b %b\n" "$(CYAN)" "$(1)" "$(2)$(RESET)"
endef

# Main target that depends on all subtasks
build_root_project: build_printf check_missing_functions sync_objects
	@printf "\033[0;33mRoot project build complete\033[0m\n"

# Build the main printf project
build_printf: $(LIBFT)
	@printf "\033[0;34m╔═══════════════ BUILDING ROOT PROJECT ═══════════════╗\033[0m\n\n"
	@printf "\033[0;33mBuilding ft_printf in parent directory...\033[0m\n"
	
	@if ! $(MAKE) -C $(PRINTF_DIR) > /tmp/ft_printf_make.log 2>&1; then \
		printf "\033[0;31mRoot project build failed. Error log:\033[0m\n"; \
		cat /tmp/ft_printf_make.log; \
		exit 1; \
	fi
	@printf "  \033[0;36mRoot project build \033[0;32m[✓]\033[0m\n"
	
	@if [ ! -f "$(PRINTF_DIR)/libftprintf.a" ]; then \
		printf "\033[0;31mlibftprintf.a not found in root directory\033[0m\n"; \
		exit 1; \
	else \
		printf "\033[0;32mFound libftprintf.a in root directory\033[0m\n"; \
	fi

# Check for and compile any missing functions
check_missing_functions:
	@printf "\033[0;33mChecking for missing functions...\033[0m\n"
	@mkdir -p $(PRINTF_DIR)/obj
	
	@missing_found=0; \
	cd $(PRINTF_DIR) && \
	for func in "ft_print_width" "ft_flags_init" "ft_isflag" "ft_istype"; do \
		printf "\033[0;33mLooking for $$func...\033[0m"; \
		files=$$(grep -l "^[^/]*$$func" --include="*.c" -r src/ 2>/dev/null || echo ""); \
		if [ -z "$$files" ]; then \
			printf "\033[0;31mNot found!\033[0m\n"; \
		else \
			printf "\033[0;32mFound in: $$files\033[0m\n"; \
			for file in $$files; do \
				base_file=$$(basename "$$file" .c); \
				dir_name=$$(dirname "$$file" | sed 's|^src/||'); \
				obj_path="obj/$$dir_name"; \
				mkdir -p "$$obj_path" 2>/dev/null; \
				if [ ! -f "$$obj_path/$$base_file.o" ]; then \
					printf "\033[0;33mCompiling $$file...\033[0m\n"; \
					gcc -Wall -Wextra -Werror -I. -I./include -c "$$file" -o "$$obj_path/$$base_file.o" && \
					printf "\033[0;32mSuccessfully compiled $$file\033[0m\n" && missing_found=1 || \
					printf "\033[0;31mFailed to compile $$file\033[0m\n"; \
				else \
					printf "\033[0;32mAlready compiled: $$file\033[0m\n"; \
					missing_found=1; \
				fi; \
			done; \
		fi; \
	done; \
	\
	if [ $$missing_found -eq 1 ]; then \
		find obj -type f -name "*.o" -print0 | xargs -0 ar rcs libftprintf_supp.a 2>/dev/null; \
		printf "\033[0;32mCreated supplemental archive with missing functions\033[0m\n"; \
	else \
		printf "\033[0;33mNo supplemental objects to archive\033[0m\n"; \
	fi

# Synchronize object files
sync_objects:
	@printf "\033[0;33mSynchronizing object files...\033[0m\n"
	@rm -rf $(OBJ_DIR)/printf
	
	@if [ -d "$(ROOT_OBJ_DIR)" ]; then \
		mkdir -p $(OBJ_DIR)/printf; \
		find $(ROOT_OBJ_DIR) -type f -name "*.o" ! -path "*/libft/*" | sort | while read src; do \
			filename=$$(basename $$src); \
			rel_path=$$(echo $$src | sed 's|$(ROOT_OBJ_DIR)/||'); \
			dst_dir=$(OBJ_DIR)/printf/$$(dirname $$rel_path); \
			mkdir -p $$dst_dir 2>/dev/null || true; \
			cp $$src $$dst_dir/ 2>/dev/null || true; \
		done; \
		printf "\033[0;32mObject files synchronized\033[0m\n"; \
	else \
		printf "\033[0;33mRoot Object directory not found. Creating objects locally.\033[0m\n"; \
		for src in $(PRINTF_SRCS); do \
			rel_path=$$(echo $$src | sed 's|$(PRINTF_DIR)/||'); \
			obj_path=$(OBJ_DIR)/printf/$$(dirname $$rel_path); \
			mkdir -p $$obj_path; \
		done; \
	fi

# Build libft dependency
$(LIBFT): ensure_libft_dir
	@printf "\033[44m\033[1;37m LIBFT \033[0m \033[1;33mImporting dependency...\033[0m\n"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@printf "\033[1;33mLibrary status: \033[0;32mLINKED\033[0m\n"

# Ensure libft directory exists
ensure_libft_dir:
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		printf "\033[0;33mLibft directory not found at $(LIBFT_DIR)\033[0m\n"; \
		mkdir -p $(LIBFT_DIR); \
		touch $(LIBFT); \
		printf "\033[0;32mCreated empty libft.a stub\033[0m\n"; \
	fi

.PHONY: build_root_project build_printf check_missing_functions sync_objects ensure_libft_dir
