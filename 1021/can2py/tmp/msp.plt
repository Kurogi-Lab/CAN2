set grid;set title "Recursive MultiStep Pred: T=100 N=50 seed=10 Tpinv=-1 H=159(Ey15)"
set term postscript eps enhanced color;set output "tmp/msp.eps"
plot "tmp/msp2000.dat" using 2:3 w l t "y","" using 2:1 w l t "yp", "" using 2:($1-$3) w l t "yp-y"
