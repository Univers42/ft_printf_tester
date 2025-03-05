/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:22 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/05 13:48:18 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

typedef struct s_test_stats {
    int passed;
    int failed;
    int total;
} t_test_stats;

t_test_stats stats = {0, 0, 0};

void print_header(const char *title)
{
    int len = strlen(title);
    int i;
    
    printf("\n%s%s", BOLD, BLUE);
    for (i = 0; i < len + 4; i++)
        printf("=");
    printf("\n| %s |\n", title);
    for (i = 0; i < len + 4; i++)
        printf("=");
    printf("%s\n\n", RESET);
}

int main()
{
    int dummy;
    char long_str[1000];
    
    printf("%s%s===================================\n", BOLD, CYAN);
    printf("   FT_PRINTF COMPREHENSIVE TESTER   \n");
    printf("===================================%s\n\n", RESET);    
    print_header("BASIC FUNCTIONALITY TESTS");    
    run_test("Basic character", "%c", 'A');
    run_test("Multiple characters", "%c %c %c", 'a', 'b', 'c');
    run_test("Character with text", "This is a character: %c", 'X');    
    run_test("Basic string", "%s", "Hello, World!");
    run_test("Empty string", "%s", "");
    run_test("NULL string", "%s", NULL);
    run_test("Multiple strings", "%s %s", "Hello,", "World!");
    run_test("Zero integer", "%d", 0);
    run_test("Positive integer", "%d", 42);
    run_test("Negative integer", "%d", -42);
    run_test("INT_MAX", "%d", INT_MAX);
    run_test("INT_MIN", "%d", INT_MIN);
    run_test("Multiple integers", "%d %i %d", 1, 2, 3);
    run_test("Zero unsigned", "%u", 0);
    run_test("Positive unsigned", "%u", 42);
    run_test("Large unsigned", "%u", UINT_MAX);
    run_test("Zero hex", "%x", 0);
    run_test("Positive hex", "%x", 42);
    run_test("Large hex", "%x", UINT_MAX);
    run_test("Zero hex uppercase", "%X", 0);
    run_test("Positive hex uppercase", "%X", 42);
    run_test("Large hex uppercase", "%X", UINT_MAX);    
    dummy = 42;
    run_test("Basic pointer", "%p", &dummy);
    run_test("NULL pointer", "%p", NULL);
    run_test("Percent sign", "%%");
    run_test("Multiple percent signs", "%% %% %%");
    print_header("WIDTH AND PRECISION TESTS");
    run_test("Width with character", "%5c", 'A');
    run_test("Width with string", "%10s", "Hello");
    run_test("Width with integer", "%7d", 42);
    run_test("Width with unsigned", "%7u", 42);
    run_test("Width with hex", "%7x", 42);
    run_test("Width with pointer", "%15p", &dummy);
    run_test("Precision with string", "%.5s", "Hello World");
    run_test("Precision with integer", "%.5d", 42);
    run_test("Precision with unsigned", "%.5u", 42);
    run_test("Precision with hex", "%.5x", 42);
    run_test("Width and precision with string", "%10.5s", "Hello World");
    run_test("Width and precision with integer", "%10.5d", 42);
    run_test("Width and precision with negative", "%10.5d", -42);
    run_test("Width and precision with unsigned", "%10.5u", 42);
    run_test("Width and precision with hex", "%10.5x", 42);    
    run_test("Zero precision with string", "%.0s", "Hello");
    run_test("Zero precision with zero", "%.0d", 0);
    run_test("Zero precision with integer", "%.0d", 42);
    print_header("FLAG TESTS");    
    run_test("Left-justify character", "%-5c", 'A');
    run_test("Left-justify string", "%-10s", "Hello");
    run_test("Left-justify integer", "%-7d", 42);
    run_test("Left-justify negative", "%-7d", -42);
    run_test("Left-justify unsigned", "%-7u", 42);
    run_test("Left-justify hex", "%-7x", 42);
    run_test("Left-justify pointer", "%-15p", &dummy);
    run_test("Show sign positive", "%+d", 42);
    run_test("Show sign negative", "%+d", -42);
    run_test("Show sign zero", "%+d", 0);
    run_test("Space if positive", "% d", 42);
    run_test("Space if negative", "% d", -42);
    run_test("Space if zero", "% d", 0);    
    run_test("Zero padding integer", "%05d", 42);
    run_test("Zero padding negative", "%05d", -42);
    run_test("Zero padding unsigned", "%05u", 42);
    run_test("Zero padding hex", "%05x", 42);
    run_test("Hash flag with non-zero hex", "%#x", 42);
    run_test("Hash flag with zero hex", "%#x", 0);
    run_test("Hash flag with uppercase hex", "%#X", 42);    
    print_header("COMBINATION TESTS");
    run_test("Left-justify + width + precision", "%-10.5d", 42);
    run_test("Show sign + width + precision", "%+10.5d", 42);
    run_test("Space + width + precision", "% 10.5d", 42);
    run_test("Zero padding + width + precision", "%010.5d", 42);
    run_test("Hash + width + precision", "%#10.5x", 42);
    run_test("Left-justify + show sign", "%-+10d", 42);
    run_test("Left-justify + space", "%- 10d", 42);
    run_test("Left-justify + hash", "%-#10x", 42);
    run_test("Show sign + zero padding", "%+010d", 42);
    run_test("Space + zero padding", "% 010d", 42);
    run_test("Hash + zero padding", "%#010x", 42);
    print_header("EDGE CASES");
    run_test("Long int MAX", "%ld", LONG_MAX);
    run_test("Long int MIN", "%ld", LONG_MIN);
    run_test("Unsigned long MAX", "%lu", ULONG_MAX);
    run_test("Mixed conversions", "Char: %c, String: %s, Int: %d, Hex: %x", 'A', "Hello", 42, 42);
    run_test("Invalid specifier", "Invalid: %z");
    memset(long_str, 'A', 999);
    long_str[999] = '\0';
    run_test("Long string", "%s", long_str);    
    print_summary();
    return (0);
}
