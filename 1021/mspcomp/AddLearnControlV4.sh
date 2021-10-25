#一個のtermianlを開いて、8行目を実行する。
#---------------------------------------実行方法　1----------------------------------------
#give up the debug information.


#use $ControlMeg to control

#model="nonlinear";ControlMeg=AddLearningControl;ky=40;ku=40;b=1;a=0;trainedCr_Cm_N_It="2 10 200 20 2 55 200 5 2 100 200 5 6 10 200 20 6 55 200 8 6 100 200 5 10 10 200 20 10 55 200 4 10 100 200 17";crControlRange="2 3 4 5 6 7 8 9 10";cmControlRange="10 20 30 40 50 60 70 80 90 100";mspcDir=~/sotuicc/20134/mspc/;mailAddress="ko@kurolab.cntl.kyutech.ac.jp";doPlot="yesno";kyoyou=0.1;itblock=20;tt=100;r=5;T=100;umax=10;cC=0.5;ck=0.5;AP_TS1=0.05;N2s=12;printalldata="yesno";nohup sh ./AddLearnControlV4.sh $ControlMeg $ky $ku $b $a "$trainedCr_Cm_N_It" "$crControlRange" "$cmControlRange" $mspcDir $mailAddress $doPlot $kyoyou $itblock $tt $r $T $umax $cC $ck $AP_TS1 $N2s $printalldata $model 1> ./${ControlMeg}.ky=${ky}.ku=${ku}.b=$b.a=$a.trainedCr_Cm_N_It=${trainedCr_Cm_N_It// /_}.crRange=${crControlRange// /_}.cmRange=${cmControlRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.ck=$ck.AP_TS1=$AP_TS1.N2s=$N2s.txt 2>&1 &



#-------------------------------------------------------------------------------
#use "jobs" command to see the status of linux jobs.

##code

ControlMeg=$1
ky=$2
ku=$3
b=$4
a=$5
#
trainedCr_Cm_N_It=(${6})
crControlRange="${7}"
cmControlRange="${8}"
mspcDir=${9}
mailAddress=${10}
doPlot=${11}
kyoyou=${12}
itblock=${13}
tt=${14}
r=${15}
T=${16}
umax=${17}
cC=${18}
ck=${19}
AP_TS1=${20} #define AP_TS1 0.5 //virtual sampling period
N2s=${21}
printalldata=${22}
model=${23}

#
cr1=${trainedCr_Cm_N_It[0]}
cm1=${trainedCr_Cm_N_It[1]}
N1=${trainedCr_Cm_N_It[2]}
it1=${trainedCr_Cm_N_It[3]}
#
cr2=${trainedCr_Cm_N_It[4]}
cm2=${trainedCr_Cm_N_It[5]}
N2=${trainedCr_Cm_N_It[6]}
it2=${trainedCr_Cm_N_It[7]}
#
cr3=${trainedCr_Cm_N_It[8]}
cm3=${trainedCr_Cm_N_It[9]}
N3=${trainedCr_Cm_N_It[10]}
it3=${trainedCr_Cm_N_It[11]}
#
cr4=${trainedCr_Cm_N_It[12]}
cm4=${trainedCr_Cm_N_It[13]}
N4=${trainedCr_Cm_N_It[14]}
it4=${trainedCr_Cm_N_It[15]}
#
cr5=${trainedCr_Cm_N_It[16]}
cm5=${trainedCr_Cm_N_It[17]}
N5=${trainedCr_Cm_N_It[18]}
it5=${trainedCr_Cm_N_It[19]}
#
cr6=${trainedCr_Cm_N_It[20]}
cm6=${trainedCr_Cm_N_It[21]}
N6=${trainedCr_Cm_N_It[22]}
it6=${trainedCr_Cm_N_It[23]}
#
cr7=${trainedCr_Cm_N_It[24]}
cm7=${trainedCr_Cm_N_It[25]}
N7=${trainedCr_Cm_N_It[26]}
it7=${trainedCr_Cm_N_It[27]}
#
cr8=${trainedCr_Cm_N_It[28]}
cm8=${trainedCr_Cm_N_It[29]}
N8=${trainedCr_Cm_N_It[30]}
it8=${trainedCr_Cm_N_It[31]}
#
cr9=${trainedCr_Cm_N_It[32]}
cm9=${trainedCr_Cm_N_It[33]}
N9=${trainedCr_Cm_N_It[34]}
it9=${trainedCr_Cm_N_It[35]}
#
cr10=${trainedCr_Cm_N_It[36]}
cm10=${trainedCr_Cm_N_It[37]}
N10=${trainedCr_Cm_N_It[38]}
it10=${trainedCr_Cm_N_It[39]}
#


