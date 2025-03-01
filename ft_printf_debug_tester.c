#include "../ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>  // Add this for time() function

#define BUFFER_SIZE 4096
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

// Global test counters
int test_count = 0;
int pass_count = 0;
int fail_count = 0;
int total_runs = 0;
int runs_with_failures = 0;

// Special flag to control whether we're running in deterministic mode
int deterministic_mode = 1;

// Signal handler for segfaults
void handle_segfault(int sig) {
    (void)sig;  // Mark parameter as used to avoid warning
    printf("\n%s[CRASH] Segmentation fault detected during test execution!%s\n", RED, RESET);
    exit(1);
}

// Safer version of test function that runs in a separate process
void run_test_safely(const char *test_name, const char *format, ...) {
    pid_t pid = fork();
    if (pid == -1) {
        printf("%s[ERROR] Fork failed%s\n", RED, RESET);
        return;
    }

    if (pid == 0) {  // Child process
        // Set up signal handler for segmentation faults
        signal(SIGSEGV, handle_segfault);
        
        char expected_output[BUFFER_SIZE] = {0};
        char actual_output[BUFFER_SIZE] = {0};
        int expected_ret, actual_ret;
        va_list args, args_copy;
        
        va_start(args, format);
        va_copy(args_copy, args);
        
        // Get output from standard printf
        expected_ret = vsnprintf(expected_output, BUFFER_SIZE, format, args);
        
        // Clear args and use the copy for ft_printf
        va_end(args);
        
        // Get output from ft_printf
        actual_ret = ft_printf(format, args_copy);
        
        // Clean up
        va_end(args_copy);
        
        // Compare results
        if (strcmp(expected_output, actual_output) == 0 && expected_ret == actual_ret) {
            printf("%s[PASS]%s %s\n", GREEN, RESET, test_name);
            exit(0); // Success
        } else {
            printf("%s[FAIL]%s %s\n", RED, RESET, test_name);
            printf("  Format:    \"%s\"\n", format);
            printf("  Expected:  \"%s\" (ret: %d)\n", expected_output, expected_ret);
            printf("  Actual:    \"%s\" (ret: %d)\n", actual_output, actual_ret);
            exit(1); // Failure
        }
    } else {  // Parent process
        int status;
        waitpid(pid, &status, 0);
        
        test_count++;
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            pass_count++;
        } else {
            fail_count++;
        }
    }
}

// Run the same test multiple times to check for consistency
void consistency_test(const char *test_name, int iterations, const char *format, ...) {
    int i, success_count = 0, failure_count = 0;
    va_list args;
    
    printf("Running consistency test for '%s' (%d iterations):\n", test_name, iterations);
    
    for (i = 0; i < iterations; i++) {
        char expected_output[BUFFER_SIZE] = {0};
        char actual_output[BUFFER_SIZE] = {0};
        int expected_ret, actual_ret;
        
        // Start args for this iteration
        va_start(args, format);
        
        // Get expected output from standard printf
        expected_ret = vsnprintf(expected_output, BUFFER_SIZE, format, args);
        
        // Clean up this use of args
        va_end(args);
        
        // Start args again for ft_printf
        va_start(args, format);
        
        // Get actual output from ft_printf
        actual_ret = ft_printf(format, args);
        
        // Clean up
        va_end(args);
        
        // Compare results
        if (strcmp(expected_output, actual_output) == 0 && expected_ret == actual_ret) {
            success_count++;
        } else {
            failure_count++;
            // Only print details on first failure
            if (failure_count == 1) {
                printf("  %s[FAIL]%s Iteration %d\n", RED, RESET, i+1);
                printf("    Format:    \"%s\"\n", format);
                printf("    Expected:  \"%s\" (ret: %d)\n", expected_output, expected_ret);
                printf("    Actual:    \"%s\" (ret: %d)\n", actual_output, actual_ret);
            }
        }
    }
    
    // Print summary
    if (failure_count == 0) {
        printf("%s[CONSISTENT]%s Test passed all %d iterations\n", GREEN, RESET, iterations);
    } else {
        printf("%s[INCONSISTENT]%s Test passed %d/%d iterations, failed %d/%d iterations\n", 
               RED, RESET, success_count, iterations, failure_count, iterations);
    }
}

