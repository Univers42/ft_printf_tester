# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃              Utility Functions                    ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Function to display section separator with enhanced visual style
define show_separator
	@printf "${BG_BLU}${BWHT}${BOLD}════════════════════════════════════════════════════════════════════${RST}\n"
endef

# Function to display section header with enhanced visual style
define show_section
	@printf "\n"
	$(call show_separator)
	@printf "${BG_BLU}${BWHT}${BOLD}   $(1)   ${RST}\n"
	$(call show_separator)
	@printf "\n"
endef

# Function to check if a command exists with visual feedback
define check_command
	@which $(1) > /dev/null 2>&1 || { \
		printf "${ERROR}✗${RST} ${ERROR_COLOR}$(1) not found. Please install $(1).${RST}\n"; \
		exit 1; \
	}
	@printf "${SUCCESS}✓${RST} ${BOLD}$(1)${RST} ${SUBTLE}is available${RST}\n"
endef

# Check build prerequisites with visual feedback
check_prerequisites:
	@$(call section_header, "SYSTEM PREREQUISITES CHECK")
	$(call check_command,gcc)
	$(call check_command,ar)
	$(call check_command,make)
	@printf "\n${BGRN}✓${RST} ${BOLD}All prerequisites satisfied${RST}\n\n"

# Get git commit hash if available
GIT_HASH := $(shell git rev-parse --short HEAD 2>/dev/null || echo "unknown")

# Get current date
DATE := $(shell date "+%Y-%m-%d %H:%M:%S")

# Show version info with enhanced styling
version:
	@$(call section_header, "TESTER VERSION INFORMATION")
	@printf "${BBG_BLU}${BWHT}${BOLD}  FT_PRINTF TESTER  ${RST}\n\n"
	@printf "${BOLD}${BCYN}Version:${RST} ${BWHT}1.0.0${RST}\n"
	@printf "${BOLD}${BCYN}Build:${RST} ${BWHT}$(GIT_HASH)${RST}\n"
	@printf "${BOLD}${BCYN}Date:${RST} ${BWHT}$(DATE)${RST}\n\n"

# Welcome screen animation with 3D effect
define welcome_screen
	@clear
	@printf "${BLINK}${BRIGHT_FG}${BOLD}Initializing...${RST}\n"
	@sleep 0.3
	@clear
	@printf "\n\n\n\n\n"
	@printf "${MAIN_COLOR}          ┏━━━━━━━━━━━━━━━━━━━━━━┓${RST}\n"
	@printf "${MAIN_COLOR}          ┃${RST} ${BRIGHT_FG}Welcome to FT_PRINTF${RST} ${MAIN_COLOR}┃${RST}\n"
	@printf "${MAIN_COLOR}          ┃${RST} ${BRIGHT_FG}  Ultimate Tester    ${RST} ${MAIN_COLOR}┃${RST}\n"
	@printf "${MAIN_COLOR}          ┗━━━━━━━━━━━━━━━━━━━━━━┛${RST}\n\n"
	@sleep 0.5
	
	@clear
	@$(call 3d_banner)
	@printf "\n\n${BOLD}${GRADIENT2}                Initializing FT_PRINTF Tester...${RST}\n\n"
	@printf "${GRADIENT1}["
	@for i in `seq 1 40`; do \
		if [ "$$i" -le "13" ]; then \
			printf "${GRADIENT2}◆${RST}"; \
		elif [ "$$i" -le "26" ]; then \
			printf "${GRADIENT3}◆${RST}"; \
		else \
			printf "${GRADIENT4}◆${RST}"; \
		fi; \
		sleep 0.015; \
	done
	@printf "${GRADIENT1}]${RST}\n\n"
	@sleep 0.2
endef

