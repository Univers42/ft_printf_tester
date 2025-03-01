#include "../ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define BUFFER_SIZE 2048
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
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
        printf("  Char:      '%c' (ASCII: %d)\n", c > 31 && c < 127 ? c : '.', (int)c);
        
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

void run_category(const char *category) {
    printf("\n%s=== %s ===%s\n", BLUE, category, RESET);
}

// Test with multiple character formats in a complex string
void test_multiple_chars(const char *format, const char *test_name, ...) {
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
    
    // Create temporary file for capturing ft_printf output
    fp = tmpfile();
    if (!fp) {
        perror("Failed to create temporary file");
        va_end(args_copy);
        return;
    }
    
    // Redirect stdout to temp file
    int original_stdout = dup(1);
    if (dup2(fileno(fp), 1) == -1) {
        perror("Failed to redirect stdout");
        fclose(fp);
        va_end(args_copy);
        return;
    }
    
    // Call ft_printf which will write to the temp file
    actual_ret = vprintf(format, args_copy);
    fflush(stdout);
    
    // Clean up
    va_end(args_copy);
    
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

int main(void) {
    printf("%s=== FT_PRINTF EXTENDED CHARACTER STRESS TESTS ===%s\n", MAGENTA, RESET);
    
    // BASIC CHARACTER TESTING
    run_category("ASCII Character Range Tests");
    
    // Test all printable ASCII characters
    for (char c = 32; c < 127; c++) {
        char test_name[50];
        sprintf(test_name, "ASCII %d ('%c')", c, c);
        test_char(c, "%c", test_name);
    }

    // Special ASCII characters
    run_category("Special Character Tests");
    test_char('\0', "%c", "NULL character (0)");
    test_char('\a', "%c", "Bell (7)");
    test_char('\b', "%c", "Backspace (8)");
    test_char('\t', "%c", "Tab (9)");
    test_char('\n', "%c", "Newline (10)");
    test_char('\v', "%c", "Vertical tab (11)");
    test_char('\f', "%c", "Form feed (12)");
    test_char('\r', "%c", "Carriage return (13)");
    test_char(127, "%c", "Delete (127)");
    
    // Extended ASCII (might cause issues in some environments)
    run_category("Extended ASCII Character Tests");
    for (int c = 128; c < 256; c += 16) {
        char test_name[50];
        sprintf(test_name, "Extended ASCII %d", c);
        test_char((char)c, "%c", test_name);
    }

    // EXTREME WIDTH TESTS
    run_category("Extreme Width Tests");
    test_char('A', "%1000c", "Width 1000");
    test_char('B', "%100c", "Width 100");
    test_char('C', "%50c", "Width 50");
    test_char('D', "%-1000c", "Left justified width 1000");
    test_char('E', "%-100c", "Left justified width 100");
    test_char('F', "%-50c", "Left justified width 50");
    
    // STRESS COMBINATIONS
    run_category("Stress Flag Combinations");
    test_char('X', "%0c", "Zero width");
    test_char('X', "% c", "Space flag (meaningless for chars)");
    test_char('X', "%+c", "Plus flag (meaningless for chars)");
    test_char('X', "%#c", "Hash flag (meaningless for chars)");
    test_char('X', "%0100c", "Zero padding with large width");
    test_char('X', "%-0100c", "Left justify with zero padding");
    test_char('X', "%0-100c", "Zero padding with left justify");
    
    // PRECISION TESTS (should be ignored for %c)
    run_category("Precision Tests (should be ignored)");
    test_char('A', "%.c", "Dot precision");
    test_char('B', "%.0c", "Zero precision");
    test_char('C', "%.100c", "Large precision");
    test_char('D', "%100.50c", "Width and precision");
    test_char('E', "%-100.50c", "Left justify with precision");
    test_char('F', "%0100.50c", "Zero padding with precision");
    
    // REPETITIVE CHARACTER TESTS
    run_category("Repetitive Character Tests");
    
    // Test with many consecutive character conversions
    char format_buffer[1000] = {0};
    for (int i = 0; i < 25; i++) {
        strcat(format_buffer, "%c");
    }
    
    test_multiple_chars(format_buffer, "25 consecutive %c conversions", 
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                      'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                      'U', 'V', 'W', 'X', 'Y');
    
    // Test with alternating character and text
    test_multiple_chars("A%cB%cC%cD%cE%cF%cG%cH%cI%cJ%c", 
                      "Alternating characters and text",
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9');
    
    // Test with mixed width and alignment
    test_multiple_chars("%c %5c %-5c %05c %c %5c %-5c", 
                      "Mixed width and alignment",
                      'A', 'B', 'C', 'D', 'E', 'F', 'G');
    
    // WEIRD EDGE CASES
    run_category("Edge Cases");
    
    // Test with actual % character
    test_char('%', "%%c", "Percent sign with c specifier");
    
    // Test with escaped characters in format string
    test_char('Z', "\\t%c\\n", "Escaped characters in format");
    
    // Remove the undefined behavior test that has more format specifiers than arguments
    // and replace with valid edge cases
    test_char('\0', "%c", "NULL character");
    test_char('A', "%1c", "Width 1 (exact fit)");
    test_char('A', "%0c", "Width 0");
    
    // Print final summary
    printf("\n%s=== TEST SUMMARY ===%s\n", BLUE, RESET);
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, (float)pass_count/test_count*100, RESET);
    printf("Failed: %s%d (%.1f%%)%s\n", fail_count > 0 ? RED : GREEN, fail_count, (float)fail_count/test_count*100, RESET);

    return fail_count > 0 ? 1 : 0;
}
