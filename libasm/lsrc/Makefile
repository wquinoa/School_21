# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/07 04:54:12 by wquinoa           #+#    #+#              #
#    Updated: 2020/07/09 19:43:11 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_lst_sort.c

OBJ		= $(SRCS:c=o)
DEP		= $(SRCS:c=d)

NAME = libtest.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $^

%.o: %.c
	@gcc -c $< -o $@

clean:
	@rm -rf $(OBJ) $(DEP)

fclean: clean
	@rm -rf $(NAME)

re: fclean all