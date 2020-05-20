#!/bin/sh

gcc ft_printf.c $1 -L. -lft src/ft_putnbr_base.c -Wall -Werror -Wextra
./a.out |cat -e