// Run a specific category of tests
void run_test_category(const char *category_name, void (*test_func)(void)) {
    printf("\n%s=== %s Tests ===%s\n", BLUE, category_name, RESET);
    
    // Track failures for this category
    int prev_fail_count = fail_count;
    
    // Run the test function
    test_func();
    
    // Summary for this category
    int category_tests = test_count - (total_runs > 0 ? total_runs : 0);
    int category_passes = pass_count - (total_runs > 0 ? (total_runs - runs_with_failures) : 0);
    int category_fails = fail_count - prev_fail_count;
    
    printf("\n%s%s Summary: %d tests, %d passed, %d failed%s\n", 
           category_fails > 0 ? RED : GREEN,
           category_name, 
           category_tests, 
           category_passes, 
           category_fails,
           RESET);
    
    // Update totals
    total_runs += category_tests;
    if (category_fails > 0) {
        runs_with_failures++;
    }
}

// Basic functionality tests
void basic_tests(void) {
    run_test_safely("Character test", "%c", 'A');
    run_test_safely("Multiple characters", "%c %c %c", 'a', 'b', 'c');
    run_test_safely("String test", "%s", "Hello, world!");
    run_test_safely("NULL string", "%s", NULL);
    run_test_safely("Integer test", "%d", 42);
    run_test_safely("Negative integer", "%d", -42);
    run_test_safely("Zero integer", "%d", 0);
    run_test_safely("Multiple formats", "%d %s %c", 123, "test", 'X');
}

// Character flag tests
void char_tests(void) {
    run_test_safely("Char with width", "%5c", 'A');
    run_test_safely("Char with left padding", "%-5c", 'A');
    run_test_safely("Char with zero padding", "%05c", 'A');
    run_test_safely("Char with precision", "%.c", 'A'); // Precision should be ignored for %c
    run_test_safely("Char with width and precision", "%5.2c", 'A'); // Precision should be ignored for %c
    run_test_safely("Char with multiple flags", "%-05c", 'A'); // Left padding should take precedence
}

// Run the same basic test 5 times to check consistency
void consistency_checks(void) {
    consistency_test("Character test", 5, "%c", 'A');
    consistency_test("String test", 5, "%s", "Hello, world!");
    consistency_test("Integer test", 5, "%d", 42);
    consistency_test("Mixed formats", 5, "%d %s %c", 123, "test", 'X');
}

int main(int argc, char **argv) {
    // Check for command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--non-deterministic") == 0) {
            deterministic_mode = 0;
        }
    }
    
    printf("=== FT_PRINTF DEBUG TESTER ===\n");
    if (deterministic_mode) {
        printf("Running in deterministic mode (using fixed seeds for any randomness)\n");
        srand(42); // Fixed seed
    } else {
        printf("Running in non-deterministic mode (using system-provided random seeds)\n");
        srand(time(NULL)); // Random seed
    }
    
    // Run tests with isolation to detect crashes and provide better diagnostics
    run_test_category("Basic Functionality", basic_tests);
    run_test_category("Character Flags", char_tests);
    run_test_category("Consistency", consistency_checks);
    
    // Print final summary
    printf("\n=== FINAL RESULTS ===\n");
    printf("Total tests: %d\n", total_runs);
    printf("Passed: %s%d (%d%%)%s\n", GREEN, total_runs - runs_with_failures,
           (total_runs > 0) ? ((total_runs - runs_with_failures) * 100 / total_runs) : 0, RESET);
    printf("Failed: %s%d (%d%%)%s\n", runs_with_failures > 0 ? RED : GREEN, 
           runs_with_failures, (total_runs > 0) ? (runs_with_failures * 100 / total_runs) : 0, RESET);
           
    return runs_with_failures > 0 ? 1 : 0;
}
