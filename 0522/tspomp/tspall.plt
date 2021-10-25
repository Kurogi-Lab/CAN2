set nokey;set style data lines
plot "tspall.dat" using ($1):3 lt 1 lc rgb "black" t "y^N50"
pause -1 "hit return to quit."

set term tgif;set output "tspall.obj";replot
