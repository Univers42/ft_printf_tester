# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 13:42:50 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/07 01:12:12 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Initialize directory structure
$(shell mkdir -p make/animations make/rules make/configurations make/functions make/commands make/dependencies make/targets)

# Include configuration files
include make/configurations/variables.mk
include make/configurations/colors.mk
include make/configurations/commands.mk
include make/configurations/config.mk
include make/configurations/flags.mk

# Include function definitions
include make/functions/utils.mk
include make/functions/progress.mk
include make/functions/header.mk
include make/functions/footer.mk
include make/functions/errors.mk
include make/functions/test_header.mk

# Include rules
include make/rules/compile.mk
include make/rules/build.mk
include make/rules/arch.mk
include make/rules/link.mk
include make/rules/rules.mk

# Include dependencies
include make/dependencies/dependencies.mk
include make/dependencies/dependencies_rules.mk

# Include animations
include make/animations/animations.mk
include make/animations/animations_rules.mk
include make/animations/progress.mk

# Include commands
include make/commands/commands.mk
include make/commands/commands_rules.mk

# Include target definitions
include make/targets/tests.mk
include make/targets/helper.mk
include make/targets/clean.mk

# Add the new source files to your existing SRC list
SRC += src/ft_printf_format_parser.c
SRC += src/ft_printf_mixed_tests.c
SRC += src/ft_printf_va_helper.c
SRC += src/ft_printf_stress_core.c
SRC += src/ft_printf_stress_format.c
SRC += src/ft_printf_stress_basic.c
SRC += src/ft_printf_stress_width_precision.c
SRC += src/ft_printf_stress_edge_cases.c
SRC += src/ft_printf_stress_pointer_rapid.c
SRC += src/ft_printf_stress_main.c

# Main target
all: intro header_all build_root_project make_dirs $(LIBFT) $(TESTERS) footer_all
	
.PHONY: all intro build_root_project clean fclean re setup \
	test debug simple stress flags char chars_ex ultimate controller list help \
	$(TEST_UTILS) $(SIMPLE_PRINTF) FORCE
