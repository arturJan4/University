#!/bin/bash
g++ sortuj.cpp -o a.out
echo "n Bubble-Sort STL-sort" > testy.csv
for i in {1..1001..10}
	do	
		VAR=$(./a.out $i)
		echo "$VAR" >> testy.csv
#		./a.out $i
	done
rm ./a.out

gnuplot -p wykres.gp
gnuplot -p wykresLog2.gp
