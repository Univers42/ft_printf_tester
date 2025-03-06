/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debug.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:22:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 16:06:41 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_DEBUG_H
# define FT_PRINTF_DEBUG_H

# include "ft_printf_test_utils.h"

/* Test buffer size for output comparison - globally accessible */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# define RANDOM_TEXT_LENGTH 1000
# define RANDOM_STR_MAX 100
# define RANDOM_TEST_MAX_LENGTH 1000
# define RANDOM_INT_MAX 1000
# define RANDOM_INT_MIN -1000
# define R_SIZE 1000

/* Global test counters - extern so they can be defined elsewhere */
extern int test_count;
extern int pass_count;
extern int fail_count;


/* Debug level definitions */
# define DEBUG_NONE   0  
# define DEBUG_ERROR  1  
# define DEBUG_INFO   2  
# define DEBUG_TRACE  3  

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

/* Debug function prototypes */
void debug_print_char(char c);
void debug_print_string(const char *str);
void debug_print_pointer(void *ptr);
void debug_print_int(int num);
void debug_print_uint(unsigned int num);
void debug_print_hex(unsigned int num, int uppercase);
void debug_print_format_specifier(const char *format);

#endif /* FT_PRINTF_DEBUG_H */
