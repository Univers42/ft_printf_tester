/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_tests_extended.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:45 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/05 14:05:22 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"

int main(void) {
    printf("%s=== FT_PRINTF EXTENDED INTEGER TESTS ===%s\n", MAGENTA, RESET);
    run_category("Basic Integer Tests");
    test_int(0, "%d", "Zero");
    test_int(1, "%d", "One");
    test_int(-1, "%d", "Negative one");
    test_int(42, "%d", "Positive small");
    test_int(-42, "%d", "Negative small");
    test_int(2147483647, "%d", "INT_MAX");
    test_int(-2147483648, "%d", "INT_MIN");
    run_category("Format %i Tests");
    test_int(0, "%i", "Zero with %i");
    test_int(1, "%i", "One with %i");
    test_int(-1, "%i", "Negative one with %i");
    test_int(42, "%i", "Positive small with %i");
    test_int(-42, "%i", "Negative small with %i");
    test_int(2147483647, "%i", "INT_MAX with %i");
    test_int(-2147483648, "%i", "INT_MIN with %i");
    run_category("Width Tests");
    test_int(0, "%5d", "Zero with width 5");
    test_int(42, "%5d", "Positive with width 5");
    test_int(-42, "%5d", "Negative with width 5");
    test_int(INT_MAX, "%15d", "INT_MAX with width 15");
    test_int(INT_MIN, "%15d", "INT_MIN with width 15");
    run_category("Left-Justify Tests");
    test_int(0, "%-5d", "Zero left-justified width 5");
    test_int(42, "%-5d", "Positive left-justified width 5");
    test_int(-42, "%-5d", "Negative left-justified width 5");
    test_int(INT_MAX, "%-15d", "INT_MAX left-justified width 15");
    test_int(INT_MIN, "%-15d", "INT_MIN left-justified width 15");
    run_category("Zero-Padding Tests");
    test_int(0, "%05d", "Zero zero-padded width 5");
    test_int(42, "%05d", "Positive zero-padded width 5");
    test_int(-42, "%05d", "Negative zero-padded width 5");
    test_int(INT_MAX, "%015d", "INT_MAX zero-padded width 15");
    test_int(INT_MIN, "%015d", "INT_MIN zero-padded width 15");
    run_category("Precision Tests");
    test_int(0, "%.0d", "Zero with precision 0");
    test_int(0, "%.d", "Zero with precision '.'");
    test_int(42, "%.5d", "Positive with precision 5");
    test_int(-42, "%.5d", "Negative with precision 5");
    test_int(INT_MAX, "%.10d", "INT_MAX with precision 10");
    test_int(INT_MIN, "%.10d", "INT_MIN with precision 10");
    run_category("Width and Precision Combined");
    test_int(0, "%10.5d", "Zero width 10 precision 5");
    test_int(42, "%10.5d", "Positive width 10 precision 5");
    test_int(-42, "%10.5d", "Negative width 10 precision 5");
    test_int(INT_MAX, "%15.10d", "INT_MAX width 15 precision 10");
    test_int(INT_MIN, "%15.10d", "INT_MIN width 15 precision 10");
    run_category("Left-Justify, Width, and Precision");
    test_int(0, "%-10.5d", "Zero left-justified width 10 precision 5");
    test_int(42, "%-10.5d", "Positive left-justified width 10 precision 5");
    test_int(-42, "%-10.5d", "Negative left-justified width 10 precision 5");
    test_int(INT_MAX, "%-15.10d", "INT_MAX left-justified width 15 precision 10");
    test_int(INT_MIN, "%-15.10d", "INT_MIN left-justified width 15 precision 10");
    run_category("Plus Flag Tests");
    test_int(0, "%+d", "Zero with plus flag");
    test_int(42, "%+d", "Positive with plus flag");
    test_int(-42, "%+d", "Negative with plus flag");
    test_int(INT_MAX, "%+d", "INT_MAX with plus flag");
    test_int(INT_MIN, "%+d", "INT_MIN with plus flag");
    run_category("Space Flag Tests");
    test_int(0, "% d", "Zero with space flag");
    test_int(42, "% d", "Positive with space flag");
    test_int(-42, "% d", "Negative with space flag");
    test_int(INT_MAX, "% d", "INT_MAX with space flag");
    test_int(INT_MIN, "% d", "INT_MIN with space flag");
    run_category("Complex Combinations");
    test_int(0, "%+10.5d", "Zero plus flag width 10 precision 5");
    test_int(42, "%+10.5d", "Positive plus flag width 10 precision 5");
    test_int(-42, "%+10.5d", "Negative plus flag width 10 precision 5");
    test_int(0, "% 10.5d", "Zero space flag width 10 precision 5");
    test_int(42, "% 10.5d", "Positive space flag width 10 precision 5");
    test_int(-42, "% 10.5d", "Negative space flag width 10 precision 5");
    test_int(42, "%+-10.5d", "Positive plus flag left-justified width 10 precision 5");
    test_int(-42, "%+-10.5d", "Negative plus flag left-justified width 10 precision 5");
    test_int(42, "% -10.5d", "Positive space flag left-justified width 10 precision 5");
    test_int(-42, "% -10.5d", "Negative space flag left-justified width 10 precision 5");
    test_int(42, "%+010d", "Positive plus flag zero-padded width 10");
    test_int(-42, "%+010d", "Negative plus flag zero-padded width 10");
    test_int(42, "% 010d", "Positive space flag zero-padded width 10");
    test_int(-42, "% 010d", "Negative space flag zero-padded width 10");
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
