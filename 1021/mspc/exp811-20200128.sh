#!/bin/bash
#(8-1-1)
#export d0=../../result-mspc200124; mkdir -p $d0
if [ "$d0" == "" ]; then source exp800-20200128.sh; fi
#export a=0.7 b=1 tt=100; #good for Ubuntu12.04
#export d1=${d0}/a${a}b${b}tt${tt}s${seed}; if [ ! -e $d1 ]; then mkdir $d1;fi  #include information of seed20200127
source $d1/f12345.dat
#
export Nas="$N1 $N2 $N3 $N4 2"
export Na=(0 $N1 $N2 $N3 $N4 2) #配列array にパラメタ設定, 第0要素はダミー，第５要素はプラントP1(m=10)とP2(m=10)用
export NM=${Na[1]};for i in 2 3 4 ;do if [ $NM -lt ${Na[$i]} ]; then NM=${Na[$i]}; fi ;done #NMに最大値8を設定
#echo "#Na[@]=${Na[@]}, Na[1]=${Na[1]}, Na[2]=${Na[2]}", Na[3]=${Na[3]}", Na[4]=${Na[4]}, NM=$NM"; #確認
export fas="$f1 $f2 $f3 $f4 2"
export fa=(0 $f1 $f2 $f3 $f4 2)
export NMA=0;for i in 1 2 3 4 ;do NMA=`expr ${NMA} + ${Na[$i]}`; done #NM
export mL1s="20 50 20 50 20 50"
export mL1=(0 20 50 20 50 20 50); #学習は20,50 N1,N2,N3,N4に対する学習モデルの荷重質量m、最後の20,50はプラントモデルのm
export objs="ST ST OS OS";  #
export obj=(0 "ST" "ST" "OS" "OS");  #N1,N2,N3,N4に対する制御目的#export obj=(0 "S" "S" "O" "O");  #N1,N2,N3,N4に対する制御目的 #
export mX1s="10 20 30 40 50 60"
export mX1=(0 10 20 30 40 50 60); #テストを10-60
