#一個のtermianlを開いて、4行目を実行する。
#---------------------------------------実行方法　1----------------------------------------

#b1=1;N1=20;a1=0;cr1=2;cm1=10;ky1=6;ku1=6;itblock1=5;controlTimes1=100;b2=50;N2=20;a2=0.1;cr2=2;cm2=10;ky2=6;ku2=6;itblock2=5;controlTimes2=100;mspcDataDir=~/sotuicc/mspcdata/;dataname1="single CAN2";dataname2="bagging CAN2";outputEps="yes";outputPng="yes";sh ./plotTrainv1.sh $b1 $N1 $a1 $cr1 $cm1 $ky1 $ku1 $itblock1 $controlTimes1 $b2 $N2 $a2 $cr2 $cm2 $ky2 $ku2 $itblock2 $controlTimes2 $mspcDataDir "${dataname1}" "${dataname2}" "${outputEps}" "${outputPng}"

#b1=1;N1=20;a1=0;cr1=2;cm1=100;ky1=6;ku1=6;itblock1=5;controlTimes1=100;b2=50;N2=20;a2=0.1;cr2=2;cm2=100;ky2=6;ku2=6;itblock2=5;controlTimes2=100;mspcDataDir=~/sotuicc/mspcdata/;dataname1="single CAN2";dataname2="bagging CAN2";outputEps="yes";outputPng="yes";sh ./plotTrainv1.sh $b1 $N1 $a1 $cr1 $cm1 $ky1 $ku1 $itblock1 $controlTimes1 $b2 $N2 $a2 $cr2 $cm2 $ky2 $ku2 $itblock2 $controlTimes2 $mspcDataDir "${dataname1}" "${dataname2}" "${outputEps}" "${outputPng}"

#b1=1;N1=20;a1=0;cr1=10;cm1=10;ky1=6;ku1=6;itblock1=5;controlTimes1=100;b2=50;N2=20;a2=0.1;cr2=10;cm2=10;ky2=6;ku2=6;itblock2=5;controlTimes2=100;mspcDataDir=~/sotuicc/mspcdata/;dataname1="single CAN2";dataname2="bagging CAN2";outputEps="yes";outputPng="yes";sh ./plotTrainv1.sh $b1 $N1 $a1 $cr1 $cm1 $ky1 $ku1 $itblock1 $controlTimes1 $b2 $N2 $a2 $cr2 $cm2 $ky2 $ku2 $itblock2 $controlTimes2 $mspcDataDir "${dataname1}" "${dataname2}" "${outputEps}" "${outputPng}"

#b1=1;N1=20;a1=0;cr1=10;cm1=100;ky1=6;ku1=6;itblock1=5;controlTimes1=100;b2=50;N2=20;a2=0.1;cr2=10;cm2=100;ky2=6;ku2=6;itblock2=5;controlTimes2=100;mspcDataDir=~/sotuicc/mspcdata/;dataname1="single CAN2";dataname2="bagging CAN2";outputEps="yes";outputPng="yes";sh ./plotTrainv1.sh $b1 $N1 $a1 $cr1 $cm1 $ky1 $ku1 $itblock1 $controlTimes1 $b2 $N2 $a2 $cr2 $cm2 $ky2 $ku2 $itblock2 $controlTimes2 $mspcDataDir "${dataname1}" "${dataname2}" "${outputEps}" "${outputPng}"



##code

b1=$1;N1=$2;a1=$3;cr1=$4;cm1=$5;ky1=$6;ku1=$7;itblock1=$8;controlTimes1=$9
b2=${10};N2=${11};a2=${12};cr2=${13};cm2=${14};ky2=${15};ku2=${16};itblock2=${17};controlTimes2=${18}
mspcDataDir=${19};dataname1=${20};dataname2=${21};outputEps=${22};outputPng=${23}

parameterString="b1=${b1}.a1=${a1}.N1=${N1}.cr1=${cr1}.cm1=${cm1}.ky1=${ky1}.ku1=${ku1}.itblock1=${itblock1}.controlTimes1=${controlTimes1}.b2=${b2}.a2=${a2}.N2=${N2}.cr2=${cr2}.cm2=${cm2}.ky2=${ky2}.ku2=${ku2}.itblock2=${itblock2}.controlTimes2=${controlTimes2}"
echo ${parameterString}

