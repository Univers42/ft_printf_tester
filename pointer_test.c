/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:18:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:18:01 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"  // Include utilities header

// Remove the duplicate implementation of test_pointer_with_flags
// Since we're now using the implementation from ft_printf_test_utils.c

int main(void) {
    printf("\n%s=== FT_PRINTF POINTER TESTS ===%s\n\n", MAGENTA, RESET);
    
    void *p1 = (void *)0x12345678;
    void *p2 = (void *)0xdeadbeef;
    void *p3 = (void *)0x0;
    void *p4 = NULL;
    void *p5 = &p1;  // pointer to a pointer
    
    run_category("Basic Pointer Tests");
    test_pointer(p1, "%p", "Regular pointer");
    test_pointer(p2, "%p", "Pointer with hex chars");
    test_pointer(p3, "%p", "Zero pointer");
    test_pointer(p4, "%p", "NULL pointer");
    test_pointer(p5, "%p", "Pointer to pointer");
    test_pointer(&main, "%p", "Function pointer");
    
    run_category("Width Tests");
    test_pointer(p1, "%20p", "Width 20");
    test_pointer(p2, "%30p", "Width 30");
    test_pointer(p4, "%15p", "NULL with width 15");
    
    run_category("Left-justify Tests");
    test_pointer(p1, "%-20p", "Left-justified width 20");
    test_pointer(p2, "%-30p", "Left-justified width 30");
    test_pointer(p4, "%-15p", "NULL left-justified width 15");
    
    run_category("Context Tests");
    test_pointer(p1, "Pointer: %p", "With text");
    test_pointer(p2, "%p is a pointer", "Text after");
    test_pointer(p3, "Before %p after", "Text before and after");
    
    run_category("Flag Combination Tests");
    // Use the helper function from ft_printf_test_utils.c
    test_pointer_with_flags(p1, "%+p", "Plus flag (platform-dependent)");
    test_pointer_with_flags(p2, "% p", "Space flag (platform-dependent)");
    test_pointer_with_flags(p3, "%#p", "Hash flag (may be redundant)");
    test_pointer_with_flags(p4, "%0p", "Zero flag without width");
    test_pointer_with_flags(p5, "%020p", "Zero padding with width");
    test_pointer_with_flags(&main, "%-020p", "Left-justify overrides zero padding");
    
    // Print summary
    print_summary();
    
    return fail_count > 0 ? 1 : 0;
}
