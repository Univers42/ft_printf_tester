/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_test_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:10:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 16:15:53 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TEST_UTILS_H
# define FT_PRINTF_TEST_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include <fcntl.h>
# include "colors.h"
# include "structs.h"

# define BUFFER_SIZE 4096
# define VERBOSE 0

/* Output formatting utilities */
void test_pointer_with_flags(void *ptr, const char *format, const char *test_name);
void test_hex(unsigned int value, int is_upper, const char *format, const char *test_name);
void test_multiple_chars(const char *format, const char *test_name, ...);
void test_multiple_strings(const char *format, const char *test_name, ...);
void test_multiple_pointers(const char *format, const char *test_name, ...);
void test_format(const char *format, const char *test_name, void *value, char type);
int capture_output(char *buffer, int size, const char *format, ...);
void capture_formatted_output(char *buffer, int *ret, const char *format, va_list args);
void compare_and_print_results(const char *expected, int expected_ret, 
                               const char *actual, int actual_ret, 
                               const char *format, const char *test_name);
void print_formatted_string(const char *str, int ret);
void print_with_visible_spaces(const char *str);
void run_category(const char *category);
void print_summary(void);
void print_test_header(const char *title, const char *color);
void print_test_footer(const char *title, const char *color);
void print_test_comparison(const char *format, int orig_ret, int ft_ret,
    char *orig_out, char *ft_out);
void initialize_test_counters(void);
void get_test_results(int *total, int *failed);
void test_char(char c, const char *format, const char *test_name);
void test_int(int value, const char *format, const char *test_name);
void test_unsigned(unsigned int value, const char *format, const char *test_name);
void test_string(const char *str, const char *format, const char *test_name);
void test_pointer(void *ptr, const char *format, const char *test_name);
void run_test(const char *test_name, const char *format, ...);

int ft_printf(const char *format, ...);

#endif
