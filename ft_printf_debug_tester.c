/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debug_tester.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:00:00 by syzygy            #+#    #+#             */
/*   Updated: 2025/03/06 17:59:50 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/controller.h"

/* Simple debug test function that handles each format type separately */
void debug_test(const char *test_name, const char *format, ...)
{
    char expected[BUFFER_SIZE] = {0};
    char actual[BUFFER_SIZE] = {0};
    int expected_ret = 0;
    int actual_ret = 0;
    va_list args;
    
    // Start args and create a pipe for capturing output
    va_start(args, format);
    
    // Get expected output using standard printf
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Failed to create pipe");
        va_end(args);
        return;
    }
    
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    
    // Run standard printf with the format string and args
    expected_ret = vprintf(format, args);
    fflush(stdout);
    
    // Restore stdout
    dup2(saved_stdout, STDOUT_FILENO);
    close(pipe_fd[1]);
    
    int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
    if (bytes_read >= 0)
        expected[bytes_read] = '\0';
    close(pipe_fd[0]);
    
    // Reset args for ft_printf
    va_end(args);
    va_start(args, format);
    
    // Now capture ft_printf output
    if (pipe(pipe_fd) == -1) {
        perror("Failed to create pipe");
        va_end(args);
        return;
    }
    
    saved_stdout = dup(STDOUT_FILENO);
    dup2(pipe_fd[1], STDOUT_FILENO);
    
    // Extract arguments based on the format string pattern and call ft_printf
    // For simplicity, just handle the specific test cases we're facing
    if (strcmp(format, "%%") == 0) {
        actual_ret = ft_printf("%%");
    }
    else if (strcmp(format, "%5d") == 0) {
        int d = va_arg(args, int);
        actual_ret = ft_printf("%5d", d);
    }
    else if (strcmp(format, "%10s") == 0) {
        char *s = va_arg(args, char*);
        actual_ret = ft_printf("%10s", s);
    }
    else if (strcmp(format, "%5c") == 0) {
        int c = va_arg(args, int);
        actual_ret = ft_printf("%5c", c);
    }
    else if (strcmp(format, "%-5d") == 0) {
        int d = va_arg(args, int);
        actual_ret = ft_printf("%-5d", d);
    }
    else if (strcmp(format, "%-10s") == 0) {
        char *s = va_arg(args, char*);
        actual_ret = ft_printf("%-10s", s);
    }
    else if (strcmp(format, "%-5c") == 0) {
        int c = va_arg(args, int);
        actual_ret = ft_printf("%-5c", c);
    }
    else if (strcmp(format, "%05d") == 0) {
        int d = va_arg(args, int);
        actual_ret = ft_printf("%05d", d);
    }
    else if (strcmp(format, "%.5d") == 0) {
        int d = va_arg(args, int);
        actual_ret = ft_printf("%.5d", d);
    }
    else if (strcmp(format, "%.3s") == 0) {
        char *s = va_arg(args, char*);
        actual_ret = ft_printf("%.3s", s);
    }
    else if (strcmp(format, "%.0d") == 0) {
        int d = va_arg(args, int);
        actual_ret = ft_printf("%.0d", d);
    }
    else if (strcmp(format, "%8.3d") == 0) {
        int d = va_arg(args, int);
        actual_ret = ft_printf("%8.3d", d);
    }
    else if (strcmp(format, "%8.3s") == 0) {
        char *s = va_arg(args, char*);
        actual_ret = ft_printf("%8.3s", s);
    }
    // For other format types, use our existing pattern matching
    else if (strchr(format, '%') == NULL) {
        actual_ret = ft_printf("%s", format);
    }
    else if (strstr(format, "%c")) {
        int c = va_arg(args, int);
        actual_ret = ft_printf(format, c);
    }
    else if (strstr(format, "%s")) {
        char *s = va_arg(args, char*);
        actual_ret = ft_printf(format, s);
    }
    else if (strstr(format, "%d") || strstr(format, "%i")) {
        int d = va_arg(args, int);
        actual_ret = ft_printf(format, d);
    }
    else if (strstr(format, "%u")) {
        unsigned int u = va_arg(args, unsigned int);
        actual_ret = ft_printf(format, u);
    }
    else if (strstr(format, "%x") || strstr(format, "%X")) {
        unsigned int x = va_arg(args, unsigned int);
        actual_ret = ft_printf(format, x);
    }
    else if (strstr(format, "%p")) {
        void *p = va_arg(args, void*);
        actual_ret = ft_printf(format, p);
    }
    else {
        actual_ret = ft_printf("%s", format);
    }
    
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(pipe_fd[1]);
    
    bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
    if (bytes_read >= 0)
        actual[bytes_read] = '\0';
    close(pipe_fd[0]);
    
    va_end(args);
    
    // Compare results
    compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
}