# Fancy confirmation dialog
define confirm_action
	@printf "\n${BG_YLW}${BBLK} CONFIRM ${RST} ${BOLD}$(1)${RST}\n"
	@printf "${SUBTLE}┌────────────────────────────────────┐${RST}\n"
	@printf "${SUBTLE}│${RST} ${DIM}Press [y] to confirm or any key to abort${RST} ${SUBTLE}│${RST}\n"
	@printf "${SUBTLE}└────────────────────────────────────┘${RST}\n"
	@printf "${ACCENT2}▶${RST} "
	@read -n 1 -r answer; \
	if [ "$$answer" != "y" ] && [ "$$answer" != "Y" ]; then \
		printf "\n\n${BG_ERROR}${BRIGHT_FG} ABORTED ${RST} ${BOLD}Operation canceled.${RST}\n\n"; \
		exit 1; \
	fi; \
	printf "\n\n${BG_SUCCESS}${BRIGHT_FG} CONFIRMED ${RST} ${BOLD}Proceeding...${RST}\n\n"
endef

# Spinner animation for long operations
define show_spinner
	@printf "${BOLD}${1}${RST} "
	@for frame in $(SPINNER_FRAMES); do \
		printf "\r${BOLD}${1}${RST} ${BLINK}$$frame${RST}"; \
		sleep 0.1; \
	done
	@printf "\r${BOLD}${1}${RST} ${CHECK}\n"
endef

