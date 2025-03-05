/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_tester.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:02 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/05 13:36:42 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"

typedef struct s_test_stats
{
    int passed;
    int failed;
    int total;
}	t_test_stats;

t_test_stats	g_stats = {0, 0, 0};

void	redirect_stdout(int *saved_stdout, int *pipe_fd, char *buffer)
{
    *saved_stdout = dup(STDOUT_FILENO);
    pipe(pipe_fd);
    dup2(pipe_fd[1], STDOUT_FILENO);
    setvbuf(stdout, buffer, _IOFBF, BUFFER_SIZE);
}

void	restore_stdout(int saved_stdout, int *pipe_fd)
{
    fflush(stdout);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
}

int	capture_ft_printf_output(char *buffer, int buffer_size, int *ret_val, const char *format, ...)
{
    int		saved_stdout;
    int		pipe_fd[2];
    char	stdout_buf[BUFFER_SIZE] = {0};
    int		read_bytes;
    va_list	args;

    redirect_stdout(&saved_stdout, pipe_fd, stdout_buf);
    va_start(args, format);
    *ret_val = ft_printf(format, args);
    va_end(args);
    fflush(stdout);
    read_bytes = read(pipe_fd[0], buffer, buffer_size - 1);
    buffer[read_bytes > 0 ? read_bytes : 0] = '\0';
    restore_stdout(saved_stdout, pipe_fd);
    return (read_bytes);
}

int	capture_printf_output(char *buffer, int buffer_size, int *ret_val, const char *format, ...)
{
    int		saved_stdout;
    int		pipe_fd[2];
    char	stdout_buf[BUFFER_SIZE] = {0};
    int		read_bytes;
    va_list	args;

    redirect_stdout(&saved_stdout, pipe_fd, stdout_buf);
    va_start(args, format);
    *ret_val = printf(format, args);
    va_end(args);
    fflush(stdout);
    read_bytes = read(pipe_fd[0], buffer, buffer_size - 1);
    buffer[read_bytes > 0 ? read_bytes : 0] = '\0';
    restore_stdout(saved_stdout, pipe_fd);
    return (read_bytes);
}

char	*random_string(int max_length)
{
    static const char	charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int					length;
    char				*str;

    length = rand() % max_length + 1;
    str = (char *)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++)
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    str[length] = '\0';
    return (str);
}

char	*random_format_string(int max_length)
{
    static const char	*specifiers = "cspdiuxX%";
    static const char	*flags = "-+#0 ";
    char				*format;
    int					pos;
    int					spec_count;

    format = (char *)malloc(max_length + 1);
    pos = 0;
    spec_count = rand() % 3 + 1;
    while (pos < max_length - 10 && spec_count > 0)
    {
        int text_len = rand() % 5;
        for (int i = 0; i < text_len && pos < max_length - 10; i++)
            format[pos++] = 'A' + rand() % 26;
        if (pos < max_length - 10)
        {
            format[pos++] = '%';
            int flag_count = rand() % 3;
            for (int i = 0; i < flag_count && pos < max_length - 8; i++)
                format[pos++] = flags[rand() % strlen(flags)];
            if (rand() % 3 == 0 && pos < max_length - 7)
            {
                int width = rand() % 20 + 1;
                pos += sprintf(format + pos, "%d", width);
            }
            if (rand() % 3 == 0 && pos < max_length - 5)
            {
                format[pos++] = '.';
                int precision = rand() % 10;
                pos += sprintf(format + pos, "%d", precision);
            }
            format[pos++] = specifiers[rand() % strlen(specifiers)];
            spec_count--;
        }
    }
    format[pos] = '\0';
    return (format);
}

void	run_stress_tests(void)
{
    run_test("Stress test 1", "%d", 123456789);
    run_test("Stress test 2", "%s", "A very long string to test the buffer size and performance of the ft_printf function.");
    run_test("Stress test 3", "%x", 0xabcdef);
    run_test("Stress test 4", "%p", &run_stress_tests);
    run_test("Stress test 5", "Mixed: %d %s %x %p", 42, "test", 0x1234, &run_stress_tests);
}

