#
#(8-1-1)
if [ "$d0" == "" ]; then source exp811-20200128.sh; fi
if [ "layout" == "" ]; then export layout="4,6"; fi
export Na=(0 ${Nas}) fa=(0 ${fas}) mL1=(0 ${mL1s}) obj=(0 ${objs}) mX1=(0 ${mX1s}) mX2=(0 ${mX2s})
#echo "Na=${Na[@]}"
#export d0=../../result-mspc200124; mkdir -p $d0
#export a=0.7 b=1 tt=100; #good for Ubuntu12.04
#export d1=${d0}/a${a}b${b}tt${tt}s${seed}; if [ ! -e $d1 ]; then mkdir $d1;fi  #include information of seed20200127
#source $d1/f12345.dat
#export Na=(0 $N1 $N2 $N3 $N4 2) #配列array にパラメタ設定, 第0要素はダミー，第５要素はプラントP1(m=10)とP2(m=10)用
#export NM=${Na[1]};for i in 2 3 4 ;do if [ $NM -lt ${Na[$i]} ]; then NM=${Na[$i]}; fi ;done #NMに最大値8を設定
#echo "#Na[@]=${Na[@]}, Na[1]=${Na[1]}, Na[2]=${Na[2]}", Na[3]=${Na[3]}", Na[4]=${Na[4]}, NM=$NM"; #確認
#export fa=(0 $f1 $f2 $f3 $f4 2)
#export NMA=0;for i in 1 2 3 4 ;do NMA=`expr ${NMA} + ${Na[$i]}`; done #NM
#export mL1=(0 20 50 20 50 20 50); #学習は20,50 N1,N2,N3,N4に対する学習モデルの荷重質量m、最後の20,50はプラントモデルのm
#export obj=(0 "ST" "ST" "OS" "OS");  #N1,N2,N3,N4に対する制御目的#export obj=(0 "S" "S" "O" "O");  #N1,N2,N3,N4に対する制御目的 #
#export mX1=(0 10 20 30 40 50 60); #テストを10-60
#
for usexdX in 0 ;do #for usexdX in 0 1 ;do #usexdX=1 for use crane.x and crane.dX, 0 for nouse crane.x nor crane.dX
  export cmS1="10" fS="f1 f2 f12" NM=10 DISP=1 LAMBDA="" umax="umax:10:$usexdX"; source $d1/f12345.dat;sh mspctest160920.sh #N=8,2,6,10
  #####
  fplt="gpc-t-Api.plt"
  cat /dev/null > $fplt
  echo "set term postscript eps enhanced color; set nokey" >>$fplt
  echo "set xlabel \"{/=16 {/Arial-Italic t}} [s]\"" >>$fplt
  for OBJ in $OBJS ;do
    for mX in $cmS1 ;do 
      echo "set output \"gpc-t-APi-mX${mX}${OBJ}-xdX${usexdX}.eps\"" >>$fplt
      echo -n "set ytics (">>$fplt
      n=0
      if [ $OBJ = "ST" ]; then
        N12=`expr ${Na[1]} + ${Na[2]}`
        Nsum1=`echo ${N12}+0.5|bc`
        for M in 2 1 ; do #for ST
          for nM in `seq 1 ${Na[$M]}`; do
            echo -n "\"{/=16 {/Arial-Italic M(${mL1[${M}]},${nM},{${obj[$M]}})}}\" $n" >>$fplt
            let n=${n}+1 #n=`expr ${n} + 1`;
#            echo "n=${n} N12=${N12}"
            if [ $n -ne $N12 ]; then echo -n "," >> $fplt ; fi
          done
        done
        echo ")" >> $fplt
        echo "plot [][-1:${Nsum1}] \"tmp/t-AP_i-m${mX}f1.dat\" using 1:(\$3+$N2)  w l lw 2, \"tmp/t-AP_i-m${mX}f2.dat\" using 1:(\$3)  w l lw 2, \"tmp/t-AP_i-m${mX}f12.dat\" using 1:((2-\$2)*$N2+\$3)  w l lw 2 notitle">>$fplt
      else 
        n=0
        N34=`expr ${Na[3]} + ${Na[4]}`
        Nsum1=`echo ${N34}+0.5|bc`
        for M in 4 3 ; do  #for OS
          for nM in `seq 1 ${Na[$M]}`; do
            echo -n "\"{/=16 {/Arial-Italic M(${mL1[${M}]},${nM},{${obj[$M]}})}}\" $n" >>$fplt
            n=`expr ${n} + 1`;
            if [ $n -ne $N34 ]; then echo -n "," >> $fplt ; fi
          done
        done
        echo ")">>$fplt
        echo "plot [0:50][-1:${Nsum1}] \"tmp/t-AP_i-m${mX}f3.dat\" using 1:(\$3+$N4)  w l lw 4 lt 1 lc rgb \"green\", \"tmp/t-AP_i-m${mX}f4.dat\" using 1:(\$3)  w l lw 4 lt 1 lc rgb \"blue\", \"tmp/t-AP_i-m${mX}f34.dat\" using 1:((2-\$2)*$N4+\$3)  w l lw 1 lt 1 lc rgb \"black\"">>$fplt
      fi
    done
  done
  echo "quit" >> $fplt
  gnuplot $fplt
done #for ixdX in 0 1: do

for OBJ in $OBJS ;do
for cm in $cmS1 ; do
gv -scale=5.0 gpc-t-APi-mX${cm}${OBJ}-xdX0.eps&
echo "OBJ=$OBJ stab=$stab cm=$cm"
done
done
