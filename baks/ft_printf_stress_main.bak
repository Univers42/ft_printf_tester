/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 01:19:09 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_stress.h"

/* Global test counters */
int test_count = 0;
int pass_count = 0;
int fail_count = 0;

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
