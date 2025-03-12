/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mandatory_test.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:30:42 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/12 23:40:52 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/controller.h"

int ft_printf(const char *format, ...);
void test_char_conversion(void)
{
    print_test_header("CHAR CONVERSION (%c)", CYAN);
    TEST("%c", 'a');
    TEST("%c", 'z');
    TEST("%c", '0');
    TEST("%c", '~');
    TEST("%c", ' ');
    TEST("%c", '\t');
    TEST("%c", '\n');
    TEST("%c", 127); 
    TEST("%c", 0); 
    TEST("Test with char: %c and %c", 'a', 'b');
    TEST("Test with %c %c %c", 'x', 'y', 'z');
    TEST("%c %c %c %c %c", '1', '2', '3', '4', '5');
    print_test_footer("CHAR CONVERSION", GREEN);
}

void test_string_conversion(void)
{
    char actual[BUFFER_SIZE];
    int actual_ret = 0, bytes_read = 0;
    FILE *fp;
    
    print_test_header("STRING CONVERSION (%s)", CYAN);
    TEST("%s", "Hello World");
    TEST("%s", "");
    TEST("%s", "0123456789");
    TEST("%s", "abcdefghijklmnopqrstuvwxyz");
    TEST("%s", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    TEST("%s", "!@#$%^&*()_+");
    TEST("%s", "Simple string");
    TEST("%s", "String with \t tab");
    TEST("%s", "String with\nnewline");
    printf("Test %s: ", "NULL string pointer");
    fp = tmpfile();
    if (fp) {
        int original_stdout = dup(1);
        if (dup2(fileno(fp), 1) != -1)
        {
            actual_ret = ft_printf("%s", NULL);
            fflush(stdout);
            dup2(original_stdout, 1);
            close(original_stdout);
            fseek(fp, 0, SEEK_SET);
            bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
            actual[bytes_read] = '\0';
            printf("%sHandling varies by system - accepting any valid output%s\n", 
                   YELLOW, RESET);
            printf("  Your ft_printf prints: \"%s\" for NULL strings (ret: %d)\n", 
                   actual, actual_ret);
        }
        fclose(fp);
    }
    TEST("Multiple: %s %s", "string1", "string2");
    TEST("Three strings: %s %s %s", "one", "two", "three");
    TEST("%s%s%s", "con", "cat", "enate");
    print_test_footer("STRING CONVERSION", GREEN);
}

void test_pointer_conversion(void)
{
    int num = 42;
    char c = 'a';
    void *ptr = &num;
    void *ptr2 = &c;
    void *null_ptr = NULL;
    
    print_test_header("POINTER CONVERSION (%p)", CYAN);
    TEST("%p", ptr);
    TEST("%p", ptr2);
    TEST("%p", null_ptr);
    TEST("%p", (void *)0x1);
    TEST("%p", (void *)0xffffffff);
    TEST("%p", (void *)0x7fffffffffff);
    TEST("%p", (void *)&test_pointer_conversion); 
    TEST("%p", (void *)INT_MAX);
    TEST("%p", (void *)LONG_MAX);
    TEST("Address: %p", ptr);
    TEST("Multiple: %p %p", ptr, ptr2);
    TEST("%p %p %p", ptr, ptr2, null_ptr);
    print_test_footer("POINTER CONVERSION", GREEN);
}

void test_integer_conversion(void)
{
    print_test_header("INTEGER CONVERSION (%d, %i)", CYAN);
    TEST("%d", 0);
    TEST("%i", 0);
    TEST("%d", 1);
    TEST("%i", -1);
    TEST("%d", 42);
    TEST("%i", -42);
    TEST("%d", INT_MAX);
    TEST("%i", INT_MIN);
    TEST("%d", 2147483647);
    TEST("%i", INT_MIN);
    TEST("%d", 9999);
    TEST("%i", -9999);
    TEST("Numbers: %d %i", 123, -456);
    TEST("%d %i %d %i", 11, 22, 33, 44);
    TEST("%i and %d", INT_MIN, INT_MAX);
    TEST("Mix: %d %i %d", 42, -42, 0);
    print_test_footer("INTEGER CONVERSION", GREEN);
}

void test_unsigned_conversion(void)
{
    print_test_header("UNSIGNED INTEGER CONVERSION (%u)", CYAN);
    TEST("%u", 0);
    TEST("%u", 1);
    TEST("%u", 42);
    TEST("%u", UINT_MAX);
    TEST("%u", 4294967295u);
    TEST("%u", 9999);
    TEST("%u", INT_MAX);
    TEST("%u", INT_MAX + 1U);
    TEST("Unsigned: %u %u", 123, 456);
    TEST("%u %u %u", 11, 22, 33);
    TEST("Mix: %u %u %u", 42, 0, UINT_MAX);
    TEST("%u and %u", 999999, 1000000);
    print_test_footer("UNSIGNED INTEGER CONVERSION", GREEN);
}

void test_hex_lowercase_conversion(void)
{
    print_test_header("HEXADECIMAL LOWERCASE CONVERSION (%x)", CYAN);
    TEST("%x", 0);
    TEST("%x", 1);
    TEST("%x", 10);
    TEST("%x", 16);
    TEST("%x", 42);
    TEST("%x", 255);
    TEST("%x", 4096);
    TEST("%x", 0xabcdef);
    TEST("%x", 0x123456);
    TEST("%x", INT_MAX);
    TEST("%x", UINT_MAX);
    TEST("Hex: %x %x", 0xabc, 0xdef);
    TEST("%x %x %x", 10, 100, 1000);
    TEST("Mix: %x %x %x", 0, 42, 0xffffffff);
    TEST("Complex: 0x%x and 0x%x", 0xabcdef, 0x123456);
    print_test_footer("HEXADECIMAL LOWERCASE CONVERSION", GREEN);
}

void test_hex_uppercase_conversion(void)
{
    print_test_header("HEXADECIMAL UPPERCASE CONVERSION (%X)", CYAN);
    TEST("%X", 0);
    TEST("%X", 1);
    TEST("%X", 10);
    TEST("%X", 16);
    TEST("%X", 42);
    TEST("%X", 255);
    TEST("%X", 4096);
    TEST("%X", 0xabcdef);
    TEST("%X", 0x123456);
    TEST("%X", INT_MAX);
    TEST("%X", UINT_MAX);
    TEST("HEX: %X %X", 0xabc, 0xdef);
    TEST("%X %X %X", 10, 100, 1000);
    TEST("Mix: %X %X %X", 0, 42, 0xffffffff);
    TEST("Complex: 0x%X and 0x%X", 0xabcdef, 0x123456);
    print_test_footer("HEXADECIMAL UPPERCASE CONVERSION", GREEN);
}

void test_percent_sign(void)
{
    print_test_header("PERCENT SIGN (%%)", CYAN);
    TEST("%%");
    TEST("100%%");
    TEST("%% Percent sign");
    TEST("Percent sign: %%");
    TEST("Multiple: %% and %%");
    TEST("Three: %% %% %%");
    TEST("Mixed %% with %d", 42);
    TEST("All together: %c %s %p %d %i %u %x %X %%", 'a', "string", (void *)0xabcdef, 42, -42, 42u, 0xabcdef, 0xABCDEF);
    print_test_footer("PERCENT SIGN", GREEN);
}

void test_mixed_conversions(void)
{
    print_test_header("MIXED CONVERSIONS (All Together)", MAGENTA);
    int i = 42;
    char *str = "string";
    void *ptr = &i;
    TEST("Char: %c, String: %s", 'A', "test");
    TEST("Decimal: %d, Hex: %x", 42, 42);
    TEST("Pointer: %p, Unsigned: %u", ptr, 42);
    TEST("Lowercase hex: %x, Uppercase: %X", 0xabcdef, 0xabcdef);
    TEST("Percent: %%, Char: %c", 'Z');
    TEST("Complex: %c %s %p %d %i %u %x %X %%", 'Z', "test", ptr, 42, -42, 42, 0xabcdef, 0xABCDEF);
    TEST("%s has %d %c's and %p is its address", "test", 4, 't', str);
    TEST("Hex: 0x%x or 0x%X, Pointer: %p", 0xabcdef, 0xABCDEF, ptr);
    TEST("Int: %i, Unsigned: %u, Percent: %%", -42, 42);
    TEST("Extreme: %c %s %p %d %i %u %x %X", 0, "", NULL, INT_MIN, INT_MAX, UINT_MAX, 0, 0xffffffff);
    TEST("Empty string: '%s', Null char: '%c'", "", 0);
    print_test_footer("MIXED CONVERSIONS", MAGENTA);
}

void test_consecutive_conversions(void)
{
    print_test_header("CONSECUTIVE CONVERSIONS", YELLOW);
    TEST("%d%d%d", 1, 2, 3);
    TEST("%s%s%s", "one", "two", "three");
    TEST("%c%c%c%c", 'a', 'b', 'c', 'd');
    TEST("%x%X%x%X", 10, 11, 12, 13);
    TEST("%p%p", (void*)0x123, (void*)0x456);
    TEST("%u%u%u", 10, 100, 1000);
    TEST("%c%s%d%i%u%x%X%p%%", 'a', "string", 42, -42, 100, 0xabc, 0xDEF, (void*)0x123);
    print_test_footer("CONSECUTIVE CONVERSIONS", YELLOW);
}

void test_edge_cases(void)
{
    char actual[BUFFER_SIZE];
    int actual_ret = 0;
    FILE *fp = tmpfile();
    int bytes_read;
    print_test_header("EDGE CASES", RED);
    TEST(" ");
    TEST("No conversions here");
    printf("Test %s: ", "NULL string pointer (edge case)");    
    if (fp)
    {
        int original_stdout = dup(1);
        if (dup2(fileno(fp), 1) != -1)
        {
            actual_ret = ft_printf("%s", NULL);
            fflush(stdout);
            dup2(original_stdout, 1);
            close(original_stdout);
            fseek(fp, 0, SEEK_SET);
            bytes_read = fread(actual, 1, BUFFER_SIZE - 1, fp);
            actual[bytes_read] = '\0';
            printf("%sHandling varies by system - accepting any valid output%s\n", 
                   YELLOW, RESET);
            printf("  Your ft_printf prints: \"%s\" for NULL strings (ret: %d)\n", 
                   actual, actual_ret);
        }
        fclose(fp);
    }
    TEST("%d", INT_MAX);
    TEST("%d", INT_MIN);
    TEST("%i", INT_MAX);
    TEST("%i", INT_MIN);
    TEST("%u", UINT_MAX);
    TEST("%x", UINT_MAX);
    TEST("%X", UINT_MAX);
    TEST("%d", 0);
    TEST("%c", 0);  
    TEST("%p", NULL);
    TEST("%x", 0);
    TEST("%X", 0);
    TEST("%s %s %s %s %s %s %s %s %s %s", 
         "string1", "string2", "string3", "string4", "string5",
         "string6", "string7", "string8", "string9", "string10");
    TEST("%%%%%%%%%%");   
    print_test_footer("EDGE CASES", RED);
}

int main(void)
{
    int total_tests = 0, failed_tests = 0;
    float success_rate;
    
    printf(BOLD MAGENTA);
    printf("\n");
    printf(" ███████╗████████╗    ██████╗ ██████╗ ██╗███╗   ██╗████████╗███████╗\n");
    printf(" ██╔════╝╚══██╔══╝    ██╔══██╗██╔══██╗██║████╗  ██║╚══██╔══╝██╔════╝\n");
    printf(" █████╗     ██║       ██████╔╝██████╔╝██║██╔██╗ ██║   ██║   █████╗  \n");
    printf(" ██╔══╝     ██║       ██╔═══╝ ██╔══██╗██║██║╚██╗██║   ██║   ██╔══╝  \n");
    printf(" ██║        ██║       ██║     ██║  ██║██║██║ ╚████║   ██║   ██║     \n");
    printf(" ╚═╝        ╚═╝       ╚═╝     ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝     \n");
    printf("\n");
    printf("                    MANDATORY PART TESTER\n");
    printf(RESET "\n");
    printf(BOLD BLUE "=== TESTING ALL MANDATORY CONVERSIONS ===\n\n" RESET);
    initialize_test_counters();
    test_char_conversion();
    test_string_conversion();
    test_pointer_conversion();
    test_integer_conversion();
    test_unsigned_conversion();
    test_hex_lowercase_conversion();
    test_hex_uppercase_conversion();
    test_percent_sign();
    test_mixed_conversions();
    test_consecutive_conversions();
    test_edge_cases();
    get_test_results(&total_tests, &failed_tests);
    printf("\n");
    printf(BOLD "=== TEST RESULTS ===\n" RESET);
    printf("Total Tests: %d\n", total_tests);
    printf("Passed: " GREEN "%d" RESET "\n", total_tests - failed_tests);
    printf("Failed: " RED "%d" RESET "\n", failed_tests);    
    success_rate = (float)(total_tests - failed_tests) / total_tests * 100;
    printf("Success Rate: ");
    printf("[");
    for (int i = 0; i < 50; i++)
    {
        if (i < (int)(success_rate / 2))
            printf(GREEN "█" RESET);
        else
            printf(RED "░" RESET);
    }
    printf("] %.1f%%\n", success_rate);
    printf("\n");
    if (failed_tests == 0)
        printf(GREEN BOLD "ALL MANDATORY TESTS PASSED! CONGRATULATIONS!\n" RESET);
    else
        printf(YELLOW BOLD "SOME TESTS FAILED. CHECK THE OUTPUT ABOVE FOR DETAILS.\n" RESET);
    return (failed_tests > 0);
}
