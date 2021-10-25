export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc
mkdir -p $d0
#######
#(1) step 1
#(1-1) 1st step  and 1st phase (learning and predictin phase) by tspredv3.c
#(1-2) 1st-step and 2nd phase (Hierachical classification phase) by tspredv3prob1c and kmeans2_kuro.py (K=2) method)
#######
date > $d0/cmd-io-sum.dat
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc
export N="N:5-300:5" Sth=0.5 n_seed="1" TP0="2100" phase="" ID=1
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -phase "$phase" -ID "$ID"
source $d0/d1.env
echo "#saved in d1=$d1"         >> $d0/cmd-io-sum.dat
cat $d1/cmd.sh >> $d0/cmd-io-sum.dat
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
emacs $d0/cmd-io-sum.dat&
