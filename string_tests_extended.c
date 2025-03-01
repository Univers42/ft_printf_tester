#include "../ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <stdarg.h>

#define BUFFER_SIZE 4096
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

int test_count = 0;
int pass_count = 0;
int fail_count = 0;

// Test function with improved diagnostics for strings
void test_string(const char *str, const char *format, const char *test_name) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    test_count++;
    
    // Get expected output using sprintf
    expected_ret = sprintf(expected, format, str);
    
    // Create temporary file for capturing ft_printf output
    fp = tmpfile();
    if (!fp) {
        perror("Failed to create temporary file");
        return;
    }
    
    // Redirect stdout to temp file
    int original_stdout = dup(1);
    if (dup2(fileno(fp), 1) == -1) {
        perror("Failed to redirect stdout");
        fclose(fp);
        return;
    }
    
    // Call ft_printf which will write to the temp file
    actual_ret = ft_printf(format, str);
    fflush(stdout);
    
    // Restore stdout
    dup2(original_stdout, 1);
    close(original_stdout);
    
    // Read result from temp file
    fseek(fp, 0, SEEK_SET);
    int bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
    actual[bytes_read] = '\0';
    fclose(fp);
    
    // Compare results
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s %s\n", GREEN, RESET, test_name);
        pass_count++;
    } else {
        printf("%s[FAIL]%s %s\n", RED, RESET, test_name);
        printf("  Format:    \"%s\"\n", format);
        printf("  Input:     %s\"%s\"%s\n", BLUE, 
               str ? str : "NULL", RESET);
        
        // Print expected output with visible spaces
        printf("  Expected:  \"");
        for (int i = 0; i < (int)strlen(expected); i++) {
            if (expected[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (expected[i] < 32 || expected[i] > 126)
                printf("%s\\%03o%s", BLUE, expected[i], RESET); // Non-printable
            else
                printf("%c", expected[i]);
        }
        printf("\" (ret: %d)\n", expected_ret);
        
        // Print actual output with visible spaces
        printf("  Actual:    \"");
        for (int i = 0; i < (int)strlen(actual); i++) {
            if (actual[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (actual[i] == '0')
                printf("%s0%s", RED, RESET); // Highlight zeros
            else if (actual[i] < 32 || actual[i] > 126)
                printf("%s\\%03o%s", BLUE, actual[i], RESET); // Non-printable
            else
                printf("%c", actual[i]);
        }
        printf("\" (ret: %d)\n", actual_ret);
        fail_count++;
    }
}

// Fixed version of test_multiple_strings that works properly with variable arguments
void test_multiple_strings(const char *format, const char *test_name, ...) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    va_list args;
    
    test_count++;
    
    // Create temporary file for capturing ft_printf output
    fp = tmpfile();
    if (!fp) {
        perror("Failed to create temporary file");
        return;
    }
    
    // First capture expected output from printf
    va_start(args, test_name);
    expected_ret = vsnprintf(expected, BUFFER_SIZE, format, args);
    va_end(args);
    
    // Redirect stdout to temp file
    int original_stdout = dup(1);
    if (dup2(fileno(fp), 1) == -1) {
        perror("Failed to redirect stdout");
        fclose(fp);
        return;
    }
    
    // Call ft_printf which will write to the temp file
    // We need to manually extract and pass each argument because ft_printf doesn't have a vprintf version
    va_start(args, test_name);
    
    // We need to manually handle the variadic arguments based on the format string
    // First create a buffer with just the first 10 arguments, which should be enough for our tests
    const char* arg1 = va_arg(args, const char*);
    const char* arg2 = va_arg(args, const char*);
    const char* arg3 = va_arg(args, const char*);
    const char* arg4 = va_arg(args, const char*);
    const char* arg5 = va_arg(args, const char*);
    const char* arg6 = va_arg(args, const char*);
    const char* arg7 = va_arg(args, const char*);
    const char* arg8 = va_arg(args, const char*);
    const char* arg9 = va_arg(args, const char*);
    const char* arg10 = va_arg(args, const char*);
    
    // Now call ft_printf with all these arguments
    actual_ret = ft_printf(format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    
    va_end(args);
    fflush(stdout);
    
    // Restore stdout
    dup2(original_stdout, 1);
    close(original_stdout);
    
    // Read result from temp file
    fseek(fp, 0, SEEK_SET);
    int bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
    actual[bytes_read] = '\0';
    fclose(fp);
    
    // Compare results
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s %s\n", GREEN, RESET, test_name);
        pass_count++;
    } else {
        printf("%s[FAIL]%s %s\n", RED, RESET, test_name);
        printf("  Format:    \"%s\"\n", format);
        
        // Print expected output with visible spaces
        printf("  Expected:  \"");
        for (int i = 0; i < (int)strlen(expected); i++) {
            if (expected[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (expected[i] < 32 || expected[i] > 126)
                printf("%s\\%03o%s", BLUE, expected[i], RESET); // Non-printable
            else
                printf("%c", expected[i]);
        }
        printf("\" (ret: %d)\n", expected_ret);
        
        // Print actual output with visible spaces
        printf("  Actual:    \"");
        for (int i = 0; i < (int)strlen(actual); i++) {
            if (actual[i] == ' ')
                printf("%s·%s", YELLOW, RESET);
            else if (actual[i] == '0')
                printf("%s0%s", RED, RESET);
            else if (actual[i] < 32 || actual[i] > 126)
                printf("%s\\%03o%s", BLUE, actual[i], RESET);
            else
                printf("%c", actual[i]);
        }
        printf("\" (ret: %d)\n", actual_ret);
        fail_count++;
    }
}

void run_category(const char *category) {
    printf("\n%s=== %s ===%s\n", BLUE, category, RESET);
}

int main(void) {
    printf("%s=== FT_PRINTF EXTENDED STRING TESTS ===%s\n", MAGENTA, RESET);
    
    // BASIC STRING TESTS
    run_category("Basic String Tests");
    test_string("Hello, world!", "%s", "Basic string");
    test_string("", "%s", "Empty string");
    test_string(NULL, "%s", "NULL string"); // Should print (null)
    test_string("42", "%s", "Short string");
    test_string("This is a somewhat longer string to test string handling", "%s", "Longer string");
    
    // STRING WITH SPECIAL CHARACTERS
    run_category("Special Character Strings");
    test_string("Hello\nworld", "%s", "String with newline");
    test_string("Hello\tworld", "%s", "String with tab");
    test_string("Hello\rworld", "%s", "String with carriage return");
    test_string("Hello\\world", "%s", "String with backslash");
    test_string("Hello\"world\"", "%s", "String with quotes");
    test_string("Hello%%world", "%s", "String with percent signs");
    test_string("!@#$%^&*()_+", "%s", "String with special characters");
    // test_string("👋 Hello 🌍", "%s", "String with emoji (may not work as expected)");
    
    // WIDTH TESTS
    run_category("Width Tests");
    test_string("Hello", "%10s", "Width larger than string");
    test_string("Hello", "%5s", "Width equal to string");
    test_string("Hello", "%3s", "Width smaller than string");
    test_string("Hello", "%0s", "Width of 0");
    test_string("Hello", "%1s", "Width of 1");
    test_string("Hello", "%100s", "Very large width");
    
    // LEFT JUSTIFY TESTS
    run_category("Left Justify Tests");
    test_string("Hello", "%-10s", "Left justified, width larger");
    test_string("Hello", "%-5s", "Left justified, width equal");
    test_string("Hello", "%-3s", "Left justified, width smaller");
    test_string("Hello", "%-0s", "Left justified, width 0");
    test_string("Hello", "%-1s", "Left justified, width 1");
    test_string("Hello", "%-100s", "Left justified, very large width");
    
    // ZERO PADDING TESTS
    run_category("Zero Padding Tests");
    test_string("Hello", "%010s", "Zero-padded width larger");
    test_string("Hello", "%05s", "Zero-padded width equal");
    test_string("Hello", "%03s", "Zero-padded width smaller");
    
    // PRECISION TESTS
    run_category("Precision Tests");
    test_string("Hello", "%.10s", "Precision larger than string");
    test_string("Hello", "%.5s", "Precision equal to string");
    test_string("Hello", "%.3s", "Precision smaller than string");
    test_string("Hello", "%.0s", "Precision of 0");
    test_string("Hello", "%.s", "Precision with no value");
    test_string("", "%.0s", "Empty string, precision 0");
    test_string("", "%.10s", "Empty string, precision 10");
    
    // WIDTH AND PRECISION COMBINATIONS
    run_category("Width and Precision Combinations");
    test_string("Hello", "%10.8s", "Width > precision > string");
    test_string("Hello", "%10.5s", "Width > precision = string");
    test_string("Hello", "%10.3s", "Width > string > precision");
    test_string("Hello", "%5.8s", "Precision > width = string");
    test_string("Hello", "%5.3s", "Width = string > precision");
    test_string("Hello", "%3.8s", "Precision > string > width");
    test_string("Hello", "%3.3s", "Width = precision < string");
    
    // FLAGS COMBINATION TESTS
    run_category("Flag Combinations");
    test_string("Hello", "%-10.8s", "Left-justified, width > precision");
    test_string("Hello", "%-10.3s", "Left-justified, width > precision, truncated");
    test_string("Hello", "%010.8s", "Zero-padded, width > precision");
    test_string("Hello", "%010.3s", "Zero-padded, width > precision, truncated");
    test_string("Hello", "%-010s", "Left-justified takes precedence over zero padding");
    test_string("Hello", "%010.0s", "Zero-padded, zero precision");
    
    // EDGE CASES
    run_category("Edge Cases");
    
    // Very long strings
    char long_str[1000];
    memset(long_str, 'A', 999);
    long_str[999] = '\0';
    test_string(long_str, "%s", "Very long string (999 chars)");
    test_string(long_str, "%.500s", "Very long string with precision truncation");
    
    // Strings with all kinds of characters
    char mixed_str[128];
    for (int i = 1; i < 127; i++) {  // Start from 1 to avoid NULL byte
        mixed_str[i-1] = (char)i;
    }
    mixed_str[126] = '\0';
    test_string(mixed_str, "%s", "String with all ASCII characters");
    test_string(mixed_str, "%.50s", "ASCII string with precision");
    
    // MULTIPLE STRING TESTS - Fixed to avoid VA_LIST issues
    run_category("Multiple Strings Tests");
    
    // Test with multiple strings but only a limited number
    test_multiple_strings("%s %s %s", "Multiple strings basic",
                         "first", "second", "third", NULL, NULL,
                         NULL, NULL, NULL, NULL, NULL);
    
    // Test with alternating strings and text
    test_multiple_strings("Test: %s and %s and %s and %s", 
                         "Multiple strings with text",
                         "first", "second", "third", "fourth",
                         NULL, NULL, NULL, NULL, NULL, NULL);
    
    // Test with mixed formats
    test_multiple_strings("%s %10s %-10s %.5s %10.5s",
                         "Mixed string formats",
                         "normal", "widened", "left", "truncated", "both",
                         NULL, NULL, NULL, NULL, NULL);
    
    // STRESS TESTS
    run_category("Stress Tests");
    
    // Null termination edge cases
    char one_char[2] = {'A', '\0'};
    test_string(one_char, "%s", "One char string");
    test_string(one_char, "%5s", "One char string with width");
    test_string(one_char, "%.s", "One char string with empty precision");
    
    // Extreme width and precision values
    test_string("Hello", "%1000s", "Width 1000");
    test_string("Hello", "%.1000s", "Precision 1000");
    test_string("Hello", "%1000.500s", "Width 1000, precision 500");
    test_string("Hello", "%-1000s", "Left-justified width 1000");
    test_string("Hello", "%01000s", "Zero-padded width 1000");
    
    // NULL handling with flags
    test_string(NULL, "%10s", "NULL with width");
    test_string(NULL, "%-10s", "NULL with left-justification");
    test_string(NULL, "%.3s", "NULL with precision");
    test_string(NULL, "%10.3s", "NULL with width and precision");
    
    // Print final summary
    printf("\n%s=== TEST SUMMARY ===%s\n", BLUE, RESET);
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, (float)pass_count/test_count*100, RESET);
    printf("Failed: %s%d (%.1f%%)%s\n", fail_count > 0 ? RED : GREEN, fail_count, (float)fail_count/test_count*100, RESET);

    return fail_count > 0 ? 1 : 0;
}