int	main(void)
{
    int		i;
    char	*random_fmt;
    char	*random_str;

    srand(time(NULL));
    printf("%s%s========================================================\n", BOLD, CYAN);
    printf("        FT_PRINTF ADVANCED STRESS TESTER v1.0          \n");
    printf("========================================================%s\n\n", RESET);
    printf("%s%s===== BASIC FUNCTIONALITY TESTS =====%s\n\n", BOLD, BLUE, RESET);
    run_test("No conversion", "Hello, World!");
    run_test("Single character", "%c", 'A');
    run_test("String", "%s", "Hello, World!");
    run_test("NULL string", "%s", NULL);
    run_test("Empty string", "%s", "");
    run_test("Integer", "%d", 42);
    run_test("Negative integer", "%d", -42);
    run_test("Zero integer", "%d", 0);
    run_test("Unsigned integer", "%u", 42);
    run_test("Hex lowercase", "%x", 0xDEADBEEF);
    run_test("Hex uppercase", "%X", 0xDEADBEEF);
    run_test("Pointer", "%p", main);
    run_test("Percent sign", "%%");
    run_test("Multiple conversions", "%c %s %d %u %x %p %%", 'A', "Hello", 42, 123, 0xDEAD, main);
    printf("\n%s%s===== EDGE CASE TESTS =====%s\n\n", BOLD, BLUE, RESET);
    run_test("INT_MAX", "%d", INT_MAX);
    run_test("INT_MIN", "%d", INT_MIN);
    run_test("UINT_MAX", "%u", UINT_MAX);
    run_test("LONG_MAX", "%ld", LONG_MAX);
    run_test("LONG_MIN", "%ld", LONG_MIN);
    run_test("Consecutive percent signs", "%% %% %%");
    run_test("Very long string", "%s", "This is a very long string that should test the buffer handling of your ft_printf implementation. It's important to make sure that your function can handle strings of arbitrary length correctly, especially when combined with other formatting options.");
    run_test("Multiple spaces", "%d %d %d %d %d", 1, 2, 3, 4, 5);
    printf("\n%s%s===== FLAG TESTS =====%s\n\n", BOLD, BLUE, RESET);
    run_test("Minus flag with char", "%-5c", 'A');
    run_test("Minus flag with string", "%-10s", "Hello");
    run_test("Plus flag with positive int", "%+d", 42);
    run_test("Plus flag with negative int", "%+d", -42);
    run_test("Space flag with positive int", "% d", 42);
    run_test("Space flag with negative int", "% d", -42);
    run_test("Zero flag with int", "%05d", 42);
    run_test("Zero flag with negative int", "%05d", -42);
    run_test("Hash flag with hex", "%#x", 42);
    run_test("Hash flag with zero", "%#x", 0);
    printf("\n%s%s===== WIDTH AND PRECISION TESTS =====%s\n\n", BOLD, BLUE, RESET);
    run_test("Width only", "%10d", 42);
    run_test("Width only with string", "%10s", "Hello");
    run_test("Precision only with int", "%.5d", 42);
    run_test("Precision only with string", "%.5s", "Hello World");
    run_test("Precision zero int", "%.0d", 0);
    run_test("Precision zero string", "%.0s", "Hello");
    run_test("Width and precision", "%10.5d", 42);
    run_test("Width and precision with string", "%10.5s", "Hello World");
    printf("\n%s%s===== COMBINATION TESTS =====%s\n\n", BOLD, BLUE, RESET);
    run_test("All flags", "%+-#0 d", 42);
    run_test("Width + flags", "%+-10d", 42);
    run_test("Precision + flags", "%+.5d", 42);
    run_test("Width + precision + flags", "%+-10.5d", 42);
    run_test("Multiple mixed conversions", "Char: %c, String: %s, Int: %+d, Hex: %#x, Pointer: %p", 'A', "Hello", 42, 0xDEAD, main);
    printf("\n%s%s===== RANDOM FORMAT STRING TESTS =====%s\n\n", BOLD, BLUE, RESET);
    int random_test_count = 20;
    for (i = 0; i < random_test_count; i++)
    {
        random_fmt = random_format_string(RANDOM_TEST_MAX_LENGTH);
        random_str = random_string(RANDOM_STR_MAX);
        char test_name[50];
        sprintf(test_name, "Random Test #%d", i + 1);
        if (strlen(random_fmt) > 15)
        {
            free(random_fmt);
            random_fmt = malloc(3);
            if (random_fmt)
                strcpy(random_fmt, "%s");
            else
            {
                free(random_str);
                continue;
            }
        }
        if (random_fmt && random_str)
        {
            if (strstr(random_fmt, "%s"))
                run_test(test_name, random_fmt, random_str);
            else if (strstr(random_fmt, "%c"))
                run_test(test_name, random_fmt, 'A' + (i % 26));
            else if (strstr(random_fmt, "%d") || strstr(random_fmt, "%i"))
                run_test(test_name, random_fmt, rand() % 1000 - 500);
            else if (strstr(random_fmt, "%u") || strstr(random_fmt, "%x") || strstr(random_fmt, "%X"))
                run_test(test_name, random_fmt, rand() % 1000);
            else if (strstr(random_fmt, "%p"))
                run_test(test_name, random_fmt, &main);
            else
                run_test(test_name, random_fmt);
        }
        if (random_fmt)
        {
            free(random_fmt);
            random_fmt = NULL;
        }
        if (random_str)
        {
            free(random_str);
            random_str = NULL;
        }
    }
    print_summary();
    return (0);
}
