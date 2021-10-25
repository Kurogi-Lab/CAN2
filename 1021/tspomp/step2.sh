source $d0/d1.env         #export d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1
source $d1/N-L2.env       #export N=N:190,55,75
export Sth=0.8 n_seed=30 TP0="2100" phase="" ID=3
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -phase "$phase" -ID "$ID"
#### export phase=2 #for avoiding the excesution of 1st phase again
source $d0/d1.env
echo "#saved in d1=$d1"         >> $d0/cmd-io-sum.dat
tail -2 $d1/cmd.sh >> $d0/cmd-io-sum.dat
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
emacs $d0/cmd-io-sum.dat
