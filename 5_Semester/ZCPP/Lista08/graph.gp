set title "Gamma(0.5, x) values"

set terminal pngcairo size 1024,768 enhanced font 'Arial,12'

set output "critical_strip.png"

set xlabel "imaginary part"
set ylabel "value"

set grid
plot "results.csv" using 1:2 with lines lw 1 title "Real", \
     "results.csv" using 1:3 with lines lw 1 title "Imaginary"