/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debug_tester_simple.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:31 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 17:25:01 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/controller.h"

// Direct comparison function for simple debug tests
void run_direct_test(const char *test_name, const char *format, ...)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    va_list args;
    int pipe_fd[2];
    int saved_stdout;
    int bytes_read;
    
    // Extract the specific argument based on the format string
    va_start(args, format);
    
    // Capture expected output from standard printf
    if (pipe(pipe_fd) == -1) {
        perror("Failed to create pipe");
        return;
    }
    
    saved_stdout = dup(STDOUT_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    
    if (strstr(format, "%c") == format) {
        int c = va_arg(args, int);
        expected_ret = printf(format, c);
    } 
    else if (strstr(format, "%s") == format) {
        char *s = va_arg(args, char *);
        expected_ret = printf(format, s);
    }
    else if (strstr(format, "%d") == format || strstr(format, "%i") == format) {
        int d = va_arg(args, int);
        expected_ret = printf(format, d);
    }
    else if (strstr(format, "%u") == format) {
        unsigned int u = va_arg(args, unsigned int);
        expected_ret = printf(format, u);
    }
    else if (strstr(format, "%x") == format || strstr(format, "%X") == format) {
        unsigned int x = va_arg(args, unsigned int);
        expected_ret = printf(format, x);
    }
    else if (strstr(format, "%p") == format) {
        void *p = va_arg(args, void *);
        expected_ret = printf(format, p);
    }
    else {
        // For %% or any other case
        expected_ret = printf("%s", format);  // Fix: Use "%s" as format string
    }
    
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(pipe_fd[1]);
    
    bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
    if (bytes_read >= 0)
        expected[bytes_read] = '\0';
    close(pipe_fd[0]);
    
    // Reset args to beginning for ft_printf
    va_end(args);
    va_start(args, format);
    
    // Capture ft_printf output
    if (pipe(pipe_fd) == -1) {
        perror("Failed to create pipe");
        return;
    }
    
    saved_stdout = dup(STDOUT_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    
    if (strstr(format, "%c") == format) {
        int c = va_arg(args, int);
        actual_ret = ft_printf(format, c);
    } 
    else if (strstr(format, "%s") == format) {
        char *s = va_arg(args, char *);
        actual_ret = ft_printf(format, s);
    }
    else if (strstr(format, "%d") == format || strstr(format, "%i") == format) {
        int d = va_arg(args, int);
        actual_ret = ft_printf(format, d);
    }
    else if (strstr(format, "%u") == format) {
        unsigned int u = va_arg(args, unsigned int);
        actual_ret = ft_printf(format, u);
    }
    else if (strstr(format, "%x") == format || strstr(format, "%X") == format) {
        unsigned int x = va_arg(args, unsigned int);
        actual_ret = ft_printf(format, x);
    }
    else if (strstr(format, "%p") == format) {
        void *p = va_arg(args, void *);
        actual_ret = ft_printf(format, p);
    }
    else {
        // For %% or any other case
        actual_ret = ft_printf("%s", format);  // Fix: Use "%s" as format string
    }
    
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(pipe_fd[1]);
    
    bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
    if (bytes_read >= 0)
        actual[bytes_read] = '\0';
    close(pipe_fd[0]);
    
    va_end(args);
    
    compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
}

void run_simple_tests(void) {
    run_direct_test("Simple character", "%c", 'A');
    run_direct_test("Simple string", "%s", "Hello, world!");
    run_direct_test("Simple integer", "%d", 42);
    run_direct_test("Simple negative integer", "%d", -42);
    run_direct_test("Simple unsigned integer", "%u", 42);
    run_direct_test("Simple hex (lowercase)", "%x", 42);
    run_direct_test("Simple hex (uppercase)", "%X", 42);
    run_direct_test("Simple pointer", "%p", &run_simple_tests);
    run_direct_test("Simple percent", "%%");
}

int main(void) {
    printf("%s=== FT_PRINTF SIMPLE DEBUG TESTER ===%s\n", MAGENTA, RESET);
    initialize_test_counters();
    run_simple_tests();
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
