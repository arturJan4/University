set title "IPC w zależności od n dla poszczególnych wariantów binsearch"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (2^n)"
set ylabel "IPC"

set key autotitle columnhead

set xrange [15:25]
plot "data_ipc_combined.dat" using 1:2 with linespoints title "binsearch0" lw 2, \
     "data_ipc_combined.dat" using 1:3 with linespoints title "binsearch1 (var 0)" lw 2, \
     "data_ipc_combined.dat" using 1:4 with linespoints title "binsearch1 (var 1)" lw 2, \
     "data_ipc_combined.dat" using 1:5 with linespoints title "binsearch1 (var 2)" lw 2, \