set title "Cykle per iteracja w zależności od rozmiaru macierzy"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (n)"
set ylabel "Cycles per iteration"

set xrange [0:700]
plot "data_cpi_to_n.dat" using 1:2 with linespoints lw 2 title "ijk", \
     "data_cpi_to_n.dat" using 1:3 with linespoints lw 2 title "kij", \
     "data_cpi_to_n.dat" using 1:4 with linespoints lw 2 title "jki", \
     "data_cpi_to_n.dat" using 1:5 with linespoints lw 2 title "BLOCK", \

# vim: ft=gnuplot