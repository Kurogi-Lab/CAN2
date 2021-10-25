export ddata=../tmp
export dsh=../sh
if [ "$fntrain" == "" ];then fntrain=${ddata}/train.csv; fi
if [ "$fntest" == "" ];then fntest=${ddata}/test.csv; fi
if [ "$seed" == "" ];then seed=1; fi
if [ "$Tpinv" == "" ];then Tpinv=999; fi
if [ "$nop" == "" ];then nop=0; fi
if [ "$n_bags" == "" ];then n_bags=1; n_alpha=1; fi
if [ "$DISP" == "" ];then DISP=1; fi
export n_train=`rows.sh $fntrain`
export n_test=`rows.sh $fntest`
make data-clean
mkdir -p tmp
fntraintest=tmp/train-test.csv
cp $fntrain $fntraintest 
cat $fntest >> $fntraintest 
wc $fntrain $fntest $fntraintest
#export T=100 N=100 # for check 6-3
#export n_bags=20 alpha=0.7;#bagging
#export n_bags=1 alpha=1;#single with n_bags==1
export k=`cat $fntest|awk 'END{print NF-1;}'`
export k1=`expr $k + 1`;export LINESIZE=`expr 16 \* $k1`
####single
if [ "$n_bags" = "1" ];then  #single
export cmd="ensrs $fntrain -1:$fntraintest $N-$N:1 k:$k Lstd:0:2 ib:0:0:0:0 T:$T seed:$seed Tpinv:$Tpinv nop:$nop" #singleCAN2
else   ####bagging CAN2
export cmd="ensrs ${fntrain} 2:$n_bags:$alpha:$seed $N-$N:1 bg:${fntraintest} k:$k T:$T BIAS:1 Lstd:0:2 ib:0:0:0:0 vm2:-1 Tpinv:$Tpinv nop:$nop DISP:$DISP";
#export cmd="ensrs ${fntrain} 2:$n_bags:$alpha:$seed $N-$N:1 bg:${fntraintest} k:$k T:$T BIAS:1 Lstd:0:2 ib:0:0:0:0 vm2:-1 seed:$seed Tpinv:$Tpinv nop:$nop";
fi
###
#start_time=`date "+%Y-%m-%d %H:%M:%S"`
T0N=`date +%N`   #A 000000000から999999999までのナノ秒
T0=`date +%s`   #A
echo $cmd;#if [ "$nop" == "0" ];then echo $cmd;fi
$cmd
#end_time=`date "+%Y-%m-%d %H:%M:%S"`
T1N=`date +%N`   #B
T1=`date +%s`   #A
#echo "DT = ${T1} - ${T0}"
#t1=$SECONDS
###analyze result
ntrain=`rows.sh $fntrain`
ntest=`rows.sh $fntest`
head -$ntrain predict+.dat > tmp/predicttrain.dat
tail -$ntest  predict+.dat > tmp/predicttest.dat
export fntest=$fntest fnpred=tmp/predicttest.dat; 
if [ "$DISP" != "0" ]; then
$dsh/show${k}dpred.sh&
if [ "$n_bags" = "1" ];then  #single
cat >tmp/mse_t.plt <<EOF
set term postscript eps enhanced color;set output "tmp/mse_t.eps"
set logscale y;set format y "%.1e";plot "tmp/mse_t.csv" using 0:1 w lp t "MSEtr", "" using 0:2 w lp t "MSE"
EOF
#set logscale y;set format y "%.1e";plot "tmp/mse_t.csv" using 0:3 w lp t "NMSEtr", "" using 0:4 w lp t "NMSE"
gnuplot tmp/mse_t.plt; 
gv tmp/mse_t.eps&
fi
fi
MSE=`cat tmp/predicttrain.dat |awk 'BEGIN{s2=n=0;}{e=$1-$3;s2+=e*e;n++;}END{printf("%e ",s2/n)}'`
MSE=$MSE`cat tmp/predicttest.dat |awk 'BEGIN{s2=n=0;}{e=$1-$3;s2+=e*e;n++;}END{printf("%e ",s2/n)}'`
#PT=`echo "scale=3; (${T1} - ${T0})/1000000"|bc` #millisec
#DT=`expr ${T1} - ${T0}`
#PT=`expr ${DT} / 1000000` #millisec
#m=`expr ${PT} % 1000`
#PT=`expr ${PT} / 1000`
PT=`expr ${T1} - ${T0}`
PT0=$PT
H=`expr ${PT} / 3600`
PT=`expr ${PT} % 3600`
M=`expr ${PT} / 60`
S=`expr ${PT} % 60`
#echo "$T $MSE #MSEtr MSE N$N b$n_bags a$alpha ${H}:${M}:${S}"
#HMS=`expr $H \* $M`
DTN=`expr ${T1N} - ${T0N}`
#echo "HMS,DTN=$HMS, $DTN"
#if [ ( ${DTN} -ge 0 ) -a  ( ${HMS} -eq 0 ) ]; then
PT=`expr ${DTN} / 1000000` #millisec
m=`expr ${PT} % 1000`
if [ ${m} -lt 0 ]; then
#echo "m=$m"
m=`expr 1000 + $m`
if [ ${m} -gt 500 ]; then S=`expr $S - 1`; PT0=`expr ${PT0} - 1`; fi
fi
#echo "$T $MSE ${PT0}.${m}s(${H}:${M}:${S}.${m}) #MSEtr MSE Time N$N can2c-single"
echo "[$T,$Tpinv](${PT0}.${m}s) $MSE  #[T,Tpinv] MSEtr MSE n${n_train},${n_test} N$N b$n_bags a$alpha seed$seed nop$nop"
#echo "$T $MSE ${PT0}.${m}s(${H}:${M}:${S}.${m}) #[T,Tpinv] MSEtr MSE Time n${n_train},${n_test} N$N b$n_bags a$alpha seed$seed nop$nop"
#999999999
#  s   m
#echo "$T $MSE #MSEtr MSE N$N b$n_bags a$alpha ${H}:${M}:${S}.${m}"
#echo "DT = ${T1} - ${T0}"
