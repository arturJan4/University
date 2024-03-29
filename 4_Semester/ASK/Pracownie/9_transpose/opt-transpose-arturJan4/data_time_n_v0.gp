set title "Czas wykonywania w zależności od rozmiaru tablicy (BLOCK = 8)"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (n)"
set ylabel "Czas wykonywania w sekundach"

# set xrange [0:32264]
plot "data_time_n_v0.dat" using 1:2 with linespoints lw 2 title "transpose0", \

# vim: ft=gnuplot
