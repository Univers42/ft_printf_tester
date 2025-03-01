#include "../ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

int test_count = 0;
int pass_count = 0;
int fail_count = 0;

// Capture stdout from a function into a buffer using a temporary file
int capture_output(char *buffer, int size, int (*func)(const char*, ...), const char *format, ...) {
    FILE *tmp_file = tmpfile();
    if (!tmp_file) {
        perror("tmpfile");
        exit(EXIT_FAILURE);
    }

    int saved_stdout = dup(STDOUT_FILENO);
    dup2(fileno(tmp_file), STDOUT_FILENO);

    va_list args;
    va_start(args, format);
    int ret_val = func(format, args);
    va_end(args);

    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    fseek(tmp_file, 0, SEEK_SET);
    size_t nread = fread(buffer, 1, size - 1, tmp_file);
    buffer[nread] = '\0';

    fclose(tmp_file);
    return ret_val;
}

void pointer_test(const char *test_name, const char *fmt, void *ptr) {
    test_count++;
    printf("Test %d: %s... ", test_count, test_name);
    
    char expected_output[BUFFER_SIZE] = {0};
    char actual_output[BUFFER_SIZE] = {0};
    int expected_ret, actual_ret;
    
    // Capture expected output using printf
    expected_ret = snprintf(expected_output, BUFFER_SIZE, fmt, ptr);
    
    // Capture actual output using ft_printf
    actual_ret = capture_output(actual_output, BUFFER_SIZE, ft_printf, fmt, ptr);
    
    // Compare the format and structure of the output
    if (expected_ret == actual_ret && strcmp(expected_output, actual_output) == 0) {
        printf("%sPASSED%s\n\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%sFAILED%s\n", RED, RESET);
        printf("  Expected output: \"%s\"\n", expected_output);
        printf("  Actual output:   \"%s\"\n", actual_output);
        printf("  Expected return: %d\n", expected_ret);
        printf("  Actual return:   %d\n\n", actual_ret);
        fail_count++;
    }
}

int main(void) {
    printf("===== POINTER FT_PRINTF TESTS =====\n\n");
    
    // Pointer tests
    int dummy_var = 0;
    pointer_test("Pointer to int", "Pointer: %p", &dummy_var);
    pointer_test("Pointer to function", "Pointer: %p", &main);
    pointer_test("Pointer to NULL", "Pointer: %p", NULL);
    
    // Summary
    printf("\n===== TEST SUMMARY =====\n");
    printf("Total: %d\n", test_count);
    printf("Passed: %s%d%s\n", GREEN, pass_count, RESET);
    printf("Failed: %s%d%s\n", RED, fail_count, RESET);
    printf("\n");
    
    return (fail_count > 0);
}
