#!/bin/bash
#export fnpred=$1
#export fntest=$2
if [ "$fnpred" = "" -o "fntest" = "" ]; then
  echo "Use this prog ($0) after execute 'export fnpred=<fnpred> fntest=<fntest>', where"
  echo " <fntest> has lines of 'x y', and <fnpred> has 'yp' for a function y=(x1,x2)."
  exit
fi
#export fntest=tmp/test.csv
#export fnpred=tmp/pred.txt
mkdir -p tmp
export fnpredxy=tmp/predxy.txt
export fnplt=tmp/pred.plt
export fneps=tmp/pred.eps
#export bl=`wc $fnpred |awk '{print sqrt($1)}'`
paste $fntest $fnpred | awk 'BEGIN{l=0;bl=ENVIRON["bl"];}{printf("%s %s %s\n",$1,$2,$3)}'> $fnpredxy
#paste $fntest $fnpred | awk 'BEGIN{l=0;bl=ENVIRON["bl"];}{printf("%s %s %s\n",$1,$2,$3);l++;if(l%bl==0) printf("\n");}'> $fnpredxy
#cat $fnpredxy |awk 'BEGIN{MSE=0;n=0}{e=$2-$3;MSE+=e*e;n++;}END{printf("RMSE=%e\n",sqrt(MSE/n))}'
#set term postscript eps enhanced color;set output "$fneps"
cat > $fnplt <<EOF
#set term png;set output "tmp/pred.png" #(1)
set term tgif;set output "tmp/pred.obj" #(2)
set title "T=$T N=$N seed=$seed"
set multiplot
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.9
set bmargin screen 0.5
plot "$fnpredxy" using 1:2 w l t "y", "" using 1:3 w lp pt 6 t "yp"
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.4
set bmargin screen 0.1
plot "$fnpredxy" using 1:(\$3-\$2) w l t "yp-y"
unset multiplot
quit
EOF
gnuplot $fnplt >& /dev/null
#eog -n tmp/pred.png& #color (1)
tgif -print -f -eps tmp/pred.obj>& /dev/null; gv $fneps & #black-white (2)
#plot "$fnpredxy" using 1:2 w lp pt 7 t "y", "" using 1:3 w lp pt 6 t "yp"

