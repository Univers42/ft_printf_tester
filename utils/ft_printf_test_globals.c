#include "ft_printf_test_globals.h"

/* Global test counters used across multiple test files */
int test_count = 0;     /* Total number of tests run */
int pass_count = 0;     /* Number of tests that passed */
int fail_count = 0;     /* Number of tests that failed */

/* Global test statistics for unified reporting */
int g_total_tests = 0;  /* Grand total of tests across all test files */
int g_failed_tests = 0; /* Grand total of failed tests */

/* Initialize the test counters */
void init_globals(void)
{
    test_count = 0;
    pass_count = 0;
    fail_count = 0;
    g_total_tests = 0;
    g_failed_tests = 0;
}
