#!/bin/bash
####################
####making Mcs.eps from here
####################
d=$1
cd $d
#concatinate yp.csv and T.csv
cat T.csv|awk 'BEGIN{FS=","}{printf(",%s,%s,%s\n",$3,$4,$5)}'| paste yp.csv - > ypT.csv
#cat M.txt|awk 'END{print NR,NF;}' #
#gnuplot
#set xlabel "series"
#n0=0;plot for [n=n0+1:n0+10] "M.dat" using 0:n w lp pt (n+3-n0) lc rgb hsv(255-6*(n-n0),255,255) lw 1 t "1601MV-1611PV" #3101MV-3119PV
##1601MV-1611PV 1-22
##3101MV-3119PV
#行列入替
cat M.txt| awk '{for(i=1; i<=NF; i++) {a[NR,i]=$i}}NF>p{p = NF }END {for(j=1; j<=p; j++) { str=a[1,j]; for(i=2; i<=NR; i++){ str=str" "a[i,j]; } print str}}' >Mt.txt
#i,j,M[i,j]
cat M.txt| awk '{for(i=1; i<=NF; i++) {a[NR,i]=$i}}NF>p{p=NF}END{
  for(i=1; i<=NR; i++){
    for(j=1; j<=p; j++){
      printf("%d %d %s\n",i,j,a[i,j]);
    }
    printf("\n")
  }}' >Mij.txt
cat M.txt| awk '{for(i=1; i<=NF; i++) {a[NR,i]=$i}}NF>p{p=NF}END{
  for(i=1; i<=NR; i++){
    for(j=1; j<p; j++){
      printf("%d %d %s\n",i,j,a[i,j]);
    }
    printf("\n")
  }}' >Mij_.txt
#wc.sh M.txt
#M.txt 20 61  #N=20
#M.txt 100 61 #N=100
N=`rows.sh M.txt`;
C=`cols.sh M.txt`
cat > tmp.plt <<EOF
set key off
set grid
set ylabel "Mij"
set xlabel "j"
set term postscript eps enhanced color; set output "Mc.eps" #set term tgif; set output "Mc.obj"
plot [0:$C][-1:1] for [n=1:$N] "Mt.txt" using (\$0):n w lp pt (n+3) lc rgb hsv(12*(n+10),255,255) lw 1 t "1601MV-1605PV"
set xlabel "i"
set term postscript eps enhanced color; set output "Ms.eps" #set term tgif; set output "Ms.obj"
plot [0:$N][-1:1] for [n=1:$C] "M.txt" using (\$0):n w lp pt (n+3) lc rgb hsv(12*(n+10),255,255) lw 1 t "1601MV-1605PV"
set pm3d; set hidden3d
set view 38,36
set xlabel "j";
set ylabel "i";
set zlabel "Mij";
set term postscript eps enhanced color; set output "Mcs.eps" #set term tgif; set output "Msc.obj"
splot [0:$C][0:$N][-1:1] "Mij_.txt" using 2:1:3 w l
quit
EOF
gnuplot tmp.plt
#convert space to comma
for f in M Mt Mij Mij_; do
#for f in ypT T yp ysA; do
  echo "txt2csv.sh $f.txt > $f.csv"
  txt2csv.sh $f.txt > $f.csv
done
gv Mc.eps&
gv Ms.eps&
gv Mcs.eps&
cd ../../chainer
