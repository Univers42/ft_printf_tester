/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_test_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:22:48 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/03 23:56:19 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TEST_UTILS_H
# define FT_PRINTF_TEST_UTILS_H
# include "ft_printf_debug.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>

// Set this to 1 for more detailed output
# define VERBOSE 0

// ANSI color codes for output
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

// Buffer size for capturing output - use a unique name to avoid conflicts
# define FT_TEST_BUFFER_SIZE 8192

// Function declarations
void	print_test_header(const char *title, const char *color);
void	print_test_footer(const char *title, const char *color);
void	print_test_comparison(const char *format, int orig_ret, int ft_ret, char *orig_out, char *ft_out);
void	initialize_test_counters(void);
void	get_test_results(int *total, int *failed);
void    print_with_visible_spaces(const char *str);
void    print_formatted_string(const char *str, int ret);
void    run_category(  const char *category);
void print_summary(void);
void run_test(const char *title, const char *format, ...);
void test_char(char c, const char *format, const char *test_name);
void test_string(const char *str, const char *format, const char *test_name);
void test_int(int num, const char *format, const char *test_name);
void test_pointer(void *ptr, const char *format, const char *test_name);
void test_pointer_with_flags(void *ptr, const char *format, const char *test_name);
void test_hex(unsigned int value, int is_upper, const char *format, const char *test_name);
void test_multiple_chars(const char *format, const char *test_name, ...);
void test_multiple_strings(const char *format, const char *test_name, ...);
void test_multiple_pointers(const char *format, const char *test_name, ...);
void test_format(const char *format, const char *test_name, void *value, char type);
int capture_output(char *buffer, int size, const char *format, ...);
void capture_formatted_output(char *buffer, int *ret, const char *format, va_list args);;
void compare_and_print_results(const char *expected, int expected_ret, 
                             const char *actual, int actual_ret, 
                             const char *format, const char *test_name);

// External ft_printf declaration
int ft_printf(const char *format, ...);

// Completely revised TEST macro that uses pipes to directly capture ft_printf output
# define TEST(format, ...) do { \
	int orig_ret, ft_ret; \
	char orig_buf[FT_TEST_BUFFER_SIZE] = {0}; \
	char ft_buf[FT_TEST_BUFFER_SIZE] = {0}; \
	\
	/* Capture standard printf output */ \
	FILE *orig_stream = fmemopen(orig_buf, sizeof(orig_buf) - 1, "w"); \
	if (!orig_stream) { \
		printf("Error: Failed to open memory stream\n"); \
		exit(1); \
	} \
	orig_ret = fprintf(orig_stream, format, ##__VA_ARGS__); \
	fclose(orig_stream); \
	\
	/* Directly capture ft_printf output using pipe */ \
	int pipe_fd[2]; \
	if (pipe(pipe_fd) == -1) { \
		printf("Error: Failed to create pipe\n"); \
		exit(1); \
	} \
	\
	int saved_stdout = dup(STDOUT_FILENO); \
	dup2(pipe_fd[1], STDOUT_FILENO); \
	\
	/* Call ft_printf directly */ \
	ft_ret = ft_printf(format, ##__VA_ARGS__); \
	fflush(stdout); \
	\
	/* Restore stdout */ \
	dup2(saved_stdout, STDOUT_FILENO); \
	close(pipe_fd[1]); \
	\
	/* Read captured output from pipe */ \
	int bytes_read = read(pipe_fd[0], ft_buf, FT_TEST_BUFFER_SIZE - 1); \
	if (bytes_read >= 0) \
		ft_buf[bytes_read] = '\0'; \
	close(pipe_fd[0]); \
	close(saved_stdout); \
	\
	/* Compare results */ \
	print_test_comparison(format, orig_ret, ft_ret, orig_buf, ft_buf); \
} while (0)

// Function to redirect ft_printf to a FILE stream
int		simple_ft_printf(FILE *stream, const char *format, ...);

#endif
