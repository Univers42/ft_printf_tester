#ifndef FT_PRINTF_DEBUG_H
#define FT_PRINTF_DEBUG_H

#include <stdio.h>  // For stderr
#include <stdarg.h> // For va_list and related macros

// Debug levels
#define DEBUG_OFF    0  // No debugging
#define DEBUG_ERROR  1  // Only error messages
#define DEBUG_INFO   2  // Errors and info messages
#define DEBUG_TRACE  3  // Detailed function tracing

// Set the debug level here
#define DEBUG_LEVEL DEBUG_INFO

// Debug macros
#if DEBUG_LEVEL >= DEBUG_ERROR
  #define DEBUG_ERROR(fmt, ...) \
      fprintf(stderr, "ERROR: " fmt "\n", ##__VA_ARGS__)
#else
  #define DEBUG_ERROR(fmt, ...)
#endif

#if DEBUG_LEVEL >= DEBUG_INFO
  #define DEBUG_INFO(fmt, ...) \
      fprintf(stderr, "INFO: " fmt "\n", ##__VA_ARGS__)
#else
  #define DEBUG_INFO(fmt, ...)
#endif

#if DEBUG_LEVEL >= DEBUG_TRACE
  #define DEBUG_TRACE(fmt, ...) \
      fprintf(stderr, "TRACE: %s: " fmt "\n", __func__, ##__VA_ARGS__)
  #define DEBUG_ENTER() \
      fprintf(stderr, "ENTER: %s\n", __func__)
  #define DEBUG_EXIT() \
      fprintf(stderr, "EXIT: %s\n", __func__)
#else
  #define DEBUG_TRACE(fmt, ...)
  #define DEBUG_ENTER()
  #define DEBUG_EXIT()
#endif

// Function to dump format specifier for debugging
static void debug_dump_format_spec(t_format *fmt_spec) {
#if DEBUG_LEVEL >= DEBUG_INFO
    fprintf(stderr, "Format Spec:\n");
    fprintf(stderr, "  - left_justify: %d\n", fmt_spec->left_justify);
    fprintf(stderr, "  - show_sign: %d\n", fmt_spec->show_sign);
    fprintf(stderr, "  - space_or_sign: %d\n", fmt_spec->space_or_sign);
    fprintf(stderr, "  - zero_padding: %d\n", fmt_spec->zero_padding);
    fprintf(stderr, "  - hash_flag: %d\n", fmt_spec->hash_flag);
    fprintf(stderr, "  - width: %d\n", fmt_spec->width);
    fprintf(stderr, "  - precision: %d\n", fmt_spec->precision);
    fprintf(stderr, "  - specifier: %c\n", fmt_spec->specifier);
#endif
}

#endif // FT_PRINTF_DEBUG_H
