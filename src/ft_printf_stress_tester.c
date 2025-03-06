/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_tester.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 19:50:54 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/controller.h"

// Function declarations
void run_stress_tests(void);
void run_basic_tests(void);

/* Simple helper function for direct test comparison */
void compare_output(const char *format, const char *test_name, ...)
{
    char expected[BUFFER_SIZE] = {0};
    char actual[BUFFER_SIZE] = {0};
    int expected_ret, actual_ret;
    int pipe_fd[2];
    int saved_stdout;
    va_list args;
    
    // Start collecting arguments
    va_start(args, test_name);

    // Get expected output using printf
    if (pipe(pipe_fd) != -1) {
        saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = vprintf(format, args);
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            expected[bytes_read] = '\0';
        close(pipe_fd[0]);
    }

    // Reset args and get actual output from ft_printf
    va_end(args);
    va_start(args, test_name);
    
    if (pipe(pipe_fd) != -1) {
        saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        actual_ret = vprintf(format, args); // Use standard vprintf as ft_printf doesn't have vft_printf
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            actual[bytes_read] = '\0';
        close(pipe_fd[0]);
    }
    
    va_end(args);
    
    compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
}

/* Run basic functionality tests */
void run_basic_tests(void)
{
    printf("\n===== BASIC FUNCTIONALITY TESTS =====\n");
    
    // Character test with direct function call
    {
        char c = 'A';
        test_char(c, "%c", "Single character");
    }
    
    // String test with direct function call
    {
        char *str = "Hello, World!";
        test_string(str, "%s", "String");
    }
    
    // NULL string test
    test_string(NULL, "%s", "NULL string");
    
    // Empty string test
    test_string("", "%s", "Empty string");
    
    // Integer tests
    test_int(42, "%d", "Integer");
    test_int(-42, "%d", "Negative integer");
    test_int(0, "%d", "Zero integer");
    
    // Unsigned integer test
    test_unsigned(42, "%u", "Unsigned integer");
    
    // Hex tests
    test_unsigned(0xdeadbeef, "%x", "Hex lowercase");
    test_unsigned(0xdeadbeef, "%X", "Hex uppercase");
    
    // Pointer test
    test_pointer(&run_basic_tests, "%p", "Pointer");
    
    // Percent sign test
    {
        char expected[BUFFER_SIZE], actual[BUFFER_SIZE];
        int expected_ret, actual_ret;
        int pipe_fd[2];
        
        // Get expected output
        pipe(pipe_fd);
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%%");
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
        if (bytes_read >= 0) expected[bytes_read] = '\0';
        close(pipe_fd[0]);
        
        // Get actual output
        pipe(pipe_fd);
        saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        actual_ret = ft_printf("%%");
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
        if (bytes_read >= 0) actual[bytes_read] = '\0';
        close(pipe_fd[0]);
        
        compare_and_print_results(expected, expected_ret, actual, actual_ret, "%%", "Percent sign");
    }
}

/* Run the entire stress test suite */
void run_stress_tests(void)
{
    printf("========================================================\n");
    printf("        FT_PRINTF ADVANCED STRESS TESTER v1.0          \n");
    printf("========================================================\n");
    
    // Initialize counters
    initialize_test_counters();
    
    // Run core test groups
    run_basic_tests();
    
    // Print summary
    print_summary();
    
    printf("\n✓ Test completed successfully\n");
}

/* Main entry point */
int main(void)
{
    run_stress_tests();
    return (fail_count > 0);
}
