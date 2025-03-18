# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 10:00:00 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/17 21:00:00 by dyl-syzygy       #+#    #+#              #
#                                                                              #
# **************************************************************************** #

# ╔════════════════════════════════════════════════════════════════════════════╗
# ║                                                                            ║
# ║  ███████╗████████╗    ██████╗ ██████╗ ██╗███╗   ██╗████████╗███████╗       ║
# ║  ██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██║████╗  ██║╚══██╔══╝██╔════╝       ║
# ║  █████╗     ██║       ██████╔╝██████╔╝██║██╔██╗ ██║   ██║   █████╗         ║
# ║  ██╔══╝     ██║       ██╔═══╝ ██╔══██╗██║██║╚██╗██║   ██║   ██╔══╝         ║
# ║  ██║        ██║       ██║     ██║  ██║██║██║ ╚████║   ██║   ██║            ║
# ║  ╚═╝        ╚═╝       ╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝            ║
# ║                                                                            ║
# ║                      ✧ ULTIMATE TESTER ✧                                  ║
# ║                                                                            ║
# ╚════════════════════════════════════════════════════════════════════════════╝

# Include all makefiles - ordered to avoid conflicts
include make/colors.mk
include make/config.mk
include make/sources.mk
include make/utils.mk
# Include main.mk last since we want to override its targets
include make/targets.mk

.PHONY: all clean fclean re run programs controller help visuals gui-3d build-monitor install-3d-deps visual-showcase progress-demo text-demo animation-demo error-demo interactive-help
.DEFAULT_GOAL := all

# Define core targets here instead of including from main.mk to avoid conflicts
all: init $(NAME) programs controller
	@printf "\n  ${GRADIENT1}┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓${RST}\n"
	@printf "  ${GRADIENT1}┃${RST}    ${GRADIENT3}✨${RST}  ${BRIGHT_FG}${BOLD}FT_PRINTF ULTIMATE TESTER READY${RST}    ${GRADIENT3}✨${RST}     ${GRADIENT1}┃${RST}\n"
	@printf "  ${GRADIENT1}┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛${RST}\n"
	@printf "\n${NEON_GREEN}✓${RST} ${BOLD}Build complete${RST} ${ACCENT_GOLD}✨${RST}\n"
	@printf "${ACCENT_PURPLE}→${RST} ${BOLD}Run${RST} ${GRADIENT2}./tester${RST} ${BOLD}to launch tests${RST}\n\n"

# Initialize with banner display
init:
	@$(call print_banner)
	@sleep 0.3

programs: prepare_dirs $(NAME)
	@$(MAKE) -s make_libft
	@$(MAKE) -s make_libprintf
	@printf "\n${BCYN}▶ Building Test Suite${RST}\n\n"
	@$(call build_tests)

controller: make_libft make_libprintf $(NAME) prepare_dirs
	@printf "${MAG}⚡${RST} ${DIM}Creating controller module...${RST}\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(CONTROLLER) $(SRCS_DIR)/ft_printf_ultimate_controller.c $(NAME) $(LIBPRINTF) $(LIBFT) >/dev/null
	@ln -sf $(BIN_DIR)/$(CONTROLLER) ./tester
	@printf "${GRN}✓${RST} ${BOLD}Controller ready${RST}\n\n"

run: controller programs
	@printf "${BLU}┌─────────${GRN}🧪${RST} ${BOLD}LAUNCHING TEST SUITE${RST} ${GRN}🧪${BLU}─────────┐${RST}\n"
	@printf "${BLU}│${RST}  ${DIM}Beginning comprehensive ft_printf testing...${RST}\n"
	@printf "${BLU}└────────────────────────────────────────────────┘${RST}\n\n"
	@./tester

clean:
	@$(call cleaning_animation, "Cleaning Project")
	@printf "  \n${GRADIENT1}  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓${RST}\n"
	@printf "  ${GRADIENT1}┃${RST} ${ACCENT_GOLD}✧${RST} ${GRADIENT3}Removing object files...${RST}                    ${GRADIENT1}┃${RST}\n"
	@printf "  ${GRADIENT1}┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛${RST}"
	@$(MAKE) -C $(LIBFT_PATH) clean >/dev/null
	@$(MAKE) -C $(LIBPRINTF_PATH) clean >/dev/null
	@rm -rf $(OBJ_DIR)
	@printf "\n  ${NEON_GREEN}✓${RST} ${GRADIENT2}${BOLD}Objects successfully removed${RST} ${ACCENT_GOLD}✨${RST}\n\n"

fclean:
	@$(call cleaning_animation, "Deep Cleaning")
	@printf "  \n  ${GRADIENT1}┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓${RST}\n"
	@printf "  ${GRADIENT1}┃${RST} ${ACCENT_GOLD}✧${RST} ${GRADIENT3}Removing binaries and libraries...${RST}          ${GRADIENT1}┃${RST}\n"
	@printf "  ${GRADIENT1}┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛${RST}\n"
	@$(MAKE) -C $(LIBFT_PATH) clean >/dev/null
	@$(MAKE) -C $(LIBPRINTF_PATH) fclean >/dev/null
	@rm -f $(NAME)
	@rm -f tester
	@rm -rf $(PROGRAM_DIR)
	@printf "  ${NEON_GREEN}✓${RST} ${GRADIENT2}${BOLD}Project reset complete${RST} ${ACCENT_GOLD}✨${RST}\n\n"

re: fclean all

help:
	@$(call show_enhanced_help)

interactive-help:
	@$(call interactive_help)

# Visual effect targets remain as defined in make/visual_showcase.mk
