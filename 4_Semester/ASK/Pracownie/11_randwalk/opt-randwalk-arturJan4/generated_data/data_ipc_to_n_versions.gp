set title "IPC w zależności od n dla poszczególnych ułożeń instrukcji"

# set terminal postscript eps enhanced
set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set datafile separator ','
set xlabel "Rozmiar tablicy (2^n)"
set ylabel "IPC"

set key autotitle columnhead

set xrange [0:15]
plot "data_ipc_n_combined.dat" using 1:2 with linespoints title "1-2-3-4 (default)" lw 2, \
     "data_ipc_n_combined.dat" using 1:26 with linespoints title "2-1-4-3" lw 2, \
     "data_ipc_n_combined.dat" using 1:27 with linespoints title "1-3-4-2" lw 2, \
     "data_ipc_n_combined.dat" using 1:28 with linespoints title "mediana" lw 2, \