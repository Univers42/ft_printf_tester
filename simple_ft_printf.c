#include <stdarg.h>
#include "../ft_printf.h"

/*
 * This is a simple wrapper for ft_printf used in testing
 * It exists because some tests use simple_ft_printf instead of ft_printf directly
 */
int simple_ft_printf(const char *format, ...)
{
    va_list args;
    int     ret;
    
    va_start(args, format);
    ret = ft_printf(format, args);
    va_end(args);
    
    return (ret);
}
