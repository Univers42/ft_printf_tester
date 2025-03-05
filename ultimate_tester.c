/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:18:24 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/05 14:35:30 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <stdarg.h>

#define BR_CYAN   "\033[96m"
#define BR_BLUE   "\033[94m"
#define BR_MAGENTA "\033[95m"
#define BR_GREEN  "\033[92m"
#define BG_MAGENTA "\033[45m"
#include "ft_printf_test_utils.h"
#define CLEAR_SCREEN "\033[2J\033[H"
typedef enum {
    CHAR_TEST,
    STRING_TEST,
    INT_TEST,
    UINT_TEST,
    HEX_TEST,
    POINTER_TEST,
    PERCENT_TEST,
    MIXED_TEST,
    STRESS_TEST
} TestCategory;

const char *category_names[] =
{
    "Character Tests",
    "String Tests",
    "Integer Tests",
    "Unsigned Integer Tests",
    "Hexadecimal Tests",
    "Pointer Tests",
    "Percent Sign Tests",
    "Mixed Format Tests",
    "Stress Tests"
};


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


void display_category(TestCategory category)
{
    printf("\n%s%s=== %s ===%s\n\n", BOLD, YELLOW, category_names[category], RESET);
}


void display_results()
{
    int terminal_width = 80;
    float pass_percentage = (float)pass_count / test_count * 100;
    int gauge_width = 50;
    int filled;

    printf("\n");
    for (int i = 0; i < terminal_width; i++) printf("%s═%s", MAGENTA, RESET);
    printf("\n%s%s%s TEST SUMMARY %s\n", BG_MAGENTA, BOLD, WHITE, RESET);
    for (int i = 0; i < terminal_width; i++) printf("%s═%s", MAGENTA, RESET);    
    printf("\n%sTotal tests:%s %d\n", BOLD, RESET, test_count);
    printf("%sPassed:%s %s%d (%.1f%%)%s\n", BOLD, RESET, 
           GREEN, pass_count, pass_percentage, RESET);
    printf("%sFailed:%s %s%d (%.1f%%)%s\n", BOLD, RESET, 
           fail_count > 0 ? RED : GREEN, 
           fail_count, 100.0 - pass_percentage, RESET);
    printf("\n");
    filled = (int)(pass_percentage / 100.0 * gauge_width);    
    printf("%s[%s", BOLD, RESET);
    for (int i = 0; i < gauge_width; i++)
    {
        if (i < filled)
            printf("%s█%s", GREEN, RESET);
        else
            printf("%s▒%s", RED, RESET);
    }
    printf("%s]%s %.1f%%\n\n", BOLD, RESET, pass_percentage);
}


void test_characters()
{
    display_category(CHAR_TEST);
    run_test("Basic character", "%c", 'A');
    run_test("Digit character", "%c", '0');
    run_test("Space character", "%c", ' ');
    run_test("Special character", "%c", '@');
    run_test("Width 5", "%5c", 'Z');
    run_test("Left-aligned width 5", "%-5c", 'Z');
    run_test("Width 10", "%10c", 'Z');
    run_test("Left-aligned width 10", "%-10c", 'Z');
    run_test("ASCII 0 (NULL character)", "%c", 0);
    run_test("ASCII 127 (DEL character)", "%c", 127);
    run_test("Characters in context", "Before %c middle %c after", 'A', 'Z');
    run_test("Multiple characters", "%c%c%c%c%c", 'H', 'E', 'L', 'L', 'O');
}

void test_strings()
{
    char long_string[1000];
    
    display_category(STRING_TEST);    
    run_test("Basic string", "%s", "Hello, world!");
    run_test("Empty string", "%s", "");
    run_test("NULL string", "%s", NULL);
    run_test("Width 20", "%20s", "Hello");
    run_test("Left-aligned width 20", "%-20s", "Hello");
    run_test("Precision 3", "%.3s", "Hello");
    run_test("Precision 0", "%.0s", "Hello");
    run_test("Precision dot", "%.s", "Hello");
    run_test("Width 10, precision 3", "%10.3s", "Hello");
    run_test("Left-aligned width 10, precision 3", "%-10.3s", "Hello");
    run_test("String with special chars", "%s", "Hello\nWorld");
    run_test("String with tabs", "%s", "Hello\tWorld");
    run_test("NULL with precision 3", "%.3s", NULL);
    run_test("NULL with precision 10", "%.10s", NULL);
    memset(long_string, 'A', 999);
    long_string[999] = '\0';
    run_test("Very long string", "%s", long_string);
    run_test("Long string with precision", "%.50s", long_string);
}

