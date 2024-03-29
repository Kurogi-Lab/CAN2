##############
# can2py: can2-python
### Do the following command first
###
### Execute 'make data-clean' for the first time
###
20211019
#regression
export d0=$PWD
cd ${d0}/can2py
export fn=Geo1d  ntrain=100 restest=50 extest=10 k=1;
python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export dst=${d0}/data/${fn}_${ntrain}_${restest}_${extest}
mkdir -p $dst
cp tmp/train.csv tmp/test.csv $dst
export fntrain=$dst/train.csv fntest=$dst/test.csv fnpred=$dst/pred.csv
export T=100 N=90 k=1;
#time python can2.py -fn $fntrain,$fntest,$fnpred -k $k -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,2.2,$T,5,50,350 --gpu -1 -DISP 1 -nop 1
time python can2.py -fn $fntrain,$fntest,$fnpred -k $k -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1 -nop 1 -s 0
100(0.725s) 8.251e-06 3.231e-05 #ep(time),MSEtr,MSE n100,71 k1 N60 T100,1000 seed0 nop1
100(1.050s) 7.310e-06 4.198e-05 #ep(time),MSEtr,MSE n100,71 k1 N90 T100,1000 seed0 nop1
100(1.228s) 5.843e-06 2.627e-05 #ep(time),MSEtr,MSE n100,71 k1 N100 T100,1000 seed0 nop1***?
100(1.249s) 5.843e-06 2.627e-05 #ep(time),MSEtr,MSE n100,71 k1 N110 T100,1000 seed0 nop1
100(1.236s) 5.843e-06 2.627e-05 #ep(time),MSEtr,MSE n100,71 k1 N120 T100,1000 seed0 nop1

100(1.182s) 5.843e-06 2.627e-05 #ep(time),MSEtr,MSE n100,71 k1 N100 T100,1000 seed1 nop1

export fn=Geo1d  ntrain=100 restest=50 extest=10 k=1;
export fntrain=$dst/train.csv fntest=$dst/test.csv fnpred=$dst/pred.csv
export T=100 N=60 k=1 Tpinv=-1 seed=1 m_cpu=0 b=100 a=2.2 nop=1
python ensrs.py -fn $fntrain,$fntest,$fnpred -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 -DISP 0 -Tpinv $Tpinv -s $seed -nop $nop -bag $b,$a,$seed,$m_cpu
[100,-1](53.1s) 3.052e-05 #[T,Tpinv] MSE n100,71 k1 N40 b100 a2.2 s1 m6 seed1 nop1
[100,-1](55.5s) 2.105e-05 #[T,Tpinv] MSE n100,71 k1 N50 b100 a2.2 s1 m6 seed1 nop1***
[100,-1](74.9s) 2.275e-05 #[T,Tpinv] MSE n100,71 k1 N60 b100 a2.2 s1 m6 seed1 nop1

[100,-1](113.5s) 2.413e-05 #[T,Tpinv] MSE n100,71 k1 N50 b200 a2.2 s1 m6 seed1 nop1
[100,-1](154.3s) 2.210e-05 #[T,Tpinv] MSE n100,71 k1 N60 b200 a2.2 s1 m6 seed1 nop1***
[100,-1](159.7s) 2.511e-05 #[T,Tpinv] MSE n100,71 k1 N70 b200 a2.2 s1 m6 seed1 nop1
#python ensrs.py -fn $fntrain,$fntest,$fnpred -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,2.2,$T,5,50,350 -DISP 0 -Tpinv $Tpinv -s $seed -nop $nop -bag $b,$a,$seed,$m_cpu
#[100,-1](154.2s) 2.209e-05 #[T,Tpinv] MSE n100,71 k1 N60 b200 a2.2 s1 m6 seed1 nop1
#[100,-1](164.8s) 2.510e-05 #[T,Tpinv] MSE n100,71 k1 N70 b200 a2.2 s1 m6 seed1 nop1


#time-series
export T=100 Tpinv=-1 k=8 N=50 seed=0 tp0=2000 tpD=1 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1
export fn=$d0/data/lorenz1e-8T0.025n10000p256m1_gmp.txt
export fns=$d0/data/lorenz1e-8T0.025n10000p256m1_gmp+null+N50k10s${seed}.net
python can2.py -fn $fn -k $k -t 0-2000:$tp0-$(($tp0+500)):$tpD:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y" -fns $fns

100(14.734s) 4.604e-05 8.478e-05 #ep(time),MSEtr,MSE n1992,500 k8 N50 T100,-1 seed0 nop1 t0-2000:2000-2500:1:15H170 predTime0.016s
100(15.112s) 5.371e-05 8.513e-05 #ep(time),MSEtr,MSE n1992,500 k8 N50 T100,-1 seed2 nop1 t0-2000:2000-2500:1:15H220 predTime0.017s
100(15.267s) 6.829e-05 1.070e-04 #ep(time),MSEtr,MSE n1992,500 k8 N50 T100,-1 seed1 nop1 t0-2000:2000-2500:1:15H129 predTime0.017s
#bagging
export T=100 Tpinv=-1 k=8 N=50 seed=10 b=20 a=1.0 tp0=2000 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1 m_cpu=0 fn=$d0/data/lorenz1e-8T0.025n10000p256m1_gmp.txt
make data-clean
python ensrs.py -fn $fn,,tmp/msp${tp0}.dat -k $k -t 0-2000:$tp0-$(($tp0+500)):1:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 0 -Tpinv $Tpinv -nop $nop -y " $y" -bag $b,$a,$seed,$m_cpu
[100,-1](154.0s) #[T,Tpinv] k8 N20 b20a0.7s0m6 nop1 t0-2000:2000-2500:1:15H129 seed0
[100,-1](165.1s) #[T,Tpinv] k8 N30 b20a0.7s0m6 nop1 t0-2000:2000-2500:1:15H142
[100,-1](167.5s) #[T,Tpinv] k8 N40 b20a0.7s0m6 nop1 t0-2000:2000-2500:1:15H145
[100,-1](172.6s) #[T,Tpinv] k8 N50 b20a0.7s0m6 nop1 t0-2000:2000-2500:1:15H222 ***
[100,-1](174.1s) #[T,Tpinv] k8 N60 b20a0.7s0m6 nop1 t0-2000:2000-2500:1:15H157

[100,-1](96.9s) #[T,Tpinv] k8 N10 b20a0.7s10m6 nop1 t0-2000:2000-2500:1:15H33 seed10
[100,-1](153.8s) #[T,Tpinv] k8 N20 b20a0.7s10m6 nop1 t0-2000:2000-2500:1:15H158 ***
[100,-1](167.9s) #[T,Tpinv] k8 N30 b20a0.7s10m6 nop1 t0-2000:2000-2500:1:15H158
[100,-1](170.2s) #[T,Tpinv] k8 N40 b20a0.7s10m6 nop1 t0-2000:2000-2500:1:15H158


#k=10
export T=100 Tpinv=-1 k=10 N=50 seed=2 tp0=2000 tpD=1 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1
export fn=$d0/data/lorenz1e-8T0.025n10000p256m1_gmp.txt
export fns=$d0/data/lorenz1e-8T0.025n10000p256m1_gmp+null+N50k10s${seed}.net
python can2.py -fn $fn -k $k -t 0-2000:$tp0-$(($tp0+500)):$tpD:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y" -fns $fns
100(16.821s) 4.635e-05 1.238e-04 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed0 nop1 t0-2000:2000-2500:1:15H22 predTime0.018s
100(16.885s) 4.113e-05 1.174e-04 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed1 nop1 t0-2000:2000-2500:1:15H194 predTime0.018s
100(17.034s) 4.211e-05 1.293e-04 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed2 nop1 t0-2000:2000-2500:1:15H101 predTime0.017s
100(16.696s) 4.206e-05 6.654e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 t0-2000:2000-2500:1:15H222 predTime0.021s
#bagging
export T=100 Tpinv=-1 k=10 N=50 seed=10 b=20 a=1.0 tp0=2000 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1 m_cpu=0 fn=$d0/data/lorenz1e-8T0.025n10000p256m1_gmp.txt 
python ensrs.py -fn $fn,,tmp/msp${tp0}.dat -k $k -t 0-2000:$tp0-$(($tp0+500)):1:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 0 -Tpinv $Tpinv -nop $nop -y " $y" -bag $b,$a,$seed,$m_cpu
[100,-1](226.9s) #[T,Tpinv] k10 N50 b20a1.0s10m6 nop1 t0-2000:2000-2500:1:15H159 seed0
[100,-1](227.1s) #[T,Tpinv] k10 N50 b20a1.0s0m6 nop1 t0-2000:2000-2500:1:15H158 seed1

[100,-1](333.2s) #[T,Tpinv] k10 N50 b30a1.0s10m6 nop1 t0-2000:2000-2500:1:15H158 seed=10


####
20210331
python can2.py -fn tmp/train199.dat,tmp/test199.dat,tmp/geo1dpred-geo1dtrain+geo1dtest+b200a2.2s1N60k1j199.dat -k 1 -in 60,6,0.2,3,0,0.5,0.2 -s 1 -ex 1,0.05,2.2,100,5,50,350 -Tpinv -1 -s 1 -nop 1 -DISP 0 -g 0
100(54.302s) 3.198e-07 5.768e-06 #ep(time),MSEtr,MSE n440,71 k1 N60 T100,-1 seed1 nop1 -g 0
100(1.563s) 6.166e-06 2.087e-05 #ep(time),MSEtr,MSE n440,71 k1 N60 T100,-1 seed1 nop1 -g -1

20210322
####
#(1) データ作成（下記の20191101<-20191031nightの4-1と同じ）
export fn=Geo1d ntrain=50 restest=50 extest=10 k=1;
export fn=Geo1d ntrain=1000 restest=50 extest=10 k=1;
export fn=Geo1d ntrain=200 restest=50 extest=10 k=1;
python makesamples.py -msd $fn,$ntrain,$restest,$extest #
#
mkdir -p ../data
dst=../data/Geo1d_${ntrain}_${restest}_${extest}/
mkdir -p $dst
cp tmp/train.csv tmp/test.csv $dst
#
#(2) ensrs.pyによる学習と予測
#(2-1) 使用例
export fntrain=$dst/train.csv fntest=$dst/test.csv fnpred=$dst/pred.csv
export T=100 N=60 k=1 Tpinv=-1 seed=1 m_cpu=0 b=200 a=2.2 nop=1 
python ensrs.py -fn $fntrain,$fntest,$fnpred -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,2.2,$T,5,50,350 -DISP 0 -Tpinv $Tpinv -s $seed -nop $nop -bag $b,$a,$seed,$m_cpu
#(2-2) 結果
[100,-1](112.4s) 2.896e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s1 m8 seed1 nop1 ubuntu20.04susanoo
[100,-1](547.5s) 8.319e-07 #[T,Tpinv] MSE n1000,71 k1 N60 b200 a2.2 s1 m8 seed1 nop1 ubuntu20.04susanoo

[100,-1](96.7s) 2.896e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s1 m12 seed1 nop1 ubuntu1404mesaho
[100,-1](125.8s) 2.896e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s1 m12 seed1 nop1 ubuntu20.04kuro-laptop
[100,-1](639.8s) 8.319e-07 #[T,Tpinv] MSE n1000,71 k1 N60 b200 a2.2 s1 m12 seed1 nop1 ubuntu20.04kuro-laptop

[100,-1](67.7s) 1.739e-04 #[T,Tpinv] MSE n50,71 k1 N60 b200 a2.2 s1 m12 seed1 nop1 ubuntu20.04kuro-laptop

export T=100 Tpinv=-1 k=10 N=50 seed=10 tp0=2000 tpD=1 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1
export fns=tmp/data/lorenz1e-8T0.025n10000p256m1_gmp+null+N${N}k${k}s${seed}.net
python can2.py -fn $d0/data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:$tpD:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y" -fns $fns
#result
100(16.696s) 4.206e-05 6.654e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 t0-2000:2000-2500:1:15H222 predTime0.021s


########################
20200122 development of bagging for timeseries 
########################
#(1) bug の修正
#(1-1) a bug in my_function.py L116,117  => 20200122 modified
#(1-2) ensrs.pyのtime-seriesのbugを修正
####
#(2) time series prediction by single can2
####
#(2-1) tr0-tr1=0-2000の学習と保存、tp0-tp1=2000-2500までの学習、
###
export T=100 Tpinv=-1 k=10 N=50 seed=10 tp0=2000 tpD=1 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1
export fns=tmp/lorenz1e-8T0.025n10000p256m1_gmp+null+N50k10s${seed}.net
python can2.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:$tpD:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y" -fns $fns
#result
#100(15.019s) 4.206e-05 6.654e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 t0-2000:2000-2500:1:15H222 predTime0.019s
###
#(2-2) tr0-tr1=0-2000の保存netを用いて、tp0=2000,2100,...,3000までの予測、
###
for tp0 in `seq 2000 100 3000` ; do
python can2.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:$tpD:$Ey -in '' -ex '' -fnl $fns --gpu -1 -DISP 1 -nop $nop
done
#result for seed=10
 t0-2000:2000-2500:1:15H222 predTime0.021s
 t0-2000:2100-2600:1:15H92 predTime0.020s
 t0-2000:2200-2700:1:15H162 predTime0.020s
 t0-2000:2300-2800:1:15H81 predTime0.019s
 t0-2000:2400-2900:1:15H61 predTime0.020s
 t0-2000:2500-3000:1:15H254 predTime0.027s
 t0-2000:2600-3100:1:15H127 predTime0.019s
 t0-2000:2700-3200:1:15H208 predTime0.019s
 t0-2000:2800-3300:1:15H138 predTime0.020s
 t0-2000:2900-3400:1:15H74 predTime0.019s
 t0-2000:3000-3500:1:15H150 predTime0.019s
