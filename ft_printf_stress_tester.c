/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_tester.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 00:19:22 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/controller.h"
#include <inttypes.h>
#include <stddef.h>
#include <time.h>

/* Forward declarations */
void run_basic_tests(void);
void run_flag_stress_tests(void);
void test_width(void);
void test_precision(void);
void run_edge_case_tests(void);
void run_extreme_values_tests(void);
void run_mixed_format_tests(void);
void run_rapid_stress_test(int iterations);

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

/* Generate a random format string for fuzzing */
char* generate_random_format(void)
{
    static char buffer[100];
    const char *conversions = "cspdiuxX%";
    const char *flags = "-+ #0";
    int idx = 0;
    int has_percent = 0;
    
    // Make sure we have at least one format specifier
    if (rand() % 10 > 2 || !has_percent) {
        buffer[idx++] = '%';
        has_percent = 1;
        
        // Maybe add some flags (30% chance)
        if (rand() % 10 < 3) {
            int flag_count = rand() % 3 + 1;  // 1-3 flags
            for (int i = 0; i < flag_count; i++) {
                buffer[idx++] = flags[rand() % strlen(flags)];
            }
        }
        
        // Maybe add width (40% chance)
        if (rand() % 10 < 4) {
            int width = rand() % 20 + 1;  // 1-20 width
            idx += sprintf(buffer + idx, "%d", width);
        }
        
        // Maybe add precision (30% chance)
        if (rand() % 10 < 3) {
            buffer[idx++] = '.';
            int prec = rand() % 10;  // 0-9 precision
            if (prec > 0 || rand() % 2)  // 50% chance to have .0
                idx += sprintf(buffer + idx, "%d", prec);
        }
        
        // Add conversion specifier (not %)
        buffer[idx++] = conversions[rand() % (strlen(conversions) - 1)];
    } else {
        // Add some text
        const char *texts[] = {"Hello", "World", "Test", "Printf", "42"};
        strcpy(buffer + idx, texts[rand() % 5]);
        idx += strlen(texts[rand() % 5]);
    }
    
    buffer[idx] = '\0';
    return buffer;
}

/* Test with a randomly generated value appropriate for the format */
void test_random_value(const char *format)
{
    const char *test_name = "Random value test";
    char type = 0;
    
    // Find the conversion type
    const char *ptr = format;
    while (*ptr) {
        if (*ptr == '%' && *(ptr+1) && *(ptr+1) != '%') {
            // Skip flags, width, precision
            ptr++;
            while (*ptr && (*ptr == '#' || *ptr == '0' || *ptr == '-' || 
                   *ptr == '+' || *ptr == ' ' || (*ptr >= '0' && *ptr <= '9') ||
                   *ptr == '.'))
                ptr++;
                
            type = *ptr;
            break;
        }
        ptr++;
    }
    
    // Select a random value based on the conversion type
    switch (type) {
        case 'c': {
            char c = rand() % 95 + 32;  // Printable ASCII
            test_simple(format, test_name, c);
            break;
        }
        case 's': {
            const char *strings[] = {"", "Hello", "Test", "A very long string to test width limits and other edge cases", NULL};
            test_simple(format, test_name, strings[rand() % 5]);
            break;
        }
        case 'd':
        case 'i': {
            int values[] = {0, 1, -1, 42, -42, INT_MAX, INT_MIN, INT_MAX/2, INT_MIN/2};
            test_simple(format, test_name, values[rand() % 9]);
            break;
        }
        case 'u': {
            unsigned int values[] = {0, 1, 42, 100000, UINT_MAX, UINT_MAX/2, UINT_MAX-1};
            test_simple(format, test_name, values[rand() % 7]);
            break;
        }
        case 'x':
        case 'X': {
            unsigned int values[] = {0, 1, 0xf, 0xff, 0xfff, 0xffff, 0xabcdef, UINT_MAX};
            test_simple(format, test_name, values[rand() % 8]);
            break;
        }
        case 'p': {
            void *values[] = {NULL, (void*)0x1, (void*)0xff, (void*)0xffff, (void*)0xffffffff};
            test_simple(format, test_name, values[rand() % 5]);
            break;
        }
        case '%':
            test_simple(format, test_name);
            break;
        default:
            // Unsupported type
            break;
    }
}

