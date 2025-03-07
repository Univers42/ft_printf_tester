/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:20:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 01:49:24 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDED_IN_MAIN_FILE
# include "../headers/controller.h"
#endif

/* These variables are declared in ft_printf_test_utils.c */
#ifndef INCLUDED_IN_MAIN_FILE
extern int test_count;
extern int pass_count;
extern int fail_count;
extern int g_total_tests;
extern int g_failed_tests;
#endif

void	run_category(const char *category)
{
	printf("\n%s=== %s ===%s\n", BLUE, category, RESET);
}

void	print_summary(void)
{
	printf("\n%s=== TEST SUMMARY ===%s\n", BLUE, RESET);
	printf("Total tests: %d\n", test_count);
	printf("Passed: %s%d (%.1f%%)%s\n", GREEN, pass_count,
		(float)pass_count / test_count * 100, RESET);
	printf("Failed: %s%d (%.1f%%)%s\n",
		fail_count > 0 ? RED : GREEN, fail_count,
		(float)fail_count / test_count * 100, RESET);
}

void	compare_and_print_results(const char *expected, int expected_ret,
		const char *actual, int actual_ret, 
		const char *format, const char *test_name)
{
	test_count++;
	if (strcmp(expected, actual) == 0 && expected_ret == actual_ret)
	{
		printf("%s[PASS]%s %s\n", GREEN, RESET, test_name);
		pass_count++;
	}
	else
	{
		printf("%s[FAIL]%s %s\n", RED, RESET, test_name);
		printf("  Format:    \"%s\"\n", format);
		printf("  Expected:  ");
		print_formatted_string(expected, expected_ret);
		printf("\n  Actual:    ");
		print_formatted_string(actual, actual_ret);
		printf("\n");
		fail_count++;
	}
}

void	print_test_comparison(const char *format, int orig_ret, int ft_ret,
		char *orig_out, char *ft_out)
{
	int	strings_match;
	int	return_match;
	int	test_passed;

	g_total_tests++;
	strings_match = (strcmp(orig_out, ft_out) == 0);
	return_match = (orig_ret == ft_ret);
	test_passed = strings_match && return_match;
	if (VERBOSE || !test_passed)
	{
		printf("Test %d: ", g_total_tests);
		printf(BOLD "\"" RESET "%s" BOLD "\"" RESET "\n", format);
		if (!strings_match)
		{
			printf("  %sOutput mismatch:%s\n", RED, RESET);
			printf("    Expected: \"%s\"\n", orig_out);
			printf("    Got:      \"%s\"\n", ft_out);
		}
		if (!return_match)
		{
			printf("  %sReturn value mismatch:%s\n", RED, RESET);
			printf("    Expected: %d\n", orig_ret);
			printf("    Got:      %d\n", ft_ret);
		}
		if (test_passed)
			printf("  %s✓ Test passed%s\n\n", GREEN, RESET);
		else
			printf("  %s✗ Test failed%s\n\n", RED, RESET);
	}
	else
	{
		printf("Test %d: %s%s%s\n", g_total_tests,
			test_passed ? GREEN : RED,
			test_passed ? "✓" : "✗", 
			RESET);
	}
	if (!test_passed)
		g_failed_tests++;
}

void	initialize_test_counters(void)
{
	g_total_tests = 0;
	g_failed_tests = 0;
	test_count = 0;
	pass_count = 0;
	fail_count = 0;
}

void	get_test_results(int *total, int *failed)
{
	*total = g_total_tests;
	*failed = g_failed_tests;
}

/* Handle multiple specifiers test carefully to avoid segmentation fault */
void test_multiple_specifiers(void)
{
    char expected[BUFFER_SIZE];
    char actual[BUFFER_SIZE];
    int expected_ret, actual_ret;
    int pipe_fd[2];
    char c = 'A';
    char *s = "test";
    int d = 42;
    unsigned int x = 0xabc;
    void *p = (void*)0x1234;

    printf("[TEST] Multiple specifiers\n");
    printf("  Format:    \"%%c %%s %%d %%x %%p %%%%\"\n");
    
    // Get expected output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        expected_ret = printf("%c %s %d %x %p %%", c, s, d, x, p);
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], expected, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            expected[bytes_read] = '\0';
        close(pipe_fd[0]);
    } else {
        strcpy(expected, "PIPE_ERROR");
        expected_ret = -1;
    }
    
    // Get ft_printf output
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        // Pass each argument individually to avoid va_list issues
        actual_ret = ft_printf("%c %s %d %x %p %%", c, s, d, x, p);
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], actual, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            actual[bytes_read] = '\0';
        close(pipe_fd[0]);
    } else {
        strcpy(actual, "PIPE_ERROR");
        actual_ret = -1;
    }
    
    compare_and_print_results(expected, expected_ret, actual, actual_ret, "%c %s %d %x %p %%", "Multiple specifiers");
}

// In the main function or wherever the test is called:
void run_edge_case_tests(void)
{
    /* ...existing code... */
    
    // Replace the problematic test with our safer version
    test_multiple_specifiers(); // Instead of the test that causes segfault
    
    /* ...existing code... */
}