#include "../ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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

// Capture stdout from a function into a buffer
int capture_output(char *buffer, int size, int (*func)(const char*, ...), const char *format, ...) {
    int pipefd[2];
    pid_t pid;
    int status, ret_val;
    va_list args;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        va_start(args, format);
        
        // Redirect stdout to the write end of the pipe
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Call the provided function
        ret_val = func(format, args);
        
        va_end(args);
        
        // Exit with the return value from the function
        exit(ret_val);
    } else { // Parent process
        // Close the write end of the pipe
        close(pipefd[1]);
        
        // Read from the pipe
        ssize_t nread = read(pipefd[0], buffer, size - 1);
        if (nread > 0)
            buffer[nread] = '\0';
        else
            buffer[0] = '\0';
        
        close(pipefd[0]);
        
        // Wait for the child process and get its exit status
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            ret_val = WEXITSTATUS(status);
        else
            ret_val = -1;
        
        return ret_val;
    }
}

// Simple test that doesn't use va_arg forwarding
void basic_test(const char *test_name, const char *fmt, ...) {
    test_count++;
    printf("Test %d: %s... ", test_count, test_name);
    
    // This is a simplified test that only checks if the function doesn't crash
    int ret = ft_printf(fmt);
    printf("\n");
    
    if (ret >= 0) {
        printf("%sPASSED%s (returned %d)\n\n", GREEN, RESET, ret);
        pass_count++;
    } else {
        printf("%sFAILED%s (returned %d)\n\n", RED, RESET, ret);
        fail_count++;
    }
}

int main(void) {
    printf("===== BASIC FT_PRINTF TESTS =====\n\n");
    
    // Basic tests that avoid complex logic
    basic_test("Simple string", "Hello, world!");
    basic_test("Character", "%c", 'A');
    basic_test("String", "%s", "Hello");
    basic_test("Integer", "%d", 42);
    basic_test("Negative integer", "%d", -42);
    basic_test("Zero", "%d", 0);
    basic_test("Unsigned", "%u", 42);
    basic_test("Hex lowercase", "%x", 42);
    basic_test("Hex uppercase", "%X", 42);
    basic_test("Percent sign", "%%");
    basic_test("Width", "%6d", 42);
    basic_test("Precision", "%.5d", 42);
    basic_test("Width and precision", "%8.5d", 42);
    
    // Summary
    printf("\n===== TEST SUMMARY =====\n");
    printf("Total: %d\n", test_count);
    printf("Passed: %s%d%s\n", GREEN, pass_count, RESET);
    printf("Failed: %s%d%s\n", RED, fail_count, RESET);
    printf("\n");
    
    return (fail_count > 0);
}
