set title "% Miss Rate w L1 w zależności od rozmiaru macierzy (n) dla poszczególnych BLOCK"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (n)"
set ylabel "Miss Rate L1 (%)"

set key autotitle columnhead

set xrange [0:8192]
plot "data_block_l1_n.dat" using 1:4 with linespoints lw 2, \
     "data_block_l1_n.dat" using 1:5 with linespoints lw 2, \
     "data_block_l1_n.dat" using 1:6 with linespoints lw 2, \
     "data_block_l1_n.dat" using 1:7 with linespoints lw 2, \

