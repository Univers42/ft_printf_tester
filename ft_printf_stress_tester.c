/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_tester.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 00:00:50 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/controller.h"
#include <inttypes.h>
#include <stddef.h>

/* Function declarations - rename to avoid conflict */
void test_char_simple(char c);
void test_string_simple(char *s);
void test_integer_simple(int n);
void test_unsigned_simple(unsigned int u);
void test_hex_simple(unsigned int x, int uppercase);
void test_pointer_simple(void *p);
void test_percent_simple(void);
void run_basic_tests(void);
void test_plus_flag(int n);
void test_space_flag(int n);
void test_hash_flag(unsigned int n, int uppercase);
void test_width(void);
void test_precision(void);
void run_flag_stress_tests(void);
/* Rename our implementation to avoid conflict with the one in ft_printf_test_utils.h */
void stress_test_format(const char *format, const char *test_name, void *value, char type);

/* Basic test helper function that directly calls ft_printf with specific arguments */
void test_char_simple(char c)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output using printf
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%c", c);
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
        
        actual_ret = ft_printf("%c", c);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "%c", "Character");
}

void test_string_simple(char *s)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%s", s);
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
        
        actual_ret = ft_printf("%s", s);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "%s", "String");
}

void test_integer_simple(int n)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%d", n);
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
        
        actual_ret = ft_printf("%d", n);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "%d", "Integer");
}

void test_unsigned_simple(unsigned int u)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%u", u);
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
        
        actual_ret = ft_printf("%u", u);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "%u", "Unsigned integer");
}

void test_hex_simple(unsigned int x, int uppercase)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    const char *format = uppercase ? "%X" : "%x";
    const char *name = uppercase ? "Hex uppercase" : "Hex lowercase";
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf(format, x);
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
        
        actual_ret = ft_printf(format, x);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, format, name);
}

void test_pointer_simple(void *p)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%p", p);
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
        
        actual_ret = ft_printf("%p", p);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "%p", "Pointer");
}

void test_percent_simple()
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%%");
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
        
        actual_ret = ft_printf("%%");
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "%%", "Percent sign");
}

void test_text_simple()
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("Hello, world!");
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
        
        actual_ret = ft_printf("Hello, world!");
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "Hello, world!", "Simple text");
}

/* Basic test suite with direct function calls */
void run_basic_tests(void)
{
    printf("\n===== BASIC FUNCTIONALITY =====\n");
    test_text_simple();
    test_char_simple('A');
    test_string_simple("Hello");
    test_integer_simple(42);
    test_integer_simple(-42);
    test_unsigned_simple(4294967295u);
    test_hex_simple(0xabcdef, 0);
    test_hex_simple(0xABCDEF, 1);
    test_pointer_simple((void*)0x1234);
    test_percent_simple();
    
    // Test empty and NULL strings
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Empty string test
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("Empty: %s", "");
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            expected[bytes_read] = '\0';
        close(pipe_fd[0]);
    }
    
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        actual_ret = ft_printf("Empty: %s", "");
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            actual[bytes_read] = '\0';
        close(pipe_fd[0]);
    }
    
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "Empty: %s", "Empty string");
    
    // NULL string test - safe approach
    // Instead of directly using NULL with %s, we use a variable
    char *null_str = NULL;
    
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("NULL: %s", null_str);  // Using a variable instead of NULL literal
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            expected[bytes_read] = '\0';
        close(pipe_fd[0]);
    }
    
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        actual_ret = ft_printf("NULL: %s", null_str);  // Using a variable instead of NULL literal
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            actual[bytes_read] = '\0';
        close(pipe_fd[0]);
    }
    
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "NULL: %s", "NULL string");
}

/* Flag tests with direct function calls */
void test_plus_flag(int n) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%+d", n);
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
        
        actual_ret = ft_printf("%+d", n);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "%+d", "Plus flag");
}

void test_space_flag(int n) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("% d", n);
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
        
        actual_ret = ft_printf("% d", n);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "% d", "Space flag");
}

void test_hash_flag(unsigned int n, int uppercase) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    const char *format = uppercase ? "%#X" : "%#x";
    const char *name = uppercase ? "Hash with HEX" : "Hash with hex";
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf(format, n);
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
        
        actual_ret = ft_printf(format, n);
        
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
    compare_and_print_results(expected, expected_ret, actual, actual_ret, format, name);
}

/* Width tests */
void test_width(void) {
    printf("\n===== WIDTH TESTS =====\n");
    
    // Width with different types
    int int_val = 42;
    char *str_val = "Hello";
    char char_val = 'A';
    unsigned int hex_val = 0xABCDEF;
    
    // Pass pointers or addresses of values - use our renamed function
    stress_test_format("%10d", "Width with int", &int_val, 'i');
    stress_test_format("%10s", "Width with string", str_val, 's');
    stress_test_format("%10c", "Width with char", &char_val, 'c');
    stress_test_format("%10x", "Width with hex", &hex_val, 'x');
    
    // Variable widths
    stress_test_format("%1d", "Width 1", &int_val, 'i');
    stress_test_format("%20d", "Width 20", &int_val, 'i');
    stress_test_format("%50d", "Width 50", &int_val, 'i');
}

/* Precision tests */
void test_precision(void) {
    printf("\n===== PRECISION TESTS =====\n");
    
    // Precision with different types
    int int_val = 42;
    char *str_val = "Hello World";
    int zero_val = 0;
    
    // Pass pointers or addresses of values - use our renamed function
    stress_test_format("%.5d", "Precision with int", &int_val, 'i');
    stress_test_format("%.5s", "Precision with string", str_val, 's');
    
    // Variable precisions
    stress_test_format("%.1d", "Precision 1", &int_val, 'i');
    stress_test_format("%.10d", "Precision 10", &int_val, 'i');
    
    // Zero precision special cases
    stress_test_format("%.0d", "Zero precision with 0", &zero_val, 'i');
    stress_test_format("%.0d", "Zero precision with non-zero", &int_val, 'i');
}

/* Run flag stress tests with direct function calls */
void run_flag_stress_tests(void)
{
    printf("\n===== FLAG STRESS TESTS =====\n");
    
    // Basic flag tests
    test_plus_flag(42);
    test_plus_flag(-42);
    test_space_flag(42);
    test_space_flag(-42);
    test_hash_flag(42, 0);
    test_hash_flag(42, 1);
    
    // Extended flag tests - use our renamed function
    int int_val = 42;
    unsigned int hex_val = 42;
    
    stress_test_format("%-10d", "Left-justify flag", &int_val, 'd');
    stress_test_format("%010d", "Zero-padding flag", &int_val, 'd');
    
    // Flag combinations
    stress_test_format("%+010d", "Plus with zero padding", &int_val, 'd');
    stress_test_format("% #x", "Space with hash", &hex_val, 'x');
    stress_test_format("%#10X", "Hash with width", &hex_val, 'X');
}

/* Helper function for complex test cases - renamed to avoid conflict */
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

/* Main function to run the stress tester */
int main(void)
{
    printf("========================================================\n");
    printf("        FT_PRINTF ADVANCED STRESS TESTER v3.0          \n");
    printf("========================================================\n");
    
    initialize_test_counters();
    
    // Run basic tests first
    run_basic_tests();
    
    // Then run more complex tests
    run_flag_stress_tests();
    test_width();
    test_precision();
    
    // Print final summary
    printf("\n========================================================\n");
    print_summary();
    
    return 0;
}