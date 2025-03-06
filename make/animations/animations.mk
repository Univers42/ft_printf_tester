# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    animations.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 14:29:07 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/06 15:45:23 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Animation loader definitions
define loading_spinner
	@for i in $(shell seq 1 $(1)); do \
		for c in "⣾" "⣽" "⣻" "⢿" "⡿" "⣟" "⣯" "⣷"; do \
			printf "$(2)  %s $(3)$(RESET)\r" "$$c"; \
			sleep 0.05; \
		done; \
	done
endef

define pulse_text
	@for i in 1 2 3; do \
		printf "\r$(BOLD)$(1)$(RESET)" ; \
		sleep 0.15 ; \
		printf "\r$(BOLD)$(2)$(RESET)" ; \
		sleep 0.15 ; \
	done
	@printf "\r$(BOLD)$(1)$(RESET)\n\n"
endef

define blink_text
	@for i in 1 2 3; do \
		printf "$(3)"; \
		sleep 0.2; \
		printf "\r%*s\r" $${#3} ""; \
		sleep 0.2; \
	done
	@printf "$(3)\n"
endef
