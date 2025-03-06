/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debug_tester_simple.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:31 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 15:22:27 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "headers/controller.h"

void run_simple_tests(void) {
    run_test("Simple character", "%c", 'A');
    run_test("Simple string", "%s", "Hello, world!");
    run_test("Simple integer", "%d", 42);
    run_test("Simple negative integer", "%d", -42);
    run_test("Simple unsigned integer", "%u", 42);
    run_test("Simple hex (lowercase)", "%x", 42);
    run_test("Simple hex (uppercase)", "%X", 42);
    run_test("Simple pointer", "%p", &run_simple_tests);
    run_test("Simple percent", "%%");
}

int main(void) {
    printf("%s=== FT_PRINTF SIMPLE DEBUG TESTER ===%s\n", MAGENTA, RESET);
    run_simple_tests();
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
