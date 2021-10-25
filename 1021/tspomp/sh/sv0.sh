#!/bin/bash
###
####################################
#copy&paste from here for step0  #set basic environments 
####################################
make
######
######Tune&Confirm (No.1) from here
###platform=SY for Shigeta and Yamochi, K for Komatsu !!!!!!!!!!!!!!!!!!!!
export platform=K　#platform=K for Komatsu 
export platform=SY #platform=SY for Shigeta and Yamochi
export platform=Ku20omp20 # u20 for ubuntu20.04 20210618 u20@susanoo SPTK with icc new print_mfcc print"%g" after initialize 12voicedata
#export platform=Ku20omp21 # for test
export platform=Ku20omp22 # for test 20210810
###Tune&Confirm (No.1) to here
######
#export d0=~/sotu/2012/12voicedata_ueki/             #old
#export dl=../../12voicedata_ueki_all; mkdir -p $dl  #old
export d0=~/data/12voicedata_ueki/                   #new20210618
export dl=~/data/12voicedata_ueki_all; mkdir -p $dl  #new20210618
export dn=${dl}_n; mkdir -p $dn #save normalized speech signal
export dm=${dl}_m; mkdir -p $dm           #folder for saving mixed speech
###############
#[1.1a and 1.1b] 小松君は不足ファイルを置き換えて,fnerrを空集合にする, 矢持さん，重田君は元に戻す。
###############
#####
if [ "${platform:0:1}" = "S" ];then
## [1.1a] 矢持さん、重田君は次を実行する(Yamochi,Shigeta)
## mmt-san2とfhs-hachi5が不足したまま、L=1:2:3:4:5:6:7:8:9:10 nf=$((7*10*10-2))=698個のデータで実験する
###
export L=1:2:3:4:5:6:7:8:9:10 nf=$((7*10*10-2)) fnerr=mmt-san2:fhs-hachi5 
export D=zero:ichi:ni:san:si:go:roku:nana:hachi:kyu
export S=fhs:fms:mkk:mko:mmt:mnh:mym
#rm $dn/mmt-san2.dat $dn/fhs-hachi5.dat #(0.3a)を行った場合。これはしなくてもよいが念のため元に戻した方が間違わない
###
else #if [ "${platform:0:1}" = "K" ];then  #else for if [ "${platform:0:1}" = "S" ];then
###
##[1.1b] 小松君は，次を実行する(Komatsu)
## mmt-san2をmmt-san10、fhs-hachi5をfhs-hachi10で置き換えて、L:1:2:3:4:5:6:7:8:9 nf=$((7*10*9))=630個のデータで実験する。
###
if [ ! -e $dn/mmt-san2.dat ]; then cp $dn/mmt-san10.dat $dn/mmt-san2.dat; fi
if [ ! -e $dn/fhs-hachi5.dat ]; then cp $dn/fhs-hachi10.dat $dn/fhs-hachi5.dat; fi
export L=1:2:3:4:5:6:7:8:9 nf=$((7*10*9)) fnerr='_' #fnerr='_' # for no error file
export D=zero:ichi:ni:san:si:go:roku:nana:hachi:kyu
export S=fhs:fms:mkk:mko:mmt:mnh:mym
fi #closing if [ "${platform:0:1}" = "S" ];then
######
echo -e "\n\nplatform=$platform with nf=$nf fnerr=$fnerr L=$L"
export R=1 #R=1:0.8:0.6:0.4:0.2
######
######Tune&Confirm (No.2) from here #select method and settings
##################
######### #LPC+SE best  ###############
###export k=20 l=5 ns=120 FD=sC;
###export k=23 l=5 ns=120 FD=sC;
######
###export method="LPC+SE",${k},${l},${FD},${ns} #LPC+SE(spectral envelope)  #best?F0.734
###############
#MFCC best iconip21 #Params for AFME0=/home/kuro/data/12voicedata_ueki_all_MFCCl22m20n22E0R1_Ku20omp20/MFCCtrain_xy.dat
###############
export l=22 n_MFCC=20 n_MFCCFB=22 E_MFCC=0;#**no EnergyF91.03
export  method=MFCC,${l},${n_MFCC},${n_MFCCFB},${E_MFCC},${N} #best?F0.893
export dr=${dl}_MFCCl${l}m${n_MFCC}n${n_MFCCFB}E${E_MFCC}R${R}_${platform}; mkdir -p $dr  #
############
#CAN2+PD best iconip21 #Params for AFCa07b20=~/data/12voicedata_ueki_all_CAN2k20N50a0.7b20R1_Ku20omp20/pP1F2x23G3x0.5m0train_xy.dat 
############
export k=20 N=50 a=0.7 b=20 s=1 FD=pP1 nr=2 na=23 nG=3 sG=0.5 mel=0; #-mbas 2:50:1.6:1
### 
export method="CAN2q,${k},${N},${a},${b},${s}:MFCC,${fs_kHz},${m_mfcc},${n_mfcc}" #CAN2+pole distribution
export dr=${dl}_CAN2k${k}N${N}a${a}b${b}R${R}_${platform}; mkdir -p $dr
#export method="CAN2+PD,${k},${N},${a},${b},${s},${FD},${nr},${na},${nG},${sG},${mel},${N2},${a2},${b2},${s2}" #CAN2+pole distribution
export method="CAN2q,${k},${N},${a},${b},${s}:PD,${FD},${nr},${na},${nG},${sG}" #CAN2+pole distribution
#export fs_kHz=8 m_mfcc=20 n_mfcc=22
############
#LPCSPTK #for mel-filterbank?
export k=19 l=21 n=128 window=1 n_melfb=128;# best #n for n-FFT
export method="LPCSPTK,${k},${l},${n},${window}:M2SES,${n_melfb}"
export dr=${dl}_LPCSPTKk${k}l${l}n${n}R${R}_${platform}; mkdir -p $dr  
############
#LPCSE1 best iconip21 #Params for AFLk19l20n64=/home/kuro/data/12voicedata_ueki_all_LPCSE1k19l20n64R1_Ku20LPCw1/LPCSE1train_xy.datexport k=19 l=21 n=64 N=120 window=1;# best
export k=19 l=21 n=64 window=0 n_melfb=128;# best #n for n-FFT
export method="LPCSE1,${k},${l},${n},${window}"
export dr=${dl}_LPCSE1k${k}l${l}n${n}w${window}R${R}_${platform}; mkdir -p $dr
# step1.2 -> step2b2
########################
######Tune&Confirm (No.2) to here
#### set dr (folder-name to save the results)
echo -e "\n\n###Check the settings:\n`ls $dm/* 2>/dev/null|wc -l` files in \$dm=$dm. \n`ls ${dr}/ 2>/dev/null|wc -l` files in \$dr=$dr. (Files in \$dr is created by the following steps)\n\$method=${method}\n###\n#After creating the files in \$dm by step 1.1,\n#goto step1.2-> step2b.2 for \$method=MFCC... and \$method=LPCSE..., \n#goto step1.2-> step2a.1->step2a.2->step2a.3 for \$method=CAN2+PD.., \n###\n"
####################################
#copy&paste to here for step0  #set basic environments 
####################################

