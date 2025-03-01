#include "ft_printf_test_utils.h"
#include <string.h>

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
