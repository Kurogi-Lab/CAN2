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
#b=$1 #bagging parameter 1
#N=$2 #you can set N to "10 20 30", it works too. max number is 10
#a=$3 #bagging parameter 2
#mspcDir=$4 #Dir of mspc fold
#mailAddress=$5 #
#ky=$6 #ky of input
#ku=$7 #ku of input
#controlTrainingIterations=$8 #
#crRange="$9" #cr parameter of CRANE
#cmRange="${10}" #cm parameter of CRANE
#doPlot="${11}" #plot or not
#kyoyou=${12} #allowable error of overshoot
#itblock=${13} #used data of previous iterations for CAN2 training
#tt=${14} ##total time?
#r=${15} #destination position
#T=${16} ##CAN learn time?
#umax=${17} #max force
#cC=${18} #cc parameter of CRANE
#AP_TS1=${19} #define AP_TS1 0.5 //virtual sampling period
#N2s=${20} #time of evaluation function
#printalldata=${21} #set the debug=1 will print all data with sampling period
#ck=${22} #ck parameter of CRANE
#useRI=${23} #use true model or not
#RI=${24} #parameter of using true model
RIstring=$useRI":"$RI #this is about true model training
##model=${25}
#
##echo a6=${6},a7=${7},a8=${8},a9=${9},a10=${10},a15=${15},a20=${20},a21=${21},a22=${22},a23=${23},a24=${24}
#echo a10=${10},a11=${11},a12=${12},a13=${13},a14=${14},a15=${15},a20=${20},a21=${21},a22=${22},a23=${23},a24=${24}


for Ni in $N; do if [ "$CAN2UnitsString" = "" ]; then CAN2UnitsString=$Ni; else CAN2UnitsString=${CAN2UnitsString}:${Ni}; fi; done

echo "cr=$crRange cm=$cmRange N=$CAN2UnitsString"

#cd to the mspcdir,change it if you will do a lot of experiments in one computer.
cd ${mspcDir}

parameterString="b=${b}.a=${a}.N=$CAN2UnitsString.ky=${ky}.ku=${ku}.controlTrainingIterations=${controlTrainingIterations}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.ck=$ck.useRI=$useRI.RI=$RI.AP_TS1=$AP_TS1.N2s=$N2s"

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
	make CC=$CC
#	make CC=icc
fi

#
# train by controlling some cranes

date


echo "exec for cr=$crRange cm=$cmRange Ur=$Ur UT=$UT N=$N model=$model"
cat /dev/null > listSS.dat

for cr in $crRange; do for cm in $cmRange; do
#  for uT in $UT; do
#      for ur in $Ur; do

if [ "$dataclean" = "yes" ]; then 
      mv listSS.dat listSS.txt
      make data-clean #しないとｍｓｐｃフォルダのresult-ensrs2geフォルダにCAN２のファイルが残ってしまう、新しいCAN２の保存ができない
      mv listSS.txt listSS.dat
fi
     for unit in $N; do
	      # 訓練
	 if [ "$model" = "nonlinear" ]
	 then
	     cmd="./emulate_crane2 it:$controlTrainingIterations:$itblock r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax uI:${uI} tt:$tt kxt:1 method:12:${unit}:${b}:$a:0 DISP:$DISP listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou RI:$RIstring"
	     echo $cmd; time $cmd;
	 fi
	 if [ "$model" = "linear" ]
	 then
	     cmd="./emulate_crane4 it:$controlTrainingIterations:$itblock r:$r cr:$cr cm:$cm cC:$cC ck:$ck umax:$umax uI:${uI} tt:$tt kxt:1 method:12:${unit}:${b}:$a:0 DISP:$DISP listSS:1 T:$T N2s:$N2s LAMBDA:0.01 ky:$kyoyou RI:$RIstring"
	     echo $cmd; time $cmd;
	 fi
		# 結果ファイルとcan2ファイルの移動
	 d0=../result-mspc30
#	 d0=../../result-mspc
	 if [ ! -e $d0 ]; then mkdir $d0;fi
	 d1=${d0}/a${a}b${b}tt${tt}
	 if [ ! -e $d1 ]; then mkdir $d1;fi
		#mv -f result-ensrs2ge/net* ${d1}/
	 cp -r -f result-ensrs2ge/net* ${d1}/ #-f (force) -R (recursive)
     done #done for unit

#  done #done for ur0
#  done #done for uT0

done; #closing for cm
done  #closing for cr
	#listSS.dat
echo "This is the mark row.(result of cr:$cr cm:$cm crane)"
cat listSS.dat
getCurrentListss=`cat listSS.dat`
alllistSS="$alllistSS""\n""${parameterString}""_cr=${cr}_cm=${cm}\n""$getCurrentListss\n"
	# str1 store BestST result,str2 store BestOS result,strR store all result.
cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9;rowid=1} {if($1>0) {v=$1+$2*0.05; if(v<vm) {vm=v;i=rowid}};rowid=rowid+1} END {printf("head %d listSS.dat",-i)}'`
echo -e -n "\nParameters:b=$b,a=$a,N=${CAN2UnitsString}\n#BestST+0.05OS: ";$cmd | tail -1
str1=`$cmd|tail -1`
strR="$strR""\nParameters:b=$b,a=$a,N=${CAN2UnitsString}\n#BestST+0.05OS: ""$str1\n"
cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9;rowid=1} {if($1>0) {v=$2+0.05*$1; if(v<vm) {vm=v;i=rowid}};rowid=rowid+1} END {printf("head %d listSS.dat",-i)}'`
echo -n "#BestOS+0.05ST: ";$cmd | tail -1
str2=`$cmd|tail -1`
strR="$strR""#BestOS+0.05ST: ""$str2\n"
#orig###orig
#orig#cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9;rowid=1} {if($1>0) {v=$1+$2*0.01; if(v<vm) {vm=v;i=rowid}};rowid=rowid+1} END {printf("head %d listSS.dat",-i)}'`
#orig#echo -e -n "\nParameters:b=$b,a=$a,N=${CAN2UnitsString}\n#BestST+0.01OS: ";$cmd | tail -1
#orig#str1=`$cmd|tail -1`
#orig#strR="$strR""\nParameters:b=$b,a=$a,N=${CAN2UnitsString}\n#BestST+0.01OS: ""$str1\n"
#orig#cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9;rowid=1} {if($1>0) {v=$2+0.01*$1; if(v<vm) {vm=v;i=rowid}};rowid=rowid+1} END {printf("head %d listSS.dat",-i)}'`
#orig#echo -n "#BestOS+0.01ST: ";$cmd | tail -1
#orig#str2=`$cmd|tail -1`
#orig#strR="$strR""#BestOS+0.01ST: ""$str2\n"
date

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

