# Main compiler flags are already defined in variables.mk

# Additional flags for debug mode
DEBUG_CFLAGS = -g3 -fsanitize=address

# Additional flags for release mode
RELEASE_CFLAGS = -O2

# Additional flags for test mode
TEST_CFLAGS = -coverage

# Link flags
LDFLAGS = 

# Define a function to dynamically determine library flags at runtime
define get_ldlibs
$(shell if [ -f "$(LIBFT_DIR)/libft.a" ] && [ -s "$(LIBFT_DIR)/libft.a" ]; then \
	echo "-L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft"; \
else \
	echo "-L$(PRINTF_DIR) -lftprintf"; \
fi)
endef

define get_ldlibs_supp
$(shell if [ -f "$(PRINTF_DIR)/libftprintf_supp.a" ]; then \
	if [ -f "$(LIBFT_DIR)/libft.a" ] && [ -s "$(LIBFT_DIR)/libft.a" ]; then \
		echo "-L$(PRINTF_DIR) -lftprintf -lftprintf_supp -L$(LIBFT_DIR) -lft"; \
	else \
		echo "-L$(PRINTF_DIR) -lftprintf -lftprintf_supp"; \
	fi; \
else \
	if [ -f "$(LIBFT_DIR)/libft.a" ] && [ -s "$(LIBFT_DIR)/libft.a" ]; then \
		echo "-L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft"; \
	else \
		echo "-L$(PRINTF_DIR) -lftprintf"; \
	fi; \
fi)
endef

# These will be evaluated at runtime when needed
LDLIBS = $(call get_ldlibs)
LDLIBS_SUPP = $(call get_ldlibs_supp)
