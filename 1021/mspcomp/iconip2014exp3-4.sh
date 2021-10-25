d0=../result-mspc6; #if [ ! -e $d0 ]; then mkdir $d0;fi
b=1;a=0.7;tt=100;it=10;
d1=${d0}/a${a}b${b}tt${tt}; #if [ ! -e $d1 ]; then mkdir $d1;fi
ny=4;nu=1
#f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
#sed -e s/"AP_ny "/"AP_ny ${ny}\/\/"/ -e s/"AP_nu "/"AP_nu ${nu}\/\/"/ $f1 > $f0 ; make CC=icc   ##1st trial
N1=15;t=8;f1=${d1}/net_cr2cm10N${N1}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 32.9  0  8 #ST[s] OS[mm] it for cr2cm10N15ny4nu1iti2IS2r5T100 
N2=10;t=2;f2=${d1}/net_cr2cm40N${N2}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 21.2  0  2 #ST[s] OS[mm] it for cr2cm40N10ny4nu1iti2IS2r5T100 
N3=10;t=9;f3=${d1}/net_cr2cm70N${N3}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 38.8  0  9 #ST[s] OS[mm] it for cr2cm70N10ny4nu1iti2IS2r5T100 f3
N4=25;t=2;f4=${d1}/net_cr2cm100N${N4}ny${ny}nu${nu}iti2IS2r5T100it${t}; #BestOS+0.01ST: 74.9  0  2 #ST[s] OS[mm] it for cr2cm100N25ny4nu1iti2IS2r5T100
N5=20;t=7;f5=${d1}/net_cr2cm90N${N5}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 32.6  0  7 #ST[s] OS[mm] it for cr2cm90N20ny4nu1iti2IS2r5T100 f5
N6=30;t=3;f6=${d1}/net_cr2cm75N${N6}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 41.9  1  3 #ST[s] OS[mm] it for cr2cm75N30ny4nu1iti2IS2r5T100
N7=50;t=2;f7=${d1}/net_cr2cm96N${N7}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 35.5  0  2 #ST[s] OS[mm] it for cr2cm96N50ny4nu1iti2IS2r5T100
N8=40;t=2;f8=${d1}/net_cr2cm98N${N8}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 42.8  0  2 #ST[s] OS[mm] it for cr2cm98N40ny4nu1iti2IS2r5T100
N9=30;t=6;f9=${d1}/net_cr2cm92N${N9}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 42.8  0  6 #ST[s] OS[mm] it for cr2cm92N30ny4nu1iti2IS2r5T100
N10=30;t=6;f10=${d1}/net_cr2cm97N${N10}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 44.8  0  6 #ST[s] OS[mm] it for cr2cm97N30ny4nu1iti2IS2r5T100 f10
##							       #	#									      
#N1=30;t=2 ;f1=${d1}/net_cr2cm10N${N1}ny${ny}nu${nu}iti2IS2r5T100it${t}; #BestST+0.01OS: 19.6 98  2 #ST[s] OS[mm] it for cr2cm10N30ny4nu1iti2IS2r5T100 
#N2=5 ;t=9 ;f2=${d1}/net_cr2cm40N${N2}ny${ny}nu${nu}iti2IS2r5T100it${t}; #BestST+0.01OS: 20.5 59  9 #ST[s] OS[mm] it for cr2cm40N5ny4nu1iti2IS2r5T100  
#N3=10;t=10;f3=${d1}/net_cr2cm70N${N3}ny${ny}nu${nu}iti2IS2r5T100it${t}; #BestST+0.01OS: 25.1 44 10 #ST[s] OS[mm] it for cr2cm70N10ny4nu1iti2IS2r5T100 
#N4=10;t=7 ;f4=${d1}/net_cr2cm100N${N4}ny${ny}nu${nu}iti2IS2r5T100it${t};#BestST+0.01OS: 28.6 94  7 #ST[s] OS[mm] it for cr2cm100N10ny4nu1iti2IS2r5T100
#ny=4;nu=4
##f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
##sed -e s/"AP_ny "/"AP_ny ${ny}\/\/"/ -e s/"AP_nu "/"AP_nu ${nu}\/\/"/ $f1 > $f0 ; make CC=icc   ##1st trial
#N1=10;t=2;f1=${d1}/net_cr2cm10N${N1}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 24.3  0  2 #ST[s] OS[mm] it for cr2cm10N10ny4nu4iti2IS2r5T100
#N2=5 ;t=6;f2=${d1}/net_cr2cm40N${N2}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 23.6  0  6 #ST[s] OS[mm] it for cr2cm40N5ny4nu4iti2IS2r5T100 
#N3=15;t=10;f3=${d1}/net_cr2cm70N${N3}ny${ny}nu${nu}iti2IS2r5T100it${t};  #BestOS+0.01ST: 37.5  0 10 #ST[s] OS[mm] it for cr2cm70N15ny4nu4iti2IS2r5T100
#N4=30;t=7;f4=${d1}/net_cr2cm100N${N4}ny${ny}nu${nu}iti2IS2r5T100it${t}; #BestOS+0.01ST: 63.1 13  7 #ST[s] OS[mm] it for cr2cm100N30ny4nu4iti2IS2r5T10
##							       #	#									     
#N1=20;t=9 ;f1=${d1}/net_cr2cm10N${N1}ny${ny}nu${nu}iti2IS2r5T100it${t}; #BestST+0.01OS: 18.0 32  9 #ST[s] OS[mm] it for cr2cm10N20ny4nu4iti2IS2r5T100
#N2=10;t=10;f2=${d1}/net_cr2cm40N${N2}ny${ny}nu${nu}iti2IS2r5T100it${t}; #BestST+0.01OS: 21.1 88 10 #ST[s] OS[mm] it for cr2cm40N10ny4nu4iti2IS2r5T100
#N3=5 ;t=7 ;f3=${d1}/net_cr2cm70N${N3}ny${ny}nu${nu}iti2IS2r5T100it${t}; #BestST+0.01OS: 23.0 42  7 #ST[s] OS[mm] it for cr2cm70N5ny4nu4iti2IS2r5T100 
#N4=5 ;t=4 ;f4=${d1}/net_cr2cm100N${N4}ny${ny}nu${nu}iti2IS2r5T100it${t};#BestST+0.01OS: 28.5 53  4 #ST[s] OS[mm] it for cr2cm100N5ny4nu4iti2IS2r5T100
#
#f1234=$f1:$f2:$f3:$f4;
#N1234=$N1:$N2:$N3:$N4;
#f1234=$f1:$f2:$f3:$f4:$f5;
#N1234=$N1:$N2:$N3:$N4:$N5;
#f1234=$f1:$f2:$f3:$f4:$f5:$f6;
#N1234=$N1:$N2:$N3:$N4:$N5:$N6;
#f1234=$f3:$f5;
#N1234=$N3:$N5;
f3510=$f3:$f5:$f10;
N3510=$N3:$N5:$N10;
####
fr=cntlresult.dat; cat /dev/null > $fr
#ky=0.1;//rr_kyoyou=0.1m=100mm default
#for ff in $f1234 ; do
for ff in $f3510 ; do
if [ "$ff" = "$f1" ]; then NN=$N1; echo -n "f1   " >> $fr; fi
if [ "$ff" = "$f2" ]; then NN=$N2; echo -n "f2   " >> $fr; fi
if [ "$ff" = "$f3" ]; then NN=$N3; echo -n "f3   " >> $fr; fi
if [ "$ff" = "$f4" ]; then NN=$N4; echo -n "f4   " >> $fr; fi
if [ "$ff" = "$f3510" ]; then NN=$N3510; echo -n "f3510" >> $fr; fi
rm listSS.dat;
cr=2;for cm in 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100; do 
echo -n "$cr $cm ">>listSS.dat
cmd="emulate_crane4 it:1:1 r:5 cr:2   cm:$cm cC:10 ck:15 ky:0.1 umax:10 tt:$tt kxt:1  method:12:$N1:$b:$a:0:${ff} N:${NN} DISP:0 listSS:1 T:100 N2s:12 LAMBDA:0.01"
echo "Doing $cmd";$cmd
done;
cat listSS.dat;cat listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#%.2f(%.2f %.2f %.2f) %.1f(%.1f %.1f %.1f) #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}' >> $fr
done;
cat $fr