cat $0
tt=50;
b=1;
#a=0.7;r=5;it0=100;it1=2;it=${it0}:${it1};T=100
a=0.7;r=5;it0=20;it1=2;it=${it0}:${it1};T=100
#for I in 5 6 7 8; do 
#for I in 1 2 3 4; do 
for I in 1; do 
#for b=1
if [ "$b" = 1 ]; then
#for bestST b1
if [ "$I" = 1 ]; then cr=2; cm=10; N=20; fi
if [ "$I" = 2 ]; then cr=2; cm=100; N=30; fi
if [ "$I" = 3 ]; then cr=10; cm=10;N=20; fi
if [ "$I" = 4 ]; then cr=10; cm=100; N=8; fi
#for bestOS b1
if [ "$I" = 5 ]; then cr=2; cm=10; N=30; fi 
if [ "$I" = 6 ]; then cr=2; cm=100; N=20; fi
if [ "$I" = 7 ]; then cr=10; cm=10;N=10; fi
if [ "$I" = 8 ]; then cr=10; cm=100; N=6; fi
else #if [ "$b" = "10" ]; then
#for bestST
if [ "$I" = 1 ]; then cr=2; cm=10; N=30; fi
if [ "$I" = 2 ]; then cr=2; cm=100; N=20; fi
if [ "$I" = 3 ]; then cr=10; cm=10;N=6; fi
if [ "$I" = 4 ]; then cr=10; cm=100; N=8; fi
#for bestOS
if [ "$I" = 5 ]; then cr=2; cm=10; N=20; fi
if [ "$I" = 6 ]; then cr=2; cm=100; N=30; fi
if [ "$I" = 7 ]; then cr=10; cm=10;N=20; fi
if [ "$I" = 8 ]; then cr=10; cm=100; N=8; fi #same for bestST
fi
rm listSS.dat; 
cmd="emulate_crane2 it:${it} r:${r} cr:${cr} cm:${cm} cC:0.5 umax:10 tt:$tt kxt:1 method:12:${N}:${b}:${a}:0 DISP:0 listSS:1 T:100 N2s:12 LAMBDA:0.01"
make data-clean;date;echo "Executing $cmd";time $cmd;date
d0=../result-mspc; if [ ! -e $d0 ]; then mkdir $d0;fi
d1=${d0}/a${a}b${b}tt${tt}; if [ ! -e $d1 ]; then mkdir $d1;fi
mv result-ensrs2ge/net* ${d1}/
#listSS="${d1}/net_cr${cr}cm${cm}N${N}ny4nu4iti${it1}IS2r${r}T${T}it${it0}/listSS.dat";cp $listSS listSS.dat
cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9} {if($1>0) {v=$2+$1*0.01; if(v<vm) {vm=v;i=$3+1}}} END {printf("head %d listSS.dat",-i)}'`;echo -n "#BestOS+0.01ST: ";$cmd | tail -1;cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9} {if($1>0) {v=$1+0.01*$2; if(v<vm) {vm=v;i=$3+1}}} END {printf("head %d listSS.dat",-i)}'`;echo -n "#BestST+0.01OS: ";$cmd | tail -1
cat listSS.dat
done; 
