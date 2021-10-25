#####################
## Use can2b from http://kurolab.cntl.kyutech.ac.jp/~kuro/sotu/2015/can2b150722.7z 
##############################################copy&paste from here
export mail=local; #export mail=global;                          ####  local-mail or global-mail
if [ "$mail" = "local" ]; then 
  export mailAddress="kuro"; cat /dev/null > /var/mail/kuro; #### local-mail saved in /var/mail/kuro
else 
  export mailAddress="kuro@cntl.kyutech.ac.jp";              #### global-mail; change mailAddress to your mail-address
fi
export sh=bash;                 # for old version of sh of Ubuntu12.04 
export exesh=TrainingCAN2V30.sh #export exesh=TrainingCAN2V23.sh #sh=bash;exesh=TrainingCAN2V21.sh
cd ..; rm -rf mspc?
for I in 1 2 3 4; do                                         ### batch jobs are done in the working directory ../mspc$I/
if [ "$I" = "1" ]; then export crRange=2  cmRange=10; fi 
if [ "$I" = "2" ]; then export crRange=2  cmRange=100; fi 
if [ "$I" = "3" ]; then export crRange=10 cmRange=10; fi 
if [ "$I" = "4" ]; then export crRange=10 cmRange=100; fi 
#########
#make working directory
#########
export D0=~/sotu/2016/mspc;                                   ### batch jobs are done in the working directory ~/sotu/2015/mspc$I/
DW=${D0}$I;rm -rf $DW;mkdir -p $DW; cd $DW; ln -s $D0/share .; ln -s ../can2b .;
for f in Makefile apc_crane.c emulate_crane.c crane1sub.c crane2sub.c calcAinvb.c cs_emu.h crane.c linear1sub.c apc_linear.c emulate_linear.c crane3sub.c crane4sub.c $exesh; do cp $D0/$f .; done
export CC=icc; #export CC=gcc; #
make CC=$CC
for f in can2 pred2y_ts meanpred; do ln -s  can2b/$f .; done
export mspcDir=$DW;
export model=nonlinear;
export ky=4 ku=4 uI=1
export b=1 a=0 N="2 4 6 8 10 20 30 40 50";#export b=1 a=0 N="2 4 6 8 10 20 30 40" 
#export b=1 a=0 N="2 4 6 8 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160  180 200";#export b=1 a=0 N="2 4 6 8 10 20 30 40" 
export controlTrainingIterations=10 itblock=2;
#export kyoyou=0.1 tt=100 r=5 T=100 umax=10 cC=0.5 ck=0;//?? ck does not used by the crane2 but linear(crane4)
export kyoyou=0.1 tt=100 r=5 T=100 umax=10 cC=0.5 ck=15;
export AP_TS1=0.5 N2s=12;
export useRI=0 RI=0.05;
export doPlot="yesno" printalldata="yesno";
export fo="./TrainingCAN2.result.b=${b}.a=${a}.N=${N// /_}.ky=${ky}.ku=${ku}.controlTrainingIterations=${controlTrainingIterations}.crRange=${crRange// /_}.cmRange=${cmRange// /_}.kyoyou=$kyoyou.itblock=$itblock.tt=$tt.r=$r.T=$T.umax=$umax.cC=$cC.AP_TS1=$AP_TS1.N2s=$N2s.txt"; 
####
nohup $sh $exesh > $fo 2>&1 &
#echo "$sh $exesh $b \"$N\" $a $mspcDir $mailAddress $ky $ku $controlTrainingIterations $crRange $cmRange $doPlot $kyoyou $itblock $tt $r $T $umax $cC $AP_TS1 $N2s $printalldata $ck $useRI $RI $model 1"> cmd.sh;
##
#$sh cmd.sh > $fo 2>&1 &
#nohup $sh cmd.sh > $fo 2>&1 &
done; #for I
date
