/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_library.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syzygy <syzygy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:00:00 by syzygy            #+#    #+#             */
/*   Updated: 2025/03/23 16:19:14 by syzygy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include "../headers/controller.h"

/*
 * This utility verifies which library is actually being used at runtime
 * It prints detailed information about the loaded symbols and libraries
 */

void verify_linked_library(void)
{
    void *handle;
    void *symbol;
    char *error;
    
    printf("\n=== LIBRARY VERIFICATION DIAGNOSTIC ===\n");
    
    // Try to find symbols specific to mandatory or bonus implementations
    printf("Checking for ft_printf function...\n");
    
    // First try to open the program itself
    handle = dlopen(NULL, RTLD_LAZY);
    if (!handle) {
        printf("Error opening program: %s\n", dlerror());
        return;
    }
    
    // Clear any existing error
    dlerror();
    
    // Check for ft_printf (should be available in both versions)
    symbol = dlsym(handle, "ft_printf");
    error = dlerror();
    
    if (error != NULL) {
        printf("ERROR: Cannot find ft_printf symbol: %s\n", error);
        printf("DIAGNOSTIC: Program is NOT correctly linked to any ft_printf implementation!\n");
    } else {
        printf("SUCCESS: Found ft_printf symbol at address: %p\n", symbol);
        
        // Now try to find which library the function is from
        Dl_info info;
        if (dladdr(symbol, &info)) {
            printf("Symbol found in: %s\n", info.dli_fname);
            
            if (strstr(info.dli_fname, "bonus")) {
                printf("DIAGNOSTIC: Program is using BONUS implementation: %s\n", info.dli_fname);
            } else {
                printf("DIAGNOSTIC: Program is using MANDATORY implementation: %s\n", info.dli_fname);
            }
        } else {
            printf("Could not determine which library contains ft_printf\n");
        }
    }
    
    dlclose(handle);
    printf("=== END OF DIAGNOSTIC ===\n\n");
}
