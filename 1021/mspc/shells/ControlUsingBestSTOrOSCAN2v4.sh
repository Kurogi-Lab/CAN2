#一個のtermianlを開いて、8行目や11行目を実行する。it1からit4の値を訓練の結果に調べること。
#---------------------------------------実行方法　1----------------------------------------
#write debug information to another file.

#CAN2Str=ST or CAN2Str=OS

#use best OS CAN2 to control
#b=1;N=20;a=0;mspcDir=~/sotuicc/2012a/mspc/;CAN2Str=OS;it1=10;it2=6;it3=15;it4=12;mailAddress="youname@kurolab2.cntl.kyutech.ac.jp";ky=4;ku=4;doPlot="yesno";itblock=2;nohup sh ./ControlUsingBestSTOrOSCAN2v4.sh $b $N $a $mspcDir $CAN2Str $it1 $it2 $it3 $it4 $mailAddress $ky $ku $doPlot $itblock 1> ./ControlUsingBest_${CAN2Str}_CAN2.result.b=$b.a=$a.N=${N}.ky=${ky}.ku=${ku}.itblock=$itblock.txt 2> ./ControlUsingBest_${CAN2Str}_CAN2.debugResult.b=$b.a=$a.N=${N}.ky=${ky}.ku=${ku}.itblock=$itblock.txt &

#use best ST CAN2 to control
#b=1;N=20;a=0;mspcDir=~/sotuicc/2012a/mspc/;CAN2Str=ST;it1=10;it2=6;it3=15;it4=12;mailAddress="youname@kurolab2.cntl.kyutech.ac.jp";ky=4;ku=4;doPlot="yesno";itblock=2;nohup sh ./ControlUsingBestSTOrOSCAN2v4.sh $b $N $a $mspcDir $CAN2Str $it1 $it2 $it3 $it4 $mailAddress $ky $ku $doPlot $itblock 1> ./ControlUsingBest_${CAN2Str}_CAN2.result.b=$b.a=$a.N=${N}.ky=${ky}.ku=${ku}.itblock=$itblock.txt 2> ./ControlUsingBest_${CAN2Str}_CAN2.debugResult.b=$b.a=$a.N=${N}.ky=${ky}.ku=${ku}.itblock=$itblock.txt &
#---------------------------------------実行方法　2----------------------------------------
#write result and debug information to one file

#CAN2Str=ST or CAN2Str=OS

#use best OS CAN2 to control
#b=1;N=20;a=0;mspcDir=~/sotuicc/2012a/mspc/;CAN2Str=OS;it1=10;it2=6;it3=15;it4=12;mailAddress="youname@kurolab2.cntl.kyutech.ac.jp";ky=4;ku=4;doPlot="yesno";itblock=2;nohup sh ./ControlUsingBestSTOrOSCAN2v4.sh $b $N $a $mspcDir $CAN2Str $it1 $it2 $it3 $it4 $mailAddress $ky $ku $doPlot $itblock 1> ./ControlUsingBest_${CAN2Str}_CAN2.result.b=$b.a=$a.N=${N}.ky=${ky}.ku=${ku}.itblock=$itblock.txt 2>&1 &

#use best ST CAN2 to control
#b=1;N=20;a=0;mspcDir=~/sotuicc/2012a/mspc/;CAN2Str=ST;it1=10;it2=6;it3=15;it4=12;mailAddress="youname@kurolab2.cntl.kyutech.ac.jp";ky=4;ku=4;doPlot="yesno";itblock=2;nohup sh ./ControlUsingBestSTOrOSCAN2v4.sh $b $N $a $mspcDir $CAN2Str $it1 $it2 $it3 $it4 $mailAddress $ky $ku $doPlot $itblock 1> ./ControlUsingBest_${CAN2Str}_CAN2.result.b=$b.a=$a.N=${N}.ky=${ky}.ku=${ku}.itblock=$itblock.txt 2>&1 &
#-------------------------------------------------------------------------------
#use "jobs" command to see the status of linux jobs.

##code

cd $4 #goto mspc dir
b=$1;N=$2;a=$3
CAN2Str=$5
it1=${6}
it2=${7}
it3=${8}
it4=${9}
mailAddress=${10}
ky=${11}
ku=${12}
doPlot="${13}"
itblock=${14}
d=../../mspcdata/result/b${b}a${a}_7e
f1=$d/net_cr2cm10N${N}ny${ky}nu${ku}iti${itblock}IS2r5T100it${it1}
f2=$d/net_cr2cm100N${N}ny${ky}nu${ku}iti${itblock}IS2r5T100it${it2}
f3=$d/net_cr10cm10N${N}ny${ky}nu${ku}iti${itblock}IS2r5T100it${it3}
f4=$d/net_cr10cm100N${N}ny${ky}nu${ku}iti${itblock}IS2r5T100it${it4}

#do plot or no 
if [ "$doPlot" != "yes" ]
then
	DISP=0
else
	DISP=1
fi

changeApc_crane=0
#check the ky
if
	grep "#define AP_ny ""$ky" apc_crane.c
then
	echo "ky is right in the apc_crane.c"
