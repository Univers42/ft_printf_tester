/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_basic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/17 19:15:19 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf_stress.h"

/* Basic test suite with direct function calls */
void run_basic_tests(void)
{
    printf("\n===== BASIC FUNCTIONALITY =====\n");
    
    // Simple text test
    test_simple("Hello, world!", "Simple text");
    
    // Basic type tests
    test_simple("%c", "Character", 'A');
    test_simple("%s", "String", "Hello");
    test_simple("%d", "Integer", 42);
    test_simple("%i", "Integer alternative", -42);
    test_simple("%u", "Unsigned integer", 4294967295u);
    test_simple("%x", "Hex lowercase", 0xabcdef);
    test_simple("%X", "Hex uppercase", 0xABCDEF);
    test_simple("%p", "Pointer", (void*)0x1234);
    test_simple("%%", "Percent sign");
    
    // String edge cases
    test_simple("Empty: %s", "Empty string", "");
    
    // NULL string test using a variable to avoid compiler warnings
    char *null_str = NULL;
    test_simple("NULL: %s", "NULL string", null_str);
}

/* Run flag stress tests */
void run_flag_stress_tests(void)
{
    printf("\n===== FLAG STRESS TESTS =====\n");
    
    // Sign flags with integers
    test_simple("%+d", "Plus sign with positive", 42);
    test_simple("%+d", "Plus sign with negative", -42);
    test_simple("% d", "Space flag with positive", 42);
    test_simple("% d", "Space flag with negative", -42);
    
    // Hash flags with hex
    test_simple("%#x", "Hash with hex", 42);
    test_simple("%#X", "Hash with HEX", 42);
    
    // Width and justification
    int int_val = 42;
    unsigned int hex_val = 42;
    
    stress_test_format("%-10d", "Left-justify flag", &int_val, 'd');
    stress_test_format("%010d", "Zero-padding flag", &int_val, 'd');
    
    // Flag combinations
    stress_test_format("%+010d", "Plus with zero padding", &int_val, 'd');
    stress_test_format("% #x", "Space with hash", &hex_val, 'x');
    stress_test_format("%#10X", "Hash with width", &hex_val, 'X');
    
    // Additional complex flag combinations
    stress_test_format("%+-10.5d", "Plus-minus with width & precision", &int_val, 'd');
    stress_test_format("%0+10.5d", "Zero-plus with width & precision", &int_val, 'd');
    stress_test_format("%0+#10.5x", "Zero-plus-hash with width & precision", &hex_val, 'x');
    stress_test_format("%-#10.5X", "Minus-hash with width & precision", &hex_val, 'X');
}