#result for seed=1
100(14.674s) 4.113e-05 1.174e-04 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed1 nop1 t0-2000:2000-2500:1:15H194 predTime0.018s
 t0-2000:2000-2500:1:15H194 predTime0.019s
 t0-2000:2100-2600:1:15H99 predTime0.019s
 t0-2000:2200-2700:1:15H135 predTime0.020s
 t0-2000:2300-2800:1:15H69 predTime0.019s
 t0-2000:2400-2900:1:15H57 predTime0.020s
 t0-2000:2500-3000:1:15H135 predTime0.019s
 t0-2000:2600-3100:1:15H154 predTime0.020s
 t0-2000:2700-3200:1:15H84 predTime0.021s
 t0-2000:2800-3300:1:15H138 predTime0.019s
 t0-2000:2900-3400:1:15H72 predTime0.019s
 t0-2000:3000-3500:1:15H179 predTime0.019s
##result for N=100
100(17.451s) 4.191e-05 1.686e-04 #ep(time),MSEtr,MSE n1990,500 k10 N100 T100,-1 seed10 nop1 t0-2000:2000-2500:1:15H157 predTime0.021s
 t0-2000:2000-2500:1:15H157 predTime0.021s
 t0-2000:2100-2600:1:15H92 predTime0.021s
 t0-2000:2200-2700:1:15H268 predTime0.021s
 t0-2000:2300-2800:1:15H67 predTime0.021s
 t0-2000:2400-2900:1:15H202 predTime0.023s
 t0-2000:2500-3000:1:15H246 predTime0.025s
 t0-2000:2600-3100:1:15H153 predTime0.031s
 t0-2000:2700-3200:1:15H180 predTime0.021s
 t0-2000:2800-3300:1:15H138 predTime0.021s
 t0-2000:2900-3400:1:15H86 predTime0.023s
 t0-2000:3000-3500:1:15H271 predTime0.021s

####
#(3) time series prediction by bagging can2 with parallel processing (concurrent.features; see web pages)
####
make data-clean #to obtain learning time , Do make data-clean sometimes.
###
#(3-1) learn and save nets by bagging CAN2 (なお、b=1のときsingle CAN2と同じ）
###
export T=100 Tpinv=-1 k=10 N=50 seed=10 b=20 a=1.0 tp0=2000 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1 m_cpu=0 fn=/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt
 
