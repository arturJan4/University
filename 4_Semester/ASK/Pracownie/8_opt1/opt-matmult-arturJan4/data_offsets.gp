set title "Czas wykonywania w zależności od offsetu: (Reverse)"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (n)"
set ylabel "Czas wykonywania w sekundach"

set xrange [0:1024]
plot "data_offsets.dat" using 2:3 with linespoints lw 2 title "ijk", \
     "data_offsets.dat" using 2:4 with linespoints lw 2 title "kij", \
     "data_offsets.dat" using 2:5 with linespoints lw 2 title "jki", \
     "data_offsets.dat" using 2:6 with linespoints lw 2 title "BLOCK", \

# vim: ft=gnuplot
