#ifndef FT_PRINTF_TEST_GLOBALS_H
#define FT_PRINTF_TEST_GLOBALS_H

/* Global test counters used across multiple test files */
extern int test_count;     /* Total number of tests run */
extern int pass_count;     /* Number of tests that passed */
extern int fail_count;     /* Number of tests that failed */

/* Global test statistics for unified reporting */
extern int g_total_tests;  /* Grand total of tests across all test files */
extern int g_failed_tests; /* Grand total of failed tests */

/* Initialize the test counters */
void init_globals(void);

#endif /* FT_PRINTF_TEST_GLOBALS_H */
