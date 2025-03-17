/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_test_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:08 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/17 19:25:41 by dyl-syzygy       ###   ########.fr       */
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
// #include "../../utils/ft_printf_output_format.c"
// #include "../../utils/ft_printf_test_runner.c"
// #include "../../utils/ft_printf_capture.c"
// #include "../../utils/ft_printf_str_char_tests.c"
// #include "../../utils/ft_printf_num_tests.c"
// #include "../../utils/ft_printf_ptr_tests.c"
// #include "../../utils/ft_printf_general_tests.c"