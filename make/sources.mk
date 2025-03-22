# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 20:30:00 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/22 20:18:03 by syzygy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Source Management                    ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Find all .c files recursively in the utils directory 
# (excluding program dir)
SRCS := $(shell find $(UTILS_DIR) -name "*.c" -type f) \
        $(shell find $(SRCS_DIR) -name "*.c" -type f -not -path "*/$(PROGRAM_DIR)/*")

# Generate object file list from source files
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Build Rules                          ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Rule to build object files - Modified to show errors
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to build the tester library - Fixed alignment
$(NAME): $(OBJS)
	@$(call section_header, "ASSEMBLING CORE LIBRARY")
	@printf "${ACCENT2}⚡${RST} ${BOLD}Creating ${MAIN_COLOR}$(NAME)${RST}...${RST}"
	@ar rcs $(NAME) $(OBJS) >/dev/null 2>&1
	@printf "\r${SUCCESS}✓${RST} ${BOLD}Library successfully created!${RST}        \n\n"

# Rule to create directories - Made more robust and verbose
prepare_dirs:
	@mkdir -p $(BIN_DIR) $(TESTS_DIR) $(PROGRAM_DIR)/utils/stress
	@printf "${DIM}Created directory structure:${RST}\n"
	@printf "  ${DIM}$(BIN_DIR)${RST}\n"
	@printf "  ${DIM}$(TESTS_DIR)${RST}\n"
	@printf "  ${DIM}$(PROGRAM_DIR)/utils/stress${RST}\n"
	@chmod -R 755 $(BIN_DIR) $(TESTS_DIR) $(PROGRAM_DIR) 2>/dev/null || true

# Rule to build libft - Fixed alignment
make_libft:
	@$(call section_header, "BUILDING FOUNDATION LIBRARY")
	@printf "${ACCENT2}⚡${RST} ${BOLD}Compiling libft components...${RST}"
	@$(MAKE) -C $(LIBFT_PATH) >/dev/null 2>&1
	@printf "\r${SUCCESS}✓${RST} ${BOLD}Foundation library ready!${RST}        \n\n"

# Rule to build the printf library - Fixed alignment
make_libprintf:
	@$(call section_header, "BUILDING PRINTF LIBRARY")
	@printf "${ACCENT2}⚡${RST} ${BOLD}Compiling printf components...${RST}"
	@$(MAKE) -C $(LIBPRINTF_PATH) >/dev/null 2>&1
	@printf "\r${SUCCESS}✓${RST} ${BOLD}Printf library ready!${RST}        \n\n"

# Count the number of source files for progress display
TOTAL_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

# Display compilation progress for a single file with enhanced visuals
define compile_file
	@$(eval COMPILED_SRCS := $(shell echo $$(($(COMPILED_SRCS) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(COMPILED_SRCS) * 100 / $(TOTAL_SRCS)))))
	@$(eval FILE_NAME := $(notdir $(1)))
	@printf "${BOLD}${BCYN}[${RST} ${BLINK}${BYLW}⚙${RST} ${BOLD}${BCYN}]${RST} ${DIM}Compiling${RST} ${BOLD}${FILE_NAME}${RST} (${BGRN}$(PERCENT)%%${RST})\r"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $(1) -o $(OBJ_DIR)/$(1:.c=.o) >/dev/null 2>&1
endef
