# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/07 23:33:20 by wquinoa           #+#    #+#              #
#    Updated: 2020/07/31 13:51:19 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#|    Source files
EXTR :=			ft_atoi.c			ft_calloc.c			ft_itoa.c			ft_swap.c			get_next_line.c

TO_IS :=		ft_isalnum.c		ft_isalpha.c		ft_isascii.c		ft_isdigit.c		ft_isprint.c			\
				ft_isspace.c		ft_tolower.c		ft_toupper.c

MEM :=			ft_bzero.c			ft_memccpy.c		ft_memchr.c			ft_memcmp.c			ft_memcpy.c				\
				ft_memmove.c		ft_memset.c

STRING :=		ft_split.c			ft_strchr.c			ft_strdup.c			ft_strjoin.c		ft_strlcat.c			\
				ft_strlcpy.c		ft_strlen.c			ft_strmapi.c		ft_strncmp.c		ft_strnstr.c			\
				ft_strrchr.c		ft_strtrim.c		ft_substr.c			ft_strcmp.c			ft_strjoin_3.c			\
				ft_del.c

PRINT :=		ft_fput.c			ft_putchar_fd.c		ft_putendl_fd.c		ft_putnbr_fd.c		ft_putstr_fd.c			\
				ft_put.c

LISTS :=		ft_lstadd_back.c	ft_lstadd_front.c	ft_lstclear.c		ft_lstdelone.c		ft_lstiter.c			\
				ft_lstlast.c		ft_lstmap.c			ft_lstnew.c			ft_lstsize.c

BTREE :=		prefix_infix_suffix.c tree_create_node.c tree_insert_data.c tree_search.c

TAB :=			ft_tabclear.c		ft_tablen.c			ft_tabmap.c

BSRCS :=		ft_math.c			ft_print.c			ft_printf.c			ft_putnbr_basep.c


#|    Utilities
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
NORME = norminette $(SRCS) $(BSRCS) *.h | awk '{sub(/Norme/,"$(GRN)Norme$(WHT)")}1' | awk '{sub(/Error/,"$(RED)Error$(WHT)")}1'

#|    Good stuff
NAME = libft.a
BIN = ./obj

SRCS =	$(addprefix ft_to_is/, $(TO_IS))	$(addprefix extr/, $(EXTR)) \
		$(addprefix ft_lists/, $(LISTS))	$(addprefix ft_print/, $(PRINT)) \
		$(addprefix ft_tab/, $(TAB))		$(addprefix ft_mem/, $(MEM)) \
		$(addprefix ft_string/, $(STRING))	$(addprefix ft_btree/, $(BTREE))
B_FILES = $(addprefix ft_printf/src/, $(BSRCS))
HEAD =	$(NAME:a=h)
OBJ =	$(SRC:c=o) $(TO_IS:c=o) $(MEM:c=o) \
		$(STRING:c=o) $(LISTS:c=o) $(PRINT:c=o) \
		$(TAB:c=o) $(EXTR:c=o) $(BTREE:c=o)
BOBJ =	$(B_FILES:c=o)
DEP =	$(OBJ_FILES:o=d)
CC =	gcc
CF =	-Wall -Wextra -Werror
.PHONY: all bonus clean fclean re
vpath %c extr  ft_btree  ft_lists  ft_mem  ft_print  ft_printf/src  ft_string  ft_tab  ft_to_is

#|    Conditionals
#$(VERBOSE).SILENT:
#.ONESHELL:
ifdef WITH_BONUS
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ)) $(addprefix $(BIN)/, $(BSRCS:c=o))
else
OBJ_FILES = $(addprefix $(BIN)/, $(OBJ))
endif

#|    Targets / rules
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

#|    Creating bindir and objects
$(BIN):
	@mkdir $(BIN)
	@printf "$(MADE_MSG) %-42s$(WHT)\r" $@

-include $(DEP)
$(BIN)/%.o: %.c | $(BIN)
	@$(CC) -I./ $< -c $(CF) -o $@
	@printf "   Adding $(DRK)$(GRN) %-42s$(WHT)\r" "$@..."

#|    Trash removal rules
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