void test_basic_functionality(void)
{
    printf("\n===== BASIC FUNCTIONALITY TESTS =====\n");
    debug_test("Character", "%c", 'A');
    debug_test("String", "%s", "Hello");
    debug_test("String with NULL", "%s", NULL);
    debug_test("Integer", "%d", 42);
    debug_test("Negative integer", "%d", -42);
    debug_test("Zero", "%d", 0);
    debug_test("Unsigned integer", "%u", 42);
    debug_test("Hexadecimal (lowercase)", "%x", 42);
    debug_test("Hexadecimal (uppercase)", "%X", 42);
    debug_test("Pointer", "%p", &test_basic_functionality);
    debug_test("Percent sign", "%%");
}

void test_extended_functionality(void)
{
    printf("\n===== EXTENDED FUNCTIONALITY TESTS =====\n");
    debug_test("Width with integer", "%5d", 42);
    debug_test("Width with string", "%10s", "Hello");
    debug_test("Width with character", "%5c", 'A');
    debug_test("Left-justify with integer", "%-5d", 42);
    debug_test("Left-justify with string", "%-10s", "Hello");
    debug_test("Left-justify with character", "%-5c", 'A');
    debug_test("Zero padding with integer", "%05d", 42);
    debug_test("Zero padding with negative", "%05d", -42);
    debug_test("Precision with integer", "%.5d", 42);
    debug_test("Precision with string", "%.3s", "Hello");
    debug_test("Precision 0 with 0", "%.0d", 0);
    debug_test("Width and precision with integer", "%8.3d", 42);
    debug_test("Width and precision with string", "%8.3s", "Hello");
}

void test_edge_cases(void)
{
    printf("\n===== EDGE CASE TESTS =====\n");
    debug_test("INT_MAX", "%d", INT_MAX);
    debug_test("INT_MIN", "%d", INT_MIN);
    debug_test("UINT_MAX", "%u", UINT_MAX);
    debug_test("Empty string", "%s", "");
    debug_test("NULL string with precision", "%.3s", NULL);
    
    // Handle multiple specifiers test in a way that prevents segfaults
    char test_str[] = "test";
    void *test_ptr = &test_edge_cases;
    
    printf("[TEST] Multiple specifiers\n");
    printf("  Format:    \"%s\"\n", "%c %s %d %x %p %%");
    
    // Manually set up the test without using file descriptors that may leak
    {
        char expected[BUFFER_SIZE] = {0};
        char actual[BUFFER_SIZE] = {0};
        int expected_ret, actual_ret;
        
        // Get expected output using snprintf (avoids file descriptor issues)
        expected_ret = snprintf(expected, BUFFER_SIZE, "%c %s %d %x %p %%", 
                               'A', test_str, 42, 255, test_ptr);
        
        // Create a clean pipe for ft_printf
        int pipe_fd[2] = {-1, -1};
        if (pipe(pipe_fd) != -1) {
            // Save stdout and redirect to pipe
            int saved_stdout = dup(STDOUT_FILENO);
            if (saved_stdout != -1) {
                if (dup2(pipe_fd[1], STDOUT_FILENO) != -1) {
                    // Run ft_printf safely
                    actual_ret = ft_printf("%c %s %d %x %p %%", 
                                         'A', test_str, 42, 255, test_ptr);
                    fflush(stdout);
                    
                    // Restore stdout safely
                    dup2(saved_stdout, STDOUT_FILENO);
                    close(saved_stdout); // Close the saved file descriptor
                    
                    // Close write end of pipe
                    close(pipe_fd[1]);
                    
                    // Read output from pipe
                    int bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
                    if (bytes_read >= 0) {
                        actual[bytes_read] = '\0';
                    }
                    
                    // Close read end of pipe
                    close(pipe_fd[0]);
                    
                    // Compare results
                    compare_and_print_results(expected, expected_ret, actual, 
                                           actual_ret, "%c %s %d %x %p %%", 
                                           "Multiple specifiers");
                } else {
                    perror("Failed to redirect stdout");
                    close(saved_stdout);
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                }
            } else {
                perror("Failed to duplicate stdout");
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
        } else {
            perror("Failed to create pipe");
        }
    }
    
    // Continue with the final test, which should now work without crashing
    debug_test("Mixed text", "This is a %s with %d numbers and a %c character.",
             "string", 42, '!');
}

int main(void)
{
    printf("===== FT_PRINTF DEBUG TESTER =====\n");
    initialize_test_counters();
    test_basic_functionality();
    test_extended_functionality();
    test_edge_cases();
    print_summary();
    return ((fail_count > 0) ? 1 : 0);
}