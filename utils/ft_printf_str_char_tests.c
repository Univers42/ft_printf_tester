/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_char_tests.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:30:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/12 23:29:51 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_test_utils.h"

int ft_printf(const char *format, ...);

void	test_char(char c, const char *format, const char *test_name)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	expected_ret = sprintf(expected, format, c);
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
	actual_ret = ft_printf(format, c);
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
	{
		printf("  Char:      '%c' (ASCII: %d)\n", 
			c > 31 && c < 127 ? c : '.', (int)c);
	}
}

void	test_multiple_chars(const char *format, const char *test_name, ...)
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
	int		num_chars = 0;
	char	c1, c2, c3, c4;

	// Count format specifiers to determine number of characters
	const char *ptr = format;
	while ((ptr = strstr(ptr, "%c")) != NULL) {
		num_chars++;
		ptr++; // Move past the current '%c'
	}

	va_start(args, test_name);
	va_copy(args_copy, args);
	
	// Get expected output using standard printf
	expected_ret = vsnprintf(expected, BUFFER_SIZE, format, args);
	
	// Setup for capturing ft_printf output
	fp = tmpfile();
	if (!fp) {
		perror("Failed to create temporary file");
		va_end(args);
		va_end(args_copy);
		return;
	}
	
	original_stdout = dup(1);
	if (dup2(fileno(fp), 1) == -1) {
		perror("Failed to redirect stdout");
		fclose(fp);
		va_end(args);
		va_end(args_copy);
		return;
	}
	
	// Extract characters from args_copy and call ft_printf with them directly
	if (num_chars == 1) {
		c1 = va_arg(args_copy, int); // va_arg uses int for char
		actual_ret = ft_printf(format, c1);
	} else if (num_chars == 2) {
		c1 = va_arg(args_copy, int);
		c2 = va_arg(args_copy, int);
		actual_ret = ft_printf(format, c1, c2);
	} else if (num_chars == 3) {
		c1 = va_arg(args_copy, int);
		c2 = va_arg(args_copy, int);
		c3 = va_arg(args_copy, int);
		actual_ret = ft_printf(format, c1, c2, c3);
	} else if (num_chars == 4) {
		c1 = va_arg(args_copy, int);
		c2 = va_arg(args_copy, int);
		c3 = va_arg(args_copy, int);
		c4 = va_arg(args_copy, int);
		actual_ret = ft_printf(format, c1, c2, c3, c4);
	} else {
		// Fallback for more characters (limited support)
		printf("Warning: test_multiple_chars can only handle up to 4 characters\n");
		actual_ret = ft_printf(format, 0);
	}
	
	fflush(stdout);
	
	// Restore stdout
	dup2(original_stdout, 1);
	close(original_stdout);
	
	// Get output from temporary file
	fseek(fp, 0, SEEK_SET);
	bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
	actual[bytes_read] = '\0';
	fclose(fp);
	
	va_end(args);
	va_end(args_copy);
	
	compare_and_print_results(expected, expected_ret, actual, actual_ret,
		format, test_name);
}

// Enhanced test function that can handle many consecutive character conversions
void test_multiple_chars_extended(const char *format, const char *test_name, ...)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    va_list args;
    va_list args_copy;
    int pipe_fd[2];
    int saved_stdout;
    int bytes_read;
    
    // Initialize va_lists
    va_start(args, test_name);
    va_copy(args_copy, args);
    
    // Capture expected output from standard printf
    if (pipe(pipe_fd) == -1) {
        perror("Failed to create pipe");
        va_end(args);
        va_end(args_copy);
        return;
    }
    
    saved_stdout = dup(STDOUT_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    
    // Use vprintf for expected output
    expected_ret = vprintf(format, args);
    
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(pipe_fd[1]);
    
    bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
    if (bytes_read >= 0)
        expected[bytes_read] = '\0';
    close(pipe_fd[0]);
    
    // Now capture ft_printf output using individual args to avoid vprintf issues
    if (pipe(pipe_fd) == -1) {
        perror("Failed to create pipe");
        va_end(args);
        va_end(args_copy);
        return;
    }
    
    saved_stdout = dup(STDOUT_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    
    // Extract format and count how many %c specifiers we have
    int count_formats = 0;
    const char *ptr = format;
    while ((ptr = strstr(ptr, "%c")) != NULL) {
        count_formats++;
        ptr += 2;  // Skip past the found "%c"
    }
    
    // Manual handling for specific format strings we know are problematic
    if (strcmp(format, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c") == 0) {
        // Handle the 25 consecutive chars case
        char chars[25];
        for (int i = 0; i < 25; i++) {
            chars[i] = (char)va_arg(args_copy, int);
        }
        actual_ret = ft_printf(format, chars[0], chars[1], chars[2], chars[3], chars[4],
                                     chars[5], chars[6], chars[7], chars[8], chars[9], 
                                     chars[10], chars[11], chars[12], chars[13], chars[14],
                                     chars[15], chars[16], chars[17], chars[18], chars[19],
                                     chars[20], chars[21], chars[22], chars[23], chars[24]);
    } 
    else if (strcmp(format, "A%cB%cC%cD%cE%cF%cG%cH%cI%cJ%c") == 0) {
        // Handle the alternating chars and text case
        char chars[10];
        for (int i = 0; i < 10; i++) {
            chars[i] = (char)va_arg(args_copy, int);
        }
        actual_ret = ft_printf(format, chars[0], chars[1], chars[2], chars[3], chars[4],
                                     chars[5], chars[6], chars[7], chars[8], chars[9]);
    }
    else if (strcmp(format, "%c %5c %-5c %05c %c %5c %-5c") == 0) {
        // Handle the mixed width and alignment case
        char chars[7];
        for (int i = 0; i < 7; i++) {
            chars[i] = (char)va_arg(args_copy, int);
        }
        actual_ret = ft_printf(format, chars[0], chars[1], chars[2], chars[3], 
                                     chars[4], chars[5], chars[6]);
    }
    else {
        // Generic approach for unknown format strings (may not work for all cases)
        actual_ret = ft_printf("Warning: test_multiple_chars_extended only supports predefined formats\n");
    }
    
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(pipe_fd[1]);
    
    bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
    if (bytes_read >= 0)
        actual[bytes_read] = '\0';
    close(pipe_fd[0]);
    
    va_end(args);
    va_end(args_copy);
    
    compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
}

void	test_string(const char *str, const char *format, const char *test_name)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	FILE	*fp;
	int		original_stdout;
	int		bytes_read;

	expected_ret = sprintf(expected, format, str);
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
	actual_ret = ft_printf(format, str);
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
		printf("  Input:     %s\"%s\"%s\n", BLUE, str ? str : "NULL", RESET);
}

void	test_multiple_strings(const char *format, const char *test_name, ...)
{
	char	expected[BUFFER_SIZE];
	char	actual[BUFFER_SIZE];
	int		expected_ret;
	int		actual_ret;
	va_list	args;
	va_list	args_copy;

	va_start(args, test_name);
	va_copy(args_copy, args);
	expected_ret = vsnprintf(expected, BUFFER_SIZE, format, args);
	va_end(args);
	capture_formatted_output(actual, &actual_ret, format, args_copy);
	va_end(args_copy);
	compare_and_print_results(expected, expected_ret, actual, actual_ret,
		format, test_name);
}
