/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ultimate_controller.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:28 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:17:29 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <sys/wait.h>

// Define our own bright colors since they're missing from ft_printf_debug.h
#define BR_CYAN   "\033[96m"
#define BR_BLUE   "\033[94m"
#define BR_MAGENTA "\033[95m"
#define BR_GREEN  "\033[92m"

// ANSI color codes and formatting
#define RESET     "\033[0m"
#define BOLD      "\033[1m"
#define DIM       "\033[2m"
#define ITALIC    "\033[3m"
#define UNDERLINE "\033[4m"
#define BLINK     "\033[5m"
#define REVERSE   "\033[7m"

// Foreground colors
#define BLACK     "\033[30m"
#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define MAGENTA   "\033[35m"
#define CYAN      "\033[36m"
#define WHITE     "\033[37m"

// Background colors
#define BG_BLACK  "\033[40m"
#define BG_RED    "\033[41m"
#define BG_GREEN  "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE   "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN   "\033[46m"
#define BG_WHITE  "\033[47m"

// Control characters
#define CLEAR_SCREEN "\033[2J\033[H"

// Available test programs
typedef struct {
    int id;
    const char *name;
    const char *description;
    const char *executable;
    const char *arguments;
} Test;

// Test program definitions - fix numbering and remove unwanted entry
Test tests[] = {
    {1, "Character Tests", "Basic character conversion tests", "./program/char_tests", ""},
    {2, "Extended Character Tests", "Comprehensive character tests", "./program/char_tests_extended", ""},
    {3, "String Tests", "Extended string conversion tests", "./program/string_tests_extended", ""},
    {4, "Integer Tests", "Extended integer conversion tests", "./program/int_tests_extended", ""},
    {5, "Unsigned Tests", "Unsigned integer conversion tests", "./program/unsigned_tests_extended", ""},
    {6, "Hexadecimal Tests", "Hex conversion tests", "./program/hex_tests_extended", ""},
    {7, "Pointer Tests", "Pointer conversion tests", "./program/ptr_tests_extended", ""},
    {8, "Flag Combinations", "Tests various flag combinations", "./program/flag_combinations_tester", ""},
    {9, "Special Flags", "Tests special flag behavior", "./program/special_flags_tester", ""},
    {10, "Debug Tester", "Full debug tester", "./program/ft_printf_debug_tester", ""},
    {11, "Simple Debug", "Simple debug tester", "./program/ft_printf_debug_tester_simple", ""},
    {12, "Stress Tests", "Performance and edge case tests", "./program/ft_printf_stress_tester", ""},
    {0, "Run All Tests", "Run all test programs in sequence", "", ""}
};

int num_tests = sizeof(tests) / sizeof(Test);

// Function to introduce a small delay (visual effect)
void delay_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

// Function to animate a loading bar
void loading_bar(const char *message, int duration_ms, int segments) {
    int segment_time = duration_ms / segments;
    int i;
    
    printf("%s%s%s [", CYAN, message, RESET);
    fflush(stdout);
    
    for (i = 0; i < segments; i++) {
        delay_ms(segment_time);
        printf("%s█%s", BR_CYAN, RESET);
        fflush(stdout);
    }
    
    printf("] %sDone!%s\n", GREEN, RESET);
}

// Function to display spinner animation
void spinner(const char *message, int duration_ms) {
    char spin_chars[] = {'|', '/', '-', '\\'};
    int i, iterations = duration_ms / 100;
    
    for (i = 0; i < iterations; i++) {
        printf("\r%s %c ", message, spin_chars[i % 4]);
        fflush(stdout);
        delay_ms(100);
    }
    printf("\r%s %s%s%s\n", message, GREEN, "✓", RESET);
}

// Display a centered header
void display_header(const char *title) {
    int terminal_width = 80;  // Assume 80 columns if we can't determine it
    int title_len = strlen(title);
    int padding = (terminal_width - title_len) / 2;
    
    printf("\n");
    for (int i = 0; i < terminal_width; i++) printf("%s═%s", CYAN, RESET);
    printf("\n%*s%s%s%s%s%*s\n", padding, "", BG_BLUE, BOLD, title, RESET, padding, "");
    for (int i = 0; i < terminal_width; i++) printf("%s═%s", CYAN, RESET);
    printf("\n");
}

