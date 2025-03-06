/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_generic_tests.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 16:04:43 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/controller.h"

// Example of a function that might have used TestCategory
void run_test_by_category(printf_test_type_t category, void *value, const char *format)
{
    switch (category)
    {
        case CHAR_TEST:
            test_char(*(char*)value, format, "Character test");
            break;
        case STRING_TEST:
            test_string((char*)value, format, "String test");
            break;
        case INT_TEST:
            test_int(*(int*)value, format, "Integer test");
            break;
        case UINT_TEST:
            test_unsigned(*(unsigned int*)value, format, "Unsigned int test");
            break;
        case HEX_TEST:
            test_hex(*(unsigned int*)value, 0, format, "Hexadecimal test");
            break;
        case POINTER_TEST:
            test_pointer(value, format, "Pointer test");
            break;
        case PERCENT_TEST:
            test_string("", format, "Percent test");
            break;
        case MIXED_TEST:
            // Handle mixed test case
            break;
        case PRINTF_STRESS_TEST:
            // Handle stress test case
            break;
        default:
            printf("Unknown test category\n");
    }
}
