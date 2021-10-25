#!/bin/bash
#
source exp800-20200128.sh
#if [ "$d0" == "" ]; then export d0=../../result-mspc; fi
#if [ "$seed" == "" ]; then export seed=13; fi
#export a=0.7 b=1 tt=100;
#export d1=${d0}/a${a}b${b}tt${tt}s${seed}; if [ ! -e $d1 ]; then mkdir $d1;fi
#make all-clean;make CC=icc;    #uncomment if necessary
#export tS="tS:0.01"; #デフォールトのサンプリング周期tS="tS:0.01";
######
#仮想サンプリング周期はAP_TS1=0.5 (see apc_crane.c)";
export LANG=C
export stab=""
date1=`date`
export cmS0="20 50" NN="10 11" it=10 update=0 umax="umax:10:1";sh mspctrain160518.sh #-->$d1/f1234.dat学習時
#export cmS0="20 50" NN="10 11" it=10 update=0 umax="umax:10:1";sh mspctrain160518.sh #-->$d1/f1234.dat学習時 ICONIP2019?
date2=`date`
export cmS1=`seq 10 5 60` fS="f1 f2 f12 f3 f4 f34" umax="umax:10:0" NM=8 DISP=0;source $d1/f1234.dat;sh mspctest160920.sh #テスト時
date3=`date`
#export cmS0="20 50" NN="2 4 6 8" it=10 update=0 umax="umax:10:1";sh mspctrain160518.sh #-->$d1/f1234.dat学習時
#export cmS1="10 15 20 25 30 35 40 45 50 55 60" fS="f1 f2 f12 f3 f4 f34" umax="umax:10:0" NM=8 DISP=0;source $d1/f1234.dat;sh mspctest160920.sh #テスト時
cp ${d1}/f1234.dat $d1/f12345.dat
cat ${d1}/f1234.dat|awk '{printf("#%s\n",$0);}'
cat ${d1}/mspcresult.dat|awk '{printf("#%s\n",$0);}'
echo "date1=$date1 date2=$date2 date3=$date3"

