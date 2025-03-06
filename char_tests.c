/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 01:16:19 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/06 18:07:22 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "headers/controller.h"

// Fix the test with multiple characters
void test_characters_in_context(void) {
    // Fix: Pass characters directly rather than using a helper function
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    int ret1, ret2;
    
    // Store the expected result from printf
    ret1 = sprintf(buf1, "Test: %c and %c", 'X', 'Y');
    
    // Capture ft_printf output
    int pipe_fd[2];
    if (pipe(pipe_fd) != -1) {
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        
        // Call ft_printf with separate character arguments
        ret2 = ft_printf("Test: %c and %c", 'X', 'Y');
        
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipe_fd[1]);
        
        int bytes_read = read(pipe_fd[0], buf2, BUFFER_SIZE - 1);
        if (bytes_read >= 0)
            buf2[bytes_read] = '\0';
        close(pipe_fd[0]);
        
        // Compare results
        compare_and_print_results(buf1, ret1, buf2, ret2, 
                                "Test: %c and %c", "Multiple characters in context");
    }
}

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
    // Using our improved function to correctly handle multiple characters
    test_characters_in_context();
    
    printf("\n=== CHAR TESTS COMPLETED ===\n");
    return 0;
}
