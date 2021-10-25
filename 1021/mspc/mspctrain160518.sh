#/bin/bash
###########
make data-clean
if [ "$it" = "" ] ; then it=10; fi
if [ "$uI" = "" ] ; then uI="uI:0:0.8:5"; fi
if [ "$RI" = "" ] ; then RI="RI:1:0.05"; fi
if [ "$update" != "0" ]; then
f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
ny=4;nu=4;sed -e s/"AP_ny "/"AP_ny ${ny}\/\/"/ -e s/"AP_nu "/"AP_nu ${nu}\/\/"/ $f1 > $f0 ; make CC=icc   ##1st trial
fi
if [ "$uI" = "" ] ; then uI="uI:0:0.8:5"; fi
if [ "$RI" = "" ] ; then RI="RI:1:0.05"; fi
if [ "$tS" = "" ] ; then tS="tS:0.01"; fi
if [ "$seed" = "" ] ; then seed=0; fi
cat /dev/null > listSS.dat
#
#_date0=`date`
_T0=`date +%s`
#
for N in `echo $NN`; do #active initially
for cm in `echo $cmS0`; do #No.3
cmd="emulate_crane4 it:${it}:2 r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 $umax tt:$tt kxt:1 method:12:${N}:${b}:${a}:${seed} DISP:0 listSS:1 T:100 N2s:12 LAMBDA:0.01 $uI $RI $tS"
date;echo "#Exec mspctrain160518.sh:L19 $cmd";time $cmd;date
#mv    result-ensrs/net* ${d1}/ #
cp -r result-ensrs/net* ${d1}/
done; #for cm
done  #for N active initially
#
#_date1=`date`
_T1=`date +%s`
#
fout="BestSTOS.dat"
cat /dev/null > $fout
for cm in `echo $cmS0`; do export M=5000 #Exp.No.3
export q="cr2cm${cm}N";
echo -n "#BestST+0.01OS: " >> $fout;
cmd2=`cat listSS.dat|awk 'BEGIN {vm=1e9;l=0;q=substr(ENVIRON["q"],1,8);M=ENVIRON["M"];}{l++;p=substr($8,1,8);if($1>0 &&p==q&&$2<M){v=$1+0.01*$2;if(v<vm){vm=v;i=l}}}END{printf("head %d listSS.dat\n",-i)}'`;$cmd2 | tail -1>> $fout
echo -n "#BestOS+0.01ST: " >> $fout
cmd1=`cat listSS.dat|awk 'BEGIN {vm=1e9;l=0;q=substr(ENVIRON["q"],1,8);}{l++;p=substr($8,1,8);if($1>0&&p==q){v=$2+$1*0.01;if(v<vm) {vm=v;i=l}}}END{printf("head -%d listSS.dat\n",i)}'`;$cmd1 | tail -1>> $fout
done
#
#export _date2=`date`
export _T2=`date +%s`
#
cat $fout|awk 'BEGIN{l=1;L[1]=1;L[2]=3;L[3]=2;L[4]=4;}{if(substr($1,1,1)=="#"){match($9,"N.*ny");N=substr($9,RSTART+1,RLENGTH-3);match($9,"cm.*N");cm=substr($9,RSTART+2,RLENGTH-3);it=$4;printf("export N%d=%s f%d=${d1}/net_cr2cm%dN%sny4nu4iti2IS2r5T100ur0.8uT5it%d; \n",L[l],N,L[l],cm,N,it);l++;}}END{printf("\n")};' > f1234.dat
#OK
#cat $fout|awk 'BEGIN{l=1;L[1]=1;L[2]=3;L[3]=2;L[4]=4;}{if(substr($1,1,1)=="#"){match($9,"N.*ny");N=substr($9,RSTART+1,RLENGTH-3);match($9,"cm.*N");cm=substr($9,RSTART+2,RLENGTH-3);it=$4;printf("export N%d=%s it%d=%s;export f%d=${d1}/net_cr2cm%dN${N%d}ny4nu4iti2IS2r5T100ur0.8uT5it${it%d}\n",L[l],N,L[l],it,L[l],cm,L[l],L[l]);l++;}}END{printf("\n")};' > f1234.dat
#cat $fout|awk 'BEGIN{l=1;L[1]=1;L[2]=3;L[3]=2;L[4]=4;}{if(substr($1,1,1)=="#"){match($9,"N.*ny");n1=RSTART+1;N=substr($9,RSTART+1,RLENGTH-3);it=$4;printf("export N%d=%s it%d=%s;export f%d=${d1}/net_cr2cm%dN${N%d}ny4nu4iti2IS2r5T100ur0.8uT5it${it%d}\n",L[l],N,L[l],it,L[l],L[l],L[l]);l++;}}END{printf("\n")};' > f1234.dat
#cat BestSTOS.dat|awk 'BEGIN{l=1;}{match($9,"N.*ny");n1=RSTART+1;N=substr($9,RSTART+1,RLENGTH-3);it=$4;printf("\nexport N%d=%s it%d=%s;",l,N,l,it);l++;}END{printf("\n")};' > Nit.dat
#cat $fout|awk 'BEGIN{l=1;L[1]=1;L[2]=3;L[3]=2;L[4]=4;}{if(substr($1,1,1)=="#"){match($9,"N.*ny");n1=RSTART+1;N=substr($9,RSTART+1,RLENGTH-3);it=$4;printf("export N%d=%s it%d=%s;\n",L[l],N,L[l],it);l++;}}END{printf("\n")};' >> f1234.dat
paste f1234.dat BestSTOS.dat|head -4 | sort -n > ${d1}/f1234.dat
_DT=$((_T1 - _T0))
_H=$((_DT / 3600 ))
_DT=$((_DT % 3600 ))
_M=$((_DT / 60 ))
_S=$((_DT % 60))
#export date2=`date`
export _msg1="train=${_H}:${_M}:${_S}"
#export LANG=C; echo "Elapsed Time=${H}:${M}:${S} (${date0} - ${date1}) for train"
_DT=$((_T2 - _T1 ))
_H=$((_DT / 3600 ))
_DT1=$((_DT % 3600 ))
_M=$((_DT1 / 60 ))
_S=$((_DT1 % 60 ))
#export date2=`date`
_msg2="check=${_H}:${_M}:${_S}"
#export LANG=C; msg2="test:${H}:${M}:${S}"
#export LANG=C; echo "Elapsed Time=${H}:${M}:${S} (${date1} - ${date2}) for test"
#echo "#Elapsed time for ${_msg1}"
#echo "#Elapsed time to ${_msg1} and ${_msg2}"
#echo "#Elapsed time to ${_msg1}"
#export LANG=C;echo "#start=${_date0} train-finish=${_date1} check-finish=${date2}"
echo "#Elapsed time for ${_msg1}" >>${d1}/f1234.dat
echo "#d1=${d1};cat \${d1}/f1234.dat";cat ${d1}/f1234.dat
