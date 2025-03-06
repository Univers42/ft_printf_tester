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
#include <stddef.h>
/* Function declarations for mixed format tests */
void run_robust_mixed_format_tests(void);
int call_ft_printf_with_types(const char *format, va_list args, char *types, int type_count);

/* Function declaration for the internal helper */
int parse_format_string(const char *format, char *types, int max_types);

#endif