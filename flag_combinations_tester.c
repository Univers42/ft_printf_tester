/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_combinations_tester.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:24 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:16:25 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"

// Test flag combinations for a specific conversion type
void test_flags_for_conversion(char type, void *test_value) {
    char format[20];
    char test_desc[100];
    int widths[] = {0, 1, 5, 10}; // Different field widths to test
    int precisions[] = {0, 1, 5, 10}; // Different precisions to test
    
    // Skip precision for types where it doesn't apply meaningfully
    int skip_precision = (type == 'c' || type == 'p' || type == '%');
    
    // Set up the conversion character
    char conv[2] = {type, '\0'};
    
    // Test all combinations of flags
    for (int width_idx = 0; width_idx < 4; width_idx++) {
        int width = widths[width_idx];
        
        // No flags, just width
        if (width > 0) {
            sprintf(format, "%%%d%s", width, conv);
            sprintf(test_desc, "Width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        
        // Left align flag with width
        if (width > 0) {
            sprintf(format, "%%-%d%s", width, conv);
            sprintf(test_desc, "Left-aligned width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        
        // Zero padding flag with width (doesn't make sense for some types)
        if (width > 0 && type != 's' && type != 'p' && type != '%') {
            sprintf(format, "%%0%d%s", width, conv);
            sprintf(test_desc, "Zero-padded width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        
        // Left align with zero padding (left align takes precedence)
        if (width > 0 && type != 's' && type != 'p' && type != '%') {
            sprintf(format, "%%-0%d%s", width, conv);
            sprintf(test_desc, "Left-aligned zero-padded width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        
        if (!skip_precision) {
            // Test with precision but no width
            for (int prec_idx = 0; prec_idx < 4; prec_idx++) {
                int precision = precisions[prec_idx];
                
                sprintf(format, "%%.%d%s", precision, conv);
                sprintf(test_desc, "Precision %d with type %%%s", precision, conv);
                test_format(format, test_desc, test_value, type);
                
                // With width and precision
                if (width > 0) {
                    // Width and precision
                    sprintf(format, "%%%d.%d%s", width, precision, conv);
                    sprintf(test_desc, "Width %d, precision %d with type %%%s", 
                            width, precision, conv);
                    test_format(format, test_desc, test_value, type);
                    
                    // Left align, width and precision
                    sprintf(format, "%%-%d.%d%s", width, precision, conv);
                    sprintf(test_desc, "Left-aligned width %d, precision %d with type %%%s", 
                            width, precision, conv);
                    test_format(format, test_desc, test_value, type);
                    
                    // Zero padding, width and precision (precision should override zero padding)
                    if (type != 's') {
                        sprintf(format, "%%0%d.%d%s", width, precision, conv);
                        sprintf(test_desc, "Zero-padded width %d, precision %d with type %%%s", 
                                width, precision, conv);
                        test_format(format, test_desc, test_value, type);
                    }
                    
                    // All flags: left align, zero padding, width, precision
                    if (type != 's') {
                        sprintf(format, "%%-0%d.%d%s", width, precision, conv);
                        sprintf(test_desc, "Left-aligned zero-padded width %d, precision %d with type %%%s", 
                                width, precision, conv);
                        test_format(format, test_desc, test_value, type);
                    }
                }
            }
        }
    }
}

int main(void) {
    printf("%s=== FT_PRINTF FLAG & WIDTH COMBINATIONS TESTER ===%s\n", MAGENTA, RESET);
    
    // Test values for each type
    char c_val = 'X';
    char *s_val = "Hello";
    char *s_empty = "";
    char *s_null = NULL;
    int d_pos = 42;
    int d_neg = -42;
    int d_zero = 0;
    unsigned int u_val = 4294967295u; // UINT_MAX
    unsigned int x_val = 0xabcdef;
    void *p_val = &d_pos;
    void *p_null = NULL;
    
    // Character tests
    run_category("Character Format Tests");
    test_flags_for_conversion('c', &c_val);
    
    // String tests
    run_category("String Format Tests");
    test_flags_for_conversion('s', s_val);
    run_category("Empty String Tests");
    test_flags_for_conversion('s', s_empty);
    run_category("NULL String Tests");
    test_flags_for_conversion('s', s_null);
    
    // Integer tests
    run_category("Positive Integer Tests");
    test_flags_for_conversion('d', &d_pos);
    run_category("Negative Integer Tests");
    test_flags_for_conversion('d', &d_neg);
    run_category("Zero Integer Tests");
    test_flags_for_conversion('d', &d_zero);
    
    // Identical i format
    run_category("Positive Integer Tests (%%i)");
    test_flags_for_conversion('i', &d_pos);
    
    // Unsigned tests
    run_category("Unsigned Integer Tests");
    test_flags_for_conversion('u', &u_val);
    
    // Hex lowercase tests
    run_category("Hex Lowercase Tests");
    test_flags_for_conversion('x', &x_val);
    
    // Hex uppercase tests
    run_category("Hex Uppercase Tests");
    test_flags_for_conversion('X', &x_val);
    
    // Pointer tests
    run_category("Pointer Tests");
    test_flags_for_conversion('p', p_val);
    run_category("NULL Pointer Tests");
    test_flags_for_conversion('p', p_null);
    
    // Percent sign tests
    run_category("Percent Sign Tests");
    test_flags_for_conversion('%', NULL);
    
    // Print final summary
    print_summary();

    return fail_count > 0 ? 1 : 0;
}
