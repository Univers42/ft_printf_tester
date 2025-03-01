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

// Generic test function that works with any data type
void test_format(const char *format, const char *test_name, void *value, char type) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    test_count++;
    
    // Create temporary file for capturing ft_printf output
    fp = tmpfile();
    if (!fp) {
        perror("Failed to create temporary file");
        return;
    }
    
    // Get expected output using sprintf
    switch (type) {
        case 'c': expected_ret = sprintf(expected, format, *((char*)value)); break;
        case 's': expected_ret = sprintf(expected, format, (char*)value); break;
        case 'p': expected_ret = sprintf(expected, format, value); break;
        case 'd':
        case 'i': expected_ret = sprintf(expected, format, *((int*)value)); break;
        case 'u': expected_ret = sprintf(expected, format, *((unsigned int*)value)); break;
        case 'x':
        case 'X': expected_ret = sprintf(expected, format, *((unsigned int*)value)); break;
        default:  expected_ret = sprintf(expected, format, 0); break; // For %% test, pass dummy arg
    }
    
    // Redirect stdout to temp file
    int original_stdout = dup(1);
    if (dup2(fileno(fp), 1) == -1) {
        perror("Failed to redirect stdout");
        fclose(fp);
        return;
    }
    
    // Call ft_printf which will write to the temp file
    switch (type) {
        case 'c': actual_ret = ft_printf(format, *((char*)value)); break;
        case 's': actual_ret = ft_printf(format, (char*)value); break;
        case 'p': actual_ret = ft_printf(format, value); break;
        case 'd':
        case 'i': actual_ret = ft_printf(format, *((int*)value)); break;
        case 'u': actual_ret = ft_printf(format, *((unsigned int*)value)); break;
        case 'x':
        case 'X': actual_ret = ft_printf(format, *((unsigned int*)value)); break;
        default:  actual_ret = ft_printf(format, 0); break; // For %% test, pass dummy arg
    }
    
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
        
        // Show value based on type
        switch (type) {
            case 'c': printf("  Value:     '%c'\n", *((char*)value)); break;
            case 's': printf("  Value:     \"%s\"\n", (char*)value ? (char*)value : "NULL"); break;
            case 'p': printf("  Value:     %p\n", value); break;
            case 'd':
            case 'i': printf("  Value:     %d\n", *((int*)value)); break;
            case 'u': printf("  Value:     %u\n", *((unsigned int*)value)); break;
            case 'x': printf("  Value:     0x%x\n", *((unsigned int*)value)); break;
            case 'X': printf("  Value:     0x%X\n", *((unsigned int*)value)); break;
        }
        
        // Print expected output with visible spaces
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
        
        // Print actual output with visible spaces
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

void run_category(const char *category) {
    printf("\n%s=== %s ===%s\n", BLUE, category, RESET);
}

