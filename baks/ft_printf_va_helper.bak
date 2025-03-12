/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_va_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 21:02:13 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/controller.h"

/* Helper function to get format specifier types */
void get_format_specifiers(const char *format, char *types, int max_types)
{
    int count = 0;
    const char *ptr = format;
    
    while (*ptr && count < max_types) {
        if (*ptr == '%') {
            ptr++;
            // Skip flags
            while (*ptr && (*ptr == '#' || *ptr == '0' || *ptr == '-' || 
                   *ptr == '+' || *ptr == ' '))
                ptr++;
            
            // Skip width and precision
            while (*ptr && (*ptr >= '0' && *ptr <= '9'))
                ptr++;
            if (*ptr == '.') {
                ptr++;
                while (*ptr && (*ptr >= '0' && *ptr <= '9'))
                    ptr++;
            }
            
            // Get the actual specifier
            if (*ptr && *ptr != '%') {
                types[count++] = *ptr;
            } else if (*ptr == '%') {
                // Skip %% as it doesn't consume an argument
                ptr++;
                continue;
            }
        }
        if (*ptr)
            ptr++;
    }
    
    types[count] = '\0';
}

/* Call ft_printf with proper argument types based on format specifiers */
int call_ft_printf_with_args(const char *format, va_list args)
{
    char types[20] = {0};
    get_format_specifiers(format, types, 19);
    
    // Extract and organize arguments based on type
    void *arg_ptrs[20] = {0};
    int i_vals[20] = {0};
    unsigned int u_vals[20] = {0};
    char c_vals[20] = {0};
    
    for (int i = 0; types[i] != '\0'; i++) {
        switch (types[i]) {
            case 's': 
                arg_ptrs[i] = va_arg(args, char*); 
                break;
            case 'p': 
                arg_ptrs[i] = va_arg(args, void*); 
                break;
            case 'd':
            case 'i': 
                i_vals[i] = va_arg(args, int); 
                break;
            case 'u':
            case 'x':
            case 'X': 
                u_vals[i] = va_arg(args, unsigned int); 
                break;
            case 'c': 
                c_vals[i] = (char)va_arg(args, int); 
                break;
            default:
                i_vals[i] = va_arg(args, int);
        }
    }
    
    // Call ft_printf with appropriate arguments based on format types
    int ret = 0;
    switch (strlen(types)) {
        case 0:
            ret = ft_printf(format);
            break;
        case 1:
            switch (types[0]) {
                case 's': ret = ft_printf(format, arg_ptrs[0]); break;
                case 'p': ret = ft_printf(format, arg_ptrs[0]); break;
                case 'd': 
                case 'i': ret = ft_printf(format, i_vals[0]); break;
                case 'u':
                case 'x':
                case 'X': ret = ft_printf(format, u_vals[0]); break;
                case 'c': ret = ft_printf(format, c_vals[0]); break;
                default: ret = ft_printf(format, i_vals[0]);
            }
            break;
        // Add cases for 2, 3, 4, or more arguments as needed
        // This is just a basic implementation
        default:
            ret = ft_printf("Error: Too many format specifiers");
    }
    
    return ret;
}