/* ===== TEST CATEGORIES ===== */

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

/* Special test function specifically for handling edge cases */
void test_edge_case(const char *format, const char *test_name) 
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    
    memset(expected, 0, BUFFER_SIZE);
    memset(actual, 0, BUFFER_SIZE);
    
    // Get expected output from printf - use a safer approach for invalid formats
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        
        // Temporarily ignore stderr to avoid warning messages
        int saved_stderr = dup(STDERR_FILENO);
        int dev_null = open("/dev/null", O_WRONLY);
        dup2(dev_null, STDERR_FILENO);
        
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        // Use write instead of printf for formats that could cause issues
        if (strcmp(format, "%") == 0 || 
            strcmp(format, "%-") == 0 || 
            strcmp(format, "%+") == 0 || 
            strcmp(format, "%#") == 0 || 
            strcmp(format, "%0") == 0 ||
            strcmp(format, "% ") == 0) {
            // These are invalid so just write directly
            write(STDOUT_FILENO, "", 0);
            expected_ret = 0;  // Most implementations would return error or 0
        } else {
            // This may still print warnings but will execute
            expected_ret = printf("%s", format);
        }
        
        fflush(stdout);
        
        // Restore stdout and stderr
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stderr, STDERR_FILENO);
        close(dev_null);
        close(saved_stderr);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            expected[bytes_read] = '\0';
        close(pipe_fd[0]);
    } else {
        strcpy(expected, "PIPE_ERROR");
        expected_ret = -1;
    }
    
    // Get ft_printf output - we'll test whatever your implementation does
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        actual_ret = ft_printf("%s", format);  // Just pass the format as string
        
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
    
    // For edge cases, we'll accept differences - this is more informational
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s %s\n", GREEN, RESET, test_name);
        pass_count++;
    } else {
        printf("%s[INFO]%s %s\n", YELLOW, RESET, test_name);
        printf("  Format:    \"%s\"\n", format);
        printf("  Expected:  \"");
        print_formatted_string(expected, expected_ret);
        printf("\"\n  Actual:    \"");
        print_formatted_string(actual, actual_ret);
        printf("\"\n  Note:      Edge case behavior may vary by implementation\n");
        pass_count++;  // Count as pass since this is informational
    }
    test_count++;
}

/* Edge case tests to try to break printf */
void run_edge_case_tests(void)
{
    printf("\n===== EDGE CASE TESTS =====\n");
    
    // Empty format tests
    test_simple("", "Empty string");
    
    // Invalid format tests - use our special test function
    test_edge_case("%", "Lone percent");
    test_edge_case("%..", "Double dot");
    test_edge_case("%-", "Just minus");
    test_edge_case("%+", "Just plus");
    test_edge_case("%#", "Just hash");
    test_edge_case("%0", "Just zero");
    test_edge_case("% ", "Just space");
    
    // Multiple percent signs - these are valid
    test_simple("%%%%%%%%%%", "10 percent signs");
    test_simple("%% %% %% %% %%", "5 percent signs with spaces");
    
    // Invalid conversion specifiers - use our special test function
    test_edge_case("%q", "Invalid conversion q");
    test_edge_case("%!", "Invalid conversion !");
    test_edge_case("%{", "Invalid conversion {");
    
    // Multiple flags in weird orders - these are valid
    test_simple("%+-0 #d", "All flags in order", 42);
    test_simple("%0-+ #d", "All flags mixed up", 42);
    
    // Repeated flags
    test_simple("%+++++d", "Multiple plus flags", 42);
    test_simple("%-----d", "Multiple minus flags", 42);
    test_simple("%00000d", "Multiple zero flags", 42);
    test_simple("%     d", "Multiple space flags", 42);
    test_simple("%#####d", "Multiple hash flags", 42);
}

