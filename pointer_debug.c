/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:17:56 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/05 14:07:51 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "ft_printf_debug.h"

int main(void) {
    int num = 42;
    void *ptr = &num;
    char hex_chars[] = "0123456789abcdef";
    int shift;
    int printf_ret, ft_printf_ret, digits;
    unsigned long addr;
    
    printf("=== Pointer Test Debug ===\n\n");
    printf("Standard printf:\n");
    printf_ret = printf("Pointer: %p\n", ptr);
    printf("Return value: %d\n\n", printf_ret);
    printf("Your ft_printf:\n");
    ft_printf_ret = ft_printf("Pointer: %p\n", ptr);
    printf("Return value: %d\n\n", ft_printf_ret);
    printf("Debugging pointer address:\n");
    addr = (unsigned long)ptr;
    printf("Address as unsigned long: %lu\n", addr);
    printf("Address as hex: 0x");
    digits = sizeof(void*) * 2; 
    for (shift = (digits - 1) * 4; shift >= 0; shift -= 4)
        printf("%c", hex_chars[(addr >> shift) & 0xF]);
    printf("\n");
    return 0;
}
