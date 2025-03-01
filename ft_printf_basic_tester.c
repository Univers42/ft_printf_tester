#include "../ft_printf.h"
#include "ft_printf_test_utils.h"  // Include this header for run_test and other utilities

// Rename to avoid conflict with ft_printf_test_utils.c
int capture_output_local(char *buffer, size_t bufsize, int (*func)(const char*, ...), const char *format, ...) {
    int pipefd[2];
    pid_t pid;
    int status, ret_val;

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
        va_list args;
        va_start(args, format);
        
        // Redirect stdout to the write end of the pipe
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Call the provided function
        if (func == ft_printf) {
            ret_val = func(format, args);
        } else {
            ret_val = vprintf(format, args);
        }
        
        va_end(args);
        
        // Exit with the return value from the function
        exit(ret_val);
    } else { // Parent process
        // Close the write end of the pipe
        close(pipefd[1]);
        
        // Read from the pipe
        ssize_t nread = read(pipefd[0], buffer, bufsize-1);
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

int main(void) {
    printf("===== BASIC FT_PRINTF TESTS =====\n\n");
    
    // Test simple string with no format specifiers
    run_test("Simple String", "Hello, world!");
    
    // Test basic format specifiers one at a time
    run_test("Character", "Character: %c", 'A');
    run_test("String", "String: %s", "test");
    run_test("Integer", "Integer: %d", 42);
    run_test("Negative integer", "Negative: %d", -42);
    run_test("Zero", "Zero: %d", 0);
    run_test("Unsigned", "Unsigned: %u", 42);
    run_test("Hex lowercase", "Hex: %x", 42);
    run_test("Hex uppercase", "HEX: %X", 42);
    run_test("Percent sign", "Percent: %%");
    
    // Test simple flag combinations
    run_test("Width", "Width: %5d", 42);
    run_test("Precision", "Precision: %.5d", 42);
    run_test("Left Justify", "Left: %-5d", 42);
    run_test("Plus Sign", "Plus: %+d", 42);
    run_test("Space", "Space: % d", 42);
    run_test("Zero Padding", "Zero: %05d", 42);
    run_test("Hash", "Hash: %#x", 42);
    
    return 0;
}
