#include "../ft_printf.h"
#include "ft_printf_test_utils.h"  // Include this header for utilities
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

// Remove duplicate definitions of test_count, pass_count, fail_count that are already
// defined in ft_printf_test_utils.c
// int test_count = 0;
// int pass_count = 0;
// int fail_count = 0;

// Remove or rename duplicate capture_output function that conflicts with
// the one in ft_printf_test_utils.c
int capture_output_fixed(char *buffer, size_t bufsize, const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Redirect stdout to a temporary file
    FILE *temp = tmpfile();
    if (!temp) {
        perror("tmpfile");
        va_end(args);
        return -1;
    }

    int original_stdout = dup(STDOUT_FILENO);
    if (dup2(fileno(temp), STDOUT_FILENO) == -1) {
        perror("dup2");
        fclose(temp);
        va_end(args);
        return -1;
    }

    // Call ft_printf with the arguments
    int ret_val = vprintf(format, args);
    fflush(stdout);
    
    // Restore stdout
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
    
    // Read the captured output
    rewind(temp);
    size_t read_size = fread(buffer, 1, bufsize - 1, temp);
    buffer[read_size] = '\0';
    
    fclose(temp);
    va_end(args);
    return ret_val;
}

// Main function that uses the utility functions from ft_printf_test_utils.h
int main(void) {
    printf("=== FT_PRINTF FIXED TESTER ===\n\n");
    
    // Use run_test from ft_printf_test_utils.c
    run_test("Simple string", "Hello, world!");
    run_test("Character", "%c", 'A');
    run_test("String", "%s", "test");
    run_test("Integer", "%d", 42);
    run_test("Negative integer", "%d", -42);
    
    // Test a mix of format specifiers
    run_test("Mixed formats", "This %s is %c %d% complete!", "test", 'a', 100);
    
    // Print summary using print_summary from ft_printf_test_utils.c
    print_summary();
    
    return fail_count > 0 ? 1 : 0;
}
