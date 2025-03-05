/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tests_extended.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:18:17 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/05 14:14:03 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"
#include <string.h>

int main(void) {
    char binary_data[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    
    printf("%s=== FT_PRINTF EXTENDED STRING TESTS ===%s\n", MAGENTA, RESET);
    run_category("Basic String Tests");
    test_string("Hello, World!", "%s", "Basic string");
    test_string("", "%s", "Empty string");
    test_string(NULL, "%s", "NULL string");
    run_category("Special String Tests");
    test_string("Hello\nWorld", "%s", "String with newline");
    test_string("Hello\tWorld", "%s", "String with tab");
    test_string("Hello\\World", "%s", "String with backslash");
    test_string("Hello\"World", "%s", "String with quotes");
    test_string("   Spaces   ", "%s", "String with spaces");
    run_category("Long String Tests");
    char long_string[1001];
    memset(long_string, 'A', 1000);
    long_string[1000] = '\0';
    test_string(long_string, "%s", "1000 character string");
    char mixed_long[1001] = {0};
    for (int i = 0; i < 1000; i++)
        mixed_long[i] = 32 + (i % 95);
    test_string(mixed_long, "%s", "Long string with mixed characters");
    run_category("Width Tests");
    test_string("Hello", "%10s", "Width 10 with 5-char string");
    test_string("Hello", "%5s", "Width 5 with 5-char string (exact fit)");
    test_string("Hello", "%3s", "Width 3 with 5-char string (truncation won't happen without precision)");
    test_string("", "%5s", "Width 5 with empty string");
    test_string(NULL, "%10s", "Width 10 with NULL string");
    run_category("Left-Justify Tests");
    test_string("Hello", "%-10s", "Left-justified width 10");
    test_string("Hello", "%-5s", "Left-justified width 5 (exact fit)");
    test_string("Hello", "%-3s", "Left-justified width 3");
    test_string("", "%-5s", "Left-justified width 5 with empty string");
    test_string(NULL, "%-10s", "Left-justified width 10 with NULL string");
    run_category("Precision Tests");
    test_string("Hello, World!", "%.5s", "Precision 5 (should truncate)");
    test_string("Hello, World!", "%.15s", "Precision 15 (no truncation)");
    test_string("Hello, World!", "%.0s", "Precision 0 (should print nothing)");
    test_string("Hello, World!", "%.s", "Precision '.' (should print nothing)");
    test_string("", "%.5s", "Precision 5 with empty string");
    test_string(NULL, "%.5s", "Precision 5 with NULL string");
    run_category("Width and Precision Combined");
    test_string("Hello, World!", "%15.5s", "Width 15, precision 5");
    test_string("Hello, World!", "%5.15s", "Width 5, precision 15");
    test_string("Hello, World!", "%5.5s", "Width 5, precision 5");
    test_string("Hello, World!", "%15.0s", "Width 15, precision 0");
    test_string("", "%10.5s", "Width 10, precision 5 with empty string");
    test_string(NULL, "%10.5s", "Width 10, precision 5 with NULL string");
    run_category("Left-Justify with Precision");
    test_string("Hello, World!", "%-15.5s", "Left-justified width 15, precision 5");
    test_string("Hello, World!", "%-5.15s", "Left-justified width 5, precision 15");
    test_string("Hello, World!", "%-5.5s", "Left-justified width 5, precision 5");
    test_string("Hello, World!", "%-15.0s", "Left-justified width 15, precision 0");
    test_string("", "%-10.5s", "Left-justified width 10, precision 5 with empty string");
    test_string(NULL, "%-10.5s", "Left-justified width 10, precision 5 with NULL string");
    run_category("Extreme Cases");
    test_string("Hello", "%1000s", "Width 1000");
    test_string("Hello", "%.1000s", "Precision 1000");
    test_string("Hello", "%1000.1000s", "Width 1000, precision 1000");
    test_string("Hello", "%-1000s", "Left-justified width 1000");
    test_string("Hello", "%-1000.1000s", "Left-justified width 1000, precision 1000");
    run_category("Flag Tests (Should be Ignored)");
    test_string("Hello", "%+s", "Plus flag (should be ignored)");
    test_string("Hello", "% s", "Space flag (should be ignored)");
    test_string("Hello", "%#s", "Hash flag (should be ignored)");
    test_string("Hello", "%0s", "Zero flag without width (should be ignored)");
    test_string("Hello", "%010s", "Zero padding (should be ignored)");
    test_string("Hello", "%+- #010s", "All flags (should print normally)");
    run_category("Multiple String Arguments");
    test_multiple_strings("%s %s", "Two strings", "Hello", "World");
    test_multiple_strings("%s %s %s", "Three strings", "The", "Quick", "Brown");
    test_multiple_strings("%10s %.5s", "Different formats", "Hello", "World");
    test_multiple_strings("%s %s %s %s %s", "Five strings", "This", "Is", "A", "String", "Test");
    run_category("Mixed Format Strings");
    test_multiple_strings("%s: %d", "String with integer", "Number", 42);
    test_multiple_strings("Char: %c, String: %s", "String with character", 'A', "Test");
    test_multiple_strings("%s: %x", "String with hex", "Hexadecimal", 255);
    test_multiple_strings("%s %s: %d, %u, %x, %c", "Complex mix", "This", "is", 42, 42u, 42, 'Z');
    run_category("Format String Edge Cases");
    test_string("%s", "%s", "Percent-s as content");
    test_string("%d", "%s", "Percent-d as content");
    test_string("%%s", "%s", "Double-percent-s as content");
    test_string("100%%", "%s", "Number with percent as content");
    run_category("Special Characters in Strings");
    test_string(binary_data, "%s", "Binary data with NULL bytes");
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
