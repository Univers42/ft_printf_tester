/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_tests_extended.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:18:31 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:18:33 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"

int main(void) {
    printf("%s=== FT_PRINTF EXTENDED UNSIGNED INTEGER TESTS ===%s\n", MAGENTA, RESET);
    
    // Remove these duplicate global variables
    // int test_count = 0;
    // int pass_count = 0;
    // int fail_count = 0;
    
    // Remove duplicate function implementations
    // void run_category(const char *category) { ... }
    // void test_unsigned(unsigned int value, const char *format, const char *test_name) { ... }
    
    // BASIC UNSIGNED INTEGER TESTS
    run_category("Basic Unsigned Integer Tests");
    
    // Test different values
    test_unsigned(0, "%u", "Zero");
    test_unsigned(1, "%u", "One");
    test_unsigned(42, "%u", "Positive small");
    test_unsigned(2147483647, "%u", "INT_MAX equivalent");
    test_unsigned(2147483648u, "%u", "INT_MAX + 1");
    test_unsigned(4294967295u, "%u", "UINT_MAX");
    
    // WIDTH TESTS
    run_category("Width Tests");
    
    // Test width formatting
    test_unsigned(0, "%5u", "Zero with width 5");
    test_unsigned(42, "%5u", "Positive with width 5");
    test_unsigned(2147483647, "%15u", "Large value with width 15");
    test_unsigned(4294967295u, "%15u", "UINT_MAX with width 15");
    
    // LEFT-JUSTIFY TESTS
    run_category("Left-Justify Tests");
    
    // Test left justification
    test_unsigned(0, "%-5u", "Zero left-justified width 5");
    test_unsigned(42, "%-5u", "Positive left-justified width 5");
    test_unsigned(2147483647, "%-15u", "Large value left-justified width 15");
    test_unsigned(4294967295u, "%-15u", "UINT_MAX left-justified width 15");
    
    // ZERO-PADDING TESTS
    run_category("Zero-Padding Tests");
    
    // Test zero padding
    test_unsigned(0, "%05u", "Zero zero-padded width 5");
    test_unsigned(42, "%05u", "Positive zero-padded width 5");
    test_unsigned(2147483647, "%015u", "Large value zero-padded width 15");
    test_unsigned(4294967295u, "%015u", "UINT_MAX zero-padded width 15");
    
    // PRECISION TESTS
    run_category("Precision Tests");
    
    // Test precision
    test_unsigned(0, "%.0u", "Zero with precision 0");
    test_unsigned(0, "%.u", "Zero with precision '.'");
    test_unsigned(42, "%.5u", "Positive with precision 5");
    test_unsigned(2147483647, "%.10u", "Large value with precision 10");
    test_unsigned(4294967295u, "%.10u", "UINT_MAX with precision 10");
    
    // WIDTH AND PRECISION COMBINED
    run_category("Width and Precision Combined");
    
    // Test width and precision together
    test_unsigned(0, "%10.5u", "Zero width 10 precision 5");
    test_unsigned(42, "%10.5u", "Positive width 10 precision 5");
    test_unsigned(2147483647, "%15.10u", "Large value width 15 precision 10");
    test_unsigned(4294967295u, "%15.10u", "UINT_MAX width 15 precision 10");
    
    // LEFT-JUSTIFY, WIDTH, AND PRECISION
    run_category("Left-Justify, Width, and Precision");
    
    // Test left-justify with width and precision
    test_unsigned(0, "%-10.5u", "Zero left-justified width 10 precision 5");
    test_unsigned(42, "%-10.5u", "Positive left-justified width 10 precision 5");
    test_unsigned(2147483647, "%-15.10u", "Large value left-justified width 15 precision 10");
    test_unsigned(4294967295u, "%-15.10u", "UINT_MAX left-justified width 15 precision 10");
    
    // PLUS FLAG TESTS (should have no effect on unsigned)
    run_category("Plus Flag Tests");
    
    // Test plus flag (should be ignored for %u)
    test_unsigned(0, "%+u", "Zero with plus flag");
    test_unsigned(42, "%+u", "Positive with plus flag");
    test_unsigned(4294967295u, "%+u", "UINT_MAX with plus flag");
    
    // SPACE FLAG TESTS (should have no effect on unsigned)
    run_category("Space Flag Tests");
    
    // Test space flag (should be ignored for %u)
    test_unsigned(0, "% u", "Zero with space flag");
    test_unsigned(42, "% u", "Positive with space flag");
    test_unsigned(4294967295u, "% u", "UINT_MAX with space flag");
    
    // HASH FLAG TESTS (should have no effect on unsigned)
    run_category("Hash Flag Tests");
    
    // Test hash flag (should be ignored for %u)
    test_unsigned(0, "%#u", "Zero with hash flag");
    test_unsigned(42, "%#u", "Positive with hash flag");
    test_unsigned(4294967295u, "%#u", "UINT_MAX with hash flag");
    
    // COMBINED FLAG TESTS
    run_category("Combined Flag Tests");
    
    test_unsigned(42, "%+05u", "Plus and zero padding");
    test_unsigned(42, "%+ u", "Plus and space");
    test_unsigned(42, "%+#u", "Plus and hash");
    test_unsigned(42, "% 05u", "Space and zero padding");
    test_unsigned(42, "% #u", "Space and hash");
    test_unsigned(42, "%#05u", "Hash and zero padding");
    test_unsigned(42, "%+0#5u", "Plus, hash, and zero padding");
    test_unsigned(42, "%+ #u", "Plus, space, and hash");
    
    // COMPLEX COMBINATIONS
    run_category("Complex Combinations");
    
    test_unsigned(0, "%+10.5u", "Zero plus flag width 10 precision 5");
    test_unsigned(42, "%+10.5u", "Positive plus flag width 10 precision 5");
    test_unsigned(0, "% 10.5u", "Zero space flag width 10 precision 5");
    test_unsigned(42, "% 10.5u", "Positive space flag width 10 precision 5");
    test_unsigned(42, "%+-10.5u", "Positive plus flag left-justified width 10 precision 5");
    test_unsigned(42, "% -10.5u", "Positive space flag left-justified width 10 precision 5");
    test_unsigned(42, "%+010u", "Positive plus flag zero-padded width 10");
    test_unsigned(42, "% 010u", "Positive space flag zero-padded width 10");
    
    // EXTREME CASES
    run_category("Extreme Cases");
    
    // Edge cases
    test_unsigned(0, "%.0u", "Zero with precision 0");
    test_unsigned(0, "%0.0u", "Zero with zero padding and precision 0");
    test_unsigned(0, "%5.0u", "Zero with width 5 and precision 0");
    test_unsigned(4294967295u, "%50u", "UINT_MAX with very large width");
    test_unsigned(4294967295u, "%.50u", "UINT_MAX with very large precision");
    test_unsigned(4294967295u, "%50.50u", "UINT_MAX with very large width and precision");
    test_unsigned(4294967295u, "%.0u", "UINT_MAX with precision 0");
    
    // Print final summary
    print_summary();
    
    return fail_count > 0 ? 1 : 0;
}