void test_integers()
{
    display_category(INT_TEST);
    run_test("Zero", "%d", 0);
    run_test("Positive integer", "%d", 42);
    run_test("Negative integer", "%d", -42);
    run_test("INT_MAX", "%d", INT_MAX);
    run_test("INT_MIN", "%d", INT_MIN);
    run_test("Width 10", "%10d", 42);
    run_test("Left-aligned width 10", "%-10d", 42);
    run_test("Zero-padded width 10", "%010d", 42);
    run_test("Negative with width 10", "%10d", -42);
    run_test("Negative with left-aligned width 10", "%-10d", -42);
    run_test("Negative with zero-padded width 10", "%010d", -42);    
    run_test("Precision 5", "%.5d", 42);
    run_test("Zero with precision 0", "%.0d", 0);
    run_test("Zero with precision dot", "%.d", 0);
    run_test("Width 10, precision 5", "%10.5d", 42);
    run_test("Left-aligned width 10, precision 5", "%-10.5d", 42);
    run_test("Negative with precision 5", "%.5d", -42);
    run_test("Plus flag with positive", "%+d", 42);
    run_test("Plus flag with zero", "%+d", 0);
    run_test("Plus flag with width", "%+10d", 42);
    run_test("Plus flag with precision", "%+.5d", 42);
    run_test("Space flag with positive", "% d", 42);
    run_test("Space flag with zero", "% d", 0);
    run_test("Space flag with negative", "% d", -42);
    run_test("Complex combination 1", "%+10.5d", 42);
    run_test("Complex combination 2", "%-+10.5d", 42);
    run_test("Complex combination 3", "%0+10d", 42);
    run_test("Complex combination 4", "% 10.5d", 42);
    run_test("Complex combination 5", "%- 10.5d", 42);
}

#undef test_unsigned
#undef test_hex

void my_test_unsigned()
{
    display_category(UINT_TEST);    
    run_test("Zero", "%u", 0);
    run_test("Positive unsigned", "%u", 42);
    run_test("Large unsigned", "%u", 4294967295u); 
    run_test("Width 10", "%10u", 42);
    run_test("Left-aligned width 10", "%-10u", 42);
    run_test("Zero-padded width 10", "%010u", 42);
    run_test("Precision 5", "%.5u", 42);
    run_test("Zero with precision 0", "%.0u", 0);
    run_test("Zero with precision dot", "%.u", 0);
    run_test("Width 10, precision 5", "%10.5u", 42);
    run_test("Left-aligned width 10, precision 5", "%-10.5u", 42);
    run_test("Plus flag (should be ignored)", "%+u", 42);
    run_test("Space flag (should be ignored)", "% u", 42);
}

void my_test_hex()
{
    display_category(HEX_TEST);    
    run_test("Zero lowercase", "%x", 0);
    run_test("Positive lowercase", "%x", 42);
    run_test("Large lowercase", "%x", 0xabcdef);
    run_test("Zero uppercase", "%X", 0);
    run_test("Positive uppercase", "%X", 42);
    run_test("Large uppercase", "%X", 0xABCDEF);
    run_test("Width 10 lowercase", "%10x", 0xabc);
    run_test("Left-aligned width 10 lowercase", "%-10x", 0xabc);
    run_test("Zero-padded width 10 lowercase", "%010x", 0xabc);
    run_test("Width 10 uppercase", "%10X", 0xABC);
    run_test("Left-aligned width 10 uppercase", "%-10X", 0xABC);
    run_test("Zero-padded width 10 uppercase", "%010X", 0xABC);
}

