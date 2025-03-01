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
        case 'd':
        case 'i': expected_ret = sprintf(expected, format, *((int*)value)); break;
        case 'x':
        case 'X': expected_ret = sprintf(expected, format, *((unsigned int*)value)); break;
        default:  expected_ret = sprintf(expected, format, *((int*)value)); break;
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
        case 'd':
        case 'i': actual_ret = ft_printf(format, *((int*)value)); break;
        case 'x':
        case 'X': actual_ret = ft_printf(format, *((unsigned int*)value)); break;
        default:  actual_ret = ft_printf(format, *((int*)value)); break;
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
            case 'd':
            case 'i': printf("  Value:     %d\n", *((int*)value)); break;
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

int main(void) {
    printf("%s=== FT_PRINTF SPECIAL FLAGS TESTS (#, +, SPACE) ===%s\n", MAGENTA, RESET);
    
    // Test values
    int pos_val = 42;
    int neg_val = -42;
    int zero_val = 0;
    unsigned int hex_val = 0xabcdef;
    
    // HASH FLAG TESTS WITH HEX
    run_category("Hash Flag with Hexadecimal");
    
    // Basic hash flag usage with hex
    test_format("%#x", "Hash flag with lowercase hex", &hex_val, 'x');
    test_format("%#X", "Hash flag with uppercase hex", &hex_val, 'X');
    test_format("%#x", "Hash flag with zero in lowercase hex", &zero_val, 'x');
    test_format("%#X", "Hash flag with zero in uppercase hex", &zero_val, 'X');
    
    // Hash flag with width
    test_format("%#10x", "Hash flag with width in lowercase hex", &hex_val, 'x');
    test_format("%#10X", "Hash flag with width in uppercase hex", &hex_val, 'X');
    
    // Hash flag with left align
    test_format("%#-10x", "Hash flag with left align in lowercase hex", &hex_val, 'x');
    test_format("%#-10X", "Hash flag with left align in uppercase hex", &hex_val, 'X');
    
    // Hash flag with zero padding
    test_format("%#010x", "Hash flag with zero padding in lowercase hex", &hex_val, 'x');
    test_format("%#010X", "Hash flag with zero padding in uppercase hex", &hex_val, 'X');
    
    // Hash flag with precision
    test_format("%#.10x", "Hash flag with precision in lowercase hex", &hex_val, 'x');
    test_format("%#.10X", "Hash flag with precision in uppercase hex", &hex_val, 'X');
    
    // Hash flag with width and precision
    test_format("%#15.10x", "Hash flag with width and precision in lowercase hex", &hex_val, 'x');
    test_format("%#15.10X", "Hash flag with width and precision in uppercase hex", &hex_val, 'X');
    
    // SPACE FLAG TESTS
    run_category("Space Flag with Integers");
    
    // Basic space flag usage
    test_format("% d", "Space flag with positive integer", &pos_val, 'd');
    test_format("% i", "Space flag with positive integer (%%i)", &pos_val, 'i');
    test_format("% d", "Space flag with negative integer", &neg_val, 'd');
    test_format("% i", "Space flag with negative integer (%%i)", &neg_val, 'i');
    test_format("% d", "Space flag with zero", &zero_val, 'd');
    
    // Space flag with width
    test_format("% 10d", "Space flag with width", &pos_val, 'd');
    test_format("% 10d", "Space flag with width (negative)", &neg_val, 'd');
    
    // Space flag with left align
    test_format("% -10d", "Space flag with left align", &pos_val, 'd');
    test_format("% -10d", "Space flag with left align (negative)", &neg_val, 'd');
    
    // Space flag with zero padding
    test_format("% 010d", "Space flag with zero padding", &pos_val, 'd');
    test_format("% 010d", "Space flag with zero padding (negative)", &neg_val, 'd');
    
    // Space flag with precision
    test_format("% .10d", "Space flag with precision", &pos_val, 'd');
    test_format("% .10d", "Space flag with precision (negative)", &neg_val, 'd');
    
    // Space flag with width and precision
    test_format("% 15.10d", "Space flag with width and precision", &pos_val, 'd');
    test_format("% 15.10d", "Space flag with width and precision (negative)", &neg_val, 'd');
    
    // PLUS FLAG TESTS
    run_category("Plus Flag with Integers");
    
    // Basic plus flag usage
    test_format("%+d", "Plus flag with positive integer", &pos_val, 'd');
    test_format("%+i", "Plus flag with positive integer (%%i)", &pos_val, 'i');
    test_format("%+d", "Plus flag with negative integer", &neg_val, 'd');
    test_format("%+i", "Plus flag with negative integer (%%i)", &neg_val, 'i');
    test_format("%+d", "Plus flag with zero", &zero_val, 'd');
    
    // Plus flag with width
    test_format("%+10d", "Plus flag with width", &pos_val, 'd');
    test_format("%+10d", "Plus flag with width (negative)", &neg_val, 'd');
    
    // Plus flag with left align
    test_format("%+-10d", "Plus flag with left align", &pos_val, 'd');
    test_format("%+-10d", "Plus flag with left align (negative)", &neg_val, 'd');
    
    // Plus flag with zero padding
    test_format("%+010d", "Plus flag with zero padding", &pos_val, 'd');
    test_format("%+010d", "Plus flag with zero padding (negative)", &neg_val, 'd');
    
    // Plus flag with precision
    test_format("%+.10d", "Plus flag with precision", &pos_val, 'd');
    test_format("%+.10d", "Plus flag with precision (negative)", &neg_val, 'd');
    
    // Plus flag with width and precision
    test_format("%+15.10d", "Plus flag with width and precision", &pos_val, 'd');
    test_format("%+15.10d", "Plus flag with width and precision (negative)", &neg_val, 'd');
    
    // COMBINATION FLAG TESTS
    run_category("Flag Combinations");
    
    // Space and plus flags together (plus should win)
    test_format("%+ d", "Space and plus flags together (plus wins)", &pos_val, 'd');
    test_format("% +d", "Plus and space flags together (plus wins)", &pos_val, 'd');
    
    // Flag combinations with integers
    test_format("%+ 10d", "Space, plus, and width", &pos_val, 'd');
    test_format("%+ -10d", "Space, plus, and left align", &pos_val, 'd');
    test_format("%+ 010d", "Space, plus, and zero padding", &pos_val, 'd');
    test_format("%+ .10d", "Space, plus, and precision", &pos_val, 'd');
    test_format("%+ 15.10d", "Space, plus, width, and precision", &pos_val, 'd');
    
    // Hash flag with other flags for hex
    test_format("%#+ x", "Hash with space and plus (hex)", &hex_val, 'x');
    test_format("%#+ 10x", "Hash with space, plus, and width (hex)", &hex_val, 'x');
    test_format("%#+ -10x", "Hash with space, plus, and left align (hex)", &hex_val, 'x');
    test_format("%#+ 010x", "Hash with space, plus, and zero padding (hex)", &hex_val, 'x');
    test_format("%#+ .10x", "Hash with space, plus, and precision (hex)", &hex_val, 'x');
    test_format("%#+ 15.10x", "Hash with space, plus, width, and precision (hex)", &hex_val, 'x');
    
    // EDGE CASES
    run_category("Edge Cases");
    
    // INT_MAX and INT_MIN
    int max_val = INT_MAX;
    int min_val = INT_MIN;
    test_format("%+d", "Plus flag with INT_MAX", &max_val, 'd');
    test_format("%+d", "Plus flag with INT_MIN", &min_val, 'd');
    test_format("% d", "Space flag with INT_MAX", &max_val, 'd');
    test_format("% d", "Space flag with INT_MIN", &min_val, 'd');
    
    // Very large width values
    test_format("%+50d", "Plus flag with large width", &pos_val, 'd');
    test_format("% 50d", "Space flag with large width", &pos_val, 'd');
    test_format("%#50x", "Hash flag with large width", &hex_val, 'x');
    
    // Print final summary
    printf("\n%s=== TEST SUMMARY ===%s\n", BLUE, RESET);
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, (float)pass_count/test_count*100, RESET);
    printf("Failed: %s%d (%.1f%%)%s\n", fail_count > 0 ? RED : GREEN, fail_count, (float)fail_count/test_count*100, RESET);

    return fail_count > 0 ? 1 : 0;
}
