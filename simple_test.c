/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:18:09 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:18:10 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

// Prototype for our simple implementation
int	simple_ft_printf(const char *format, ...);

int main(void)
{
    int count1, count2, count3;
    
    printf("\n----- TESTING SIMPLE IMPLEMENTATION -----\n\n");
    
    // Test 1: Simple character
    printf("Test 1: Character\n");
    printf("printf:      ");
    count1 = printf("Character: %c\n", 'A');
    printf("ft_printf:   ");
    count2 = ft_printf("Character: %c\n", 'A');
    printf("simple_printf:");
    count3 = simple_ft_printf("Character: %c\n", 'A');
    printf("Return values - printf: %d, ft_printf: %d, simple_printf: %d\n\n", count1, count2, count3);
    
    // Test 2: Simple string
    printf("Test 2: String\n");
    printf("printf:      ");
    count1 = printf("String: %s\n", "Hello, world!");
    printf("ft_printf:   ");
    count2 = ft_printf("String: %s\n", "Hello, world!");
    printf("simple_printf:");
    count3 = simple_ft_printf("String: %s\n", "Hello, world!");
    printf("Return values - printf: %d, ft_printf: %d, simple_printf: %d\n\n", count1, count2, count3);
    
    // Test 3: Simple integer
    printf("Test 3: Integer\n");
    printf("printf:      ");
    count1 = printf("Integer: %d\n", 42);
    printf("ft_printf:   ");
    count2 = ft_printf("Integer: %d\n", 42);
    printf("simple_printf:");
    count3 = simple_ft_printf("Integer: %d\n", 42);
    printf("Return values - printf: %d, ft_printf: %d, simple_printf: %d\n\n", count1, count2, count3);
    
    return (0);
}
