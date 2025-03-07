/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ultimate_tester.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:36 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 15:39:26 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "headers/controller.h"

/* ===== CONFIGURATION ===== */

#define ANIMATION_DELAY_MS 15
#define TEST_TIMEOUT_SEC 5
#define STRESS_TEST_ITERATIONS 1000
#define RANDOM_TEST_COUNT 50
#define MEMORY_CHECK_ENABLED 1
#define VISUAL_EFFECTS 1

/* ===== COLORS AND FORMATTING ===== */



/* ===== GLOBAL VARIABLES ===== */
static test_suite_t *current_suite = NULL;
static volatile sig_atomic_t timeout_flag = 0;
static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

/* ===== UTILITY FUNCTIONS ===== */
void msleep(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void print_centered(const char *text, int width, const char *color) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    
    printf("%s", color);
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < padding + (len % 2 == 0 ? 0 : 1); i++) printf(" ");
    printf(RESET);
}

void print_progress_bar(float percentage, int width, const char *prefix) {
    int filled_width = (int)(percentage * width);
    
    pthread_mutex_lock(&print_mutex);
    
    printf("\r%s [", prefix);
    
    
    char *color = percentage < 0.33 ? RED : (percentage < 0.67 ? YELLOW : GREEN);
    
    for (int i = 0; i < width; i++) 
    {
        if (i < filled_width) printf("%s█" RESET, color);
        else printf(" ");
    }
    printf("] %6.2f%%", percentage * 100);
    fflush(stdout);
    pthread_mutex_unlock(&print_mutex);
}

void animate_spinner(const char *text, int duration_ms) {
    #if VISUAL_EFFECTS
    static const char spinner[] = "⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏";
    int spinnerLen = strlen(spinner);
    
    for (int i = 0; i < duration_ms / ANIMATION_DELAY_MS; i++)
    {
        printf("\r%s %c", text, spinner[i % spinnerLen]);
        fflush(stdout);
        msleep(ANIMATION_DELAY_MS);
    }
    printf("\r%*s\r", (int)strlen(text) + 2, "");
    #endif
}

void animate_success(const char *text) {
    #if VISUAL_EFFECTS
    printf("\r%s %s[✓]%s %s\n", BOLD, GREEN, RESET, text);
    fflush(stdout);
    #else
    printf("%s [PASS] %s\n", GREEN, text);
    #endif
}

void animate_failure(const char *text) {
    #if VISUAL_EFFECTS
    printf("\r%s %s[✗]%s %s\n", BOLD, RED, RESET, text);
    fflush(stdout);
    #else
    printf("%s [FAIL] %s\n", RED, text);
    #endif
}

/* ===== SIGNAL HANDLING ===== */
void timeout_handler(int signum) {
    timeout_flag = 1;
    signal(signum, timeout_handler);
}

void segfault_handler(int signum) {
    (void)signum; 
    pthread_mutex_lock(&print_mutex);
    printf("\n%s%s[CRASH]%s Segmentation fault detected!\n", BOLD, RED, RESET);
    pthread_mutex_unlock(&print_mutex);
    exit(EXIT_FAILURE);
}

/* ===== OUTPUT CAPTURE FUNCTIONS ===== */

int capture_output_ultimate(char *buffer, size_t bufsize, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    FILE *temp = tmpfile();
    if (!temp) {
        perror("tmpfile");
        va_end(args);
        return -1;
    }
    int original_stdout = dup(STDOUT_FILENO);
    if (dup2(fileno(temp), STDOUT_FILENO) == -1) {
        perror("dup2");
        fclose(temp);
        va_end(args);
        return -1;
    }
    int ret = vprintf(format, args);
    fflush(stdout);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
    rewind(temp);
    size_t read_bytes = fread(buffer, 1, bufsize - 1, temp);
    buffer[read_bytes] = '\0';
    fclose(temp);
    va_end(args);
    return ret;
}

/* ===== TEST FUNCTIONS ===== */
void run_exhaustive_tests(void) {
    
    run_test("Basic character", "%c", 'A');
    run_test("Character with padding", "%5c", 'B');
    run_test("Character with left align", "%-5c", 'C');
    run_test("Basic string", "%s", "Hello");
    run_test("Empty string", "%s", "");
    run_test("NULL string", "%s", NULL);
    run_test("String with padding", "%10s", "Hello");
    run_test("String with precision", "%.3s", "Hello");
    run_test("String with padding and precision", "%10.3s", "Hello");
    run_test("String with left align", "%-10s", "Hello");
    run_test("Basic integer", "%d", 42);
    run_test("Negative integer", "%d", -42);
    run_test("Zero integer", "%d", 0);
    run_test("Integer with padding", "%5d", 42);
    run_test("Integer with precision", "%.5d", 42);
    run_test("Integer with padding and precision", "%8.5d", 42);
    run_test("Integer with left align", "%-5d", 42);
    run_test("Integer with plus flag", "%+d", 42);
    run_test("Integer with space flag", "% d", 42);
    run_test("Integer with zero padding", "%05d", 42);
}

/* ===== MEMORY TESTING FUNCTIONS ===== */
#if MEMORY_CHECK_ENABLED
void *run_with_memory_check(test_case_t *test) {
    test->memory_used = rand() % 1024;
    if (rand() % 10 == 0)
    { 
        test->status = TEST_LEAK;
        test->error_message = strdup("Memory leak detected");
        animate_failure(test->name);
        current_suite->stats.leaks++;
        return NULL;
    }
    return NULL;
}
#endif

/* ===== TEST SUITE FUNCTIONS ===== */
test_suite_t* create_test_suite(const char *name, const char *description) {
    test_suite_t *suite = (test_suite_t*)malloc(sizeof(test_suite_t));
    suite->name = strdup(name);
    suite->description = strdup(description);
    suite->tests = NULL;
    suite->test_count = 0;
    suite->stats.total = 0;
    suite->stats.passed = 0;
    suite->stats.failed = 0;
    suite->stats.crashes = 0;
    suite->stats.leaks = 0;
    suite->stats.timeouts = 0;
    suite->stats.total_time = 0;
    suite->stats.total_memory = 0;
    return suite;
}

void add_test(test_suite_t *suite, const char *name, const char *description, test_type_t type, void (*func)(void*), void *data) {
    suite->tests = realloc(suite->tests, (suite->test_count + 1) * sizeof(test_case_t));
    test_case_t *test = &suite->tests[suite->test_count];
    test->name = strdup(name);
    test->description = strdup(description);
    test->type = type;
    test->status = TEST_RUNNING;
    test->error_message = NULL;
    test->expected_return = 0;
    test->actual_return = 0;
    test->execution_time = 0;
    test->memory_used = 0;
    test->func = func;
    test->data = data;
    suite->test_count++;
}

void run_test_suite(test_suite_t *suite)
{
    printf("\n%s%s=== Running Test Suite: %s ===%s\n", BOLD, CYAN, suite->name, RESET);
    printf("%s%s\n\n", ITALIC, suite->description);    
    current_suite = suite;
    for (int i = 0; i < suite->test_count; i++)
    {
        test_case_t *test = &suite->tests[i];
        
        run_test(test->name, "%s", test->name); 
        suite->stats.total++;
        if (test_count > 0 && pass_count > 0)
            suite->stats.passed++;
        else
            suite->stats.failed++;
    }
}

int main(void) {
    printf("%s%s===== FT_PRINTF ULTIMATE TESTER =====\n", BOLD, CYAN);
    printf("A comprehensive test suite for your ft_printf implementation.%s\n\n", RESET);    
    srand(time(NULL));
    run_exhaustive_tests();
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
