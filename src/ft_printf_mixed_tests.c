/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mixed_tests.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:30:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 00:26:30 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/controller.h"

/* A more robust mixed format tester that uses a special approach for multiple
 * format specifiers to avoid segmentation faults.
 */

typedef struct s_mixed_test_args {
    int int_args[10];
    unsigned int uint_args[10];
    char char_args[10];
    char *str_args[10];
    void *ptr_args[10];
    char arg_types[10];
    int arg_count;
} t_mixed_test_args;

/* Converts a type character into an argument type enum */
t_arg_type char_to_arg_type(char c)
{
    switch (c) {
        case 'c': return ARG_CHAR;
        case 's': return ARG_STRING;
        case 'd': 
        case 'i': return ARG_INT;
        case 'u': return ARG_UINT;
        case 'x':
        case 'X': return ARG_HEX;
        case 'p': return ARG_POINTER;
        default: return ARG_INT;
    }
}

/* Parse a format string and extract information about the arguments */
void parse_mixed_format(const char *format, t_mixed_test_args *args)
{
    const char *ptr = format;
    args->arg_count = 0;
    
    while (*ptr && args->arg_count < 10) {
        if (*ptr == '%' && *(ptr + 1) != '%') {
            ptr++; // Skip %
            
            // Skip flags, width, precision
            while (*ptr && (*ptr == '#' || *ptr == '0' || *ptr == '-' || 
                  *ptr == '+' || *ptr == ' ' || (*ptr >= '0' && *ptr <= '9') ||
                  *ptr == '.')) {
                if (*ptr == '.') {
                    ptr++;
                    while (*ptr && (*ptr >= '0' && *ptr <= '9'))
                        ptr++;
                } else {
                    ptr++;
                }
            }
            
            // Record the conversion type
            if (*ptr) {
                args->arg_types[args->arg_count++] = *ptr;
                ptr++;
            }
        } 
        else if (*ptr == '%' && *(ptr + 1) == '%') {
            ptr += 2; // Skip %%
        }
        else {
            ptr++;
        }
    }
}

/* Try to test a format string with mixed argument types 
 * This function sets up random test values for each argument type
 */
