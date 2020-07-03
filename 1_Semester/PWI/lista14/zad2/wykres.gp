set terminal qt
set title "Czas działania algorytmów sortowania"
set ylabel "Czas[ms]"
set xlabel "n elementów"
set key left center
set xrange[1:1000]
set key autotitle columnhead
plot 'testy.csv' using 1:2 with lines, '' using 1:3 with lines

