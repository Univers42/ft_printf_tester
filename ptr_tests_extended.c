/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_tests_extended.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:18:04 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:18:05 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include "ft_printf_test_utils.h"

int main(void) {
    printf("%s=== FT_PRINTF EXTENDED POINTER TESTS ===%s\n", MAGENTA, RESET);
    
    // Create an array of test pointers
    void *ptrs[10];
    for (int i = 0; i < 10; i++) {
        ptrs[i] = &ptrs[i]; // Pointers to themselves
    }
    
    // Special pointers to test
    void *null_ptr = NULL;
    void *zero_ptr = (void *)0;
    void *max_ptr = (void *)ULONG_MAX;
    void *func_ptr = (void *)&printf;
    
    // BASIC POINTER TESTS
    run_category("Basic Pointer Tests");
    
    // Test different pointers
    test_pointer(ptrs[0], "%p", "Pointer to stack");
    test_pointer(null_ptr, "%p", "NULL pointer");
    test_pointer(zero_ptr, "%p", "Zero address pointer");
    test_pointer(max_ptr, "%p", "Maximum address pointer");
    test_pointer(func_ptr, "%p", "Function pointer");
    
    // Width tests
    run_category("Width Tests");
    
    // Test width formatting with different alignments
    test_pointer(ptrs[0], "%20p", "Width 20 (right-aligned)");
    test_pointer(null_ptr, "%20p", "NULL with width 20");
    test_pointer(ptrs[0], "%-20p", "Width 20 (left-aligned)");
    test_pointer(null_ptr, "%-20p", "NULL with width 20 (left-aligned)");
    test_pointer(ptrs[0], "%1p", "Width smaller than pointer representation");
    test_pointer(ptrs[0], "%50p", "Large width");
    
    // PRECISION TESTS (precision should be ignored for pointers)
    run_category("Precision Tests (should be ignored)");
    
    test_pointer(ptrs[0], "%.p", "Dot precision");
    test_pointer(null_ptr, "%.p", "NULL with dot precision");
    test_pointer(ptrs[0], "%.0p", "Zero precision");
    test_pointer(ptrs[0], "%.20p", "Large precision");
    test_pointer(ptrs[0], "%20.10p", "Width and precision");
    test_pointer(ptrs[0], "%-20.10p", "Left-alignment with precision");
    
    // FLAG TESTS - using safe test function that accounts for platform differences
    run_category("Flag Tests");
    
    // Using the helper function from test_utils to handle platform-specific behavior
    test_pointer_with_flags(ptrs[0], "%+p", "Plus flag (platform-dependent)");
    test_pointer_with_flags(null_ptr, "%+p", "NULL with plus flag");
    test_pointer_with_flags(ptrs[0], "% p", "Space flag (platform-dependent)");
    test_pointer_with_flags(ptrs[0], "%#p", "Hash flag (may be redundant)");
    test_pointer_with_flags(ptrs[0], "%0p", "Zero flag without width");
    test_pointer_with_flags(ptrs[0], "%020p", "Zero padding with width");
    test_pointer_with_flags(ptrs[0], "%-020p", "Left-justify with zero padding");
    
    // CONTEXT TESTS
    run_category("Context Tests");
    
    test_pointer(ptrs[0], "Pointer value: %p", "Text before");
    test_pointer(ptrs[0], "%p is a pointer", "Text after");
    test_pointer(ptrs[0], "The pointer %p is on the stack", "Text before and after");
    
    // Use test_multiple_pointers for tests with multiple pointers
    test_multiple_pointers("%p vs %p", "Multiple pointers in format", ptrs[0], ptrs[1]);
    
    // STRESS TESTS
    run_category("Stress Tests");
    
    // Test with extreme formatting
    test_pointer(ptrs[0], "%100p", "Very large width");
    test_pointer(ptrs[0], "%-100p", "Very large left-aligned width");
    test_pointer(ptrs[0], "%0100p", "Very large zero-padded width");
    test_pointer(max_ptr, "%p", "ULONG_MAX pointer");
    
    // Test with complex combinations
    test_pointer_with_flags(ptrs[0], "%+#-020.10p", "All flags combined");
    
    // Use test_multiple_pointers for tests with multiple pointers
    test_multiple_pointers("Multiple: %p %p %p %p %p", "Multiple pointers", 
                         ptrs[0], ptrs[1], ptrs[2], ptrs[3], ptrs[4]);
    
    // EDGE CASES
    run_category("Edge Cases");
    
    // Compare NULL and 0 pointers
    printf("Comparing NULL (0x0) pointers:\n");
    test_pointer(NULL, "%p", "NULL literal");
    test_pointer(null_ptr, "%p", "NULL pointer variable");
    test_pointer((void*)0, "%p", "Explicit (void*)0");
    
    // Test casting other types to pointers
    test_pointer((void*)0xdeadbeef, "%p", "Hex constant cast to pointer");
    test_pointer((void*)0x0, "%p", "Zero hex cast to pointer");
    test_pointer((void*)&test_count, "%p", "Address of global variable");
    
    // Print final summary
    print_summary();
    
    return fail_count > 0 ? 1 : 0;
}
