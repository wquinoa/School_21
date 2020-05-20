#!/bin/sh

gcc ft_printf.c $1 -L. -lft libft/ft_putnbr_base.c -Wall -Werror -Wextra
./a.out |cat -e
