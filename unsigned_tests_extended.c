/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_tests_extended.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:48:22 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/03 23:52:15 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ft_printf_test_utils.h"
#include "ft_printf_debug.h"

// External ft_printf declaration
int ft_printf(const char *format, ...);

// Function prototype for test_unsigned if it's not included in the headers
void test_unsigned(unsigned int value, const char *format, const char *test_name);

int main(void)
{
    printf("=== UNSIGNED INTEGER CONVERSION EXTENDED TEST ===\n\n");
    
    // Initialize test counters
    test_count = 0;
    pass_count = 0;
    fail_count = 0;
    
    // Basic unsigned tests
    test_unsigned(0, "%u", "Zero");
    test_unsigned(1, "%u", "One");
    test_unsigned(42, "%u", "Small positive");
    test_unsigned(UINT_MAX, "%u", "Maximum unsigned int");
    test_unsigned(UINT_MAX - 1, "%u", "Almost maximum");
    test_unsigned(INT_MAX, "%u", "INT_MAX as unsigned");
    test_unsigned(INT_MAX + 1U, "%u", "INT_MAX + 1");
    
    // Test with negative values (converted to unsigned)
    int negative = -1;
    test_unsigned((unsigned int)negative, "%u", "Negative as unsigned (-1)");
    negative = -42;
    test_unsigned((unsigned int)negative, "%u", "Negative as unsigned (-42)");
    negative = INT_MIN;
    test_unsigned((unsigned int)negative, "%u", "INT_MIN as unsigned");
    
    // Binary powers
    test_unsigned(1U << 0, "%u", "2^0");
    test_unsigned(1U << 1, "%u", "2^1");
    test_unsigned(1U << 4, "%u", "2^4");
    test_unsigned(1U << 8, "%u", "2^8");
    test_unsigned(1U << 16, "%u", "2^16");
    test_unsigned(1U << 24, "%u", "2^24");
    test_unsigned(1U << 31, "%u", "2^31");
    
    // Common values
    test_unsigned(100, "%u", "Hundred");
    test_unsigned(1000, "%u", "Thousand");
    test_unsigned(10000, "%u", "Ten thousand");
    test_unsigned(100000, "%u", "Hundred thousand");
    test_unsigned(1000000, "%u", "Million");
    test_unsigned(4294967295U, "%u", "4294967295 (UINT_MAX)");
    
    // Test overflow behavior
    unsigned int big_value = UINT_MAX;
    test_unsigned(big_value + 1, "%u", "Overflow test");
    
    // Print summary
    printf("\n=== TEST SUMMARY ===\n");
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, 
           (float)pass_count / test_count * 100, RESET);
    printf("Failed: %s%d (%.1f%%)%s\n", 
           fail_count > 0 ? RED : GREEN, fail_count, 
           (float)fail_count / test_count * 100, RESET);
    
    return (fail_count > 0);
}
