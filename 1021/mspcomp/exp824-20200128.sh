#!/bin/bash
#(8-1-1)
if [ "$d0" == "" ]; then source exp811-20200128.sh; fi
if [ "$mX2s" == "" ]; then export mX2s=`seq 10 5 60` ; fi
export Na=(0 ${Nas}) fa=(0 ${fas}) mL1=(0 ${mL1s}) obj=(0 ${objs}) mX1=(0 ${mX1s}) mX2=(0 ${mX2s})
#export d0=../../result-mspc200124; mkdir -p $d0
#export a=0.7 b=1 tt=100; #good for Ubuntu12.04
#export d1=${d0}/a${a}b${b}tt${tt}s${seed}; if [ ! -e $d1 ]; then mkdir $d1;fi  #include information of seed20200127
#source $d1/f12345.dat
#export Na=(0 $N1 $N2 $N3 $N4 2) #配列array にパラメタ設定, 第0要素はダミー，第５要素はプラントP1(m=10)とP2(m=10)用
#export NM=${Na[1]};for i in 2 3 4 ;do if [ $NM -lt ${Na[$i]} ]; then NM=${Na[$i]}; fi ;done #NMに最大値8を設定
##echo "#Na[@]=${Na[@]}, Na[1]=${Na[1]}, Na[2]=${Na[2]}", Na[3]=${Na[3]}", Na[4]=${Na[4]}, NM=$NM"; #確認
#export fa=(0 $f1 $f2 $f3 $f4 2)
#export NMA=0;for i in 1 2 3 4 ;do NMA=`expr ${NMA} + ${Na[$i]}`; done #NM
#export mL1=(0 20 50 20 50 20 50); #学習は20,50 N1,N2,N3,N4に対する学習モデルの荷重質量m、最後の20,50はプラントモデルのm
#export obj=(0 "ST" "ST" "OS" "OS");  #N1,N2,N3,N4に対する制御目的#export obj=(0 "S" "S" "O" "O");  #N1,N2,N3,N4に対する制御目的 #
#export mX1=(0 10 20 30 40 50 60); #テストを10-60
#export mX2=(0 `seq 10 5 60`); #結果を論文に表示するためのテスト集合 ICONIP2019
#export mX2=(0 10 60); #結果を論文に表示するためのテスト集合 ICONIP2019
################
#(8-2-4-1) gpc 極零の表示 M毎
################
fplt="gpc-poleszeros.plt"
#echo "mX2s=$mX2s OBJS=$OBJS"
#export mX2=(0 ${mX2s})
#echo "mX2=${mX2[@]} OBJS=$OBJS"
for irf in 0; do #irf=0 for 極座標, 1 for 直交座標
#for irf in 0 1; do #irf=0 for 極座標, 1 for 直交座標
  if [ $irf = 0 ]; then 
  rf=""; 
cat > $fplt <<EOF
unset key
set size ratio -1
set grid
set parametric 
rr=3;r=1;
rr=1.5;r=1;
set xrange [-rr:rr];set yrange [-rr:rr]
unset xtics;unset ytics
set xtics (-r,0,r);set ytics (-r,0,r)
set pointsize 0.6
EOF
  else #if [ $irf = 0 ]; then 
rf="-rf"; 
cat > $fplt <<EOF
unset key
set size ratio -1
set grid
set xrange [0:1.5];set yrange [-0.2:1.2]
#set xtics (0,0.5,1,1.5);set ytics (0,.2,.4,.6,.8,1)
set xtics (0,0.5,1,1.5);set ytics (0,.5,1)
set pointsize 0.8
EOF
  fi
  for pz in poles; do #  for pz in poles zeros; do #error with zero @20191231
    if [ $pz = poles ]; then i0=6; fi
    if [ $pz = zeros ]; then i0=7; fi
    nmX=0
    for mX in ${mX2[@]}; do
      if [ $mX == 0 ]; then continue ; fi
      let nmX++; 