// Terminal visual effects
void animate_terminal() {
    printf(CLEAR_SCREEN);  // Clear the screen first
    
    // Display an animated logo
    const char *logo[] = {
        "███████╗████████╗    ██████╗ ██████╗ ██╗███╗   ██╗████████╗███████╗",
        "██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██║████╗  ██║╚══██╔══╝██╔════╝",
        "█████╗     ██║       ██████╔╝██████╔╝██║██╔██╗ ██║   ██║   █████╗  ",
        "██╔══╝     ██║       ██╔═══╝ ██╔══██╗██║██║╚██╗██║   ██║   ██╔══╝  ",
        "██║        ██║       ██║     ██║  ██║██║██║ ╚████║   ██║   ██║     ",
        "╚═╝        ╚═╝       ╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝     ",
        "                                                                    ",
        "         ██╗   ██╗██╗  ████████╗██╗███╗   ███╗ █████╗ ████████╗███████╗",
        "         ██║   ██║██║  ╚══██╔══╝██║████╗ ████║██╔══██╗╚══██╔══╝██╔════╝",
        "         ██║   ██║██║     ██║   ██║██╔████╔██║███████║   ██║   █████╗  ",
        "         ██║   ██║██║     ██║   ██║██║╚██╔╝██║██╔══██║   ██║   ██╔══╝  ",
        "         ╚██████╔╝███████╗██║   ██║██║ ╚═╝ ██║██║  ██║   ██║   ███████╗",
        "          ╚═════╝ ╚══════╝╚═╝   ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚══════╝",
        "                                                                    ",
        "                ████████╗███████╗███████╗████████╗███████╗██████╗ ",
        "                ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗",
        "                   ██║   █████╗  ███████╗   ██║   █████╗  ██████╔╝",
        "                   ██║   ██╔══╝  ╚════██║   ██║   ██╔══╝  ██╔══██╗",
        "                   ██║   ███████╗███████║   ██║   ███████╗██║  ██║",
        "                   ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝"
    };
    
    // Colorful animation for logo
    int num_lines = sizeof(logo) / sizeof(logo[0]);
    
    // Colors to cycle through
    const char *colors[] = {CYAN, BLUE, MAGENTA, RED, YELLOW, GREEN, BR_CYAN, BR_BLUE, BR_MAGENTA};
    int num_colors = sizeof(colors) / sizeof(colors[0]);
    
    // Animate each line of the logo
    for (int i = 0; i < num_lines; i++) {
        printf("%s%s%s\n", colors[i % num_colors], logo[i], RESET);
        delay_ms(80); // Short delay between lines
        fflush(stdout);
    }
    
    printf("\n\n");
    
    // Loading animation
    loading_bar("Initializing controller environment", 1000, 20);
    spinner("Loading test programs", 1000);
    loading_bar("Preparing execution engine", 800, 15);
    spinner("Setting up test framework", 800);
    
    printf("\n%s%s ULTIMATE FT_PRINTF CONTROLLER READY %s\n\n", BOLD, BR_GREEN, RESET);
    delay_ms(500);
}

// Display test selection menu
void display_menu() {
    printf("%s╔═══════════════════════════════════════════════════════════╗%s\n", BLUE, RESET);
    printf("%s║%s%s              FT_PRINTF TEST SELECTION                 %s%s║%s\n", BLUE, RESET, BOLD, RESET, BLUE, RESET);
    printf("%s╠═══════════════════════════════════════════════════════════╣%s\n", BLUE, RESET);
    
    // Display tests, starting from index 0 (now the first test)
    for (int i = 0; i < num_tests - 1; i++) {
        printf("%s║%s %2d. %-48s %s║%s\n", 
               BLUE, CYAN, tests[i].id, tests[i].name, BLUE, RESET);
    }
    
    // Special option for running all tests
    printf("%s║%s  0. %-48s %s║%s\n", BLUE, GREEN, tests[num_tests-1].name, BLUE, RESET);
    printf("%s║%s  q. %-48s %s║%s\n", BLUE, RED, "Quit", BLUE, RESET);
    printf("%s╚═══════════════════════════════════════════════════════════╝%s\n", BLUE, RESET);
    
    printf("\n%sEnter your choice:%s ", BOLD, RESET);
}

// Check if a file exists and is executable
int is_executable(const char *path) {
    return access(path, X_OK) == 0;
}

