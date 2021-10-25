#!/bin/bash
#
if [ "$d0" == "" ]; then export d0=../../result-mspc; fi
if [ "$seed" == "" ]; then export seed=13; fi
export a=0.7 b=1 tt=100;
export d1=${d0}/a${a}b${b}tt${tt}s${seed}; if [ ! -e $d1 ]; then mkdir $d1;fi
#export d0=../result-mspc170129; if [ ! -e $d0 ]; then mkdir $d0;fi
#rm -rf $d0
#export d0=../result-mspc190522; if [ ! -e $d0 ]; then mkdir $d0;fi
#export d0=../result-mspc191228; if [ ! -e $d0 ]; then mkdir $d0;fi
#f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
#ny=5;nu=5;sed -e s/"AP_ny "/"AP_ny ${ny}\/\/"/ -e s/"AP_nu "/"AP_nu ${nu}\/\/"/ $f1 > $f0 ; make CC=icc   ##1st trial
#f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
#export d1=${d0}/a${a}b${b}tt${tt}; if [ ! -e $d1 ]; then mkdir $d1;fi
#export d1=${d0}/a${a}b${b}tt${tt}nu${nu}; if [ ! -e $d1 ]; then mkdir $d1;fi
make all-clean;make CC=icc;    #uncomment if necessary
export tS="tS:0.01"; #デフォールトのサンプリング周期tS="tS:0.01";
#export tS="tS:0.1"; #デフォールトのサンプリング周期tS="tS:0.01";#export tS="tS:0.25"; #デフォールトのサンプリング周期tS="tS:0.01";
######
#仮想サンプリング周期はAP_TS1=0.5 (see apc_crane.c)";
#export cmS0="20 50" NN="10 11" it=10 update=0 umax="umax:10:1";sh mspctrain160518.sh #-->$d1/f1234.dat学習時
##export cmS0="20 50" NN="10 11" it=10 update=0 umax="umax:10:1";sh mspctrain160518.sh #-->$d1/f1234.dat学習時 ICONIP2019?
#export cmS1=`seq 10 5 60` fS="f1 f2 f12 f3 f4 f34" umax="umax:10:0" NM=8 DISP=0;source $d1/f1234.dat;sh mspctest160920.sh #テスト時
##export cmS0="20 50" NN="2 4 6 8" it=10 update=0 umax="umax:10:1";sh mspctrain160518.sh #-->$d1/f1234.dat学習時
##export cmS1="10 15 20 25 30 35 40 45 50 55 60" fS="f1 f2 f12 f3 f4 f34" umax="umax:10:0" NM=8 DISP=0;source $d1/f1234.dat;sh mspctest160920.sh #テスト時
#
#cp $d1/f1234.dat $d1/f12345.dat
#cat $d1/f1234.dat|awk '{printf("#%s\n",$0);}'
#cat $d1/mspcresult.dat|awk '{printf("#%s\n",$0);}'
