set title "Czas wykonywania (n - 4096) w zależności od rozmiaru bloku"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar bloku (BLOCK)"
set ylabel "Czas wykonywania w sekundach"

set xrange [0:512]
plot "data_blocks.dat" using 1:2 with linespoints lw 2 notitle
# vim: ft=gnuplot
