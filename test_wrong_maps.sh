#!/bin/bash

MAP_DIR=wrong_maps

for i in `ls ${MAP_DIR}`
do
	echo "Testing [$i]"
	echo "'Error' count : $(./cub3d $i 2>&1 | grep "Error" | wc -l)"
	test "$(./cub3d $i 2>&1 | grep "Error" | wc -l)" -ne 0 || echo -e "\e[31mMissing an error on [$i]\e[0m"
done
echo "End of test"