else
	echo "will change [#define AP_ny] to right value in the apc_crane.c."
	changeApc_crane=1
fi
#check the ku
if
	grep "#define AP_nu ""$ku" apc_crane.c
then
	echo "ku is right in the apc_crane.c"
else
	echo "will change [#define AP_nu] to right value in the apc_crane.c."
	changeApc_crane=1
fi

#change apc_crane.c and make again
if [ $changeApc_crane = 1 ]
then
	sed -i -e s/"#define AP_ny "/"#define AP_ny ${ky}\/\/"/ -e s/"#define AP_nu "/"#define AP_nu ${ku}\/\/"/  apc_crane.c
	make
fi

#1
rm listSS.dat
for cr in 2 3 4 5 6 7 8 9 10; do for cm in 10 20 30 40 50 60 70 80 90 100; do
echo -n "$cr $cm ">>listSS.dat
emulate_crane2 it:1:1 r:5 cr:$cr cm:$cm cC:0.5 umax:10 tt:100 kxt:1 method:12:$N:$b:$a:0:$f1 DISP:${DISP} listSS:1 T:100 N2s:12 LAMBDA:0.01
done;done
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f1"
#90個の結果を統計する。
cmd=`grep -v '^-1' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#%.2f(%.2f %.2f %.2f) %.1f(%.1f %.1f %.1f) #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^-1' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result1="$cmd"" #fail #""${cmd2}"
echo "This is the mark row."
#2
rm listSS.dat
for cr in 2 3 4 5 6 7 8 9 10; do for cm in 10 20 30 40 50 60 70 80 90 100; do
echo -n "$cr $cm ">>listSS.dat
emulate_crane2 it:1:1 r:5 cr:$cr cm:$cm cC:0.5 umax:10 tt:100 kxt:1 method:12:$N:$b:$a:0:$f2 DISP:${DISP} listSS:1 T:100 N2s:12 LAMBDA:0.01
done;done
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f2"
#90個の結果を統計する。
cmd=`grep -v '^-1' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#%.2f(%.2f %.2f %.2f) %.1f(%.1f %.1f %.1f) #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^-1' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result2="$cmd"" #fail #""${cmd2}"
echo "This is the mark row."
#3
rm listSS.dat
for cr in 2 3 4 5 6 7 8 9 10; do for cm in 10 20 30 40 50 60 70 80 90 100; do
echo -n "$cr $cm ">>listSS.dat
emulate_crane2 it:1:1 r:5 cr:$cr cm:$cm cC:0.5 umax:10 tt:100 kxt:1 method:12:$N:$b:$a:0:$f3 DISP:${DISP} listSS:1 T:100 N2s:12 LAMBDA:0.01
done;done
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f3"
#90個の結果を統計する。
cmd=`grep -v '^-1' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#%.2f(%.2f %.2f %.2f) %.1f(%.1f %.1f %.1f) #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^-1' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result3="$cmd"" #fail #""${cmd2}"
echo "This is the mark row."
#4
rm listSS.dat
for cr in 2 3 4 5 6 7 8 9 10; do for cm in 10 20 30 40 50 60 70 80 90 100; do
echo -n "$cr $cm ">>listSS.dat
emulate_crane2 it:1:1 r:5 cr:$cr cm:$cm cC:0.5 umax:10 tt:100 kxt:1 method:12:$N:$b:$a:0:$f4 DISP:${DISP} listSS:1 T:100 N2s:12 LAMBDA:0.01
done;done
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f4"
#90個の結果を統計する。
cmd=`grep -v '^-1' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#%.2f(%.2f %.2f %.2f) %.1f(%.1f %.1f %.1f) #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^-1' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result4="$cmd"" #fail #""${cmd2}"
echo "This is the mark row."
#all
rm listSS.dat
for cr in 2 3 4 5 6 7 8 9 10; do for cm in 10 20 30 40 50 60 70 80 90 100; do
echo -n "$cr $cm ">>listSS.dat
emulate_crane2 it:1:1 r:5 cr:$cr cm:$cm cC:0.5 umax:10 tt:100 kxt:1 method:12:$N:$b:$a:0:$f1:$f2:$f3:$f4 DISP:${DISP} listSS:1 T:100 N2s:12 LAMBDA:0.01
done;done
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by 4 CAN2s which are f1,f2,f3,f4"
#90個の結果を統計する。
cmd=`grep -v '^-1' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#%.2f(%.2f %.2f %.2f) %.1f(%.1f %.1f %.1f) #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^-1' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result1234="$cmd"" #fail #""${cmd2}"
echo "This is the mark row."
#create the result string
allresult="Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f1\n $result1 \nUse best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f2\n $result2 \nUse best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f3\n $result3 \nUse best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f4\n $result4 \nUse best ${CAN2Str} CAN2 to control,b=$b,a=$a, by 4 CAN2s which are f1,f2,f3,f4\n $result1234"
echo -n -e "$allresult"
#
if [ "$mailAddress" != "" ]
then
echo -e -n "$allresult"|mail -s "Use best ""${CAN2Str}"" CAN2s to control,b=$b,a=$a" $mailAddress
fi
