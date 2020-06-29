# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/17 21:10:46 by wquinoa           #+#    #+#              #
#    Updated: 2020/06/29 12:00:27 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Source files                                                                                                      |#
#+----------------------------------------------------------------------------------------------------------------------+#

SRCS :=			ft_init2.c			ft_sprites.c		\
				ft_minimap.c		ft_castndraw.c		\
				ft_read_map.c		ft_add_sprite.c		\
				ft_keys.c			bmp.c				\
				ft_paint.c			ft_texncol.c		\
				ft_errors.c			ft_mapval.c			\
				draw_untextured.c

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Utilities                                                                                                         |#
#+----------------------------------------------------------------------------------------------------------------------+#
#
#																			#
WHT		= \033[0m#															#
GRN		= \033[32m#															#
RED		= \033[31m#															#
WHT1	= \033[0;1m#														#
GRN1	= \033[32;1m#														#
RED1	= \033[31;1m#														#
DRK		= \033[2m#															#
MADE_MSG = \n	$(WHT1)Created $(GRN1)#										#
SELF_MSG = \t$(DRK)by wquinoa#												#
DEL_MSG = \n	$(WHT1)Removed $(DRK)$(RED1)#								#
ERROR_MSG = "\n	$(WHT1)$(DRK)Nothing to $@\n"#								#
#																			#
REPLACE =  2>&1| awk '{sub(/.\//,"  $(WHT) $(DRK)removed $(RED)")}1'
#
#+----------------------------------------------------------------------------------------------------------------------+#
#|    Good stuff                                                                                                        |#
#+----------------------------------------------------------------------------------------------------------------------+#

NAME		= libcub3d.a

BIN			= ./.obj
SRC_DIR		= ./src
INCL_DIR	= ./includes

HEAD		:= cub3d.h
OBJ			:= $(SRCS:c=o)
BOBJ		:= $(BSRCS:c=o)

INCLUDES	:= $(addprefix $(INCL_DIR)/, $(HEAD))
OBJ_FILES	:= $(addprefix $(BIN)/, $(OBJ))
SRC_FILES	:= $(addprefix $(SRC_DIR)/, $(SRCS))

CC			= gcc
CF			= -Wall -Wextra -Werror -O2

.PHONY: run, libs, clean, clibs, fclean, fclibs, re
#+----------------------------------------------------------------------------------------------------------------------+#
#|    Rules                                                                                                             |#
#+----------------------------------------------------------------------------------------------------------------------+#

all: $(NAME)
	@echo "$(SELF_MSG)"

$(NAME): $(OBJ_FILES) | libs
	@ar rcs $(NAME) $^
	@echo "$(MADE_MSG)cub3d$(WHT)\n"
	@$(CC) $(CF) main.c -L. -lcub3d -lft -lmlx -framework OpenGL -framework AppKit -o cub3d

run: $(NAME)
	@./cub3d map.cub

libs:
	@cd libft && make bonus
	@cp libft/libft.a libft.a
	@cd minilibx_mms && make
	@cp minilibx_mms/libmlx.dylib .

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Creating bindir and objects                                                                                       |#
#+----------------------------------------------------------------------------------------------------------------------+#

$(BIN):
	@mkdir $(BIN)
	@echo "$(MADE_MSG) $@$(WHT)\n"

$(BIN)/%.o: $(SRC_DIR)/%.c $(INCLUDES) | $(BIN)
	@$(CC) -I$(INCLUDES) $< -c $(CF) -o $@
	@echo "   Adding $(DRK)$(GRN)$@...$(WHT)"

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Trash removal rules                                                                                               |#
#+----------------------------------------------------------------------------------------------------------------------+#

clean: clibs
	@if test -d $(BIN); \
	then rm -rfvd $(BIN) $(REPLACE) && rm libft.a libmlx.dylib; \
	echo "$(DEL_MSG).o files$(WHT)\n"; \
	else echo $(ERROR_MSG); \
	fi

clibs:
	@cd minilibx_mms && make clean
	@cd libft && make clean

fclean: clean | fclibs
	@rm -rfv cub3d 2>&1 | awk '{sub(cub3d, "  $(WHT) $(DRK)removed $(RED)")}1'
	@rm -rf scr.bmp
	@if test -f $(NAME); \
	then rm -rfv ./$(NAME) $(REPLACE); \
	echo "$(DEL_MSG) cub3d$(WHT)\n"; \
	else echo $(ERROR_MSG); \
	fi

fclibs:
	@cd libft && make fclean

re: fclean all
