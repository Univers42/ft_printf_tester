/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_ft_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:56:48 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/03 23:52:44 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_test_utils.h"

// External ft_printf function declaration
extern int ft_printf(const char *format, ...);

// Simple ft_printf wrapper that redirects output to a FILE stream
int simple_ft_printf(FILE *stream, const char *format, ...)
{
    // Save the original stdout
    int original_stdout = dup(fileno(stdout));
    
    // Redirect stdout to the given FILE stream
    dup2(fileno(stream), fileno(stdout));
    
    // Call ft_printf with the variadic arguments
    va_list args;
    va_start(args, format);
    
    int ret = 0;
    
    // We need a more robust approach to pass through the arguments
    // Let's handle the most common test cases by counting the format specifiers
    
    // Count format specifiers
    int fmt_count = 0;
    const char *p = format;
    while (*p) {
        if (*p == '%') {
            if (*(p+1) != '%') {
                fmt_count++;
            }
            p++;
        }
        p++;
    }
    
    // Based on the number of format specifiers, handle different cases
    if (fmt_count == 0) {
        // No format specifiers, just a plain string
        ret = ft_printf("%s", format);
    } else if (fmt_count == 1) {
        // One format specifier - handle each type
        if (strstr(format, "%c")) {
            int c_val = va_arg(args, int);
            ret = ft_printf(format, c_val);
        } else if (strstr(format, "%s")) {
            char *s_val = va_arg(args, char *);
            ret = ft_printf(format, s_val);
        } else if (strstr(format, "%p")) {
            void *p_val = va_arg(args, void *);
            ret = ft_printf(format, p_val);
        } else if (strstr(format, "%d") || strstr(format, "%i")) {
            int d_val = va_arg(args, int);
            ret = ft_printf(format, d_val);
        } else if (strstr(format, "%u")) {
            unsigned int u_val = va_arg(args, unsigned int);
            ret = ft_printf(format, u_val);
        } else if (strstr(format, "%x")) {
            unsigned int x_val = va_arg(args, unsigned int);
            ret = ft_printf(format, x_val);
        } else if (strstr(format, "%X")) {
            unsigned int X_val = va_arg(args, unsigned int);
            ret = ft_printf(format, X_val);
        } else if (strstr(format, "%%")) {
            ret = ft_printf("%%");
        }
    } else if (fmt_count == 2) {
        // Two format specifiers
        if (strstr(format, "%c") && strstr(format, "%s")) {
            int c_val = va_arg(args, int);
            char *s_val = va_arg(args, char *);
            ret = ft_printf(format, c_val, s_val);
        } else if (strstr(format, "%d") && strstr(format, "%i")) {
            int d_val = va_arg(args, int);
            int i_val = va_arg(args, int);
            ret = ft_printf(format, d_val, i_val);
        } else if (strstr(format, "%x") && strstr(format, "%X")) {
            unsigned int x_val = va_arg(args, unsigned int);
            unsigned int X_val = va_arg(args, unsigned int);
            ret = ft_printf(format, x_val, X_val);
        } else {
            // Generic handling for two arguments
            void *arg1 = va_arg(args, void *);
            void *arg2 = va_arg(args, void *);
            ret = ft_printf(format, arg1, arg2);
        }
    } else {
        // For three or more format specifiers, pass the first 10 args
        // This is a simplification but should work for most test cases
        void *arg1, *arg2, *arg3, *arg4, *arg5, *arg6, *arg7, *arg8, *arg9, *arg10;
        
        // Get as many args as needed (up to 10)
        if (fmt_count >= 1) arg1 = va_arg(args, void *);
        if (fmt_count >= 2) arg2 = va_arg(args, void *);
        if (fmt_count >= 3) arg3 = va_arg(args, void *);
        if (fmt_count >= 4) arg4 = va_arg(args, void *);
        if (fmt_count >= 5) arg5 = va_arg(args, void *);
        if (fmt_count >= 6) arg6 = va_arg(args, void *);
        if (fmt_count >= 7) arg7 = va_arg(args, void *);
        if (fmt_count >= 8) arg8 = va_arg(args, void *);
        if (fmt_count >= 9) arg9 = va_arg(args, void *);
        if (fmt_count >= 10) arg10 = va_arg(args, void *);
        
        // Call ft_printf with the appropriate number of args
        switch (fmt_count) {
            case 1: ret = ft_printf(format, arg1); break;
            case 2: ret = ft_printf(format, arg1, arg2); break;
            case 3: ret = ft_printf(format, arg1, arg2, arg3); break;
            case 4: ret = ft_printf(format, arg1, arg2, arg3, arg4); break;
            case 5: ret = ft_printf(format, arg1, arg2, arg3, arg4, arg5); break;
            case 6: ret = ft_printf(format, arg1, arg2, arg3, arg4, arg5, arg6); break;
            case 7: ret = ft_printf(format, arg1, arg2, arg3, arg4, arg5, arg6, arg7); break;
            case 8: ret = ft_printf(format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); break;
            case 9: ret = ft_printf(format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); break;
            default: ret = ft_printf(format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); break;
        }
    }
    
    va_end(args);
    
    // Restore the original stdout
    fflush(stdout);
    dup2(original_stdout, fileno(stdout));
    close(original_stdout);
    
    return ret;
}
