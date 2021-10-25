#!/bin/bash
#can2の訓練
#一個のtermianlを開いて、実行方法を参考して実行する("#"入れず)。

#change log
#2015年1月20日15:53:34 change controlTimes to controlTrainingIterations
#2015年1月21日14:34:47 support the linear model training and true model training

#---------------------------------------実行方法----------------------------------------

#nonlinear
#model="nonlinear";b=1;a=0;N="200";crRange="2 10";cmRange="10 100";mspcDir=~/sotuicc/20131/mspc/;mailAddress="ko@kurolab.cntl.kyutech.ac.jp";ky=40;ku=40;controlTrainingIterations=10;itblock=20;doPlot="yesno";kyoyou=0.1;tt=100;r=5;T=100;umax=10;cC=0.5;ck=15;AP_TS1=0.5;N2s=12;useRI=0;RI=0.05;printalldata="yesno";nohup sh ./TrainingCAN2V20.sh $b "$N" $a $mspcDir $mailAddress $ky $ku $controlTrainingIterations "$crRange" "$cmRange" $doPlot $kyoyou $itblock $tt $r $T $umax $cC $AP_TS1 $N2s $printalldata $ck $useRI $RI $model 1> ./TrainingCAN2.result.b=${b}.a=${a}.N=${N// /_}.ky=${ky}.ku=${ku}.controlTrainingIterations=${controlTrainingIterations}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.AP_TS1=$AP_TS1.N2s=$N2s.txt 2>&1 &

#linear
#model="linear";b=1;a=0;N="200";crRange="2 10";cmRange="10 100";mspcDir=~/sotuicc/20131/mspc/;mailAddress="ko@kurolab.cntl.kyutech.ac.jp";ky=40;ku=40;controlTrainingIterations=20;itblock=20;doPlot="yesno";kyoyou=0.1;tt=100;r=5;T=100;umax=10;cC=0.5;ck=15;AP_TS1=0.5;N2s=12;useRI=0;RI=0.05;printalldata="yesno";nohup sh ./TrainingCAN2V20.sh $b "$N" $a $mspcDir $mailAddress $ky $ku $controlTrainingIterations "$crRange" "$cmRange" $doPlot $kyoyou $itblock $tt $r $T $umax $cC $AP_TS1 $N2s $printalldata $ck $useRI $RI $model 1> ./TrainingCAN2.result.b=${b}.a=${a}.N=${N// /_}.ky=${ky}.ku=${ku}.controlTrainingIterations=${controlTrainingIterations}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.AP_TS1=$AP_TS1.N2s=$N2s.txt 2>&1 &

#true model
#model="linear";b=1;a=0;N="1";crRange="2";cmRange="10 40 70 100";mspcDir=~/sotuicc/20151/mspc/;mailAddress="ko@kurolab.cntl.kyutech.ac.jp";ky=4;ku=1;controlTrainingIterations=1;itblock=1;doPlot="yesno";kyoyou=0.1;tt=1000;r=5;T=100;umax=10;cC=10;ck=15;AP_TS1=0.5;N2s=12;useRI=1;RI=0.05;printalldata="yesno";nohup sh ./TrainingCAN2V20.sh $b "$N" $a $mspcDir $mailAddress $ky $ku $controlTrainingIterations "$crRange" "$cmRange" $doPlot $kyoyou $itblock $tt $r $T $umax $cC $AP_TS1 $N2s $printalldata $ck $useRI $RI $model 1> ./TrainingCAN2.result.b=${b}.a=${a}.N=${N// /_}.ky=${ky}.ku=${ku}.controlTrainingIterations=${controlTrainingIterations}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.AP_TS1=$AP_TS1.N2s=$N2s.txt 2>&1 &

#-------------------------------------------------------------------------------


##code

