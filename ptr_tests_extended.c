/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_tests_extended.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:18:04 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/05 14:09:21 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_test_utils.h"

int main(void) {
    void *ptrs[10];
    for (int i = 0; i < 10; i++)
    ptrs[i] = &ptrs[i];
    void *null_ptr = NULL;
    void *zero_ptr = (void *)0;
    void *max_ptr = (void *)ULONG_MAX;
    void *func_ptr = (void *)&printf;
    
    printf("%s=== FT_PRINTF EXTENDED POINTER TESTS ===%s\n", MAGENTA, RESET);
    run_category("Basic Pointer Tests");
    test_pointer(ptrs[0], "%p", "Pointer to stack");
    test_pointer(null_ptr, "%p", "NULL pointer");
    test_pointer(zero_ptr, "%p", "Zero address pointer");
    test_pointer(max_ptr, "%p", "Maximum address pointer");
    test_pointer(func_ptr, "%p", "Function pointer");
    run_category("Width Tests");
    test_pointer(ptrs[0], "%20p", "Width 20 (right-aligned)");
    test_pointer(null_ptr, "%20p", "NULL with width 20");
    test_pointer(ptrs[0], "%-20p", "Width 20 (left-aligned)");
    test_pointer(null_ptr, "%-20p", "NULL with width 20 (left-aligned)");
    test_pointer(ptrs[0], "%1p", "Width smaller than pointer representation");
    test_pointer(ptrs[0], "%50p", "Large width");
    run_category("Precision Tests (should be ignored)");
    test_pointer(ptrs[0], "%.p", "Dot precision");
    test_pointer(null_ptr, "%.p", "NULL with dot precision");
    test_pointer(ptrs[0], "%.0p", "Zero precision");
    test_pointer(ptrs[0], "%.20p", "Large precision");
    test_pointer(ptrs[0], "%20.10p", "Width and precision");
    test_pointer(ptrs[0], "%-20.10p", "Left-alignment with precision");
    run_category("Flag Tests");
    test_pointer_with_flags(ptrs[0], "%+p", "Plus flag (platform-dependent)");
    test_pointer_with_flags(null_ptr, "%+p", "NULL with plus flag");
    test_pointer_with_flags(ptrs[0], "% p", "Space flag (platform-dependent)");
    test_pointer_with_flags(ptrs[0], "%#p", "Hash flag (may be redundant)");
    test_pointer_with_flags(ptrs[0], "%0p", "Zero flag without width");
    test_pointer_with_flags(ptrs[0], "%020p", "Zero padding with width");
    test_pointer_with_flags(ptrs[0], "%-020p", "Left-justify with zero padding");
    run_category("Context Tests");
    test_pointer(ptrs[0], "Pointer value: %p", "Text before");
    test_pointer(ptrs[0], "%p is a pointer", "Text after");
    test_pointer(ptrs[0], "The pointer %p is on the stack", "Text before and after");
    test_multiple_pointers("%p vs %p", "Multiple pointers in format", ptrs[0], ptrs[1]);
    run_category("Stress Tests");
    test_pointer(ptrs[0], "%100p", "Very large width");
    test_pointer(ptrs[0], "%-100p", "Very large left-aligned width");
    test_pointer(ptrs[0], "%0100p", "Very large zero-padded width");
    test_pointer(max_ptr, "%p", "ULONG_MAX pointer");
    test_pointer_with_flags(ptrs[0], "%+#-020.10p", "All flags combined");
    test_multiple_pointers("Multiple: %p %p %p %p %p", "Multiple pointers", 
                         ptrs[0], ptrs[1], ptrs[2], ptrs[3], ptrs[4]);
    run_category("Edge Cases");
    printf("Comparing NULL (0x0) pointers:\n");
    test_pointer(NULL, "%p", "NULL literal");
    test_pointer(null_ptr, "%p", "NULL pointer variable");
    test_pointer((void*)0, "%p", "Explicit (void*)0");
    test_pointer((void*)0xdeadbeef, "%p", "Hex constant cast to pointer");
    test_pointer((void*)0x0, "%p", "Zero hex cast to pointer");
    test_pointer((void*)&test_count, "%p", "Address of global variable");
    print_summary();
    return (fail_count > 0 ? 1 : 0);
}