d1=${mspcDataDir}result/b${b1}a${a1}_7e
d2=${mspcDataDir}result/b${b2}a${a2}_7e
f1=$d1/net_cr${cr1}cm${cm1}N${N1}ny${ky1}nu${ku1}iti${itblock1}IS2r5T100it${controlTimes1}/listSS.dat
f2=$d2/net_cr${cr2}cm${cm2}N${N2}ny${ky2}nu${ku2}iti${itblock2}IS2r5T100it${controlTimes2}/listSS.dat

rm temp1.dat
rm temp2.dat

cat ${f1}|sed "s/^-1\.0[[:blank:]]\+[[:digit:]]\+[[:blank:]]\+/1000000 1000000 /g"  > temp1.dat
cat ${f2}|sed "s/^-1\.0[[:blank:]]\+[[:digit:]]\+[[:blank:]]\+/1000000 1000000 /g"  > temp2.dat

#
#set xlabel ""
#set ylabel ""
#set title ""
#-------------------------------Settling time plot----------------------------------------------
#plot Settling time
gnuplot -persist <<EOF
set yrange [0:50]
set xtics 0,5,200
set ylabel "s"
set title "Settling time"
plot "temp1.dat" using 3:1 w lp pt 5 title "${dataname1} cr=${cr1}_cm=${cm1}","temp2.dat" using 3:1 w lp pt 5 title "${dataname2} cr=${cr2}_cm=${cm2}"
EOF

#plot eps
if [ "$outputEps" = "yes" ]
then
	gnuplot  <<EOF
	set terminal postscript eps color
	set output "Settling time.${parameterString}.eps"
	set yrange [0:50]
	set xtics 0,5,200
	set ylabel "s"
	set title "Settling time"
	plot "temp1.dat" using 3:1 w lp pt 5 ps 0.5 title "${dataname1} cr=${cr1}_cm=${cm1}","temp2.dat" using 3:1 w lp pt 5 ps 0.5 title "${dataname2} cr=${cr2}_cm=${cm2}"
	set term x11
EOF
fi

#plot png
if [ "$outputPng" = "yes" ]
then
	gnuplot  <<EOF
	set terminal png
	set output "Settling time.${parameterString}.png"
	set yrange [0:50]
	set xtics 0,5,200
	set ylabel "s"
	set title "Settling time"
	plot "temp1.dat" using 3:1 w lp pt 5 ps 0.5 title "${dataname1} cr=${cr1}_cm=${cm1}","temp2.dat" using 3:1 w lp pt 5 ps 0.5 title "${dataname2} cr=${cr2}_cm=${cm2}"
	set term x11
EOF
fi

#-------------------------------Overshoot plot----------------------------------------------

#plot overshoot
gnuplot -persist <<EOF
set yrange [0:500]
set xtics 0,5,200
set ylabel "mm"
set title "Overshoot"
plot "temp1.dat" using 3:2 w lp pt 5 title "${dataname1} cr=${cr1}_cm=${cm1}","temp2.dat" using 3:2 w lp pt 5 title "${dataname2} cr=${cr2}_cm=${cm2}"
EOF

#plot eps
if [ "$outputEps" = "yes" ]
then
	gnuplot  <<EOF
	set terminal postscript eps color
	set output "Overshoot.${parameterString}.eps"
	set yrange [0:500]
	set xtics 0,5,200
	set ylabel "mm"
	set title "Overshoot"
	plot "temp1.dat" using 3:2 w lp pt 5 ps 0.5 title "${dataname1} cr=${cr1}_cm=${cm1}","temp2.dat" using 3:2 w lp pt 5 ps 0.5 title "${dataname2} cr=${cr2}_cm=${cm2}"
	set term x11
EOF
fi

#plot png
if [ "$outputPng" = "yes" ]
then
	gnuplot  <<EOF
	set terminal png
	set output "Overshoot.${parameterString}.png"
	set yrange [0:500]
	set xtics 0,5,200
	set ylabel "mm"
	set title "Overshoot"
	plot "temp1.dat" using 3:2 w lp pt 5 ps 0.5 title "${dataname1} cr=${cr1}_cm=${cm1}","temp2.dat" using 3:2 w lp pt 5 ps 0.5 title "${dataname2} cr=${cr2}_cm=${cm2}"
	set term x11
EOF
fi
