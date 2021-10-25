d0=../result-mspc2-8; if [ ! -e $d0 ]; then mkdir $d0;fi
b=1;a=0.7;tt=100;it=10
d1=${d0}/a${a}b${b}tt${tt}; if [ ! -e $d1 ]; then mkdir $d1;fi
f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
if [ "$update" ]; then
ny=4;nu=4;sed -e s/"AP_ny "/"AP_ny ${ny}\/\/"/ -e s/"AP_nu "/"AP_nu ${nu}\/\/"/ $f1 > $f0 ; make CC=icc   ##1st trial
fi
cat /dev/null > listSS.dat
###
for N in `echo $NN`; do #active initially
#for N in 5 10; do #active initially
#for N in 5 10 15 20 25 30; do #active initially
for cm in 10 50; do #No.3
cmd="emulate_crane4 it:${it}:2 r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 umax:10 tt:$tt kxt:1 method:12:${N}:${b}:${a}:0 DISP:0 listSS:1 T:100 N2s:12 LAMBDA:0.01"
date;echo "Executing $cmd";time $cmd;date
mv result-ensrs2ge/net* ${d1}/ #cp -r result-ensrs2ge/net* ${d1}/
done; #for I
done  #for N active initially
for cm3 in 10N 50N; do export M=5000 #Exp.No.3
export q="cr2cm${cm3}";
cmd1=`cat listSS.dat|awk 'BEGIN {vm=1e9;l=0;q=ENVIRON["q"];} {l++;p=substr($8,1,8);if($1>0 && p==q){v=$2+$1*0.01; if(v<vm) {vm=v;i=l}}} END {printf("head -%d listSS.dat\n",i)}'`;echo -n "#BestOS+0.01ST: ";
$cmd1 | tail -1;
cmd2=`cat listSS.dat|awk 'BEGIN {vm=1e9;l=0;q=ENVIRON["q"];M=ENVIRON["M"];} {l++;p=substr($8,1,8);if($1>0 && p==q && $2<M) {v=$1+0.01*$2; if(v<vm) {vm=v;i=l}}} END {printf("head %d listSS.dat\n",-i)}'`;echo -n "#BestST+0.01OS: ";
$cmd2 | tail -1
done
