/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_basic_tester.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:26 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 15:34:01 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "headers/controller.h"

int capture_output_local(char *buffer, size_t bufsize, int (*func)(const char*, ...), const char *format, ...)
{
    int pipefd[2];
    pid_t pid;
    int status, ret_val;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    { 
        va_list args;
        va_start(args, format);

        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        if (func == ft_printf)
            ret_val = func(format, args);
        else
            ret_val = vprintf(format, args);
        va_end(args);
        exit(ret_val);
    } 
    else
    {    
        close(pipefd[1]);
        ssize_t nread = read(pipefd[0], buffer, bufsize-1);
        if (nread > 0)
            buffer[nread] = '\0';
        else
            buffer[0] = '\0';
        close(pipefd[0]);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            ret_val = WEXITSTATUS(status);
        else
            ret_val = -1;
        return (ret_val);
    }
}

int main(void)
{
    printf("===== BASIC FT_PRINTF TESTS =====\n\n");    
    run_test("Simple String", "Hello, world!");
    run_test("Character", "Character: %c", 'A');
    run_test("String", "String: %s", "test");
    run_test("Integer", "Integer: %d", 42);
    run_test("Negative integer", "Negative: %d", -42);
    run_test("Zero", "Zero: %d", 0);
    run_test("Unsigned", "Unsigned: %u", 42);
    run_test("Hex lowercase", "Hex: %x", 42);
    run_test("Hex uppercase", "HEX: %X", 42);
    run_test("Percent sign", "Percent: %%");
    run_test("Width", "Width: %5d", 42);
    run_test("Precision", "Precision: %.5d", 42);
    run_test("Left Justify", "Left: %-5d", 42);
    run_test("Plus Sign", "Plus: %+d", 42);
    run_test("Space", "Space: % d", 42);
    run_test("Zero Padding", "Zero: %05d", 42);
    run_test("Hash", "Hash: %#x", 42);
    return 0;
}