// Execute a test program and display its output with proper error handling
int run_controller_test(Test test) {
    // Display test header
    printf("\n%s%s=== Running: %s ===%s\n", BOLD, YELLOW, test.name, RESET);
    printf("%s%s%s\n\n", ITALIC, test.description, RESET);
    
    // Set up the command
    char command[256];
    snprintf(command, sizeof(command), "%s %s", test.executable, test.arguments);
    
    // Check if the executable exists before trying to run it
    if (!is_executable(test.executable)) {
        printf("%s%s✗ Error: Test program not found: %s%s\n", 
               BOLD, RED, test.executable, RESET);
        printf("    Run 'make ensure_testers' to compile all test programs.\n\n");
        return -1;
    }
    
    // Show loading spinner
    spinner("Starting test program", 500);
    
    // Execute the test program
    int status = system(command);
    
    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        if (exit_status == 0) {
            printf("\n%s%s✓ Test completed successfully%s\n", BOLD, GREEN, RESET);
        } else {
            printf("\n%s%s✗ Test completed with errors (exit code: %d)%s\n", 
                    BOLD, RED, exit_status, RESET);
        }
    } else if (WIFSIGNALED(status)) {
        printf("\n%s%s✗ Test was terminated by signal %d%s\n", 
                BOLD, RED, WTERMSIG(status), RESET);
    } else {
        printf("\n%s%s? Test ended with unknown status%s\n", BOLD, YELLOW, RESET);
    }
    
    return status;
}

// Run all tests in sequence
void run_all_tests() {
    int success_count = 0;
    int fail_count = 0;
    
    display_header("RUNNING ALL TESTS");
    
    // Skip the last test (which is "Run All Tests") and run all the others
    for (int i = 0; i < num_tests - 1; i++) {
        printf("\n%s%s=== Test %d/%d: %s ===%s\n", 
               BOLD, CYAN, i+1, num_tests-1, tests[i].name, RESET);
        
        int status = run_controller_test(tests[i]); // Update function call here
        
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            success_count++;
        } else {
            fail_count++;
        }
        
        // Separation between tests
        printf("\n%s%s════════════════════════════════════════════════%s\n", 
               BOLD, CYAN, RESET);
        
        delay_ms(500); // Brief pause between tests
    }
    
    // Display summary
    printf("\n%s%s=== ALL TESTS COMPLETED ===%s\n", BOLD, MAGENTA, RESET);
    printf("Total tests:    %d\n", num_tests-1);
    printf("Successful:     %s%d%s\n", GREEN, success_count, RESET);
    printf("Failed:         %s%d%s\n", 
           fail_count > 0 ? RED : GREEN, fail_count, RESET);
    
    float success_percentage = (float)success_count / (num_tests-1) * 100;
    
    // Display a progress bar
    int bar_width = 50;
    int filled_width = (int)(success_percentage * bar_width / 100);
    
    printf("\nSuccess rate:   [");
    for (int i = 0; i < bar_width; i++) {
        if (i < filled_width) {
            printf("%s█%s", GREEN, RESET);
        } else {
            printf("%s▒%s", RED, RESET);
        }
    }
    printf("] %.1f%%\n\n", success_percentage);
}

// Main function
int main() {
    // Enable animations only for interactive sessions
    int enable_animations = isatty(STDOUT_FILENO);
    
    // Show animated intro if in interactive mode
    if (enable_animations) {
        animate_terminal();
    } else {
        printf("FT_PRINTF ULTIMATE TEST CONTROLLER\n\n");
    }
    
    int running = 1;
    while (running) {
        display_menu();
        
        // Get user choice
        char input[10];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Check for quit
        if (input[0] == 'q' || input[0] == 'Q') {
            break;
        }
        
        // Convert to integer
        int choice = atoi(input);
        
        // Clear screen for new test output
        if (enable_animations) {
            printf(CLEAR_SCREEN);
        }
        
        // Handle the choice - fix logic
        if (choice == 0) {
            run_all_tests();
        } else {
            // Find the test by ID
            Test *selected_test = NULL;
            for (int i = 0; i < num_tests; i++) {
                if (tests[i].id == choice) {
                    selected_test = &tests[i];
                    break;
                }
            }
            
            if (selected_test) {
                run_controller_test(*selected_test); // Update function call here
            } else {
                printf("%s%sInvalid choice. Please try again.%s\n\n", BOLD, RED, RESET);
                continue;
            }
        }
        
        if (enable_animations) {
            printf("\n%sPress Enter to return to menu...%s", YELLOW, RESET);
            getchar(); // Wait for Enter key
            printf(CLEAR_SCREEN);
        } else {
            running = 0; // Exit after one run in non-interactive mode
        }
    }
    
    if (enable_animations) {
        printf("\n%s%sFT_PRINTF ULTIMATE TEST CONTROLLER EXITING...%s\n", BOLD, CYAN, RESET);
        delay_ms(500);
    }
    
    return 0;
}
