#include "../ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

int test_count = 0;
int pass_count = 0;
int fail_count = 0;

// Test function with improved diagnostics
void test_char(char c, const char *format, const char *test_name) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    test_count++;
    
    // Get expected output using sprintf
    expected_ret = sprintf(expected, format, c);
    
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
    actual_ret = ft_printf(format, c);
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
        printf("  Char:      '%c' (ASCII: %d)\n", c, c);
        
        // Print expected output with visible spaces
        printf("  Expected:  \"");
        for (int i = 0; i < (int)strlen(expected); i++) {
            if (expected[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
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
    printf("=== FT_PRINTF EXTENDED CHAR TESTS ===\n");

    // BASIC CHARACTER TESTING
    run_category("Basic Character Tests");
    test_char('A', "%c", "Uppercase letter");
    test_char('z', "%c", "Lowercase letter");
    test_char('0', "%c", "Digit");
    test_char('!', "%c", "Exclamation mark");
    test_char('@', "%c", "At sign");
    test_char('#', "%c", "Hash symbol");
    test_char('$', "%c", "Dollar sign");
    test_char('%', "%c", "Percent sign");
    test_char('^', "%c", "Caret");
    test_char('&', "%c", "Ampersand");
    test_char('*', "%c", "Asterisk");
    test_char('(', "%c", "Opening parenthesis");
    test_char(')', "%c", "Closing parenthesis");
    test_char(' ', "%c", "Space character");
    test_char('\t', "%c", "Tab character");
    test_char('\n', "%c", "Newline character");

    // WIDTH TESTS
    run_category("Width Tests");
    test_char('A', "%1c", "Width 1 (same as char)");
    test_char('B', "%2c", "Width 2 (1 space + char)");
    test_char('C', "%5c", "Width 5 (4 spaces + char)");
    test_char('D', "%10c", "Width 10 (9 spaces + char)");
    test_char('E', "%20c", "Width 20 (19 spaces + char)");
    test_char('F', "%0c", "Width 0 (should be same as no width)");

    // LEFT JUSTIFICATION TESTS
    run_category("Left Justification Tests");
    test_char('A', "%-1c", "Left justified width 1");
    test_char('B', "%-2c", "Left justified width 2 (char + 1 space)");
    test_char('C', "%-5c", "Left justified width 5 (char + 4 spaces)");
    test_char('D', "%-10c", "Left justified width 10 (char + 9 spaces)");
    test_char('E', "%-20c", "Left justified width 20 (char + 19 spaces)");

    // ZERO PADDING TESTS (should be ignored for %c, always spaces)
    run_category("Zero Padding Tests (should use spaces for chars)");
    test_char('A', "%01c", "Zero padding width 1");
    test_char('B', "%02c", "Zero padding width 2");
    test_char('C', "%05c", "Zero padding width 5");
    test_char('D', "%010c", "Zero padding width 10");
    
    // MIXED FLAGS
    run_category("Mixed Flags Tests");
    test_char('A', "%-01c", "Left justified with zero padding width 1");
    test_char('B', "%-02c", "Left justified with zero padding width 2");
    test_char('C', "%-05c", "Left justified with zero padding width 5");
    test_char('D', "%-010c", "Left justified with zero padding width 10");

    // PRECISION TESTS (should be ignored for %c)
    run_category("Precision Tests (should be ignored for %c)");
    test_char('A', "%.c", "Precision with no value");
    test_char('B', "%.0c", "Precision 0");
    test_char('C', "%.5c", "Precision 5");
    test_char('D', "%5.10c", "Width 5, precision 10");
    test_char('E', "%10.5c", "Width 10, precision 5");
    test_char('F', "%-5.10c", "Left justified width 5, precision 10");
    test_char('G', "%-10.5c", "Left justified width 10, precision 5");
    test_char('H', "%05.10c", "Zero-padded width 5, precision 10");

    // MULTIPLE CHARACTERS AND CONTEXT TESTS
    run_category("Multiple Characters Tests");
    
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    // Multiple characters in different patterns
    printf("\n%sTesting multiple characters in different formats:%s\n", YELLOW, RESET);
    
    // Test 1: Basic multiple characters
    test_count++;
    expected_ret = sprintf(expected, "%c%c%c", 'A', 'B', 'C');
    fp = tmpfile();
    int original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("%c%c%c", 'A', 'B', 'C');
    fflush(stdout);
    dup2(original_stdout, 1);
    close(original_stdout);
    fseek(fp, 0, SEEK_SET);
    int bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
    actual[bytes_read] = '\0';
    fclose(fp);
    
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s Multiple consecutive characters\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Multiple consecutive characters\n", RED, RESET);
        printf("  Format:    \"%%c%%c%%c\"\n");
        printf("  Expected:  \"%s\" (ret: %d)\n", expected, expected_ret);
        printf("  Actual:    \"%s\" (ret: %d)\n", actual, actual_ret);
        fail_count++;
    }
    
    // Test 2: Characters with text
    test_count++;
    expected_ret = sprintf(expected, "Testing: %c is first, %c is second, %c is third", 'X', 'Y', 'Z');
    fp = tmpfile();
    original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Testing: %c is first, %c is second, %c is third", 'X', 'Y', 'Z');
    fflush(stdout);
    dup2(original_stdout, 1);
    close(original_stdout);
    fseek(fp, 0, SEEK_SET);
    bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
    actual[bytes_read] = '\0';
    fclose(fp);
    
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s Characters with text\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Characters with text\n", RED, RESET);
        printf("  Format:    \"Testing: %%c is first, %%c is second, %%c is third\"\n");
        printf("  Expected:  \"%s\" (ret: %d)\n", expected, expected_ret);
        printf("  Actual:    \"%s\" (ret: %d)\n", actual, actual_ret);
        fail_count++;
    }
    
    // Test 3: Characters with different formats
    test_count++;
    expected_ret = sprintf(expected, "[%c] [%5c] [%-5c]", 'A', 'B', 'C');
    fp = tmpfile();
    original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("[%c] [%5c] [%-5c]", 'A', 'B', 'C');
    fflush(stdout);
    dup2(original_stdout, 1);
    close(original_stdout);
    fseek(fp, 0, SEEK_SET);
    bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
    actual[bytes_read] = '\0';
    fclose(fp);
    
    if (strcmp(expected, actual) == 0 && expected_ret == actual_ret) {
        printf("%s[PASS]%s Characters with mixed formats\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Characters with mixed formats\n", RED, RESET);
        printf("  Format:    \"[%%c] [%%5c] [%%-5c]\"\n");
        printf("  Expected:  \"%s\" (ret: %d)\n", expected, expected_ret);
        printf("  Actual:    \"%s\" (ret: %d)\n", actual, actual_ret);
        fail_count++;
    }
    
    // Print summary
    printf("\n%s=== TEST SUMMARY ===%s\n", BLUE, RESET);
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, (float)pass_count/test_count*100, RESET);
    printf("Failed: %s%d (%.1f%%)%s\n", fail_count > 0 ? RED : GREEN, fail_count, (float)fail_count/test_count*100, RESET);

    return fail_count > 0 ? 1 : 0;
}
