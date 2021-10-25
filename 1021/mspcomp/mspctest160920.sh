#/bin/bash
#source ${d1}/f1234.dat;
fr=${d1}/mspcresult.dat; cat /dev/null > $fr
if [ "$NM" = "" ]; then NM=10 ; fi  #NM=10; ##maximam ??
if [ "$tS" = "" ] ; then tS="tS:0.01"; fi
if [ "$uI" = "" ] ; then uI="uI:0:0.8:5"; fi
if [ "$RI" = "" ] ; then RI="RI:1:0.05"; fi
fstos=${d1}/stos.dat; cat /dev/null > $fstos
if [ "$fS" = "" ]; then fS="f1 f2 f12 f3 f4 f34" ; fi
if [ "$DISP" = "" ]; then DISP=0 ; fi
if [ "$stab" = "" ]; then stab="-1,-1,-1,2" ; fi

for fn in `echo $fS`; do
if [ $fn = f1 ];  then ff=$f1;NN=$N1;echo -n "## BestST\n">>$fr; fi
if [ $fn = f2 ];  then ff=$f2;NN=$N2; fi
if [ $fn = f12 ]; then ff=$f1:$f2;NN=$N1:$N2; fi
if [ $fn = f21 ]; then ff=$f2:$f1;NN=$N2:$N1; fi
if [ $fn = f3 ];  then ff=$f3;NN=$N3;echo -n "## BestOS\n">>$fr; fi
if [ $fn = f4 ];  then ff=$f4;NN=$N4; fi
if [ $fn = f34 ]; then ff=$f3:$f4;NN=$N3:$N4; fi
if [ $fn = f43 ]; then ff=$f4:$f3;NN=$N4:$N3; fi
if [ $fn = f5 ];  then ff=$f5;NN=$N5; fi
if [ $fn = f35 ]; then ff=$f3:$f5;NN=$N3:$N5; fi
if [ $fn = f345 ]; then ff=$f3:$f4:$f5;NN=$N3:$N4:$N5; fi
if [ $fn = f354 ]; then ff=$f3:$f5:$f6;NN=$N3:$N5:$N4; fi
echo -n "$fn ">>$fr; 

cat /dev/null> listSS.dat;
cr=2;
if [ "$cmS1" = "" ]; then cmS1="10 15 20 25 30 35 40 45 50" ; fi
for cm in `echo $cmS1`; do 
  if [ "$DISP" = "1" ]; then dr=tmp/m${cm}${fn};mkdir -p $dr; fi
#for cm in 10 15 20 25 30 35 40 45 50; do 
echo -n "$cr $cm ">>listSS.dat
cmd="emulate_crane4 it:1:1 r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 $umax tt:$tt kxt:1 method:12:$NM:$b:$a:${seed}:${ff} N:${NN} DISP:$DISP listSS:1 T:100 N2s:12 LAMBDA:0.01 $uI $RI $tS stab:$stab"
echo "#Exec mspctest160920.sh:L36 $cmd in ";$cmd
cp t-AP_i.dat tmp/t-AP_i-m${cm}${fn}.dat
if [ "$DISP" = "1" ]; then cp y.plt $dr/; cp _y.dat $dr/ ; fi
done;#done for cm
cat listSS.dat;cat listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#%.2f(%.2f %.2f %.2f) %.1f(%.1f %.1f %.1f) #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}' >> $fr
#if [ $ff = $f3 ];  then cat listSS.dat >> $fr; fi
echo "#${fn}=$ff" >> $fstos
cat listSS.dat >> $fstos
done;#for ff
#echo "# ${d1}/f12345.dat";cat ${d1}/f12345.dat
echo "# $fr";cat $fr
echo "#Detailed st and os are viewed by emacs $fstos."
