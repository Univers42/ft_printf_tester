/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:04 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/02 01:16:05 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>

int main(void)
{
    int count1, count2;
    
    printf("\n----- TESTING BASIC FUNCTIONALITY -----\n\n");
    
    // Test 1: Simple character
    printf("Test 1: Character\n");
    printf("Expected: ");
    count1 = printf("Character: %c\n", 'A');
    printf("Actual:   ");
    count2 = ft_printf("Character: %c\n", 'A');
    printf("Return values - printf: %d, ft_printf: %d\n\n", count1, count2);
    
    // Test 2: Simple string
    printf("Test 2: String\n");
    printf("Expected: ");
    count1 = printf("String: %s\n", "Hello, world!");
    printf("Actual:   ");
    count2 = ft_printf("String: %s\n", "Hello, world!");
    printf("Return values - printf: %d, ft_printf: %d\n\n", count1, count2);
    
    // Test 3: Simple integer
    printf("Test 3: Integer\n");
    printf("Expected: ");
    count1 = printf("Integer: %d\n", 42);
    printf("Actual:   ");
    count2 = ft_printf("Integer: %d\n", 42);
    printf("Return values - printf: %d, ft_printf: %d\n\n", count1, count2);
    
    // Test 4: Percent sign
    printf("Test 4: Percent sign\n");
    printf("Expected: ");
    count1 = printf("Percent: %%\n");
    printf("Actual:   ");
    count2 = ft_printf("Percent: %%\n");
    printf("Return values - printf: %d, ft_printf: %d\n\n", count1, count2);
    
    // Test 5: Combined formats
    printf("Test 5: Combined formats\n");
    printf("Expected: ");
    count1 = printf("Combined: %c %s %d %%\n", 'X', "test", 42);
    printf("Actual:   ");
    count2 = ft_printf("Combined: %c %s %d %%\n", 'X', "test", 42);
    printf("Return values - printf: %d, ft_printf: %d\n\n", count1, count2);
    
    return (0);
}
