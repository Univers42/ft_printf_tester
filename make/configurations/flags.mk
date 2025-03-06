# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    flags.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 14:26:21 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/06 14:25:17 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Main compiler flags are already defined in variables.mk

# Additional flags for debug mode
DEBUG_CFLAGS = -g3 -fsanitize=address

# Additional flags for release mode
RELEASE_CFLAGS = -O2

# Additional flags for test mode
TEST_CFLAGS = -coverage

# Link flags
LDFLAGS = 

# Library flags
LDLIBS = -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft
LDLIBS_SUPP = -L$(PRINTF_DIR) -lftprintf -lftprintf_supp -L$(LIBFT_DIR) -lft
