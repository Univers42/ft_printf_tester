/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_converters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:10:00 by syzygy            #+#    #+#             */
/*   Updated: 2025/03/22 20:08:13 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/controller.h"
#include "../../include/ft_printf.h"
#include "../../include/ft_types.h"
#include "../../include/structs.h"

/**
 * Test implementation of converter for percent sign (%) format specifier.
 */
int	ft_convert_percent(char type, t_flags flags, va_list args)
{
	(void)type;
	(void)args;
	return (ft_print_percent(flags));
}

/**
 * Test implementation of converter for character format specifier.
 */
int	ft_convert_char(char type, t_flags flags, va_list args)
{
	(void)type;
	return (ft_print_char((unsigned char)va_arg(args, int), flags));
}

/**
 * Test implementation of converter for string format specifier.
 */
int	ft_convert_str(char type, t_flags flags, va_list args)
{
	(void)type;
	return (ft_print_str(va_arg(args, char *), flags));
}

/**
 * Test implementation of converter for integer format specifier.
 */
int	ft_convert_int(char type, t_flags flags, va_list args)
{
	(void)type;
	return (ft_print_int(va_arg(args, int), flags));
}

/**
 * Test implementation of converter for unsigned integer format specifier.
 */
int	ft_convert_unsigned(char type, t_flags flags, va_list args)
{
	(void)type;
	return (ft_print_unsigned(va_arg(args, unsigned int), flags));
}

/**
 * Test implementation of converter for lowercase hexadecimal format specifier.
 */
int	ft_convert_hex_lower(char type, t_flags flags, va_list args)
{
	(void)type;
	return (ft_print_hex_format(va_arg(args, unsigned int), 0, flags));
}

/**
 * Test implementation of converter for uppercase hexadecimal format specifier.
 */
int	ft_convert_hex_upper(char type, t_flags flags, va_list args)
{
	(void)type;
	return (ft_print_hex_format(va_arg(args, unsigned int), 1, flags));
}

/**
 * Test implementation of converter for pointer format specifier.
 */
int	ft_convert_ptr(char type, t_flags flags, va_list args)
{
	void	*ptr;

	(void)type;
	ptr = va_arg(args, void *);
	if (!ptr && (flags.flags_bits & DOT_FLAG) && flags.precision == 0)
		flags.flags_bits &= ~DOT_FLAG;
	return (ft_print_ptr((unsigned long)ptr, flags));
}
