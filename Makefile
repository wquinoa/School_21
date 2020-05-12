# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/07 23:33:20 by wquinoa           #+#    #+#              #
#    Updated: 2020/05/12 10:55:13 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colours and utility
WHT = \033[0m
GRN = \033[32m
RED = \033[31m
WHT1 = \033[0;1m
GRN1 = \033[32;1m
RED1 = \033[31;1m
DRK = \033[2m
REPLACE =  2>&1| awk '{sub(/.\//,"  $(WHT) $(DRK)removed $(RED)")}1'
MADE_MSG = \n	$(WHT1)Created $(GRN1)
DEL_MSG = \n	$(WHT1)No more $(DRK)$(RED1)
ERROR_MSG = "\n	$(WHT1)$(DRK)Nothing to $@\n"

# Source files
SRCS :=			ft_atoi.c					\
				ft_bzero.c					\
				ft_calloc.c					\
				ft_isalnum.c				\
				ft_isalpha.c				\
				ft_isascii.c				\
				ft_isdigit.c				\
				ft_isprint.c				\
				ft_itoa.c					\
				ft_memccpy.c				\
				ft_memchr.c					\
				ft_memcmp.c					\
				ft_memcpy.c					\
				ft_memmove.c				\
				ft_memset.c					\
				ft_putchar_fd.c				\
				ft_putendl_fd.c				\
				ft_putnbr_fd.c				\
				ft_putstr_fd.c				\
				ft_split.c					\
				ft_strchr.c					\
				ft_strdup.c					\
				ft_strjoin.c				\
				ft_strlcat.c				\
				ft_strlcpy.c				\
				ft_strlen.c					\
				ft_strmapi.c				\
				ft_strncmp.c				\
				ft_strnstr.c				\
				ft_strrchr.c				\
				ft_strtrim.c				\
				ft_substr.c					\
				ft_tolower.c				\
				ft_toupper.c

# Bonus files
BSRCS :=		ft_lstadd_back.c			\
				ft_lstadd_front.c			\
				ft_lstclear.c				\
				ft_lstdelone.c				\
				ft_lstiter.c				\
				ft_lstlast.c				\
				ft_lstmap.c					\
				ft_lstnew.c					\
				ft_lstsize.c				\
				ft_abs_bonus.c				\
				ft_del_bonus.c				\
				ft_isspace_bonus.c			\
				ft_join_bonus.c				\
				ft_max_bonus.c				\
				ft_min_bonus.c				\
				ft_nlen_bonus.c				\
				ft_putlst_bonus.c			\
				ft_strjoin_dlm_bonus.c		\
				ft_tabclear_bonus.c			\
				ft_tablen_bonus.c			\
				ft_tabmap_bonus.c

# Rules
NAME = ./libft.a
INCL = ./
OBJ = $(SRCS:c=o)
BOBJ = $(BSRCS:c=o)
BIN = ./bin
CC = gcc
CF = -Wall -Wextra -Werror
.PHONY: all bonus clean fclean re

# Conditional object file list
ifdef WITH_BONUS
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ) $(BOBJ))
else
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ))
endif

all: $(NAME)

bonus:
	@$(MAKE) 'WITH_BONUS = true' all
	@echo "	$(WHT1)...and $(GRN1)bonus$(WHT)\n"

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $^
	@echo "$(MADE_MSG)lib$(WHT)\n"

$(BIN):
	@mkdir $(BIN)
	@echo "$(MADE_MSG) $@$(WHT)\n"

$(BIN)/%.o: %.c | $(BIN)
	@$(CC) -I. $< -c $(CF) -o $@ 
	@echo "   Adding $(DRK)$(GRN)$@...$(WHT)"

clean:
	@if test -d $(BIN); \
	then rm -rfvd $(BIN) $(REPLACE); \
	echo "$(DEL_MSG).o files$(WHT)\n"; \
	else echo $(ERROR_MSG); \
	fi

fclean: clean
	@if test -f $(NAME); \
	then rm -rfv $(NAME) $(REPLACE); \
	echo "$(DEL_MSG) lib$(WHT)\n"; \
	else echo $(ERROR_MSG); \
	fi

so: fclean
	gcc -fPIC -c *.c
	gcc -shared -Wl,-soname,libft.so -o libft.so *.o

re: fclean all
