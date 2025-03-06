/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_test_macros.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:20:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 16:14:11 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TEST_MACROS_H
# define FT_PRINTF_TEST_MACROS_H

# include "ft_printf_test_utils.h"

/**
 * Common test macros used across test files
 */

/* Simple format-specific test macros */
# define TEST_FORMAT(fmt, ...) test_format(fmt, fmt, (void *)&__VA_ARGS__, \
                        fmt[strcspn(fmt, "cspdiuxX%")])

# define TEST_CHAR(fmt, c) test_char(c, fmt, fmt)
# define TEST_STR(fmt, str) test_string(str, fmt, fmt)
# define TEST_INT(fmt, num) test_int(num, fmt, fmt)
# define TEST_UINT(fmt, num) test_unsigned(num, fmt, fmt)
# define TEST_HEX(fmt, num, upper) test_hex(num, upper, fmt, fmt)
# define TEST_PTR(fmt, ptr) test_pointer(ptr, fmt, fmt)

/* Multi-argument test macros */
# define TEST_MULTI_CHAR(fmt, ...) test_multiple_chars(fmt, fmt, __VA_ARGS__)
# define TEST_MULTI_STR(fmt, ...) test_multiple_strings(fmt, fmt, __VA_ARGS__)
# define TEST_MULTI_PTR(fmt, ...) test_multiple_pointers(fmt, fmt, __VA_ARGS__)

/* Named test with custom description */
# define TEST_NAMED(name, fmt, ...) test_format(fmt, name, (void *)&__VA_ARGS__, \
                                   fmt[strcspn(fmt, "cspdiuxX%")])

/* Main TEST macro using pipes and direct comparison */                                                                      
# define TEST(format, ...) do { \
        int orig_ret, ft_ret; \
        char orig_buf[BUFFER_SIZE] = {0}; \
        char ft_buf[BUFFER_SIZE] = {0}; \
        \
        /* Capture standard printf output */ \
        FILE *orig_stream = fmemopen(orig_buf, sizeof(orig_buf) - 1, "w"); \
        if (!orig_stream) { \
            printf("Error: Failed to open memory stream\n"); \
            exit(1); \
        } \
        orig_ret = fprintf(orig_stream, format, ##__VA_ARGS__); \
        fclose(orig_stream); \
        \
        /* Directly capture ft_printf output using pipe */ \
        int pipe_fd[2]; \
        if (pipe(pipe_fd) == -1) { \
            printf("Error: Failed to create pipe\n"); \
            exit(1); \
        } \
        \
        int saved_stdout = dup(STDOUT_FILENO); \
        dup2(pipe_fd[1], STDOUT_FILENO); \
        \
        /* Call ft_printf directly */ \
        ft_ret = ft_printf(format, ##__VA_ARGS__); \
        fflush(stdout); \
        \
        /* Restore stdout */ \
        dup2(saved_stdout, STDOUT_FILENO); \
        close(pipe_fd[1]); \
        \
        /* Read captured output from pipe */ \
        int bytes_read = read(pipe_fd[0], ft_buf, BUFFER_SIZE - 1); \
        if (bytes_read >= 0) \
            ft_buf[bytes_read] = '\0'; \
        close(pipe_fd[0]); \
        close(saved_stdout); \
        \
        /* Compare results */ \
        print_test_comparison(format, orig_ret, ft_ret, orig_buf, ft_buf); \
    } while (0)
#endif /* FT_PRINTF_TEST_MACROS_H */