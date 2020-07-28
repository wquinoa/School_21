# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/07 23:33:20 by wquinoa           #+#    #+#              #
#    Updated: 2020/07/28 14:08:47 by wquinoa          ###   ########.fr        #
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
				ft_putchar_fd.c		ft_putendl_fd.c		ft_putnbr_fd.c		ft_putstr_fd.c		ft_strcmp.c				\
				ft_lstadd_back.c	ft_lstadd_front.c	ft_lstclear.c		ft_lstdelone.c		ft_lstiter.c			\
				ft_lstlast.c		ft_lstmap.c			ft_lstnew.c			ft_lstsize.c		ft_fput.c				\
				ft_del.c			ft_isspace.c		ft_join.c			ft_strjoin_dlm.c	ft_swap.c				\
				ft_tabclear.c		ft_tablen.c			ft_tabmap.c			get_next_line.c

BSRCS :=		ft_math.c			ft_print.c			ft_printf.c			ft_putnbr_basep.c		\


#+----------------------------------------------------------------------------------------------------------------------+#
#|    Utilities                                                                                                         |#
#+----------------------------------------------------------------------------------------------------------------------+#

WHT = \033[0m#																#
GRN = \033[32m#																#
RED = \033[31m#																#
WHT1 = \033[0;1m#															#
GRN1 = \033[32;1m#															#
RED1 = \033[31;1m#															#
DRK = \033[2m#																#
MADE_MSG = \n   $(WHT1)Created $(GRN1)#										#
DEL_MSG = \r   $(WHT1)Removed $(DRK)$(RED1)#								#
ERROR_MSG = "\n   $(WHT1)$(DRK)Nothing to $@$(WHT)\n"#						#
REPLACE =  2>&1| awk '{sub(/.\//,"  $(WHT) $(DRK)removed $(RED)")}1'
NORME = norminette *.c *.h | awk '{sub(/Norme/,"$(GRN)Norme$(WHT)")}1' | awk '{sub(/Error/,"$(RED)Error$(WHT)")}1'

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Good stuff                                                                                                        |#
#+----------------------------------------------------------------------------------------------------------------------+#

NAME = libft.a
BIN = ./obj
BDIR = ft_printf/src

B_FILES = $(addprefix $(BDIR)/, $(BSRCS))
HEAD = $(NAME:a=h)
OBJ = $(SRCS:c=o)
BOBJ = $(B_FILES:c=o)
CC = gcc
CF = -Wall -Wextra -Werror
.PHONY: all bonus clean fclean re

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Conditionals                                                                                                      |#
#+----------------------------------------------------------------------------------------------------------------------+#

#$(VERBOSE).SILENT:
#.ONESHELL:
ifdef WITH_BONUS
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ)) $(addprefix $(BIN)/, $(BSRCS:c=o))
else
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
	@echo "$(MADE_MSG)$(NAME)$(WHT)"
ifeq ($(WITH_BONUS),true)
	@echo "$(WHT1)   added   $(GRN1)ft_printf$(WHT)"
endif

norme:
	@echo "$(DRK)$(BLU1)\n\t$(NAME)$(WHT)\n"
	@$(NORME)

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Creating bindir and objects                                                                                       |#
#+----------------------------------------------------------------------------------------------------------------------+#

$(BIN):
	@mkdir $(BIN)
	@printf "$(MADE_MSG) %-42s$(WHT)\r" $@

$(BIN)/%.o: %.c $(HEAD) | $(BIN)
	@$(CC) -I./ $< -c $(CF) -o $@
	@printf "   Adding $(DRK)$(GRN) %-42s$(WHT)\r" "$@..."

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Trash removal rules                                                                                               |#
#+----------------------------------------------------------------------------------------------------------------------+#

clean:
	@if test -d $(BIN); \
	then rm -rfvd $(BIN) $(REPLACE); \
	echo "\n$(DEL_MSG).o files$(WHT)"; \
	fi

fclean: clean
	@if test -f $(NAME); \
	then rm -rfv ./$(NAME) $(REPLACE); \
	rm -rf a.out; \
	echo "$(DEL_MSG)$(NAME)$(WHT)"; \
	fi

re: fclean all
