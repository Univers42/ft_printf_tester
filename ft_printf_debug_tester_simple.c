#include "../ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

int test_count = 0;
int pass_count = 0;
int fail_count = 0;

// Very simple test that directly calls both printf and ft_printf
void test_case(const char *test_name, const char *format, ...) {
    va_list args;
    int printf_ret, ft_printf_ret;
    char printf_output[1024] = {0};
    char ft_printf_output[1024] = {0};
    int pipefd[2];
    int saved_stdout;

    test_count++;
    
    // First call: standard printf
    printf("%s[TEST]%s %s\n", BLUE, RESET, test_name);
    printf("Format: \"%s\"\n", format);
    
    // Redirect stdout to pipe for printf
    pipe(pipefd);
    saved_stdout = dup(STDOUT_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    va_start(args, format);
    printf_ret = vprintf(format, args);
    va_end(args);
    fflush(stdout);
    read(pipefd[0], printf_output, sizeof(printf_output) - 1);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    close(pipefd[0]);

    printf("printf output: \"%s\"\n", printf_output);
    
    // Second call: ft_printf
    // Redirect stdout to pipe for ft_printf
    pipe(pipefd);
    saved_stdout = dup(STDOUT_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    va_start(args, format);
    ft_printf_ret = ft_printf(format, args);
    va_end(args);
    fflush(stdout);
    read(pipefd[0], ft_printf_output, sizeof(ft_printf_output) - 1);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    close(pipefd[0]);

    printf("ft_printf output: \"%s\"\n", ft_printf_output);
    
    // Print return values
    printf("printf return: %d\n", printf_ret);
    printf("ft_printf return: %d\n", ft_printf_ret);
    
    // Simple comparison of return values and output
    if (printf_ret == ft_printf_ret && strcmp(printf_output, ft_printf_output) == 0) {
        printf("%s[PASS]%s Return values and output match\n\n", GREEN, RESET);
        pass_count++;
    } else {
        printf("%s[FAIL]%s Return values or output don't match\n", RED, RESET);
        printf("  Expected output: \"%s\"\n", printf_output);
        printf("  Actual output:   \"%s\"\n", ft_printf_output);
        printf("  Expected return: %d\n", printf_ret);
        printf("  Actual return:   %d\n\n", ft_printf_ret);
        fail_count++;
    }
}

// Print overall test summary
void print_summary() {
    printf("\n%s%s===== TEST SUMMARY =====%s\n", BOLD, YELLOW, RESET);
    printf("Total tests:  %d\n", test_count);
    printf("Passed:       %s%d (%.1f%%)%s\n", 
           pass_count == test_count ? GREEN : RED, 
           pass_count, 
           test_count > 0 ? (float)pass_count / test_count * 100 : 0,
           RESET);
    printf("Failed:       %s%d (%.1f%%)%s\n",
           fail_count == 0 ? GREEN : RED,
           fail_count,
           test_count > 0 ? (float)fail_count / test_count * 100 : 0,
           RESET);
}

int main() {
    printf("\n%s%s===== SIMPLE FT_PRINTF DEBUG TESTER =====%s\n\n", BOLD, BLUE, RESET);
    
    // Basic format tests
    test_case("Simple string", "Hello, world!");
    test_case("Character", "Character: %c", 'A');
    test_case("String", "String: %s", "test");
    test_case("NULL string", "NULL string: %s", NULL);
    test_case("Integer", "Integer: %d", 42);
    test_case("Negative integer", "Negative: %d", -42);
    test_case("Unsigned", "Unsigned: %u", 42);
    test_case("Hex lowercase", "Hex: %x", 0xDEADBEEF);
    test_case("Hex uppercase", "HEX: %X", 0xDEADBEEF);
    test_case("Pointer", "Pointer: %p", &test_count);
    test_case("Percent sign", "Percent: %%");
    
    // Multiple format specifiers
    test_case("Multiple formats", "Int: %d, String: %s, Char: %c", 123, "test", 'X');
    
    // Edge cases
    test_case("Zero int with zero precision", "%.0d", 0);
    test_case("INT_MAX", "%d", INT_MAX);
    test_case("INT_MIN", "%d", INT_MIN);
    
    // Print summary
    print_summary();
    
    return fail_count > 0;
}
