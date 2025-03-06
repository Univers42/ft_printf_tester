/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_tester.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 00:08:40 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/controller.h"
#include <inttypes.h>
#include <stddef.h>

/* Forward declarations */
void run_basic_tests(void);
void run_flag_stress_tests(void);
void test_width(void);
void test_precision(void);

/* ===== CORE TESTING UTILITY FUNCTIONS ===== */

/**
 * Simple test function with direct input values
 * Eliminates the need for specialized test functions for each type
 */
void test_simple(const char *format, const char *test_name, ...)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    va_list args, args_copy;
    
    va_start(args, test_name);
    va_copy(args_copy, args);
    
    // Get expected output using printf
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = vprintf(format, args);
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            expected[bytes_read] = '\0';
        close(pipe_fd[0]);
    } else {
        strcpy(expected, "PIPE_ERROR");
        expected_ret = -1;
    }
    
    // Get ft_printf output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        // Find the format specifier type
        const char *ptr = strchr(format, '%');
        if (ptr && *(ptr+1) != '%') {
            // Skip flags, width, precision
            ptr++;
            while (*ptr && (*ptr == '#' || *ptr == '0' || *ptr == '-' || 
                   *ptr == '+' || *ptr == ' ' || (*ptr >= '0' && *ptr <= '9') ||
                   *ptr == '.'))
                ptr++;
                
            // Extract the actual type
            if (*ptr) {
                switch (*ptr) {
                    case 'c': actual_ret = ft_printf(format, va_arg(args_copy, int)); break;
                    case 's': actual_ret = ft_printf(format, va_arg(args_copy, char*)); break;
                    case 'd':
                    case 'i': actual_ret = ft_printf(format, va_arg(args_copy, int)); break;
                    case 'u':
                    case 'x':
                    case 'X': actual_ret = ft_printf(format, va_arg(args_copy, unsigned int)); break;
                    case 'p': actual_ret = ft_printf(format, va_arg(args_copy, void*)); break;
                    default: actual_ret = ft_printf(format, va_arg(args_copy, int));
                }
            } else {
                actual_ret = ft_printf(format);
            }
        } else {
            // No format or just %% - no argument needed
            actual_ret = ft_printf(format);
        }
        
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            actual[bytes_read] = '\0';
        close(pipe_fd[0]);
    } else {
        strcpy(actual, "PIPE_ERROR");
        actual_ret = -1;
    }
    
    va_end(args);
    va_end(args_copy);
    
    // Compare results
    compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
}

/* More specialized version for handling different value types */
void stress_test_format(const char *format, const char *test_name, void *value, char type)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        switch (type) {
            case 'c': expected_ret = printf(format, *(char*)value); break;
            case 's': expected_ret = printf(format, (char*)value); break;
            case 'p': expected_ret = printf(format, value); break;
            case 'd':
            case 'i': expected_ret = printf(format, *(int*)value); break;
            case 'u': expected_ret = printf(format, *(unsigned int*)value); break;
            case 'x':
            case 'X': expected_ret = printf(format, *(unsigned int*)value); break;
            default: expected_ret = printf(format, *(int*)value);
        }
        
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            expected[bytes_read] = '\0';
        close(pipe_fd[0]);
    } else {
        strcpy(expected, "PIPE_ERROR");
        expected_ret = -1;
    }
    
    // Get ft_printf output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        switch (type) {
            case 'c': actual_ret = ft_printf(format, *(char*)value); break;
            case 's': actual_ret = ft_printf(format, (char*)value); break;
            case 'p': actual_ret = ft_printf(format, value); break;
            case 'd':
            case 'i': actual_ret = ft_printf(format, *(int*)value); break;
            case 'u': actual_ret = ft_printf(format, *(unsigned int*)value); break;
            case 'x':
            case 'X': actual_ret = ft_printf(format, *(unsigned int*)value); break;
            default: actual_ret = ft_printf(format, *(int*)value);
        }
        
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            actual[bytes_read] = '\0';
        close(pipe_fd[0]);
    } else {
        strcpy(actual, "PIPE_ERROR");
        actual_ret = -1;
    }
    
    // Compare results
    compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
}

/* ===== BASIC TEST FUNCTIONS ===== */

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

/* ===== FLAG TESTS ===== */

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
}

/* ===== WIDTH TESTS ===== */

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
}

/* ===== PRECISION TESTS ===== */

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
}

/* ===== MAIN FUNCTION ===== */

/* Main function to run the stress tester */
int main(void)
{
    printf("========================================================\n");
    printf("        FT_PRINTF ADVANCED STRESS TESTER v3.0          \n");
    printf("========================================================\n");
    
    initialize_test_counters();
    
    // Run tests in order of increasing complexity
    run_basic_tests();
    run_flag_stress_tests();
    test_width();
    test_precision();
    
    // Print final summary
    printf("\n========================================================\n");
    print_summary();
    
    return 0;
}