#一個のtermianlを開いて、8行目や11行目を実行する。it1からit4の値を訓練の結果に調べること。
#---------------------------------------実行方法　1----------------------------------------
#give up the debug information.

#CAN2Str=ST or CAN2Str=OS
#model="nonlinear" or #model="linear"

#use best ST CAN2 to control
#model="nonlinear";CAN2Str=ST;ky=4;ku=4;b=1;a=0;N1=20;N2=20;N3=20;N4=20;it1=37;it2=66;it3=23;it4=38;crcmTrainRange="2 10 2 100 10 10 10 100";crControlRange="2 3 4 5 6 7 8 9 10";cmControlRange="10 20 30 40 50 60 70 80 90 100";mspcDir=~/sotuicc/201315/mspc/;mailAddress="ko@kurolab2.cntl.kyutech.ac.jp";doPlot="yesno";kyoyou=0.1;itblock=2;tt=100;r=5;T=100;umax=10;cC=0.5;ck=10;AP_TS1=0.5;N2s=12;printalldata="yesno";nohup sh ./ControlUsingBestSTOrOSCAN2v14.sh $CAN2Str $ky $ku $b $a ${N1} $it1 ${N2} $it2 ${N3} $it3 ${N4} $it4 "$crcmTrainRange" "$crControlRange" "$cmControlRange" $mspcDir $mailAddress $doPlot $kyoyou $itblock $tt $r $T $umax $cC $ck $AP_TS1 $N2s $printalldata $model 1> ./ControlBy_${CAN2Str}.ky=${ky}.ku=${ku}.b=$b.a=$a.N1=${N1}.it1=${it1}.N2=${N2}.it2=${it2}.N3=${N3}.it3=${it3}.N4=${N4}.it4=${it4}.crcmTrain=${crcmTrainRange// /_}.crRange=${crControlRange// /_}.cmRange=${cmControlRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.ck=$ck.AP_TS1=$AP_TS1.N2s=$N2s.txt 2>&1 &

#use best OS CAN2 to control
#model="nonlinear";CAN2Str=OS;ky=4;ku=4;b=1;a=0;N1=20;N2=20;N3=20;N4=20;it1=37;it2=66;it3=23;it4=38;crcmTrainRange="2 10 2 100 10 10 10 100";crControlRange="2 3 4 5 6 7 8 9 10";cmControlRange="10 20 30 40 50 60 70 80 90 100";mspcDir=~/sotuicc/201314/mspc/;mailAddress="ko@kurolab2.cntl.kyutech.ac.jp";doPlot="yesno";kyoyou=0.1;itblock=2;tt=100;r=5;T=100;umax=10;cC=0.5;ck=10;AP_TS1=0.5;N2s=12;printalldata="yesno";nohup sh ./ControlUsingBestSTOrOSCAN2v14.sh $CAN2Str $ky $ku $b $a ${N1} $it1 ${N2} $it2 ${N3} $it3 ${N4} $it4 "$crcmTrainRange" "$crControlRange" "$cmControlRange" $mspcDir $mailAddress $doPlot $kyoyou $itblock $tt $r $T $umax $cC $ck $AP_TS1 $N2s $printalldata $model 1> ./ControlBy_${CAN2Str}.ky=${ky}.ku=${ku}.b=$b.a=$a.N1=${N1}.it1=${it1}.N2=${N2}.it2=${it2}.N3=${N3}.it3=${it3}.N4=${N4}.it4=${it4}.crcmTrain=${crcmTrainRange// /_}.crRange=${crControlRange// /_}.cmRange=${cmControlRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.ck=$ck.AP_TS1=$AP_TS1.N2s=$N2s.txt 2>&1 &

#-------------------------------------------------------------------------------
#use "jobs" or "ps aux | grep ControlUsingBest" command to see the status of linux jobs.

#Parameter Comment

#CAN2Str
#ky
#ku
#b
#a
#N1
#it1
#N2
#it2
#N3
#it3
#N4
#it4
#crcmTrainRange
#crControlRange
#cmControlRange
#mspcDir
#mailAddress
#doPlot
#kyoyou
#itblock : it is used to select the trained can2, different to the "1" in "emulate_crane2 it:1:1".
#tt
#r
#T

