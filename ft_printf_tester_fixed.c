/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tester_fixed.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:19 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/05 13:46:13 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"  
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

int capture_output_fixed(char *buffer, size_t bufsize, const char *format, ...)
{
    va_list args;
    int ret_val, original_stdout;
    
    va_start(args, format);    
    FILE *temp = tmpfile();
    if (!temp)
    {
        perror("tmpfile");
        va_end(args);
        return -1;
    }
    original_stdout = dup(STDOUT_FILENO);
    if (dup2(fileno(temp), STDOUT_FILENO) == -1)
    {
        perror("dup2");
        fclose(temp);
        va_end(args);
        return -1;
    }
    ret_val = vprintf(format, args);
    fflush(stdout); 
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
    rewind(temp);
    size_t read_size = fread(buffer, 1, bufsize - 1, temp);
    buffer[read_size] = '\0';
    fclose(temp);
    va_end(args);
    return (ret_val);
}

int main(void) {
    printf("=== FT_PRINTF FIXED TESTER ===\n\n");    
    run_test("Simple string", "Hello, world!");
    run_test("Character", "%c", 'A');
    run_test("String", "%s", "test");
    run_test("Integer", "%d", 42);
    run_test("Negative integer", "%d", -42);
    run_test("Mixed formats", "This %s is %c %d% complete!", "test", 'a', 100);
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
