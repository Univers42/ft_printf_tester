# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colors.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 13:52:58 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/06 13:53:55 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
GRAY = \033[0;90m

# Bold Colors
BOLD_BLACK = \033[1;30m
BOLD_RED = \033[1;31m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
BOLD_BLUE = \033[1;34m
BOLD_PURPLE = \033[1;35m
BOLD_CYAN = \033[1;36m
BOLD_WHITE = \033[1;37m
BOLD_GRAY = \033[1;90m

# Special Colors 
PINK = \033[38;5;206m
ORANGE = \033[38;5;208m
LIME = \033[38;5;118m
SKY = \033[38;5;39m
GOLD = \033[38;5;220m
TEAL = \033[38;5;6m
LAVENDER = \033[38;5;147m
PEACH = \033[38;5;215m
MINT = \033[38;5;84m
SALMON = \033[38;5;209m
INDIGO = \033[38;5;62m
TURQUOISE = \033[38;5;80m
MAGENTA = \033[38;5;201m
OLIVE = \033[38;5;142m

# Background Colors
BG_BLACK = \033[40m
BG_RED = \033[41m
BG_GREEN = \033[42m
BG_YELLOW = \033[43m
BG_BLUE = \033[44m
BG_PURPLE = \033[45m
BG_CYAN = \033[46m
BG_WHITE = \033[47m
BG_GRAY = \033[100m

# Special Background Colors
BG_PINK = \033[48;5;206m
BG_ORANGE = \033[48;5;208m
BG_LIME = \033[48;5;118m
BG_SKY = \033[48;5;39m
BG_GOLD = \033[48;5;220m
BG_DARK_BLUE = \033[48;5;18m
BG_DARK_GREEN = \033[48;5;22m
BG_DARK_RED = \033[48;5;52m
BG_DARK_PURPLE = \033[48;5;54m

# Text Styles
BOLD = \033[1m
FAINT = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
HIDDEN = \033[8m
STRIKE = \033[9m

# Reset
RESET = \033[0m

# Special Characters and Glyphs
CHECK = ✓
CROSS = ✗
STAR = ★
SPARKLE = ✨
ARROW_RIGHT = →
ARROW_LEFT = ←
ARROW_UP = ↑
ARROW_DOWN = ↓
LIGHTNING = ⚡
HAMMER = 🔨
GEAR = ⚙
WARN = ⚠
INFO = ℹ
OK = ✓
FIRE = 🔥
ROCKET = 🚀
LIGHT = 💡
CLOCK = 🕒
DIAMOND = ♦
HEART = ♥
CLUB = ♣
SPADE = ♠
SMILE = 😊
THINK = 🤔
COOL = 😎

# ⚡ Master Versions ⚡
SUCCESS = $(BOLD_GREEN)$(CHECK) 
ERROR = $(BOLD_RED)$(CROSS) 
WARNING = $(BOLD_YELLOW)$(WARN) 
INFO_MARK = $(BOLD_BLUE)$(INFO) 
WORKING = $(BOLD_CYAN)$(GEAR) 
FLAME = $(BOLD_ORANGE)$(FIRE) 
BEAM = $(BOLD_CYAN)$(LIGHT) 
BLAST = $(BOLD_YELLOW)$(ROCKET) 
TIME = $(BOLD_PURPLE)$(CLOCK) 