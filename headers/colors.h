#ifndef FT_COLORS_H
#define FT_COLORS_H

// Text colors
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define ORANGE      "\033[38;5;208m"

// Bright text colors
#define BR_CYAN     "\033[96m"
#define BR_BLUE     "\033[94m"
#define BR_MAGENTA  "\033[95m"
#define BR_GREEN    "\033[92m"

// Background colors
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"
#define BG_ORANGE   "\033[48;5;208m"

// Text styles
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"

// Screen control
#define CLEAR_SCREEN "\033[2J\033[H"

#endif // FT_COLORS_H
