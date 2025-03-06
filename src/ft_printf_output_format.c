/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output_format.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:15:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 16:40:37 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Note: This file is designed to be included in ft_printf_test_utils.c */
/* Therefore no need to include headers or define functions that are already declared */
#include "../headers/controller.h"

void	print_formatted_string(const char *str, int ret)
{
	int	i;

	printf("\"");
	for (i = 0; i < (int)strlen(str); i++)
	{
		if (str[i] == ' ')
			printf("%s·%s", YELLOW, RESET);
		else if (str[i] == '0')
			printf("%s0%s", CYAN, RESET);
		else if (str[i] < 32 || str[i] > 126)
			printf("%s\\%03o%s", BLUE, str[i], RESET);
		else
			printf("%c", str[i]);
	}
	printf("\" (ret: %d)", ret);
}

void	print_with_visible_spaces(const char *str)
{
	int	i;

	for (i = 0; i < (int)strlen(str); i++)
	{
		if (str[i] == ' ')
			printf("%s·%s", YELLOW, RESET);
		else
			printf("%c", str[i]);
	}
}

void	print_test_header(const char *title, const char *color)
{
	printf("%s%s=== %s ===%s\n\n", BOLD, color, title, RESET);
}

void	print_test_footer(const char *title, const char *color)
{
	printf("\n%s%s=== End of %s ===%s\n\n", BOLD, color, title, RESET);
}