##code

CAN2Str=$1
ky=$2
ku=$3
b=$4
a=$5
N1=$6
it1=$7
N2=$8
it2=${9}
N3=${10}
it3=${11}
N4=${12}
it4=${13}
crcmTrainRange=(${14})
crControlRange="${15}"
cmControlRange="${16}"
mspcDir=${17}
mailAddress=${18}
doPlot=${19}
kyoyou=${20}
itblock=${21}
tt=${22}
r=${23}
T=${24}
umax=${25}
cC=${26}
ck=${27}
AP_TS1=${28} #define AP_TS1 0.5 //virtual sampling period
N2s=${29}
printalldata=${30}
model=${31}

parameterString="b=${b}.a=${a}.N1=${N1}.it1=${it1}.N2=${N2}.it2=${it2}.N3=${N3}.it3=${it3}.N4=${N4}.it4=${it4}.ky=${ky}.ku=${ku}.crcmTrain=${crcmTrainRange[0]}_${crcmTrainRange[1]}_${crcmTrainRange[2]}_${crcmTrainRange[3]}_${crcmTrainRange[4]}_${crcmTrainRange[5]}_${crcmTrainRange[6]}_${crcmTrainRange[7]}.crRange=${crControlRange// /_}.cmRange=${cmControlRange// /_}.kyoyou=$kyoyou.itblock=${itblock}.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.ck=$ck.AP_TS1=$AP_TS1.N2s=$N2s"

#goto mspc dir
cd $mspcDir

#使うCAN２のフォルダpathの定義
#d=../../result-mspc/a${a}b${b}tt${tt}
#d=../../result-mspc/a${a}b${b}tt100
d=../../result-mspc/a${a}b${b}tt${tt}${model}
f1=$d/net_cr${crcmTrainRange[0]}cm${crcmTrainRange[1]}N${N1}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it1}
f2=$d/net_cr${crcmTrainRange[2]}cm${crcmTrainRange[3]}N${N2}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it2}
f3=$d/net_cr${crcmTrainRange[4]}cm${crcmTrainRange[5]}N${N3}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it3}
f4=$d/net_cr${crcmTrainRange[6]}cm${crcmTrainRange[7]}N${N4}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it4}



#check the mspcDir have not been used.
mspcDirUsed=`ps aux|grep "ControlUsingBestSTOrOSCAN2.*""${mspcDir}"|grep -c -v "grep"`
if [ ${mspcDirUsed} -gt 2 ]
then
	echo "Error,this mspc dir have be used!"
	echo -e `ps aux|grep "ControlUsingBestSTOrOSCAN2.*""${mspcDir}"|grep -v "grep"`|mail -s "Error,this mspc dir have be used! change the mspc dir! ""parameter=$parameterString" $mailAddress
	exit 1
fi

#do plot or no 
if [ "$doPlot" != "yes" ]
then
	DISP=0
else
	DISP=1
fi

doCompile=0
#check the ky
if
	grep "#define AP_ny ""$ky" apc_crane.c
then
	echo "ky is right in the apc_crane.c"
else
	echo "will change [#define AP_ny] to right value in the apc_crane.c."
	sed -i -e s/"#define AP_ny "/"#define AP_ny ${ky}\/\/"/ apc_crane.c
	doCompile=1
fi
#check the ku
if
	grep "#define AP_nu ""$ku" apc_crane.c
then
	echo "ku is right in the apc_crane.c"
else
	echo "will change [#define AP_nu] to right value in the apc_crane.c."
	sed -i -e s/"#define AP_nu "/"#define AP_nu ${ku}\/\/"/ apc_crane.c
	doCompile=1
fi

#check the AP_TS1
if
	grep "#define AP_TS1 ""$AP_TS1" apc_crane.c
then
	echo "AP_TS1 is right in the apc_crane.c"
else
	echo "will change [#define AP_TS1] to right value in the apc_crane.c."
	sed -i -e s/"#define AP_TS1 "/"#define AP_TS1 ${AP_TS1}\/\/"/ apc_crane.c
	doCompile=1
