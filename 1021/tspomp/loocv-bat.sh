#!/bin/bash
###
#export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc;mkdir -p $d00
if [ "$ddc" = "" ]; then export ddc=../../chaos.data; fi
if [ "$fbc" = "" ]; then export fbc=lorenz1e-8T0.025n10000p256m1_gmp; fi
if [ "$d00" = "" ]; then export d00=../../result-chaospred; mkdir -p $d00; fi
export d0=$d00/$fbc;mkdir -p $d0
echo -e "\n\$d0=$d0"
#(2-0)
##Nの設定
export mbam=${m}:${b}:${a}:${mc}
export D=k${k}N${N}ns${ns}m${m}b${b}a${a}
export fHg=$d0/${D}Hg.dat 
cat /dev/null > $fHg
export date0=`date`
export T0=`date +%s`
for TP0 in $TP0S; do
export Sth=0.5 phase="" #TP0="2000"  
if [ "$k" = "" ]; then export k=10; fi
if [ "$ID" = "" ]; then export ID=" "; fi
if [ "$msg" = "" ]; then export msg=" "; fi
#export N=N:50,60,70,80,90,100 n_seed=17 
#export N=N:50-100:10 n_seed=17 
#export N=N:50-100:5 n_seed=9
#export N=N:50-150:20 n_seed=17 
#(2-1)&(2-2)
date >> $d0/cmd-io-sum.dat
cmd="python loocv-predhorizon.py -ddc $ddc -fbc $fbc -d00 $d00 -N $N -mbam $mbam -Sth $Sth -ns $ns -TP0 $TP0 -k $k"
echo $cmd;$cmd
grep "#t0-" $d0/cmd.out >> $fHg
grep "#t0-" $d0/cmd.out |grep "(ncmax"
#python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -ns "$ns" -TP0 "$TP0" -phase "$phase" -ID "$ID" -msg "$msg"
#python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -ns "$ns" -TP0 "$TP0" -phase "$phase" -k $k
source $d0/d1.env #d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1-5
echo "#saved in export d1=$d1" >> $d0/cmd-io-sum.dat
tail -2 $d1/cmd.sh >> $d0/cmd-io-sum.dat
cp $d1/cmd.out $d1/cmd-Sth${Sth:2}.out
#export LANG=C;DATE=`date`;echo "#$DATE TP0=$TP0 $N ns=$ns ==>(hV,hg)=(,) $msg" >> $d0/cmd-io-sum.dat
stdbuf -o0 grep "Hgmax\|Results2" $d1/cmd.out |sort >> $d0/cmd-io-sum.dat
#stdbuf -o0 grep "hi-LOOCV@L0c\|hi-LOOCV@L2c\|h(yi,yg)@L0c\|Hgmax\|Results2" $d1/cmd.out |sort >> $d0/cmd-io-sum.dat
tail -11 $d0/cmd-io-sum.dat
done
export fHgo=$d0/${D}Hgn.dat key="(ncmax" 
grep $key $fHg > tmp/tmp1.dat
cat tmp/tmp1.dat |awk 'BEGIN{D=ENVIRON["D"];key=ENVIRON["key"];hg=hoL0=hoL1=hoL2=E0=E1=E2=n=0}{n++;hg+=$1;hoL0+=$2;hoL1+=$3;hoL2+=$4;E0+=$5;E1+=$6;E2+=$7;}END{printf("# %.1f %.1f %.1f %.1f %.5g %.5g %.5g %d %s %s)#mean Hgmax,Hgo0,1,2,E0,1,2\n",hg/n,hoL0/n,hoL1/n,hoL2/n,E0/n,E1/n,E2/n,n,D,key);}'> $fHgo
cat tmp/tmp1.dat >> $fHgo
head -1 $fHgo
export T1=`date +%s`
export DT=$((T1 - T0))
export H=$((DT / 3600 ))
export DT=$((DT % 3600 ))
export M=$((DT / 60 ))
export S=$((DT % 60))
export date2=`date`
export LANG=C; echo "Elapsed Time=${H}:${M}:${S} (${date0} - ${date2})"
