#!/bin/sh

while getopts ":hbc" opt; do
	case ${opt} in
		h )
		cat *.c | grep -v 'static' | egrep '^\w+[^a-zA-Z\d]+ft_' | sed s/\)$/\)\;/
		;;
		b ) cat *bonus.c | grep -v 'static' | egrep '^\w+[^a-zA-Z\d]+ft_' | sed s/\)$/\)\;/
		;;
		c ) cat ft_*.c *.h | egrep -o '\w+\(.*\)' | tr '$' '\n' | egrep -v '(ft_|malloc|sizeof|free|write)'
			norminette ft*.c *.h | egrep -B1 '(Warning|Error)'
		;;
		\? ) echo "Usage: [-h] [-b] [-c]"
		;;
	esac
done
