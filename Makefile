NAME			=	libftprintf.a

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS 		=	rcs
RM				=	rm -rf

SRC_DIR			=	..
SRC				=	ft_printf ft_print_char ft_print_str ft_print_hex ft_print_int ft_print_ptr ft_print_unsigned ft_nbr_len ft_flags ft_flags_utils ft_print_flag ft_printf_itoa ft_printf_utoa ft_printf_xtoa
SRCS 			=	$(addsuffix .c, $(SRC))

OBJ_DIR			=	obj
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH		=	$(SRC_DIR)/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

TEST_SRCS		=	$(wildcard *.c)
TEST_OBJS		=	$(TEST_SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_EXECUTABLES =	$(filter-out $(OBJ_DIR)/char_tests.o $(OBJ_DIR)/pointer_debug.o $(OBJ_DIR)/pointer_test.o, $(TEST_SRCS:%.c=%))

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@mkdir -p $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o:		%.c
					@mkdir -p $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@

all:				$(TEST_EXECUTABLES) char_tests pointer_debug pointer_test

bonus:				all

$(NAME):			$(LIBFT) $(OBJ_DIR) $(OBJS)
					cp	$(LIBFT) $(NAME)
					$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(LIBFT):
					make -C $(LIBFT_PATH) all

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
					make -C $(LIBFT_PATH) clean
					$(RM) $(OBJ_DIR)
					rm -f $(TEST_OBJS)

fclean:				clean
					make -C $(LIBFT_PATH) fclean
					$(RM) $(TEST_EXECUTABLES) $(OBJS) char_tests pointer_debug pointer_test

re:					fclean all

$(TEST_EXECUTABLES): %: $(OBJ_DIR)/%.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

# Individual test targets
test:				$(OBJ_DIR)/test.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o test $(OBJ_DIR)/test.o $(OBJS) $(LIBFT)
					./test

ultimate:			$(OBJ_DIR)/ft_printf_ultimate_tester.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o ft_printf_ultimate_tester $(OBJ_DIR)/ft_printf_ultimate_tester.o $(OBJS) $(LIBFT)
					./ft_printf_ultimate_tester

tester:				$(OBJ_DIR)/ft_printf_tester.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o ft_printf_tester $(OBJ_DIR)/ft_printf_tester.o $(OBJS) $(LIBFT)
					./ft_printf_tester

fixed:				$(OBJ_DIR)/ft_printf_tester_fixed.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o ft_printf_tester_fixed $(OBJ_DIR)/ft_printf_tester_fixed.o $(OBJS) $(LIBFT)
					./ft_printf_tester_fixed

stress:				$(OBJ_DIR)/ft_printf_stress_tester.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o ft_printf_stress_tester $(OBJ_DIR)/ft_printf_stress_tester.o $(OBJS) $(LIBFT)
					./ft_printf_stress_tester

debug:				$(OBJ_DIR)/ft_printf_debug_tester.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o ft_printf_debug_tester $(OBJ_DIR)/ft_printf_debug_tester.o $(OBJS) $(LIBFT)
					./ft_printf_debug_tester

simple:				$(OBJ_DIR)/ft_printf_debug_tester_simple.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o ft_printf_debug_tester_simple $(OBJ_DIR)/ft_printf_debug_tester_simple.o $(OBJS) $(LIBFT)
					./ft_printf_debug_tester_simple

pointer_debug:		$(OBJ_DIR)/pointer_debug.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o pointer_debug $(OBJ_DIR)/pointer_debug.o $(OBJS) $(LIBFT)
					./pointer_debug

pointer_test:		$(OBJ_DIR)/pointer_test.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o pointer_test $(OBJ_DIR)/pointer_test.o $(OBJS) $(LIBFT)
					./pointer_test

char_tests:			$(OBJ_DIR)/char_tests.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o char_tests $(OBJ_DIR)/char_tests.o $(OBJS) $(LIBFT)
					./char_tests

# Add extended character tests
char_tests_extended:	$(OBJ_DIR)/char_tests_extended.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o char_tests_extended $(OBJ_DIR)/char_tests_extended.o $(OBJS) $(LIBFT)
					./char_tests_extended

# Add string tests
string_tests_extended:	$(OBJ_DIR)/string_tests_extended.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o string_tests_extended $(OBJ_DIR)/string_tests_extended.o $(OBJS) $(LIBFT)
					./string_tests_extended

# Add integer tests
int_tests_extended:	$(OBJ_DIR)/int_tests_extended.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o int_tests_extended $(OBJ_DIR)/int_tests_extended.o $(OBJS) $(LIBFT)
					./int_tests_extended

# Add pointer extended tests
ptr_tests_extended:	$(OBJ_DIR)/ptr_tests_extended.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o ptr_tests_extended $(OBJ_DIR)/ptr_tests_extended.o $(OBJS) $(LIBFT)
					./ptr_tests_extended

# Add unsigned integer tests
unsigned_tests_extended:	$(OBJ_DIR)/unsigned_tests_extended.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o unsigned_tests_extended $(OBJ_DIR)/unsigned_tests_extended.o $(OBJS) $(LIBFT)
					./unsigned_tests_extended

# Add hexadecimal tests
hex_tests_extended:	$(OBJ_DIR)/hex_tests_extended.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o hex_tests_extended $(OBJ_DIR)/hex_tests_extended.o $(OBJS) $(LIBFT)
					./hex_tests_extended

# Add flag combinations tester
flag_combinations_tester:	$(OBJ_DIR)/flag_combinations_tester.o $(OBJS) $(LIBFT)
					$(CC) $(CFLAGS) -o flag_combinations_tester $(OBJ_DIR)/flag_combinations_tester.o $(OBJS) $(LIBFT)
					./flag_combinations_tester

run_tests:			$(TEST_EXECUTABLES) char_tests pointer_debug pointer_test
					@for test in $(TEST_EXECUTABLES) char_tests pointer_debug pointer_test; do \
						echo "Running $$test..."; \
						./$$test; \
					done

.PHONY:				all bonus clean fclean re run_tests test ultimate tester fixed stress debug simple pointer_debug pointer_test char_tests char_tests_extended string_tests_extended int_tests_extended ptr_tests_extended unsigned_tests_extended hex_tests_extended flag_combinations_tester