void test_mixed_format_random(const char *format, const char *test_name)
{
    t_mixed_test_args args;
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    // Initialize with random values
    parse_mixed_format(format, &args);
    for (int i = 0; i < args.arg_count; i++) {
        switch (args.arg_types[i]) {
            case 'c': 
                args.char_args[i] = 'A' + (rand() % 26);
                break;
            case 's':
                if (rand() % 10 == 0) {
                    args.str_args[i] = NULL; // Occasionally test NULL
                } else {
                    const char *options[] = {"", "Hello", "Test", "42"};
                    args.str_args[i] = (char*)options[rand() % 4];
                }
                break;
            case 'd':
            case 'i':
                args.int_args[i] = rand() % 10000 - 5000;
                break;
            case 'u':
            case 'x':
            case 'X':
                args.uint_args[i] = rand() % 100000;
                break;
            case 'p':
                args.ptr_args[i] = (void*)(long)(rand() % 100000);
                break;
            default:
                args.int_args[i] = rand() % 100;
                break;
        }
    }
    
    // Get expected output from printf
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        // Call printf with the appropriate arguments
        switch (args.arg_count) {
            case 1:
                switch (args.arg_types[0]) {
                    case 'c': expected_ret = printf(format, args.char_args[0]); break;
                    case 's': expected_ret = printf(format, args.str_args[0]); break;
                    case 'd': 
                    case 'i': expected_ret = printf(format, args.int_args[0]); break;
                    case 'u': 
                    case 'x':
                    case 'X': expected_ret = printf(format, args.uint_args[0]); break;
                    case 'p': expected_ret = printf(format, args.ptr_args[0]); break;
                    default: expected_ret = printf(format, args.int_args[0]);
                }
                break;
            case 2:
                expected_ret = printf(format, 
                    args.arg_types[0] == 'c' ? (int)args.char_args[0] : 
                    args.arg_types[0] == 's' ? (intptr_t)args.str_args[0] :
                    args.arg_types[0] == 'p' ? (intptr_t)args.ptr_args[0] :
                    args.arg_types[0] == 'u' || args.arg_types[0] == 'x' || args.arg_types[0] == 'X' ? 
                        args.uint_args[0] : args.int_args[0],
                    
                    args.arg_types[1] == 'c' ? (int)args.char_args[1] : 
                    args.arg_types[1] == 's' ? (intptr_t)args.str_args[1] :
                    args.arg_types[1] == 'p' ? (intptr_t)args.ptr_args[1] :
                    args.arg_types[1] == 'u' || args.arg_types[1] == 'x' || args.arg_types[1] == 'X' ? 
                        args.uint_args[1] : args.int_args[1]
                );
                break;
            case 3:
                expected_ret = printf(format, 
                    args.arg_types[0] == 'c' ? (int)args.char_args[0] : 
                    args.arg_types[0] == 's' ? (intptr_t)args.str_args[0] :
                    args.arg_types[0] == 'p' ? (intptr_t)args.ptr_args[0] :
                    args.arg_types[0] == 'u' || args.arg_types[0] == 'x' || args.arg_types[0] == 'X' ? 
                        args.uint_args[0] : args.int_args[0],
                    
                    args.arg_types[1] == 'c' ? (int)args.char_args[1] : 
                    args.arg_types[1] == 's' ? (intptr_t)args.str_args[1] :
                    args.arg_types[1] == 'p' ? (intptr_t)args.ptr_args[1] :
                    args.arg_types[1] == 'u' || args.arg_types[1] == 'x' || args.arg_types[1] == 'X' ? 
                        args.uint_args[1] : args.int_args[1],
                        
                    args.arg_types[2] == 'c' ? (int)args.char_args[2] : 
                    args.arg_types[2] == 's' ? (intptr_t)args.str_args[2] :
                    args.arg_types[2] == 'p' ? (intptr_t)args.ptr_args[2] :
                    args.arg_types[2] == 'u' || args.arg_types[2] == 'x' || args.arg_types[2] == 'X' ? 
                        args.uint_args[2] : args.int_args[2]
                );
                break;
            // Add cases for more arguments if needed
            default:
                expected_ret = printf("Support for %d arguments not implemented", args.arg_count);
                break;
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
        
        // Call ft_printf with the appropriate arguments
        switch (args.arg_count) {
            case 1:
                switch (args.arg_types[0]) {
                    case 'c': actual_ret = ft_printf(format, args.char_args[0]); break;
                    case 's': actual_ret = ft_printf(format, args.str_args[0]); break;
                    case 'd': 
                    case 'i': actual_ret = ft_printf(format, args.int_args[0]); break;
                    case 'u': 
                    case 'x':
                    case 'X': actual_ret = ft_printf(format, args.uint_args[0]); break;
                    case 'p': actual_ret = ft_printf(format, args.ptr_args[0]); break;
                    default: actual_ret = ft_printf(format, args.int_args[0]);
                }
                break;
            case 2:
                actual_ret = ft_printf(format, 
                    args.arg_types[0] == 'c' ? (int)args.char_args[0] : 
                    args.arg_types[0] == 's' ? (intptr_t)args.str_args[0] :
                    args.arg_types[0] == 'p' ? (intptr_t)args.ptr_args[0] :
                    args.arg_types[0] == 'u' || args.arg_types[0] == 'x' || args.arg_types[0] == 'X' ? 
                        args.uint_args[0] : args.int_args[0],
                    
                    args.arg_types[1] == 'c' ? (int)args.char_args[1] : 
                    args.arg_types[1] == 's' ? (intptr_t)args.str_args[1] :
                    args.arg_types[1] == 'p' ? (intptr_t)args.ptr_args[1] :
                    args.arg_types[1] == 'u' || args.arg_types[1] == 'x' || args.arg_types[1] == 'X' ? 
                        args.uint_args[1] : args.int_args[1]
                );
                break;
            case 3:
                actual_ret = ft_printf(format, 
                    args.arg_types[0] == 'c' ? (int)args.char_args[0] : 
                    args.arg_types[0] == 's' ? (intptr_t)args.str_args[0] :
                    args.arg_types[0] == 'p' ? (intptr_t)args.ptr_args[0] :
                    args.arg_types[0] == 'u' || args.arg_types[0] == 'x' || args.arg_types[0] == 'X' ? 
                        args.uint_args[0] : args.int_args[0],
                    
                    args.arg_types[1] == 'c' ? (int)args.char_args[1] : 
                    args.arg_types[1] == 's' ? (intptr_t)args.str_args[1] :
                    args.arg_types[1] == 'p' ? (intptr_t)args.ptr_args[1] :
                    args.arg_types[1] == 'u' || args.arg_types[1] == 'x' || args.arg_types[1] == 'X' ? 
                        args.uint_args[1] : args.int_args[1],
                        
                    args.arg_types[2] == 'c' ? (int)args.char_args[2] : 
                    args.arg_types[2] == 's' ? (intptr_t)args.str_args[2] :
                    args.arg_types[2] == 'p' ? (intptr_t)args.ptr_args[2] :
                    args.arg_types[2] == 'u' || args.arg_types[2] == 'x' || args.arg_types[2] == 'X' ? 
                        args.uint_args[2] : args.int_args[2]
                );
                break;
            // Add cases for more arguments if needed
            default:
                actual_ret = ft_printf("Support for %d arguments not implemented", args.arg_count);
                break;
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

/* Run a series of mixed format tests with specific values */
void test_mixed_format_with_values(const char *format, const char *test_name, ...)
{
    t_mixed_test_args args;
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    va_list va_args;
    
    // Parse the format
    parse_mixed_format(format, &args);
    
    // Read the arguments
    va_start(va_args, test_name);
    for (int i = 0; i < args.arg_count; i++) {
        switch (args.arg_types[i]) {
            case 'c':
                args.char_args[i] = (char)va_arg(va_args, int);
                break;
            case 's':
                args.str_args[i] = va_arg(va_args, char*);
                break;
            case 'd':
            case 'i':
                args.int_args[i] = va_arg(va_args, int);
                break;
            case 'u':
            case 'x':
            case 'X':
                args.uint_args[i] = va_arg(va_args, unsigned int);
                break;
            case 'p':
                args.ptr_args[i] = va_arg(va_args, void*);
                break;
            default:
                args.int_args[i] = va_arg(va_args, int);
                break;
        }
    }
    va_end(va_args);
    
    // Get expected output from printf
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        // Call printf with the appropriate arguments
        switch (args.arg_count) {
            case 1:
                switch (args.arg_types[0]) {
                    case 'c': expected_ret = printf(format, args.char_args[0]); break;
                    case 's': expected_ret = printf(format, args.str_args[0]); break;
                    case 'd': 
                    case 'i': expected_ret = printf(format, args.int_args[0]); break;
                    case 'u': 
                    case 'x':
                    case 'X': expected_ret = printf(format, args.uint_args[0]); break;
                    case 'p': expected_ret = printf(format, args.ptr_args[0]); break;
                    default: expected_ret = printf(format, args.int_args[0]);
                }
                break;
            case 2:
                expected_ret = printf(format, 
                    args.arg_types[0] == 'c' ? (int)args.char_args[0] : 
                    args.arg_types[0] == 's' ? (intptr_t)args.str_args[0] :
                    args.arg_types[0] == 'p' ? (intptr_t)args.ptr_args[0] :
                    args.arg_types[0] == 'u' || args.arg_types[0] == 'x' || args.arg_types[0] == 'X' ? 
                        args.uint_args[0] : args.int_args[0],
                    
                    args.arg_types[1] == 'c' ? (int)args.char_args[1] : 
                    args.arg_types[1] == 's' ? (intptr_t)args.str_args[1] :
                    args.arg_types[1] == 'p' ? (intptr_t)args.ptr_args[1] :
                    args.arg_types[1] == 'u' || args.arg_types[1] == 'x' || args.arg_types[1] == 'X' ? 
                        args.uint_args[1] : args.int_args[1]
                );
                break;
            case 3:
                expected_ret = printf(format, 
                    args.arg_types[0] == 'c' ? (int)args.char_args[0] : 
                    args.arg_types[0] == 's' ? (intptr_t)args.str_args[0] :
                    args.arg_types[0] == 'p' ? (intptr_t)args.ptr_args[0] :
                    args.arg_types[0] == 'u' || args.arg_types[0] == 'x' || args.arg_types[0] == 'X' ? 
                        args.uint_args[0] : args.int_args[0],
                    
                    args.arg_types[1] == 'c' ? (int)args.char_args[1] : 
                    args.arg_types[1] == 's' ? (intptr_t)args.str_args[1] :
                    args.arg_types[1] == 'p' ? (intptr_t)args.ptr_args[1] :
                    args.arg_types[1] == 'u' || args.arg_types[1] == 'x' || args.arg_types[1] == 'X' ? 
                        args.uint_args[1] : args.int_args[1],
                        
                    args.arg_types[2] == 'c' ? (int)args.char_args[2] : 
                    args.arg_types[2] == 's' ? (intptr_t)args.str_args[2] :
                    args.arg_types[2] == 'p' ? (intptr_t)args.ptr_args[2] :
                    args.arg_types[2] == 'u' || args.arg_types[2] == 'x' || args.arg_types[2] == 'X' ? 
                        args.uint_args[2] : args.int_args[2]
                );
                break;
            // Add cases for more arguments if needed
            default:
                expected_ret = printf("Support for %d arguments not implemented", args.arg_count);
                break;
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
        
        // Call ft_printf with the appropriate arguments
        switch (args.arg_count) {
            case 1:
                switch (args.arg_types[0]) {
                    case 'c': actual_ret = ft_printf(format, args.char_args[0]); break;
                    case 's': actual_ret = ft_printf(format, args.str_args[0]); break;
                    case 'd': 
                    case 'i': actual_ret = ft_printf(format, args.int_args[0]); break;
                    case 'u': 
                    case 'x':
                    case 'X': actual_ret = ft_printf(format, args.uint_args[0]); break;
                    case 'p': actual_ret = ft_printf(format, args.ptr_args[0]); break;
                    default: actual_ret = ft_printf(format, args.int_args[0]);
                }
                break;
            case 2:
                actual_ret = ft_printf(format, 
                    args.arg_types[0] == 'c' ? (int)args.char_args[0] : 
                    args.arg_types[0] == 's' ? (intptr_t)args.str_args[0] :
                    args.arg_types[0] == 'p' ? (intptr_t)args.ptr_args[0] :
                    args.arg_types[0] == 'u' || args.arg_types[0] == 'x' || args.arg_types[0] == 'X' ? 
                        args.uint_args[0] : args.int_args[0],
                    
                    args.arg_types[1] == 'c' ? (int)args.char_args[1] : 
                    args.arg_types[1] == 's' ? (intptr_t)args.str_args[1] :
                    args.arg_types[1] == 'p' ? (intptr_t)args.ptr_args[1] :
                    args.arg_types[1] == 'u' || args.arg_types[1] == 'x' || args.arg_types[1] == 'X' ? 
                        args.uint_args[1] : args.int_args[1]
                );
                break;
            case 3:
                actual_ret = ft_printf(format, 
                    args.arg_types[0] == 'c' ? (int)args.char_args[0] : 
                    args.arg_types[0] == 's' ? (intptr_t)args.str_args[0] :
                    args.arg_types[0] == 'p' ? (intptr_t)args.ptr_args[0] :
                    args.arg_types[0] == 'u' || args.arg_types[0] == 'x' || args.arg_types[0] == 'X' ? 
                        args.uint_args[0] : args.int_args[0],
                    
                    args.arg_types[1] == 'c' ? (int)args.char_args[1] : 
                    args.arg_types[1] == 's' ? (intptr_t)args.str_args[1] :
                    args.arg_types[1] == 'p' ? (intptr_t)args.ptr_args[1] :
                    args.arg_types[1] == 'u' || args.arg_types[1] == 'x' || args.arg_types[1] == 'X' ? 
                        args.uint_args[1] : args.int_args[1],
                        
                    args.arg_types[2] == 'c' ? (int)args.char_args[2] : 
                    args.arg_types[2] == 's' ? (intptr_t)args.str_args[2] :
                    args.arg_types[2] == 'p' ? (intptr_t)args.ptr_args[2] :
                    args.arg_types[2] == 'u' || args.arg_types[2] == 'x' || args.arg_types[2] == 'X' ? 
                        args.uint_args[2] : args.int_args[2]
                );
                break;
            // Add cases for more arguments if needed
            default:
                actual_ret = ft_printf("Support for %d arguments not implemented", args.arg_count);
                break;
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

/* Run a comprehensive set of mixed format tests */
void run_robust_mixed_format_tests(void)
{
    printf("\n===== ROBUST MIXED FORMAT TESTS =====\n");
    
    // Test with two specifiers
    test_mixed_format_with_values("%d %s", "Int and string", 42, "hello");
    test_mixed_format_with_values("%c %d", "Char and int", 'A', 42);
    test_mixed_format_with_values("%s %p", "String and pointer", "test", (void*)0x1234);
    test_mixed_format_with_values("%x %u", "Hex and unsigned", 0xabcdef, 42);
    
    // Test with three specifiers
    test_mixed_format_with_values("%d %s %c", "Int, string, and char", 42, "hello", 'A');
    test_mixed_format_with_values("%p %x %d", "Pointer, hex, and int", (void*)0x1234, 0xabcdef, 42);
    
    // Test with text interspersed
    test_mixed_format_with_values("Int: %d, String: %s", "Text with values", 42, "test");
    test_mixed_format_with_values("Hex: %x, Char: %c, Pointer: %p", 
                               "Multiple types with text",
                               0xabcdef, 'A', (void*)0x1234);
    
    // Test all types in one format
    test_mixed_format_with_values("c=%c s=%s p=%p d=%d i=%i u=%u x=%x X=%X",
                               "All types in one format",
                               'A', "string", (void*)0x1234, 42, -42, 42, 0xabcdef, 0xABCDEF);
    
    // Test with random values for stress testing
    printf("\n--- Random Mixed Format Tests ---\n");
    for (int i = 0; i < 10; i++) {
        const char *formats[] = {
            "%d %s",
            "%c %p",
            "%u %x %s",
            "Test: %d, %s, %c",
            "Values: %x, %p, %d, %s"
        };
        test_mixed_format_random(formats[rand() % 5], "Random mixed test");
    }
}
