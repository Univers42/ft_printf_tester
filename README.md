The issue is in your ft_print_char.c file. According to the C standard, the '0' flag should be ignored for character formatting - spaces should always be used for padding. Let's fix this:

ft_print_char.c+2-1
The key change is in the ft_pad_width function call, where I'm now passing 0 as the third parameter instead of flags.zero. This ensures that zero padding is never used for character formatting, which is the correct behavior according to the C standard.






