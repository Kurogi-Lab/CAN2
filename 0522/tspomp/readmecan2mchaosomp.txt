###################
# Ensamble prediction using LOOCV Predictable Horizon
#
# (0) execute 'make' first
#
################### 
20200622
###################
dsingle=/home/kuro/sotu/2019/can2m/tsp
dbagging=/home/kuro/sotu/2019/can2m/tspomp

# test again for bagging in can2m/tspomp/
cd $dbagging
export L=2 N=60 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=70 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=80 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=90 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=100 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=110 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=50 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=40 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=N:40 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m/tsp

###result ofr bagging
cat > ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat <<EOF
40  309.8 202.7 200.3 198.9 0.9977 0.99872 0.99937 32 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N40ns50m2b20a2.3 (ncmax)
50  343.9 206.5 208.7 211.1 0.99807 0.99875 0.99948 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N50ns50m2b20a2.3 (ncmax)
60  338.0 210.2 210.2 207.0 0.99743 0.99849 0.99912 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N60ns50m2b20a2.3 (ncmax)
70  341.7 198.1 207.3 206.3 0.99742 0.99836 0.99932 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N70ns50m2b20a2.3 (ncmax)
80  333.0 197.0 197.0 196.8 0.9972  0.99813 0.99909 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N80ns50m2b20a2.3 (ncmax)
90  334.9 186.2 186.2 192.1 0.99733 0.99855 0.99922 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N90ns50m2b20a2.3 (ncmax)
100 314.2 202.0 199.9 198.3 0.99729 0.99856 0.99922 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N100ns50m2b20a2.3 (ncmax)
110 331.5 195.8 184.4 189.5 0.99774 0.99854 0.99929 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N110ns50m2b20a2.3 (ncmax)
EOF

# 
cd $dsingle
export L=2 N=N:50 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m/tsp
###result ofr single
cat > ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat <<EOF
40  282.3 171.2 174.7 180.2 0.99488 0.99765 0.99882 34 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:50ns50  (ncmax)
50  311.6 191.1 191.0 188.8 0.9943 0.99722 0.99831 30  #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:50ns50  H0-2ndmax
60  314.9 183.9 183.1 190.2 0.99433 0.99735 0.99829 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:60ns50
70  305.7 190.6 187.4 190.9 0.99503 0.99746 0.9988 30  #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:70ns50  L2-2ndmax
80  328.3 193.4 191.3 198.8 0.99559 0.99749 0.99863 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:80ns50  Homax  H2-2ndmax
90  332.8 191.4 186.6 207.2 0.99596 0.9977 0.99893 30  #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:90ns50   Entropy L2max H2max
100 321.2 185.2 186.4 180.8 0.99602 0.99745 0.99855 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:100ns50 (ncmax) Entropy L0max
110 325.6 184.5 186.8 187.9 0.9959 0.99768 0.99855 30  #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:110ns50 (ncmax)
#120 318.0 179.9 182.6 181.3 0.99578 0.99727 0.99844 60 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:120ns50 (ncmax)
#200 314.6 177.5 175.4 171.6 0.99369 0.99689 0.99815 30 #mean Hgmax,Hgo0,1,2,E0,1,2: k10N:200ns50 (ncmax)
EOF
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 3:6 w p pt 6
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 4:7 w p pt 8
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 5:8 w p pt 10

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 3:6 w lp, "" using 5:8 w lp
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 3:6 w lp
#figs
fHgn=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N50ns50m2b20a2.3Hgn.dat 
fHgn=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:90ns50Hgn.dat

D=k10N70ns50m2b20a2.3
fHgn=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat
D=k10N:90ns50
fHgn=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:90ns50.dat
###
gnuplot
###(1)
gnuplot
plot [0:5500] "../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt" using 5:1 w l
unset key;set term tgif;set output "lorenz0-5500h1e-8p256T0.025.obj"
replot
set term x11;set key

###(2) Hg vs. N for single and bagging
set grid;set key
plot [][150:220] "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 1:5 w lp pt 6 t "5", "" using 1:4 w lp pt 8 t "4", "" using 1:3 w lp pt 10 t "3", "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 1:5 w lp pt 6 t "5", "" using 1:4 w lp pt 8 t "4", "" using 1:3 w lp pt 10 t "3"
set term tgif;set output "Hg-N.obj"
replot
set term x11;set key
###(3)
### Ent vs Hg for single and bagging
gnuplot
set grid;set key
plot [170:230]"../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 5:8 w lp pt 6 t "5", "" using 4:7 w lp pt 8 t "4", "" using 3:6 w lp pt 10 t "3", "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 5:8 w lp pt 6t "5", "" using 4:7 w lp pt 8 t "4", "" using 3:6 w lp pt 10 t "3"
set term tgif;set output "E-Hg.obj"
replot
set term x11;set key
###(4) Hg vs tp
gnuplot
set grid
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N50ns50m2b20a2.3Hgn.dat" using ($0*100+2000):4 w lp pt 6 t "b", "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:90ns50Hgn.dat" using ($0*100+2000):4 w lp pt 6 t "s"
set term tgif;set output "Hg-tp-L2.obj"
replot;set term x11;set key

gnuplot
set grid
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N50ns50m2b20a2.3Hgn.dat" using ($0*100+2000):2 w lp pt 6 t "b", "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:90ns50Hgn.dat" using ($0*100+2000):2 w lp pt 6 t "s"
set term tgif;set output "Hg-tp-L0.obj"
replot;set term x11;set key
##Hg=350 bag 
##Hg=260 single

D=k10N50ns50m2b20a2.3
TT=t0-2000:2400-2900
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/${TT}$D
python kmeans2_kuro.py -d1 $d1 -fnyp tspSth.dat -fnyg yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0 

hi-LOOCV@L2c1 with n43 min200.4 max266.1 mean252.8 median256.0 std13.9 best-iNshh(7,50,0,385,266*)  Entropy=1.000 D=k10N50ns50m2b20a2.3
hi-LOOCV@L2c3 with n40 min134.3 max207.0 mean182.0 median187.7 std20.0 best-iNshh(14,90,14,237,207*)  Entropy=0.998 D=k10N:90ns50



### Hg vs tp y-t
!gv ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:3900-4400k10N50ns50m2b20a2.3/y_L2.eps&
!gv ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:3900-4400k10N:90ns50/y_L2.eps&
#draw obtained y
D=k10N:90ns50
D=k10N50ns50m2b20a2.3
TT=t0-2000:2400-2900
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/${TT}$D
python kmeans2_kuro.py -d1 $d1 -fnyp tspSth.dat -fnyg yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0 
gv $d1/y_L0.eps&
gv $d1/y_L1.eps&
gv $d1/y_L2.eps&
###

export D=k10N:90ns50
export D=k10N50ns50m2b20a2.3
export TT=t0-2000:2400-2900
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/${TT}${D}
export iconip20figs=$d0/iconip20figs; mkdir -p $iconip20figs
for f in y_L0.eps y_L1.eps y_L2.eps hh_L0.eps hh_L1c0.eps hh_L1c1.eps hh_L2c0.eps hh_L2c1.eps hh_L2c2.eps hh_L2c3.eps ; do
ls -l ${d1}/${f}
cp ${d1}/${f} ${iconip20figs}/${TT}${D}${f}
done 
cp /home/kuro/sotu/2019/can2m/tsp/*.obj .

scp mesaho:/home/kuro/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/iconip20figs/* .


!gv ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:3900-4400k10N50ns50m2b20a2.3/hh_L2.eps&
!gv ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:3900-4400k10N:90ns50/hh_L2.eps&

scp mesaho:/home/kuro/sotu/2019/can2m/tsp/*.obj .
scp mesaho:/home/kuro/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4200-4700k10N:90ns50/y_L?.eps .

scp mesaho:/home/kuro/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:3900-4400k10N50ns50m2b20a2.3/hh_L2.eps .
scp mesaho:/home/kuro/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:3900-4400k10N:90ns50/hh_L2.eps .
scp mesaho:/home/kuro/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2400-2900k10N50ns50m2b20a2.3/hh_L2.eps .
scp mesaho:/home/kuro/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2400-2900k10N:90ns50/hh_L2.eps .

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 3:6 w lp pt 6, "" using 4:7 w lp pt 8, "" using 5:8 w lp pt 10
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 3:6 w lp pt 6, "" using 4:7 w lp pt 8, "" using 5:8 w lp pt 10

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 3:6 w p pt 6, "" using 4:7 w p pt 8, "" using 5:8 w p pt 10
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 3:6 w p pt 6, "" using 4:7 w p pt 8, "" using 5:8 w p pt 10


!gv ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4200-4700k10N70ns50m2b20a2.3/y_L2.eps
!gv ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4200-4700k10N70ns50m2b20a2.3/y_L2.eps

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 3:6 w p pt 7, "" using 4:7 w p pt 9, "" using 5:8 w p pt 11






#plot [][180:260] "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 1:3 w lp pt 10, "" using 1:4 w lp pt 8, "" using 1:5 w lp pt 6
#plot [][180:260] "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 1:3 w lp pt 11, "" using 1:4 w lp pt 9, "" using 1:5 w lp 7

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 1:5 w lp pt 6, "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 1:5 w lp pt 7

#plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 1:6 w p pt 7, "" using 1:7 w p pt 9, "" using 1:8 w p pt 11
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 1:6 w p pt 7, "" using 1:7 w p pt 9, "" using 1:8 w p pt 11

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 3:6 w p pt 7, "" using 4:7 w p pt 9, "" using 5:8 w p pt 11
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 3:6 w p pt 6, "" using 4:7 w p pt 8, "" using 5:8 w p pt 10
###2 ###1 Ent vs. Hg different L, N=90 N=70
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:90ns50Hgn.dat" using 2:5 w p pt 11, "" using 3:6 w p pt 9, "" using 4:7 w p pt 7
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using 2:5 w p pt 10, "" using 3:6 w p pt 8, "" using 4:7 w p pt 6

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:90ns50Hgn.dat" using ($0*100+2000):4 w lp pt 7 #single
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using ($0*100+2000):4 w lp pt 6 #single


#
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 3:6 w p pt 6
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 4:7 w p pt 8
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b20a2.3.dat" using 5:8 w p pt 10

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 3:6 w p pt 7
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 4:7 w p pt 9
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/HEns50b1.dat" using 5:8 w p pt 11

###2
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:90ns50Hgn.dat" using ($0*100+2000):4 w lp pt 7 #single
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using ($0*100+2000):4 w lp pt 6 #single
###3
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:90ns50Hgn.dat" using 2:5 w p pt 11, "" using 3:6 w p pt 9, "" using 4:7 w p pt 7
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using 2:5 w p pt 10, "" using 3:6 w p pt 8, "" using 4:7 w p pt 6

#
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using ($0*100+2000):4 w lp pt 6
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using ($0*100+2000):2 w lp pt 10, "" using ($0*100+2000):3 w lp pt 8, "" using ($0*100+2000):4 w lp pt 6
#4200 worst
#4900 best
#!gv ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4200-4700k10N70ns50m2b20a2.3/y_L2.eps
unset key
replot
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using 2:5 w p pt 10
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using 3:6 w p pt 8
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using 4:7 w p pt 6
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns50m2b20a2.3Hgn.dat" using 2:5 w p pt 10, "" using 3:6 w p pt 8, "" using 4:7 w p pt 6

../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4900-5400k10N70ns50m2b20a2.3

#mean Hgmax,Hgo0,1,2,E0,1,2: 370.9 228.7 225.7 222.8 0.99804 0.99874 0.99946 30 k10N50ns50m2b20a2.3 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 386.3 238.2 240.1 239.0 0.99742 0.99846 0.99917 30 k10N60ns50m2b20a2.3 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 409.2 249.4 259.3 258.7 0.99739 0.99836 0.99933 30 k10N70ns50m2b20a2.3 (ncmax) E0-Max H0max H2max
#mean Hgmax,Hgo0,1,2,E0,1,2: 379.5 211.6 208.5 206.0 0.99712 0.99814 0.99911 30 k10N80ns50m2b20a2.3 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 377.9 221.2 222.5 226.9 0.99725 0.99851 0.99921 30 k10N90ns50m2b20a2.3 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 372.3 227.8 228.2 226.1 0.99734 0.99855 0.99923 30 k10N100ns50m2b20a2.3 (ncmax)  E02ndMax
#mean Hgmax,Hgo0,1,2,E0,1,2: 377.9 221.2 222.5 226.9 0.99725 0.99851 0.99921 30 k10N110ns50m2b20a2.3 (ncmax)

#mean Hgmax,Hgo0,1,2,E0,1,2: 311.6 191.1 191.0 188.8 0.9943 0.99722 0.99831 30 k10N:50ns50  H0-2ndmax
#mean Hgmax,Hgo0,1,2,E0,1,2: 314.9 183.9 183.1 190.2 0.99433 0.99735 0.99829 30 k10N:60ns50
#mean Hgmax,Hgo0,1,2,E0,1,2: 305.7 190.6 187.4 190.9 0.99503 0.99746 0.9988 30 k10N:70ns50  L2-2ndmax
#mean Hgmax,Hgo0,1,2,E0,1,2: 328.3 193.4 191.3 198.8 0.99559 0.99749 0.99863 30 k10N:80ns50  Homax  H2-2ndmax
#mean Hgmax,Hgo0,1,2,E0,1,2: 332.8 191.4 186.6 207.2 0.99596 0.9977 0.99893 30 k10N:90ns50   Entropy L2max H2max
#mean Hgmax,Hgo0,1,2,E0,1,2: 321.2 185.2 186.4 180.8 0.99602 0.99745 0.99855 30 k10N:100ns50 (ncmax) Entropy L0max
#mean Hgmax,Hgo0,1,2,E0,1,2: 325.6 184.5 186.8 187.9 0.9959 0.99768 0.99855 30 k10N:110ns50 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 318.0 179.9 182.6 181.3 0.99578 0.99727 0.99844 60 k10N:120ns50 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 314.6 177.5 175.4 171.6 0.99369 0.99689 0.99815 30 k10N:200ns50 (ncmax)
################### 
20200615
###################
for f in am.c am.h can2.c ensrs.c meanpred.c my_function.c my_function.h my_misc.c my_misc.h my_plinn.c my_plinn.h pred2y_ts.c randoms.c randoms.h share sim.c sim.h; do
rm $f
ln -s ../can2comp/$f .
done
###
###
20200618 #executing can2m/tsp
export L=2 N=N:200 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m/tsp
###
export L=2 N=60 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp 
####



export L=2 N=5-300:5 ns=1 mbam=2:20:1.0:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m/tspomp
export L=2 N=60 ns=20 mbam=2:20:2.3:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m/tspomp ************
export L=2 N=50 ns=20 mbam=2:20:2.3:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m/tspomp
export L=2 N=80 ns=20 mbam=2:20:2.3:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp
export L=2 N=70 ns=20 mbam=2:20:2.3:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #** can2m1/tspomp
###check 20200617
320 166 166 166 0.99684 0.99909 0.99779 #Hgmax,(ncmax27)HgoL0,1,2,Entr0,1,2 #t0-2000:2000-2500k10N60ns50m2b20a2.3
320 166 166 166 0.99684 0.99909 0.99779 #Hgmax,(Entropymax0.99779)HgoL0,1,2,ncmaxL 27 #t0-2000:2000-2500k10N60ns50m2b20a2.3
###check 20200617
430 280 280 370 0.99262 0.99597 0.99938 #Hgmax,(Entropymax0.99938)HgoL0,1,2,ncmaxL 46 #t0-2000:2000-2500k10N80ns50m2b20a2.3
430 280 280 370 0.99262 0.99597 0.99938 #Hgmax,(ncmax46)HgoL0,1,2,Entr0,1,2 #t0-2000:2000-2500k10N80ns50m2b20a2.3
###
341 313 313 313 0.99447 0.99781 0.99923 #Hgmax,(Entropymax0.99923)HgoL0,1,2,ncmaxL 26 #t0-2000:2000-2500k10N70ns50m2b20a2.3
341 313 313 313 0.99447 0.99781 0.99923 #Hgmax,(ncmax26)HgoL0,1,2,Entr0,1,2 #t0-2000:2000-2500k10N70ns50m2b20a2.3
#20200618executing
export L=2 N=70 ns=50 mbam=2:20:2.3:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp 
export L=2 N=50 ns=50 mbam=2:20:2.3:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp 
export L=2 N=80 ns=50 mbam=2:20:2.3:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp 
export L=2 N=60 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp 
export L=2 N=110 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp 
export L=2 N=100 ns=50 k=10 m=2 b=1 a=1.0 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp 
export L=2 N=50 ns=50 k=10 m=2 b=20 a=2.3 mc=0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh& #can2m1/tspomp 
#
###
grep "#t0-" ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/cmd-io-sum.dat|grep ncmax
###################(2)
#for D in k10N50ns20m2b20a2.3 k10N60ns20m2b20a2.3 k10N70ns20m2b20a2.3 k10N80ns20m2b20a2.3 k10N:50ns50 k10N:60ns50 k10N:70ns50 k10N:80ns50 k10N:90ns50 k10N:100ns50; do
#
source init.sh
export DS="k10N50ns20m2b20a2.3 k10N60ns20m2b20a2.3 k10N70ns20m2b20a2.3 k10N80ns20m2b20a2.3 k10N:50ns50 k10N:60ns50 k10N:70ns50 k10N:80ns50 k10N:90ns50 k10N:100ns50"
export DS=k10N70ns50m2b20a2.3
export DS=k10N50ns50m2b20a2.3
export DS=k10N80ns50m2b20a2.3
export DS=k10N60ns50m2b20a2.3
export DS=k10N:110ns50
export DS=k10N:120ns50
export DS=k10N:200ns50
###
for D in $DS; do
ls -l $d0 | grep "t0-2000:3500-4000${D}"
cat /dev/null>tmp/tmp.out
export L=2 D
for tp0 in `seq 2000 100 4900`; do
python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D} -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0 >>tmp/tmp.out
done #for tp0
export fHg=$d0/${D}Hg.dat 
grep "#t0-" tmp/tmp.out > $fHg
echo "#result saved in cat $fHg"
done #for D
####(3)
for D in $DS; do
export D fHg=$d0/${D}Hg.dat 
#export fHgo=$d0/${D}HgE.dat key="(Entro" 
export fHgo=$d0/${D}Hgn.dat key="(ncmax" 
grep $key $fHg > tmp/tmp1.dat
cat tmp/tmp1.dat |awk 'BEGIN{D=ENVIRON["D"];key=ENVIRON["key"];hg=hoL0=hoL1=hoL2=E0=E1=E2=n=0}{n++;hg+=$1;hoL0+=$2;hoL1+=$3;hoL2+=$4;E0+=$5;E1+=$6;E2+=$7;}END{printf("#mean Hgmax,Hgo0,1,2,E0,1,2: %.1f %.1f %.1f %.1f %.5g %.5g %.5g %d %s %s)\n",hg/n,hoL0/n,hoL1/n,hoL2/n,E0/n,E1/n,E2/n,n,D,key);}'> $fHgo
cat tmp/tmp1.dat >> $fHgo
done
###############(4)
for D in $DS; do
head -1 $d0/${D}Hgn.dat
#head -1 $d0/${D}HgE.dat
done
##########(5) for files check
for D in $DS; do
ls -l $d0 | grep "t0-2000:3500-4000${D}"
cat /dev/null>tmp/tmp.out
export L=2
for tp0 in `seq 2000 100 4900`; do
echo "d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D}"
ls ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D}
done #for tp0
done #for D
#
#result
#mean Hgmax,Hgo0,1,2,E0,1,2: 325.6 184.5 186.8 187.9 0.9959 0.99768 0.99855 30 k10N:110ns50 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 382.2 233.7 235.5 234.4 0.99738 0.9985 0.99909 32 k10N60ns50m2b20a2.3 (ncmax)  E0-2ndMax H0-2ndmax 
#mean Hgmax,Hgo0,1,2,E0,1,2: 409.2 249.4 259.3 258.7 0.99739 0.99836 0.99933 30 k10N70ns50m2b20a2.3 (ncmax) E0-Max H0max H2max
#mean Hgmax,Hgo0,1,2,E0,1,2: 379.5 211.6 208.5 206.0 0.99712 0.99814 0.99911 30 k10N80ns50m2b20a2.3 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 377.9 221.2 222.5 226.9 0.99725 0.99851 0.99921 30 k10N90ns50m2b20a2.3 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 372.3 227.8 228.2 226.1 0.99734 0.99855 0.99923 30 k10N100ns50m2b20a2.3 (ncmax)  E02ndMax
#mean Hgmax,Hgo0,1,2,E0,1,2: 377.9 221.2 222.5 226.9 0.99725 0.99851 0.99921 30 k10N110ns50m2b20a2.3 (ncmax)

#mean Hgmax,Hgo0,1,2,E0,1,2: 311.6 191.1 191.0 188.8 0.9943 0.99722 0.99831 30 k10N:50ns50  H0-2ndmax
#mean Hgmax,Hgo0,1,2,E0,1,2: 314.9 183.9 183.1 190.2 0.99433 0.99735 0.99829 30 k10N:60ns50
#mean Hgmax,Hgo0,1,2,E0,1,2: 305.7 190.6 187.4 190.9 0.99503 0.99746 0.9988 30 k10N:70ns50  L2-2ndmax
#mean Hgmax,Hgo0,1,2,E0,1,2: 328.3 193.4 191.3 198.8 0.99559 0.99749 0.99863 30 k10N:80ns50  Homax  H2-2ndmax
#mean Hgmax,Hgo0,1,2,E0,1,2: 332.8 191.4 186.6 207.2 0.99596 0.9977 0.99893 30 k10N:90ns50   Entropy L2max H2max
#mean Hgmax,Hgo0,1,2,E0,1,2: 321.2 185.2 186.4 180.8 0.99602 0.99745 0.99855 30 k10N:100ns50 (ncmax) Entropy L0max
#mean Hgmax,Hgo0,1,2,E0,1,2: 314.6 177.5 175.4 171.6 0.99369 0.99689 0.99815 30 k10N:200ns50 (ncmax)

#mean Hgmax,Hgo0,1,2,E0,1,2: 280.1 163.7 163.6 161.3 0.99369 0.99635 0.99801 30 k10N100ns50m2b1a1.0 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 279.7 172.3 167.8 164.2 0.99341 0.99659 0.99779 30 k10N200ns50m2b1a1.0 (ncmax)
#mean Hgmax,Hgo0,1,2,E0,1,2: 289.0 156.9 163.1 155.5 0.99474 0.99667 0.99785 30 k10N300ns50m2b1a1.0 (ncmax)


#mean Hgmax,Hgo0,1,2,E0,1,2: 346.8 223.9 219.1 216.3 0.99721 0.99859 0.99909 30 k10N50ns20m2b20a2.3 Entropy-max
#mean Hgmax,Hgo0,1,2,E0,1,2: 345.4 238.3 235.3 231.7 0.99642 0.99841 0.99881 30 k10N60ns20m2b20a2.3
#mean Hgmax,Hgo0,1,2,E0,1,2: 369.8 263.9 265.4 263.1 0.99632 0.99837 0.9988 30 k10N70ns20m2b20a2.3  ***
#mean Hgmax,Hgo0,1,2,E0,1,2: 326.9 214.2 211.1 208.6 0.99613 0.99749 0.99816 30 k10N80ns20m2b20a2.3
#

#########
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 346.8 223.9 233.9 212.5 0.99721 0.99859 0.99909 30 k10N50ns20m2b20a2.3 E2max
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 345.4 238.3 229.5 225.8 0.99642 0.99841 0.99878 30 k10N60ns20m2b20a2.3
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 369.8 263.9 268.3 244.4 0.99632 0.99837 0.9988 30 k10N70ns20m2b20a2.3 
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 308.4 218.8 211.5 196.9 0.99626 0.99791 0.99797 22 k10N80ns20m2b20a2.3

#E#mean Hgmax,Hgo0,1,2,E0,1,2: 311.6 191.1 191.0 188.4 0.9943 0.9972 0.9983 30 k10N:50ns50
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 314.9 183.9 188.8 186.1 0.99433 0.99732 0.99836 30 k10N:60ns50
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 305.7 190.6 187.4 173.3 0.99503 0.99746 0.99879 30 k10N:70ns50
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 328.3 193.4 203.9 195.8 0.99559 0.99755 0.99863 30 k10N:80ns50
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 332.8 191.4 186.4 171.6 0.99596 0.99767 0.99893 30 k10N:90ns50 *
#E#mean Hgmax,Hgo0,1,2,E0,1,2: 321.2 185.2 199.2 183.6 0.99602 0.99753 0.99857 30 k10N:100ns50


gnuplot
plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N50ns20m2b20a2.3Hgo.dat" using ($0*100+2000):2 w lp, "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N60ns20m2b20a2.3Hgo.dat" using ($0*100+2000):2 w lp, "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N70ns20m2b20a2.3Hgo.dat" using ($0*100+2000):2 w lp, "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:60ns50Hgo.dat" using ($0*100+2000):2 w lp, "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:80ns50Hgo.dat" using ($0*100+2000):2 w lp

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N:50ns50Hgo.dat" using ($0*100+2000):1 w lp

plot "../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/k10N60ns20m2b20a2.3Hgo.dat" using ($0*100+2000):1 w lp, "" using ($0*100+2000):4 w lp

gv ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2000-2500k10N60ns20m2b20a2.3/hh_L0.eps&
gv ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N60ns20m2b20a2.3/hh_L0.eps&
gv ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2200-2700k10N60ns20m2b20a2.3/hh_L0.eps&
gv ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2300-2800k10N60ns20m2b20a2.3/hh_L0.eps&
gv ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2400-2900k10N60ns20m2b20a2.3/hh_L0.eps&
gv ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-3000:3300-2800k10N60ns20m2b20a2.3/hh_L0.eps&

###export L=2 N=60 ns=20 mbam=2:1:1.0:0 TP0S=2000;loocv-bat.sh #single CAN2
###
###export L=2 N=5-300:5 ns=1 mbam=2:20:1.0:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh&
###export L=2 N=60 ns=20 mbam=2:20:0.7:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh&
###export L=2 N=60 ns=50 mbam=2:20:0.7:0 TP0S=3500;loocv-bat.sh
###
###export L=2 N=60 ns=20 mbam=2:20:1.0:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh&
###export L=2 N=50-100:10 ns=20 mbam=2:20:1.0:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh&
###grep "#t0-" nohup.out|grep ncmax
###export L=2 N=60 ns=50 mbam=2:20:1.0:0 TP0S=4200;loocv-bat.sh
###
#summary
#mean Hgmax,Hgo0,1,2,E0,1,2:346.8 223.9 219.1 216.3 0.99721 0.99859 0.99859 30 k10N50ns20m2b20a2.3
#mean Hgmax,Hgo0,1,2,E0,1,2:345.4 238.3 235.3 234.6 0.99642 0.99841 0.99841 30 k10N60ns20m2b20a2.3 ***
#mean Hgmax,Hgo0,1,2,E0,1,2:357.6 251.1 250.4 246.8 0.99637 0.99839 0.99839 60 k10N70ns20m2b20a2.3 ***max mean max ent
#mean Hgmax,Hgo0,1,2,E0,1,2:326.9 214.2 211.1 216.5 0.99613 0.9975 0.9975 30 k10N80ns20m2b20a2.3 
###
#mean Hgmax,HgoL1,...:296.6 151.4 151.4 154.4 30 k10N:5-300:5ns1 
#mean Hgmax,HgoL1,...:101.8 82.2 81.8 80.9 30 k10N5-300:5ns1m2b20a1.0

#mean Hgmax,HgoL1,...:316.8 192.0 196.6 198.9 30 k10N50-100:10ns5omp
#mean Hgmax,HgoL1,...:309.6 213.3 210.3 204.9 30 k10N60ns20m2b20a1.0
#mean Hgmax,HgoL1,...:306.2 207.5 211.6 208.5 30 k10N60ns20m2b20a0.7
#mean Hgmax,HgoL1,...:345.4 238.3 235.3 231.7 30 k10N60ns20m2b20a2.3 *************
#mean Hgmax,HgoL1,...:369.8 263.9 265.4 261.1 30 k10N70ns20m2b20a2.3 small at 4200 big variance?
#mean Hgmax,HgoL1,...:346.8 223.9 219.1 218.3 30 k10N50ns20m2b20a2.3 **bad at 4200
#mean Hgmax,HgoL1,...:326.9 214.2 212.4 200.6 30 k10N80ns20m2b20a2.3

#mean Hgmax,HgoL1,...:279.1 178.1 181.5 183.2 30 k10N:50ns17   2littleL0L1L2
#mean Hgmax,HgoL1,...:281.4 198.7 195.6 190.2 30 k10N:60ns17   2little L0 3littleL2
#mean Hgmax,HgoL1,...:261.1 185.1 192.9 183.8 30 k10N:70ns17  2littleL0L2
#mean Hgmax,HgoL1,...:284.9 191.6 202.2 191.4 30 k10N:80ns17  Biggest L1 2littleL2
#mean Hgmax,HgoL1,...:287.2 186.2 199.8 202.9 30 k10N:90ns17  Biggest L2
#mean Hgmax,HgoL1,...:290.2 200.3 192.8 188.7 30 k10N:100ns17 Biggest Hg L0
#mean Hgmax,HgoL1,...:281.4 198.7 190.0 192.0 30 k10N:60ns17 good but small@#t0-2000:3300-3800k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 302  74 74 71  
#mean Hgmax,HgoL1,...:352.4 214.2 214.4 210.4 30 k10N:50-100:10ns17 best Hg,L0,L1,L2 ***bad at 3300 4200
#mean Hgmax,HgoL1,...:331.9 197.7 198.2 189.7 30 k10N:50-80:10ns17
#mean Hgmax,HgoL1,...:347.1 185.2 185.2 194.0 30 k10N:50-200:30ns17

##use this for iconip2020 ??
#mean Hgmax,HgoL1,...:311.6 191.1 191.0 185.9 30 k10N:50ns50 L1
#mean Hgmax,HgoL1,...:314.9 183.9 183.1 198.0 30 k10N:60ns50 2ndBest L2-withAllBiggerthan100 ****
#mean Hgmax,HgoL1,...:305.7 190.6 187.4 190.9 30 k10N:70ns50 
#mean Hgmax,HgoL1,...:328.3 193.4 193.2 196.8 30 k10N:80ns50 Biggest L0,L1
#mean Hgmax,HgoL1,...:332.8 191.4 186.6 198.7 30 k10N:90ns50 Biggest Hg L2-butSmallValues@4-tp0's
#mean Hgmax,HgoL1,...:318.2 182.8 183.1 176.4 29 k10N:100ns50
#mean Hgmax,HgoL1,...:369.5 188.8 188.8 190.1 30 k10N:50-80:10ns50 BiggestHg 3smallerthan100

#mean Hgmax,HgoL1,...:296.6 151.4 151.4 154.4 30 k10N:5-300:5ns1 
export L=2 k=10 N=N:50-100:10 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m1

#############
#mean Hgmax,Hgo0,1,2,E0,1,2:326.9 214.2 211.1 216.5 0.99613 0.9975 0.9975 30 k10N80ns20m2b20a2.3
kuro@klab1:~/sotu/2019/can2m/tspomp$ #t0-2000:2000-2500k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 338  161 161 280 0.98906 0.99785 0.99831
#t0-2000:2100-2600k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 441  99 99 279 0.99581 0.98763 0.99918
#t0-2000:2200-2700k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 407  199 199 222 0.99766 0.99885 0.99933
#t0-2000:2300-2800k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 274  213 213 213 0.99051 0.9925 0.99695
#t0-2000:2400-2900k10N80ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 445  351 351 351 0.99849 0.99945 0.99935
#t0-2000:2500-3000k10N80ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 433  283 283 281 0.99913 0.99952 0.99974
#t0-2000:2600-3100k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 358  156 156 156 0.99806 0.99736 0.99988
#t0-2000:2700-3200k10N80ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 328  151 151 151 0.99757 0.99769 0.9979
#t0-2000:2800-3300k10N80ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 214  213 213 213 0.99769 0.9996 0.99954
#t0-2000:2900-3400k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 425  331 331 331 0.99813 0.99858 0.99977
#t0-2000:3000-3500k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 299  240 240 240 0.99895 0.99811 0.99972
#t0-2000:3100-3600k10N80ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 397  167 167 168 0.99491 0.99807 0.99556
#t0-2000:3200-3700k10N80ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 122  109 109 110 0.99613 0.99959 0.99964
#t0-2000:3300-3800k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 257  77 75 75 0.99008 0.99472 0.99507
#t0-2000:3400-3900k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 377  311 311 314 0.99648 0.9987 0.99568
#t0-2000:3500-4000k10N80ns20m2b20a2.3 #Hgmax,(ncmax6)HgoL0,1,2,Entr0,1,2: 286  282 282 282 0.99764 0.99639 0.9999
#t0-2000:3600-4100k10N80ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 360  241 241 241 0.99936 0.99957 0.99947
#t0-2000:3700-4200k10N80ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 231  136 136 136 0.99792 0.99883 0.99818
#t0-2000:3800-4300k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 249  163 163 163 0.99618 0.99762 0.99975
#t0-2000:3900-4400k10N80ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 327  268 268 268 0.99539 0.99876 0.99905
#t0-2000:4000-4500k10N80ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,1,2,Entr0,1,2: 285  196 196 197 0.98769 0.99837 0.99912
#t0-2000:4100-4600k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 345  310 218 310 0.99954 0.99922 0.99972
#t0-2000:4200-4700k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 362  327 327 106 0.99213 0.99421 0.99668
#t0-2000:4300-4800k10N80ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 373  287 287 251 0.99867 0.99976 0.99987
#t0-2000:4400-4900k10N80ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 432  276 276 276 0.99834 0.99945 0.99921
#t0-2000:4500-5000k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 287  176 176 176 0.99311 0.99827 0.99854
#t0-2000:4600-5100k10N80ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 225  166 166 166 0.99858 0.99869 0.99829
#t0-2000:4700-5200k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 346  188 188 188 0.99711 0.99814 0.99929
#t0-2000:4800-5300k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 324  238 238 238 0.99859 0.99932 0.99881
#t0-2000:4900-5400k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 261  112 112 112 0.995 0.99008 0.98631

#mean Hgmax,Hgo0,1,2,E0,1,2:346.8 223.9 219.1 216.3 0.99721 0.99859 0.99859 30 k10N50ns20m2b20a2.3
#t0-2000:2000-2500k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 491  166 166 166 0.9993 0.99956 0.99875
#t0-2000:2100-2600k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 345  265 265 265 0.99692 0.99818 0.99882
#t0-2000:2200-2700k10N50ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 346  225 225 225 0.99942 0.99964 0.99958
#t0-2000:2300-2800k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 306  245 245 184 0.99893 0.99966 0.99969
#t0-2000:2400-2900k10N50ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 353  245 245 245 0.99326 0.99917 0.99887
#t0-2000:2500-3000k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 315  227 227 227 0.99917 0.99929 0.99967
#t0-2000:2600-3100k10N50ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 332  242 242 242 0.99851 0.99924 0.9995
#t0-2000:2700-3200k10N50ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 270  206 206 206 0.99648 0.99811 0.99921
#t0-2000:2800-3300k10N50ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 389  349 349 349 0.99806 0.99825 0.99837
#t0-2000:2900-3400k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 312  281 281 281 0.99933 0.99972 0.99978
#t0-2000:3000-3500k10N50ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,1,2,Entr0,1,2: 329  239 239 239 0.99642 0.99732 0.9983
#t0-2000:3100-3600k10N50ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 289  289 144 144 0.99876 0.99869 0.99963
#t0-2000:3200-3700k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 496  108 108 108 0.99615 0.99851 0.99928
#t0-2000:3300-3800k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 334  242 242 242 0.99417 0.99877 0.99977
#t0-2000:3400-3900k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 288  174 174 174 0.99711 0.99646 0.99753
#t0-2000:3500-4000k10N50ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 291  251 251 251 0.99245 0.99666 0.99797
#t0-2000:3600-4100k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 360  283 283 283 0.99884 0.99901 0.99945
#t0-2000:3700-4200k10N50ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 327  174 174 174 0.99716 0.99889 0.99912
#t0-2000:3800-4300k10N50ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 394  164 164 164 0.99896 0.99737 0.99939
#t0-2000:3900-4400k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 364  131 130 131 0.99562 0.9984 0.99701
#t0-2000:4000-4500k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 415  327 327 327 0.99876 0.9997 0.99952
#t0-2000:4100-4600k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 371  250 250 250 0.99901 0.99899 0.99888
#t0-2000:4200-4700k10N50ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 267  98 98 98 0.99045 0.99726 0.99804
#t0-2000:4300-4800k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 433  198 198 198 0.99906 0.99907 0.99911
#t0-2000:4400-4900k10N50ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 306  158 158 158 0.99806 0.99917 0.99905
#t0-2000:4500-5000k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 265  234 234 234 0.99898 0.99967 0.99964
#t0-2000:4600-5100k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 231  199 199 199 0.99893 0.99964 0.99939
#t0-2000:4700-5200k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 341  218 218 218 0.99777 0.99982 0.99959
#t0-2000:4800-5300k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 390  292 292 269 0.99847 0.99907 0.99982
#t0-2000:4900-5400k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 454  238 238 238 0.99178 0.99451 0.99988

##############
#mean Hgmax,Hgo0,1,2,E0,1,2:345.4 238.3 235.3 234.6 0.99642 0.99841 0.99841 30 k10N60ns20m2b20a2.3
#t0-2000:2000-2500k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 309  160 160 160 0.99145 0.99924 0.99845
#t0-2000:2100-2600k10N60ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 327  236 236 236 0.99239 0.99604 0.99708
#t0-2000:2200-2700k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 277  277 277 195 0.99823 0.99981 0.99972
#t0-2000:2300-2800k10N60ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 364  185 184 184 0.99608 0.99852 0.99915
#t0-2000:2400-2900k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 444  231 231 231 0.9922 0.99941 0.99928
#t0-2000:2500-3000k10N60ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 373  313 313 320 0.99972 0.99996 0.99999
#t0-2000:2600-3100k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 417  157 157 157 0.99834 0.99907 0.99878
#t0-2000:2700-3200k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 300  235 235 235 0.99849 0.99877 0.99883
#t0-2000:2800-3300k10N60ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 319  227 227 259 0.99841 0.99941 0.99997
#t0-2000:2900-3400k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 336  335 335 335 0.99904 0.99903 0.99916
#t0-2000:3000-3500k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 303  237 237 237 0.99648 0.99862 0.99873
#t0-2000:3100-3600k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 263  142 142 263 0.99239 0.9968 0.99405
#t0-2000:3200-3700k10N60ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 434  221 221 190 0.99596 0.99878 0.99976
#t0-2000:3300-3800k10N60ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 389  210 210 210 0.996 0.99823 0.99967
#t0-2000:3400-3900k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 291  184 184 184 0.99611 0.99583 0.99643
#t0-2000:3500-4000k10N60ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 394  280 280 210 0.99598 0.99833 0.99989
#t0-2000:3600-4100k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 450  240 240 240 0.99909 0.99964 0.99945
#t0-2000:3700-4200k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 264  198 198 198 0.99728 0.99857 0.99878
#t0-2000:3800-4300k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 245  218 219 219 0.99559 0.99893 0.99838
#t0-2000:3900-4400k10N60ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 355  326 237 237 0.99903 0.99975 0.99986
#t0-2000:4000-4500k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 318  200 200 200 0.99391 0.99964 0.99981
#t0-2000:4100-4600k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 322  292 292 292 0.99933 0.99894 0.99931
#t0-2000:4200-4700k10N60ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 385  237 237 237 0.99093 0.9971 0.99795
#t0-2000:4300-4800k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 467  282 282 282 0.99823 0.99905 0.9996
#t0-2000:4400-4900k10N60ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 331  302 302 302 0.99886 0.99828 0.998
#t0-2000:4500-5000k10N60ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,1,2,Entr0,1,2: 252  215 215 215 0.99134 0.99686 0.99717
#t0-2000:4600-5100k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 265  260 260 260 0.9986 0.99948 0.99858
#t0-2000:4700-5200k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 399  249 249 249 0.99836 0.99896 0.99957
#t0-2000:4800-5300k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 498  235 235 235 0.99816 0.99929 0.99879
#t0-2000:4900-5400k10N60ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 271  265 265 265 0.99652 0.99205 0.99735
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=E0=E1=E2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;E0+=$7;E1+=$8;E2+=$8;}END{printf("#mean Hgmax,Hgo0,1,2,E0,1,2:%.1f %.1f %.1f %.1f %.5g %.5g %.5g %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,E0/n,E1/n,E2/n,n);}'
echo $D

#mean Hgmax,Hgo0,1,2,E0,1,2:357.6 251.1 250.4 246.8 0.99637 0.99839 0.99839 60 k10N70ns20m2b20a2.3
#t0-2000:2000-2500k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 309  160 160 160 0.99145 0.99924 0.99845
#t0-2000:2100-2600k10N60ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 327  236 236 236 0.99239 0.99604 0.99708
#t0-2000:2200-2700k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 277  277 277 195 0.99823 0.99981 0.99972
#t0-2000:2300-2800k10N60ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 364  185 184 184 0.99608 0.99852 0.99915
#t0-2000:2400-2900k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 444  231 231 231 0.9922 0.99941 0.99928
#t0-2000:2500-3000k10N60ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 373  313 313 320 0.99972 0.99996 0.99999
#t0-2000:2600-3100k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 417  157 157 157 0.99834 0.99907 0.99878
#t0-2000:2700-3200k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 300  235 235 235 0.99849 0.99877 0.99883
#t0-2000:2800-3300k10N60ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 319  227 227 259 0.99841 0.99941 0.99997
#t0-2000:2900-3400k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 336  335 335 335 0.99904 0.99903 0.99916
#t0-2000:3000-3500k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 303  237 237 237 0.99648 0.99862 0.99873
#t0-2000:3100-3600k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 263  142 142 263 0.99239 0.9968 0.99405
#t0-2000:3200-3700k10N60ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 434  221 221 190 0.99596 0.99878 0.99976
#t0-2000:3300-3800k10N60ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 389  210 210 210 0.996 0.99823 0.99967
#t0-2000:3400-3900k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 291  184 184 184 0.99611 0.99583 0.99643
#t0-2000:3500-4000k10N60ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 394  280 280 210 0.99598 0.99833 0.99989
#t0-2000:3600-4100k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 450  240 240 240 0.99909 0.99964 0.99945
#t0-2000:3700-4200k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 264  198 198 198 0.99728 0.99857 0.99878
#t0-2000:3800-4300k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 245  218 219 219 0.99559 0.99893 0.99838
#t0-2000:3900-4400k10N60ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 355  326 237 237 0.99903 0.99975 0.99986
#t0-2000:4000-4500k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 318  200 200 200 0.99391 0.99964 0.99981
#t0-2000:4100-4600k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 322  292 292 292 0.99933 0.99894 0.99931
#t0-2000:4200-4700k10N60ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 385  237 237 237 0.99093 0.9971 0.99795
#t0-2000:4300-4800k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 467  282 282 282 0.99823 0.99905 0.9996
#t0-2000:4400-4900k10N60ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 331  302 302 302 0.99886 0.99828 0.998
#t0-2000:4500-5000k10N60ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,1,2,Entr0,1,2: 252  215 215 215 0.99134 0.99686 0.99717
#t0-2000:4600-5100k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 265  260 260 260 0.9986 0.99948 0.99858
#t0-2000:4700-5200k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 399  249 249 249 0.99836 0.99896 0.99957
#t0-2000:4800-5300k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 498  235 235 235 0.99816 0.99929 0.99879
#t0-2000:4900-5400k10N60ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 271  265 265 265 0.99652 0.99205 0.99735
#t0-2000:2000-2500k10N70ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 314  171 217 158 0.99545 0.99925 0.99943
#t0-2000:2100-2600k10N70ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,1,2,Entr0,1,2: 262  247 247 247 0.99387 0.99736 0.99925
#t0-2000:2200-2700k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 292  196 196 196 0.99737 0.99921 0.99986
#t0-2000:2300-2800k10N70ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,1,2,Entr0,1,2: 300  300 300 300 0.99364 0.9978 0.99976
#t0-2000:2400-2900k10N70ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 414  292 292 226 0.99279 0.99947 0.99923
#t0-2000:2500-3000k10N70ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 341  313 313 314 0.99957 0.99966 0.99936
#t0-2000:2600-3100k10N70ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 392  158 158 158 0.99828 0.99698 0.99804
#t0-2000:2700-3200k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 391  237 237 237 0.99737 0.99701 0.99707
#t0-2000:2800-3300k10N70ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 354  229 229 229 0.99885 0.99885 0.99995
#t0-2000:2900-3400k10N70ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,1,2,Entr0,1,2: 485  246 246 246 0.99524 0.99857 0.99913
#t0-2000:3000-3500k10N70ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 360  328 328 328 0.9998 0.99962 0.99978
#t0-2000:3100-3600k10N70ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 256  143 143 143 0.99723 0.99565 0.99848
#t0-2000:3200-3700k10N70ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 498  194 194 194 0.99621 0.9984 0.99909
#t0-2000:3300-3800k10N70ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 302  273 273 273 0.9895 0.99565 0.99677
#t0-2000:3400-3900k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 498  354 354 354 0.99505 0.99656 0.99794
#t0-2000:3500-4000k10N70ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 291  222 222 291 0.99449 0.995 0.99785
#t0-2000:3600-4100k10N70ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,1,2,Entr0,1,2: 362  207 207 207 0.99918 0.99986 0.99956
#t0-2000:3700-4200k10N70ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 369  369 369 369 0.99773 0.9989 0.99804
#t0-2000:3800-4300k10N70ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,1,2,Entr0,1,2: 337  308 308 308 0.99847 0.99924 0.9996
#t0-2000:3900-4400k10N70ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 358  354 354 354 0.99408 0.99844 0.99922
#t0-2000:4000-4500k10N70ns20m2b20a2.3 #Hgmax,(ncmax16)HgoL0,1,2,Entr0,1,2: 465  374 374 374 0.99739 0.99866 0.99909
#t0-2000:4100-4600k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 308  280 280 280 0.9991 0.9996 0.99968
#t0-2000:4200-4700k10N70ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 361  98 98 98 0.99261 0.99916 0.99507
#t0-2000:4300-4800k10N70ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,1,2,Entr0,1,2: 408  256 256 256 0.9992 0.99975 0.99937
#t0-2000:4400-4900k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,1,2,Entr0,1,2: 418  333 333 285 0.99769 0.99904 0.99962
#t0-2000:4500-5000k10N70ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,1,2,Entr0,1,2: 435  201 201 200 0.99268 0.998 0.99853
#t0-2000:4600-5100k10N70ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,1,2,Entr0,1,2: 380  256 256 165 0.99521 0.99956 0.99862
#t0-2000:4700-5200k10N70ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 278  220 220 220 0.99762 0.99807 0.99832
#t0-2000:4800-5300k10N70ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,1,2,Entr0,1,2: 387  324 324 324 0.99851 0.99928 0.99964
#t0-2000:4900-5400k10N70ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,1,2,Entr0,1,2: 477  434 434 434 0.9953 0.99846 0.99879
###########################
cat > tmp.dat<<EOF
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=E0=E1=E2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;E0+=$7;E1+=$8;E2+=$8;}END{printf("#mean Hgmax,Hgo0,1,2,E0,1,2:%.1f %.1f %.1f %.1f %.5g %.5g %.5g %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,E0/n,E1/n,E2/n,n);}'

cat > tmp.dat<<EOF
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=E0=E1=E2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;E0+=$7;E1+=$8;E2+=$8;}END{printf("#mean Hgmax,Hgo0,1,2,E0,1,2:%.1f %.1f %.1f %.1f %.5g %.5g %.5g %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,E0/n,E1/n,E2/n,n);}'

cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N70ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 314  171 217 158
#t0-2000:2100-2600k10N70ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 262  247 247 247
#t0-2000:2200-2700k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 292  196 196 196
#t0-2000:2300-2800k10N70ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 300  300 300 300
#t0-2000:2400-2900k10N70ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 414  292 292 291
#t0-2000:2500-3000k10N70ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 341  313 313 314
#t0-2000:2600-3100k10N70ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 392  158 158 158
#t0-2000:2700-3200k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 391  237 237 237
#t0-2000:2800-3300k10N70ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 354  229 229 229
#t0-2000:2900-3400k10N70ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 485  246 246 246
#t0-2000:3000-3500k10N70ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 360  328 328 328
#t0-2000:3100-3600k10N70ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 256  143 143 143
#t0-2000:3200-3700k10N70ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 498  194 194 194
#t0-2000:3300-3800k10N70ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 302  273 273 273
#t0-2000:3400-3900k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 498  354 354 354
#t0-2000:3500-4000k10N70ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 291  222 222 291
#t0-2000:3600-4100k10N70ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 362  207 207 207
#t0-2000:3700-4200k10N70ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 369  369 369 369
#t0-2000:3800-4300k10N70ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 337  308 308 308
#t0-2000:3900-4400k10N70ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 358  354 354 354
#t0-2000:4000-4500k10N70ns20m2b20a2.3 #Hgmax,(ncmax16)HgoL0,HgoL1,...: 465  374 374 374
#t0-2000:4100-4600k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 308  280 280 280
#t0-2000:4200-4700k10N70ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 361  98 98 98
#t0-2000:4300-4800k10N70ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 408  256 256 256
#t0-2000:4400-4900k10N70ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 418  333 333 285
#t0-2000:4500-5000k10N70ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 435  201 201 200
#t0-2000:4600-5100k10N70ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 380  256 256 165
#t0-2000:4700-5200k10N70ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 278  220 220 220
#t0-2000:4800-5300k10N70ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 387  324 324 324
#t0-2000:4900-5400k10N70ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 477  434 434 434
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:369.8 263.9 265.4 261.1 30 k10N70ns20m2b20a2.3 small 4200

cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 338  161 161 280
#t0-2000:2100-2600k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 441  99 99 98
#t0-2000:2200-2700k10N80ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 407  199 199 222
#t0-2000:2300-2800k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 274  213 213 213
#t0-2000:2400-2900k10N80ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 445  351 351 351
#t0-2000:2500-3000k10N80ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 433  283 283 281
#t0-2000:2600-3100k10N80ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 358  156 156 156
#t0-2000:2700-3200k10N80ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 328  151 151 151
#t0-2000:2800-3300k10N80ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 214  213 213 213
#t0-2000:2900-3400k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 425  331 331 331
#t0-2000:3000-3500k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 299  240 240 240
#t0-2000:3100-3600k10N80ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 397  167 167 168
#t0-2000:3200-3700k10N80ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 122  109 109 110
#t0-2000:3300-3800k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 257  77 75 75
#t0-2000:3400-3900k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 377  311 311 314
#t0-2000:3500-4000k10N80ns20m2b20a2.3 #Hgmax,(ncmax6)HgoL0,HgoL1,...: 286  282 282 78
#t0-2000:3600-4100k10N80ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 360  241 241 241
#t0-2000:3700-4200k10N80ns20m2b20a2.3 #Hgmax,(ncmax6)HgoL0,HgoL1,...: 231  136 174 136
#t0-2000:3800-4300k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 249  163 163 163
#t0-2000:3900-4400k10N80ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 327  268 268 268
#t0-2000:4000-4500k10N80ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 285  196 196 197
#t0-2000:4100-4600k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 345  310 218 218
#t0-2000:4200-4700k10N80ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 362  327 327 106
#t0-2000:4300-4800k10N80ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 373  287 287 251
#t0-2000:4400-4900k10N80ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 432  276 276 276
#t0-2000:4500-5000k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 287  176 176 176
#t0-2000:4600-5100k10N80ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 225  166 166 166
#t0-2000:4700-5200k10N80ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 346  188 188 188
#t0-2000:4800-5300k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 324  238 238 238
#t0-2000:4900-5400k10N80ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 261  112 112 112
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:326.9 214.2 212.4 200.6 30 k10N80ns20m2b20a2.3
####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 309  160 160 160
#t0-2000:2100-2600k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 327  236 236 236
#t0-2000:2200-2700k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 277  277 277 195
#t0-2000:2300-2800k10N60ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 364  185 184 184
#t0-2000:2400-2900k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 444  231 231 231
#t0-2000:2500-3000k10N60ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 373  313 313 320
#t0-2000:2600-3100k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 417  157 157 157
#t0-2000:2700-3200k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 300  235 235 235
#t0-2000:2800-3300k10N60ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 319  227 227 259
#t0-2000:2900-3400k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 336  335 335 335
#t0-2000:3000-3500k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 303  237 237 237
#t0-2000:3100-3600k10N60ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 263  142 142 142
#t0-2000:3200-3700k10N60ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 434  221 221 190
#t0-2000:3300-3800k10N60ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 389  210 210 210
#t0-2000:3400-3900k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 291  184 184 184
#t0-2000:3500-4000k10N60ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 394  280 280 210
#t0-2000:3600-4100k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 450  240 240 240
#t0-2000:3700-4200k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 264  198 198 198
#t0-2000:3800-4300k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 245  218 219 219
#t0-2000:3900-4400k10N60ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 355  326 237 237
#t0-2000:4000-4500k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 318  200 200 200
#t0-2000:4100-4600k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 322  292 292 292
#t0-2000:4200-4700k10N60ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 385  237 237 272
#t0-2000:4300-4800k10N60ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 467  282 282 282
#t0-2000:4400-4900k10N60ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 331  302 302 302
#t0-2000:4500-5000k10N60ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 252  215 215 215
#t0-2000:4600-5100k10N60ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 265  260 260 260
#t0-2000:4700-5200k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 399  249 249 249
#t0-2000:4800-5300k10N60ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 498  235 235 235
#t0-2000:4900-5400k10N60ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 271  265 265 265
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:345.4 238.3 235.3 231.7 30 k10N60ns20m2b20a2.3
##################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 491  166 166 166
#t0-2000:2100-2600k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 345  265 265 265
#t0-2000:2200-2700k10N50ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 346  225 225 225
#t0-2000:2300-2800k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 306  245 245 245
#t0-2000:2400-2900k10N50ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 353  245 245 245
#t0-2000:2500-3000k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 315  227 227 227
#t0-2000:2600-3100k10N50ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 332  242 242 242
#t0-2000:2700-3200k10N50ns20m2b20a2.3 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 270  206 206 206
#t0-2000:2800-3300k10N50ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 389  349 349 349
#t0-2000:2900-3400k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 312  281 281 281
#t0-2000:3000-3500k10N50ns20m2b20a2.3 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 329  239 239 239
#t0-2000:3100-3600k10N50ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 289  289 144 144
#t0-2000:3200-3700k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 496  108 108 108
#t0-2000:3300-3800k10N50ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 334  242 242 242
#t0-2000:3400-3900k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 288  174 174 174
#t0-2000:3500-4000k10N50ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 291  251 251 251
#t0-2000:3600-4100k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 360  283 283 283
#t0-2000:3700-4200k10N50ns20m2b20a2.3 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 327  174 174 174
#t0-2000:3800-4300k10N50ns20m2b20a2.3 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 394  164 164 164
#t0-2000:3900-4400k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 364  131 130 131
#t0-2000:4000-4500k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 415  327 327 327
#t0-2000:4100-4600k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 371  250 250 250
#t0-2000:4200-4700k10N50ns20m2b20a2.3 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 267  98 98 98
#t0-2000:4300-4800k10N50ns20m2b20a2.3 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 433  198 198 198
#t0-2000:4400-4900k10N50ns20m2b20a2.3 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 306  158 158 158
#t0-2000:4500-5000k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 265  234 234 234
#t0-2000:4600-5100k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 231  199 199 199
#t0-2000:4700-5200k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 341  218 218 218
#t0-2000:4800-5300k10N50ns20m2b20a2.3 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 390  292 292 269
#t0-2000:4900-5400k10N50ns20m2b20a2.3 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 454  238 238 238
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:346.8 223.9 219.1 218.3 30 k10N50ns20m2b20a2.3
#############

cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N60ns20m2b20a0.7 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 349  349 349 349
#t0-2000:2100-2600k10N60ns20m2b20a0.7 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 240  92 92 92
#t0-2000:2200-2700k10N60ns20m2b20a0.7 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 283  195 195 195
#t0-2000:2300-2800k10N60ns20m2b20a0.7 #Hgmax,(ncmax16)HgoL0,HgoL1,...: 363  362 362 362
#t0-2000:2400-2900k10N60ns20m2b20a0.7 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 256  173 173 173
#t0-2000:2500-3000k10N60ns20m2b20a0.7 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 404  281 281 281
#t0-2000:2600-3100k10N60ns20m2b20a0.7 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 273  157 157 157
#t0-2000:2700-3200k10N60ns20m2b20a0.7 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 250  151 151 151
#t0-2000:2800-3300k10N60ns20m2b20a0.7 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 229  140 140 141
#t0-2000:2900-3400k10N60ns20m2b20a0.7 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 367  280 280 280
#t0-2000:3000-3500k10N60ns20m2b20a0.7 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 391  270 270 207
#t0-2000:3100-3600k10N60ns20m2b20a0.7 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 178  136 136 136
#t0-2000:3200-3700k10N60ns20m2b20a0.7 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 359  359 359 359
#t0-2000:3300-3800k10N60ns20m2b20a0.7 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 245  83 83 211
#t0-2000:3400-3900k10N60ns20m2b20a0.7 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 322  177 177 177
#t0-2000:3500-4000k10N60ns20m2b20a0.7 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 363  261 261 262
#t0-2000:3600-4100k10N60ns20m2b20a0.7 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 360  179 179 179
#t0-2000:3700-4200k10N60ns20m2b20a0.7 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 226  138 138 138
#t0-2000:3800-4300k10N60ns20m2b20a0.7 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 219  160 172 172
#t0-2000:3900-4400k10N60ns20m2b20a0.7 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 268  181 181 133
#t0-2000:4000-4500k10N60ns20m2b20a0.7 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 195  177 177 177
#t0-2000:4100-4600k10N60ns20m2b20a0.7 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 367  223 223 223
#t0-2000:4200-4700k10N60ns20m2b20a0.7 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 389  98 210 98
#t0-2000:4300-4800k10N60ns20m2b20a0.7 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 328  284 284 284
#t0-2000:4400-4900k10N60ns20m2b20a0.7 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 342  174 174 174
#t0-2000:4500-5000k10N60ns20m2b20a0.7 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 314  172 172 172
#t0-2000:4600-5100k10N60ns20m2b20a0.7 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 284  279 279 279
#t0-2000:4700-5200k10N60ns20m2b20a0.7 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 293  220 220 220
#t0-2000:4800-5300k10N60ns20m2b20a0.7 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 417  193 193 193
#t0-2000:4900-5400k10N60ns20m2b20a0.7 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 313  281 281 281
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:306.2 207.5 211.6 208.5 30 k10N60ns20m2b20a0.7

export L=2 N=60 ns=50 mbam=2:20:0.7:0 TP0S=2100;loocv-bat.sh
#t0-2000:2100-2600k10N60ns50m2b20a0.7 #Hgmax,(Entropymax0.103)HgoL0,HgoL1,...: 295  93 93 235
#t0-2000:2100-2600k10N60ns50m2b20a0.7 #Hgmax,(ncmax20)HgoL0,HgoL1,...: 295  93 93 94
export L=2 N=60 ns=50 mbam=2:20:0.7:0 TP0S=4200;loocv-bat.sh
#t0-2000:4200-4700k10N60ns50m2b20a0.7 #Hgmax,(Entropymax0.112)HgoL0,HgoL1,...: 389  98 98 210
#t0-2000:4200-4700k10N60ns50m2b20a0.7 #Hgmax,(ncmax20)HgoL0,HgoL1,...: 389  98 299 98

#t0-2000:2100-2600k10N60ns20m2b20a2.3 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 327  236 236 236

cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N60ns20m2b20a1.0 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 324  166 166 166
#t0-2000:2100-2600k10N60ns20m2b20a1.0 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 386  238 238 93
#t0-2000:2200-2700k10N60ns20m2b20a1.0 #Hgmax,(ncmax16)HgoL0,HgoL1,...: 299  299 299 299
#t0-2000:2300-2800k10N60ns20m2b20a1.0 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 155  152 152 152
#t0-2000:2400-2900k10N60ns20m2b20a1.0 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 281  174 174 174
#t0-2000:2500-3000k10N60ns20m2b20a1.0 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 464  255 255 255
#t0-2000:2600-3100k10N60ns20m2b20a1.0 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 452  241 241 241
#t0-2000:2700-3200k10N60ns20m2b20a1.0 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 359  245 245 245
#t0-2000:2800-3300k10N60ns20m2b20a1.0 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 345  145 145 145
#t0-2000:2900-3400k10N60ns20m2b20a1.0 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 281  221 221 216
#t0-2000:3000-3500k10N60ns20m2b20a1.0 #Hgmax,(ncmax12)HgoL0,HgoL1,...: 299  238 238 238
#t0-2000:3100-3600k10N60ns20m2b20a1.0 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 172  172 172 172
#t0-2000:3200-3700k10N60ns20m2b20a1.0 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 118  104 104 104
#t0-2000:3300-3800k10N60ns20m2b20a1.0 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 247  85 85 84
#t0-2000:3400-3900k10N60ns20m2b20a1.0 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 291  273 173 173
#t0-2000:3500-4000k10N60ns20m2b20a1.0 #Hgmax,(ncmax7)HgoL0,HgoL1,...: 191  75 86 75
#t0-2000:3600-4100k10N60ns20m2b20a1.0 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 482  296 296 296
#t0-2000:3700-4200k10N60ns20m2b20a1.0 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 259  108 108 108
#t0-2000:3800-4300k10N60ns20m2b20a1.0 #Hgmax,(ncmax14)HgoL0,HgoL1,...: 314  301 301 301
#t0-2000:3900-4400k10N60ns20m2b20a1.0 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 272  209 209 209
#t0-2000:4000-4500k10N60ns20m2b20a1.0 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 347  213 213 213
#t0-2000:4100-4600k10N60ns20m2b20a1.0 #Hgmax,(ncmax11)HgoL0,HgoL1,...: 460  398 398 398
#t0-2000:4200-4700k10N60ns20m2b20a1.0 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 393  243 243 243
#t0-2000:4300-4800k10N60ns20m2b20a1.0 #Hgmax,(ncmax8)HgoL0,HgoL1,...: 281  193 193 193
#t0-2000:4400-4900k10N60ns20m2b20a1.0 #Hgmax,(ncmax15)HgoL0,HgoL1,...: 241  229 229 229
#t0-2000:4500-5000k10N60ns20m2b20a1.0 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 324  234 234 234
#t0-2000:4600-5100k10N60ns20m2b20a1.0 #Hgmax,(ncmax13)HgoL0,HgoL1,...: 194  168 168 168
#t0-2000:4700-5200k10N60ns20m2b20a1.0 #Hgmax,(ncmax10)HgoL0,HgoL1,...: 443  350 350 350
#t0-2000:4800-5300k10N60ns20m2b20a1.0 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 388  265 265 265
#t0-2000:4900-5400k10N60ns20m2b20a1.0 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 225  109 109 108
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:309.6 213.3 210.3 204.9 30 k10N60ns20m2b20a1.0
export L=2 N=60 ns=50 mbam=2:20:1.0:0 TP0S=3300;loocv-bat.sh
#t0-2000:3300-3800k10N60ns50m2b20a1.0 #Hgmax,(Entropymax0.187)HgoL0,HgoL1,...: 276  85 276 75
#t0-2000:3300-3800k10N60ns50m2b20a1.0 #Hgmax,(ncmax22)HgoL0,HgoL1,...: 276  85 85 85
#t0-2000:3300-3800k10N60ns50m2b20a0.7 #Hgmax,(Entropymax0.046)HgoL0,HgoL1,...: 304  212 212 211
#t0-2000:3300-3800k10N60ns50m2b20a0.7 #Hgmax,(ncmax27)HgoL0,HgoL1,...: 304  212 212 211

export L=2 N=60 ns=50 mbam=2:20:1.0:0 TP0S=3500;loocv-bat.sh
#t0-2000:3500-4000k10N60ns50m2b20a1.0 #Hgmax,(Entropymax0.157)HgoL0,HgoL1,...: 204  75 75 187
#t0-2000:3500-4000k10N60ns50m2b20a1.0 #Hgmax,(ncmax16)HgoL0,HgoL1,...: 204  75 75 187

cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax85)HgoL0,HgoL1,...: 312  164 164 162
#t0-2000:2100-2600k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax56)HgoL0,HgoL1,...: 362  96 96 94
#t0-2000:2200-2700k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax98)HgoL0,HgoL1,...: 348  228 228 228
#t0-2000:2300-2800k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax72)HgoL0,HgoL1,...: 336  245 245 243
#t0-2000:2400-2900k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax100)HgoL0,HgoL1,...: 381  205 205 205
#t0-2000:2500-3000k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax79)HgoL0,HgoL1,...: 498  281 281 405
#t0-2000:2600-3100k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax69)HgoL0,HgoL1,...: 390  364 364 364
#t0-2000:2700-3200k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax105)HgoL0,HgoL1,...: 450  149 149 149
#t0-2000:2800-3300k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax80)HgoL0,HgoL1,...: 318  227 227 227
#t0-2000:2900-3400k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax64)HgoL0,HgoL1,...: 457  281 281 281
#t0-2000:3000-3500k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax102)HgoL0,HgoL1,...: 332  154 154 154
#t0-2000:3100-3600k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax82)HgoL0,HgoL1,...: 381  262 258 258
#t0-2000:3200-3700k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax80)HgoL0,HgoL1,...: 286  192 166 192
#t0-2000:3300-3800k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax74)HgoL0,HgoL1,...: 401  208 208 208
#t0-2000:3400-3900k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax44)HgoL0,HgoL1,...: 380  256 256 172
#t0-2000:3500-4000k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax46)HgoL0,HgoL1,...: 467  81 81 80
#t0-2000:3600-4100k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax77)HgoL0,HgoL1,...: 394  208 208 208
#t0-2000:3700-4200k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax58)HgoL0,HgoL1,...: 345  147 147 147
#t0-2000:3800-4300k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax73)HgoL0,HgoL1,...: 341  280 280 161
#t0-2000:3900-4400k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax99)HgoL0,HgoL1,...: 409  210 210 210
#t0-2000:4000-4500k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax110)HgoL0,HgoL1,...: 383  227 227 227
#t0-2000:4100-4600k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax76)HgoL0,HgoL1,...: 431  220 220 220
#t0-2000:4200-4700k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax43)HgoL0,HgoL1,...: 421  98 97 96
#t0-2000:4300-4800k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax57)HgoL0,HgoL1,...: 469  312 312 312
#t0-2000:4400-4900k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax106)HgoL0,HgoL1,...: 460  213 213 213
#t0-2000:4500-5000k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax46)HgoL0,HgoL1,...: 312  234 233 203
#t0-2000:4600-5100k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax59)HgoL0,HgoL1,...: 381  212 212 212
#t0-2000:4800-5300k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax73)HgoL0,HgoL1,...: 389  182 182 182
#t0-2000:4900-5400k10N50-100:10ns20m2b20a1.0 #Hgmax,(ncmax51)HgoL0,HgoL1,...: 387  116 116 115
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:309.6 213.3 210.3 204.9 30 k10N60ns20m2b20a1.0



tspredv3prob1 ds:../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4200-4700k10N60ns50m2b20a1.0 at:-18.5_18.5:40 Sth:0.5 e4H:15 Hth:.8,0,999 ftr:../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt DISP:0 nop:1
tspredv3prob1 ds:../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4900-5400k10N:90ns50 at:-18.5_18.5:40 Sth:0.5 e4H:15 Hth:.8,0,999 ftr:../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt DISP:0 nop:1

#t0-2000:4200-4700k10N60ns50m2b20a1.0 #Hgmax,(Entropymax0.115)HgoL0,HgoL1,...: 395  299 299 96
#t0-2000:4200-4700k10N60ns50m2b20a1.0 #Hgmax,(ncmax17)HgoL0,HgoL1,...: 395  299 299 106
#t0-2000:4200-4700k10N60ns20m2b20a1.0 #Hgmax,(ncmax9)HgoL0,HgoL1,...: 393  243 243 243


export L=2 N=60 ns=50 mbam=2:20:1.0:0 TP0S=2100;nohup loocv-bat.sh & #bagging CAN2
export L=2 N=60 ns=50 mbam=2:1:1.0:0 TP0S=2100;nohup loocv-bat.sh &  #single CAN2

export L=2 N=50-100:10 ns=5 mbam=2:50:1.0:0 TP0S=2100;nohup loocv-bat.sh & #executing can2m
export L=2 N=50-100:10 ns=10 mbam=2:20:1.0:0 TP0S=2100;nohup loocv-bat.sh & #executing can2m

export L=2 N=50-100:10 ns=5 TP0S=2000;nohup loocv-bat.sh & #executing can2m
export L=2 N=50-100:10 ns=5 TP0S=2000;nohup loocv-bat.sh & #executing can2m
#t0-2000:2000-2500k10N50-300:5ns20omp #Hgmax,(Entropymax0.035)HgoL0,HgoL1,...: 146  140 136 141
#t0-2000:3300-3800k10N50-100:10ns5omp #Hgmax,(Entropymax0.073)HgoL0,HgoL1,...: 155  79 68 68
#t0-2000:3300-3800k10N50-100:10ns5omp #Hgmax,(ncmax11) HgoL0,HgoL1,...: 155  79 79 153


maximum-of-multiple-member-predictable horizon
D=k10N:50-100:10ns17
export D=k10N:50-100:10ns17 tp0=3300 M=2
python mmmph.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D} -fnyp tspSth.dat -fnyg yg.dat -M 2 -Ey 15 -DISP 0
################
#t0-2000:2100-2600k10N50-100:10ns5m2b50a1.0 #Hgmax,(ncmax16)HgoL0,HgoL1,...: 278  93 93 93
#t0-2000:2100-2600k10N50-100:10ns10m2b20a1.0 #Hgmax,(ncmax19)HgoL0,HgoL1,...: 326  92 92 236
#t0-2000:3500-4000k10N50-100:10ns10m2b20a1.0 #Hgmax,(Entropymax0.108)HgoL0,HgoL1,...: 316  78 78 250
#t0-2000:3500-4000k10N50-100:10ns10m2b20a1.0 #Hgmax,(ncmax22)HgoL0,HgoL1,...: 316  78 78 77
#t0-2000:4200-4700k10N50-100:10ns10m2b20a1.0 #Hgmax,(Entropymax0.106)HgoL0,HgoL1,...: 327  237 237 95
#t0-2000:4200-4700k10N50-100:10ns10m2b20a1.0 #Hgmax,(ncmax19)HgoL0,HgoL1,...: 327  237 96 95


export L=2 N=50-100:10 ns=5 mbam=2:20:1.0:0 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N50-100:10ns5omp #Hgmax,(ncmax16)HgoL0,HgoL1,...: 309  309 309 309
#t0-2000:2100-2600k10N50-100:10ns5omp #Hgmax,(ncmax10)HgoL0,HgoL1,...: 327  94 94 91
#t0-2000:2200-2700k10N50-100:10ns5omp #Hgmax,(ncmax11)HgoL0,HgoL1,...: 282  223 223 223
#t0-2000:2300-2800k10N50-100:10ns5omp #Hgmax,(ncmax18)HgoL0,HgoL1,...: 360  209 209 210
#t0-2000:2400-2900k10N50-100:10ns5omp #Hgmax,(ncmax12)HgoL0,HgoL1,...: 472  207 207 207
#t0-2000:2500-3000k10N50-100:10ns5omp #Hgmax,(ncmax14)HgoL0,HgoL1,...: 400  341 341 341
#t0-2000:2600-3100k10N50-100:10ns5omp #Hgmax,(ncmax13)HgoL0,HgoL1,...: 305  153 153 153
#t0-2000:2700-3200k10N50-100:10ns5omp #Hgmax,(ncmax10)HgoL0,HgoL1,...: 296  264 264 264
#t0-2000:2800-3300k10N50-100:10ns5omp #Hgmax,(ncmax15)HgoL0,HgoL1,...: 277  228 228 228
#t0-2000:2900-3400k10N50-100:10ns5omp #Hgmax,(ncmax16)HgoL0,HgoL1,...: 472  472 472 472
#t0-2000:3000-3500k10N50-100:10ns5omp #Hgmax,(ncmax20)HgoL0,HgoL1,...: 323  233 233 233
#t0-2000:3100-3600k10N50-100:10ns5omp #Hgmax,(ncmax18)HgoL0,HgoL1,...: 225  134 134 134
#t0-2000:3200-3700k10N50-100:10ns5omp #Hgmax,(ncmax17)HgoL0,HgoL1,...: 282  132 132 132
#t0-2000:3300-3800k10N50-100:10ns5omp #Hgmax,(ncmax11)HgoL0,HgoL1,...: 155  79 79 153
#t0-2000:3400-3900k10N50-100:10ns5omp #Hgmax,(ncmax11)HgoL0,HgoL1,...: 494  175 175 175
#t0-2000:3500-4000k10N50-100:10ns5omp #Hgmax,(ncmax12)HgoL0,HgoL1,...: 313  78 78 78
#t0-2000:3600-4100k10N50-100:10ns5omp #Hgmax,(ncmax13)HgoL0,HgoL1,...: 390  185 185 206
#t0-2000:3700-4200k10N50-100:10ns5omp #Hgmax,(ncmax11)HgoL0,HgoL1,...: 252  136 136 168
#t0-2000:3800-4300k10N50-100:10ns5omp #Hgmax,(ncmax13)HgoL0,HgoL1,...: 173  166 166 166
#t0-2000:3900-4400k10N50-100:10ns5omp #Hgmax,(ncmax12)HgoL0,HgoL1,...: 271  178 178 178
#t0-2000:4000-4500k10N50-100:10ns5omp #Hgmax,(ncmax17)HgoL0,HgoL1,...: 352  168 168 168
#t0-2000:4100-4600k10N50-100:10ns5omp #Hgmax,(ncmax9)HgoL0,HgoL1,...: 308  220 214 214
#t0-2000:4200-4700k10N50-100:10ns5omp #Hgmax,(ncmax11)HgoL0,HgoL1,...: 213  94 94 93
#t0-2000:4300-4800k10N50-100:10ns5omp #Hgmax,(ncmax11)HgoL0,HgoL1,...: 438  198 345 345
#t0-2000:4400-4900k10N50-100:10ns5omp #Hgmax,(ncmax12)HgoL0,HgoL1,...: 329  211 209 209
#t0-2000:4500-5000k10N50-100:10ns5omp #Hgmax,(ncmax10)HgoL0,HgoL1,...: 256  167 167 167
#t0-2000:4600-5100k10N50-100:10ns5omp #Hgmax,(ncmax11)HgoL0,HgoL1,...: 254  249 249 197
#t0-2000:4700-5200k10N50-100:10ns5omp #Hgmax,(ncmax13)HgoL0,HgoL1,...: 311  161 161 160
#t0-2000:4800-5300k10N50-100:10ns5omp #Hgmax,(ncmax16)HgoL0,HgoL1,...: 323  181 181 181
#t0-2000:4900-5400k10N50-100:10ns5omp #Hgmax,(ncmax10)HgoL0,HgoL1,...: 341  114 114 113
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:316.8 192.0 196.6 198.9 30 k10N50-100:10ns5omp
###################
20200613
###################

source init.sh
export L=2 N=N:200 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m1
export L=2 N=N:110 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m1
export L=2 N=N:50 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m
export L=2 N=N:50-200:30 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m
export L=2 N=N:50-100:10 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m1
export L=2 N=N:5-300:5 ns=1 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing    can2m2

export L=2 N=N:50-200:30 ns=20 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m
export L=2 N=N:80 ns=50 TP0S=`seq 3300 100 3300`;nohup loocv-bat.sh & #executing can2m

export L=2 k=10 N=N:60 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m

#20200614
export L=2 k=10 N=N:50-80:10 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m

export L=2 k=10 N=N:50 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m1
export L=2 k=10 N=N:70 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m2
export L=2 k=10 N=N:50-80:10 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m

export L=2 k=10 N=N:50 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m
export L=2 k=10 N=N:60 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m1
##
export L=2 k=10 N=N:70 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m
export L=2 k=10 N=N:80 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m1
##
export L=2 k=10 N=N:50-80:10 ns=17 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m
export L=2 k=10 N=N:60_N:80:20 ns=50_25 TP0S=3300;nohup loocv-bat.sh & #executing can2m1
#t0-2000:3300-3800k10N:80:20ns50_25 #Hgmax,HgoL0,HgoL1,...: 342  74 74 68


export D=k10N:50-80:10ns17 L=2
for tp0 in 4500 4600 4700 4800 4900; do
python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D} -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0
done

D=k10N:50-80:10ns50
for tp0 in 2400 2500 2600 2700 3900 4000; do
python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D} -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0
done
##check 
D=k10N:50-100:10ns17
export D=k10N:50-100:10ns17 tp0=3300 L=4
python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D} -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0

##check 
export D=k10N:50-80:10ns50 L=4
python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D} -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0


see emacs ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/cmd-io-sum.dat


python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4400-4900k10N:50-100:10ns17 -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0 -tp0 4400 -msg ""
python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:3300-3800k10N:50-100:10ns17 -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0 -tp0 4400 

###
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax21)HgoL0,HgoL1,...: 48  26 27 21
#t0-2000:2100-2600k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax29)HgoL0,HgoL1,...: 120  117 117 117
#t0-2000:2200-2700k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax29)HgoL0,HgoL1,...: 200  167 167 167
#t0-2000:2300-2800k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax25)HgoL0,HgoL1,...: 100  95 95 94
#t0-2000:2400-2900k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax29)HgoL0,HgoL1,...: 88  87 87 87
#t0-2000:2500-3000k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax35)HgoL0,HgoL1,...: 164  139 139 139
#t0-2000:2600-3100k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax31)HgoL0,HgoL1,...: 43  43 43 43
#t0-2000:2700-3200k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax20)HgoL0,HgoL1,...: 80  80 80 79
#t0-2000:2800-3300k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax47)HgoL0,HgoL1,...: 28  28 28 28
#t0-2000:2900-3400k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax28)HgoL0,HgoL1,...: 99  81 82 83
#t0-2000:3000-3500k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax33)HgoL0,HgoL1,...: 125  118 118 118
#t0-2000:3100-3600k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax37)HgoL0,HgoL1,...: 82  49 49 49
#t0-2000:3200-3700k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax42)HgoL0,HgoL1,...: 74  45 45 45
#t0-2000:3300-3800k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax48)HgoL0,HgoL1,...: 79  32 32 32
#t0-2000:3400-3900k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax32)HgoL0,HgoL1,...: 237  203 190 201
#t0-2000:3500-4000k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax22)HgoL0,HgoL1,...: 107  100 100 100
#t0-2000:3600-4100k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax33)HgoL0,HgoL1,...: 182  178 178 151
#t0-2000:3700-4200k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax32)HgoL0,HgoL1,...: 79  54 51 51
#t0-2000:3800-4300k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax50)HgoL0,HgoL1,...: 36  22 22 22
#t0-2000:3900-4400k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax38)HgoL0,HgoL1,...: 90  89 89 89
#t0-2000:4000-4500k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax33)HgoL0,HgoL1,...: 32  31 31 31
#t0-2000:4100-4600k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax32)HgoL0,HgoL1,...: 322  107 107 106
#t0-2000:4200-4700k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax32)HgoL0,HgoL1,...: 47  47 47 47
#t0-2000:4300-4800k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax30)HgoL0,HgoL1,...: 35  35 35 35
#t0-2000:4400-4900k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax53)HgoL0,HgoL1,...: 115  113 113 113
#t0-2000:4500-5000k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax35)HgoL0,HgoL1,...: 64  64 64 64
#t0-2000:4600-5100k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax31)HgoL0,HgoL1,...: 108  78 78 77
#t0-2000:4700-5200k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax40)HgoL0,HgoL1,...: 67  67 67 67
#t0-2000:4800-5300k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax28)HgoL0,HgoL1,...: 35  35 35 35
#t0-2000:4900-5400k10N5-300:5ns1m2b20a1.0 #Hgmax,(ncmax38)HgoL0,HgoL1,...: 168  137 137 137
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:101.8 82.2 81.8 80.9 30 k10N5-300:5ns1m2b20a1.0
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 414  157 157 157
#t0-2000:2100-2600k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 291  258 258 176
#t0-2000:2200-2700k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 371  166 166 166
#t0-2000:2300-2800k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 361  190 190 191
#t0-2000:2400-2900k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 351  230 230 61
#t0-2000:2500-3000k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 346  252 252 252
#t0-2000:2600-3100k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 277  154 154 185
#t0-2000:2700-3200k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 273  175 175 175
#t0-2000:2800-3300k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 374  231 231 231
#t0-2000:2900-3400k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 310  209 209 188
#t0-2000:3000-3500k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 243  243 243 243
#t0-2000:3100-3600k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 267  138 202 202
#t0-2000:3200-3700k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 255  167 167 167
#t0-2000:3300-3800k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 302  74 74 71
#t0-2000:3400-3900k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 317  169 169 169
#t0-2000:3500-4000k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 400  243 243 84
#t0-2000:3600-4100k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 360  244 244 244
#t0-2000:3700-4200k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 260  111 111 109
#t0-2000:3800-4300k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 282  222 222 224
#t0-2000:3900-4400k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 498  313 313 313
#t0-2000:4000-4500k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 323  196 196 228
#t0-2000:4100-4600k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 416  190 190 190
#t0-2000:4200-4700k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 323  220 220 220
#t0-2000:4300-4800k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 342  279 279 279
#t0-2000:4400-4900k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 362  157 157 273
#t0-2000:4500-5000k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 270  170 170 170
#t0-2000:4600-5100k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 319  196 196 196
#t0-2000:4700-5200k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 319  188 188 188
#t0-2000:4800-5300k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 414  268 219 219
#t0-2000:4900-5400k10N:50-80:10ns17 #Hgmax,HgoL0,HgoL1,...: 317  120 120 120
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:331.9 197.7 198.2 189.7 30 k10N:50-80:10ns17
####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 274  168 168 168
#t0-2000:2100-2600k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 268  177 177 177
#t0-2000:2200-2700k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 316  316 316 316
#t0-2000:2300-2800k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 245  167 160 167
#t0-2000:2400-2900k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 237  61 61 61
#t0-2000:2500-3000k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 283  270 270 270
#t0-2000:2600-3100k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 277  126 148 126
#t0-2000:2700-3200k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 267  175 175 175
#t0-2000:2800-3300k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 349  257 257 257
#t0-2000:2900-3400k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 213  189 189 189
#t0-2000:3000-3500k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 237  151 151 151
#t0-2000:3100-3600k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 205  202 201 205
#t0-2000:3200-3700k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 178  102 102 102
#t0-2000:3300-3800k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 183  74 74 74
#t0-2000:3400-3900k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 316  232 232 232
#t0-2000:3500-4000k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 400  160 160 160
#t0-2000:3600-4100k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 360  210 213 210
#t0-2000:3700-4200k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 260  111 111 111
#t0-2000:3800-4300k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 282  128 128 128
#t0-2000:3900-4400k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 267  122 122 122
#t0-2000:4000-4500k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 228  169 169 169
#t0-2000:4100-4600k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 205  205 205 205
#t0-2000:4200-4700k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 293  105 105 105
#t0-2000:4300-4800k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 312  194 280 280
#t0-2000:4400-4900k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 362  244 244 305
#t0-2000:4500-5000k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 260  144 144 146
#t0-2000:4600-5100k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 319  319 319 319
#t0-2000:4700-5200k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 247  188 188 188
#t0-2000:4800-5300k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 414  208 208 208
#t0-2000:4900-5400k10N:50ns17 #Hgmax,HgoL0,HgoL1,...: 317  169 169 169
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:279.1 178.1 181.5 183.2 30 k10N:50ns17

####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 218  157 158 158
#t0-2000:2100-2600k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 270  258 258 223
#t0-2000:2200-2700k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 256  166 166 166
#t0-2000:2300-2800k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 361  193 125 79
#t0-2000:2400-2900k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 230  230 230 230
#t0-2000:2500-3000k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 315  225 225 225
#t0-2000:2600-3100k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 247  154 154 154
#t0-2000:2700-3200k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 268  170 170 170
#t0-2000:2800-3300k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 374  227 227 227
#t0-2000:2900-3400k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 277  213 213 213
#t0-2000:3000-3500k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 238  152 152 152
#t0-2000:3100-3600k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 204  138 138 138
#t0-2000:3200-3700k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 196  171 178 178
#t0-2000:3300-3800k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 302  74 74 71
#t0-2000:3400-3900k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 317  206 173 173
#t0-2000:3500-4000k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 281  159 159 159
#t0-2000:3600-4100k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 244  244 244 244
#t0-2000:3700-4200k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 199  113 113 113
#t0-2000:3800-4300k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 231  185 185 130
#t0-2000:3900-4400k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 269  139 139 237
#t0-2000:4000-4500k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 323  323 323 323
#t0-2000:4100-4600k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 416  201 201 201
#t0-2000:4200-4700k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 249  220 220 220
#t0-2000:4300-4800k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 342  255 255 255
#t0-2000:4400-4900k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 301  273 273 273
#t0-2000:4500-5000k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 270  170 170 170
#t0-2000:4600-5100k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 233  195 195 195
#t0-2000:4700-5200k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 319  272 272 152
#t0-2000:4800-5300k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 380  254 254 254
#t0-2000:4900-5400k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 311  223 223 222
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:281.4 198.7 195.6 190.2 30 k10N:60ns17

####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 218  157 157 157
#t0-2000:2100-2600k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 233  203 203 99
#t0-2000:2200-2700k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 277  167 167 223
#t0-2000:2300-2800k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 190  168 168 168
#t0-2000:2400-2900k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 264  263 263 263
#t0-2000:2500-3000k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 346  251 251 251
#t0-2000:2600-3100k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 214  186 186 186
#t0-2000:2700-3200k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 240  150 150 175
#t0-2000:2800-3300k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 228  165 165 165
#t0-2000:2900-3400k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 310  202 202 202
#t0-2000:3000-3500k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 240  210 210 210
#t0-2000:3100-3600k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 230  140 140 140
#t0-2000:3200-3700k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 255  105 103 103
#t0-2000:3300-3800k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 88  75 75 75
#t0-2000:3400-3900k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 231  170 170 170
#t0-2000:3500-4000k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 374  242 242 242
#t0-2000:3600-4100k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 239  181 181 181
#t0-2000:3700-4200k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 256  111 111 111
#t0-2000:3800-4300k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 247  247 247 247
#t0-2000:3900-4400k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 498  313 313 313
#t0-2000:4000-4500k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 290  196 196 199
#t0-2000:4100-4600k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 204  190 190 190
#t0-2000:4200-4700k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 323  97 323 98
#t0-2000:4300-4800k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 313  192 192 192
#t0-2000:4400-4900k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 275  157 157 157
#t0-2000:4500-5000k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 260  172 172 172
#t0-2000:4600-5100k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 241  196 196 168
#t0-2000:4700-5200k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 217  188 188 188
#t0-2000:4800-5300k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 268  208 206 206
#t0-2000:4900-5400k10N:70ns17 #Hgmax,HgoL0,HgoL1,...: 264  250 264 264
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:261.1 185.1 192.9 183.8 30 k10N:70ns17

####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 414  156 183 183
#t0-2000:2100-2600k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 291  291 291 98
#t0-2000:2200-2700k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 371  193 193 193
#t0-2000:2300-2800k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 273  178 178 178
#t0-2000:2400-2900k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 351  248 248 248
#t0-2000:2500-3000k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 286  224 224 224
#t0-2000:2600-3100k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 253  151 151 185
#t0-2000:2700-3200k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 273  270 270 270
#t0-2000:2800-3300k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 257  170 170 170
#t0-2000:2900-3400k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 277  214 214 209
#t0-2000:3000-3500k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 243  243 243 243
#t0-2000:3100-3600k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 267  143 143 143
#t0-2000:3200-3700k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 194  167 167 167
#t0-2000:3300-3800k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 266  73 73 73
#t0-2000:3400-3900k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 317  171 171 171
#t0-2000:3500-4000k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 251  243 243 243
#t0-2000:3600-4100k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 330  178 178 178
#t0-2000:3700-4200k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 146  110 110 110
#t0-2000:3800-4300k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 232  224 224 224
#t0-2000:3900-4400k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 326  266 266 266
#t0-2000:4000-4500k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 303  226 179 258
#t0-2000:4100-4600k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 203  202 202 202
#t0-2000:4200-4700k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 262  96 262 96
#t0-2000:4300-4800k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 342  206 206 206
#t0-2000:4400-4900k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 303  158 233 158
#t0-2000:4500-5000k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 265  169 265 265
#t0-2000:4600-5100k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 240  167 167 167
#t0-2000:4700-5200k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 318  273 273 274
#t0-2000:4800-5300k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 379  219 219 219
#t0-2000:4900-5400k10N:80ns17 #Hgmax,HgoL0,HgoL1,...: 313  120 120 120
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:284.9 191.6 202.2 191.4 30 k10N:80ns17

D=k10N:80ns17
for tp0 in 2200 2300 3200 3300  4400 4700; do
python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D} -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0
done


####################
cat > tmp.dat<<EOF

EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:287.2 186.2 199.8 202.9 30 k10N:90ns17
####################

####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 295  188 188 185
#t0-2000:2100-2600k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 236  93 204 93
#t0-2000:2200-2700k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 289  197 197 166
#t0-2000:2300-2800k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 188  168 168 168
#t0-2000:2400-2900k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 354  290 290 290
#t0-2000:2500-3000k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 309  284 284 284
#t0-2000:2600-3100k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 249  185 185 185
#t0-2000:2700-3200k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 267  151 151 151
#t0-2000:2800-3300k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 348  167 256 256
#t0-2000:2900-3400k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 492  216 216 216
#t0-2000:3000-3500k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 244  243 243 243
#t0-2000:3100-3600k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 172  134 134 134
#t0-2000:3200-3700k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 180  132 132 132
#t0-2000:3300-3800k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 280  74 74 74
#t0-2000:3400-3900k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 421  171 171 171
#t0-2000:3500-4000k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 339  339 339 339
#t0-2000:3600-4100k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 296  241 241 241
#t0-2000:3700-4200k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 200  143 143 143
#t0-2000:3800-4300k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 244  180 180 222
#t0-2000:3900-4400k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 352  236 236 236
#t0-2000:4000-4500k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 303  200 200 226
#t0-2000:4100-4600k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 205  202 202 202
#t0-2000:4200-4700k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 290  97 97 97
#t0-2000:4300-4800k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 312  252 252 282
#t0-2000:4400-4900k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 278  211 211 211
#t0-2000:4500-5000k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 236  166 236 236
#t0-2000:4600-5100k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 241  167 167 158
#t0-2000:4700-5200k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 335  140 140 287
#t0-2000:4800-5300k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 410  208 208 208
#t0-2000:4900-5400k10N:90ns17 #Hgmax,HgoL0,HgoL1,...: 250  112 250 250
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:287.2 186.2 199.8 202.9 30 k10N:90ns17
####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 191  183 183 188
#t0-2000:2100-2600k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 357  357 357 92
#t0-2000:2200-2700k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 267  267 267 267
#t0-2000:2300-2800k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 215  167 167 167
#t0-2000:2400-2900k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 322  228 228 228
#t0-2000:2500-3000k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 316  316 316 316
#t0-2000:2600-3100k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 308  151 183 151
#t0-2000:2700-3200k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 269  148 148 264
#t0-2000:2800-3300k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 314  168 195 195
#t0-2000:2900-3400k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 370  215 215 215
#t0-2000:3000-3500k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 276  244 244 234
#t0-2000:3100-3600k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 277  138 138 138
#t0-2000:3200-3700k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 173  103 103 103
#t0-2000:3300-3800k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 283  74 81 81
#t0-2000:3400-3900k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 379  174 174 174
#t0-2000:3500-4000k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 239  77 77 77
#t0-2000:3600-4100k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 299  215 215 215
#t0-2000:3700-4200k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 170  118 118 170
#t0-2000:3800-4300k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 228  180 180 171
#t0-2000:3900-4400k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 400  326 326 400
#t0-2000:4000-4500k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 492  197 197 197
#t0-2000:4100-4600k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 393  362 362 201
#t0-2000:4200-4700k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 294  98 98 98
#t0-2000:4300-4800k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 287  282 193 193
#t0-2000:4400-4900k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 307  212 212 212
#t0-2000:4500-5000k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 178  178 178 178
#t0-2000:4600-5100k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 235  166 166 166
#t0-2000:4700-5200k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 319  140 140 247
#t0-2000:4800-5300k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 236  212 212 212
#t0-2000:4900-5400k10N:100ns17 #Hgmax,HgoL0,HgoL1,...: 312  312 112 112
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:290.2 200.3 192.8 188.7 30 k10N:100ns17
#########
cat > tmp.dat<<EOF

EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'

#2000 2700 3700
D=k10N:50-80:10ns50
tp0=3800;python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-$((tp0+500))${D} -fnyp tspSth.dat -fnyg yg.dat -K 2 -L $L -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0

####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 424  169 169 218
#t0-2000:2100-2600k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 292  258 258 258
#t0-2000:2200-2700k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 430  196 196 196
#t0-2000:2300-2800k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 362  168 168 168
#t0-2000:2400-2900k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 385  237 237 174
#t0-2000:2500-3000k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 437  253 253 253
#t0-2000:2600-3100k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 375  185 185 247
#t0-2000:2700-3200k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 300  175 175 175
#t0-2000:2800-3300k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 381  231 231 226
#t0-2000:2900-3400k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 345  213 213 213
#t0-2000:3000-3500k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 375  236 236 235
#t0-2000:3100-3600k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 279  143 143 143
#t0-2000:3200-3700k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 297  106 106 167
#t0-2000:3300-3800k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 342  74 74 72
#t0-2000:3400-3900k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 377  173 173 173
#t0-2000:3500-4000k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 402  239 239 239
#t0-2000:3600-4100k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 360  299 299 299
#t0-2000:3700-4200k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 324  113 113 113
#t0-2000:3800-4300k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 282  225 225 227
#t0-2000:3900-4400k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 498  125 125 125
#t0-2000:4000-4500k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 491  196 196 196
#t0-2000:4100-4600k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 418  202 202 195
#t0-2000:4200-4700k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 323  96 96 96
#t0-2000:4300-4800k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 498  283 283 194
#t0-2000:4400-4900k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 365  273 273 273
#t0-2000:4500-5000k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 353  169 169 63
#t0-2000:4600-5100k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 319  165 165 165
#t0-2000:4700-5200k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 319  141 141 141
#t0-2000:4800-5300k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 414  210 210 238
#t0-2000:4900-5400k10N:50-80:10ns50 #Hgmax,HgoL0,HgoL1,...: 317  112 112 222
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:369.5 188.8 188.8 190.1 30 k10N:50-80:10ns50
####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 295  188 187 196
#t0-2000:2100-2600k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 353  93 93 93
#t0-2000:2200-2700k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 289  267 267 289
#t0-2000:2300-2800k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 245  167 167 188
#t0-2000:2400-2900k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 354  237 237 237
#t0-2000:2500-3000k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 406  299 299 284
#t0-2000:2600-3100k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 366  184 184 184
#t0-2000:2700-3200k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 297  151 151 151
#t0-2000:2800-3300k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 378  259 259 259
#t0-2000:2900-3400k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 492  215 215 310
#t0-2000:3000-3500k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 270  225 225 225
#t0-2000:3100-3600k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 202  142 111 111
#t0-2000:3200-3700k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 180  106 106 106
#t0-2000:3300-3800k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 280  74 74 74
#t0-2000:3400-3900k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 421  175 175 175
#t0-2000:3500-4000k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 339  77 77 76
#t0-2000:3600-4100k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 296  241 241 241
#t0-2000:3700-4200k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 281  116 116 116
#t0-2000:3800-4300k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 366  224 189 222
#t0-2000:3900-4400k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 498  352 352 352
#t0-2000:4000-4500k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 382  301 301 301
#t0-2000:4100-4600k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 361  202 202 202
#t0-2000:4200-4700k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 293  96 96 261
#t0-2000:4300-4800k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 313  253 253 253
#t0-2000:4400-4900k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 359  211 211 212
#t0-2000:4500-5000k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 236  171 171 202
#t0-2000:4600-5100k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 359  167 167 167
#t0-2000:4700-5200k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 367  217 141 141
#t0-2000:4800-5300k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 410  220 220 220
#t0-2000:4900-5400k10N:90ns50 #Hgmax,HgoL0,HgoL1,...: 296  112 112 112
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:332.8 191.4 186.6 198.7 30 k10N:90ns50

####################
####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 332  219 219 191
#t0-2000:2100-2600k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 357  92 92 92
#t0-2000:2200-2700k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 314  267 267 267
#t0-2000:2300-2800k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 215  179 179 188
#t0-2000:2400-2900k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 355  228 228 202
#t0-2000:2500-3000k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 316  247 247 247
#t0-2000:2600-3100k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 308  184 184 184
#t0-2000:2700-3200k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 269  238 238 238
#t0-2000:2800-3300k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 314  198 198 198
#t0-2000:2900-3400k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 370  213 213 215
#t0-2000:3000-3500k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 330  241 241 241
#t0-2000:3100-3600k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 297  135 135 135
#t0-2000:3200-3700k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 199  133 133 103
#t0-2000:3300-3800k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 283  73 73 73
#t0-2000:3400-3900k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 379  174 174 174
#t0-2000:3500-4000k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 251  77 77 75
#t0-2000:3600-4100k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 299  211 211 211
#t0-2000:3700-4200k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 281  119 119 119
#t0-2000:3800-4300k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 392  171 180 171
#t0-2000:3900-4400k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 400  269 269 268
#t0-2000:4000-4500k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 492  200 200 197
#t0-2000:4100-4600k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 393  201 201 201
#t0-2000:4200-4700k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 356  97 97 97
#t0-2000:4400-4900k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 307  211 211 211
#t0-2000:4500-5000k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 300  169 169 169
#t0-2000:4600-5100k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 240  162 162 162
#t0-2000:4700-5200k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 319  247 247 140
#t0-2000:4800-5300k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 242  235 235 235
#t0-2000:4900-5400k10N:100ns50 #Hgmax,HgoL0,HgoL1,...: 317  112 112 111
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:318.2 182.8 183.1 176.4 29 k10N:100ns50
####################


####################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 250  217 218 218
#t0-2000:2100-2600k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 261  232 232 232
#t0-2000:2200-2700k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 318  197 197 197
#t0-2000:2300-2800k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 243  168 168 168
#t0-2000:2400-2900k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 291  258 258 172
#t0-2000:2500-3000k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 437  253 249 249
#t0-2000:2600-3100k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 274  184 184 184
#t0-2000:2700-3200k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 240  151 151 208
#t0-2000:2800-3300k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 310  199 199 138
#t0-2000:2900-3400k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 310  248 248 248
#t0-2000:3000-3500k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 375  236 236 235
#t0-2000:3100-3600k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 279  141 141 141
#t0-2000:3200-3700k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 255  103 103 103
#t0-2000:3300-3800k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 197  73 73 69
#t0-2000:3400-3900k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 351  170 170 170
#t0-2000:3500-4000k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 402  320 320 320
#t0-2000:3600-4100k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 241  149 149 149
#t0-2000:3700-4200k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 324  113 113 111
#t0-2000:3800-4300k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 254  248 248 248
#t0-2000:3900-4400k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 498  124 124 124
#t0-2000:4000-4500k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 305  292 198 198
#t0-2000:4100-4600k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 306  190 190 195
#t0-2000:4200-4700k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 323  96 96 206
#t0-2000:4300-4800k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 377  279 280 280
#t0-2000:4400-4900k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 365  157 157 157
#t0-2000:4500-5000k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 269  264 264 264
#t0-2000:4600-5100k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 254  165 165 169
#t0-2000:4700-5200k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 317  140 140 217
#t0-2000:4800-5300k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 268  239 239 237
#t0-2000:4900-5400k10N:70ns50 #Hgmax,HgoL0,HgoL1,...: 278  112 112 119
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:305.7 190.6 187.4 190.9 30 k10N:70ns50 
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#################
cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 424  424 424 424
#t0-2000:2100-2600k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 291  93 93 93
#t0-2000:2200-2700k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 371  259 259 259
#t0-2000:2300-2800k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 273  167 167 168
#t0-2000:2400-2900k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 385  248 248 201
#t0-2000:2500-3000k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 381  249 249 249
#t0-2000:2600-3100k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 274  247 247 247
#t0-2000:2700-3200k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 296  147 147 148
#t0-2000:2800-3300k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 381  259 196 196
#t0-2000:2900-3400k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 345  211 211 215
#t0-2000:3000-3500k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 243  243 243 243
#t0-2000:3100-3600k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 267  138 138 138
#t0-2000:3200-3700k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 231  106 106 106
#t0-2000:3300-3800k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 304  73 73 72
#t0-2000:3400-3900k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 319  174 174 174
#t0-2000:3500-4000k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 251  77 77 77
#t0-2000:3600-4100k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 330  211 211 211
#t0-2000:3700-4200k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 286  111 111 111
#t0-2000:3800-4300k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 245  224 224 224
#t0-2000:3900-4400k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 358  266 266 265
#t0-2000:4000-4500k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 491  197 197 257
#t0-2000:4100-4600k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 334  201 201 201
#t0-2000:4200-4700k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 292  96 96 96
#t0-2000:4300-4800k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 498  254 312 193
#t0-2000:4400-4900k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 357  272 272 272
#t0-2000:4500-5000k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 296  169 169 176
#t0-2000:4600-5100k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 317  164 164 164
#t0-2000:4700-5200k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 318  141 141 141
#t0-2000:4800-5300k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 379  269 269 269
#t0-2000:4900-5400k10N:80ns50 #Hgmax,HgoL0,HgoL1,...: 313  111 111 313
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:328.3 193.4 193.2 196.8 30 k10N:80ns50


cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 414  187 157 157
#t0-2000:2100-2600k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 357  258 258 100
#t0-2000:2200-2700k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 371  316 316 267
#t0-2000:2300-2800k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 361  190 168 191
#t0-2000:2400-2900k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 354  350 350 202
#t0-2000:2500-3000k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 346  284 284 284
#t0-2000:2600-3100k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 308  185 185 185
#t0-2000:2700-3200k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 273  270 270 270
#t0-2000:2800-3300k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 374  257 256 257
#t0-2000:2900-3400k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 492  215 215 215
#t0-2000:3000-3500k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 276  243 243 243
#t0-2000:3100-3600k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 277  138 144 144
#t0-2000:3200-3700k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 255  106 106 167
#t0-2000:3300-3800k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 302  74 74 71
#t0-2000:3400-3900k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 421  175 175 175
#t0-2000:3500-4000k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 400  243 243 77
#t0-2000:3600-4100k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 360  241 241 241
#t0-2000:3700-4200k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 260  115 115 115
#t0-2000:3800-4300k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 282  179 171 187
#t0-2000:3900-4400k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 498  326 326 267
#t0-2000:4000-4500k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 492  196 256 256
#t0-2000:4100-4600k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 416  202 202 202
#t0-2000:4200-4700k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 323  97 97 261
#t0-2000:4300-4800k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 342  282 282 282
#t0-2000:4400-4900k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 362  273 273 273
#t0-2000:4500-5000k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 270  169 169 178
#t0-2000:4600-5100k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 319  196 196 196
#t0-2000:4700-5200k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 335  141 141 319
#t0-2000:4800-5300k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 414  208 208 219
#t0-2000:4900-5400k10N:50-100:10ns17 #Hgmax,HgoL0,HgoL1,...: 317  311 311 311
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:352.4 214.2 214.4 210.4 30 k10N:50-100:10ns17

export L=2 N=N:60 ns=50 TP0S=`seq 2000 100 4900`;nohup loocv-bat.sh & #executing can2m
cat > tmp.dat <<EOF
#t0-2000:2000-2500k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 365  219 158 171
#t0-2000:2100-2600k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 292  292 292 292
#t0-2000:2200-2700k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 262  166 166 166
#t0-2000:2300-2800k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 361  168 168 168
#t0-2000:2400-2900k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 324  261 261 261
#t0-2000:2500-3000k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 347  225 225 225
#t0-2000:2600-3100k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 375  154 154 247
#t0-2000:2700-3200k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 300  178 178 178
#t0-2000:2800-3300k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 374  228 228 352
#t0-2000:2900-3400k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 279  214 214 188
#t0-2000:3000-3500k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 304  152 152 152
#t0-2000:3100-3600k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 204  138 136 136
#t0-2000:3200-3700k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 196  105 105 105
#t0-2000:3300-3800k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 342  74 74 239
#t0-2000:3400-3900k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 377  174 174 174
#t0-2000:3500-4000k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 309  189 189 189
#t0-2000:3600-4100k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 260  150 192 192
#t0-2000:3700-4200k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 282  113 113 113
#t0-2000:3800-4300k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 281  185 182 182
#t0-2000:3900-4400k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 304  126 126 126
#t0-2000:4000-4500k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 323  231 231 231
#t0-2000:4100-4600k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 418  201 201 201
#t0-2000:4200-4700k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 305  220 220 220
#t0-2000:4300-4800k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 342  254 254 254
#t0-2000:4400-4900k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 301  273 273 273
#t0-2000:4500-5000k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 353  170 170 143
#t0-2000:4600-5100k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 253  166 166 166
#t0-2000:4700-5200k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 319  159 159 164
#t0-2000:4800-5300k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 380  219 219 208
#t0-2000:4900-5400k10N:60ns50 #Hgmax,HgoL0,HgoL1,...: 314  112 112 223
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:314.9 183.9 183.1 198.0 30 k10N:60ns50

cat >tmp.dat<<EOF
#t0-2000:2000-2500k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 218  157 158 158
#t0-2000:2100-2600k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 270  258 258 223
#t0-2000:2200-2700k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 256  166 166 166
#t0-2000:2300-2800k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 361  193 125 79
#t0-2000:2400-2900k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 230  230 62 230
#t0-2000:2500-3000k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 315  225 225 225
#t0-2000:2600-3100k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 247  154 154 154
#t0-2000:2700-3200k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 268  170 170 170
#t0-2000:2800-3300k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 374  227 227 227
#t0-2000:2900-3400k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 277  213 213 213
#t0-2000:3000-3500k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 238  152 152 152
#t0-2000:3100-3600k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 204  138 138 138
#t0-2000:3200-3700k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 196  171 178 178
#t0-2000:3300-3800k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 302  74 74 71  
#t0-2000:3400-3900k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 317  206 173 173
#t0-2000:3500-4000k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 281  159 159 159
#t0-2000:3600-4100k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 244  244 244 244
#t0-2000:3700-4200k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 199  113 113 113
#t0-2000:3800-4300k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 231  185 185 185
#t0-2000:3900-4400k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 269  139 139 237
#t0-2000:4000-4500k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 323  323 323 323
#t0-2000:4100-4600k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 416  201 201 201
#t0-2000:4200-4700k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 249  220 220 220
#t0-2000:4300-4800k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 342  255 255 255
#t0-2000:4400-4900k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 301  273 273 273
#t0-2000:4500-5000k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 270  170 170 170
#t0-2000:4600-5100k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 233  195 195 195
#t0-2000:4700-5200k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 319  272 272 152
#t0-2000:4800-5300k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 380  254 254 254
#t0-2000:4900-5400k10N:60ns17 #Hgmax,HgoL0,HgoL1,...: 311  223 223 222
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:281.4 198.7 190.0 192.0 30 k10N:60ns17

#t0-2000:2000-2500k10N:50-200:30ns20 #Hgmax,HgoL0,HgoL1,...: 414  194 194 191
#t0-2000:2100-2600k10N:50-200:30ns20 #Hgmax,HgoL0,HgoL1,...: 321  92 92 92
#t0-2000:2200-2700k10N:50-200:30ns20 #Hgmax,HgoL0,HgoL1,...: 371  166 166 166
#t0-2000:2300-2800k10N:50-200:30ns20 #Hgmax,HgoL0,HgoL1,...: 362  189 189 186
#t0-2000:2400-2900k10N:50-200:30ns20 #Hgmax,HgoL0,HgoL1,...: 448  237 237 288
#t0-2000:2500-3000k10N:50-200:30ns20 #Hgmax,HgoL0,HgoL1,...: 376  249 249 355
#t0-2000:2600-3100k10N:50-200:30ns20 #Hgmax,HgoL0,HgoL1,...: 338  184 184 184


cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 332  304 304 304
#t0-2000:2100-2600k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 268  257 257 257
#t0-2000:2200-2700k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 430  194 194 194
#t0-2000:2300-2800k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 362  167 167 167
#t0-2000:2400-2900k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 237  201 201 201
#t0-2000:2500-3000k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 355  283 283 283
#t0-2000:2600-3100k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 310  185 185 184
#t0-2000:2700-3200k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 267  175 175 175
#t0-2000:2800-3300k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 349  275 275 199
#t0-2000:2900-3400k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 249  213 213 213
#t0-2000:3000-3500k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 244  151 151 151
#t0-2000:3100-3600k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 205  174 174 174
#t0-2000:3200-3700k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 297  106 106 106
#t0-2000:3300-3800k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 279  74 74 72
#t0-2000:3400-3900k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 316  175 175 175
#t0-2000:3500-4000k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 400  239 239 239
#t0-2000:3600-4100k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 360  211 211 211
#t0-2000:3700-4200k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 290  113 113 113
#t0-2000:3800-4300k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 282  174 174 174
#t0-2000:3900-4400k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 267  121 121 121
#t0-2000:4000-4500k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 303  169 169 193
#t0-2000:4100-4600k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 350  195 193 193
#t0-2000:4200-4700k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 306  181 181 104
#t0-2000:4300-4800k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 342  284 284 284
#t0-2000:4400-4900k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 362  243 243 243
#t0-2000:4500-5000k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 260  169 169 144
#t0-2000:4600-5100k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 319  241 241 241
#t0-2000:4700-5200k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 275  140 140 140
#t0-2000:4800-5300k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 414  208 208 212
#t0-2000:4900-5400k10N:50ns50 #Hgmax,HgoL0,HgoL1,...: 317  111 111 111
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:311.6 191.1 191.0 185.9 30 k10N:50ns50

cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 414  194 194 194
#t0-2000:2100-2600k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 321  92 92 269
#t0-2000:2200-2700k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 371  166 166 166
#t0-2000:2300-2800k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 273  189 189 186
#t0-2000:2400-2900k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 448  231 231 288
#t0-2000:2500-3000k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 376  249 249 286
#t0-2000:2600-3100k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 277  184 184 184
#t0-2000:2700-3200k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 387  270 270 270
#t0-2000:2800-3300k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 349  286 286 286
#t0-2000:2900-3400k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 308  212 212 214
#t0-2000:3000-3500k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 332  243 243 243
#t0-2000:3100-3600k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 267  134 134 143
#t0-2000:3200-3700k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 353  101 101 101
#t0-2000:3300-3800k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 300  75 75 72
#t0-2000:3400-3900k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 351  175 175 175
#t0-2000:3500-4000k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 400  77 77 75
#t0-2000:3600-4100k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 360  179 179 179
#t0-2000:3700-4200k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 260  118 118 118
#t0-2000:3800-4300k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 367  180 180 180
#t0-2000:3900-4400k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 357  267 267 267
#t0-2000:4000-4500k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 464  302 302 301
#t0-2000:4100-4600k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 361  201 201 194
#t0-2000:4200-4700k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 320  96 96 96
#t0-2000:4300-4800k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 376  254 254 254
#t0-2000:4400-4900k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 362  277 277 277
#t0-2000:4500-5000k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 265  178 177 176
#t0-2000:4600-5100k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 319  167 167 167
#t0-2000:4700-5200k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 344  140 140 140
#t0-2000:4800-5300k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 414  208 208 208
#t0-2000:4900-5400k10N:50-200:30ns17 #Hgmax,HgoL0,HgoL1,...: 317  112 112 112
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:347.1 185.2 185.2 194.0 30 k10N:50-200:30ns17

cat > tmp.dat<<EOF
#t0-2000:2000-2500k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 395  191 191 191
#t0-2000:2100-2600k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 321  91 91 91
#t0-2000:2200-2700k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 279  166 166 166
#t0-2000:2300-2800k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 202  66 66 66
#t0-2000:2400-2900k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 354  225 225 225
#t0-2000:2500-3000k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 312  246 246 246
#t0-2000:2600-3100k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 247  155 155 148
#t0-2000:2700-3200k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 275  147 147 147
#t0-2000:2800-3300k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 256  175 175 256
#t0-2000:2900-3400k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 331  214 212 212
#t0-2000:3000-3500k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 237  149 149 149
#t0-2000:3100-3600k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 234  135 135 133
#t0-2000:3200-3700k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 178  44 44 44
#t0-2000:3300-3800k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 281  74 74 74
#t0-2000:3400-3900k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 334  176 176 176
#t0-2000:3500-4000k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 242  77 77 77
#t0-2000:3600-4100k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 299  150 150 150
#t0-2000:3700-4200k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 200  118 119 51
#t0-2000:3800-4300k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 390  187 187 187
#t0-2000:3900-4400k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 302  124 124 124
#t0-2000:4000-4500k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 259  192 192 192
#t0-2000:4100-4600k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 416  201 201 201
#t0-2000:4200-4700k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 293  97 97 97
#t0-2000:4300-4800k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 400  192 192 279
#t0-2000:4400-4900k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 338  267 267 267
#t0-2000:4500-5000k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 244  166 166 166
#t0-2000:4600-5100k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 240  78 77 77
#t0-2000:4700-5200k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 319  141 141 141
#t0-2000:4800-5300k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 409  186 186 186
#t0-2000:4900-5400k10N:5-300:5ns1 #Hgmax,HgoL0,HgoL1,...: 311  113 113 112
EOF
cat tmp.dat|awk 'BEGIN{hg=hoL0=hoL1=hoL2=n=0}{n++;hg+=$3;hoL0+=$4;hoL1+=$5;hoL2+=$6;}END{printf("#mean Hgmax,HgoL1,...:%.1f %.1f %.1f %.1f %d\n",hg/n,hoL0/n,hoL1/n,hoL2/n,n);}'
#mean Hgmax,HgoL1,...:296.6 151.4 151.4 154.4 30 k10N:5-300:5ns1 


#Results2 are saved in d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2000-2500k10N:50-200:30ns17


###################
20200609
###################
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc;mkdir -p $d00
export L=2 N=N:50-300:30 n_seed=17 TP0S=2900;nohup loocv-bat.sh &
export L=2 N=N:5-300:5 n_seed=1 TP0S=2000;nohup loocv-bat.sh &


export L=2 
export N="N:50,75,100" n_seed="33"
export N=N:50,60,70,80,90,100 n_seed=17 
export N=N:50-100:10 n_seed=17 
export N=N:50-100:5 n_seed=9
export N=N:50-150:20 n_seed=17 
export N=N:50-200:30 n_seed=17 
export N=N:50-200:30 n_seed=17
export TP0S="2400 2500"
nohup loocv-bat.sh &
###################
20191220
###################
#課題１：20191219のstep1を行わず、Nを、例えばN=50に固定してstep2を行ってもそれなりにうまくいくのでは無いかと考えた。
#なぜなら、同一のデータを用いて同一の入出力関数を学習しているはずだから。
# Nが小さい場合と大きい場合の違いは？
# 最適なNは？
#課題２：選ばれたクラスタ内のhi-LOOCVとhgの関係の解析？20191219(2-4)check correlation between hg and hi-LOOCV
###################
##以下、実験
###################
#(1-0) 初期設定
#######
####################カット＆ペーストここから
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc;mkdir -p $d00
export L=2 N=N:50-100:12 n_seed=17 TP0S=`seq 2000 100 2900`;nohup loocv-bat.sh & 
export L=2 N=N:50-100:15 n_seed=17 TP0S=`seq 2000 100 2900`;nohup loocv-bat.sh & 
#(2-0)
##Nの設定
export n_seed=50 Sth=0.5 phase="" TP0="2000"  
export ID="${n_seed}" #export ID=ID"${n_seed}-${Sth:2}" 
export N=N:50 L=2
#export L=2 N="N:50_N:100" n_seed="25_50"
export L=2 N="N:50,75,100" n_seed="33"
export N=N:50,60,70,80,90,100 n_seed=17 
export N=N:50-100:10 n_seed=17 
export N=N:50-100:5 n_seed=9
export N=N:50-150:20 n_seed=17 
export N=N:50-200:30 n_seed=17 
#(2-1)&(2-2)
date >> $d0/cmd-io-sum.dat
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -phase "$phase" -ID "$ID"
source $d0/d1.env #d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1-5
echo "#saved in d1=$d1"         >> $d0/cmd-io-sum.dat
tail -2 $d1/cmd.sh >> $d0/cmd-io-sum.dat
cp $d1/cmd.out $d1/cmd-Sth${Sth:2}.out
export LANG=C;DATE=`date`;echo "#$DATE TP0=$TP0 $N ns=$n_seed ==>(hV,hg)=(,)" >> $d0/cmd-io-sum.dat
grep "hi-LOOCV@L0c\|hi-LOOCV@L2c\|h(yi,yg)@L2c\|h(yi,yg)@L0c" $d1/cmd.out |sort >> $d0/cmd-io-sum.dat
tail -11 $d0/cmd-io-sum.dat
####################カット＆ペーストここまで
N:50-300:40 n_seed=17
#export t0=50 td=40 t1=300; seq 50 40 300 ;seq 2000 100 300
export N=N:50-300:30 n_seed=17;export TP0S=2000;nohup loocv-bat.sh &
export N=N:50-200:30 n_seed=17;export TP0S=2000;nohup loocv-bat.sh &
export L=2 N=N:50-200:20 n_seed=17 TP0S=`seq 2300 100 2900`;nohup loocv-bat.sh & 
#emacs ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/cmd-io-sum.dat
export L=2 N=N:50-100:10 n_seed=17 TP0S=`seq 2300 100 2900`;nohup loocv-bat.sh & 
export L=2 N=N:5-300:5 n_seed=1 TP0S=`seq 2500 100 2900` ID=can2m1 ;nohup loocv-bat.sh & #

export L=2 N=N:50-100:5  n_seed=10 TP0S=`seq 2000 100 2900` ID=can2m ;nohup loocv-bat.sh & #finish
export L=2 N=N:50-100:10 n_seed=20 TP0S=`seq 2000 100 2900` ID=can2m1 ;nohup loocv-bat.sh & #executing
export L=2 N=N:50-200:30 n_seed=20 TP0S=`seq 2000 100 2900` ID=can2m2-2 ;nohup loocv-bat.sh & #executing
#Fri Jun 12 20:10:45 JST 2020 TP0=2900 N:50-200:30 ns=20 ==>(hV,hg)=(218,308) 212
export L=2 N=N:50-100:10 n_seed=15 TP0S=`seq 2000 100 2900` ID=can2m-2 ;nohup loocv-bat.sh & #executing
#For result, see emacs ~/sotu/2019/result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/cmd-io-sum.dat
source init.sh
d0=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/

export L=2 N=N:50-200:30 ns=15 TP0S=`seq 2000 100 2900` ID=can2m3 ;nohup loocv-bat.sh & #executing
export L=2 N=N:50-200:30 ns=15 TP0S=`seq 2000 100 2000` ID=" ";nohup loocv-bat.sh & #executing

../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2000-2500k10N:50-200:30ns17
#result20200612
#N:50-140:30 ns=17 223.2(L2) 188.2(L0)
#N:50-200:30 ns=17 244.6(L2)*176.2(L0) ***L2 adequate N1-N2:NDiv ns for L2 best
#N:50-200:30 ns=20 223.6(L2) 207.9(L0) around ***
#N:50-200:30 ns=15 220.8(L2) 211.8(L0) around ***
#N:50-300:30 ns=17 181.4(L2),184.8(L0)
#N:50-200:20 ns=17 209.3(L2) 203.7(L0)
#N:50-100:20 ns=17 179.7(L2) 187.9(L0)
#N:50-100:15 ns=17 214.5(L2) 231.8(L0)
#N:50-100:12 ns=17 225.8(L2) 226.8(L0)
#N:50-100:10 ns=17 212.7(L2) 234.6(L0)***
#N:50-100:10 ns=20 189.4(L2) 194.0(L0) can2m1 around ***
#N:50-100:10 ns=15 199.3(L2) 225.4(L0) can2m-2 around ***
#N:50-80:10  ns=17 177.7(L2) 202.2(L0) 
#N:50-100:5  ns=10 178.7(L2) 166.7(L0) 
#N:5-300:5 ns=1    177.2(L2) 169.0(L0) original
N:50-100:10 ns=20 can2m1

#N:50,60,70,80,90,100 ns=17 200.3(L2) 251.2(L0;best*)
#N:50,62,75,87,100 ns=20  floor(50+1.25*i) 236.2(L2best) 234.6(L0)

##############best L2
#N:50-200:30 ns=17 244.6(L2 best) 176.2(L0) ### best L2
#Thu Jun 11 16:42:45 JST 2020 TP0=2000 N:50-200:30 ns=17 ==>(hV,hg)=(194,414) 194L0
#Thu Jun 11 16:52:52 JST 2020 TP0=2100 N:50-200:30 ns=17 ==>(hV,hg)=(269,321) 92L0
#Thu Jun 11 17:02:58 JST 2020 TP0=2200 N:50-200:30 ns=17 ==>(hV,hg)=(269,371) 92L0
#Thu Jun 11 17:13:03 JST 2020 TP0=2300 N:50-200:30 ns=17 ==>(hV,hg)=(186,273) 189L0
#Thu Jun 11 16:20:30 JST 2020 TP0=2400 N:50-200:30 ns=17 ==>(hV,hg)=(288,448) 231L0
#Thu Jun 11 16:30:38 JST 2020 TP0=2500 N:50-200:30 ns=17 ==>(hV,hg)=(286,376) 148L0
#Thu Jun 11 17:24:55 JST 2020 TP0=2600 N:50-200:30 ns=17 ==>(hV,hg)=(184,227) 184L0
#Thu Jun 11 17:35:04 JST 2020 TP0=2700 N:50-200:30 ns=17 ==>(hV,hg)=(270,387) 270L0
#Thu Jun 11 17:45:14 JST 2020 TP0=2800 N:50-200:30 ns=17 ==>(hV,hg)=(286,349) 286L0
#Thu Jun 11 17:55:21 JST 2020 TP0=2900 N:50-200:30 ns=17 ==>(hV,hg)=(214,308) 76L0
print (194+269+269+186+288+286+184+270+286+214)/10., 244.6
print (194+92+92+189+231+148+184+270+286+76)/10.,176.2
##############
#N:50-100:10 ns=17 212.7(L2) 234.6(L0) ### best L0
#Fri Jun 12 13:02:30 JST 2020 TP0=2000 N:50-100:10 ns=17 ==>(hV,hg)=(157,414) 187
#Fri Jun 12 13:09:11 JST 2020 TP0=2100 N:50-100:10 ns=17 ==>(hV,hg)=(100,357) 92
#Fri Jun 12 13:16:09 JST 2020 TP0=2200 N:50-100:10 ns=17 ==>(hV,hg)=(267,371) 316
#Fri Jun 12 13:22:57 JST 2020 TP0=2300 N:50-100:10 ns=17 ==>(hV,hg)=(190,361) 190
#Fri Jun 12 13:29:37 JST 2020 TP0=2400 N:50-100:10 ns=17 ==>(hV,hg)=(202,354) 350
#Fri Jun 12 13:36:18 JST 2020 TP0=2500 N:50-100:10 ns=17 ==>(hV,hg)=(284,346) 284
#Fri Jun 12 13:42:57 JST 2020 TP0=2600 N:50-100:10 ns=17 ==>(hV,hg)=(185,308) 185
#Fri Jun 12 13:49:39 JST 2020 TP0=2700 N:50-100:10 ns=17 ==>(hV,hg)=(270,273) 270
#Fri Jun 12 13:56:19 JST 2020 TP0=2800 N:50-100:10 ns=17 ==>(hV,hg)=(257,374) 257
#Fri Jun 12 14:02:59 JST 2020 TP0=2900 N:50-100:10 ns=17 ==>(hV,hg)=(215,492) 215
print (157+100+267+190+202+284+185+270+257+215)/10.,(187+92+316+190+350+284+185+270+257+215)/10.,212.7, 234.6

export L=2 N=N:50-200:30 n_seed=15 TP0S="2300" ID=can2m ;nohup loocv-bat.sh & #executing
#N:50-200:30 ns=15 220.8(L2) 211.8(L0) can2m3
#Fri Jun 12 18:36:50 JST 2020 TP0=2000 N:50-200:30 ns=15 ==>(hV,hg)=(189,414) 191
#Fri Jun 12 18:46:13 JST 2020 TP0=2100 N:50-200:30 ns=15 ==>(hV,hg)=(92,321) 93
#Fri Jun 12 18:55:55 JST 2020 TP0=2200 N:50-200:30 ns=15 ==>(hV,hg)=(186,362) 186
#Fri Jun 12 22:36:27 JST 2020 TP0=2300 N:50-200:30 ns=15 ==>(hV,hg)=(186,273) 189  can2m1 check L0
#Fri Jun 12 19:14:36 JST 2020 TP0=2400 N:50-200:30 ns=15 ==>(hV,hg)=(288,448) 231
#Fri Jun 12 19:24:01 JST 2020 TP0=2500 N:50-200:30 ns=15 ==>(hV,hg)=(286,376) 249
#Fri Jun 12 19:33:51 JST 2020 TP0=2600 N:50-200:30 ns=15 ==>(hV,hg)=(211,338) 211
#Fri Jun 12 19:43:00 JST 2020 TP0=2700 N:50-200:30 ns=15 ==>(hV,hg)=(270,387)270
#Fri Jun 12 19:52:12 JST 2020 TP0=2800 N:50-200:30 ns=15 ==>(hV,hg)=(286,349) 286
#Fri Jun 12 22:16:05 JST 2020 TP0=2900 N:50-200:30 ns=15 ==>(hV,hg)=(214,308) 212 can2m1 check L0
print (189+92+186+186+288+286+211+270+286+214)/10.,(191+93+186+189+231+249+211+270+286+212)/10.,220.8 211.8

export L=2 N=N:50-100:10 n_seed=15 TP0S="2600 2700 2800" ID=can2m ;nohup loocv-bat.sh & #executing
#N:50-100:10 ns=15 199.3(L2) 225.4(L0) can2m-2
#Fri Jun 12 18:32:28 JST 2020 TP0=2000 N:50-100:10 ns=15 ==>(hV,hg)=(157,414) 187
#Fri Jun 12 18:38:33 JST 2020 TP0=2100 N:50-100:10 ns=15 ==>(hV,hg)=(99,291) 205
#Fri Jun 12 18:44:45 JST 2020 TP0=2200 N:50-100:10 ns=15 ==>(hV,hg)=(166,371) 166
#Fri Jun 12 18:50:48 JST 2020 TP0=2300 N:50-100:10 ns=15 ==>(hV,hg)=(191,361) 168
#Fri Jun 12 18:56:56 JST 2020 TP0=2400 N:50-100:10 ns=15 ==>(hV,hg)=(202,351) 350
#Fri Jun 12 19:03:22 JST 2020 TP0=2500 N:50-100:10 ns=15 ==>(hV,hg)=(249,346) 249
#Fri Jun 12 22:13:01 JST 2020 TP0=2600 N:50-100:10 ns=15 ==>(hV,hg)=(185,308) 185 can2m
#Fri Jun 12 22:19:24 JST 2020 TP0=2700 N:50-100:10 ns=15 ==>(hV,hg)=(270,273) 270 can2m
#Fri Jun 12 22:25:21 JST 2020 TP0=2800 N:50-100:10 ns=15 ==>(hV,hg)=(259,374) 259 can2m
#Fri Jun 12 19:28:36 JST 2020 TP0=2900 N:50-100:10 ns=15 ==>(hV,hg)=(215,492) 215
print (157+99+166+191+202+249+185+270+259+215)/10.,(187+205+166+168+350+249+185+270+259+215)/10.,199.3 225.4

export L=2 N=N:50-200:30 n_seed=20 TP0S="2200 2300 2400 2600 2800 2900" ID=can2m ;nohup loocv-bat.sh & #executing
#N:50-200:30 n_seed=20 223.6(L2) 207.9(L0) can2m2-2
#Fri Jun 12 18:18:12 JST 2020 TP0=2000 N:50-200:30 ns=20 ==>(hV,hg)=(191,414) 194
#Fri Jun 12 18:30:27 JST 2020 TP0=2100 N:50-200:30 ns=20 ==>(hV,hg)=(92,321)   92
#Fri Jun 12 20:50:01 JST 2020 TP0=2200 N:50-200:30 ns=20 ==>(hV,hg)=(166,371) 166 can2m
#Fri Jun 12 21:02:03 JST 2020 TP0=2300 N:50-200:30 ns=20 ==>(hV,hg)=(186,362) 189 can2m
#Fri Jun 12 21:14:12 JST 2020 TP0=2400 N:50-200:30 ns=20 ==>(hV,hg)=(288,448) 237 can2m
#Fri Jun 12 19:21:11 JST 2020 TP0=2500 N:50-200:30 ns=20 ==>(hV,hg)=(355,376) 249
#Fri Jun 12 21:26:28 JST 2020 TP0=2600 N:50-200:30 ns=20 ==>(hV,hg)=(184,338) 184 can2m
#Fri Jun 12 19:46:19 JST 2020 TP0=2700 N:50-200:30 ns=20 ==>(hV,hg)=(270,387) 270
#Fri Jun 12 21:38:56 JST 2020 TP0=2800 N:50-200:30 ns=20 ==>(hV,hg)=(286,379) 286 can2m
#Fri Jun 12 21:51:12 JST 2020 TP0=2900 N:50-200:30 ns=20 ==>(hV,hg)=(218,308) 212 can2m
print (191+92+166+186+288+355+184+270+286+218)/10.,(194+92+166+189+237+249+184+270+286+212)/10.,223.6 207.9




#N:50-100:10 ns=20 189.4(L2) 194.0(L0) can2m1
#Fri Jun 12 17:46:02 JST 2020 TP0=2000 N:50-100:10 ns=20 ==>(hV,hg)=(169,414) 169
#Fri Jun 12 17:54:41 JST 2020 TP0=2100 N:50-100:10 ns=20 ==>(hV,hg)=(191,414) 194
#Fri Jun 12 18:02:45 JST 2020 TP0=2200 N:50-100:10 ns=20 ==>(hV,hg)=(166,371) 166
#Fri Jun 12 18:10:39 JST 2020 TP0=2300 N:50-100:10 ns=20 ==>(hV,hg)=(191,362) 168
#Fri Jun 12 18:18:38 JST 2020 TP0=2400 N:50-100:10 ns=20 ==>(hV,hg)=(202,354) 237
#Fri Jun 12 19:15:56 JST 2020 TP0=2500 N:50-100:10 ns=20 ==>(hV,hg)=(173,273) 173 ???
#Fri Jun 12 18:34:45 JST 2020 TP0=2600 N:50-100:10 ns=20 ==>(hV,hg)=(154,337) 185
#Fri Jun 12 18:43:29 JST 2020 TP0=2700 N:50-100:10 ns=20 ==>(hV,hg)=(174,300) 174
#Fri Jun 12 18:51:45 JST 2020 TP0=2800 N:50-100:10 ns=20 ==>(hV,hg)=(259,378) 259
#Fri Jun 12 18:59:55 JST 2020 TP0=2900 N:50-100:10 ns=20 ==>(hV,hg)=(215,492) 215
print (169+191+166+191+202+173+154+174+259+215)/10., (169+194+166+168+237+173+185+174+259+215)/10.,189.4 194.0


#N:50-100:5 ns=10 178.7(L2) 166.7(L0) can2m
#Fri Jun 12 16:40:06 JST 2020 TP0=2000 N:50-100:5 ns=10 ==>(hV,hg)=(157,359) 157
#Fri Jun 12 16:47:22 JST 2020 TP0=2100 N:50-100:5 ns=10 ==>(hV,hg)=(99,353) 205
#Fri Jun 12 16:54:50 JST 2020 TP0=2200 N:50-100:5 ns=10 ==>(hV,hg)=(166,289) 166
#Fri Jun 12 17:02:12 JST 2020 TP0=2300 N:50-100:5 ns=10 ==>(hV,hg)=(188,395) 168
#Fri Jun 12 17:17:23 JST 2020 TP0=2500 N:50-100:5 ns=10 ==>(hV,hg)=(284,348) 284
#Fri Jun 12 17:24:42 JST 2020 TP0=2600 N:50-100:5 ns=10 ==>(hV,hg)=(153,308) 153
#Fri Jun 12 17:32:14 JST 2020 TP0=2700 N:50-100:5 ns=10 ==>(hV,hg)=(270,416) 270
#Fri Jun 12 17:39:29 JST 2020 TP0=2800 N:50-100:5 ns=10 ==>(hV,hg)=(259,446) 259
#Fri Jun 12 17:46:49 JST 2020 TP0=2900 N:50-100:5 ns=10 ==>(hV,hg)=(211,492) 213
print (157+99+166+188+284+153+270+259+211)/10., (157+2-5+166+168+284+153+270+259+213)/10.,178.7 166.7

#N:50-80:10 ns=17 177.7(L2) 202.2(L0) can2m2
#Fri Jun 12 16:53:23 JST 2020 TP0=2000 N:50-80:10 ns=17 ==>(hV,hg)=(157,414) 157
#Fri Jun 12 16:57:33 JST 2020 TP0=2100 N:50-80:10 ns=17 ==>(hV,hg)=(176,291) 258
#Fri Jun 12 17:01:38 JST 2020 TP0=2200 N:50-80:10 ns=17 ==>(hV,hg)=(166,371) 166
#Fri Jun 12 17:05:45 JST 2020 TP0=2300 N:50-80:10 ns=17 ==>(hV,hg)=(191,361) 190
#Fri Jun 12 17:10:09 JST 2020 TP0=2400 N:50-80:10 ns=17 ==>(hV,hg)=(61,351) 230
#Fri Jun 12 17:14:13 JST 2020 TP0=2500 N:50-80:10 ns=17 ==>(hV,hg)=(252,346) 252
#Fri Jun 12 17:18:14 JST 2020 TP0=2600 N:50-80:10 ns=17 ==>(hV,hg)=(154,277) 154
#Fri Jun 12 17:22:18 JST 2020 TP0=2700 N:50-80:10 ns=17 ==>(hV,hg)=(175,273) 175
#Fri Jun 12 17:26:18 JST 2020 TP0=2800 N:50-80:10 ns=17 ==>(hV,hg)=(257,374) 231
#Fri Jun 12 17:30:21 JST 2020 TP0=2900 N:50-80:10 ns=17 ==>(hV,hg)=(188,310) 209
print (157+176+166+191+61+252+154+175+257+188)/10., (157+258+166+190+230+252+154+175+231+209)/10.,177.7 202.2

#N:5-300:5 ns=1 can2m1 177.2(L2) 169.0(L0)
#Fri Jun 12 15:48:08 JST 2020 TP0=2000 N:5-300:5 ns=1 ==>(hV,hg)=(191,395) 191
#Fri Jun 12 15:56:32 JST 2020 TP0=2100 N:5-300:5 ns=1 ==>(hV,hg)=(91,321) 91
#Fri Jun 12 16:04:31 JST 2020 TP0=2200 N:5-300:5 ns=1 ==>(hV,hg)=(190,422) 187
#Fri Jun 12 16:12:05 JST 2020 TP0=2300 N:5-300:5 ns=1 ==>(hV,hg)=(66,202) 66
#Fri Jun 12 16:19:14 JST 2020 TP0=2400 N:5-300:5 ns=1 ==>(hV,hg)=(225,354) 225
#Fri Jun 12 16:39:48 JST 2020 TP0=2500 N:5-300:5 ns=1 ==>(hV,hg)=(246,312) 246
#Fri Jun 12 16:47:03 JST 2020 TP0=2600 N:5-300:5 ns=1 ==>(hV,hg)=(148,247) 148
#Fri Jun 12 16:54:25 JST 2020 TP0=2700 N:5-300:5 ns=1 ==>(hV,hg)=(147,275) 147
#Fri Jun 12 17:01:47 JST 2020 TP0=2800 N:5-300:5 ns=1 ==>(hV,hg)=(256,256) 175
#Fri Jun 12 17:09:12 JST 2020 TP0=2900 N:5-300:5 ns=1 ==>(hV,hg)=(212,331) 214
print (191+91+190+66+225+246+148+147+256+212)/10.,(191+91+187+66+225+246+148+147+175+214)/10.,177.2 169.0

#N:50-100:15 ns=17 214.5(L2) 231.8(L0)
#Fri Jun 12 14:52:52 JST 2020 TP0=2000 N:50-100:15 ns=17 ==>(hV,hg)=(157,422) 217
#Fri Jun 12 14:57:15 JST 2020 TP0=2100 N:50-100:15 ns=17 ==>(hV,hg)=(99,353) 233
#Fri Jun 12 15:01:39 JST 2020 TP0=2200 N:50-100:15 ns=17 ==>(hV,hg)=(371,371) 371
#Fri Jun 12 15:06:05 JST 2020 TP0=2300 N:50-100:15 ns=17 ==>(hV,hg)=(188,301) 167
#Fri Jun 12 15:10:25 JST 2020 TP0=2400 N:50-100:15 ns=17 ==>(hV,hg)=(237,351) 238
#Fri Jun 12 15:14:46 JST 2020 TP0=2500 N:50-100:15 ns=17 ==>(hV,hg)=(253,286) 253
#Fri Jun 12 15:19:09 JST 2020 TP0=2600 N:50-100:15 ns=17 ==>(hV,hg)=(185,308) 185
#Fri Jun 12 15:23:34 JST 2020 TP0=2700 N:50-100:15 ns=17 ==>(hV,hg)=(270,387) 270
#Fri Jun 12 15:27:56 JST 2020 TP0=2800 N:50-100:15 ns=17 ==>(hV,hg)=(170,349) 170
#Fri Jun 12 15:32:22 JST 2020 TP0=2900 N:50-100:15 ns=17 ==>(hV,hg)=(215,342) 214
print (157+99+371+188+237+253+185+270+170+215)/10.,(217+233+371+167+238+253+185+270+170+214)/10.,214.5, 231.8
#N:50-100:12 ns=17 225.8(L2) 226.8(L0)
#Fri Jun 12 14:53:16 JST 2020 TP0=2000 N:50-100:12 ns=17 ==>(hV,hg)=(304,336) 220
#Fri Jun 12 14:58:49 JST 2020 TP0=2100 N:50-100:12 ns=17 ==>(hV,hg)=(262,323) 262
#Fri Jun 12 15:04:23 JST 2020 TP0=2200 N:50-100:12 ns=17 ==>(hV,hg)=(192,316) 192
#Fri Jun 12 15:09:58 JST 2020 TP0=2300 N:50-100:12 ns=17 ==>(hV,hg)=(179,246) 245
#Fri Jun 12 15:15:27 JST 2020 TP0=2400 N:50-100:12 ns=17 ==>(hV,hg)=(203,498) 233
#Fri Jun 12 15:20:59 JST 2020 TP0=2500 N:50-100:12 ns=17 ==>(hV,hg)=(247,310) 247
#Fri Jun 12 15:26:35 JST 2020 TP0=2600 N:50-100:12 ns=17 ==>(hV,hg)=(183,277) 183
#Fri Jun 12 15:32:18 JST 2020 TP0=2700 N:50-100:12 ns=17 ==>(hV,hg)=(215,342) 214
#Fri Jun 12 15:37:51 JST 2020 TP0=2800 N:50-100:12 ns=17 ==>(hV,hg)=(256,349) 256
#Fri Jun 12 15:43:23 JST 2020 TP0=2900 N:50-100:12 ns=17 ==>(hV,hg)=(217,309) 216
print (304+262+192+179+203+247+183+215+256+217)/10.,(220+262+192+245+233+247+183+214+256+216)/10.,225.8 226.8

#N:50-100:20 ns=17 179.7(L2) 187.9(L0)
#Fri Jun 12 14:36:39 JST 2020 TP0=2000 N:50-100:20 ns=17 ==>(hV,hg)=(157,295) 187
#Fri Jun 12 14:39:51 JST 2020 TP0=2100 N:50-100:20 ns=17 ==>(hV,hg)=(98,268) 203
#Fri Jun 12 14:42:59 JST 2020 TP0=2200 N:50-100:20 ns=17 ==>(hV,hg)=(166,316) 166
#Fri Jun 12 13:02:58 JST 2020 TP0=2300 N:50-100:20 ns=17 ==>(hV,hg)=(168,245) 66
#Fri Jun 12 13:06:08 JST 2020 TP0=2400 N:50-100:20 ns=17 ==>(hV,hg)=(290,354) 290
#Fri Jun 12 13:09:20 JST 2020 TP0=2500 N:50-100:20 ns=17 ==>(hV,hg)=(251,346) 251
#Fri Jun 12 13:12:30 JST 2020 TP0=2600 N:50-100:20 ns=17 ==>(hV,hg)=(185,277) 185
#Fri Jun 12 13:16:05 JST 2020 TP0=2700 N:50-100:20 ns=17 ==>(hV,hg)=(267,371) 316
#Fri Jun 12 13:22:28 JST 2020 TP0=2900 N:50-100:20 ns=17 ==>(hV,hg)=(215,492) 215
print (157+98+166+168+290+251+185+267+215)/10.,(187+203+166+66+290+251+185+316+215)/10.,179.7, 187.9


#N:50-200:20 ns=17 209.3(L2) 203.7(L0)
#Fri Jun 12 08:19:50 JST 2020 TP0=2000 N:50-200:20 ns=17 ==>(hV,hg)=(189,391) 187L0
#Fri Jun 12 08:32:57 JST 2020 TP0=2100 N:50-200:20 ns=17 ==>(hV,hg)=(92,321) 93L0
#Fri Jun 12 08:46:18 JST 2020 TP0=2200 N:50-200:20 ns=17 ==>(hV,hg)=(166,316) 166L0
#Fri Jun 12 11:19:01 JST 2020 TP0=2300 N:50-200:20 ns=17 ==>(hV,hg)=(189,245) 190
#Fri Jun 12 11:32:28 JST 2020 TP0=2400 N:50-200:20 ns=17 ==>(hV,hg)=(201,475) 234
#Fri Jun 12 11:46:07 JST 2020 TP0=2500 N:50-200:20 ns=17 ==>(hV,hg)=(247,376) 247
#Fri Jun 12 11:59:50 JST 2020 TP0=2600 N:50-200:20 ns=17 ==>(hV,hg)=(184,290) 184
#Fri Jun 12 12:12:58 JST 2020 TP0=2700 N:50-200:20 ns=17 ==>(hV,hg)=(265,356) 265
#Fri Jun 12 12:26:08 JST 2020 TP0=2800 N:50-200:20 ns=17 ==>(hV,hg)=(348,350) 259
#Fri Jun 12 12:39:11 JST 2020 TP0=2900 N:50-200:20 ns=17 ==>(hV,hg)=(212,492) 212
print (189+92+166+189+201+247+184+265+348+212)/10.,(187+93+166+190+234+247+184+265+259+212)/10.,209.3 203.7

#N:50-300:30 ns=17 181.4(L2),184.8(L0)
#Fri Jun 12 00:50:43 JST 2020 TP0=2000 N:50-300:30 ns=17 ==>(hV,hg)=(194,414) 140L0
#Fri Jun 12 01:10:44 JST 2020 TP0=2100 N:50-300:30 ns=17 ==>(hV,hg)=(92,322) 93L0
#Fri Jun 12 01:30:59 JST 2020 TP0=2200 N:50-300:30 ns=17 ==>(hV,hg)=(166,371) 166L0
#Fri Jun 12 01:50:55 JST 2020 TP0=2300 N:50-300:30 ns=17 ==>(hV,hg)=(67,273) 68L0
#Fri Jun 12 02:11:02 JST 2020 TP0=2400 N:50-300:30 ns=17 ==>(hV,hg)=(345,448) 309L0
#Fri Jun 12 02:31:06 JST 2020 TP0=2500 N:50-300:30 ns=17 ==>(hV,hg)=(247,376) 248L0
#Fri Jun 12 02:51:19 JST 2020 TP0=2600 N:50-300:30 ns=17 ==>(hV,hg)=(185,277) 185L0
#Fri Jun 12 03:11:28 JST 2020 TP0=2700 N:50-300:30 ns=17 ==>(hV,hg)=(149,387) 270L0
#Fri Jun 12 03:31:35 JST 2020 TP0=2800 N:50-300:30 ns=17 ==>(hV,hg)=(175,349) 175L0
#Fri Jun 12 07:58:18 JST 2020 TP0=2900 N:50-300:30 ns=17 ==>(hV,hg)=(194,414) 194L0
print (194+92+166+67+345+247+185+149+175+194)/10.,181.4
print (140++93+166+68+309+248+185+270+175+194)/10.,184.8

#N:50-140:30 ns=17 223.2(L2) 188.2(L0)
export L=2 N=N:50-140:30 n_seed=17 TP0S=2000;nohup loocv-bat.sh & 223.2(L2) 188.2(L0)
#Thu Jun 11 20:46:34 JST 2020 TP0=2000 N:50-140:30 ns=17 ==>(hV,hg)=(217,414) 189L0
#Thu Jun 11 20:57:57 JST 2020 TP0=2100 N:50-140:30 ns=17 ==>(hV,hg)=(176,291) 93L0
#Thu Jun 11 21:03:24 JST 2020 TP0=2200 N:50-140:30 ns=17 ==>(hV,hg)=(371,371) 371L0
#Thu Jun 11 21:08:51 JST 2020 TP0=2300 N:50-140:30 ns=17 ==>(hV,hg)=(191,273) 191L0
#Thu Jun 11 21:14:18 JST 2020 TP0=2400 N:50-140:30 ns=17 ==>(hV,hg)=(231,351) 231L0
#Thu Jun 11 21:19:46 JST 2020 TP0=2500 N:50-140:30 ns=17 ==>(hV,hg)=(286,376) 249L0
#Thu Jun 11 21:25:14 JST 2020 TP0=2600 N:50-140:30 ns=17 ==>(hV,hg)=(184,277) 184L0
#Thu Jun 11 21:36:10 JST 2020 TP0=2700 N:50-140:30 ns=17 ==>(hV,hg)=(189,414) 191L0
#Thu Jun 11 21:36:10 JST 2020 TP0=2800 N:50-140:30 ns=17 ==>(hV,hg)=(170,349) 170L0
#Thu Jun 11 21:41:36 JST 2020 TP0=2900 N:50-140:30 ns=17 ==>(hV,hg)=(217,308) 213L0
print (217+176+371+191+231+286+184+189+170+217)/10.,223.2
print (189+93+171+191+231+249+184+191+170+213)/10.,188.2

#Thu Jun 11 20:30:43 JST 2020 TP0=2000 N:50-200:30 ns=15 ==>(hV,hg)=(189,414) 191L0
#Thu Jun 11 18:50:03 JST 2020 TP0=2000 N:50-200:30 ns=20 ==>(hV,hg)=(191,414) 194L0
#Thu Jun 11 16:42:45 JST 2020 TP0=2000 N:50-200:30 ns=17 ==>(hV,hg)=(194,414) 194L0
#Thu Jun 11 18:33:34 JST 2020 TP0=2000 N:50-300:30 ns=17 ==>(hV,hg)=(194,414) 194L0 == N:50-200:30
#Thu Jun 11 20:46:34 JST 2020 TP0=2000 N:50-140:30 ns=17 ==>(hV,hg)=(217,414) 189L0

#N:50-150:20 n_seed=17
#Thu Jun 11 14:20:11 JST 2020 TP0=2000 N:50-150:20 ns=17 ==>(hV,hg)=(110,391) 187L0
#Thu Jun 11 14:34:17 JST 2020 TP0=2100 N:50-150:20 ns=17 ==>(hV,hg)=(233,278) 93L0
#Thu Jun 11 14:46:48 JST 2020 TP0=2200 N:50-150:20 ns=17 ==>(hV,hg)=(166,316) 166L0
#Thu Jun 11 15:47:50 JST 2020 TP0=2300 N:50-150:20 ns=17 ==>(hV,hg)=(189,245) 190L0


#N:50,60,70,80,90,100 ns=17 200.3(L2) 251.2(L0;best*)
#Thu Jun 11 02:00:27 JST 2020 TP0=2000 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(157,414) 187L0
#Thu Jun 11 02:07:11 JST 2020 TP0=2100 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(100,357) 258L0
#Thu Jun 11 07:46:00 JST 2020 TP0=2200 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(267,371) 316L0
#Thu Jun 11 07:54:31 JST 2020 TP0=2300 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(191,361) 190L0
#Thu Jun 11 08:02:44 JST 2020 TP0=2400 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(202,354) 350L0
#Thu Jun 11 08:11:15 JST 2020 TP0=2500 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(159,346) 284L0
#Thu Jun 11 08:19:22 JST 2020 TP0=2600 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(185,308) 185L0
#Thu Jun 11 08:30:18 JST 2020 TP0=2700 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(270,273) 270L0
#Thu Jun 11 08:50:18 JST 2020 TP0=2800 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(257,374) 257L0
#Thu Jun 11 09:01:23 JST 2020 TP0=2900 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(215,492) 215L0
print (157+100+267+191+202+159+185+270+257++215)/10.,200.3
print (187+258+316+190+350+284+185+270+257+215)/10.,251.2
#Thu Jun 11 09:13:42 JST 2020 TP0=2000 N:50,60,70,80,90,100 ns=20 ==>(hV,hg)=(169,414) 172L0
#Thu Jun 11 10:09:40 JST 2020 TP0=2100 N:50,60,70,80,90,100 ns=20 ==>(hV,hg)=(100,357) 258L0
#Thu Jun 11 15:47:50 JST 2020 TP0=2300 N:50-150:20 ns=17 ==>(hV,hg)=(189,245) 190L0

##N:50,62,75,87,100 ns=20  floor(50+1.25*i) 236.2@L2(best) 234.6@L0
#Thu Jun 11 00:24:35 JST 2020 TP0=2000 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(221,336) 222L0
#Thu Jun 11 00:32:54 JST 2020 TP0=2100 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(262,357) 262L0
#Thu Jun 11 00:45:03 JST 2020 TP0=2200 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(267,316) 267L0
#Thu Jun 11 00:53:32 JST 2020 TP0=2300 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(167,362) 245L0
#Thu Jun 11 01:03:59 JST 2020 TP0=2400 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(203,475) 232L0
#Thu Jun 11 01:12:12 JST 2020 TP0=2500 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(286,355) 286L0
#Thu Jun 11 01:20:25 JST 2020 TP0=2600 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(183,308) 184L0
#Thu Jun 11 01:28:27 JST 2020 TP0=2700 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(174,355) 174L0
#Thu Jun 11 01:37:42 JST 2020 TP0=2800 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(409,470) 259L0
#Thu Jun 11 01:47:21 JST 2020 TP0=2900 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(190,370) 216L0
print (221+262+267+167+203+286+183+174+409+190)/10.,236.2 L2
print (221+262+267+245+232+286+184+174+259+216)/10.,234.6 L0

#N:50-100:5 ns=10 198.8(L2) 207.6(L0)
#n_L2ci のmax と　2ndmax 差がちいさい
#Thu Jun 11 12:20:18 JST 2020 TP0=2000 N:50-100:5 ns=10 ==>(hV,hg)=(157,359) 187L0
#Thu Jun 11 12:40:28 JST 2020 TP0=2100 N:50-100:5 ns=10 ==>(hV,hg)=(99,353) 205L0
#Thu Jun 11 12:52:07 JST 2020 TP0=2200 N:50-100:5 ns=10 ==>(hV,hg)=(166,289) 166L0　#n_L2ci のmax と　2ndmax 差が小さい
#Thu Jun 11 13:10:15 JST 2020 TP0=2300 N:50-100:5 ns=10 ==>(hV,hg)=(188,395) 168L0
#Thu Jun 11 13:19:58 JST 2020 TP0=2400 N:50-100:5 ns=10 ==>(hV,hg)=(201,345) 290L0
#Thu Jun 11 13:28:14 JST 2020 TP0=2500 N:50-100:5 ns=10 ==>(hV,hg)=(284,346) 286L0
#Thu Jun 11 13:39:05 JST 2020 TP0=2600 N:50-100:5 ns=10 ==>(hV,hg)=(153,308) 153L0
#Thu Jun 11 13:47:34 JST 2020 TP0=2700 N:50-100:5 ns=10 ==>(hV,hg)=(270,416) 270L0
#Thu Jun 11 13:56:01 JST 2020 TP0=2800 N:50-100:5 ns=10 ==>(hV,hg)=(259,446) 259L0
#Thu Jun 11 14:04:21 JST 2020 TP0=2900 N:50-100:5 ns=10 ==>(hV,hg)=(211,492) 192L0
print (157+99+166+188+201+284+153+270+259+211)/10.,198.8
print (187+205+166+168+290+286+53+270+259+192)/10.,207.6

#N:50,75,100 ns=33 ==> 217.0 best2 so far
#Wed Jun 10 17:42:33 JST 2020 TP0=2000 N:50,75,100 ns=33 ==>(hV,hg)=(332,333)
#Wed Jun 10 17:50:29 JST 2020 TP0=2100 N:50,75,100 ns=33 ==>(hV,hg)=(205,359)
#Wed Jun 10 18:02:54 JST 2020 TP0=2200 N:50,75,100 ns=33 ==>(hV,hg)=(193,316) 267L0
#Wed Jun 10 18:48:06 JST 2020 TP0=2300 N:50,75,100 ns=33 ==>(hV,hg)=(188,362) 167L0 xxx
#Wed Jun 10 18:57:00 JST 2020 TP0=2400 N:50,75,100 ns=33 ==>(hV,hg)=(203,355) 220L0
#Wed Jun 10 19:06:04 JST 2020 TP0=2500 N:50,75,100 ns=33 ==>(hV,hg)=(282,355)
#Wed Jun 10 19:14:08 JST 2020 TP0=2600 N:50,75,100 ns=33 ==>(hV,hg)=(185,308)
#Wed Jun 10 19:21:41 JST 2020 TP0=2700 N:50,75,100 ns=33 ==>(hV,hg)=(175,355)
#Wed Jun 10 20:21:31 JST 2020 TP0=2800 N:50,75,100 ns=33 ==>(hV,hg)=(197,349)
#Wed Jun 10 20:32:15 JST 2020 TP0=2900 N:50,75,100 ns=33 ==>(hV,hg)=(210,370)
#bc.sh "(332+205+193+188+203+282+185+175+197+210)/10.",217.0

#N:50,100 ns=50 ==>214.0
#Wed Jun 10 16:21:24 JST 2020 TP0=2000 N:50,100 ns=50 ==>(hV,hg)=(219,332)
#Wed Jun 10 16:12:20 JST 2020 TP0=2100 N:50,100 ns=50 ==>(hV,hg)=(268,357)
#Wed Jun 10 16:31:28 JST 2020 TP0=2200 N:50,100 ns=50 ==>(hV,hg)=(267,430)
#Wed Jun 10 16:43:19 JST 2020 TP0=2300 N:50,100 ns=50 ==>(hV,hg)=(167,362)
#Wed Jun 10 16:50:59 JST 2020 TP0=2400 N:50,100 ns=50 ==>(hV,hg)=(202,355)
#Wed Jun 10 16:58:58 JST 2020 TP0=2500 N:50,100 ns=50 ==>(hV,hg)=(247,355)
#Wed Jun 10 17:06:47 JST 2020 TP0=2600 N:50,100 ns=50 ==>(hV,hg)=(185,310)
#Wed Jun 10 17:15:06 JST 2020 TP0=2700 N:50,100 ns=50 ==>(hV,hg)=(174,269)
#Wed Jun 10 17:22:59 JST 2020 TP0=2800 N:50,100 ns=50 ==>(hV,hg)=(198,349)
#Wed Jun 10 17:30:20 JST 2020 TP0=2900 N:50,100 ns=50 ==>(hV,hg)=(213,370)
#print (219+268+267+167+202+247+185+174+198+213)/10.,214.0

#N:50 ns=100 ==> 198 worse than ns=50
#Wed Jun 10 20:43:00 JST 2020 TP0=2000 N:50 ns=100 ==>(hV,hg)=(157,332)
#Wed Jun 10 20:53:18 JST 2020 TP0=2100 N:50 ns=100 ==>(hV,hg)=(233,268)
#Wed Jun 10 21:03:03 JST 2020 TP0=2200 N:50 ns=100 ==>(hV,hg)=(197,430)
#Wed Jun 10 21:14:03 JST 2020 TP0=2300 N:50 ns=100 ==>(hV,hg)=(167,362)
#Wed Jun 10 22:02:22 JST 2020 TP0=2400 N:50 ns=100 ==>(hV,hg)=(262,267)
#Wed Jun 10 22:26:06 JST 2020 TP0=2500 N:50 ns=100 ==>(hV,hg)=(251,355)
#Wed Jun 10 23:13:10 JST 2020 TP0=2600 N:50 ns=100 ==>(hV,hg)=(183,310)
#Wed Jun 10 23:21:14 JST 2020 TP0=2700 N:50 ns=100 ==>(hV,hg)=(175,448)
#Wed Jun 10 23:29:58 JST 2020 TP0=2800 N:50 ns=100 ==>(hV,hg)=(139,349) #better in L2,L0
#Wed Jun 10 23:43:31 JST 2020 TP0=2900 N:50 ns=100 ==>(hV,hg)=(218,309)
#bc.sh "(157+233+197+167+262+251+183+175+139+218)/10.",198

#### N:50 ==>=214.3
#                             tp0=2000 N:50 ns=50  ==>(hV,hg)=(304,332) ***
#                             tp0=2100 N:50 ns=50  ==>(hV,hg)=(257,268)
#                             tp0=2200 N:50 ns=50  ==>(hV,hg)=(194,430)
#                             tp0=2300 N:50 ns=50  ==>(hV,hg)=(167,362) 
#                             tp0=2400 N:50 ns=50  ==>(hV,hg)=(167,362)
#Tue Jun  9 11:36:47 JST 2020 TP0=2500 N:50 ns=50  ==> (hV,hg)=(283,355)
#Tue Jun  9 11:41:44 JST 2020 TP0=2600 N:50 ns=50  ==>(hV,hg)=(184,310)
#Tue Jun  9 16:12:56 JST 2020 TP0=2700 N:50 ns=50 ==>(hV,hg)=(175,267)
#Tue Jun  9 16:09:12 JST 2020 TP0=2800 N:50 ns=50 ==>(hV,hg)=(199,349) 275L0
#Tue Jun  9 17:22:38 JST 2020 TP0=2900 N:50 ns=50 ==>(hV,hg)=(213,249)
#Tue Jun  9 17:27:45 JST 2020 TP0=3000 N:50 ns=50 ==>(hV,hg)=(151,244)
print (304+257+194+167+167+283+184+175+199+213)/10.=214.3

#N:50_N:100 ns=25_50
#Wed Jun 10 11:49:00 JST 2020 TP0=2000 N:50_N:100 ns=25_50 ==>(hV,hg)=(219,332) ***?
#Wed Jun 10 14:57:57 JST 2020 TP0=2100 N:50_N:100 ns=25_50 ==>(hV,hg)=(93,357) xxx better in L2(304,332) ***
#Wed Jun 10 15:06:23 JST 2020 TP0=2200 N:50_N:100 ns=25_50 ==>(hV,hg)=(267,316)*sameinL0
#Wed Jun 10 15:17:16 JST 2020 TP0=2300 N:50_N:100 ns=25_50 ==>(hV,hg)=(188,362)
#Wed Jun 10 15:23:46 JST 2020 TP0=2400 N:50_N:100 ns=25_50 ==>(hV,hg)=(202,355) *better in L2 in L0
#Wed Jun 10 15:31:58 JST 2020 TP0=2500 N:50_N:100 ns=25_50 ==>(hV,hg)=(247,355)

#Tue Jun  9 16:20:26 JST 2020 TP0=2800 N:50,100 ns=50 ==>(hV,hg)=(198,349) 259L0
##############
#Fri Jun 12 22:36:27 JST 2020 TP0=2300 N:50-200:30 ns=15 ==>(hV,hg)=(186,273) 189  can2m1 check L0
h(yi,yg)@L0c0 with n88 min61.0 max273.0 mean118.6 median110.5 std54.5 best-iNshh(36,80,12,273*,119) can2m1
h(yi,yg)@L2c0 with n27 min72.0 max192.0 mean154.4 median167.0 std33.6 best-iNshh(7,170,11,192*,194) can2m1
h(yi,yg)@L2c1 with n23 min70.0 max273.0 mean162.1 median168.0 std46.7 best-iNshh(36,80,12,273*,162) can2m1
h(yi,yg)@L2c2 with n25 min61.0 max68.0 mean66.0 median66.0 std1.4 best-iNshh(81,50,9,68*,107) can2m1
h(yi,yg)@L2c3 with n13 min68.0 max69.0 mean68.3 median68.0 std0.5 best-iNshh(44,80,4,69*,253)(45,110,7,69*,259)(62,200,0,69*,257)(78,140,14,69*,218) can2m1
hi-LOOCV@L0c0 with n88 min74.0 max135.4 mean110.0 median111.0 std14.5 best-iNshh(0,170,3,189,135*) can2m1
hi-LOOCV@L2c0 with n27 min99.2 max209.7 mean166.8 median171.0 std33.7 best-iNshh(4,110,14,186,210*) can2m1
hi-LOOCV@L2c1 with n23 min73.4 max188.9 mean154.6 median167.6 std30.5 best-iNshh(65,50,4,190,189*) can2m1
hi-LOOCV@L2c2 with n25 min91.6 max188.6 mean159.8 median174.7 std28.9 best-iNshh(32,50,0,65,189*) can2m1
hi-LOOCV@L2c3 with n13 min127.2 max266.4 mean244.0 median257.3 std35.7 best-iNshh(3,80,6,68,266*) can2m1

#Fri Jun 12 22:25:21 JST 2020 TP0=2800 N:50-100:10 ns=15 ==>(hV,hg)=(259,374) 259 can2m
h(yi,yg)@L0c0 with n90 min52.0 max374.0 mean161.8 median166.0 std69.3 best-iNshh(13,60,1,374*,152) can2m
h(yi,yg)@L2c0 with n14 min54.0 max136.0 mean97.1 median106.0 std28.6 best-iNshh(64,100,3,136*,124) can2m
h(yi,yg)@L2c1 with n64 min108.0 max374.0 mean191.4 median169.5 std56.4 best-iNshh(13,60,1,374*,183) can2m
h(yi,yg)@L2c2 with n1 min53.0 max53.0 mean53.0 median53.0 std0.0 best-iNshh(89,50,11,53*,-1) can2m
h(yi,yg)@L2c3 with n9 min63.0 max175.0 mean88.7 median65.0 std45.9 best-iNshh(61,80,11,175*,160) can2m
hi-LOOCV@L0c0 with n90 min54.7 max162.2 mean130.4 median146.8 std30.9 best-iNshh(4,100,14,259,162*) can2m
hi-LOOCV@L2c0 with n14 min71.4 max135.9 mean109.7 median115.5 std19.2 best-iNshh(72,80,3,108,136*) can2m
hi-LOOCV@L2c1 with n64 min108.5 max189.7 mean172.2 median177.3 std15.5 best-iNshh(4,100,14,259,190*) can2m
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(89,50,11,53,-1*) can2m
hi-LOOCV@L2c3 with n9 min159.8 max261.0 mean223.8 median229.9 std27.1 best-iNshh(68,100,9,63,261*) can2m

#Fri Jun 12 22:19:24 JST 2020 TP0=2700 N:50-100:10 ns=15 ==>(hV,hg)=(270,273) 270 can2m
h(yi,yg)@L0c0 with n88 min86.0 max273.0 mean166.6 median150.0 std45.5 best-iNshh(34,80,3,273*,162) can2m
h(yi,yg)@L2c0 with n7 min89.0 max119.0 mean113.4 median117.0 std10.0 best-iNshh(78,80,14,119*,125) can2m
h(yi,yg)@L2c1 with n77 min98.0 max273.0 mean175.6 median153.0 std41.1 best-iNshh(34,80,3,273*,171) can2m
h(yi,yg)@L2c2 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(87,50,5,86*,-1) can2m
h(yi,yg)@L2c3 with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(86,50,7,87*,-1) can2m
hi-LOOCV@L0c0 with n88 min89.6 max170.7 mean154.4 median161.0 std19.3 best-iNshh(2,80,8,270,171*) can2m
hi-LOOCV@L2c0 with n7 min109.0 max227.5 mean192.7 median218.5 std48.1 best-iNshh(76,80,4,118,228*) can2m
hi-LOOCV@L2c1 with n77 min129.1 max180.3 mean169.1 median169.6 std8.0 best-iNshh(2,80,8,270,180*) can2m
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(87,50,5,86,-1*) can2m
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(86,50,7,87,-1*) can2m

#Fri Jun 12 22:16:05 JST 2020 TP0=2900 N:50-200:30 ns=15 ==>(hV,hg)=(214,308) 212 can2m1
h(yi,yg)@L0c0 with n87 min72.0 max308.0 mean163.9 median188.0 std67.0 best-iNshh(47,140,1,308*,151) can2m1
h(yi,yg)@L2c0 with n26 min78.0 max217.0 mean165.1 median211.0 std59.5 best-iNshh(26,200,5,217*,250) can2m1
h(yi,yg)@L2c1 with n41 min122.0 max308.0 mean206.9 median211.0 std39.0 best-iNshh(47,140,1,308*,203) can2m1
h(yi,yg)@L2c2 with n13 min72.0 max77.0 mean73.6 median73.0 std1.2 best-iNshh(86,140,7,77*,77) can2m1
h(yi,yg)@L2c3 with n7 min75.0 max76.0 mean75.7 median76.0 std0.5 best-iNshh(80,140,13,76*,198)(81,80,10,76*,175)(82,170,7,76*,231)(84,50,0,76*,151)(85,80,2,76*,153) can2m1
hi-LOOCV@L0c0 with n87 min79.4 max189.8 mean144.2 median151.8 std35.8 best-iNshh(0,50,10,212,190*) can2m1
hi-LOOCV@L2c0 with n26 min154.4 max273.7 mean228.5 median237.8 std34.6 best-iNshh(56,200,7,85,274*) can2m1
hi-LOOCV@L2c1 with n41 min124.1 max222.2 mean198.2 median209.8 std25.5 best-iNshh(3,170,5,214,222*) can2m1
hi-LOOCV@L2c2 with n13 min77.2 max206.3 mean187.9 median196.7 std33.1 best-iNshh(73,50,7,73,206*) can2m1
hi-LOOCV@L2c3 with n7 min151.3 max230.7 mean181.1 median174.8 std26.1 best-iNshh(82,170,7,76,231*) can2m1

#Fri Jun 12 22:13:01 JST 2020 TP0=2600 N:50-100:10 ns=15 ==>(hV,hg)=(185,308) 185 can2m
h(yi,yg)@L0c0 with n90 min116.0 max308.0 mean166.2 median151.0 std38.4 best-iNshh(48,100,5,308*,162) can2m
h(yi,yg)@L2c0 with n34 min144.0 max251.0 mean153.3 median150.0 std17.3 best-iNshh(10,100,10,251*,186) can2m
h(yi,yg)@L2c1 with n37 min129.0 max308.0 mean199.1 median185.0 std34.8 best-iNshh(48,100,5,308*,194) can2m
h(yi,yg)@L2c2 with n14 min124.0 max127.0 mean125.4 median125.0 std1.1 best-iNshh(75,60,8,127*,224)(79,60,6,127*,217)(82,60,4,127*,220) can2m
h(yi,yg)@L2c3 with n5 min116.0 max128.0 mean125.4 median128.0 std4.7 best-iNshh(73,90,4,128*,228)(76,60,10,128*,228)(77,70,5,128*,224) can2m
hi-LOOCV@L0c0 with n90 min119.4 max177.7 mean159.1 median163.9 std13.2 best-iNshh(1,80,3,185,178*) can2m
hi-LOOCV@L2c0 with n34 min181.8 max218.2 mean200.3 median201.4 std8.9 best-iNshh(13,60,1,148,218*) can2m
hi-LOOCV@L2c1 with n37 min141.9 max227.9 mean200.9 median202.8 std18.5 best-iNshh(1,80,3,185,228*) can2m
hi-LOOCV@L2c2 with n14 min199.9 max225.2 mean214.2 median213.4 std7.4 best-iNshh(71,100,13,126,225*) can2m
hi-LOOCV@L2c3 with n5 min115.2 max228.5 mean193.3 median223.5 std44.4 best-iNshh(73,90,4,128,228*) can2m

#Fri Jun 12 22:06:57 JST 2020 TP0=2800 N:50-200:30 ns=15 ==>(hV,hg)=(286,349) 286 can2m1
h(yi,yg)@L0c0 with n90 min50.0 max349.0 mean164.9 median167.5 std64.9 best-iNshh(13,50,1,349*,156) can2m1
h(yi,yg)@L2c0 with n77 min105.0 max349.0 mean182.6 median170.0 std52.4 best-iNshh(13,50,1,349*,173) can2m1
h(yi,yg)@L2c1 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(87,50,12,54*,-1) can2m1
h(yi,yg)@L2c2 with n6 min65.0 max72.0 mean68.3 median68.0 std3.3 best-iNshh(77,170,0,72*,126)(79,140,0,72*,127) can2m1
h(yi,yg)@L2c3 with n4 min50.0 max53.0 mean51.5 median51.5 std1.1 best-iNshh(85,50,11,53*,117) can2m1
hi-LOOCV@L0c0 with n90 min52.0 max165.1 mean135.1 median153.1 std33.8 best-iNshh(7,200,9,286,165*) can2m1
hi-LOOCV@L2c0 with n77 min94.5 max183.3 mean162.4 median171.5 std19.9 best-iNshh(7,200,9,286,183*) can2m1
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(87,50,12,54,-1*) can2m1
hi-LOOCV@L2c2 with n6 min125.8 max152.2 mean137.5 median135.1 std10.9 best-iNshh(81,80,12,65,152*) can2m1
hi-LOOCV@L2c3 with n4 min116.7 max169.7 mean146.5 median149.8 std23.1 best-iNshh(88,200,10,51,170*) can2m1

#Fri Jun 12 21:57:53 JST 2020 TP0=2700 N:50-200:30 ns=15 ==>(hV,hg)=(270,387) 270 can2m1
h(yi,yg)@L0c0 with n89 min86.0 max387.0 mean171.8 median150.0 std52.7 best-iNshh(14,200,12,387*,164) can2m1
h(yi,yg)@L2c0 with n78 min98.0 max387.0 mean180.6 median154.0 std50.0 best-iNshh(14,200,12,387*,172) can2m1
h(yi,yg)@L2c1 with n8 min115.0 max119.0 mean116.9 median116.5 std1.5 best-iNshh(78,80,14,119*,164)(79,200,9,119*,166) can2m1
h(yi,yg)@L2c2 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(88,50,5,86*,-1) can2m1
hi-LOOCV@L0c0 with n89 min88.5 max174.2 mean155.2 median161.4 std18.0 best-iNshh(0,80,8,270,174*) can2m1
hi-LOOCV@L2c0 with n78 min134.9 max183.5 mean168.6 median170.2 std7.6 best-iNshh(0,80,8,270,184*) can2m1
hi-LOOCV@L2c1 with n8 min145.7 max189.1 mean166.4 median165.9 std11.8 best-iNshh(80,170,13,117,189*) can2m1
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(88,50,5,86,-1*) can2m1

#Fri Jun 12 21:51:12 JST 2020 TP0=2900 N:50-200:30 ns=20 ==>(hV,hg)=(218,308) 212 can2m
h(yi,yg)@L0c0 with n116 min71.0 max308.0 mean161.7 median188.0 std67.4 best-iNshh(61,140,1,308*,150) can2m
h(yi,yg)@L2c0 with n55 min122.0 max308.0 mean207.1 median212.0 std36.8 best-iNshh(61,140,1,308*,204) can2m
h(yi,yg)@L2c1 with n33 min78.0 max217.0 mean160.3 median211.0 std61.4 best-iNshh(39,200,5,217*,251) can2m
h(yi,yg)@L2c2 with n9 min75.0 max76.0 mean75.8 median76.0 std0.4 best-iNshh(101,140,13,76*,213)(106,80,10,76*,184)(107,170,17,76*,261)(110,170,7,76*,234)(111,140,19,76*,199)(112,80,2,76*,178)(113,50,0,76*,173) can2m
h(yi,yg)@L2c3 with n19 min71.0 max77.0 mean73.3 median73.0 std1.4 best-iNshh(115,140,7,77*,77) can2m
hi-LOOCV@L0c0 with n116 min79.4 max191.2 mean143.1 median150.7 std34.9 best-iNshh(0,50,10,212,191*) can2m
hi-LOOCV@L2c0 with n55 min124.0 max225.1 mean201.2 median208.7 std24.6 best-iNshh(34,110,18,218,225*) can2m
hi-LOOCV@L2c1 with n33 min152.3 max288.2 mean244.5 median250.8 std33.9 best-iNshh(65,80,15,86,288*) can2m
hi-LOOCV@L2c2 with n9 min172.6 max261.2 mean202.2 median198.9 std27.8 best-iNshh(107,170,17,76,261*) can2m
hi-LOOCV@L2c3 with n19 min76.9 max208.4 mean189.9 median199.3 std29.3 best-iNshh(91,80,19,74,208*) can2m


#Fri Jun 12 21:48:18 JST 2020 TP0=2500 N:50-200:30 ns=15 ==>(hV,hg)=(286,376) 249 can2m1
h(yi,yg)@L0c0 with n90 min114.0 max376.0 mean199.0 median201.5 std61.9 best-iNshh(18,110,5,376*,200) can2m1
h(yi,yg)@L2c0 with n40 min114.0 max376.0 mean235.8 median225.5 std55.4 best-iNshh(18,110,5,376*,234) can2m1
h(yi,yg)@L2c1 with n22 min140.0 max256.0 mean212.2 median248.0 std49.2 best-iNshh(28,200,8,256*,280) can2m1
h(yi,yg)@L2c2 with n25 min133.0 max138.0 mean136.4 median137.0 std1.4 best-iNshh(68,140,14,138*,234)(69,50,14,138*,230)(70,110,12,138*,236)(71,110,11,138*,234)(72,170,14,138*,232)(73,200,13,138*,224)(75,80,14,138*,213) can2m1
h(yi,yg)@L2c3 with n1 min131.0 max131.0 mean131.0 median131.0 std0.0 best-iNshh(88,140,4,131*,-1) can2m1
hi-LOOCV@L0c0 with n90 min126.8 max223.0 mean183.4 median183.5 std22.0 best-iNshh(0,50,1,249,223*) can2m1
hi-LOOCV@L2c0 with n40 min140.8 max236.6 mean214.1 median226.3 std26.9 best-iNshh(13,80,8,286,237*) can2m1
hi-LOOCV@L2c1 with n22 min197.5 max329.0 mean306.2 median316.3 std28.1 best-iNshh(8,170,4,249,329*)(45,200,11,148,329*) can2m1
hi-LOOCV@L2c2 with n25 min181.7 max282.6 mean242.5 median238.2 std27.7 best-iNshh(47,200,12,136,283*) can2m1
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(88,140,4,131,-1*) can2m1

#Fri Jun 12 21:38:56 JST 2020 TP0=2800 N:50-200:30 ns=20 ==>(hV,hg)=(286,379) 286 can2m
h(yi,yg)@L0c0 with n120 min50.0 max379.0 mean169.5 median167.0 std64.3 best-iNshh(4,200,17,379*,166) can2m
h(yi,yg)@L0c0 with n120 min50.0 max379.0 mean169.5 median167.0 std64.3 best-iNshh(4,200,17,379*,166) can2m
h(yi,yg)@L2c0 with n77 min54.0 max379.0 mean181.0 median167.0 std66.1 best-iNshh(4,200,17,379*,178) can2m
h(yi,yg)@L2c1 with n33 min136.0 max288.0 mean175.3 median169.0 std30.3 best-iNshh(3,140,3,288*,171) can2m
h(yi,yg)@L2c2 with n4 min50.0 max53.0 mean51.5 median51.5 std1.1 best-iNshh(115,50,11,53*,117) can2m
h(yi,yg)@L2c3 with n6 min65.0 max72.0 mean68.3 median68.0 std3.3 best-iNshh(107,170,0,72*,126)(109,140,0,72*,127) can2m
hi-LOOCV@L0c0 with n120 min51.3 max168.9 mean141.1 median157.0 std31.9 best-iNshh(7,200,9,286,169*) can2m
hi-LOOCV@L0c0 with n120 min51.3 max168.9 mean141.1 median157.0 std31.9 best-iNshh(7,200,9,286,169*) can2m
hi-LOOCV@L2c0 with n77 min54.9 max180.5 mean154.0 median157.8 std25.8 best-iNshh(7,200,9,286,181*) can2m
hi-LOOCV@L2c1 with n33 min138.9 max210.9 mean188.1 median194.9 std20.1 best-iNshh(39,200,15,175,211*) can2m
hi-LOOCV@L2c2 with n4 min116.7 max169.7 mean146.5 median149.8 std23.1 best-iNshh(118,200,10,51,170*) can2m
hi-LOOCV@L2c3 with n6 min125.8 max152.2 mean137.5 median135.1 std10.9 best-iNshh(111,80,12,65,152*) can2m

#Fri Jun 12 21:29:23 JST 2020 TP0=2100 N:50-200:30 ns=15 ==>(hV,hg)=(261,321) 93 can2m1
h(yi,yg)@L0c0 with n86 min88.0 max321.0 mean129.1 median95.0 std62.8 best-iNshh(43,170,1,321*,124) can2m1
h(yi,yg)@L2c0 with n37 min88.0 max97.0 mean91.2 median91.0 std1.5 best-iNshh(85,170,12,97*,93) can2m1
h(yi,yg)@L2c1 with n11 min93.0 max96.0 mean94.5 median95.0 std1.1 best-iNshh(64,200,3,96*,215)(68,170,11,96*,197) can2m1
h(yi,yg)@L2c2 with n35 min97.0 max321.0 mean182.8 median176.0 std69.4 best-iNshh(43,170,1,321*,176) can2m1
h(yi,yg)@L2c3 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(84,50,9,98*,-1) can2m1
hi-LOOCV@L0c0 with n86 min95.8 max161.8 mean131.3 median126.2 std19.6 best-iNshh(0,50,4,93,162*) can2m1
hi-LOOCV@L2c0 with n37 min93.0 max222.6 mean199.2 median206.7 std28.5 best-iNshh(1,80,6,92,223*) can2m1
hi-LOOCV@L2c1 with n11 min196.7 max274.9 mean229.7 median217.0 std24.0 best-iNshh(55,170,14,95,275*) can2m1
hi-LOOCV@L2c2 with n35 min104.8 max185.1 mean157.0 median163.4 std22.7 best-iNshh(40,110,2,261,185*) can2m1
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(84,50,9,98,-1*) can2m1

#Fri Jun 12 21:26:28 JST 2020 TP0=2600 N:50-200:30 ns=20 ==>(hV,hg)=(184,338) 184 can2m
h(yi,yg)@L0c0 with n120 min34.0 max338.0 mean167.4 median154.5 std46.0 best-iNshh(28,200,19,338*,166) can2m
h(yi,yg)@L2c0 with n1 min34.0 max34.0 mean34.0 median34.0 std0.0 best-iNshh(119,170,18,34*,-1) can2m
h(yi,yg)@L2c2 with n5 min93.0 max94.0 mean93.6 median94.0 std0.5 best-iNshh(113,170,2,94*,243)(114,140,2,94*,242)(115,140,8,94*,228) can2m
h(yi,yg)@L2c3 with n113 min106.0 max338.0 mean173.1 median157.0 std40.7 best-iNshh(28,200,19,338*,172) can2m
hi-LOOCV@L0c0 with n120 min34.6 max177.8 mean153.5 median160.4 std23.9 best-iNshh(10,110,8,184,178*) can2m
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(119,170,18,34,-1*) can2m
hi-LOOCV@L2c2 with n5 min188.2 max243.2 mean221.6 median228.5 std21.6 best-iNshh(113,170,2,94,243*) can2m
hi-LOOCV@L2c3 with n113 min116.9 max184.2 mean163.2 median166.0 std14.9 best-iNshh(10,110,8,184,184*) can2m

#Fri Jun 12 21:20:15 JST 2020 TP0=2000 N:50-200:30 ns=15 ==>(hV,hg)=(216,414) 191 can2m1
h(yi,yg)@L0c0 with n87 min21.0 max414.0 mean180.0 median188.0 std64.3 best-iNshh(40,80,10,414*,169) can2m1
h(yi,yg)@L2c0 with n32 min98.0 max391.0 mean186.0 median171.5 std65.1 best-iNshh(19,80,12,391*,178) can2m1
h(yi,yg)@L2c1 with n5 min21.0 max116.0 mean59.4 median30.0 std40.5 best-iNshh(82,110,7,116*,106) can2m1
h(yi,yg)@L2c2 with n36 min97.0 max414.0 mean193.3 median189.5 std54.7 best-iNshh(40,80,10,414*,182) can2m1
h(yi,yg)@L2c3 with n14 min21.0 max197.0 mean175.4 median191.5 std44.4 best-iNshh(31,200,5,197*,203) can2m1
hi-LOOCV@L0c0 with n87 min20.2 max186.9 mean156.2 median170.9 std34.7 best-iNshh(6,140,0,191,187*) can2m1
hi-LOOCV@L2c0 with n32 min107.2 max181.5 mean157.2 median160.5 std22.2 best-iNshh(21,80,13,217,181*) can2m1
hi-LOOCV@L2c1 with n5 min77.5 max118.8 mean104.9 median106.5 std14.7 best-iNshh(83,80,11,29,119*) can2m1
hi-LOOCV@L2c2 with n36 min97.1 max215.8 mean184.6 median192.2 std26.2 best-iNshh(0,80,8,189,216*) can2m1
hi-LOOCV@L2c3 with n14 min17.1 max216.2 mean188.6 median207.0 std51.5 best-iNshh(44,170,8,181,216*) can2m1

#Fri Jun 12 21:14:12 JST 2020 TP0=2400 N:50-200:30 ns=20 ==>(hV,hg)=(288,448) 237 can2m
h(yi,yg)@L0c0 with n118 min56.0 max448.0 mean186.4 median201.0 std78.3 best-iNshh(32,200,4,448*,183) can2m
h(yi,yg)@L2c0 with n61 min66.0 max448.0 mean195.8 median186.0 std68.5 best-iNshh(32,200,4,448*,195) can2m
h(yi,yg)@L2c1 with n38 min173.0 max351.0 mean233.6 median229.0 std37.0 best-iNshh(6,80,10,351*,233) can2m
h(yi,yg)@L2c2 with n6 min56.0 max76.0 mean60.8 median58.5 std6.9 best-iNshh(105,50,14,76*,59) can2m
h(yi,yg)@L2c3 with n13 min60.0 max66.0 mean62.5 median62.0 std1.7 best-iNshh(115,110,15,66*,66) can2m
hi-LOOCV@L0c0 with n118 min60.8 max187.8 mean148.0 median165.2 std40.7 best-iNshh(10,140,13,237,188*) can2m
hi-LOOCV@L2c0 with n61 min61.8 max200.2 mean174.6 median185.1 std26.4 best-iNshh(25,140,4,288,200*) can2m
hi-LOOCV@L2c1 with n38 min155.5 max254.4 mean225.0 median233.0 std25.2 best-iNshh(12,170,5,227,254*) can2m
hi-LOOCV@L2c2 with n6 min59.0 max181.2 mean139.3 median156.5 std46.5 best-iNshh(107,50,1,59,181*) can2m
hi-LOOCV@L2c3 with n13 min65.8 max190.3 mean153.8 median159.9 std33.5 best-iNshh(98,110,1,64,190*) can2m

#Fri Jun 12 21:02:03 JST 2020 TP0=2300 N:50-200:30 ns=20 ==>(hV,hg)=(186,362) 189 can2m
h(yi,yg)@L0c0 with n118 min61.0 max362.0 mean123.8 median123.0 std59.5 best-iNshh(46,50,18,362*,119) can2m
h(yi,yg)@L2c0 with n23 min70.0 max273.0 mean152.6 median167.0 std53.9 best-iNshh(29,80,12,273*,156) can2m
h(yi,yg)@L2c1 with n48 min72.0 max362.0 mean165.8 median167.0 std44.2 best-iNshh(46,50,18,362*,164) can2m
h(yi,yg)@L2c2 with n16 min68.0 max69.0 mean68.2 median68.0 std0.4 best-iNshh(62,80,4,69*,259)(64,110,7,69*,258)(89,200,0,69*,262)(107,140,14,69*,224) can2m
h(yi,yg)@L2c3 with n31 min61.0 max68.0 mean66.0 median66.0 std1.3 best-iNshh(110,50,9,68*,108) can2m
hi-LOOCV@L0c0 with n118 min73.2 max138.3 mean111.8 median112.0 std15.3 best-iNshh(0,200,16,189,138*) can2m
hi-LOOCV@L2c0 with n23 min75.3 max199.4 mean160.2 median173.5 std32.5 best-iNshh(2,200,19,168,199*) can2m
hi-LOOCV@L2c1 with n48 min98.1 max205.9 mean165.4 median165.6 std26.5 best-iNshh(19,110,14,186,206*) can2m
hi-LOOCV@L2c2 with n16 min127.0 max267.1 mean247.2 median257.2 std32.6 best-iNshh(34,50,13,68,267*) can2m
hi-LOOCV@L2c3 with n31 min91.4 max192.1 mean165.7 median178.9 std28.6 best-iNshh(69,170,9,66,192*) can2m

#Fri Jun 12 20:50:01 JST 2020 TP0=2200 N:50-200:30 ns=20 ==>(hV,hg)=(166,371) 166 can2m
h(yi,yg)@L0c0 with n118 min76.0 max371.0 mean179.1 median166.0 std47.8 best-iNshh(34,80,12,371*,179) can2m
h(yi,yg)@L2c0 with n29 min99.0 max214.0 mean146.8 median134.0 std29.6 best-iNshh(76,140,5,214*,152) can2m
h(yi,yg)@L2c1 with n86 min132.0 max371.0 mean193.4 median167.0 std44.1 best-iNshh(34,80,12,371*,194) can2m
h(yi,yg)@L2c2 with n1 min76.0 max76.0 mean76.0 median76.0 std0.0 best-iNshh(117,170,2,76*,-1) can2m
hi-LOOCV@L0c0 with n118 min77.7 max187.6 mean167.1 median176.0 std23.0 best-iNshh(5,80,1,166,188*) can2m
hi-LOOCV@L2c0 with n29 min95.0 max172.5 mean148.4 median154.7 std18.0 best-iNshh(92,200,2,147,172*) can2m
hi-LOOCV@L2c1 with n86 min131.6 max207.1 mean191.5 median191.7 std11.0 best-iNshh(5,80,1,166,207*) can2m
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(117,170,2,76,-1*) can2m

#Fri Jun 12 20:10:45 JST 2020 TP0=2900 N:50-200:30 ns=20 ==>(hV,hg)=(218,308) 212
h(yi,yg)@L0c0 with n116 min71.0 max308.0 mean161.7 median188.0 std67.4 best-iNshh(61,140,1,308*,150) can2m2-2
h(yi,yg)@L2c0 with n19 min71.0 max77.0 mean73.3 median73.0 std1.4 best-iNshh(115,140,7,77*,77) can2m2-2
h(yi,yg)@L2c1 with n9 min75.0 max76.0 mean75.8 median76.0 std0.4 best-iNshh(101,140,13,76*,213)(106,80,10,76*,184)(107,170,17,76*,261)(110,170,7,76*,234)(111,140,19,76*,199)(112,80,2,76*,178)(113,50,0,76*,173) can2m2-2
h(yi,yg)@L2c2 with n54 min122.0 max308.0 mean207.4 median212.0 std37.1 best-iNshh(61,140,1,308*,204) can2m2-2
h(yi,yg)@L2c3 with n34 min78.0 max217.0 mean161.2 median211.0 std60.7 best-iNshh(39,200,5,217*,249) can2m2-2
hi-LOOCV@L0c0 with n116 min79.4 max191.2 mean143.1 median150.7 std34.9 best-iNshh(0,50,10,212,191*) can2m2-2
hi-LOOCV@L2c0 with n19 min76.9 max208.4 mean189.9 median199.3 std29.3 best-iNshh(91,80,19,74,208*) can2m2-2
hi-LOOCV@L2c1 with n9 min172.6 max261.2 mean202.2 median198.9 std27.8 best-iNshh(107,170,17,76,261*) can2m2-2
hi-LOOCV@L2c2 with n54 min124.5 max225.8 mean201.6 median209.7 std24.9 best-iNshh(34,110,18,218,226*) can2m2-2
hi-LOOCV@L2c3 with n34 min152.8 max282.0 mean239.8 median247.2 std35.1 best-iNshh(65,80,15,86,282*) can2m2-2

#Fri Jun 12 20:01:15 JST 2020 TP0=2900 N:50-200:30 ns=15 ==>(hV,hg)=(214,308) 212
h(yi,yg)@L0c0 with n87 min72.0 max308.0 mean163.9 median188.0 std67.0 best-iNshh(47,140,1,308*,151) can2m3
h(yi,yg)@L2c0 with n26 min78.0 max217.0 mean165.1 median211.0 std59.5 best-iNshh(26,200,5,217*,250) can2m3
h(yi,yg)@L2c1 with n41 min122.0 max308.0 mean206.9 median211.0 std39.0 best-iNshh(47,140,1,308*,203) can2m3
h(yi,yg)@L2c2 with n13 min72.0 max77.0 mean73.6 median73.0 std1.2 best-iNshh(86,140,7,77*,77) can2m3
h(yi,yg)@L2c3 with n7 min75.0 max76.0 mean75.7 median76.0 std0.5 best-iNshh(80,140,13,76*,198)(81,80,10,76*,175)(82,170,7,76*,231)(84,50,0,76*,151)(85,80,2,76*,153) can2m3
hi-LOOCV@L0c0 with n87 min79.4 max189.8 mean144.2 median151.8 std35.8 best-iNshh(0,50,10,212,190*) can2m3
hi-LOOCV@L2c0 with n26 min154.4 max273.7 mean228.5 median237.8 std34.6 best-iNshh(56,200,7,85,274*) can2m3
hi-LOOCV@L2c1 with n41 min124.1 max222.2 mean198.2 median209.8 std25.5 best-iNshh(3,170,5,214,222*) can2m3
hi-LOOCV@L2c2 with n13 min77.2 max206.3 mean187.9 median196.7 std33.1 best-iNshh(73,50,7,73,206*) can2m3
hi-LOOCV@L2c3 with n7 min151.3 max230.7 mean181.1 median174.8 std26.1 best-iNshh(82,170,7,76,231*) can2m3

#Fri Jun 12 19:52:12 JST 2020 TP0=2800 N:50-200:30 ns=15 ==>(hV,hg)=(286,349) 286
h(yi,yg)@L0c0 with n90 min50.0 max349.0 mean164.9 median167.5 std64.9 best-iNshh(13,50,1,349*,156) can2m3
h(yi,yg)@L2c0 with n76 min108.0 max349.0 mean183.7 median170.0 std51.9 best-iNshh(13,50,1,349*,173) can2m3
h(yi,yg)@L2c1 with n4 min54.0 max105.0 mean67.2 median55.0 std21.8 best-iNshh(76,200,0,105*,74) can2m3
h(yi,yg)@L2c2 with n6 min65.0 max72.0 mean68.3 median68.0 std3.3 best-iNshh(77,170,0,72*,126)(79,140,0,72*,127) can2m3
h(yi,yg)@L2c3 with n4 min50.0 max53.0 mean51.5 median51.5 std1.1 best-iNshh(85,50,11,53*,117) can2m3
hi-LOOCV@L0c0 with n90 min52.0 max165.1 mean135.1 median153.1 std33.8 best-iNshh(7,200,9,286,165*) can2m3
hi-LOOCV@L2c0 with n76 min106.2 max184.4 mean164.2 median172.5 std18.8 best-iNshh(7,200,9,286,184*) can2m3
hi-LOOCV@L2c1 with n4 min74.0 max106.3 mean91.5 median92.8 std14.8 best-iNshh(86,50,7,55,106*) can2m3
hi-LOOCV@L2c2 with n6 min125.8 max152.2 mean137.5 median135.1 std10.9 best-iNshh(81,80,12,65,152*) can2m3
hi-LOOCV@L2c3 with n4 min116.7 max169.7 mean146.5 median149.8 std23.1 best-iNshh(88,200,10,51,170*) can2m3

#Fri Jun 12 19:46:19 JST 2020 TP0=2700 N:50-200:30 ns=20 ==>(hV,hg)=(270,387) 270
h(yi,yg)@L0c0 with n119 min86.0 max387.0 mean168.4 median150.0 std53.0 best-iNshh(11,200,12,387*,162) can2m2-2
h(yi,yg)@L2c0 with n98 min98.0 max387.0 mean181.3 median159.0 std49.2 best-iNshh(11,200,12,387*,173) can2m2-2
h(yi,yg)@L2c1 with n11 min114.0 max119.0 mean116.5 median116.0 std1.6 best-iNshh(98,80,14,119*,151)(100,200,9,119*,153) can2m2-2
h(yi,yg)@L2c2 with n6 min89.0 max117.0 mean105.7 median107.5 std8.9 best-iNshh(105,140,16,117*,148) can2m2-2
h(yi,yg)@L2c3 with n4 min86.0 max88.0 mean87.0 median87.0 std0.7 best-iNshh(115,80,6,88*,223) can2m2-2
hi-LOOCV@L0c0 with n119 min88.8 max170.6 mean150.4 median157.7 std19.0 best-iNshh(2,80,8,270,171*) can2m2-2
hi-LOOCV@L2c0 with n98 min133.9 max184.2 mean169.2 median170.0 std7.3 best-iNshh(2,80,8,270,184*) can2m2-2
hi-LOOCV@L2c1 with n11 min151.4 max212.1 mean175.6 median178.0 std19.4 best-iNshh(99,110,15,117,212*) can2m2-2
hi-LOOCV@L2c2 with n6 min127.2 max163.4 mean149.0 median147.9 std11.8 best-iNshh(114,170,17,89,163*) can2m2-2
hi-LOOCV@L2c3 with n4 min173.7 max223.3 mean202.7 median206.8 std21.2 best-iNshh(115,80,6,88,223*) can2m2-2


#Fri Jun 12 19:43:00 JST 2020 TP0=2700 N:50-200:30 ns=15 ==>(hV,hg)=(270,387)270
h(yi,yg)@L0c0 with n89 min86.0 max387.0 mean171.8 median150.0 std52.7 best-iNshh(14,200,12,387*,164) can2m3
h(yi,yg)@L2c0 with n8 min115.0 max119.0 mean116.9 median116.5 std1.5 best-iNshh(78,80,14,119*,164)(79,200,9,119*,166) can2m3
h(yi,yg)@L2c1 with n78 min98.0 max387.0 mean180.6 median154.0 std50.0 best-iNshh(14,200,12,387*,172) can2m3
h(yi,yg)@L2c2 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(88,50,5,86*,-1) can2m3
hi-LOOCV@L0c0 with n89 min88.5 max174.2 mean155.2 median161.4 std18.0 best-iNshh(0,80,8,270,174*) can2m3
hi-LOOCV@L2c0 with n8 min145.7 max189.1 mean166.4 median165.9 std11.8 best-iNshh(80,170,13,117,189*) can2m3
hi-LOOCV@L2c1 with n78 min134.9 max183.5 mean168.6 median170.2 std7.6 best-iNshh(0,80,8,270,184*) can2m3
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(88,50,5,86,-1*) can2m3


#Fri Jun 12 19:33:51 JST 2020 TP0=2600 N:50-200:30 ns=15 ==>(hV,hg)=(211,338) 211
h(yi,yg)@L2c0 with n69 min106.0 max338.0 mean182.5 median184.0 std48.1 best-iNshh(28,200,19,338*,180) can2m2-2
h(yi,yg)@L2c1 with n49 min93.0 max186.0 mean151.7 median150.0 std25.1 best-iNshh(3,200,8,186*,171) can2m2-2
h(yi,yg)@L2c2 with n1 min34.0 max34.0 mean34.0 median34.0 std0.0 best-iNshh(119,170,18,34*,-1) can2m2-2
hi-LOOCV@L2c0 with n69 min117.7 max188.9 mean164.9 median174.4 std18.6 best-iNshh(23,110,13,211,189*) can2m2-2
hi-LOOCV@L2c1 with n49 min100.2 max186.2 mean167.4 median175.4 std22.8 best-iNshh(54,170,9,149,186*) can2m2-2
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(119,170,18,34,-1*) can2m2-2
Fri Jun 12 19:33:51 JST 2020


#Fri Jun 12 19:28:36 JST 2020 TP0=2900 N:50-100:10 ns=15 ==>(hV,hg)=(215,492) 215
h(yi,yg)@L0c0 with n87 min72.0 max492.0 mean168.3 median188.0 std77.4 best-iNshh(34,90,8,492*,164) can2m-2
h(yi,yg)@L2c0 with n15 min72.0 max75.0 mean73.6 median74.0 std0.7 best-iNshh(64,100,7,75*,182) can2m-2
h(yi,yg)@L2c1 with n7 min76.0 max76.0 mean76.0 median76.0 std0.0 best-iNshh(74,80,10,76*,171)(77,100,10,76*,194)(78,70,14,76*,234)(79,60,2,76*,266)(80,90,13,76*,258)(83,50,0,76*,206)(86,80,2,76*,178) can2m-2
h(yi,yg)@L2c2 with n49 min126.0 max492.0 mean211.3 median211.0 std55.7 best-iNshh(34,90,8,492*,205) can2m-2
h(yi,yg)@L2c3 with n16 min77.0 max314.0 mean165.8 median211.5 std72.7 best-iNshh(48,90,4,314*,196) can2m-2
hi-LOOCV@L0c0 with n87 min84.7 max178.5 mean137.5 median147.9 std32.3 best-iNshh(2,90,1,215,179*) can2m-2
hi-LOOCV@L2c0 with n15 min177.0 max231.2 mean210.4 median217.9 std16.8 best-iNshh(63,70,2,74,231*) can2m-2
hi-LOOCV@L2c1 with n7 min170.8 max265.7 mean215.1 median205.7 std35.0 best-iNshh(79,60,2,76,266*) can2m-2
hi-LOOCV@L2c2 with n49 min124.4 max224.8 mean199.3 median207.9 std24.6 best-iNshh(2,90,1,215,225*) can2m-2
hi-LOOCV@L2c3 with n16 min124.5 max269.0 mean198.0 median202.4 std34.1 best-iNshh(56,100,13,86,269*) can2m-2

#Fri Jun 12 19:24:01 JST 2020 TP0=2500 N:50-200:30 ns=15 ==>(hV,hg)=(286,376) 249
h(yi,yg)@L0c0 with n90 min114.0 max376.0 mean199.0 median201.5 std61.9 best-iNshh(18,110,5,376*,200) can2m3
h(yi,yg)@L2c0 with n22 min140.0 max256.0 mean212.2 median248.0 std49.2 best-iNshh(28,200,8,256*,280) can2m3
h(yi,yg)@L2c1 with n40 min114.0 max376.0 mean235.8 median225.5 std55.4 best-iNshh(18,110,5,376*,234) can2m3
h(yi,yg)@L2c2 with n25 min133.0 max138.0 mean136.4 median137.0 std1.4 best-iNshh(68,140,14,138*,234)(69,50,14,138*,230)(70,110,12,138*,236)(71,110,11,138*,234)(72,170,14,138*,232)(73,200,13,138*,224)(75,80,14,138*,213) can2m3
h(yi,yg)@L2c3 with n1 min131.0 max131.0 mean131.0 median131.0 std0.0 best-iNshh(88,140,4,131*,-1) can2m3
hi-LOOCV@L0c0 with n90 min126.8 max223.0 mean183.4 median183.5 std22.0 best-iNshh(0,50,1,249,223*) can2m3
hi-LOOCV@L2c0 with n22 min197.5 max329.0 mean306.2 median316.3 std28.1 best-iNshh(8,170,4,249,329*)(45,200,11,148,329*) can2m3
hi-LOOCV@L2c1 with n40 min140.8 max236.6 mean214.1 median226.3 std26.9 best-iNshh(13,80,8,286,237*) can2m3
hi-LOOCV@L2c2 with n25 min181.7 max282.6 mean242.5 median238.2 std27.7 best-iNshh(47,200,12,136,283*) can2m3
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(88,140,4,131,-1*) can2m3

#Fri Jun 12 19:21:11 JST 2020 TP0=2500 N:50-200:30 ns=20 ==>(hV,hg)=(355,376) 249
h(yi,yg)@L0c0 with n120 min114.0 max376.0 mean202.8 median223.5 std60.4 best-iNshh(33,110,5,376*,204) can2m2-2
h(yi,yg)@L2c0 with n30 min133.0 max138.0 mean136.4 median137.0 std1.4 best-iNshh(85,140,14,138*,243)(89,200,17,138*,243)(93,110,12,138*,243)(94,50,14,138*,230)(98,170,14,138*,238)(99,110,11,138*,233)(102,200,13,138*,225)(104,80,14,138*,213) can2m2-2
h(yi,yg)@L2c1 with n1 min131.0 max131.0 mean131.0 median131.0 std0.0 best-iNshh(118,140,4,131*,-1) can2m2-2
h(yi,yg)@L2c2 with n52 min114.0 max376.0 mean235.4 median225.5 std53.0 best-iNshh(33,110,5,376*,235) can2m2-2
h(yi,yg)@L2c3 with n35 min139.0 max270.0 mean217.1 median248.0 std48.4 best-iNshh(15,50,16,270*,253) can2m2-2
hi-LOOCV@L0c0 with n120 min125.8 max229.2 mean187.4 median190.7 std24.8 best-iNshh(0,50,1,249,229*) can2m2-2
hi-LOOCV@L2c0 with n30 min180.6 max287.7 mean245.7 median242.8 std28.1 best-iNshh(68,140,10,137,288*) can2m2-2
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(118,140,4,131,-1*) can2m2-2
hi-LOOCV@L2c2 with n52 min139.0 max235.7 mean215.3 median225.6 std24.9 best-iNshh(28,50,18,355,236*) can2m2-2
hi-LOOCV@L2c3 with n35 min191.5 max336.5 mean291.7 median302.1 std35.0 best-iNshh(60,200,11,148,336*) can2m2-2

#Fri Jun 12 19:15:56 JST 2020 TP0=2500 N:50-100:10 ns=20 ==>(hV,hg)=(173,273) 173
h(yi,yg)@L0c0 with n88 min86.0 max273.0 mean166.6 median150.0 std45.5 best-iNshh(34,80,3,273*,162) can2m-2
h(yi,yg)@L2c0 with n46 min89.0 max273.0 mean187.1 median175.5 std48.9 best-iNshh(34,80,3,273*,173) can2m-2
h(yi,yg)@L2c1 with n38 min98.0 max269.0 mean150.2 median147.5 std21.3 best-iNshh(4,100,10,269*,154) can2m-2
h(yi,yg)@L2c2 with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(86,50,7,87*,-1) can2m-2
h(yi,yg)@L2c3 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(87,50,5,86*,-1) can2m-2
hi-LOOCV@L0c0 with n88 min89.6 max170.7 mean154.4 median161.0 std19.3 best-iNshh(2,80,8,270,171*) can2m-2
hi-LOOCV@L2c0 with n46 min92.2 max199.1 mean171.0 median178.5 std23.4 best-iNshh(6,60,10,173,199*) can2m-2
hi-LOOCV@L2c1 with n38 min154.1 max211.6 mean194.3 median195.5 std12.5 best-iNshh(0,70,12,150,212*) can2m-2
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(86,50,7,87,-1*) can2m-2
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(87,50,5,86,-1*) can2m-2

#Fri Jun 12 19:14:36 JST 2020 TP0=2400 N:50-200:30 ns=15 ==>(hV,hg)=(288,448) 231
h(yi,yg)@L0c0 with n89 min56.0 max448.0 mean190.1 median201.0 std78.6 best-iNshh(30,200,4,448*,185) can2m3
h(yi,yg)@L2c0 with n29 min173.0 max351.0 mean229.9 median229.0 std34.1 best-iNshh(14,80,10,351*,227) can2m3
h(yi,yg)@L2c1 with n47 min66.0 max448.0 mean201.0 median188.0 std73.0 best-iNshh(30,200,4,448*,199) can2m3
h(yi,yg)@L2c2 with n7 min56.0 max76.0 mean60.9 median59.0 std6.4 best-iNshh(77,50,14,76*,60) can2m3
h(yi,yg)@L2c3 with n6 min61.0 max65.0 mean63.0 median63.0 std1.4 best-iNshh(85,110,13,65*,148) can2m3
hi-LOOCV@L0c0 with n89 min60.2 max192.2 mean152.0 median169.5 std41.9 best-iNshh(7,140,7,231,192*) can2m3
hi-LOOCV@L2c0 with n29 min147.7 max257.0 mean219.4 median227.4 std27.8 best-iNshh(7,140,7,231,257*) can2m3
hi-LOOCV@L2c1 with n47 min61.8 max205.8 mean176.7 median187.7 std28.7 best-iNshh(17,140,4,288,206*) can2m3
hi-LOOCV@L2c2 with n7 min59.7 max186.0 mean145.9 median162.5 std44.9 best-iNshh(82,50,1,59,186*) can2m3
hi-LOOCV@L2c3 with n6 min147.8 max253.4 mean195.5 median177.2 std41.9 best-iNshh(76,110,1,64,253*) can2m3


#Fri Jun 12 19:08:37 JST 2020 TP0=2400 N:50-200:30 ns=20 ==>(hV,hg)=(288,448) 237
h(yi,yg)@L0c0 with n118 min56.0 max448.0 mean186.4 median201.0 std78.3 best-iNshh(32,200,4,448*,183) can2m2-2
h(yi,yg)@L2c0 with n6 min56.0 max76.0 mean60.8 median58.5 std6.9 best-iNshh(105,50,14,76*,59) can2m2-2
h(yi,yg)@L2c1 with n13 min60.0 max66.0 mean62.5 median62.0 std1.7 best-iNshh(115,110,15,66*,66) can2m2-2
h(yi,yg)@L2c2 with n38 min173.0 max351.0 mean233.6 median229.0 std37.0 best-iNshh(6,80,10,351*,233) can2m2-2
h(yi,yg)@L2c3 with n61 min66.0 max448.0 mean195.8 median186.0 std68.5 best-iNshh(32,200,4,448*,195) can2m2-2
hi-LOOCV@L0c0 with n118 min60.8 max187.8 mean148.0 median165.2 std40.7 best-iNshh(10,140,13,237,188*) can2m2-2
hi-LOOCV@L2c0 with n6 min59.0 max181.2 mean139.3 median156.5 std46.5 best-iNshh(107,50,1,59,181*) can2m2-2
hi-LOOCV@L2c1 with n13 min65.8 max190.3 mean153.8 median159.9 std33.5 best-iNshh(98,110,1,64,190*) can2m2-2
hi-LOOCV@L2c2 with n38 min155.5 max254.4 mean225.0 median233.0 std25.2 best-iNshh(12,170,5,227,254*) can2m2-2
hi-LOOCV@L2c3 with n61 min61.8 max200.2 mean174.6 median185.1 std26.4 best-iNshh(25,140,4,288,200*) can2m2-2

#Fri Jun 12 18:36:50 JST 2020 TP0=2000 N:50-200:30 ns=15 ==>(hV,hg)=(189,414) 191
h(yi,yg)@L0c0 with n87 min21.0 max414.0 mean180.0 median188.0 std64.3 best-iNshh(40,80,10,414*,169) can2m3
h(yi,yg)@L2c0 with n14 min21.0 max197.0 mean175.4 median191.5 std44.4 best-iNshh(31,200,5,197*,203) can2m3
h(yi,yg)@L2c1 with n36 min97.0 max414.0 mean193.3 median189.5 std54.7 best-iNshh(40,80,10,414*,182) can2m3
h(yi,yg)@L2c2 with n32 min98.0 max391.0 mean186.0 median171.5 std65.1 best-iNshh(19,80,12,391*,178) can2m3
h(yi,yg)@L2c3 with n5 min21.0 max116.0 mean59.4 median30.0 std40.5 best-iNshh(82,110,7,116*,106) can2m3
hi-LOOCV@L0c0 with n87 min20.2 max186.9 mean156.2 median170.9 std34.7 best-iNshh(6,140,0,191,187*) can2m3
hi-LOOCV@L2c0 with n14 min17.1 max216.2 mean188.6 median207.0 std51.5 best-iNshh(44,170,8,181,216*) can2m3
hi-LOOCV@L2c1 with n36 min97.1 max215.8 mean184.6 median192.2 std26.2 best-iNshh(0,80,8,189,216*) can2m3
hi-LOOCV@L2c2 with n32 min107.2 max181.5 mean157.2 median160.5 std22.2 best-iNshh(21,80,13,217,181*) can2m3
hi-LOOCV@L2c3 with n5 min77.5 max118.8 mean104.9 median106.5 std14.7 best-iNshh(83,80,11,29,119*) can2m3

#Fri Jun 12 19:05:15 JST 2020 TP0=2300 N:50-200:30 ns=15 ==>(hV,hg)=(186,273) 189
h(yi,yg)@L0c0 with n88 min61.0 max273.0 mean118.6 median110.5 std54.5 best-iNshh(36,80,12,273*,119) can2m3
h(yi,yg)@L2c0 with n23 min61.0 max68.0 mean65.9 median66.0 std1.4 best-iNshh(81,50,9,68*,107) can2m3
h(yi,yg)@L2c1 with n15 min67.0 max69.0 mean68.1 median68.0 std0.6 best-iNshh(44,80,4,69*,249)(45,110,7,69*,253)(62,200,0,69*,255)(78,140,14,69*,199) can2m3
h(yi,yg)@L2c2 with n23 min70.0 max273.0 mean162.1 median168.0 std46.7 best-iNshh(36,80,12,273*,162) can2m3
h(yi,yg)@L2c3 with n27 min72.0 max192.0 mean154.4 median167.0 std33.6 best-iNshh(7,170,11,192*,194) can2m3
hi-LOOCV@L0c0 with n88 min74.0 max135.4 mean110.0 median111.0 std14.5 best-iNshh(0,170,3,189,135*) can2m3
hi-LOOCV@L2c0 with n23 min91.6 max187.2 mean157.0 median173.1 std28.5 best-iNshh(32,50,0,65,187*) can2m3
hi-LOOCV@L2c1 with n15 min126.9 max260.4 mean235.1 median248.9 std35.1 best-iNshh(3,80,6,68,260*) can2m3
hi-LOOCV@L2c2 with n23 min73.4 max188.9 mean154.6 median167.6 std30.5 best-iNshh(65,50,4,190,189*) can2m3
hi-LOOCV@L2c3 with n27 min99.2 max209.7 mean166.8 median171.0 std33.7 best-iNshh(4,110,14,186,210*) can2m3

#Fri Jun 12 19:03:22 JST 2020 TP0=2500 N:50-100:10 ns=15 ==>(hV,hg)=(249,346) 249
h(yi,yg)@L0c0 with n88 min114.0 max346.0 mean203.2 median223.5 std63.1 best-iNshh(13,70,2,346*,204) can2m-2
h(yi,yg)@L2c0 with n7 min114.0 max164.0 mean147.4 median159.0 std20.9 best-iNshh(73,50,10,164*,192) can2m-2
h(yi,yg)@L2c1 with n52 min148.0 max346.0 mean248.4 median248.5 std40.9 best-iNshh(13,70,2,346*,249) can2m-2
h(yi,yg)@L2c2 with n21 min132.0 max139.0 mean134.8 median135.0 std1.6 best-iNshh(85,100,11,139*,138) can2m-2
h(yi,yg)@L2c3 with n8 min137.0 max138.0 mean137.5 median137.5 std0.5 best-iNshh(75,50,14,138*,300)(78,60,13,138*,285)(80,80,14,138*,254)(83,100,10,138*,207) can2m-2
hi-LOOCV@L0c0 with n88 min122.7 max209.2 mean180.7 median186.9 std21.7 best-iNshh(2,100,14,249,209*) can2m-2
hi-LOOCV@L2c0 with n7 min191.7 max233.8 mean213.8 median211.0 std14.1 best-iNshh(71,70,4,159,234*) can2m-2
hi-LOOCV@L2c1 with n52 min175.6 max258.4 mean236.1 median244.9 std20.3 best-iNshh(2,100,14,249,258*) can2m-2
hi-LOOCV@L2c2 with n21 min138.1 max257.9 mean225.0 median229.4 std27.8 best-iNshh(55,60,12,136,258*) can2m-2
hi-LOOCV@L2c3 with n8 min207.3 max300.3 mean270.2 median276.1 std27.1 best-iNshh(75,50,14,138,300*) can2m-2

#Fri Jun 12 18:59:55 JST 2020 TP0=2900 N:50-100:10 ns=20 ==>(hV,hg)=(215,492) 215
h(yi,yg)@L0c0 with n117 min70.0 max492.0 mean160.3 median188.0 std78.3 best-iNshh(32,90,8,492*,157) can2m1
h(yi,yg)@L2c0 with n62 min76.0 max492.0 mean207.3 median205.5 std59.4 best-iNshh(32,90,8,492*,202) can2m1
h(yi,yg)@L2c1 with n18 min78.0 max314.0 mean176.2 median212.0 std65.8 best-iNshh(63,90,4,314*,210) can2m1
h(yi,yg)@L2c2 with n30 min70.0 max77.0 mean73.1 median73.0 std1.6 best-iNshh(114,100,11,77*,84)(115,100,2,77*,84) can2m1
h(yi,yg)@L2c3 with n7 min75.0 max76.0 mean75.9 median76.0 std0.3 best-iNshh(103,80,10,76*,214)(104,100,10,76*,274)(105,70,14,76*,263)(109,60,2,76*,236)(110,90,19,76*,271)(112,90,13,76*,228) can2m1
hi-LOOCV@L0c0 with n117 min82.8 max168.1 mean131.4 median140.0 std26.6 best-iNshh(2,90,1,215,168*) can2m1
hi-LOOCV@L2c0 with n62 min78.9 max215.4 mean192.0 median203.0 std29.4 best-iNshh(2,90,1,215,215*) can2m1
hi-LOOCV@L2c1 with n18 min132.6 max263.1 mean213.9 median228.0 std38.1 best-iNshh(75,80,15,86,263*) can2m1
hi-LOOCV@L2c2 with n30 min83.6 max211.4 mean188.8 median197.0 std32.2 best-iNshh(77,70,2,74,211*) can2m1
hi-LOOCV@L2c3 with n7 min209.3 max274.2 mean242.4 median236.3 std25.0 best-iNshh(104,100,10,76,274*) can2m1

#Fri Jun 12 18:56:56 JST 2020 TP0=2400 N:50-100:10 ns=15 ==>(hV,hg)=(202,351) 350
h(yi,yg)@L0c0 with n86 min56.0 max351.0 mean166.8 median200.0 std81.0 best-iNshh(22,80,10,351*,163) can2m-2
h(yi,yg)@L2c0 with n24 min56.0 max64.0 mean60.8 median61.0 std2.3 best-iNshh(75,80,7,64*,141)(76,90,6,64*,126)(79,100,14,64*,113) can2m-2
h(yi,yg)@L2c1 with n1 min66.0 max66.0 mean66.0 median66.0 std0.0 best-iNshh(84,100,6,66*,-1) can2m-2
h(yi,yg)@L2c2 with n22 min173.0 max351.0 mean240.9 median233.0 std43.2 best-iNshh(22,80,10,351*,239) can2m-2
h(yi,yg)@L2c3 with n37 min68.0 max322.0 mean199.4 median201.0 std42.0 best-iNshh(17,100,7,322*,197) can2m-2
hi-LOOCV@L0c0 with n86 min64.1 max168.3 mean128.6 median141.6 std34.0 best-iNshh(3,90,10,350,168*) can2m-2
hi-LOOCV@L2c0 with n24 min91.7 max202.7 mean153.8 median158.4 std25.5 best-iNshh(58,90,5,62,203*) can2m-2
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(84,100,6,66,-1*) can2m-2
hi-LOOCV@L2c2 with n22 min173.8 max248.2 mean226.7 median236.5 std20.2 best-iNshh(3,90,10,350,248*) can2m-2
hi-LOOCV@L2c3 with n37 min125.5 max215.5 mean190.8 median197.6 std21.9 best-iNshh(14,100,2,202,216*) can2m-2

#Fri Jun 12 18:55:55 JST 2020 TP0=2200 N:50-200:30 ns=15 ==>(hV,hg)=(186,362) 186
h(yi,yg)@L2c0 with n43 min72.0 max362.0 mean166.1 median167.0 std46.2 best-iNshh(46,50,18,362*,163) can2m2-2
h(yi,yg)@L2c1 with n28 min70.0 max273.0 mean154.5 median167.5 std49.8 best-iNshh(29,80,12,273*,161) can2m2-2
h(yi,yg)@L2c2 with n16 min68.0 max69.0 mean68.2 median68.0 std0.4 best-iNshh(62,80,4,69*,259)(64,110,7,69*,258)(89,200,0,69*,262)(107,140,14,69*,224) can2m2-2
h(yi,yg)@L2c3 with n31 min61.0 max68.0 mean66.0 median66.0 std1.3 best-iNshh(110,50,9,68*,108) can2m2-2
hi-LOOCV@L2c0 with n43 min98.2 max204.2 mean166.0 median163.0 std27.5 best-iNshh(19,110,14,186,204*) can2m2-2
hi-LOOCV@L2c1 with n28 min74.3 max199.5 mean159.3 median166.8 std32.3 best-iNshh(78,140,18,179,200*) can2m2-2
hi-LOOCV@L2c2 with n16 min127.0 max267.1 mean247.2 median257.2 std32.6 best-iNshh(34,50,13,68,267*) can2m2-2
hi-LOOCV@L2c3 with n31 min91.4 max192.1 mean165.7 median178.9 std28.6 best-iNshh(69,170,9,66,192*) can2m2-2

#Fri Jun 12 18:51:45 JST 2020 TP0=2800 N:50-100:10 ns=20 ==>(hV,hg)=(259,378) 259
h(yi,yg)@L0c0 with n120 min52.0 max378.0 mean167.2 median166.5 std68.8 best-iNshh(28,90,17,378*,160) can2m1
h(yi,yg)@L2c0 with n92 min108.0 max378.0 mean190.7 median169.5 std58.6 best-iNshh(28,90,17,378*,179) can2m1
h(yi,yg)@L2c1 with n16 min54.0 max136.0 mean98.3 median106.0 std26.9 best-iNshh(89,100,3,136*,122) can2m1
h(yi,yg)@L2c2 with n9 min63.0 max175.0 mean88.7 median65.0 std45.9 best-iNshh(91,80,11,175*,160) can2m1
h(yi,yg)@L2c3 with n1 min52.0 max52.0 mean52.0 median52.0 std0.0 best-iNshh(119,70,12,52*,-1) can2m1
hi-LOOCV@L0c0 with n120 min53.8 max166.1 mean136.4 median151.1 std29.9 best-iNshh(5,100,14,259,166*) can2m1
hi-LOOCV@L2c0 with n92 min109.2 max187.6 mean169.5 median174.2 std15.0 best-iNshh(5,100,14,259,188*) can2m1
hi-LOOCV@L2c1 with n16 min68.7 max139.1 mean113.5 median120.4 std21.1 best-iNshh(99,80,3,108,139*) can2m1
hi-LOOCV@L2c2 with n9 min159.8 max261.0 mean223.8 median229.9 std27.1 best-iNshh(101,100,9,63,261*) can2m1
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(119,70,12,52,-1*) can2m1

#Fri Jun 12 18:50:48 JST 2020 TP0=2300 N:50-100:10 ns=15 ==>(hV,hg)=(191,361) 168
h(yi,yg)@L0c0 with n89 min65.0 max361.0 mean136.1 median126.0 std57.6 best-iNshh(12,60,14,361*,137) can2m-2
h(yi,yg)@L2c0 with n47 min70.0 max361.0 mean162.3 median166.0 std50.2 best-iNshh(12,60,14,361*,158) can2m-2
h(yi,yg)@L2c1 with n24 min78.0 max245.0 mean136.6 median154.5 std49.6 best-iNshh(1,50,12,245*,166) can2m-2
h(yi,yg)@L2c2 with n8 min68.0 max69.0 mean68.5 median68.5 std0.5 best-iNshh(74,80,4,69*,269)(77,90,4,69*,256)(79,100,9,69*,203)(80,90,12,69*,256) can2m-2
h(yi,yg)@L2c3 with n10 min65.0 max68.0 mean66.3 median66.0 std1.0 best-iNshh(71,80,6,68*,193)(86,50,9,68*,109) can2m-2
hi-LOOCV@L0c0 with n89 min72.8 max150.0 mean115.9 median119.0 std20.4 best-iNshh(0,90,6,168,150*) can2m-2
hi-LOOCV@L2c0 with n47 min69.6 max171.8 mean150.5 median152.9 std18.0 best-iNshh(9,60,1,191,172*) can2m-2
hi-LOOCV@L2c1 with n24 min84.7 max200.6 mean170.2 median178.5 std27.9 best-iNshh(60,60,11,79,201*) can2m-2
hi-LOOCV@L2c2 with n8 min127.9 max268.9 mean236.6 median255.9 std45.7 best-iNshh(74,80,4,69,269*) can2m-2
hi-LOOCV@L2c3 with n10 min108.6 max193.1 mean166.7 median170.6 std23.3 best-iNshh(71,80,6,68,193*) can2m-2

#Fri Jun 12 18:46:13 JST 2020 TP0=2100 N:50-200:30 ns=15 ==>(hV,hg)=(92,321) 93
h(yi,yg)@L0c0 with n86 min88.0 max321.0 mean129.1 median95.0 std62.8 best-iNshh(43,170,1,321*,124) can2m3
h(yi,yg)@L2c0 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(84,50,9,98*,-1) can2m3
h(yi,yg)@L2c1 with n35 min97.0 max321.0 mean182.8 median176.0 std69.4 best-iNshh(43,170,1,321*,176) can2m3
h(yi,yg)@L2c2 with n37 min88.0 max97.0 mean91.2 median91.0 std1.5 best-iNshh(85,170,12,97*,93) can2m3
h(yi,yg)@L2c3 with n11 min93.0 max96.0 mean94.5 median95.0 std1.1 best-iNshh(64,200,3,96*,215)(68,170,11,96*,197) can2m3
hi-LOOCV@L0c0 with n86 min95.8 max161.8 mean131.3 median126.2 std19.6 best-iNshh(0,50,4,93,162*) can2m3
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(84,50,9,98,-1*) can2m3
hi-LOOCV@L2c1 with n35 min104.8 max185.1 mean157.0 median163.4 std22.7 best-iNshh(40,110,2,261,185*) can2m3
hi-LOOCV@L2c2 with n37 min93.0 max222.6 mean199.2 median206.7 std28.5 best-iNshh(1,80,6,92,223*) can2m3
hi-LOOCV@L2c3 with n11 min196.7 max274.9 mean229.7 median217.0 std24.0 best-iNshh(55,170,14,95,275*) can2m3

#Fri Jun 12 18:44:45 JST 2020 TP0=2200 N:50-100:10 ns=15 ==>(hV,hg)=(166,371) 166
h(yi,yg)@L0c0 with n89 min46.0 max371.0 mean171.0 median165.0 std49.8 best-iNshh(40,80,12,371*,170) can2m-2
h(yi,yg)@L2c0 with n82 min89.0 max371.0 mean177.5 median166.0 std46.0 best-iNshh(40,80,12,371*,176) can2m-2
h(yi,yg)@L2c1 with n6 min97.0 max105.0 mean103.2 median104.5 std2.9 best-iNshh(81,60,14,105*,192)(82,60,12,105*,197)(83,70,10,105*,137) can2m-2
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(88,90,2,46*,-1) can2m-2
hi-LOOCV@L0c0 with n89 min46.1 max177.9 mean157.1 median166.9 std24.5 best-iNshh(2,90,4,166,178*) can2m-2
hi-LOOCV@L2c0 with n82 min87.1 max185.0 mean167.9 median175.9 std18.3 best-iNshh(2,90,4,166,185*) can2m-2
hi-LOOCV@L2c1 with n6 min97.4 max196.6 mean155.9 median158.5 std36.2 best-iNshh(82,60,12,105,197*) can2m-2
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(88,90,2,46,-1*) can2m-2

#Fri Jun 12 18:43:29 JST 2020 TP0=2700 N:50-100:10 ns=20 ==>(hV,hg)=(174,300) 174
h(yi,yg)@L0c0 with n117 min86.0 max300.0 mean167.0 median151.0 std46.0 best-iNshh(10,60,19,300*,168) can2m1
h(yi,yg)@L2c0 with n1 min87.0 max87.0 mean87.0 median8]),)
h(yi,yg)@L2c1 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(116,50,5,86*,-1) can2m1
h(yi,yg)@L2c2 with n102 min89.0 max300.0 mean175.6 median167.5 std42.7 best-iNshh(10,60,19,300*,177) can2m1
h(yi,yg)@L2c3 with n11 min112.0 max119.0 mean116.1 median116.0 std1.9 best-iNshh(101,80,14,119*,124) can2m1
hi-LOOCV@L0c0 with n117 min88.7 max171.8 mean153.1 median160.0 std19.0 best-iNshh(3,50,12,174,172*) can2m1
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(115,50,7,87,-1*) can2m1
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(116,50,5,86,-1*) can2m1
hi-LOOCV@L2c2 with n102 min90.6 max180.9 mean166.5 median168.9 std12.0 best-iNshh(3,50,12,174,181*) can2m1
hi-LOOCV@L2c3 with n11 min123.7 max219.5 mean183.8 median186.0 std28.0 best-iNshh(107,70,1,116,220*) can2m1

????#Fri Jun 12 18:43:27 JST 2020 TP0=2200 N:50-200:30 ns=20 ==>(hV,hg)=(174,300) 174
h(yi,yg)@L0c0 with n117 min86.0 max300.0 mean167.0 median151.0 std46.0 best-iNshh(10,60,19,300*,168) can2m1
h(yi,yg)@L2c0 with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(115,50,7,87*,-1) can2m1
h(yi,yg)@L2c1 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(116,50,5,86*,-1) can2m1
h(yi,yg)@L2c2 with n102 min89.0 max300.0 mean175.6 median167.5 std42.7 best-iNshh(10,60,19,300*,177) can2m1
h(yi,yg)@L2c3 with n11 min112.0 max119.0 mean116.1 median116.0 std1.9 best-iNshh(101,80,14,119*,124) can2m1
hi-LOOCV@L0c0 with n117 min88.7 max171.8 mean153.1 median160.0 std19.0 best-iNshh(3,50,12,174,172*) can2m1
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(115,50,7,87,-1*) can2m1
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(116,50,5,86,-1*) can2m1
hi-LOOCV@L2c2 with n102 min90.6 max180.9 mean166.5 median168.9 std12.0 best-iNshh(3,50,12,174,181*) can2m1
hi-LOOCV@L2c3 with n11 min123.7 max219.5 mean183.8 median186.0 std28.0 best-iNshh(107,70,1,116,220*) can2m1

#Fri Jun 12 18:32:28 JST 2020 TP0=2000 N:50-100:10 ns=15 ==>(hV,hg)=(157,414) 187
h(yi,yg)@L0c0 with n85 min29.0 max414.0 mean165.5 median157.0 std59.2 best-iNshh(54,80,10,414*,158) can2m-2
h(yi,yg)@L2c0 with n27 min180.0 max414.0 mean211.6 median188.0 std57.7 best-iNshh(54,80,10,414*,193) can2m-2
h(yi,yg)@L2c1 with n19 min137.0 max218.0 mean166.6 median157.0 std23.1 best-iNshh(1,70,13,218*,189) can2m-2
h(yi,yg)@L2c2 with n34 min29.0 max295.0 mean137.3 median156.0 std52.7 best-iNshh(31,90,9,295*,161) can2m-2
h(yi,yg)@L2c3 with n5 min98.0 max123.0 mean104.0 median99.0 std9.5 best-iNshh(72,80,14,123*,127) can2m-2
hi-LOOCV@L0c0 with n85 min71.6 max172.8 mean148.5 median161.5 std24.8 best-iNshh(4,90,1,187,173*) can2m-2
hi-LOOCV@L2c0 with n27 min165.3 max242.5 mean204.5 median204.8 std20.4 best-iNshh(4,90,1,187,243*) can2m-2
hi-LOOCV@L2c1 with n19 min118.0 max208.4 mean182.5 median188.9 std23.2 best-iNshh(13,60,14,158,208*) can2m-2
hi-LOOCV@L2c2 with n34 min130.2 max194.9 mean169.6 median169.6 std18.1 best-iNshh(5,80,9,157,195*) can2m-2
hi-LOOCV@L2c3 with n5 min80.0 max175.2 mean140.2 median156.5 std34.0 best-iNshh(82,50,5,98,175*) can2m-2

#Fri Jun 12 18:38:33 JST 2020 TP0=2100 N:50-100:10 ns=15 ==>(hV,hg)=(99,291) 205
h(yi,yg)@L0c0 with n86 min90.0 max291.0 mean140.7 median99.0 std58.6 best-iNshh(13,80,12,291*,144) can2m-2
h(yi,yg)@L2c0 with n28 min90.0 max98.0 mean91.7 median92.0 std1.5 best-iNshh(83,100,9,98*,93) can2m-2
h(yi,yg)@L2c1 with n1 min96.0 max96.0 mean96.0 median96.0 std0.0 best-iNshh(84,70,11,96*,-1) can2m-2
h(yi,yg)@L2c2 with n45 min96.0 max291.0 mean160.2 median174.0 std55.4 best-iNshh(13,80,12,291*,185) can2m-2
h(yi,yg)@L2c3 with n12 min98.0 max270.0 mean185.6 median205.0 std62.1 best-iNshh(37,60,8,270*,180) can2m-2
hi-LOOCV@L0c0 with n86 min96.1 max152.5 mean130.9 median131.6 std13.0 best-iNshh(10,70,3,205,153*) can2m-2
hi-LOOCV@L2c0 with n28 min93.4 max230.3 mean203.6 median220.5 std31.4 best-iNshh(29,80,4,92,230*) can2m-2
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(84,70,11,96,-1*) can2m-2
hi-LOOCV@L2c2 with n45 min91.2 max190.8 mean173.6 median181.1 std19.6 best-iNshh(32,70,1,99,191*) can2m-2
hi-LOOCV@L2c3 with n12 min109.9 max225.3 mean195.8 median203.8 std30.2 best-iNshh(52,100,6,265,225*) can2m-2

#Fri Jun 12 18:34:45 JST 2020 TP0=2600 N:50-100:10 ns=20 ==>(hV,hg)=(154,337) 185
h(yi,yg)@L0c0 with n120 min116.0 max337.0 mean168.7 median153.0 std42.0 best-iNshh(22,60,17,337*,167) can2m1
h(yi,yg)@L2c0 with n8 min116.0 max128.0 mean126.2 median128.0 std3.9 best-iNshh(94,90,4,128*,265)(97,60,10,128*,263)(101,80,19,128*,228)(102,50,15,128*,198)(107,70,5,128*,253) can2m1
h(yi,yg)@L2c1 with n20 min124.0 max127.0 mean125.5 median125.0 std1.1 best-iNshh(92,50,19,127*,224)(93,70,19,127*,222)(99,60,6,127*,225)(100,60,8,127*,224)(103,60,4,127*,223) can2m1
h(yi,yg)@L2c2 with n40 min144.0 max251.0 mean153.2 median151.0 std16.0 best-iNshh(13,100,10,251*,182) can2m1
h(yi,yg)@L2c3 with n52 min129.0 max337.0 mean203.7 median185.0 std38.2 best-iNshh(22,60,17,337*,201) can2m1
hi-LOOCV@L0c0 with n120 min116.3 max178.6 mean159.1 median164.1 std13.1 best-iNshh(8,90,8,185,179*) can2m1
hi-LOOCV@L2c0 with n8 min115.1 max264.6 mean209.5 median224.4 std53.9 best-iNshh(94,90,4,128,265*) can2m1
hi-LOOCV@L2c1 with n20 min156.7 max225.1 mean209.0 median209.6 std15.2 best-iNshh(99,60,6,127,225*) can2m1
hi-LOOCV@L2c2 with n40 min181.6 max219.6 mean202.1 median204.8 std9.9 best-iNshh(40,60,11,154,220*) can2m1
hi-LOOCV@L2c3 with n52 min139.5 max227.4 mean202.7 median203.7 std16.9 best-iNshh(8,90,8,185,227*) can2m1

#Fri Jun 12 18:32:28 JST 2020 TP0=2000 N:50-100:10 ns=15 ==>(hV,hg)=(157,414) 187
h(yi,yg)@L0c0 with n85 min29.0 max414.0 mean165.5 median157.0 std59.2 best-iNshh(54,80,10,414*,158) can2m-2
h(yi,yg)@L2c0 with n27 min180.0 max414.0 mean211.6 median188.0 std57.7 best-iNshh(54,80,10,414*,193) can2m-2
h(yi,yg)@L2c1 with n19 min137.0 max218.0 mean166.6 median157.0 std23.1 best-iNshh(1,70,13,218*,189) can2m-2
h(yi,yg)@L2c2 with n34 min29.0 max295.0 mean137.3 median156.0 std52.7 best-iNshh(31,90,9,295*,161) can2m-2
h(yi,yg)@L2c3 with n5 min98.0 max123.0 mean104.0 median99.0 std9.5 best-iNshh(72,80,14,123*,127) can2m-2
hi-LOOCV@L0c0 with n85 min71.6 max172.8 mean148.5 median161.5 std24.8 best-iNshh(4,90,1,187,173*) can2m-2
hi-LOOCV@L2c0 with n27 min165.3 max242.5 mean204.5 median204.8 std20.4 best-iNshh(4,90,1,187,243*) can2m-2
hi-LOOCV@L2c1 with n19 min118.0 max208.4 mean182.5 median188.9 std23.2 best-iNshh(13,60,14,158,208*) can2m-2
hi-LOOCV@L2c2 with n34 min130.2 max194.9 mean169.6 median169.6 std18.1 best-iNshh(5,80,9,157,195*) can2m-2
hi-LOOCV@L2c3 with n5 min80.0 max175.2 mean140.2 median156.5 std34.0 best-iNshh(82,50,5,98,175*) can2m-2

#Fri Jun 12 18:30:27 JST 2020 TP0=2100 N:50-200:30 ns=20 ==>(hV,hg)=(92,321) 92
h(yi,yg)@L0c0 with n116 min88.0 max321.0 mean129.7 median95.0 std62.6 best-iNshh(52,170,1,321*,129) can2m2-2
h(yi,yg)@L2c0 with n54 min88.0 max97.0 mean91.4 median91.0 std1.4 best-iNshh(115,170,12,97*,93) can2m2-2
h(yi,yg)@L2c1 with n10 min94.0 max96.0 mean95.1 median95.0 std0.7 best-iNshh(91,200,3,96*,275)(101,170,11,96*,255)(104,110,15,96*,249) can2m2-2
h(yi,yg)@L2c2 with n48 min88.0 max321.0 mean182.4 median175.5 std68.7 best-iNshh(52,170,1,321*,185) can2m2-2
h(yi,yg)@L2c3 with n4 min96.0 max116.0 mean101.5 median97.0 std8.4 best-iNshh(111,50,19,116*,120) can2m2-2
hi-LOOCV@L0c0 with n116 min95.8 max163.8 mean132.6 median129.5 std19.2 best-iNshh(9,170,15,92,164*) can2m2-2
hi-LOOCV@L2c0 with n54 min93.4 max230.4 mean206.2 median213.5 std27.3 best-iNshh(9,170,15,92,230*) can2m2-2
hi-LOOCV@L2c1 with n10 min210.8 max317.3 mean257.4 median252.1 std33.3 best-iNshh(86,170,14,95,317*) can2m2-2
hi-LOOCV@L2c2 with n48 min101.5 max192.6 mean160.5 median166.6 std22.5 best-iNshh(48,200,7,259,193*) can2m2-2
hi-LOOCV@L2c3 with n4 min114.0 max164.3 mean139.2 median139.2 std22.5 best-iNshh(109,110,6,96,164*) can2m2-2

#Fri Jun 12 18:26:38 JST 2020 TP0=2500 N:50-100:10 ns=20 ==>(hV,hg)=(202,354) 237
h(yi,yg)@L0c0 with n116 min56.0 max354.0 mean162.2 median180.5 std80.9 best-iNshh(29,90,16,354*,157) can2m1
h(yi,yg)@L2c0 with n33 min56.0 max64.0 mean60.9 median61.0 std2.2 best-iNshh(102,80,7,64*,142)(104,90,6,64*,132)(106,100,14,64*,119) can2m1
h(yi,yg)@L2c1 with n1 min66.0 max66.0 mean66.0 median66.0 std0.0 best-iNshh(115,100,6,66*,-1) can2m1
h(yi,yg)@L2c2 with n31 min173.0 max351.0 mean235.5 median230.0 std38.0 best-iNshh(11,80,10,351*,234) can2m1
h(yi,yg)@L2c3 with n49 min68.0 max354.0 mean189.7 median201.0 std54.6 best-iNshh(29,90,16,354*,188) can2m1
hi-LOOCV@L0c0 with n116 min64.1 max162.0 mean125.0 median135.9 std31.6 best-iNshh(4,70,19,237,162*) can2m1
hi-LOOCV@L2c0 with n33 min92.7 max199.2 mean157.9 median163.6 std24.8 best-iNshh(75,90,5,62,199*) can2m1
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(115,100,6,66,-1*) can2m1
hi-LOOCV@L2c2 with n31 min172.5 max249.1 mean225.5 median234.0 std21.9 best-iNshh(16,100,11,226,249*) can2m1
hi-LOOCV@L2c3 with n49 min85.2 max201.6 mean176.5 median185.6 std25.7 best-iNshh(28,100,2,202,202*) can2m1

#Fri Jun 12 18:18:38 JST 2020 TP0=2400 N:50-100:10 ns=20 ==>(hV,hg)=(202,354) 237
h(yi,yg)@L0c0 with n116 min56.0 max354.0 mean162.2 median180.5 std80.9 best-iNshh(29,90,16,354*,157) can2m1
h(yi,yg)@L2c0 with n33 min56.0 max64.0 mean60.9 median61.0 std2.2 best-iNshh(102,80,7,64*,142)(104,90,6,64*,132)(106,100,14,64*,119) can2m1
h(yi,yg)@L2c1 with n1 min66.0 max66.0 mean66.0 median66.0 std0.0 best-iNshh(115,100,6,66*,-1) can2m1
h(yi,yg)@L2c2 with n31 min173.0 max351.0 mean235.5 median230.0 std38.0 best-iNshh(11,80,10,351*,234) can2m1
h(yi,yg)@L2c3 with n49 min68.0 max354.0 mean189.7 median201.0 std54.6 best-iNshh(29,90,16,354*,188) can2m1
hi-LOOCV@L0c0 with n116 min64.1 max162.0 mean125.0 median135.9 std31.6 best-iNshh(4,70,19,237,162*) can2m1
hi-LOOCV@L2c0 with n33 min92.7 max199.2 mean157.9 median163.6 std24.8 best-iNshh(75,90,5,62,199*) can2m1
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(115,100,6,66,-1*) can2m1
hi-LOOCV@L2c2 with n31 min172.5 max249.1 mean225.5 median234.0 std21.9 best-iNshh(16,100,11,226,249*) can2m1
hi-LOOCV@L2c3 with n49 min85.2 max201.6 mean176.5 median185.6 std25.7 best-iNshh(28,100,2,202,202*) can2m1

#Fri Jun 12 18:18:12 JST 2020 TP0=2000 N:50-200:30 ns=20 ==>(hV,hg)=(191,414) 194
h(yi,yg)@L0c0 with n116 min20.0 max414.0 mean175.5 median186.0 std62.4 best-iNshh(54,80,10,414*,169) can2m2-2
h(yi,yg)@L2c0 with n55 min97.0 max414.0 mean195.3 median190.0 std52.5 best-iNshh(54,80,10,414*,185) can2m2-2
h(yi,yg)@L2c1 with n20 min20.0 max197.0 mean172.1 median194.0 std51.6 best-iNshh(48,200,5,197*,204)(49,140,17,197*,209) can2m2-2
h(yi,yg)@L2c2 with n8 min21.0 max129.0 mean60.8 median30.0 std42.9 best-iNshh(102,80,16,129*,116) can2m2-2
h(yi,yg)@L2c3 with n33 min71.0 max355.0 mean172.5 median157.0 std56.1 best-iNshh(76,140,11,355*,168) can2m2-2
hi-LOOCV@L0c0 with n116 min20.0 max187.4 mean154.4 median170.1 std38.3 best-iNshh(5,140,2,194,187*) can2m2-2
hi-LOOCV@L2c0 with n55 min97.1 max214.6 mean189.4 median198.4 std24.3 best-iNshh(15,140,0,191,215*) can2m2-2
hi-LOOCV@L2c1 with n20 min17.8 max222.1 mean184.4 median205.6 std58.7 best-iNshh(58,170,17,196,222*) can2m2-2
hi-LOOCV@L2c2 with n8 min78.4 max132.7 mean117.0 median120.4 std15.3 best-iNshh(112,50,19,30,133*) can2m2-2
hi-LOOCV@L2c3 with n33 min72.5 max176.5 mean150.6 median157.7 std24.4 best-iNshh(53,110,9,219,177*) can2m2-2

#Fri Jun 12 18:10:39 JST 2020 TP0=2300 N:50-100:10 ns=20 ==>(hV,hg)=(191,362) 168
h(yi,yg)@L0c0 with n118 min65.0 max362.0 mean136.7 median145.0 std58.8 best-iNshh(33,50,18,362*,131) can2m1
h(yi,yg)@L2c0 with n62 min70.0 max362.0 mean164.9 median163.5 std51.0 best-iNshh(33,50,18,362*,162) can2m1
h(yi,yg)@L2c1 with n35 min70.0 max245.0 mean128.3 median124.0 std51.5 best-iNshh(1,50,12,245*,162) can2m1
h(yi,yg)@L2c2 with n12 min65.0 max68.0 mean66.3 median66.0 std0.9 best-iNshh(95,80,6,68*,193)(115,50,9,68*,109) can2m1
h(yi,yg)@L2c3 with n9 min68.0 max69.0 mean68.6 median69.0 std0.5 best-iNshh(97,80,4,69*,261)(104,60,19,69*,200)(106,90,4,69*,250)(107,100,9,69*,205)(109,90,12,69*,250) can2m1
hi-LOOCV@L0c0 with n118 min72.7 max154.2 mean116.3 median118.6 std21.0 best-iNshh(0,90,6,168,154*) can2m1
hi-LOOCV@L2c0 with n62 min69.1 max172.7 mean153.1 median155.2 std17.8 best-iNshh(14,60,1,191,173*) can2m1
hi-LOOCV@L2c1 with n35 min86.0 max203.8 mean168.7 median179.9 std30.7 best-iNshh(69,60,11,79,204*) can2m1
hi-LOOCV@L2c2 with n12 min108.5 max193.2 mean170.5 median176.3 std22.7 best-iNshh(95,80,6,68,193*) can2m1
hi-LOOCV@L2c3 with n9 min127.8 max261.4 mean228.4 median249.6 std41.8 best-iNshh(97,80,4,69,261*) can2m1

#Fri Jun 12 18:02:45 JST 2020 TP0=2200 N:50-100:10 ns=20 ==>(hV,hg)=(166,371) 166
h(yi,yg)@L0c0 with n119 min46.0 max371.0 mean179.4 median166.0 std53.0 best-iNshh(14,80,12,371*,181) can2m1
h(yi,yg)@L2c0 with n112 min89.0 max371.0 mean184.7 median166.0 std49.9 best-iNshh(14,80,12,371*,186) can2m1
h(yi,yg)@L2c1 with n6 min97.0 max105.0 mean103.2 median104.5 std2.9 best-iNshh(110,60,14,105*,192)(112,60,12,105*,197)(113,70,10,105*,137) can2m1
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(118,90,2,46*,-1) can2m1
hi-LOOCV@L0c0 with n119 min46.0 max185.4 mean163.1 median173.2 std24.3 best-iNshh(1,50,4,166,185*) can2m1
hi-LOOCV@L2c0 with n112 min87.3 max191.1 mean171.8 median179.1 std18.8 best-iNshh(1,50,4,166,191*) can2m1
hi-LOOCV@L2c1 with n6 min97.4 max196.6 mean155.9 median158.5 std36.2 best-iNshh(112,60,12,105,197*) can2m1
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(118,90,2,46,-1*) can2m1


#Fri Jun 12 17:54:41 JST 2020 TP0=2100 N:50-100:10 ns=20 ==>(hV,hg)=(191,414) 194
h(yi,yg)@L0c0 with n116 min20.0 max414.0 mean175.5 median186.0 std62.4 best-iNshh(54,80,10,414*,169) can2m2
h(yi,yg)@L2c0 with n8 min21.0 max129.0 mean60.8 median30.0 std42.9 best-iNshh(102,80,16,129*,116) can2m2
h(yi,yg)@L2c1 with n33 min71.0 max355.0 mean172.5 median157.0 std56.1 best-iNshh(76,140,11,355*,168) can2m2
h(yi,yg)@L2c2 with n20 min20.0 max197.0 mean172.1 median194.0 std51.6 best-iNshh(48,200,5,197*,204)(49,140,17,197*,209) can2m2
h(yi,yg)@L2c3 with n55 min97.0 max414.0 mean195.3 median190.0 std52.5 best-iNshh(54,80,10,414*,185) can2m2
hi-LOOCV@L0c0 with n116 min20.0 max187.4 mean154.4 median170.1 std38.3 best-iNshh(5,140,2,194,187*) can2m2
hi-LOOCV@L2c0 with n8 min78.4 max132.7 mean117.0 median120.4 std15.3 best-iNshh(112,50,19,30,133*) can2m2
hi-LOOCV@L2c1 with n33 min72.5 max176.5 mean150.6 median157.7 std24.4 best-iNshh(53,110,9,219,177*) can2m2
hi-LOOCV@L2c2 with n20 min17.8 max222.1 mean184.4 median205.6 std58.7 best-iNshh(58,170,17,196,222*) can2m2
hi-LOOCV@L2c3 with n55 min97.1 max214.6 mean189.4 median198.4 std24.3 best-iNshh(15,140,0,191,215*) can2m2
Fri Jun 12 17:54:41 JST 2020

#Fri Jun 12 17:46:49 JST 2020 TP0=2900 N:50-100:5 ns=10 ==>(hV,hg)=(211,492) 213
h(yi,yg)@L0c0 with n107 min72.0 max492.0 mean180.5 median192.0 std76.2 best-iNshh(36,90,8,492*,177) can2m
h(yi,yg)@L2c0 with n35 min78.0 max314.0 mean201.6 median214.0 std46.1 best-iNshh(69,90,4,314*,212) can2m
h(yi,yg)@L2c1 with n51 min76.0 max492.0 mean209.7 median201.0 std70.0 best-iNshh(36,90,8,492*,202) can2m
h(yi,yg)@L2c2 with n17 min72.0 max76.0 mean73.6 median73.0 std1.2 best-iNshh(104,65,7,76*,105)(106,60,2,76*,87) can2m
h(yi,yg)@L2c3 with n4 min77.0 max77.0 mean77.0 median77.0 std0.0 best-iNshh(93,75,7,77*,259)(99,100,2,77*,262)(100,85,9,77*,267)(102,55,3,77*,274) can2m
hi-LOOCV@L0c0 with n107 min81.9 max192.0 mean147.5 median157.5 std36.6 best-iNshh(0,55,6,213,192*) can2m
hi-LOOCV@L2c0 with n35 min113.1 max256.7 mean220.1 median236.1 std37.1 best-iNshh(47,70,1,215,257*) can2m
hi-LOOCV@L2c1 with n51 min78.9 max206.0 mean181.6 median193.0 std30.8 best-iNshh(40,70,0,211,206*) can2m
hi-LOOCV@L2c2 with n17 min86.6 max245.5 mean192.1 median196.5 std41.4 best-iNshh(83,65,0,75,246*) can2m
hi-LOOCV@L2c3 with n4 min259.3 max273.7 mean265.5 median264.5 std5.4 best-iNshh(102,55,3,77,274*) can2m

#Fri Jun 12 17:46:02 JST 2020 TP0=2000 N:50-100:10 ns=20 ==>(hV,hg)=(169,414) 169
h(yi,yg)@L0c0 with n114 min20.0 max414.0 mean158.9 median157.0 std61.4 best-iNshh(68,80,10,414*,153) can2m1
h(yi,yg)@L2c0 with n89 min98.0 max414.0 mean175.0 median157.0 std48.3 best-iNshh(68,80,10,414*,168) can2m1
h(yi,yg)@L2c1 with n9 min20.0 max196.0 mean154.1 median180.0 std55.1 best-iNshh(105,70,1,196*,162) can2m1
h(yi,yg)@L2c2 with n6 min30.0 max101.0 mean42.0 median30.0 std26.4 best-iNshh(101,80,4,101*,136) can2m1
h(yi,yg)@L2c3 with n10 min29.0 max158.0 mean89.2 median79.5 std60.5 best-iNshh(75,60,4,158*,190) can2m1
hi-LOOCV@L0c0 with n114 min21.1 max166.9 mean141.3 median155.9 std30.7 best-iNshh(10,100,13,172,167*) can2m1
hi-LOOCV@L2c0 with n89 min101.7 max180.5 mean167.0 median173.4 std16.7 best-iNshh(17,100,9,169,181*) can2m1
hi-LOOCV@L2c1 with n9 min16.0 max180.1 mean142.3 median168.0 std52.4 best-iNshh(100,80,2,180,180*) can2m1
hi-LOOCV@L2c2 with n6 min124.6 max160.0 mean139.8 median140.0 std12.2 best-iNshh(109,50,19,30,160*) can2m1
hi-LOOCV@L2c3 with n10 min144.9 max195.2 mean180.1 median189.5 std18.5 best-iNshh(96,60,11,30,195*) can2m1

#Fri Jun 12 17:39:29 JST 2020 TP0=2800 N:50-100:5 ns=10 ==>(hV,hg)=(259,446) 259
h(yi,yg)@L0c0 with n109 min55.0 max446.0 mean167.9 median166.0 std69.3 best-iNshh(12,55,8,446*,160) can2m
h(yi,yg)@L2c0 with n67 min136.0 max446.0 mean198.4 median173.0 std65.2 best-iNshh(12,55,8,446*,180) can2m
h(yi,yg)@L2c1 with n22 min55.0 max136.0 mean109.4 median107.0 std21.0 best-iNshh(72,65,2,136*,131)(77,100,3,136*,142)(78,55,4,136*,143)(79,95,3,136*,126) can2m
h(yi,yg)@L2c2 with n12 min63.0 max231.0 mean165.8 median167.0 std35.5 best-iNshh(3,50,8,231*,169) can2m
h(yi,yg)@L2c3 with n8 min63.0 max169.0 mean77.2 median64.0 std34.7 best-iNshh(83,75,9,169*,245) can2m
hi-LOOCV@L0c0 with n109 min55.0 max166.7 mean136.6 median149.6 std25.7 best-iNshh(0,75,8,259,167*) can2m
hi-LOOCV@L2c0 with n67 min146.3 max195.7 mean173.8 median175.7 std13.4 best-iNshh(0,75,8,259,196*) can2m
hi-LOOCV@L2c1 with n22 min57.4 max149.2 mean130.1 median138.6 std24.4 best-iNshh(85,80,3,108,149*) can2m
hi-LOOCV@L2c2 with n12 min169.1 max243.3 mean219.4 median224.7 std20.3 best-iNshh(29,70,9,175,243*) can2m
hi-LOOCV@L2c3 with n8 min223.1 max254.7 mean244.2 median245.9 std8.5 best-iNshh(102,85,6,64,255*) can2m

#Fri Jun 12 17:32:14 JST 2020 TP0=2700 N:50-100:5 ns=10 ==>(hV,hg)=(270,416) 270
h(yi,yg)@L0c0 with n106 min83.0 max416.0 mean171.1 median150.0 std59.6 best-iNshh(10,55,9,416*,164) can2m
h(yi,yg)@L2c0 with n7 min115.0 max118.0 mean116.6 median117.0 std0.9 best-iNshh(88,80,4,118*,246) can2m
h(yi,yg)@L2c1 with n89 min89.0 max416.0 mean184.8 median155.0 std54.8 best-iNshh(10,55,9,416*,177) can2m
h(yi,yg)@L2c2 with n9 min86.0 max88.0 mean87.1 median87.0 std0.7 best-iNshh(96,85,6,88*,237)(98,80,6,88*,221)(100,65,9,88*,200) can2m
h(yi,yg)@L2c3 with n1 min83.0 max83.0 mean83.0 median83.0 std0.0 best-iNshh(105,55,5,83*,-1) can2m
hi-LOOCV@L0c0 with n106 min86.2 max172.4 mean149.6 median157.6 std21.4 best-iNshh(2,80,8,270,172*) can2m
hi-LOOCV@L2c0 with n7 min191.2 max258.2 mean239.9 median250.0 std21.7 best-iNshh(93,70,1,116,258*) can2m
hi-LOOCV@L2c1 with n89 min89.9 max186.5 mean169.2 median169.6 std11.1 best-iNshh(2,80,8,270,187*) can2m
hi-LOOCV@L2c2 with n9 min167.2 max253.2 mean211.5 median212.6 std27.6 best-iNshh(95,100,4,87,253*) can2m
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(105,55,5,83,-1*) can2m

#Fri Jun 12 17:30:21 JST 2020 TP0=2900 N:50-80:10 ns=17 ==>(hV,hg)=(188,310) 209
h(yi,yg)@L0c0 with n65 min72.0 max310.0 mean161.2 median188.0 std64.4 best-iNshh(10,70,6,310*,159) can2m2
h(yi,yg)@L2c0 with n11 min72.0 max74.0 mean73.5 median74.0 std0.7 best-iNshh(47,60,14,74*,216)(48,60,13,74*,219)(49,80,3,74*,218)(51,70,13,74*,218)(52,70,2,74*,221)(54,70,10,74*,202)(55,50,3,74*,192) can2m2
h(yi,yg)@L2c1 with n5 min76.0 max76.0 mean76.0 median76.0 std0.0 best-iNshh(56,80,10,76*,150)(58,60,2,76*,259)(62,70,14,76*,219)(63,50,0,76*,221)(64,80,2,76*,180) can2m2
h(yi,yg)@L2c2 with n11 min78.0 max216.0 mean160.9 median211.0 std61.5 best-iNshh(23,60,1,216*,229)(35,80,1,216*,226) can2m2
h(yi,yg)@L2c3 with n38 min126.0 max310.0 mean197.9 median189.5 std38.4 best-iNshh(10,70,6,310*,195) can2m2
hi-LOOCV@L0c0 with n65 min83.7 max170.7 mean134.0 median147.8 std29.4 best-iNshh(1,80,0,209,171*) can2m2
hi-LOOCV@L2c0 with n11 min185.2 max223.5 mean210.0 median216.5 std12.0 best-iNshh(50,50,7,73,224*) can2m2
hi-LOOCV@L2c1 with n5 min150.0 max259.0 mean205.7 median218.8 std37.5 best-iNshh(58,60,2,76,259*) can2m2
hi-LOOCV@L2c2 with n11 min142.3 max277.7 mean212.7 median220.0 std38.6 best-iNshh(42,80,15,86,278*) can2m2
hi-LOOCV@L2c3 with n38 min127.7 max205.2 mean189.0 median198.0 std22.0 best-iNshh(22,50,12,188,205*) can2m2

#Fri Jun 12 17:26:18 JST 2020 TP0=2800 N:50-80:10 ns=17 ==>(hV,hg)=(257,374) 231
h(yi,yg)@L0c0 with n68 min52.0 max374.0 mean159.2 median166.5 std67.2 best-iNshh(23,60,1,374*,147) can2m2
h(yi,yg)@L2c0 with n47 min55.0 max374.0 mean176.5 median168.0 std62.6 best-iNshh(23,60,1,374*,166) can2m2
h(yi,yg)@L2c1 with n15 min65.0 max231.0 mean147.1 median169.0 std51.7 best-iNshh(0,50,8,231*,141) can2m2
h(yi,yg)@L2c2 with n1 min55.0 max55.0 mean55.0 median55.0 std0.0 best-iNshh(65,50,7,55*,-1) can2m2
h(yi,yg)@L2c3 with n1 min53.0 max53.0 mean53.0 median53.0 std0.0 best-iNshh(67,50,11,53*,-1) can2m2
hi-LOOCV@L0c0 with n68 min55.7 max158.3 mean126.0 median143.9 std32.3 best-iNshh(0,50,8,231,158*) can2m2
hi-LOOCV@L2c0 with n47 min74.7 max173.7 mean150.0 median158.5 std21.8 best-iNshh(5,80,7,257,174*) can2m2
hi-LOOCV@L2c1 with n15 min106.2 max214.6 mean156.3 median159.8 std29.6 best-iNshh(48,60,14,174,215*) can2m2
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(65,50,7,55,-1*) can2m2
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(67,50,11,53,-1*) can2m2

#Fri Jun 12 17:24:42 JST 2020 TP0=2600 N:50-100:5 ns=10 ==>(hV,hg)=(153,308) 153
h(yi,yg)@L0c0 with n110 min39.0 max308.0 mean165.5 median151.0 std38.6 best-iNshh(73,100,5,308*,164) can2m
h(yi,yg)@L2c0 with n16 min116.0 max128.0 mean125.3 median125.5 std2.8 best-iNshh(93,75,5,128*,208)(94,90,4,128*,159)(95,70,5,128*,161) can2m
h(yi,yg)@L2c1 with n93 min129.0 max308.0 mean173.8 median153.0 std35.2 best-iNshh(73,100,5,308*,172) can2m
h(yi,yg)@L2c2 with n1 min39.0 max39.0 mean39.0 median39.0 std0.0 best-iNshh(109,65,7,39*,-1) can2m
hi-LOOCV@L0c0 with n110 min39.5 max179.9 mean162.0 median167.1 std18.2 best-iNshh(0,75,7,153,180*) can2m
hi-LOOCV@L2c0 with n16 min111.4 max208.3 mean183.1 median191.1 std23.0 best-iNshh(93,75,5,128,208*) can2m
hi-LOOCV@L2c1 with n93 min149.2 max190.8 mean177.0 median176.7 std8.1 best-iNshh(0,75,7,153,191*) can2m
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(109,65,7,39,-1*) can2m

#Fri Jun 12 17:22:18 JST 2020 TP0=2700 N:50-80:10 ns=17 ==>(hV,hg)=(175,273) 175
h(yi,yg)@L0c0 with n66 min86.0 max273.0 mean166.7 median159.5 std46.1 best-iNshh(29,80,3,273*,164) can2m2
h(yi,yg)@L2c0 with n56 min98.0 max273.0 mean177.2 median174.0 std41.8 best-iNshh(29,80,3,273*,174) can2m2
h(yi,yg)@L2c1 with n7 min112.0 max119.0 mean116.7 median117.0 std2.1 best-iNshh(56,80,14,119*,126) can2m2
h(yi,yg)@L2c2 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(65,50,5,86*,-1) can2m2
hi-LOOCV@L0c0 with n66 min89.1 max179.7 mean152.6 median158.3 std20.4 best-iNshh(8,50,0,175,180*) can2m2
hi-LOOCV@L2c0 with n56 min117.7 max192.3 mean168.9 median170.3 std12.9 best-iNshh(8,50,0,175,192*) can2m2
hi-LOOCV@L2c1 with n7 min123.8 max230.5 mean196.9 median221.2 std45.6 best-iNshh(54,80,4,118,230*) can2m2
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(65,50,5,86,-1*) can2m2

#Fri Jun 12 17:18:14 JST 2020 TP0=2600 N:50-80:10 ns=17 ==>(hV,hg)=(154,277) 154
h(yi,yg)@L0c0 with n68 min116.0 max277.0 mean161.9 median151.0 std37.3 best-iNshh(5,50,10,277*,162) can2m2
h(yi,yg)@L2c0 with n23 min147.0 max157.0 mean151.3 median151.0 std2.8 best-iNshh(20,50,14,157*,189) can2m2
h(yi,yg)@L2c1 with n25 min129.0 max277.0 mean200.8 median186.0 std33.1 best-iNshh(5,50,10,277*,201) can2m2
h(yi,yg)@L2c2 with n18 min124.0 max128.0 mean125.9 median126.0 std1.4 best-iNshh(51,60,10,128*,170)(57,70,5,128*,169)(63,50,15,128*,145) can2m2
h(yi,yg)@L2c3 with n1 min116.0 max116.0 mean116.0 median116.0 std0.0 best-iNshh(67,50,5,116*,-1) can2m2
hi-LOOCV@L0c0 with n68 min120.6 max169.6 mean154.8 median157.9 std10.7 best-iNshh(6,60,11,154,170*) can2m2
hi-LOOCV@L2c0 with n23 min180.4 max233.4 mean207.5 median211.7 std13.3 best-iNshh(6,60,11,154,233*) can2m2
hi-LOOCV@L2c1 with n25 min144.0 max212.6 mean195.8 median200.4 std16.9 best-iNshh(10,80,3,185,213*) can2m2
hi-LOOCV@L2c2 with n18 min145.3 max219.2 mean192.9 median197.5 std16.5 best-iNshh(37,70,15,127,219*) can2m2
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(67,50,5,116,-1*) can2m2

#Fri Jun 12 17:17:23 JST 2020 TP0=2500 N:50-100:5 ns=10 ==>(hV,hg)=(284,348) 284
h(yi,yg)@L0c0 with n108 min114.0 max346.0 mean203.4 median223.5 std60.8 best-iNshh(23,70,2,346*,203) can2m
h(yi,yg)@L2c0 with n67 min148.0 max346.0 mean242.4 median247.0 std43.1 best-iNshh(23,70,2,346*,241) can2m
h(yi,yg)@L2c1 with n12 min114.0 max162.0 mean150.7 median159.0 std17.2 best-iNshh(76,90,9,162*,229)(94,65,9,162*,189) can2m
h(yi,yg)@L2c2 with n21 min132.0 max136.0 mean134.0 median134.0 std1.3 best-iNshh(78,80,1,136*,246)(79,80,5,136*,245) can2m
h(yi,yg)@L2c3 with n8 min136.0 max139.0 mean137.2 median137.0 std1.0 best-iNshh(106,95,3,139*,146) can2m
hi-LOOCV@L0c0 with n108 min125.1 max213.7 mean181.4 median189.8 std23.3 best-iNshh(0,80,8,286,214*) can2m
hi-LOOCV@L2c0 with n67 min175.9 max259.1 mean232.3 median239.0 std21.5 best-iNshh(5,90,6,284,259*) can2m
hi-LOOCV@L2c1 with n12 min176.0 max249.3 mean219.2 median222.6 std21.0 best-iNshh(75,65,4,158,249*) can2m
hi-LOOCV@L2c2 with n21 min200.8 max247.9 mean227.3 median234.8 std16.8 best-iNshh(74,75,7,135,248*) can2m
hi-LOOCV@L2c3 with n8 min146.3 max292.3 mean243.4 median268.2 std47.0 best-iNshh(66,100,3,137,292*) can2m

#Fri Jun 12 17:14:13 JST 2020 TP0=2500 N:50-80:10 ns=17 ==>(hV,hg)=(252,346) 252
h(yi,yg)@L0c0 with n67 min114.0 max346.0 mean193.3 median193.0 std56.9 best-iNshh(19,70,2,346*,192) can2m2
h(yi,yg)@L2c0 with n39 min140.0 max346.0 mean232.9 median225.0 std41.5 best-iNshh(19,70,2,346*,230) can2m2
h(yi,yg)@L2c1 with n7 min114.0 max164.0 mean147.7 median159.0 std21.1 best-iNshh(50,50,10,164*,222)(52,70,16,164*,221) can2m2
h(yi,yg)@L2c2 with n6 min137.0 max138.0 mean137.5 median137.5 std0.5 best-iNshh(56,50,14,138*,308)(58,60,13,138*,251)(60,80,14,138*,255) can2m2
h(yi,yg)@L2c3 with n15 min131.0 max136.0 mean134.2 median135.0 std1.7 best-iNshh(40,60,12,136*,235)(44,80,5,136*,241)(45,80,1,136*,241)(49,70,7,136*,224) can2m2
hi-LOOCV@L0c0 with n67 min125.4 max197.7 mean173.5 median171.7 std18.3 best-iNshh(8,70,13,252,198*) can2m2
hi-LOOCV@L2c0 with n39 min153.7 max240.6 mean220.5 median229.5 std19.4 best-iNshh(8,70,13,252,241*) can2m2
hi-LOOCV@L2c1 with n7 min200.3 max229.2 mean216.7 median220.8 std10.3 best-iNshh(48,70,4,159,229*) can2m2
hi-LOOCV@L2c2 with n6 min251.0 max321.4 mean287.5 median295.2 std26.1 best-iNshh(32,60,3,137,321*) can2m2
hi-LOOCV@L2c3 with n15 min197.4 max241.0 mean223.8 median229.4 std15.1 best-iNshh(38,70,14,135,241*) can2m2

#Fri Jun 12 17:10:09 JST 2020 TP0=2400 N:50-80:10 ns=17 ==>(hV,hg)=(61,351) 230
h(yi,yg)@L0c0 with n64 min56.0 max351.0 mean147.0 median172.5 std80.6 best-iNshh(20,80,10,351*,142) can2m2
h(yi,yg)@L2c0 with n24 min57.0 max64.0 mean60.8 median61.0 std2.1 best-iNshh(54,80,7,64*,143) can2m2
h(yi,yg)@L2c1 with n1 min56.0 max56.0 mean56.0 median56.0 std0.0 best-iNshh(63,50,5,56*,-1) can2m2
h(yi,yg)@L2c2 with n17 min173.0 max351.0 mean233.2 median230.0 std38.6 best-iNshh(20,80,10,351*,227) can2m2
h(yi,yg)@L2c3 with n20 min68.0 max259.0 mean189.3 median200.0 std38.8 best-iNshh(26,80,11,259*,189) can2m2
hi-LOOCV@L0c0 with n64 min70.1 max146.2 mean115.9 median119.0 std22.6 best-iNshh(1,60,13,230,146*) can2m2
hi-LOOCV@L2c0 with n24 min100.2 max186.9 mean160.1 median164.8 std21.7 best-iNshh(40,50,16,61,187*) can2m2
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(63,50,5,56,-1*) can2m2
hi-LOOCV@L2c2 with n17 min173.4 max239.8 mean218.3 median224.6 std19.2 best-iNshh(22,70,14,264,240*) can2m2
hi-LOOCV@L2c3 with n20 min125.2 max203.5 mean181.3 median189.6 std20.7 best-iNshh(11,70,3,202,204*) can2m2

#Fri Jun 12 17:09:12 JST 2020 TP0=2900 N:5-300:5 ns=1 ==>(hV,hg)=(212,331) 214
h(yi,yg)@L0c0 with n57 min73.0 max331.0 mean151.5 median188.0 std68.1 best-iNshh(42,75,0,331*,119) can2m1
h(yi,yg)@L2c0 with n23 min188.0 max221.0 mean211.6 median212.0 std6.0 best-iNshh(17,135,0,221*,264) can2m1
h(yi,yg)@L2c1 with n14 min76.0 max331.0 mean150.9 median135.0 std78.1 best-iNshh(42,75,0,331*,147) can2m1
h(yi,yg)@L2c2 with n16 min77.0 max87.0 mean85.0 median86.0 std3.1 best-iNshh(30,240,0,87*,307)(31,235,0,87*,308)(32,270,0,87*,302)(33,255,0,87*,303)(34,250,0,87*,303)(35,245,0,87*,308) can2m1
h(yi,yg)@L2c3 with n4 min73.0 max75.0 mean73.5 median73.0 std0.9 best-iNshh(52,65,0,75*,218) can2m1
hi-LOOCV@L0c0 with n57 min79.8 max215.3 mean155.5 median174.4 std42.1 best-iNshh(0,170,0,214,215*) can2m1
hi-LOOCV@L2c0 with n23 min187.0 max294.5 mean277.8 median284.5 std22.1 best-iNshh(9,140,0,212,295*) can2m1
hi-LOOCV@L2c1 with n14 min95.5 max152.5 mean133.4 median139.1 std16.4 best-iNshh(39,100,0,213,152*) can2m1
hi-LOOCV@L2c2 with n16 min286.7 max330.3 mean305.5 median305.1 std11.4 best-iNshh(28,215,0,86,330*) can2m1
hi-LOOCV@L2c3 with n4 min188.0 max218.3 mean205.0 median206.8 std11.6 best-iNshh(52,65,0,75,218*) can2m1

#Fri Jun 12 17:05:45 JST 2020 TP0=2300 N:50-80:10 ns=17 ==>(hV,hg)=(191,361) 190
h(yi,yg)@L0c0 with n67 min65.0 max361.0 mean143.3 median148.0 std58.5 best-iNshh(11,60,14,361*,140) can2m2
h(yi,yg)@L2c0 with n39 min70.0 max361.0 mean160.9 median158.0 std54.2 best-iNshh(11,60,14,361*,153) can2m2
h(yi,yg)@L2c1 with n18 min79.0 max245.0 mean147.6 median161.5 std49.5 best-iNshh(1,50,12,245*,162) can2m2
h(yi,yg)@L2c2 with n5 min68.0 max69.0 mean68.2 median68.0 std0.4 best-iNshh(60,80,4,69*,257) can2m2
h(yi,yg)@L2c3 with n5 min65.0 max68.0 mean66.2 median66.0 std1.0 best-iNshh(64,50,9,68*,109) can2m2
hi-LOOCV@L0c0 with n67 min72.9 max152.0 mean119.7 median126.1 std22.0 best-iNshh(0,70,10,190,152*) can2m2
hi-LOOCV@L2c0 with n39 min70.1 max161.1 mean146.3 median151.0 std15.1 best-iNshh(8,60,1,191,161*) can2m2
hi-LOOCV@L2c1 with n18 min83.1 max201.9 mean161.9 median162.1 std30.2 best-iNshh(51,60,11,79,202*) can2m2
hi-LOOCV@L2c2 with n5 min126.8 max280.8 mean243.5 median272.5 std59.0 best-iNshh(54,70,4,68,281*) can2m2
hi-LOOCV@L2c3 with n5 min109.0 max158.0 mean146.5 median154.8 std18.8 best-iNshh(66,80,13,66,158*) can2m2

#Fri Jun 12 17:02:12 JST 2020 TP0=2300 N:50-100:5 ns=10 ==>(hV,hg)=(188,395) 168
h(yi,yg)@L0c0 with n108 min65.0 max395.0 mean133.5 median126.5 std55.7 best-iNshh(26,85,9,395*,134) can2m
h(yi,yg)@L2c0 with n66 min70.0 max395.0 mean161.8 median166.0 std45.8 best-iNshh(26,85,9,395*,155) can2m
h(yi,yg)@L2c1 with n18 min78.0 max190.0 mean118.2 median86.5 std43.6 best-iNshh(59,50,4,190*,196) can2m
h(yi,yg)@L2c2 with n14 min65.0 max68.0 mean66.4 median66.0 std0.9 best-iNshh(76,80,6,68*,214)(105,50,9,68*,108) can2m
h(yi,yg)@L2c3 with n10 min68.0 max69.0 mean68.6 median69.0 std0.5 best-iNshh(82,80,4,69*,261)(87,85,4,69*,239)(90,90,4,69*,250)(96,65,4,69*,231)(99,100,9,69*,200)(104,55,7,69*,147) can2m
hi-LOOCV@L0c0 with n108 min71.8 max148.5 mean114.8 median115.2 std21.2 best-iNshh(0,90,6,168,148*) can2m
hi-LOOCV@L2c0 with n66 min68.8 max178.0 mean154.4 median165.3 std22.4 best-iNshh(4,65,1,188,178*) can2m
hi-LOOCV@L2c1 with n18 min84.0 max200.1 mean168.5 median170.4 std30.2 best-iNshh(81,70,6,79,200*) can2m
hi-LOOCV@L2c2 with n14 min108.3 max213.7 mean189.5 median196.9 std27.2 best-iNshh(76,80,6,68,214*) can2m
hi-LOOCV@L2c3 with n10 min135.4 max261.9 mean219.6 median234.8 std42.7 best-iNshh(72,75,4,68,262*) can2m

#Fri Jun 12 17:01:47 JST 2020 TP0=2800 N:5-300:5 ns=1 ==>(hV,hg)=(256,256) 175
h(yi,yg)@L0c0 with n56 min49.0 max256.0 mean114.3 median91.5 std56.2 best-iNshh(12,85,0,256*,108)(14,90,0,256*,108) can2m1
h(yi,yg)@L2c0 with n22 min54.0 max256.0 mean165.9 median174.0 std50.9 best-iNshh(12,85,0,256*,164)(14,90,0,256*,163) can2m1
h(yi,yg)@L2c1 with n12 min49.0 max167.0 mean79.3 median63.0 std39.4 best-iNshh(7,55,0,167*,227)(8,220,0,167*,226) can2m1
h(yi,yg)@L2c2 with n16 min71.0 max79.0 mean72.9 median72.0 std2.3 best-iNshh(52,265,0,79*,97) can2m1
h(yi,yg)@L2c3 with n6 min104.0 max107.0 mean105.2 median105.0 std1.1 best-iNshh(48,185,0,107*,180) can2m1
hi-LOOCV@L0c0 with n56 min47.8 max137.8 mean101.1 median101.7 std15.9 best-iNshh(0,260,0,175,138*) can2m1
hi-LOOCV@L2c0 with n22 min61.3 max164.1 mean144.4 median154.9 std28.4 best-iNshh(12,85,0,256,164*) can2m1
hi-LOOCV@L2c1 with n12 min54.5 max243.6 mean216.6 median227.1 std49.5 best-iNshh(5,290,0,63,244*) can2m1
hi-LOOCV@L2c2 with n16 min97.5 max198.9 mean170.9 median186.4 std33.0 best-iNshh(25,150,0,72,199*) can2m1
hi-LOOCV@L2c3 with n6 min180.2 max273.0 mean226.7 median223.1 std34.0 best-iNshh(42,190,0,106,273*) can2m1

#Fri Jun 12 17:01:38 JST 2020 TP0=2200 N:50-80:10 ns=17 ==>(hV,hg)=(166,371) 166
h(yi,yg)@L0c0 with n67 min89.0 max371.0 mean175.4 median166.0 std53.9 best-iNshh(23,80,12,371*,175) can2m2
h(yi,yg)@L2c0 with n61 min99.0 max371.0 mean182.7 median166.0 std50.8 best-iNshh(23,80,12,371*,182) can2m2
h(yi,yg)@L2c1 with n1 min89.0 max89.0 mean89.0 median89.0 std0.0 best-iNshh(66,50,12,89*,-1) can2m2
h(yi,yg)@L2c2 with n4 min103.0 max105.0 mean104.5 median105.0 std0.9 best-iNshh(60,60,12,105*,226)(61,70,10,105*,134)(62,60,14,105*,200) can2m2
h(yi,yg)@L2c3 with n1 min97.0 max97.0 mean97.0 median97.0 std0.0 best-iNshh(64,60,10,97*,-1) can2m2
hi-LOOCV@L0c0 with n67 min86.7 max179.7 mean157.2 median169.2 std23.1 best-iNshh(0,50,4,166,180*) can2m2
hi-LOOCV@L2c0 with n61 min97.6 max187.6 mean168.7 median176.1 std17.7 best-iNshh(0,50,4,166,188*) can2m2
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(66,50,12,89,-1*) can2m2
hi-LOOCV@L2c2 with n4 min134.0 max226.3 mean175.3 median170.5 std39.0 best-iNshh(60,60,12,105,226*) can2m2
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(64,60,10,97,-1*) can2m2
Fri Jun 12 17:01:38 JST 2020

#Fri Jun 12 16:57:33 JST 2020 TP0=2100 N:50-80:10 ns=17 ==>(hV,hg)=(176,291) 258
h(yi,yg)@L0c0 with n65 min90.0 max291.0 mean145.7 median106.0 std58.1 best-iNshh(6,80,12,291*,158) can2m2
h(yi,yg)@L2c0 with n13 min106.0 max270.0 mean194.9 median205.0 std51.9 best-iNshh(33,60,8,270*,188) can2m2
h(yi,yg)@L2c1 with n36 min96.0 max291.0 mean151.9 median147.0 std54.0 best-iNshh(6,80,12,291*,183) can2m2
h(yi,yg)@L2c2 with n15 min90.0 max94.0 mean91.7 median92.0 std0.9 best-iNshh(53,60,16,94*,216) can2m2
h(yi,yg)@L2c3 with n1 min96.0 max96.0 mean96.0 median96.0 std0.0 best-iNshh(63,70,11,96*,-1) can2m2
hi-LOOCV@L0c0 with n65 min96.3 max162.2 mean136.8 median139.4 std19.4 best-iNshh(0,60,12,258,162*) can2m2
hi-LOOCV@L2c0 with n13 min147.2 max242.8 mean188.8 median188.2 std25.5 best-iNshh(34,60,15,234,243*) can2m2
hi-LOOCV@L2c1 with n36 min90.9 max193.4 mean173.9 median182.7 std21.6 best-iNshh(3,80,7,176,193*) can2m2
hi-LOOCV@L2c2 with n15 min146.9 max240.6 mean212.7 median223.4 std27.7 best-iNshh(46,80,4,92,241*) can2m2
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(63,70,11,96,-1*) can2m2

#Fri Jun 12 16:54:50 JST 2020 TP0=2200 N:50-100:5 ns=10 ==>(hV,hg)=(166,289) 166
h(yi,yg)@L0c0 with n107 min46.0 max289.0 mean171.5 median165.0 std38.1 best-iNshh(66,90,5,289*,169) can2m
h(yi,yg)@L2c0 with n56 min158.0 max289.0 mean179.3 median166.0 std32.0 best-iNshh(66,90,5,289*,177) can2m
h(yi,yg)@L2c1 with n50 min103.0 max260.0 mean165.2 median145.5 std39.1 best-iNshh(51,95,7,260*,167) can2m
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(106,90,2,46*,-1) can2m
hi-LOOCV@L0c0 with n107 min46.0 max184.9 mean165.7 median172.6 std20.2 best-iNshh(0,90,4,166,185*) can2m
hi-LOOCV@L2c0 with n56 min173.5 max221.2 mean198.0 median198.6 std16.0 best-iNshh(0,90,4,166,221*) can2m
hi-LOOCV@L2c1 with n50 min106.0 max187.9 mean166.2 median168.2 std19.4 best-iNshh(45,60,2,193,188*) can2m
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(106,90,2,46,-1*) can2m

#Fri Jun 12 16:54:25 JST 2020 TP0=2700 N:5-300:5 ns=1 ==>(hV,hg)=(147,275) 147
h(yi,yg)@L0c0 with n58 min51.0 max275.0 mean150.1 median147.0 std40.0 best-iNshh(42,285,0,275*,147) can2m1
h(yi,yg)@L2c0 with n55 min89.0 max275.0 mean154.2 median147.0 std36.6 best-iNshh(42,285,0,275*,151) can2m1
h(yi,yg)@L2c1 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(56,25,0,86*,-1) can2m1
h(yi,yg)@L2c2 with n1 min51.0 max51.0 mean51.0 median51.0 std0.0 best-iNshh(57,5,0,51*,-1) can2m1
hi-LOOCV@L0c0 with n58 min51.2 max179.6 mean150.9 median158.8 std25.1 best-iNshh(0,65,0,147,180*) can2m1
hi-LOOCV@L2c0 with n55 min92.7 max185.3 mean159.4 median164.7 std19.2 best-iNshh(0,65,0,147,185*) can2m1
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,25,0,86,-1*) can2m1
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(57,5,0,51,-1*) can2m1

#Fri Jun 12 16:53:23 JST 2020 TP0=2000 N:50-80:10 ns=17 ==>(hV,hg)=(157,414) 157
h(yi,yg)@L0c0 with n64 min20.0 max414.0 mean160.6 median157.0 std64.6 best-iNshh(36,80,10,414*,150) can2m2
h(yi,yg)@L2c0 with n48 min98.0 max414.0 mean174.8 median157.0 std58.0 best-iNshh(36,80,10,414*,160) can2m2
h(yi,yg)@L2c1 with n10 min29.0 max158.0 mean97.7 median115.0 std58.1 best-iNshh(39,60,4,158*,178) can2m2
h(yi,yg)@L2c2 with n5 min152.0 max196.0 mean178.2 median180.0 std14.4 best-iNshh(59,70,1,196*,189) can2m2
h(yi,yg)@L2c3 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(63,50,15,20*,-1) can2m2
hi-LOOCV@L0c0 with n64 min21.0 max165.0 mean138.3 median153.7 std30.8 best-iNshh(1,80,6,157,165*) can2m2
hi-LOOCV@L2c0 with n48 min103.4 max183.2 mean162.2 median168.6 std19.0 best-iNshh(1,80,6,157,183*) can2m2
hi-LOOCV@L2c1 with n10 min114.1 max184.9 mean158.5 median167.8 std26.2 best-iNshh(51,60,11,30,185*) can2m2
hi-LOOCV@L2c2 with n5 min147.0 max217.2 mean196.1 median211.5 std26.5 best-iNshh(58,80,2,180,217*) can2m2
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(63,50,15,20,-1*) can2m2

#Fri Jun 12 16:47:22 JST 2020 TP0=2100 N:50-100:5 ns=10 ==>(hV,hg)=(99,353) 205
h(yi,yg)@L0c0 with n105 min90.0 max353.0 mean127.0 median99.0 std56.7 best-iNshh(1,95,5,353*,148) can2m
h(yi,yg)@L2c0 with n21 min98.0 max353.0 mean190.5 median177.0 std61.2 best-iNshh(1,95,5,353*,173) can2m
h(yi,yg)@L2c1 with n44 min98.0 max321.0 mean128.7 median99.0 std53.1 best-iNshh(6,55,0,321*,187) can2m
h(yi,yg)@L2c2 with n39 min90.0 max95.0 mean91.6 median92.0 std1.0 best-iNshh(100,55,4,95*,123) can2m
h(yi,yg)@L2c3 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(104,100,9,98*,-1) can2m
hi-LOOCV@L0c0 with n105 min97.7 max150.2 mean134.0 median137.1 std11.8 best-iNshh(3,70,3,205,150*) can2m
hi-LOOCV@L2c0 with n21 min111.2 max202.4 mean167.4 median174.6 std26.3 best-iNshh(9,50,7,205,202*) can2m
hi-LOOCV@L2c1 with n44 min121.5 max192.7 mean173.1 median174.7 std16.2 best-iNshh(7,95,1,99,193*) can2m
hi-LOOCV@L2c2 with n39 min123.1 max228.2 mean209.8 median219.6 std25.3 best-iNshh(31,85,6,93,228*)(35,100,0,92,228*) can2m
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(104,100,9,98,-1*) can2m

#Fri Jun 12 16:47:03 JST 2020 TP0=2600 N:5-300:5 ns=1 ==>(hV,hg)=(148,247) 148
h(yi,yg)@L0c0 with n57 min32.0 max247.0 mean155.4 median148.0 std30.0 best-iNshh(48,60,0,247*,158) can2m1
h(yi,yg)@L2c0 with n38 min144.0 max184.0 mean148.9 median148.0 std6.4 best-iNshh(42,290,0,184*,155) can2m1
h(yi,yg)@L2c1 with n18 min93.0 max247.0 mean175.9 median183.0 std37.6 best-iNshh(48,60,0,247*,187) can2m1
h(yi,yg)@L2c2 with n1 min32.0 max32.0 mean32.0 median32.0 std0.0 best-iNshh(56,5,0,32*,-1) can2m1
hi-LOOCV@L0c0 with n57 min32.5 max193.4 mean171.0 median180.1 std26.5 best-iNshh(6,300,0,155,193*) can2m1
hi-LOOCV@L2c0 with n38 min154.8 max218.1 mean204.4 median204.8 std10.6 best-iNshh(0,155,0,148,218*) can2m1
hi-LOOCV@L2c1 with n18 min92.9 max192.5 mean168.5 median184.8 std28.5 best-iNshh(44,80,0,186,192*) can2m1
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,5,0,32,-1*) can2m1

#Fri Jun 12 16:40:06 JST 2020 TP0=2000 N:50-100:5 ns=10 ==>(hV,hg)=(157,359) 157
h(yi,yg)@L0c0 with n102 min98.0 max359.0 mean175.2 median170.5 std42.3 best-iNshh(21,85,0,359*,172) can2m
h(yi,yg)@L2c0 with n59 min126.0 max305.0 mean167.3 median157.0 std37.4 best-iNshh(41,55,3,305*,166) can2m
h(yi,yg)@L2c1 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(98,50,5,98*,-1) can2m
h(yi,yg)@L2c2 with n13 min99.0 max196.0 mean174.9 median183.0 std25.9 best-iNshh(96,70,1,196*,195) can2m
h(yi,yg)@L2c3 with n27 min156.0 max359.0 mean200.0 median188.0 std45.8 best-iNshh(21,85,0,359*,199) can2m
hi-LOOCV@L0c0 with n102 min69.9 max187.9 mean151.3 median157.0 std25.1 best-iNshh(2,90,1,187,188*) can2m
hi-LOOCV@L2c0 with n59 min140.4 max187.7 mean168.0 median170.4 std13.8 best-iNshh(60,60,6,157,188*) can2m
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(98,50,5,98,-1*) can2m
hi-LOOCV@L2c2 with n13 min107.1 max219.3 mean192.9 median201.6 std31.8 best-iNshh(93,65,1,191,219*) can2m
hi-LOOCV@L2c3 with n27 min162.4 max236.5 mean211.7 median221.1 std23.6 best-iNshh(0,55,0,190,237*) can2m

#Fri Jun 12 16:39:48 JST 2020 TP0=2500 N:5-300:5 ns=1 ==>(hV,hg)=(246,312) 246
h(yi,yg)@L0c0 with n57 min66.0 max312.0 mean203.4 median224.0 std57.7 best-iNshh(28,145,0,312*,202) can2m1
h(yi,yg)@L2c0 with n54 min137.0 max312.0 mean209.7 median224.5 std52.2 best-iNshh(28,145,0,312*,208) can2m1
h(yi,yg)@L2c1 with n1 min100.0 max100.0 mean100.0 median100.0 std0.0 best-iNshh(55,25,0,100*,-1) can2m1
h(yi,yg)@L2c2 with n1 min66.0 max66.0 mean66.0 median66.0 std0.0 best-iNshh(56,20,0,66*,-1) can2m1
hi-LOOCV@L0c0 with n57 min66.0 max248.7 mean195.1 median204.0 std40.3 best-iNshh(0,200,0,246,249*) can2m1
hi-LOOCV@L2c0 with n54 min149.7 max257.8 mean207.3 median214.5 std34.0 best-iNshh(0,200,0,246,258*) can2m1
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,25,0,100,-1*) can2m1
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,20,0,66,-1*) can2m1


#Fri Jun 12 16:19:14 JST 2020 TP0=2400 N:5-300:5 ns=1 ==>(hV,hg)=(225,354) 225
h(yi,yg)@L0c0 with n57 min56.0 max354.0 mean216.1 median227.0 std65.1 best-iNshh(20,200,0,354*,214)
h(yi,yg)@L2c0 with n51 min146.0 max354.0 mean234.2 median230.0 std40.0 best-iNshh(20,200,0,354*,232)
h(yi,yg)@L2c1 with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(51,5,0,87*,-1)
h(yi,yg)@L2c2 with n1 min56.0 max56.0 mean56.0 median56.0 std0.0 best-iNshh(55,25,0,56*,-1)
h(yi,yg)@L2c3 with n1 min56.0 max56.0 mean56.0 median56.0 std0.0 best-iNshh(56,30,0,56*,-1)
hi-LOOCV@L0c0 with n57 min61.5 max222.5 mean190.4 median210.7 std45.9 best-iNshh(6,290,0,225,222*)
hi-LOOCV@L2c0 with n51 min148.6 max241.8 mean222.4 median229.4 std19.1 best-iNshh(6,290,0,225,242*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(51,5,0,87,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,25,0,56,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,30,0,56,-1*)

#Fri Jun 12 16:12:05 JST 2020 TP0=2300 N:5-300:5 ns=1 ==>(hV,hg)=(66,202) 66
h(yi,yg)@L0c0 with n55 min63.0 max202.0 mean78.1 median66.0 std34.9 best-iNshh(49,75,0,202*,81)
h(yi,yg)@L2c0 with n5 min63.0 max63.0 mean63.0 median63.0 std0.0 best-iNshh(44,195,0,63*,192)(45,225,0,63*,196)(46,180,0,63*,192)(47,175,0,63*,168)(48,170,0,63*,168)
h(yi,yg)@L2c1 with n44 min65.0 max69.0 mean66.3 median66.0 std0.8 best-iNshh(43,200,0,69*,116)
h(yi,yg)@L2c2 with n1 min156.0 max156.0 mean156.0 median156.0 std0.0 best-iNshh(54,45,0,156*,-1)
h(yi,yg)@L2c3 with n5 min166.0 max202.0 mean181.0 median178.0 std11.8 best-iNshh(49,75,0,202*,257)
hi-LOOCV@L0c0 with n55 min72.5 max194.5 mean156.1 median175.0 std38.7 best-iNshh(0,90,0,66,194*)
hi-LOOCV@L2c0 with n5 min167.5 max196.2 mean183.1 median192.0 std12.8 best-iNshh(45,225,0,63,196*)
hi-LOOCV@L2c1 with n44 min116.2 max224.5 mean198.6 median201.5 std21.0 best-iNshh(0,90,0,66,224*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(54,45,0,156,-1*)
hi-LOOCV@L2c3 with n5 min185.8 max257.2 mean220.6 median201.8 std30.5 best-iNshh(49,75,0,202,257*)(50,70,0,177,257*)

#Fri Jun 12 16:04:41 JST 2020 TP0=2000 N:50-100:5 ns=17 ==>(hV,hg)=(169,422) 171
h(yi,yg)@L0c0 with n177 min20.0 max422.0 mean167.5 median158.0 std63.8 best-iNshh(48,65,15,422*,165)
h(yi,yg)@L2c0 with n70 min99.0 max414.0 mean188.8 median183.5 std59.2 best-iNshh(68,80,10,414*,177)
h(yi,yg)@L2c1 with n15 min20.0 max196.0 mean154.3 median180.0 std57.9 best-iNshh(169,70,1,196*,170)
h(yi,yg)@L2c2 with n55 min126.0 max422.0 mean182.9 median158.0 std50.0 best-iNshh(48,65,15,422*,182)
h(yi,yg)@L2c3 with n37 min29.0 max193.0 mean109.8 median128.0 std56.4 best-iNshh(92,75,4,193*,154)
hi-LOOCV@L0c0 with n177 min21.7 max171.2 mean146.7 median160.3 std28.4 best-iNshh(6,90,1,187,171*)
hi-LOOCV@L2c0 with n70 min99.8 max195.1 mean172.7 median179.3 std20.1 best-iNshh(4,55,0,190,195*)
hi-LOOCV@L2c1 with n15 min28.0 max190.1 mean148.9 median174.3 std53.8 best-iNshh(162,65,1,191,190*)
hi-LOOCV@L2c2 with n55 min135.0 max194.9 mean178.4 median182.7 std15.1 best-iNshh(18,85,15,169,195*)
hi-LOOCV@L2c3 with n37 min98.9 max179.1 mean153.3 median155.6 std19.8 best-iNshh(120,60,4,158,179*)

#Fri Jun 12 16:04:31 JST 2020 TP0=2200 N:5-300:5 ns=1 ==>(hV,hg)=(190,422) 187
h(yi,yg)@L0c0 with n177 min20.0 max422.0 mean167.5 median158.0 std63.8 best-iNshh(48,65,15,422*,165)
h(yi,yg)@L2c0 with n78 min99.0 max414.0 mean187.8 median183.5 std58.0 best-iNshh(68,80,10,414*,176)
h(yi,yg)@L2c1 with n15 min20.0 max196.0 mean154.3 median180.0 std57.9 best-iNshh(169,70,1,196*,170)
h(yi,yg)@L2c2 with n59 min127.0 max422.0 mean177.1 median157.0 std47.7 best-iNshh(48,65,15,422*,176)
h(yi,yg)@L2c3 with n25 min29.0 max193.0 mean89.7 median99.0 std57.7 best-iNshh(92,75,4,193*,153)
hi-LOOCV@L0c0 with n177 min21.7 max171.2 mean146.7 median160.3 std28.4 best-iNshh(6,90,1,187,171*)
hi-LOOCV@L0c0 with n177 min21.7 max171.2 mean146.7 median160.3 std28.4 best-iNshh(6,90,1,187,171*)
hi-LOOCV@L2c0 with n78 min100.0 max191.7 mean170.5 median177.5 std19.8 best-iNshh(4,55,0,190,192*)
hi-LOOCV@L2c1 with n15 min28.0 max190.1 mean148.9 median174.3 std53.8 best-iNshh(162,65,1,191,190*)
hi-LOOCV@L2c2 with n59 min138.1 max195.2 mean177.5 median180.3 std15.2 best-iNshh(54,65,9,157,195*)
hi-LOOCV@L2c3 with n25 min107.4 max167.5 mean147.7 median152.8 std18.3 best-iNshh(149,100,11,29,168*)

#Fri Jun 12 15:56:32 JST 2020 TP0=2100 N:5-300:5 ns=1 ==>(hV,hg)=(91,321) 91
h(yi,yg)@L0c0 with n57 min90.0 max321.0 mean103.7 median91.0 std40.5 best-iNshh(48,55,0,321*,106)
h(yi,yg)@L2c0 with n1 min90.0 max90.0 mean90.0 median90.0 std0.0 best-iNshh(47,80,0,90*,-1)
h(yi,yg)@L2c1 with n47 min90.0 max94.0 mean91.5 median91.0 std0.8 best-iNshh(17,245,0,94*,244)
h(yi,yg)@L2c2 with n7 min99.0 max321.0 mean177.7 median196.0 std77.9 best-iNshh(48,55,0,321*,218)
h(yi,yg)@L2c3 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(56,45,0,98*,-1)
hi-LOOCV@L0c0 with n57 min100.5 max230.2 mean193.0 median206.8 std41.6 best-iNshh(0,190,0,91,230*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(47,80,0,90,-1*)
hi-LOOCV@L2c1 with n47 min173.8 max259.8 mean236.8 median237.2 std15.7 best-iNshh(0,190,0,91,260*)
hi-LOOCV@L2c2 with n7 min188.7 max217.5 mean206.6 median214.7 std11.7 best-iNshh(48,55,0,321,218*)(50,75,0,99,218*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,45,0,98,-1*)

#Fri Jun 12 15:48:08 JST 2020 TP0=2000 N:5-300:5 ns=1 ==>(hV,hg)=(191,395) 191
h(yi,yg)@L0c0 with n58 min19.0 max395.0 mean130.5 median171.0 std90.1 best-iNshh(25,195,0,395*,128)
h(yi,yg)@L2c0 with n38 min71.0 max395.0 mean188.4 median190.0 std51.7 best-iNshh(25,195,0,395*,186)
h(yi,yg)@L2c1 with n1 min45.0 max45.0 mean45.0 median45.0 std0.0 best-iNshh(57,5,0,45*,-1)
h(yi,yg)@L2c2 with n5 min19.0 max20.0 mean19.6 median20.0 std0.5 best-iNshh(53,230,0,20*,166)(54,225,0,20*,166)(55,235,0,20*,133)
h(yi,yg)@L2c3 with n14 min19.0 max20.0 mean19.2 median19.0 std0.4 best-iNshh(39,210,0,20*,235)(41,215,0,20*,231)(56,220,0,20*,63)
hi-LOOCV@L0c0 with n58 min36.9 max174.2 mean115.9 median119.1 std43.9 best-iNshh(0,125,0,191,174*)
hi-LOOCV@L2c0 with n38 min71.2 max257.7 mean207.3 median229.0 std45.7 best-iNshh(0,125,0,191,258*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(57,5,0,45,-1*)
hi-LOOCV@L2c2 with n5 min90.0 max166.2 mean129.1 median133.2 std34.1 best-iNshh(53,230,0,20,166*)
hi-LOOCV@L2c3 with n14 min62.8 max276.8 mean234.8 median238.6 std50.9 best-iNshh(37,280,0,19,277*)(38,285,0,19,277*)

#Fri Jun 12 15:43:23 JST 2020 TP0=2900 N:50-100:12 ns=17 ==>(hV,hg)=(217,309) 216
h(yi,yg)@L0c0 with n84 min72.0 max309.0 mean169.4 median188.0 std66.8 best-iNshh(26,98,8,309*,168)(31,98,12,309*,166)
h(yi,yg)@L2c0 with n45 min125.0 max309.0 mean202.4 median189.0 std38.8 best-iNshh(26,98,8,309*,201)(31,98,12,309*,200)
h(yi,yg)@L2c1 with n19 min77.0 max278.0 mean191.0 median215.0 std60.4 best-iNshh(15,86,6,278*,220)
h(yi,yg)@L2c2 with n8 min75.0 max76.0 mean75.9 median76.0 std0.3 best-iNshh(72,98,10,76*,177)(75,62,7,76*,222)(77,86,10,76*,222)(78,74,10,76*,136)(79,50,0,76*,210)(80,98,11,76*,212)(82,62,2,76*,199)
h(yi,yg)@L2c3 with n12 min72.0 max75.0 mean73.5 median73.5 std0.8 best-iNshh(64,86,13,75*,224)
hi-LOOCV@L0c0 with n84 min87.5 max187.4 mean142.8 median153.4 std33.5 best-iNshh(1,98,6,216,187*)
hi-LOOCV@L2c0 with n45 min128.0 max218.0 mean193.3 median198.7 std21.9 best-iNshh(4,86,5,217,218*)
hi-LOOCV@L2c1 with n19 min129.1 max270.4 mean229.8 median241.7 std33.9 best-iNshh(39,74,7,218,270*)
hi-LOOCV@L2c2 with n8 min135.9 max222.1 mean190.6 median204.6 std31.7 best-iNshh(77,86,10,76,222*)
hi-LOOCV@L2c3 with n12 min186.7 max231.0 mean215.1 median219.4 std14.1 best-iNshh(63,62,13,74,231*)

#Fri Jun 12 15:37:51 JST 2020 TP0=2800 N:50-100:12 ns=17 ==>(hV,hg)=(256,349) 256
h(yi,yg)@L0c0 with n85 min53.0 max349.0 mean163.8 median167.0 std65.2 best-iNshh(28,50,1,349*,152)
h(yi,yg)@L2c0 with n49 min105.0 max349.0 mean175.7 median152.0 std62.4 best-iNshh(28,50,1,349*,169)
h(yi,yg)@L2c1 with n29 min63.0 max315.0 mean170.1 median170.0 std51.8 best-iNshh(29,86,14,315*,169)
h(yi,yg)@L2c2 with n5 min53.0 max54.0 mean53.2 median53.0 std0.4 best-iNshh(78,74,12,54*,210)
h(yi,yg)@L2c3 with n1 min55.0 max55.0 mean55.0 median55.0 std0.0 best-iNshh(84,50,7,55*,-1)
hi-LOOCV@L0c0 with n85 min56.3 max166.3 mean134.5 median147.2 std30.3 best-iNshh(0,62,14,168,166*)
hi-LOOCV@L2c0 with n49 min110.2 max172.8 mean153.6 median156.6 std17.0 best-iNshh(11,62,16,256,173*)
hi-LOOCV@L2c1 with n29 min92.5 max218.0 mean184.4 median194.8 std29.9 best-iNshh(65,74,13,171,218*)
hi-LOOCV@L2c2 with n5 min144.0 max210.5 mean195.2 median207.5 std25.7 best-iNshh(78,74,12,54,210*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(84,50,7,55,-1*)

#Fri Jun 12 15:32:22 JST 2020 TP0=2900 N:50-100:15 ns=17 ==>(hV,hg)=(215,342) 214
h(yi,yg)@L0c0 with n66 min72.0 max342.0 mean165.8 median187.5 std72.5 best-iNshh(21,65,5,342*,162)
h(yi,yg)@L2c0 with n15 min72.0 max76.0 mean74.1 median74.0 std1.1 best-iNshh(57,80,10,76*,138)(59,65,7,76*,125)
h(yi,yg)@L2c1 with n1 min77.0 max77.0 mean77.0 median77.0 std0.0 best-iNshh(65,95,13,77*,-1)
h(yi,yg)@L2c2 with n9 min78.0 max216.0 mean160.4 median189.0 std58.9 best-iNshh(25,80,1,216*,189)
h(yi,yg)@L2c3 with n41 min76.0 max342.0 mean202.7 median209.0 std55.3 best-iNshh(21,65,5,342*,197)
hi-LOOCV@L0c0 with n66 min78.9 max173.2 mean134.9 median144.5 std31.0 best-iNshh(1,80,14,214,173*)
hi-LOOCV@L2c0 with n15 min111.9 max231.2 mean179.4 median192.4 std34.4 best-iNshh(44,65,0,75,231*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(65,95,13,77,-1*)
hi-LOOCV@L2c2 with n9 min144.2 max271.4 mean188.1 median189.4 std39.0 best-iNshh(53,80,15,86,271*)
hi-LOOCV@L2c3 with n41 min80.8 max208.3 mean181.1 median194.8 std31.0 best-iNshh(0,65,2,215,208*)

#Fri Jun 12 15:32:18 JST 2020 TP0=2700 N:50-100:12 ns=17 ==>(hV,hg)=(215,342) 214
h(yi,yg)@L0c0 with n66 min72.0 max342.0 mean165.8 median187.5 std72.5 best-iNshh(21,65,5,342*,162)
h(yi,yg)@L2c0 with n15 min72.0 max76.0 mean74.1 median74.0 std1.1 best-iNshh(57,80,10,76*,138)(59,65,7,76*,125)
h(yi,yg)@L2c1 with n1 min77.0 max77.0 mean77.0 median77.0 std0.0 best-iNshh(65,95,13,77*,-1)
h(yi,yg)@L2c2 with n9 min78.0 max216.0 mean160.4 median189.0 std58.9 best-iNshh(25,80,1,216*,189)
h(yi,yg)@L2c3 with n41 min76.0 max342.0 mean202.7 median209.0 std55.3 best-iNshh(21,65,5,342*,197)
hi-LOOCV@L0c0 with n66 min78.9 max173.2 mean134.9 median144.5 std31.0 best-iNshh(1,80,14,214,173*)
hi-LOOCV@L2c0 with n15 min111.9 max231.2 mean179.4 median192.4 std34.4 best-iNshh(44,65,0,75,231*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(65,95,13,77,-1*)
hi-LOOCV@L2c2 with n9 min144.2 max271.4 mean188.1 median189.4 std39.0 best-iNshh(53,80,15,86,271*)
hi-LOOCV@L2c3 with n41 min80.8 max208.3 mean181.1 median194.8 std31.0 best-iNshh(0,65,2,215,208*)

#Fri Jun 12 15:27:56 JST 2020 TP0=2800 N:50-100:15 ns=17 ==>(hV,hg)=(170,349) 170
h(yi,yg)@L0c0 with n68 min52.0 max349.0 mean152.9 median165.0 std62.3 best-iNshh(26,50,1,349*,144)
h(yi,yg)@L2c0 with n56 min105.0 max349.0 mean173.1 median167.0 std49.0 best-iNshh(26,50,1,349*,164)
h(yi,yg)@L2c1 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(65,50,12,54*,-1)
h(yi,yg)@L2c2 with n1 min52.0 max52.0 mean52.0 median52.0 std0.0 best-iNshh(67,65,12,52*,-1)
h(yi,yg)@L2c3 with n6 min64.0 max65.0 mean64.5 median64.5 std0.5 best-iNshh(59,50,13,65*,226)(60,80,6,65*,260)(61,80,12,65*,251)
hi-LOOCV@L0c0 with n68 min55.9 max158.2 mean125.8 median139.8 std30.5 best-iNshh(3,80,9,170,158*)
hi-LOOCV@L2c0 with n56 min105.2 max176.9 mean154.7 median163.2 std19.3 best-iNshh(3,80,9,170,177*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(65,50,12,54,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(67,65,12,52,-1*)
hi-LOOCV@L2c3 with n6 min226.2 max262.2 mean244.7 median245.8 std14.3 best-iNshh(58,95,11,64,262*)

#Fri Jun 12 15:26:35 JST 2020 TP0=2600 N:50-100:12 ns=17 ==>(hV,hg)=(183,277) 183
h(yi,yg)@L0c0 with n85 min39.0 max277.0 mean167.1 median154.0 std43.3 best-iNshh(4,50,10,277*,168)
h(yi,yg)@L2c0 with n15 min116.0 max128.0 mean124.5 median125.0 std2.6 best-iNshh(68,50,15,128*,144)(74,74,5,128*,151)
h(yi,yg)@L2c1 with n68 min146.0 max277.0 mean180.1 median171.5 std36.4 best-iNshh(4,50,10,277*,181)
h(yi,yg)@L2c2 with n1 min39.0 max39.0 mean39.0 median39.0 std0.0 best-iNshh(84,62,7,39*,-1)
hi-LOOCV@L0c0 with n85 min41.9 max173.0 mean157.0 median165.4 std21.8 best-iNshh(11,86,14,183,173*)
hi-LOOCV@L2c0 with n15 min109.8 max202.7 mean181.9 median192.8 std25.9 best-iNshh(77,50,8,126,203*)
hi-LOOCV@L2c1 with n68 min166.3 max187.8 mean178.6 median180.0 std5.0 best-iNshh(11,86,14,183,188*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(84,62,7,39,-1*)

#Fri Jun 12 15:23:34 JST 2020 TP0=2700 N:50-100:15 ns=17 ==>(hV,hg)=(270,387) 270
h(yi,yg)@L0c0 with n67 min86.0 max387.0 mean176.5 median155.0 std58.9 best-iNshh(27,65,13,387*,165)
h(yi,yg)@L2c0 with n58 min131.0 max387.0 mean188.9 median174.0 std53.3 best-iNshh(27,65,13,387*,176)
h(yi,yg)@L2c1 with n1 min112.0 max112.0 mean112.0 median112.0 std0.0 best-iNshh(60,50,15,112*,-1)
h(yi,yg)@L2c2 with n5 min87.0 max88.0 mean87.6 median88.0 std0.5 best-iNshh(61,80,6,88*,260)(63,65,9,88*,225)(64,65,15,88*,226)
h(yi,yg)@L2c3 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(66,50,5,86*,-1)
hi-LOOCV@L0c0 with n67 min92.0 max179.5 mean154.3 median160.0 std22.0 best-iNshh(2,80,8,270,179*)
hi-LOOCV@L2c0 with n58 min136.3 max192.5 mean172.4 median171.1 std10.0 best-iNshh(2,80,8,270,192*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(60,50,15,112,-1*)
hi-LOOCV@L2c2 with n5 min177.5 max259.5 mean229.5 median226.2 std30.1 best-iNshh(61,80,6,88,260*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(66,50,5,86,-1*)

#Fri Jun 12 15:20:59 JST 2020 TP0=2500 N:50-100:12 ns=17 ==>(hV,hg)=(247,310) 247
h(yi,yg)@L0c0 with n85 min114.0 max310.0 mean193.8 median192.0 std56.0 best-iNshh(22,98,9,310*,194)
h(yi,yg)@L2c0 with n9 min137.0 max138.0 mean137.9 median138.0 std0.3 best-iNshh(52,74,1,138*,325)(56,50,14,138*,325)(61,98,10,138*,319)(66,98,11,138*,326)(68,98,3,138*,303)(74,62,7,138*,283)(77,98,16,138*,303)(79,62,12,138*,271)
h(yi,yg)@L2c1 with n20 min130.0 max137.0 mean134.7 median135.0 std1.6 best-iNshh(35,50,12,137*,258)
h(yi,yg)@L2c2 with n50 min139.0 max310.0 mean232.3 median238.0 std40.7 best-iNshh(22,98,9,310*,231)
h(yi,yg)@L2c3 with n6 min114.0 max166.0 mean153.8 median160.5 std18.0 best-iNshh(69,62,3,166*,202)
hi-LOOCV@L0c0 with n85 min134.2 max207.1 mean177.4 median174.2 std18.2 best-iNshh(11,86,0,247,207*)
hi-LOOCV@L2c0 with n9 min271.4 max325.8 mean303.4 median302.9 std20.7 best-iNshh(66,98,11,138,326*)
hi-LOOCV@L2c1 with n20 min170.7 max271.2 mean235.5 median238.5 std27.2 best-iNshh(63,86,5,134,271*)
hi-LOOCV@L2c2 with n50 min144.4 max253.9 mean223.9 median231.0 std22.3 best-iNshh(11,86,0,247,254*)
hi-LOOCV@L2c3 with n6 min201.8 max219.2 mean210.8 median210.4 std6.7 best-iNshh(84,50,9,114,219*)

#Fri Jun 12 15:19:09 JST 2020 TP0=2600 N:50-100:15 ns=17 ==>(hV,hg)=(185,308) 185
h(yi,yg)@L0c0 with n68 min39.0 max308.0 mean167.4 median153.0 std44.0 best-iNshh(21,65,14,308*,169)
h(yi,yg)@L2c0 with n55 min129.0 max308.0 mean179.1 median157.0 std39.5 best-iNshh(21,65,14,308*,181)
h(yi,yg)@L2c1 with n12 min116.0 max128.0 mean124.5 median125.0 std2.8 best-iNshh(56,50,15,128*,133)
h(yi,yg)@L2c2 with n1 min39.0 max39.0 mean39.0 median39.0 std0.0 best-iNshh(67,65,7,39*,-1)
hi-LOOCV@L0c0 with n68 min39.7 max171.8 mean156.3 median162.9 std19.2 best-iNshh(0,65,13,185,172*)
hi-LOOCV@L2c0 with n55 min150.0 max184.5 mean174.3 median176.0 std7.1 best-iNshh(0,65,13,185,185*)
hi-LOOCV@L2c1 with n12 min111.4 max196.5 mean177.5 median188.4 std25.9 best-iNshh(61,50,8,126,197*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(67,65,7,39,-1*)

#Fri Jun 12 15:15:27 JST 2020 TP0=2400 N:50-100:12 ns=17 ==>(hV,hg)=(203,498) 233
h(yi,yg)@L0c0 with n82 min56.0 max498.0 mean160.8 median172.5 std86.1 best-iNshh(22,86,16,498*,148)
h(yi,yg)@L2c0 with n34 min68.0 max498.0 mean204.6 median201.0 std66.6 best-iNshh(22,86,16,498*,196)
h(yi,yg)@L2c1 with n20 min74.0 max293.0 mean224.7 median231.5 std42.6 best-iNshh(11,86,0,293*,223)
h(yi,yg)@L2c2 with n25 min56.0 max65.0 mean60.8 median61.0 std2.5 best-iNshh(80,98,14,65*,80)
h(yi,yg)@L2c3 with n1 min67.0 max67.0 mean67.0 median67.0 std0.0 best-iNshh(76,74,6,67*,-1)
hi-LOOCV@L0c0 with n82 min68.5 max168.5 mean118.6 median122.5 std29.9 best-iNshh(1,62,3,233,168*)
hi-LOOCV@L2c0 with n34 min124.3 max203.2 mean184.6 median193.3 std17.8 best-iNshh(13,50,4,203,203*)
hi-LOOCV@L2c1 with n20 min176.0 max268.8 mean238.5 median245.6 std27.5 best-iNshh(16,74,7,234,269*)
hi-LOOCV@L2c2 with n25 min79.8 max173.0 mean141.6 median148.7 std23.8 best-iNshh(52,74,15,62,173*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(76,74,6,67,-1*)

#Fri Jun 12 15:14:46 JST 2020 TP0=2500 N:50-100:15 ns=17 ==>(hV,hg)=(253,286) 253
h(yi,yg)@L0c0 with n68 min114.0 max286.0 mean188.9 median177.0 std53.5 best-iNshh(1,80,8,286*,198)
h(yi,yg)@L2c0 with n38 min140.0 max286.0 mean227.9 median225.0 std39.7 best-iNshh(1,80,8,286*,242)
h(yi,yg)@L2c1 with n6 min114.0 max164.0 mean152.8 median159.5 std17.5 best-iNshh(55,50,10,164*,200)
h(yi,yg)@L2c2 with n15 min132.0 max139.0 mean135.0 median135.0 std1.7 best-iNshh(63,65,8,139*,138)
h(yi,yg)@L2c3 with n9 min137.0 max139.0 mean137.9 median138.0 std0.6 best-iNshh(66,95,3,139*,172)
hi-LOOCV@L0c0 with n68 min137.4 max200.0 mean173.5 median173.2 std15.9 best-iNshh(0,80,12,253,200*)
hi-LOOCV@L2c0 with n38 min160.5 max246.9 mean218.6 median221.2 std20.0 best-iNshh(0,80,12,253,247*)
hi-LOOCV@L2c1 with n6 min197.8 max227.4 mean211.6 median211.8 std10.8 best-iNshh(52,65,4,158,227*)
hi-LOOCV@L2c2 with n15 min138.3 max263.4 mean228.1 median243.8 std34.6 best-iNshh(42,95,13,135,263*)
hi-LOOCV@L2c3 with n9 min171.8 max288.0 mean260.1 median279.9 std34.9 best-iNshh(61,95,11,138,288*)

#Fri Jun 12 15:10:25 JST 2020 TP0=2400 N:50-100:15 ns=17 ==>(hV,hg)=(237,351) 238
h(yi,yg)@L0c0 with n67 min56.0 max351.0 mean153.9 median172.0 std83.8 best-iNshh(10,80,10,351*,151)
h(yi,yg)@L2c0 with n34 min66.0 max345.0 mean200.6 median201.0 std57.4 best-iNshh(8,95,0,345*,201)(9,95,11,345*,201)
h(yi,yg)@L2c1 with n11 min75.0 max351.0 mean195.4 median228.0 std82.4 best-iNshh(10,80,10,351*,189)
h(yi,yg)@L2c2 with n9 min56.0 max61.0 mean58.7 median59.0 std1.8 best-iNshh(50,50,7,61*,193)
h(yi,yg)@L2c3 with n13 min61.0 max65.0 mean62.4 median62.0 std1.3 best-iNshh(64,95,14,65*,99)
hi-LOOCV@L0c0 with n67 min64.4 max151.9 mean115.4 median122.1 std25.4 best-iNshh(7,80,6,238,152*)
hi-LOOCV@L2c0 with n34 min62.7 max201.4 mean179.2 median191.4 std29.6 best-iNshh(0,50,3,237,201*)
hi-LOOCV@L2c1 with n11 min141.6 max264.1 mean198.8 median212.0 std40.6 best-iNshh(37,95,15,230,264*)
hi-LOOCV@L2c2 with n9 min112.9 max193.2 mean168.8 median183.4 std25.3 best-iNshh(50,50,7,61,193*)
hi-LOOCV@L2c3 with n13 min99.4 max228.4 mean193.5 median202.6 std34.2 best-iNshh(43,65,12,63,228*)

#Fri Jun 12 15:09:58 JST 2020 TP0=2300 N:50-100:12 ns=17 ==>(hV,hg)=(179,246) 245
h(yi,yg)@L0c0 with n80 min65.0 max246.0 mean142.5 median158.5 std47.3 best-iNshh(15,74,12,246*,144)
h(yi,yg)@L2c0 with n10 min65.0 max69.0 mean67.3 median67.5 std1.3 best-iNshh(71,86,5,69*,162)(74,86,4,69*,144)
h(yi,yg)@L2c1 with n1 min65.0 max65.0 mean65.0 median65.0 std0.0 best-iNshh(78,86,0,65*,-1)
h(yi,yg)@L2c2 with n50 min69.0 max246.0 mean156.7 median159.0 std28.9 best-iNshh(15,74,12,246*,157)
h(yi,yg)@L2c3 with n18 min79.0 max245.0 mean153.2 median165.5 std56.2 best-iNshh(0,50,12,245*,165)
hi-LOOCV@L0c0 with n80 min70.8 max154.1 mean120.7 median130.9 std24.6 best-iNshh(0,50,12,245,154*)
hi-LOOCV@L2c0 with n10 min106.9 max195.7 mean161.0 median160.7 std25.4 best-iNshh(68,50,13,68,196*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(78,86,0,65,-1*)
hi-LOOCV@L2c2 with n50 min68.7 max171.0 mean153.0 median160.8 std19.5 best-iNshh(4,98,6,179,171*)
hi-LOOCV@L2c3 with n18 min85.2 max208.9 mean164.9 median176.3 std36.3 best-iNshh(35,50,4,190,209*)

#Fri Jun 12 15:06:05 JST 2020 TP0=2300 N:50-100:15 ns=17 ==>(hV,hg)=(188,301) 167
h(yi,yg)@L0c0 with n66 min65.0 max301.0 mean138.0 median145.0 std52.2 best-iNshh(18,95,1,301*,136)
h(yi,yg)@L2c0 with n35 min70.0 max301.0 mean152.5 median158.0 std37.2 best-iNshh(18,95,1,301*,154)
h(yi,yg)@L2c1 with n17 min79.0 max273.0 mean166.6 median167.0 std48.6 best-iNshh(3,80,12,273*,175)
h(yi,yg)@L2c2 with n10 min65.0 max68.0 mean66.6 median66.5 std0.9 best-iNshh(51,80,6,68*,185)(64,50,9,68*,108)
h(yi,yg)@L2c3 with n4 min68.0 max69.0 mean68.5 median68.5 std0.5 best-iNshh(57,80,4,69*,232)(60,65,4,69*,222)
hi-LOOCV@L0c0 with n66 min72.3 max144.8 mean117.3 median121.3 std21.9 best-iNshh(2,95,16,167,145*)
hi-LOOCV@L2c0 with n35 min69.7 max164.4 mean144.0 median144.1 std16.6 best-iNshh(11,65,1,188,164*)
hi-LOOCV@L2c1 with n17 min129.0 max204.9 mean168.9 median174.7 std23.9 best-iNshh(28,65,6,168,205*)
hi-LOOCV@L2c2 with n10 min108.4 max192.8 mean171.7 median182.1 std24.6 best-iNshh(58,95,13,67,193*)
hi-LOOCV@L2c3 with n4 min127.7 max231.7 mean203.2 median226.7 std43.8 best-iNshh(50,50,13,68,232*)(57,80,4,69,232*)

#Fri Jun 12 15:04:23 JST 2020 TP0=2200 N:50-100:12 ns=17 ==>(hV,hg)=(192,316) 192
h(yi,yg)@L0c0 with n85 min89.0 max316.0 mean176.9 median166.0 std47.6 best-iNshh(3,50,13,316*,180)
h(yi,yg)@L2c0 with n78 min99.0 max316.0 mean183.8 median168.0 std43.4 best-iNshh(3,50,13,316*,187)
h(yi,yg)@L2c1 with n1 min89.0 max89.0 mean89.0 median89.0 std0.0 best-iNshh(84,50,12,89*,-1)
h(yi,yg)@L2c2 with n5 min103.0 max104.0 mean103.8 median104.0 std0.4 best-iNshh(77,98,2,104*,189)(78,62,12,104*,188)(79,62,14,104*,159)(80,98,4,104*,154)
h(yi,yg)@L2c3 with n1 min90.0 max90.0 mean90.0 median90.0 std0.0 best-iNshh(83,62,10,90*,-1)
hi-LOOCV@L0c0 with n85 min87.1 max181.8 mean160.1 median167.5 std22.9 best-iNshh(11,74,3,192,182*)
hi-LOOCV@L2c0 with n78 min97.4 max189.3 mean171.3 median175.3 std16.6 best-iNshh(11,74,3,192,189*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(84,50,12,89,-1*)
hi-LOOCV@L2c2 with n5 min140.8 max188.8 mean166.0 median159.0 std19.2 best-iNshh(77,98,2,104,189*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(83,62,10,90,-1*)

#Fri Jun 12 15:01:39 JST 2020 TP0=2200 N:50-100:15 ns=17 ==>(hV,hg)=(371,371) 371
h(yi,yg)@L0c0 with n66 min45.0 max371.0 mean187.4 median164.5 std63.1 best-iNshh(0,80,12,371*,190)(4,95,12,371*,188)
h(yi,yg)@L2c0 with n62 min99.0 max371.0 mean193.5 median166.0 std59.6 best-iNshh(0,80,12,371*,196)(4,95,12,371*,194)
h(yi,yg)@L2c1 with n1 min89.0 max89.0 mean89.0 median89.0 std0.0 best-iNshh(64,50,12,89*,-1)
h(yi,yg)@L2c2 with n1 min45.0 max45.0 mean45.0 median45.0 std0.0 best-iNshh(65,65,14,45*,-1)
hi-LOOCV@L0c0 with n66 min45.0 max189.5 mean162.0 median171.8 std25.4 best-iNshh(0,80,12,371,190*)
hi-LOOCV@L2c0 with n62 min97.7 max195.9 mean171.5 median177.5 std17.7 best-iNshh(0,80,12,371,196*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(64,50,12,89,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(65,65,14,45,-1*)

#Fri Jun 12 14:53:16 JST 2020 TP0=2000 N:50-100:12 ns=17 ==>(hV,hg)=(304,336) 220
h(yi,yg)@L0c0 with n82 min20.0 max336.0 mean168.0 median168.5 std58.2 best-iNshh(14,74,12,336*,168)
h(yi,yg)@L2c0 with n24 min156.0 max304.0 mean199.6 median185.0 std47.9 best-iNshh(7,98,4,304*,207)(17,86,6,304*,201)
h(yi,yg)@L2c1 with n23 min29.0 max172.0 mean116.7 median141.0 std49.2 best-iNshh(36,86,4,172*,150)
h(yi,yg)@L2c2 with n8 min20.0 max197.0 mean166.9 median186.5 std55.9 best-iNshh(49,98,3,197*,199)
h(yi,yg)@L2c3 with n27 min99.0 max336.0 mean184.1 median185.0 std43.0 best-iNshh(14,74,12,336*,181)
hi-LOOCV@L0c0 with n82 min20.7 max173.9 mean144.6 median154.5 std27.4 best-iNshh(1,86,15,220,174*)
hi-LOOCV@L2c0 with n24 min150.5 max206.6 mean186.0 median184.5 std12.7 best-iNshh(7,98,4,304,207*)
hi-LOOCV@L2c1 with n23 min108.6 max168.4 mean150.4 median151.7 std16.4 best-iNshh(39,74,4,157,168*)
hi-LOOCV@L2c2 with n8 min15.7 max202.6 mean173.0 median192.6 std59.6 best-iNshh(65,98,5,191,203*)
hi-LOOCV@L2c3 with n27 min100.0 max196.0 mean172.5 median181.5 std24.6 best-iNshh(11,86,10,185,196*)

#Fri Jun 12 14:58:49 JST 2020 TP0=2100 N:50-100:12 ns=17 ==>(hV,hg)=(262,323) 262
h(yi,yg)@L0c0 with n83 min88.0 max323.0 mean139.8 median99.0 std61.6 best-iNshh(14,62,8,323*,144)
h(yi,yg)@L2c0 with n49 min97.0 max323.0 mean172.4 median175.0 std61.8 best-iNshh(14,62,8,323*,180)
h(yi,yg)@L2c1 with n4 min96.0 max98.0 mean97.2 median97.5 std0.8 best-iNshh(76,98,3,98*,113)(77,50,9,98*,108)
h(yi,yg)@L2c2 with n28 min88.0 max96.0 mean91.7 median91.5 std1.4 best-iNshh(80,62,11,96*,107)
h(yi,yg)@L2c3 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(79,86,14,98*,-1)
hi-LOOCV@L0c0 with n83 min98.8 max151.4 mean131.9 median135.9 std13.4 best-iNshh(4,62,12,262,151*)
hi-LOOCV@L2c0 with n49 min114.4 max193.3 mean167.8 median174.6 std19.6 best-iNshh(4,62,12,262,193*)
hi-LOOCV@L2c1 with n4 min107.7 max164.3 mean135.8 median135.7 std25.5 best-iNshh(82,62,16,97,164*)
hi-LOOCV@L2c2 with n28 min106.6 max239.1 mean213.7 median229.0 std30.8 best-iNshh(15,74,13,93,239*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(79,86,14,98,-1*)

#Fri Jun 12 14:57:15 JST 2020 TP0=2100 N:50-100:15 ns=17 ==>(hV,hg)=(99,353) 233
h(yi,yg)@L0c0 with n65 min90.0 max353.0 mean135.3 median99.0 std61.6 best-iNshh(12,95,5,353*,145)
h(yi,yg)@L2c0 with n37 min96.0 max353.0 mean148.1 median100.0 std62.8 best-iNshh(12,95,5,353*,175)
h(yi,yg)@L2c1 with n6 min106.0 max280.0 mean213.7 median227.5 std53.3 best-iNshh(56,95,6,280*,233)
h(yi,yg)@L2c2 with n19 min90.0 max95.0 mean91.7 median92.0 std1.0 best-iNshh(59,65,15,95*,134)
h(yi,yg)@L2c3 with n1 min97.0 max97.0 mean97.0 median97.0 std0.0 best-iNshh(63,65,14,97*,-1)
hi-LOOCV@L0c0 with n65 min93.8 max151.5 mean132.9 median134.6 std15.5 best-iNshh(0,65,12,233,152*)
hi-LOOCV@L2c0 with n37 min90.8 max193.0 mean172.3 median181.1 std20.4 best-iNshh(8,65,10,99,193*)
hi-LOOCV@L2c1 with n6 min163.4 max253.4 mean208.3 median205.9 std29.1 best-iNshh(55,95,14,236,253*)
hi-LOOCV@L2c2 with n19 min133.7 max256.3 mean222.0 median228.3 std33.3 best-iNshh(39,95,12,92,256*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(63,65,14,97,-1*)

#Fri Jun 12 14:52:52 JST 2020 TP0=2000 N:50-100:15 ns=17 ==>(hV,hg)=(157,422) 217
h(yi,yg)@L0c0 with n64 min20.0 max422.0 mean173.5 median158.5 std77.2 best-iNshh(12,65,15,422*,163)
h(yi,yg)@L2c0 with n24 min123.0 max414.0 mean208.2 median187.5 std74.9 best-iNshh(2,80,10,414*,192)
h(yi,yg)@L2c1 with n6 min20.0 max193.0 mean153.2 median181.5 std61.1 best-iNshh(53,95,2,193*,192)
h(yi,yg)@L2c2 with n31 min29.0 max422.0 mean157.8 median157.0 std73.8 best-iNshh(12,65,15,422*,172)
h(yi,yg)@L2c3 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(59,50,5,98*,-1)
hi-LOOCV@L0c0 with n64 min20.8 max167.1 mean142.2 median155.2 std28.3 best-iNshh(0,80,13,217,167*)
hi-LOOCV@L2c0 with n24 min123.8 max193.8 mean176.1 median182.7 std17.8 best-iNshh(29,95,3,348,194*)
hi-LOOCV@L2c1 with n6 min15.8 max193.0 mean144.1 median170.6 std62.0 best-iNshh(56,65,1,191,193*)
hi-LOOCV@L2c2 with n31 min140.5 max183.2 mean165.0 median168.1 std12.2 best-iNshh(16,80,6,157,183*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(59,50,5,98,-1*)

#Fri Jun 12 14:42:59 JST 2020 TP0=2200 N:50-100:20 ns=17 ==>(hV,hg)=(166,316) 166
h(yi,yg)@L0c0 with n50 min46.0 max316.0 mean178.1 median166.0 std55.4 best-iNshh(7,50,13,316*,176)
h(yi,yg)@L2c0 with n47 min89.0 max316.0 mean184.1 median166.0 std51.3 best-iNshh(7,50,13,316*,182)
h(yi,yg)@L2c1 with n1 min103.0 max103.0 mean103.0 median103.0 std0.0 best-iNshh(46,50,5,103*,-1)
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(49,90,2,46*,-1)
hi-LOOCV@L0c0 with n50 min46.0 max177.9 mean156.7 median169.0 std27.8 best-iNshh(0,50,4,166,178*)
hi-LOOCV@L2c0 with n47 min87.5 max184.0 mean166.3 median176.7 std21.8 best-iNshh(0,50,4,166,184*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(46,50,5,103,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(49,90,2,46,-1*)

#Fri Jun 12 14:39:51 JST 2020 TP0=2100 N:50-100:20 ns=17 ==>(hV,hg)=(98,268) 203
h(yi,yg)@L0c0 with n50 min90.0 max268.0 mean143.3 median126.0 std52.6 best-iNshh(7,50,1,268*,156)
h(yi,yg)@L2c0 with n14 min106.0 max236.0 mean196.6 median203.5 std31.8 best-iNshh(31,90,14,236*,201)
h(yi,yg)@L2c1 with n23 min96.0 max268.0 mean139.8 median146.0 std46.5 best-iNshh(7,50,1,268*,176)
h(yi,yg)@L2c2 with n12 min90.0 max93.0 mean91.6 median91.5 std1.0 best-iNshh(24,50,4,93*,258)(39,90,12,93*,240)(41,90,4,93*,249)
h(yi,yg)@L2c3 with n1 min96.0 max96.0 mean96.0 median96.0 std0.0 best-iNshh(47,70,11,96*,-1)
hi-LOOCV@L0c0 with n50 min96.4 max165.0 mean137.1 median137.5 std18.2 best-iNshh(5,70,12,203,165*)
hi-LOOCV@L2c0 with n14 min122.2 max225.8 mean195.9 median198.7 std24.5 best-iNshh(4,70,3,205,226*)
hi-LOOCV@L2c1 with n23 min90.2 max177.7 mean161.7 median167.2 std19.5 best-iNshh(27,70,15,98,178*)
hi-LOOCV@L2c2 with n12 min175.0 max258.1 mean227.5 median235.1 std25.6 best-iNshh(24,50,4,93,258*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(47,70,11,96,-1*)

#Fri Jun 12 14:36:39 JST 2020 TP0=2000 N:50-100:20 ns=17 ==>(hV,hg)=(157,295) 187
h(yi,yg)@L0c0 with n47 min20.0 max295.0 mean162.4 median157.0 std52.4 best-iNshh(18,90,9,295*,161)
h(yi,yg)@L2c0 with n19 min137.0 max274.0 mean192.4 median188.0 std31.6 best-iNshh(5,50,3,274*,194)
h(yi,yg)@L2c1 with n23 min29.0 max295.0 mean143.4 median156.0 std50.3 best-iNshh(18,90,9,295*,153)
h(yi,yg)@L2c2 with n4 min99.0 max196.0 mean165.2 median183.0 std38.7 best-iNshh(44,70,1,196*,166)
h(yi,yg)@L2c3 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(46,50,15,20*,-1)
hi-LOOCV@L0c0 with n47 min20.8 max175.5 mean144.1 median158.1 std32.3 best-iNshh(7,90,1,187,175*)
hi-LOOCV@L2c0 with n19 min136.6 max224.8 mean194.0 median197.1 std22.3 best-iNshh(7,90,1,187,225*)
hi-LOOCV@L2c1 with n23 min107.4 max189.5 mean159.8 median162.5 std23.6 best-iNshh(14,70,9,157,189*)
hi-LOOCV@L2c2 with n4 min104.0 max188.3 mean159.7 median173.2 std33.1 best-iNshh(43,70,2,180,188*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(46,50,15,20,-1*)

#Fri Jun 12 14:02:59 JST 2020 TP0=2900 N:50-100:10 ns=17 ==>(hV,hg)=(215,492) 215
h(yi,yg)@L0c0 with n99 min72.0 max492.0 mean170.4 median188.0 std76.8 best-iNshh(25,90,8,492*,167)
h(yi,yg)@L2c0 with n18 min77.0 max314.0 mean164.2 median211.5 std72.1 best-iNshh(59,90,4,314*,199)
h(yi,yg)@L2c1 with n58 min126.0 max492.0 mean210.4 median205.5 std56.3 best-iNshh(25,90,8,492*,205)
h(yi,yg)@L2c2 with n16 min72.0 max75.0 mean73.6 median74.0 std0.7 best-iNshh(76,100,7,75*,186)
h(yi,yg)@L2c3 with n7 min76.0 max76.0 mean76.0 median76.0 std0.0 best-iNshh(85,80,10,76*,171)(87,70,14,76*,234)(88,100,10,76*,194)(91,60,2,76*,266)(92,90,13,76*,258)(97,50,0,76*,206)(98,80,2,76*,178)
hi-LOOCV@L0c0 with n99 min83.8 max179.1 mean139.2 median153.2 std31.8 best-iNshh(0,90,1,215,179*)
hi-LOOCV@L2c0 with n18 min126.6 max269.9 mean206.4 median212.8 std35.5 best-iNshh(66,80,15,86,270*)
hi-LOOCV@L2c1 with n58 min124.8 max218.8 mean197.5 median205.2 std22.1 best-iNshh(0,90,1,215,219*)
hi-LOOCV@L2c2 with n16 min178.6 max234.1 mean213.3 median219.5 std17.5 best-iNshh(72,90,16,74,234*)
hi-LOOCV@L2c3 with n7 min170.8 max265.7 mean215.1 median205.7 std35.0 best-iNshh(91,60,2,76,266*)

#Fri Jun 12 13:56:19 JST 2020 TP0=2800 N:50-100:10 ns=17 ==>(hV,hg)=(257,374) 257
h(yi,yg)@L0c0 with n102 min52.0 max374.0 mean164.4 median167.0 std66.9 best-iNshh(20,60,1,374*,155)
h(yi,yg)@L2c0 with n14 min54.0 max136.0 mean97.1 median106.0 std28.6 best-iNshh(76,100,3,136*,124)
h(yi,yg)@L2c1 with n76 min108.0 max374.0 mean190.2 median170.0 std54.2 best-iNshh(20,60,1,374*,182)
h(yi,yg)@L2c2 with n1 min53.0 max53.0 mean53.0 median53.0 std0.0 best-iNshh(101,50,11,53*,-1)
h(yi,yg)@L2c3 with n9 min63.0 max175.0 mean88.7 median65.0 std45.9 best-iNshh(74,80,11,175*,160)
hi-LOOCV@L0c0 with n102 min54.3 max165.2 mean134.5 median150.0 std31.0 best-iNshh(0,50,16,257,165*)
hi-LOOCV@L2c0 with n14 min71.4 max135.9 mean109.7 median115.5 std19.2 best-iNshh(84,80,3,108,136*)
hi-LOOCV@L2c1 with n76 min108.5 max189.5 mean172.0 median176.5 std14.3 best-iNshh(0,50,16,257,189*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(101,50,11,53,-1*)
hi-LOOCV@L2c3 with n9 min159.8 max261.0 mean223.8 median229.9 std27.1 best-iNshh(80,100,9,63,261*)

#Fri Jun 12 13:49:39 JST 2020 TP0=2700 N:50-100:10 ns=17 ==>(hV,hg)=(270,273) 270
h(yi,yg)@L0c0 with n100 min86.0 max273.0 mean167.3 median150.5 std46.0 best-iNshh(40,80,3,273*,164)
h(yi,yg)@L2c0 with n87 min98.0 max273.0 mean176.4 median164.0 std42.0 best-iNshh(40,80,3,273*,173)
h(yi,yg)@L2c1 with n9 min89.0 max131.0 mean115.2 median117.0 std10.5 best-iNshh(85,80,1,131*,121)
h(yi,yg)@L2c2 with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(98,50,7,87*,-1)
h(yi,yg)@L2c3 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(99,50,5,86*,-1)
hi-LOOCV@L0c0 with n100 min89.2 max171.8 mean154.7 median161.3 std19.5 best-iNshh(7,80,8,270,172*)
hi-LOOCV@L2c0 with n87 min117.4 max181.7 mean169.5 median170.6 std8.8 best-iNshh(7,80,8,270,182*)
hi-LOOCV@L2c1 with n9 min108.8 max202.1 mean162.9 median194.8 std39.8 best-iNshh(87,80,4,118,202*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(98,50,7,87,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(99,50,5,86,-1*)

#Fri Jun 12 13:42:57 JST 2020 TP0=2600 N:50-100:10 ns=17 ==>(hV,hg)=(185,308) 185
h(yi,yg)@L0c0 with n102 min116.0 max308.0 mean166.0 median152.0 std38.2 best-iNshh(55,100,5,308*,163)
h(yi,yg)@L2c0 with n42 min129.0 max308.0 mean199.5 median185.0 std33.9 best-iNshh(55,100,5,308*,195)
h(yi,yg)@L2c1 with n37 min144.0 max251.0 mean153.2 median151.0 std16.6 best-iNshh(11,100,10,251*,184)
h(yi,yg)@L2c2 with n16 min124.0 max127.0 mean125.4 median125.0 std1.1 best-iNshh(84,60,8,127*,225)(88,60,6,127*,218)(91,60,4,127*,221)
h(yi,yg)@L2c3 with n7 min116.0 max128.0 mean126.0 median128.0 std4.1 best-iNshh(80,90,4,128*,260)(83,60,10,128*,257)(85,50,15,128*,181)(89,70,5,128*,247)
hi-LOOCV@L0c0 with n102 min116.0 max177.9 mean158.9 median163.5 std13.0 best-iNshh(4,90,8,185,178*)
hi-LOOCV@L2c0 with n42 min140.8 max229.2 mean201.9 median203.9 std18.8 best-iNshh(4,90,8,185,229*)
hi-LOOCV@L2c1 with n37 min183.6 max217.9 mean201.1 median202.9 std9.1 best-iNshh(17,60,1,148,218*)
hi-LOOCV@L2c2 with n16 min201.6 max225.9 mean213.5 median215.8 std7.9 best-iNshh(79,100,13,126,226*)
hi-LOOCV@L2c3 with n7 min115.2 max259.8 mean203.2 median232.8 std56.6 best-iNshh(80,90,4,128,260*)

#Fri Jun 12 13:36:18 JST 2020 TP0=2500 N:50-100:10 ns=17 ==>(hV,hg)=(284,346) 284
h(yi,yg)@L0c0 with n100 min114.0 max346.0 mean201.8 median216.5 std62.2 best-iNshh(13,70,2,346*,202)
h(yi,yg)@L2c0 with n60 min140.0 max346.0 mean244.2 median247.5 std43.4 best-iNshh(13,70,2,346*,244)
h(yi,yg)@L2c1 with n8 min114.0 max164.0 mean149.5 median159.5 std20.3 best-iNshh(79,50,10,164*,218)(81,70,16,164*,217)
h(yi,yg)@L2c2 with n24 min131.0 max139.0 mean134.7 median135.0 std1.7 best-iNshh(97,100,11,139*,138)
h(yi,yg)@L2c3 with n8 min137.0 max138.0 mean137.5 median137.5 std0.5 best-iNshh(85,50,14,138*,300)(88,60,13,138*,285)(91,80,14,138*,254)(96,100,10,138*,207)
hi-LOOCV@L0c0 with n100 min123.0 max208.5 mean179.3 median181.3 std21.3 best-iNshh(8,90,8,284,209*)
hi-LOOCV@L2c0 with n60 min153.1 max255.6 mean230.0 median239.4 std23.2 best-iNshh(8,90,8,284,256*)
hi-LOOCV@L2c1 with n8 min200.9 max227.3 mean214.7 median213.8 std8.8 best-iNshh(80,70,4,159,227*)
hi-LOOCV@L2c2 with n24 min138.0 max253.9 mean225.3 median231.3 std26.3 best-iNshh(68,90,1,135,254*)
hi-LOOCV@L2c3 with n8 min207.3 max300.3 mean270.2 median276.1 std27.1 best-iNshh(85,50,14,138,300*)

#Fri Jun 12 13:29:37 JST 2020 TP0=2400 N:50-100:10 ns=17 ==>(hV,hg)=(202,354) 350
h(yi,yg)@L0c0 with n98 min56.0 max354.0 mean162.0 median191.0 std84.4 best-iNshh(29,90,16,354*,155)
h(yi,yg)@L2c0 with n39 min68.0 max354.0 mean204.1 median201.0 std47.8 best-iNshh(29,90,16,354*,201)
h(yi,yg)@L2c1 with n24 min173.0 max351.0 mean239.8 median231.0 std41.5 best-iNshh(10,80,10,351*,238)
h(yi,yg)@L2c2 with n32 min56.0 max64.0 mean60.9 median61.0 std2.2 best-iNshh(85,80,7,64*,145)(87,90,6,64*,134)(89,100,14,64*,118)
h(yi,yg)@L2c3 with n1 min66.0 max66.0 mean66.0 median66.0 std0.0 best-iNshh(97,100,6,66*,-1)
hi-LOOCV@L0c0 with n98 min64.2 max162.2 mean124.5 median132.5 std30.2 best-iNshh(5,90,10,350,162*)
hi-LOOCV@L2c0 with n39 min125.6 max214.7 mean191.9 median200.7 std21.5 best-iNshh(25,100,2,202,215*)
hi-LOOCV@L2c1 with n24 min173.7 max250.7 mean229.5 median238.2 std20.3 best-iNshh(6,100,11,226,251*)
hi-LOOCV@L2c2 with n32 min92.0 max198.9 mean156.5 median162.0 std24.8 best-iNshh(60,90,5,62,199*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(97,100,6,66,-1*)


#Fri Jun 12 13:22:57 JST 2020 TP0=2300 N:50-100:10 ns=17 ==>(hV,hg)=(190,361) 190
h(yi,yg)@L0c0 with n101 min65.0 max361.0 mean138.4 median148.0 std55.4 best-iNshh(12,60,14,361*,140)
h(yi,yg)@L2c0 with n56 min70.0 max361.0 mean160.6 median159.5 std46.5 best-iNshh(12,60,14,361*,158)
h(yi,yg)@L2c1 with n27 min78.0 max245.0 mean139.9 median161.0 std51.0 best-iNshh(0,50,12,245*,166)
h(yi,yg)@L2c2 with n8 min68.0 max69.0 mean68.5 median68.5 std0.5 best-iNshh(84,80,4,69*,269)(89,90,4,69*,256)(91,100,9,69*,203)(92,90,12,69*,256)
h(yi,yg)@L2c3 with n10 min65.0 max68.0 mean66.3 median66.0 std1.0 best-iNshh(82,80,6,68*,193)(98,50,9,68*,109)
hi-LOOCV@L0c0 with n101 min72.5 max149.4 mean117.5 median122.1 std21.2 best-iNshh(2,70,10,190,149*)
hi-LOOCV@L2c0 with n56 min69.2 max168.3 mean150.2 median152.3 std16.2 best-iNshh(13,60,1,191,168*)
hi-LOOCV@L2c1 with n27 min87.3 max199.8 mean167.5 median178.5 std30.5 best-iNshh(74,60,11,79,200*)
hi-LOOCV@L2c2 with n8 min127.9 max268.9 mean236.6 median255.9 std45.7 best-iNshh(84,80,4,69,269*)
hi-LOOCV@L2c3 with n10 min108.6 max193.1 mean166.7 median170.6 std23.3 best-iNshh(82,80,6,68,193*)

#Fri Jun 12 13:22:28 JST 2020 TP0=2900 N:50-100:20 ns=17 ==>(hV,hg)=(215,492) 215
h(yi,yg)@L0c0 with n50 min72.0 max492.0 mean168.1 median188.0 std83.7 best-iNshh(16,90,8,492*,161)
h(yi,yg)@L2c0 with n1 min76.0 max76.0 mean76.0 median76.0 std0.0 best-iNshh(47,50,0,76*,-1)
h(yi,yg)@L2c1 with n11 min72.0 max74.0 mean73.5 median74.0 std0.7 best-iNshh(33,70,2,74*,231)(35,90,16,74*,210)(38,70,13,74*,207)(39,50,3,74*,193)(40,90,10,74*,222)(42,70,10,74*,203)
h(yi,yg)@L2c2 with n7 min78.0 max314.0 mean172.9 median159.0 std76.1 best-iNshh(28,90,4,314*,195)
h(yi,yg)@L2c3 with n29 min126.0 max492.0 mean212.3 median201.0 std66.7 best-iNshh(16,90,8,492*,202)
hi-LOOCV@L0c0 with n50 min84.5 max166.2 mean132.4 median142.3 std26.8 best-iNshh(6,90,1,215,166*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(47,50,0,76,-1*)
hi-LOOCV@L2c1 with n11 min183.0 max231.4 mean211.8 median210.1 std14.8 best-iNshh(33,70,2,74,231*)
hi-LOOCV@L2c2 with n7 min122.8 max224.7 mean168.5 median164.7 std32.0 best-iNshh(25,70,1,215,225*)
hi-LOOCV@L2c3 with n29 min126.0 max210.5 mean193.0 median202.6 std23.0 best-iNshh(6,90,1,215,210*)

#Fri Jun 12 13:16:09 JST 2020 TP0=2200 N:50-100:10 ns=17 ==>(hV,hg)=(267,371) 316
h(yi,yg)@L0c0 with n101 min46.0 max371.0 mean177.5 median166.0 std52.0 best-iNshh(21,80,12,371*,178)
h(yi,yg)@L2c0 with n94 min89.0 max371.0 mean183.7 median166.0 std48.2 best-iNshh(21,80,12,371*,184)
h(yi,yg)@L2c1 with n6 min97.0 max105.0 mean103.2 median104.5 std2.9 best-iNshh(93,60,14,105*,192)(94,60,12,105*,197)(95,70,10,105*,137)
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(100,90,2,46*,-1)
hi-LOOCV@L0c0 with n101 min46.0 max180.0 mean160.4 median172.3 std24.5 best-iNshh(9,50,13,316,180*)
hi-LOOCV@L2c0 with n94 min87.3 max186.4 mean170.2 median179.0 std18.5 best-iNshh(32,100,6,267,186*)
hi-LOOCV@L2c1 with n6 min97.4 max196.6 mean155.9 median158.5 std36.2 best-iNshh(94,60,12,105,197*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(100,90,2,46,-1*)

#Fri Jun 12 13:16:05 JST 2020 TP0=2700 N:50-100:20 ns=17 ==>(hV,hg)=(267,371) 316
h(yi,yg)@L0c0 with n101 min46.0 max371.0 mean177.5 median166.0 std52.0 best-iNshh(21,80,12,371*,178)
h(yi,yg)@L0c0 with n101 min46.0 max371.0 mean177.5 median166.0 std52.0 best-iNshh(21,80,12,371*,178)
h(yi,yg)@L2c0 with n94 min89.0 max371.0 mean183.7 median166.0 std48.2 best-iNshh(21,80,12,371*,184)
h(yi,yg)@L2c1 with n6 min97.0 max105.0 mean103.2 median104.5 std2.9 best-iNshh(93,60,14,105*,192)(94,60,12,105*,197)(95,70,10,105*,137)
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(100,90,2,46*,-1)
hi-LOOCV@L0c0 with n101 min46.0 max180.0 mean160.4 median172.3 std24.5 best-iNshh(9,50,13,316,180*)
hi-LOOCV@L0c0 with n101 min46.0 max180.0 mean160.4 median172.3 std24.5 best-iNshh(9,50,13,316,180*)
hi-LOOCV@L2c0 with n94 min87.3 max186.4 mean170.2 median179.0 std18.5 best-iNshh(32,100,6,267,186*)
hi-LOOCV@L2c1 with n6 min97.4 max196.6 mean155.9 median158.5 std36.2 best-iNshh(94,60,12,105,197*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(100,90,2,46,-1*)

#Fri Jun 12 13:12:30 JST 2020 TP0=2600 N:50-100:20 ns=17 ==>(hV,hg)=(185,277) 185
h(yi,yg)@L0c0 with n51 min116.0 max277.0 mean165.4 median153.0 std37.5 best-iNshh(4,50,10,277*,165)
h(yi,yg)@L2c0 with n15 min145.0 max157.0 mean150.0 median150.0 std3.1 best-iNshh(31,50,14,157*,170)
h(yi,yg)@L2c1 with n22 min182.0 max277.0 mean201.5 median185.0 std27.2 best-iNshh(4,50,10,277*,201)
h(yi,yg)@L2c2 with n8 min124.0 max126.0 mean124.6 median124.5 std0.7 best-iNshh(43,50,8,126*,227)
h(yi,yg)@L2c3 with n6 min116.0 max128.0 mean125.7 median127.5 std4.3 best-iNshh(34,90,4,128*,249)(38,50,15,128*,187)(39,70,5,128*,238)
hi-LOOCV@L0c0 with n51 min119.9 max176.8 mean155.9 median158.9 std13.8 best-iNshh(7,90,8,185,177*)
hi-LOOCV@L2c0 with n15 min170.0 max210.6 mean199.5 median201.6 std9.6 best-iNshh(26,70,9,151,211*)
hi-LOOCV@L2c1 with n22 min165.0 max228.0 mean206.4 median207.6 std14.0 best-iNshh(7,90,8,185,228*)
hi-LOOCV@L2c2 with n8 min189.3 max228.1 mean214.0 median219.1 std14.4 best-iNshh(45,50,6,124,228*)
hi-LOOCV@L2c3 with n6 min115.2 max249.2 mean181.8 median185.0 std51.8 best-iNshh(34,90,4,128,249*)

#Fri Jun 12 13:09:20 JST 2020 TP0=2500 N:50-100:20 ns=17 ==>(hV,hg)=(251,346) 251
h(yi,yg)@L0c0 with n50 min114.0 max346.0 mean202.7 median193.0 std61.7 best-iNshh(6,70,2,346*,203)
h(yi,yg)@L2c0 with n30 min148.0 max346.0 mean244.3 median249.0 std43.6 best-iNshh(6,70,2,346*,245)
h(yi,yg)@L2c1 with n6 min114.0 max164.0 mean153.5 median160.5 std17.8 best-iNshh(30,50,10,164*,228)(31,70,16,164*,227)
h(yi,yg)@L2c2 with n12 min132.0 max136.0 mean134.2 median134.5 std1.3 best-iNshh(38,70,7,136*,226)(40,90,13,136*,250)
h(yi,yg)@L2c3 with n1 min138.0 max138.0 mean138.0 median138.0 std0.0 best-iNshh(48,50,14,138*,-1)
hi-LOOCV@L0c0 with n50 min136.4 max211.2 mean179.9 median175.9 std23.4 best-iNshh(4,70,3,251,211*)
hi-LOOCV@L2c0 with n30 min152.4 max258.7 mean232.9 median244.7 std27.1 best-iNshh(4,70,3,251,259*)
hi-LOOCV@L2c1 with n6 min206.4 max228.2 mean220.2 median222.3 std7.6 best-iNshh(30,50,10,164,228*)
hi-LOOCV@L2c2 with n12 min196.0 max249.6 mean224.0 median225.8 std17.4 best-iNshh(40,90,13,136,250*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(48,50,14,138,-1*)

#Fri Jun 12 13:09:11 JST 2020 TP0=2100 N:50-100:10 ns=17 ==>(hV,hg)=(100,357) 92
h(yi,yg)@L0c0 with n98 min90.0 max357.0 mean143.9 median99.0 std62.4 best-iNshh(2,100,16,357*,154)
h(yi,yg)@L2c0 with n28 min90.0 max93.0 mean91.5 median92.0 std0.9 best-iNshh(34,50,4,93*,235)(65,90,12,93*,227)(72,90,4,93*,230)
h(yi,yg)@L2c1 with n1 min96.0 max96.0 mean96.0 median96.0 std0.0 best-iNshh(96,70,11,96*,-1)
h(yi,yg)@L2c2 with n52 min96.0 max357.0 mean160.4 median160.5 std61.1 best-iNshh(2,100,16,357*,184)
h(yi,yg)@L2c3 with n15 min98.0 max270.0 mean194.4 median206.0 std58.3 best-iNshh(38,60,8,270*,191)
hi-LOOCV@L0c0 with n98 min95.8 max156.3 mean132.6 median130.8 std13.9 best-iNshh(0,60,12,258,156*)
hi-LOOCV@L2c0 with n28 min148.2 max236.5 mean213.4 median225.9 std24.8 best-iNshh(43,80,4,92,237*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(96,70,11,96,-1*)
hi-LOOCV@L2c2 with n52 min91.2 max193.6 mean174.0 median181.5 std18.9 best-iNshh(6,60,1,100,194*)
hi-LOOCV@L2c3 with n15 min107.6 max234.2 mean196.0 median191.2 std29.5 best-iNshh(46,60,15,234,234*)

#Fri Jun 12 13:06:08 JST 2020 TP0=2400 N:50-100:20 ns=17 ==>(hV,hg)=(290,354) 290
h(yi,yg)@L0c0 with n48 min56.0 max354.0 mean157.8 median187.0 std89.2 best-iNshh(20,90,16,354*,150)
h(yi,yg)@L2c0 with n1 min67.0 max67.0 mean67.0 median67.0 std0.0 best-iNshh(46,70,6,67*,-1)
h(yi,yg)@L2c1 with n17 min56.0 max64.0 mean60.8 median61.0 std2.0 best-iNshh(43,90,6,64*,129)
h(yi,yg)@L2c2 with n1 min143.0 max143.0 mean143.0 median143.0 std0.0 best-iNshh(39,90,4,143*,-1)
h(yi,yg)@L2c3 with n27 min68.0 max354.0 mean226.2 median215.0 std54.6 best-iNshh(20,90,16,354*,217)
hi-LOOCV@L0c0 with n48 min68.5 max155.3 mean122.7 median131.5 std27.8 best-iNshh(15,90,0,290,155*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(46,70,6,67,-1*)
hi-LOOCV@L2c1 with n17 min93.4 max219.8 mean166.9 median173.0 std26.3 best-iNshh(25,90,5,62,220*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(39,90,4,143,-1*)
hi-LOOCV@L2c3 with n27 min109.0 max223.9 mean206.1 median213.9 std23.2 best-iNshh(15,90,0,290,224*)

#Fri Jun 12 13:02:58 JST 2020 TP0=2300 N:50-100:20 ns=17 ==>(hV,hg)=(168,245) 66
h(yi,yg)@L0c0 with n51 min65.0 max245.0 mean132.3 median142.0 std44.9 best-iNshh(0,50,12,245*,144)
h(yi,yg)@L2c0 with n4 min65.0 max68.0 mean66.0 median65.5 std1.2 best-iNshh(48,50,9,68*,109)
h(yi,yg)@L2c1 with n6 min68.0 max69.0 mean68.3 median68.0 std0.5 best-iNshh(43,90,12,69*,256)(44,90,4,69*,256)
h(yi,yg)@L2c2 with n27 min122.0 max188.0 mean151.8 median160.0 std21.6 best-iNshh(27,90,14,188*,162)
h(yi,yg)@L2c3 with n14 min78.0 max245.0 mean141.1 median161.5 std51.2 best-iNshh(0,50,12,245*,166)
hi-LOOCV@L0c0 with n51 min70.5 max145.5 mean116.9 median118.0 std21.7 best-iNshh(2,90,6,168,146*)
hi-LOOCV@L2c0 with n4 min109.0 max147.0 mean134.8 median141.7 std15.4 best-iNshh(46,90,0,66,147*)
hi-LOOCV@L2c1 with n6 min127.6 max266.0 mean237.5 median256.3 std49.4 best-iNshh(40,50,13,68,266*)
hi-LOOCV@L2c2 with n27 min131.1 max170.6 mean151.2 median151.7 std12.5 best-iNshh(10,70,3,168,171*)
hi-LOOCV@L2c3 with n14 min82.4 max189.8 mean163.8 median170.0 std28.5 best-iNshh(34,90,2,78,190*)

#Fri Jun 12 13:02:30 JST 2020 TP0=2000 N:50-100:10 ns=17 ==>(hV,hg)=(157,414) 187
h(yi,yg)@L0c0 with n97 min20.0 max414.0 mean161.8 median157.0 std59.3 best-iNshh(61,80,10,414*,155)
h(yi,yg)@L2c0 with n47 min29.0 max295.0 mean152.1 median157.0 std54.4 best-iNshh(40,90,9,295*,171)
h(yi,yg)@L2c1 with n4 min30.0 max101.0 mean82.0 median98.5 std30.0 best-iNshh(86,80,4,101*,216)
h(yi,yg)@L2c2 with n38 min123.0 max414.0 mean184.7 median181.5 std56.6 best-iNshh(61,80,10,414*,172)
h(yi,yg)@L2c3 with n8 min20.0 max196.0 mean150.1 median180.0 std57.2 best-iNshh(92,70,1,196*,159)
hi-LOOCV@L0c0 with n97 min20.8 max171.3 mean145.2 median159.2 std28.6 best-iNshh(6,90,1,187,171*)
hi-LOOCV@L2c0 with n47 min141.3 max189.9 mean171.5 median175.0 std14.2 best-iNshh(8,70,9,157,190*)
hi-LOOCV@L2c1 with n4 min78.3 max215.7 mean156.0 median165.0 std53.3 best-iNshh(86,80,4,101,216*)
hi-LOOCV@L2c2 with n38 min123.4 max192.8 mean174.0 median178.6 std17.0 best-iNshh(60,100,3,188,193*)
hi-LOOCV@L2c3 with n8 min15.7 max171.9 mean133.1 median160.4 std51.3 best-iNshh(83,80,2,180,172*)


#Fri Jun 12 12:39:11 JST 2020 TP0=2900 N:50-200:20 ns=17 ==>(hV,hg)=(212,492) 212
h(yi,yg)@L0c0 with n134 min72.0 max492.0 mean169.9 median189.0 std74.8 best-iNshh(51,90,8,492*,167)
h(yi,yg)@L2c0 with n10 min75.0 max76.0 mean75.8 median76.0 std0.4 best-iNshh(112,150,13,76*,236)(116,70,14,76*,256)(122,90,13,76*,267)(123,130,11,76*,266)(125,190,13,76*,240)(127,170,7,76*,233)(128,130,13,76*,191)(130,50,0,76*,202)
h(yi,yg)@L2c1 with n20 min72.0 max77.0 mean73.5 median73.5 std1.1 best-iNshh(131,190,6,77*,78)
h(yi,yg)@L2c2 with n70 min77.0 max492.0 mean208.4 median212.0 std56.7 best-iNshh(51,90,8,492*,204)
h(yi,yg)@L2c3 with n34 min78.0 max314.0 mean174.9 median210.0 std65.6 best-iNshh(75,90,4,314*,215)
hi-LOOCV@L0c0 with n134 min79.9 max185.1 mean143.3 median156.5 std34.6 best-iNshh(0,90,2,212,185*)
hi-LOOCV@L2c0 with n10 min191.0 max266.9 mean233.5 median236.6 std24.9 best-iNshh(122,90,13,76,267*)
hi-LOOCV@L2c1 with n20 min77.5 max231.5 mean204.6 median210.0 std32.0 best-iNshh(102,110,10,74,231*)
hi-LOOCV@L2c2 with n70 min78.2 max220.2 mean192.4 median205.7 std31.9 best-iNshh(27,170,16,212,220*)
hi-LOOCV@L2c3 with n34 min135.1 max268.4 mean215.2 median223.9 std36.5 best-iNshh(76,150,6,85,268*)

#Fri Jun 12 12:26:08 JST 2020 TP0=2800 N:50-200:20 ns=17 ==>(hV,hg)=(348,350) 259
h(yi,yg)@L0c0 with n136 min52.0 max350.0 mean174.2 median167.0 std63.3 best-iNshh(20,190,6,350*,172)
h(yi,yg)@L2c0 with n6 min52.0 max55.0 mean53.2 median53.0 std1.1 best-iNshh(134,50,7,55*,86)
h(yi,yg)@L2c1 with n6 min65.0 max106.0 mean76.3 median72.0 std13.5 best-iNshh(123,190,0,106*,73)
h(yi,yg)@L2c2 with n86 min105.0 max350.0 mean190.3 median170.0 std59.1 best-iNshh(20,190,6,350*,187)
h(yi,yg)@L2c3 with n38 min63.0 max288.0 mean172.3 median168.5 std44.4 best-iNshh(12,150,7,288*,171)
hi-LOOCV@L0c0 with n136 min54.7 max174.1 mean147.3 median162.2 std31.7 best-iNshh(10,150,2,259,174*)
hi-LOOCV@L2c0 with n6 min85.8 max160.8 mean123.2 median124.3 std29.8 best-iNshh(130,190,10,53,161*)
hi-LOOCV@L2c1 with n6 min72.6 max198.0 mean139.3 median145.3 std50.3 best-iNshh(126,150,0,72,198*)
hi-LOOCV@L2c2 with n86 min106.9 max190.3 mean167.9 median170.5 std19.5 best-iNshh(3,90,12,348,190*)
hi-LOOCV@L2c3 with n38 min108.5 max214.9 mean188.8 median198.1 std24.0 best-iNshh(57,90,6,167,215*)

#Fri Jun 12 12:12:58 JST 2020 TP0=2700 N:50-200:20 ns=17 ==>(hV,hg)=(265,356) 265
h(yi,yg)@L0c0 with n135 min86.0 max356.0 mean170.3 median150.0 std49.7 best-iNshh(29,190,1,356*,168)
h(yi,yg)@L2c0 with n10 min115.0 max118.0 mean116.7 median117.0 std0.8 best-iNshh(124,70,10,118*,234)
h(yi,yg)@L2c1 with n117 min98.0 max356.0 mean179.5 median153.0 std46.9 best-iNshh(29,190,1,356*,177)
h(yi,yg)@L2c2 with n5 min106.0 max117.0 mean111.8 median112.0 std4.7 best-iNshh(127,130,16,117*,192)(128,150,16,117*,192)
h(yi,yg)@L2c3 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(134,50,5,86*,-1)
hi-LOOCV@L0c0 with n135 min87.4 max176.9 mean156.7 median162.4 std17.3 best-iNshh(0,150,14,265,177*)
hi-LOOCV@L2c0 with n10 min196.3 max264.0 mean242.7 median248.2 std19.0 best-iNshh(117,110,15,117,264*)
hi-LOOCV@L2c1 with n117 min129.0 max187.0 mean170.8 median172.3 std8.5 best-iNshh(0,150,14,265,187*)
hi-LOOCV@L2c2 with n5 min136.8 max192.5 mean180.3 median190.5 std21.8 best-iNshh(127,130,16,117,192*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(134,50,5,86,-1*)

#Fri Jun 12 11:59:50 JST 2020 TP0=2600 N:50-200:20 ns=17 ==>(hV,hg)=(184,290) 184
h(yi,yg)@L0c0 with n136 min93.0 max290.0 mean174.0 median182.0 std42.9 best-iNshh(38,150,5,290*,174)
h(yi,yg)@L2c0 with n112 min138.0 max290.0 mean185.7 median183.0 std37.8 best-iNshh(38,150,5,290*,185)
h(yi,yg)@L2c1 with n19 min116.0 max128.0 mean125.3 median126.0 std2.6 best-iNshh(113,90,4,128*,180)(114,50,15,128*,148)(116,70,5,128*,176)
h(yi,yg)@L2c2 with n4 min93.0 max94.0 mean93.8 median94.0 std0.4 best-iNshh(132,170,2,94*,206)(133,130,13,94*,223)(134,130,2,94*,213)
h(yi,yg)@L2c3 with n1 min112.0 max112.0 mean112.0 median112.0 std0.0 best-iNshh(130,150,8,112*,-1)
hi-LOOCV@L0c0 with n136 min95.0 max185.0 mean160.8 median164.8 std19.7 best-iNshh(8,110,8,184,185*)
hi-LOOCV@L2c0 with n112 min151.8 max199.3 mean179.5 median181.3 std10.8 best-iNshh(8,110,8,184,199*)
hi-LOOCV@L2c1 with n19 min112.8 max207.6 mean179.4 median183.6 std21.2 best-iNshh(112,190,7,127,208*)
hi-LOOCV@L2c2 with n4 min193.3 max222.7 mean208.8 median209.7 std10.7 best-iNshh(133,130,13,94,223*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(130,150,8,112,-1*)

#Fri Jun 12 11:46:07 JST 2020 TP0=2500 N:50-200:20 ns=17 ==>(hV,hg)=(247,376) 247
h(yi,yg)@L0c0 with n135 min114.0 max376.0 mean205.4 median223.0 std64.7 best-iNshh(41,110,5,376*,207)
h(yi,yg)@L2c0 with n16 min137.0 max138.0 mean137.6 median138.0 std0.5 best-iNshh(91,130,12,138*,310)(97,170,14,138*,315)(100,110,12,138*,311)(101,190,12,138*,315)(103,50,14,138*,298)(104,130,9,138*,318)(105,190,7,138*,316)(108,110,11,138*,295)(117,150,7,138*,257)(120,150,13,138*,260)
h(yi,yg)@L2c1 with n22 min132.0 max139.0 mean135.2 median135.0 std1.9 best-iNshh(124,150,9,139*,163)(125,130,10,139*,162)(127,190,14,139*,164)
h(yi,yg)@L2c2 with n91 min139.0 max376.0 mean237.7 median247.0 std54.5 best-iNshh(41,110,5,376*,239)
h(yi,yg)@L2c3 with n6 min114.0 max164.0 mean153.5 median160.5 std17.8 best-iNshh(112,50,10,164*,228)(118,70,16,164*,227)
hi-LOOCV@L0c0 with n135 min126.9 max228.1 mean186.3 median189.1 std25.8 best-iNshh(2,170,15,247,228*)
hi-LOOCV@L2c0 with n16 min257.3 max317.7 mean292.7 median291.9 std19.6 best-iNshh(104,130,9,138,318*)
hi-LOOCV@L2c1 with n22 min162.0 max245.0 mean216.1 median226.8 std28.3 best-iNshh(95,110,3,136,245*)
hi-LOOCV@L2c2 with n91 min145.1 max270.9 mean229.4 median236.5 std28.6 best-iNshh(2,170,15,247,271*)
hi-LOOCV@L2c3 with n6 min206.4 max228.2 mean220.2 median222.3 std7.6 best-iNshh(112,50,10,164,228*)

#Fri Jun 12 11:32:28 JST 2020 TP0=2400 N:50-200:20 ns=17 ==>(hV,hg)=(201,475) 234
h(yi,yg)@L0c0 with n133 min56.0 max475.0 mean186.2 median201.0 std85.7 best-iNshh(44,190,2,475*,180)
h(yi,yg)@L2c0 with n44 min117.0 max411.0 mean245.0 median233.0 std45.8 best-iNshh(14,130,3,411*,230)
h(yi,yg)@L2c1 with n63 min66.0 max475.0 mean196.4 median201.0 std71.9 best-iNshh(44,190,2,475*,195)
h(yi,yg)@L2c2 with n22 min56.0 max66.0 mean61.1 median61.0 std2.5 best-iNshh(130,110,15,66*,64)
h(yi,yg)@L2c3 with n4 min66.0 max76.0 mean68.8 median66.5 std4.2 best-iNshh(115,50,14,76*,224)
hi-LOOCV@L0c0 with n133 min61.3 max186.3 mean144.2 median165.8 std42.1 best-iNshh(31,190,12,234,186*)
hi-LOOCV@L2c0 with n44 min114.6 max262.8 mean234.2 median244.5 std29.7 best-iNshh(84,130,7,228,263*)
hi-LOOCV@L2c1 with n63 min61.7 max201.3 mean176.3 median188.7 std27.3 best-iNshh(51,90,9,201,201*)
hi-LOOCV@L2c2 with n22 min64.0 max194.3 mean150.2 median159.1 std29.0 best-iNshh(106,90,5,62,194*)
hi-LOOCV@L2c3 with n4 min77.0 max228.3 mean184.0 median215.3 std62.3 best-iNshh(126,150,16,66,228*)

#Fri Jun 12 11:19:01 JST 2020 TP0=2300 N:50-200:20 ns=17 ==>(hV,hg)=(189,245) 190
h(yi,yg)@L0c0 with n133 min63.0 max245.0 mean123.4 median124.0 std51.9 best-iNshh(31,50,12,245*,128)
h(yi,yg)@L2c0 with n13 min63.0 max69.0 mean68.0 median68.0 std1.5 best-iNshh(107,110,7,69*,196)(110,90,4,69*,233)(123,90,12,69*,236)(129,130,4,69*,136)(130,190,12,69*,138)
h(yi,yg)@L2c1 with n37 min65.0 max68.0 mean66.2 median66.0 std0.7 best-iNshh(106,150,4,68*,163)
h(yi,yg)@L2c2 with n19 min78.0 max245.0 mean141.3 median162.0 std51.3 best-iNshh(31,50,12,245*,165)
h(yi,yg)@L2c3 with n64 min96.0 max193.0 mean162.4 median167.0 std26.1 best-iNshh(12,130,11,193*,195)
hi-LOOCV@L0c0 with n133 min73.6 max145.3 mean111.9 median109.5 std17.7 best-iNshh(0,150,8,190,145*)
hi-LOOCV@L2c0 with n13 min91.6 max236.4 mean176.2 median195.6 std49.0 best-iNshh(123,90,12,69,236*)
hi-LOOCV@L2c1 with n37 min119.8 max203.4 mean179.2 median186.6 std23.2 best-iNshh(65,110,0,67,203*)
hi-LOOCV@L2c2 with n19 min80.6 max206.0 mean171.0 median172.9 std29.8 best-iNshh(116,90,8,79,206*)
hi-LOOCV@L2c3 with n64 min98.3 max210.9 mean168.4 median173.2 std28.7 best-iNshh(22,130,5,189,211*)

#Fri Jun 12 08:46:18 JST 2020 TP0=2200 N:50-200:20 ns=17 ==>(hV,hg)=(166,316) 166L0
h(yi,yg)@L0c0 with n134 min46.0 max316.0 mean172.3 median165.0 std46.8 best-iNshh(47,50,13,316*,173)
h(yi,yg)@L2c0 with n128 min99.0 max316.0 mean177.1 median166.0 std41.9 best-iNshh(47,50,13,316*,178)
h(yi,yg)@L2c1 with n4 min76.0 max89.0 mean79.2 median76.0 std5.6 best-iNshh(128,50,12,89*,112)
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(133,90,2,46*,-1)
hi-LOOCV@L0c0 with n134 min46.4 max187.8 mean161.4 median171.4 std27.4 best-iNshh(2,150,12,166,188*)
hi-LOOCV@L2c0 with n128 min97.6 max193.4 mean170.2 median176.9 std19.9 best-iNshh(2,150,12,166,193*)
hi-LOOCV@L2c1 with n4 min112.3 max171.0 mean147.7 median153.7 std24.8 best-iNshh(129,190,2,76,171*)(130,150,2,76,171*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(133,90,2,46,-1*)

#Fri Jun 12 08:32:57 JST 2020 TP0=2100 N:50-200:20 ns=17 ==>(hV,hg)=(92,321) 93L0
h(yi,yg)@L0c0 with n134 min87.0 max321.0 mean126.1 median95.5 std56.7 best-iNshh(63,170,1,321*,131)
h(yi,yg)@L2c0 with n56 min88.0 max321.0 mean172.9 median175.0 std62.5 best-iNshh(63,170,1,321*,189)
h(yi,yg)@L2c1 with n9 min96.0 max98.0 mean96.4 median96.0 std0.7 best-iNshh(130,50,9,98*,98)
h(yi,yg)@L2c2 with n58 min87.0 max97.0 mean91.4 median91.0 std1.5 best-iNshh(133,170,12,97*,93)
h(yi,yg)@L2c3 with n11 min93.0 max96.0 mean94.6 median95.0 std0.9 best-iNshh(100,150,6,96*,266)(105,130,9,96*,226)
hi-LOOCV@L0c0 with n134 min95.2 max162.2 mean133.4 median131.5 std17.2 best-iNshh(8,190,6,93,162*)
hi-LOOCV@L2c0 with n56 min94.6 max200.2 mean170.2 median174.3 std23.1 best-iNshh(54,190,15,100,200*)
hi-LOOCV@L2c1 with n9 min98.2 max276.8 mean219.2 median242.6 std63.1 best-iNshh(120,110,6,96,277*)(124,130,6,96,277*)
hi-LOOCV@L2c2 with n58 min93.3 max232.4 mean205.5 median217.6 std26.2 best-iNshh(12,170,15,92,232*)
hi-LOOCV@L2c3 with n11 min219.7 max326.6 mean277.8 median280.3 std36.2 best-iNshh(73,130,1,95,327*)

#Fri Jun 12 08:19:50 JST 2020 TP0=2000 N:50-200:20 ns=17 ==>(hV,hg)=(189,391) 187L0
h(yi,yg)@L0c0 with n131 min20.0 max391.0 mean179.5 median186.0 std56.6 best-iNshh(61,150,12,391*,180)(87,150,11,391*,161)
h(yi,yg)@L2c0 with n6 min21.0 max157.0 mean63.7 median29.5 std52.9 best-iNshh(118,70,4,157*,159)
h(yi,yg)@L2c1 with n41 min98.0 max391.0 mean191.9 median172.0 std64.3 best-iNshh(61,150,12,391*,191)(87,150,11,391*,191)
h(yi,yg)@L2c2 with n21 min20.0 max196.0 mean168.8 median186.0 std52.1 best-iNshh(28,150,8,196*,208)(65,170,5,196*,209)(71,190,8,196*,202)(74,130,6,196*,199)(108,70,1,196*,199)
h(yi,yg)@L2c3 with n63 min97.0 max362.0 mean186.0 median189.0 std36.7 best-iNshh(43,110,14,362*,186)
hi-LOOCV@L0c0 with n131 min20.0 max192.0 mean161.6 median175.2 std34.7 best-iNshh(5,150,0,187,192*)
hi-LOOCV@L2c0 with n6 min94.2 max194.2 mean139.1 median137.9 std32.8 best-iNshh(125,90,11,29,194*)
hi-LOOCV@L2c1 with n41 min103.4 max190.9 mean170.4 median175.1 std21.0 best-iNshh(61,150,12,391,191*)
hi-LOOCV@L2c2 with n21 min17.6 max209.8 mean179.1 median199.7 std57.2 best-iNshh(68,150,6,195,210*)
hi-LOOCV@L2c3 with n63 min98.2 max207.6 mean182.6 median192.9 std24.9 best-iNshh(2,110,1,189,208*)

#Thu Jun 11 21:41:36 JST 2020 TP0=2900 N:50-140:30 ns=17 ==>(hV,hg)=(217,308) 213L0
h(yi,yg)@L0c0 with n65 min73.0 max308.0 mean170.2 median189.0 std66.5 best-iNshh(30,140,1,308*,158)
h(yi,yg)@L2c0 with n5 min75.0 max76.0 mean75.8 median76.0 std0.4 best-iNshh(59,140,13,76*,164)(60,80,10,76*,156)(62,50,0,76*,138)(63,80,2,76*,138)
h(yi,yg)@L2c1 with n9 min73.0 max77.0 mean74.0 median74.0 std1.2 best-iNshh(64,140,7,77*,78)
h(yi,yg)@L2c2 with n17 min78.0 max216.0 mean171.9 median212.0 std58.0 best-iNshh(23,80,1,216*,233)
h(yi,yg)@L2c3 with n34 min126.0 max308.0 mean208.7 median211.5 std38.9 best-iNshh(30,140,1,308*,204)
hi-LOOCV@L0c0 with n65 min79.0 max194.3 mean147.1 median158.3 std37.4 best-iNshh(8,140,10,213,194*)
hi-LOOCV@L2c0 with n5 min138.0 max164.2 mean150.8 median156.0 std10.8 best-iNshh(59,140,13,76,164*)
hi-LOOCV@L2c1 with n9 min77.8 max210.1 mean182.7 median196.5 std39.9 best-iNshh(55,50,7,73,210*)
hi-LOOCV@L2c2 with n17 min153.9 max294.0 mean239.5 median247.9 std37.9 best-iNshh(43,80,15,86,294*)
hi-LOOCV@L2c3 with n34 min127.6 max219.5 mean197.9 median207.9 std22.6 best-iNshh(16,140,16,217,219*)

#Thu Jun 11 21:36:10 JST 2020 TP0=2800 N:50-140:30 ns=17 ==>(hV,hg)=(170,349) 170L0
h(yi,yg)@L0c0 with n68 min53.0 max349.0 mean168.2 median168.5 std66.0 best-iNshh(9,50,1,349*,159)
h(yi,yg)@L2c0 with n59 min108.0 max349.0 mean184.5 median170.0 std55.0 best-iNshh(9,50,1,349*,175)
h(yi,yg)@L2c1 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(66,50,12,54*,-1)
h(yi,yg)@L2c2 with n1 min53.0 max53.0 mean53.0 median53.0 std0.0 best-iNshh(67,50,11,53*,-1)
h(yi,yg)@L2c3 with n1 min65.0 max65.0 mean65.0 median65.0 std0.0 best-iNshh(63,80,6,65*,-1)
hi-LOOCV@L0c0 with n68 min53.7 max166.8 mean138.3 median155.0 std32.7 best-iNshh(4,80,9,170,167*)
hi-LOOCV@L2c0 with n59 min109.7 max183.1 mean163.4 median172.3 std19.1 best-iNshh(4,80,9,170,183*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(66,50,12,54,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(67,50,11,53,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(63,80,6,65,-1*)

#Thu Jun 11 21:36:10 JST 2020 TP0=2700 N:50-140:30 ns=17 ==>(hV,hg)=(189,414) 191L0
h(yi,yg)@L0c0 with n87 min21.0 max414.0 mean180.0 median188.0 std64.3 best-iNshh(40,80,10,414*,169)
h(yi,yg)@L2c0 with n32 min98.0 max391.0 mean186.0 median171.5 std65.1 best-iNshh(19,80,12,391*,178)
h(yi,yg)@L2c3 with n14 min21.0 max197.0 mean175.4 median191.5 std44.4 best-iNshh(31,200,5,197*,203)
h(yi,yg)@L2c2 with n36 min97.0 max414.0 mean193.3 median189.5 std54.7 best-iNshh(40,80,10,414*,182)
hi-LOOCV@L0c0 with n87 min20.2 max186.9 mean156.2 median170.9 std34.7 best-iNshh(6,140,0,191,187*)
hi-LOOCV@L2c0 with n32 min107.2 max181.5 mean157.2 median160.5 std22.2 best-iNshh(21,80,13,217,181*)
hi-LOOCV@L2c3 with n14 min17.1 max216.2 mean188.6 median207.0 std51.5 best-iNshh(44,170,8,181,216*)
hi-LOOCV@L2c2 with n36 min97.1 max215.8 mean184.6 median192.2 std26.2 best-iNshh(0,80,8,189,216*)

#Thu Jun 11 21:25:14 JST 2020 TP0=2600 N:50-140:30 ns=17 ==>(hV,hg)=(184,277) 184L0
h(yi,yg)@L0c0 with n68 min94.0 max277.0 mean170.0 median156.5 std40.5 best-iNshh(5,50,10,277*,172)
h(yi,yg)@L2c0 with n40 min116.0 max244.0 mean166.4 median156.5 std21.4 best-iNshh(6,50,4,244*,164)
h(yi,yg)@L2c1 with n1 min94.0 max94.0 mean94.0 median94.0 std0.0 best-iNshh(67,140,2,94*,-1)
h(yi,yg)@L2c2 with n9 min124.0 max126.0 mean125.0 median125.0 std0.8 best-iNshh(55,110,5,126*,205)(57,80,2,126*,205)(60,50,8,126*,214)
h(yi,yg)@L2c3 with n17 min128.0 max277.0 mean211.2 median212.0 std44.9 best-iNshh(5,50,10,277*,217)
hi-LOOCV@L0c0 with n68 min96.5 max183.3 mean158.7 median161.9 std18.6 best-iNshh(12,110,8,184,183*)
hi-LOOCV@L2c0 with n40 min133.4 max205.8 mean181.9 median180.4 std14.4 best-iNshh(12,110,8,184,206*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(67,140,2,94,-1*)
hi-LOOCV@L2c2 with n9 min201.9 max213.5 mean207.9 median208.2 std4.2 best-iNshh(60,50,8,126,214*)
hi-LOOCV@L2c3 with n17 min130.9 max226.4 mean200.9 median210.5 std27.8 best-iNshh(16,140,13,214,226*)

#Thu Jun 11 21:19:46 JST 2020 TP0=2500 N:50-140:30 ns=17 ==>(hV,hg)=(286,376) 249L0
h(yi,yg)@L0c0 with n68 min114.0 max376.0 mean197.6 median194.0 std59.8 best-iNshh(9,110,5,376*,199)
h(yi,yg)@L2c0 with n14 min140.0 max270.0 mean199.1 median198.5 std53.5 best-iNshh(1,50,16,270*,249)
h(yi,yg)@L2c1 with n35 min114.0 max376.0 mean230.5 median225.0 std51.4 best-iNshh(9,110,5,376*,228)
h(yi,yg)@L2c2 with n17 min133.0 max138.0 mean136.3 median136.0 std1.5 best-iNshh(50,50,14,138*,222)(51,110,11,138*,229)(53,140,14,138*,224)(55,110,12,138*,227)(58,80,14,138*,200)
h(yi,yg)@L2c3 with n1 min131.0 max131.0 mean131.0 median131.0 std0.0 best-iNshh(65,140,4,131*,-1)
hi-LOOCV@L0c0 with n68 min129.7 max215.1 mean178.5 median181.5 std20.0 best-iNshh(0,50,1,249,215*)
hi-LOOCV@L2c0 with n14 min211.5 max325.1 mean284.3 median300.9 std35.1 best-iNshh(44,140,15,148,325*)
hi-LOOCV@L2c1 with n35 min138.6 max232.6 mean212.0 median225.1 std24.7 best-iNshh(3,80,8,286,233*)
hi-LOOCV@L2c2 with n17 min184.8 max288.8 mean236.8 median231.2 std30.3 best-iNshh(39,80,7,137,289*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(65,140,4,131,-1*)

#Thu Jun 11 21:14:18 JST 2020 TP0=2400 N:50-140:30 ns=17 ==>(hV,hg)=(231,351) 231L0
h(yi,yg)@L0c0 with n67 min56.0 max351.0 mean168.6 median200.0 std77.5 best-iNshh(16,80,10,351*,165)
h(yi,yg)@L2c0 with n23 min173.0 max351.0 mean230.0 median229.0 std30.8 best-iNshh(16,80,10,351*,226)
h(yi,yg)@L2c1 with n26 min66.0 max288.0 mean188.2 median199.5 std55.1 best-iNshh(29,140,9,288*,195)(30,140,4,288*,195)
h(yi,yg)@L2c2 with n6 min56.0 max76.0 mean60.8 median58.5 std6.9 best-iNshh(57,50,14,76*,59)
h(yi,yg)@L2c3 with n12 min60.0 max66.0 mean62.6 median62.0 std1.8 best-iNshh(64,110,15,66*,66)
hi-LOOCV@L0c0 with n67 min63.9 max184.2 mean131.8 median146.8 std38.4 best-iNshh(5,140,7,231,184*)
hi-LOOCV@L2c0 with n23 min165.7 max271.5 mean228.6 median237.7 std28.4 best-iNshh(5,140,7,231,272*)
hi-LOOCV@L2c1 with n26 min61.8 max202.1 mean173.6 median186.5 std31.7 best-iNshh(17,110,14,202,202*)
hi-LOOCV@L2c2 with n6 min59.0 max181.2 mean139.3 median156.5 std46.5 best-iNshh(55,50,1,59,181*)
hi-LOOCV@L2c3 with n12 min65.9 max189.5 mean152.0 median157.8 std34.7 best-iNshh(49,80,7,64,190*)

#Thu Jun 11 21:08:51 JST 2020 TP0=2300 N:50-140:30 ns=17 ==>(hV,hg)=(191,273) 191L0
h(yi,yg)@L0c0 with n67 min61.0 max273.0 mean124.6 median124.0 std52.9 best-iNshh(16,80,12,273*,124)
h(yi,yg)@L2c0 with n26 min96.0 max273.0 mean175.1 median172.5 std30.3 best-iNshh(16,80,12,273*,175)
h(yi,yg)@L2c1 with n15 min111.0 max192.0 mean137.3 median125.0 std24.1 best-iNshh(35,110,6,192*,115)
h(yi,yg)@L2c2 with n19 min61.0 max68.0 mean66.3 median66.0 std1.6 best-iNshh(8,80,6,68*,195)(32,140,2,68*,195)(38,140,13,68*,187)(39,140,4,68*,187)(63,50,9,68*,107)
h(yi,yg)@L2c3 with n7 min68.0 max70.0 mean68.7 median69.0 std0.7 best-iNshh(66,80,8,70*,77)
hi-LOOCV@L0c0 with n67 min73.6 max131.2 mean108.8 median109.1 std14.0 best-iNshh(6,80,5,191,131*)
hi-LOOCV@L2c0 with n26 min97.4 max202.2 mean173.2 median174.6 std18.7 best-iNshh(6,80,5,191,202*)
hi-LOOCV@L2c1 with n15 min114.7 max156.7 mean135.8 median133.1 std13.4 best-iNshh(37,80,11,125,157*)
hi-LOOCV@L2c2 with n19 min107.0 max195.1 mean165.3 median174.3 std27.5 best-iNshh(8,80,6,68,195*)(32,140,2,68,195*)
hi-LOOCV@L2c3 with n7 min77.3 max227.5 mean183.0 median209.8 std55.4 best-iNshh(34,80,4,69,228*)

#Thu Jun 11 21:03:24 JST 2020 TP0=2200 N:50-140:30 ns=17 ==>(hV,hg)=(371,371) 371L0
h(yi,yg)@L0c0 with n68 min77.0 max371.0 mean179.2 median166.0 std51.2 best-iNshh(13,80,12,371*,180)
h(yi,yg)@L2c0 with n1 min77.0 max77.0 mean77.0 median77.0 std0.0 best-iNshh(67,140,2,77*,-1)
h(yi,yg)@L2c2 with n62 min99.0 max371.0 mean186.0 median166.5 std48.2 best-iNshh(13,80,12,371*,187)
h(yi,yg)@L2c3 with n4 min103.0 max135.0 mean123.0 median127.0 std12.7 best-iNshh(60,50,7,135*,163)
hi-LOOCV@L0c0 with n68 min78.1 max179.7 mean162.6 median173.8 std23.0 best-iNshh(13,80,12,371,180*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(67,140,2,77,-1*)
hi-LOOCV@L2c2 with n62 min97.6 max186.6 mean173.3 median180.9 std17.1 best-iNshh(13,80,12,371,187*)
hi-LOOCV@L2c3 with n4 min109.7 max175.7 mean155.8 median169.0 std27.1 best-iNshh(63,110,2,121,176*)

#Thu Jun 11 20:57:57 JST 2020 TP0=2100 N:50-140:30 ns=17 ==>(hV,hg)=(176,291) 93L0
h(yi,yg)@L0c0 with n65 min88.0 max291.0 mean137.3 median98.0 std61.8 best-iNshh(22,80,12,291*,133)
h(yi,yg)@L2c0 with n4 min92.0 max95.0 mean93.2 median93.0 std1.1 best-iNshh(62,140,3,95*,175)
h(yi,yg)@L2c1 with n22 min88.0 max92.0 mean90.8 median91.0 std1.1 best-iNshh(4,80,6,92*,221)(8,80,13,92*,216)(9,110,7,92*,219)(19,140,7,92*,222)(20,140,2,92*,219)
h(yi,yg)@L2c2 with n35 min97.0 max291.0 mean176.3 median175.0 std61.6 best-iNshh(22,80,12,291*,171)
h(yi,yg)@L2c3 with n4 min96.0 max98.0 mean96.5 median96.0 std0.9 best-iNshh(63,50,9,98*,94)
hi-LOOCV@L0c0 with n65 min100.1 max144.2 mean127.4 median133.4 std13.2 best-iNshh(0,50,4,93,144*)
hi-LOOCV@L2c0 with n4 min175.0 max240.0 mean212.5 median217.5 std25.6 best-iNshh(0,50,4,93,240*)
hi-LOOCV@L2c1 with n22 min149.5 max222.1 mean206.4 median215.4 std21.3 best-iNshh(19,140,7,92,222*)
hi-LOOCV@L2c2 with n35 min104.2 max179.6 mean156.6 median166.9 std21.6 best-iNshh(15,80,7,176,180*)
hi-LOOCV@L2c3 with n4 min94.0 max240.3 mean196.5 median225.8 std59.8 best-iNshh(64,110,6,96,240*)

#Thu Jun 11 20:46:34 JST 2020 TP0=2000 N:50-140:30 ns=17 ==>(hV,hg)=(217,414) 189L0
h(yi,yg)@L0c0 with n65 min20.0 max414.0 mean177.6 median183.0 std69.4 best-iNshh(13,80,10,414*,164)
h(yi,yg)@L2c0 with n36 min97.0 max414.0 mean197.1 median189.0 std63.7 best-iNshh(13,80,10,414*,183)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(64,50,15,20*,-1)
h(yi,yg)@L2c2 with n24 min29.0 max355.0 mean167.1 median157.0 std65.8 best-iNshh(25,140,11,355*,177)
h(yi,yg)@L2c3 with n4 min98.0 max116.0 mean103.5 median100.0 std7.3 best-iNshh(60,110,7,116*,153)
hi-LOOCV@L0c0 with n65 min20.1 max177.5 mean148.0 median158.8 std30.3 best-iNshh(9,110,1,189,178*)
hi-LOOCV@L2c0 with n36 min97.5 max206.9 mean180.6 median191.0 std25.9 best-iNshh(9,110,1,189,207*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(64,50,15,20,-1*)
hi-LOOCV@L2c2 with n24 min143.0 max183.9 mean164.0 median167.1 std12.7 best-iNshh(5,80,13,217,184*)
hi-LOOCV@L2c3 with n4 min153.3 max222.3 mean193.5 median199.2 std27.6 best-iNshh(56,50,5,98,222*)

#Thu Jun 11 20:30:43 JST 2020 TP0=2000 N:50-200:30 ns=15 ==>(hV,hg)=(189,414) 191L0
h(yi,yg)@L0c0 with n87 min21.0 max414.0 mean180.0 median188.0 std64.3 best-iNshh(40,80,10,414*,169)
h(yi,yg)@L2c0 with n14 min21.0 max197.0 mean175.4 median191.5 std44.4 best-iNshh(31,200,5,197*,203)
h(yi,yg)@L2c1 with n36 min97.0 max414.0 mean193.3 median189.5 std54.7 best-iNshh(40,80,10,414*,182)
h(yi,yg)@L2c2 with n32 min98.0 max391.0 mean186.0 median171.5 std65.1 best-iNshh(19,80,12,391*,178)
h(yi,yg)@L2c3 with n5 min21.0 max116.0 mean59.4 median30.0 std40.5 best-iNshh(82,110,7,116*,106)
hi-LOOCV@L0c0 with n87 min20.2 max186.9 mean156.2 median170.9 std34.7 best-iNshh(6,140,0,191,187*)
hi-LOOCV@L2c0 with n14 min17.1 max216.2 mean188.6 median207.0 std51.5 best-iNshh(44,170,8,181,216*)
hi-LOOCV@L2c1 with n36 min97.1 max215.8 mean184.6 median192.2 std26.2 best-iNshh(0,80,8,189,216*)
hi-LOOCV@L2c2 with n32 min107.2 max181.5 mean157.2 median160.5 std22.2 best-iNshh(21,80,13,217,181*)
hi-LOOCV@L2c3 with n5 min77.5 max118.8 mean104.9 median106.5 std14.7 best-iNshh(83,80,11,29,119*)


#Thu Jun 11 18:50:03 JST 2020 TP0=2000 N:50-200:30 ns=20 ==>(hV,hg)=(191,414) 194L0
h(yi,yg)@L0c0 with n116 min20.0 max414.0 mean175.5 median186.0 std62.4 best-iNshh(54,80,10,414*,169)
h(yi,yg)@L2c0 with n8 min21.0 max129.0 mean60.8 median30.0 std42.9 best-iNshh(102,80,16,129*,116)
h(yi,yg)@L2c1 with n33 min71.0 max355.0 mean172.5 median157.0 std56.1 best-iNshh(76,140,11,355*,168)
h(yi,yg)@L2c2 with n20 min20.0 max197.0 mean172.1 median194.0 std51.6 best-iNshh(48,200,5,197*,204)(49,140,17,197*,209)
h(yi,yg)@L2c3 with n55 min97.0 max414.0 mean195.3 median190.0 std52.5 best-iNshh(54,80,10,414*,185)
hi-LOOCV@L0c0 with n116 min20.0 max187.4 mean154.4 median170.1 std38.3 best-iNshh(5,140,2,194,187*)
hi-LOOCV@L2c0 with n8 min78.4 max132.7 mean117.0 median120.4 std15.3 best-iNshh(112,50,19,30,133*)
hi-LOOCV@L2c1 with n33 min72.5 max176.5 mean150.6 median157.7 std24.4 best-iNshh(53,110,9,219,177*)
hi-LOOCV@L2c2 with n20 min17.8 max222.1 mean184.4 median205.6 std58.7 best-iNshh(58,170,17,196,222*)
hi-LOOCV@L2c3 with n55 min97.1 max214.6 mean189.4 median198.4 std24.3 best-iNshh(15,140,0,191,215*)

#Thu Jun 11 17:45:14 JST 2020 TP0=2800 N:50-200:30 ns=17 ==>(hV,hg)=(286,349) 286L0
h(yi,yg)@L0c0 with n102 min50.0 max349.0 mean165.6 median167.0 std62.1 best-iNshh(27,50,1,349*,157)
h(yi,yg)@L2c0 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(99,50,12,54*,-1)
h(yi,yg)@L2c1 with n89 min105.0 max349.0 mean181.0 median169.0 std50.4 best-iNshh(27,50,1,349*,171)
h(yi,yg)@L2c2 with n6 min65.0 max72.0 mean68.3 median68.0 std3.3 best-iNshh(89,170,0,72*,126)(91,140,0,72*,127)
h(yi,yg)@L2c3 with n4 min50.0 max53.0 mean51.5 median51.5 std1.1 best-iNshh(97,50,11,53*,117)
hi-LOOCV@L0c0 with n102 min51.6 max165.7 mean138.5 median155.3 std33.1 best-iNshh(10,200,9,286,166*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(99,50,12,54,-1*)
hi-LOOCV@L2c1 with n89 min94.3 max181.6 mean163.0 median171.5 std18.9 best-iNshh(10,200,9,286,182*)
hi-LOOCV@L2c2 with n6 min125.8 max152.2 mean137.5 median135.1 std10.9 best-iNshh(93,80,12,65,152*)
hi-LOOCV@L2c3 with n4 min116.7 max169.7 mean146.5 median149.8 std23.1 best-iNshh(100,200,10,51,170*)

#Thu Jun 11 17:55:21 JST 2020 TP0=2900 N:50-200:30 ns=17 ==>(hV,hg)=(214,308) 76L0
h(yi,yg)@L0c0 with n98 min72.0 max308.0 mean165.7 median188.0 std65.7 best-iNshh(51,140,1,308*,153)
h(yi,yg)@L2c0 with n7 min75.0 max76.0 mean75.7 median76.0 std0.5 best-iNshh(88,140,13,76*,198)(90,80,10,76*,175)(94,170,7,76*,231)(95,50,0,76*,151)(96,80,2,76*,153)
h(yi,yg)@L2c1 with n14 min72.0 max77.0 mean73.7 median73.0 std1.2 best-iNshh(97,140,7,77*,77)
h(yi,yg)@L2c2 with n48 min122.0 max308.0 mean205.7 median210.5 std37.7 best-iNshh(51,140,1,308*,202)
h(yi,yg)@L2c3 with n29 min78.0 max217.0 mean165.5 median211.0 std59.5 best-iNshh(33,200,5,217*,250)
hi-LOOCV@L0c0 with n98 min79.2 max190.6 mean145.6 median153.6 std35.4 best-iNshh(0,50,10,212,191*)
hi-LOOCV@L2c0 with n7 min151.3 max230.7 mean181.1 median174.8 std26.1 best-iNshh(94,170,7,76,231*)
hi-LOOCV@L2c1 with n14 min77.5 max208.0 mean189.7 median200.2 std32.3 best-iNshh(85,50,7,73,208*)
hi-LOOCV@L2c2 with n48 min124.9 max222.7 mean197.8 median204.3 std24.4 best-iNshh(5,170,5,214,223*)
hi-LOOCV@L2c3 with n29 min155.8 max276.8 mean234.3 median243.0 std35.3 best-iNshh(49,170,6,85,277*)

#Thu Jun 11 17:35:04 JST 2020 TP0=2700 N:50-200:30 ns=17 ==>(hV,hg)=(270,387) 270L0
h(yi,yg)@L0c0 with n101 min86.0 max387.0 mean169.8 median150.0 std53.8 best-iNshh(11,200,12,387*,162)
h(yi,yg)@L2c0 with n84 min98.0 max387.0 mean182.2 median159.0 std50.3 best-iNshh(11,200,12,387*,173)
h(yi,yg)@L2c1 with n9 min115.0 max119.0 mean116.9 median117.0 std1.4 best-iNshh(84,80,14,119*,159)(86,200,9,119*,162)
h(yi,yg)@L2c2 with n4 min86.0 max88.0 mean87.0 median87.0 std0.7 best-iNshh(97,80,6,88*,223)
h(yi,yg)@L2c3 with n4 min107.0 max117.0 mean111.0 median110.0 std3.9 best-iNshh(90,140,16,117*,164)
hi-LOOCV@L0c0 with n101 min89.1 max172.7 mean151.3 median158.1 std18.9 best-iNshh(1,80,8,270,173*)
hi-LOOCV@L2c0 with n84 min134.6 max185.9 mean169.2 median169.9 std7.9 best-iNshh(1,80,8,270,186*)
hi-LOOCV@L2c1 with n9 min158.2 max217.0 mean177.6 median171.0 std19.9 best-iNshh(85,110,15,117,217*)
hi-LOOCV@L2c2 with n4 min173.7 max223.3 mean202.7 median206.8 std21.2 best-iNshh(97,80,6,88,223*)
hi-LOOCV@L2c3 with n4 min139.7 max163.7 mean154.8 median158.0 std9.5 best-iNshh(90,140,16,117,164*)

#Thu Jun 11 17:24:55 JST 2020 TP0=2600 N:50-200:30 ns=17 ==>(hV,hg)=(184,227) 184L0
h(yi,yg)@L0c0 with n102 min93.0 max277.0 mean169.7 median155.0 std40.7 best-iNshh(7,50,10,277*,171)
h(yi,yg)@L2c0 with n85 min129.0 max277.0 mean180.4 median183.0 std35.6 best-iNshh(7,50,10,277*,182)
h(yi,yg)@L2c1 with n13 min106.0 max128.0 mean123.0 median125.0 std5.6 best-iNshh(85,50,15,128*,131)
h(yi,yg)@L2c2 with n1 min94.0 max94.0 mean94.0 median94.0 std0.0 best-iNshh(100,140,8,94*,-1)
h(yi,yg)@L2c3 with n1 min93.0 max93.0 mean93.0 median93.0 std0.0 best-iNshh(101,170,13,93*,-1)
hi-LOOCV@L0c0 with n102 min95.9 max179.1 mean158.5 median163.0 std18.7 best-iNshh(20,110,8,184,179*)
hi-LOOCV@L2c0 with n85 min148.5 max191.6 mean175.8 median174.3 std8.9 best-iNshh(20,110,8,184,192*)
hi-LOOCV@L2c1 with n13 min111.8 max198.8 mean171.6 median181.2 std26.5 best-iNshh(93,50,7,125,199*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(100,140,8,94,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(101,170,13,93,-1*)

#Thu Jun 11 17:13:03 JST 2020 TP0=2300 N:50-200:30 ns=17 ==>(hV,hg)=(186,273) 189L0
h(yi,yg)@L0c0 with n100 min61.0 max273.0 mean120.2 median122.5 std54.0 best-iNshh(36,80,12,273*,120)
h(yi,yg)@L2c0 with n26 min70.0 max273.0 mean162.5 median167.5 std44.1 best-iNshh(36,80,12,273*,163)
h(yi,yg)@L2c1 with n32 min72.0 max192.0 mean156.0 median166.5 std32.5 best-iNshh(8,170,11,192*,195)
h(yi,yg)@L2c2 with n28 min61.0 max68.0 mean66.0 median66.0 std1.3 best-iNshh(93,50,9,68*,107)
h(yi,yg)@L2c3 with n14 min68.0 max69.0 mean68.3 median68.0 std0.5 best-iNshh(50,80,4,69*,261)(57,110,7,69*,259)(74,200,0,69*,256)(90,140,14,69*,220)
hi-LOOCV@L0c0 with n100 min73.4 max137.9 mean111.1 median111.7 std14.7 best-iNshh(0,200,16,189,138*)
hi-LOOCV@L2c0 with n26 min73.0 max191.8 mean154.8 median165.0 std29.6 best-iNshh(10,110,16,179,192*)
hi-LOOCV@L2c1 with n32 min99.0 max208.0 mean166.5 median164.2 std33.0 best-iNshh(5,110,14,186,208*)
hi-LOOCV@L2c2 with n28 min91.4 max189.9 mean164.2 median177.5 std29.3 best-iNshh(40,50,0,65,190*)
hi-LOOCV@L2c3 with n14 min127.2 max268.9 mean246.4 median258.1 std35.0 best-iNshh(7,80,6,68,269*)

#Thu Jun 11 17:02:58 JST 2020 TP0=2200 N:50-200:30 ns=17 ==>(hV,hg)=(269,371) 92L0
h(yi,yg)@L0c0 with n100 min76.0 max371.0 mean177.3 median166.0 std48.0 best-iNshh(32,80,12,371*,178)
hi-LOOCV@L0c0 with n100 min77.9 max182.7 mean164.1 median174.2 std23.2 best-iNshh(12,110,0,166,183*)
hi-LOOCV@L2c0 with n42 min93.3 max230.1 mean203.5 median214.8 std29.0 best-iNshh(5,170,15,92,230*)
hi-LOOCV@L2c1 with n9 min210.4 max315.9 mean246.0 median239.0 std31.6 best-iNshh(77,170,14,95,316*)
hi-LOOCV@L2c2 with n44 min102.1 max192.7 mean161.5 median169.7 std23.5 best-iNshh(29,170,8,269,193*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(96,50,9,98,-1*)

#Thu Jun 11 16:52:52 JST 2020 TP0=2100 N:50-200:30 ns=17 ==>(hV,hg)=(269,321) 92L0
h(yi,yg)@L0c0 with n98 min88.0 max321.0 mean132.3 median96.0 std63.8 best-iNshh(36,170,1,321*,132)
h(yi,yg)@L2c0 with n42 min88.0 max97.0 mean91.4 median91.0 std1.5 best-iNshh(97,170,12,97*,93)
h(yi,yg)@L2c1 with n9 min94.0 max96.0 mean95.1 median95.0 std0.7 best-iNshh(78,200,3,96*,270)(83,170,11,96*,247)(88,110,15,96*,239)
h(yi,yg)@L2c2 with n44 min88.0 max321.0 mean181.5 median175.5 std68.4 best-iNshh(36,170,1,321*,186)
h(yi,yg)@L2c3 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(96,50,9,98*,-1)
hi-LOOCV@L0c0 with n98 min95.5 max158.5 mean130.4 median129.1 std16.4 best-iNshh(5,170,15,92,159*)
hi-LOOCV@L2c0 with n42 min93.3 max230.1 mean203.5 median214.8 std29.0 best-iNshh(5,170,15,92,230*)
hi-LOOCV@L2c1 with n9 min210.4 max315.9 mean246.0 median239.0 std31.6 best-iNshh(77,170,14,95,316*)
hi-LOOCV@L2c2 with n44 min102.1 max192.7 mean161.5 median169.7 std23.5 best-iNshh(29,170,8,269,193*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(96,50,9,98,-1*)

#Thu Jun 11 16:42:45 JST 2020 TP0=2000 N:50-200:30 ns=17 ==>(hV,hg)=(194,414) 194L0
h(yi,yg)@L0c0 with n98 min20.0 max414.0 mean177.9 median185.5 std63.1 best-iNshh(43,80,10,414*,168)
h(yi,yg)@L2c0 with n56 min97.0 max414.0 mean191.4 median189.5 std44.4 best-iNshh(43,80,10,414*,186)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(97,50,15,20*,-1)
h(yi,yg)@L2c2 with n33 min98.0 max391.0 mean184.7 median168.0 std64.5 best-iNshh(17,80,12,391*,177)
h(yi,yg)@L2c3 with n7 min21.0 max157.0 mean83.3 median101.0 std51.5 best-iNshh(76,80,9,157*,114)
hi-LOOCV@L0c0 with n98 min19.9 max187.6 mean154.7 median169.5 std36.4 best-iNshh(1,140,2,194,188*)
hi-LOOCV@L2c0 with n56 min96.3 max216.1 mean193.8 median206.3 std25.4 best-iNshh(22,200,8,194,216*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(97,50,15,20,-1*)
hi-LOOCV@L2c2 with n33 min107.0 max179.9 mean155.9 median161.4 std21.7 best-iNshh(30,80,13,217,180*)
hi-LOOCV@L2c3 with n7 min63.3 max133.7 mean110.6 median114.2 std21.6 best-iNshh(93,110,11,30,134*)

#Thu Jun 11 18:33:34 JST 2020 TP0=2000 N:50-300:30 ns=17 ==>(hV,hg)=(194,414) 194L0 == N:50-200:30
h(yi,yg)@L0c0 with n149 min15.0 max414.0 mean169.0 median185.0 std68.8 best-iNshh(72,80,10,414*,159)
h(yi,yg)@L2c0 with n7 min17.0 max20.0 mean18.9 median19.0 std1.0 best-iNshh(144,50,15,20*,66)(145,230,0,20*,66)
h(yi,yg)@L2c1 with n1 min15.0 max15.0 mean15.0 median15.0 std0.0 best-iNshh(148,260,5,15*,-1)
h(yi,yg)@L2c2 with n51 min29.0 max391.0 mean175.5 median157.0 std70.1 best-iNshh(28,80,12,391*,170)
h(yi,yg)@L2c3 with n88 min21.0 max414.0 mean182.4 median189.0 std48.8 best-iNshh(72,80,10,414*,179)
hi-LOOCV@L0c0 with n149 min18.5 max178.9 mean139.3 median160.3 std44.1 best-iNshh(5,140,2,194,179*)
hi-LOOCV@L2c0 with n7 min62.0 max151.3 mean109.2 median131.0 std38.8 best-iNshh(137,230,12,19,151*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(148,260,5,15,-1*)
hi-LOOCV@L2c2 with n51 min107.9 max180.1 mean152.8 median158.4 std21.0 best-iNshh(83,110,4,222,180*)
hi-LOOCV@L2c3 with n88 min22.3 max210.6 mean181.5 median199.9 std38.5 best-iNshh(18,200,7,194,211*)


#Thu Jun 11 16:30:38 JST 2020 TP0=2500 N:50-200:30 ns=17 ==>(hV,hg)=(286,376) 148L0
h(yi,yg)@L0c0 with n102 min114.0 max376.0 mean201.0 median216.5 std60.5 best-iNshh(24,110,5,376*,202)
h(yi,yg)@L2c0 with n26 min148.0 max270.0 mean218.9 median248.0 std47.3 best-iNshh(9,50,16,270*,262)
h(yi,yg)@L2c1 with n43 min114.0 max376.0 mean239.6 median227.0 std49.7 best-iNshh(24,110,5,376*,238)
h(yi,yg)@L2c2 with n4 min139.0 max140.0 mean139.5 median139.5 std0.5 best-iNshh(80,80,15,140*,267)(84,110,4,140*,242)
h(yi,yg)@L2c3 with n29 min131.0 max139.0 mean136.1 median136.0 std1.8 best-iNshh(98,170,7,139*,143)
hi-LOOCV@L0c0 with n102 min125.6 max226.8 mean185.1 median189.2 std23.8 best-iNshh(0,50,1,249,227*)
hi-LOOCV@L2c0 with n26 min261.9 max336.0 mean311.1 median313.8 std21.3 best-iNshh(41,140,15,148,336*)
hi-LOOCV@L2c1 with n43 min139.9 max240.4 mean222.3 median231.7 std22.4 best-iNshh(14,80,8,286,240*)
hi-LOOCV@L2c2 with n4 min150.3 max270.3 mean232.5 median254.7 std48.7 best-iNshh(94,200,15,139,270*)
hi-LOOCV@L2c3 with n29 min142.9 max266.0 mean222.6 median223.9 std31.4 best-iNshh(62,200,12,136,266*)

#Thu Jun 11 16:20:30 JST 2020 TP0=2400 N:50-200:30 ns=17 ==>(hV,hg)=(288,448) 231L0
h(yi,yg)@L0c0 with n101 min56.0 max448.0 mean185.2 median201.0 std79.6 best-iNshh(33,200,4,448*,181)
h(yi,yg)@L2c0 with n30 min173.0 max351.0 mean229.0 median229.0 std28.6 best-iNshh(13,80,10,351*,226)
h(yi,yg)@L2c1 with n53 min66.0 max448.0 mean202.2 median188.0 std71.2 best-iNshh(33,200,4,448*,201)
h(yi,yg)@L2c2 with n12 min60.0 max66.0 mean62.6 median62.0 std1.8 best-iNshh(97,110,15,66*,66)
h(yi,yg)@L2c3 with n6 min56.0 max76.0 mean60.8 median58.5 std6.9 best-iNshh(87,50,14,76*,59)
hi-LOOCV@L0c0 with n101 min61.1 max189.5 mean146.1 median163.8 std41.4 best-iNshh(8,140,7,231,189*)
hi-LOOCV@L2c0 with n30 min167.7 max262.5 mean228.8 median236.8 std25.9 best-iNshh(8,140,7,231,262*)
hi-LOOCV@L2c1 with n53 min62.0 max206.2 mean178.1 median187.2 std28.2 best-iNshh(23,140,4,288,206*)
hi-LOOCV@L2c2 with n12 min65.9 max189.5 mean152.0 median157.8 std34.7 best-iNshh(84,80,7,64,190*)
hi-LOOCV@L2c3 with n6 min59.0 max181.2 mean139.3 median156.5 std46.5 best-iNshh(91,50,1,59,181*)

#Thu Jun 11 15:47:50 JST 2020 TP0=2300 N:50-150:20 ns=17 ==>(hV,hg)=(189,245) 190L0
h(yi,yg)@L0c0 with n102 min65.0 max245.0 mean125.1 median124.0 std50.1 best-iNshh(6,50,12,245*,134)
h(yi,yg)@L2c0 with n24 min65.0 max68.0 mean66.1 median66.0 std0.8 best-iNshh(83,150,4,68*,162)
h(yi,yg)@L2c1 with n10 min68.0 max69.0 mean68.4 median68.0 std0.5 best-iNshh(78,110,7,69*,215)(85,90,4,69*,243)(95,90,12,69*,246)(101,130,4,69*,132)
h(yi,yg)@L2c2 with n17 min78.0 max245.0 mean142.6 median162.0 std51.2 best-iNshh(6,50,12,245*,163)
h(yi,yg)@L2c3 with n51 min96.0 max193.0 mean158.1 median166.0 std26.2 best-iNshh(10,130,11,193*,184)
hi-LOOCV@L0c0 with n102 min76.1 max140.8 mean111.2 median106.3 std17.6 best-iNshh(0,150,8,190,141*)
hi-LOOCV@L2c0 with n24 min124.9 max197.4 mean177.4 median186.3 std20.0 best-iNshh(57,110,0,67,197*)
hi-LOOCV@L2c1 with n10 min104.8 max245.6 mean201.4 median230.9 std54.1 best-iNshh(95,90,12,69,246*)
hi-LOOCV@L2c2 with n17 min81.2 max201.7 mean167.3 median166.1 std30.1 best-iNshh(80,90,8,79,202*)
hi-LOOCV@L2c3 with n51 min97.8 max195.6 mean159.3 median169.1 std23.8 best-iNshh(26,130,5,189,196*)

#Thu Jun 11 14:46:48 JST 2020 TP0=2200 N:50-150:20 ns=17 ==>(hV,hg)=(166,316) 166L0
h(yi,yg)@L0c0 with n101 min46.0 max316.0 mean174.8 median166.0 std47.9 best-iNshh(26,50,13,316*,175)
h(yi,yg)@L2c0 with n97 min99.0 max316.0 mean179.3 median166.0 std43.1 best-iNshh(26,50,13,316*,179)
h(yi,yg)@L2c1 with n1 min76.0 max76.0 mean76.0 median76.0 std0.0 best-iNshh(98,150,2,76*,-1)
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(100,90,2,46*,-1)
hi-LOOCV@L0c0 with n101 min46.4 max186.4 mean162.4 median172.3 std27.0 best-iNshh(3,150,12,166,186*)
hi-LOOCV@L2c0 with n97 min97.6 max191.4 mean170.7 median177.5 std19.1 best-iNshh(3,150,12,166,191*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(98,150,2,76,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(100,90,2,46,-1*)

#Thu Jun 11 14:34:17 JST 2020 TP0=2100 N:50-150:20 ns=17 ==>(hV,hg)=(233,278) 93L0
h(yi,yg)@L0c0 with n100 min87.0 max278.0 mean130.3 median96.5 std56.4 best-iNshh(68,110,14,278*,118)
h(yi,yg)@L2c0 with n47 min97.0 max278.0 mean172.9 median176.0 std57.7 best-iNshh(68,110,14,278*,147)
h(yi,yg)@L2c1 with n6 min96.0 max98.0 mean96.7 median96.5 std0.7 best-iNshh(97,50,9,98*,104)
h(yi,yg)@L2c2 with n40 min87.0 max94.0 mean91.2 median91.0 std1.5 best-iNshh(7,130,14,94*,220)(18,150,8,94*,226)
h(yi,yg)@L2c3 with n7 min95.0 max96.0 mean95.6 median96.0 std0.5 best-iNshh(78,70,11,96*,265)(79,130,9,96*,337)(80,110,15,96*,284)(81,150,6,96*,317)
hi-LOOCV@L0c0 with n100 min98.2 max152.8 mean130.3 median132.9 std13.1 best-iNshh(0,50,4,93,153*)
hi-LOOCV@L2c0 with n47 min94.6 max197.1 mean169.2 median174.6 std22.6 best-iNshh(33,70,13,233,197*)
hi-LOOCV@L2c1 with n6 min104.4 max250.4 mean188.9 median206.6 std58.8 best-iNshh(83,110,6,96,250*)(90,130,6,96,250*)
hi-LOOCV@L2c2 with n40 min138.8 max231.4 mean210.1 median220.7 std22.4 best-iNshh(0,50,4,93,231*)
hi-LOOCV@L2c3 with n7 min265.3 max337.0 mean306.0 median316.8 std30.3 best-iNshh(79,130,9,96,337*)

#Thu Jun 11 14:20:11 JST 2020 TP0=2000 N:50-150:20 ns=17 ==>(hV,hg)=(110,391) 187L0
h(yi,yg)@L0c0 with n97 min20.0 max391.0 mean178.1 median186.0 std58.1 best-iNshh(38,150,12,391*,181)(55,150,11,391*,168)
h(yi,yg)@L2c0 with n55 min97.0 max362.0 mean184.9 median189.0 std36.9 best-iNshh(23,110,14,362*,185)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(96,50,15,20*,-1)
h(yi,yg)@L2c2 with n38 min29.0 max391.0 mean178.2 median157.0 std74.0 best-iNshh(38,150,12,391*,188)(55,150,11,391*,189)
h(yi,yg)@L2c3 with n1 min116.0 max116.0 mean116.0 median116.0 std0.0 best-iNshh(91,110,7,116*,-1)
hi-LOOCV@L0c0 with n97 min20.2 max187.6 mean159.2 median169.7 std30.9 best-iNshh(1,90,1,187,188*)
hi-LOOCV@L2c0 with n55 min98.7 max210.8 mean183.7 median196.1 std27.1 best-iNshh(10,110,3,186,211*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(96,50,15,20,-1*)
hi-LOOCV@L2c2 with n38 min134.1 max188.5 mean172.9 median178.8 std14.8 best-iNshh(55,150,11,391,189*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(91,110,7,116,-1*)

#Thu Jun 11 14:04:21 JST 2020 TP0=2900 N:50-100:5 ns=10 ==>(hV,hg)=(211,492) 192L0
h(yi,yg)@L0c0 with n107 min72.0 max492.0 mean180.5 median192.0 std76.2 best-iNshh(36,90,8,492*,177)
h(yi,yg)@L2c0 with n17 min72.0 max76.0 mean73.6 median73.0 std1.2 best-iNshh(104,65,7,76*,105)(106,60,2,76*,87)
h(yi,yg)@L2c1 with n4 min77.0 max77.0 mean77.0 median77.0 std0.0 best-iNshh(93,75,7,77*,259)(99,100,2,77*,262)(100,85,9,77*,267)(102,55,3,77*,274)
h(yi,yg)@L2c2 with n35 min78.0 max314.0 mean201.6 median214.0 std46.1 best-iNshh(69,90,4,314*,212)
h(yi,yg)@L2c3 with n51 min76.0 max492.0 mean209.7 median201.0 std70.0 best-iNshh(36,90,8,492*,202)
hi-LOOCV@L0c0 with n107 min81.9 max192.0 mean147.5 median157.5 std36.6 best-iNshh(0,55,6,213,192*)
hi-LOOCV@L2c0 with n17 min86.6 max245.5 mean192.1 median196.5 std41.4 best-iNshh(83,65,0,75,246*)
hi-LOOCV@L2c1 with n4 min259.3 max273.7 mean265.5 median264.5 std5.4 best-iNshh(102,55,3,77,274*)
hi-LOOCV@L2c2 with n35 min113.1 max256.7 mean220.1 median236.1 std37.1 best-iNshh(47,70,1,215,257*)
hi-LOOCV@L2c3 with n51 min78.9 max206.0 mean181.6 median193.0 std30.8 best-iNshh(40,70,0,211,206*)

#Thu Jun 11 13:56:01 JST 2020 TP0=2800 N:50-100:5 ns=10 ==>(hV,hg)=(259,446) 259L0
h(yi,yg)@L0c0 with n109 min55.0 max446.0 mean167.9 median166.0 std69.3 best-iNshh(12,55,8,446*,160)
h(yi,yg)@L2c0 with n8 min63.0 max169.0 mean77.2 median64.0 std34.7 best-iNshh(83,75,9,169*,245)
h(yi,yg)@L2c1 with n12 min63.0 max231.0 mean165.8 median167.0 std35.5 best-iNshh(3,50,8,231*,169)
h(yi,yg)@L2c2 with n22 min55.0 max136.0 mean109.4 median107.0 std21.0 best-iNshh(72,65,2,136*,131)(77,100,3,136*,142)(78,55,4,136*,143)(79,95,3,136*,126)
h(yi,yg)@L2c3 with n67 min136.0 max446.0 mean198.4 median173.0 std65.2 best-iNshh(12,55,8,446*,180)
hi-LOOCV@L0c0 with n109 min55.0 max166.7 mean136.6 median149.6 std25.7 best-iNshh(0,75,8,259,167*)
hi-LOOCV@L2c0 with n8 min223.1 max254.7 mean244.2 median245.9 std8.5 best-iNshh(102,85,6,64,255*)
hi-LOOCV@L2c1 with n12 min169.1 max243.3 mean219.4 median224.7 std20.3 best-iNshh(29,70,9,175,243*)
hi-LOOCV@L2c2 with n22 min57.4 max149.2 mean130.1 median138.6 std24.4 best-iNshh(85,80,3,108,149*)
hi-LOOCV@L2c3 with n67 min146.3 max195.7 mean173.8 median175.7 std13.4 best-iNshh(0,75,8,259,196*)

#Thu Jun 11 13:47:34 JST 2020 TP0=2700 N:50-100:5 ns=10 ==>(hV,hg)=(270,416) 270L0
h(yi,yg)@L0c0 with n106 min83.0 max416.0 mean171.1 median150.0 std59.6 best-iNshh(10,55,9,416*,164)
h(yi,yg)@L2c0 with n89 min89.0 max416.0 mean184.8 median155.0 std54.8 best-iNshh(10,55,9,416*,177)
h(yi,yg)@L2c1 with n7 min115.0 max118.0 mean116.6 median117.0 std0.9 best-iNshh(88,80,4,118*,246)
h(yi,yg)@L2c2 with n9 min86.0 max88.0 mean87.1 median87.0 std0.7 best-iNshh(96,85,6,88*,237)(98,80,6,88*,221)(100,65,9,88*,200)
h(yi,yg)@L2c3 with n1 min83.0 max83.0 mean83.0 median83.0 std0.0 best-iNshh(105,55,5,83*,-1)
hi-LOOCV@L0c0 with n106 min86.2 max172.4 mean149.6 median157.6 std21.4 best-iNshh(2,80,8,270,172*)
hi-LOOCV@L2c0 with n89 min89.9 max186.5 mean169.2 median169.6 std11.1 best-iNshh(2,80,8,270,187*)
hi-LOOCV@L2c1 with n7 min191.2 max258.2 mean239.9 median250.0 std21.7 best-iNshh(93,70,1,116,258*)
hi-LOOCV@L2c2 with n9 min167.2 max253.2 mean211.5 median212.6 std27.6 best-iNshh(95,100,4,87,253*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(105,55,5,83,-1*)

#Thu Jun 11 13:39:05 JST 2020 TP0=2600 N:50-100:5 ns=10 ==>(hV,hg)=(153,308) 153L0
h(yi,yg)@L0c0 with n110 min39.0 max308.0 mean165.5 median151.0 std38.6 best-iNshh(73,100,5,308*,164)
h(yi,yg)@L2c0 with n16 min116.0 max128.0 mean125.3 median125.5 std2.8 best-iNshh(93,75,5,128*,208)(94,90,4,128*,159)(95,70,5,128*,161)
h(yi,yg)@L2c1 with n93 min129.0 max308.0 mean173.8 median153.0 std35.2 best-iNshh(73,100,5,308*,172)
h(yi,yg)@L2c2 with n1 min39.0 max39.0 mean39.0 median39.0 std0.0 best-iNshh(109,65,7,39*,-1)
hi-LOOCV@L0c0 with n110 min39.5 max179.9 mean162.0 median167.1 std18.2 best-iNshh(0,75,7,153,180*)
hi-LOOCV@L2c0 with n16 min111.4 max208.3 mean183.1 median191.1 std23.0 best-iNshh(93,75,5,128,208*)
hi-LOOCV@L2c1 with n93 min149.2 max190.8 mean177.0 median176.7 std8.1 best-iNshh(0,75,7,153,191*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(109,65,7,39,-1*)

#Thu Jun 11 13:28:14 JST 2020 TP0=2500 N:50-100:5 ns=10 ==>(hV,hg)=(284,346) 286L0
h(yi,yg)@L0c0 with n108 min114.0 max346.0 mean203.4 median223.5 std60.8 best-iNshh(23,70,2,346*,203)
h(yi,yg)@L2c0 with n67 min148.0 max346.0 mean242.4 median247.0 std43.1 best-iNshh(23,70,2,346*,241)
h(yi,yg)@L2c1 with n12 min114.0 max162.0 mean150.7 median159.0 std17.2 best-iNshh(76,90,9,162*,229)(94,65,9,162*,189)
h(yi,yg)@L2c2 with n22 min132.0 max136.0 mean134.1 median134.0 std1.3 best-iNshh(78,80,1,136*,245)(79,80,5,136*,244)(85,70,7,136*,225)
h(yi,yg)@L2c3 with n7 min136.0 max139.0 mean137.4 median137.0 std0.9 best-iNshh(106,95,3,139*,147)
hi-LOOCV@L0c0 with n108 min125.1 max213.7 mean181.4 median189.8 std23.3 best-iNshh(0,80,8,286,214*)
hi-LOOCV@L2c0 with n67 min175.9 max259.1 mean232.3 median239.0 std21.5 best-iNshh(5,90,6,284,259*)
hi-LOOCV@L2c1 with n12 min176.0 max249.3 mean219.2 median222.6 std21.0 best-iNshh(75,65,4,158,249*)
hi-LOOCV@L2c2 with n22 min200.3 max246.8 mean227.1 median233.2 std16.3 best-iNshh(74,75,7,135,247*)
hi-LOOCV@L2c3 with n7 min147.2 max302.5 mean256.4 median275.7 std49.9 best-iNshh(66,100,3,137,302*)

#Thu Jun 11 13:19:58 JST 2020 TP0=2400 N:50-100:5 ns=10 ==>(hV,hg)=(201,345) 290L0
h(yi,yg)@L0c0 with n106 min56.0 max345.0 mean169.7 median190.0 std75.1 best-iNshh(9,95,0,345*,165)
h(yi,yg)@L2c0 with n24 min56.0 max64.0 mean60.8 median61.0 std2.5 best-iNshh(86,65,6,64*,156)(90,80,7,64*,156)(95,85,7,64*,128)(97,90,6,64*,127)
h(yi,yg)@L2c1 with n4 min66.0 max76.0 mean71.2 median71.5 std4.8 best-iNshh(98,75,7,76*,193)(99,95,6,76*,222)
h(yi,yg)@L2c2 with n27 min75.0 max326.0 mean225.7 median230.0 std42.5 best-iNshh(8,75,6,326*,225)
h(yi,yg)@L2c3 with n51 min120.0 max345.0 mean199.1 median201.0 std43.7 best-iNshh(9,95,0,345*,193)
hi-LOOCV@L0c0 with n106 min63.0 max170.7 mean128.5 median138.5 std33.3 best-iNshh(3,90,0,290,171*)
hi-LOOCV@L2c0 with n24 min89.0 max211.0 mean158.7 median164.0 std31.2 best-iNshh(78,90,5,62,211*)
hi-LOOCV@L2c1 with n4 min75.7 max222.0 mean178.2 median207.5 std60.3 best-iNshh(99,95,6,76,222*)
hi-LOOCV@L2c2 with n27 min142.3 max256.1 mean228.9 median233.5 std27.2 best-iNshh(68,85,1,236,256*)
hi-LOOCV@L2c3 with n51 min121.1 max205.0 mean186.4 median190.9 std18.0 best-iNshh(34,90,9,201,205*)

#Thu Jun 11 13:10:15 JST 2020 TP0=2300 N:50-100:5 ns=10 ==>(hV,hg)=(188,395) 168L0
h(yi,yg)@L0c0 with n108 min65.0 max395.0 mean133.5 median126.5 std55.7 best-iNshh(26,85,9,395*,134)
h(yi,yg)@L2c0 with n14 min65.0 max68.0 mean66.4 median66.0 std0.9 best-iNshh(76,80,6,68*,214)(105,50,9,68*,108)
h(yi,yg)@L2c1 with n10 min68.0 max69.0 mean68.6 median69.0 std0.5 best-iNshh(82,80,4,69*,261)(87,85,4,69*,239)(90,90,4,69*,250)(96,65,4,69*,231)(99,100,9,69*,200)(104,55,7,69*,147)
h(yi,yg)@L2c2 with n66 min70.0 max395.0 mean161.8 median166.0 std45.8 best-iNshh(26,85,9,395*,155)
h(yi,yg)@L2c3 with n18 min78.0 max190.0 mean118.2 median86.5 std43.6 best-iNshh(59,50,4,190*,196)
hi-LOOCV@L0c0 with n108 min71.8 max148.5 mean114.8 median115.2 std21.2 best-iNshh(0,90,6,168,148*)
hi-LOOCV@L2c0 with n14 min108.3 max213.7 mean189.5 median196.9 std27.2 best-iNshh(76,80,6,68,214*)
hi-LOOCV@L2c1 with n10 min135.4 max261.9 mean219.6 median234.8 std42.7 best-iNshh(72,75,4,68,262*)
hi-LOOCV@L2c2 with n66 min68.8 max178.0 mean154.4 median165.3 std22.4 best-iNshh(4,65,1,188,178*)
hi-LOOCV@L2c3 with n18 min84.0 max200.1 mean168.5 median170.4 std30.2 best-iNshh(81,70,6,79,200*)

#Thu Jun 11 12:52:07 JST 2020 TP0=2200 N:50-100:5 ns=10 ==>(hV,hg)=(166,289) 166L0
h(yi,yg)@L0c0 with n107 min46.0 max289.0 mean171.5 median165.0 std38.1 best-iNshh(66,90,5,289*,169)
h(yi,yg)@L2c0 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(106,90,2,46*,-1)
h(yi,yg)@L2c2 with n50 min103.0 max260.0 mean165.2 median145.5 std39.1 best-iNshh(51,95,7,260*,167)
h(yi,yg)@L2c3 with n56 min158.0 max289.0 mean179.3 median166.0 std32.0 best-iNshh(66,90,5,289*,177)
hi-LOOCV@L0c0 with n107 min46.0 max184.9 mean165.7 median172.6 std20.2 best-iNshh(0,90,4,166,185*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(106,90,2,46,-1*)
hi-LOOCV@L2c2 with n50 min106.0 max187.9 mean166.2 median168.2 std19.4 best-iNshh(45,60,2,193,188*)
hi-LOOCV@L2c3 with n56 min173.5 max221.2 mean198.0 median198.6 std16.0 best-iNshh(0,90,4,166,221*)

#Thu Jun 11 12:40:28 JST 2020 TP0=2100 N:50-100:5 ns=10 ==>(hV,hg)=(99,353) 205L0
h(yi,yg)@L0c0 with n105 min90.0 max353.0 mean127.0 median99.0 std56.7 best-iNshh(1,95,5,353*,148)
h(yi,yg)@L2c0 with n39 min90.0 max95.0 mean91.6 median92.0 std1.0 best-iNshh(100,55,4,95*,123)
h(yi,yg)@L2c1 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(104,100,9,98*,-1)
h(yi,yg)@L2c2 with n44 min98.0 max321.0 mean128.7 median99.0 std53.1 best-iNshh(6,55,0,321*,187)
h(yi,yg)@L2c3 with n21 min98.0 max353.0 mean190.5 median177.0 std61.2 best-iNshh(1,95,5,353*,173)
hi-LOOCV@L0c0 with n105 min97.7 max150.2 mean134.0 median137.1 std11.8 best-iNshh(3,70,3,205,150*)
hi-LOOCV@L2c0 with n39 min123.1 max228.2 mean209.8 median219.6 std25.3 best-iNshh(31,85,6,93,228*)(35,100,0,92,228*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(104,100,9,98,-1*)
hi-LOOCV@L2c2 with n44 min121.5 max192.7 mean173.1 median174.7 std16.2 best-iNshh(7,95,1,99,193*)
hi-LOOCV@L2c3 with n21 min111.2 max202.4 mean167.4 median174.6 std26.3 best-iNshh(9,50,7,205,202*)

#Thu Jun 11 12:20:18 JST 2020 TP0=2000 N:50-100:5 ns=10 ==>(hV,hg)=(157,359) 187L0
h(yi,yg)@L0c0 with n102 min98.0 max359.0 mean175.2 median170.5 std42.3 best-iNshh(21,85,0,359*,172)
h(yi,yg)@L2c0 with n26 min156.0 max359.0 mean200.1 median188.0 std46.7 best-iNshh(21,85,0,359*,199)
h(yi,yg)@L2c1 with n13 min152.0 max196.0 mean182.4 median184.0 std14.3 best-iNshh(15,95,8,196*,220)(96,70,1,196*,206)
h(yi,yg)@L2c2 with n4 min98.0 max124.0 mean105.5 median100.0 std10.7 best-iNshh(92,55,6,124*,94)
h(yi,yg)@L2c3 with n59 min126.0 max305.0 mean167.3 median157.0 std37.4 best-iNshh(41,55,3,305*,166)
hi-LOOCV@L0c0 with n102 min69.9 max187.9 mean151.3 median157.0 std25.1 best-iNshh(2,90,1,187,188*)
hi-LOOCV@L2c0 with n26 min162.2 max237.8 mean212.8 median225.5 std24.4 best-iNshh(0,55,0,190,238*)
hi-LOOCV@L2c1 with n13 min160.2 max232.8 mean210.2 median217.5 std22.9 best-iNshh(93,65,1,191,233*)
hi-LOOCV@L2c2 with n4 min25.0 max158.7 mean109.2 median126.5 std55.2 best-iNshh(97,80,4,101,159*)(98,50,5,98,159*)
hi-LOOCV@L2c3 with n59 min140.4 max187.7 mean168.0 median170.4 std13.8 best-iNshh(60,60,6,157,188*)

#Thu Jun 11 10:31:37 JST 2020 TP0=2000 N:50-100:5 ns=9 ==>(hV,hg)=(157,359) 187L0
h(yi,yg)@L0c0 with n91 min98.0 max359.0 mean176.3 median180.0 std42.0 best-iNshh(21,85,0,359*,173)
h(yi,yg)@L2c0 with n53 min126.0 max305.0 mean168.0 median157.0 std34.6 best-iNshh(41,55,3,305*,167)
h(yi,yg)@L2c1 with n4 min98.0 max124.0 mean105.5 median100.0 std10.7 best-iNshh(84,55,6,124*,94)
h(yi,yg)@L2c2 with n23 min181.0 max359.0 mean205.5 median188.0 std46.9 best-iNshh(21,85,0,359*,198)
h(yi,yg)@L2c3 with n11 min152.0 max196.0 mean181.1 median184.0 std15.0 best-iNshh(85,70,1,196*,203)
hi-LOOCV@L0c0 with n91 min74.5 max191.8 mean152.7 median156.8 std25.4 best-iNshh(1,90,1,187,192*)
hi-LOOCV@L2c0 with n53 min136.4 max192.7 mean169.1 median171.6 std14.3 best-iNshh(38,80,6,157,193*)
hi-LOOCV@L2c1 with n4 min25.0 max158.7 mean109.2 median126.5 std55.2 best-iNshh(86,80,4,101,159*)(87,50,5,98,159*)
hi-LOOCV@L2c2 with n23 min191.3 max249.9 mean225.8 median236.9 std20.7 best-iNshh(10,100,3,188,250*)
hi-LOOCV@L2c3 with n11 min162.5 max231.5 mean207.4 median209.9 std23.2 best-iNshh(81,65,1,191,232*)

#Thu Jun 11 10:09:40 JST 2020 TP0=2100 N:50,60,70,80,90,100 ns=20 ==>(hV,hg)=(100,357) 258L0
h(yi,yg)@L0c0 with n115 min89.0 max357.0 mean137.8 median99.0 std61.1 best-iNshh(2,100,16,357*,146)
h(yi,yg)@L2c0 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(113,100,18,98*,-1)
h(yi,yg)@L2c1 with n44 min89.0 max96.0 mean91.5 median92.0 std1.4 best-iNshh(112,70,11,96*,98)
h(yi,yg)@L2c2 with n17 min98.0 max270.0 mean192.9 median206.0 std59.4 best-iNshh(62,60,8,270*,189)
h(yi,yg)@L2c3 with n52 min96.0 max357.0 mean160.4 median160.5 std61.1 best-iNshh(2,100,16,357*,184)
hi-LOOCV@L0c0 with n115 min96.0 max146.7 mean130.7 median134.4 std12.1 best-iNshh(1,60,12,258,147*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(113,100,18,98,-1*)
hi-LOOCV@L2c1 with n44 min98.1 max232.8 mean205.4 median220.4 std29.1 best-iNshh(18,60,0,92,233*)
hi-LOOCV@L2c2 with n17 min109.6 max227.2 mean189.7 median191.4 std31.8 best-iNshh(67,60,15,234,227*)
hi-LOOCV@L2c3 with n52 min91.2 max193.6 mean174.0 median181.5 std18.9 best-iNshh(16,60,1,100,194*)

#Thu Jun 11 09:13:42 JST 2020 TP0=2000 N:50,60,70,80,90,100 ns=20 ==>(hV,hg)=(169,414) 172L0
h(yi,yg)@L0c0 with n114 min20.0 max414.0 mean158.9 median157.0 std61.4 best-iNshh(68,80,10,414*,153)
h(yi,yg)@L2c0 with n89 min98.0 max414.0 mean175.0 median157.0 std48.3 best-iNshh(68,80,10,414*,168)
h(yi,yg)@L2c1 with n9 min20.0 max196.0 mean154.1 median180.0 std55.1 best-iNshh(105,70,1,196*,162)
h(yi,yg)@L2c2 with n10 min29.0 max158.0 mean89.2 median79.5 std60.5 best-iNshh(75,60,4,158*,190)
h(yi,yg)@L2c3 with n6 min30.0 max101.0 mean42.0 median30.0 std26.4 best-iNshh(101,80,4,101*,136)
hi-LOOCV@L0c0 with n114 min21.1 max166.9 mean141.3 median155.9 std30.7 best-iNshh(10,100,13,172,167*)
hi-LOOCV@L2c0 with n89 min101.7 max180.5 mean167.0 median173.4 std16.7 best-iNshh(17,100,9,169,181*)
hi-LOOCV@L2c1 with n9 min16.0 max180.1 mean142.3 median168.0 std52.4 best-iNshh(100,80,2,180,180*)
hi-LOOCV@L2c2 with n10 min144.9 max195.2 mean180.1 median189.5 std18.5 best-iNshh(96,60,11,30,195*)
hi-LOOCV@L2c3 with n6 min124.6 max160.0 mean139.8 median140.0 std12.2 best-iNshh(109,50,19,30,160*)

#Thu Jun 11 09:01:23 JST 2020 TP0=2900 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(215,492) 215L0
h(yi,yg)@L0c0 with n99 min72.0 max492.0 mean170.4 median188.0 std76.8 best-iNshh(25,90,8,492*,167)
h(yi,yg)@L2c0 with n7 min76.0 max76.0 mean76.0 median76.0 std0.0 best-iNshh(85,80,10,76*,171)(87,70,14,76*,234)(88,100,10,76*,194)(91,60,2,76*,266)(92,90,13,76*,258)(97,50,0,76*,206)(98,80,2,76*,178)
h(yi,yg)@L2c1 with n16 min72.0 max75.0 mean73.6 median74.0 std0.7 best-iNshh(76,100,7,75*,186)
h(yi,yg)@L2c2 with n58 min126.0 max492.0 mean210.4 median205.5 std56.3 best-iNshh(25,90,8,492*,205)
h(yi,yg)@L2c3 with n18 min77.0 max314.0 mean164.2 median211.5 std72.1 best-iNshh(59,90,4,314*,199)
hi-LOOCV@L0c0 with n99 min83.8 max179.1 mean139.2 median153.2 std31.8 best-iNshh(0,90,1,215,179*)
hi-LOOCV@L2c0 with n7 min170.8 max265.7 mean215.1 median205.7 std35.0 best-iNshh(91,60,2,76,266*)
hi-LOOCV@L2c1 with n16 min178.6 max234.1 mean213.3 median219.5 std17.5 best-iNshh(72,90,16,74,234*)
hi-LOOCV@L2c2 with n58 min124.8 max218.8 mean197.5 median205.2 std22.1 best-iNshh(0,90,1,215,219*)
hi-LOOCV@L2c3 with n18 min126.6 max269.9 mean206.4 median212.8 std35.5 best-iNshh(66,80,15,86,270*)

#Thu Jun 11 08:50:18 JST 2020 TP0=2800 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(257,374) 257L0
h(yi,yg)@L0c0 with n102 min52.0 max374.0 mean164.4 median167.0 std66.9 best-iNshh(20,60,1,374*,155)
h(yi,yg)@L2c0 with n76 min108.0 max374.0 mean190.2 median170.0 std54.2 best-iNshh(20,60,1,374*,182)
h(yi,yg)@L2c1 with n14 min54.0 max136.0 mean97.1 median106.0 std28.6 best-iNshh(76,100,3,136*,124)
h(yi,yg)@L2c2 with n9 min63.0 max175.0 mean88.7 median65.0 std45.9 best-iNshh(74,80,11,175*,160)
h(yi,yg)@L2c3 with n1 min53.0 max53.0 mean53.0 median53.0 std0.0 best-iNshh(101,50,11,53*,-1)
hi-LOOCV@L0c0 with n102 min54.3 max165.2 mean134.5 median150.0 std31.0 best-iNshh(0,50,16,257,165*)
hi-LOOCV@L2c0 with n76 min108.5 max189.5 mean172.0 median176.5 std14.3 best-iNshh(0,50,16,257,189*)
hi-LOOCV@L2c1 with n14 min71.4 max135.9 mean109.7 median115.5 std19.2 best-iNshh(84,80,3,108,136*)
hi-LOOCV@L2c2 with n9 min159.8 max261.0 mean223.8 median229.9 std27.1 best-iNshh(80,100,9,63,261*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(101,50,11,53,-1*)

#Thu Jun 11 08:30:18 JST 2020 TP0=2700 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(270,273) 270L0
h(yi,yg)@L0c0 with n100 min86.0 max273.0 mean167.3 median150.5 std46.0 best-iNshh(40,80,3,273*,164)
h(yi,yg)@L2c0 with n87 min98.0 max273.0 mean176.4 median164.0 std42.0 best-iNshh(40,80,3,273*,173)
h(yi,yg)@L2c1 with n9 min89.0 max131.0 mean115.2 median117.0 std10.5 best-iNshh(85,80,1,131*,121)
h(yi,yg)@L2c2 with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(98,50,7,87*,-1)
h(yi,yg)@L2c3 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(99,50,5,86*,-1)
hi-LOOCV@L0c0 with n100 min89.2 max171.8 mean154.7 median161.3 std19.5 best-iNshh(7,80,8,270,172*)
hi-LOOCV@L2c0 with n87 min117.4 max181.7 mean169.5 median170.6 std8.8 best-iNshh(7,80,8,270,182*)
hi-LOOCV@L2c1 with n9 min108.8 max202.1 mean162.9 median194.8 std39.8 best-iNshh(87,80,4,118,202*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(98,50,7,87,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(99,50,5,86,-1*)

#Thu Jun 11 08:19:22 JST 2020 TP0=2600 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(185,308) 185L0
h(yi,yg)@L0c0 with n102 min116.0 max308.0 mean166.0 median152.0 std38.2 best-iNshh(55,100,5,308*,163)
h(yi,yg)@L2c0 with n16 min124.0 max127.0 mean125.4 median125.0 std1.1 best-iNshh(84,60,8,127*,225)(88,60,6,127*,218)(91,60,4,127*,221)
h(yi,yg)@L2c1 with n7 min116.0 max128.0 mean126.0 median128.0 std4.1 best-iNshh(80,90,4,128*,260)(83,60,10,128*,257)(85,50,15,128*,181)(89,70,5,128*,247)
h(yi,yg)@L2c2 with n37 min144.0 max251.0 mean153.2 median151.0 std16.6 best-iNshh(11,100,10,251*,184)
h(yi,yg)@L2c3 with n42 min129.0 max308.0 mean199.5 median185.0 std33.9 best-iNshh(55,100,5,308*,195)
hi-LOOCV@L0c0 with n102 min116.0 max177.9 mean158.9 median163.5 std13.0 best-iNshh(4,90,8,185,178*)
hi-LOOCV@L2c0 with n16 min201.6 max225.9 mean213.5 median215.8 std7.9 best-iNshh(79,100,13,126,226*)
hi-LOOCV@L2c1 with n7 min115.2 max259.8 mean203.2 median232.8 std56.6 best-iNshh(80,90,4,128,260*)
hi-LOOCV@L2c2 with n37 min183.6 max217.9 mean201.1 median202.9 std9.1 best-iNshh(17,60,1,148,218*)
hi-LOOCV@L2c3 with n42 min140.8 max229.2 mean201.9 median203.9 std18.8 best-iNshh(4,90,8,185,229*)

#Thu Jun 11 08:11:15 JST 2020 TP0=2500 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(159,346) 284L0
h(yi,yg)@L0c0 with n100 min114.0 max346.0 mean201.8 median216.5 std62.2 best-iNshh(13,70,2,346*,202)
h(yi,yg)@L2c0 with n60 min140.0 max346.0 mean244.2 median247.5 std43.4 best-iNshh(13,70,2,346*,244)
h(yi,yg)@L2c1 with n8 min114.0 max164.0 mean149.5 median159.5 std20.3 best-iNshh(79,50,10,164*,218)(81,70,16,164*,217)
h(yi,yg)@L2c2 with n8 min137.0 max138.0 mean137.5 median137.5 std0.5 best-iNshh(85,50,14,138*,300)(88,60,13,138*,285)(91,80,14,138*,254)(96,100,10,138*,207)
h(yi,yg)@L2c3 with n24 min131.0 max139.0 mean134.7 median135.0 std1.7 best-iNshh(97,100,11,139*,138)
hi-LOOCV@L0c0 with n100 min123.0 max208.5 mean179.3 median181.3 std21.3 best-iNshh(8,90,8,284,209*)
hi-LOOCV@L2c0 with n60 min153.1 max255.6 mean230.0 median239.4 std23.2 best-iNshh(8,90,8,284,256*)
hi-LOOCV@L2c1 with n8 min200.9 max227.3 mean214.7 median213.8 std8.8 best-iNshh(80,70,4,159,227*)
hi-LOOCV@L2c2 with n8 min207.3 max300.3 mean270.2 median276.1 std27.1 best-iNshh(85,50,14,138,300*)
hi-LOOCV@L2c3 with n24 min138.0 max253.9 mean225.3 median231.3 std26.3 best-iNshh(68,90,1,135,254*)

#Thu Jun 11 08:02:44 JST 2020 TP0=2400 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(202,354) 350L0
h(yi,yg)@L0c0 with n98 min56.0 max354.0 mean162.0 median191.0 std84.4 best-iNshh(29,90,16,354*,155)
h(yi,yg)@L2c0 with n24 min173.0 max351.0 mean239.8 median231.0 std41.5 best-iNshh(10,80,10,351*,238)
h(yi,yg)@L2c1 with n39 min68.0 max354.0 mean204.1 median201.0 std47.8 best-iNshh(29,90,16,354*,201)
h(yi,yg)@L2c2 with n32 min56.0 max64.0 mean60.9 median61.0 std2.2 best-iNshh(85,80,7,64*,145)(87,90,6,64*,134)(89,100,14,64*,118)
h(yi,yg)@L2c3 with n1 min66.0 max66.0 mean66.0 median66.0 std0.0 best-iNshh(97,100,6,66*,-1)
hi-LOOCV@L0c0 with n98 min64.2 max162.2 mean124.5 median132.5 std30.2 best-iNshh(5,90,10,350,162*)
hi-LOOCV@L2c0 with n24 min173.7 max250.7 mean229.5 median238.2 std20.3 best-iNshh(6,100,11,226,251*)
hi-LOOCV@L2c1 with n39 min125.6 max214.7 mean191.9 median200.7 std21.5 best-iNshh(25,100,2,202,215*)
hi-LOOCV@L2c2 with n32 min92.0 max198.9 mean156.5 median162.0 std24.8 best-iNshh(60,90,5,62,199*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(97,100,6,66,-1*)

#Thu Jun 11 07:54:31 JST 2020 TP0=2300 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(191,361) 190L0
h(yi,yg)@L0c0 with n101 min65.0 max361.0 mean138.4 median148.0 std55.4 best-iNshh(12,60,14,361*,140)
h(yi,yg)@L2c0 with n10 min65.0 max68.0 mean66.3 median66.0 std1.0 best-iNshh(82,80,6,68*,193)(98,50,9,68*,109)
h(yi,yg)@L2c1 with n8 min68.0 max69.0 mean68.5 median68.5 std0.5 best-iNshh(84,80,4,69*,269)(89,90,4,69*,256)(91,100,9,69*,203)(92,90,12,69*,256)
h(yi,yg)@L2c2 with n56 min70.0 max361.0 mean160.6 median159.5 std46.5 best-iNshh(12,60,14,361*,158)
h(yi,yg)@L2c3 with n27 min78.0 max245.0 mean139.9 median161.0 std51.0 best-iNshh(0,50,12,245*,166)
hi-LOOCV@L0c0 with n101 min72.5 max149.4 mean117.5 median122.1 std21.2 best-iNshh(2,70,10,190,149*)
hi-LOOCV@L2c0 with n10 min108.6 max193.1 mean166.7 median170.6 std23.3 best-iNshh(82,80,6,68,193*)
hi-LOOCV@L2c1 with n8 min127.9 max268.9 mean236.6 median255.9 std45.7 best-iNshh(84,80,4,69,269*)
hi-LOOCV@L2c2 with n56 min69.2 max168.3 mean150.2 median152.3 std16.2 best-iNshh(13,60,1,191,168*)
hi-LOOCV@L2c3 with n27 min87.3 max199.8 mean167.5 median178.5 std30.5 best-iNshh(74,60,11,79,200*)

#Thu Jun 11 07:46:00 JST 2020 TP0=2200 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(267,371) 316L0
h(yi,yg)@L0c0 with n101 min46.0 max371.0 mean177.5 median166.0 std52.0 best-iNshh(21,80,12,371*,178)
h(yi,yg)@L2c0 with n94 min89.0 max371.0 mean183.7 median166.0 std48.2 best-iNshh(21,80,12,371*,184)
h(yi,yg)@L2c1 with n6 min97.0 max105.0 mean103.2 median104.5 std2.9 best-iNshh(93,60,14,105*,192)(94,60,12,105*,197)(95,70,10,105*,137)
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(100,90,2,46*,-1)
hi-LOOCV@L0c0 with n101 min46.0 max180.0 mean160.4 median172.3 std24.5 best-iNshh(9,50,13,316,180*)
hi-LOOCV@L2c0 with n94 min87.3 max186.4 mean170.2 median179.0 std18.5 best-iNshh(32,100,6,267,186*)
hi-LOOCV@L2c1 with n6 min97.4 max196.6 mean155.9 median158.5 std36.2 best-iNshh(94,60,12,105,197*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(100,90,2,46,-1*)

#Thu Jun 11 02:00:27 JST 2020 TP0=2000 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(157,414) 187L0
h(yi,yg)@L0c0 with n97 min20.0 max414.0 mean161.8 median157.0 std59.3 best-iNshh(61,80,10,414*,155)
h(yi,yg)@L2c0 with n38 min123.0 max414.0 mean184.7 median181.5 std56.6 best-iNshh(61,80,10,414*,172)
h(yi,yg)@L2c1 with n8 min20.0 max196.0 mean150.1 median180.0 std57.2 best-iNshh(92,70,1,196*,159)
h(yi,yg)@L2c2 with n47 min29.0 max295.0 mean152.1 median157.0 std54.4 best-iNshh(40,90,9,295*,171)
h(yi,yg)@L2c3 with n4 min30.0 max101.0 mean82.0 median98.5 std30.0 best-iNshh(86,80,4,101*,216)
hi-LOOCV@L0c0 with n97 min20.8 max171.3 mean145.2 median159.2 std28.6 best-iNshh(6,90,1,187,171*)
hi-LOOCV@L2c0 with n38 min123.4 max192.8 mean174.0 median178.6 std17.0 best-iNshh(60,100,3,188,193*)
hi-LOOCV@L2c1 with n8 min15.7 max171.9 mean133.1 median160.4 std51.3 best-iNshh(83,80,2,180,172*)
hi-LOOCV@L2c2 with n47 min141.3 max189.9 mean171.5 median175.0 std14.2 best-iNshh(8,70,9,157,190*)
hi-LOOCV@L2c3 with n4 min78.3 max215.7 mean156.0 median165.0 std53.3 best-iNshh(86,80,4,101,216*)

#Thu Jun 11 02:07:11 JST 2020 TP0=2100 N:50,60,70,80,90,100 ns=17 ==>(hV,hg)=(100,357) 258L0
h(yi,yg)@L0c0 with n98 min90.0 max357.0 mean143.9 median99.0 std62.4 best-iNshh(2,100,16,357*,154)
h(yi,yg)@L2c0 with n51 min96.0 max357.0 mean159.5 median147.0 std61.4 best-iNshh(2,100,16,357*,184)
h(yi,yg)@L2c1 with n16 min98.0 max270.0 mean195.1 median205.5 std56.5 best-iNshh(38,60,8,270*,191)
h(yi,yg)@L2c2 with n30 min90.0 max96.0 mean91.7 median92.0 std1.3 best-iNshh(96,70,11,96*,99)
h(yi,yg)@L2c3 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(95,100,9,98*,-1)
hi-LOOCV@L0c0 with n98 min95.8 max156.3 mean132.6 median130.8 std13.9 best-iNshh(0,60,12,258,156*)
hi-LOOCV@L2c0 with n51 min91.1 max193.5 mean173.9 median181.7 std18.8 best-iNshh(6,60,1,100,194*)
hi-LOOCV@L2c1 with n16 min106.9 max232.5 mean192.9 median189.2 std28.6 best-iNshh(46,60,15,234,233*)
hi-LOOCV@L2c2 with n30 min98.6 max232.7 mean205.6 median221.3 std31.1 best-iNshh(43,80,4,92,233*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(95,100,9,98,-1*)


#Thu Jun 11 01:47:21 JST 2020 TP0=2900 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(190,370) 216L0
h(yi,yg)@L0c0 with n99 min70.0 max370.0 mean160.8 median187.0 std71.8 best-iNshh(42,100,16,370*,147)
h(yi,yg)@L2c0 with n26 min70.0 max76.0 mean73.3 median73.0 std1.5 best-iNshh(88,100,10,76*,117)(90,62,7,76*,112)(92,75,10,76*,105)
h(yi,yg)@L2c1 with n1 min77.0 max77.0 mean77.0 median77.0 std0.0 best-iNshh(98,100,2,77*,-1)
h(yi,yg)@L2c2 with n27 min78.0 max249.0 mean197.1 median214.0 std44.2 best-iNshh(18,75,5,249*,200)(19,62,11,249*,200)
h(yi,yg)@L2c3 with n43 min76.0 max370.0 mean196.8 median189.0 std58.4 best-iNshh(42,100,16,370*,192)
hi-LOOCV@L0c0 with n99 min86.7 max173.9 mean133.5 median142.4 std29.2 best-iNshh(3,87,12,216,174*)
hi-LOOCV@L2c0 with n26 min104.7 max206.6 mean176.0 median183.1 std29.0 best-iNshh(70,75,19,74,207*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(98,100,2,77,-1*)
hi-LOOCV@L2c2 with n27 min101.7 max258.5 mean220.1 median235.3 std38.6 best-iNshh(34,100,3,214,259*)
hi-LOOCV@L2c3 with n43 min85.0 max202.4 mean177.5 median191.1 std31.1 best-iNshh(36,100,18,190,202*)

#Thu Jun 11 01:37:42 JST 2020 TP0=2800 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(409,470) 259L0
h(yi,yg)@L0c0 with n100 min46.0 max470.0 mean170.2 median167.0 std80.3 best-iNshh(7,87,12,470*,165)
h(yi,yg)@L2c0 with n71 min83.0 max470.0 mean188.1 median168.0 std78.7 best-iNshh(7,87,12,470*,184)
h(yi,yg)@L2c1 with n21 min63.0 max259.0 mean154.3 median168.0 std56.3 best-iNshh(11,100,14,259*,164)
h(yi,yg)@L2c2 with n1 min46.0 max46.0 mean46.0 median46.0 std0.0 best-iNshh(99,87,14,46*,-1)
h(yi,yg)@L2c3 with n7 min53.0 max55.0 mean53.6 median53.0 std0.7 best-iNshh(98,50,7,55*,85)
hi-LOOCV@L0c0 with n100 min46.4 max166.2 mean132.6 median146.1 std32.1 best-iNshh(11,100,14,259,166*)
hi-LOOCV@L2c0 with n71 min84.6 max184.4 mean153.7 median155.9 std23.3 best-iNshh(6,62,17,409,184*)
hi-LOOCV@L2c1 with n21 min109.7 max232.5 mean191.6 median196.4 std27.3 best-iNshh(87,87,9,64,232*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(99,87,14,46,-1*)
hi-LOOCV@L2c3 with n7 min85.3 max186.0 mean140.1 median159.5 std34.8 best-iNshh(92,75,12,54,186*)
#Thu Jun 11 01:28:27 JST 2020 TP0=2700 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(174,355) 174L0
h(yi,yg)@L0c0 with n96 min86.0 max355.0 mean166.1 median152.0 std44.8 best-iNshh(58,75,7,355*,156)
h(yi,yg)@L2c0 with n4 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(90,87,6,87*,217)(91,100,4,87*,221)(92,75,6,87*,214)(94,50,7,87*,205)
h(yi,yg)@L2c1 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(95,50,5,86*,-1)
h(yi,yg)@L2c2 with n84 min129.0 max355.0 mean175.3 median167.5 std39.9 best-iNshh(58,75,7,355*,164)
h(yi,yg)@L2c3 with n7 min89.0 max119.0 mean112.4 median116.0 std9.8 best-iNshh(84,87,16,119*,153)(85,87,4,119*,158)
hi-LOOCV@L0c0 with n96 min90.0 max171.7 mean152.8 median160.7 std19.6 best-iNshh(4,50,12,174,172*)
hi-LOOCV@L2c0 with n4 min204.7 max221.0 mean214.2 median215.5 std6.0 best-iNshh(91,100,4,87,221*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(95,50,5,86,-1*)
hi-LOOCV@L2c2 with n84 min145.5 max181.6 mean167.9 median169.7 std7.2 best-iNshh(4,50,12,174,182*)
hi-LOOCV@L2c3 with n7 min108.3 max170.0 mean149.0 median153.3 std19.8 best-iNshh(86,87,17,116,170*)

#Thu Jun 11 01:20:25 JST 2020 TP0=2600 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(183,308) 184L0
h(yi,yg)@L0c0 with n100 min39.0 max308.0 mean168.1 median155.5 std43.2 best-iNshh(49,100,5,308*,165)
h(yi,yg)@L2c0 with n12 min123.0 max127.0 mean124.8 median125.0 std1.1 best-iNshh(82,50,19,127*,201)
h(yi,yg)@L2c1 with n51 min128.0 max308.0 mean186.9 median183.0 std40.1 best-iNshh(49,100,5,308*,183)
h(yi,yg)@L2c2 with n35 min116.0 max277.0 mean162.7 median154.0 std30.3 best-iNshh(5,50,10,277*,161)
h(yi,yg)@L2c3 with n1 min39.0 max39.0 mean39.0 median39.0 std0.0 best-iNshh(99,62,7,39*,-1)
hi-LOOCV@L0c0 with n100 min41.8 max178.9 mean157.6 median164.3 std20.9 best-iNshh(1,87,7,184,179*)
hi-LOOCV@L2c0 with n12 min201.1 max221.8 mean211.2 median207.7 std7.1 best-iNshh(83,62,15,124,222*)
hi-LOOCV@L2c1 with n51 min135.5 max197.4 mean178.2 median183.1 std13.3 best-iNshh(8,100,16,183,197*)
hi-LOOCV@L2c2 with n35 min125.9 max192.9 mean167.7 median171.4 std17.1 best-iNshh(65,62,13,156,193*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(99,62,7,39,-1*)

#Thu Jun 11 01:12:12 JST 2020 TP0=2500 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(286,355) 286L0
h(yi,yg)@L0c0 with n99 min114.0 max355.0 mean195.7 median191.0 std61.8 best-iNshh(10,50,18,355*,200)
h(yi,yg)@L2c0 with n56 min148.0 max355.0 mean239.4 median247.5 std47.6 best-iNshh(10,50,18,355*,246)
h(yi,yg)@L2c1 with n7 min114.0 max166.0 mean155.1 median161.0 std17.0 best-iNshh(82,62,3,166*,205)
h(yi,yg)@L2c2 with n21 min130.0 max139.0 mean134.4 median135.0 std1.9 best-iNshh(95,100,11,139*,138)
h(yi,yg)@L2c3 with n15 min136.0 max138.0 mean137.1 median137.0 std0.8 best-iNshh(61,87,19,138*,322)(70,87,1,138*,329)(71,50,14,138*,309)(90,100,10,138*,215)(92,62,7,138*,208)(93,62,12,138*,201)
hi-LOOCV@L0c0 with n99 min135.9 max206.5 mean177.8 median178.2 std17.3 best-iNshh(0,62,8,286,207*)
hi-LOOCV@L2c0 with n56 min173.2 max257.0 mean226.3 median233.4 std22.0 best-iNshh(0,62,8,286,257*)
hi-LOOCV@L2c1 with n7 min203.2 max214.7 mean208.6 median209.2 std4.4 best-iNshh(98,50,9,114,215*)
hi-LOOCV@L2c2 with n21 min137.7 max259.4 mean224.1 median231.6 std29.5 best-iNshh(53,87,14,135,259*)
hi-LOOCV@L2c3 with n15 min201.0 max328.6 mean276.4 median290.1 std38.1 best-iNshh(70,87,1,138,329*)

#Thu Jun 11 01:03:59 JST 2020 TP0=2400 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(203,475) 232L0
h(yi,yg)@L0c0 with n98 min56.0 max475.0 mean164.9 median172.5 std84.7 best-iNshh(19,87,16,475*,158)
h(yi,yg)@L2c0 with n25 min56.0 max65.0 mean61.0 median61.0 std2.5 best-iNshh(88,75,13,65*,105)
h(yi,yg)@L2c1 with n1 min66.0 max66.0 mean66.0 median66.0 std0.0 best-iNshh(96,100,6,66*,-1)
h(yi,yg)@L2c2 with n46 min68.0 max475.0 mean188.8 median181.0 std68.8 best-iNshh(19,87,16,475*,185)
h(yi,yg)@L2c3 with n24 min165.0 max351.0 mean238.8 median231.0 std37.0 best-iNshh(15,87,0,351*,236)
hi-LOOCV@L0c0 with n98 min64.3 max168.4 mean121.2 median130.4 std32.8 best-iNshh(3,87,14,232,168*)
hi-LOOCV@L2c0 with n25 min96.7 max174.0 mean143.0 median144.5 std22.7 best-iNshh(67,87,13,61,174*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(96,100,6,66,-1*)
hi-LOOCV@L2c2 with n46 min85.2 max190.9 mean169.7 median178.5 std23.2 best-iNshh(27,75,11,203,191*)
hi-LOOCV@L2c3 with n24 min152.6 max268.3 mean245.9 median255.6 std25.1 best-iNshh(58,100,1,232,268*)

#Thu Jun 11 00:53:32 JST 2020 TP0=2300 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(167,362) (245,362)inL0
h(yi,yg)@L0c0 with n98 min65.0 max362.0 mean142.2 median158.5 std57.3 best-iNshh(24,50,18,362*,132)
h(yi,yg)@L2c0 with n56 min69.0 max362.0 mean160.0 median160.0 std44.8 best-iNshh(24,50,18,362*,158)
h(yi,yg)@L2c1 with n23 min78.0 max272.0 mean160.6 median167.0 std58.0 best-iNshh(3,87,12,272*,176)
h(yi,yg)@L2c2 with n8 min68.0 max70.0 mean68.6 median68.5 std0.7 best-iNshh(94,62,19,70*,110)
h(yi,yg)@L2c3 with n11 min65.0 max70.0 mean66.6 median66.0 std1.4 best-iNshh(92,62,18,70*,71)
hi-LOOCV@L0c0 with n98 min71.9 max152.7 mean116.0 median121.3 std22.6 best-iNshh(0,50,12,245,153*)
hi-LOOCV@L2c0 with n56 min68.9 max172.3 mean149.0 median157.4 std21.5 best-iNshh(1,87,16,167,172*)
hi-LOOCV@L2c1 with n23 min120.9 max213.8 mean185.2 median192.0 std23.5 best-iNshh(51,62,6,189,214*)
hi-LOOCV@L2c2 with n8 min110.0 max233.9 mean192.5 median215.1 std45.9 best-iNshh(90,87,4,69,234*)
hi-LOOCV@L2c3 with n11 min70.8 max181.4 mean148.2 median159.8 std34.1 best-iNshh(87,50,0,65,181*)

#Thu Jun 11 00:45:03 JST 2020 TP0=2200 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(267,316)
h(yi,yg)@L0c0 with n97 min89.0 max316.0 mean183.0 median166.0 std52.6 best-iNshh(1,50,13,316*,189)
h(yi,yg)@L2c0 with n74 min132.0 max316.0 mean198.9 median185.5 std47.9 best-iNshh(1,50,13,316*,207)
h(yi,yg)@L2c1 with n18 min89.0 max193.0 mean140.5 median133.0 std27.0 best-iNshh(56,100,10,193*,155)
h(yi,yg)@L2c2 with n4 min103.0 max104.0 mean103.8 median104.0 std0.4 best-iNshh(90,100,2,104*,174)(91,62,14,104*,171)(92,62,12,104*,162)
h(yi,yg)@L2c3 with n1 min90.0 max90.0 mean90.0 median90.0 std0.0 best-iNshh(95,62,10,90*,-1)
hi-LOOCV@L0c0 with n97 min87.3 max189.8 mean163.8 median174.3 std22.2 best-iNshh(4,100,6,267,190*)
hi-LOOCV@L2c0 with n74 min134.6 max208.1 mean185.2 median188.2 std14.7 best-iNshh(4,100,6,267,208*)
hi-LOOCV@L2c1 with n18 min80.9 max200.7 mean163.8 median172.4 std33.1 best-iNshh(73,75,11,134,201*)
hi-LOOCV@L2c2 with n4 min139.3 max173.7 mean161.5 median166.5 std13.6 best-iNshh(90,100,2,104,174*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(95,62,10,90,-1*)

#Thu Jun 11 00:32:54 JST 2020 TP0=2100 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(262,357)
h(yi,yg)@L0c0 with n97 min88.0 max357.0 mean141.4 median99.0 std63.7 best-iNshh(2,100,16,357*,150)
h(yi,yg)@L2c0 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(96,100,9,98*,-1)
h(yi,yg)@L2c1 with n35 min88.0 max96.0 mean91.3 median91.0 std1.4 best-iNshh(94,62,11,96*,100)
h(yi,yg)@L2c2 with n54 min97.0 max357.0 mean180.0 median177.5 std62.5 best-iNshh(2,100,16,357*,197)
h(yi,yg)@L2c3 with n6 min96.0 max116.0 mean100.3 median97.5 std7.0 best-iNshh(87,50,19,116*,123)
hi-LOOCV@L0c0 with n97 min98.1 max154.0 mean131.2 median134.1 std14.1 best-iNshh(0,62,12,262,154*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(96,100,9,98,-1*)
hi-LOOCV@L2c1 with n35 min99.6 max239.9 mean203.8 median214.2 std30.9 best-iNshh(14,62,18,91,240*)
hi-LOOCV@L2c2 with n54 min121.3 max204.2 mean172.7 median174.7 std19.8 best-iNshh(0,62,12,262,204*)
hi-LOOCV@L2c3 with n6 min116.0 max183.2 mean148.9 median146.4 std29.9 best-iNshh(92,62,16,97,183*)
#Thu Jun 11 00:24:35 JST 2020 TP0=2000 N:50,62,75,87,100 ns=20 ==>(hV,hg)=(221,336)
h(yi,yg)@L0c0 with n97 min20.0 max336.0 mean160.6 median158.0 std61.2 best-iNshh(36,87,6,336*,158)
h(yi,yg)@L2c0 with n75 min98.0 max336.0 mean177.2 median159.0 std45.9 best-iNshh(36,87,6,336*,173)
h(yi,yg)@L2c1 with n8 min20.0 max197.0 mean151.6 median181.5 std58.2 best-iNshh(56,87,3,197*,166)
h(yi,yg)@L2c2 with n10 min29.0 max193.0 mean95.6 median79.5 std68.0 best-iNshh(21,75,4,193*,182)
h(yi,yg)@L2c3 with n4 min30.0 max31.0 mean30.2 median30.0 std0.4 best-iNshh(95,62,19,31*,151)
hi-LOOCV@L0c0 with n97 min21.1 max167.9 mean138.9 median153.5 std31.7 best-iNshh(6,87,15,222,168*)
hi-LOOCV@L2c0 with n75 min102.3 max184.7 mean163.6 median169.6 std18.6 best-iNshh(0,62,8,221,185*)
hi-LOOCV@L2c1 with n8 min15.9 max177.6 mean134.8 median161.5 std52.3 best-iNshh(87,62,1,191,178*)
hi-LOOCV@L2c2 with n10 min136.6 max199.1 mean179.9 median179.6 std17.3 best-iNshh(63,62,4,158,199*)
hi-LOOCV@L2c3 with n4 min118.3 max151.0 mean139.3 median144.0 std13.1 best-iNshh(95,62,19,31,151*)

#Wed Jun 10 23:43:31 JST 2020 TP0=2900 N:50 ns=100 ==>(hV,hg)=(218,309)
h(yi,yg)@L0c0 with n99 min36.0 max309.0 mean145.5 median157.0 std62.8 best-iNshh(49,50,50,309*,143)
h(yi,yg)@L2c0 with n68 min50.0 max309.0 mean179.1 median178.5 std46.0 best-iNshh(49,50,50,309*,175)
h(yi,yg)@L2c1 with n29 min70.0 max87.0 mean74.3 median74.0 std3.0 best-iNshh(21,50,22,87*,90)
h(yi,yg)@L2c2 with n1 min39.0 max39.0 mean39.0 median39.0 std0.0 best-iNshh(76,50,77,39*,-1)
hi-LOOCV@L0c0 with n99 min36.6 max149.9 mean118.7 median120.8 std25.1 best-iNshh(18,50,19,218,150*)
hi-LOOCV@L2c0 with n68 min58.0 max185.9 mean159.0 median169.1 std24.8 best-iNshh(18,50,19,218,186*)
hi-LOOCV@L2c1 with n29 min84.5 max192.1 mean150.1 median163.0 std33.8 best-iNshh(59,50,60,74,192*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(76,50,77,39,-1*)

#Wed Jun 10 23:29:58 JST 2020 TP0=2800 N:50 ns=100 ==>(hV,hg)=(139,349) #better in L2,L0
h(yi,yg)@L0c0 with n100 min48.0 max349.0 mean147.2 median139.0 std57.4 best-iNshh(1,50,1,349*,140)
h(yi,yg)@L2c0 with n27 min65.0 max275.0 mean175.5 median170.0 std46.4 best-iNshh(49,50,49,275*,184)
h(yi,yg)@L2c1 with n60 min104.0 max349.0 mean155.1 median138.5 std46.1 best-iNshh(1,50,1,349*,151)
h(yi,yg)@L2c2 with n8 min48.0 max52.0 mean50.6 median51.0 std1.6 best-iNshh(21,50,21,52*,130)(31,50,31,52*,135)(32,50,32,52*,127)
h(yi,yg)@L2c3 with n5 min53.0 max55.0 mean53.8 median54.0 std0.7 best-iNshh(7,50,7,55*,125)
hi-LOOCV@L0c0 with n100 min51.9 max147.9 mean121.2 median135.2 std29.7 best-iNshh(14,50,14,173,148*)
hi-LOOCV@L2c0 with n27 min75.0 max201.2 mean171.4 median181.0 std30.4 best-iNshh(75,50,75,170,201*)
hi-LOOCV@L2c1 with n60 min113.0 max161.8 mean143.7 median150.0 std14.8 best-iNshh(66,50,66,139,162*)
hi-LOOCV@L2c2 with n8 min98.0 max135.3 mean122.4 median128.2 std13.3 best-iNshh(77,50,77,51,135*)
hi-LOOCV@L2c3 with n5 min107.0 max178.2 mean131.0 median124.5 std24.5 best-iNshh(41,50,41,54,178*)
#Wed Jun 10 23:21:14 JST 2020 TP0=2700 N:50 ns=100 ==>(hV,hg)=(175,448)
h(yi,yg)@L0c0 with n98 min85.0 max448.0 mean157.5 median148.0 std56.2 best-iNshh(91,50,93,448*,149)
h(yi,yg)@L2c0 with n73 min98.0 max448.0 mean177.4 median172.0 std51.2 best-iNshh(91,50,93,448*,166)
h(yi,yg)@L2c1 with n12 min89.0 max119.0 mean113.2 median115.0 std7.5 best-iNshh(57,50,59,119*,122)
h(yi,yg)@L2c2 with n9 min85.0 max88.0 mean86.6 median86.0 std1.0 best-iNshh(26,50,28,88*,183)(80,50,82,88*,184)
h(yi,yg)@L2c3 with n4 min85.0 max90.0 mean87.5 median87.5 std2.1 best-iNshh(42,50,44,90*,151)
hi-LOOCV@L0c0 with n98 min90.4 max162.7 mean138.6 median149.1 std21.0 best-iNshh(0,50,0,175,163*)
hi-LOOCV@L2c0 with n73 min141.8 max183.7 mean167.1 median167.5 std8.5 best-iNshh(0,50,0,175,184*)
hi-LOOCV@L2c1 with n12 min95.4 max210.0 mean175.9 median189.9 std33.3 best-iNshh(90,50,92,116,210*)
hi-LOOCV@L2c2 with n9 min160.1 max190.6 mean178.0 median183.1 std11.3 best-iNshh(34,50,36,86,191*)
hi-LOOCV@L2c3 with n4 min147.7 max155.0 mean151.3 median151.3 std2.6 best-iNshh(45,50,47,85,155*)

#Wed Jun 10 23:13:10 JST 2020 TP0=2600 N:50 ns=100 ==>(hV,hg)=(183,310)
h(yi,yg)@L0c0 with n99 min48.0 max310.0 mean160.4 median152.0 std45.4 best-iNshh(40,50,40,310*,163)
h(yi,yg)@L2c0 with n37 min95.0 max310.0 mean154.9 median127.0 std48.8 best-iNshh(40,50,40,310*,161)
h(yi,yg)@L2c1 with n43 min146.0 max275.0 mean175.7 median182.0 std28.4 best-iNshh(57,50,57,275*,173)
h(yi,yg)@L2c2 with n16 min48.0 max277.0 mean138.5 median151.5 std60.4 best-iNshh(10,50,10,277*,154)
h(yi,yg)@L2c3 with n1 min126.0 max126.0 mean126.0 median126.0 std0.0 best-iNshh(89,50,90,126*,-1)
hi-LOOCV@L0c0 with n99 min66.8 max171.5 mean148.7 median154.6 std19.0 best-iNshh(66,50,66,187,171*)
hi-LOOCV@L2c0 with n37 min96.0 max172.3 mean158.0 median162.2 std14.1 best-iNshh(80,50,80,215,172*)
hi-LOOCV@L2c1 with n43 min163.5 max203.9 mean182.9 median183.6 std10.7 best-iNshh(0,50,0,183,204*)
hi-LOOCV@L2c2 with n16 min151.1 max202.0 mean182.9 median187.8 std14.6 best-iNshh(41,50,41,150,202*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(89,50,90,126,-1*)

#Wed Jun 10 22:26:06 JST 2020 TP0=2500 N:50 ns=100 ==>(hV,hg)=(251,355)
h(yi,yg)@L0c0 with n98 min73.0 max355.0 mean182.8 median189.5 std54.8 best-iNshh(18,50,18,355*,184)
h(yi,yg)@L2c0 with n91 min105.0 max355.0 mean189.3 median191.0 std51.4 best-iNshh(18,50,18,355*,191)
h(yi,yg)@L2c1 with n6 min101.0 max106.0 mean103.2 median103.0 std1.7 best-iNshh(95,50,97,106*,95)
h(yi,yg)@L2c2 with n1 min73.0 max73.0 mean73.0 median73.0 std0.0 best-iNshh(76,50,77,73*,-1)
hi-LOOCV@L0c0 with n98 min73.2 max190.9 mean161.4 median166.0 std23.2 best-iNshh(23,50,23,251,191*)
hi-LOOCV@L2c0 with n91 min110.1 max197.4 mean170.9 median175.7 std18.1 best-iNshh(23,50,23,251,197*)
hi-LOOCV@L2c1 with n6 min95.4 max160.6 mean140.4 median142.2 std21.7 best-iNshh(25,50,25,102,161*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(76,50,77,73,-1*)

#Wed Jun 10 22:02:22 JST 2020 TP0=2400 N:50 ns=100 ==>(hV,hg)=(262,267)
h(yi,yg)@L0c0 with n97 min54.0 max267.0 mean114.5 median68.0 std67.5 best-iNshh(64,50,66,267*,118)
h(yi,yg)@L2c0 with n48 min68.0 max267.0 mean168.2 median172.0 std59.0 best-iNshh(64,50,66,267*,177)
h(yi,yg)@L2c1 with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(76,50,78,87*,-1)
h(yi,yg)@L2c2 with n23 min61.0 max65.0 mean62.3 median62.0 std1.1 best-iNshh(73,50,75,65*,96)
h(yi,yg)@L2c3 with n24 min54.0 max76.0 mean59.5 median58.5 std4.8 best-iNshh(13,50,14,76*,77)
hi-LOOCV@L0c0 with n97 min63.5 max119.6 mean98.2 median101.7 std15.1 best-iNshh(52,50,53,262,120*)
hi-LOOCV@L2c0 with n48 min89.4 max180.9 mean154.5 median161.7 std22.8 best-iNshh(52,50,53,262,181*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(76,50,78,87,-1*)
hi-LOOCV@L2c2 with n23 min95.9 max208.3 mean184.8 median191.1 std25.0 best-iNshh(89,50,92,62,208*)
hi-LOOCV@L2c3 with n24 min70.6 max144.5 mean111.9 median121.7 std22.7 best-iNshh(45,50,46,59,145*)
#Wed Jun 10 21:14:03 JST 2020 TP0=2300 N:50 ns=100 ==>(hV,hg)=(167,362)
h(yi,yg)@L0c0 with n98 min63.0 max362.0 mean136.7 median136.5 std55.2 best-iNshh(18,50,18,362*,128)
h(yi,yg)@L2c0 with n72 min80.0 max362.0 mean160.3 median159.5 std44.8 best-iNshh(18,50,18,362*,149)
h(yi,yg)@L2c1 with n5 min86.0 max94.0 mean89.8 median89.0 std2.9 best-iNshh(30,50,30,94*,122)
h(yi,yg)@L2c2 with n15 min64.0 max68.0 mean66.7 median67.0 std1.1 best-iNshh(7,50,7,68*,125)(13,50,13,68*,172)(27,50,27,68*,131)(91,50,93,68*,198)
h(yi,yg)@L2c3 with n6 min63.0 max70.0 mean67.0 median67.5 std2.7 best-iNshh(75,50,76,70*,113)(76,50,77,70*,114)
hi-LOOCV@L0c0 with n98 min69.3 max142.8 mean114.1 median121.7 std22.2 best-iNshh(23,50,23,167,143*)
hi-LOOCV@L2c0 with n72 min87.1 max168.7 mean145.9 median148.5 std16.4 best-iNshh(23,50,23,167,169*)
hi-LOOCV@L2c1 with n5 min107.5 max171.5 mean142.7 median146.0 std25.0 best-iNshh(28,50,28,88,172*)
hi-LOOCV@L2c2 with n15 min119.8 max215.0 mean174.5 median190.9 std31.4 best-iNshh(48,50,49,67,215*)
hi-LOOCV@L2c3 with n6 min85.2 max113.6 mean103.9 median107.0 std9.8 best-iNshh(76,50,77,70,114*)

#Wed Jun 10 21:03:03 JST 2020 TP0=2200 N:50 ns=100 ==>(hV,hg)=(197,430)
h(yi,yg)@L0c0 with n100 min73.0 max430.0 mean160.1 median157.5 std53.5 best-iNshh(43,50,43,430*,159)
h(yi,yg)@L2c0 with n86 min99.0 max430.0 mean170.7 median161.0 std50.0 best-iNshh(43,50,43,430*,169)
h(yi,yg)@L2c1 with n9 min97.0 max104.0 mean102.6 median103.0 std2.1 best-iNshh(55,50,55,104*,142)(81,50,81,104*,169)(84,50,84,104*,168)
h(yi,yg)@L2c2 with n1 min73.0 max73.0 mean73.0 median73.0 std0.0 best-iNshh(76,50,76,73*,-1)
h(yi,yg)@L2c3 with n4 min75.0 max89.0 mean82.0 median82.0 std5.7 best-iNshh(12,50,12,89*,142)
hi-LOOCV@L0c0 with n100 min74.5 max165.7 mean143.5 median151.3 std21.6 best-iNshh(56,50,56,197,166*)
hi-LOOCV@L2c0 with n86 min96.8 max177.2 mean160.4 median163.7 std11.9 best-iNshh(56,50,56,197,177*)
hi-LOOCV@L2c1 with n9 min100.8 max168.9 mean142.7 median141.9 std20.1 best-iNshh(81,50,81,104,169*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(76,50,76,73,-1*)
hi-LOOCV@L2c3 with n4 min90.7 max173.3 mean144.8 median157.7 std33.8 best-iNshh(30,50,30,86,173*)(72,50,72,78,173*)

#Wed Jun 10 20:53:18 JST 2020 TP0=2100 N:50 ns=100 ==>(hV,hg)=(233,268)
h(yi,yg)@L0c0 with n98 min54.0 max268.0 mean131.3 median99.0 std53.2 best-iNshh(1,50,1,268*,136)
h(yi,yg)@L2c0 with n55 min96.0 max268.0 mean163.8 median163.0 std51.1 best-iNshh(1,50,1,268*,174)
h(yi,yg)@L2c1 with n42 min86.0 max98.0 mean90.6 median91.0 std2.4 best-iNshh(68,50,70,98*,93)
h(yi,yg)@L2c2 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(30,50,31,54*,-1)
hi-LOOCV@L0c0 with n98 min53.9 max140.5 mean124.0 median128.4 std13.6 best-iNshh(69,50,71,92,140*)
hi-LOOCV@L2c0 with n55 min95.3 max176.8 mean156.0 median162.7 std20.3 best-iNshh(22,50,23,233,177*)
hi-LOOCV@L2c1 with n42 min93.2 max210.9 mean171.0 median180.6 std28.9 best-iNshh(69,50,71,92,211*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,31,54,-1*)
#Wed Jun 10 20:43:00 JST 2020 TP0=2000 N:50 ns=100 ==>(hV,hg)=(157,332)
h(yi,yg)@L0c0 with n96 min14.0 max332.0 mean140.5 median149.5 std59.9 best-iNshh(31,50,33,332*,139)
h(yi,yg)@L2c0 with n6 min19.0 max21.0 mean19.5 median19.0 std0.8 best-iNshh(64,50,66,21*,60)
h(yi,yg)@L2c1 with n1 min14.0 max14.0 mean14.0 median14.0 std0.0 best-iNshh(43,50,45,14*,-1)
h(yi,yg)@L2c2 with n19 min29.0 max160.0 mean116.1 median128.0 std42.6 best-iNshh(83,50,86,160*,146)
h(yi,yg)@L2c3 with n68 min71.0 max332.0 mean163.3 median156.0 std43.8 best-iNshh(31,50,33,332*,161)
hi-LOOCV@L0c0 with n96 min14.0 max150.4 mean119.9 median132.9 std35.3 best-iNshh(49,50,51,157,150*)
hi-LOOCV@L2c0 with n6 min59.6 max179.0 mean137.5 median171.7 std53.2 best-iNshh(79,50,81,19,179*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(43,50,45,14,-1*)
hi-LOOCV@L2c2 with n19 min90.3 max146.4 mean130.1 median132.6 std12.2 best-iNshh(83,50,86,160,146*)
hi-LOOCV@L2c3 with n68 min72.2 max172.9 mean153.4 median161.9 std19.4 best-iNshh(74,50,76,157,173*)

#N:50,75,100 ns=33
#Wed Jun 10 20:32:15 JST 2020 TP0=2900 N:50,75,100 ns=33 ==>(hV,hg)=(210,370)
h(yi,yg)@L0c0 with n98 min36.0 max370.0 mean153.0 median164.5 std70.0 best-iNshh(29,100,16,370*,140)
h(yi,yg)@L2c0 with n68 min76.0 max370.0 mean188.6 median190.0 std54.0 best-iNshh(29,100,16,370*,170)
h(yi,yg)@L2c1 with n29 min70.0 max77.0 mean73.8 median73.0 std2.0 best-iNshh(63,75,7,77*,103)(89,100,31,77*,103)(93,100,11,77*,102)(94,100,2,77*,100)
h(yi,yg)@L2c2 with n1 min36.0 max36.0 mean36.0 median36.0 std0.0 best-iNshh(97,50,20,36*,-1)
hi-LOOCV@L0c0 with n98 min36.1 max163.0 mean125.8 median131.2 std26.0 best-iNshh(1,50,25,210,163*)
hi-LOOCV@L2c0 with n68 min76.7 max203.1 mean167.2 median176.2 std28.5 best-iNshh(1,50,25,210,203*)
hi-LOOCV@L2c1 with n29 min93.1 max188.0 mean153.1 median165.2 std30.7 best-iNshh(58,100,32,74,188*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(97,50,20,36,-1*)
#Wed Jun 10 20:21:31 JST 2020 TP0=2800 N:50,75,100 ns=33 ==>(hV,hg)=(197,349)
h(yi,yg)@L0c0 with n99 min48.0 max349.0 mean158.0 median165.0 std63.8 best-iNshh(12,50,1,349*,152)
h(yi,yg)@L2c0 with n24 min63.0 max259.0 mean160.8 median168.5 std58.4 best-iNshh(25,100,14,259*,171)
h(yi,yg)@L2c1 with n65 min104.0 max349.0 mean173.3 median165.0 std54.6 best-iNshh(12,50,1,349*,168)
h(yi,yg)@L2c2 with n4 min53.0 max55.0 mean54.0 median54.0 std0.7 best-iNshh(94,50,7,55*,105)
h(yi,yg)@L2c3 with n6 min48.0 max53.0 mean51.3 median52.0 std1.6 best-iNshh(89,75,31,53*,140)
hi-LOOCV@L0c0 with n99 min50.5 max161.0 mean129.6 median144.8 std31.8 best-iNshh(7,75,32,197,161*)
hi-LOOCV@L2c0 with n24 min101.9 max211.1 mean180.7 median190.6 std28.1 best-iNshh(77,100,9,63,211*)
hi-LOOCV@L2c1 with n65 min108.4 max184.3 mean155.9 median156.8 std20.1 best-iNshh(7,75,32,197,184*)
hi-LOOCV@L2c2 with n4 min94.7 max136.7 mean115.8 median116.0 std16.9 best-iNshh(92,50,12,54,137*)
hi-LOOCV@L2c3 with n6 min91.4 max147.4 mean132.9 median138.8 std18.9 best-iNshh(95,50,32,52,147*)
#Wed Jun 10 19:21:41 JST 2020 TP0=2700 N:50,75,100 ns=33 ==>(hV,hg)=(175,355)
h(yi,yg)@L0c0 with n96 min86.0 max355.0 mean159.0 median149.0 std48.1 best-iNshh(47,75,7,355*,149)
h(yi,yg)@L2c0 with n77 min89.0 max355.0 mean172.8 median155.0 std43.3 best-iNshh(47,75,7,355*,161)
h(yi,yg)@L2c1 with n12 min89.0 max117.0 mean112.3 median114.5 std7.4 best-iNshh(75,100,26,117*,181)(78,75,24,117*,191)(80,75,1,117*,179)
h(yi,yg)@L2c2 with n5 min86.0 max88.0 mean87.0 median87.0 std0.6 best-iNshh(91,50,28,88*,223)
h(yi,yg)@L2c3 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(95,50,27,86*,-1)
hi-LOOCV@L0c0 with n96 min88.3 max162.4 mean142.7 median152.7 std20.8 best-iNshh(0,50,10,175,162*)
hi-LOOCV@L2c0 with n77 min90.7 max176.9 mean163.5 median167.5 std13.3 best-iNshh(0,50,10,175,177*)
hi-LOOCV@L2c1 with n12 min98.1 max193.5 mean166.0 median177.2 std28.4 best-iNshh(77,100,30,114,194*)
hi-LOOCV@L2c2 with n5 min174.0 max223.8 mean204.9 median207.8 std18.6 best-iNshh(88,100,4,87,224*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(95,50,27,86,-1*)

#Wed Jun 10 19:14:08 JST 2020 TP0=2600 N:50,75,100 ns=33 ==>(hV,hg)=(185,308)
h(yi,yg)@L0c0 with n99 min49.0 max308.0 mean168.7 median168.0 std38.5 best-iNshh(50,100,5,308*,166)
h(yi,yg)@L2c0 with n44 min128.0 max308.0 mean185.4 median183.0 std34.7 best-iNshh(50,100,5,308*,181)
h(yi,yg)@L2c1 with n13 min123.0 max127.0 mean125.4 median126.0 std1.4 best-iNshh(80,75,24,127*,221)(81,75,28,127*,216)(83,50,19,127*,226)(85,50,26,127*,217)
h(yi,yg)@L2c2 with n41 min116.0 max277.0 mean167.4 median157.0 std32.4 best-iNshh(17,50,10,277*,166)
h(yi,yg)@L2c3 with n1 min49.0 max49.0 mean49.0 median49.0 std0.0 best-iNshh(98,75,16,49*,-1)
hi-LOOCV@L0c0 with n99 min50.0 max189.0 mean160.5 median161.3 std19.4 best-iNshh(0,50,27,185,189*)
hi-LOOCV@L2c0 with n44 min133.9 max207.1 mean179.4 median185.0 std16.0 best-iNshh(0,50,27,185,207*)
hi-LOOCV@L2c1 with n13 min155.5 max229.2 mean207.2 median207.2 std18.8 best-iNshh(77,100,24,126,229*)
hi-LOOCV@L2c2 with n41 min124.8 max191.8 mean167.9 median171.9 std17.4 best-iNshh(1,50,28,185,192*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(98,75,16,49,-1*)

#Wed Jun 10 19:06:04 JST 2020 TP0=2500 N:50,75,100 ns=33 ==>(hV,hg)=(282,355)
h(yi,yg)@L0c0 with n98 min102.0 max355.0 mean202.8 median193.0 std59.9 best-iNshh(5,50,18,355*,205)
h(yi,yg)@L2c0 with n71 min114.0 max355.0 mean229.1 median226.0 std49.1 best-iNshh(5,50,18,355*,233)
h(yi,yg)@L2c1 with n25 min133.0 max139.0 mean135.8 median136.0 std1.6 best-iNshh(93,100,11,139*,141)
h(yi,yg)@L2c2 with n1 min102.0 max102.0 mean102.0 median102.0 std0.0 best-iNshh(97,50,25,102*,-1)
hi-LOOCV@L0c0 with n98 min102.0 max211.7 mean179.5 median179.1 std23.3 best-iNshh(1,75,8,282,212*)
hi-LOOCV@L2c0 with n71 min147.3 max241.5 mean211.4 median217.9 std23.2 best-iNshh(1,75,8,282,242*)
hi-LOOCV@L2c1 with n25 min140.6 max261.2 mean223.0 median226.0 std31.6 best-iNshh(65,100,3,137,261*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(97,50,25,102,-1*)
#Wed Jun 10 18:57:00 JST 2020 TP0=2400 N:50,75,100 ns=33 ==>(hV,hg)=(203,355) 228L0
h(yi,yg)@L0c0 with n98 min53.0 max355.0 mean145.2 median155.0 std80.2 best-iNshh(23,100,22,355*,143)
h(yi,yg)@L2c0 with n9 min53.0 max66.0 mean63.2 median64.0 std3.7 best-iNshh(94,100,6,66*,69)
h(yi,yg)@L2c1 with n25 min54.0 max66.0 mean60.1 median61.0 std2.5 best-iNshh(89,100,25,66*,64)
h(yi,yg)@L2c2 with n42 min68.0 max322.0 mean172.1 median172.0 std57.5 best-iNshh(28,100,7,322*,175)
h(yi,yg)@L2c3 with n22 min76.0 max355.0 mean224.2 median230.5 std60.8 best-iNshh(23,100,22,355*,219)
hi-LOOCV@L0c0 with n98 min54.1 max152.2 mean107.1 median107.8 std26.6 best-iNshh(5,100,16,228,152*)
hi-LOOCV@L2c0 with n9 min52.0 max165.1 mean125.4 median143.6 std40.8 best-iNshh(70,100,29,64,165*)
hi-LOOCV@L2c1 with n25 min64.0 max177.4 mean140.1 median154.8 std34.4 best-iNshh(56,100,5,59,177*)
hi-LOOCV@L2c2 with n42 min115.9 max187.2 mean165.6 median174.8 std21.1 best-iNshh(25,100,3,203,187*)
hi-LOOCV@L2c3 with n22 min86.6 max255.3 mean212.7 median230.9 std44.0 best-iNshh(52,100,1,232,255*)

#Wed Jun 10 18:48:06 JST 2020 TP0=2300 N:50,75,100 ns=33 ==>(hV,hg)=(188,362)
h(yi,yg)@L0c0 with n97 min64.0 max362.0 mean138.0 median155.0 std58.1 best-iNshh(21,50,18,362*,129)
h(yi,yg)@L2c0 with n46 min121.0 max362.0 mean166.8 median164.5 std44.4 best-iNshh(21,50,18,362*,161)
h(yi,yg)@L2c1 with n28 min79.0 max302.0 mean148.8 median160.0 std53.4 best-iNshh(5,50,20,302*,150)
h(yi,yg)@L2c2 with n7 min68.0 max69.0 mean68.4 median68.0 std0.5 best-iNshh(87,100,9,69*,216)(88,75,23,69*,234)(92,75,29,69*,233)
h(yi,yg)@L2c3 with n16 min64.0 max68.0 mean66.4 median67.0 std1.1 best-iNshh(70,75,27,68*,186)(94,50,9,68*,107)
hi-LOOCV@L0c0 with n97 min72.1 max144.2 mean113.2 median114.5 std20.7 best-iNshh(0,50,26,167,144*)
hi-LOOCV@L2c0 with n46 min127.5 max178.8 mean159.8 median164.4 std14.7 best-iNshh(12,100,21,188,179*)
hi-LOOCV@L2c1 with n28 min90.5 max175.9 mean141.1 median145.0 std25.9 best-iNshh(48,75,17,183,176*)
hi-LOOCV@L2c2 with n7 min128.8 max234.0 mean209.9 median232.8 std36.3 best-iNshh(88,75,23,69,234*)
hi-LOOCV@L2c3 with n16 min97.0 max189.3 mean165.2 median177.4 std30.1 best-iNshh(84,50,0,65,189*)

#Wed Jun 10 18:02:54 JST 2020 TP0=2200 N:50,75,100 ns=33 ==>(hV,hg)=(193,316) 267L0
h(yi,yg)@L0c0 with n98 min86.0 max316.0 mean177.9 median165.5 std53.0 best-iNshh(1,50,13,316*,182)
h(yi,yg)@L2c0 with n6 min103.0 max135.0 mean108.8 median103.5 std11.7 best-iNshh(88,50,7,135*,111)
h(yi,yg)@L2c1 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(97,50,30,86*,-1)
h(yi,yg)@L2c2 with n49 min99.0 max291.0 mean172.5 median179.0 std43.8 best-iNshh(15,75,29,291*,172)
h(yi,yg)@L2c3 with n40 min158.0 max316.0 mean201.4 median166.0 std51.2 best-iNshh(1,50,13,316*,206)
hi-LOOCV@L0c0 with n98 min82.1 max183.1 mean157.8 median165.9 std22.6 best-iNshh(14,100,6,267,183*)
hi-LOOCV@L2c0 with n6 min111.2 max169.8 mean151.9 median155.1 std19.7 best-iNshh(92,50,5,103,170*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(97,50,30,86,-1*)
hi-LOOCV@L2c2 with n49 min95.7 max196.6 mean171.3 median171.7 std17.2 best-iNshh(18,75,23,193,197*)
hi-LOOCV@L2c3 with n40 min172.0 max216.6 mean197.1 median198.3 std11.0 best-iNshh(12,50,4,166,217*)

#Wed Jun 10 17:50:29 JST 2020 TP0=2100 N:50,75,100 ns=33 ==>(hV,hg)=(205,359)
h(yi,yg)@L0c0 with n97 min54.0 max359.0 mean135.7 median98.0 std68.0 best-iNshh(18,75,28,359*,139)
h(yi,yg)@L2c0 with n40 min86.0 max98.0 mean91.4 median91.0 std2.3 best-iNshh(94,100,18,98*,96)(95,100,9,98*,96)
h(yi,yg)@L2c1 with n56 min96.0 max359.0 mean168.8 median148.0 std73.4 best-iNshh(18,75,28,359*,176)
h(yi,yg)@L2c2 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(96,50,31,54*,-1)
hi-LOOCV@L0c0 with n97 min53.8 max148.8 mean127.4 median131.5 std15.5 best-iNshh(14,75,3,205,149*)
hi-LOOCV@L2c0 with n40 min95.9 max219.0 mean182.2 median195.7 std32.2 best-iNshh(26,100,17,93,219*)
hi-LOOCV@L2c1 with n56 min99.2 max192.9 mean159.2 median164.1 std25.6 best-iNshh(14,75,3,205,193*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(96,50,31,54,-1*)

#Wed Jun 10 17:42:33 JST 2020 TP0=2000 N:50,75,100 ns=33 ==>(hV,hg)=(332,333)
h(yi,yg)@L0c0 with n95 min19.0 max333.0 mean159.5 median159.0 std66.0 best-iNshh(26,75,12,333*,164)
h(yi,yg)@L2c0 with n81 min71.0 max333.0 mean178.3 median182.0 std47.6 best-iNshh(26,75,12,333*,184)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(93,75,22,20*,-1)
h(yi,yg)@L2c2 with n11 min21.0 max193.0 mean59.2 median30.0 std53.9 best-iNshh(22,75,4,193*,133)
h(yi,yg)@L2c3 with n1 min19.0 max19.0 mean19.0 median19.0 std0.0 best-iNshh(94,75,27,19*,-1)
hi-LOOCV@L0c0 with n95 min21.9 max165.5 mean132.4 median149.9 std38.4 best-iNshh(28,100,29,332,165*)
hi-LOOCV@L2c0 with n81 min69.4 max185.6 mean159.5 median167.8 std25.2 best-iNshh(28,100,29,332,186*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(93,75,22,20,-1*)
hi-LOOCV@L2c2 with n11 min104.8 max142.9 mean124.5 median125.0 std11.8 best-iNshh(87,50,27,29,143*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(94,75,27,19,-1*)

#N:50,100 ns=50
#Wed Jun 10 17:30:20 JST 2020 TP0=2900 N:50,100 ns=50 ==>(hV,hg)=(213,370)
h(yi,yg)@L0c0 with n98 min36.0 max370.0 mean148.9 median157.5 std66.4 best-iNshh(23,100,16,370*,136)
h(yi,yg)@L2c0 with n30 min70.0 max77.0 mean74.0 median74.0 std1.7 best-iNshh(87,50,41,77*,94)(90,100,31,77*,98)(92,100,11,77*,98)(94,100,2,77*,98)
h(yi,yg)@L2c1 with n67 min76.0 max370.0 mean184.1 median190.0 std50.1 best-iNshh(23,100,16,370*,166)
h(yi,yg)@L2c2 with n1 min36.0 max36.0 mean36.0 median36.0 std0.0 best-iNshh(97,50,20,36*,-1)
hi-LOOCV@L0c0 with n98 min36.2 max162.2 mean125.4 median125.6 std24.4 best-iNshh(2,50,38,213,162*)
hi-LOOCV@L2c0 with n30 min93.8 max212.3 mean170.8 median184.7 std37.5 best-iNshh(60,100,46,75,212*)
hi-LOOCV@L2c1 with n67 min76.7 max203.7 mean165.2 median171.9 std30.0 best-iNshh(2,50,38,213,204*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(97,50,20,36,-1*)

#Wed Jun 10 17:22:59 JST 2020 TP0=2800 N:50,100 ns=50 ==>(hV,hg)=(198,349)
h(yi,yg)@L0c0 with n100 min48.0 max349.0 mean161.3 median167.5 std64.9 best-iNshh(5,50,1,349*,155)
h(yi,yg)@L2c0 with n61 min78.0 max349.0 mean179.7 median170.0 std55.2 best-iNshh(5,50,1,349*,174)
h(yi,yg)@L2c1 with n28 min63.0 max275.0 mean164.0 median168.5 std54.6 best-iNshh(15,50,49,275*,184)
h(yi,yg)@L2c2 with n6 min48.0 max52.0 mean51.0 median51.5 std1.4 best-iNshh(90,50,32,52*,154)(91,50,21,52*,144)(97,50,31,52*,137)
h(yi,yg)@L2c3 with n5 min53.0 max55.0 mean53.8 median54.0 std0.7 best-iNshh(92,50,7,55*,125)
hi-LOOCV@L0c0 with n100 min51.0 max163.6 mean131.1 median145.4 std33.8 best-iNshh(28,100,14,259,164*)
hi-LOOCV@L2c0 with n61 min77.5 max188.0 mean158.9 median157.6 std22.8 best-iNshh(38,100,29,198,188*)
hi-LOOCV@L2c1 with n28 min79.9 max192.7 mean162.3 median174.5 std32.5 best-iNshh(35,100,23,167,193*)
hi-LOOCV@L2c2 with n6 min99.2 max154.2 mean137.5 median140.3 std18.5 best-iNshh(89,100,37,51,154*)
hi-LOOCV@L2c3 with n5 min107.0 max178.2 mean131.0 median124.5 std24.5 best-iNshh(94,50,41,54,178*)

#Wed Jun 10 17:15:06 JST 2020 TP0=2700 N:50,100 ns=50 ==>(hV,hg)=(174,269)
h(yi,yg)@L0c0 with n98 min85.0 max269.0 mean154.1 median149.0 std48.3 best-iNshh(29,100,10,269*,150)
h(yi,yg)@L2c0 with n13 min89.0 max118.0 mean112.8 median115.0 std7.2 best-iNshh(73,50,46,118*,191)
h(yi,yg)@L2c1 with n72 min89.0 max269.0 mean173.3 median171.0 std41.5 best-iNshh(29,100,10,269*,168)
h(yi,yg)@L2c2 with n7 min85.0 max88.0 mean86.4 median86.0 std0.9 best-iNshh(90,50,28,88*,199)
h(yi,yg)@L2c3 with n6 min85.0 max102.0 mean92.3 median89.5 std7.0 best-iNshh(83,100,42,102*,195)(84,100,29,102*,180)
hi-LOOCV@L0c0 with n98 min90.0 max158.5 mean136.2 median147.1 std20.7 best-iNshh(6,50,12,174,158*)
hi-LOOCV@L2c0 with n13 min92.8 max214.8 mean176.1 median188.9 std35.3 best-iNshh(68,100,34,117,215*)
hi-LOOCV@L2c1 with n72 min90.5 max178.7 mean163.6 median166.8 std13.5 best-iNshh(6,50,12,174,179*)
hi-LOOCV@L2c2 with n7 min145.5 max199.0 mean184.0 median197.5 std18.9 best-iNshh(94,50,36,86,199*)
hi-LOOCV@L2c3 with n6 min125.8 max197.8 mean169.7 median185.4 std30.3 best-iNshh(86,50,29,89,198*)

#Wed Jun 10 17:06:47 JST 2020 TP0=2600 N:50,100 ns=50 ==>(hV,hg)=(185,310)
h(yi,yg)@L0c0 with n99 min48.0 max310.0 mean168.9 median156.0 std40.6 best-iNshh(9,50,40,310*,171)
h(yi,yg)@L2c0 with n54 min129.0 max310.0 mean185.7 median183.0 std38.3 best-iNshh(9,50,40,310*,190)
h(yi,yg)@L2c1 with n14 min124.0 max128.0 mean125.5 median125.5 std1.3 best-iNshh(83,50,15,128*,135)
h(yi,yg)@L2c2 with n1 min125.0 max125.0 mean125.0 median125.0 std0.0 best-iNshh(93,50,7,125*,-1)
h(yi,yg)@L2c3 with n28 min48.0 max277.0 mean163.2 median151.5 std35.3 best-iNshh(12,50,10,277*,165)
hi-LOOCV@L0c0 with n99 min84.0 max188.0 mean161.9 median165.8 std17.4 best-iNshh(0,50,27,185,188*)
hi-LOOCV@L2c0 with n54 min147.5 max214.2 mean182.2 median183.5 std16.8 best-iNshh(0,50,27,185,214*)
hi-LOOCV@L2c1 with n14 min135.3 max220.8 mean190.0 median193.6 std23.2 best-iNshh(85,50,19,127,221*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(93,50,7,125,-1*)
hi-LOOCV@L2c3 with n28 min152.3 max205.9 mean180.3 median179.1 std12.0 best-iNshh(34,100,11,149,206*)

#Wed Jun 10 16:58:58 JST 2020 TP0=2500 N:50,100 ns=50 ==>(hV,hg)=(247,355)
h(yi,yg)@L0c0 with n99 min102.0 max355.0 mean197.0 median192.0 std60.1 best-iNshh(5,50,18,355*,200)
h(yi,yg)@L2c0 with n69 min114.0 max355.0 mean225.2 median225.0 std50.2 best-iNshh(5,50,18,355*,230)
h(yi,yg)@L2c1 with n28 min105.0 max138.0 mean134.1 median135.5 std5.9 best-iNshh(59,50,14,138*,191)(91,100,21,138*,181)(94,100,10,138*,156)
h(yi,yg)@L2c2 with n1 min102.0 max102.0 mean102.0 median102.0 std0.0 best-iNshh(98,50,25,102*,-1)
hi-LOOCV@L0c0 with n99 min102.1 max206.8 mean174.4 median174.6 std23.4 best-iNshh(34,100,22,247,207*)
hi-LOOCV@L2c0 with n69 min145.5 max239.0 mean207.8 median212.2 std25.3 best-iNshh(34,100,22,247,239*)
hi-LOOCV@L2c1 with n28 min118.0 max245.3 mean210.0 median220.4 std32.6 best-iNshh(73,100,45,136,245*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(98,50,25,102,-1*)

#Wed Jun 10 16:50:59 JST 2020 TP0=2400 N:50,100 ns=50 ==>(hV,hg)=(202,355)
h(yi,yg)@L0c0 with n99 min53.0 max355.0 mean141.8 median158.0 std77.0 best-iNshh(49,100,22,355*,139)
h(yi,yg)@L2c0 with n6 min54.0 max76.0 mean65.0 median66.0 std6.6 best-iNshh(90,50,14,76*,101)
h(yi,yg)@L2c1 with n28 min56.0 max64.0 mean61.1 median61.0 std2.3 best-iNshh(67,100,29,64*,132)(74,100,42,64*,121)(75,100,14,64*,117)(76,100,31,64*,120)(77,100,44,64*,113)(79,50,27,64*,132)(82,50,42,64*,129)
h(yi,yg)@L2c2 with n48 min53.0 max322.0 mean166.8 median172.0 std61.7 best-iNshh(40,100,7,322*,175)
h(yi,yg)@L2c3 with n17 min173.0 max355.0 mean231.1 median230.0 std35.0 best-iNshh(49,100,22,355*,224)
hi-LOOCV@L0c0 with n99 min54.4 max150.3 mean110.6 median114.2 std27.7 best-iNshh(26,100,16,228,150*)
hi-LOOCV@L2c0 with n6 min60.2 max128.2 mean91.5 median90.3 std22.2 best-iNshh(88,50,33,67,128*)
hi-LOOCV@L2c1 with n28 min100.5 max185.6 mean143.5 median149.0 std24.7 best-iNshh(69,50,43,62,186*)
hi-LOOCV@L2c2 with n48 min56.8 max186.8 mean162.1 median170.4 std25.4 best-iNshh(21,100,2,202,187*)
hi-LOOCV@L2c3 with n17 min176.6 max265.2 mean237.7 median247.4 std23.4 best-iNshh(65,100,33,232,265*)


#Wed Jun 10 16:43:19 JST 2020 TP0=2300 N:50,100 ns=50 ==>(hV,hg)=(167,362)
h(yi,yg)@L0c0 with n97 min64.0 max362.0 mean134.9 median148.0 std55.5 best-iNshh(39,50,18,362*,127)
h(yi,yg)@L2c0 with n20 min64.0 max68.0 mean66.5 median67.0 std1.0 best-iNshh(73,100,33,68*,190)(93,50,9,68*,107)
h(yi,yg)@L2c1 with n5 min68.0 max69.0 mean68.4 median68.0 std0.5 best-iNshh(91,100,46,69*,211)(92,100,9,69*,202)
h(yi,yg)@L2c2 with n38 min88.0 max362.0 mean152.6 median158.0 std44.0 best-iNshh(39,50,18,362*,147)
h(yi,yg)@L2c3 with n34 min79.0 max302.0 mean165.3 median167.0 std44.3 best-iNshh(18,50,20,302*,166)
hi-LOOCV@L0c0 with n97 min73.8 max143.5 mean114.3 median118.2 std20.6 best-iNshh(0,50,39,167,143*)
hi-LOOCV@L2c0 with n20 min97.1 max209.5 mean175.3 median192.6 std36.1 best-iNshh(69,50,46,67,209*)
hi-LOOCV@L2c1 with n5 min129.8 max211.0 mean187.4 median201.5 std30.5 best-iNshh(59,50,13,68,211*)
hi-LOOCV@L2c2 with n38 min90.5 max159.4 mean139.6 median147.1 std19.4 best-iNshh(13,100,48,167,159*)
hi-LOOCV@L2c3 with n34 min124.6 max201.6 mean168.4 median175.4 std22.6 best-iNshh(8,100,17,167,202*)

#Wed Jun 10 16:31:28 JST 2020 TP0=2200 N:50,100 ns=50 ==>(hV,hg)=(267,430)
h(yi,yg)@L0c0 with n100 min44.0 max430.0 mean172.3 median164.0 std55.8 best-iNshh(1,50,43,430*,171)
h(yi,yg)@L2c0 with n7 min96.0 max124.0 mean105.1 median103.0 std8.1 best-iNshh(89,100,44,124*,122)
h(yi,yg)@L2c1 with n92 min86.0 max430.0 mean178.8 median165.5 std53.0 best-iNshh(1,50,43,430*,178)
h(yi,yg)@L2c2 with n1 min44.0 max44.0 mean44.0 median44.0 std0.0 best-iNshh(99,100,35,44*,-1)
hi-LOOCV@L0c0 with n100 min43.8 max174.9 mean152.6 median162.4 std24.4 best-iNshh(49,100,6,267,175*)
hi-LOOCV@L2c0 with n7 min72.7 max149.7 mean117.1 median121.8 std29.7 best-iNshh(91,50,5,103,150*)
hi-LOOCV@L2c1 with n92 min82.6 max181.7 mean162.9 median170.4 std18.9 best-iNshh(49,100,6,267,182*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(99,100,35,44,-1*)

#Wed Jun 10 16:21:24 JST 2020 TP0=2000 N:50,100 ns=50 ==>(hV,hg)=(219,332)
h(yi,yg)@L0c0 with n96 min13.0 max332.0 mean158.6 median158.0 std66.8 best-iNshh(7,50,33,332*,157)(25,100,29,332*,159)
h(yi,yg)@L2c0 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(92,50,15,20*,-1)
h(yi,yg)@L2c1 with n4 min13.0 max21.0 mean17.2 median17.5 std3.8 best-iNshh(90,50,22,21*,30)(93,50,34,21*,30)
h(yi,yg)@L2c2 with n8 min29.0 max158.0 mean83.9 median97.0 std45.8 best-iNshh(29,50,46,158*,130)
h(yi,yg)@L2c3 with n81 min71.0 max332.0 mean178.1 median172.0 std49.5 best-iNshh(7,50,33,332*,177)(25,100,29,332*,179)
hi-LOOCV@L0c0 with n96 min15.7 max162.4 mean131.0 median147.4 std39.0 best-iNshh(27,100,43,219,162*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(92,50,15,20,-1*)
hi-LOOCV@L2c1 with n4 min30.0 max85.7 mean57.7 median57.5 std27.7 best-iNshh(94,50,45,14,86*)
hi-LOOCV@L2c2 with n8 min89.3 max141.4 mean128.2 median133.3 std15.7 best-iNshh(87,50,19,30,141*)
hi-LOOCV@L2c3 with n81 min71.2 max181.3 mean161.2 median170.6 std21.7 best-iNshh(27,100,43,219,181*)

#Wed Jun 10 16:12:20 JST 2020 TP0=2100 N:50,100 ns=50 ==>(hV,hg)=(268,357)
h(yi,yg)@L0c0 with n97 min54.0 max357.0 mean132.9 median98.0 std62.5 best-iNshh(13,100,16,357*,136)
h(yi,yg)@L2c0 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(96,50,31,54*,-1)
h(yi,yg)@L2c2 with n47 min86.0 max98.0 mean91.8 median92.0 std2.1 best-iNshh(93,100,18,98*,96)(94,100,9,98*,96)
h(yi,yg)@L2c3 with n49 min96.0 max357.0 mean173.8 median175.0 std65.7 best-iNshh(13,100,16,357*,182)
hi-LOOCV@L0c0 with n97 min53.8 max159.8 mean129.4 median130.9 std18.2 best-iNshh(19,100,17,93,160*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(96,50,31,54,-1*)
hi-LOOCV@L2c2 with n47 min95.9 max236.3 mean193.2 median203.5 std35.8 best-iNshh(20,100,47,93,236*)
hi-LOOCV@L2c3 with n49 min97.4 max183.2 mean154.2 median162.8 std23.0 best-iNshh(41,50,1,268,183*)

#Wed Jun 10 16:03:55 JST 2020 TP0=2100 N:50_N:100 ns=40_50 ==>(hV,hg)=(93,237)
h(yi,yg)@L0c0 with n88 min54.0 max357.0 mean132.0 median96.0 std63.2 best-iNshh(13,100,16,357*,133)
h(yi,yg)@L2c0 with n42 min96.0 max357.0 mean177.0 median175.0 std66.9 best-iNshh(13,100,16,357*,182)
h(yi,yg)@L2c1 with n45 min86.0 max98.0 mean91.8 median92.0 std2.2 best-iNshh(85,100,9,98*,96)(86,100,18,98*,96)
h(yi,yg)@L2c2 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(87,50,31,54*,-1)
hi-LOOCV@L0c0 with n88 min53.8 max164.1 mean129.9 median128.5 std20.2 best-iNshh(18,100,47,93,164*)
hi-LOOCV@L2c0 with n42 min97.9 max182.3 mean152.7 median162.5 std23.2 best-iNshh(39,50,1,268,182*)
hi-LOOCV@L2c1 with n45 min96.0 max237.2 mean192.8 median202.3 std36.5 best-iNshh(18,100,47,93,237*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(87,50,31,54,-1*)

#Wed Jun 10 15:41:57 JST 2020 TP0=2100 N:50_N:100 ns=30_50 ==>(hV,hg)=(93,357)
h(yi,yg)@L0c0 with n78 min86.0 max357.0 mean131.5 median95.0 std64.2 best-iNshh(8,100,16,357*,133)
h(yi,yg)@L2c0 with n5 min96.0 max116.0 mean101.0 median98.0 std7.5 best-iNshh(72,50,19,116*,128)
h(yi,yg)@L2c1 with n31 min98.0 max357.0 mean190.3 median177.0 std67.9 best-iNshh(8,100,16,357*,197)
h(yi,yg)@L2c2 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(77,100,9,98*,-1)
h(yi,yg)@L2c3 with n39 min89.0 max96.0 mean91.6 median91.0 std1.5 best-iNshh(70,100,39,96*,122)
hi-LOOCV@L0c0 with n78 min98.0 max165.9 mean132.0 median128.8 std20.0 best-iNshh(15,100,47,93,166*)
hi-LOOCV@L2c0 with n5 min119.0 max153.5 mean133.7 median127.8 std13.4 best-iNshh(69,100,24,97,154*)
hi-LOOCV@L2c1 with n31 min111.8 max197.3 mean168.1 median173.0 std20.3 best-iNshh(36,50,1,268,197*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(77,100,9,98,-1*)
hi-LOOCV@L2c3 with n39 min121.6 max243.3 mean205.6 median219.3 std29.4 best-iNshh(15,100,47,93,243*)xxx

#Wed Jun 10 15:31:58 JST 2020 TP0=2500 N:50_N:100 ns=25_50 ==>(hV,hg)=(247,355)
h(yi,yg)@L0c0 with n75 min114.0 max355.0 mean202.4 median193.0 std60.3 best-iNshh(3,50,18,355*,205)
h(yi,yg)@L2c0 with n48 min140.0 max355.0 mean238.1 median247.0 std45.5 best-iNshh(3,50,18,355*,242)
h(yi,yg)@L2c1 with n5 min114.0 max164.0 mean151.4 median160.0 std18.8 best-iNshh(57,50,10,164*,190)
h(yi,yg)@L2c2 with n12 min136.0 max138.0 mean136.8 median137.0 std0.8 best-iNshh(48,50,14,138*,258)(66,100,21,138*,234)(73,100,10,138*,181)
h(yi,yg)@L2c3 with n10 min133.0 max139.0 mean135.1 median135.0 std1.6 best-iNshh(71,100,11,139*,138)
hi-LOOCV@L0c0 with n75 min136.6 max217.6 mean182.8 median181.6 std22.1 best-iNshh(13,100,22,247,218*)
hi-LOOCV@L2c0 with n48 min154.7 max261.6 mean228.0 median236.4 std24.4 best-iNshh(13,100,22,247,262*)*
hi-LOOCV@L2c1 with n5 min190.2 max264.5 mean234.0 median229.5 std26.9 best-iNshh(74,50,9,114,264*)
hi-LOOCV@L2c2 with n12 min180.8 max300.2 mean263.8 median272.8 std31.1 best-iNshh(60,100,3,137,300*)
hi-LOOCV@L2c3 with n10 min138.0 max228.9 mean212.4 median225.7 std27.9 best-iNshh(69,100,15,136,229*)

#Wed Jun 10 15:23:46 JST 2020 TP0=2400 N:50_N:100 ns=25_50 ==>(hV,hg)=(202,355)
h(yi,yg)@L0c0 with n74 min53.0 max355.0 mean153.3 median171.5 std78.9 best-iNshh(38,100,22,355*,150)
h(yi,yg)@L2c0 with n13 min218.0 max355.0 mean240.2 median232.0 std33.5 best-iNshh(38,100,22,355*,232)
h(yi,yg)@L2c1 with n37 min68.0 max322.0 mean182.1 median199.0 std56.0 best-iNshh(25,100,7,322*,182)
h(yi,yg)@L2c2 with n18 min56.0 max76.0 mean61.9 median61.0 std4.1 best-iNshh(69,50,14,76*,64)
h(yi,yg)@L2c3 with n6 min53.0 max64.0 mean62.2 median64.0 std4.1 best-iNshh(51,100,44,64*,113)(52,100,14,64*,125)(54,100,29,64*,141)(59,100,42,64*,152)(60,100,31,64*,152)
hi-LOOCV@L0c0 with n74 min54.3 max158.5 mean115.7 median119.4 std30.3 best-iNshh(12,100,16,228,158*)*betterinL0
hi-LOOCV@L2c0 with n13 min227.2 max280.1 mean260.1 median262.8 std15.7 best-iNshh(67,100,1,232,280*)*better result
hi-LOOCV@L2c1 with n37 min115.4 max195.3 mean170.6 median180.0 std22.3 best-iNshh(11,100,2,202,195*)***?
hi-LOOCV@L2c2 with n18 min64.2 max170.0 mean139.0 median158.6 std38.0 best-iNshh(57,50,16,61,170*)
hi-LOOCV@L2c3 with n6 min52.0 max152.2 mean122.7 median133.4 std34.6 best-iNshh(59,100,42,64,152*)

#Wed Jun 10 15:17:16 JST 2020 TP0=2300 N:50_N:100 ns=25_50 ==>(hV,hg)=(188,362)
h(yi,yg)@L0c0 with n73 min64.0 max362.0 mean136.7 median155.0 std57.9 best-iNshh(29,50,18,362*,127)
h(yi,yg)@L2c0 with n22 min79.0 max302.0 mean166.6 median167.0 std50.3 best-iNshh(13,50,20,302*,169)
h(yi,yg)@L2c1 with n32 min91.0 max362.0 mean157.6 median158.5 std44.4 best-iNshh(29,50,18,362*,151)
h(yi,yg)@L2c2 with n15 min64.0 max68.0 mean66.4 median67.0 std1.1 best-iNshh(56,100,33,68*,185)(69,50,9,68*,106)
h(yi,yg)@L2c3 with n4 min68.0 max69.0 mean68.5 median68.5 std0.5 best-iNshh(67,100,46,69*,212)(68,100,9,69*,205)
hi-LOOCV@L0c0 with n73 min73.6 max144.2 mean113.4 median116.6 std21.0 best-iNshh(1,50,14,167,144*)
hi-LOOCV@L2c0 with n22 min118.9 max204.6 mean172.3 median180.2 std25.6 best-iNshh(3,100,17,167,205*)
hi-LOOCV@L2c1 with n32 min92.3 max165.0 mean145.9 median156.0 std18.7 best-iNshh(10,100,21,188,165*)***
hi-LOOCV@L2c2 with n15 min97.1 max190.5 mean162.9 median183.4 std33.3 best-iNshh(54,100,38,67,190*)
hi-LOOCV@L2c3 with n4 min128.7 max212.7 mean189.7 median208.7 std35.4 best-iNshh(45,50,13,68,213*)

#Wed Jun 10 15:06:23 JST 2020 TP0=2200 N:50_N:100 ns=25_50 ==>(hV,hg)=(267,316)
h(yi,yg)@L0c0 with n75 min44.0 max316.0 mean174.3 median165.0 std51.9 best-iNshh(1,50,13,316*,180)
h(yi,yg)@L2c0 with n69 min89.0 max316.0 mean181.1 median166.0 std47.9 best-iNshh(1,50,13,316*,187)
h(yi,yg)@L2c1 with n5 min96.0 max124.0 mean106.0 median103.0 std9.4 best-iNshh(67,100,44,124*,120)
h(yi,yg)@L2c2 with n1 min44.0 max44.0 mean44.0 median44.0 std0.0 best-iNshh(74,100,35,44*,-1)
hi-LOOCV@L0c0 with n75 min43.8 max179.9 mean155.8 median168.8 std26.0 best-iNshh(37,100,6,267,180*)*sameinL0
hi-LOOCV@L2c0 with n69 min87.0 max187.3 mean167.0 median176.3 std19.6 best-iNshh(37,100,6,267,187*)
hi-LOOCV@L2c1 with n5 min79.0 max141.2 mean119.6 median120.2 std22.2 best-iNshh(69,50,5,103,141*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(74,100,35,44,-1*)

#Wed Jun 10 14:57:57 JST 2020 TP0=2100 N:50_N:100 ns=25_50 ==>(hV,hg)=(357,357)
h(yi,yg)@L0c0 with n73 min86.0 max357.0 mean131.3 median96.0 std64.2 best-iNshh(7,100,16,357*,133)
h(yi,yg)@L2c0 with n5 min96.0 max116.0 mean101.0 median98.0 std7.5 best-iNshh(68,50,19,116*,128)
h(yi,yg)@L2c1 with n29 min98.0 max357.0 mean189.5 median177.0 std68.6 best-iNshh(7,100,16,357*,197)
h(yi,yg)@L2c2 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(71,100,9,98*,-1)
h(yi,yg)@L2c3 with n36 min89.0 max96.0 mean91.7 median92.0 std1.6 best-iNshh(64,100,39,96*,123)
hi-LOOCV@L0c0 with n73 min98.1 max166.3 mean131.7 median128.2 std20.4 best-iNshh(17,100,47,93,166*)*bad
hi-LOOCV@L2c0 with n5 min119.0 max153.5 mean133.7 median127.8 std13.4 best-iNshh(62,100,24,97,154*)
hi-LOOCV@L2c1 with n29 min112.9 max197.0 mean167.7 median173.9 std20.1 best-iNshh(7,100,16,357,197*)**better in L2
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(71,100,9,98,-1*)
hi-LOOCV@L2c3 with n36 min123.2 max246.4 mean207.4 median222.1 std31.4 best-iNshh(17,100,47,93,246*) *bad


##############
#Wed Jun 10 14:39:38 JST 2020 TP0=2000 N:50 ns=40  ==>(hV,hg)=(220,332)
#                             tp0=2000 N:50 ns=50  ==>(hV,hg)=(304,332) ***
#                             TP0=2000 N:100 ns=50 ==>(hV,hg)=(219,492)
#TP0=2000 N:50,100 ==>(hV,hg)=(219,492) same as N:100 ? worse
#Wed Jun 10 13:06:08 JST 2020 TP0=2000 N:50_N:100 ns=50_10 ==>(hV,hg)=(188,332)
#Wed Jun 10 12:47:59 JST 2020 TP0=2000 N:50_N:100 ns=30_50 ==>(hV,hg)=(188,332)
#Wed Jun 10 11:49:00 JST 2020 TP0=2000 N:50_N:100 ns=25_50 ==>(hV,hg)=(219,332) ***?
#Wed Jun 10 12:57:50 JST 2020 TP0=2000 N:50_N:100 ns=10_50 ==>(hV,hg)=(219,332)
#Wed Jun 10 14:26:09 JST 2020 TP0=2000 N:50_N:100 ns=50_1 ==>(hV,hg)=(304,332) (182,332)
#Wed Jun 10 14:39:38 JST 2020 TP0=2000 N:50 ns=40 ==>(hV,hg)=(220,332)
h(yi,yg)@L0c0 with n38 min19.0 max332.0 mean142.0 median145.0 std71.5 best-iNshh(31,50,33,332*,135)
h(yi,yg)@L2c0 with n31 min71.0 max332.0 mean166.3 median157.0 std53.8 best-iNshh(31,50,33,332*,159)
h(yi,yg)@L2c1 with n1 min29.0 max29.0 mean29.0 median29.0 std0.0 best-iNshh(25,50,27,29*,-1)
h(yi,yg)@L2c2 with n1 min21.0 max21.0 mean21.0 median21.0 std0.0 best-iNshh(32,50,34,21*,-1)
h(yi,yg)@L2c3 with n1 min19.0 max19.0 mean19.0 median19.0 std0.0 best-iNshh(35,50,37,19*,-1)
hi-LOOCV@L0c0 with n38 min20.7 max139.0 mean110.4 median126.8 std37.0 best-iNshh(30,50,32,220,139*)
hi-LOOCV@L2c0 with n31 min72.3 max163.4 mean145.3 median148.7 std20.8 best-iNshh(30,50,32,220,163*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(25,50,27,29,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(32,50,34,21,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(35,50,37,19,-1*)
#Wed Jun 10 14:36:16 JST 2020 TP0=2000 N:50_N:100 ns=40_1 ==>(hV,hg)=(189,332)
h(yi,yg)@L0c0 with n39 min19.0 max332.0 mean143.2 median146.0 std71.0 best-iNshh(5,50,33,332*,137)
h(yi,yg)@L2c0 with n32 min71.0 max332.0 mean167.0 median157.5 std53.1 best-iNshh(5,50,33,332*,160)
h(yi,yg)@L2c1 with n1 min29.0 max29.0 mean29.0 median29.0 std0.0 best-iNshh(33,50,27,29*,-1)
h(yi,yg)@L2c2 with n1 min21.0 max21.0 mean21.0 median21.0 std0.0 best-iNshh(36,50,22,21*,-1)
h(yi,yg)@L2c3 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(38,50,15,20*,-1)
hi-LOOCV@L0c0 with n39 min20.7 max141.7 mean111.8 median127.4 std37.4 best-iNshh(1,50,21,189,142*)
hi-LOOCV@L2c0 with n32 min72.3 max165.6 mean146.3 median150.2 std21.2 best-iNshh(1,50,21,189,166*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(33,50,27,29,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(36,50,22,21,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(38,50,15,20,-1*)

#Wed Jun 10 14:26:09 JST 2020 TP0=2000 N:50_N:100 ns=50_1 ==>(hV,hg)=(304,332) (182,332)
h(yi,yg)@L0c0 with n49 min14.0 max332.0 mean145.8 median156.0 std71.2 best-iNshh(8,50,33,332*,140)
h(yi,yg)@L2c0 with n41 min71.0 max332.0 mean168.2 median158.0 std53.6 best-iNshh(8,50,33,332*,162)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(46,50,15,20*,-1)
h(yi,yg)@L2c2 with n4 min21.0 max94.0 mean43.5 median29.5 std29.4 best-iNshh(41,50,44,94*,91)
h(yi,yg)@L2c3 with n1 min14.0 max14.0 mean14.0 median14.0 std0.0 best-iNshh(48,50,45,14*,-1)
hi-LOOCV@L0c0 with n49 min14.0 max148.7 mean113.2 median129.6 std37.7 best-iNshh(7,50,47,304,149*)
hi-LOOCV@L2c0 with n41 min72.4 max165.6 mean146.3 median152.0 std20.6 best-iNshh(3,50,28,182,166*)(7,50,47,304,166*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(46,50,15,20,-1*)
hi-LOOCV@L2c2 with n4 min91.0 max126.0 mean113.0 median117.5 std14.0 best-iNshh(44,50,22,21,126*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(48,50,45,14,-1*)

#Wed Jun 10 13:06:08 JST 2020 TP0=2000 N:50_N:100 ns=50_10 ==>(hV,hg)=(188,332)
h(yi,yg)@L0c0 with n58 min14.0 max332.0 mean149.4 median156.5 std66.7 best-iNshh(14,50,33,332*,145)
h(yi,yg)@L2c0 with n49 min71.0 max332.0 mean169.3 median159.0 std49.6 best-iNshh(14,50,33,332*,164)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(55,50,15,20*,-1)
h(yi,yg)@L2c2 with n5 min21.0 max119.0 mean58.6 median30.0 std40.0 best-iNshh(48,50,48,119*,149)
h(yi,yg)@L2c3 with n1 min14.0 max14.0 mean14.0 median14.0 std0.0 best-iNshh(57,50,45,14*,-1)
hi-LOOCV@L0c0 with n58 min14.0 max151.9 mean119.9 median134.1 std37.9 best-iNshh(22,100,4,186,152*)
hi-LOOCV@L2c0 with n49 min71.2 max172.1 mean150.8 median154.7 std21.3 best-iNshh(33,100,3,188,172*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,50,15,20,-1*)
hi-LOOCV@L2c2 with n5 min89.2 max149.0 mean127.4 median140.8 std22.9 best-iNshh(48,50,48,119,149*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(57,50,45,14,-1*)

#Wed Jun 10 12:57:50 JST 2020 TP0=2000 N:50_N:100 ns=10_50 ==>(hV,hg)=(219,332)
h(yi,yg)@L0c0 with n57 min13.0 max332.0 mean172.2 median182.0 std57.9 best-iNshh(8,100,29,332*,172)
h(yi,yg)@L2c0 with n55 min29.0 max332.0 mean177.8 median183.0 std50.5 best-iNshh(8,100,29,332*,178)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(55,100,35,20*,-1)
h(yi,yg)@L2c2 with n1 min13.0 max13.0 mean13.0 median13.0 std0.0 best-iNshh(56,100,45,13*,-1)
hi-LOOCV@L0c0 with n57 min13.3 max180.8 mean152.5 median164.0 std33.4 best-iNshh(3,100,43,219,181*)
hi-LOOCV@L2c0 with n55 min92.2 max186.9 mean162.7 median171.2 std22.3 best-iNshh(3,100,43,219,187*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,100,35,20,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,100,45,13,-1*)

#Wed Jun 10 12:47:59 JST 2020 TP0=2000 N:50_N:100 ns=30_50 ==>(hV,hg)=(188,332)
h(yi,yg)@L0c0 with n76 min13.0 max332.0 mean162.2 median168.5 std62.0 best-iNshh(27,100,29,332*,162)
h(yi,yg)@L2c0 with n6 min21.0 max112.0 mean53.5 median29.5 std37.4 best-iNshh(64,100,44,112*,129)
h(yi,yg)@L2c1 with n1 min13.0 max13.0 mean13.0 median13.0 std0.0 best-iNshh(75,100,45,13*,-1)
h(yi,yg)@L2c2 with n67 min98.0 max332.0 mean178.5 median182.0 std44.5 best-iNshh(27,100,29,332*,179)
h(yi,yg)@L2c3 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(74,50,15,20*,-1)
hi-LOOCV@L0c0 with n76 min13.4 max168.4 mean139.9 median154.3 std37.4 best-iNshh(19,100,43,219,168*)
hi-LOOCV@L2c0 with n6 min93.6 max154.2 mean124.0 median124.5 std17.8 best-iNshh(70,50,19,30,154*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(75,100,45,13,-1*)
hi-LOOCV@L2c2 with n67 min101.7 max184.2 mean165.5 median175.3 std19.5 best-iNshh(21,100,8,188,184*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(74,50,15,20,-1*)
#Wed Jun 10 11:49:00 JST 2020 TP0=2000 N:50_N:100 ns=25_50 ==>(hV,hg)=(219,332)
h(yi,yg)@L0c0 with n71 min13.0 max332.0 mean163.2 median168.0 std60.8 best-iNshh(24,100,29,332*,163)
h(yi,yg)@L2c0 with n64 min98.0 max332.0 mean177.2 median177.0 std44.6 best-iNshh(24,100,29,332*,178)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(69,50,15,20*,-1)
h(yi,yg)@L2c2 with n4 min21.0 max112.0 mean48.0 median29.5 std37.1 best-iNshh(62,100,44,112*,111)
h(yi,yg)@L2c3 with n1 min13.0 max13.0 mean13.0 median13.0 std0.0 best-iNshh(70,100,45,13*,-1)
hi-LOOCV@L0c0 with n71 min13.4 max170.2 mean142.0 median156.2 std36.8 best-iNshh(15,100,43,219,170*)
hi-LOOCV@L2c0 with n64 min101.9 max183.2 mean164.3 median171.4 std19.2 best-iNshh(15,100,43,219,183*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(69,50,15,20,-1*)
hi-LOOCV@L2c2 with n4 min104.3 max155.0 mean119.8 median110.0 std20.4 best-iNshh(66,50,19,30,155*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(70,100,45,13,-1*)

#tp0=2000 N:50 ==>(hV,hg)=(304,332)
h(yi,yg)@L2c0 with n40 min71.0 max332.0 mean167.8 median158.0 std54.2 best-iNshh(31,50,33,332*,162)
h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(13,50,15,20*,-1)
h(yi,yg)@L2c2 with n4 min21.0 max94.0 mean43.5 median29.5 std29.4 best-iNshh(42,50,44,94*,91)
h(yi,yg)@L2c3 with n1 min14.0 max14.0 mean14.0 median14.0 std0.0 best-iNshh(43,50,45,14*,-1)
hi-LOOCV@L0c0 with n48 min14.0 max147.9 mean112.1 median128.1 std37.4 best-iNshh(45,50,47,304,148*)
hi-LOOCV@L2c0 with n40 min72.5 max165.1 mean145.5 median151.7 std20.2 best-iNshh(45,50,47,304,165*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(13,50,15,20,-1*)
hi-LOOCV@L2c2 with n4 min91.0 max126.0 mean113.0 median117.5 std14.0 best-iNshh(20,50,22,21,126*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(43,50,45,14,-1*)

#Tue Jun  9 13:10:27 JST 2020 TP0=2000 N:100 ==>(hV,hg)=(219,492)
h(yi,yg)@L0c0 with n98 min13.0 max492.0 mean178.3 median170.5 std69.2 best-iNshh(93,100,95,492*,179)
h(yi,yg)@L2c0 with n37 min29.0 max492.0 mean166.6 median157.0 std73.1 best-iNshh(93,100,95,492*,165)
h(yi,yg)@L2c1 with n57 min126.0 max368.0 mean197.1 median189.0 std50.1 best-iNshh(57,100,59,368*,197)
h(yi,yg)@L2c2 with n1 min17.0 max17.0 mean17.0 median17.0 std0.0 best-iNshh(62,100,64,17*,-1)
h(yi,yg)@L2c3 with n1 min21.0 max21.0 mean21.0 median21.0 std0.0 best-iNshh(95,100,97,21*,-1)
hi-LOOCV@L0c0 with n98 min13.4 max186.6 mean155.7 median166.6 std35.6 best-iNshh(41,100,43,219,187*)
hi-LOOCV@L2c0 with n37 min107.2 max190.4 mean171.8 median181.9 std22.0 best-iNshh(26,100,27,156,190*)
hi-LOOCV@L2c1 with n57 min127.7 max202.8 mean184.8 median194.0 std20.2 best-iNshh(84,100,86,191,203*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(62,100,64,17,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(95,100,97,21,-1*)
#Tue Jun  9 13:00:49 JST 2020 TP0=2000 N:50,100 ==>(hV,hg)=(219,492)
h(yi,yg)@L0c0 with n194 min13.0 max492.0 mean159.6 median157.0 std67.4 best-iNshh(81,100,95,492*,161)
h(yi,yg)@L2c0 with n124 min71.0 max492.0 mean182.5 median176.5 std55.2 best-iNshh(81,100,95,492*,183)
h(yi,yg)@L2c1 with n57 min29.0 max304.0 mean141.7 median146.0 std53.5 best-iNshh(3,50,47,304*,153)(60,100,41,304*,154)
h(yi,yg)@L2c2 with n8 min17.0 max21.0 mean19.2 median19.0 std1.1 best-iNshh(191,50,66,21*,51)
h(yi,yg)@L2c3 with n5 min13.0 max21.0 mean18.0 median21.0 std3.7 best-iNshh(182,50,22,21*,50)(183,100,97,21*,52)(184,50,34,21*,39)
hi-LOOCV@L0c0 with n194 min14.6 max165.1 mean134.8 median152.2 std36.7 best-iNshh(75,100,43,219,165*)
hi-LOOCV@L2c0 with n124 min70.5 max186.9 mean168.2 median177.6 std21.0 best-iNshh(75,100,43,219,187*)
hi-LOOCV@L2c1 with n57 min92.7 max171.8 mean145.5 median149.8 std17.2 best-iNshh(47,100,88,158,172*)
hi-LOOCV@L2c2 with n8 min51.0 max198.1 mean140.7 median175.9 std57.0 best-iNshh(181,100,35,20,198*)
hi-LOOCV@L2c3 with n5 min39.2 max68.0 mean55.4 median52.0 std10.9 best-iNshh(192,50,45,14,68*)

#tp0=2100 N:50 ==>(hV,hg)=(257,268)
h(yi,yg)@L0c0 with n48 min54.0 max268.0 mean144.1 median131.0 std57.7 best-iNshh(1,50,1,268*,151)
h(yi,yg)@L2c0 with n14 min86.0 max94.0 mean91.1 median91.0 std1.8 best-iNshh(35,50,36,94*,184)
h(yi,yg)@L2c1 with n33 min96.0 max268.0 mean169.2 median174.0 std52.6 best-iNshh(1,50,1,268*,181)
h(yi,yg)@L2c2 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(30,50,31,54*,-1)
hi-LOOCV@L0c0 with n48 min53.9 max151.3 mean128.2 median130.1 std19.2 best-iNshh(44,50,46,257,151*)
hi-LOOCV@L2c0 with n14 min112.6 max223.7 mean190.3 median196.9 std30.0 best-iNshh(41,50,43,92,224*)
hi-LOOCV@L2c1 with n33 min93.3 max181.4 mean158.5 median166.7 std22.0 best-iNshh(44,50,46,257,181*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,31,54,-1*)
#tp0=2200 N:50 ==>(hV,hg)=(194,430)
h(yi,yg)@L0c0 with n50 min86.0 max430.0 mean165.6 median159.0 std60.5 best-iNshh(43,50,43,430*,161)
h(yi,yg)@L2c0 with n44 min99.0 max430.0 mean174.9 median161.5 std58.7 best-iNshh(43,50,43,430*,170)
h(yi,yg)@L2c1 with n1 min86.0 max86.0 mean86.0 median86.0 std0.0 best-iNshh(30,50,30,86*,-1)
h(yi,yg)@L2c2 with n1 min103.0 max103.0 mean103.0 median103.0 std0.0 best-iNshh(31,50,31,103*,-1)
h(yi,yg)@L2c3 with n1 min103.0 max103.0 mean103.0 median103.0 std0.0 best-iNshh(35,50,35,103*,-1)
hi-LOOCV@L0c0 with n50 min83.1 max163.8 mean144.4 median151.9 std20.5 best-iNshh(17,50,17,194,164*)
hi-LOOCV@L2c0 with n44 min97.0 max173.2 mean158.1 median161.2 std13.4 best-iNshh(17,50,17,194,173*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,30,86,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(31,50,31,103,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(35,50,35,103,-1*)
###
#TP0=2300 N:40 ==>(hV,hg)=(159,218)
#tp0=2300 N:50 ==>(hV,hg)=(167,362) ***
#TP0=2300 N:55 ==>(hV,hg)=(168,338)
#TP0=2300 N:60 ==>(hV,hg)=(168,361)
#tp0=2300 N:70 ==>(hV,hg)=(168,243)
#tp0=2300 N:100 ==>(hV,hg)=(188,215) *better hV
#TP0=2300 N:50,100 ==>(hV,hg)=(167,362) same as N:50 worse hV
#Wed Jun 10 10:24:48 JST 2020 TP0=2300 N:50_N:100 ns=40_50 ==>(hV,hg)=(167,362)
#Wed Jun 10 10:39:42 JST 2020 TP0=2300 N:50_N:100 ns=30_50 ==>(hV,hg)=(188,362)
#Wed Jun 10 10:06:05 JST 2020 TP0=2300 N:50_N:100 ns=25_50 ==>(hV,hg)=(188,362) ***?
#Wed Jun 10 10:14:30 JST 2020 TP0=2300 N:50_N:100 ns=10_50 ==>(hV,hg)=(188,215)

###
#Wed Jun 10 10:54:51 JST 2020 TP0=2300 N:50_N:100 ns=50_100 ==>(hV,hg)=(188,362)
h(yi,yg)@L0c0 with n147 min64.0 max362.0 mean129.4 median142.0 std55.2 best-iNshh(68,50,18,362*,121)
h(yi,yg)@L2c0 with n40 min64.0 max70.0 mean66.5 median67.0 std1.3 best-iNshh(146,100,86,70*,71)
h(yi,yg)@L2c1 with n8 min68.0 max69.0 mean68.5 median68.5 std0.5 best-iNshh(136,100,65,69*,241)(138,100,46,69*,218)(139,100,9,69*,197)(144,100,89,69*,194)
h(yi,yg)@L2c2 with n55 min88.0 max362.0 mean156.1 median159.0 std38.3 best-iNshh(68,50,18,362*,152)
h(yi,yg)@L2c3 with n44 min79.0 max302.0 mean164.3 median167.0 std44.4 best-iNshh(44,50,20,302*,164)
hi-LOOCV@L0c0 with n147 min73.4 max138.8 mean111.5 median111.0 std17.6 best-iNshh(7,50,14,167,139*)
hi-LOOCV@L2c0 with n40 min71.3 max201.6 mean168.8 median184.1 std32.6 best-iNshh(106,100,53,66,202*)
hi-LOOCV@L2c1 with n8 min129.4 max240.6 mean192.9 median195.2 std32.7 best-iNshh(136,100,65,69,241*)
hi-LOOCV@L2c2 with n55 min89.6 max173.0 mean148.1 median157.0 std20.9 best-iNshh(33,100,21,188,173*)
hi-LOOCV@L2c3 with n44 min92.9 max199.1 mean167.6 median175.2 std24.5 best-iNshh(0,100,17,167,199*)
#Wed Jun 10 10:39:42 JST 2020 TP0=2300 N:50_N:100 ns=30_50 ==>(hV,hg)=(188,362)
h(yi,yg)@L0c0 with n78 min64.0 max362.0 mean134.5 median151.5 std57.5 best-iNshh(29,50,18,362*,126)
h(yi,yg)@L2c0 with n27 min79.0 max302.0 mean155.0 median167.0 std51.9 best-iNshh(7,50,20,302*,157)
h(yi,yg)@L2c1 with n30 min121.0 max362.0 mean163.3 median159.0 std41.9 best-iNshh(29,50,18,362*,157)
h(yi,yg)@L2c2 with n16 min64.0 max68.0 mean66.4 median67.0 std1.1 best-iNshh(56,100,33,68*,186)(74,50,9,68*,106)
h(yi,yg)@L2c3 with n5 min68.0 max69.0 mean68.4 median68.0 std0.5 best-iNshh(69,100,46,69*,211)(72,100,9,69*,202)
hi-LOOCV@L0c0 with n78 min73.8 max142.1 mean112.0 median113.4 std20.2 best-iNshh(1,50,14,167,142*)
hi-LOOCV@L2c0 with n27 min88.5 max184.1 mean148.3 median156.6 std28.0 best-iNshh(6,100,17,167,184*)
hi-LOOCV@L2c1 with n30 min126.4 max173.6 mean157.0 median162.8 std13.8 best-iNshh(12,100,21,188,174*)
hi-LOOCV@L2c2 with n16 min97.1 max196.8 mean167.1 median185.8 std34.5 best-iNshh(53,50,29,67,197*)
hi-LOOCV@L2c3 with n5 min129.8 max211.0 mean187.4 median201.5 std30.5 best-iNshh(45,50,13,68,211*)

#Wed Jun 10 10:24:48 JST 2020 TP0=2300 N:50_N:100 ns=40_50 ==>(hV,hg)=(167,362)
h(yi,yg)@L0c0 with n87 min64.0 max362.0 mean134.0 median148.0 std56.1 best-iNshh(34,50,18,362*,126)
h(yi,yg)@L2c0 with n60 min79.0 max362.0 mean162.5 median166.0 std43.6 best-iNshh(34,50,18,362*,152)
h(yi,yg)@L2c1 with n4 min88.0 max94.0 mean91.8 median92.5 std2.5 best-iNshh(71,100,23,94*,147)(72,50,30,94*,152)
h(yi,yg)@L2c2 with n18 min64.0 max68.0 mean66.4 median67.0 std1.0 best-iNshh(64,100,33,68*,188)(83,50,9,68*,106)
h(yi,yg)@L2c3 with n5 min68.0 max69.0 mean68.4 median68.0 std0.5 best-iNshh(80,100,46,69*,211)(82,100,9,69*,202)
hi-LOOCV@L0c0 with n87 min73.8 max143.6 mean112.9 median115.1 std20.7 best-iNshh(0,50,39,167,144*)
hi-LOOCV@L2c0 with n60 min101.1 max176.7 mean148.9 median154.2 std19.6 best-iNshh(0,50,39,167,177*)
hi-LOOCV@L2c1 with n4 min124.0 max151.7 mean142.8 median147.8 std11.0 best-iNshh(72,50,30,94,152*)
hi-LOOCV@L2c2 with n18 min97.1 max195.4 mean167.6 median187.9 std33.3 best-iNshh(59,50,29,67,195*)
hi-LOOCV@L2c3 with n5 min129.8 max211.0 mean187.4 median201.5 std30.5 best-iNshh(52,50,13,68,211*)
#Wed Jun 10 10:14:30 JST 2020 TP0=2300 N:50_N:100 ns=10_50 ==>(hV,hg)=(188,215)
h(yi,yg)@L0c0 with n58 min64.0 max215.0 mean129.3 median151.5 std47.8 best-iNshh(22,100,16,215*,117)
h(yi,yg)@L2c0 with n17 min79.0 max215.0 mean156.5 median167.0 std40.2 best-iNshh(22,100,16,215*,181)
h(yi,yg)@L2c1 with n25 min91.0 max192.0 mean150.7 median159.0 std27.2 best-iNshh(21,100,29,192*,161)
h(yi,yg)@L2c2 with n1 min69.0 max69.0 mean69.0 median69.0 std0.0 best-iNshh(55,100,46,69*,-1)
h(yi,yg)@L2c3 with n13 min64.0 max68.0 mean66.4 median67.0 std1.1 best-iNshh(43,100,33,68*,190)(56,50,9,68*,106)
hi-LOOCV@L0c0 with n58 min75.9 max142.0 mean109.9 median112.5 std19.1 best-iNshh(0,100,47,192,142*)
hi-LOOCV@L2c0 with n17 min119.6 max210.8 mean176.7 median180.4 std26.0 best-iNshh(0,100,47,192,211*)
hi-LOOCV@L2c1 with n25 min92.9 max163.0 mean143.7 median154.1 std19.4 best-iNshh(16,100,21,188,163*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,100,46,69,-1*)
hi-LOOCV@L2c3 with n13 min106.4 max195.2 mean170.0 median188.2 std31.3 best-iNshh(44,100,37,67,195*)
#Wed Jun 10 10:06:05 JST 2020 TP0=2300 N:50_N:100 ns=25_50 ==>(hV,hg)=(188,362)
h(yi,yg)@L0c0 with n73 min64.0 max362.0 mean136.7 median155.0 std57.9 best-iNshh(29,50,18,362*,127)
h(yi,yg)@L2c0 with n6 min67.0 max69.0 mean68.2 median68.0 std0.7 best-iNshh(67,100,46,69*,163)(68,100,9,69*,159)
h(yi,yg)@L2c1 with n13 min64.0 max68.0 mean66.2 median66.0 std1.0 best-iNshh(56,100,33,68*,199)
h(yi,yg)@L2c2 with n32 min91.0 max362.0 mean157.6 median158.5 std44.4 best-iNshh(29,50,18,362*,151)
h(yi,yg)@L2c3 with n22 min79.0 max302.0 mean166.6 median167.0 std50.3 best-iNshh(13,50,20,302*,169)
hi-LOOCV@L0c0 with n73 min73.6 max144.2 mean113.4 median116.6 std21.0 best-iNshh(1,50,14,167,144*)
hi-LOOCV@L2c0 with n6 min88.0 max167.8 mean133.1 median138.1 std31.4 best-iNshh(45,50,13,68,168*)
hi-LOOCV@L2c1 with n13 min120.2 max205.2 mean184.1 median198.0 std28.4 best-iNshh(54,100,38,67,205*)
hi-LOOCV@L2c2 with n32 min92.3 max165.0 mean145.9 median156.0 std18.7 best-iNshh(10,100,21,188,165*)
hi-LOOCV@L2c3 with n22 min118.9 max204.6 mean172.3 median180.2 std25.6 best-iNshh(3,100,17,167,205*)
#Wed Jun 10 09:44:27 JST 2020 TP0=2300 N:50_N:100 ns=10_40 ==>(hV,hg)=(192,215)
h(yi,yg)@L0c0 with n49 min64.0 max215.0 mean126.4 median125.0 std47.7 best-iNshh(17,100,16,215*,112)
h(yi,yg)@L2c0 with n1 min69.0 max69.0 mean69.0 median69.0 std0.0 best-iNshh(47,100,9,69*,-1)
h(yi,yg)@L2c1 with n12 min64.0 max68.0 mean66.5 median67.0 std1.1 best-iNshh(36,100,33,68*,197)(46,50,9,68*,107)
h(yi,yg)@L2c2 with n24 min122.0 max192.0 mean162.2 median165.0 std18.7 best-iNshh(16,100,29,192*,182)
h(yi,yg)@L2c3 with n11 min79.0 max215.0 mean124.4 median123.0 std45.3 best-iNshh(17,100,16,215*,139)
hi-LOOCV@L0c0 with n49 min73.7 max135.6 mean107.9 median105.6 std16.4 best-iNshh(7,100,6,167,136*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(47,100,9,69,-1*)
hi-LOOCV@L2c1 with n12 min107.2 max202.0 mean179.0 median195.5 std31.7 best-iNshh(37,100,37,67,202*)
hi-LOOCV@L2c2 with n24 min125.9 max181.9 mean161.4 median164.5 std14.5 best-iNshh(16,100,29,192,182*)
hi-LOOCV@L2c3 with n11 min90.2 max161.8 mean134.8 median139.1 std22.9 best-iNshh(12,50,4,190,162*)
#Wed Jun 10 09:57:28 JST 2020 TP0=2300 N:50_N:100 ns=17_33 ==>(hV,hg)=(,)
h(yi,yg)@L0c0 with n49 min64.0 max245.0 mean134.5 median155.0 std47.1 best-iNshh(0,50,12,245*,144)
h(yi,yg)@L2c0 with n25 min91.0 max192.0 mean149.3 median157.0 std26.8 best-iNshh(17,100,29,192*,159)
h(yi,yg)@L2c1 with n14 min79.0 max245.0 mean156.4 median167.0 std48.5 best-iNshh(0,50,12,245*,171)
h(yi,yg)@L2c2 with n7 min64.0 max68.0 mean66.3 median67.0 std1.3 best-iNshh(47,50,9,68*,106)
h(yi,yg)@L2c3 with n1 min68.0 max68.0 mean68.0 median68.0 std0.0 best-iNshh(46,50,7,68*,-1)
hi-LOOCV@L0c0 with n49 min71.1 max144.4 mean113.4 median118.2 std21.7 best-iNshh(1,50,14,167,144*)
hi-LOOCV@L2c0 with n25 min93.0 max164.6 mean143.3 median151.7 std19.1 best-iNshh(4,100,27,159,165*)
hi-LOOCV@L2c1 with n14 min118.5 max206.2 mean171.9 median178.8 std25.7 best-iNshh(24,50,4,190,206*)
hi-LOOCV@L2c2 with n7 min106.3 max177.2 mean153.9 median169.7 std27.3 best-iNshh(35,100,4,67,177*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(46,50,7,68,-1*)

#Tue Jun  9 11:15:09 JST 2020 TP0=2300 N:40 ==>(hV,hg)=(159,218)
h(yi,yg)@L0c0 with n48 min64.0 max218.0 mean123.3 median123.0 std41.4 best-iNshh(17,40,18,218*,125)
h(yi,yg)@L2c0 with n32 min79.0 max218.0 mean146.2 median155.0 std30.5 best-iNshh(17,40,18,218*,149)
h(yi,yg)@L2c1 with n7 min87.0 max94.0 mean91.6 median93.0 std3.0 best-iNshh(26,40,27,94*,145)(31,40,32,94*,150)(35,40,36,94*,148)
h(yi,yg)@L2c2 with n1 min64.0 max64.0 mean64.0 median64.0 std0.0 best-iNshh(21,40,22,64*,-1)
h(yi,yg)@L2c3 with n6 min67.0 max69.0 mean67.7 median67.5 std0.7 best-iNshh(6,40,7,69*,83)
hi-LOOCV@L0c0 with n48 min71.0 max136.4 mean110.6 median117.3 std19.3 best-iNshh(19,40,20,159,136*)
hi-LOOCV@L2c0 with n32 min107.4 max167.0 mean146.2 median145.0 std14.3 best-iNshh(19,40,20,159,167*)
hi-LOOCV@L2c1 with n7 min125.2 max149.5 mean140.1 median143.0 std8.5 best-iNshh(31,40,32,94,150*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(21,40,22,64,-1*)
hi-LOOCV@L2c3 with n6 min82.8 max191.8 mean166.4 median181.4 std37.7 best-iNshh(8,40,9,68,192*)
#tp0=2300 N:50 ==>(hV,hg)=(167,362)
h(yi,yg)@L0c0 with n49 min65.0 max362.0 mean138.6 median137.0 std61.0 best-iNshh(18,50,18,362*,129)
h(yi,yg)@L2c0 with n35 min121.0 max362.0 mean165.9 median159.0 std50.8 best-iNshh(18,50,18,362*,154)
h(yi,yg)@L2c1 with n1 min94.0 max94.0 mean94.0 median94.0 std0.0 best-iNshh(30,50,30,94*,-1)
h(yi,yg)@L2c2 with n1 min67.0 max67.0 mean67.0 median67.0 std0.0 best-iNshh(22,50,22,67*,-1)
h(yi,yg)@L2c3 with n11 min65.0 max68.0 mean67.0 median67.0 std1.0 best-iNshh(7,50,7,68*,119)(9,50,9,68*,107)(13,50,13,68*,168)(27,50,27,68*,142)
hi-LOOCV@L0c0 with n49 min73.6 max139.6 mean114.8 median122.6 std19.8 best-iNshh(26,50,26,167,140*)
hi-LOOCV@L2c0 with n35 min122.2 max167.9 mean148.5 median148.4 std14.4 best-iNshh(26,50,26,167,168*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,30,94,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(22,50,22,67,-1*)
hi-LOOCV@L2c3 with n11 min107.4 max221.3 mean171.1 median187.7 std38.0 best-iNshh(48,50,49,67,221*)
Tue Jun  9 11:25:47 JST 2020 TP0=2300 N:55 ==>(hV,hg)=(168,338)
h(yi,yg)@L0c0 with n48 min60.0 max338.0 mean127.1 median123.5 std59.4 best-iNshh(18,55,19,338*,123)
h(yi,yg)@L2c0 with n28 min79.0 max338.0 mean166.9 median167.0 std46.6 best-iNshh(18,55,19,338*,161)
h(yi,yg)@L2c1 with n4 min82.0 max93.0 mean89.2 median91.0 std4.3 best-iNshh(10,55,11,93*,122)
h(yi,yg)@L2c2 with n10 min65.0 max68.0 mean66.4 median67.0 std1.0 best-iNshh(28,55,29,68*,197)
h(yi,yg)@L2c3 with n6 min60.0 max70.0 mean67.7 median69.0 std3.4 best-iNshh(32,55,34,70*,102)
hi-LOOCV@L0c0 with n48 min70.6 max133.1 mean105.7 median105.2 std17.1 best-iNshh(17,55,18,168,133*)
hi-LOOCV@L2c0 with n28 min103.0 max177.5 mean150.4 median157.8 std20.7 best-iNshh(17,55,18,168,178*)
hi-LOOCV@L2c1 with n4 min97.0 max121.7 mean113.5 median117.7 std9.7 best-iNshh(10,55,11,93,122*)
hi-LOOCV@L2c2 with n10 min131.0 max197.3 mean179.6 median191.1 std24.6 best-iNshh(34,55,36,67,197*)
hi-LOOCV@L2c3 with n6 min98.0 max194.2 mean150.5 median158.6 std40.8 best-iNshh(23,55,24,69,194*)

#Tue Jun  9 11:20:35 JST 2020 TP0=2300 N:60 ==>(hV,hg)=(168,361)
h(yi,yg)@L0c0 with n50 min32.0 max361.0 mean130.1 median123.5 std69.4 best-iNshh(14,60,14,361*,126)
h(yi,yg)@L2c0 with n35 min70.0 max361.0 mean158.2 median159.0 std64.9 best-iNshh(14,60,14,361*,153)
h(yi,yg)@L2c1 with n14 min62.0 max70.0 mean66.9 median67.0 std2.1 best-iNshh(18,60,18,70*,87)(27,60,27,70*,89)
h(yi,yg)@L2c2 with n1 min32.0 max32.0 mean32.0 median32.0 std0.0 best-iNshh(31,60,31,32*,-1)
hi-LOOCV@L0c0 with n50 min32.1 max137.3 mean103.8 median109.1 std21.2 best-iNshh(36,60,36,168,137*)
hi-LOOCV@L2c0 with n35 min74.5 max168.6 mean135.1 median135.1 std21.4 best-iNshh(36,60,36,168,169*)
hi-LOOCV@L2c1 with n14 min86.6 max160.5 mean123.7 median125.3 std28.2 best-iNshh(46,60,46,68,161*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(31,60,31,32,-1*)
Tue Jun  9 11:20:35 JST 2020 TP0=2300 N:60
#tp0=2300 N:70 ==>(hV,hg)=(168,243)
h(yi,yg)@L0c0 with n49 min31.0 max243.0 mean129.9 median126.0 std48.0 best-iNshh(39,70,40,243*,143)
h(yi,yg)@L2c0 with n39 min79.0 max243.0 mean147.1 median161.0 std37.8 best-iNshh(39,70,40,243*,164)
h(yi,yg)@L2c1 with n9 min65.0 max69.0 mean66.6 median66.0 std1.4 best-iNshh(28,70,29,69*,78)
h(yi,yg)@L2c2 with n1 min31.0 max31.0 mean31.0 median31.0 std0.0 best-iNshh(30,70,31,31*,-1)
hi-LOOCV@L0c0 with n49 min31.6 max144.5 mean114.4 median118.0 std25.4 best-iNshh(7,70,7,168,145*)
hi-LOOCV@L2c0 with n39 min88.6 max165.6 mean140.8 median144.9 std19.4 best-iNshh(7,70,7,168,166*)
hi-LOOCV@L2c1 with n9 min77.9 max186.9 mean144.8 median157.4 std31.2 best-iNshh(26,70,27,68,187*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,70,31,31,-1*)
#tp0=2300 N:100 ==>(hV,hg)=(188,215)
h(yi,yg)@L0c0 with n48 min64.0 max215.0 mean131.2 median157.0 std49.0 best-iNshh(16,100,16,215*,119)
h(yi,yg)@L2c0 with n11 min64.0 max68.0 mean66.4 median67.0 std1.1 best-iNshh(32,100,33,68*,197)
h(yi,yg)@L2c1 with n1 min69.0 max69.0 mean69.0 median69.0 std0.0 best-iNshh(44,100,46,69*,-1)
h(yi,yg)@L2c2 with n14 min79.0 max215.0 mean156.2 median167.5 std42.5 best-iNshh(16,100,16,215*,186)
h(yi,yg)@L2c3 with n21 min91.0 max192.0 mean154.3 median159.0 std27.5 best-iNshh(28,100,29,192*,168)
##
hi-LOOCV@L0c0 with n48 min75.9 max145.1 mean113.1 median115.2 std21.0 best-iNshh(40,100,41,179,145*)
hi-LOOCV@L2c0 with n11 min120.0 max202.3 mean177.7 median191.3 std27.9 best-iNshh(36,100,37,67,202*)
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(44,100,46,69,-1*)
hi-LOOCV@L2c2 with n14 min145.4 max213.6 mean185.0 median186.2 std23.8 best-iNshh(45,100,47,192,214*)
hi-LOOCV@L2c3 with n21 min93.0 max168.9 mean149.8 median159.1 std21.5 best-iNshh(21,100,21,188,169*)  better than L0c0
#Tue Jun  9 11:49:28 JST 2020 TP0=2300 N:50,100 ==>(hV,hg)=(167,362)
h(yi,yg)@L0c0 with n97 min64.0 max362.0 mean134.9 median148.0 std55.5 best-iNshh(39,50,18,362*,127)
h(yi,yg)@L2c0 with n38 min88.0 max362.0 mean152.6 median158.0 std44.0 best-iNshh(39,50,18,362*,147)
h(yi,yg)@L2c1 with n34 min79.0 max302.0 mean165.3 median167.0 std44.3 best-iNshh(18,50,20,302*,166)
h(yi,yg)@L2c2 with n18 min64.0 max68.0 mean66.4 median67.0 std1.0 best-iNshh(73,100,33,68*,201)
h(yi,yg)@L2c3 with n7 min67.0 max69.0 mean68.1 median68.0 std0.6 best-iNshh(91,100,46,69*,170)(92,100,9,69*,164)
hi-LOOCV@L0c0 with n97 min73.8 max143.5 mean114.3 median118.2 std20.6 best-iNshh(0,50,39,167,143*)
hi-LOOCV@L2c0 with n38 min90.5 max159.4 mean139.6 median147.1 std19.4 best-iNshh(13,100,48,167,159*)
hi-LOOCV@L2c1 with n34 min124.6 max201.6 mean168.4 median175.4 std22.6 best-iNshh(8,100,17,167,202*)
hi-LOOCV@L2c2 with n18 min120.7 max222.1 mean193.0 median203.6 std31.0 best-iNshh(69,50,46,67,222*)
hi-LOOCV@L2c3 with n7 min86.8 max174.2 mean139.0 median154.0 std32.4 best-iNshh(59,50,13,68,174*)

#tp0=2400 N:50 ==>(hV,hg)=(167,362)
h(yi,yg)@L0c0 with n49 min54.0 max237.0 mean109.9 median68.0 std61.3 best-iNshh(2,50,3,237*,107)
h(yi,yg)@L2c0 with n21 min68.0 max237.0 mean166.0 median172.0 std53.4 best-iNshh(2,50,3,237*,163)
h(yi,yg)@L2c1 with n6 min68.0 max117.0 mean92.2 median91.5 std24.2 best-iNshh(20,50,21,117*,135)(47,50,48,117*,197)
h(yi,yg)@L2c2 with n18 min56.0 max64.0 mean60.4 median61.0 std2.2 best-iNshh(26,50,27,64*,124)(41,50,42,64*,125)
h(yi,yg)@L2c3 with n4 min54.0 max76.0 mean64.5 median64.0 std8.1 best-iNshh(13,50,14,76*,116)
hi-LOOCV@L0c0 with n49 min61.5 max124.0 mean98.9 median98.3 std16.1 best-iNshh(12,50,13,201,124*)
hi-LOOCV@L2c0 with n21 min138.8 max198.1 mean173.3 median172.8 std16.7 best-iNshh(12,50,13,201,198*)
hi-LOOCV@L2c1 with n6 min135.2 max196.8 mean175.3 median187.0 std22.2 best-iNshh(47,50,48,117,197*)
hi-LOOCV@L2c2 with n18 min109.3 max183.9 mean147.6 median153.6 std23.1 best-iNshh(42,50,43,62,184*)
hi-LOOCV@L2c3 with n4 min58.3 max116.7 mean89.5 median91.5 std26.9 best-iNshh(32,50,33,67,117*)
#Tue Jun  9 11:36:47 JST 2020 TP0=2500 N:50 ==> (hV,hg)=(283,355)
h(yi,yg)@L0c0 with n49 min102.0 max355.0 mean187.7 median191.0 std57.0 best-iNshh(18,50,18,355*,189)
h(yi,yg)@L2c0 with n35 min114.0 max355.0 mean211.7 median193.0 std49.6 best-iNshh(18,50,18,355*,215)
h(yi,yg)@L2c1 with n12 min105.0 max138.0 mean131.5 median133.5 std8.3 best-iNshh(14,50,14,138*,159)
h(yi,yg)@L2c2 with n1 min104.0 max104.0 mean104.0 median104.0 std0.0 best-iNshh(46,50,47,104*,-1)
hi-LOOCV@L0c0 with n49 min102.6 max190.8 mean164.2 median169.5 std22.0 best-iNshh(29,50,29,283,191*)
hi-LOOCV@L2c0 with n35 min158.9 max216.7 mean195.6 median199.6 std15.3 best-iNshh(29,50,29,283,217*)
hi-LOOCV@L2c1 with n12 min116.5 max195.8 mean180.5 median193.4 std23.9 best-iNshh(28,50,28,135,196*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(46,50,47,104,-1*)
#Tue Jun  9 11:41:44 JST 2020 TP0=2600 N:50 ==>(hV,hg)=(184,310)
h(yi,yg)@L0c0 with n50 min48.0 max310.0 mean159.7 median151.0 std42.3 best-iNshh(40,50,40,310*,162)
h(yi,yg)@L2c0 with n16 min48.0 max157.0 mean144.4 median150.5 std25.0 best-iNshh(14,50,14,157*,168)
h(yi,yg)@L2c1 with n20 min129.0 max310.0 mean196.3 median185.0 std39.8 best-iNshh(40,50,40,310*,204)
h(yi,yg)@L2c2 with n6 min116.0 max128.0 mean125.3 median127.0 std4.2 best-iNshh(15,50,15,128*,134)
h(yi,yg)@L2c3 with n8 min124.0 max126.0 mean124.6 median124.5 std0.7 best-iNshh(8,50,8,126*,222)
hi-LOOCV@L0c0 with n50 min83.6 max171.8 mean152.2 median156.7 std15.0 best-iNshh(43,50,43,185,172*)
hi-LOOCV@L2c0 with n16 min114.5 max211.7 mean189.7 median194.2 std23.0 best-iNshh(13,50,13,149,212*)
hi-LOOCV@L2c1 with n20 min140.8 max226.3 mean199.1 median200.7 std19.4 best-iNshh(17,50,17,184,226*)
hi-LOOCV@L2c2 with n6 min115.0 max226.6 mean183.5 median200.8 std43.4 best-iNshh(19,50,19,127,227*)
hi-LOOCV@L2c3 with n8 min157.4 max222.4 mean206.7 median218.0 std22.4 best-iNshh(8,50,8,126,222*)

#Tue Jun  9 16:12:56 JST 2020 TP0=2700 N:50 ns=50 ==>(hV,hg)=(175,267)
h(yi,yg)@L0c0 with n48 min85.0 max267.0 mean146.4 median148.0 std47.0 best-iNshh(8,50,9,267*,141)
h(yi,yg)@L2c0 with n32 min98.0 max267.0 mean170.7 median164.0 std38.0 best-iNshh(8,50,9,267*,164)
h(yi,yg)@L2c1 with n7 min89.0 max118.0 mean111.6 median115.0 std9.4 best-iNshh(44,50,46,118*,170)
h(yi,yg)@L2c2 with n5 min86.0 max88.0 mean86.6 median86.0 std0.8 best-iNshh(26,50,28,88*,181)
h(yi,yg)@L2c3 with n4 min85.0 max90.0 mean87.5 median87.5 std2.1 best-iNshh(42,50,44,90*,151)
hi-LOOCV@L0c0 with n48 min92.4 max157.8 mean129.8 median139.7 std19.9 best-iNshh(0,50,0,175,158*)
hi-LOOCV@L2c0 with n32 min139.6 max187.3 mean165.2 median164.9 std10.0 best-iNshh(0,50,0,175,187*)
hi-LOOCV@L2c1 with n7 min93.0 max203.0 mean164.0 median170.0 std33.4 best-iNshh(32,50,34,117,203*)
hi-LOOCV@L2c2 with n5 min144.5 max203.8 mean179.7 median181.2 std22.4 best-iNshh(34,50,36,86,204*)
hi-LOOCV@L2c3 with n4 min147.7 max155.0 mean151.3 median151.3 std2.6 best-iNshh(45,50,47,85,155*)

#Tue Jun  9 16:09:12 JST 2020 TP0=2800 N:50 ns=50 ==>(hV,hg)=(199,349) 275L0
h(yi,yg)@L0c0 with n50 min48.0 max349.0 mean145.8 median152.0 std67.9 best-iNshh(1,50,1,349*,135)
h(yi,yg)@L2c0 with n5 min48.0 max52.0 mean51.0 median52.0 std1.5 best-iNshh(21,50,21,52*,137)(31,50,31,52*,137)(32,50,32,52*,135)
h(yi,yg)@L2c1 with n5 min53.0 max55.0 mean53.8 median54.0 std0.7 best-iNshh(7,50,7,55*,125)
h(yi,yg)@L2c2 with n15 min65.0 max275.0 mean174.9 median170.0 std56.8 best-iNshh(49,50,49,275*,192)
h(yi,yg)@L2c3 with n25 min104.0 max349.0 mean165.7 median165.0 std53.8 best-iNshh(1,50,1,349*,156)
hi-LOOCV@L0c0 with n50 min53.7 max145.0 mean113.7 median126.7 std31.1 best-iNshh(49,50,49,275,145*)
hi-LOOCV@L2c0 with n5 min99.2 max137.2 mean129.1 median137.0 std15.0 best-iNshh(30,50,30,51,137*)(31,50,31,52,137*)
hi-LOOCV@L2c1 with n5 min107.0 max178.2 mean131.0 median124.5 std24.5 best-iNshh(41,50,41,54,178*)
hi-LOOCV@L2c2 with n15 min73.4 max192.0 mean163.5 median175.3 std30.6 best-iNshh(49,50,49,275,192*)
hi-LOOCV@L2c3 with n25 min111.4 max165.1 mean145.5 median151.0 std17.3 best-iNshh(28,50,28,199,165*)

#Tue Jun  9 16:20:26 JST 2020 TP0=2800 N:50,100 ns=50 ==>(hV,hg)=(198,349) 259L0
h(yi,yg)@L0c0 with n100 min48.0 max349.0 mean161.3 median167.5 std64.9 best-iNshh(5,50,1,349*,155)
h(yi,yg)@L2c0 with n61 min78.0 max349.0 mean179.7 median170.0 std55.2 best-iNshh(5,50,1,349*,174)
h(yi,yg)@L2c1 with n28 min63.0 max275.0 mean164.0 median168.5 std54.6 best-iNshh(15,50,49,275*,184)
h(yi,yg)@L2c2 with n6 min48.0 max52.0 mean51.0 median51.5 std1.4 best-iNshh(90,50,32,52*,154)(91,50,21,52*,144)(97,50,31,52*,137)
h(yi,yg)@L2c3 with n5 min53.0 max55.0 mean53.8 median54.0 std0.7 best-iNshh(92,50,7,55*,125)
hi-LOOCV@L0c0 with n100 min51.0 max163.6 mean131.1 median145.4 std33.8 best-iNshh(28,100,14,259,164*)
hi-LOOCV@L2c0 with n61 min77.5 max188.0 mean158.9 median157.6 std22.8 best-iNshh(38,100,29,198,188*)
hi-LOOCV@L2c1 with n28 min79.9 max192.7 mean162.3 median174.5 std32.5 best-iNshh(35,100,23,167,193*)
hi-LOOCV@L2c2 with n6 min99.2 max154.2 mean137.5 median140.3 std18.5 best-iNshh(89,100,37,51,154*)
hi-LOOCV@L2c3 with n5 min107.0 max178.2 mean131.0 median124.5 std24.5 best-iNshh(94,50,41,54,178*)
#Tue Jun  9 17:22:38 JST 2020 TP0=2900 N:50 ns=50 ==>(hV,hg)=(213,249)
h(yi,yg)@L0c0 with n49 min36.0 max249.0 mean148.1 median157.0 std60.0 best-iNshh(33,50,34,249*,150)
h(yi,yg)@L2c0 with n13 min71.0 max77.0 mean73.3 median73.0 std1.5 best-iNshh(40,50,41,77*,77)
h(yi,yg)@L2c1 with n35 min76.0 max249.0 mean179.0 median187.0 std40.5 best-iNshh(33,50,34,249*,183)
h(yi,yg)@L2c2 with n1 min36.0 max36.0 mean36.0 median36.0 std0.0 best-iNshh(19,50,20,36*,-1)
hi-LOOCV@L0c0 with n49 min36.2 max155.9 mean122.0 median132.7 std26.4 best-iNshh(12,50,13,213,156*)
hi-LOOCV@L2c0 with n13 min77.0 max201.8 mean170.4 median175.0 std30.3 best-iNshh(48,50,49,73,202*)
hi-LOOCV@L2c1 with n35 min75.5 max190.9 mean160.2 median169.9 std26.9 best-iNshh(12,50,13,213,191*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(19,50,20,36,-1*)

#Tue Jun  9 17:27:45 JST 2020 TP0=3000 N:50 ns=50 ==>(hV,hg)=(151,244)
h(yi,yg)@L0c0 with n50 min87.0 max244.0 mean156.0 median149.0 std40.8 best-iNshh(29,50,29,244*,157)
h(yi,yg)@L2c0 with n37 min113.0 max244.0 mean171.4 median151.0 std33.2 best-iNshh(29,50,29,244*,171)
h(yi,yg)@L2c1 with n9 min100.0 max151.0 mean122.6 median103.0 std23.9 best-iNshh(37,50,37,151*,205)
h(yi,yg)@L2c2 with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(35,50,35,87*,-1)
h(yi,yg)@L2c3 with n1 min89.0 max89.0 mean89.0 median89.0 std0.0 best-iNshh(20,50,20,89*,-1)
hi-LOOCV@L0c0 with n50 min91.7 max173.6 mean153.4 median160.7 std22.2 best-iNshh(16,50,16,151,174*)
hi-LOOCV@L2c0 with n37 min114.1 max186.2 mean173.2 median175.8 std12.2 best-iNshh(16,50,16,151,186*)
hi-LOOCV@L2c1 with n9 min200.9 max253.0 mean223.1 median212.9 std20.0 best-iNshh(26,50,26,148,253*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(35,50,35,87,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(20,50,20,89,-1*)

#Tue Jun  9 18:17:39 JST 2020 TP0=3100 N:50 ns=50 ==>(hV,hg)=(174,205)
h(yi,yg)@L0c0 with n48 min48.0 max205.0 mean136.4 median138.0 std39.3 best-iNshh(1,50,1,205*,131)
h(yi,yg)@L2c0 with n1 min75.0 max75.0 mean75.0 median75.0 std0.0 best-iNshh(36,50,36,75*,-1)
h(yi,yg)@L2c1 with n43 min97.0 max205.0 mean144.6 median139.0 std32.8 best-iNshh(1,50,1,205*,139)
h(yi,yg)@L2c2 with n1 min52.0 max52.0 mean52.0 median52.0 std0.0 best-iNshh(45,50,45,52*,-1)
hi-LOOCV@L0c0 with n48 min47.9 max142.4 mean117.8 median124.9 std21.8 best-iNshh(8,50,8,174,142*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(36,50,36,75,-1*)
hi-LOOCV@L2c1 with n43 min92.8 max151.5 mean130.6 median134.2 std14.5 best-iNshh(8,50,8,174,152*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(45,50,45,52,-1*)


##############bad!!!
#Tue Jun  9 15:35:24 JST 2020 TP0=2700 N:50 ==>(hV,hg)=(175,448)
h(yi,yg)@L0c0 with n98 min85.0 max448.0 mean157.5 median148.0 std56.2 best-iNshh(91,50,93,448*,149)
h(yi,yg)@L2c0 with n73 min98.0 max448.0 mean177.4 median172.0 std51.2 best-iNshh(91,50,93,448*,166)
h(yi,yg)@L2c1 with n12 min89.0 max119.0 mean113.2 median115.0 std7.5 best-iNshh(57,50,59,119*,122)
h(yi,yg)@L2c2 with n9 min85.0 max88.0 mean86.6 median86.0 std1.0 best-iNshh(26,50,28,88*,183)(80,50,82,88*,184)
h(yi,yg)@L2c3 with n4 min85.0 max90.0 mean87.5 median87.5 std2.1 best-iNshh(42,50,44,90*,151)
hi-LOOCV@L0c0 with n98 min90.4 max162.7 mean138.6 median149.1 std21.0 best-iNshh(0,50,0,175,163*)
hi-LOOCV@L2c0 with n73 min141.8 max183.7 mean167.1 median167.5 std8.5 best-iNshh(0,50,0,175,184*)
hi-LOOCV@L2c1 with n12 min95.4 max210.0 mean175.9 median189.9 std33.3 best-iNshh(90,50,92,116,210*)
hi-LOOCV@L2c2 with n9 min160.1 max190.6 mean178.0 median183.1 std11.3 best-iNshh(34,50,36,86,191*)
hi-LOOCV@L2c3 with n4 min147.7 max155.0 mean151.3 median151.3 std2.6 best-iNshh(45,50,47,85,155*)
#Tue Jun  9 16:04:06 JST 2020 TP0=2800 N:50 ==>(hV,hg)=(139,349)  173L0
h(yi,yg)@L0c0 with n100 min48.0 max349.0 mean147.2 median139.0 std57.4 best-iNshh(1,50,1,349*,140)
h(yi,yg)@L2c0 with n60 min104.0 max349.0 mean155.1 median138.5 std46.1 best-iNshh(1,50,1,349*,151)
h(yi,yg)@L2c1 with n27 min65.0 max275.0 mean175.5 median170.0 std46.4 best-iNshh(49,50,49,275*,184)
h(yi,yg)@L2c2 with n8 min48.0 max52.0 mean50.6 median51.0 std1.6 best-iNshh(21,50,21,52*,130)(31,50,31,52*,135)(32,50,32,52*,127)
h(yi,yg)@L2c3 with n5 min53.0 max55.0 mean53.8 median54.0 std0.7 best-iNshh(7,50,7,55*,125)
hi-LOOCV@L0c0 with n100 min51.9 max147.9 mean121.2 median135.2 std29.7 best-iNshh(14,50,14,173,148*)
hi-LOOCV@L2c0 with n60 min113.0 max161.8 mean143.7 median150.0 std14.8 best-iNshh(66,50,66,139,162*)
hi-LOOCV@L2c1 with n27 min75.0 max201.2 mean171.4 median181.0 std30.4 best-iNshh(75,50,75,170,201*)
hi-LOOCV@L2c2 with n8 min98.0 max135.3 mean122.4 median128.2 std13.3 best-iNshh(77,50,77,51,135*)
hi-LOOCV@L2c3 with n5 min107.0 max178.2 mean131.0 median124.5 std24.5 best-iNshh(41,50,41,54,178*)






###################
20200605
###################
make
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc
export TP0="2000" 
export N="N:50-100:10" Sth=0.5 n_seed="1" phase="" 
#export N="N:5-300:5" Sth=0.5 n_seed="1" phase="" 
export ID="${n_seed}" #export ID=ID"${n_seed}-${Sth:2}" #Sth=0.5 -> S{Sth:2}=5  -> ID=ID1-5
export L=2 #L=2
#####################
##### export phase=2 #for avoiding the excesution of 1st phase again
#####################
#(1-1)&(1-2)
#(1-1)learning
date > $d0/cmd-io-sum.dat
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -phase "$phase" -ID "$ID"
#(1-2) clustering?
source $d0/d1.env #d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1
echo "###saved in d1=$d1"         >> $d0/cmd-io-sum.dat
#emacs $d1/cmd.sh;source $d1/cmd.sh  #edit cmd.sh if necessary with phase=1
source $d1/cmd.sh >> $d0/cmd-io-sum.dat
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
date >> $d0/cmd-io-sum.dat
grep "hi-LOOCV@L0c\|hi-LOOCV@L2c\|h(yi,yg)@L2c" $d1/cmd.out |sort
#結果例TP0=2000 #result 2020/06/05
hi-LOOCV@L0c0 with n58 min36.9 max174.2 mean115.9 median119.1 std43.9 best-iNshh(0,125,0,191,174*)
hi-LOOCV@L2c0 with n38 min71.2 max257.7 mean207.3 median229.0 std45.7 best-iNshh(0,125,0,191,258*)  ***
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(57,5,0,45,-1*)
hi-LOOCV@L2c2 with n14 min62.8 max276.8 mean234.8 median238.6 std50.9 best-iNshh(37,280,0,19,277*)(38,285,0,19,277*)
hi-LOOCV@L2c3 with n5 min90.0 max166.2 mean129.1 median133.2 std34.1 best-iNshh(53,230,0,20,166*)
h(yi,yg)@L2c0 with n38 min71.0 max395.0 mean188.4 median190.0 std51.7 best-iNshh(25,195,0,395*,186)
h(yi,yg)@L2c1 with n1 min45.0 max45.0 mean45.0 median45.0 std0.0 best-iNshh(57,5,0,45*,-1)
h(yi,yg)@L2c2 with n14 min19.0 max20.0 mean19.2 median19.0 std0.4 best-iNshh(39,210,0,20*,235)(41,215,0,20*,231)(56,220,0,20*,63)
h(yi,yg)@L2c3 with n5 min19.0 max20.0 mean19.6 median20.0 std0.5 best-iNshh(53,230,0,20*,166)(54,225,0,20*,166)(55,235,0,20*,133)
==>N=125,280,285,230
#Tue Jun  9 19:11:42 JST 2020 TP0=2000 N:50-200:25 ns=50 ==>(hV,hg)=(,)
h(yi,yg)@L0c0 with n338 min13.0 max391.0 mean164.9 median184.0 std67.5 best-iNshh(87,150,12,391*,168)(189,150,11,391*,153)
h(yi,yg)@L2c0 with n129 min71.0 max391.0 mean170.1 median157.0 std54.5 best-iNshh(87,150,12,391*,174)(189,150,11,391*,174)
h(yi,yg)@L2c1 with n170 min23.0 max367.0 mean192.9 median192.0 std38.0 best-iNshh(160,150,39,367*,190)
h(yi,yg)@L2c2 with n21 min13.0 max21.0 mean16.9 median16.0 std2.8 best-iNshh(316,50,34,21*,20)
h(yi,yg)@L2c3 with n18 min21.0 max145.0 mean36.8 median29.0 std30.7 best-iNshh(297,150,35,145*,103)
hi-LOOCV@L0c0 with n338 min14.3 max173.8 mean137.8 median158.2 std44.2 best-iNshh(14,125,15,194,174*)
hi-LOOCV@L2c0 with n129 min73.6 max175.0 mean153.4 median163.3 std22.3 best-iNshh(119,75,43,169,175*)
hi-LOOCV@L2c1 with n170 min124.0 max216.9 mean197.5 median206.8 std20.7 best-iNshh(52,125,8,196,217*)
hi-LOOCV@L2c2 with n21 min20.4 max122.0 mean74.9 median73.4 std30.6 best-iNshh(321,200,43,16,122*)
hi-LOOCV@L2c3 with n18 min43.7 max124.5 mean101.8 median108.6 std26.1 best-iNshh(306,50,27,29,124*)

#結果の見方（意味）
#hi-LOOCV@L2c<i>: 第L=2階層の<i>番目のクラスタのhi-LOOCVに関する統計
#n<n>: そのクラスタ内の要素数が<n>個
#min<min>:クラスタ内の hi-LOOCV の最小値
#max<max>:クラスタ内の hi-LOOCV の最大値
#mean<mean>:クラスタ内の hi-LOOCV の平均値
#median<median>:クラスタ内の hi-LOOCV のmedian
#std<std>:クラスタ内の hi-LOOCV の標準偏差(2乗平均平方根)、
#best-iNshh(0,125,0,191,258*)の見方
#第1要素i=0：予測時系列の番号（類似度で削除した後の通し番号）、
#第2要素N=125:ユニット数のCAN2で予測を行った
#第3要素s=0:全ての予測時系列中の通し番号（類似度で削除する前の番号）?
#第4要素191：この予測時系列のhg
#第5要素258：このクラスタの中で最長のhi-LOOCV;左の<max>と同じ値.
#            上の例ではL2c2には,maxが２つN=280,285ある
#この例では, n>2に対する、N=125,280,285,230,がN_{ij},この内最小のN=125を用いてstep2を行う
#########
#結果例TP0=2000 #result 2020/06/05
hi-LOOCV@L0c0 with n58 min36.9 max174.2 mean115.9 median119.1 std43.9 best-iNshh(0,125,0,191,174*)
hi-LOOCV@L2c0 with n38 min71.2 max257.7 mean207.3 median229.0 std45.7 best-iNshh(0,125,0,191,258*)  ***
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(57,5,0,45,-1*)
hi-LOOCV@L2c2 with n14 min62.8 max276.8 mean234.8 median238.6 std50.9 best-iNshh(37,280,0,19,277*)(38,285,0,19,277*)
hi-LOOCV@L2c3 with n5 min90.0 max166.2 mean129.1 median133.2 std34.1 best-iNshh(53,230,0,20,166*)
h(yi,yg)@L2c0 with n38 min71.0 max395.0 mean188.4 median190.0 std51.7 best-iNshh(25,195,0,395*,186)
h(yi,yg)@L2c1 with n1 min45.0 max45.0 mean45.0 median45.0 std0.0 best-iNshh(57,5,0,45*,-1)
h(yi,yg)@L2c2 with n14 min19.0 max20.0 mean19.2 median19.0 std0.4 best-iNshh(39,210,0,20*,235)(41,215,0,20*,231)(56,220,0,20*,63)
h(yi,yg)@L2c3 with n5 min19.0 max20.0 mean19.6 median20.0 std0.5 best-iNshh(53,230,0,20*,166)(54,225,0,20*,166)(55,235,0,20*,133)
==>N=125,280,285,230
#TP0=2100
hi-LOOCV@L0c0 with n57 min100.5 max230.2 mean193.0 median206.8 std41.6 best-iNshh(0,190,0,91,230*)
#
hi-LOOCV@L2c1 with n47 min173.8 max259.8 mean236.8 median237.2 std15.7 best-iNshh(0,190,0,91,260*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(47,80,0,90,-1*)
hi-LOOCV@L2c3 with n7 min188.7 max217.5 mean206.6 median214.7 std11.7 best-iNshh(48,55,0,321,218*)(50,75,0,99,218*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,45,0,98,-1*)
#
h(yi,yg)@L2c1 with n47 min90.0 max94.0 mean91.5 median91.0 std0.8 best-iNshh(17,245,0,94*,244)
h(yi,yg)@L2c0 with n1 min90.0 max90.0 mean90.0 median90.0 std0.0 best-iNshh(47,80,0,90*,-1)
h(yi,yg)@L2c3 with n7 min99.0 max321.0 mean177.7 median196.0 std77.9 best-iNshh(48,55,0,321*,218)
h(yi,yg)@L2c2 with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(56,45,0,98*,-1)
==> N=190,55,75==> N=55
#########
#(2) step2 step1で得られた各クラスタで求めたユニット数Nでn_seed=30で実験
#########
#(2-0-1) n_seedなどの設定
export n_seed=50 Sth=0.5 phase="" #TP0="2000"  
export ID="${n_seed}" #export ID=ID"${n_seed}-${Sth:2}" 
#
#(2-0-2) d1の設定（デフォールト）
source $d0/d1.env   #このファイル$d0/d1.env中にstep1の結果を保存したディレクトリが書いてある。
##d1の設定（再実験）特定のtp0に対する再実験を行いたいときは以下のコマンドでd1(step1で作ったもの）を設定
# export d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1
# export d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2300-2800k10N:5-300:5ID1
###
#(2-0-3) Nの設定（デフォールト）
#source $d1/N-L2.env #ファイル$d1/N-L2.envの中にN_{ij}が記入してある
##Nの設定（再実験）$d1/N-L2.envからNを選んで設定
export N=N:55 #for TP0=21000
export N=N:125 #for TP0=20000
#if [ $TP0 = "2100" ]; then export N=N:125; fi
#if [ $TP0 = "2200" ]; then export N=N:55; fi
#
#(2-1)&(2-2)
export L=2 #L=2
date >> $d0/cmd-io-sum.dat
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -phase "$phase" -ID "$ID"
source $d0/d1.env #d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1-5
echo "#saved in d1=$d1"         >> $d0/cmd-io-sum.dat
tail -2 $d1/cmd.sh >> $d0/cmd-io-sum.dat
cp $d1/cmd.out $d1/cmd-Sth${Sth:2}.out
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat 
date >> $d0/cmd-io-sum.dat
#emacs $d0/cmd-io-sum.dat&
grep "hi-LOOCV@L0c\|hi-LOOCV@L${L}c\|h(yi,yg)@L${L}c" $d1/cmd.out 
##########
#(2-3) (2-2)の再実験 (異なるNやSthでの実験を行う）
##########
N=N:125;ID=50;tp0=2000;Sth=0.5
N=N:55;ID=50;tp0=2100;Sth=0.5
N=N:50;ID=50;tp0=2200; #export N=N:50
N=N:70;ID=50;tp0=2300;Sth=0.5
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-`expr $tp0 + 500`k10${N}ID${ID}
bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 

## results
#n_seed=50 (30<n_seeds <100)で 要素数nがmaxのクラスタのh-LOOCV最大の予測が、h(yi,yg)が長い
#小さなN=55(<75<190) の結果良い(ずっと下参照？）（なぜ：過学習が少ない？）
##########

#tp0=2000
hi-LOOCV@L0c0 with n49 min13.4 max194.9 mean166.2 median175.1 std33.5 best-iNshh(33,125,33,184,195*)

hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(25,125,25,71,-1*)
hi-LOOCV@L2c0 with n33 min136.5 max214.0 mean194.1 median202.5 std18.8 best-iNshh(33,125,33,184,214*) ***good hg=184 with max(hi-LOOCV)&n33
hi-LOOCV@L2c3 with n14 min130.2 max169.5 mean158.5 median161.4 std10.6 best-iNshh(31,125,31,186,170*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(44,125,45,14,-1*)

h(yi,yg)@L2c1 with n1 min71.0 max71.0 mean71.0 median71.0 std0.0 best-iNshh(25,125,25,71*,-1)
h(yi,yg)@L2c0 with n33 min130.0 max246.0 mean186.8 median185.0 std21.3 best-iNshh(37,125,38,246*,182)
h(yi,yg)@L2c3 with n14 min128.0 max358.0 mean177.9 median157.0 std59.0 best-iNshh(39,125,40,358*,168)
h(yi,yg)@L2c2 with n1 min14.0 max14.0 mean14.0 median14.0 std0.0 best-iNshh(44,125,45,14*,-1)

N=50
hi-LOOCV@L0c0 with n48 min14.0 max147.9 mean112.1 median128.1 std37.4 best-iNshh(45,50,47,304,148*) ***best
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(13,50,15,20,-1*)
hi-LOOCV@L2c0 with n40 min72.5 max165.1 mean145.5 median151.7 std20.2 best-iNshh(45,50,47,304,165*) ***best with N=50
hi-LOOCV@L2c3 with n4 min91.0 max126.0 mean113.0 median117.5 std14.0 best-iNshh(20,50,22,21,126*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(43,50,45,14,-1*)

h(yi,yg)@L2c1 with n1 min20.0 max20.0 mean20.0 median20.0 std0.0 best-iNshh(13,50,15,20*,-1)
h(yi,yg)@L2c0 with n40 min71.0 max332.0 mean167.8 median158.0 std54.2 best-iNshh(31,50,33,332*,162)
h(yi,yg)@L2c3 with n4 min21.0 max94.0 mean43.5 median29.5 std29.4 best-iNshh(42,50,44,94*,91)
h(yi,yg)@L2c2 with n1 min14.0 max14.0 mean14.0 median14.0 std0.0 best-iNshh(43,50,45,14*,-1)

N=55
hi-LOOCV@L0c0 with n48 min13.9 max150.4 mean113.6 median133.4 std41.6 best-iNshh(21,55,23,195,150*) ***better?
hi-LOOCV@L2c0 with n23 min36.0 max177.5 mean143.4 median156.4 std30.7 best-iNshh(46,55,48,219,178*)
hi-LOOCV@L2c1 with n18 min122.1 max184.5 mean159.6 median166.0 std18.6 best-iNshh(47,55,49,193,185*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(43,55,45,14,-1*)
hi-LOOCV@L2c2 with n4 min53.3 max173.3 mean108.3 median103.3 std50.3 best-iNshh(42,55,44,20,173*)

h(yi,yg)@L2c0 with n23 min31.0 max425.0 mean173.5 median157.0 std74.0 best-iNshh(41,55,43,425*,166)
h(yi,yg)@L2c1 with n18 min121.0 max216.0 mean165.7 median158.0 std29.9 best-iNshh(26,55,28,216*,164)
h(yi,yg)@L2c2 with n4 min20.0 max21.0 mean20.5 median20.5 std0.5 best-iNshh(17,55,19,21*,141)(20,55,22,21*,53)
h(yi,yg)@L2c3 with n1 min14.0 max14.0 mean14.0 median14.0 std0.0 best-iNshh(43,55,45,14*,-1)

hi-LOOCV@L0c0 with n48 min13.3 max180.2 mean153.6 median166.6 std35.6 best-iNshh(41,100,43,219,180*)
hi-LOOCV@L2c1 with n8 min95.9 max168.4 mean140.3 median143.5 std26.5 best-iNshh(40,100,42,128,168*)
hi-LOOCV@L2c0 with n38 min164.3 max200.8 mean187.1 median191.5 std11.0 best-iNshh(27,100,28,191,201*) **worse?
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(43,100,45,13,-1*)
h(yi,yg)@L2c1 with n8 min29.0 max128.0 mean113.2 median127.0 std32.2 best-iNshh(7,100,7,128*,168)(40,100,42,128*,168)(45,100,47,128*,146)
h(yi,yg)@L2c0 with n38 min143.0 max332.0 mean192.9 median187.5 std40.8 best-iNshh(28,100,29,332*,193)
h(yi,yg)@L2c2 with n1 min13.0 max13.0 mean13.0 median13.0 std0.0 best-iNshh(43,100,45,13*,-1)

why do L3=
hi-LOOCV@L0c0 with n49 min13.4 max194.9 mean166.2 median175.1 std33.5 best-iNshh(33,125,33,184,195*)
hi-LOOCV@L3c1 with n4 min151.3 max200.3 mean181.2 median186.5 std18.3 best-iNshh(35,125,35,129,200*)
hi-LOOCV@L3c0 with n10 min170.9 max184.1 mean177.7 median177.3 std4.7 best-iNshh(31,125,31,186,184*)
hi-LOOCV@L3c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(44,125,45,14,-1*)
hi-LOOCV@L3c5 with n28 min183.1 max225.7 mean209.2 median213.5 std13.2 best-iNshh(33,125,33,184,226*) ***Same result with L=2
hi-LOOCV@L3c4 with n5 min122.5 max218.5 mean187.4 median189.5 std34.8 best-iNshh(3,125,3,157,218*)
hi-LOOCV@L3c6 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(25,125,25,71,-1*)

h(yi,yg)@L3c1 with n4 min128.0 max147.0 mean133.0 median128.5 std8.1 best-iNshh(43,125,44,147*,190)
h(yi,yg)@L3c0 with n10 min144.0 max358.0 mean195.9 median178.0 std61.0 best-iNshh(39,125,40,358*,184)
h(yi,yg)@L3c2 with n1 min14.0 max14.0 mean14.0 median14.0 std0.0 best-iNshh(44,125,45,14*,-1)
h(yi,yg)@L3c5 with n28 min170.0 max246.0 mean193.2 median190.0 std15.7 best-iNshh(37,125,38,246*,187)
h(yi,yg)@L3c4 with n5 min130.0 max157.0 mean151.2 median156.0 std10.6 best-iNshh(3,125,3,157*,218)(7,125,7,157*,217)
h(yi,yg)@L3c6 with n1 min71.0 max71.0 mean71.0 median71.0 std0.0 best-iNshh(25,125,25,71*,-1)

hi-LOOCV@L4c11 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(13,125,13,128,-1*)
hi-LOOCV@L4c10 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(43,125,44,147,-1*)
hi-LOOCV@L4c12 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(44,125,45,14,-1*)
hi-LOOCV@L4c1 with n21 min205.8 max242.2 mean228.5 median228.6 std7.9 best-iNshh(33,125,33,184,242*)
hi-LOOCV@L4c0 with n7 min201.7 max238.3 mean213.7 median208.5 std11.8 best-iNshh(34,125,34,218,238*)
hi-LOOCV@L4c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(18,125,18,130,-1*)
hi-LOOCV@L4c2 with n4 min212.7 max249.3 mean230.7 median230.3 std18.0 best-iNshh(7,125,7,157,249*)
hi-LOOCV@L4c4 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(25,125,25,71,-1*)
hi-LOOCV@L4c9 with n4 min195.3 max223.7 mean213.8 median218.2 std11.2 best-iNshh(27,125,27,157,224*)
hi-LOOCV@L4c8 with n6 min188.4 max206.2 mean199.9 median204.9 std7.9 best-iNshh(31,125,31,186,206*)

#tp0=2100
hi-LOOCV@L0c0 with n48 min54.2 max144.0 mean122.1 median124.7 std17.4 best-iNshh(39,55,41,323,144*)
#
hi-LOOCV@L2c1 with n28 min68.7 max184.5 mean156.0 median164.8 std25.8 best-iNshh(39,55,41,323,184*) ***
hi-LOOCV@L2c0 with n19 min113.6 max215.2 mean170.0 median174.3 std25.6 best-iNshh(15,55,16,94,215*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(29,55,31,54,-1*)
#
h(yi,yg)@L2c1 with n28 min68.0 max323.0 mean180.1 median175.5 std71.4 best-iNshh(39,55,41,323*,184)
h(yi,yg)@L2c0 with n19 min88.0 max95.0 mean91.9 median92.0 std2.1 best-iNshh(3,55,4,95*,159)(12,55,13,95*,162)(38,55,40,95*,176)(44,55,46,95*,183)
h(yi,yg)@L2c2 with n1 min54.0 max54.0 mean54.0 median54.0 std0.0 best-iNshh(29,55,31,54*,-1)



###################
20191220
###################
#bagging prediction for Murata
time ./tspredv3 ../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 0-2000:2000-2200 mp:1:1:1 DiffMode:0 Hosei:0 N:50 M:1-1:1 ib:0:0:0:0 rsa:2:0.7:1:20 k:10 y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:50 vt:0.5 vr:10 lossall:1 DISP:2 nop:1


./tspredv3 ../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt 0-2000:2000-2500 mp:1:1:1 DiffMode:0 Hosei:0 N:50 M:1-1:1 ib:0:0:0:0 rsa:2:0.7:1:20 k:10 y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:100 vt:0.5 vr:10 lossall:1 DISP:0 e4t:0 e4p:0 seed:1 nop:1
#-->real7m21.404s

Executing5 'ensrs tmp/lorenz1e-8T0.025n10000p256m1_gmp:y0-2000.dat 2:20:0.7:1 50-50:1 bg:/dev/null M:1-1:1 ib:0:0:0:0 rsa:2:0.7:1:50 k:10 y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:100 vt:0.5 vr:10 lossall:1 DISP:0 e4t:0 e4p:0 seed:1 nop:1 y:-18.5:18.5:0:1 x0:-18.5:18.5:0:1 x1:-18.5:18.5:0:1 x2:-18.5:18.5:0:1 x3:-18.5:18.5:0:1 x4:-18.5:18.5:0:1 x5:-18.5:18.5:0:1 x6:-18.5:18.5:0:1 x7:-18.5:18.5:0:1 x8:-18.5:18.5:0:1 x9:-18.5:18.5:0:1 > /dev/null'

###################
20191220
###################
#課題１：20191219のstep1を行わず、Nを、例えばN=50に固定してstep2を行ってもそれなりにうまくいくのでは無いかと考えた。
#なぜなら、同一のデータを用いて同一の入出力関数を学習しているはずだから。
# Nが小さい場合と大きい場合の違いは？
# 最適なNは？
#課題２：選ばれたクラスタ内のhi-LOOCVとhgの関係の解析？20191219(2-4)check correlation between hg and hi-LOOCV
###################
##以下、実験
###################
#(1-0) 初期設定
#######
####################カット＆ペーストここから
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc;mkdir -p $d00
#(2-0)
export n_seed=50 Sth=0.5 phase="" TP0="2000"  
export ID="${n_seed}" #export ID=ID"${n_seed}-${Sth:2}" 
##Nの設定
export N=N:50 L=2
#(2-1)&(2-2)
date >> $d0/cmd-io-sum.dat
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -phase "$phase" -ID "$ID"
source $d0/d1.env #d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1-5
echo "#saved in d1=$d1"         >> $d0/cmd-io-sum.dat
tail -2 $d1/cmd.sh >> $d0/cmd-io-sum.dat
cp $d1/cmd.out $d1/cmd-Sth${Sth:2}.out
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat 
date >> $d0/cmd-io-sum.dat
echo "################"
grep "hi-LOOCV@L0c" $d1/cmd.out 
grep "hi-LOOCV@L2c" $d1/cmd.out 
grep "h(yi,yg)@L2c" $d1/cmd.out
grep "hi-LOOCV@L0c\|hi-LOOCV@L2c\|h(yi,yg)@L2c" $d1/cmd.out |sort
####################カット＆ペーストここまで
#tp0=2000 N:50 
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,30,86,-1*)
hi-LOOCV@L2c0 with n44 min97.0 max173.2 mean158.1 median161.2 std13.4 best-iNshh(17,50,17,194,173*) ***
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(31,50,31,103,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(35,50,35,103,-1*)
#tp2100 N:50 
hi-LOOCV@L2c1 with n14 min112.6 max223.7 mean190.3 median196.9 std30.0 best-iNshh(41,50,43,92,224*)
hi-LOOCV@L2c0 with n33 min93.3 max181.4 mean158.5 median166.7 std22.0 best-iNshh(44,50,46,257,181*) ***
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,31,54,-1*)
#tp2200 N:50 
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,30,86,-1*)
hi-LOOCV@L2c0 with n44 min97.0 max173.2 mean158.1 median161.2 std13.4 best-iNshh(17,50,17,194,173*)***
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(31,50,31,103,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(35,50,35,103,-1*)
#tp0=2300 N:50 
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,30,94,-1*)
hi-LOOCV@L2c0 with n35 min122.2 max167.9 mean148.5 median148.4 std14.4 best-iNshh(26,50,26,167,168*)***
hi-LOOCV@L2c3 with n11 min107.4 max221.3 mean171.1 median187.7 std38.0 best-iNshh(48,50,49,67,221*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(22,50,22,67,-1*)

#Nが大きいとよくない性質？
#tp0=2000 N:225 
hi-LOOCV@L2c1 with n13 min122.5 max175.4 mean156.2 median162.7 std16.8 best-iNshh(19,225,20,188,175*) ***?
hi-LOOCV@L2c0 with n26 min32.5 max211.0 mean175.9 median198.4 std48.7 best-iNshh(18,225,19,183,211*) ***
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(46,225,49,13,-1*)
hi-LOOCV@L2c2 with n5 min30.0 max211.0 mean166.7 median192.8 std68.9 best-iNshh(11,225,12,19,211*)
#tp0=2300 N:225 xxx
hi-LOOCV@L2c1 with n8 min92.4 max269.4 mean217.4 median241.8 std58.8 best-iNshh(20,225,20,69,269*)
hi-LOOCV@L2c0 with n22 min71.7 max207.3 mean167.7 median181.3 std36.8 best-iNshh(33,225,33,67,207*) xxx
hi-LOOCV@L2c3 with n7 min179.8 max251.5 mean207.6 median204.3 std25.1 best-iNshh(23,225,23,179,252*)
hi-LOOCV@L2c2 with n13 min67.3 max189.7 mean147.7 median163.6 std36.8 best-iNshh(25,225,25,188,190*)


###################
20191219
###################
#1. カオス時系列の学習と予測により得られる予測時系列のうち，ground truth(yg)に対する
#予測可能範囲hg(=h(yi,yg))がより大きい予測を求める手法として，LOOCV予測範囲と階層的クラスタリングを用いる
#手法を提案しているが、最終クラスタの中で予測可能範囲がより長い予測を特定することができていない。
#この問題を解決するため以下のstep1 とstep2 からなる手法を検討する。
#
# (1) まず，step1で、従来の階層的クラスタリングを行う：このstep1は, phase1 (1-1)と
# phase2(1-1)からなり，phase1は学習・予測,  phase2はアトラクタの類似度による予測時系列の絞り込み
#(tspredv3prob1.c)とKmeans法による２階層クラスタリング(kmeans2_kuro.py；２クラス分類するKmeans法を
#２階層行う→４クラスタが求まる)からなる。
#step1の実行後，各クラスタのLOOCV予測可能範囲 (hi-LOOCV=h(yi,Y_all\yi）の統計として
#min,max,mean, median, stdを求め,このうち，hi-LOOCVが最も長い(max)予測を行ったユニット数を
#N_{ij}(i=1,2,3,4;j=1,2,...)と表す．ここでi=1,2,3,4はクラスタ番号を表す。ただし要素数が1の
#クラスタはhi-LOOCVは求まらないので以下の処理では除外する．各クラスタで最大のhi-LOOCVをもつ
#予測は複数ある場合があり，それらをj=1,2,..で区別し、それらすべてについて以下の処理を行う。
# ただし、以下のいくつかの結果ではN_{ij}のうち最小のN_{ij}を用いれば、十分長いhgが得られる
#ことを示したい。（それ以外に最適なN_{ij}を求める手法は今のところ浮かんでいない）
#
# (2) step2では、step1で得られた最小のユニット数min(N_{ij})をもつCAN2に対し、
#乱数の種(seed)をn_seed(=50;seed=0,1,...,n_seed-1)を用いて，
#phase1(2-2):n_seed個の学習と予測、および
#phase2(2-2):アトラクタ類似度による絞り込みと２階層クラスタリングを行う。
#
#いくつかの実験として、 n_seed=30,50,100個, N_{ij}(i=1,2,3,4;j=1,...)に対し、予測初期時刻を
#tp0=2000,...,2300として行った。n_seed=30や100ではうまくいかない場合があり(?),
#以下、とりあえずn_seed=50でtp=2100,2200,...,4900について結果を出して検討したい。
#
#すべてのユニット数N_{ij}(i=1,2,3,4;j=1,...)でまあまあの結果が得られた(?)が、
#この検証を全部行うと時間がかかるので、とりあえず、最小のmin(N_{ij)での結果を検討したい。
#なお,min(N_{ij})を使うとより大きなユニット数での予測より過学習が少ないと考えられる。
#
#結果予想（希望的）：step1で求めたユニット数min(N_{ij})のCAN2を用いて
#step2でn_seed=50個に対する予測を行い、得られた50個の予測を２階層クラスタリングし、
#得られた最大４つのクラスタのうち要素数が最大のクラスタを選び、
#そのクラスタ中の最大のLOOCV予測範囲(hi-LOOCV)を持つ予測は、
#十分長い予測可能範囲hgをもつことを示したい。
#
#実験手順
#######
#(0) 0th-step 使用するディレクトリの設定
#######
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc
mkdir -p $d0
#######
#(1) step 1 従来の階層的クラスタリング
#######
#(1-0) 初期設定
#######
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc
export TP0="2000" 
#export 2000 2100 2200 2300 2400 2500 2600 2700 2800 2900 3000 3100 3200 3300 3400 3500 3600 3700 3800 3900 4000 4100 4200 4300 4400 4500 4600 4700 4800 4900
export N="N:5-300:5" Sth=0.5 n_seed="1" phase="" 
export ID="${n_seed}" #export ID=ID"${n_seed}-${Sth:2}" #Sth=0.5 -> S{Sth:2}=5  -> ID=ID1-5
#
##### export phase=2 #for avoiding the excesution of 1st phase again
#
#(1-1)&(1-2)
#
date > $d0/cmd-io-sum.dat
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -phase "$phase" -ID "$ID"
#
source $d0/d1.env #d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1
echo "###saved in d1=$d1"         >> $d0/cmd-io-sum.dat
#emacs $d1/cmd.sh;source $d1/cmd.sh  #edit cmd.sh if necessary with phase=1
cat $d1/cmd.sh >> $d0/cmd-io-sum.dat
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
date >> $d0/cmd-io-sum.dat
grep "hi-LOOCV@L2c" $d1/cmd.out 
grep "h(yi,yg)@L2c" $d1/cmd.out 
#emacs $d0/cmd-io-sum.dat&
#結果例TP0=2000
#hi-LOOCV@L2c0 with n14 min62.8 max276.8 mean234.8 median238.6 std50.9 best-iNshh(37,280,0,19,277*)(38,285,0,19,277*)
#hi-LOOCV@L2c1 with n5 min90.0 max166.2 mean129.1 median133.2 std34.1 best-iNshh(53,230,0,20,166*)
#hi-LOOCV@L2c2 with n38 min71.2 max257.7 mean207.3 median229.0 std45.7 best-iNshh(0,125,0,191,258*)
#hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(57,5,0,45,-1*)
#結果の見方（意味）
#hi-LOOCV@L2c<i>: 第L=2階層の<i>番目のクラスタのhi-LOOCVに関する統計
#n<n>: そのクラスタ内の要素数が<n>個
#min<min>:クラスタ内の hi-LOOCV の最小値
#max<max>:クラスタ内の hi-LOOCV の最大値
#mean<mean>:クラスタ内の hi-LOOCV の平均値
#median<median>:クラスタ内の hi-LOOCV のmedian
#std<std>:クラスタ内の hi-LOOCV の標準偏差(2乗平均平方根)、
#best-iNshh(0,125,0,191,258*)の見方
#第1要素i=0：予測時系列の番号（類似度で削除した後の通し番号）、
#第2要素N=125:ユニット数のCAN2で予測を行った
#第3要素s=0:全ての予測時系列中の通し番号（類似度で削除する前の番号）?
#第4要素191：この予測時系列のhg
#第5要素258：このクラスタの中で最長のhi-LOOCV;左の<max>と同じ値.
#            上の例ではL2c0には,maxが２つN=280,285ある
#この例では, N=230,280,285,125がN_{ij},この内N=125を用いてstep2を行う

#########
#(2) step2 step1で得られた各クラスタで求めたユニット数Nでn_seed=30で実験
#########
#(2-0-1) n_seedなどの設定
export n_seed=50 Sth=0.5 phase="" #TP0="2100"  
export ID="${n_seed}" #export ID=ID"${n_seed}-${Sth:2}" 
#
#(2-0-2) d1の設定（デフォールト）
source $d0/d1.env   #このファイル$d0/d1.env中にstep1の結果を保存したディレクトリが書いてある。
##d1の設定（再実験）特定のtp0に対する再実験を行いたいときは以下のコマンドでd1(step1で作ったもの）を設定
# export d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1
# export d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2300-2800k10N:5-300:5ID1
###
#(2-0-3) Nの設定（デフォールト）
source $d1/N-L2.env #ファイル$d1/N-L2.envの中にN_{ij}が記入してある
##Nの設定（再実験）$d1/N-L2.envからNを選んで設定
#export N=N:125 #export N=N:230,280,285,125
#
#(2-1)&(2-2)
date >> $d0/cmd-io-sum.dat
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -phase "$phase" -ID "$ID"
source $d0/d1.env #d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:5-300:5ID1-5
echo "#saved in d1=$d1"         >> $d0/cmd-io-sum.dat
tail -2 $d1/cmd.sh >> $d0/cmd-io-sum.dat
cp $d1/cmd.out $d1/cmd-Sth${Sth:2}.out
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/cmd-io-sum.dat 
date >> $d0/cmd-io-sum.dat
grep "hi-LOOCV@L2c" $d1/cmd.out 
grep "h(yi,yg)@L2c" $d1/cmd.out
#emacs $d0/cmd-io-sum.dat&
##########
#(2-3) (2-2)の再実験 (異なるNやSthでの実験を行う）
##########
N=N:125;ID=50;tp0=2000;Sth=0.5
N=N:55;ID=50;tp0=2100;Sth=0.5
N=N:50;ID=50;tp0=2200; #export N=N:50
N=N:70;ID=50;tp0=2300;Sth=0.5
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:${tp0}-`expr $tp0 + 500`k10${N}ID${ID}
bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 

## results
#n_seed=50 (30<n_seeds <100)で 要素数nがmaxのクラスタのh-LOOCV最大の予測が、h(yi,yg)が長い
#小さなN=55(<75<190) の結果良い(ずっと下参照？）（なぜ：過学習が少ない？）
##########

#tp0=2000
hi-LOOCV@L2c1 with n33 min136.5 max214.0 mean194.1 median202.5 std18.8 best-iNshh(33,125,33,184,214*) good hg=184 with max(hi-LOOCV)&n33
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(25,125,25,71,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(44,125,45,14,-1*)
hi-LOOCV@L2c2 with n14 min130.2 max169.5 mean158.5 median161.4 std10.6 best-iNshh(31,125,31,186,170*)

#tp0=2100
hi-LOOCV@L2c1 with n28 min68.7 max184.5 mean156.0 median164.8 std25.8 best-iNshh(39,55,41,323,184*) good hg=323 with max(hi-LOOCV)&n28
hi-LOOCV@L2c0 with n19 min113.6 max215.2 mean170.0 median174.3 std25.6 best-iNshh(15,55,16,94,215*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(29,55,31,54,-1*)

#tp0=2200
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,50,30,86,-1*)
hi-LOOCV@L2c0 with n44 min97.0 max173.2 mean158.1 median161.2 std13.4 best-iNshh(17,50,17,194,173*) good hg=194 with max(hi-LOOCV)&n44
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(35,50,35,103,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(31,50,31,103,-1*)

#tp0=2300
hi-LOOCV@L2c1 with n39 min88.6 max165.6 mean140.8 median144.9 std19.4 best-iNshh(7,70,7,168,166*) good hg=168 with max(hi-LOOCV)&n39
hi-LOOCV@L2c0 with n9 min77.9 max186.9 mean144.8 median157.4 std31.2 best-iNshh(26,70,27,68,187*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,70,31,31,-1*)
############
#(2-4)check correlation between hg and hi-LOOCV
############

############
#other results
############
export N=N:225,90,75,70
#tp0=2300 export N=N:225,90,75,70
N=N:225;ID=50;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2300-2800k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n8 min92.4 max269.4 mean217.4 median241.8 std58.8 best-iNshh(20,225,20,69,269*)
hi-LOOCV@L2c0 with n22 min71.7 max207.3 mean167.7 median181.3 std36.8 best-iNshh(33,225,33,67,207*) nmax
hi-LOOCV@L2c3 with n13 min67.3 max189.7 mean147.7 median163.6 std36.8 best-iNshh(25,225,25,188,190*) ***nmax2
hi-LOOCV@L2c2 with n7 min179.8 max251.5 mean207.6 median204.3 std25.1 best-iNshh(23,225,23,179,252*)
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n6 min156.0 max218.2 mean198.8 median203.1 std20.8 best-iNshh(8,90,8,79,218*)
hi-LOOCV@L2c0 with n25 min125.8 max191.7 mean169.8 median180.0 std19.4 best-iNshh(14,90,14,188,192*) nmax
hi-LOOCV@L2c3 with n5 min68.5 max204.5 mean170.8 median195.0 std51.8 best-iNshh(45,90,47,70,204*)
hi-LOOCV@L2c2 with n12 min132.1 max185.2 mean157.8 median158.7 std16.7 best-iNshh(24,90,26,68,185*)

#tp0=2300 export N=N:225,90,75,70
N=N:75;ID=50;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2300-2800k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n26 min128.2 max183.4 mean160.9 median164.4 std16.0 best-iNshh(40,75,40,167,183*)**nmax
hi-LOOCV@L2c0 with n9 min120.8 max187.8 mean158.6 median169.1 std21.4 best-iNshh(17,75,17,183,188*)
hi-LOOCV@L2c3 with n6 min124.0 max177.8 mean161.7 median164.7 std17.9 best-iNshh(19,75,19,66,178*)
hi-LOOCV@L2c2 with n9 min173.8 max286.4 mean230.0 median222.9 std33.4 best-iNshh(39,75,39,68,286*)

N=N:70;ID=50;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2300-2800k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n9 min77.9 max186.9 mean144.8 median157.4 std31.2 best-iNshh(26,70,27,68,187*)
hi-LOOCV@L2c0 with n39 min88.6 max165.6 mean140.8 median144.9 std19.4 best-iNshh(7,70,7,168,166*) ***nmax
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(30,70,31,31,-1*)

N=N:75;ID=50;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2300-2800k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 


N=N:70;ID=50;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2300-2800k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n5 min167.5 max196.2 mean183.1 median192.0 std12.8 best-iNshh(45,225,0,63,196*)
hi-LOOCV@L2c0 with n44 min116.2 max224.5 mean198.6 median201.5 std21.0 best-iNshh(0,90,0,66,224*) nmax??
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(54,45,0,156,-1*)
hi-LOOCV@L2c2 with n5 min185.8 max257.2 mean220.6 median201.8 std30.5 best-iNshh(49,75,0,202,257*)(50,70,0,177,257*)

#tp0=2100 export N=N:190,75,55
N=N:190;ID=50;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n21 min149.6 max209.9 mean193.6 median200.7 std16.1 best-iNshh(33,190,34,91,210*)
hi-LOOCV@L2c0 with n14 min181.2 max282.7 mean250.0 median259.6 std28.8 best-iNshh(39,190,40,95,283*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(35,190,36,117,-1*)
hi-LOOCV@L2c2 with n13 min111.1 max211.0 mean167.1 median161.2 std24.7 best-iNshh(15,190,15,100,211*)
#
N=N:75;ID=50;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(40,75,40,96,-1*)
hi-LOOCV@L2c0 with n18 min144.2 max215.5 mean186.7 median195.9 std23.3 best-iNshh(6,75,6,91,215*)
hi-LOOCV@L2c3 with n7 min125.8 max169.0 mean152.4 median159.0 std17.1 best-iNshh(10,75,10,146,169*)
hi-LOOCV@L2c2 with n22 min147.5 max236.2 mean204.8 median209.8 std23.0 best-iNshh(12,75,12,203,236*) ***nmax
#
###
N=N:55;ID=100;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n50 min112.4 max194.3 mean163.4 median168.0 std21.5 best-iNshh(39,55,41,323,194*) ***stdMax#2 nmax
hi-LOOCV@L2c0 with n46 min98.8 max188.8 mean154.2 median161.0 std25.0 best-iNshh(34,55,36,93,189*)  stdMax*
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(29,55,31,54,-1*)
####################################
N=N:55;ID=80;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n35 min115.1 max197.1 mean161.2 median164.1 std23.2 best-iNshh(34,55,36,93,197*)
hi-LOOCV@L2c0 with n42 min70.8 max183.1 mean154.1 median165.5 std24.7 best-iNshh(39,55,41,323,183*)***#stdmax nmax
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(29,55,31,54,-1*)

N=N:55;ID=50;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n28 min68.7 max184.5 mean156.0 median164.8 std25.8 best-iNshh(39,55,41,323,184*)***#stdMax nmax
hi-LOOCV@L2c0 with n19 min113.6 max215.2 mean170.0 median174.3 std25.6 best-iNshh(15,55,16,94,215*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(29,55,31,54,-1*)

N=N:55;ID=30;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID${ID}
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n12 min68.9 max186.1 mean152.4 median165.9 std30.4 best-iNshh(21,55,23,293,186*) ***nmax
hi-LOOCV@L2c0 with n4 min112.0 max143.3 mean132.3 median137.0 std12.7 best-iNshh(7,55,8,99,143*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(16,55,17,89,-1*)
hi-LOOCV@L2c2 with n11 min141.2 max224.8 mean177.6 median186.8 std25.9 best-iNshh(15,55,16,94,225*) 


###N=N:55;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID20
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c0 with n11 min112.4 max178.2 mean160.2 median166.8 std17.0 best-iNshh(13,55,14,204,178*) ***#stdMax#2
hi-LOOCV@L2c3 with n6 min129.2 max253.4 mean196.3 median202.0 std37.6 best-iNshh(15,55,16,94,253*)  xxx#stdMax#1
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(16,55,17,89,-1*)

N=N:190;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID30
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n19 min160.4 max241.8 mean216.1 median218.2 std18.3 best-iNshh(17,190,17,92,242*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(20,190,20,90,-1*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(18,190,18,146,-1*)
hi-LOOCV@L2c2 with n7 min152.2 max252.2 mean198.3 median200.2 std30.9 best-iNshh(15,190,15,100,252*)  #stdMax

N=N:75;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID30
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n13 min136.5 max239.0 mean202.3 median207.8 std28.8 best-iNshh(12,75,12,203,239*)
hi-LOOCV@L2c0 with n4 min91.3 max178.3 mean148.8 median162.8 std35.3 best-iNshh(10,75,10,146,178*)  #stdMax
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(24,75,24,96,-1*)
hi-LOOCV@L2c2 with n12 min142.4 max225.5 mean199.8 median201.8 std22.9 best-iNshh(4,75,4,91,226*)(6,75,6,91,226*)

N=N:55;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID30
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(18,190,18,146,-1*)
hi-LOOCV@L2c0 with n7 min152.2 max252.2 mean198.3 median200.2 std30.9 best-iNshh(15,190,15,100,252*) #stdMax
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(20,190,20,90,-1*)
hi-LOOCV@L2c2 with n19 min160.4 max241.8 mean216.1 median218.2 std18.3 best-iNshh(17,190,17,92,242*)
##############

N=N:190;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID30
Sth=0.8;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(20,190,20,90,-1*)
hi-LOOCV@L2c0 with n18 min188.5 max246.2 mean222.6 median222.2 std13.9 best-iNshh(17,190,17,92,246*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(18,190,18,146,-1*)
hi-LOOCV@L2c2 with n5 min173.2 max244.0 mean194.5 median179.8 std26.3 best-iNshh(15,190,15,100,244*) stdMax
###
N=N:75;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID30
Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n4 min91.3 max178.3 mean148.8 median162.8 std35.3 best-iNshh(10,75,10,146,178*) stdMax#1
hi-LOOCV@L2c0 with n13 min136.5 max239.0 mean202.3 median207.8 std28.8 best-iNshh(12,75,12,203,239*) stdMax#2
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(24,75,24,96,-1*)
hi-LOOCV@L2c2 with n12 min142.4 max225.5 mean199.8 median201.8 std22.9 best-iNshh(4,75,4,91,226*)(6,75,6,91,226*)
#
N=N:75;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10${N}ID30
Sth=0.8;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(20,75,24,96,-1*)
hi-LOOCV@L2c0 with n12 min142.4 max225.5 mean199.8 median201.8 std22.9 best-iNshh(3,75,4,91,226*)(4,75,6,91,226*)
hi-LOOCV@L2c3 with n9 min138.2 max233.5 mean198.9 median206.2 std27.4 best-iNshh(9,75,12,203,234*) stdMax#2
hi-LOOCV@L2c2 with n4 min91.3 max178.3 mean148.8 median162.8 std35.3 best-iNshh(7,75,10,146,178*)  stdMax#1
###
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:55ID30
N=N:55;Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n4 min112.0 max143.3 mean132.3 median137.0 std12.7 best-iNshh(7,55,8,99,143*)
hi-LOOCV@L2c0 with n12 min68.9 max186.1 mean152.4 median165.9 std30.4 best-iNshh(21,55,23,293,186*) ***stdMax
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(16,55,17,89,-1*)
hi-LOOCV@L2c2 with n11 min141.2 max224.8 mean177.6 median186.8 std25.9 best-iNshh(15,55,16,94,225*)

d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:55ID30
N=N:55;Sth=0.8;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n12 min68.9 max186.1 mean152.4 median165.9 std30.4 best-iNshh(20,55,23,293,186*) ***stdMax
hi-LOOCV@L2c0 with n4 min112.0 max143.3 mean132.3 median137.0 std12.7 best-iNshh(7,55,8,99,143*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(16,55,17,89,-1*)
hi-LOOCV@L2c2 with n10 min137.3 max233.4 mean185.7 median191.5 std26.6 best-iNshh(15,55,16,94,233*)
#############


#############
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:190,75ID30
N=N:190,75;Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n13 min178.8 max271.2 mean231.9 median242.8 std28.8 best-iNshh(36,190,11,94,271*)
hi-LOOCV@L2c0 with n21 min146.9 max223.8 mean200.7 median217.9 std23.4 best-iNshh(4,75,4,91,224*)
hi-LOOCV@L2c3 with n13 min89.6 max237.2 mean199.7 median214.1 std38.2 best-iNshh(15,190,22,98,237*)
hi-LOOCV@L2c2 with n13 min151.8 max209.2 mean179.3 median185.5 std20.0 best-iNshh(54,75,3,205,209*) stdMin#1

d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:190,75ID30
Sth=0.8;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n20 min146.9 max226.3 mean202.6 median220.1 std25.0 best-iNshh(4,75,4,91,226*)
hi-LOOCV@L2c0 with n13 min178.8 max271.2 mean231.9 median242.8 std28.8 best-iNshh(28,190,11,94,271*)
hi-LOOCV@L2c3 with n6 min91.0 max190.0 mean161.2 median170.1 std33.6 best-iNshh(50,75,10,146,190*)   stdMax
hi-LOOCV@L2c2 with n14 min167.5 max231.2 mean198.5 median194.0 std17.8 best-iNshh(15,190,15,100,231*)

d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:190,75ID30
Sth=0.9;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n16 min146.7 max229.9 mean203.6 median218.5 std25.9 best-iNshh(3,75,4,91,230*)    #no good prediction with Sth=0.9
hi-LOOCV@L2c0 with n10 min155.3 max268.0 mean231.2 median246.9 std32.0 best-iNshh(21,190,23,94,268*)
hi-LOOCV@L2c3 with n6 min177.8 max209.6 mean192.5 median192.3 std11.6 best-iNshh(28,75,25,97,210*)
hi-LOOCV@L2c2 with n5 min91.0 max169.8 mean146.8 median159.0 std28.5 best-iNshh(32,75,20,99,170*)




d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:190,55ID30
N=N:190,55;Sth=0.5;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n16 min68.9 max192.8 mean160.2 median170.4 std30.0 best-iNshh(48,55,23,293,193*) *std1stMax
hi-LOOCV@L2c0 with n9 min111.5 max186.0 mean155.3 median151.6 std23.6 best-iNshh(35,190,14,98,186*)
hi-LOOCV@L2c3 with n12 min181.5 max274.5 mean251.8 median260.8 std24.7 best-iNshh(9,55,13,95,275*)
hi-LOOCV@L2c2 with n21 min116.4 max219.2 mean194.8 median208.9 std28.9 best-iNshh(4,55,24,92,219*)


d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:190,55ID30
Sth=0.9;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
hi-LOOCV@L2c1 with n22 min161.0 max243.9 mean214.7 median216.6 std21.0 best-iNshh(7,190,6,93,244*)
hi-LOOCV@L2c0 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(27,55,17,89,-1*)
hi-LOOCV@L2c3 with n13 min110.7 max174.2 mean149.4 median154.1 std17.9 best-iNshh(30,55,23,293,174*) stdMin
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(36,55,11,68,-1*)

Sth=0.8 N=N:190,55
hi-LOOCV@L2c1 with n16 min68.9 max188.2 mean158.1 median168.8 std28.7 best-iNshh(37,55,23,293,188*) *std2ndMax
hi-LOOCV@L2c0 with n6 min112.0 max157.0 mean139.9 median140.7 std14.8 best-iNshh(33,190,14,98,157*)
hi-LOOCV@L2c3 with n20 min116.3 max222.9 mean199.7 median213.9 std29.1 best-iNshh(4,55,24,92,223*)
hi-LOOCV@L2c2 with n12 min181.5 max274.5 mean251.8 median260.8 std24.7 best-iNshh(8,55,13,95,275*)

#tp0=2300 export N=N:225,90,75,70
Sth=0.5
hi-LOOCV@L2c1 with n5 min167.5 max196.2 mean183.1 median192.0 std12.8 best-iNshh(45,225,0,63,196*)
hi-LOOCV@L2c0 with n44 min116.2 max224.5 mean198.6 median201.5 std21.0 best-iNshh(0,90,0,66,224*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(54,45,0,156,-1*)
hi-LOOCV@L2c2 with n5 min185.8 max257.2 mean220.6 median201.8 std30.5 best-iNshh(49,75,0,202,257*)(50,70,0,177,257*)with Max-std

#step2 otheway with tp0=2100  n_seed=20
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:190,55,75ID20;
Sth=0.95;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
Sth=0.8
hi-LOOCV@L2c1 with n11 min100.8 max266.3 mean229.1 median245.4 std48.4 best-iNshh(9,190,11,94,266*) std1stbiggest
hi-LOOCV@L2c0 with n18 min116.2 max211.4 mean188.8 median198.2 std26.5 best-iNshh(6,75,4,91,211*)
hi-LOOCV@L2c3 with n14 min68.8 max189.4 mean158.7 median170.0 std32.4 best-iNshh(37,55,14,204,189*)*** with std2ndbiggest *-n
hi-LOOCV@L2c2 with n10 min149.4 max178.4 mean165.9 median164.3 std9.1 best-iNshh(29,190,14,98,178*)
$h=0.5
i-LOOCV@L2c1 with n14 min69.1 max212.7 mean171.2 median177.2 std38.8 best-iNshh(33,75,3,205,213*) *** with 2nd-biggest-std -n
hi-LOOCV@L2c0 with n15 min151.1 max200.5 mean173.9 median168.9 std16.6 best-iNshh(15,190,14,98,200*)
hi-LOOCV@L2c3 with n19 min116.2 max209.4 mean187.5 median196.6 std25.0 best-iNshh(6,75,9,91,209*)
hi-LOOCV@L2c2 with n11 min100.8 max266.3 mean229.1 median245.4 std48.4 best-iNshh(13,190,11,94,266*) #std1biggest
Sth=0.9
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(33,55,11,68,-1*)
hi-LOOCV@L2c0 with n12 min101.9 max166.1 mean152.0 median155.6 std16.1 best-iNshh(21,55,10,228,166*) ***std2ndbiggest
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(32,75,11,97,-1*)
hi-LOOCV@L2c2 with n19 min135.9 max241.2 mean203.0 median209.9 std29.3 best-iNshh(4,190,6,93,241*)
Sth=0.95
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(11,55,17,89,-1*)
hi-LOOCV@L2c0 with n11 min141.9 max234.2 mean199.9 median203.2 std28.2 best-iNshh(2,190,17,92,234*) NG
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(14,75,1,100,-1*)
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(15,75,11,97,-1*)

#step2 otheway with tp0=2100  n_seed=30
Sth=0.8;d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10N:190,55,75ID30;bash $d1/cmd.sh;grep "hi-LOOCV@L2c" $d1/cmd.out 
#Sth=0.8
hi-LOOCV@L2c1 with n18 min68.8 max206.0 mean169.9 median181.1 std32.5 best-iNshh(45,75,28,359,206*) ***2nd-biggest-std -n
hi-LOOCV@L2c0 with n16 min111.8 max177.1 mean162.6 median167.8 std15.1 best-iNshh(46,190,14,98,177*)
hi-LOOCV@L2c3 with n15 min100.9 max269.0 mean231.4 median240.9 std42.0 best-iNshh(4,55,16,94,269*)
hi-LOOCV@L2c2 with n30 min116.3 max229.0 mean202.3 median220.4 std29.3 best-iNshh(2,55,24,92,229*)
#Sth=0.9
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,55,11,68,-1*)
hi-LOOCV@L2c0 with n19 min110.2 max184.9 mean156.9 median159.3 std18.3 best-iNshh(37,55,23,293,185*)***2nd-biggest-n and std
hi-LOOCV@L2c3 with n4 min105.0 max176.0 mean141.7 median142.8 std34.2 best-iNshh(32,75,24,96,176*)
hi-LOOCV@L2c2 with n32 min137.3 max230.4 mean212.6 median220.6 std22.5 best-iNshh(9,75,4,91,230*)
#Sth=0.9
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,55,11,68,-1*)
hi-LOOCV@L2c0 with n19 min110.2 max184.9 mean156.9 median159.3 std18.3 best-iNshh(37,55,23,293,185*) 2ndlargest-std -n
hi-LOOCV@L2c3 with n4 min105.0 max176.0 mean141.7 median142.8 std34.2 best-iNshh(32,75,24,96,176*)
hi-LOOCV@L2c2 with n32 min137.3 max230.4 mean212.6 median220.6 std22.5 best-iNshh(9,75,4,91,230*)
#Sth=0.95
hi-LOOCV@L2c1 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(18,55,17,89,-1*)
hi-LOOCV@L2c0 with n18 min110.2 max230.2 mean199.3 median211.0 std31.8 best-iNshh(4,55,24,92,230*)
hi-LOOCV@L2c3 with n5 min112.2 max147.5 mean135.8 median140.0 std12.2 best-iNshh(20,75,8,149,148*)2ndlargest-std -n
hi-LOOCV@L2c2 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(21,75,11,97,-1*)


###################
20191211
###################
(1)
#1st-phase
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred;export d0=$d00/$fbc
export N="N:5-300:5" Sth=0.5 n_seed="1" TP0="2100" step="" ID=1
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
source $d0/d1.env
echo "#saved in d1=$d1"         >> $d0/resultall.dat
tail -2 $d1/cmd.sh >> $d0/resultall.dat
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/resultall.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/resultall.dat
#2nd-phase

source $d1/N-L2.env
export Sth=0.8 n_seed=30
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -Sth $Sth -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"

source $d0/d1.env
echo "#saved in d1=$d1"         >> $d0/resultall.dat
tail -2 $d1/cmd.sh >> $d0/resultall.dat
grep "hi-LOOCV@L2c" $d1/cmd.out >> $d0/resultall.dat
grep "h(yi,yg)@L2c" $d1/cmd.out >> $d0/resultall.dat

cat $d0/resultall.dat
#saved in d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:90,225,75,70ID2
hi-LOOCV@L2c1 with n4 min179.7 max310.7 mean244.5 median243.8 std46.4 best-iNshh(75,90,11,97,311*)
hi-LOOCV@L2c0 with n40 min121.3 max208.0 mean167.4 median170.3 std23.0 best-iNshh(18,225,12,92,208*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(74,70,7,99,-1*)
hi-LOOCV@L2c2 with n33 min174.2 max243.6 mean213.9 median213.1 std20.5 best-iNshh(4,75,11,280,244*)
h(yi,yg)@L2c1 with n4 min97.0 max105.0 mean101.0 median101.0 std4.0 best-iNshh(76,225,11,105*,241)(77,70,10,105*,247)
h(yi,yg)@L2c0 with n40 min87.0 max96.0 mean90.8 median90.0 std2.5 best-iNshh(71,225,6,96*,123)(73,70,15,96*,121)
h(yi,yg)@L2c3 with n1 min99.0 max99.0 mean99.0 median99.0 std0.0 best-iNshh(74,70,7,99*,-1)
h(yi,yg)@L2c2 with n33 min99.0 max441.0 mean235.6 median228.0 std71.9 best-iNshh(3,225,16,441*,229)
#saved in d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:90,225,75,70ID2
hi-LOOCV@L2c1 with n40 min121.3 max208.0 mean167.4 median170.3 std23.0 best-iNshh(18,225,12,92,208*)
hi-LOOCV@L2c0 with n4 min179.7 max310.7 mean244.5 median243.8 std46.4 best-iNshh(75,90,11,97,311*)
hi-LOOCV@L2c3 with n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(74,70,7,99,-1*)
hi-LOOCV@L2c2 with n33 min174.2 max243.6 mean213.9 median213.1 std20.5 best-iNshh(4,75,11,280,244*)
h(yi,yg)@L2c1 with n40 min87.0 max96.0 mean90.8 median90.0 std2.5 best-iNshh(71,225,6,96*,123)(73,70,15,96*,121)
h(yi,yg)@L2c0 with n4 min97.0 max105.0 mean101.0 median101.0 std4.0 best-iNshh(76,225,11,105*,241)(77,70,10,105*,247)
h(yi,yg)@L2c3 with n1 min99.0 max99.0 mean99.0 median99.0 std0.0 best-iNshh(74,70,7,99*,-1)
h(yi,yg)@L2c2 with n33 min99.0 max441.0 mean235.6 median228.0 std71.9 best-iNshh(3,225,16,441*,229)
####################################


#(1-1)
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:5-300:5" n_seed="1" TP0="2400" step="" ID=1;export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
source $d0/d1.env
grep "L2c" $d1/cmd.out
L2c0:h-LOOCV with  n51 min148.6 max241.8 mean222.4 median229.4 std19.1 best-iNshh(6,290,0,225,242*)***
L2c1:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(51,5,0,87,-1*)
L2c2:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,30,0,56,-1*)
L2c3:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,25,0,56,-1*)

L2c1:h(yi,yg) with n1 min87.0 max87.0 mean87.0 median87.0 std0.0 best-iNshh(51,5,0,87*,-1)
L2c0:h(yi,yg) with n51 min146.0 max354.0 mean234.2 median230.0 std40.0 best-iNshh(20,200,0,354*,232)
L2c3:h(yi,yg) with n1 min56.0 max56.0 mean56.0 median56.0 std0.0 best-iNshh(55,25,0,56*,-1)
L2c2:h(yi,yg) with n1 min56.0 max56.0 mean56.0 median56.0 std0.0 best-iNshh(56,30,0,56*,-1)



#(1-1)
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:5-300:5" n_seed="1" TP0="2300" step="" ID=1;export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
source $d0/d1.env
grep "L2c" $d1/cmd.out
L2c0:h-LOOCV with  n5 min167.5 max196.2 mean183.1 median192.0 std12.8 best-iNshh(45,225,0,63,196*)
L2c1:h-LOOCV with  n44 min116.2 max224.5 mean198.6 median201.5 std21.0 best-iNshh(0,90,0,66,224*)
L2c2:h-LOOCV with  n5 min185.8 max257.2 mean220.6 median201.8 std30.5 best-iNshh(49,75,0,202,257*)(50,70,0,177,257*)***
L2c3:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(54,45,0,156,-1*)

L2c1:h(yi,yg) with n44 min65.0 max69.0 mean66.3 median66.0 std0.8 best-iNshh(43,200,0,69*,116)
L2c0:h(yi,yg) with n5 min63.0 max63.0 mean63.0 median63.0 std0.0 best-iNshh(44,195,0,63*,192)(45,225,0,63*,196)(46,180,0,63*,192)(47,175,0,63*,168)(48,170,0,63*,168)
L2c3:h(yi,yg) with n1 min156.0 max156.0 mean156.0 median156.0 std0.0 best-iNshh(54,45,0,156*,-1)
L2c2:h(yi,yg) with n5 min166.0 max202.0 mean181.0 median178.0 std11.8 best-iNshh(49,75,0,202*,257)

#(1-2)
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:75,190" n_seed=20 TP0="2100" step="" ID=2;export d0=$d00/$fbc
source $d1/N-L2.env; TP0~2300
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
source $d0/d1.env
grep "L2c" $d1/cmd.out

L2c0:h-LOOCV with  n33 min174.2 max243.6 mean213.9 median213.1 std20.5 best-iNshh(4,75,11,280,244*)***
L2c1:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0      std0.0  best-iNshh(74,70,7,99,-1*)
L2c2:h-LOOCV with  n40 min121.3 max208.0 mean167.4 median170.3 std23.0 best-iNshh(18,225,12,92,208*)
L2c3:h-LOOCV with  n4 min179.7 max310.7 mean244.5 median243.8  std46.4* best-iNshh(75,90,11,97,311*)

L2c1:h(yi,yg) with n1 min99.0 max99.0 mean99.0 median99.0     std0.0   best-iNshh(74,70,7,99*,-1)
L2c0:h(yi,yg) with n33 min99.0 max441.0 mean235.6 median228.0 std71.9* best-iNshh(3,225,16,441*,229)***
L2c3:h(yi,yg) with n4 min97.0 max105.0 mean101.0 median101.0  std4.0   best-iNshh(76,225,11,105*,241)(77,70,10,105*,247)
L2c2:h(yi,yg) with n40 min87.0 max96.0 mean90.8 median90.0    std2.5   best-iNshh(71,225,6,96*,123)(73,70,15,96*,121)


#(1) TP0=2200
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:5-300:5" n_seed="1" TP0="2200" step="" ID=1;export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
source $d0/d1.env
grep "L2c" $d1/cmd.out
L2c1:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(54,35,0,102,-1*)
L2c0:h-LOOCV with  n52 min127.4 max237.3 mean203.5 median194.7 std22.0 best-iNshh(0,50,0,166,237*)***
L2c2:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(55,40,0,72,-1*)

L2c1:h(yi,yg) with n1 min102.0 max102.0 mean102.0 median102.0  std0.0  best-iNshh(54,35,0,102*,-1)
L2c0:h(yi,yg) with n52 min127.0 max279.0 mean185.5 median166.5 std41.6* best-iNshh(28,270,0,279*,193)(29,125,0,279*,193)
L2c2:h(yi,yg) with n1 min72.0 max72.0 mean72.0 median72.0      std0.0 best-iNshh(55,40,0,72*,-1)



#(1)
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:5-300:5" n_seed="1" TP0="2100" step="" ID=1;export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
source $d0/d1.env
grep "L2c" $d1/cmd.out
L2c1:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0      std0.0  best-iNshh(47,80,0,90,-1*)
L2c0:h-LOOCV with  n47 min173.8 max259.8 mean236.8 median237.2 std15.7* best-iNshh(0,190,0,91,260*)
L2c3:h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0      std0.0   best-iNshh(56,45,0,98,-1*)
L2c2:h-LOOCV with  n7 min188.7 max217.5 mean206.6 median214.7  std11.7  best-iNshh(48,55,0,321,218*)(50,75,0,99,218*) ***

L2c1:h(yi,yg) with n1 min90.0 max90.0 mean90.0 median90. 0   std0.0 best-iNshh(47,80,0,90*,-1)
L2c0:h(yi,yg) with n47 min90.0 max94.0 mean91.5 median91.0   std0.8 best-iNshh(17,245,0,94*,244)
L2c3:h(yi,yg) with n1 min98.0 max98.0 mean98.0 median98.0    std0.0 best-iNshh(56,45,0,98*,-1)
L2c2:h(yi,yg) with n7 min99.0 max321.0 mean177.7 median196.0 std77.9* best-iNshh(48,55,0,321*,218)***
source $d1/N-L2.env
#export N=N:190,55,75
###############

(1-2)
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-300:5ID1
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:75,190" n_seed=20 TP0="2100" step="" ID=2;export d0=$d00/$fbc
source $d1/N-L2.env
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
source $d0/d1.env
grep "L2c" $d1/cmd.out
L2c1:h-LOOCV with  n11 min100.8 max266.3 mean229.1 median245.4 std48.4 best-iNshh(13,190,11,94,266*)
L2c0:h-LOOCV with  n19* min116.2 max209.4 mean187.5 median196.6 std25.0 best-iNshh(6,75,9,91,209*)
L2c3:h-LOOCV with  n19* min150.7 max199.4 mean175.3 median171.3 std14.9 best-iNshh(15,190,14,98,199*)
L2c2:h-LOOCV with  n10 min69.1 max232.7 mean181.5 median196.1  std50.1* best-iNshh(53,75,14,205,233*)***maximum std?

L2c1:h(yi,yg) with n11 min93.0 max97.0 mean94.0 median94.0    std1.2   best-iNshh(57,75,11,97*,101)
L2c0:h(yi,yg) with n19 min88.0 max92.0 mean90.6 median91.0    std1.1   best-iNshh(1,55,19,92*,206)(17,190,17,92*,207)(26,190,2,92*,197)(39,190,3,92*,197)
L2c3:h(yi,yg) with n19 min97.0 max321.0 mean136.8 median100.0 std54.4* best-iNshh(11,55,0,321*,194)***
L2c2:h(yi,yg) with n10 min68.0 max265.0 mean201.7 median205.0 std51.3  best-iNshh(56,55,15,265*,122)

###################
20191211
###################
#(0) program check
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:10-20:10" n_seed="1" TP0="2100" step="" ID=1
export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
#Step2: Results are saved in ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/cmd.out

#(1-1)
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:5-300:5" n_seed="1" TP0="2100" step="" ID=1;export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"

grep "export d1" $d0/cmd.sh >tmp/tmp.env;source tmp/tmp.env
grep L2c $d1/cmd.out
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-300:5ID1

grep kmeans ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-300:5ID1/cmd.sh
python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-300:5ID1 -fnyp tspSth.dat -fnyg yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0 -tp0 2100 >> ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-300:5ID1/cmd.out

L2c0: h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(56,45,0,98,-1*)
L2c0: h(yi,yg) with n1 min98.0 max98.0 mean98.0 median98.0 std0.0 best-iNshh(56,45,0,98*,-1)
L2c1: h-LOOCV with  n7 min188.7 max217.5 mean206.6 median214.7 std11.7 best-iNshh(48,55,0,321,218*)(50,75,0,99,218*) ***321,218*
L2c1: h(yi,yg) with n7 min99.0 max321.0 mean177.7 median196.0 std77.9 best-iNshh(48,55,0,321*,218)
L2c2: h-LOOCV with  n47 min173.8 max259.8 mean236.8 median237.2 std15.7 best-iNshh(0,190,0,91,260*)
L2c2: h(yi,yg) with n47 min90.0 max94.0 mean91.5 median91.0 std0.8 best-iNshh(17,245,0,94*,244)
L2c3: h-LOOCV with  n1 min-1.0 max-1.0 mean-1.0 median-1.0 std0.0 best-iNshh(47,80,0,90,-1*)
L2c3: h(yi,yg) with n1 min90.0 max90.0 mean90.0 median90.0 std0.0 best-iNshh(47,80,0,90*,-1)

(1-2)
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-300:5ID1
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:75,190" n_seed=20 TP0="2100" step="" ID=2;export d0=$d00/$fbc
source $d1/N-L2.env
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"


(1-2)
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:75,190" n_seed=30 TP0="2100" step="" ID=2;export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
#python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:55,190ID3 -fnyp tspSth.dat -fnyg yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0 -tp0 2100 
L2c0: h-LOOCV with  n21 min116.4 max219.2 mean194.8 median208.9 std28.9 best-iNshh(4,55,24,92,219*)
L2c0: h(yi,yg) with n21 min89.0 max92.0 mean90.8 median91.0 std0.9 best-iNshh(0,55,19,92*,209)(4,55,24,92*,219)(17,190,17,92*,208)(24,190,3,92*,213)(25,190,2,92*,199)
L2c1: h-LOOCV with  n12 min181.5 max274.5 mean251.8 median260.8 std24.7 best-iNshh(9,55,13,95,275*)
L2c1: h(yi,yg) with n12 min93.0 max95.0 mean93.8 median94.0 std0.7 best-iNshh(9,55,13,95*,275)(14,55,4,95*,259)
L2c2: h-LOOCV with  n16 min68.9 max192.8 mean160.2 median170.4 std30.0 best-iNshh(48,55,23,293,193*)****
L2c2: h(yi,yg) with n16 min68.0 max321.0 mean192.6 median176.0 std65.7 best-iNshh(29,55,0,321*,180)
L2c3: h-LOOCV with  n9 min111.5 max186.0 mean155.3 median151.6 std23.6 best-iNshh(35,190,14,98,186*)
L2c3: h(yi,yg) with n9 min97.0 max174.0 mean106.7 median98.0 std23.8 best-iNshh(30,190,25,174*,152)





export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:5-200:5" n_seed="1" TP0="2200" step="" ID=1
export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"

(1-3)
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp d00=../../result-chaospred N="N:5-200:5" n_seed="1" TP0="2300" step="" ID=1
export d0=$d00/$fbc
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"



python kmeans2_kuro.py -d1 ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-200:5ID1 -fnyp tspSth.dat -fnyg yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey 15 -hh 30 -DISP 0 -tp0 2100 

grep "saved in d1" ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/cmd.out
#Results2 are saved in d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-200:5ID1
d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2100-2600k10NN:5-200:5ID1
cat $d1/Ns-L2.env
source $d1/Ns-L2.env
export N_S="N:20 N:105 N:15" n_seed_S="50 50 50" ID=2
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -d00 $d00 -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"
L2 c1 n=23 h0=105  iY= [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 34]
L2 c0 n=13 h0=95  iY= [11, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 35]
L2 c2 n=1 h0=0  iY= [36]


export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp N="N:5-300:5" n_seed="1" TP0="2100" step="" ID=1
python loocv-predhorizon.py -ddc "$ddc" -fbc "$fbc" -N "$N" -n_seed "$n_seed" -TP0 "$TP0" -step "$step" -ID "$ID"


###################
20191209 LOOCV <- 20171031 in can2b/readme.timeseries
###################
###(1)
export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp N_S="N:5-300:5" n_seed_S="1" TP0="2100" step="" ID=1
source loocv-PredHrzn.sh
#export step=2; source loocv-PredHrzn.sh #for doing step2 to confirm
###(2)
source $d1/Ns-L2.env 
export step="" ID=2;source loocv-PredHrzn.sh

export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp N=N:5-300:5 n_seed=1 TP0="3000 4000"
bash loocv-PredHrzn.sh

export ddc=../../chaos.data fbc=lorenz1e-8T0.025n10000p256m1_gmp N=N:5-300:5 n_seed=1 TP0="2100" step=2
bash loocv-PredHrzn.sh
source $d1/Ns-L2.env
export step="";sh loocv-PredHrzn.sh

###################
20191206 LOOCV <- 20171031 in can2b/readme.timeseries
###################
make
d00=../../result-chaospred; mkdir -p $d00
make data-clean
export fnlog=chaospred2019.log
export Ey=15
cat /dev/null > $fnlog
#../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt*
fb=lorenz1e-8T0.025n10000p256m1_gmp
#
d0=$d00/$fb; mkdir -p $d0
fny=../../chaos.data/${fb}.txt # fny=~/sotu/2017/chaos/data/${fb}.txt
export N=N:10-300:10; # export N=N:5-300:5; #export N=N:5-300:2; #
export tr1=2000; #tr1=5000;
export n_seed=50
for tp0 in 2000; do #for research study
#for tp0 in 2000 2100 2200 2300 2400 2500 2600 2700 2800 2900 3000 3100 3200 3300 3400 3500 3600 3700 3800 3900 4000 4100 4200 4300 4400 4500 4600 4700 4800 4900; do #
rm --force lossall.dat tspall.dat tspall_id.dat
export tp1=`bc.sh ${tp0}+500` #export tp1=`expr $tp0 + 500` #export tp1=`expr $tp0 + 800` #
export t=0-${tr1}:${tp0}-${tp1};
export K="10" #export K="8" #
export KS=${K//+/ }; #replace "+" by " "
for k in ${KS}; do
for s in `seq 1 ${n_seed}`;do
export cmd="./tspredv3 $fny $t mp:1:1:1 DiffMode:0 Hosei:0 $N M:1-1:1 ib:0:0:0:0 rsa:-1:1:1 k:${k} y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:100 vt:0.5 vr:10 lossall:1 DISP:0 e4t:0 e4p:0 nop:1 seed:${s}"
#export cmd="./tspredv3 $fny $t mp:1:1:1 DiffMode:0 Hosei:0 $N M:1-1:1 ib:0:0:0:0 rsa:2:0.7:1:50 k:${k} y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:100 vt:0.5 vr:10 lossall:1 DISP:0 e4t:0 e4p:0 seed:${s}"
echo $cmd;time $cmd ##yp(t) saved in tspall.dat
done # for s
done # for k
#
export d1=$d0/t${t}k${K}${N} ##export d1=../result-timeseries/t${t}k${K}${N}
mkdir -p $d1
for f in lossall.dat tspall.dat tspall.plt; do if [ -e $f ]; then cp $f $d1; fi; done #tspall.plt only for DISP:2
###(1.2) choose best prediction and probability
cmd1="tspredv3prob1 ds:$d1 at:-18.5_18.5:40 Sth:.5 e4H:$Ey Hth:.8,0,999 ftr:$fny DISP:0 "  #change Sth if necessary
#cmd1="tspredv3prob1 ds:$d1 at:-18.5_18.5:40 Sth:.5 e4H:$Ey Hth:.8,0,999 ftr:$fny DISP:2"  #change Sth if necessary
#cmd1="tspredv3prob1 ds:$d1 at:-18.5_18.5:40 Sth:.9 e4H:$Ey Hth:.8,0,999 ftr:$fny DISP:0"  #change Sth if necessary
echo "$cmd1" >> $fnlog
$cmd1 >> $fnlog
##
## $fnlog contains data 'xN15(S0.117389),5<15<300 ,oN20(S0.486892),5<20<300 '
##saved tspAll.dat tspSth.dat yg.dat tspp.dat tp/typ.dat
##
for f in SLH.dat; do cp $f $d1; done
echo "###Confirm by '$cmd1'";
date
done # for tp0

##
###
cat $fnlog |awk '{if(substr($1,1,8)=="tspredv3") printf("%s ",$0); else if(substr($1,1,2)=="#H") printf("%s\n", $0);}' >$d1/cmd.dat
#############
#tspredv3prob1 ds:../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2000-2500k10N:5-300:5 at:-18.5_18.5:40 Sth:.5 e4H:15 Hth:.8,0,999 ftr:../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt DISP:2 seed:11 #H355<E 23L140>N140S0.745L10.550_L 6.83bst[H391N150S0.866L10.43( 3/352)_L 7.33]H*HL 0.53(s0.768n52)S*H-0.264764(s0.670)N5-300
#
#tspredv3prob1 ds:../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:2000-2500k10N:5-300:5 at:-18.5_18.5:40 Sth:.5 e4H:15 Hth:.8,0,999 ftr:../../chaos.data/lorenz1e-8T0.025n10000p256m1_gmp.txt DISP:0' ;echo $cmd;$cmd
## d1=../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4900-5400k10N:5-300:5
######
### Do tspredv3prob1 again for kmeans2_kuro.py
######
cat $d1/cmd.dat |awk '{
s=substr($2,4);match(s,/:.*/);tp0=substr(s,RSTART+1,4);
printf("export cmd=\047%s %s %s %s %s %s %s %s DISP:0\047 ;echo \044cmd;\044cmd\n",$1,$2,$3,$4,$5,$6,$7,$8);#20171030
printf("python ./kmeans2_kuro.py -fnyp ./tmp/tspSth.dat -fnyg ./tmp/yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey $Ey -hh 0 -DISP 0 -tp0 %s\n",tp0);
}' >$d1/cmd.sh
bash $d1/cmd.sh > $d1/cmd.out
##
##python ./kmeans2_kuro.py -fnyp ./tmp/tspSth.dat -fnyg ./tmp/yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey $Ey -hh 0 -DISP 0 -tp0 2000
##
##$d1/cmd.ut contains data 'xN15(S0.117389),5<15<300 ,oN20(S0.486892),5<20<300 '
##  saved tspAll.dat tspSth.dat yg.dat(ground-truth) tspp.dat tp/typ.dat
##
cat $d1/cmd.out | grep '#class hg deg' >$d1/hgdeg.dat
#cat $d0/cmd.out | grep '\*\*\*\|#class hg deg'
cat $d1/cmd.out | grep 'L2 c\|\*\*\*\|#class hg deg'
head -30 $d1/hgdeg.dat > $d1/hgdeg30.dat
echo "###Results are saved in d1=$d1"
#cat $d1/cmd.dat
echo "###d1=$d1"
cat $d1/hgdeg.dat
echo -n "###d1=$d1";cat $d1/hgdeg.dat|awk 'BEGIN{n=0;m=0;min=1e3;max=0;}{h[n]=$3;n++;m+=$3;if(min>$3)min=$3;if(max<$3)max=$3}END{m/=n;v=0;for(i=0;i<n;i++){v+=(h[i]-m)*(h[i]-m);}printf(" PH min max mean std=%.0f %.0f %.0f %.0f\n",min,max,m,sqrt(v/n));}'
#d1=../result-timeseries/lorenz1e-4T0.025n10000p128m1-/t0-2000:4900-5400k10N:5-300:5;
#############################copy&paset to here
#######
cat > tmp.plt <<EOF
set style data lp; set nokey
set pointsize 1.5
max(x0,x1)=(x0>x1)?x0:x1
min0(x0,x1)=(x0<x1)?x0:x1 #admit 0
min(x0,x1)=(x0<1)?x1:(x1<1)?x0:min0(x0,x1) #remove 0
min(x0,x1)=(x0==0)?x1:(x1==0)?x0:min0(x0,x1) #remove 0
###use this for iconip17
set output 'hgdeg-nth3.obj';set term tgif; 
plot "${d1}/hgdeg.dat" using 1:3 lt 1 lw 2 pt 6 lc rgb "dark-green", "" using 1:(max(max(max(max(max(max(\$3,\$6),\$9),\$12),\$15),\$18),\$21)) lt 5 lw 2 pt 8 lc rgb "green", "" using 1:(min(min(min(min(min(min(\$3,\$6),\$9),\$12),\$15),\$18),\$21)) lt 5 lw 2 pt 10 lc rgb "cyan",100
set output 'hgdeg-nth3.eps';set term postscript eps enhanced color; replot
quit
EOF
gnuplot tmp.plt

cp hgdeg-nth3.obj $d1/ #Fig.3
cp hgdeg-nth3.eps $d1/ #Fig.3
gv hgdeg-nth3.eps&
cp -i hgdeg-nth3.eps ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4900-5400k10N:5-300:5/hgdeg-nth3-seed1.eps
cp -i hgdeg-nth3.eps ../../result-chaospred/lorenz1e-8T0.025n10000p256m1_gmp/t0-2000:4900-5400k10N:5-300:5/hgdeg-nth3-seed11.eps
####(2)
