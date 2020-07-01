# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/17 21:10:46 by wquinoa           #+#    #+#              #
#    Updated: 2020/07/01 16:49:49 by wquinoa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Source files                                                                                                      |#
#+----------------------------------------------------------------------------------------------------------------------+#

SRCS :=			ft_sprites.c		ft_minimap.c		ft_castndraw.c		\
				bmp.c				ft_paint.c			ft_texncol.c		\
				ft_errors.c			ft_mapval.c			ft_read_map.c		\
				ft_add_sprite.c		draw_untextured.c

BSRC :=			ft_keys_bonus.c		ft_init2_bonus.c	 ft_init_sound_bonus.c

VRBL :=			ft_keys.c			ft_init2.c

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
NORME = norminette *.c *.h | awk '{sub(/Norme/,"$(GRN)Norme$(WHT)")}1' | awk '{sub(/Error/,"$(RED)Error$(WHT)")}1'
#
#+----------------------------------------------------------------------------------------------------------------------+#
#|    Good stuff                                                                                                        |#
#+----------------------------------------------------------------------------------------------------------------------+#

NAME		= libcub3d.a

BIN			= ./.obj
SRC_DIR		= ./src
BNS_DIR		= ./bonus
INCL_DIR	= ./includes

OBJ			:= $(SRCS:c=o)
BOBJ		:= $(BSRC:c=o)
VOBJ		:= $(VRBL:c=o)

VAR_FILES	:= $(addprefix $(SRC)/, $(VSRC))
BNS_FILES	:= $(addprefix $(BNS_DIR)/, $(BSRC))

CC			= gcc
CF			= -Wall -Wextra -Werror
RUN			= ./cub3D

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Conditionals                                                                                                      |#
#+----------------------------------------------------------------------------------------------------------------------+#

ifdef WITH_BONUS
$(VERBOSE).SILENT:
SRC_FILES	:= $(addprefix $(SRC_DIR)/, $(SRCS)) $(BNS_FILES)
OBJ_FILES	:= $(addprefix $(BIN)/, $(OBJ) $(BOBJ))
INCLUDES	:= $(addprefix $(INCL_DIR)/, cub3d_bonus.h)
else
SRC_FILES	:= $(addprefix $(SRC_DIR)/, $(SRCS)) $(VAR_FILES)
OBJ_FILES	:= $(addprefix $(BIN)/, $(OBJ) $(VOBJ))
INCLUDES	:= $(addprefix $(INCL_DIR)/, cub3d.h)
endif

.PHONY: run, libs, bonus, clean, clibs, fclean, fclibs, re
#+----------------------------------------------------------------------------------------------------------------------+#
#|    Rules                                                                                                             |#
#+----------------------------------------------------------------------------------------------------------------------+#

all: $(NAME)
	@echo "$(SELF_MSG)"

bonus: $(OBJ_FILES)
	@$(MAKE) 'WITH_BONUS = true' all

$(NAME): $(OBJ_FILES) | libs
	@ar rcs $(NAME) $^
ifeq ($(WITH_BONUS),true)
	@$(CC) $(CF) main.c SDL2-A/src/audio.c -L. -lcub3d -lmlx -framework OpenGL \
	-framework AppKit `sdl2-config --cflags --libs` -D BONUS=1 -O3 -o cub3D
	@echo "	$(WHT1)$(MADE_MSG)cub3D\n	$(WHT1)    and $(GRN1)bonus$(WHT)\n"
else
	@$(CC) $(CF) main.c -L. -lcub3d -lmlx -framework OpenGL -framework AppKit -o cub3D
	@echo "$(MADE_MSG)cub3D$(WHT)\n"
endif

libs:
	@cd libft && make bonus
	@cp libft/libft.a libcub3d.a
	@cd minilibx_mms && make
	@cp minilibx_mms/libmlx.dylib .

run: bonus
	./cub3D ./bonus/map1.cub

norme:
	@echo "$(WHT1)\nlibft$(WHT)\n" && cd libft && $(NORME)
	@echo "$(WHT1)\nsrc$(WHT)\n" && cd src && $(NORME)
	@echo "$(WHT1)\nbonus$(WHT)\n" && cd bonus && $(NORME)
	@echo "$(WHT1)\nincludes$(WHT)\n" && cd includes && $(NORME)

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Creating bindir and objects                                                                                       |#
#+----------------------------------------------------------------------------------------------------------------------+#

$(BIN):
	@mkdir $(BIN)
	@echo "$(MADE_MSG) $@$(WHT)\n"

$(BIN)/%.o: */%.c $(INCLUDES) | $(BIN)
	@$(CC) -I$(INCLUDES) $< -c $(CF) -o $@
	@echo "   Adding $(DRK)$(GRN)$@...$(WHT)"

#+----------------------------------------------------------------------------------------------------------------------+#
#|    Trash removal rules                                                                                               |#
#+----------------------------------------------------------------------------------------------------------------------+#

clean: clibs
	@if test -d $(BIN); \
	then rm -rfvd $(BIN) $(REPLACE) && rm libmlx.dylib; \
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
	echo "$(DEL_MSG) cub3D$(WHT)\n"; \
	else echo $(ERROR_MSG); \
	fi

fclibs:
	@cd libft && make fclean

re: fclean all
