/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debug.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:55 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:16:57 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_DEBUG_H
# define FT_PRINTF_DEBUG_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
/* Test buffer size for output comparison - globally accessible */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# define RANDOM_TEXT_LENGTH 1000
# define RANDOM_STR_MAX 100
# define RANDOM_TEST_MAX_LENGTH 1000
# define RANDOM_INT_MAX 1000
# define RANDOM_INT_MIN -1000
/* Color codes for test output - globally accessible */
# ifndef RED
#  define RED     "\033[0;31m"
#  define GREEN   "\033[0;32m"
#  define YELLOW  "\033[0;33m"
#  define BLUE    "\033[0;34m"
#  define PURPLE  "\033[0;35m"
#  define MAGENTA "\033[0;35m"
#  define CYAN    "\033[0;36m"
#  define RESET   "\033[0m"
#  define BOLD     "\033[1m"
#  define WHITE    "\033[0;37m"
#  define BG_RED   "\033[41m"
#  define BG_GREEN "\033[42m"
#  define BG_BLUE  "\033[44m"
#  define BG_CYAN  "\033[46m"
#  define BG_WHITE "\033[47m"
# endif

/* Global test counters - extern so they can be defined elsewhere */
extern int test_count;
extern int pass_count;
extern int fail_count;


/* Debug level definitions */
# define DEBUG_NONE   0  // No debug output
# define DEBUG_ERROR  1  // Only error messages
# define DEBUG_INFO   2  // Errors and info messages
# define DEBUG_TRACE  3  // Detailed function tracing

/* Set current debug level */
# ifndef DEBUG_LEVEL
#  define DEBUG_LEVEL DEBUG_NONE
# endif

/* Debug message macros */
# if DEBUG_LEVEL >= DEBUG_ERROR
#  define DEBUG_ERROR_MSG(fmt, ...) \
    fprintf(stderr, RED "[ERROR] " fmt RESET "\n", ##__VA_ARGS__)
# else
#  define DEBUG_ERROR_MSG(fmt, ...)
# endif

# if DEBUG_LEVEL >= DEBUG_INFO
#  define DEBUG_INFO_MSG(fmt, ...) \
    fprintf(stderr, BLUE "[INFO] " fmt RESET "\n", ##__VA_ARGS__)
# else
#  define DEBUG_INFO_MSG(fmt, ...)
# endif

# if DEBUG_LEVEL >= DEBUG_TRACE
#  define DEBUG_TRACE_MSG(fmt, ...) \
    fprintf(stderr, CYAN "[TRACE] %s:%d:%s() " fmt RESET "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__)
# else
#  define DEBUG_TRACE_MSG(fmt, ...)
# endif

/* Utility functions for testing */
void print_test_result(const char *test_name, int pass, const char *format, 
                      const char *expected, int expected_ret, 
                      const char *actual, int actual_ret);

#endif /* FT_PRINTF_DEBUG_H */