fi

#printalldata or no 
if [ "$printalldata" = "yes" ]
then
	if grep "int debug=1" emulate_crane.c
	then
		echo "int debug=1,dots in emulate_crane.c"
	else
		echo "will change to int debug=1,dots in emulate_crane.c"
		sed -i -e s/"int debug="/"int debug=1;\/\/"/ emulate_crane.c
		sed -i -e s/"set style data lines"/"set style data dots"/ emulate_crane.c
		doCompile=1
	fi
else
	if grep "int debug=0" emulate_crane.c
	then
		echo "int debug=0,lines in emulate_crane.c"
	else
		echo "will change to int debug=0,lines in emulate_crane.c"
		sed -i -e s/"int debug="/"int debug=0;\/\/"/ emulate_crane.c
		sed -i -e s/"set style data dots"/"set style data lines"/ emulate_crane.c
		doCompile=1
	fi
fi

#change apc_crane.c and make again
if [ $doCompile = 1 ]
then
	make CC=icc
fi

#1
rm listSS.dat
ydatFileNum=1
for cr in $crControlRange; do for cm in $cmControlRange; do
echo -n "$cr $cm ">>listSS.dat
if [ "$model" = "nonlinear" ]
then
	emulate_crane2 it:1:1 r:$r cr:$cr cm:$cm cC:$cC umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f1 N:${N1} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
if [ "$model" = "linear" ]
then
	emulate_crane4 it:1:1 r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f1 N:${N1} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
#cp y.dat "y-can2f1-No"$ydatFileNum"-"$cr"-"$cm".dat"
cp y.dat "y-can2f1"${model}${CAN2Str}"Control-parameter-"$cr"-"$cm".dat"
let ydatFileNum++
done;done
cp listSS.dat listSS1.dat
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f1"
#結果を統計する。
cmd=`grep -v '^.*\s.*\s-1\.0' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#{%.2f}{%.2f} {%.2f} {%.2f} {%.1f}{%.1f} {%.1f} {%.1f} #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^.*\s.*\s-1\.0' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result1="$cmd"" #fail #""${cmd2}"
echo "This is the mark row 1."
#2
rm listSS.dat
ydatFileNum=1
for cr in $crControlRange; do for cm in $cmControlRange; do
echo -n "$cr $cm ">>listSS.dat
if [ "$model" = "nonlinear" ]
then
	emulate_crane2 it:1:1 r:$r cr:$cr cm:$cm cC:$cC umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f2 N:${N2} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
if [ "$model" = "linear" ]
then
	emulate_crane4 it:1:1 r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f2 N:${N2} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
#cp y.dat "y-can2f2-No"$ydatFileNum"-"$cr"-"$cm".dat"
cp y.dat "y-can2f2"${model}${CAN2Str}"Control-parameter-"$cr"-"$cm".dat"
let ydatFileNum++
done;done
cp listSS.dat listSS2.dat
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f2"
#結果を統計する。
cmd=`grep -v '^.*\s.*\s-1\.0' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#{%.2f}{%.2f} {%.2f} {%.2f} {%.1f}{%.1f} {%.1f} {%.1f} #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^.*\s.*\s-1\.0' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result2="$cmd"" #fail #""${cmd2}"
echo "This is the mark row 2."
#3
rm listSS.dat
ydatFileNum=1
for cr in $crControlRange; do for cm in $cmControlRange; do
echo -n "$cr $cm ">>listSS.dat
if [ "$model" = "nonlinear" ]
then
	emulate_crane2 it:1:1 r:$r cr:$cr cm:$cm cC:$cC umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f3 N:${N3} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
if [ "$model" = "linear" ]
then
	emulate_crane4 it:1:1 r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f3 N:${N3} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
