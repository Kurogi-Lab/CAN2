#####################
#can2c: can2-c-language  without Open-CV
####
#### Execute 'make' for the first time !!!
####
###################
20200204
###################
#バギング時系列予測 with 並列処理
#bagging prediction with parallel-processing for Murata
#(1)
make
make data-clean
export T=100 Tpinv=-1 k=10 N=50 seed=1 b=20 a=1.0 tp0=2000 Ey=15 m_cpu=0 nop=1;let tp1=$tp0+500
ensrs ../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 2:$b:$a:$seed:$m_cpu $N t:0-2000:$tp0-`echo $tp0+500|bc`:1:$Ey bg:/dev/null M:1-1:1 ib:0:0:0:0 k:$k T:$T Tpinv:$Tpinv y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 vt:0.5 vr:10 nop:$nop
[100,-1](11.8s) #{T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2000-2500:15H144
#結果表示は
gnuplot
set grid; plot "tmp/pred2000-2500.dat" using 2:1 w l t "yp","" using 2:3 w l t "y", "" using 2:($1-$3) w l t "yp-y"

#(2) tr0-tr1=0-2000の保存netを用いて、tp0=2000,2100,...,3000までの予測、
for tp0 in `seq 2000 100 3000` ; do
ensrs ../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 2:$b:$a:$seed:$m_cpu $N t:0-2000:$tp0-`echo $tp0+500|bc`:1:$Ey bg:/dev/null M:1-1:1 ib:0:0:0:0 k:$k T:$T Tpinv:$Tpinv y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 vt:0.5 vr:10 nop:$nop
done
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2000-2500:15H144 to remove prediction with big error
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2100-2600:15H97
[100,-1](0.2s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2200-2700:15H193
[100,-1](0.2s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2300-2800:15H168
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2400-2900:15H203
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2500-3000:15H251
[100,-1](0.2s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2600-3100:15H185
[100,-1](0.2s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2700-3200:15H156
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2800-3300:15H230
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2900-3400:15H218
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:3000-3500:15H239

[100,-1](0.2s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:3000-3500:15H239
[100,-1](11.8s) #{T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2000-2500:15H144
[100,-1](0.4s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2000-2500:15H144
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2100-2600:15H97  !!!
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2200-2700:15H193
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2300-2800:15H168
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2400-2900:15H263
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2500-3000:15H285
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2600-3100:15H185
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2700-3200:15H238
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2800-3300:15H229
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:2900-3400:15H218
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed1 nop1 m_cpu12 0-2000:3000-3500:15H239

#seed=2
[100,-1](11.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2000-2500:15H158
[100,-1](0.4s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2000-2500:15H158
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2100-2600:15H235
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2200-2700:15H269
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2300-2800:15H159
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2400-2900:15H233
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2500-3000:15H226
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2600-3100:15H186
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2700-3200:15H239
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2800-3300:15H139
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:2900-3400:15H190
[100,-1](0.3s) #[T,Tinv] k10 N50 b20(nens1) a1 seed2 nop1 m_cpu12 0-2000:3000-3500:15H165

#ensrsomp /home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 2:20:0.7:1 50 t:0-2000:2000-2500 bg:/dev/null M:1-1:1 ib:0:0:0:0 k:10 y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:50 vt:0.5 vr:10 lossall:1 DISP:2 y:-18.5:18.5:0:1 nop:1 Tpinv:-1

###
#tp0=2100 に対し，a=2.2 のとき安定してよい結果、b=40,50,...,100, 
export T=100 Tpinv=-1 k=10 N=50 seed=1 b=50 a=2.2 tp0=2100 Ey=15 m_cpu=0 nop=1;let tp1=$tp0+500
ensrs ../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 2:$b:$a:$seed:$m_cpu $N t:0-2000:$tp0-`echo $tp0+500|bc`:1:$Ey bg:/dev/null M:1-1:1 ib:0:0:0:0 k:$k T:$T Tpinv:$Tpinv y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 vt:0.5 vr:10 nop:$nop
[100,-1](18.4s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu6 0-2000:2100-2600:15H220 Ubuntu12.04 with icc(intel-compiler)
[100,-1](48.8s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2100-2600:15H220 Ubuntu14.04 with gcc-compiler
[100,-1](1.3s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2000-2500:15H158
[100,-1](1.3s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2100-2600:15H220
[100,-1](1.2s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2200-2700:15H195
[100,-1](1.3s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2300-2800:15H167
[100,-1](1.3s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2400-2900:15H229
[100,-1](1.3s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2500-3000:15H228
[100,-1](1.2s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2600-3100:15H185
[100,-1](1.3s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2700-3200:15H240
[100,-1](1.3s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2800-3300:15H258
[100,-1](1.3s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:2900-3400:15H310
[100,-1](1.2s) #[T,Tinv] k10 N50 b50(nens1) a2.2 seed1 nop1 m_cpu12 0-2000:3000-3500:15H244
##b=100

[100,-1](22.5s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2000-2500:15H158 Ubuntu12.04 with icc(intel-compiler)
[100,-1](9.7s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2000-2500:15H158
[100,-1](9.6s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2100-2600:15H234
[100,-1](9.7s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2200-2700:15H194
[100,-1](9.5s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2300-2800:15H169
[100,-1](9.2s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2400-2900:15H229
[100,-1](9.1s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2500-3000:15H227
[100,-1](9.2s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2600-3100:15H185
[100,-1](9.1s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2700-3200:15H270
[100,-1](9.4s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2800-3300:15H172
[100,-1](9.1s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:2900-3400:15H252
[100,-1](9.1s) #[T,Tinv] k10 N50 b100(nens1) a2.2 seed2 nop1 m_cpu6 0-2000:3000-3500:15H212


##############
20200103 <- 20191231 experiments for ensrs.py bagging method for 北山君課題
##############
#bagging test for Kitayama
#(1) old version 
export fntrain=../../can2m.result/geo1dtrain.csv fntest=../../can2m.result/geo1dtest.csv
export T=100 N=60 seed=2 Tpinv=-1 nop=1 n_bags=100 alpha=2.2 DISP=0;
../sh/can2cbagtest.sh 

#ensrs without parallel-processing  is:
time ensrsorig ../../can2m.result/geo1dtrain.csv 2:100:2.2:1 60-60:1 bg:../../can2m.result/geo1dtest.csv k:1 T:100 BIAS:1 Lstd:0:2 ib:0:0:0:0 vm2:-1 seed:2 Tpinv:50 nop:1
100-1(21.9s) 6.748e-07 #nbag(time) MSE n440,71 N60 b100 a2.2 seed2 nop1 m_cpu1 #??20200204
100-1(22.289s) 9.400e-07 71 #nbag(time) MSE ntest
export m_cpu=0

#(2) bagging test with omp(OpenMP):parallel-processing
cd ../can2comp
export m_cpu=0
time ensrs ../../can2m.result/geo1dtrain.csv 2:100:2.2:1:$m_cpu 60-60:1 bg:../../can2m.result/geo1dtest.csv k:1 T:100 BIAS:1 Lstd:0:2 ib:0:0:0:0 vm2:-1 seed:2 Tpinv:-1 nop:1
#result --> predict+.dat
[100,-1](3.6s) 6.748e-07 #[T,Tpinv](time) n440,71 k1 N60 b100 a2.2 s2 nop1 m_cpu12
[100,-1](3.5s) 1.687e-06 #[T,Tpinv](time) n440,71 k1 N60 b100 a2.2 s1 nop1 m_cpu12

[100,-1](3.7s) 1.687e-06 #time MSE n440,71 N60 b100(nens1) a2.2 seed1 nop1 m_cpu12
[100,-1](3.6s) 1.317e-06 #time MSE n440,71 N60 b100(nens1) a2.2 seed2 nop1 m_cpu12

[100,50](3.3s) 6.748e-07 #time MSE n440,71 N60 b100(nens1) a2.2 seed2 nop1 m_cpu12
[100,50](3.3s) 1.429e-06 #time MSE n440,71 N60 b100(nens1) a2.2 seed1 nop1 m_cpu12

#result
[100,-1](30.347s) 6.860762e-08 1.583188e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed2 nop1

[100,-1](254.780s) 1.000059e-07 1.911652e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b200 a2.2 seed1 nop1 laptop
[100,-1](249.955s) 8.639603e-08 1.501708e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b200 a2.2 seed2 nop1
[100,-1](263.355s) 7.012102e-08 1.397194e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b200 a2.2 seed3 nop1
[100,-1](257.426s) 2.531288e-07 2.528315e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b200 a2.2 seed4 nop1
[100,-1](255.540s) 1.089240e-07 1.530904e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b200 a2.2 seed5 nop1

[100,-1](129.208s) 1.034550e-07 2.135739e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed1 nop1 laptop
[100,-1](125.745s) 6.860762e-08 1.583188e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed2 nop1
[100,-1](125.231s) 9.110389e-08 1.765346e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed3 nop1
[100,-1](134.363s) 2.762765e-07 2.357939e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed4 nop1
[100,-1](127.488s) 1.495858e-07 1.539922e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed5 nop1

[100,50](118.878s) 8.000587e-08 1.792482e-06   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed1 nop1 laptop
[100,50](116.916s) 4.509503e-08 9.400353e-07   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed2 nop1
[100,50](119.41s) 3.610943e-08 8.435933e-07   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed3 nop1
[100,50](120.517s) 5.521946e-08 7.554505e-07   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed4 nop1
[100,50](118.602s) 7.941070e-08 9.225388e-07   #[T,Tpinv] MSEtr MSE n200,71 N60 b100 a2.2 seed5 nop1

##############
20191227 experiments for can2.py time-series pythen version
##############
#(1) 時系列予測機能のpythonへの移植のためのcan2.pyとの比較実験例:
#    (詳細は../can2py/readmecan2py.txt参照)
export T=100 Tpinv=-1 k=10 N=50 seed=47 Ey=15 nop=1 #カット＆ペーストここから
cat > param.dat <<EOF
0        #0:time-series,1:function,3:ijcnn04,4:range-data           
10 0     #dimensionality k1, k2				       
/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt
0-2000:2000-2500:0:0:$Ey			        
-18.5 18.5 0 1 #y-normalization[ymin0:ymax0]->[ymin1:ymax1]
0 0 0.000000e+00 #r1 r2 					        
in          init-net			                
50          number-of-cells				          	
6           n_compare					
5.000000e-01 3 0     v_thresh vmin vmin2	         		
1.000000e+01           v_ratio				                
2.000000e-01 1.400000e-03 7.000000e-01   width,gamma  #window width                         
ex          execution						
1 1.400000e-03 7.000000e-01   #<0:online,1:batch>, <gamma0>, <entropy_thresh>     
100        i_times number of learning iterations	        
100 50 350    number-of-display, rot_x, rot_z			       
msp       
qu        
EOF
can2 nop:$nop seed:$seed DISP:1 Tpinv:-1 <param.dat #カット＆ペーストここまで 

###
100(2.812s) 3.650e-08 2.292e-04 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed1 nop1 H194(Ey15) t0-2000:2000-2500:0:0
100(2.821s) 3.650e-08 1.806e-04 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed1 nop1 H269(Ey15) t0-2000:2100-2600:0:0
100(2.735s) 3.650e-08 1.163e-04 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed1 nop1 H134(Ey15) t0-2000:2200-2700:0:0
100(2.741s) 3.650e-08 9.719e-05 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed1 nop1 H158(Ey15) 
###
100(2.791s) 3.243e-08 1.185e-04 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed1 nop1 H101(Ey15) t0-2000:2000-2500:0:0
100(2.661s) 3.837e-08 1.002e-04 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed2 nop1 H158(Ey15) 
100(2.670s) 2.773e-08 1.021e-04 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed3 nop1 H150(Ey15) 
100(2.650s) 3.474e-08 1.713e-04 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed4 nop1 H175(Ey15) 
100(2.750s) 3.673e-08 1.150e-04 #ep(time),MSEtr,MSE k10 N50 T100,-1 seed5 nop1 H121(Ey15) 

#(4-1)黒木の課題：
#can2 nop:1 seed:47 Tpinv:50 

##############
20191108
##############
#(1) 時系列予測機能のpythonへの移植のための実験例:
#can2 nop:1 seed:47 Tpinv:50 #カット＆ペーストここから
can2 nop:1 seed:47          #カット＆ペーストここから
0        #0:time-series,1:function,3:ijcnn04,4:range-data           
10 0     #dimensionality k1, k2				       
/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt
0-2000:2000-2500			        
-1.850000e+01 1.850000e+01 0.000000e+00 1.000000e+00 #y-normalization[ymin0:ymax0]->[ymin1:ymax1]
0 0 0.000000e+00 #r1 r2 					        
in          init-net			                
50          number-of-cells				          	
6           n_compare					
5.000000e-01 3 0     v_thresh vmin vmin2	         		
1.000000e+01           v_ratio				                
2.000000e-01 1.400000e-03 7.000000e-01   width,gamma  #window width                         
ex          execution						
1 1.400000e-03 7.000000e-01   #<0:online,1:batch>, <gamma0>, <entropy_thresh>     
100        i_times number of learning iterations	        
100 50 350    number-of-display, rot_x, rot_z			       
msp       #カット＆ペーストここまで
qu         
###############
can2 nop:1 seed:17 #cut&past：ここから
0        #0:time-series,1:function,3:ijcnn04,4:range-data           
10 0     #dimensionality k1, k2				       
/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt
0-2000:2000-2500			        
-1.850000e+01 1.850000e+01 0.000000e+00 1.000000e+00 #y-normalization[ymin0:ymax0]->[ymin1:ymax1]
0 0 0.000000e+00 #r1 r2 					        
in          init-net			                
50          number-of-cells				          	
6           n_compare					
0.2 3 0     v_thresh vmin vmin2	         		
0.5           v_ratio				                
0.2 1.400000e-03 7.000000e-01   width,gamma  #window width                         
ex          execution						
1 1.400000e-03 7.000000e-01   #<0:online,1:batch>, <gamma0>, <entropy_thresh>     
100        i_times number of learning iterations	        
100 50 350    number-of-display, rot_x, rot_z			       
msp       #cut&past：一旦ここまで
qu         

##############
20191108
##############
#(1) 時系列予測機能のpythonへの移植のための実験例:
can2 nop:1 #cut&past：ここから
0                #0:timeseries,1:chaos prepare_data() in my_function.c
10		 #channels                 
/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt
2000 2200       #Ttrain,Ttotal: points in time of training and total data 
0 0 0 0       #y0min y0max y1min y1max for normalization
in               #
300		 #n_cells storing vectors          
20		#n_compare                
0.5		#v_thresh                 
10		#v_ratio
0.2		#width   window width             
ex		#execute 
1 0 1		#i j k :i=0:online,i=1:batch, j/kは分解能(resolution)
100		#iterations to execute    
50		#display
msp　　         #cut&past：一旦ここまで
quit
/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt
/home/kuro/sotu/2019/chaos.data/lorenz1e-6T0.025n20000p256m1_gmp.txt
/home/kuro/sotu/2019/chaos.data/lorenz1e-8T0.025n10000p64m1_gmp.txt
/home/kuro/sotu/2019/can2m/tmp/lorenz1e-6T0.025n10000p64m1_gmp.txt

xterm -geometry 80x5+0-0 -e gnuplot w.gpl&
xterm -geometry 80x5+0-0 -e gnuplot e_msp.gpl&
xterm -geometry 80x5+0-0 -e gnuplot y_msp.gpl &
>>100ssp3.0297e-03(0.000075)68msp8.7961e+00(0.217893)100train1.2929e-07(0.000000)N300k10w0.2vm0:0
>>200ssp3.0272e-03(0.000075)68msp8.7961e+00(0.217893)200train7.7922e-08(0.000000)N300k10w0.2vm0:0

can2 nop:0 #cut&past：ここから
0                #0:timeseries,1:chaos prepare_data() in my_function.c
10		 #channels                 
/home/kuro/sotu/2019/can2m/tmp/lorenz1e-6T0.025n10000p64m1_gmp.txt
2000 2200       #Ttrain,Ttotal: points in time of training and total data 
0 0 0 0       #y0min y0max y1min y1max for normalization
in          init-net			                
300          number-of-cells				          	
6           n_compare					
2.000000e-01 3 0     v_thresh vmin vmin2	         		
5.000000e+00           v_ratio				                
2.000000e-01 5.000000e-02 7.000000e-01   width,gamma  #window width                         
ex          execution						
1 5.000000e-02 7.000000e-01   #<0:online,1:batch>, <gamma0>, <entropy_thresh>     
100        i_times number of learning iterations	        
200 50 350    number-of-display, rot_x, rot_z			       
msp
>>31ssp6.3508e-04(0.000016)8msp1.6138e+00(0.039975)200train7.6231e-08(0.000000)N300k10w0.2vm3:0
MSE>>200ssp7.97e-04(0.000020)msp7.20e+01(1.782706)MSEtr7.62e-08N300k10+0w0.2vm3:0

MSE---;1.779887e+02 NMSE---;4.409055e+00 N200
MSE---;1.533549e+02 NMSE---;3.798838e+00 N250
MSE---;9.129003e+01 NMSE---;2.261395e+00 N300
MSE---;8.637419e+01 NMSE---;2.139623e+00 N350
MSE---;1.350445e+02 NMSE---;3.345261e+00 N400
#上のパラメータはcan2b/readme.timeseriesの以下のような行を参照し、実行すると得られる。
#./tspredv3 /home/kuro/sotu/2019/can2m/tmp/lorenz1e-6T0.025n10000p64m1_gmp.txt 0-2000:2000-2500 mp:1:1:1 DiffMode:0 Hosei:0 N:200-200:5 M:1-1:1 ib:0:0:0:0 rsa:-1:0.7:1:50 k:10 y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:100 vt:0.5 vr:10 lossall:1 DISP:0 e4t:0 e4p:0

##########
head -1990 tmp/train+test.dat >../tmp/lorenztrain.csv
tail -200 tmp/train+test.dat >../lorenztest.csv

export T=200 N=100 seed=1 Tpinv=999 nop=1 fntrain=../tmp/lorenztrain.csv fntest=../tmp/lorenztest.csv;../sh/can2csingletest.sh
export T=100 N=90 seed=1 Tpinv=50 nop=1 fntrain=../tmp/train.csv fntest=../tmp/test.csv DISP=1;../sh/can2csingletest.sh 

can2 nop:0
1          #0:time-series,1:function,3:ijcnn04,4:range-data,No.1
10 0       #dimensionality k1 k2					
../tmp/lorenztrain.csv						       	        
../tmp/lorenztest.csv				        
0.000000e+00 0.000000e+00 0.000000e+00 0.000000e+00 0.000000e+00:0.000000e+00:0.000000e+00:0.000000e+00   #y-normalization[ymin0:ymax0]->[ymin1:ymax1]
in          init-net			                
300          number-of-cells				          	
6           n_compare					
2.000000e-01 3 0     v_thresh vmin vmin2	         		
5.000000e+00           v_ratio				                
2.000000e-01 5.000000e-02 7.000000e-01   width,gamma  #window width                         
ex          execution						
1 5.000000e-02 7.000000e-01   #<0:online,1:batch>, <gamma0>, <entropy_thresh>     
200        i_times number of learning iterations	        
200 50 350    number-of-display, rot_x, rot_z			       
ssp0_      #prediction of training data -> predict0.dat    
qu         
200 7.731e-08 5.701e-04 1.23e-09 1.41e-05 MSEtr MSE NMSEtr NMSE N300k10w0.2vm3:0
200 9.368e-08 5.792e-04 1.49e-09 1.43e-05 MSEtr MSE NMSEtr NMSE N250k10w0.2vm3:0
200 7.158e-08 2.108e-04 1.14e-09 5.22e-06 MSEtr MSE NMSEtr NMSE N350k10w0.2vm3:0 

##############
20191101
##############
#(1) 計算時間をより正確に計るため，学習途中の情報を非表示にするオプションnop=1 (noprint mode)を追加．
     →nop=1はnop=0の約1/2の計算時間？
#
export T=100 N=90 seed=1 Tpinv=50 nop=1 fntrain=../../can2m.result/train.csv fntest=../../can2m.result/test.csv;../sh/can2csingletest.sh 
export T=100 N=90 seed=1 Tpinv=50 nop=1 fntrain=../tmp/train.csv fntest=../tmp/test.csv;../sh/can2csingletest.sh 
#
export T=100 N=90 seed=1 Tpinv=50 nop=1 fntrain=../tmp/train.csv fntest=../tmp/test.csv DISP=1 n_bags="1" alpha=1;../sh/can2cbagtest.sh
100 6.742e-09 3.655e-07 2.245s(0:0:2.245) #MSEtr MSE Time n200,71 N90 can2c-single seed1 nop1 
100 6.742087e-09 3.655233e-07  3.245s(0:0:3.245) #MSEtr MSE Time n200,71 N90 b1 a1 seed1 nop1

100 3.635e-08 3.671e-07 0.232s(0:0:0.232) #MSEtr MSE Time n200,71 N90 can2c-single seed2 nop1 Desktop
100 1.269e-06 3.968e-06 0.223s(0:0:0.223) #MSEtr MSE Time n200,71 N90 can2c-single seed3 nop1 Desktop
100 2.457e-08 7.441e-07 0.357s(0:0:0.357) #MSEtr MSE Time n200,71 N90 can2c-single seed1 nop0 Desktop
100 3.635e-08 3.671e-07 0.616s(0:0:0.616) #MSEtr MSE Time n200,71 N90 can2c-single seed2 nop0 Desktop
100 1.269e-06 3.968e-06 0.602s(0:0:0.602) #MSEtr MSE Time n200,71 N90 can2c-single seed3 nop0 Desktop
##							         
100 2.457e-08 7.441e-07 0.874s(0:0:0.874) #MSEtr MSE Time n200,71 N90 can2c-single seed1 nop1 laptop
100 3.635e-08 3.671e-07 0.893s(0:0:0.893) #MSEtr MSE Time n200,71 N90 can2c-single seed2 nop1  laptop
100 7.987e-08 4.708e-07 0.890s(0:0:0.890) #MSEtr MSE Time n200,71 N90 can2c-single seed4 nop1  laptop
100 8.119e-06 1.396e-05 0.923s(0:0:0.923) #MSEtr MSE Time n200,71 N90 can2c-single seed5 nop1  laptop
100 2.457e-08 7.441e-07 1.577s(0:0:1.577) #MSEtr MSE Time n200,71 N90 can2c-single seed1 nop0  laptop
100 3.635e-08 3.671e-07 1.677s(0:0:1.677) #MSEtr MSE Time n200,71 N90 can2c-single seed2 nop0  laptop
100 1.269e-06 3.968e-06 1.694s(0:0:1.694) #MSEtr MSE Time n200,71 N90 can2c-single seed3 nop0  laptop

#bagging
export T=100 N=60 seed=2 Tpinv=50 nop=1 fntrain=../tmp/train.csv fntest=../tmp/test.csv n_bags=100 alpha=2.2;../sh/can2cbagtest.sh 
sh 
100 5.193899e-08 1.428614e-06  28.507s(0:0:28.507) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed1 nop1
100 9.485342e-08 6.748179e-07  28.3s(0:0:28.3) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed2 nop1
100 9.407648e-08 4.540634e-07  28.515s(0:0:28.515) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed3 nop1
100 5.193899e-08 1.428614e-06  74.789s(0:1:14.789) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed1 nop0
100 9.485342e-08 6.748179e-07  96.766s(0:1:36.766) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed2 nop0
100 9.407648e-08 4.540634e-07  87.559s(0:1:27.559) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed3 nop0
100 9.407648e-08 4.540634e-07  101.605s(0:1:41.605) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed3 nop0

100 5.193899e-08 1.428614e-06  132.899s(0:2:12.899) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed1 nop1 yuka(laptop)
100 9.485342e-08 6.748179e-07  161.243s(0:2:41.243) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed2 nop1
100 9.407648e-08 4.540634e-07  148.344s(0:2:28.344) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed3 nop1
100 5.193899e-08 1.428614e-06  302.615s(0:5:2.615) #MSEtr MSE Time N60 b100 a2.2 n200,71 seed1 nop0

##############
20191031
##############
#(1) #(1) 学習回数T=100の後半のt=Tpinv=50以降は擬似逆行列(pseudo-inverse matrix)を使うとよい結果。
　　seedに依存しにくいcan2cのバギングでも確認。
make clean;make #or make clean;make DEBUG=-g RAND=2 GSL=1 #RAND 2 -> myrand(); GSL=1 for pinv and RLS(逐次最小二乗法）
#can2c-single #result for Geo1d_200_50_10
export T=100 N=90 seed=1 Tpinv=50 fntrain=../tmp/train.csv fntest=../tmp/test.csv;../sh/can2csingletest.sh 
#
100 2.457e-08 7.441e-07 1.270s(0:0:1.270) #MSEtr MSE Time N90 can2c-single RAND=2 seed=1 theta_r=1.1 GSL=1 Tpinv50
100 3.635e-08 3.671e-07 0.230s(0:0:0.230) #MSEtr MSE Time N90 can2c-single RAND=2 seed=2 theta_r=1.1 GSL=1 Tpinv50
100 1.269e-06 3.968e-06 0.219s(0:0:0.219) #MSEtr MSE Time N90 can2c-single RAND=2 seed=3 theta_r=1.1 GSL=1 Tpinv50
100 7.987e-08 4.708e-07 0.223s(0:0:0.223) #MSEtr MSE Time N90 can2c-single RAND=2 seed=4 theta_r=1.1 GSL=1 Tpinv50

#can2c-bagging #result for Geo1d_200_50_10
export T=100 N=60 seed=1  Tpinv=50 fntrain=../tmp/train.csv fntest=../tmp/test.csv n_bags=100 alpha=2.2;../sh/can2cbagtest.sh 
100 3.029432e-06 5.456698e-06  38.222s(0:0:38.222) #MSEtr MSE Time N20 b100 a2.2 RAND2 seed1 theta_r=1.1 Tpinv50 
100 5.377465e-08 5.987244e-07  42.473s(0:0:42.473) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed1 theta_r=1.1 Tpinv50 N40 best among N20-60
100 2.696968e-08 6.196064e-07  76.393s(0:1:16.393) #MSEtr MSE Time N50 b100 a2.2 RAND2 seed1 theta_r=1.1 Tpinv50 
100 5.193899e-08 1.428614e-06  46.973s(0:0:46.973) #MSEtr MSE Time N60 b100 a2.2 RAND2 seed1 theta_r=1.1 Tpinv50 
#
#N=40 Tpinv50
export T=100 N=40 seed=1 Tpinv=50 fntrain=../tmp/train.csv fntest=../tmp/test.csv n_bags=100 alpha=2.2;../sh/can2cbagtest.sh 
100 5.377465e-08 5.987244e-07  42.473s(0:0:42.473) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed1 theta_r=1.1 Tpinv50 best among N20-60
100 1.212115e-07 1.010994e-06  73.504s(0:1:13.504) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed2 theta_r=1.1 Tpinv50 
100 8.582186e-08 7.362504e-07  52.187s(0:0:52.187) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed3 theta_r=1.1 Tpinv50 
100 8.348910e-08 6.860912e-07  53.536s(0:0:53.536) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed4 theta_r=1.1 Tpinv50 
100 7.516317e-08 5.101630e-07  63.428s(0:1:3.428) #MSEtr MSE Time N40 b100 a2.2  RAND2 seed5 theta_r=1.1 Tpinv50 
#N=40 Tpinv999
export T=100 N=40 seed=1 Tpinv=999 fntrain=../tmp/train.csv fntest=../tmp/test.csv n_bags=100 alpha=2.2;../sh/can2cbagtest.sh 
100 1.481102e-07 1.103185e-06  46.987s(0:0:46.987) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed1 theta_r=1.1 Tpinv999
100 1.768401e-07 1.034213e-06  54.746s(0:0:54.746) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed2 theta_r=1.1 Tpinv999
100 2.072651e-07 1.256409e-06  52.694s(0:0:52.694) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed3 theta_r=1.1 Tpinv999
100 1.547743e-07 1.209358e-06  63.44s(0:1:3.44) #MSEtr MSE Time N40 b100 a2.2    RAND2 seed4 theta_r=1.1 Tpinv999
100 2.046601e-07 1.374716e-06  48.108s(0:0:48.108) #MSEtr MSE Time N40 b100 a2.2 RAND2 seed5 theta_r=1.1 Tpinv999
#N=60 Tpinv50
export T=100 N=60 seed=5  Tpinv=50 fntrain=../tmp/train.csv fntest=../tmp/test.csv n_bags=100 alpha=2.2;../sh/can2cbagtest.sh 
100 5.193899e-08 1.428614e-06  52.154s(0:0:52.154) #MSEtr MSE Time N60 b100 a2.2 RAND2 seed1 theta_r=1.1 Tpinv50
100 9.485342e-08 6.748179e-07  68.220s(0:1:8.220) #MSEtr MSE Time N60 b100 a2.2  RAND2 seed2 theta_r=1.1 Tpinv50
100 9.407648e-08 4.540634e-07  57.467s(0:0:57.467) #MSEtr MSE Time N60 b100 a2.2 RAND2 seed3 theta_r=1.1 Tpinv50
100 8.546880e-08 9.618145e-07  63.387s(0:1:3.387) #MSEtr MSE Time N60 b100 a2.2  RAND2 seed4 theta_r=1.1 Tpinv50
100 5.323706e-08 1.042482e-06  55.271s(0:0:55.271) #MSEtr MSE Time N60 b100 a2.2 RAND2 seed5 theta_r=1.1 Tpinv50
#N=60 Tpinv999
export T=100 N=60 seed=1 Tpinv=999 fntrain=../tmp/train.csv fntest=../tmp/test.csv n_bags=100 alpha=2.2;../sh/can2cbagtest.sh 
100 9.573804e-08 1.686562e-06  58.618s(0:0:58.618) #MSEtr MSE Time N60 b100 a2.2 RAND2 seed1 theta_r=1.1 Tpinv999
100 1.376990e-07 1.316682e-06  61.131s(0:1:1.131) #MSEtr MSE Time N60 b100 a2.2  RAND2 seed2 theta_r=1.1 Tpinv999
100 1.539038e-07 1.903728e-06  57.382s(0:0:57.382) #MSEtr MSE Time N60 b100 a2.2 RAND2 seed3 theta_r=1.1 Tpinv999
100 9.099572e-08 1.826675e-06  63.355s(0:1:3.355) #MSEtr MSE Time N60 b100 a2.2  RAND2 seed4 theta_r=1.1 Tpinv999
100 1.126948e-07 1.403404e-06  75.450s(0:1:15.450) #MSEtr MSE Time N60 b100 a2.2 RAND2 seed5 theta_r=1.1 Tpinv999
##############
20191025
##############
#(1) readmecan2py.txtで行ったようにmy_plinn.py #wの再初期化式(論文式(24))の係数θrを1.9から0.9と1.1にしてみた。
#-> 1.9と1.1で変わらない結果->もともと精度がよいから？
make DEBUG=-g RAND=2 #MYRAND 2 
#check can2c-single
export T=100 N=90 seed=2 fntrain=../tmp/train.csv fntest=../tmp/test.csv;../sh/can2csingletest.sh #geo1d single (1-1)
100 3.864e-07 1.344e-06 2.446s(0:0:2.446) #MSEtr MSE Time N90 can2c-single RAND=2 seed=1 theta_r=1.9
100 9.696e-08 5.638e-07 1.580s(0:0:1.580) #MSEtr MSE Time N90 can2c-single RAND=2 seed=2 theta_r=1.9
100 1.512e-06 4.108e-06 1.678s(0:0:1.678) #MSEtr MSE Time N90 can2c-single RAND=2 seed=3 theta_r=1.9
100 1.841e-07 3.123e-06 1.706s(0:0:1.706) #MSEtr MSE Time N90 can2c-single RAND=2 seed=4 theta_r=1.9

100 3.864e-07 1.344e-06 1.602s(0:0:1.602) #MSEtr MSE Time N90 can2c-single RAND=2 seed=1 theta_r=1.1
100 9.696e-08 5.638e-07 1.432s(0:0:1.432) #MSEtr MSE Time N90 can2c-single RAND=2 seed=2 theta_r=1.1
100 1.512e-06 4.108e-06 1.491s(0:0:1.491) #MSEtr MSE Time N90 can2c-single RAND=2 seed=3 theta_r=1.1
100 1.841e-07 3.123e-06 2.495s(0:0:2.495) #MSEtr MSE Time N90 can2c-single RAND=2 seed=4 theta_r=1.1

100 3.287e-06 9.201e-06 1.564s(0:0:1.564) #MSEtr MSE Time N90 can2c-single RAND=3 seed=1 theta_r=1.1
100 2.315e-07 1.179e-06 1.658s(0:0:1.658) #MSEtr MSE Time N90 can2c-single RAND=3 seed=2 theta_r=1.1
100 1.690e-05 2.816e-05 1.503s(0:0:1.503) #MSEtr MSE Time N90 can2c-single RAND=3 seed=3 theta_r=1.1
100 3.871e-07 1.418e-06 1.494s(0:0:1.494) #MSEtr MSE Time N90 can2c-single RAND=3 seed=3 theta_r=1.1

#check can2c-bagging
export T=100 N=60 seed=1 fntrain=../tmp/train.csv fntest=../tmp/test.csv n_bags=100 alpha=2.2;../sh/can2cbagtest.sh #bagging for Geo1d_200_50_10
100 9.320017e-08 1.650727e-06  43.338s(0:0:43.338) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=1 theta_r=1.1 via mesaho
100 1.375280e-07 1.250999e-06  45.247s(0:0:45.247) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=2 theta_r=1.1
100 1.528453e-07 1.886948e-06  46.593s(0:0:46.593) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=3 theta_r=1.1
100 9.239093e-08 1.799586e-06  45.290s(0:0:45.290) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=4 theta_r=1.1
100 9.456767e-08 1.610711e-06  46.344s(0:0:46.344) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=5 theta_r=1.1

100 7.837088e-08 1.446343e-06  44.275s(0:0:44.275) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=1 theta_r=1.9
100 9.043513e-08 1.206428e-06  42.933s(0:0:42.933) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=2 theta_r=1.9
100 1.450179e-07 3.445693e-06  46.168s(0:0:46.168) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=3 theta_r=1.9
100 9.714625e-08 1.533174e-06  45.416s(0:0:45.416) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=4 theta_r=1.9
100 6.665854e-08 1.128905e-06  46.275s(0:0:46.275) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=5 theta_r=1.9

100 7.837088e-08 1.446343e-06  289.481s(0:4:49.481) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=1 theta_r=1.9 via yuka

100 9.669704e-08 1.269121e-06  51.471s(0:0:51.471) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=1 theta_r=1.1 via mesaho stabler result?
100 2.149688e-07 1.733653e-06  48.124s(0:0:48.124) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=2 theta_r=1.1 via mesaho
100 7.275943e-08 1.675916e-06  50.180s(0:0:50.180) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=3 theta_r=1.1 via mesaho
100 1.030796e-07 1.645947e-06  52.927s(0:0:52.927) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=4 theta_r=1.1 via mesaho
100 1.061157e-07 1.546243e-06  49.174s(0:0:49.174) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=5 theta_r=1.1 via mesaho
100 3.348728e-07 1.567709e-06  51.591s(0:0:51.591) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=6 theta_r=1.1 via mesaho
100 1.192066e-07 1.540021e-06  58.929s(0:0:58.929) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=7 theta_r=1.1 via mesaho


#####################
20191029 
#####################
#(1) test RANDO versions
#make clean;make DEBUG=-g GSL=0 RAND=0 #RANDOM 0 
#make clean;make DEBUG=-g GSL=0 RAND=1 #DRAND48 1
make clean;make DEBUG=-g GSL=0 RAND=2 #MYRAND 2 use this !!!!
#make clean;make DEBUG=-g GSL=0 RAND=3 #ZMTRAND 3
# Cf. test GSL versions 
# make clean;make GSL=0 #without GSL for modify_M_batch 
# make clean;make GSL=1 #with GSL for modify_M_batch 
# make clean;make GSL=2 #Do not use (GSL=1 is used in meanpred.c)!!!

#(2) seed（乱数の初期値）を設定できるようにした.singleCAN2cはseedの違いでMSEの変動が大きいが、baggingCAN2Cでは小さい
#　　ようだ。
#single
#(1) single CAN2Cの実行例：
export T=100 N=90 seed=2 fntrain=../tmp/train.csv fntest=../tmp/test.csv;../sh/can2csingletest.sh #geo1d single (1-1)
100 3.864e-07 1.344e-06 1.717s(0:0:1.717) #MSEtr MSE Time N90 can2c-single RAND=2 seed=1 ??
100 9.696e-08 5.638e-07 1.551s(0:0:1.551) #MSEtr MSE Time N90 can2c-single RAND=2 seed=2
100 1.512e-06 4.108e-06 1.593s(0:0:1.593) #MSEtr MSE Time N90 can2c-single RAND=2 seed=3
100 1.841e-07 3.123e-06 1.687s(0:0:1.687) #MSEtr MSE Time N90 can2c-single RAND=2 seed=4

100 2.221e-07 8.947e-07 1.593s(0:0:1.593) #MSEtr MSE Time N90 can2c-single RAND=0 seed=1
100 1.155e-05 7.015e-06 2.441s(0:0:2.441) #MSEtr MSE Time N90 can2c-single RAND=0 seed=2
100 7.350e-06 1.131e-05 1.791s(0:0:1.791) #MSEtr MSE Time N90 can2c-single RAND=0 seed=3

100 5.363e-07 2.931e-06 1.689s(0:0:1.689) #MSEtr MSE Time N90 can2c-single RAND=1 seed=1
100 4.987e-07 5.419e-07 1.514s(0:0:1.514) #MSEtr MSE Time N90 can2c-single RAND=1 seed=2
100 1.814e-05 1.971e-05 1.452s(0:0:1.452) #MSEtr MSE Time N90 can2c-single RAND=1 seed=3

100 3.287e-06 9.201e-06 1.701s(0:0:1.701) #MSEtr MSE Time N90 can2c-single RAND=3 seed=1
100 2.315e-07 1.179e-06 1.828s(0:0:1.828) #MSEtr MSE Time N90 can2c-single RAND=3 seed=2
100 1.690e-05 2.816e-05 1.509s(0:0:1.509) #MSEtr MSE Time N90 can2c-single RAND=3 seed=3
100 3.871e-07 1.418e-06 1.511s(0:0:1.511) #MSEtr MSE Time N90 can2c-single RAND=3 seed=4

#(2) bagging CAN2C
export T=100 N=60 seed=1 n_bags=100 alpha=2.2;../sh/can2cbagtest.sh #bagging for Geo1d_200_50_10

100 7.837088e-08 1.446343e-06  289.481s(0:4:49.481) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=1
100 9.043513e-08 1.206428e-06  290.433s(0:4:50.433) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=2
100 1.450179e-07 3.445693e-06  290.469s(0:4:50.469) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=3
100 9.714625e-08 1.533174e-06  289.892s(0:4:49.892) #MSEtr MSE Time N60 b100 a2.2 RAND=2 seed=4

100 6.289147e-08 1.308560e-06  305.58s(0:5:5.58) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=1
100 1.802001e-07 1.781859e-06  303.15s(0:5:3.15) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=2
100 7.597515e-08 1.189584e-06  286.203s(0:4:46.203) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=3
100 9.125783e-08 1.370732e-06  295.589s(0:4:55.589) #MSEtr MSE Time N60 b100 a2.2 RAND=3 seed=4
100 9.709223e-08 1.319138e-06  298.83s(0:4:58.83) #MSEtr MSE Time N60 b100 a2.2  RAND=3 seed=5

100 6.349685e-08 1.112893e-06  329.2s(0:5:29.2) #MSEtr MSE Time N60 b100 a2.2  seed=2 Geo1d_200_50_10    seed=1
100 8.184378e-08 1.213374e-06  314.292s(0:5:14.292) #MSEtr MSE Time N60 b100 a2.2 seed=1 Geo1d_200_50_10 seed=2

#####################
20191023
#####################
(1) single CAN2の実行例：
export T=100 N=90 seed=1 fntrain=../tmp/train.csv fntest=../tmp/test.csv;../sh/can2csingletest.sh #geo1d single (1-1)
または
export T=100 N=90 seed=1 fntrain=../tmp/train.csv fntest=../tmp/test.csv n_bags=1 alpha=1; ../sh/can2cbagtest.sh #geo1d single (1-2)
(2)bagging CAN2の実行例
export T=100 N=60 seed=1 n_bags=100 alpha=2.2;../sh/can2cbagtest.sh #bagging for Geo1d_50_50_10
100 5.067914e-06 2.147857e-04  #MSEtr MSE N70 b100 a2.2 0:3:7.60  #bagging for Geo1d_50_50_10 #define RAND ZMTRAND
100 6.952028e-06 1.747436e-04  #MSEtr MSE N70 b100 a2.2 0:3:10.342 #bagging for Geo1d_50_50_10 #define RAND DRAND48
100 5.519075e-06 1.664098e-04  #MSEtr MSE N70 b100 a2.2 0:3:15.44 #bagging for Geo1d_50_50_10 #define RAND RANDOM
100 5.519075e-06 1.664098e-04  #MSEtr MSE N70 b100 a2.2 0:3:22.521 #bagging for Geo1d_50_50_10 #define RAND MYRAND

100 6.952028e-06 1.747436e-04  #MSEtr MSE N70 b100 a2.2 0:3:10.342 #bagging for Geo1d_50_50_10 #define RAND DRAND48
100 5.555562e-06 2.188716e-04  #MSEtr MSE N60 b100 a2.2 0:2:44.650 #bagging for Geo1d_50_50_10 #define RAND DRAND48
100 4.589446e-06 2.120313e-04  #MSEtr MSE N80 b100 a2.2 0:3:19.966 #bagging for Geo1d_50_50_10 #define RAND DRAND48

100 5.505384e-06 1.907118e-04  #MSEtr MSE N60 b100 a2.2 0:3:28.318 #bagging for Geo1d_50_50_10 #define RAND RANDOM

#注意１：sh/can2singletest.sh は純粋に訓練データをtrain.csv、テストデータをtest.csvで行う。
　　　　訓練データのMSEtrは、各ユニットの誤差の和を用いていて、
　　　　各ユニットが、データを補充している場合は正確な訓練誤差ではない。
       sim.cの5222行(20191012のこめんとがある行のこめんとを外せばよい？
#注意２：sh/can2test.shは，訓練データをtrain.csv、
       テストデータをtrain.csvとtest.csvを合わせたtrain-test.csvを
　　　　使い、各エポックで表示するMSEはtrain-test.csvに対するものである。
       但し、最後に表示するのMSEtrとMSEは訓練誤差とテストデータtest.csvに
　　　　対するテスト誤差を計算して表示する．



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
