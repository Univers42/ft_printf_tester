/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ultimate_controller.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:28 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 01:51:00 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/controller.h"

Test tests[] = {
    {1, "Mandatory Part", "All required conversions (cspdiuxX%)", "./program/ft_printf_mandatory_test", ""},
    {2, "Character Tests", "Basic character conversion tests", "./program/char_tests", ""},
    {3, "Extended Character Tests", "Comprehensive character tests", "./program/char_tests_extended", ""},
    {4, "String Tests", "Extended string conversion tests", "./program/string_tests_extended", ""},
    {5, "Integer Tests", "Extended integer conversion tests", "./program/int_tests_extended", ""},
    {6, "Unsigned Tests", "Unsigned integer conversion tests", "./program/unsigned_tests_extended", ""},
    {7, "Hexadecimal Tests", "Hex conversion tests", "./program/hex_tests_extended", ""},
    {8, "Pointer Tests", "Pointer conversion tests", "./program/ptr_tests_extended", ""},
    {9, "Flag Combinations", "Tests various flag combinations", "./program/flag_combinations_tester", ""},
    {10, "Special Flags", "Tests special flag behavior", "./program/special_flags_tester", ""},
    {11, "Debug Tester", "Full debug tester", "./program/ft_printf_tester", ""},
    {12, "Simple Debug", "Simple debug tester", "./program/ft_printf_debug_tester_simple", ""},
    {13, "Stress Tests", "Performance and edge case tests", "./program/ft_printf_stress_tester", ""},
    {0, "Run All Tests", "Run all test programs in sequence", "", ""}
};

int num_tests = sizeof(tests) / sizeof(Test);


void delay_ms(int milliseconds)
{
    struct timespec ts;

    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}


void loading_bar(const char *message, int duration_ms, int segments)
{
    int segment_time = duration_ms / segments;
    int i;
    
    printf("%s%s%s [", CYAN, message, RESET);
    fflush(stdout);    
    for (i = 0; i < segments; i++)
    {
        delay_ms(segment_time);
        printf("%s█%s", BR_CYAN, RESET);
        fflush(stdout);
    }
    printf("] %sDone!%s\n", GREEN, RESET);
}


void spinner(const char *message, int duration_ms)
{
    char spin_chars[] = {'|', '/', '-', '\\'};
    int i, iterations = duration_ms / 100;
    
    for (i = 0; i < iterations; i++)
    {
        printf("\r%s %c ", message, spin_chars[i % 4]);
        fflush(stdout);
        delay_ms(100);
    }
    printf("\r%s %s%s%s\n", message, GREEN, "✓", RESET);
}


void display_header(const char *title)
{
    int terminal_width = 80;  
    int title_len = strlen(title);
    int padding = (terminal_width - title_len) / 2;
    
    printf("\n");
    for (int i = 0; i < terminal_width; i++) printf("%s═%s", CYAN, RESET);
    printf("\n%*s%s%s%s%s%*s\n", padding, "", BG_BLUE, BOLD, title, RESET, padding, "");
    for (int i = 0; i < terminal_width; i++) printf("%s═%s", CYAN, RESET);
    printf("\n");
}


void animate_terminal()
{
    printf(CLEAR_SCREEN);      
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
    
    
    int num_lines = sizeof(logo) / sizeof(logo[0]);
    const char *colors[] = {CYAN, BLUE, MAGENTA, RED, YELLOW, GREEN, BR_CYAN, BR_BLUE, BR_MAGENTA};
    int num_colors = sizeof(colors) / sizeof(colors[0]);
    for (int i = 0; i < num_lines; i++)
    {
        printf("%s%s%s\n", colors[i % num_colors], logo[i], RESET);
        delay_ms(80); 
        fflush(stdout);
    }
    printf("\n\n");
    loading_bar("Initializing controller environment", 1000, 20);
    spinner("Loading test programs", 1000);
    loading_bar("Preparing execution engine", 800, 15);
    spinner("Setting up test framework", 800);
    printf("\n%s%s ULTIMATE FT_PRINTF CONTROLLER READY %s\n\n", BOLD, BR_GREEN, RESET);
    delay_ms(500);
}


void display_menu()
{
    printf("%s╔═══════════════════════════════════════════════════════════╗%s\n", BLUE, RESET);
    printf("%s║%s%s              FT_PRINTF TEST SELECTION                 %s%s║%s\n", BLUE, RESET, BOLD, RESET, BLUE, RESET);
    printf("%s╠═══════════════════════════════════════════════════════════╣%s\n", BLUE, RESET);    
    printf("%s║%s%s%s 1. %-48s %s║%s\n", 
           BLUE, RESET, BG_GREEN, BOLD, tests[0].name, BLUE, RESET);
    printf("%s║%s%s%s    (Testing only: c s p d i u x X %%)                    %s║%s\n", 
           BLUE, RESET, ITALIC, YELLOW, BLUE, RESET);
    for (int i = 1; i < num_tests - 1; i++)
        printf("%s║%s %2d. %-48s %s║%s\n", BLUE, CYAN, tests[i].id, tests[i].name, BLUE, RESET);
    printf("%s║%s  0. %-48s %s║%s\n", BLUE, GREEN, tests[num_tests-1].name, BLUE, RESET);
    printf("%s║%s  q. %-48s %s║%s\n", BLUE, RED, "Quit", BLUE, RESET);
    printf("%s╚═══════════════════════════════════════════════════════════╝%s\n", BLUE, RESET);
    printf("\n%sEnter your choice:%s ", BOLD, RESET);
}


