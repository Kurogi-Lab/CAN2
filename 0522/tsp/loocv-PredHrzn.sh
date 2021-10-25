#/bin/bash
make
d00=../../result-chaospred; mkdir -p $d00
#../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt*
if [ "$fbc" = "" ];then export fbc=lorenz1e-8T0.025n10000p256m1_gmp ;fi
if [ "$ddc" = "" ];then export ddc=../../chaos.data ;fi
#if [ "$n_seed" = "" ];then export n_seed=1 ; fi
#if [ "$N" = "" ];then export N=N:5-300:5 ;fi
if [ "$TP0" = "" ];then export TP0=`seq 2000 100 4900` ; fi
if [ "${n_seed_S}" = "" ];then export n_seed_S="1" ; fi #_A=Array
if [ "${N_S}" = "" ];then export N_S="N:5-300:5" ;fi                 #_A=Array
echo "###N_S=$N_S"
echo "###n_seed_S=$n_seed_S"
export N_A=(`echo $N_S`) #echo "N_S=${N_S} N_A=${N_A[*]}"
export n_seed_A=(`echo $n_seed_S`) 

#
export d0=$d00/$fbc; mkdir -p $d0
#export N=N:10-300:10; # export N=N:5-300:5; #export N=N:5-300:2; #
export tr1=2000; #tr1=5000;
#export n_seed=50
#ddc=../../chaos.data
fny=$ddc/${fbc}.txt # fny=~/sotu/2017/chaos/data/${fbc}.txt
export Ey=15
export fnlog=chaospred2019.log
###############
#####step 1
###############
#echo "step=$step TP0=$TP0"
#if [ "$step" = "1" ];then
if [ "$step" = "1" -o "$step" = "1+2" -o "$step" = "" ];then
make data-clean
cat /dev/null > $d0/$fnlog
for tp0 in $TP0; do #for research study
#for tp0 in 2000 2100 2200 2300 2400 2500 2600 2700 2800 2900 3000 3100 3200 3300 3400 3500 3600 3700 3800 3900 4000 4100 4200 4300 4400 4500 4600 4700 4800 4900; do #
rm --force lossall.dat tspall.dat tspall_id.dat
export tp1=`bc.sh ${tp0}+500` #export tp1=`expr $tp0 + 500` #export tp1=`expr $tp0 + 800` #
export t=0-${tr1}:${tp0}-${tp1};
export K="10" #export K="8" #
export KS=$K #export KS=${K//+/ }; #replace "+" by " "
echo "KS=$KS"
for k in ${KS} ;do
export nN_A=${#N_A[@]}
export nN_A1=`bc.sh "${nN_A}-1"`
for it in `seq 0 ${nN_A1}` ;do
export N=${N_A[${it}]}
export n_seed=${n_seed_A[${it}]}
for s in `seq 1 ${n_seed}`;do
echo "#######################seed=${s}"
export cmd="./tspredv3 $fny $t mp:1:1:1 DiffMode:0 Hosei:0 $N M:1-1:1 ib:0:0:0:0 rsa:-1:1:1 k:${k} y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:100 vt:0.5 vr:10 lossall:1 DISP:0 e4t:0 e4p:0 nop:1 seed:${s}"
#export cmd="./tspredv3 $fny $t mp:1:1:1 DiffMode:0 Hosei:0 $N M:1-1:1 ib:0:0:0:0 rsa:2:0.7:1:50 k:${k} y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:100 vt:0.5 vr:10 lossall:1 DISP:0 e4t:0 e4p:0 seed:${s}"
echo $cmd;time $cmd ##yp(t) saved in tspall.dat
done # for s in `seq 1 ${n_seed}`;do
done # for it in `seq 1 ${#N_A[@]}` ;do
done # for k in ${KS}; do
#
export d1=$d0/t${t}k${K}${N}ID${ID} ##export d1=../result-timeseries/t${t}k${K}${N}

mkdir -p $d1
#echo "check d1=$d1"
for f in lossall.dat tspall.dat tspall.plt tspall_id.dat; do if [ -e $f ]; then cp $f $d1; fi; done #tspall.plt only for DISP:2
#for f in lossall.dat tspall.dat tspall.plt tspall_id.dat; do if [ -e $f ]; then cp $f $d1; fi; done #tspall.plt only for DISP:2
###(1.2) choose best prediction and probability
cmd1="tspredv3prob1 ds:$d1 at:-18.5_18.5:40 Sth:.5 e4H:$Ey Hth:.8,0,999 ftr:$fny DISP:0 "  #change Sth if necessary
#cmd1="tspredv3prob1 ds:$d1 at:-18.5_18.5:40 Sth:.5 e4H:$Ey Hth:.8,0,999 ftr:$fny DISP:2"  #change Sth if necessary
#cmd1="tspredv3prob1 ds:$d1 at:-18.5_18.5:40 Sth:.9 e4H:$Ey Hth:.8,0,999 ftr:$fny DISP:0"  #change Sth if necessary
echo "$cmd1" >> $d0/$fnlog
#$cmd1 >> $fnlog necessary?
##
## $fnlog contains data 'xN15(S0.117389),5<15<300 ,oN20(S0.486892),5<20<300 '
##saved tspAll.dat tspSth.dat yg.dat tspp.dat tp/typ.dat
##
for f in SLH.dat; do cp $f $d1; done
echo "###Confirm by '$cmd1'";
date
done # for tp0
fi
###############
#####step 2
###############
if [ "$step" = "2" -o "$step" = "1+2" -o "$step" = "" ];then
#d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:200-700k10N:10-300:10
#export fnlog=$d0/chaospred2019.log
#export Ey=15
######
### Do tspredv3prob1 again for kmeans2_kuro.py
######
cat $d0/$fnlog |awk 'BEGIN{Ey=ENVIRON["Ey"]}{
if(substr($1,1,8)=="tspredv3"){
s=substr($2,4);match(s,/:.*/);tp0=substr(s,RSTART+1,4);
d1=substr($2,4,length($2));
printf("export d1=%s\n",d1);
printf("export cmd=\047%s %s %s %s %s %s %s DISP:0\047 ;echo \044cmd;\044cmd\n",$1,$2,$3,$4,$5,$6,$7);
printf("python ./kmeans2_kuro.py -d1 \044d1 -fnyp tspSth.dat -fnyg yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey %s -hh 0 -DISP 0 -tp0 %s\n",Ey,tp0);}
}' >$d0/cmd.sh
#cat $d0/$fnlog |awk '{if(substr($1,1,8)=="tspredv3") printf("%s\n",$0); else if(substr($1,1,2)=="#H") printf("%s\n", $0);}' >$d0/cmd.dat
#cat $d0/cmd.dat |awk 'BEGIN{Ey=ENVIRON["Ey"]}{
#s=substr($2,4);match(s,/:.*/);tp0=substr(s,RSTART+1,4);
#printf("export cmd=\047%s %s %s %s %s %s %s DISP:0\047 ;echo \044cmd;\044cmd\n",$1,$2,$3,$4,$5,$6,$7);#20171030
#printf("python ./kmeans2_kuro.py -d1 %s -fnyp tspSth.dat -fnyg yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey %s -hh 0 -DISP 0 -tp0 %s\n",substr($2,4,length($2)),Ey,tp0);
#}' >$d0/cmd.sh
source $d0/cmd.sh > $d0/cmd.out
#bash $d0/cmd.sh > $d0/cmd.out
##
##python ./kmeans2_kuro.py -fnyp ./tmp/tspSth.dat -fnyg ./tmp/yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey $Ey -hh 0 -DISP 0 -tp0 2000
##$d1/cmd.out contains data 'xN15(S0.117389),5<15<300 ,oN20(S0.486892),5<20<300 '
##  saved tspSth_id.dat tspall_id.dat for kmeans2_kuro.py
#   tspAll.dat tspSth.dat yg.dat(ground-truth) tspp.dat tp/typ.dat 
##
cat $d0/cmd.out | grep '#class hg deg' >$d0/hgdeg.dat
cat $d0/cmd.out | grep 'L2 c\|\*\*\*\|#class hg deg' ##cat $d0/cmd.out | grep '\*\*\*\|#class hg deg'
head -30 $d0/hgdeg.dat > $d0/hgdeg30.dat
echo "###Results are saved in d0=$d0"
#cat $d1/cmd.dat
echo "###d0=$d0"
cat $d0/hgdeg.dat
echo -n "###d0=$d0";cat $d0/hgdeg.dat|awk 'BEGIN{n=0;m=0;min=1e3;max=0;}{h[n]=$3;n++;m+=$3;if(min>$3)min=$3;if(max<$3)max=$3}END{m/=n;v=0;for(i=0;i<n;i++){v+=(h[i]-m)*(h[i]-m);}printf(" PH min max mean std=%.0f %.0f %.0f %.0f\n",min,max,m,sqrt(v/n));}'
#finish
#cat $d0/tspSth_id.dat | awk '{sed -n $1P tspall_id.dat}' 
fi
#mkdir -p tmp
#printenv > tmp/current.env
#echo "d0=$d0" >> tmp/current.env
#echo "d1=$d1" >> tmp/current.env
###############
#####step 3
###############
