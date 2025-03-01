#include "../ft_printf.h"
#include "ft_printf_debug.h"

int main(void) {
    int num = 42;
    void *ptr = &num;

    printf("=== Pointer Test Debug ===\n\n");
    
    // Standard printf output for comparison
    printf("Standard printf:\n");
    int printf_ret = printf("Pointer: %p\n", ptr);
    printf("Return value: %d\n\n", printf_ret);
    
    // Your ft_printf output
    printf("Your ft_printf:\n");
    int ft_printf_ret = ft_printf("Pointer: %p\n", ptr);
    printf("Return value: %d\n\n", ft_printf_ret);

    // Print the pointer as individual hex digits to see where it's failing
    printf("Debugging pointer address:\n");
    unsigned long addr = (unsigned long)ptr;
    printf("Address as unsigned long: %lu\n", addr);
    printf("Address as hex: 0x");
    
    // Print each hex digit
    char hex_chars[] = "0123456789abcdef";
    int shift;
    int digits = sizeof(void*) * 2; // Number of hex digits in a pointer
    
    for (shift = (digits - 1) * 4; shift >= 0; shift -= 4) {
        printf("%c", hex_chars[(addr >> shift) & 0xF]);
    }
    printf("\n");

    return 0;
}
