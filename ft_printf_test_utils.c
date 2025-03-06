/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_test_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:08 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 17:08:05 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Define this macro to inform included files that they are being included */
#define INCLUDED_IN_MAIN_FILE 1
#include "headers/controller.h"

/* Global variables needed by test functions */
int test_count = 0;
int pass_count = 0;
int fail_count = 0;
static int g_total_tests = 0;
static int g_failed_tests = 0;

int ft_printf(const char *format, ...);

/* Include all the source files that were split out */
#include "src/ft_printf_output_format.c"
#include "src/ft_printf_test_runner.c"
#include "src/ft_printf_capture.c"
#include "src/ft_printf_str_char_tests.c"
#include "src/ft_printf_num_tests.c"
#include "src/ft_printf_ptr_tests.c"
#include "src/ft_printf_general_tests.c"
/* Removed ft_printf_stress_tester.c include as it's compiled separately */