// Test flag combinations for a specific conversion type
void test_flags_for_conversion(char type, void *test_value) {
    char format[20];
    char test_desc[100];
    int widths[] = {0, 1, 5, 10}; // Different field widths to test
    int precisions[] = {0, 1, 5, 10}; // Different precisions to test
    
    // Skip precision for types where it doesn't apply meaningfully
    int skip_precision = (type == 'c' || type == 'p' || type == '%');
    
    // Set up the conversion character
    char conv[2] = {type, '\0'};
    
    // Test all combinations of flags
    for (int width_idx = 0; width_idx < 4; width_idx++) {
        int width = widths[width_idx];
        
        // No flags, just width
        if (width > 0) {
            sprintf(format, "%%%d%s", width, conv);
            sprintf(test_desc, "Width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        
        // Left align flag with width
        if (width > 0) {
            sprintf(format, "%%-%d%s", width, conv);
            sprintf(test_desc, "Left-aligned width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        
        // Zero padding flag with width (doesn't make sense for some types)
        if (width > 0 && type != 's' && type != 'p' && type != '%') {
            sprintf(format, "%%0%d%s", width, conv);
            sprintf(test_desc, "Zero-padded width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        
        // Left align with zero padding (left align takes precedence)
        if (width > 0 && type != 's' && type != 'p' && type != '%') {
            sprintf(format, "%%-0%d%s", width, conv);
            sprintf(test_desc, "Left-aligned zero-padded width %d with type %%%s", width, conv);
            test_format(format, test_desc, test_value, type);
        }
        
        if (!skip_precision) {
            // Test with precision but no width
            for (int prec_idx = 0; prec_idx < 4; prec_idx++) {
                int precision = precisions[prec_idx];
                
                sprintf(format, "%%.%d%s", precision, conv);
                sprintf(test_desc, "Precision %d with type %%%s", precision, conv);
                test_format(format, test_desc, test_value, type);
                
                // With width and precision
                if (width > 0) {
                    // Width and precision
                    sprintf(format, "%%%d.%d%s", width, precision, conv);
                    sprintf(test_desc, "Width %d, precision %d with type %%%s", 
                            width, precision, conv);
                    test_format(format, test_desc, test_value, type);
                    
                    // Left align, width and precision
                    sprintf(format, "%%-%d.%d%s", width, precision, conv);
                    sprintf(test_desc, "Left-aligned width %d, precision %d with type %%%s", 
                            width, precision, conv);
                    test_format(format, test_desc, test_value, type);
                    
                    // Zero padding, width and precision (precision should override zero padding)
                    if (type != 's') {
                        sprintf(format, "%%0%d.%d%s", width, precision, conv);
                        sprintf(test_desc, "Zero-padded width %d, precision %d with type %%%s", 
                                width, precision, conv);
                        test_format(format, test_desc, test_value, type);
                    }
                    
                    // All flags: left align, zero padding, width, precision
                    if (type != 's') {
                        sprintf(format, "%%-0%d.%d%s", width, precision, conv);
                        sprintf(test_desc, "Left-aligned zero-padded width %d, precision %d with type %%%s", 
                                width, precision, conv);
                        test_format(format, test_desc, test_value, type);
                    }
                }
            }
        }
    }
}

int main(void) {
    printf("%s=== FT_PRINTF FLAG & WIDTH COMBINATIONS TESTER ===%s\n", MAGENTA, RESET);
    
    // Test values for each type
    char c_val = 'X';
    char *s_val = "Hello";
    char *s_empty = "";
    char *s_null = NULL;
    int d_pos = 42;
    int d_neg = -42;
    int d_zero = 0;
    unsigned int u_val = 4294967295u; // UINT_MAX
    unsigned int x_val = 0xabcdef;
    void *p_val = &d_pos;
    void *p_null = NULL;
    
    // Character tests
    run_category("Character Format Tests");
    test_flags_for_conversion('c', &c_val);
    
    // String tests
    run_category("String Format Tests");
    test_flags_for_conversion('s', s_val);
    run_category("Empty String Tests");
    test_flags_for_conversion('s', s_empty);
    run_category("NULL String Tests");
    test_flags_for_conversion('s', s_null);
    
    // Integer tests
    run_category("Positive Integer Tests");
    test_flags_for_conversion('d', &d_pos);
    run_category("Negative Integer Tests");
    test_flags_for_conversion('d', &d_neg);
    run_category("Zero Integer Tests");
    test_flags_for_conversion('d', &d_zero);
    
    // Identical i format
    run_category("Positive Integer Tests (%%i)");
    test_flags_for_conversion('i', &d_pos);
    
    // Unsigned tests
    run_category("Unsigned Integer Tests");
    test_flags_for_conversion('u', &u_val);
    
    // Hex lowercase tests
    run_category("Hex Lowercase Tests");
    test_flags_for_conversion('x', &x_val);
    
    // Hex uppercase tests
    run_category("Hex Uppercase Tests");
    test_flags_for_conversion('X', &x_val);
    
    // Pointer tests
    run_category("Pointer Tests");
    test_flags_for_conversion('p', p_val);
    run_category("NULL Pointer Tests");
    test_flags_for_conversion('p', p_null);
    
    // Percent sign tests
    run_category("Percent Sign Tests");
    test_flags_for_conversion('%', NULL);
    
    // Print final summary
    printf("\n%s=== TEST SUMMARY ===%s\n", BLUE, RESET);
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, (float)pass_count/test_count*100, RESET);
    printf("Failed: %s%d (%.1f%%)%s\n", fail_count > 0 ? RED : GREEN, fail_count, (float)fail_count/test_count*100, RESET);

    return fail_count > 0 ? 1 : 0;
}
