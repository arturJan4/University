set terminal qt
set datafile separator ";"
set auto x
set yrange[0:12]
set title "Logika dla informatyków: prognoza ocen"
set key autotitle columnheader
set linetype  1 lc rgb "#009E73" 
set linetype  2 lc rgb "#56B4E9" 
set linetype  3 lc rgb "#E69F00" 
set linetype  4 lc rgb "#F0E442" 
set linetype  5 lc rgb "#0072B2" 
set linetype  6 lc rgb "#E51E10" 
set style data histogram
set style fill solid border -1
plot for [i=2:i=7] 'logika_prognoza.csv' using i:xtic(1)


