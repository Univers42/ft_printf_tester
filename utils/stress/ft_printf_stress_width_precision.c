/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_width_precision.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/17 19:15:39 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf_stress.h"

/* Width formatting tests */
void test_width(void)
{
    printf("\n===== WIDTH TESTS =====\n");
    
    // Width with different types
    int int_val = 42;
    char *str_val = "Hello";
    char char_val = 'A';
    unsigned int hex_val = 0xABCDEF;
    
    // Pass pointers or addresses of values
    stress_test_format("%10d", "Width with int", &int_val, 'i');
    stress_test_format("%10s", "Width with string", str_val, 's');
    stress_test_format("%10c", "Width with char", &char_val, 'c');
    stress_test_format("%10x", "Width with hex", &hex_val, 'x');
    
    // Variable widths
    stress_test_format("%1d", "Width 1", &int_val, 'i');
    stress_test_format("%20d", "Width 20", &int_val, 'i');
    stress_test_format("%50d", "Width 50", &int_val, 'i');
    
    // Add extreme width tests
    char *str_val_extreme = "abc";
    unsigned int hex_val_extreme = 0xabc;
    
    // Very large widths
    stress_test_format("%100d", "Width 100", &int_val, 'd');
    stress_test_format("%500s", "Width 500", str_val_extreme, 's');
    
    // Zero width for comparison
    stress_test_format("%0d", "Zero width", &int_val, 'd');
    
    // Width with many flags
    stress_test_format("%+-#050x", "All flags with width", &hex_val_extreme, 'x');
}

/* Precision formatting tests */
void test_precision(void)
{
    printf("\n===== PRECISION TESTS =====\n");
    
    // Precision with different types
    int int_val = 42;
    char *str_val = "Hello World";
    int zero_val = 0;
    
    // Pass pointers or addresses of values
    stress_test_format("%.5d", "Precision with int", &int_val, 'i');
    stress_test_format("%.5s", "Precision with string", str_val, 's');
    
    // Variable precisions
    stress_test_format("%.1d", "Precision 1", &int_val, 'i');
    stress_test_format("%.10d", "Precision 10", &int_val, 'i');
    
    // Zero precision special cases
    stress_test_format("%.0d", "Zero precision with 0", &zero_val, 'i');
    stress_test_format("%.0d", "Zero precision with non-zero", &int_val, 'i');
    
    // Extreme precision tests
    int int_val_extreme = 123456;
    char *str_val_extreme = "This is a long string to test precision limits";
    
    stress_test_format("%.20d", "Large precision with int", &int_val_extreme, 'd');
    stress_test_format("%.50s", "Large precision with string", str_val_extreme, 's');
    
    // Special cases
    stress_test_format("%10.0d", "Width with zero precision", &int_val_extreme, 'd');
    stress_test_format("%10.s", "Width with empty precision", str_val_extreme, 's');
    
    // Test the effect of precision on different values
    int zero = 0;
    stress_test_format("%.0d", "Zero precision with zero", &zero, 'd');
    stress_test_format("%.d", "Empty precision with zero", &zero, 'd');
}
