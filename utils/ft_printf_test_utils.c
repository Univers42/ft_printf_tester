/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_test_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:08 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/23 15:29:33 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Define this macro to inform included files that they are being included */
#define INCLUDED_IN_MAIN_FILE 1
#include "../../headers/controller.h"

/* Reference external global variables - don't define them here */
extern int test_count;
extern int pass_count;
extern int fail_count;
extern int g_total_tests;
extern int g_failed_tests;

int ft_printf(const char *format, ...);

/* IMPORTANT: Remove the direct includes of source files that are already
   compiled separately into the library */
// DO NOT include these files - they're already being compiled separately
#include "ft_printf_output_format.c"
#include "ft_printf_test_runner.c"
#include "ft_printf_capture.c"
#include "ft_printf_str_char_tests.c"
#include "ft_printf_num_tests.c"
#include "ft_printf_ptr_tests.c"
#include "ft_printf_general_tests.c"