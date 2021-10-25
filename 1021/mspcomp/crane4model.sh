#
#d0=../result-mspc2; if [ ! -e $d0 ]; then mkdir $d0;fi
b=1;a=0.7;tt=1000;it=1;it2=1   #change for Exp.No.2
#b=1;a=0.7;tt=100;it=10;
d1=${d0}/a${a}b${b}tt${tt}; if [ ! -e $d1 ]; then mkdir $d1;fi
f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
###
#ny=4;nu=4;sed -e s/"AP_ny "/"AP_ny ${ny}\/\/"/ -e s/"AP_nu "/"AP_nu ${nu}\/\/"/ $f1 > $f0 ; make CC=icc   ##1st trial
###
###
mkdir -p tmp
cat /dev/null > listSS.dat
cat /dev/null > tmp/M.dat
if [ "$uI" = "" ] ; then uI="uI:0:0.8:5"; fi
if [ "$RI" = "" ] ; then RI="RI:1:0.05"; fi
for N in 1; do                    #Activate at Exp.No.1
#for N in 5 10 15 20 25 30; do #active initially
#for N in 5 10 15 20 25 30 35 40 45 50; do #active initially
#do once to here
#for I in 1; do #No.1
for cm in `echo $cmS`; do #No.1
#for I in 75 80 85 90 95; do 
#original
#cm=$I;
#if [ "$I" = 1 ]; then cm=10; fi 
#if [ "$I" = 2 ]; then cm=40; fi
#if [ "$I" = 3 ]; then cm=70; fi
#if [ "$I" = 4 ]; then cm=100; fi
cmd="emulate_crane4 it:${it}:${it2} r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 umax:10 $uI tt:$tt kxt:1 method:12:${N}:${b}:${a}:0 DISP:1 listSS:1 T:100 N2s:12 LAMBDA:0.01 $RI"; #change for Exp.No.2
#cmd="emulate_crane4 it:${it}:${it2} r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 umax:10 tt:$tt kxt:1 method:12:${N}:${b}:${a}:0 DISP:1 listSS:1 T:100 N2s:12 LAMBDA:0.01 RI:1:0.05"; #change for Exp.No.2
date;echo "Executing $cmd";time $cmd;date
cp -r result-ensrs2ge/net* ${d1}/ #cp -r result-ensrs2ge/net* ${d1}/
#cat listSS.dat >> listSS.txt
done; #for I
done  #for N active initially

###for cm in 10N 40N 70N 100; do export M=10000 #Exp.No.1
####for cm in 10N 40N 70N 100; do export M=100   #Exp.No.3
####for cm in 75N 80N 85N 90N 95N; do
###export q="cr2cm${cm}";
###cmd1=`cat listSS.dat|awk 'BEGIN {vm=1e9;l=0;q=ENVIRON["q"];} {l++;p=substr($8,1,8);if($1>0 && p==q){v=$2+$1*0.01; if(v<vm) {vm=v;i=l}}} END {printf("head -%d listSS.dat",i)}'`;echo -n "#TrueModel: ";$cmd1 | tail -1;
###done
