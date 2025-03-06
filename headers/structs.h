/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 01:15:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 00:26:31 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#define BUFFER_SIZE 4096

typedef struct {
    int id;
    const char *name;
    const char *description;
    const char *executable;
    const char *arguments;
} Test;

typedef struct s_test_stats
{
    int passed;
    int failed;
    int total;
}	t_test_stats;


/* ===== TEST FRAMEWORK TYPES ===== */
typedef enum {
    BASIC_TEST,
    EDGE_CASE_TEST,
    STRESS_TEST,
    MEMORY_TEST,
    RANDOM_TEST,
    SECURITY_TEST
} test_type_t;

/* ===== PRINTF-SPECIFIC TEST TYPES ===== */
typedef enum e_printf_test_type {
    CHAR_TEST,
    STRING_TEST,
    INT_TEST,
    UINT_TEST,
    HEX_TEST,
    POINTER_TEST,
    PERCENT_TEST,
    MIXED_TEST,
    PRINTF_STRESS_TEST
} printf_test_type_t;

typedef enum {
    TEST_RUNNING,
    TEST_PASSED,
    TEST_FAILED,
    TEST_TIMEOUT,
    TEST_CRASH,
    TEST_LEAK
} test_status_t;

typedef struct {
    const char *name;
    const char *description;
    test_type_t type;
    test_status_t status;
    char *error_message;
    int expected_return;
    int actual_return;
    double execution_time;
    size_t memory_used;
    void (*func)(void *);
    void *data;
} test_case_t;

typedef struct {
    int total;
    int passed;
    int failed;
    int crashes;
    int leaks;
    int timeouts;
    double total_time;
    size_t total_memory;
} test_stats_t;

typedef struct {
    const char *name;
    const char *description;
    test_case_t *tests;
    int test_count;
    test_stats_t stats;
} test_suite_t;

/* Types of arguments that can be passed to printf */
typedef enum e_arg_type {
    ARG_CHAR,
    ARG_STRING,
    ARG_INT,
    ARG_UINT,
    ARG_HEX,
    ARG_POINTER,
    ARG_PERCENT
} t_arg_type;

/* Structure for mixed format testing */
typedef struct s_mixed_test_args {
    int int_args[10];
    unsigned int uint_args[10];
    char char_args[10];
    char *str_args[10];
    void *ptr_args[10];
    char arg_types[10];
    int arg_count;
} t_mixed_test_args;

#endif