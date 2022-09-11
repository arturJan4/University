set title "Czas wykonywania w zależności od rozmiaru tablicy i liczby kroków (steps)"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (2^n)"
set ylabel "Czas wykonywania w sekundach"

set xrange [1:16]
plot "data_time_n.dat" using 1:2 with linespoints lw 2 title "steps=64", \
     "data_time_n.dat" using 1:3 with linespoints lw 2 title "steps=512", \
     "data_time_n.dat" using 1:4 with linespoints lw 2 title "steps=4096", \

# vim: ft=gnuplot