/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_combinations_tester.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:24 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 15:34:04 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "headers/controller.h"

void test_flags_for_conversion(char type, void *test_value) {
    char format[20];
    char test_desc[100];
    int widths[] = {0, 1, 5, 10}; 
    int precisions[] = {0, 1, 5, 10}; 
    int skip_precision = (type == 'c' || type == 'p' || type == '%');
    char conv[2] = {type, '\0'};
    for (int width_idx = 0; width_idx < 4; width_idx++) {
        int width = widths[width_idx];
        if (width > 0)
        {
            sprintf(format, "%%%d%s", width, conv);
            sprintf(test_desc, "Width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        if (width > 0)
        {
            sprintf(format, "%%-%d%s", width, conv);
            sprintf(test_desc, "Left-aligned width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        if (width > 0 && type != 's' && type != 'p' && type != '%') {
            sprintf(format, "%%0%d%s", width, conv);
            sprintf(test_desc, "Zero-padded width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        if (width > 0 && type != 's' && type != 'p' && type != '%') {
            sprintf(format, "%%-0%d%s", width, conv);
            sprintf(test_desc, "Left-aligned zero-padded width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        if (!skip_precision)
        {
            for (int prec_idx = 0; prec_idx < 4; prec_idx++)
            {
                int precision = precisions[prec_idx];
                sprintf(format, "%%.%d%s", precision, conv);
                sprintf(test_desc, "Precision %d with type %%%s", precision, conv);
                test_format(format, test_desc, test_value, type);
                if (width > 0)
                {
                    sprintf(format, "%%%d.%d%s", width, precision, conv);
                    sprintf(test_desc, "Width %d, precision %d with type %%%s", 
                            width, precision, conv);
                    test_format(format, test_desc, test_value, type);
                    sprintf(format, "%%-%d.%d%s", width, precision, conv);
                    sprintf(test_desc, "Left-aligned width %d, precision %d with type %%%s", 
                            width, precision, conv);
                    test_format(format, test_desc, test_value, type);
                    if (type != 's')
                    {
                        sprintf(format, "%%0%d.%d%s", width, precision, conv);
                        sprintf(test_desc, "Zero-padded width %d, precision %d with type %%%s", 
                                width, precision, conv);
                        test_format(format, test_desc, test_value, type);
                    }
                    if (type != 's')
                    {
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
    char c_val = 'X';
    char *s_val = "Hello";
    char *s_empty = "";
    char *s_null = NULL;
    int d_pos = 42;
    int d_neg = -42;
    int d_zero = 0;
    unsigned int u_val = 4294967295u; 
    unsigned int x_val = 0xabcdef;
    void *p_val = &d_pos;
    void *p_null = NULL;
    
    
    printf("%s=== FT_PRINTF FLAG & WIDTH COMBINATIONS TESTER ===%s\n", MAGENTA, RESET);
    run_category("Character Format Tests");
    test_flags_for_conversion('c', &c_val);
    run_category("String Format Tests");
    test_flags_for_conversion('s', s_val);
    run_category("Empty String Tests");
    test_flags_for_conversion('s', s_empty);
    run_category("NULL String Tests");
    test_flags_for_conversion('s', s_null);
    run_category("Positive Integer Tests");
    test_flags_for_conversion('d', &d_pos);
    run_category("Negative Integer Tests");
    test_flags_for_conversion('d', &d_neg);
    run_category("Zero Integer Tests");
    test_flags_for_conversion('d', &d_zero);
    run_category("Positive Integer Tests (%%i)");
    test_flags_for_conversion('i', &d_pos);
    run_category("Unsigned Integer Tests");
    test_flags_for_conversion('u', &u_val);
    run_category("Hex Lowercase Tests");
    test_flags_for_conversion('x', &x_val);
    run_category("Hex Uppercase Tests");
    test_flags_for_conversion('X', &x_val);
    run_category("Pointer Tests");
    test_flags_for_conversion('p', p_val);
    run_category("NULL Pointer Tests");
    test_flags_for_conversion('p', p_null);
    run_category("Percent Sign Tests");
    test_flags_for_conversion('%', NULL);
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
