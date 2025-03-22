/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_flag_handlers.c                            :+:      :+:    :+:   */
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
 * Test implementation of minus flag handler.
 */
void	handle_minus(t_flags *flags, va_list args)
{
	(void)args;
	set_flag_bit('-', flags);
	flags->flags_bits &= ~ZERO_FLAG;
}

/**
 * Test implementation of zero flag handler.
 */
void	handle_zero(t_flags *flags, va_list args)
{
	(void)args;
	set_flag_bit('0', flags);
}

/**
 * Test implementation of dot flag handler.
 */
void	handle_dot(t_flags *flags, va_list args)
{
	(void)args;
	set_flag_bit('.', flags);
	flags->flags_bits &= ~ZERO_FLAG;
	flags->precision = 0;
}

/**
 * Test implementation of hash flag handler.
 */
void	handle_hash(t_flags *flags, va_list args)
{
	(void)args;
	set_flag_bit('#', flags);
}

/**
 * Test implementation of space flag handler.
 */
void	handle_space(t_flags *flags, va_list args)
{
	(void)args;
	set_flag_bit(' ', flags);
}

/**
 * Test implementation of plus flag handler.
 */
void	handle_plus(t_flags *flags, va_list args)
{
	(void)args;
	set_flag_bit('+', flags);
	flags->flags_bits &= ~SPACE_FLAG;
}

/**
 * Test implementation of star flag handler.
 */
void	handle_star(t_flags *flags, va_list args)
{
	set_flag_bit('*', flags);
	ft_handle_width(va_arg(args, int), flags);
}
