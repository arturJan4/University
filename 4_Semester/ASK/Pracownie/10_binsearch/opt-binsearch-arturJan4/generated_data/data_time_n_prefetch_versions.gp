set title "Czas wykonywania w zależności od rozmiaru tablicy i wersji prefetch"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (2^n)"
set ylabel "Czas wykonywania w sekundach"

set key autotitle columnhead

set xrange [1:25]
plot "data_time_n_prefetch_versions.dat" using 1:2 with linespoints lw 2, \
     "data_time_n_prefetch_versions.dat" using 1:3 with linespoints lw 2, \
     "data_time_n_prefetch_versions.dat" using 1:4 with linespoints lw 2, \
     "data_time_n_prefetch_versions.dat" using 1:5 with linespoints lw 2, \
     "data_time_n_prefetch_versions.dat" using 1:6 with linespoints lw 2, \
     
# vim: ft=gnuplot