#cp y.dat "y-can2f3-No"$ydatFileNum"-"$cr"-"$cm".dat"
cp y.dat "y-can2f3"${model}${CAN2Str}"Control-parameter-"$cr"-"$cm".dat"
let ydatFileNum++
done;done
cp listSS.dat listSS3.dat
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f3"
#結果を統計する。
cmd=`grep -v '^.*\s.*\s-1\.0' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#{%.2f}{%.2f} {%.2f} {%.2f} {%.1f}{%.1f} {%.1f} {%.1f} #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^.*\s.*\s-1\.0' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result3="$cmd"" #fail #""${cmd2}"
echo "This is the mark row 3."
#4
rm listSS.dat
ydatFileNum=1
for cr in $crControlRange; do for cm in $cmControlRange; do
echo -n "$cr $cm ">>listSS.dat
if [ "$model" = "nonlinear" ]
then
	emulate_crane2 it:1:1 r:$r cr:$cr cm:$cm cC:$cC umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f4 N:${N4} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
if [ "$model" = "linear" ]
then
	emulate_crane4 it:1:1 r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f4 N:${N4} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
#cp y.dat "y-can2f4-No"$ydatFileNum"-"$cr"-"$cm".dat"
cp y.dat "y-can2f4"${model}${CAN2Str}"Control-parameter-"$cr"-"$cm".dat"
let ydatFileNum++
done;done
cp listSS.dat listSS4.dat
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f4"
#結果を統計する。
cmd=`grep -v '^.*\s.*\s-1\.0' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#{%.2f}{%.2f} {%.2f} {%.2f} {%.1f}{%.1f} {%.1f} {%.1f} #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^.*\s.*\s-1\.0' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result4="$cmd"" #fail #""${cmd2}"
echo "This is the mark row 4."
#all
rm listSS.dat
ydatFileNum=1
for cr in $crControlRange; do for cm in $cmControlRange; do
echo -n "$cr $cm ">>listSS.dat
if [ "$model" = "nonlinear" ]
then
	emulate_crane2 it:1:1 r:$r cr:$cr cm:$cm cC:$cC umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f1:$f2:$f3:$f4 N:${N1}:${N2}:${N3}:${N4} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
if [ "$model" = "linear" ]
then
	emulate_crane4 it:1:1 r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:$N1:$b:$a:0:$f1:$f2:$f3:$f4 N:${N1}:${N2}:${N3}:${N4} DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
#cp y.dat "y-can2f1f2f3f4-No"$ydatFileNum"-"$cr"-"$cm".dat"
cp y.dat "y-can2f1f2f3f4"${model}${CAN2Str}"Control-parameter-"$cr"-"$cm".dat"
let ydatFileNum++
done;done
cp listSS.dat listSS1234.dat
cat listSS.dat
echo "Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by 4 CAN2s which are f1,f2,f3,f4"
#結果を統計する。
cmd=`grep -v '^.*\s.*\s-1\.0' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#{%.2f}{%.2f} {%.2f} {%.2f} {%.1f}{%.1f} {%.1f} {%.1f} #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^.*\s.*\s-1\.0' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result1234="$cmd"" #fail #""${cmd2}"
echo "This is the mark row 5."
#create the result string
allresult="Use best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f1\n $result1 \nUse best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f2\n $result2 \nUse best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f3\n $result3 \nUse best ${CAN2Str} CAN2 to control,b=$b,a=$a, by only one CAN2 which is f4\n $result4 \nUse best ${CAN2Str} CAN2 to control,b=$b,a=$a, by 4 CAN2s which are f1,f2,f3,f4\n $result1234"
allresult="$allresult \n\nlistSS1.dat\n`cat listSS1.dat`"
allresult="$allresult \nlistSS2.dat\n`cat listSS2.dat`"
allresult="$allresult \nlistSS3.dat\n`cat listSS3.dat`"
allresult="$allresult \nlistSS4.dat\n`cat listSS4.dat`"
allresult="$allresult \nlistSS1234.dat\n`cat listSS1234.dat`"
echo -n -e "$allresult"
#
if [ "$mailAddress" != "" ]
then
echo -e -n "$allresult"|mail -s "Use best ""${CAN2Str}"" CAN2s to control,parameter>>""${parameterString}" $mailAddress
#echo -e -n "$allresult"|mutt -s "Use best ""${CAN2Str}"" CAN2s to control,parameter>>""${parameterString}" $mailAddress -a listSS1.dat -a listSS2.dat -a listSS3.dat -a listSS4.dat -a listSS1234.dat
fi