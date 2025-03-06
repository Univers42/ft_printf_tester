# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    progress.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dyl-syzygy <dyl-syzygy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 14:37:35 by dyl-syzygy        #+#    #+#              #
#    Updated: 2025/03/06 14:37:36 by dyl-syzygy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define progress_bar
	@for k in $(shell seq 1 $(1)); do \
		perl -e 'select(undef, undef, undef, 0.01)'; \
		count=$$(($(2) * k / $(1))); \
		printf "\r  $(YELLOW)%-25s [$(GREEN)" "$(3)"; \
		for i in $$(seq 1 $$count); do printf "▓"; done; \
		for i in $$(seq 1 $$(( $(2) - $$count ))); do printf "$(GRAY)·"; done; \
		printf "$(YELLOW)] %3d%% $(RESET)" $$(( 100 * k / $(1) )); \
	done; \
	printf "\n"
endef
