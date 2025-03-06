#ifndef FT_STRUCTS_H
#define FT_STRUCTS_H

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
typedef enum {
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

#endif