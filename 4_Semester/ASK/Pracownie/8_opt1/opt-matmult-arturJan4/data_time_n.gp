set title "Czas wykonywania w zależności od rozmiaru tablicy"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (n)"
set ylabel "Czas wykonywania w sekundach"

set xrange [0:2048]
plot "data_time_n.dat" using 1:2 with linespoints smooth csplines lw 2 title "ijk", \
     "data_time_n.dat" using 1:3 with linespoints smooth csplines lw 2 title "kij", \
     "data_time_n.dat" using 1:4 with linespoints smooth csplines lw 2 title "jki", \
     "data_time_n.dat" using 1:5 with linespoints smooth csplines lw 2 title "BLOCK", \

# vim: ft=gnuplot
