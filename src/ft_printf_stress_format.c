/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stress_format.c                          :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:00:00 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/03/07 01:09:20 by dyl-syzygy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_stress.h"

/* Generate a random format string for fuzzing */
char* generate_random_format(void)
{
    static char buffer[100];
    const char *conversions = "cspdiuxX%";
    const char *flags = "-+ #0";
    int idx = 0;
    int has_percent = 0;
    
    // Make sure we have at least one format specifier
    if (rand() % 10 > 2 || !has_percent) {
        buffer[idx++] = '%';
        has_percent = 1;
        
        // Maybe add some flags (30% chance)
        if (rand() % 10 < 3) {
            int flag_count = rand() % 3 + 1;  // 1-3 flags
            for (int i = 0; i < flag_count; i++) {
                buffer[idx++] = flags[rand() % strlen(flags)];
            }
        }
        
        // Maybe add width (40% chance)
        if (rand() % 10 < 4) {
            int width = rand() % 20 + 1;  // 1-20 width
            idx += sprintf(buffer + idx, "%d", width);
        }
        
        // Maybe add precision (30% chance)
        if (rand() % 10 < 3) {
            buffer[idx++] = '.';
            int prec = rand() % 10;  // 0-9 precision
            if (prec > 0 || rand() % 2)  // 50% chance to have .0
                idx += sprintf(buffer + idx, "%d", prec);
        }
        
        // Add conversion specifier (not %)
        buffer[idx++] = conversions[rand() % (strlen(conversions) - 1)];
    } else {
        // Add some text
        const char *texts[] = {"Hello", "World", "Test", "Printf", "42"};
        strcpy(buffer + idx, texts[rand() % 5]);
        idx += strlen(texts[rand() % 5]);
    }
    
    buffer[idx] = '\0';
    return buffer;
}

/* Test with a randomly generated value appropriate for the format */
void test_random_value(const char *format)
{
    const char *test_name = "Random value test";
    char type = 0;
    
    // Find the conversion type
    const char *ptr = format;
    while (*ptr) {
        if (*ptr == '%' && *(ptr+1) && *(ptr+1) != '%') {
            // Skip flags, width, precision
            ptr++;
            while (*ptr && (*ptr == '#' || *ptr == '0' || *ptr == '-' || 
                   *ptr == '+' || *ptr == ' ' || (*ptr >= '0' && *ptr <= '9') ||
                   *ptr == '.'))
                ptr++;
                
            type = *ptr;
            break;
        }
        ptr++;
    }
    
    // Check if this is a pointer with flags format (like %+p, % p)
    if (type == 'p' && (strstr(format, "%+") || strstr(format, "% "))) {
        // Use special handler for pointer flags
        void *values[] = {NULL, (void*)0x1, (void*)0xff, (void*)0xffff, (void*)0xffffffff};
        test_pointer_format_flags(format, test_name, values[rand() % 5]);
        return;
    }
    
    // Select a random value based on the conversion type
    switch (type) {
        case 'c': {
            char c = rand() % 95 + 32;  // Printable ASCII
            test_simple(format, test_name, c);
            break;
        }
        case 's': {
            const char *strings[] = {"", "Hello", "Test", "A very long string to test width limits and other edge cases", NULL};
            test_simple(format, test_name, strings[rand() % 5]);
            break;
        }
        case 'd':
        case 'i': {
            int values[] = {0, 1, -1, 42, -42, INT_MAX, INT_MIN, INT_MAX/2, INT_MIN/2};
            test_simple(format, test_name, values[rand() % 9]);
            break;
        }
        case 'u': {
            unsigned int values[] = {0, 1, 42, 100000, UINT_MAX, UINT_MAX/2, UINT_MAX-1};
            test_simple(format, test_name, values[rand() % 7]);
            break;
        }
        case 'x':
        case 'X': {
            unsigned int values[] = {0, 1, 0xf, 0xff, 0xfff, 0xffff, 0xabcdef, UINT_MAX};
            test_simple(format, test_name, values[rand() % 8]);
            break;
        }
        case 'p': {
            void *values[] = {NULL, (void*)0x1, (void*)0xff, (void*)0xffff, (void*)0xffffffff};
            test_simple(format, test_name, values[rand() % 5]);
            break;
        }
        case '%':
            test_simple(format, test_name);
            break;
        default:
            // Unsupported type
            break;
    }
}