#      echo "mX=$mX"
#    for nmX in 1 2; do 
#      mX=${mX2[$nmX]}; # 
      C=0;
    for nmL in $nL; do #for nmL in 1 2 3 4 5; do #M=1,2 for ST, 3,4 for OS
        nM=0;
        echo "" >> ${fplt}
        echo "unset multiplot" >> $fplt
        echo "set term postscript eps enhanced color; set output \"gpc${rf}-$pz-mX${mX}mL${mL1[${nmL}]}${obj[${nmL}]}.eps\";" >> $fplt
        echo "set multiplot layout ${layout}" >> $fplt #if [ ${nmL} -lt 5 ]; then echo "set multiplot layout 3,6" >> $fplt else echo "set multiplot layout 1,2" >> $fplt  fi
	echo "set lmargin 5;set rmargin 3" >> $fplt
	echo "set tmargin 0;set bmargin 0" >> $fplt
        for n in `seq 1 ${Na[${nmL}]}` ; do # echo ${Na[@]} = 0 10 10 11 10 2
          nM=`expr ${nM} + 1`
          i=0;
          if [ ${nmL} -lt 5 ]; then
            echo "set label 1 at graph -0.3,1.2 \"{/=12 {/Arial-Italic H(${mX2[$nmX]},${mL1[${nmL}]},${n},{${obj[${nmL}]}} )}}\"" >> $fplt;
#            echo "set label 1 at graph -0.3,1.2 \"{/=12 {/Arial-Italic H(${mX2[$nmX]},${mL1[${nmL}]},${n},O_{${obj[${nmL}]}} )}}\"" >> $fplt;
          else # using actual plant model 
            echo "set label 1 at graph 0.0,1.2 \"H(${mX2[$nmX]},${mL1[`expr $n + 4`]})\"" >> $fplt;
          fi
          if [ $irf = 0 ]; then #polar form
            echo "plot [0:2*pi] r*cos(t),r*sin(t) t \"\", \"tmp/gpc${rf}-${pz}-P${nmX}M${nM}.dat\" using 1:2 w lp pt 6 lt 1" >> $fplt
          else   #rectangular form
            echo "plot \"tmp/gpc${rf}-${pz}-P${nmX}M${nM}.dat\" using 1:2 w lp pt 6 lt 1 " >> $fplt
          fi
          i=`expr $i + 1`;
        done; #for n in `seq 1 ${Na[$nmL]}` ; do
      done; #for M in 1 2 3 4 ; do
    done #for nmX in 1 2; do 
  done; #for pz in poles zeros; do
  echo ";quit" >> $fplt 
  gnuplot $fplt
done;# for irf in 0 1;do

#上記2.1 view the figs
nmX=0
for mX in ${mX2[@]}; do
  if [ $mX == 0 ]; then continue ; fi; let ++nmX
  echo "mX=$mX"
  for nmL in $nL; do #for nmL in 1 2 3 4 5; do #M=1,2 for ST, 3,4 for OS
    cmd="gv -scale=5.0 gpc-poles-mX${mX2[$nmX]}mL${mL1[${nmL}]}${obj[${nmL}]}.eps"
    echo $cmd
    ${cmd}&
  done; #H(mX,mL,l,ST)の極
done

#for OBJ in $OBJS; do
#  nmX=0
#  for mX in ${mX2[@]}; do
#    if [ $mX == 0 ]; then continue ; fi; let ++nmX
#    echo "mX=$mX"
#    if [ $OBJ == "ST" ]; then 
#      for nmL in $nL; do #for nmL in 1 2 3 4 5; do #M=1,2 for ST, 3,4 for OS
#        cmd="gv -scale=5.0 gpc-poles-mX${mX2[$nmX]}mL${mL1[${nmL}]}${obj[${nmL}]}.eps"
#        echo $cmd
#        ${cmd}&
#      done; #H(mX,mL,l,ST)の極
#    else
#      for nmL in 3 4;do 
#        cmd="gv -scale=5.0 gpc-poles-mX${mX2[$nmX]}mL${mL1[${nmL}]}${obj[${nmL}]}.eps"
#        echo $cmd
#        ${cmd}&
#       done; #H(mX,mL,l,OS)の極
#    fi
#  done
#done