int is_executable(const char *path)
{
    return (access(path, X_OK) == 0);
}


int run_controller_test(Test test)
{
    char command[256];
    int status;

    printf("\n%s%s=== Running: %s ===%s\n", BOLD, YELLOW, test.name, RESET);
    printf("%s%s%s\n\n", ITALIC, test.description, RESET);    
    snprintf(command, sizeof(command), "%s %s", test.executable, test.arguments);
    if (!is_executable(test.executable))
    {
        printf("%s%s✗ Error: Test program not found: %s%s\n", 
               BOLD, RED, test.executable, RESET);
        printf("    Run 'make ensure_testers' to compile all test programs.\n\n");
        return (-1);
    }
    spinner("Starting test program", 500);
    status = system(command);    
    if (WIFEXITED(status))
    {
        int exit_status = WEXITSTATUS(status);
        if (exit_status == 0)
            printf("\n%s%s✓ Test completed successfully%s\n", BOLD, GREEN, RESET);
        else
            printf("\n%s%s✗ Test completed with errors (exit code: %d)%s\n", BOLD, RED, exit_status, RESET);
    } 
    else if (WIFSIGNALED(status))
        printf("\n%s%s✗ Test was terminated by signal %d%s\n", BOLD, RED, WTERMSIG(status), RESET); 
    else
        printf("\n%s%s? Test ended with unknown status%s\n", BOLD, YELLOW, RESET);
    return (status);
}


void run_all_tests()
{
    int success_count = 0;
    int fail_count = 0;
    int status;
    float success_percentage;
    int bar_width;
    int filled_width;
    
    display_header("RUNNING ALL TESTS");    
    for (int i = 0; i < num_tests - 1; i++)
    {
        printf("\n%s%s=== Test %d/%d: %s ===%s\n", 
               BOLD, CYAN, i+1, num_tests-1, tests[i].name, RESET);    
        status = run_controller_test(tests[i]); 
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            success_count++;
        else
            fail_count++;
        printf("\n%s%s════════════════════════════════════════════════%s\n", 
               BOLD, CYAN, RESET);
        delay_ms(500); 
    }
    printf("\n%s%s=== ALL TESTS COMPLETED ===%s\n", BOLD, MAGENTA, RESET);
    printf("Total tests:    %d\n", num_tests-1);
    printf("Successful:     %s%d%s\n", GREEN, success_count, RESET);
    printf("Failed:         %s%d%s\n", 
           fail_count > 0 ? RED : GREEN, fail_count, RESET);
    success_percentage = (float)success_count / (num_tests-1) * 100;
    bar_width = 50;
    filled_width = (int)(success_percentage * bar_width / 100);
    printf("\nSuccess rate:   [");
    for (int i = 0; i < bar_width; i++)
    {
        if (i < filled_width)
            printf("%s█%s", GREEN, RESET);
        else
            printf("%s▒%s", RED, RESET);
    }
    printf("] %.1f%%\n\n", success_percentage);
}


int main()
{
    
    int enable_animations = isatty(STDOUT_FILENO);
    int running, choice;
    char input[10];

    if (enable_animations)
        animate_terminal();
    else
        printf("FT_PRINTF ULTIMATE TEST CONTROLLER\n\n");
    running = 1;
    while (running) {
        display_menu();
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        if (input[0] == 'q' || input[0] == 'Q')
            break;
        choice = atoi(input);
        if (enable_animations)
            printf(CLEAR_SCREEN);
        if (choice == 0)
            run_all_tests();
        else
        {    
            Test *selected_test = NULL;
            for (int i = 0; i < num_tests; i++)
            {
                if (tests[i].id == choice)
                {
                    selected_test = &tests[i];
                    break;
                }
            }
            if (selected_test)
                run_controller_test(*selected_test); 
            else
            {
                printf("%s%sInvalid choice. Please try again.%s\n\n", BOLD, RED, RESET);
                continue;
            }
        }
        
        if (enable_animations)
        {
            printf("\n%sPress Enter to return to menu...%s", YELLOW, RESET);
            getchar(); 
            printf(CLEAR_SCREEN);
        } 
        else
            running = 0;
    }
    if (enable_animations)
    {
        printf("\n%s%sFT_PRINTF ULTIMATE TEST CONTROLLER EXITING...%s\n", BOLD, CYAN, RESET);
        delay_ms(500);
    }
    return (0);
}
