#!/bin/bash
#(8-1-1)
#export d0=../../result-mspc200124; mkdir -p $d0
if [ "$d0" == "" ]; then source exp800-20200128.sh; fi
#export a=0.7 b=1 tt=100; #good for Ubuntu12.04
#export d1=${d0}/a${a}b${b}tt${tt}s${seed}; if [ ! -e $d1 ]; then mkdir $d1;fi  #include information of seed20200127
source $d1/f12345.dat
#
export Nas="$N1 $N2 $N3 $N4 2"
export Na=(0 $N1 $N2 $N3 $N4 2) #����array �˥ѥ�᥿����, ��0���Ǥϥ��ߡ����裵���Ǥϥץ���P1(m=10)��P2(m=10)��
export NM=${Na[1]};for i in 2 3 4 ;do if [ $NM -lt ${Na[$i]} ]; then NM=${Na[$i]}; fi ;done #NM�˺�����8������
#echo "#Na[@]=${Na[@]}, Na[1]=${Na[1]}, Na[2]=${Na[2]}", Na[3]=${Na[3]}", Na[4]=${Na[4]}, NM=$NM"; #��ǧ
export fas="$f1 $f2 $f3 $f4 2"
export fa=(0 $f1 $f2 $f3 $f4 2)
export NMA=0;for i in 1 2 3 4 ;do NMA=`expr ${NMA} + ${Na[$i]}`; done #NM
export mL1s="20 50 20 50 20 50"
export mL1=(0 20 50 20 50 20 50); #�ؽ���20,50 N1,N2,N3,N4���Ф���ؽ���ǥ�βٽż���m���Ǹ��20,50�ϥץ��ȥ�ǥ��m
export objs="ST ST OS OS";  #
export obj=(0 "ST" "ST" "OS" "OS");  #N1,N2,N3,N4���Ф���������Ū#export obj=(0 "S" "S" "O" "O");  #N1,N2,N3,N4���Ф���������Ū #
export mX1s="10 20 30 40 50 60"
export mX1=(0 10 20 30 40 50 60); #�ƥ��Ȥ�10-60
