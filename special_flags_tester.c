#include "../ft_printf.h"
#include "ft_printf_test_utils.h"

// We'll focus on testing specific flag combinations that may cause issues
int main(void) {
    printf("%s=== FT_PRINTF SPECIAL FLAG COMBINATIONS TESTER ===%s\n", MAGENTA, RESET);
    
    // Remove duplicate global variables
    // int test_count = 0;
    // int pass_count = 0;
    // int fail_count = 0;
    
    // Remove duplicate functions
    // void run_category(const char *category) { ... }
    // void test_format(const char *format, const char *test_name, void *value, char type) { ... }
    
    // Set up test values
    int i_pos = 42;
    int i_neg = -42;
    int i_zero = 0;
    unsigned int u_val = UINT_MAX;
    unsigned int x_val = 0xabcdef;
    char c_val = 'X';
    char *s_val = "Hello";
    void *p_val = &i_pos;
    
    // SPECIAL FLAG COMBINATION TESTS
    run_category("CONTRADICTORY FLAGS");
    
    // Zero padding vs Left-justify (left-justify should win)
    test_format("%-05d", "Left-justify vs Zero padding (int)", &i_pos, 'd');
    test_format("%-05u", "Left-justify vs Zero padding (unsigned)", &u_val, 'u');
    test_format("%-05x", "Left-justify vs Zero padding (hex)", &x_val, 'x');
    test_format("%-05X", "Left-justify vs Zero padding (HEX)", &x_val, 'X');
    
    // Plus vs Space (plus should win)
    test_format("%+ d", "Plus vs Space (positive)", &i_pos, 'd');
    test_format("%+ d", "Plus vs Space (negative)", &i_neg, 'd');
    test_format("%+ d", "Plus vs Space (zero)", &i_zero, 'd');
    
    // Precision vs Zero padding (precision should win for numbers)
    test_format("%08.5d", "Precision vs Zero padding (int)", &i_pos, 'd');
    test_format("%08.5d", "Precision vs Zero padding (negative int)", &i_neg, 'd');
    test_format("%08.5u", "Precision vs Zero padding (unsigned)", &u_val, 'u');
    test_format("%08.5x", "Precision vs Zero padding (hex)", &x_val, 'x');
    test_format("%08.5X", "Precision vs Zero padding (HEX)", &x_val, 'X');
    
    run_category("FLAG STACKING");
    
    // Multiple flags in different orders
    test_format("% +d", "Space then Plus (positive)", &i_pos, 'd');
    test_format("%+ d", "Plus then Space (positive)", &i_pos, 'd');
    test_format("%0-8d", "Zero then Left (positive)", &i_pos, 'd');
    test_format("%-08d", "Left then Zero (positive)", &i_pos, 'd');
    test_format("%+0d", "Plus then Zero (positive)", &i_pos, 'd');
    test_format("%0+d", "Zero then Plus (positive)", &i_pos, 'd');
    test_format("% 0d", "Space then Zero (positive)", &i_pos, 'd');
    test_format("%0 d", "Zero then Space (positive)", &i_pos, 'd');
    
    run_category("FLAGS WITH PRECISION & WIDTH");
    
    // Comprehensive combinations
    test_format("%+10.5d", "Plus, Width, Precision (positive)", &i_pos, 'd');
    test_format("%+10.5d", "Plus, Width, Precision (negative)", &i_neg, 'd');
    test_format("%+10.5d", "Plus, Width, Precision (zero)", &i_zero, 'd');
    test_format("% 10.5d", "Space, Width, Precision (positive)", &i_pos, 'd');
    test_format("% 10.5d", "Space, Width, Precision (negative)", &i_neg, 'd');
    test_format("% 10.5d", "Space, Width, Precision (zero)", &i_zero, 'd');
    test_format("%#10.5x", "Hash, Width, Precision (hex)", &x_val, 'x');
    test_format("%#10.5X", "Hash, Width, Precision (HEX)", &x_val, 'X');
    test_format("%#10.0x", "Hash, Width, Zero Precision (hex)", &x_val, 'x');
    test_format("%#10.0X", "Hash, Width, Zero Precision (HEX)", &x_val, 'X');
    test_format("%#10.0x", "Hash, Width, Zero Precision (zero hex)", &i_zero, 'x');
    
    test_format("%-+10.5d", "Left, Plus, Width, Precision (positive)", &i_pos, 'd');
    test_format("%-+10.5d", "Left, Plus, Width, Precision (negative)", &i_neg, 'd');
    test_format("%-+10.5d", "Left, Plus, Width, Precision (zero)", &i_zero, 'd');
    test_format("%- 10.5d", "Left, Space, Width, Precision (positive)", &i_pos, 'd');
    test_format("%- 10.5d", "Left, Space, Width, Precision (negative)", &i_neg, 'd');
    test_format("%-#10.5x", "Left, Hash, Width, Precision (hex)", &x_val, 'x');
    test_format("%-#10.5X", "Left, Hash, Width, Precision (HEX)", &x_val, 'X');
    
    run_category("EXTREME CASES");
    
    // Very large width/precision
    test_format("%+100.50d", "Very large width & precision (positive int)", &i_pos, 'd');
    test_format("%+100.50d", "Very large width & precision (negative int)", &i_neg, 'd');
    test_format("%#100.50x", "Very large width & precision (hex)", &x_val, 'x');
    test_format("%100.50s", "Very large width & precision (string)", s_val, 's');
    test_format("%100c", "Very large width (character)", &c_val, 'c');
    test_format("%100p", "Very large width (pointer)", p_val, 'p');
    
    // Large precision but small width
    test_format("%5.50d", "Small width, large precision (positive int)", &i_pos, 'd');
    test_format("%5.50d", "Small width, large precision (negative int)", &i_neg, 'd');
    test_format("%#5.50x", "Small width, large precision (hex)", &x_val, 'x');
    test_format("%5.50s", "Small width, large precision (string)", s_val, 's');
    
    // Edge cases with zero
    test_format("%.0d", "Zero precision with zero (int)", &i_zero, 'd');
    test_format("%.d", "Dot precision with zero (int)", &i_zero, 'd');
    test_format("%.0u", "Zero precision with zero (unsigned)", &i_zero, 'u');
    test_format("%.0x", "Zero precision with zero (hex)", &i_zero, 'x');
    test_format("%.0X", "Zero precision with zero (HEX)", &i_zero, 'X');
    test_format("%#.0x", "Hash with zero precision with zero (hex)", &i_zero, 'x');
    test_format("%#.x", "Hash with dot precision with zero (hex)", &i_zero, 'x');
    test_format("%+.0d", "Plus with zero precision with zero (int)", &i_zero, 'd');
    test_format("%+.d", "Plus with dot precision with zero (int)", &i_zero, 'd');
    test_format("% .0d", "Space with zero precision with zero (int)", &i_zero, 'd');
    test_format("% .d", "Space with dot precision with zero (int)", &i_zero, 'd');
    
    // Print summary
    print_summary();
    
    return fail_count > 0 ? 1 : 0;
}