b=$1 #bagging parameter 1
N=$2 #you can set N to "10 20 30", it works too. max number is 10
Nlist=($2)
a=$3 #bagging parameter 2
mspcDir=$4 #Dir of mspc fold
mailAddress=$5 #
ky=$6 #ky of input
ku=$7 #ku of input
controlTrainingIterations=$8 #
crRange="$9" #cr parameter of CRANE
cmRange="${10}" #cm parameter of CRANE
doPlot="${11}" #plot or not
kyoyou=${12} #allowable error of overshoot
itblock=${13} #used data of previous iterations for CAN2 training
tt=${14} ##total time?
r=${15} #destination position
T=${16} ##CAN learn time?
umax=${17} #max force
cC=${18} #cc parameter of CRANE
AP_TS1=${19} #define AP_TS1 0.5 //virtual sampling period
N2s=${20} #time of evaluation function
printalldata=${21} #set the debug=1 will print all data with sampling period
ck=${22} #ck parameter of CRANE
useRI=${23} #use true model or not
RI=${24} #parameter of using true model
RIstring=$useRI":"$RI #this is about true model training
model=${25}

#CAN2UnitsString=""
#for _N in $N; do CAN2UnitsString={$CAN2UnitsString}:{$_N}; done


N1=${Nlist[0]}
N2=${Nlist[1]}
N3=${Nlist[2]}
N4=${Nlist[3]}
N5=${Nlist[4]}
N6=${Nlist[5]}
N7=${Nlist[6]}
N8=${Nlist[7]}
N9=${Nlist[8]}
N10=${Nlist[9]}

CAN2UnitsString="${N1}"

if [ "$N2" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N2}"
fi
if [ "$N3" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N3}"
fi
if [ "$N4" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N4}"
fi
if [ "$N5" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N5}"
fi
if [ "$N6" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N6}"
fi
if [ "$N7" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N7}"
fi
if [ "$N8" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N8}"
fi
if [ "$N9" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N9}"
fi
if [ "$N10" != "" ]
then
	CAN2UnitsString=$CAN2UnitsString":${N10}"
fi

echo "$crRange"
echo "$cmRange"

#cd to the mspcdir,change it if you will do a lot of experiments in one computer.
cd ${mspcDir}

parameterString="b=${b}.a=${a}.N=${CAN2UnitsString}.ky=${ky}.ku=${ku}.controlTrainingIterations=${controlTrainingIterations}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.ck=$ck.useRI=$useRI.RI=$RI.AP_TS1=$AP_TS1.N2s=$N2s"

echo "param='$parameterString'";


#check the mspcDir have not been used.
mspcDirUsed=`ps aux|grep "TrainingCAN2V.*""${mspcDir}"|grep -c -v "grep"`
if [ ${mspcDirUsed} -gt 2 ]
then
	echo "Error,this mspc dir have been used!"
	echo `ps aux|grep "TrainingCAN2V.*""${mspcDir}"|grep -v "grep"`|mail -s "Error,this mspc dir have be used! change the mspc dir! ""${parameterString}" $mailAddress
	exit 1
fi

#do plot or no 
if [ "$doPlot" != "yes" ]
then
	DISP=0
else
	DISP=1
fi

#doCompile=0;D0=`pwd`
echo "current dir = $D0";
#check the ky
if
	grep "#define AP_ny $ky" apc_crane.c
#	grep "#define AP_ny ""$ky" apc_crane.c
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
	echo "AP_TS1 is correct in the apc_crane.c"
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
		echo "will change to [int debug=1],[set style data dots] in emulate_crane.c"
		sed -i -e s/"int debug="/"int debug=1;\/\/"/ emulate_crane.c
		sed -i -e s/"set style data lines"/"set style data dots"/ emulate_crane.c
		doCompile=1
	fi
else
	if grep "int debug=0" emulate_crane.c
	then
		echo "int debug=0,lines in emulate_crane.c"
	else
		echo "will change to [int debug=0],[set style data lines] in emulate_crane.c"
		sed -i -e s/"int debug="/"int debug=0;\/\/"/ emulate_crane.c
		sed -i -e s/"set style data dots"/"set style data lines"/ emulate_crane.c
		doCompile=1
	fi
