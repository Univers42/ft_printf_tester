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
#define RESET "\033[0m"

int test_count = 0;
int pass_count = 0;
int fail_count = 0;

// Test function with improved diagnostics for integers
void test_int(int value, const char *format, const char *test_name) {
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
        printf("  Input:     %d (0x%x)\n", value, value);
        
        // Print expected output with visible spaces
        printf("  Expected:  \"");
        for (int i = 0; i < (int)strlen(expected); i++) {
            if (expected[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (expected[i] == '0')
                printf("%s0%s", BLUE, RESET); // Highlight zeros
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
                printf("%s0%s", BLUE, RESET); // Highlight zeros
            else
                printf("%c", actual[i]);
        }
        printf("\" (ret: %d)\n", actual_ret);
        fail_count++;
    }
}

// Test multiple integer formats in a single test
void test_multiple_ints(const char *format, const char *test_name, ...) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    va_list args, args2;
    
    test_count++;
    
    // Get expected output
    va_start(args, test_name);
    expected_ret = vsnprintf(expected, BUFFER_SIZE, format, args);
    va_end(args);
    
    // Get actual output
    fp = tmpfile();
    int original_stdout = dup(1);
    dup2(fileno(fp), 1);
    
    va_start(args2, test_name);
    actual_ret = ft_printf(format, args2);
    va_end(args2);
    
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
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (expected[i] == '0')
                printf("%s0%s", BLUE, RESET); // Highlight zeros
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
                printf("%s0%s", BLUE, RESET); // Highlight zeros
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
    printf("%s=== FT_PRINTF INTEGER FORMAT TESTS (%s & %s) ===%s\n", 
           MAGENTA, "%d", "%i", RESET);
    
    // BASIC INTEGER TESTS
    run_category("Basic Integer Tests");
    test_int(0, "%d", "Zero with %%d");
    test_int(0, "%i", "Zero with %%i");
    test_int(42, "%d", "Positive integer with %%d");
    test_int(42, "%i", "Positive integer with %%i");
    test_int(-42, "%d", "Negative integer with %%d");
    test_int(-42, "%i", "Negative integer with %%i");
    test_int(INT_MAX, "%d", "INT_MAX with %%d");
    test_int(INT_MAX, "%i", "INT_MAX with %%i");
    test_int(INT_MIN, "%d", "INT_MIN with %%d");
    test_int(INT_MIN, "%i", "INT_MIN with %%i");
    
    // WIDTH TESTS
    run_category("Width Tests");
    test_int(42, "%5d", "Width larger than number");
    test_int(42, "%2d", "Width smaller than number");
    test_int(42, "%5i", "Width larger than number (%%i)");
    test_int(-42, "%5d", "Width larger than negative number");
    test_int(-42, "%2d", "Width smaller than negative number");
    test_int(0, "%5d", "Zero with width");
    test_int(INT_MAX, "%15d", "INT_MAX with width");
    test_int(INT_MIN, "%15d", "INT_MIN with width");
    
    // PRECISION TESTS
    run_category("Precision Tests");
    test_int(42, "%.5d", "Precision larger than number");
    test_int(42, "%.1d", "Precision smaller than number");
    test_int(-42, "%.5d", "Precision with negative number");
    test_int(-42, "%.1d", "Precision smaller than negative number");
    test_int(0, "%.0d", "Zero with precision 0 (should print nothing)");
    test_int(0, "%.d", "Zero with precision (should print nothing)");
    test_int(0, "%.5d", "Zero with precision larger than zero");
    
    // FLAGS TESTS
    run_category("Flag Tests");
    
    // Left justification flag (-)
    test_int(42, "%-5d", "Left-justified with width");
    test_int(-42, "%-5d", "Left-justified negative with width");
    test_int(0, "%-5d", "Left-justified zero with width");
    
    // Zero padding flag (0)
    test_int(42, "%05d", "Zero-padded with width");
    test_int(-42, "%05d", "Zero-padded negative with width");
    test_int(0, "%05d", "Zero-padded zero with width");
    
    // Space flag ( )
    test_int(42, "% d", "Space flag with positive number");
    test_int(-42, "% d", "Space flag with negative number");
    test_int(0, "% d", "Space flag with zero");
    
    // Plus flag (+)
    test_int(42, "%+d", "Plus flag with positive number");
    test_int(-42, "%+d", "Plus flag with negative number");
    test_int(0, "%+d", "Plus flag with zero");
    
    // Hash flag (#) - should have no effect on integers
    test_int(42, "%#d", "Hash flag with %%d (should be ignored)");
    test_int(42, "%#i", "Hash flag with %%i (should be ignored)");
    
    // COMBINATION TESTS
    run_category("Flag Combination Tests");
    
    // Width and precision
    test_int(42, "%5.3d", "Width > precision > number");
    test_int(42, "%3.5d", "Precision > width > number");
    test_int(42, "%5.5d", "Width = precision > number");
    test_int(42, "%2.2d", "Width = precision < number");
    test_int(-42, "%5.3d", "Width > precision > negative number");
    test_int(-42, "%3.5d", "Precision > width > negative number");
    test_int(0, "%5.0d", "Width with zero precision for zero");
    test_int(0, "%5.3d", "Width with precision for zero");
    
    // Left justify + precision
    test_int(42, "%-5.3d", "Left-justified with precision");
    test_int(-42, "%-5.3d", "Left-justified negative with precision");
    test_int(0, "%-5.0d", "Left-justified zero with zero precision");
    
    // Zero padding + precision (precision should override zero padding)
    test_int(42, "%05.3d", "Zero-padding with precision (precision wins)");
    test_int(-42, "%05.3d", "Zero-padding negative with precision");
    
    // Plus/space flags with other flags
    test_int(42, "%+5d", "Plus flag with width");
    test_int(42, "%+05d", "Plus flag with zero padding");
    test_int(42, "%+5.3d", "Plus flag with width and precision");
    test_int(42, "% 5d", "Space flag with width");
    test_int(42, "% 05d", "Space flag with zero padding");
    test_int(42, "% 5.3d", "Space flag with width and precision");
    
    // Flags precedence (+ takes precedence over space)
    test_int(42, "%+ d", "Plus and space flags together (plus wins)");
    test_int(42, "% +d", "Space and plus flags together (plus wins)");
    
    // Left justify takes precedence over zero padding
    test_int(42, "%-05d", "Left-justify and zero padding (left-justify wins)");
    test_int(-42, "%-05d", "Left-justify and zero padding with negative");
    
    // Complex combinations
    test_int(42, "%+- 05.3d", "Complex flags with positive");
    test_int(-42, "%+- 05.3d", "Complex flags with negative");
    test_int(0, "%+- 05.0d", "Complex flags with zero and zero precision");
    
    // EXTREME VALUES
    run_category("Extreme Value Tests");
    test_int(INT_MAX, "%d", "INT_MAX basic");
    test_int(INT_MAX, "%+d", "INT_MAX with plus");
    test_int(INT_MAX, "%15d", "INT_MAX with large width");
    test_int(INT_MAX, "%015d", "INT_MAX with zero padding");
    test_int(INT_MAX, "%.15d", "INT_MAX with large precision");
    test_int(INT_MAX, "%15.10d", "INT_MAX with width and precision");
    
    test_int(INT_MIN, "%d", "INT_MIN basic");
    test_int(INT_MIN, "%+d", "INT_MIN with plus");
    test_int(INT_MIN, "%15d", "INT_MIN with large width");
    test_int(INT_MIN, "%015d", "INT_MIN with zero padding");
    test_int(INT_MIN, "%.15d", "INT_MIN with large precision");
    test_int(INT_MIN, "%15.10d", "INT_MIN with width and precision");
    
    // MULTI-INTEGER TESTS
    run_category("Multiple Integer Tests");
    
    // Test with manually calling the function since our test helper doesn't support varargs correctly
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    // Test multiple integers with different formats
    sprintf(expected, "Numbers: %d, %i, %d", 42, -42, 0);
    
    fp = tmpfile();
    int original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Numbers: %d, %i, %d", 42, -42, 0);
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
        printf("%s[PASS]%s Multiple integers with %%d and %%i\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Multiple integers with %%d and %%i\n", RED, RESET);
        printf("  Format:    \"Numbers: %%d, %%i, %%d\"\n");
        printf("  Expected:  \"%s\" (ret: %d)\n", expected, expected_ret);
        printf("  Actual:    \"%s\" (ret: %d)\n", actual, actual_ret);
        fail_count++;
    }
    
    // Test with mixed formats
    sprintf(expected, "Formatted: [%5d] [%-5d] [%05d] [%+d] [%.5d]", 42, 42, 42, 42, 42);
    
    fp = tmpfile();
    original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Formatted: [%5d] [%-5d] [%05d] [%+d] [%.5d]", 42, 42, 42, 42, 42);
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
        printf("%s[PASS]%s Multiple integers with different formats\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Multiple integers with different formats\n", RED, RESET);
        printf("  Format:    \"Formatted: [%%5d] [%%-5d] [%%05d] [%%+d] [%%.5d]\"\n");
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
