/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debug_tester.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:00:00 by syzygy            #+#    #+#             */
/*   Updated: 2025/03/02 01:16:40 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"

void test_basic_functionality(void)
{
    printf("\n===== BASIC FUNCTIONALITY TESTS =====\n");
    
    run_test("Character", "%c", 'A');
    run_test("String", "%s", "Hello");
    run_test("String with NULL", "%s", NULL);
    run_test("Integer", "%d", 42);
    run_test("Negative integer", "%d", -42);
    run_test("Zero", "%d", 0);
    run_test("Unsigned integer", "%u", 42);
    run_test("Hexadecimal (lowercase)", "%x", 42);
    run_test("Hexadecimal (uppercase)", "%X", 42);
    run_test("Pointer", "%p", &test_basic_functionality);
    run_test("Percent sign", "%%");
}

void test_extended_functionality(void)
{
    printf("\n===== EXTENDED FUNCTIONALITY TESTS =====\n");
    
    // Width tests
    run_test("Width with integer", "%5d", 42);
    run_test("Width with string", "%10s", "Hello");
    run_test("Width with character", "%5c", 'A');
    
    // Left-justify tests
    run_test("Left-justify with integer", "%-5d", 42);
    run_test("Left-justify with string", "%-10s", "Hello");
    run_test("Left-justify with character", "%-5c", 'A');
    
    // Zero padding tests
    run_test("Zero padding with integer", "%05d", 42);
    run_test("Zero padding with negative", "%05d", -42);
    
    // Precision tests
    run_test("Precision with integer", "%.5d", 42);
    run_test("Precision with string", "%.3s", "Hello");
    run_test("Precision 0 with 0", "%.0d", 0);
    
    // Width and precision together
    run_test("Width and precision with integer", "%8.3d", 42);
    run_test("Width and precision with string", "%8.3s", "Hello");
}

void test_edge_cases(void)
{
    printf("\n===== EDGE CASE TESTS =====\n");
    
    // Integer edge cases
    run_test("INT_MAX", "%d", INT_MAX);
    run_test("INT_MIN", "%d", INT_MIN);
    run_test("UINT_MAX", "%u", UINT_MAX);
    
    // String edge cases
    run_test("Empty string", "%s", "");
    run_test("NULL string with precision", "%.3s", NULL);
    
    // Multiple format specifiers
    run_test("Multiple specifiers", "%c %s %d %x %p %%", 
             'A', "test", 42, 255, &test_edge_cases);
    
    // Mixed text with specifiers 
    run_test("Mixed text", "This is a %s with %d numbers and a %c character.", 
             "string", 42, '!');
}

int main(void)
{
    printf("===== FT_PRINTF DEBUG TESTER =====\n");
    
    test_basic_functionality();
    test_extended_functionality();
    test_edge_cases();
    
    print_summary();
    
    return (fail_count > 0) ? 1 : 0;
}