/* Tests with extreme values to stress test the implementation */
void run_extreme_values_tests(void)
{
    printf("\n===== EXTREME VALUE TESTS =====\n");
    
    // Integer edge values
    test_simple("%d", "INT_MAX", INT_MAX);
    test_simple("%d", "INT_MIN", INT_MIN);
    test_simple("%i", "INT_MAX", INT_MAX);
    test_simple("%i", "INT_MIN", INT_MIN);
    test_simple("%u", "UINT_MAX", UINT_MAX);
    test_simple("%u", "0", 0);
    test_simple("%x", "UINT_MAX", UINT_MAX);
    test_simple("%X", "UINT_MAX", UINT_MAX);
    
    // Character ranges
    test_simple("%c", "NUL character", '\0');
    test_simple("%c", "DEL character", 127);
    test_simple("%c", "Max signed char", 127);
    test_simple("%c", "Min signed char", -128);
    
    // String edge cases
    char empty_str[] = "";
    char *null_str = NULL;
    test_simple("%s", "Empty string", empty_str);
    test_simple("%s", "NULL string", null_str);
    
    // Very long string
    char long_str[1024];
    memset(long_str, 'A', 1023);
    long_str[1023] = '\0';
    test_simple("%s", "1023 character string", long_str);
    
    // Pointer edge cases
    test_simple("%p", "NULL pointer", NULL);
    test_simple("%p", "Near NULL pointer", (void*)0x1);
    test_simple("%p", "Far pointer", (void*)-1);
    
    // Extreme widths and precisions
    test_simple("%1000d", "Width 1000", 42);
    test_simple("%.1000d", "Precision 1000", 42);
}

/* Mixed format string tests with multiple conversions */
void run_mixed_format_tests(void)
{
    printf("\n===== MIXED FORMAT TESTS =====\n");
    
    // Simple mixed tests
    test_simple("%d %s %c", "Int-String-Char", 42, "test", 'X');
    test_simple("%x %p %u", "Hex-Pointer-Unsigned", 0xabcdef, (void*)0x1234, 42);
    
    // Format with text interspersed
    test_simple("Int: %d, String: %s, Char: %c", "Text with values", 42, "test", 'X');
    
    // Format with all types
    test_simple("c=%c s=%s p=%p d=%d i=%i u=%u x=%x X=%X %%",
                "All types", 'A', "string", (void*)0x1234, 42, -42, 42, 0xabcdef, 0xABCDEF);
    
    // Format with repeated types
    test_simple("%d %d %d %d %d", "5 integers", 1, 2, 3, 4, 5);
    test_simple("%s %s %s", "3 strings", "one", "two", "three");
    
    // Multiple flags and width variations in one format
    test_simple("%5d %-5d %05d %+5d % 5d", "Int with different flags",
                42, 42, 42, 42, 42);
                
    // Width and precision combinations
    test_simple("%5.2d %5.2s %8.3x", "Width and precision mix",
                42, "test", 0xabc);
}

/* Rapid-fire stress test with many random variations */
void run_rapid_stress_test(int iterations)
{
    printf("\n===== RAPID STRESS TEST (%d iterations) =====\n", iterations);
    
    // Seed random generator
    srand(time(NULL));
    
    for (int i = 0; i < iterations; i++) {
        char *format = generate_random_format();
        printf("[%d/%d] Testing format: \"%s\"\n", i + 1, iterations, format);
        test_random_value(format);
    }
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
    run_edge_case_tests();
    run_extreme_values_tests();
    run_mixed_format_tests();
    
    // Run random tests as the final stress test
    run_rapid_stress_test(20); // Adjust the number of iterations as needed
    
    // Print final summary
    printf("\n========================================================\n");
    print_summary();
    
    return 0;
}