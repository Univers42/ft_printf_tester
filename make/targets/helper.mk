# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    helper.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 13:56:56 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/06 13:57:08 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

list:
	@echo "$(BOLD_CYAN)Available test executables:$(RESET)"
	@for test in $(TEST_EXECUTABLES); do \
		echo "  $(YELLOW)$$test$(RESET)"; \
	done

# Show help information
help:
	@echo "$(BOLD_CYAN)FT_PRINTF TESTER - Available commands:$(RESET)"
	@echo "  $(YELLOW)make$(RESET)           - Build all test programs"
	@echo "  $(YELLOW)make test$(RESET)      - Run standard test"
	@echo "  $(YELLOW)make debug$(RESET)     - Run debug test"
	@echo "  $(YELLOW)make simple$(RESET)    - Run simple test"
	@echo "  $(YELLOW)make stress$(RESET)    - Run stress test"
	@echo "  $(YELLOW)make flags$(RESET)     - Run flag tests"
	@echo "  $(YELLOW)make char$(RESET)      - Run character tests"
	@echo "  $(YELLOW)make chars_ex$(RESET)  - Run extended character tests"
	@echo "  $(YELLOW)make ultimate$(RESET)  - Run ultimate test"
	@echo "  $(YELLOW)make controller$(RESET) - Run test controller"
	@echo "  $(YELLOW)make list$(RESET)      - List all available test programs"
	@echo "  $(YELLOW)make clean$(RESET)     - Remove object files"
	@echo "  $(YELLOW)make fclean$(RESET)    - Remove objects and executables"
	@echo "  $(YELLOW)make re$(RESET)        - Rebuild everything"