#参考　：　method:12:$N1:$b:$a:0:$f1:$f2:$f3:$f4 N:${N1}:${N2}:${N3}:${N4}

#使うCAN２のフォルダpathの定義
d=../../result-mspc/a${a}b${b}tt${tt}
f1=$d/net_cr${cr1}cm${cm1}N${N1}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it1}
f2=$d/net_cr${cr2}cm${cm2}N${N2}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it2}
f3=$d/net_cr${cr3}cm${cm3}N${N3}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it3}
f4=$d/net_cr${cr4}cm${cm4}N${N4}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it4}
f5=$d/net_cr${cr5}cm${cm5}N${N5}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it5}
f6=$d/net_cr${cr6}cm${cm6}N${N6}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it6}
f7=$d/net_cr${cr7}cm${cm7}N${N7}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it7}
f8=$d/net_cr${cr8}cm${cm8}N${N8}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it8}
f9=$d/net_cr${cr9}cm${cm9}N${N9}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it9}
f10=$d/net_cr${cr10}cm${cm10}N${N10}ny${ky}nu${ku}iti${itblock}IS2r${r}T${T}it${it10}

crcmTrainString="crcmTrainString=${cr1}_${cm1}"
CAN2String="N1=${N1}.it1=${it1}"
#
CAN2FilesString="${f1}"
CAN2UnitsString="${N1}"



if [ "$N2" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr2}_${cm2}"
	CAN2String=$CAN2String".N2=${N2}.it2=${it2}"
	CAN2FilesString=$CAN2FilesString":${f2}"
	CAN2UnitsString=$CAN2UnitsString":${N2}"
fi
if [ "$N3" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr3}_${cm3}"
	CAN2String=$CAN2String".N3=${N3}.it3=${it3}"
	CAN2FilesString=$CAN2FilesString":${f3}"
	CAN2UnitsString=$CAN2UnitsString":${N3}"
fi
if [ "$N4" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr4}_${cm4}"
	CAN2String=$CAN2String".N4=${N4}.it4=${it4}"
	CAN2FilesString=$CAN2FilesString":${f4}"
	CAN2UnitsString=$CAN2UnitsString":${N4}"
fi
if [ "$N5" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr5}_${cm5}"
	CAN2String=$CAN2String".N5=${N5}.it5=${it5}"
	CAN2FilesString=$CAN2FilesString":${f5}"
	CAN2UnitsString=$CAN2UnitsString":${N5}"
fi
if [ "$N6" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr6}_${cm6}"
	CAN2String=$CAN2String".N6=${N6}.it6=${it6}"
	CAN2FilesString=$CAN2FilesString":${f6}"
	CAN2UnitsString=$CAN2UnitsString":${N6}"
fi
if [ "$N7" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr7}_${cm7}"
	CAN2String=$CAN2String".N7=${N7}.it7=${it7}"
	CAN2FilesString=$CAN2FilesString":${f7}"
	CAN2UnitsString=$CAN2UnitsString":${N7}"
fi
if [ "$N8" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr8}_${cm8}"
	CAN2String=$CAN2String".N8=${N8}.it8=${it8}"
	CAN2FilesString=$CAN2FilesString":${f8}"
	CAN2UnitsString=$CAN2UnitsString":${N8}"
