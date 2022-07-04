#!/bin/bash

MAP_DIR="$1"

test "$#" -ne 1 && echo "Missing directory" && exit 1

for i in `ls ${MAP_DIR}`
do
	echo "Testing [$MAP_DIR/$i]"
	OUTPUT=$(valgrind ./cub3d $MAP_DIR/$i 2>&1)
	RET=$?
	echo "$OUTPUT"
	test "$RET" -lt 128 || echo -e "\e[31mSIGNALED on [$i]\e[0m"
	test "$(echo $OUTPUT | grep "Error" | wc -l)" -ne 0 || echo -e "\e[31mMissing an error on [$i]\e[0m"
done
echo "End of test"