# Enhanced rainbow text effect with motion - fixed for sh compatibility
define rainbow_text
	@text="$(1)"; \
	colors="$(RAINBOW_COLORS)"; \
	for shift in 0 1 2 3 4 5 6 7 8 9 10; do \
		printf "\r"; \
		idx=$$shift; \
		for i in $$(seq 0 $$(($${#text}-1))); do \
			c=$${text:$$i:1}; \
			color=$$(echo "$$colors" | cut -d' ' -f$$((((idx+i) % 30) + 1))); \
			printf "$$color$$c${RST}"; \
		done; \
		sleep 0.1; \
	done; \
	printf "\n"
endef

# Matrix-style raining code effect
define matrix_effect
	@clear
	@text="$(1)"; \
	columns=$$(tput cols); \
	rows=$$(tput lines); \
	for j in `seq 1 $$((rows/2))`; do \
		clear; \
		for i in `seq 1 $$j`; do \
			position=$$((RANDOM % columns)); \
			spaces=""; \
			for s in `seq 1 $$position`; do \
				spaces="$$spaces "; \
			done; \
			printf "$$spaces${BGRN}$${text:$$((RANDOM % $${#text})):1}${RST}\n"; \
		done; \
		sleep 0.05; \
	done
	@clear
endef

# 3D depth illusion text effect
define depth_text
	@text="$(1)"; \
	for i in `seq 10 -1 1`; do \
		offset=""; \
		for j in `seq 1 $$i`; do \
			offset="$$offset "; \
		done; \
		printf "\r$$offset${BOLD}$$text${RST}"; \
		sleep 0.05; \
	done; \
	printf "\n"
endef

# Expanding rings animation
define expanding_rings
	@center_text="$(1)"; \
	pad_length=$$(( ($${#center_text} + 4) / 2 )); \
	padding=""; \
	for i in `seq 1 $$pad_length`; do \
		padding="$$padding "; \
	done; \
	clear; \
	for size in {1..5}; do \
		clear; \
		printf "\n\n\n"; \
		case $$size in \
			1) \
				printf "       ${ACCENT1}●${RST}\n"; \
				printf "    ${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}\n"; \
				printf "       ${ACCENT1}●${RST}\n\n"; \
				;; \
			2) \
				printf "     ${ACCENT1}●●●${RST}\n"; \
				printf "   ${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}\n"; \
				printf "   ${ACCENT1}●${RST}${BRIGHT_FG}$${center_text}${RST}${ACCENT1}●${RST}\n"; \
				printf "   ${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}\n"; \
				printf "     ${ACCENT1}●●●${RST}\n\n"; \
				;; \
			3) \
				printf "    ${ACCENT2}●●●●●${RST}\n"; \
				printf "  ${ACCENT2}●${RST}${ACCENT1}●●●${RST}${ACCENT2}●${RST}\n"; \
				printf "  ${ACCENT2}●${RST}${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}\n"; \
				printf "  ${ACCENT2}●${RST}${ACCENT1}●${RST}${BRIGHT_FG}$${center_text}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}\n"; \
				printf "  ${ACCENT2}●${RST}${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}\n"; \
				printf "  ${ACCENT2}●${RST}${ACCENT1}●●●${RST}${ACCENT2}●${RST}\n"; \
				printf "    ${ACCENT2}●●●●●${RST}\n\n"; \
				;; \
			4) \
				printf "   ${SUBTLE}●●●●●●●${RST}\n"; \
				printf " ${SUBTLE}●${RST}${ACCENT2}●●●●●${RST}${SUBTLE}●${RST}\n"; \
				printf " ${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●●●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}\n"; \
				printf " ${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}\n"; \
				printf " ${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●${RST}${BRIGHT_FG}$${center_text}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}\n"; \
				printf " ${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}\n"; \
				printf " ${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●●●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}\n"; \
				printf " ${SUBTLE}●${RST}${ACCENT2}●●●●●${RST}${SUBTLE}●${RST}\n"; \
				printf "   ${SUBTLE}●●●●●●●${RST}\n\n"; \
				;; \
			5) \
				printf "  ${DIM}●●●●●●●●●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●●●●●●●${RST}${DIM}●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●${RST}${ACCENT2}●●●●●${RST}${SUBTLE}●${RST}${DIM}●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●●●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}${DIM}●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}${DIM}●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●${RST}${BRIGHT_FG}$${center_text}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}${DIM}●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●${RST}${MAIN_COLOR}$${padding}${RST}${ACCENT1}●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}${DIM}●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●${RST}${ACCENT2}●${RST}${ACCENT1}●●●${RST}${ACCENT2}●${RST}${SUBTLE}●${RST}${DIM}●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●${RST}${ACCENT2}●●●●●${RST}${SUBTLE}●${RST}${DIM}●${RST}\n"; \
				printf " ${DIM}●${RST}${SUBTLE}●●●●●●●${RST}${DIM}●${RST}\n"; \
				printf "  ${DIM}●●●●●●●●●${RST}\n\n"; \
				;; \
		esac; \
		sleep 0.2; \
	done
endef

# Spinning dots animation with color gradient
define spinning_dots
	@msg="$(1)"; \
	colors=("${MAIN_COLOR}" "${ACCENT1}" "${ACCENT2}"); \
	frames=("⣾" "⣽" "⣻" "⢿" "⡿" "⣟" "⣯" "⣷"); \
	for i in {1..30}; do \
		color=$${colors[$$((i % 3))]}; \
		frame=$${frames[$$((i % 8))]}; \
		printf "\r${BOLD}%s${RST} $$color$$frame${RST}"; \
		sleep 0.08; \
	done; \
	printf "\r${BOLD}%s${RST} ${SUCCESS}✓${RST}\n" "$$msg"
endef

# 3D typewriter effect with depth
define typewriter_3d
	@text="$(1)"; \
	for i in `seq 0 $${#text}`; do \
		part=$${text:0:$$i}; \
		remainder=$${text:$$i}; \
		printf "\r${ACCENT1}${DIM}$$part${RST}${SUBTLE}$$remainder${RST}"; \
		sleep 0.05; \
	done
	@printf "\n"
endef

# 3D fireworks effect
define fireworks_effect
	@clear
	@for f in {1..3}; do \
		for r in {1..5}; do \
			clear; \
			case $$r in \
				1) \
					printf "\n\n\n\n\n\n\n"; \
					printf "                       ${MAIN_COLOR}*${RST}\n"; \
					;; \
				2) \
					printf "\n\n\n\n\n\n"; \
					printf "                      ${ACCENT2}\\|/${RST}\n"; \
					printf "                       ${MAIN_COLOR}|${RST}\n"; \
					;; \
				3) \
					printf "\n\n\n\n\n"; \
					printf "                     ${ACCENT1}\\\\|//${RST}\n"; \
					printf "                     ${ACCENT2}-${MAIN_COLOR}*${ACCENT2}-${RST}\n"; \
					printf "                     ${ACCENT1}//|\\\\${RST}\n"; \
					;; \
				4) \
					printf "\n\n\n\n"; \
					printf "                    ${ACCENT1}\\\\\\|///${RST}\n"; \
					printf "                    ${ACCENT2}--${MAIN_COLOR}*${ACCENT2}--${RST}\n"; \
					printf "                    ${ACCENT1}///|\\\\\\${RST}\n"; \
					printf "                     ${SUBTLE}\\|/${RST}\n"; \
					;; \
				5) \
					printf "\n\n\n"; \
					printf "                 ${DIM}*${RST}  ${ACCENT1}\\\\\\\\|////${RST}  ${DIM}*${RST}\n"; \
					printf "                ${DIM}*${RST} ${ACCENT2}*${RST} ${ACCENT2}---${MAIN_COLOR}*${ACCENT2}---${RST} ${ACCENT2}*${RST} ${DIM}*${RST}\n"; \
					printf "                   ${ACCENT1}////|\\\\\\\\${RST}\n"; \
					printf "                  ${SUBTLE}\\\\\\|///${RST}\n"; \
					printf "                    ${SUBTLE}\\|/${RST}\n"; \
					;; \
			esac; \
			sleep 0.1; \
		done; \
		printf "\n\n     ${BRIGHT_FG}${BOLD}$(2)${RST}\n\n"; \
		sleep 0.5; \
	done
