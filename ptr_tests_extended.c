#include "../ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define BUFFER_SIZE 8192
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

// Test function with improved diagnostics for pointers
void test_ptr(void *ptr, const char *format, const char *test_name) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    test_count++;
    
    // Get expected output using sprintf
    expected_ret = sprintf(expected, format, ptr);
    
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
    actual_ret = ft_printf(format, ptr);
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
        printf("  Pointer:   %p\n", ptr);
        
        // Print expected output with visible spaces
        printf("  Expected:  \"");
        for (int i = 0; i < (int)strlen(expected); i++) {
            if (expected[i] == ' ')
                printf("%s·%s", YELLOW, RESET); // Visible space
            else if (expected[i] == '0')
                printf("%s0%s", CYAN, RESET); // Highlight zeros
            else if (expected[i] == 'x' || expected[i] == 'X')
                printf("%sx%s", MAGENTA, RESET); // Highlight x/X
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
            else if (actual[i] == 'x' || actual[i] == 'X')
                printf("%sx%s", MAGENTA, RESET); // Highlight x/X
            else
                printf("%c", actual[i]);
        }
        printf("\" (ret: %d)\n", actual_ret);
        fail_count++;
    }
}

// Test with multiple pointer formats in a complex string
void test_multiple_ptrs(const char *format, const char *test_name, void *p1, void *p2, void *p3) {
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    test_count++;
    
    // Get expected output using sprintf
    expected_ret = sprintf(expected, format, p1, p2, p3);
    
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
    actual_ret = ft_printf(format, p1, p2, p3);
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
            else if (expected[i] == '0')
                printf("%s0%s", CYAN, RESET); // Highlight zeros
            else if (expected[i] == 'x' || expected[i] == 'X')
                printf("%sx%s", MAGENTA, RESET); // Highlight x/X
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
            else if (actual[i] == 'x' || actual[i] == 'X')
                printf("%sx%s", MAGENTA, RESET);
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
    printf("%s=== FT_PRINTF EXTENDED POINTER TESTS ===%s\n", MAGENTA, RESET);
    
    // Sample variables of different types for testing pointers
    int i = 42;
    char c = 'A';
    float f = 3.14;
    double d = 2.71828;
    char str[] = "Hello";
    void *null_ptr = NULL;
    int array[5] = {1, 2, 3, 4, 5};
    
    // Basic function pointers
    int (*func_ptr)(const char *, ...) = &printf;
    
    // BASIC POINTER TESTS
    run_category("Basic Pointer Tests");
    test_ptr(&i, "%p", "Pointer to int");
    test_ptr(&c, "%p", "Pointer to char");
    test_ptr(&f, "%p", "Pointer to float");
    test_ptr(&d, "%p", "Pointer to double");
    test_ptr(str, "%p", "Pointer to string");
    test_ptr(array, "%p", "Pointer to array");
    test_ptr(func_ptr, "%p", "Function pointer");
    test_ptr(null_ptr, "%p", "NULL pointer");
    test_ptr((void*)0xABCDEF, "%p", "Hexadecimal constant pointer");
    
    // WIDTH TESTS
    run_category("Width Tests");
    test_ptr(&i, "%20p", "Width larger than pointer");
    test_ptr(&i, "%3p", "Width smaller than pointer");
    test_ptr(null_ptr, "%10p", "NULL with width");
    
    // Left justify tests
    run_category("Left Justify Tests");
    test_ptr(&i, "%-20p", "Left-justified with width");
    test_ptr(&i, "%-3p", "Left-justified with small width");
    test_ptr(null_ptr, "%-10p", "Left-justified NULL");
    
    // Zero padding tests
    run_category("Zero Padding Tests");
    test_ptr(&i, "%020p", "Zero-padded with width");
    test_ptr(&i, "%03p", "Zero-padded with small width");
    test_ptr(null_ptr, "%010p", "Zero-padded NULL");
    
    // Precision tests (behavior varies by implementation)
    run_category("Precision Tests");
    test_ptr(&i, "%.20p", "Precision larger than pointer");
    test_ptr(&i, "%.3p", "Precision smaller than pointer");
    test_ptr(null_ptr, "%.10p", "NULL with precision");
    test_ptr(null_ptr, "%.0p", "NULL with zero precision");
    
    // Width and precision combinations
    run_category("Width and Precision Combinations");
    test_ptr(&i, "%20.15p", "Width > precision");
    test_ptr(&i, "%15.20p", "Width < precision");
    test_ptr(&i, "%20.20p", "Width = precision");
    test_ptr(null_ptr, "%10.5p", "NULL with width and precision");
    
    // Flag combinations
    run_category("Flag Combinations");
    test_ptr(&i, "%-020p", "Left justify with zero padding");
    test_ptr(&i, "%20.15p", "Width with precision");
    test_ptr(&i, "%-20.15p", "Left justify with width and precision");
    test_ptr(null_ptr, "%-010.5p", "NULL with all flags");
    
    // Mixed with other specifiers
    run_category("Mixed Format Specifiers");
    
    // Test with mixed formats (manually to handle the multiple variables)
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    FILE *fp;
    
    // Test multiple format specifiers in a single string
    sprintf(expected, "Int: %d, Char: %c, Ptr: %p", 42, 'X', &i);
    
    fp = tmpfile();
    int original_stdout = dup(1);
    dup2(fileno(fp), 1);
    actual_ret = ft_printf("Int: %d, Char: %c, Ptr: %p", 42, 'X', &i);
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
        printf("%s[PASS]%s Mixed format specifiers\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Mixed format specifiers\n", RED, RESET);
        printf("  Format:    \"Int: %%d, Char: %%c, Ptr: %%p\"\n");
        printf("  Expected:  \"%s\" (ret: %d)\n", expected, expected_ret);
        printf("  Actual:    \"%s\" (ret: %d)\n", actual, actual_ret);
        fail_count++;
    }
    
    // Multiple pointers test
    test_multiple_ptrs("Pointers: %p, %p, %p", "Multiple pointers", &i, &c, &f);
    
    // Different width and flag combinations for each pointer
    test_multiple_ptrs("Formatted: [%20p] [%-20p] [%020p]", "Different formats for each pointer", &i, &c, &f);
    
    // Edge case pointer values
    run_category("Edge Cases");
    
    // Test with a pointer that has lots of zeros
    int *zero_heavy_ptr = (int *)0x00000010;
    test_ptr(zero_heavy_ptr, "%p", "Pointer with many leading zeros");
    
    // Test with a pointer that has alternating bits
    void *alternating_ptr = (void *)0xAAAAAAAA;
    test_ptr(alternating_ptr, "%p", "Pointer with alternating bits");
    
    // Test with largest possible address
    void *max_ptr = (void *)-1; // All bits set to 1
    test_ptr(max_ptr, "%p", "Maximum value pointer");
    
    // Stress tests with extreme values
    run_category("Stress Tests");
    
    test_ptr(&i, "%100p", "Very large width");
    test_ptr(&i, "%-100p", "Very large left-justified width");
    test_ptr(&i, "%0100p", "Very large zero-padding");
    test_ptr(&i, "%.100p", "Very large precision");
    test_ptr(&i, "%100.50p", "Very large width and precision");
    
    // Print final summary
    printf("\n%s=== TEST SUMMARY ===%s\n", BLUE, RESET);
    printf("Total tests: %d\n", test_count);
    printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count, (float)pass_count/test_count*100, RESET);
    printf("Failed: %s%d (%.1f%%)%s\n", fail_count > 0 ? RED : GREEN, fail_count, (float)fail_count/test_count*100, RESET);

    return fail_count > 0 ? 1 : 0;
}