python ensrs.py -fn $fn,,tmp/msp${tp0}.dat -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:1:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 0 -Tpinv $Tpinv -nop $nop -y " $y" -bag $b,$a,$seed,$m_cpu
#result
[100,-1](61.3s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2000-2500:1:15H159 (b=20: number of bags=20)
[100,-1](15.4s) #[T,Tpinv] k10 N50 b1a1.0s10m12 nop1 t0-2000:2000-2500:1:15H222   (b=1 == single can2; same as above (2-1))
###
#(3-2) tr0-tr1=0-2000の保存netを用いて、tp0=2000,2100,...,3000までの予測、
###
for tp0 in `seq 2000 100 3000` ; do
python ensrs.py -fn $fn,,tmp/msp${tp0}.dat -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:1:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 0 -Tpinv $Tpinv -nop $nop -y " $y" -bag $b,$a,$seed,$m_cpu
done
#
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2000-2500:1:15H159
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2100-2600:1:15H99
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2200-2700:1:15H213
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2300-2800:1:15H168
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2400-2900:1:15H297
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2500-3000:1:15H284
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2600-3100:1:15H185
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2700-3200:1:15H152
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2800-3300:1:15H198
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2900-3400:1:15H249
[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:3000-3500:1:15H240

###N=100
[100,-1](69.4s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2000-2500:1:15H193 with training net
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2000-2500:1:15H193
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2100-2600:1:15H93
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2200-2700:1:15H195
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2300-2800:1:15H71
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2400-2900:1:15H204
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2500-3000:1:15H249
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2600-3100:1:15H186
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2700-3200:1:15H156
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2800-3300:1:15H141
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:2900-3400:1:15H215
[100,-1](0.5s) #[T,Tpinv] k10 N100 b20a1.0s10m12 nop1 t0-2000:3000-3500:1:15H236

###a=2.2 b=50
[100,-1](328.5s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2100-2600:1:15H204
[100,-1](1.0s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2000-2500:1:15H158
[100,-1](0.9s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2100-2600:1:15H204
[100,-1](0.9s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2200-2700:1:15H225
[100,-1](1.0s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2300-2800:1:15H169
[100,-1](0.9s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2400-2900:1:15H75 ??
[100,-1](0.9s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2500-3000:1:15H285
[100,-1](0.9s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2600-3100:1:15H185
[100,-1](0.9s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2700-3200:1:15H153
[100,-1](1.0s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2800-3300:1:15H228
[100,-1](1.0s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:2900-3400:1:15H250
[100,-1](0.9s) #[T,Tpinv] k10 N50 b50a2.2s10m12 nop1 t0-2000:3000-3500:1:15H240
###a=2.2 b=50
[100,-1](628.2s) #[T,Tpinv] k10 N50 b100a2.2s10m12 nop1 t0-2000:2100-2600:1:15H205
[100,-1](358.1s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2000-2500:1:15H188
[100,-1](1.0s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2100-2600:1:15H96
[100,-1](1.0s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2200-2700:1:15H195
[100,-1](1.2s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2300-2800:1:15H181
[100,-1](1.1s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2400-2900:1:15H262
[100,-1](1.1s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2500-3000:1:15H252
[100,-1](1.1s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2600-3100:1:15H184
[100,-1](1.0s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2700-3200:1:15H298
[100,-1](1.2s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2800-3300:1:15H199
[100,-1](1.1s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:2900-3400:1:15H216
[100,-1](1.0s) #[T,Tpinv] k10 N100 b50a2.2s10m12 nop1 t0-2000:3000-3500:1:15H211


########################
20200118 development of bagging for timeseries ? 
########################
#NG##20200120 
#NG####
#NG## change -t option!!!!!!!
#NG###  -t tr0-tr1:tp0-tp1:tpD:tpG:tpEy ---> -t tr0-tr1:tp0-tp1:tpD:tpEy 
#NG###   
#NG####
#NG##time-series bagging 
#NG##make data-clean #to obtain actual time
#NG#export T=100 Tpinv=-1 k=10 N=50 seed=10 b=20 a=1.0 tp0=2000 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1 m_cpu=0 fn=/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 
#NG#python ensrs.py -fn $fn,,tmp/msp${tp0}.dat -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:1:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 0 -Tpinv $Tpinv -nop $nop -y " $y" -bag $b,$a,$seed,$m_cpu
#NG##
#NG#[100,-1](62.9s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2000-2300:1:15H224 ***? good only with seed=10 for tp0=2000 =>evaluate average
#NG#[100,-1](61.2s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2000-2300:1:15H72
#NG#[100,-1](61.3s) #[T,Tpinv] k10 N50 b20a1.0s2m12 nop1 t0-2000:2000-2300:1:15H69
#NG#[100,-1](60.6s) #[T,Tpinv] k10 N50 b20a1.0s3m12 nop1 t0-2000:2000-2300:1:15H97
#NG#[100,-1](62.7s) #[T,Tpinv] k10 N50 b20a1.0s4m12 nop1 t0-2000:2000-2300:1:15H63
#NG#[100,-1](60.7s) #[T,Tpinv] k10 N50 b20a1.0s5m12 nop1 t0-2000:2000-2300:1:15H57
#NG#[100,-1](60.5s) #[T,Tpinv] k10 N50 b20a1.0s6m12 nop1 t0-2000:2000-2300:1:15H31
#NG#[100,-1](61.7s) #[T,Tpinv] k10 N50 b20a1.0s7m12 nop1 t0-2000:2000-2300:1:15H22
#NG#[100,-1](60.6s) #[T,Tpinv] k10 N50 b20a1.0s8m12 nop1 t0-2000:2000-2300:1:15H20
#NG#[100,-1](62.1s) #[T,Tpinv] k10 N50 b20a1.0s9m12 nop1 t0-2000:2000-2300:1:15H87
#NG#[100,-1](61.9s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2000-2300:1:15H224
#NG#[100,-1](64.1s) #[T,Tpinv] k11 N50 b20a1.0s10m12 nop1 t0-2000:2000-2300:1:15H57
#NG#
#NG#[100,-1](61.9s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2000-2300:1:15H224
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2100-2600:1:15H90
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2200-2700:1:15H48
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2300-2800:1:15H154
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2400-2900:1:15H168
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2500-3000:1:15H195
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2600-3100:1:15H150
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2700-3200:1:15H86
#NG#[100,-1](0.5s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2800-3300:1:15H137
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s10m12 nop1 t0-2000:2900-3400:1:15H193
#NG#
#NG#[100,-1](61.2s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2000-2300:1:15H72
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2100-2600:1:15H100
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2200-2700:1:15H64
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2300-2800:1:15H98
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2400-2900:1:15H58
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2500-3000:1:15H158
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2600-3100:1:15H187
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2600-3100:1:15H187
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2700-3200:1:15H154
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2800-3300:1:15H138
#NG#[100,-1](0.4s) #[T,Tpinv] k10 N50 b20a1.0s1m12 nop1 t0-2000:2900-3400:1:15H188
#NG#
#NG#
#NG#
#NG#[100,-1](301.1s) #[T,Tpinv] k10 N50 b100a1.0s10m12 nop1 t0-2000:2000-2300:1:15H72
#NG#[100,-1](1906.7s) #[T,Tpinv] k10 N50 b300a2.2s10m12 nop1 t0-2000:2000-2300:1:15H96
#NG#[100,-1](1271.3s) #[T,Tpinv] k10 N50 b200a2.2s10m12 nop1 t0-2000:2000-2300:1:15H115
#NG#[100,-1](597.8s) #[T,Tpinv] k10 N50 b200a1.0s10m12 nop1 t0-2000:2000-2300:1:15H109
#NG#[100,-1](302.0s) #[T,Tpinv] k10 N50 b100a1.0s10m12 nop1 t0-2000:2000-2300:1:15H72
#NG#[100,-1](13.0s) #[T,Tpinv] k10 N50 b100a2.2s10m12 nop1 t0-2000:2000-2300:1:15H97
#NG#[100,-1](1.2s) #[T,Tpinv] k10 N60 b100a2.2s10m12 nop1 t0-2000:2000-2300:1:15H80
#NG#[100,50](931.4s) #[T,Tpinv] k10 N50 b100a2.2s10m12 nop1 t0-2000:2000-2300:1:15H5
#NG#[100,50](514.9s) #[T,Tpinv] k10 N50 b100a1.0s10m12 nop1 t0-2000:2000-2300:1:15H4
#NG#
#NG##time-series single 
#NG#export T=100 Tpinv=-1 k=10 N=50 seed=10 b=1 a=1.0 tp0=2000 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1 m_cpu=0 fn=/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 
#NG#python ensrs.py -fn $fn,,tmp/msp${tp0}.dat -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:1:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 0 -Tpinv $Tpinv -nop $nop -y " $y" -bag $b,$a,$seed,$m_cpu
#NG#
#NG#python can2.py -fn tmp/train000.dat,tmp/test2000.dat,tmp/tp2000-lorenz1e-8T0.025n10000p256m1_gmp+null+b1a1.0s10N50k10j0.dat -fns tmp/lorenz1e-8T0.025n10000p256m1_gmp+null+b1a1.0s10N50k10j0.net -k 10 -in 50,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,100,5,50,350 -Tpinv -1 -nop 1 -DISP 0 -y   -18.5,18.5,0,1 
#NG#python can2.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k 10 -t 0-2000:2000-2500:1:15 -in 50,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,100,5,50,350 --gpu -1 -DISP 1 -Tpinv -1 -s 10 -nop 1 -y  -18.5,18.5,0,1 
#NG#
#NG#[100,-1](15.7s) #[T,Tpinv] k10 N50 b1a1.0s10m12 nop1 t0-2000:2000-2500:1:15H122
#NG#[100,-1](15.6s) #[T,Tpinv] k10 N50 b1a1.0s10m12 nop1 t0-2000:2000-2500:1:15H69   with object
#NG#
#NG#####
#NG##equivalent to single ?
#NG##a bag in my_function.py L116,117  => 20200122 modified
#NG#####
#NG#export T=100 Tpinv=-1 k=10 N=50 seed=10 tp0=2000 tpD=1 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1;
#NG#python can2.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:$tpD:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y" -fns tmp/lorenz1e-8T0.025n10000p256m1_gmp+null+b1a1.0s10N50k10j0.net
#NG#####
#NG###after saving net by -fns execute with different tp0
#NG#####
#NG#export T=100 Tpinv=-1 k=10 N=50 seed=10 tp0=2000 tpD=1 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1;
#NG#python can2.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k $k -t 0-2000:$tp0-`echo $tp0+500|bc`:$tpD:$Ey -in '' -ex '' --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y" -fnl tmp/lorenz1e-8T0.025n10000p256m1_gmp+null+b1a1.0s10N50k10j0.net
#NG#
#NG##100(15.449s) 4.206e-05 6.691e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 t0-2000:2000-2500:1:15H238 predTime0.019s
#NG#100(14.788s) 4.206e-05 5.982e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 t0-2000:2100-2600:1:15H79 predTime0.018s
#NG#100(14.871s) 4.206e-05 4.958e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 t0-2000:2200-2700:1:15H271 predTime0.019s


########################
20200117
########################
#net save test with time-series prediction
###
export fn=/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt T=100 Tpinv=-1 k=10 N=50 seed=10 Ey=15 nop=1 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1;
#
python can2.py -fn $fn -k $k -t 0-2000:2000-2500:0:0:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y" -fns lorenz0-2000.net
100(14.922s) 4.206e-05 6.691e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 tp2000-2500H238(Ey15.0) predTime0.025s
100(14.922s) 4.206e-05 6.691e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 tp2000-2500H238(Ey15.0) predTime0.025s



#net load
export fn=/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 
python can2.py -fn $fn -fnl lorenz0-2000.net -t 0-2000:2000-2500:0:0:$Ey -in '' -ex '' --gpu -1 -DISP 1 -nop $nop
100(14.685s) 4.206e-05 6.691e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop1 H238(Ey15.0) predTime0.021s H238(Ey15.0) predTime0.018s
tp2100-2600H79(Ey15.0) predTime0.019s
########################
# 20200103<-20191228: for bagging CAN2 in 北山君課題
########################
#(0) バギングCAN2の学習・予測機能をensrs.py に導入した．使用法は以下の通り。
#    比較実験のため、../can2c/readmecan2c.txtの20200103 のところも参照
#
#(1) データ作成（下記の20191101<-20191031nightの4-1と同じ）
export fn=Geo1d ntrain=200 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest #
export fntrain=../../can2m.result/geo1dtrain.csv fntest=../../can2m.result/geo1dtest.csv
cp tmp/train.csv $fntrain
cp tmp/test.csv $fntest
#
#(2) ensrs.pyによる学習と予測
#(2-1) 使用例
export fntrain=../../can2m.result/geo1dtrain.csv fntest=../../can2m.result/geo1dtest.csv fnpred=../../can2m.result/geo1dpred.csv
export T=100 N=60 k=1 Tpinv=-1 seed=1 m_cpu=0 b=200 a=2.2 nop=1 
python ensrs.py -fn $fntrain,$fntest,$fnpred -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,2.2,$T,5,50,350 -DISP 0 -Tpinv $Tpinv -s $seed -nop $nop -bag $b,$a,$seed,$m_cpu
#(2-2) 結果
[100,-1](96.7s) 2.896e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s1 m12 seed1 nop1
[100,-1](1850.9s) 2.896e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s1 m2 seed1 nop1
[100,-1](1563.2s) 2.724e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s2 m8 seed2 nop1
[100,-1](1775.8s) 2.791e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s3 m2 seed3 nop1
[100,-1](1839.3s) 2.610e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s4 m5 seed4 nop1
[100,-1](1561.2s) 2.982e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s5 m8 seed5 nop1
[100,-1](1531.4s) 2.507e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s6 m2 seed6 nop1

[100,-1](87.3s) 3.371e-06 #[T,Tpinv] MSE n200,71 k1 N60 b10 a2.2 s1 m2 seed1 nop1 laptop
[100,-1](908.5s) 2.782e-06 #[T,Tpinv] MSE n200,71 k1 N60 b100 a2.2 s1 m2 seed1 nop1 laptop
[100,-1](893.6s) 2.837e-06 #[T,Tpinv] MSE n200,71 k1 N60 b100 a2.2 s2 m2 seed2 nop1
[100,-1](870.6s) 3.310e-06 #[T,Tpinv] MSE n200,71 k1 N60 b100 a2.2 s3 m2 seed3 nop1
[100,-1](898.0s) 2.710e-06 #[T,Tpinv] MSE n200,71 k1 N60 b100 a2.2 s4 m2 seed4 nop1

[100,50](87.2s) 5.811e-06 #[T,Tpinv] MSE n200,71 k1 N60 b200 a2.2 s1 m12 seed1 nop1
[100,50](85.4s) 1.233e-05 #[T,Tpinv] MSE n200,71 k1 N50 b200 a2.2 s1 m12 seed1 nop1 NG
[100,50](777.6s) 8.956e-06 #[T,Tpinv] MSE n200,71 k1 N60 b100 a2.2 s1 m2 seed1 nop1
[100,50](787.4s) 3.324e-06 #[T,Tpinv] MSE n200,71 k1 N60 b100 a2.2 s2 m2 seed2 nop1
[100,50](892.6s) 1.062e-05 #[T,Tpinv] MSE n200,71 k1 N90 b100 a2.2 s1 m2 seed1 nop1
[100,50](946.5s) 3.266e-06 #[T,Tpinv] MSE n200,71 k1 N100 b100 a2.2 s1 m2 seed1 nop1

#(2-3) バグ外予測使用例
export T=100 N=60 k=1 Tpinv=50 seed=2 m_cpu=0 nop=1 
python ensrs.py -fn $fntrain,/dev/null,tmp/oobpred.dat -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,2.2,$T,5,50,350 -DISP 0 -Tpinv $Tpinv -s $seed -nop $nop -bag 100,2.2,$seed,$m_cpu
#(2-4) バグ外予測結果
[100,50](51.7s) 2.598e-05 #[T,Tpinv] MSE n200,0 k1 N60 b10 a0.7 s2 m2 seed2 nop1
[100,50](800.1s) 1.357e-05 #[T,Tpinv] MSE n200,0 k1 N60 b100 a2.2 s2 m2 seed2 nop1
[100,-1](911.0s) 7.481e-06 #[T,Tpinv] MSE n200,0 k1 N60 b100 a2.2 s2 m2 seed2 nop1
[100,50](806.2s) 1.613e-01 #[T,Tpinv] MSE n200,0 k1 N60 b100 a2.2 s2 m2 seed2 nop1
##############
20191222 for timeseries prediction 時系列予測 inr 村田さん課題
##############
#(1) 時系列予測を行う処理を追加した。追加した主なオプション
# -fn <fn>                    #ファイル名<fn>を指定。このファイルの１列目の時系列を使用
# -t <tr0>-<tr1>:<tp0>-<tp1>:0:0:<Ey>  #<tr0>-<tr1>の範囲を訓練データ、<tp0>-<tp1> の範囲を多段予測する。
#                                        <Ey>は予測可能範囲を決めるための予測誤差のしきい値
#(2) 実行例:
export T=100 Tpinv=-1 k=10 N=50 seed=10 tpD=1 Ey=15 nop=0 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1;
python can2.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k $k -t 0-2000:2000-2500:$tpD:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y"

100(14.768s) 4.113e-05 1.137e-04 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed1 nop0 H119(Ey15.0) predTime0.018s
100(14.795s) 4.211e-05 1.286e-04 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed2 nop0 H159(Ey15.0) predTime0.019s
100(14.985s) 4.100e-05 1.170e-04 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed3 nop0 H213(Ey15.0) predTime0.020s
100(15.490s) 3.935e-05 8.619e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed4 nop0 H148(Ey15.0) predTime0.023s

100(14.931s) 4.206e-05 6.691e-05 #ep(time),MSEtr,MSE n1990,500 k10 N50 T100,-1 seed10 nop0 H238(Ey15.0) predTime0.022s

#(3) 村田さんへの課題：松崎君、下田君、宮崎君がやっている、予測開始時刻<tp0>=2000,2100,...,4900について
#     およびN=50(,100),seed=1,2,3,4,5等に対する予測可能範囲、計算時間、MSEなどを調べ、
#      CAN2c(../can2c/readmecan2c.txt)による結果と比べる。

####
#(4) （これは黒木の課題?）T=100epochのうち、Tpinv=50epoch から擬似逆行列を使う学習は、一段予測のMSEを小さくするが、
#    時系列予測の予測可能範囲は一般に大きくはならなかった。しかし、埋め込み次元をk=4とする次の例で
#　　は時系列予測範囲も大きくできた。なぜか検討せよ。
#(4-1)現象
export T=100 Tpinv=50 k=4 N=50 seed=10 tpD=1 Ey=15 nop=0 n_compare=6 v_thresh=0.2 vmin=3 vmin2=0 v_ratio=0.5 width=0.2 l_mode=1 gamma0=0.05 nentropy_thresh=0.7 n_display=5 rot_x=50 rot_y=350 y=-18.5,18.5,0,1;
#
#new version tpD!=0 (tpD-step ahead prediction)
#
python can2.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k $k -t 0-2000:2000-2500:$tpD:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y"
#
#old tpD=0
#
#python can2.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -k $k -t 0-2000:2000-2500:0:0:$Ey -in $N,$n_compare,$v_thresh,$vmin,$vmin2,$v_ratio,$width -ex $l_mode,$gamma0,$nentropy_thresh,$T,$n_display,$rot_x,$rot_y --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop -y " $y"
#
100(9.699s) 4.526e-06 6.852e-06 #ep(time),MSEtr,MSE n1996,500 k4 N50 T100,50 seed10 nop0 H271(Ey15.0) predTime0.030s
100(95.292s) 5.470e-06 8.861e-06 #ep(time),MSEtr,MSE n1996,500 k4 N40 T100,50 seed10 nop0 H139(Ey15.0) predTime0.107s
100(91.440s) 4.236e-06 7.345e-06 #ep(time),MSEtr,MSE n1996,500 k4 N60 T100,50 seed10 nop0 H67(Ey15.0) predTime0.165s
100(100.106s) 4.236e-06 2.443e-04 #ep(time),MSEtr,MSE n1996,500 k4 N60 T100,50 seed10 nop0 H174(Ey15.0) predTime0.167s
100(109.848s) 8.943e-05 4.623e-04 #ep(time),MSEtr,MSE n1996,500 k4 N60 T100,-1 seed10 nop0 H136(Ey15.0) predTime0.161s
100(314.686s) 9.232e-06 2.554e-06 #ep(time),MSEtr,MSE n7996,500 k4 N70 T100,50 seed10 nop0 H136(Ey15.0) predTime0.193s
100(356.344s) 8.702e-06 3.202e-06 #ep(time),MSEtr,MSE n7996,500 k4 N100 T100,50 seed10 nop0 H169(Ey15.0) predTime0.198s
100(400.007s) 9.984e-06 7.732e-06 #ep(time),MSEtr,MSE n8996,500 k4 N100 T100,50 seed10 nop0 H211(Ey15.0) predTime0.187s

#(3-2)解析１
python showatractor.py -fn tmp/w.csv -n 0-50
python showatractor.py -fn tmp/M.csv -n 0-50
python showatractor.py -fn /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt -n 0-2000 -type y
#Tpinv=50で擬似逆行列の学習(pinv)を行うと、Mのアトラクタが平面状になるが、
#Tpinv=-1で再帰的最小２乗学習(RLS)で得られるMのアトラクタは厚みを持ったものになる。なぜ？
#またk=4のwのアトラクタは、訓練データyのアトラクタのすべてをカバーしているようには見えないが
#k=10のアトラクタはかなりの範囲をカバーしているように見える

##############
20191101<-20191031night
##############
#(1) 計算時間をより正確に計るため，学習途中の表示を非印刷にするオプションnop (noprint mode)を追加．-nop 1でnoprint, -nop 0でprint
    laptop(遅い）では,nop=1がnop=0の1/2程度の計算時間だが、Desktop(早い）ではあまり変わらなかった.
#4-1 
export fn=Geo1d ntrain=200 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest #
#4-2
export T=100 N=90 k=1 Tpinv=50 seed=1 nop=1;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop
100 1.324e-06 7.341e-07 8.975e-06 4.977e-06 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time1.246s(0:00:01.246) seed1 nop1 Desktop
100 1.553e-07 2.247e-07 1.053e-06 1.523e-06 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time1.420s(0:00:01.419) seed3 nop1 Desktop
100 6.486e-07 2.602e-06 4.398e-06 1.764e-05 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time1.171s(0:00:01.171) seed2 nop1 Desktop
100 1.324e-06 7.341e-07 8.975e-06 4.977e-06 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time1.385s(0:00:01.384) seed1 nop0 Desktop
100 6.486e-07 2.602e-06 4.398e-06 1.764e-05 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time1.373s(0:00:01.372) seed2 nop0 Desktop
100 1.553e-07 2.247e-07 1.053e-06 1.523e-06 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time1.191s(0:00:01.191) seed3 nop0 Desktop
									       
100 1.324e-06 7.341e-07 8.975e-06 4.977e-06 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time6.594s(0:00:06.593)  seed1 nop1 laptop
100 6.486e-07 2.602e-06 4.398e-06 1.764e-05 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time6.610s(0:00:06.609)  seed2 nop1 laptop
100 1.553e-07 2.247e-07 1.053e-06 1.523e-06 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time6.364s(0:00:06.363)  seed3 nop1 laptop
100 1.324e-06 7.341e-07 8.975e-06 4.977e-06 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time15.621s(0:00:15.621) seed1 nop0 laptop
100 6.486e-07 2.602e-06 4.398e-06 1.764e-05 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time15.600s(0:00:15.600) seed2 nop0 laptop
100 1.553e-07 2.247e-07 1.053e-06 1.523e-06 #MSEtr,MSE,NMSEtr,NMSE n200,71 N90 Time14.936s(0:00:14.936) seed3 nop0 laptop

##############
20191031
##############
#(1) 学習回数T=100の後半のt=Tpinv=50以降は擬似逆行列(pseudo-inverse matrix)を使うとよい結果。
　　seedに依存しにくいcan2cのバギングでも確認。
#single CAN2 regression ?
export T=100 N=90 k=1 seed=1;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1 -Tpinv 50 -s $seed -nop 1
#check Tpinv=40,50,60,80,90
100 1.904e-06 9.158e-07 1.291e-05 6.209e-06 #MSEtr,MSE,NMSEtr,NMSE Tpinv40 seed=1 theta_r=1.1
100 1.324e-06 7.341e-07 8.975e-06 4.977e-06 #MSEtr,MSE,NMSEtr,NMSE Tpinv50 seed=1 theta_r=1.1 best
100 1.324e-06 7.341e-07 8.975e-06 4.977e-06 #MSEtr,MSE,NMSEtr,NMSE Tpinv60 seed=1 theta_r=1.1
100 6.078e-06 3.108e-06 4.122e-05 2.107e-05 #MSEtr,MSE,NMSEtr,NMSE Tpinv80 seed=1 theta_r=1.1
100 6.418e-06 5.202e-06 4.351e-05 3.527e-05 #MSEtr,MSE,NMSEtr,NMSE Tpinv90 seed=1 theta_r=1.1
#Examine Effecto of Tpinv for different seeds (of random variable)
100 6.014e-07 6.696e-07 4.078e-06 4.540e-06 #MSEtr,MSE,NMSEtr,NMSE Tpinv50 seed=0 theta_r=1.1 
100 1.324e-06 7.341e-07 8.975e-06 4.977e-06 #MSEtr,MSE,NMSEtr,NMSE Tpinv50 seed=1 theta_r=1.1 same as the best above
100 1.675e-06 5.916e-06 1.136e-05 4.011e-05 #MSEtr,MSE,NMSEtr,NMSE Tpinv50 seed=2 theta_r=1.1 
100 1.037e-07 2.169e-07 7.035e-07 1.471e-06 #MSEtr,MSE,NMSEtr,NMSE Tpinv50 seed=3 theta_r=1.1 
#ignore (Kurogi's experiment)
#100 6.014e-07 6.696e-07 4.078e-06 4.540e-06 #MSEtr,MSE,NMSEtr,NMSE N90 Time13.996s(0:00:13.995) seed=0 theta_r=1.1 Tpinv80-NDS combo
#100 6.078e-06 3.108e-06 4.122e-05 2.107e-05 #MSEtr,MSE,NMSEtr,NMSE N90 Time16.066s(0:00:16.065) seed=1 theta_r=1.1 Tpinv80-NDS combo
#100 1.553e-07 2.247e-07 1.053e-06 1.523e-06 #MSEtr,MSE,NMSEtr,NMSE N90 Time12.488s(0:00:12.488) seed=3 theta_r=1.1 Tpinv80-NDS combo

##############
20191025
##############
#(1) L731@my_plinn.py #wの再初期化式(論文式(24))の係数θr(theta_r)を1.9から0.9と1.1にしてみたら、変動が少なく良い結果が得られた。
　　　しかし、can2cでは1.9と1.1で変わらない結果->もともと精度がよいから？
　　　変わらないのでtheta_r=1.1にする。
#for Geo1d_200_50_10
#4-1 export fn=Geo1d ntrain=200 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
#4-2 
export T=100 N=90 k=1 seed=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1 -s $seed
#increase MSE by modify_w_batch at GlobalTime=53 check NDS3.84 at GlobalTime=54
L731@my_plinn.py #wの再初期化式(論文式(24))の係数θrを1.9から0.9と1.1にしてみた。
100 1.381e-06 1.063e-06 9.362e-06 7.209e-06 #MSEtr,MSE,NMSEtr,NMSE N90 Time18.721s(0:00:18.721) seed=0 theta_r=1.1 same for 0.9
100 5.036e-06 4.650e-06 3.415e-05 3.153e-05 #MSEtr,MSE,NMSEtr,NMSE N90 Time18.490s(0:00:18.490) seed=1 theta_r=1.1
100 1.811e-06 4.005e-06 1.228e-05 2.716e-05 #MSEtr,MSE,NMSEtr,NMSE N90 Time17.401s(0:00:17.401) seed=2 theta_r=1.1

100 6.978e-07 9.697e-07 4.731e-06 6.575e-06 #MSEtr,MSE,NMSEtr,NMSE N90 Time18.445s(0:00:18.445) seed=0 theta_r=1.9
100 1.080e-05 5.782e-05 7.323e-05 3.921e-04 #MSEtr,MSE,NMSEtr,NMSE N90 Time17.521s(0:00:17.520) seed=1 theta_r=1.9 NG
100 4.358e-06 7.326e-06 2.955e-05 4.967e-05 #MSEtr,MSE,NMSEtr,NMSE N90 Time17.500s(0:00:17.500) seed=2 theta_r=1.9


#100 5.343e-08 3.001e-07 3.623e-07 2.035e-06 #MSEtr,MSE,NMSEtr,NMSE N90 Time17.634s(0:00:17.633) seed=1 theta_r=1.1 0>NDS>-0.001
#100 2.028e-05 6.667e-05 1.375e-04 4.521e-04 #MSEtr,MSE,NMSEtr,NMSE N90 Time17.092s(0:00:17.091) seed=0 theta_r=1.1 0>NDS>-0.001 NG


#N=20
100 6.472e-06 1.453e-05 4.389e-05 9.850e-05 #MSEtr,MSE,NMSEtr,NMSE N20 Time11.606s(0:00:11.606) TpI900 seed=0 theta_r=1.1
100 7.145e-06 1.167e-05 4.845e-05 7.914e-05 #MSEtr,MSE,NMSEtr,NMSE N20 Time11.907s(0:00:11.907) TpI900 seed=1 theta_r=1.1
100 3.215e-05 4.519e-05 2.180e-04 3.064e-04 #MSEtr,MSE,NMSEtr,NMSE N20 Time10.782s(0:00:10.782) TpI900 seed=2 theta_r=1.1
100 2.811e-04 1.963e-04 1.906e-03 1.331e-03 #MSEtr,MSE,NMSEtr,NMSE N20 Time10.121s(0:00:10.120) TpI900 seed=3 theta_r=1.1


100 3.200e-06 1.007e-05 2.170e-05 6.826e-05 #MSEtr,MSE,NMSEtr,NMSE N20 Time8.845s(0:00:08.845) TpI50 seed=0 theta_r=1.1 
100 6.221e-06 1.304e-05 4.218e-05 8.845e-05 #MSEtr,MSE,NMSEtr,NMSE N20 Time8.829s(0:00:08.829) TpI50 seed=1 theta_r=1.1 
100 9.999e-06 6.219e-06 6.780e-05 4.217e-05 #MSEtr,MSE,NMSEtr,NMSE N20 Time8.041s(0:00:08.040) TpI50 seed=2 theta_r=1.1 
100 4.930e-05 6.596e-05 3.343e-04 4.473e-04 #MSEtr,MSE,NMSEtr,NMSE N20 Time6.715s(0:00:06.714) TpI50 seed=3 theta_r=1.1 

100 1.925e-06 7.502e-06 1.306e-05 5.087e-05 #MSEtr,MSE,NMSEtr,NMSE N20 Time7.395s(0:00:07.395) NDS.001 seed=0 theta_r=1.1 
100 4.161e-06 3.236e-06 2.822e-05 2.194e-05 #MSEtr,MSE,NMSEtr,NMSE N20 Time6.280s(0:00:06.279) NDS.001 seed=1 theta_r=1.1 
100 7.117e-05 1.830e-04 4.826e-04 1.241e-03 #MSEtr,MSE,NMSEtr,NMSE N20 Time7.168s(0:00:07.168) NDS.001 seed=2 theta_r=1.1 NG
100 1.200e-04 2.444e-04 8.136e-04 1.657e-03 #MSEtr,MSE,NMSEtr,NMSE N20 Time6.570s(0:00:06.569) NDS.001 seed=3 theta_r=1.1 NG
##############
20191025
##############
#(1) def modify_M_batch(net,x,y): in my_plinn.py が逐次的であり、
#    modify_M_batch(NET *net, FLOAT **x, FLOAT *y) in my_plinn.c と違う。
#    -> 擬似逆行列(pseudo-inverse)で行えるようにした 
#    L536: net['am']['M'][i]=xp.dot(xp.linalg.pinv(x[V['ij2t'][i],:]),y[V['ij2t'][i],:]).T
     オプション　--pinv 1 または -pI 1 で擬似逆行列，0で逐次的最小二乗法
    ntrain<=100は -pI 1　が良いが、ntrain>=200では-pI 0が良い？
#(3)L1132 #c2py_ver=1 #20190114 modified by kuro 違うデータを補充
#(4) NDS の条件を-0.01にした？

#4-1 export fn=Geo1d ntrain=50 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
#4-2 for ../../can2data/Geo1d_50_50_10
export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1 -pI 0 -s 0
4.061e-06 2.165e-05 3.523e-05 1.878e-04 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:10.668 ElapsedTime -pI 1 -s 0
5.254e-06 3.030e-05 4.558e-05 2.629e-04 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:13.506 ElapsedTime -pI 0 -s 0
5.409e-06 2.369e-05 4.692e-05 2.055e-04 #MSEtr,MSE,NMSEtr,NMSE N100 0:00:16.340 ElapsedTime -pI 1 -s 0

1.869e-06 4.025e-06 1.267e-05 2.729e-05 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:15.593 ElapsedTime ntrain=200 -pI 0 -s 0 
6.288e-06 7.571e-06 4.263e-05 5.133e-05 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:14.046 ElapsedTime ntrain=200 -pI 1 -s 0 

#4-1 ../../can2data/Geo1d_100_50_10 #make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=100 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
#4-2
export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
100 2.699e-07 8.394e-06 2.341e-06 7.281e-05 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:11.208 ElapsedTime

#4-1 ../../can2data/Geo1d_1000_50_10 #make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=100 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
100 6.182e-08 2.546e-07 3.902e-07 1.607e-06 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:19.148 ElapsedTime

##############
grep "def " *.py
am.py:def init_AM(q,nc,nx,ny): 
am.py:def calc_AM(q,i):
am.py:def calc_AMxy(q,i,xi,yi):
can2.py:def myshell(cmd): #no stop even when error occured
can2.py:def make_sample_data(msd):
can2.py:def set_random_seed(seed): 
can2.py:def moverange(y1,y1min,y1max,y0min,y0max): #in my_plinn.c
can2.py:def calc_statistics(data): #in my_function.c
can2.py:def normalize_data(givendata,net): #in my_function.c
can2.py:def load_data(givendata,test,net):
cupytest2.py:#def sigmoid(x):
cupytest2.py:def numpy_sigmoid(x):
cupytest2.py:def cupy_sigmoid(x):
makesamples.py:def myshell(cmd): #no stop even when error occured
makesamples.py:def geo1d(x):
makesamples.py:def make_sample_data(msd):
makesamples.py:  return #finish def make_sample_data():
makesamples.py:def set_random_seed(seed): 
my_plinn.py:def LA(x,y1,x1,y2,x2):
my_plinn.py:def init_sort_weights(net,x,_x):
my_plinn.py:def sort_weights(net,s,v,start,end):
my_plinn.py:def calc_output(net,x,_x):
my_plinn.py:def calc_output2(net,x,givendata):#x=test['x']
my_plinn.py:def in_window(x1,x2,x,width2,n_channels):
my_plinn.py:def checkwM(cmt,net):
my_plinn.py:def modify_w_batch(net,x,y,n_train,GlobalTime,_x):
my_plinn.py:  return #def modify_w_batch(net,x_train,y_train,n_train):
my_plinn.py:def calc_alpha(net,x,y,n_train,GlobalTime):
my_plinn.py:def modify_M_batch(net,x,y):
my_plinn.py:def init_batch_wvector(net, x, n_train): #first call by init_net_batch() beloow
my_plinn.py:def reinit_cell_batch(net,x,y,n_train,GlobalTime,_x):
my_plinn.py:def init_Voronoi(V, n_cells, n_channels, n_train):
my_plinn.py:def calc_Voronoi(net,x,y,n_train,GlobalTime,_x):
my_plinn.py:def init_net_batch(net,x,n_train): #first call by exec_sim() in sim.py
my_plinn.py:def init_net(net,args): # init_net() in my_plinn.c
my_plinn.py:def store_vector_batch(net, x_train, y_train,n_train, GlobalTime, phase,_x_train):#
sim.py:def coud_check_learn(i_times,max_i_times,d_times):
sim.py:def calc_MSE(t,test,net,givendata):
sim.py:def exec_ssp_test(net, givendata, test):
sim.py:def check_learn(simdata, net, givendata, testdata, msebank): #testdata is test originary
sim.py:def exec_sim(net, givendata,test,args):
switchCupy.py:def is_cupy():
switchCupy.py:def xp_factory():
switchCupy.py:def xpfloat(xp):
switchCupy.py:def report():

##########
20191017
#########
(1) makesamples.py で fn=Geo1d とした時のデータ作成の説明：例えば、
export fn=Geo1d  ntrain=50 restest=50 extest=10 k=1;
python makesamples.py -msd $fn,$ntrain,$restest,$extest 
とすると、入力xを[0,1]の範囲からランダムにntrain個抽出して訓練データを作成し、
1/restestの刻みで範囲[-extest/restest,1+1+extext/restest]の範囲のテストデータを作成
する
例
#4-1 ../../can2data/Geo1d_50_50_10
#make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=50 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export ddst=../../can2data/${fn}_${ntrain}_${restest}_${extest}
#4-2
export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1

#############以下はあまり整理してない．
20191014
#4-1 ../../can2data/Geo1d_100_50_10 #make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=50 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 

cp ~/sotu/2019/can2b/tmp/mse_t.csv mse-can2c191014.csv

cat > mse-can2x.plt <<EOF
set logscale y
set xtics (1,20,40,60,80,100);set grid
plot [-10:110][1e-7:1] "mse-can2c191014.csv" using (\$0+1):1 w l t "MSEtr","" using (\$0+1):2 w l lc rgb "blue" t "MSE", "mse-can2py0.csv" using (\$0+1):1 w l t "MSEtr","" using (\$0+1):2 w l lc rgb "blue" t "MSE"
set term tgif;set output "Geo1d-mse-can2x.obj";replot
EOF
gnuplot mse-can2x.plt

cat > mse-MLP.plt <<EOF
set logscale y
set xtics (1,5000,10000,15000,20000);set grid
set term x11
plot [-1000:21000][1e-7:1]  "mse-MLP.csv" using (\$0+1):2 w l lt 1 t "MSEtr", "" using (\$0+1):3 w l lt 1lc rgb "blue" t "MSE"
set term tgif;set output "Geo1d-mse-MLP.obj";replot
EOF
gnuplot mse-MLP.plt

20191013
##############
#4-1 ../../can2data/Geo1d_50_50_20 #make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=50 restest=50 extest=20 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export ddst=../../can2data/${fn}_${ntrain}_${restest}_${extest}
#4-2
export T=100 N=100 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1

100 8.571e-06 2.002e-04 7.503e-05 1.753e-03 #MSEtr,MSE,NMSEtr,NMSE N100 0:00:14.455 ElapsedTime
100 8.811e-06 5.886e-04 7.712e-05 5.152e-03 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:12.809 ElapsedTime
100 8.743e-06 5.819e-04 7.653e-05 5.094e-03 #MSEtr,MSE,NMSEtr,NMSE N110 0:00:14.556 ElapsedTime

#4-1 ../../can2data/Geo1d_100_50_20 #make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=100 restest=50 extest=20 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export ddst=../../can2data/${fn}_${ntrain}_${restest}_${extest}
#4-2
export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1


##############
cat tmp/tmp.dat |awk '{print $1, $2*3600+$3*60+$4, $5*3600+$6*60+$7, $8*3600+$9*60+$10, $11*3600+$12*60+$13}' >tmp/sec.dat
cat tmp/sec.dat
50   0.163 16.148 0.898 390.587
100  0.214 19.166 1.262 685.371
1000 0.731 80.899 3.232 14062.8
cat > mses.dat <<EOF
#    can2-c-s     can2-c-b     can2-py      MLP      can2-c-s    can2-c-b     can2-py      MLP        
50   1.252420e-04 1.070902e-04 2.566e-04   1.651e-04 0.163       16.148       0.898     390.587
100  1.961e-05    9.140940e-06 9.034e-06   8.929e-05 0.214       19.166       1.262     685.371  
1000 7.959e-08    2.220421e-07 4.172e-07   3.798e-06 0.731       80.899       3.232     14062.8  #4.172e-7can2py with -s 1
EOF
gnuplot 
set term x11
set xtics (50,100,1000);seg grid
set logscale x;set logscale y;set pointsize 1.5
plot [40:1200][1e-8:1e-3] "mses.dat" using 1:2 w lp pt 8 t "can2-c-s", "" using 1:3 w lp pt 9 t "can2-c-b", "" using 1:4 w lp pt 10 t "can2-py", "" using 1:5 w lp pt 6 t "MLP"
set term tgif;set output "Geo1d-mse-n.obj";replot
#plot [40:1200][1e-8:1e-3] "mses.dat" using 1:2 w lp pt 8 t "can2-c-s", "" using 1:3 w lp pt 9 t "can2-c-b", "" using 1:4 w lp pt 10 t "can2-py", "" using 1:5 w lp pt 6 t "MLP"
#set term tgif;set output "Geo1d-mse-n.obj";replot
#
set term x11
plot [40:1200][] "mses.dat" using 1:6 w lp pt 8 t "can2-c-s", "" using 1:7 w lp pt 9 t "can2-c-b", "" using 1:8 w lp pt 10 t "can2-py", "" using 1:9 w lp pt 6 t "MLP"
set term tgif;set output "Geo1d-t-n.obj";replot
EOF
gnuplot mses.plt
#cp ./mse.csv ./mse-can2c.csv #?
cp ~/sotu/2019/can2b/tmp/mse_t.csv mse-can2c191014.csv

cat > mse-can2x.plt <<EOF
set logscale y
set xtics (1,20,40,60,80,100);set grid
plot [-10:110][1e-7:1] "mse-can2c191014.csv" using ($0+1):1 w l t "MSEtr","" using ($0+1):2 w l lc rgb "blue" t "MSE", "mse-can2py0.csv" using ($0+1):1 w l t "MSEtr","" using ($0+1):2 w l lc rgb "blue" t "MSE"
set term tgif;set output "Geo1d-mse-can2x.obj";replot
EOF
gnuplot mse-can2x.plt
cp predxy.txt Geo1d_100_50_10_can2py_predxy_n90.txt

gnuplot
set term tgif;set output "Geo1d100prederr.obj";
set multiplot
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.9
set bmargin screen 0.5
plot [:][-0.2:1.2] "test.csv" using 1:2 w l, "Geo1d_100_50_10_can2py_predxy_n90.txt" using 1:3 w l t "yp",  "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt"  using 1:3 w l t "yp"
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.4
set bmargin screen 0.1
plot [:][] "Geo1d_100_50_10_can2py_predxy_n90.txt" using 1:($3-$2) w l t "e-can2py",  "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt"  using 1:($3-$2) w l t "e-MLP"
unset multiplot
quit


set ytics ('-0.04' -0.9, '-0.02' -0.7, '0' -0.5, '0.02' -0.3, '0.04' -0.1,0, 0.5,1)
plot [:][-1.0:1.2] "test.csv" using 1:2 w l t "y", "Geo1d_100_50_10_can2py_predxy_n90.txt" using 1:3 w l t "yp-CAN2py", "" using 1:($3-$2)*10-0.5 w l t "e-CAN2py",  "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt"  using 1:3 w l t "yp-MLP", "" using 1:($3-$2)*10-0.5 w l t "e-MLP"

plot [:][-1:1.2] "test.csv" using 1:2 w l t "y", "Geo1d_100_50_10_can2py_predxy_n90.txt" using 1:3 w l t "yp-CAN2py", "" using 1:($3-$2)*10-0.4 w l t "e-CAN2py",  "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt"  using 1:3 w l t "yp-MLP", "" using 1:($3-$2)*10-0.4 w l t "e-MLP"


plot [:][-0.3:1.2] "test.csv" using 1:2 w l, "Geo1d_100_50_10_can2py_predxy_n90.txt" using 1:3 w l t "yp",  "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt"  using 1:3 w l t "yp"

plot [:][-0.3:1.2] "test.csv" using 1:2 w l, "Geo1d_100_50_10_can2py_predxy_n90.txt" using 1:($3-$2)*10 w l,  "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt"  using 1:($3-$2)*10 w l



plot [:][-0.3:1.2] "test.csv" using 1:2 w l, "Geo1d_100_50_10_can2py_predxy_n90.txt" using 1:3 w l t "yp", "" using 1:($3-$2)*10 w l

plot [:][-0.3:1.2] "test.csv" using 1:2 w l,  "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt"  using 1:3 w l t "yp", "" using 1:($3-$2)*10 w l


plot [:][-0.2:1.2] "test.csv" using 1:2 w l, "Geo1d_100_50_10_can2py_predxy_n90.txt" using 1:3 w l t "yp"

plot [:][] "predxy.txt" using 1:($3-$2) w l t "err", "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt" using 1:($3-$2) w l

plot [:][-0.2:1.2] "test.csv" using 1:2 w l, "Geo1d_100_50_10_pred_n90.txt" using 1:3 w p pt 6 t "yp"
set term tgif;set output "Geo1d-train100pred.obj";replot

plot [:][-0.2:1.2] "test.csv" using 1:2 w l, "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt" using 1:3 w p pt 6 t "yp" 
set term tgif;set output "Geo1d-train100predMLP.obj";replot

20191007
####
cd tmp
cp ~/sotu/2019/can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/loss.txt ./mse-MLP.csv
cp ~/sotu/2019/can2b/tmp/mse_t.csv ./mse-can2c.csv
cp ./mse.csv ./mse-can2c.csv

cat > mse-LM.plt <<EOF
set logscale y;set logscale y
#set xtics (1,10,100,1000,2000)
plot [0.5:30000][] "mse-can2c.csv" using ($0+1):1 w l t "MSEtr","" using ($0+1):2 w l t "MSE", "mse-can2py0.csv" using ($0+1):1 w l t "MSEtr","" using ($0+1):2 w l t "MSE", "mse-MLP.csv" using ($0+1):2 w l t "MSEtr","" using ($0+1):3 w l t "MSE"
set term tgif;set output "Geo1d-mse-LM.obj";replot
EOF
gnuplot mse-LM.plt

cat > mse-can2x.plt <<EOF
set logscale y
set xtics (1,20,40,60,80,100);set grid
plot [-10:110][1e-6:1] "mse-can2c.csv" using ($0+1):1 w l t "MSEtr","" using ($0+1):2 w l lc rgb "blue" t "MSE", "mse-can2py0.csv" using ($0+1):1 w l t "MSEtr","" using ($0+1):2 w l lc rgb "blue" t "MSE"
set term tgif;set output "Geo1d-mse-can2x.obj";replot
EOF
gnuplot mse-can2x.plt

cat > mse-MLP.plt <<EOF
set logscale y
set xtics (1,5000,10000,15000,20000);set grid
set term x11
plot [-1000:21000][][1e-6:1]  "mse-MLP.csv" using ($0+1):2 w l lt 1 t "MSEtr", "" using ($0+1):3 w l lt 1lc rgb "blue" t "MSE"
set term tgif;set output "Geo1d-mse-MLP.obj";replot
EOF
gnuplot mse-MLP.plt




mkdir ../../../can2data/Geo1d_summary
cp ../tmp/* ../../../can2data/Geo1d_summary/

#plot [0.1:20000][] "mse-can2c.csv" using 0:1 w lp pt 8 t "MSEtr","" using 0:2 w lp pt 9 t "MSE", "mse-can2py0.csv" using 0:1 w lp pt 10 t "MSEtr","" using 0:2 w lp pt 11 t "MSE", "mse-MLP.csv" using 0:2 w lp pt 6 t "MSEtr","" using 0:3 w lp pt 7 t "MSE"
#
#plot "mse-can2c.csv" using 0:1 w lp pt 8 t "MSEtr","" using 0:2 w lp pt 9 t "MSE", "mse-can2py0.csv" using 0:1 w lp pt 10 t "MSEtr","" using 0:2 w lp pt 11 t "MSE", "mse-MLP.csv" using 0:1 w lp pt 6 t "MSEtr","" using 0:2 w lp pt 7 t "MSE"
#
#plot [0.1:20000] "mse-can2c.csv" using 0:1 w lp pt 8 t "MSEtr","" using 0:2 w lp pt 9 t "MSE", "mse-can2py0.csv" using 0:1 w lp pt 10 t "MSEtr","" using 0:2 w lp pt 11 t "MSE", "mse-MLP.csv" using 0:1 w lp pt 6 t "MSEtr","" using 0:2 w lp pt 7 t "MSE"


#plot "mse-can2py.csv" using 0:1 w lp t "MSEtr","" using 0:2 w lp t "MSE", "mse-can2c.csv" using 0:1 w lp t "MSEtr","" using 0:2 w lp t "MSE"
#plot "mse-can2py0.csv" using 0:1 w lp t "MSEtr","" using 0:2 w lp t "MSE", "mse-can2py.csv" using 0:1 w lp t "MSEtr","" using 0:2 w lp t "MSE", "mse-can2c.csv" using 0:1 w lp t "MSEtr","" using 0:2 w lp t "MSE"

#H:M:S -> sec
cat > tmp/hms.dat <<EOF
50   0 0 0.163   0 0 16.148 0 00 00.898 0 06 30.587
100  0 0 0.214   0 0 19.166 0 00 01.262 0 11 25.371 
1000 0 0 0.731   0 1 20.899 0 00 03.232 3 54 22.788 
EOF
cat tmp/tmp.dat |awk '{print $1, $2*3600+$3*60+$4, $5*3600+$6*60+$7, $8*3600+$9*60+$10, $11*3600+$12*60+$13}' >tmp/sec.dat
cat tmp/sec.dat
50   0.163 16.148 0.898 390.587
100  0.214 19.166 1.262 685.371
1000 0.731 80.899 3.232 14062.8
cat > tmp/mses.dat <<EOF
#    can2-c-s     can2-c-b     can2-py      MLP      can2-c-s    can2-c-b     can2-py      MLP        
50   1.252420e-04 1.070902e-04 2.566e-04   1.651e-04 0.163 16.148 0.898 390.587
100  2.831306e-05 9.140940e-06 9.034e-06   8.929e-05 0.214 19.166 1.262 685.371  
1000 7.678325e-07 2.369439e-07 4.152e-06   3.798e-06 0.731 80.899 3.232 14062.8  
#
#100  2.831306e-05 9.140940e-06 3.442e-05   8.929e-05 0.214 19.166 1.262 685.371  
#300  -            -            3.415e-06   -         -      -     -     -
EOF
cat > mses.plt <<EOF
set term x11
set xtics (50,100,1000)
set logscale x;set logscale y;
plot [40:1200][] "mses.dat" using 1:2 w lp pt 8 t "can2-c-s", "" using 1:3 w lp pt 9 t "can2-c-b", "" using 1:4 w lp pt 10 t "can2-py", "" using 1:5 w lp pt 6 t "MLP"
set term tgif;set output "Geo1d-mse-n.obj";replot
set term x11
plot [40:1200][] "mses.dat" using 1:6 w lp pt 8 t "can2-c-s", "" using 1:7 w lp pt 9 t "can2-c-b", "" using 1:8 w lp pt 10 t "can2-py", "" using 1:9 w lp pt 6 t "MLP"
set term tgif;set output "Geo1d-t-n.obj";replot
EOF
gnuplot mses.plt

../../can2data/Geo1d_50_50_10
100   1.241e-07    1.252e-04 0:0:0.986 #MSEtr MSE t N90 can2c-single not use this
100   1.164233e-06 1.070902e-04  0:0:16.148  #MSEtr MSE N30 b100 a3.0  can2c bagging***
100   8.571e-06    2.566e-04     0:00:00.898 7.503e-05 2.246e-03 #MSEtr,MSE,NMSEtr,NMSE N100 ElapsedTime ***
20000 1.267e-04    1.651e-04     0:06:30.587 #epoch,MSEtr,MSEval,t -b 10 -nh 60 -nL 1 -func leaky_relu -do 0.0 -g 0  MLPchainer

#100   1.223126e-07 1.252420e-04  0:0:0.163   #MSEtr MSE N80 b1 a1  can2c single ***

#4-1 ../../can2data/Geo1d_100_50_10
100   8.367e-05    1.961e-05     0:0:1.500 #MSEtr MSE t N120 can2c-single use this MSEtr for 100, 8.27 is for 101
100   1.493088e-06 9.140940e-06  0:0:19.166  #MSEtr MSE N60 b100 a2.2 can2c bagging
100   1.933e-06    9.034e-06     0:00:01.262 1.677e-05 7.836e-05 #MSEtr,MSE,NMSEtr,NMSE N90 can2py ***
20000 1.702e-05    8.929e-05     0:11:25.371 #epoch,MSEtr,MSEval,t -b 10 -nh 40 -nL 1 -func leaky_relu -do 0.0 -g 0 MLP-chainer
#100   8.311e-07    1.961e-05     0:0:2.448   #MSEtr MSE t N120 can2c-single *** 
#100   1.751336e-06 2.831306e-05  0:0:0.214   #MSEtr MSE N100 b1 a1     can2c single
#4-1 ../../can2data/Geo1d_1000_50_10
100   1.198e-07    7.959e-08     0:0:4.840 #MSEtr MSE t N80 can2c-single
100   1.255490e-08 2.369439e-07  0:1:20.899   #MSEtr MSE N60 b100 a2.2 #bagging can2c
100   3.410e-06    4.152e-06     0:00:03.232  2.153e-05 2.621e-05 #MSEtr,MSE,NMSEtr,NMSE N90 can2py
50000 3.344e-06    3.798e-06     3:54:22.788  #epoch,MSEtr,MSEval,t -b 10 -nh 120 -nL 1 -func leaky_relu -do 0.0 -g 0 
100   4.777303e-07 7.678325e-07  0:0:0.731    #MSEtr MSE N100 b1 a1   #single can2c


200   1.213e-06    1.583e-06 7.660e-06 9.994e-06 #MSEtr,MSE,NMSEtr,NMSE 0:00:06.820 N90 T200 can2py ElapsedTime
##################

#4-1 ../../can2data/Geo1d_50_50_10
#make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=50 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export ddst=../../can2data/${fn}_${ntrain}_${restest}_${extest}
#4-2
export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
100 8.571e-06 2.566e-04 7.503e-05 2.246e-03 #MSEtr,MSE,NMSEtr,NMSE N100 0:00:00.898 ElapsedTime ***
100 8.811e-06 7.544e-04 7.712e-05 6.604e-03 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:00.852 ElapsedTime
100 8.743e-06 7.459e-04 7.653e-05 6.529e-03 #MSEtr,MSE,NMSEtr,NMSE N110 0:00:00.954 ElapsedTime
100 8.736e-06 7.958e-04 7.647e-05 6.966e-03 #MSEtr,MSE,NMSEtr,NMSE N120 0:00:00.870 ElapsedTime
20000 1.267e-04 1.651e-04 0:06:30.587 #epoch,MSEtr,MSEval,t -b 10 -nh 60 -nL 1 -func leaky_relu -do 0.0 -g 0  MLPchainer
100 1.223126e-07 1.252420e-04  #MSEtr MSE N80 b1 a1 0:0:0.163 can2py  single

#Geo1d compare with MLP 
#4-1 ../../can2data/Geo1d_100_50_10
#make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=100 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
fb=../../can2data/${fn}_${ntrain}_${restest}_${extest} #../../can2data/Geo1d_100_50_10
cp tmp/train.csv ${fb}_train.csv
cp tmp/test.csv ${fb}_test.csv
#sort -g train.csv >trainsort.csv
#4-2

export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
100 1.933e-06 9.034e-06 1.677e-05 7.836e-05 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:18.378 ElapsedTime with -s 0 by laptop
100 5.930e-07 3.442e-05 5.144e-06 2.986e-04 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:21.037 ElapsedTime with -s 1 by laptop

100 1.933e-06 9.034e-06 1.677e-05 7.836e-05 #MSEtr,MSE,NMSEtr,NMSE 0:00:01.262 N90 can2py ***
100 2.614e-06 3.287e-05 2.268e-05 2.851e-04 #MSEtr,MSE,NMSEtr,NMSE 0:00:01.176 N80 can2py
100 2.594e-06 2.614e-05 2.250e-05 2.267e-04 #MSEtr,MSE,NMSEtr,NMSE 0:00:01.306 N100 can2py
200 1.504e-06 8.799e-06 1.304e-05 7.632e-05 #MSEtr,MSE,NMSEtr,NMSE 0:00:02.484 N90  can2py
20000 1.702e-05 8.929e-05 0:11:25.371 #epoch,MSEtr,MSEval,t -b 10 -nh 40 -nL 1 -func leaky_relu -do 0.0 -g 0 MLP-chainer
100 1.751336e-06 2.831306e-05  #MSEtr MSE N100 b1 a1 0:0:0.214     can2c single
100 1.493088e-06 9.140940e-06  #MSEtr MSE N60 b100 a2.2 0:0:19.166 can2c bagging
200 1.621521e-06 2.322632e-05  #MSEtr MSE N100 b1 a1 0:0:0.283     can2c single
200 1.271427e-06 1.199568e-05  #MSEtr MSE N60 b100 a2.2 0:0:44.546 can2c bagging

cd tmp
set term x11;
plot [:][-0.2:1.2] "test.csv" using 1:2 w l, "trainsort.csv" using 1:2 w p pt 6
set term tgif;set output "Geo1d-train100.obj";replot
set term x11;
plot [:][-0.2:1.2] "test.csv" using 1:2 w l, "predxy.txt" using 1:3 w p pt 6 t "yp"
set term tgif;set output "Geo1d-train100pred.obj";replot
set term x11;
plot [:][-0.2:1.2] "test.csv" using 1:2 w l, "../../../can2data/Geo1d_100_50_10_leaky_relu_nh40nL1/predxy.txt" using 1:3 w p pt 6 t "yp" 
set term tgif;set output "Geo1d-train100predMLP.obj";replot

#4-1 ../../can2data/Geo1d_300_50_10
#make sample data (tmp/train.csv tmp/test.csv)
export fn=Geo1d  ntrain=300 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export ddst=../../can2data/${fn}_${ntrain}_${restest}_${extest}
#4-2
export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
100 1.373e-07 2.606e-06 9.139e-07 1.735e-05 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:21.705 ElapsedTime
100 2.122e-07 3.415e-06 1.413e-06 2.273e-05 #MSEtr,MSE,NMSEtr,NMSE N100 0:00:21.764 ElapsedTime
100 2.173e-06 6.109e-06 1.446e-05 4.067e-05 #MSEtr,MSE,NMSEtr,NMSE N80 0:00:21.458 ElapsedTime


#Geo1d compare with MLP,can2c
#4-1 ../../can2data/Geo1d_1000_50_10
export fn=Geo1d  ntrain=1000 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest #make sample data (tmp/train.csv tmp/test.csv)
fb=../../can2data/${fn}_${ntrain}_${restest}_${extest} #../../can2data/Geo1d_1000_50_10
cp tmp/train.csv ${fb}_train.csv
cp tmp/test.csv ${fb}_test.csv
#4-2
export T=100 N=90 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
100 5.401e-07 4.172e-07 3.410e-06 2.634e-06 #MSEtr,MSE,NMSEtr,NMSE N90 0:00:37.388 ElapsedTime -s 1
100 3.410e-06 4.152e-06 2.153e-05 2.621e-05 #MSEtr,MSE,NMSEtr,NMSE 0:00:03.232 N90 can2py
200 1.213e-06 1.583e-06 7.660e-06 9.994e-06 #MSEtr,MSE,NMSEtr,NMSE 0:00:06.820 N90 T200 can2py ElapsedTime

100 4.777303e-07 7.678325e-07  #MSEtr MSE N100 b1 a1 0:0:0.731    #single can2c
100 1.255490e-08 2.369439e-07  #MSEtr MSE N60 b100 a2.2 0:1:20.899 #bagging can2c
50000 3.344e-06 3.798e-06 3:54:22.788 #epoch,MSEtr,MSEval,t -b 10 -nh 120 -nL 1 -func leaky_relu -do 0.0 -g 0 









#4-1
export fn=Geo1d  ntrain=1000 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest #make sample data (tmp/train.csv tmp/test.csv)

cp tmp/train.csv ../../can2data/${fn}_${ntrain}_${restest}_${extest}_train.csv
cp tmp/test.csv ../../can2data/${fn}_${ntrain}_${restest}_${extest}_test.csv
#4-2
export T=100 N=100 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
#can2py
100 6.639e-07 3.502e-07 4.191e-06 2.211e-06 #MSEtr,MSE,NMSEtr,NMSE

##############
20191002
####
#geo1d compare with MLP
#4-1
export fn=geo1D  nx=201 dx=0.2 dx=0.1 k=1;python makesamples.py -msd $fn,$nx,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
#4-2
export T=100 N=100 k=1;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
#can2py
100 1.021e-06 4.113e-06 6.355e-06 2.561e-05 #MSEtr,MSE,NMSEtr,NMSE N100 real0m2.640s #can2py ***smallest MSE
100 3.660e-06 7.676e-06 2.279e-05 4.779e-05 #MSEtr,MSE,NMSEtr,NMSE N110 real0m2.708s #can2py
100 2.409e-06 2.221e-05 1.500e-05 1.383e-04 #MSEtr,MSE,NMSEtr,NMSE N90 real0m2.522s #can2py
100 4.882588e-07 7.197260e-06  #MSEtr MSE N110 b1 a1 0:0:0.164  #single can2c
100 4.012082e-06 7.121007e-06  #MSEtr MSE N85 b100 a1.1 0:0:26.344 #bagging can2c
20000 8.019e-06 7.959e-06 0:12:44 #epoch,MSEtr,MSEval,t -b 10 -nh 120 -nL 1 -func leaky_relu -do 0.0 -g 0 #MLP_chainer

#geo2d
#6-1
export fn=geo2d n=51 a="" b="" k=2; python makesamples.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
#6-2
export T=100 N=100 k=2;time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1
100 1.667e-04 2.574e-04 1.364e-03 2.106e-03 #MSEtr,MSE,NMSEtr,NMSE N100 real0m7.424s #can2py
100 4.534e-05 2.872e-04 3.710e-04 2.350e-03 #MSEtr,MSE,NMSEtr,NMSE N110 real0m7.342s #can2py
100 9.277e-05 2.393e-04 7.591e-04 1.958e-03 #MSEtr,MSE,NMSEtr,NMSE N120 real0m7.254s #can2py
100 4.309112e-05 2.487544e-04  #MSEtr MSE N110 b1 a1 0:0:1.578 #single can2c
100 5.365678e-06 2.233687e-05  #MSEtr MSE N100 b100 a1.2 #best #bagging can2c ***smallest MSE

#MLP-chainer
2000 5.351e-05 4.706e-05 1077 #epoch,MSEtr,MSEval,time -e 2000 -b 10 -nh 90 -do 0.0 -g 0 real18m33.790


### check 6-1 データ作成
export fn=geo2d n=51 a="" b="" k=2; python makesamples.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
export fn=geo2d n=101 a="" b="" k=2; python makesamples.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
### check 6-2 訓練とテスト
export T=100 N=100 k=2 ;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,2,2,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350 --gpu -1 -DISP 1
#n=51
#100 6.943e-05 9.677e-05 5.792e-04 8.072e-04 #MSEtr,MSE,NMSEtr,NMSE 
#100 1.038e-04 4.090e-04 8.491e-04 3.347e-03 #MSEtr,MSE,NMSEtr,NMSE Learning Time = 6.66457700729 for n=51 N=80 
#100 3.250e-05 2.191e-04 2.659e-04 1.793e-03 #MSEtr,MSE,NMSEtr,NMSE Learning Time = 6.79996681213 for n=51 N=90 #smallest NMSE
#100 6.379e-05 2.887e-04 5.220e-04 2.363e-03 #MSEtr,MSE,NMSEtr,NMSE Learning Time = 6.91568899155 for n=51 N=100 
##n=101
#100 9.280e-05 1.154e-04 7.741e-04 9.623e-04 #MSEtr,MSE,NMSEtr,NMSE Learning Time = 26.7848761082 for n=101 N=100 
#100 5.264e-05 6.795e-05 4.390e-04 5.668e-04 #MSEtr,MSE,NMSEtr,NMSE Learning Time = 24.869893074  for n=101 N=120 smallest NMSR
#100 6.505e-05 6.854e-05 5.426e-04 5.717e-04 #MSEtr,MSE,NMSEtr,NMSE Learning Time = 27.6894330978 for n=101 N=140 

#100 7.670e-05 1.023e-04 6.397e-04 8.530e-04 #MSEtr,MSE,NMSEtr,NMSE Learning Time = 2154.78400517 for n=101 N=120 gpu0




##############
20190809 kuro
##############
#(1) データを作成するのに、makesamples.pyを作った（can2.py -msd ...と同じ）

#(2) オプション -DIPS 1 でグラフを表示。-DISP 0で非表示。

#(3)
### check 6-1 データ作成
export fn=geo2d n=51 a="" b="" k=2; python makesamples.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
### check 6-2 訓練とテスト
export T=100 N=100 k=2 ;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,2,2,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350 --gpu -1 -DISP 1
#100 MSE=2.8873765e-04 MSEtr=6.3794430e-05 NMSE=2.3627624e-03 NMSEtr=5.2203472e-04 Learning Time = 8.18700289726

#(4) x[:,:n_channels]=x_train[:,:n_channles]を使うことが多いので、
# can2.pyで  givendata['_x']=x[:,:n_channels]を定義し、sim.pyでcan2の学習を
#   my_plinn.store_vector_batch(net, givendata['x'][:n_train,:], givendata['y'][:n_train,:], n_train,GlobalTime,0,givendata['_x'][:n_train,:])
#で呼び、my_plinn.pyで呼ばれる
#def store_vector_batch(net, x_train, y_train,n_train, GlobalTime, phase,_x_train):#
#で変数_x_trainにgivendata['x'][:n_train,:n_channels]が設定されるようにした。
#こうすると、計算が高速化できるかもと思ったが、ほとんど変わらなかった。

#(5) my_plinn.cで、net['None_fire_number']をnet['i_firezero']と名称変更した（読みやすさ？）
#(6) am.cのcalc_AM()をcalcAMxy()に変更（高速化）

##############
20190805 kuro
##############
#(1) cupyが動かなくなってchainerを再インストールした。バージョンは6.2.0にした
pip uninstall chainer 
pip install chainer==6.2.0 #chainer.__version__=6.2.0
pip install cupy==6.2.0    #pip install 'cupy>=6.2.0,<7.0.0'

#(2) プログラムおよび実行はこのディレクトリ
/home/kuro/sotu/2019/chainer/can2py
とし、この上のディレクトリに
/home/kuro/sotu/2019/chainer/tmp
があるものとする。

#(3) パフォーマンスチェック
#see 高速化のためのPython Tips http://nonbiri-tereka.hatenablog.com/entry/2016/09/01/072402
python -m cProfile -s time can2.py ...


##############
20190802 kuro
##############
#(1) numpyとcupyを交換可能にした。
#(1-1) オプション　--gpu -1 でnumpy
       　　　　　　--gpu 0  でcupy
# switchCupy.pyで、
#use_cupy = False ならば xp=numpy
#use_cupy = True ならば xp=cupy (むちゃくちゃおそい）
#変更内容memo
df=pd.DataFrame(cuda.to_cpu(xy)) in L479@can2py.py 
perm = numpy.random.permutation(n_train) L409@my_plinn.py
V['ij2t'][int(V['t2i'][t])].append(t) L660@my_plinn.py
t=V['ij2t'][int(ii)][int(j)]	L750@my_plinn.c
y[t]=np.dot(net['cell'][int(zzs[t])]['am']['M'][0],x[t])  L165@my_plinn.c
y_hat_xi=np.dot(net['cell'][int(sxi)]['am']['M'][0],x[t]) L246
net['w']=np.zeros((n_cells,n_channels),dtype=np.float32) #in my_plinn.py
#2
#(1) 速度比較
export fn=geo2d n=51 a="" b="" k=2; python makesamples.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
export T=100 N=100 k=2 ;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,2,2,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350 --gpu -1 -DISP 1
--gpu -1 ならば xp=numpy-> Learning Time = 8.08634090424
--gpu 0  ならば xp=cupy -> Learning Time = 590.984911919 (むちゃくちゃおそい）(cupy.float64)
                           Learning Time = 726.6780231 (cupy.float32)


##############
20190726 kuro
##############
pip install joblib #???
### check 6-1
###1326
export fn=geo2d n=51 a= b=   k=2; python can2.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
###
### check 6-2
###
export T=100 N=100;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,2,2,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350
MSE=2.1533624e-04 NMSE=1.7621130e-03 MSEtr=5.9779286e-05 NMSEtr=4.8917849e-04 calc_output Time = 8.15260791779

export T=100 N=100;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,3,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350
MSE=2.2294956e-04 NMSE=1.8244134e-03 MSEtr=3.4231280e-05 NMSEtr=2.8011719e-04 calc_output Time = 8.32502293587

#nentropy_thresho=0.5
export T=100 N=100;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350
MSE=2.4461908e-04 NMSE=2.0017367e-03 MSEtr=6.4084099e-05 NMSEtr=5.2440511e-04 calc_output Time = 11.6046469212
#N=200
MSE=2.1450238e-04 NMSE=1.7552894e-03 MSEtr=5.4659180e-06 NMSEtr=4.4728027e-05 calc_output Time = 20.7665269375
#N=300
MSE=6.9700147e-04 NMSE=5.7036166e-03 MSEtr=1.6485679e-04 NMSEtr=1.3490358e-03calc_output Time = 56.5300960541


export T=100 N=100;echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.6,$T,5,50,350 
MSE=3.6946129e-04 NMSE=3.0233301e-03 MSEtr=1.1923399e-04 NMSEtr=9.7570092e-04 Learning Time = 9.13067603111
MSE=3.6946129e-04 NMSE=3.0233301e-03 MSEtr=1.1923399e-04 NMSEtr=9.7570092e-04 Learning Time = 9.09797596931 <-init_w
MSE=3.6946129e-04 NMSE=3.0233301e-03 MSEtr=1.1923399e-04 NMSEtr=9.7570092e-04 Learning Time = 8.49387693405 <-xrange

export T=100 N=200;echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.6,$T,5,50,350 
MSE=2.0243765e-04 NMSE=1.6565628e-03 MSEtr=5.2394310e-06 NMSEtr=4.2874667e-05 Learning Time = 17.9175498486

export T=50 N=100 #result is bad why?
time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 

##############
20190711（write北山）
##############
#前回から速度がかなり速くなり、精度も変化した。
#特に３次元のcheck6関数においては30倍、40倍ほど高速になっている。
#ただしC言語と比較するとまだ遅いし、精度も若干？劣る
#なぜかcheck3関数に関してはc言語よりかなり精度がよくなった
#c言語との比較はreadme.can2bfuncを参考にしてください
#大きく修正した箇所を下に記載

##############
20190118
##############
#1.北山君から貰ったプログラムを修正した（修正のおおまかな内容は20190111 ）を参照
#2. 下記の20180111修正1）～7)が大きな修正→ほぼうまくいくようになった？
#32.以下のCheck1からcheck6により動作確認。また対応する
#   元のCプログラムとの比較(can2b14-180118.7zを解凍したcan2b/readme.can2bfuncを参照)
#   も行った。性能は、目標値yと予測値ypの図示,正規化平均二乗誤差
#　　　　(NMSE=MSE/train_var; train_var=(sum_t (y_t-mean(y_t))^2))/n_train)
#   の比較、実行時間（下記のtime python ...をするとreal 12m56.687sのような
#   結果が表示される）の比較などで行った。
#　　→おおまかにはうまくいっているように見えるが、精度と速度が劣るように思える。
###
#4.以下、確認check
###
#(0)
cd can2py
#export PYTHONDONTWRITEBYTECODE=1 #pycを作成しない
#export PYTHONDONTWRITEBYTECODE   #pycを作成する　早い
###########################################################
#check1 
###########################################################
###
### check 1-1
###
export fn=ax+b   n=101 a=1 b=10 k=1 #for y=a*x+b
echo "quit"|python can2.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
###
### check 1-2
###
export T=100 N=10
echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 
###
### check 1-3 compare with 20190118 in /home/kuro/sotu/2018/can2b/readme.can2bfunc
###

###########################################################
#check2
###########################################################
###
### check2-1
###
export fn=axx+b  n=101 a=1 b=1000 k=1 #for y=a*x^2+b
echo "quit"|python can2.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)

###
### check 2-2
###
export T=100 N=10
echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 
###
### check 2-3 compare with 20190118 in /home/kuro/sotu/2018/can2b/readme.can2bfunc
###

####################################################
#check3
####################################################
###
### check 3-1
###
export fn=uxa n=101  a=0.5 b=-1  k=1 #y=u(x-a)=0 if x<a 1 otherwise. (aを0.3,0.7などに変えて実験）
echo "quit"|python can2.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
###
### check 3-2
###
export T=100 N=10 #OK?
echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 
###
### check 3-3 compare with 20190118 in /home/kuro/sotu/2018/can2b/readme.can2bfunc
###

####################################################
#check4
####################################################
###
### check 4-1
###101
export fn=geo1d  n=201 a=1000 b=-1 k=1 #for 1d version of fn=13 #高台、斜面、平地、小山からなる１次元データ(２次元のfn=13を１次元化したもの）
echo "quit"|python can2.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
###
### check 4-2
###
export T=100 N=100  #good export ncells=7;it=100   #good if modify init_batch_wvector
echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 
###
### check 4-3 compare with 20190118 in /home/kuro/sotu/2018/can2b/readme.can2bfunc
###

####################################################
#check5
####################################################
###
### check 5-1
###1326
export fn=axx+b2d n=51  a=1 b=1000 k=2 #for nx=a, ny=b
echo "quit"|python can2.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
###
### check 5-2
###
export T=100 N=20  #result is bad why?
echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 
###
### check 5-3 compare with 20190118 in /home/kuro/sotu/2018/can2b/readme.can2bfunc
###

####################################################
#check6
####################################################
###
### check 6-1
###1326
export fn=geo2d n=51 a= b=   k=2 #for nx=a, ny=b
echo "quit"|python can2.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)
###
### check 6-2
###
export T=100 N=100;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,2,0,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350
MSE=1.8765454e-04 NMSE=1.5355915e-03 MSEtr=3.0136926e-05 NMSEtr=2.4661278e-04 calc_output Time = 8.83739304543

export T=100 N=100;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,2,2,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350
MSE=2.1533624e-04 NMSE=1.7621130e-03 MSEtr=5.9779286e-05 NMSEtr=4.8917849e-04 calc_output Time = 7.52019000053

export T=100 N=100;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350
MSE=2.4461908e-04 NMSE=2.0017367e-03 MSEtr=6.4084099e-05 NMSEtr=5.2440511e-04 calc_output Time = 11.4567801952

export T=100 N=100;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,3,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350
MSE=2.2294956e-04 NMSE=1.8244134e-03 MSEtr=3.4231280e-05 NMSEtr=2.8011719e-04 calc_output Time = 8.32502293587

#nentropy_thresho=0.5
export T=100 N=100;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.5,$T,5,50,350
MSE=2.4461908e-04 NMSE=2.0017367e-03 MSEtr=6.4084099e-05 NMSEtr=5.2440511e-04 calc_output Time = 11.6046469212
#N=200
MSE=2.1450238e-04 NMSE=1.7552894e-03 MSEtr=5.4659180e-06 NMSEtr=4.4728027e-05 calc_output Time = 20.7665269375
#N=300
MSE=6.9700147e-04 NMSE=5.7036166e-03 MSEtr=1.6485679e-04 NMSEtr=1.3490358e-03calc_output Time = 56.5300960541


export T=100 N=100;echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.6,$T,5,50,350 
MSE=3.6946129e-04 NMSE=3.0233301e-03 MSEtr=1.1923399e-04 NMSEtr=9.7570092e-04 Learning Time = 9.13067603111
MSE=3.6946129e-04 NMSE=3.0233301e-03 MSEtr=1.1923399e-04 NMSEtr=9.7570092e-04 Learning Time = 9.09797596931 <-init_w
MSE=3.6946129e-04 NMSE=3.0233301e-03 MSEtr=1.1923399e-04 NMSEtr=9.7570092e-04 Learning Time = 8.49387693405 <-xrange

export T=100 N=200;echo "quit"|time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.6,$T,5,50,350 
MSE=2.0243765e-04 NMSE=1.6565628e-03 MSEtr=5.2394310e-06 NMSEtr=4.2874667e-05 Learning Time = 17.9175498486

export T=50 N=100 #result is bad why?
time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 
###
### check 5-3 compare with 20190118 in /home/kuro/sotu/2018/can2b/readme.can2bfunc
###

##############
20190711 
##############
(20190711修正1)ベクトル化計算
数値計算においてnumpyライブラリを使い計算させるようにした。
例えば以下のような計算でベクトルの計算においては直訳for文からnp.dot()に変更
#original
#  for i in range(nx):
#    g[i]=0
#    for j in range(nx):
#      g[i]+= q['P'][i,j]*q['x'][j]

#numpy
  g=sp.dot(q['P'], q['x'])


(20190711修正2)ブロードキャストの使用
my_plinn.pyのcalc_Voronoi関数において
入力データxがどのセルに1番近いかソートを使って計算する箇所がかなり時間がかかるので
先生から送られてきたbroadcast.pyを参考にブロードキャストを使用し高速化させた。
この変更により精度が若干変わった？？。しかしif V['i2v'][i] < 0:continueの条件を組み込むこと
ができなかったので修正をお願いしたいです。(わざわざ組み込まなくても良い?)
他にmodify_w_batchとcalc_outputとの2箇所でブロードキャストを使用した。(新規にブロードキャストを使用したcalc_output2を作成)
アルゴリズムを若干変更した。

(20190711修正3)n_firesのカウント場所の変更
ブロードキャストの都合上わざわざのn_firesのカウントでforループ書くのは無駄であるので
calc_Voronoi関数においてn_firesのカウントと
net['cell'][i]['v']<=0のセル番号を記憶させるnet['None_fire_number']を新たに追加

##############
20190111 
##############
（20180111修正１）immutable, mutable
s,d2=init_sort_weights(net,s,d2,x[t]):
s,d2=sort_weights(net,s,d2,x[t]):
に変更

（20180111修正２）my_plinn.c のinit_net(net,args)で、
net['cell'][i]['w']=net['w'][i] =np.zeros((n_cells,n_channels),dtype=np.float64)
のように参照渡しのようにしているが、pythonではポインタ受け渡しの効果はないので、
net['cell'][i]['w']は使わずnet['w'][i]のみを使うようにした。
同様に、net['dw']もそのようにした.

（20180111修正３）
reinit_cell_batch(net,x_train,y_train,n_train)			#再初期化を行う(ほぼ移植完了だが不安)
のリターンが設定されていなかった、すなわち
　return 
だったので
　return reinit
と修正

（20180111修正4）
export fn=1  a=3   b=4 n=101 ncells=10    k=1 #for y=a*x+b
echo "quit"| python can2.py -msd $fn,$a,$b,$n #make sample data (tmp/train.csv tmp/test.csv)
export ncells=10;it=10
time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -y 0,0,0,1 -x 0,0,0,1 -in $ncells,6,0.2,3,0,0.5,0.2 -ex 1,0.005,0.7,$it,5,50,350 
を実行すると、連想行列の値がおかしかった。これは
calc_Voronoi(net,x_train,y_train,n_train,GlobalTime)で
ltemp = y[L_sort_index[j]]
がmutable?であり、次のltempへの入力値がy[]に代入されておかしくなっていたので、
ltemp = y[L_sort_index[j]]+0.0 #deepcopy
に修正

修正5

  alpha = net['gamma0'] / (1.+GlobalTime/net['Tgamma'])*(net['xwidth'])/(dwNorm+1.0e-10) 
を
  alpha = net['gamma0'] / (1.+float(GlobalTime)/net['Tgamma'])*(net['xwidth'])/(dwNorm+1.0e-10) #float!!!!20190115
に修正

修正６
copy.copy　を　copy.deepcopy

修正７
my_plinn.reinit_cell_batch(net,x,y,n_train,GlobalTime) で
          if length > 1e-10 and length < min_length:			#最小となる長さと訓練データ番号を保存(ちょうど０は考慮しない)
を
          if length > 1e-5 and length < min_length:			#最小となる長さと訓練データ番号を保存(ちょうど０は考慮しない)
に変更→1e-5はなぜうまくいく？


#(0)サンプルデータを作る
export PYTHONDONTWRITEBYTECODE=1 #pycを作成しない
cd /home/kuro/sotu/2018/chainer/can2py
export fn=1  a=3   b=4 n=101 ncells=10   k=1 #for y=a*x+b
export fn=2  a=1   b=5 n=101 ncells=2    k=1 #for y=a*x^2+b
export fn=3  a=201 b=-1 n=-1  ncells=10  k=1 #for 1d version of fn=13
export fn=4  a=0.5 b=101 n=-1  ncells=2  k=1 #y=u(x-a)=0 if x<a 1 otherwise.
export fn=10 a=101 b=101 n=-1 ncells=200 k=2 #for nx=a, ny=b
export fn=13 a=51 b=51  n=-1  ncells=2   k=2 #for nx=a, ny=b

export fn=ax+b    a=3   b=4   n=101 ncells=10    k=1 #for y=a*x+b            fn=1
export fn=axx+b   a=1   b=5   n=101 ncells=2    k=1 #for y=a*x^2+b           fn=2
export fn=geo1d   a=-1  b=-1  n=201 ncells=10  k=1 #for 1d version of fn=13, fn=3
export fn=uxa     a=0.5 b=-1 n=101  ncells=2  k=1 #y=u(x-a)=0 if x<a 1 otherwise., fn=4
export fn=axx+b2d a=101 b=101 n=101 ncells=200 k=2 #for nx=a, ny=b,          fn=10
export fn=geo2d a=51 b=51  n=-1  ncells=2   k=2 #for nx=a, ny=b,            fn=13
python can2.py -msd $fn,$n,$a,$b #make sample data (tmp/train.csv tmp/test.csv)

#(1)
k=`cat tmp/train.csv |awk 'BEGIN{FS=" "}END{print NF-1;}'` #k=1
export ncells=10;it=10
time python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -y 0,0,0,1 -x 0,0,0,1 -in $ncells,6,0.2,3,0,5,0.2 -ex 1,0.05,0.7,$it,5,50,350 
quit
export fntest=tmp/test.csv fnpred=predict.dat; 
if [ "$k" == "1" ]; then show1dpred.sh ; else show2dpred.sh ;fi
0,5,8
for i in range(net['n_cells']):print('V{} {}'.format(i,net['V']['ij2t'][i]))
for i in range(net['n_cells']):print('{} w{} M{}'.format(i,net['w'][i],net['cell'][i]['am']['M']))
for t in range(givendata['n_total']): print('x{} yr,y,Y{}'.format(t,my_plinn.calc_output(net,test['x'][t])))
for t in range(givendata['n_total']):print('t{} x{} y{} M{}'.format(t,net['cell'][i]['am']['x'], net['cell'][i]['am']['y'], net['cell'][i]['am']['M'])
[ 0.58  1.  ] [ 0.58] [[ 0.25170221  0.43396932]]

(2)
emacs /home/kuro/sotu/2018/can2b/main.c
M-x gud-gdb #gdb -fullname can2
make DEBUG=-g
run
1          #0:time series, 1:funciton approximation,3:ijcnn04,4:RangeData #(1) process in  load_data() 
1 0        #k1 k2
/home/kuro/sotu/2018/chainer/can2py/tmp/train.csv
/home/kuro/sotu/2018/chainer/can2py/tmp/test.csv
0.000000e+00 0.000000e+00 0.000000e+00 0.000000e+00 0.000000e+00:0.000000e+00:0.000000e+00:0.000000e+00 
#(1e) load_data() finish 
#### check tmp/train+test.csv 
in          #(2) call init_net() 
10         #number of units
6           #n_compare
0.2 3 0     #v_thresh vmin vmin2
0.5         #v_ratio
0.2 0.05 0.7   #width gamma 
#(2e) init_net() finish 
ex          #(3)call exec_sim()
1 0.05 0.7   #<0:online,1:batch>, <gamma0>, <entropy_thresh>     
100        i_times number of learning iterations	        
5 50 350    number-of-display, rot_x, rot_z			       
quit
#show y and yp (y_prediction)
export dcan2py=/home/kuro/sotu/2018/chainer/can2py
export fntest=$dcan2py/tmp/test.csv fntrain=$dcan2py/tmp/train.csv fnpred=predict.dat; 
k=`cat $fntrain |awk 'BEGIN{FS=" "}END{print NF-1;}'` #k=1 or 2
if [ "$k" = "1" ]; then $dcan2py/show1dpred.sh; else $dcan2py/show2dpred.sh ; fi
#show NMSE_train and NMSE (NMSE=MSE/train_var; train_var=(sum_t (y_t-mean(y_t))^2))/n_train)
gnuplot
set logscale y;set format y "%.1e";plot "tmp/mse_t.csv" using 0:3 w lp t "NMSEtr", "" using 0:4 w lp t "NMSE"
pause -1 "Type quit to quit"



##############
20190107 see readme_CAN2_kitayama.txt
###############
(0)サンプルデータを作る
cd /home/kuro/sotu/2018/chainer
python can2_kitayama.py -msd 10,10 #make sample data (tmp/train.csv tmp/test.csv)

(1)学習させる
#python can2_kitayama.py -fn /home/kuro/sotu/2018/chainer/tmp/train.csv,/home/kuro/sotu/2018/chainer/tmp/test.csv -k 2,0 -y 0,81,0,1 -x 0,0,0,1 -in 10,6,0.2,3,0,5,0.2 -ex 1,0.005,0.7,100,5,50,350 
#python can2_kitayama.py -fn /home/kuro/sotu/2018/chainer/tmp/train.csv,/home/kuro/sotu/2018/chainer/tmp/test.csv -k 2,0 -y 0,81,0,1 -x 0,0,0,1 -in 100,6,0.2,3,0,5,0.2 -ex 1,0.005,0.7,100,5,50,350 

python can2_kitayama.py -fn /home/kuro/sotu/2018/chainer/tmp/train.csv,/home/kuro/sotu/2018/chainer/tmp/test.csv -k 2,0 -y 0,0,0,1 -x 0,9,0,1 -in 10,6,0.2,3,0,5,0.2 -ex 1,0.005,0.7,100,5,50,350 
export PYTHONDONTWRITEBYTECODE=1
python can2_kitayama.py -fn /home/kuro/sotu/2018/chainer/tmp/train.csv,/home/kuro/sotu/2018/chainer/tmp/test.csv -k 2,0 -y 0,0,0,1 -x 0,9,0,1 -in 1,6,0.2,3,0,5,0.2 -ex 1,0.005,0.7,100,5,50,350 


##sudo apt install gdb-dbg
make all-clean;make DEBUG=-g

C-x f /home/kuro/sotu/2018/can2b/main.c
M-x gud-dgb
#
#emacs -f gud-gdb&
#gdb -fullname can2
##emacs -f gdb&
##gdb -i=mi can2

break calc_Voronoi

run
1          #0:time series, 1:funciton approximation,3:ijcnn04,4:RangeData #(1) process in  load_data() 
2 0        #k1 k2
/home/kuro/sotu/2018/chainer/tmp/train.csv
/home/kuro/sotu/2018/chainer/tmp/test.csv
0 0 0 1    #ymin0 ymax0 ymin ymax
0 9 0 1    #x[0]min0 max0 xmin xmax
0 9 0 1    #x[1]min0 max0 xmin xmax
0 0 0      #r1 r2 (r1/r2 for integers r1 and r2 is the resolution).no digitization if r1=0
#(1e) load_data() finish 
#### check tmp/train+test.csv 
in          #(2) call init_net() 
1         #number of units
6           #n_compare
0.2 3 0     #v_thresh vmin vmin2
0.5         #v_ratio
0.2         #width 
#(2e) init_net() finish 
ex          #(3)call exec_sim()
1 0.05 0.7   #<0:online,1:batch>, <gamma0>, <entropy_thresh>     
100        i_times number of learning iterations	        
5 50 350    number-of-display, rot_x, rot_z			       


##############
20180813-0831
###############can2.py am.py sim.py
#(0) make sample data tmp/train.csv tmp/test.csv
python can2.py -msd 10,10 #make sample data (tmp/train.csv tmp/test.csv)

#(1) coding done for load_data() and init_net() (com:in)
#    now(20180831) coding can2.py:409 callis exec_sim() in sim.py -> store_vector_batch() in my_plinn.py
python can2.py -fn /home/kuro/sotu/2018/chainer/tmp/train.csv,/home/kuro/sotu/2018/chainer/tmp/test.csv -k 2,0 -y 0,81,0,1 -x 0,0,0,1 -in 400,6,0.2,3,0,0.5,0.2 -ex 1,0.005,0.7,100,5,50,350
#
#python can2.py -fn /home/kuro/sotu/2018/chainer/tmp/train.csv,/home/kuro/sotu/2018/chainer/tmp/test.csv -k 2,0 -y 0,81,0,81 -in 400,6,0.2,3,0,0.5,0.2 -ex 1,0.005,0.7,100,5,50,350
#
#python can2.py -fn /home/kuro/sotu/2018/chainer/tmp/train.csv,/home/kuro/sotu/2018/chainer/tmp/test.csv -k 2,0 -y 0,81,0,1 -in 400,6,0.2,3,0,0.5,0.2 -ex 1,0.005,0.7,100,5,50,350


### オリジナルのcan2（c言語版）のデバッグ
[1]
cd /home/kuro/sotu/2018/can2b
make all-clean
make DEBUG=-g
##########
#[2] emacsを起動し、gdb[2-1]またはgud-gdb[2-1']を行う。
#注意１：gdb[2-1]は、GUD-bufferとIO-bufferを、うまく選択しながらキーボード入力しないといけない
#注意２：IO-bufferのキーボード入力のとき、C-cで中断した後、GUD-bufferでupを数回すると、
　　　　　ソースファイルが現れる。
##########
##########
#[2-1] 
wget --http-user=kurolab --http-password=0kurolab http://kurolab.cntl.kyutech.ac.jp/~kuro/sotu/2018/site-gdb.el -P ~/lib/emacs/
をしておくと、以下の、「M-x gdb-many-windows」 が、メニューバーで実行できる
cd /home/kuro/sotu/2018/can2b;emacs -f gdb&
gdb -i=mi can2
#M-x gdb-many-windows (M-x == ESC x)
#[2-1']
cd /home/kuro/sotu/2018/can2b;emacs -f gud-gdb&
gdb -fullname can2

##########
#[3] ブレークポイントの設定
#break main        #済み
#break load_data   #済み
#break init_net    #済み
#break exec_sim    #済み
break learn_net    #
break learn_net_base
#[4] 実行
run #
1          #0:time series, 1:funciton approximation,3:ijcnn04,4:RangeData #(1) process in  load_data() 
2 0        #k1 k2
/home/kuro/sotu/2018/chainer/tmp/train.csv
/home/kuro/sotu/2018/chainer/tmp/test.csv
0 0 0 0    #ymin0 ymax0 ymin ymax
#(1e) load_data() finish 
#### check tmp/train+test.csv 
in          #(2) call init_net() 
400         #number of units
6           #n_compare
0.2 3 0     #v_thresh vmin vmin2
0.5         #v_ratio
0.2         #width 
#(2e) init_net() finish 
ex          #(3)call exec_sim()
1 0.05 0.7   #<0:online,1:batch>, <gamma0>, <entropy_thresh>     
100        i_times number of learning iterations	        
5 50 350    number-of-display, rot_x, rot_z			       
