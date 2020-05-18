#!/bin/sh

#
#	I test gnl for some checklist test cases.
#	Just run me or redirect me to file with './gnl_test >> filename'
#
rm diff.txt

echo "---------| Small Buffer |----------\n\n"
for i in $(seq 1 4)
do gcc -g get_next_line.c get_next_line_utils.c main.c -D BUFFER_SIZE=$i
	echo "=Buffer size is $i===================="
	./a.out	> out
	DIFF=$(diff test.txt out)
	if [ "$DIFF" == "" ]
		then echo "Diff OK! :D\n"
		else echo "\nbuffer $i\n" >> diff.txt; diff test.txt out >> diff.txt; echo "Diff KO :(\n"
	fi
done

echo "---------| Medium  Buffer |----------\n\n"
for (( c=8; c<=64; c+=8 ))
do gcc -g get_next_line.c get_next_line_utils.c main.c -D BUFFER_SIZE=$c
	echo "=Buffer size is $c===================="
	./a.out	> out
	DIFF=$(diff test.txt out)
	if [ "$DIFF" == "" ]
		then echo "Diff OK! :D\n"
		else echo "\nbuffer $i\n" >> diff.txt; diff test.txt out >> diff.txt; echo "Diff KO :(\n"
	fi
done

echo "---------| Large    Buffer |----------\n"
gcc -g get_next_line.c get_next_line_utils.c main.c -D BUFFER_SIZE=4097
./a.out	> out
DIFF=$(diff test.txt out)
if [ "$DIFF" == "" ]
	then echo "Diff OK! :D\n"
	else diff test.txt out
fi