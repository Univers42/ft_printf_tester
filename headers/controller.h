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

/* Function declaration for the internal helper */
int call_ft_printf_with_types(const char *format, va_list args, char *types, int type_count);

#endif