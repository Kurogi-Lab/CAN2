#!/bin/bash
if [ "$d0" = "" ]; then export d0=../../result-mspc; fi
if [ "$a" = "" ]; then export a=0.7; fi
if [ "$b" = "" ]; then export b=1; fi
if [ "$d1" = "" ]; then export export d1=${d0}/a${a}b${b}tt${tt}s${seed}_mspcomp; fi
#export d0=../../result-mspc; mkdir -p $d0
#export a=0.7 b=1 tt=100; #good for Ubuntu12.04
#export d1=${d0}/a${a}b${b}tt${tt}s${seed}; 
mkdir -p $d0
mkdir -p $d1
make data-clean
#if [ ! -e $d1 ]; then mkdir $d1;fi  #include information of seed20200127
#export a=0.7 b=1 seed=2 tt=100;  #good for Ubuntu14.04
#export a=0.7 b=1 seed=13 tt=100; #good for Ubuntu12.04
#export a=0.7 b=1 seed=21 tt=100; #good for Ubuntu12.04
#rm -rf $d0/*
#f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
#ny=5;nu=5;sed -e s/"AP_ny "/"AP_ny ${ny}\/\/"/ -e s/"AP_nu "/"AP_nu ${nu}\/\/"/ $f1 > $f0 ; make CC=icc emulate_crane4  ##1st trial
#f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
#export d1=${d0}/a${a}b${b}tt${tt}nu${nu}; if [ ! -e $d1 ]; then mkdir $d1;fi
#make all-clean;make #make CC=icc;    #uncomment if necessary
#make all-clean;make CC=icc;    #uncomment if necessary
export tS="tS:0.01"; #export tS="tS:0.1"; #デフォールトのサンプリング周期tS="tS:0.01";#export tS="tS:0.25"; #デフォールトのサンプリング周期tS="tS:0.01";
#仮想サンプリング周期はAP_TS1=0.5 (see apc_crane.c)";
export stab=""
#export date0=`date`
export T0=`date +%s`
#date1=`date`
if [ "$NN" = "" ]; then export NN="10 11"; fi
if [ "$cmS0" = "" ]; then export cmS0="20 50"; fi
if [ "$umax" = "" ]; then export umax="umax:10:1"; fi
export it=10 update=0;sh mspctrain160518.sh #-->$d1/f1234.dat学習時
#export cmS0="20 50" NN="10 11" it=10 update=0 umax="umax:10:1";sh mspctrain160518.sh #-->$d1/f1234.dat学習時
#export date1=`date`
export T1=`date +%s`
#date2=`date`
echo "#export cmS1=\`seq 10 5 60\` fS=\"f1 f2 f12 f3 f4 f34\" umax=\"umax:10:0\" NM=8 DISP=0; source $d1/f1234.dat;sh mspctest160920.sh" #テスト時
if [ ! -e $d1/f1234.dat ]; then sleep 2; fi
export cmS1="`seq 10 5 60`" fS="f1 f2 f12 f3 f4 f34" umax="umax:10:0" NM=8 DISP=0;source $d1/f1234.dat;sh mspctest160920.sh #テスト時
#export cmS1=`seq 10 5 60`;
#export fS="f1 f2 f12 f3 f4 f34";
#echo "#cmS1=$cmS1 fS=$fS umax=$umax"
#export umax="umax:10:0";
#echo "#cmS1=$cmS1 fS=$fS umax=$umax"
#export NM=8 DISP=0;
#echo "#cmS1=$cmS1 fS=$fS umax=$umax"
#export date2=`date`
export T2=`date +%s`
#date3=`date`
cp $d1/f1234.dat $d1/f12345.dat
cat $d1/f1234.dat|awk '{printf("#%s\n",$0);}'
cat $d1/mspcresult.dat|awk '{printf("#%s\n",$0);}'
#echo "date1=$date1 date2=$date2 date3=$date3"
###
export DT=$((T1 - T0))
export H=$((DT / 3600))
export DT=$((DT % 3600 ))
export M=$((DT / 60 ))
export S=$((DT % 60))
#export date2=`date`
msg1="training=${H}:${M}:${S}"
#export LANG=C; echo "Elapsed Time=${H}:${M}:${S} (${date0} - ${date1}) for train"
export DT=$((T2 - T1))
export H=$((DT / 3600))
export DT1=$((DT % 3600))
export M=$((DT1 / 60))
export S=$((DT1 % 60))
#export date2=`date`
msg2="test=${H}:${M}:${S}"
#export LANG=C; msg2="test:${H}:${M}:${S}"
#export LANG=C; echo "Elapsed Time=${H}:${M}:${S} (${date1} - ${date2}) for test"
echo "#Elapsed time for ${msg1} and ${msg2}"
#export LANG=C; echo "#start=${date0} train-finish=${date1} test-finish=${date2}"
