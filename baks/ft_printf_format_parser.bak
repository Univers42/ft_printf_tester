/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 23:17:41 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/controller.h"

/* Parse format string and extract format specifier types */
int parse_format_string(const char *format, char *types, int max_types)
{
    int count = 0;
    const char *ptr = format;
    
    while (*ptr && count < max_types - 1) {
        if (*ptr == '%') {
            ptr++;
            // Skip %% as it doesn't consume an argument
            if (*ptr == '%') {
                ptr++;
                continue;
            }
            
            // Skip flags
            while (*ptr && (*ptr == '#' || *ptr == '0' || *ptr == '-' || 
                   *ptr == '+' || *ptr == ' '))
                ptr++;
            
            // Skip width
            while (*ptr && (*ptr >= '0' && *ptr <= '9'))
                ptr++;
                
            // Skip precision
            if (*ptr == '.') {
                ptr++;
                while (*ptr && (*ptr >= '0' && *ptr <= '9'))
                    ptr++;
            }
            
            // Get the actual specifier
            if (*ptr) {
                types[count++] = *ptr;
                ptr++;
            }
        } else {
            ptr++;
        }
    }
    
    types[count] = '\0';
    return count;
}

/* Call ft_printf with appropriate argument types for up to 5 format specifiers */
int call_ft_printf_with_types(const char *format, va_list args, char *types, int type_count)
{
    int ret = 0;
    va_list args_copy;
    va_copy(args_copy, args);
    
    // Storage for different argument types
    int int_args[5] = {0};
    unsigned int uint_args[5] = {0};
    char *str_args[5] = {NULL};
    void *ptr_args[5] = {NULL};
    char char_args[5] = {0};
    
    // Extract arguments based on their types
    for (int i = 0; i < type_count && i < 5; i++) {
        switch (types[i]) {
            case 's':
                str_args[i] = va_arg(args_copy, char*);
                break;
            case 'p':
                ptr_args[i] = va_arg(args_copy, void*);
                break;
            case 'd':
            case 'i':
                int_args[i] = va_arg(args_copy, int);
                break;
            case 'u':
            case 'x':
            case 'X':
                uint_args[i] = va_arg(args_copy, unsigned int);
                break;
            case 'c':
                char_args[i] = (char)va_arg(args_copy, int);
                break;
            default:
                int_args[i] = va_arg(args_copy, int);
        }
    }
    
    va_end(args_copy);
    
    // Call ft_printf with the appropriate number and types of arguments
    switch (type_count) {
        case 0:
            ret = ft_printf(format);
            break;
        case 1:
            switch (types[0]) {
                case 's': ret = ft_printf(format, str_args[0]); break;
                case 'p': ret = ft_printf(format, ptr_args[0]); break;
                case 'd': 
                case 'i': ret = ft_printf(format, int_args[0]); break;
                case 'u':
                case 'x':
                case 'X': ret = ft_printf(format, uint_args[0]); break;
                case 'c': ret = ft_printf(format, char_args[0]); break;
                default:  ret = ft_printf(format, int_args[0]);
            }
            break;
        case 2:
            // This can be expanded for specific type combinations as needed
            ret = ft_printf("Multiple format specifiers not yet implemented");
            break;
        // Add cases for 3, 4, 5 arguments as needed
        default:
            ret = ft_printf("Too many format specifiers");
    }
    
    return ret;
}