fi

#change apc_crane.c and make again
if [ "$doCompile" = "1" ]
then
	make CC=icc
fi



#
# train by controlling some cranes
echo "exec for cr=$crRange cm=$cmRange"
for cr in $crRange; do for cm in $cmRange; do
	date
	make data-clean #しないとｍｓｐｃフォルダのresult-ensrs2geフォルダにCAN２のファイルが残ってしまう、新しいCAN２の保存ができない
	for unit in $N; do
		# 訓練
		if [ "$model" = "nonlinear" ]
		then
		    cmd="./emulate_crane2 it:$controlTrainingIterations:$itblock r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:${unit}:${b}:$a:0 DISP:$DISP listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou RI:$RIstring"
		    echo $cmd; time $cmd;
#		time ./emulate_crane2 it:$controlTrainingIterations:$itblock r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:${unit}:${b}:$a:0 DISP:$DISP listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou RI:$RIstring
		fi
		if [ "$model" = "linear" ]
		then
		    cmd="./emulate_crane4 it:$controlTrainingIterations:$itblock r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:${unit}:${b}:$a:0 DISP:$DISP listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou RI:$RIstring"
		    echo $cmd; time $cmd;
#			time ./emulate_crane4 it:$controlTrainingIterations:$itblock r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax tt:$tt kxt:1 method:12:${unit}:${b}:$a:0 DISP:$DISP listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou RI:$RIstring
		fi
		# 結果ファイルとcan2ファイルの移動
		d0=../../result-mspc
		if [ ! -e $d0 ]; then mkdir $d0;fi
		d1=${d0}/a${a}b${b}tt${tt}
		if [ ! -e $d1 ]; then mkdir $d1;fi
		#mv -f result-ensrs2ge/net* ${d1}/
		cp -r -f result-ensrs2ge/net* ${d1}/ #-f (force) -R (recursive)
	done
	#listSS.dat
	echo "This is the mark row.(result of cr:$cr cm:$cm crane)"
	cat listSS.dat
	getCurrentListss=`cat listSS.dat`
	alllistSS="$alllistSS""\n""${parameterString}""_cr=${cr}_cm=${cm}\n""$getCurrentListss\n"
	# str1 store BestST result,str2 store BestOS result,strR store all result.
	cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9;rowid=1} {if($1>0) {v=$1+$2*0.01; if(v<vm) {vm=v;i=rowid}};rowid=rowid+1} END {printf("head %d listSS.dat",-i)}'`
	echo -e -n "\nParameters:b=$b,a=$a,N=${CAN2UnitsString}\n#BestST+0.01OS: ";$cmd | tail -1
	str1=`$cmd|tail -1`
	strR="$strR""\nParameters:b=$b,a=$a,N=${CAN2UnitsString}\n#BestST+0.01OS: ""$str1\n"
	cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9;rowid=1} {if($1>0) {v=$2+0.01*$1; if(v<vm) {vm=v;i=rowid}};rowid=rowid+1} END {printf("head %d listSS.dat",-i)}'`
	echo -n "#BestOS+0.01ST: ";$cmd | tail -1
	str2=`$cmd|tail -1`
	strR="$strR""#BestOS+0.01ST: ""$str2\n"
	date
done;done
#
#display result in console
echo -e "\nThis is the mark row.(all best result)"
echo "${parameterString}"
echo -e -n "$strR"
echo -e "\nThis is the mark row.(original data.)"
echo -e "$alllistSS"
echo "This is the end row."
#
#send result by mail
if [ "$mailAddress" != "" ]
then
	echo -e "$strR""\nOriginal data. \n""$alllistSS"|mail -s "Training is end,""${parameterString}" $mailAddress
fi