void test_pointers()
{
    int int_var = 42;
    char char_var = 'A';
    void *ptr1 = &int_var;
    void *ptr2 = &char_var;
    void *ptr3 = NULL;
    
    display_category(POINTER_TEST);    
    run_test("Basic pointer 1", "%p", ptr1);
    run_test("Basic pointer 2", "%p", ptr2);
    run_test("NULL pointer", "%p", ptr3);
    run_test("Width 20", "%20p", ptr1);
    run_test("Left-aligned width 20", "%-20p", ptr1);
    run_test("Width 20 with NULL", "%20p", ptr3);
    run_test("Left-aligned width 20 with NULL", "%-20p", ptr3);
    run_test("Precision 15", "%.15p", ptr1);
    run_test("Width 20, precision 15", "%20.15p", ptr1);
    run_test("Left-aligned width 20, precision 15", "%-20.15p", ptr1);
    run_test("Zero padding", "%020p", ptr1);
    run_test("Plus flag (platform-dependent)", "%+p", ptr1);
    run_test("Space flag (platform-dependent)", "% p", ptr1);
    run_test("Hash flag (platform-dependent)", "%#p", ptr1);
    run_test("Multiple pointers", "P1: %p, P2: %p, NULL: %p", ptr1, ptr2, ptr3);
}

void test_percent()
{
    display_category(PERCENT_TEST);    
    run_test("Basic percent sign", "%%");
    run_test("Multiple percent signs", "%%%% double, %%%%%% triple");
    run_test("Percent with text", "This is 100%% certain");
    run_test("Width 5", "%5%");
    run_test("Left-aligned width 5", "%-5%");
    run_test("Width 10", "%10%");
    run_test("Left-aligned width 10", "%-10%");
    run_test("Zero-padded width 5", "%05%");
}

void test_mixed()
{
    display_category(MIXED_TEST);    
    run_test("Mixed formats 1", "Char: %c, String: %s, Int: %d", 'A', "Hello", 42);
    run_test("Mixed formats 2", "Unsigned: %u, Hex: %x, Pointer: %p, Percent: %%", 
             123, 0xabc, &test_count);
    run_test("Mixed with flags", 
             "Width: %5d, Precision: %.3s, Left: %-10d, Zero: %05d", 
             42, "Hello", 123, 7);
    run_test("Complex text",
             "The %s contains %d %c%c%c%c%cs and %x in hex, plus %p pointer.",
             "string", 42, 'l', 'e', 't', 't', 'e', 0xabc, &test_count);
}

