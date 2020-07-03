# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/07 23:33:20 by wquinoa           #+#    #+#              #
#    Updated: 2020/07/02 16:14:36 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Source files                                                                                                      |#
#+----------------------------------------------------------------------------------------------------------------------+#

SRCS :=			ft_atoi.c			ft_bzero.c			ft_calloc.c			ft_isalnum.c		ft_isalpha.c			\
				ft_isascii.c		ft_isdigit.c		ft_isprint.c		ft_itoa.c			ft_memccpy.c			\
				ft_memchr.c			ft_memcmp.c			ft_memcpy.c			ft_memmove.c		ft_memset.c				\
				ft_split.c			ft_strchr.c			ft_strdup.c			ft_strjoin.c		ft_strlcat.c			\
				ft_strlcpy.c		ft_strlen.c			ft_strmapi.c		ft_strncmp.c		ft_strnstr.c			\
				ft_strrchr.c		ft_strtrim.c		ft_substr.c			ft_tolower.c		ft_toupper.c			\
				ft_putchar_fd.c		ft_putendl_fd.c		ft_putnbr_fd.c		ft_putstr_fd.c		ft_strswap.c

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Bonus files                                                                                                       |#
#+----------------------------------------------------------------------------------------------------------------------+#

BSRCS :=		ft_lstadd_back.c	ft_lstadd_front.c	ft_lstclear.c		ft_lstdelone.c		ft_lstiter.c			\
				ft_lstlast.c		ft_lstmap.c			ft_lstnew.c			ft_lstsize.c		ft_abs_bonus.c			\
				ft_del_bonus.c		ft_isspace_bonus.c	ft_join_bonus.c		ft_max_bonus.c		ft_min_bonus.c			\
				ft_nlen_bonus.c		ft_pow_bonus.c		ft_sqrt_bonus.c		ft_strjoin_dlm_bonus.c						\
				ft_tabclear_bonus.c	ft_tablen_bonus.c	ft_tabmap_bonus.c	get_next_line.c

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Utilities                                                                                                         |#
#+----------------------------------------------------------------------------------------------------------------------+#

WHT = \033[0m#																# █░░░░░░░░░▄▄▀▀▀▀▀░░░░░▀▀▀▄░█
GRN = \033[32m#																# █░░░░░░░░░░░░░░░░▀░░░▐░░░░░▐▌
RED = \033[31m#																# ▐▌░░░░░░░░░▐▀▀█░█▄░░░░░▄▄▄░▐▌
WHT1 = \033[0;1m#															#  █░░░░░░░░░░░▀▀▀░░░░░░▀▀██░░█ tfw 5th retry
GRN1 = \033[32;1m#															#  ▐▌░░░░▄░░░░░░░░░░░░░▌░░░░░░█
RED1 = \033[31;1m#															#   ▐▌░░▐░░░░░░░░░░░░░░▀▄░░░░░█
DRK = \033[2m#																#    █░░░▌░░░░░░░░▐▀░░░░▄▀░░░▐▌
MADE_MSG = \n	$(WHT1)Created $(GRN1)#										#    ▐▌░░▀▄░░░░░░░░▀░▀░▀▀░░░▄▀
DEL_MSG = \n	$(WHT1)No more $(DRK)$(RED1)#								#    ▐▌░░▐▀▄░░░░░░░░░░░░░░░░█
ERROR_MSG = "\n	$(WHT1)$(DRK)Nothing to $@\n"#								#    ▐▌░░░▌░▀▄░░░▄▀▀▀▀▀▀▄░░█
REPLACE =  2>&1| awk '{sub(/.\//,"  $(WHT) $(DRK)removed $(RED)")}1'

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Good stuff                                                                                                        |#
#+----------------------------------------------------------------------------------------------------------------------+#

NAME = libft.a
HEAD = $(NAME:a=h)
OBJ = $(SRCS:c=o)
BOBJ = $(BSRCS:c=o)
BIN = ./obj
CC = gcc
CF = -Wall -Wextra -Werror
.PHONY: all bonus clean fclean re

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Conditionals                                                                                                      |#
#+----------------------------------------------------------------------------------------------------------------------+#

#.ONESHELL:
ifdef WITH_BONUS
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ) $(BOBJ))
else
$(VERBOSE).SILENT:
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ))
endif

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Rules                                                                                                             |#
#+----------------------------------------------------------------------------------------------------------------------+#

all: $(NAME)

bonus:
	@$(MAKE) 'WITH_BONUS = true' all

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $^
	@echo "$(MADE_MSG)$(NAME)$(WHT)\n"

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Creating bindir and objects                                                                                       |#
#+----------------------------------------------------------------------------------------------------------------------+#

$(BIN):
	@mkdir $(BIN)
	@echo "$(MADE_MSG) $@$(WHT)\n"

$(BIN)/%.o: %.c $(HEAD) | $(BIN)
	@$(CC) -I./ $< -c $(CF) -o $@
	@echo "   Adding $(DRK)$(GRN)$@...$(WHT)"

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Trash removal rules                                                                                               |#
#+----------------------------------------------------------------------------------------------------------------------+#

clean:
	@if test -d $(BIN); \
	then rm -rfvd $(BIN) $(REPLACE); \
	echo "$(DEL_MSG).o files$(WHT)\n"; \
	fi

fclean: clean
	@if test -f $(NAME); \
	then rm -rfv ./$(NAME) $(REPLACE); \
	rm -rf a.out; \
	echo "$(DEL_MSG) lib$(WHT)\n"; \
	fi

re: fclean all
