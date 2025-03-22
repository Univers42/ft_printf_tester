#ifndef FT_CONTROLLER_H
#define FT_CONTROLLER_H
# include <time.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include "colors.h"
# include "structs.h" /* Include structs.h first */
# include "ft_printf_test_utils.h"
# include "ft_printf_test_macros.h"
# include "ft_printf_debug.h"
# include <pthread.h>  
# include <signal.h>
#include <inttypes.h>
# include "../includes/ft_printf_stress.h"
#include <stddef.h>
#include "../../include/ft_printf.h"
/* Function declarations for mixed format tests */
void run_robust_mixed_format_tests(void);
int call_ft_printf_with_types(const char *format, va_list args, char *types, int type_count);

/* Function declaration for the internal helper */
int parse_format_string(const char *format, char *types, int max_types);

/* Test implementations of converter functions */
int	ft_convert_percent(char type, t_flags flags, va_list args);
int	ft_convert_char(char type, t_flags flags, va_list args);
int	ft_convert_str(char type, t_flags flags, va_list args);
int	ft_convert_int(char type, t_flags flags, va_list args);
int	ft_convert_unsigned(char type, t_flags flags, va_list args);
int	ft_convert_hex_lower(char type, t_flags flags, va_list args);
int	ft_convert_hex_upper(char type, t_flags flags, va_list args);
int	ft_convert_ptr(char type, t_flags flags, va_list args);

/* Test implementations of flag handler functions */
void	handle_minus(t_flags *flags, va_list args);
void	handle_zero(t_flags *flags, va_list args);
void	handle_dot(t_flags *flags, va_list args);
void	handle_hash(t_flags *flags, va_list args);
void	handle_space(t_flags *flags, va_list args);
void	handle_plus(t_flags *flags, va_list args);
void	handle_star(t_flags *flags, va_list args);

#endif