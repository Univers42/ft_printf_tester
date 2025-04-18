/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:35:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 16:40:54 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/controller.h"

int ft_printf(const char *format, ...);

void	test_int(int value, const char *format, const char *test_name)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	expected_ret = sprintf(expected, format, value);
	fp = tmpfile();
	if (!fp)
	{
		perror("Failed to create temporary file");
		return ;
	}
	original_stdout = dup(1);
	if (dup2(fileno(fp), 1) == -1)
	{
		perror("Failed to redirect stdout");
		fclose(fp);
		return ;
	}
	actual_ret = ft_printf(format, value);
	fflush(stdout);
	dup2(original_stdout, 1);
	close(original_stdout);
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
	actual[bytes_read] = '\0';
	fclose(fp);
	compare_and_print_results(expected, expected_ret, actual, actual_ret,
		format, test_name);
	if (strcmp(expected, actual) != 0 || expected_ret != actual_ret)
		printf("  Value:     %d (0x%x)\n", value, value);
}

void	test_unsigned(unsigned int value, const char *format, const char *test_name)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	expected_ret = sprintf(expected, format, value);
	fp = tmpfile();
	if (!fp)
	{
		perror("Failed to create temporary file");
		return ;
	}
	original_stdout = dup(1);
	if (dup2(fileno(fp), 1) == -1)
	{
		perror("Failed to redirect stdout");
		fclose(fp);
		return ;
	}
	actual_ret = ft_printf(format, value);
	fflush(stdout);
	dup2(original_stdout, 1);
	close(original_stdout);
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
	actual[bytes_read] = '\0';
	fclose(fp);
	compare_and_print_results(expected, expected_ret, actual, actual_ret,
		format, test_name);
	if (strcmp(expected, actual) != 0 || expected_ret != actual_ret)
		printf("  Value:     %u (0x%x)\n", value, value);
}

void	test_hex(unsigned int value, int is_upper, const char *format,
		const char *test_name)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	(void)is_upper;
	expected_ret = sprintf(expected, format, value);
	fp = tmpfile();
	if (!fp)
	{
		perror("Failed to create temporary file");
		return ;
	}
	original_stdout = dup(1);
	if (dup2(fileno(fp), 1) == -1)
	{
		perror("Failed to redirect stdout");
		fclose(fp);
		return ;
	}
	actual_ret = ft_printf(format, value);
	fflush(stdout);
	dup2(original_stdout, 1);
	close(original_stdout);
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
	actual[bytes_read] = '\0';
	fclose(fp);
	compare_and_print_results(expected, expected_ret, actual, actual_ret,
		format, test_name);
	if (strcmp(expected, actual) != 0 || expected_ret != actual_ret)
		printf("  Value:     %u (0x%x)\n", value, value);
}
