/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_tester.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/12 23:03:58 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/controller.h"

/* These are already declared in ft_printf_test_utils.c */
extern int test_count;
extern int pass_count;
extern int fail_count;

/**
 * Simple test function with direct input values
 * Eliminates the need for specialized test functions for each type
 */
void test_simple(const char *format, const char *test_name, ...);
void stress_test_format(const char *format, const char *test_name, void *value, char type);
char* generate_random_format(void);
void test_random_value(const char *format);
void test_pointer_format_flags(const char *format, const char *test_name, void *ptr);
void test_edge_case(const char *format, const char *test_name);
void run_basic_tests(void);
void run_flag_stress_tests(void);
void test_width(void);
void test_precision(void);
void run_edge_case_tests(void);
void run_extreme_values_tests(void);
void run_mixed_format_tests(void);
void run_robust_mixed_format_tests(void);
void run_rapid_stress_test(int iterations);

// Include the actual implementations
#include "../utils/ft_printf_stress_core.c"
#include "../utils/ft_printf_stress_format.c"
#include "../utils/ft_printf_stress_basic.c"
#include "../utils/ft_printf_stress_width_precision.c"
#include "../utils/ft_printf_stress_edge_cases.c"
#include "../utils/ft_printf_stress_pointer_rapid.c"
#include "../utils/ft_printf_mixed_tests.c"

/* Main function to run the stress tester */
int main(void)
{
    printf("========================================================\n");
    printf("        FT_PRINTF ADVANCED STRESS TESTER v3.0          \n");
    printf("========================================================\n");
    
    initialize_test_counters();
    
    // Run tests in order of increasing complexity
    run_basic_tests();
    run_flag_stress_tests();
    test_width();
    test_precision();
    run_edge_case_tests();
    run_extreme_values_tests();
    run_mixed_format_tests();
    
    // Run random tests as the final stress test
    run_rapid_stress_test(20); // Adjust the number of iterations as needed
    
    // Print final summary
    printf("\n========================================================\n");
    print_summary();
    
    return 0;
}
