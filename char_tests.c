/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:19 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:16:20 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../ft_printf.h"
#include "ft_printf_test_utils.h"  // Include the utilities header

int main(void)
{
    printf("=== FT_PRINTF CHAR TESTS ===\n\n");
    
    printf("\n=== Basic character test ===\n");
    test_char('A', "%c", "Basic character");
    test_char('0', "%c", "Digit character");
    test_char(' ', "%c", "Space character");
    
    printf("\n=== Width test ===\n");
    test_char('A', "%5c", "Character with width 5");
    test_char('B', "%-5c", "Left-justified character with width 5");
    
    printf("\n=== Flag test ===\n");
    test_char('Z', "%05c", "Character with zero padding");
    
    printf("\n=== Multiple Characters Test ===\n");
    run_test("Multiple characters in context", "Test: %c and %c", 'X', 'Y');
    
    printf("\n=== CHAR TESTS COMPLETED ===\n");
    return 0;
}
