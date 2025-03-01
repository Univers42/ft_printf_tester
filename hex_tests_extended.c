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

// Test function with improved diagnostics for hexadecimal values
void test_hex(unsigned int value, const char *format, const char *test_name) {
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
        
        // Print expected output with special formatting
        printf("  Expected:  \"");
        for (int i = 0; i < (int)strlen(expected); i++) {
            if (expected[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (expected[i] == '0')
                printf("%s0%s", CYAN, RESET); // Highlight zeros
            else if ((expected[i] >= 'a' && expected[i] <= 'f') ||
                     (expected[i] >= 'A' && expected[i] <= 'F'))
                printf("%s%c%s", MAGENTA, expected[i], RESET); // Highlight hex letters
            else if (expected[i] == 'x' || expected[i] == 'X')
                printf("%s%c%s", BLUE, expected[i], RESET); // Highlight x/X
            else
                printf("%c", expected[i]);
        }
        printf("\" (ret: %d)\n", expected_ret);
        
        // Print actual output with special formatting
        printf("  Actual:    \"");
        for (int i = 0; i < (int)strlen(actual); i++) {
            if (actual[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (actual[i] == '0')
                printf("%s0%s", CYAN, RESET); // Highlight zeros
            else if ((actual[i] >= 'a' && actual[i] <= 'f') ||
                     (actual[i] >= 'A' && actual[i] <= 'F'))
                printf("%s%c%s", MAGENTA, actual[i], RESET); // Highlight hex letters
            else if (actual[i] == 'x' || actual[i] == 'X')
                printf("%s%c%s", BLUE, actual[i], RESET); // Highlight x/X
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
    printf("%s=== FT_PRINTF HEXADECIMAL TESTS (%s & %s) ===%s\n", 
           MAGENTA, "%x", "%X", RESET);
    
    // BASIC HEX TESTS
    run_category("Basic Hex Tests (lowercase)");
    test_hex(0, "%x", "Zero in lowercase");
    test_hex(42, "%x", "Small positive in lowercase");
    test_hex(0xff, "%x", "0xff (255) in lowercase");
    test_hex(0xabcdef, "%x", "0xabcdef in lowercase");
    test_hex(0x12345, "%x", "0x12345 in lowercase");
    test_hex(UINT_MAX, "%x", "UINT_MAX in lowercase");

    run_category("Basic Hex Tests (uppercase)");
    test_hex(0, "%X", "Zero in uppercase");
    test_hex(42, "%X", "Small positive in uppercase");
    test_hex(0xff, "%X", "0xff (255) in uppercase");
    test_hex(0xabcdef, "%X", "0xabcdef in uppercase");
    test_hex(0x12345, "%X", "0x12345 in uppercase");
    test_hex(UINT_MAX, "%X", "UINT_MAX in uppercase");
    
    // WIDTH TESTS
    run_category("Width Tests (lowercase)");
    test_hex(0xabc, "%10x", "Width larger than hex in lowercase");
    test_hex(0xabc, "%2x", "Width smaller than hex in lowercase");
    test_hex(0, "%5x", "Zero with width in lowercase");
    
    run_category("Width Tests (uppercase)");
    test_hex(0xabc, "%10X", "Width larger than hex in uppercase");
    test_hex(0xabc, "%2X", "Width smaller than hex in uppercase");
    test_hex(0, "%5X", "Zero with width in uppercase");
    
    // PRECISION TESTS
    run_category("Precision Tests (lowercase)");
    test_hex(0xabc, "%.10x", "Precision larger than hex in lowercase");
    test_hex(0xabc, "%.2x", "Precision smaller than hex in lowercase");
    test_hex(0, "%.0x", "Zero with precision 0 in lowercase (should print nothing)");
    test_hex(0, "%.x", "Zero with precision in lowercase (should print nothing)");
    test_hex(0, "%.5x", "Zero with precision larger than zero in lowercase");
    
    run_category("Precision Tests (uppercase)");
    test_hex(0xabc, "%.10X", "Precision larger than hex in uppercase");
    test_hex(0xabc, "%.2X", "Precision smaller than hex in uppercase");
    test_hex(0, "%.0X", "Zero with precision 0 in uppercase (should print nothing)");
    test_hex(0, "%.X", "Zero with precision in uppercase (should print nothing)");
    test_hex(0, "%.5X", "Zero with precision larger than zero in uppercase");
    
    // FLAGS TESTS
    run_category("Flag Tests (lowercase)");
    
    // Left justification flag (-)
    test_hex(0xabc, "%-10x", "Left-justified with width in lowercase");
    test_hex(0, "%-5x", "Left-justified zero with width in lowercase");
    
    // Zero padding flag (0)
    test_hex(0xabc, "%010x", "Zero-padded with width in lowercase");
    test_hex(0, "%05x", "Zero-padded zero with width in lowercase");
    
    // Hash flag (#) - adds 0x or 0X prefix
    test_hex(0xabc, "%#x", "Hash flag with hex in lowercase");
    test_hex(0, "%#x", "Hash flag with zero in lowercase (should NOT add prefix)");
    test_hex(0xabc, "%#10x", "Hash flag with width in lowercase");
    test_hex(0xabc, "%#010x", "Hash flag with zero padding in lowercase");
    
    run_category("Flag Tests (uppercase)");
    
    // Left justification flag (-)
    test_hex(0xabc, "%-10X", "Left-justified with width in uppercase");
    test_hex(0, "%-5X", "Left-justified zero with width in uppercase");
    
    // Zero padding flag (0)
    test_hex(0xabc, "%010X", "Zero-padded with width in uppercase");
    test_hex(0, "%05X", "Zero-padded zero with width in uppercase");
    
    // Hash flag (#) - adds 0x or 0X prefix
    test_hex(0xabc, "%#X", "Hash flag with hex in uppercase");
    test_hex(0, "%#X", "Hash flag with zero in uppercase (should NOT add prefix)");
    test_hex(0xabc, "%#10X", "Hash flag with width in uppercase");
    test_hex(0xabc, "%#010X", "Hash flag with zero padding in uppercase");
    
    // COMBINATION TESTS
    run_category("Flag Combination Tests (lowercase)");
    
    // Width and precision
    test_hex(0xabc, "%10.5x", "Width > precision > hex in lowercase");
    test_hex(0xabc, "%5.10x", "Precision > width > hex in lowercase");
    test_hex(0xabc, "%10.10x", "Width = precision > hex in lowercase");
    test_hex(0xabc, "%2.2x", "Width = precision < hex in lowercase");
    test_hex(0, "%5.0x", "Width with zero precision for zero in lowercase");
    test_hex(0, "%5.5x", "Width with precision for zero in lowercase");
    
    // Left justify + precision
    test_hex(0xabc, "%-10.5x", "Left-justified with precision in lowercase");
    test_hex(0, "%-5.0x", "Left-justified zero with zero precision in lowercase");
    
    // Zero padding + precision (precision should override zero padding)
    test_hex(0xabc, "%010.5x", "Zero-padding with precision in lowercase (precision wins)");
    
    // Hash flag + other flags
    test_hex(0xabc, "%#-10x", "Hash flag with left justify in lowercase");
    test_hex(0xabc, "%#010x", "Hash flag with zero padding in lowercase");
    test_hex(0xabc, "%#10.5x", "Hash flag with width and precision in lowercase");
    
    // Flags precedence
    test_hex(0xabc, "%-#010x", "Left-justify, hash, and zero padding in lowercase");
    
    run_category("Flag Combination Tests (uppercase)");
    
    // Width and precision
    test_hex(0xabc, "%10.5X", "Width > precision > hex in uppercase");
    test_hex(0xabc, "%5.10X", "Precision > width > hex in uppercase");
    test_hex(0xabc, "%10.10X", "Width = precision > hex in uppercase");
    test_hex(0xabc, "%2.2X", "Width = precision < hex in uppercase");
    test_hex(0, "%5.0X", "Width with zero precision for zero in uppercase");
    test_hex(0, "%5.5X", "Width with precision for zero in uppercase");
    
    // Left justify + precision
    test_hex(0xabc, "%-10.5X", "Left-justified with precision in uppercase");
    test_hex(0, "%-5.0X", "Left-justified zero with zero precision in uppercase");
    
    // Zero padding + precision (precision should override zero padding)
    test_hex(0xabc, "%010.5X", "Zero-padding with precision in uppercase (precision wins)");
    
    // Hash flag + other flags
    test_hex(0xabc, "%#-10X", "Hash flag with left justify in uppercase");
    test_hex(0xabc, "%#010X", "Hash flag with zero padding in uppercase");
    test_hex(0xabc, "%#10.5X", "Hash flag with width and precision in uppercase");
    
    // Flags precedence
    test_hex(0xabc, "%-#010X", "Left-justify, hash, and zero padding in uppercase");
    
    // EXTREME VALUES
    run_category("Extreme Value Tests");
    test_hex(UINT_MAX, "%x", "UINT_MAX in lowercase");
    test_hex(UINT_MAX, "%X", "UINT_MAX in uppercase");
    test_hex(UINT_MAX, "%#x", "UINT_MAX with hash in lowercase");
    test_hex(UINT_MAX, "%#X", "UINT_MAX with hash in uppercase");
    test_hex(UINT_MAX, "%20x", "UINT_MAX with large width in lowercase");
    test_hex(UINT_MAX, "%020X", "UINT_MAX with zero padding in uppercase");
    test_hex(UINT_MAX, "%.20x", "UINT_MAX with large precision in lowercase");
    test_hex(UINT_MAX, "%#20.15X", "UINT_MAX with hash, width and precision in uppercase");
    
    // Test with some notable hex values
    test_hex(0xdead, "%x", "0xdead in lowercase");
    test_hex(0xdead, "%X", "0xdead in uppercase");
    test_hex(0xbeef, "%x", "0xbeef in lowercase");
    test_hex(0xbeef, "%X", "0xbeef in uppercase");
    test_hex(0xdeadbeef, "%x", "0xdeadbeef in lowercase");
    test_hex(0xdeadbeef, "%X", "0xdeadbeef in uppercase");
    
    // MULTI-FORMAT TESTS
    run_category("Multiple Format Specifier Tests");
    
    // Test multiple hexadecimal values in a format string
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    sprintf(expected, "Values: %x, %X, %#x", 0xabc, 0xdef, 0x123);
    
    fp = tmpfile();
    int original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Values: %x, %X, %#x", 0xabc, 0xdef, 0x123);
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
        printf("%s[PASS]%s Multiple hex values mixed\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Multiple hex values mixed\n", RED, RESET);
        printf("  Format:    \"Values: %%x, %%X, %%#x\"\n");
        
        // Print expected output with special formatting
        printf("  Expected:  \"");
        for (int i = 0; i < (int)strlen(expected); i++) {
            if (expected[i] == ' ')
                printf("%s·%s", YELLOW, RESET);
            else if (expected[i] == '0')
                printf("%s0%s", CYAN, RESET);
            else if ((expected[i] >= 'a' && expected[i] <= 'f') ||
                     (expected[i] >= 'A' && expected[i] <= 'F'))
                printf("%s%c%s", MAGENTA, expected[i], RESET);
            else if (expected[i] == 'x' || expected[i] == 'X')
                printf("%s%c%s", BLUE, expected[i], RESET);
            else
                printf("%c", expected[i]);
        }
        printf("\" (ret: %d)\n", expected_ret);
        
        // Print actual output with special formatting
        printf("  Actual:    \"");
        for (int i = 0; i < (int)strlen(actual); i++) {
            if (actual[i] == ' ')
                printf("%s·%s", YELLOW, RESET);
            else if (actual[i] == '0')
                printf("%s0%s", CYAN, RESET);
            else if ((actual[i] >= 'a' && actual[i] <= 'f') ||
                     (actual[i] >= 'A' && actual[i] <= 'F'))
                printf("%s%c%s", MAGENTA, actual[i], RESET);
            else if (actual[i] == 'x' || actual[i] == 'X')
                printf("%s%c%s", BLUE, actual[i], RESET);
            else
                printf("%c", actual[i]);
        }
        printf("\" (ret: %d)\n", actual_ret);
        fail_count++;
    }
    
    // Test with mixed formats
    sprintf(expected, "Formatted: [%#8x] [%-#8X] [%#08x] [%.8X] [%#8.5x]", 
            0xabc, 0xdef, 0x123, 0x456, 0x789);
    
    fp = tmpfile();
    original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Formatted: [%#8x] [%-#8X] [%#08x] [%.8X] [%#8.5x]", 
                          0xabc, 0xdef, 0x123, 0x456, 0x789);
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
        printf("%s[PASS]%s Hex with different formats\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Hex with different formats\n", RED, RESET);
        printf("  Format:    \"Formatted: [%%#8x] [%%-#8X] [%%#08x] [%%.8X] [%%#8.5x]\"\n");
        
        // Print expected and actual outputs with special formatting
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
