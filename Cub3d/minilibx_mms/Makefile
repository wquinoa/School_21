
MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3

NAME=libmlx.dylib

INC=-I.
#OPTI=-Ounchecked
WHT		= \033[0m#															#
GRN		= \033[32m#															#
RED		= \033[31m#															#
WHT1	= \033[0;1m#														#
GRN1	= \033[32;1m#														#
RED1	= \033[31;1m#														#
DRK		= \033[2m#															#

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	@swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz
	@echo "   Adding $(DRK)$(GRN)$@...$(WHT)"

%.o: %.swift
	@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@
	@echo "   Adding $(DRK)$(GRN)$@...$(WHT)"

%.swiftmodule: %.swift
	@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)
	@echo "   Adding $(DRK)$(GRN)$@...$(WHT)"

clean:
	@rm -fv $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~ 2>&1| awk '{sub(/mlx/,"  $(WHT) $(DRK)removed $(RED) mlx")}1'
	@echo "\n"

