set term postscript;set output "y.eps"
plot "t_yp_y.txt" using 1:2 w l t "yp", "" using 1:3 w l t "y", "" using 1:($2-$3) w l t "err=yp-y"
