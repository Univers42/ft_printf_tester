/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_core.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 01:19:04 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_stress.h"

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
        
        // Special case for format strings with only %% sequences
        if (strstr(format, "%%") && !strstr(format, "%c")) {
            // Check if format only contains %% sequences
            int only_percent_percent = 1;
            const char *ptr = format;
            while ((ptr = strchr(ptr, '%')) != NULL) {
                if (*(ptr + 1) != '%') {
                    only_percent_percent = 0;
                    break;
                }
                ptr += 2; // Skip %%
            }
            
            if (only_percent_percent) {
                // Directly call ft_printf for %% only format strings
                actual_ret = ft_printf(format);
                fflush(stdout);
                dup2(saved_stdout, STDOUT_FILENO);
                close(pipe_fd[1]);
                
                int bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
                if (bytes_read >= 0)
                    actual[bytes_read] = '\0';
                close(pipe_fd[0]);
                va_end(args);
                va_end(args_copy);
                compare_and_print_results(expected, expected_ret, actual, actual_ret, format, test_name);
                return;
            }
        }
        
        // For mixed format strings, we can't easily parse and handle all combinations
        // So instead, we'll manually handle common cases and fall back to vprintf
        
        // Count format specifiers
        int format_count = 0;
        const char *ptr = format;
        while ((ptr = strchr(ptr, '%')) != NULL) {
            if (*(ptr + 1) != '%') { // Skip %% sequences
                format_count++;
            } else {
                ptr++; // Skip the second % in %%
            }
            ptr++;
        }
        
        // Based on format count, handle common cases
        if (format_count <= 1) {
            // Single format specifier case (already handled well)
            ptr = strchr(format, '%');
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
        } else if (format_count == 2) {
            // Extract first two format types
            char types[3] = {0, 0, 0};
            int type_idx = 0;
            ptr = format;
            while ((ptr = strchr(ptr, '%')) != NULL && type_idx < 2) {
                if (*(ptr + 1) != '%') { // Skip %% sequences
                    ptr++; // Skip past %
                    
                    // Skip flags, width, precision
                    while (*ptr && (*ptr == '#' || *ptr == '0' || *ptr == '-' || 
                           *ptr == '+' || *ptr == ' ' || (*ptr >= '0' && *ptr <= '9') ||
                           *ptr == '.'))
                        ptr++;
                        
                    if (*ptr) {
                        types[type_idx++] = *ptr;
                        ptr++;
                    }
                } else {
                    ptr += 2; // Skip %%
                }
            }
            
            // Handle common two-argument cases based on types
            if (types[0] == 'd' && types[1] == 'c') {
                int arg1 = va_arg(args_copy, int);
                int arg2 = va_arg(args_copy, int); // char is promoted to int in va_args
                actual_ret = ft_printf(format, arg1, arg2);
            } else if (types[0] == 's' && types[1] == 'd') {
                char* arg1 = va_arg(args_copy, char*);
                int arg2 = va_arg(args_copy, int);
                actual_ret = ft_printf(format, arg1, arg2);
            } else if (types[0] == 'x' && types[1] == 'p') {
                unsigned int arg1 = va_arg(args_copy, unsigned int);
                void* arg2 = va_arg(args_copy, void*);
                actual_ret = ft_printf(format, arg1, arg2);
            } else if (types[0] == 'd' && types[1] == 's') {
                int arg1 = va_arg(args_copy, int);
                char* arg2 = va_arg(args_copy, char*);
                actual_ret = ft_printf(format, arg1, arg2);
            } else if (types[0] == 'c' && types[1] == 'd') {
                int arg1 = va_arg(args_copy, int);
                int arg2 = va_arg(args_copy, int);
                actual_ret = ft_printf(format, arg1, arg2);
            } else if (types[0] == 's' && types[1] == 'p') {
                char* arg1 = va_arg(args_copy, char*);
                void* arg2 = va_arg(args_copy, void*);
                actual_ret = ft_printf(format, arg1, arg2);
            } else if (types[0] == 'x' && types[1] == 'u') {
                unsigned int arg1 = va_arg(args_copy, unsigned int);
                unsigned int arg2 = va_arg(args_copy, unsigned int);
                actual_ret = ft_printf(format, arg1, arg2);
            } else if (types[0] == 'p' && types[1] == 'x') {
                void* arg1 = va_arg(args_copy, void*);
                unsigned int arg2 = va_arg(args_copy, unsigned int);
                actual_ret = ft_printf(format, arg1, arg2);
            } else {
                // Unknown combination - try generic approach with int
                actual_ret = ft_printf("Error: Unsupported format combination %c %c", types[0], types[1]);
            }
        } else if (format_count == 3) {
            // Extract format types
            char types[4] = {0, 0, 0, 0};
            int type_idx = 0;
            ptr = format;
            while ((ptr = strchr(ptr, '%')) != NULL && type_idx < 3) {
                if (*(ptr + 1) != '%') { // Skip %% sequences
                    ptr++; // Skip past %
                    
                    // Skip flags, width, precision
                    while (*ptr && (*ptr == '#' || *ptr == '0' || *ptr == '-' || 
                          *ptr == '+' || *ptr == ' ' || (*ptr >= '0' && *ptr <= '9') ||
                          *ptr == '.'))
                        ptr++;
                        
                    if (*ptr) {
                        types[type_idx++] = *ptr;
                        ptr++;
                    }
                } else {
                    ptr += 2; // Skip %%
                }
            }
            
            // Handle common triple-argument cases
            if (types[0] == 'd' && types[1] == 'c' && types[2] == 's') {
                int arg1 = va_arg(args_copy, int);
                int arg2 = va_arg(args_copy, int); // char promoted to int
                char* arg3 = va_arg(args_copy, char*);
                actual_ret = ft_printf(format, arg1, arg2, arg3);
            } else if (types[0] == 'x' && types[1] == 'p' && types[2] == 'd') {
                unsigned int arg1 = va_arg(args_copy, unsigned int);
                void* arg2 = va_arg(args_copy, void*);
                int arg3 = va_arg(args_copy, int);
                actual_ret = ft_printf(format, arg1, arg2, arg3);
            } else {
                // Unknown combination - try generic approach
                actual_ret = ft_printf("Error: Unsupported 3-item format");
            }
        } else {
            // Too many format specifiers or complex case - just print error
            actual_ret = ft_printf("Error: Too many format specifiers");
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
