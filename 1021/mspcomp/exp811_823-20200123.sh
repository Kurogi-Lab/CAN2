#!/bin/bash
#(8-1-1)
if [ "$d0" == "" ]; then source exp811-20200128.sh; fi
##export d0=../../result-mspc200124; mkdir -p $d0
##export a=0.7 b=1 seed=21 tt=100; #good for Ubuntu12.04
##export d1=${d0}/a${a}b${b}tt${tt}s${seed}; if [ ! -e $d1 ]; then mkdir $d1;fi  #include information of seed20200127
#source $d1/f12345.dat
#export Na=(0 $N1 $N2 $N3 $N4 2) #配列array にパラメタ設定, 第0要素はダミー，第５要素はプラントP1(m=10)とP2(m=10)用
#export NM=${Na[1]};for i in 2 3 4 ;do if [ $NM -lt ${Na[$i]} ]; then NM=${Na[$i]}; fi ;done #NMに最大値8を設定
#echo "#Na[@]=${Na[@]}, Na[1]=${Na[1]}, Na[2]=${Na[2]}", Na[3]=${Na[3]}", Na[4]=${Na[4]}, NM=$NM"; #確認
#export fa=(0 $f1 $f2 $f3 $f4 2)
#export NMA=0;for i in 1 2 3 4 ;do NMA=`expr ${NMA} + ${Na[$i]}`; done #NM
#export mL1=(0 20 50 20 50 20 50); #学習は20,50 N1,N2,N3,N4に対する学習モデルの荷重質量m、最後の20,50はプラントモデルのm
#export obj=(0 "ST" "ST" "OS" "OS");  #N1,N2,N3,N4に対する制御目的#export obj=(0 "S" "S" "O" "O");  #N1,N2,N3,N4に対する制御目的 #
#export mX1=(0 10 20 30 40 50 60); #テストを10-60
#export mX2=(0 10 60); #結果を論文に表示するためのテスト集合 ICONIP2019
#export mX2=(0 `seq 10 5 60`); #結果を論文に表示するためのテスト集合 ICONIP2019
##
##########################
#(8-2) GPCの複数の場合の極零の表示実験　
##########################
#(8-2-1) obtain M[1..26] for f1,f2,f3,f4 -->M1234.dat
#########################
export fM=$d0/M
cat /dev/null> tmp/M.dat;
for nf in 1 2 3 4; do #for nf in 1 2 3 4 5; do#for nf in 1 2 3 5; do #
  N=${Na[nf]}
  f=${fa[nf]}
 echo "## $f" >> tmp/M.dat
 fM=${fM}${nf}
 for cm in 20; do # any cm
  cmd="emulate_crane4 it:1:1 r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 umax:10 tt:$tt kxt:1 method:12:$N:$b:$a:$seed:${f} N:${N} DISP:0 listSS:1 T:100 N2s:12 LAMBDA:0.01";$cmd
 done;#for cm
done;#for ff
cp tmp/M.dat $fM.dat
####original GPC
cat $fM.dat|awk 'BEGIN{i=1;}{if(substr($1,1,1)!="#"){printf("M[%d]:[%s,%s,%s,%s,%s,%s,%s,%s];\n",i++,$5,$6,$7,$8,$1,$2,$3,$4);}}' >$fM.mac #original
fMA=$d0/MA.mac; cat $fM.mac > $fMA
cat $fMA    #-->M[1..24]  #../result-mspc170129/MA.mac
#########################
#########################
#(8-2-2) obtain M[1..24], a[1..2] for cm=10 60 --> $d0/MA.mac 
#########################
### make fMA
###
#export n_mX2=${#mX2[@]}; export n1_mX2=`expr ${n_mX2} - 1`; export nPS=`seq 1 $n1_mX2`
fps=$d0/result-ab.dat
cat /dev/null > $fps	
for mX in ${mX2[@]}; do 
  if [ $mX == 0 ]; then continue ; fi
  cmd="d0:\"$d0\";m:${mX};TS:0.5;batch(\"plantmodeling.mac\");quit();";
  echo "Executing $cmd |maxima"
  echo $cmd |maxima > /dev/null;#-->$d0/m${mX}TS${TS}/result-ab.dat
  cat $d0/m${mX}TS0.5/result-ab.dat >> $fps
  echo "" >> $fps
done; #for m
fMA=$d0/MA.mac; 
cat $fps|awk 'BEGIN{i=ENVIRON["NMA"]+1;}{printf("M[%d]:[%s,%s,%s,%s,%s,%s,%s,%s];\n",i++,$1,$2,$3,$4,$5,$6,$7,$8);}' >> $fMA #M[25..26]=a[1..2]for check?
cat $fps|awk 'BEGIN{i=1;}{printf("a[%d]:[%s,%s,%s,%s,%s,%s,%s,%s];\n",i++,$1,$2,$3,$4,$5,$6,$7,$8);}' >> $fMA 
cat $fMA  ##-->M[1..24],a[1..2] #20190521 M[1..26],a[1..2]
##########################
##(8-2-3) generate gpc-poles* and gpc-zeros*
############
export n_mX2=${#mX2[@]}; export n1_mX2=`expr ${n_mX2} - 1`; export nPS=`seq 1 $n1_mX2`
nX=0;
for mX in ${mX2[@]}; do 
  if [ $mX == 0 ]; then continue ; fi
  let ++nX
  nM=0
  M=0
  for N in ${Na[@]} ; do 
    if [ $N == 0 ]; then continue ; fi
    let ++M
#  for M in 1 2 3 4 5; do #5= ${#Na[@]} - 1
    for n in `seq 1 ${Na[M]}` ; do
      let ++nM
      cmd="display2d:false;batch(\"$fMA\");TS:0.5;nP:${nX};nM:${nM};lu:0.24;Gzmode:0;batch(\"gpcMA2poles+.mac\");quit();";#same as the result with Gzmode:1
      echo "Execute echo $cmd|maxima;"
      echo $cmd | maxima > /dev/null;  ##error with zero @20191231
    done; #for n in `seq 1 ${Na[M]` ; do
  done; #for M in 1 2 3 4 5; do
done #for mX in ${mX2[@]}; do 

