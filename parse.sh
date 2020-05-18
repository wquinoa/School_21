#!/bin/sh

while getopts ":hbc" opt; do
	case ${opt} in
		h )
		var="$(echo $2 | tr [a-z] [A-Z] | sed s/$/_H/g)"
		echo "#ifndef $var\n# define $var\n# include <stdlib.h>\n# include <unistd.h>\n" | sed 's/\($2\)/\U&/g' >> $2.h
		cat *.c | egrep -v '(main|static)' | egrep '^\w+[^a-zA-Z\d]+' | sed s/\)$/\)\;/ | sed "s/\s{1,4}/\t/g" >> $2.h
		echo "#endif\n" >> $2.h
		;;
		c ) cat ft_*.c *.h | egrep -o '\w+\(.*\)' | tr '$' '\n' | egrep -v '(ft_|malloc|sizeof|free|write)'
			norminette ft*.c *.h | egrep -B1 '(Warning|Error)'
		;;
		\? ) echo "Usage: [-h] [-b] [-c]"
		;;
	esac
done
