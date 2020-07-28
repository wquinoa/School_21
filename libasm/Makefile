# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/04 15:27:49 by wquinoa           #+#    #+#              #
#    Updated: 2020/07/06 11:10:48 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Source files																#
SRCS	:= ft_strlen.s	ft_strcpy.s	ft_strcmp.s	ft_write.s	ft_strdup.s	ft_read.s

BSRCS	:= ft_list_push_front_bonus.s	ft_list_size_bonus.s	ft_list_sort_bonus.s

#	Utilities																	#
WHT		= \033[0m#																#
GRN		= \033[32m#																#
RED		= \033[31m#																#
WHT1	= \033[0;1m#															#
GRN1	= \033[32;1m#															#
RED1	= \033[31;1m#															#
DRK		= \033[2m#																#
MADE_MSG	= \n	$(WHT1)Created $(GRN1)#										#
DEL_MSG		= \n	$(WHT1)Removed $(DRK)$(RED1)#								#
ERROR_MSG	= "\n	$(WHT1)$(DRK)Nothing to $@\n"#								#
REPLACE		=  2>&1| awk '{sub(/.\//,"  $(WHT)$(DRK)removed $(RED)")}1'

#	Good stuff																	#
NAME	= libasm.a
OBJ		= $(SRCS:s=o)
BOBJ	= $(BSRCS:s=o)
BIN		= ./obj
CC		= nasm
CF		= -fmacho64

ifdef WITH_BONUS
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ) $(BOBJ))
else
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ))
endif
#	Rules																		#
#.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $^
	@echo "$(MADE_MSG)$(NAME)$(WHT)\n"

bonus:
	$(MAKE) 'WITH_BONUS = true' all

main: $(NAME)
	@gcc main.c $(NAME) && ./a.out

main_b: bonus
	@gcc main_bonus.c $(NAME) && ./a.out

#	Creating bindir and objects													#
$(BIN):
	@mkdir $@
	@echo "$(MADE_MSG) $@$(WHT)\n"

$(BIN)/%.o: %.s | $(BIN)
	@$(CC) $< $(CF) -o $@
	@echo "   Adding $(DRK)$(GRN)$@...$(WHT)"

#	Trash removal rules															#
clean:
	@if test -d $(BIN); \
	then rm -Rfv $(BIN) $(REPLACE); \
	echo "$(DEL_MSG).o files$(WHT)\n"; \
	else echo $(ERROR_MSG); \
	fi

fclean: clean
	@if test -f $(NAME); \
	then rm -rfv ./$(NAME) $(REPLACE) && rm -rf a.out; \
	echo "$(DEL_MSG)$(NAME)$(WHT)\n"; \
	else echo $(ERROR_MSG); \
	fi

re: fclean all
