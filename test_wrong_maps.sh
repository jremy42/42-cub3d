#!/bin/bash

MAP_DIR="$1"
VALGRIND="valgrind"
#VALGRIND=""

test "$#" -ne 1 && echo "1 and only 1 arg needed !" && exit 1

for i in $(ls ${MAP_DIR}/**/*)
do
	echo -e "\e[32mTesting [$i]\e[0m"
	OUTPUT=$($VALGRIND ./cub3d $i 2>&1)
	RET=$?
	echo "$OUTPUT"
	test "$RET" -lt 128 || echo -e "\e[31mSIGNALED on [$i]\e[0m"
	test "$(echo $OUTPUT | grep "Error" | wc -l)" -ne 0 || echo -e "\e[31mMissing an error on [$i]\e[0m"
done
echo "End of test"
