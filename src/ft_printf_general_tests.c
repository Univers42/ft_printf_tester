/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_general_tests.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:30:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 17:17:35 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDED_IN_MAIN_FILE
# include "../headers/controller.h"
#endif

int ft_printf(const char *format, ...);

/* Run a simple test with direct comparison */
void	run_test(const char *test_name, const char *format, ...)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	va_list	args;
	va_list	args_copy1;
	va_list	args_copy2;
	int		pipe_fd[2];
	int		saved_stdout;
	int		bytes_read;

	memset(expected, 0, BUFFER_SIZE);
	memset(actual, 0, BUFFER_SIZE);
	va_start(args, format);
	va_copy(args_copy1, args);
	va_copy(args_copy2, args);
	pipe(pipe_fd);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	expected_ret = vprintf(format, args_copy1);
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(pipe_fd[1]);
	bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
	if (bytes_read >= 0)
		expected[bytes_read] = '\0';
	close(pipe_fd[0]);
	pipe(pipe_fd);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	actual_ret = ft_printf(format, args_copy2);
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(pipe_fd[1]);
	bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
	if (bytes_read >= 0)
		actual[bytes_read] = '\0';
	close(pipe_fd[0]);
	va_end(args_copy1);
	va_end(args_copy2);
	va_end(args);
	compare_and_print_results(expected, expected_ret, actual, actual_ret,
		format, test_name);
}

/* Example of a function that uses printf_test_type_t */
void run_test_by_category(printf_test_type_t category, void *value, const char *format)
{
    switch (category)
    {
        case CHAR_TEST:
            test_char(*(char*)value, format, "Character test");
            break;
        case STRING_TEST:
            test_string((char*)value, format, "String test");
            break;
        case INT_TEST:
            test_int(*(int*)value, format, "Integer test");
            break;
        case UINT_TEST:
            test_unsigned(*(unsigned int*)value, format, "Unsigned int test");
            break;
        case HEX_TEST:
            test_hex(*(unsigned int*)value, 0, format, "Hexadecimal test");
            break;
        case POINTER_TEST:
            test_pointer(value, format, "Pointer test");
            break;
        case PERCENT_TEST:
            test_string("", format, "Percent test");
            break;
        case MIXED_TEST:
            // Handle mixed test case
            break;
        case PRINTF_STRESS_TEST:
            // Handle stress test case
            break;
        default:
            printf("Unknown test category\n");
    }
}

/* ---- Generic test function ---- */
void	test_format(const char *format, const char *test_name,
		void *value, char type)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	// Get the expected output first using standard printf
	switch (type)
	{
		case 'c': expected_ret = sprintf(expected, format, *((char*)value)); break;
		case 's': expected_ret = sprintf(expected, format, (char*)value); break;
		case 'p': expected_ret = sprintf(expected, format, value); break;
		case 'd':
		case 'i': expected_ret = sprintf(expected, format, *((int*)value)); break;
		case 'u': expected_ret = sprintf(expected, format, *((unsigned int*)value)); break;
		case 'x':
		case 'X': expected_ret = sprintf(expected, format, *((unsigned int*)value)); break;
		case '%': expected_ret = sprintf(expected, "%s", format); break; // Fixed: Use "%s" as format and format as argument
		default: expected_ret = sprintf(expected, format, 0); break;
	}

	// Setup file for output capture
	fp = tmpfile();
	if (!fp)
	{
		perror("Failed to create temporary file");
		return;
	}
	
	original_stdout = dup(1);
	if (dup2(fileno(fp), 1) == -1)
	{
		perror("Failed to redirect stdout");
		fclose(fp);
		return;
	}
	
	// Save the value before ft_printf to prevent any stack corruption
	// Call ft_printf with the appropriate argument type
	switch (type)
	{
		case 'c': 
		{
			char c_val = *((char*)value);
			actual_ret = ft_printf(format, c_val);
			break;
		}
		case 's':
		{
			char *s_val = (char*)value;
			actual_ret = ft_printf(format, s_val);
			break;
		}
		case 'p':
		{
			void *p_val = value;
			actual_ret = ft_printf(format, p_val);
			break;
		}
		case 'd':
		case 'i':
		{
			int d_val = *((int*)value);
			actual_ret = ft_printf(format, d_val);
			break;
		}
		case 'u':
		{
			unsigned int u_val = *((unsigned int*)value);
			actual_ret = ft_printf(format, u_val);
			break;
		}
		case 'x':
		case 'X':
		{
			unsigned int x_val = *((unsigned int*)value);
			actual_ret = ft_printf(format, x_val);
			break;
		}
		case '%':
			actual_ret = ft_printf("%s", format); break; // Same fix for ft_printf
			
		default:
			actual_ret = ft_printf(format, 0);
			break;
	}

	// Restore stdout and collect output
	fflush(stdout);
	dup2(original_stdout, 1);
	close(original_stdout);
	
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
	actual[bytes_read] = '\0';
	fclose(fp);
	
	// Compare results
	compare_and_print_results(expected, expected_ret, actual, actual_ret,
		format, test_name);
		
	// Show value in error message if needed
	if (strcmp(expected, actual) != 0 || expected_ret != actual_ret)
	{
		switch (type)
		{
			case 'c': printf("  Value:     '%c'\n", *((char*)value)); break;
			case 's': printf("  Value:     \"%s\"\n",
				(char*)value ? (char*)value : "NULL"); break;
			case 'p': printf("  Value:     %p\n", value); break;
			case 'd':
			case 'i': printf("  Value:     %d\n", *((int*)value)); break;
			case 'u': printf("  Value:     %u\n", *((unsigned int*)value)); break;
			case 'x': printf("  Value:     0x%x\n", *((unsigned int*)value)); break;
			case 'X': printf("  Value:     0x%X\n", *((unsigned int*)value)); break;
		}
	}
}
