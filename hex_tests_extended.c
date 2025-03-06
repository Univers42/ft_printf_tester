/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_tests_extended.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:40 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 15:23:08 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "headers/controller.h"

int main(void)
{
    printf("%s=== FT_PRINTF EXTENDED HEXADECIMAL TESTS ===%s\n", MAGENTA, RESET);
    run_category("Basic Lowercase Hex Tests");
    test_hex(0, 0, "%x", "Zero");
    test_hex(1, 0, "%x", "One");
    test_hex(10, 0, "%x", "Ten");
    test_hex(15, 0, "%x", "Fifteen");
    test_hex(16, 0, "%x", "Sixteen");
    test_hex(42, 0, "%x", "Forty-Two");
    test_hex(0xabcdef, 0, "%x", "Large value");
    test_hex(0xffffff, 0, "%x", "Maximum 24-bit value");
    test_hex(UINT_MAX, 0, "%x", "UINT_MAX");
    run_category("Basic Uppercase Hex Tests");
    test_hex(0, 1, "%X", "Zero");
    test_hex(1, 1, "%X", "One");
    test_hex(10, 1, "%X", "Ten");
    test_hex(15, 1, "%X", "Fifteen");
    test_hex(16, 1, "%X", "Sixteen");
    test_hex(42, 1, "%X", "Forty-Two");
    test_hex(0xabcdef, 1, "%X", "Large value");
    test_hex(0xffffff, 1, "%X", "Maximum 24-bit value");
    test_hex(UINT_MAX, 1, "%X", "UINT_MAX");
    run_category("Width Tests");
    test_hex(0, 0, "%5x", "Zero with width 5");
    test_hex(42, 0, "%5x", "Forty-Two with width 5");
    test_hex(0xabc, 0, "%10x", "0xabc with width 10");
    test_hex(0xabcdef, 0, "%15x", "Large value with width 15");
    test_hex(0, 1, "%5X", "Zero with width 5 (uppercase)");
    test_hex(42, 1, "%5X", "Forty-Two with width 5 (uppercase)");
    test_hex(0xabc, 1, "%10X", "0xabc with width 10 (uppercase)");
    test_hex(0xabcdef, 1, "%15X", "Large value with width 15 (uppercase)");
    run_category("Left-Justify Tests");
    test_hex(0, 0, "%-5x", "Zero left-justified width 5");
    test_hex(42, 0, "%-5x", "Forty-Two left-justified width 5");
    test_hex(0xabc, 0, "%-10x", "0xabc left-justified width 10");
    test_hex(0xabcdef, 0, "%-15x", "Large value left-justified width 15");
    test_hex(0, 1, "%-5X", "Zero left-justified width 5 (uppercase)");
    test_hex(42, 1, "%-5X", "Forty-Two left-justified width 5 (uppercase)");
    test_hex(0xabc, 1, "%-10X", "0xabc left-justified width 10 (uppercase)");
    test_hex(0xabcdef, 1, "%-15X", "Large value left-justified width 15 (uppercase)");
    run_category("Zero-Padding Tests");
    test_hex(0, 0, "%05x", "Zero zero-padded width 5");
    test_hex(42, 0, "%05x", "Forty-Two zero-padded width 5");
    test_hex(0xabc, 0, "%010x", "0xabc zero-padded width 10");
    test_hex(0xabcdef, 0, "%015x", "Large value zero-padded width 15");
    test_hex(0, 1, "%05X", "Zero zero-padded width 5 (uppercase)");
    test_hex(42, 1, "%05X", "Forty-Two zero-padded width 5 (uppercase)");
    test_hex(0xabc, 1, "%010X", "0xabc zero-padded width 10 (uppercase)");
    test_hex(0xabcdef, 1, "%015X", "Large value zero-padded width 15 (uppercase)");
    run_category("Precision Tests");
    test_hex(0, 0, "%.0x", "Zero with precision 0");
    test_hex(0, 0, "%.x", "Zero with precision '.'");
    test_hex(42, 0, "%.5x", "Forty-Two with precision 5");
    test_hex(0xabc, 0, "%.10x", "0xabc with precision 10");
    test_hex(0, 1, "%.0X", "Zero with precision 0 (uppercase)");
    test_hex(0, 1, "%.X", "Zero with precision '.' (uppercase)");
    test_hex(42, 1, "%.5X", "Forty-Two with precision 5 (uppercase)");
    test_hex(0xabc, 1, "%.10X", "0xabc with precision 10 (uppercase)");
    run_category("Width and Precision Combined");
    test_hex(0, 0, "%10.5x", "Zero width 10 precision 5");
    test_hex(42, 0, "%10.5x", "Forty-Two width 10 precision 5");
    test_hex(0xabc, 0, "%10.15x", "0xabc width 10 precision 15");
    test_hex(0xabcdef, 0, "%15.10x", "Large value width 15 precision 10");
    test_hex(0, 1, "%10.5X", "Zero width 10 precision 5 (uppercase)");
    test_hex(42, 1, "%10.5X", "Forty-Two width 10 precision 5 (uppercase)");
    test_hex(0xabc, 1, "%10.15X", "0xabc width 10 precision 15 (uppercase)");
    test_hex(0xabcdef, 1, "%15.10X", "Large value width 15 precision 10 (uppercase)");
    run_category("Left-Justify, Width, and Precision");
    test_hex(0, 0, "%-10.5x", "Zero left-justified width 10 precision 5");
    test_hex(42, 0, "%-10.5x", "Forty-Two left-justified width 10 precision 5");
    test_hex(0xabc, 0, "%-10.15x", "0xabc left-justified width 10 precision 15");
    test_hex(0xabcdef, 0, "%-15.10x", "Large value left-justified width 15 precision 10");
    test_hex(0, 1, "%-10.5X", "Zero left-justified width 10 precision 5 (uppercase)");
    test_hex(42, 1, "%-10.5X", "Forty-Two left-justified width 10 precision 5 (uppercase)");
    test_hex(0xabc, 1, "%-10.15X", "0xabc left-justified width 10 precision 15 (uppercase)");
    test_hex(0xabcdef, 1, "%-15.10X", "Large value left-justified width 15 precision 10 (uppercase)");
    run_category("Hash Flag Tests");
    test_hex(0, 0, "%#x", "Zero with hash flag");
    test_hex(42, 0, "%#x", "Forty-Two with hash flag");
    test_hex(0xabc, 0, "%#x", "0xabc with hash flag");
    test_hex(0xabcdef, 0, "%#x", "Large value with hash flag");
    test_hex(0, 1, "%#X", "Zero with hash flag (uppercase)");
    test_hex(42, 1, "%#X", "Forty-Two with hash flag (uppercase)");
    test_hex(0xabc, 1, "%#X", "0xabc with hash flag (uppercase)");
    test_hex(0xabcdef, 1, "%#X", "Large value with hash flag (uppercase)");
    run_category("Hash Flag with Width");
    test_hex(0, 0, "%#10x", "Zero hash flag width 10");
    test_hex(42, 0, "%#10x", "Forty-Two hash flag width 10");
    test_hex(0xabc, 0, "%#10x", "0xabc hash flag width 10");
    test_hex(0xabcdef, 0, "%#15x", "Large value hash flag width 15");
    test_hex(0, 1, "%#10X", "Zero hash flag width 10 (uppercase)");
    test_hex(42, 1, "%#10X", "Forty-Two hash flag width 10 (uppercase)");
    test_hex(0xabc, 1, "%#10X", "0xabc hash flag width 10 (uppercase)");
    test_hex(0xabcdef, 1, "%#15X", "Large value hash flag width 15 (uppercase)");
    run_category("Hash Flag with Zero Padding");
    test_hex(0, 0, "%#010x", "Zero hash flag zero-padded width 10");
    test_hex(42, 0, "%#010x", "Forty-Two hash flag zero-padded width 10");
    test_hex(0xabc, 0, "%#010x", "0xabc hash flag zero-padded width 10");
    test_hex(0xabcdef, 0, "%#015x", "Large value hash flag zero-padded width 15");
    test_hex(0, 1, "%#010X", "Zero hash flag zero-padded width 10 (uppercase)");
    test_hex(42, 1, "%#010X", "Forty-Two hash flag zero-padded width 10 (uppercase)");
    test_hex(0xabc, 1, "%#010X", "0xabc hash flag zero-padded width 10 (uppercase)");
    test_hex(0xabcdef, 1, "%#015X", "Large value hash flag zero-padded width 15 (uppercase)");
    run_category("Hash Flag with Left-Justify");
    test_hex(0, 0, "%#-10x", "Zero hash flag left-justified width 10");
    test_hex(42, 0, "%#-10x", "Forty-Two hash flag left-justified width 10");
    test_hex(0xabc, 0, "%#-10x", "0xabc hash flag left-justified width 10");
    test_hex(0xabcdef, 0, "%#-15x", "Large value hash flag left-justified width 15");
    test_hex(0, 1, "%#-10X", "Zero hash flag left-justified width 10 (uppercase)");
    test_hex(42, 1, "%#-10X", "Forty-Two hash flag left-justified width 10 (uppercase)");
    test_hex(0xabc, 1, "%#-10X", "0xabc hash flag left-justified width 10 (uppercase)");
    test_hex(0xabcdef, 1, "%#-15X", "Large value hash flag left-justified width 15 (uppercase)");
    run_category("Hash Flag with Precision");
    test_hex(0, 0, "%#.0x", "Zero hash flag precision 0");
    test_hex(0, 0, "%#.x", "Zero hash flag precision '.'");
    test_hex(42, 0, "%#.5x", "Forty-Two hash flag precision 5");
    test_hex(0xabc, 0, "%#.10x", "0xabc hash flag precision 10");
    test_hex(0, 1, "%#.0X", "Zero hash flag precision 0 (uppercase)");
    test_hex(0, 1, "%#.X", "Zero hash flag precision '.' (uppercase)");
    test_hex(42, 1, "%#.5X", "Forty-Two hash flag precision 5 (uppercase)");
    test_hex(0xabc, 1, "%#.10X", "0xabc hash flag precision 10 (uppercase)");
    run_category("Hash Flag with Width and Precision");
    test_hex(0, 0, "%#10.5x", "Zero hash flag width 10 precision 5");
    test_hex(42, 0, "%#10.5x", "Forty-Two hash flag width 10 precision 5");
    test_hex(0xabc, 0, "%#10.15x", "0xabc hash flag width 10 precision 15");
    test_hex(0xabcdef, 0, "%#15.10x", "Large value hash flag width 15 precision 10");
    test_hex(0, 1, "%#10.5X", "Zero hash flag width 10 precision 5 (uppercase)");
    test_hex(42, 1, "%#10.5X", "Forty-Two hash flag width 10 precision 5 (uppercase)");
    test_hex(0xabc, 1, "%#10.15X", "0xabc hash flag width 10 precision 15 (uppercase)");
    test_hex(0xabcdef, 1, "%#15.10X", "Large value hash flag width 15 precision 10 (uppercase)");
    run_category("Complex Combinations");
    test_hex(0xabcdef, 0, "%#-15.10x", "Complex test 1");
    test_hex(0xabcdef, 1, "%#-15.10X", "Complex test 2");
    test_hex(0xabcdef, 0, "%#015.10x", "Complex test 3");
    test_hex(0xabcdef, 1, "%#015.10X", "Complex test 4");
    test_hex(0, 0, "%#-15.10x", "Complex test 5");
    test_hex(0, 1, "%#-15.10X", "Complex test 6");
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
