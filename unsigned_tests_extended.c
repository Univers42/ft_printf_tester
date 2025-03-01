#include "../ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define BUFFER_SIZE 4096
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

int test_count = 0;
int pass_count = 0;
int fail_count = 0;

// Test function with improved diagnostics for unsigned integers
void test_unsigned(unsigned int value, const char *format, const char *test_name) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    test_count++;
    
    // Get expected output using sprintf
    expected_ret = sprintf(expected, format, value);
    
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
    actual_ret = ft_printf(format, value);
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
        printf("  Input:     %u (0x%x)\n", value, value);
        
        // Print expected output with visible spaces and zeros
        printf("  Expected:  \"");
        for (int i = 0; i < (int)strlen(expected); i++) {
            if (expected[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (expected[i] == '0')
                printf("%s0%s", CYAN, RESET); // Highlight zeros
            else
                printf("%c", expected[i]);
        }
        printf("\" (ret: %d)\n", expected_ret);
        
        // Print actual output with visible spaces and zeros
        printf("  Actual:    \"");
        for (int i = 0; i < (int)strlen(actual); i++) {
            if (actual[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (actual[i] == '0')
                printf("%s0%s", CYAN, RESET); // Highlight zeros
            else
                printf("%c", actual[i]);
        }
        printf("\" (ret: %d)\n", actual_ret);
        fail_count++;
    }
}

// Test multiple format specifiers in a single string
void test_mixed_formats(const char *format, const char *test_name, ...) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    va_list args, args_copy;
    
    test_count++;
    
    // Initialize argument lists
    va_start(args, test_name);
    va_copy(args_copy, args);
    
    // Get expected output using vsnprintf
    expected_ret = vsnprintf(expected, BUFFER_SIZE, format, args);
    va_end(args);
    
    // Get actual output using ft_printf
    fp = tmpfile();
    int original_stdout = dup(1);
    dup2(fileno(fp), 1);
    
    actual_ret = ft_printf(format, args_copy);
    va_end(args_copy);
    
    fflush(stdout);
    dup2(original_stdout, 1);
    close(original_stdout);
    
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
                printf("%s·%s", YELLOW, RESET);
            else if (expected[i] == '0')
                printf("%s0%s", CYAN, RESET);
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
                printf("%s0%s", CYAN, RESET);
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
    printf("%s=== FT_PRINTF UNSIGNED INTEGER FORMAT TESTS (%s) ===%s\n", 
           MAGENTA, "%u", RESET);
    
    // BASIC UNSIGNED INTEGER TESTS
    run_category("Basic Unsigned Integer Tests");
    test_unsigned(0, "%u", "Zero");
    test_unsigned(42, "%u", "Small positive value");
    test_unsigned(4294967295U, "%u", "UINT_MAX (largest unsigned int)");
    test_unsigned(2147483648U, "%u", "First value above INT_MAX");
    test_unsigned(1000000000, "%u", "One billion");
    test_unsigned(123456789, "%u", "Large number with all different digits");
    
    // WIDTH TESTS
    run_category("Width Tests");
    test_unsigned(42, "%5u", "Width larger than number");
    test_unsigned(42, "%2u", "Width smaller than number");
    test_unsigned(0, "%5u", "Zero with width");
    test_unsigned(4294967295U, "%15u", "UINT_MAX with width");
    test_unsigned(123456, "%10u", "6-digit number with width 10");
    
    // PRECISION TESTS
    run_category("Precision Tests");
    test_unsigned(42, "%.5u", "Precision larger than number");
    test_unsigned(42, "%.1u", "Precision smaller than number");
    test_unsigned(0, "%.0u", "Zero with precision 0 (should print nothing)");
    test_unsigned(0, "%.u", "Zero with precision (should print nothing)");
    test_unsigned(0, "%.5u", "Zero with precision larger than zero");
    test_unsigned(12345, "%.3u", "5-digit number with precision 3");
    test_unsigned(12345, "%.7u", "5-digit number with precision 7");
    
    // FLAGS TESTS
    run_category("Flag Tests");
    
    // Left justification flag (-)
    test_unsigned(42, "%-5u", "Left-justified with width");
    test_unsigned(0, "%-5u", "Left-justified zero with width");
    test_unsigned(4294967295U, "%-15u", "Left-justified UINT_MAX with width");
    
    // Zero padding flag (0)
    test_unsigned(42, "%05u", "Zero-padded with width");
    test_unsigned(0, "%05u", "Zero-padded zero with width");
    test_unsigned(123456, "%010u", "Zero-padded 6-digit number");
    
    // Hash flag (#) - should have no effect on unsigned integers
    test_unsigned(42, "%#u", "Hash flag with unsigned (should be ignored)");
    test_unsigned(0, "%#u", "Hash flag with zero (should be ignored)");
    
    // Plus flag (+) - should have no effect on unsigned integers
    test_unsigned(42, "%+u", "Plus flag with unsigned (should be ignored)");
    test_unsigned(0, "%+u", "Plus flag with zero (should be ignored)");
    
    // Space flag ( ) - should have no effect on unsigned integers
    test_unsigned(42, "% u", "Space flag with unsigned (should be ignored)");
    test_unsigned(0, "% u", "Space flag with zero (should be ignored)");
    
    // COMBINATION TESTS
    run_category("Flag Combination Tests");
    
    // Width and precision
    test_unsigned(42, "%5.3u", "Width > precision > number");
    test_unsigned(42, "%3.5u", "Precision > width > number");
    test_unsigned(42, "%5.5u", "Width = precision > number");
    test_unsigned(42, "%2.2u", "Width = precision < number");
    test_unsigned(0, "%5.0u", "Width with zero precision for zero");
    test_unsigned(0, "%5.3u", "Width with precision for zero");
    
    // Left justify + precision
    test_unsigned(42, "%-5.3u", "Left-justified with precision");
    test_unsigned(0, "%-5.0u", "Left-justified zero with zero precision");
    
    // Zero padding + precision (precision should override zero padding)
    test_unsigned(42, "%05.3u", "Zero-padding with precision (precision wins)");
    
    // Flags precedence
    test_unsigned(42, "%-05u", "Left-justify and zero padding (left-justify wins)");
    test_unsigned(42, "%0-5u", "Zero padding and left-justify (left-justify wins)");
    
    // Complex combinations
    test_unsigned(42, "%-+ #05.3u", "Complex flags with unsigned");
    test_unsigned(0, "%-+ #05.0u", "Complex flags with zero and zero precision");
    
    // EXTREME VALUES
    run_category("Extreme Value Tests");
    test_unsigned(4294967295U, "%u", "UINT_MAX basic");
    test_unsigned(4294967295U, "%15u", "UINT_MAX with large width");
    test_unsigned(4294967295U, "%015u", "UINT_MAX with zero padding");
    test_unsigned(4294967295U, "%.15u", "UINT_MAX with large precision");
    test_unsigned(4294967295U, "%20.15u", "UINT_MAX with width and precision");
    
    // Test with some large power-of-two values
    test_unsigned(1U << 31, "%u", "2^31");
    test_unsigned((1U << 31) + 1, "%u", "2^31 + 1");
    test_unsigned((1U << 31) - 1, "%u", "2^31 - 1 (INT_MAX)");
    test_unsigned((1U << 16), "%u", "2^16 (65536)");
    test_unsigned((1U << 24), "%u", "2^24 (16777216)");
    
    // MULTI-FORMAT TESTS
    run_category("Multiple Format Specifier Tests");
    
    // Test with manually executing the test
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    // Test multiple unsigned values in a format string
    sprintf(expected, "Values: %u, %u, %u", 42, 0, 4294967295U);
    
    fp = tmpfile();
    int original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Values: %u, %u, %u", 42, 0, 4294967295U);
    fflush(stdout);
    dup2(original_stdout, 1);
    close(original_stdout);
    
    fseek(fp, 0, SEEK_SET);
    int bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
    actual[bytes_read] = '\0';
    fclose(fp);
    expected_ret = strlen(expected);
    
    test_count++;
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s Multiple unsigned values\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Multiple unsigned values\n", RED, RESET);
        printf("  Format:    \"Values: %%u, %%u, %%u\"\n");
        printf("  Expected:  \"%s\" (ret: %d)\n", expected, expected_ret);
        printf("  Actual:    \"%s\" (ret: %d)\n", actual, actual_ret);
        fail_count++;
    }
    
    // Test with mixed formats
    sprintf(expected, "Formatted: [%5u] [%-5u] [%05u] [%.5u] [%5.3u]", 42, 42, 42, 42, 42);
    
    fp = tmpfile();
    original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Formatted: [%5u] [%-5u] [%05u] [%.5u] [%5.3u]", 42, 42, 42, 42, 42);
    fflush(stdout);
    dup2(original_stdout, 1);
    close(original_stdout);
    
    fseek(fp, 0, SEEK_SET);
    bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
    actual[bytes_read] = '\0';
    fclose(fp);
    expected_ret = strlen(expected);
    
    test_count++;
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s Unsigned with different formats\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Unsigned with different formats\n", RED, RESET);
        printf("  Format:    \"Formatted: [%%5u] [%%-5u] [%%05u] [%%.5u] [%%5.3u]\"\n");
        printf("  Expected:  \"%s\" (ret: %d)\n", expected, expected_ret);
        printf("  Actual:    \"%s\" (ret: %d)\n", actual, actual_ret);
        fail_count++;
    }
    
    // Mixed with other specifiers
    sprintf(expected, "Mixed: %d %s %u %c", -42, "test", 123456, 'X');
    
    fp = tmpfile();
    original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Mixed: %d %s %u %c", -42, "test", 123456, 'X');
    fflush(stdout);
    dup2(original_stdout, 1);
    close(original_stdout);
    
    fseek(fp, 0, SEEK_SET);
    bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
    actual[bytes_read] = '\0';
    fclose(fp);
    expected_ret = strlen(expected);
    
    test_count++;
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s Unsigned mixed with other specifiers\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Unsigned mixed with other specifiers\n", RED, RESET);
        printf("  Format:    \"Mixed: %%d %%s %%u %%c\"\n");
        printf("  Expected:  \"%s\" (ret: %d)\n", expected, expected_ret);
        printf("  Actual:    \"%s\" (ret: %d)\n", actual, actual_ret);
        fail_count++;
    }
    
    // Print final summary
    printf("\n%s=== TEST SUMMARY ===%s\n", BLUE, RESET);
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, (float)pass_count/test_count*100, RESET);
    printf("Failed: %s%d (%.1f%%)%s\n", fail_count > 0 ? RED : GREEN, fail_count, (float)fail_count/test_count*100, RESET);

    return fail_count > 0 ? 1 : 0;
}
