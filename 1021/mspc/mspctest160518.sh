#/bin/bash
#source ${d1}/f1234.dat;
fr=${d1}/mspcresult.dat; cat /dev/null > $fr
f12=$f1:$f2:
f34=$f3:$f4;
NM=10; ##maximam ??
fstos=${d1}/stos.dat; cat /dev/null > $fstos
if [ "$tS" = "" ] ; then tS="tS:0.01"; fi
if [ "$LAMBDA" = "" ] ; then LAMBDA="LAMBDA:0.01"; fi
if [ "$fS" = "" ]; then fS="f1 f2 f12 f3 f4 f34" ; fi
if [ "$seed" = "" ] ; then seed=0; fi
if [ "$DISP" = "" ]; then DISP=0 ; fi
for fn in `echo $fS`; do
if [ $fn = f1 ];  then ff=$f1;NN=$N1;echo -n "## BestST\nf1  ">>$fr; fi
if [ $fn = f2 ];  then ff=$f2;NN=$N2;echo -n "f2  ">>$fr; fi
if [ $fn = f12 ]; then ff=$f12;NN=$N1:$N2;echo -n "f12 ">>$fr; fi
if [ $fn = f3 ];  then ff=$f3;NN=$N3;echo -n "## BestOS\nf3  ">>$fr; fi
if [ $fn = f4 ];  then ff=$f4;NN=$N4;echo -n "f4  ">>$fr; fi
if [ $fn = f34 ]; then ff=$f34;NN=$N3:$N4;echo -n "f34 ">>$fr; fi

#for ff in $f1 $f2 $f12 $f3 $f4 $f34; do
#if [ $ff = $f1 ];  then NN=$N1;fn="f1";echo -n -e "## BestST\nf1  ">>$fr; fi
#if [ $ff = $f2 ];  then NN=$N2;fn="f2";echo -n "f2  ">>$fr; fi
#if [ $ff = $f12 ]; then NN=$N1:$N2;fn="f12";echo -n "f12 ">>$fr; fi
#if [ $ff = $f3 ];  then NN=$N3;fn="f3";echo -n -e "## BestOS\nf3  ">>$fr; fi
#if [ $ff = $f4 ];  then NN=$N4;fn="f4";echo -n "f4  ">>$fr; fi
#if [ $ff = $f34 ]; then NN=$N3:$N4;fn="f34";echo -n "f34 ">>$fr; fi
cat /dev/null> listSS.dat;
cr=2;
_T0=`date +%s`
if [ "$cmS1" = "" ]; then cmS1="10 15 20 25 30 35 40 45 50" ; fi
for cm in `echo $cmS1`; do 
#for cm in 10 15 20 25 30 35 40 45 50; do 
echo -n "$cr $cm ">>listSS.dat
cmd="emulate_crane4 it:1:1 r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 umax:10 tt:$tt kxt:1 method:12:$NM:$b:$a:${seed}:${ff} N:${NN} DISP:$DISP listSS:1 T:100 N2s:12 $LAMBDA $tS"
#cmd="emulate_crane4 it:1:1 r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 umax:10 tt:$tt kxt:1 method:12:$NM:$b:$a:0:${ff} N:${NN} DISP:$DISP listSS:1 T:100 N2s:12 $LAMBDA $tS"
echo "#mspctest160518.sh:L34 Doing $cmd";$cmd
cp t-AP_i.dat tmp/t-AP_i-m${cm}${fn}.dat
done;#done for cm
cat listSS.dat;cat listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#%.2f(%.2f %.2f %.2f) %.1f(%.1f %.1f %.1f) #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}' >> $fr
#if [ $ff = $f3 ];  then cat listSS.dat >> $fr; fi
echo "#${fn}=$ff" >> $fstos
cat listSS.dat >> $fstos
done;#for ff
echo "#d1=${d1};cat \${d1}/f1234.dat";cat ${d1}/f1234.dat
echo "#d1=${d1};fr=$fr";cat $fr
echo "#Detailed st and os are viewed by emacs $fstos."
_T1=`date +%s`
_DT=$((_T1 - _T0))
_H=$((_DT / 3600 ))
_DT=$((_DT % 3600 ))
_M=$((_DT / 60 ))
_S=$((_DT % 60))
echo "#Elapsed time to test=${_H}:${_M}:${_S}"

