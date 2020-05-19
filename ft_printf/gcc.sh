#!/bin/sh

gcc ft_printf.c $1 -L. -lft 
./a.out |cat -e
