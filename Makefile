# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/07 23:33:20 by wquinoa           #+#    #+#              #
#    Updated: 2020/05/08 03:54:41 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

BSRCS :=			ft_lstadd_back.c			\
				ft_lstadd_front.c			\
				ft_lstclear.c				\
				ft_lstdelone.c				\
				ft_lstiter.c				\
				ft_lstlast.c				\
				ft_lstmap.c					\
				ft_lstnew.c					\
				ft_lstsize.c				\
				ft_abs_bonus.c				\
				ft_isspace_bonus.c			\
				ft_join_bonus.c				\
				ft_max_bonus.c				\
				ft_min_bonus.c				\
				ft_nlen_bonus.c				\
				ft_strjoin_dlm_bonus.c		\
				ft_tabclear_bonus.c			\
				ft_tablen_bonus.c			\
				ft_tabmap_bonus.c

NAME = libft.a
OBJ = $(SRCS:c=o)
BOBJ = $(BSRCS:c=o)
CC = gcc
CF = -Wall -Wextra -Werror

all: $(NAME)

ifdef WITH_BONUS
OBJ_FILES = $(OBJ) $(BOBJ)
else
OBJ_FILES = $(OBJ)
endif

bonus:
	@$(MAKE) 'WITH_BONUS = true' all
	@echo "		  ...and \033[32mbonus\n"


$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)
	@ranlib $(NAME)
	@echo "\n	Made your \033[32mlib\n"

%.o: %.c
	$(CC) $^ -c -Wall -Werror -Wextra -o $@

clean:
	@rm -rf $(OBJ) $(BOBJ)
	@echo "\n	No more .o\033[32m files\n"

fclean: clean
	@rm -rf $(NAME)
	@echo "		   ...and  \033[32mlib\n"

re: fclean all
	@echo "\n	Remade your \033[32mlib\n"