fi
if [ "$N9" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr9}_${cm9}"
	CAN2String=$CAN2String".N9=${N9}.it9=${it9}"
	CAN2FilesString=$CAN2FilesString":${f9}"
	CAN2UnitsString=$CAN2UnitsString":${N9}"
fi
if [ "${N10}" != "" ]
then
	crcmTrainString=$crcmTrainString"_${cr10}_${cm10}"
	CAN2String=$CAN2String".N10=${N10}.it10=${it10}"
	CAN2FilesString=$CAN2FilesString":${f10}"
	CAN2UnitsString=$CAN2UnitsString":${N10}"
fi


parameterString="b=${b}.a=${a}.ky=${ky}.ku=${ku}.$crcmTrainString.crRange=${crControlRange// /_}.cmRange=${cmControlRange// /_}.kyoyou=$kyoyou.itblock=${itblock}.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.ck=$ck.AP_TS1=$AP_TS1.N2s=$N2s.$CAN2String"

#goto mspc dir
cd $mspcDir



#check the mspcDir have not been used.
mspcDirUsed=`ps aux|grep "AddLearnControlForLinearCraneV.*""${mspcDir}"|grep -c -v "grep"`
if [ ${mspcDirUsed} -gt 2 ]
then
	echo "Error,this mspc dir have be used!"
	echo -e `ps aux|grep "AddLearnControlForLinearCraneV.*""${mspcDir}"|grep -v "grep"`|mail -s "Error,this mspc dir have been used! change the mspc dir! ""parameter=$parameterString" $mailAddress
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


#all
rm listSS.dat
ydatFileNum=1
for cr in $crControlRange; do for cm in $cmControlRange; do
echo -n "$cr $cm ">>listSS.dat
if [ "$model" = "nonlinear" ]
then
	emulate_crane2 it:1:1 r:$r cr:$cr cm:$cm cC:$cC umax:$umax tt:$tt kxt:1 method:12:${N1}:$b:$a:0:$CAN2FilesString N:$CAN2UnitsString DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
if [ "$model" = "linear" ]
then
	emulate_crane4 it:1:1 r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:${N1}:$b:$a:0:$CAN2FilesString N:$CAN2UnitsString DISP:${DISP} listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou
fi
#cp y.dat "y-can2AddTrain-No"$ydatFileNum"-"$cr"-"$cm".dat"
cp y.dat "y-can2"${model}${ControlMeg}"-parameter-"$cr"-"$cm".dat"
let ydatFileNum++
done;done
cat listSS.dat
echo "Use ${ControlMeg} to control,b=$b,a=$a"
#結果を統計する。
cmd=`grep -v '^.*\s.*\s-1\.0' listSS.dat|awk 'BEGIN {sa=oa=n=0;sM=oM=-1;sm=om=1e4;} {s[n]=$3;o[n]=$4;sa+=$3;oa+=$4;n++;if(sM<$3)sM=$3;if(sm>$3)sm=$3;if(oM<$4)oM=$4;if(om>$4)om=$4;} END{sa/=n;oa/=n;sv=ov=0;for(i=0;i<n;i++){se=s[i]-sa;sv+=(se*se);oe=o[i]-oa;ov+=(oe*oe);};printf("#{%.2f}{%.2f}{%.2f}{%.2f} {%.1f}{%.1f} {%.1f} {%.1f} #mean(min,max;rmse) of ST and OS\n",sa,sm,sM,sqrt(sv/n),oa,om,oM,sqrt(ov/n));}'`
cmd2=`grep -c '^.*\s.*\s-1\.0' listSS.dat`
echo -e "$cmd"" #fail #""${cmd2}"
result="$cmd"" #fail #""${cmd2}"
echo "This is the mark row."
#create the result string
allresult="Use ${ControlMeg} to control,b=$b,a=$a,parameter>>""${parameterString}"
echo -n -e "$allresult"
#
if [ "$mailAddress" != "" ]
then
echo -e -n "$allresult"|mail -s "Use ""${ControlMeg}"" to control, parameter>>""${parameterString}" $mailAddress
fi