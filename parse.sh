#!/bin/sh

while getopts ":hbc" opt; do
	case ${opt} in
		h )
		cat *.c | grep -v 'static' | egrep '^\w+[^a-zA-Z\d]+ft_' | sed s/\)$/\)\;/
		;;
		b ) cat *bonus.c | grep -v 'static' | egrep '^\w+[^a-zA-Z\d]+ft_' | sed s/\)$/\)\;/
		;;
		c ) gcc $1 -L. -lft -Wall -Werror -Wextra
		;;
		\? ) echo "Usage: [-h] [-b] [-c]"
		;;
	esac
done
