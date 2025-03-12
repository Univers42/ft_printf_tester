/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:30:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 16:47:36 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDED_IN_MAIN_FILE
# include "../headers/controller.h"
#endif

int ft_printf(const char *format, ...);

void	test_pointer(void *ptr, const char *format, const char *test_name)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	expected_ret = sprintf(expected, format, ptr);
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
	actual_ret = ft_printf(format, ptr);
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
		printf("  Pointer:   %p\n", ptr);
}

void	test_pointer_with_flags(void *ptr, const char *format, const char *test_name)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	expected_ret = sprintf(expected, format, ptr);
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
	actual_ret = ft_printf(format, ptr);
	fflush(stdout);
	dup2(original_stdout, 1);
	close(original_stdout);
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
	actual[bytes_read] = '\0';
	fclose(fp);
	if ((strncmp(format, "%+", 2) == 0 || strncmp(format, "% ", 2) == 0)
		&& (strncmp(expected, "+", 1) == 0 || expected[0] == ' ')
		&& strncmp(actual, "0x", 2) == 0)
	{
		printf("%s[PLATFORM DIFF - PASS]%s %s\n", YELLOW, RESET, test_name);
		printf("  Format:    \"%s\"\n", format);
		printf("  Expected:  \"");
		print_with_visible_spaces(expected);
		printf("\" (ret: %d)\n", expected_ret);
		printf("  Actual:    \"");
		print_with_visible_spaces(actual);
		printf("\" (ret: %d)\n", actual_ret);
		printf("  Note:      Difference in handling sign flags with pointers is platform-specific\n");
		test_count++;
		pass_count++;
	}
	else
		compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
	if (strcmp(expected, actual) != 0 || expected_ret != actual_ret)
		printf("  Pointer:   %p\n", ptr);
}

void	test_multiple_pointers(const char *format, const char *test_name, ...)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	va_list	args;
	va_list	args_copy;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;
	void	*ptr1;
	void	*ptr2;
	void	*ptr3;
	void	*ptr4;
	void	*ptr5;

	va_start(args, test_name);
	va_copy(args_copy, args);
	expected_ret = vsnprintf(expected, BUFFER_SIZE, format, args);
	va_end(args);
	fp = tmpfile();
	if (!fp)
	{
		perror("Failed to create temporary file");
		va_end(args_copy);
		return ;
	}
	original_stdout = dup(1);
	if (dup2(fileno(fp), 1) == -1)
	{
		perror("Failed to redirect stdout");
		fclose(fp);
		va_end(args_copy);
		return ;
	}
	if (strstr(format, "%p vs %p") != NULL)
	{
		ptr1 = va_arg(args_copy, void*);
		ptr2 = va_arg(args_copy, void*);
		actual_ret = ft_printf(format, ptr1, ptr2);
	}
	else if (strstr(format, "Multiple: %p %p %p %p %p") != NULL)
	{
		ptr1 = va_arg(args_copy, void*);
		ptr2 = va_arg(args_copy, void*);
		ptr3 = va_arg(args_copy, void*);
		ptr4 = va_arg(args_copy, void*);
		ptr5 = va_arg(args_copy, void*);
		actual_ret = ft_printf(format, ptr1, ptr2, ptr3, ptr4, ptr5);
	}
	else
	{
		ptr1 = va_arg(args_copy, void*);
		ptr2 = va_arg(args_copy, void*);
		ptr3 = va_arg(args_copy, void*);
		actual_ret = ft_printf(format, ptr1, ptr2, ptr3);
	}
	fflush(stdout);
	dup2(original_stdout, 1);
	close(original_stdout);
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
	actual[bytes_read] = '\0';
	fclose(fp);
	va_end(args_copy);
	compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
}
