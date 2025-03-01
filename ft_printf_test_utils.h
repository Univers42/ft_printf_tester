/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_test_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2024/06/01 16:00:00 by syzygy            #+#    #+#             */
/*   Updated: 2024/06/01 16:00:00 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TEST_UTILS_H
# define FT_PRINTF_TEST_UTILS_H

# include "../ft_printf.h"
# include "ft_printf_debug.h"
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

// Global test counters
extern int test_count;
extern int pass_count;
extern int fail_count;

// Display functions
void print_with_visible_spaces(const char *str);
void print_formatted_string(const char *str, int ret);

// Test helper functions
void run_category(const char *category);
void print_summary(void);

// Test functions
void run_test(const char *test_name, const char *format, ...);
void test_char(char c, const char *format, const char *test_name);
void test_string(const char *str, const char *format, const char *test_name);
void test_int(int value, const char *format, const char *test_name);
void test_unsigned(unsigned int value, const char *format, const char *test_name);
void test_pointer(void *ptr, const char *format, const char *test_name);
void test_pointer_with_flags(void *ptr, const char *format, const char *test_name);
void test_hex(unsigned int value, int is_upper, const char *format, const char *test_name);

// Multiple argument tests
void test_multiple_chars(const char *format, const char *test_name, ...);
void test_multiple_strings(const char *format, const char *test_name, ...);
void test_multiple_pointers(const char *format, const char *test_name, ...);

// Generic test function
void test_format(const char *format, const char *test_name, void *value, char type);

// Capture output functions
int capture_output(char *buffer, int size, const char *format, ...);
void capture_formatted_output(char *actual, int *actual_ret, const char *format, va_list args);

// Result comparison functions
void compare_and_print_results(const char *expected, int expected_ret, 
                              const char *actual, int actual_ret, 
                              const char *format, const char *test_name);

#endif