void test_stress()
{
    char percent_buffer[100];
    
    display_category(STRESS_TEST);
    run_test("Very large width", "%1000d", 42);
    run_test("Very large left-aligned width", "%-1000d", 42);
    run_test("Very large zero-padded width", "%01000d", 42);    
    run_test("Very large precision string", "%.500s", "This string will be printed in full");
    run_test("Very large precision int", "%.500d", 42);
    run_test("Many arguments", 
             "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
             1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
    run_test("Complex format string",
             "Normal:%s, %% Width:%-10s %% Left:%-*d %% Prec:%.5d %% Zero:%010d %% Hex:%#x %% Ptr:%p",
             "test", "aligned", 10, 123, 42, 7, 0xabc, &test_count);
    run_test("INT_MIN", "%d", INT_MIN);
    run_test("UINT_MAX", "%u", UINT_MAX);
    run_test("Print a NULL character", "Start%cEnd", '\0');
    memset(percent_buffer, '%', 99);
    percent_buffer[99] = '\0';
    run_test("Many percent signs", "%s", percent_buffer);
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
        "         █████╗ ██████╗ ██╗   ██╗ █████╗ ███╗   ██╗ ██████╗███████╗",
        "        ██╔══██╗██╔══██╗██║   ██║██╔══██╗████╗  ██║██╔════╝██╔════╝",
        "        ███████║██║  ██║██║   ██║███████║██╔██╗ ██║██║     █████╗  ",
        "        ██╔══██║██║  ██║╚██╗ ██╔╝██╔══██║██║╚██╗██║██║     ██╔══╝  ",
        "        ██║  ██║██████╔╝ ╚████╔╝ ██║  ██║██║ ╚████║╚██████╗███████╗",
        "        ╚═╝  ╚═╝╚═════╝   ╚═══╝  ╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝╚══════╝",
        "                                                                    ",
        "                    ████████╗███████╗███████╗████████╗███████╗██████╗ ",
        "                    ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗",
        "                       ██║   █████╗  ███████╗   ██║   █████╗  ██████╔╝",
        "                       ██║   ██╔══╝  ╚════██║   ██║   ██╔══╝  ██╔══██╗",
        "                       ██║   ███████╗███████║   ██║   ███████╗██║  ██║",
        "                       ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝"
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
    loading_bar("Initializing test environment", 1000, 20);
    spinner("Loading test cases", 1000);
    loading_bar("Preparing output buffer", 800, 15);
    spinner("Setting up comparison logic", 800);
    printf("\n%s%s ULTIMATE FT_PRINTF TESTER READY %s\n\n", BOLD, BR_GREEN, RESET);
    delay_ms(500);
}


int display_menu()
{
    printf("%s╔════════════════════════════════════╗%s\n", BLUE, RESET);
    printf("%s║%s%s          TEST CATEGORIES          %s%s║%s\n", BLUE, RESET, BOLD, RESET, BLUE, RESET);
    printf("%s╠════════════════════════════════════╣%s\n", BLUE, RESET);
    printf("%s║%s 1. Character Tests                %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 2. String Tests                   %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 3. Integer Tests                  %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 4. Unsigned Integer Tests         %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 5. Hexadecimal Tests              %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 6. Pointer Tests                  %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 7. Percent Sign Tests             %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 8. Mixed Format Tests             %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 9. Stress Tests                   %s║%s\n", BLUE, CYAN, BLUE, RESET);
    printf("%s║%s 0. Run All Tests                  %s║%s\n", BLUE, GREEN, BLUE, RESET);
    printf("%s║%s q. Quit                           %s║%s\n", BLUE, RED, BLUE, RESET);
    printf("%s╚════════════════════════════════════╝%s\n", BLUE, RESET);
    printf("\n%sEnter your choice:%s ", BOLD, RESET);
    char input = getchar();
    while (getchar() != '\n'); 
    if (input == 'q' || input == 'Q')
        return -1;    
    return (input >= '0' && input <= '9') ? input - '0' : -2;
}

int main()
{    
    int enable_animations = isatty(STDOUT_FILENO);   

    if (enable_animations)
    {
        animate_terminal();    
        int choice;
        while ((choice = display_menu()) != -1)
        {
            if (choice == -2)
            {
                printf("%sInvalid choice. Please try again.%s\n\n", RED, RESET);
                continue;
            }
            printf(CLEAR_SCREEN);
            display_header("FT_PRINTF ULTIMATE TESTER");
            switch (choice)
            {
                case 0: 
                    test_characters();
                    test_strings();
                    test_integers();
                    my_test_unsigned();  
                    my_test_hex();       
                    test_pointers();
                    test_percent();
                    test_mixed();
                    test_stress();
                    break;
                case 1:
                    test_characters();
                    break;
                case 2:
                    test_strings();
                    break;
                case 3:
                    test_integers();
                    break;
                case 4:
                    my_test_unsigned();  
                    break;
                case 5:
                    my_test_hex();       
                    break;
                case 6:
                    test_pointers();
                    break;
                case 7:
                    test_percent();
                    break;
                case 8:
                    test_mixed();
                    break;
                case 9:
                    test_stress();
                    break;
            }
            display_results();
            printf("\n%sPress Enter to return to menu...%s", YELLOW, RESET);
            getchar();
            printf(CLEAR_SCREEN);
            test_count = 0;
            pass_count = 0;
            fail_count = 0;
        }
    }
    else
    {   
        display_header("FT_PRINTF ULTIMATE TESTER");   
        test_characters();
        test_strings();
        test_integers();
        my_test_unsigned();  
        my_test_hex();       
        test_pointers();
        test_percent();
        test_mixed();
        test_stress();
        display_results();
    }
    return (fail_count > 0) ? 1 : 0;
}
