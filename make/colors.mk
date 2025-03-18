# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colors.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 20:30:00 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/18 01:51:25 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Terminal Color Codes                 ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Reset code
RST  := \033[0m

# Text styling
BOLD := \033[1m
DIM  := \033[2m
ITAL := \033[3m
UNDR := \033[4m
BLINK := \033[5m
RBLINK := \033[6m  # Rapid blinking
INV  := \033[7m    # Inverted
HIDE := \033[8m    # Hidden

# Basic colors (normal)
BLK := \033[30m
RED := \033[31m
GRN := \033[32m
YLW := \033[33m
BLU := \033[34m
PUR := \033[35m
CYN := \033[36m
WHT := \033[37m

# Basic colors (bright)
BBLK := \033[90m
BRED := \033[91m
BGRN := \033[92m
BYLW := \033[93m
BBLU := \033[94m
BPUR := \033[95m
BCYN := \033[96m
BWHT := \033[97m

# Background colors
BG_BLK := \033[40m
BG_RED := \033[41m
BG_GRN := \033[42m
BG_YLW := \033[43m
BG_BLU := \033[44m
BG_PUR := \033[45m
BG_CYN := \033[46m
BG_WHT := \033[47m

# Bright background colors
BBG_BLK := \033[100m
BBG_RED := \033[101m
BBG_GRN := \033[102m
BBG_YLW := \033[103m
BBG_BLU := \033[104m
BBG_PUR := \033[105m
BBG_CYN := \033[106m
BBG_WHT := \033[107m

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Visual Style Definition              ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Custom 256-color palette for a more cohesive look
MAIN_COLOR := \033[38;5;39m     # Bright blue - primary theme color
ACCENT1 := \033[38;5;135m       # Medium purple - accent color
ACCENT2 := \033[38;5;208m       # Orange - secondary accent
SUCCESS := \033[38;5;41m        # Vibrant green - success messages
WARN_COLOR := \033[38;5;220m    # Gold - warnings
ERROR_COLOR := \033[38;5;196m   # Bright red - errors
SUBTLE := \033[38;5;245m        # Medium gray - subtle elements
HIGHLIGHT := \033[38;5;226m     # Bright yellow - highlight elements
BRIGHT_FG := \033[38;5;255m     # Bright white - important text

# Background variants
BG_MAIN := \033[48;5;24m        # Darker blue bg
BG_ACCENT := \033[48;5;53m      # Darker purple bg
BG_SUCCESS := \033[48;5;28m     # Darker green bg
BG_WARN := \033[48;5;94m        # Darker gold bg
BG_ERROR := \033[48;5;88m       # Darker red bg

# Enhanced color palette for 3D effects
GRADIENT1 := \033[38;5;39m  # Bright blue
GRADIENT2 := \033[38;5;45m  # Cyan
GRADIENT3 := \033[38;5;51m  # Light cyan
GRADIENT4 := \033[38;5;87m  # Very light cyan
ACCENT_GOLD := \033[38;5;220m
ACCENT_PURPLE := \033[38;5;141m
NEON_GREEN := \033[38;5;118m
NEON_PINK := \033[38;5;198m

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Visual Elements                      ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Define the banner art for the tester
define print_banner
	@clear
	@printf "\n\n"
	@printf "${GRADIENT1}╔════════════════════════════════════════════════════════════════╗${RST}\n"
	@printf "${GRADIENT1}║${RST}${ACCENT_PURPLE}                                                              ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST} ${GRADIENT2}███████╗████████╗    ██████╗ ██████╗ ██╗███╗   ██╗████████╗${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST} ${GRADIENT2}██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██║████╗  ██║╚══██╔══╝${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST} ${GRADIENT3}█████╗     ██║       ██████╔╝██████╔╝██║██╔██╗ ██║   ██║   ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST} ${GRADIENT3}██╔══╝     ██║       ██╔═══╝ ██╔══██╗██║██║╚██╗██║   ██║   ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST} ${GRADIENT4}██║        ██║       ██║     ██║  ██║██║██║ ╚████║   ██║   ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST} ${GRADIENT4}╚═╝        ╚═╝       ╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST}${ACCENT_PURPLE}                                                              ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}╠════════════════════════════════════════════════════════════════╣${RST}\n"
	@printf "${GRADIENT1}║${RST}${ACCENT_PURPLE}                                                              ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST}  ${ACCENT_GOLD}████████╗███████╗███████╗████████╗███████╗██████╗           ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST}  ${ACCENT_GOLD}╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗          ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST}  ${NEON_PINK}   ██║   █████╗  ███████╗   ██║   █████╗  ██████╔╝          ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST}  ${NEON_PINK}   ██║   ██╔══╝  ╚════██║   ██║   ██╔══╝  ██╔══██╗          ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST}  ${NEON_GREEN}   ██║   ███████╗███████║   ██║   ███████╗██║  ██║          ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST}  ${NEON_GREEN}   ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝          ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}║${RST}${ACCENT_PURPLE}                                                              ${GRADIENT1}║${RST}\n"
	@printf "${GRADIENT1}╚════════════════════════════════════════════════════════════════╝${RST}\n"
	@printf "\n"
	@printf "${ACCENT2}┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓${RST}\n"
	@printf "${ACCENT2}┃${RST} ${BLINK}${HIGHLIGHT}✧${RST}${MAIN_COLOR}      THE ULTIMATE PRINTF TEST SUITE      ${HIGHLIGHT}✧${RST} ${ACCENT2}┃${RST}\n"
	@printf "${ACCENT2}┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛${RST}\n"
	@printf "\n\n"
endef

# Simple help menu with enhanced styling
define show_help
	@printf "\n${MAIN_COLOR}╔══════════════════════════════════╗${RST}\n"
	@printf "${MAIN_COLOR}║${RST}${BRIGHT_FG}${BOLD}      AVAILABLE COMMANDS      ${RST}${MAIN_COLOR}║${RST}\n"
	@printf "${MAIN_COLOR}╚══════════════════════════════════╝${RST}\n\n"
	@printf "${BG_MAIN}${BRIGHT_FG}  make       ${RST} ${SUBTLE}Build the entire test suite${RST}\n"
	@printf "${BG_MAIN}${BRIGHT_FG}  make run   ${RST} ${SUBTLE}Execute the ft_printf tester${RST}\n"
	@printf "${BG_ERROR}${BRIGHT_FG}  make clean  ${RST} ${SUBTLE}Clean object files${RST}\n"
	@printf "${BG_ERROR}${BRIGHT_FG}  make fclean ${RST} ${SUBTLE}Full cleanup of all generated files${RST}\n"
	@printf "${BG_WARN}${BRIGHT_FG}  make re     ${RST} ${SUBTLE}Rebuild everything from scratch${RST}\n"
	@printf "${BG_ACCENT}${BRIGHT_FG}  make help   ${RST} ${SUBTLE}Display this help message${RST}\n\n"
	@printf "${BG_MAIN}${BRIGHT_FG}  make visuals ${RST} ${SUBTLE}Display 3D animation showcase${RST}\n\n"
endef

# Define an animated spinner sequence
SPINNER_FRAMES := ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏

# Status message with animation effect
define pulse_status
	@printf "${SUCCESS}✓${RST} ${MAIN_COLOR}${BOLD}$(1)${RST} ${ACCENT2}$(2)${RST}\n"
endef

# Enhanced section header with 3D effect - Fixed alignment with reduced right padding
define section_header
	@printf "${GRADIENT1}╭────────────────────────────────────────────────────────────────╮${RST}\n"
	@printf "${GRADIENT1}│${RST} ${ACCENT_GOLD}✧${RST} %-54s   ${ACCENT_GOLD}✧${RST} ${GRADIENT1}│${RST}\n" "$(1)"
	@printf "${GRADIENT1}╰────────────────────────────────────────────────────────────────╯${RST}\n\n"
endef

# Smaller section divider
define section_divider
	@printf "\n${MAIN_COLOR}────────────────────────────────────────────────────────────────${RST}\n\n"
endef

# Icon set for visual cues - modern and minimal
BUILD_ICON := ${ACCENT2}⚡${RST}
LINK_ICON := ${MAIN_COLOR}→${RST}
CHECK := ${SUCCESS}✓${RST}
WARN := ${WARN_COLOR}⚠${RST}
ERROR := ${ERROR_COLOR}✗${RST}
INFO := ${MAIN_COLOR}ℹ${RST}

# 3D-styled progress bar with shadow effect
define shadow_progress_bar
	@total=$(2); \
	current=$(1); \
	percent=$$(( current * 100 / total )); \
	bar_length=30; \
	filled=$$(( current * bar_length / total )); \
	printf "\n  ${SUBTLE}"; \
	for i in $$(seq 1 $$bar_length); do \
		if [ $$i -le $$filled ]; then \
			printf "▰"; \
		else \
			printf "▱"; \
		fi; \
	done; \
	printf "${RST}\n"; \
	printf "  ${BRIGHT_FG}"; \
	for i in $$(seq 1 $$bar_length); do \
		if [ $$i -le $$filled ]; then \
			if [ $$i -le 10 ]; then \
				printf "${ACCENT2}▰${RST}"; \
			elif [ $$i -le 20]; then \
				printf "${MAIN_COLOR}▰${RST}"; \
			else \
				printf "${ACCENT1}▰${RST}"; \
			fi; \
		else \
			printf "${DIM}▱${RST}"; \
		fi; \
	done; \
	printf " ${BOLD}%3d%%${RST}\n\n" $$percent
endef

# Artistic version display
define artistic_version
	@printf "\n"
	@printf "${BG_MAIN}${BRIGHT_FG}${BOLD}  FT_PRINTF TESTER VERSION INFO  ${RST}\n\n"
	@printf "${BOLD}Version:${RST} ${MAIN_COLOR}1.0.0${RST}\n"
	@printf "${BOLD}Build:${RST} ${ACCENT1}$(GIT_HASH)${RST}\n"
	@printf "${BOLD}Date:${RST} ${ACCENT2}$(DATE)${RST}\n\n"
endef

# Test completion message with 3D effect
define test_complete
	@clear
	@for i in {1..3}; do \
		printf "\n${BG_SUCCESS}${BRIGHT_FG}                                                 ${RST}\n"; \
		printf "${BG_SUCCESS}${BRIGHT_FG}  ✨  TESTING COMPLETED SUCCESSFULLY  ✨  ${RST}\n"; \
		printf "${BG_SUCCESS}${BRIGHT_FG}                                                 ${RST}\n\n"; \
		sleep 0.3; \
		clear; \
		sleep 0.2; \
	done
	@printf "\n${BG_SUCCESS}${BRIGHT_FG}                                                 ${RST}\n"
	@printf "${BG_SUCCESS}${BRIGHT_FG}  ✨  TESTING COMPLETED SUCCESSFULLY  ✨  ${RST}\n"
	@printf "${BG_SUCCESS}${BRIGHT_FG}                                                 ${RST}\n\n"
endef

# Sparkly success animation
define sparkle_animation
	@msg="$(1)"; \
	sparkles="✨ ⭐ 🌟 ✨ ⭐ 🌟"; \
	for i in {1..3}; do \
		for s in $$sparkles; do \
			printf "\r${BRIGHT_FG}${BOLD}%s${RST} %s " "$$msg" "$$s"; \
			sleep 0.15; \
		done; \
	done; \
	printf "\r${BRIGHT_FG}${BOLD}%s${RST} ${SUCCESS}✓${RST}\n" "$$msg"
endef
