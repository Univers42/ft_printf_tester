/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_tests_extended.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:48:22 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/12 23:41:55 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/controller.h"

void test_unsigned(unsigned int value, const char *format, const char *test_name);

int main(void)
{
       int negative = -1;
       unsigned int big_value = UINT_MAX;

       printf("=== UNSIGNED INTEGER CONVERSION EXTENDED TEST ===\n\n");
       test_count = 0;
       pass_count = 0;
       fail_count = 0;
       test_unsigned(0, "%u", "Zero");
       test_unsigned(1, "%u", "One");
       test_unsigned(42, "%u", "Small positive");
       test_unsigned(UINT_MAX, "%u", "Maximum unsigned int");
       test_unsigned(UINT_MAX - 1, "%u", "Almost maximum");
       test_unsigned(INT_MAX, "%u", "INT_MAX as unsigned");
       test_unsigned(INT_MAX + 1U, "%u", "INT_MAX + 1");
       test_unsigned((unsigned int)negative, "%u", "Negative as unsigned (-1)");
       negative = -42;
       test_unsigned((unsigned int)negative, "%u", "Negative as unsigned (-42)");
       negative = INT_MIN;
       test_unsigned((unsigned int)negative, "%u", "INT_MIN as unsigned");
       test_unsigned(1U << 0, "%u", "2^0");
       test_unsigned(1U << 1, "%u", "2^1");
       test_unsigned(1U << 4, "%u", "2^4");
       test_unsigned(1U << 8, "%u", "2^8");
       test_unsigned(1U << 16, "%u", "2^16");
       test_unsigned(1U << 24, "%u", "2^24");
       test_unsigned(1U << 31, "%u", "2^31");
       test_unsigned(100, "%u", "Hundred");
       test_unsigned(1000, "%u", "Thousand");
       test_unsigned(10000, "%u", "Ten thousand");
       test_unsigned(100000, "%u", "Hundred thousand");
       test_unsigned(1000000, "%u", "Million");
       test_unsigned(4294967295U, "%u", "4294967295 (UINT_MAX)");
       test_unsigned(big_value + 1, "%u", "Overflow test");
       printf("\n=== TEST SUMMARY ===\n");
       printf("Total tests: %d\n", test_count);
       printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, (float)pass_count / test_count * 100, RESET);
       printf("Failed: %s%d (%.1f%%)%s\n", fail_count > 0 ? RED : GREEN, fail_count, (float)fail_count / test_count * 100, RESET);
    return (fail_count > 0);
}
