#set term png;set output "tmp/pred.png" #(1)
set term tgif;set output "tmp/pred.obj" #(2)
set title "T=100 N=90 seed=1"
set multiplot
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.9
set bmargin screen 0.5
plot "tmp/predxy.txt" using 1:2 w l t "y", "" using 1:3 w lp pt 6 t "yp"
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.4
set bmargin screen 0.1
plot "tmp/predxy.txt" using 1:($3-$2) w l t "yp-y"
unset multiplot
quit
