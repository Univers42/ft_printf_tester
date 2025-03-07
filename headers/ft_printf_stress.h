/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 01:20:39 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_STRESS_H
#define FT_PRINTF_STRESS_H

#include "controller.h"

/* Core testing utilities */
void test_simple(const char *format, const char *test_name, ...);
void stress_test_format(const char *format, const char *test_name, void *value, char type);
char* generate_random_format(void);
void test_random_value(const char *format);

/* Test categories */
void run_basic_tests(void);
void run_flag_stress_tests(void);
void test_width(void);
void test_precision(void);
void run_edge_case_tests(void);
void run_extreme_values_tests(void);
void run_mixed_format_tests(void);
void run_rapid_stress_test(int iterations);
void test_pointer_format_flags(const char *format, const char *test_name, void *ptr);
void test_edge_case(const char *format, const char *test_name);
void run_robust_mixed_format_tests(void);

/* These functions are also needed from test_utils */
void print_formatted_string(const char *str, int ret);
void print_with_visible_spaces(const char *str);
void compare_and_print_results(const char *expected, int expected_ret,
                             const char *actual, int actual_ret, 
                             const char *format, const char *test_name);
void initialize_test_counters(void);
void print_summary(void);

int ft_printf(const char *format, ...);

#endif