endef

# 3D rotation animation - fixed for sh compatibility
define rotate_animation
	@printf "\n"
	@for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do \
		angle=$$((i * 18 % 360)); \
		case $$((angle / 45)) in \
			0) printf "\r${MAIN_COLOR}➤       ${RST} $(1)"; ;; \
			1) printf "\r${ACCENT1} ➤      ${RST} $(1)"; ;; \
			2) printf "\r${ACCENT2}  ➤     ${RST} $(1)"; ;; \
			3) printf "\r${ACCENT2}   ➤    ${RST} $(1)"; ;; \
			4) printf "\r${ACCENT1}    ➤   ${RST} $(1)"; ;; \
			5) printf "\r${MAIN_COLOR}     ➤  ${RST} $(1)"; ;; \
			6) printf "\r${MAIN_COLOR}      ➤ ${RST} $(1)"; ;; \
			7) printf "\r${MAIN_COLOR}       ➤${RST} $(1)"; ;; \
		esac; \
		sleep 0.1; \
	done
	@printf "\r${SUCCESS}✓${RST} ${BOLD}%s${RST}\n" "$(1)"
endef

# Enhanced sparkle animation with more vibrant effects
define sparkle_animation
	@msg="$(1)"; \
	sparkles="✨ ⭐ 🌟 ✨ ⭐ 🌟"; \
	for i in 1 2 3; do \
		for s in $$sparkles; do \
			printf "\r${GRADIENT2}${BOLD}%s${RST} %s " "$$msg" "$$s"; \
			sleep 0.15; \
		done; \
	done; \
	printf "\r${GRADIENT3}${BOLD}%s${RST} ${SUCCESS}✓${RST}  ${ACCENT_GOLD}✨${RST}\n" "$$msg"
endef

# Extremely simple but colorful cleaning animation without any complex shell operations
define cleaning_animation
	@printf "\n  ${GRADIENT2}★ ${BOLD}${BRIGHT_FG}$(1)${RST}\n\n"
endef

# Additional PHONY targets
.PHONY: version check_prerequisites
