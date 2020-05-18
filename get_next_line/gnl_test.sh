#!/bin/sh

#
#	I test gnl for some checklist test cases.
#	Just run me or redirect me to file with './gnl_test >> filename'
#

if [ "$1" = "BONUS" ]; then
	GNL="get_next_line_bonus.c get_next_line_utils_bonus.c"
else
	GNL="get_next_line.c get_next_line_utils.c"
fi
FLAGS="-g -Wall -Werror -Wextra"
DIFF=$(diff test.txt out)

if test -f diff.txt
	then rm diff.txt
fi

echo "= Small Buffer ==================================================="
echo "\$> gcc $FLAGS $GNL main.c -D BUFFER_SIZE=1-4\n"
for (( i=1; i<=4 ; i++ ))
do gcc $FLAGS $GNL main.c -D BUFFER_SIZE=$i
	echo "=Buffer size is $i==================================================="
	./a.out	> out
	if [ "$DIFF" == "" ]
		then echo "\nDiff OK! :D"
		else echo "\nbuffer $i\n" >> diff.txt; diff test.txt out >> diff.txt; echo "\nDiff KO :("
	fi
done

echo "= Medium  Buffer ==================================================="
echo "\$> gcc $FLAGS $GNL main.c -D BUFFER_SIZE=8-64\n"
for (( i=8; i<=64; i+=8 ))
do gcc $FLAGS $GNL main.c -D BUFFER_SIZE=$i
	echo "=Buffer size is $i==================================================="
	./a.out	> out
	if [ "$DIFF" == "" ]
		then echo "\nDiff OK! :D"
		else echo "\nbuffer $i\n" >> diff.txt; diff test.txt out >> diff.txt; echo "\nDiff KO :(\n"
	fi
done

echo "= Large    Buffer ==================================================="
echo "\$> gcc $FLAGS $GNL main.c -D BUFFER_SIZE=4096-8192\n"
for (( i=4096; i<=8192; i+=1024 ))
do gcc $FLAGS $GNL main.c -D BUFFER_SIZE=$i
	echo "=Buffer size is $i==================================================="
	./a.out	> out
	if [ "$DIFF" == "" ]
		then echo "\nDiff OK! :D"
		else echo "\nbuffer $i\n" >> diff.txt; diff test.txt out >> diff.txt; echo "Diff KO :(\n"
	fi
done
echo "======================================================================="

echo "Your static variables are:"
cat *.c | grep 'static'