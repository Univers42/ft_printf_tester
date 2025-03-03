/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_ft_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:12 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/03 14:06:11 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../include/ft_printf.h"  // Updated include path

/*
 * This is a simple wrapper for ft_printf used in testing
 * It calls the actual ft_printf function with the given format and arguments
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
