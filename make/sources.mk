# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 20:30:00 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/18 01:07:42 by dyl-syzygy       ###   ########.fr        #
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

# Rule to build object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ >/dev/null 2>&1

# Rule to build the tester library - Fixed alignment
$(NAME): $(OBJS)
	@$(call section_header, "ASSEMBLING CORE LIBRARY")
	@printf "${ACCENT2}⚡${RST} ${BOLD}Creating ${MAIN_COLOR}$(NAME)${RST}...${RST}"
	@ar rcs $(NAME) $(OBJS) >/dev/null 2>&1
	@printf "\r${SUCCESS}✓${RST} ${BOLD}Library successfully created!${RST}        \n\n"

# Rule to create directories
prepare_dirs:
	@mkdir -p $(BIN_DIR) $(TESTS_DIR) $(PROGRAM_DIR)/utils/stress >/dev/null 2>&1

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
