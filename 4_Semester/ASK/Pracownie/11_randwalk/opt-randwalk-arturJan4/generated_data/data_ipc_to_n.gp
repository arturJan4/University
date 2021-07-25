set title "IPC w zależności od n dla poszczególnych wariantów randwalk"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (2^n)"
set ylabel "IPC"

set key autotitle columnhead

set xrange [0:15]
plot "data_ipc_to_n.dat" using 1:2 with linespoints title "randwalk0" lw 2, \
     "data_ipc_to_n.dat" using 1:3 with linespoints title "randwalk1" lw 2, \