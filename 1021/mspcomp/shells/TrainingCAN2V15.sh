#first step 一個のtermianlを開いて、5行目もしくは9行目を実行する。
#---------------------------------------実行方法　1----------------------------------------
#(1)write debug information to another file.
#
#b=1;N=20;a=0;mspcDir=~/sotuicc/2012a/mspc/;mailAddress="youname@kurolab2.cntl.kyutech.ac.jp";ky=5;ku=5;controlTimes=100;crRange="2 10";cmRange="10 100";doPlot="yesno";kyoyou=0.1;itblock=2;nohup sh ./TrainingCAN2V15.sh $b $N $a $mspcDir $mailAddress $ky $ku $controlTimes "$crRange" "$cmRange" $doPlot $kyoyou $itblock 1> ./TrainingCAN2.result.b=${b}.a=${a}.N=${N}.ky=${ky}.ku=${ku}.controlTimes=${controlTimes}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.txt 2> ./TrainingCAN2.debugResult.b=${b}.a=${a}.N=${N}.ky=${ky}.ku=${ku}.controlTimes=${controlTimes}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.txt &
#---------------------------------------実行方法　2----------------------------------------
#(2)write result and debug information to one file
#
#b=1;N=20;a=0;mspcDir=~/sotuicc/2012a/mspc/;mailAddress="youname@kurolab2.cntl.kyutech.ac.jp";ky=5;ku=5;controlTimes=100;crRange="2 10";cmRange="10 100";doPlot="yesno";kyoyou=0.1;itblock=2;nohup sh ./TrainingCAN2V15.sh $b $N $a $mspcDir $mailAddress $ky $ku $controlTimes "$crRange" "$cmRange" $doPlot $kyoyou $itblock 1> ./TrainingCAN2.result.b=${b}.a=${a}.N=${N}.ky=${ky}.ku=${ku}.controlTimes=${controlTimes}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.txt 2>&1 &
#-------------------------------------------------------------------------------

#modified by kuro
#b=1;N=20;a=0;mspcDir=~/sotu/2012/mspc/;mailAddress="";ky=5;ku=5;controlTimes=100;crRange="2 10";cmRange="10 100";doPlot="no";kyoyou=0.1;itblock=2;nohup sh ./TrainingCAN2V15.sh $b $N $a $mspcDir $mailAddress $ky $ku $controlTimes "$crRange" "$cmRange" $doPlot $kyoyou $itblock 1> ./TrainingCAN2.result.b=${b}.a=${a}.N=${N}.ky=${ky}.ku=${ku}.controlTimes=${controlTimes}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.txt 2> ./TrainingCAN2.debugResult.b=${b}.a=${a}.N=${N}.ky=${ky}.ku=${ku}.controlTimes=${controlTimes}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.txt &


##code

b=$1;N=$2;a=$3
mspcDir=$4
cd ${mspcDir} #cd to the mspcdir,change it if you will do a lot of experiments in one computer.
mailAddress=$5
ky=$6
ku=$7
controlTimes=$8
crRange="$9"
cmRange="${10}"
echo "$crRange"
echo "$cmRange"
doPlot="${11}"
kyoyou=${12}
itblock=${13}

parameterString="b=${b}.a=${a}.N=${N}.ky=${ky}.ku=${ku}.controlTimes=${controlTimes}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock"

#check the mspcDir have not been used.
mspcDirUsed=`ps aux|grep "TrainingCAN2.*""${mspcDir}"|grep -c -v "grep"`
if [ ${mspcDirUsed} -gt 2 ]
then
	echo "Error,this mspc dir have be used!"
	echo `ps aux|grep "TrainingCAN2.*""${mspcDir}"|grep -v "grep"`|mail -s "Error,this mspc dir have be used! change the mspc dir! ""${parameterString}" $mailAddress
	exit 1
fi

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

#create net file dir
mkdir ../../mspcdata;mkdir ../../mspcdata/result/;mkdir ../../mspcdata/result/b${b}a${a}_7e
#
#train,control some crane
for cr in $crRange; do for cm in $cmRange; do
	date
	make data-clean
	# 訓練
	time ./emulate_crane2 it:$controlTimes:$itblock r:5 cr:$cr cm:$cm cC:0.5 umax:10 tt:100 kxt:1 method:12:${N}:${b}:$a:0 DISP:$DISP listSS:1 T:100 N2s:12 LAMBDA:0.01 ky:$kyoyou
	# 結果ファイルとcan2ファイルの移動
	mv result-ensrs2ge/net* ../../mspcdata/result/b${b}a${a}_7e/ 
	# listSS.datが２０(controlTimes)回変更された、ここは一番いい結果を探す。eg,net_cr2cm10N20ny4nu4iti2IS2r5T100it1フォルダは一回目の制御結果である。
	echo "This is the mark row.(result of one crane)"
	cat listSS.dat
	getCurrentListss=`cat listSS.dat`
	alllistSS="$alllistSS""\n""${parameterString}""_cr=${cr}_cm=${cm}\n""$getCurrentListss"
	# str1 store BestOS result,str2 store BestST result,strR store all result.
	cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9} {if($1>0) {v=$2+$1*0.01; if(v<vm) {vm=v;i=$3+1}}} END {printf("head %d listSS.dat",-i)}'`
	echo -n "#BestOS+0.01ST: ";$cmd | tail -1
	str1=`$cmd|tail -1`
	strR="$strR""#BestOS+0.01ST: ""$str1\n"
	cmd=`cat listSS.dat|awk 'BEGIN {vm=1e9} {if($1>0) {v=$1+0.01*$2; if(v<vm) {vm=v;i=$3+1}}} END {printf("head %d listSS.dat",-i)}'`
	echo -n "#BestST+0.01OS: ";$cmd | tail -1
	str2=`$cmd|tail -1`
	strR="$strR""#BestST+0.01OS: ""$str2\n"
	date
done;done
#
#display result in console
echo -e "\nThis is the mark row.(all best result)"
echo "${parameterString}"
echo -e -n "$strR"
echo -e "\nThis is the mark row.(original data,use that data to create graph fastly,change to csv is a idea.)"
echo -e "$alllistSS"
echo "This is the end row."
#
#send result by mail
if [ "$mailAddress" != "" ]
then
	echo -e "$strR""\n original data,use that data to create graph fastly,change to csv is a idea. \n""$alllistSS"|mail -s "Training is end,""${parameterString}" $mailAddress
fi

