#/bin/bash
###########
if [ "$it" = "" ] ; then it=10; fi
if [ "$uI" = "" ] ; then uI="uI:0:0.8:5"; fi
if [ "$RI" = "" ] ; then RI="RI:1:0.05"; fi
if [ "$update" != "0" ]; then
f0=apc_crane.c;f1=apc_crane_bak.c;cp $f0 $f1;
ny=4;nu=4;sed -e s/"AP_ny "/"AP_ny ${ny}\/\/"/ -e s/"AP_nu "/"AP_nu ${nu}\/\/"/ $f1 > $f0 ; make CC=icc   ##1st trial
fi
if [ "$uI" = "" ] ; then uI="uI:0:0.8:5"; fi
if [ "$RI" = "" ] ; then RI="RI:1:0.05"; fi
cat /dev/null > listSS.dat
###
for N in `echo $NN`; do #active initially
for cm in `echo $cmS0`; do #No.3
cmd="emulate_crane4 it:${it}:2 r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 umax:10 tt:$tt kxt:1 method:12:${N}:${b}:${a}:0 DISP:0 listSS:1 T:100 N2s:12 LAMBDA:0.01 $uI $RI"
date;echo "Executing $cmd";time $cmd;date
mv result-ensrs2ge/net* ${d1}/ #cp -r result-ensrs2ge/net* ${d1}/
done; #for cm
done  #for N active initially
fout="BestSTOS.dat"
cat /dev/null > $fout
for cm in `echo $cmS0`; do export M=5000 #Exp.No.3
export q="cr2cm${cm}N";
echo -n "#BestST+0.01OS: " >> $fout;
cmd2=`cat listSS.dat|awk 'BEGIN {vm=1e9;l=0;q=substr(ENVIRON["q"],1,8);M=ENVIRON["M"];}{l++;p=substr($8,1,8);if($1>0 &&p==q&&$2<M){v=$1+0.01*$2;if(v<vm){vm=v;i=l}}}END{printf("head %d listSS.dat\n",-i)}'`;$cmd2 | tail -1>> $fout
echo -n "#BestOS+0.01ST: " >> $fout
cmd1=`cat listSS.dat|awk 'BEGIN {vm=1e9;l=0;q=substr(ENVIRON["q"],1,8);}{l++;p=substr($8,1,8);if($1>0&&p==q){v=$2+$1*0.01;if(v<vm) {vm=v;i=l}}}END{printf("head -%d listSS.dat\n",i)}'`;$cmd1 | tail -1>> $fout
done
cat $fout|awk 'BEGIN{l=1;L[1]=1;L[2]=3;L[3]=2;L[4]=4;}{if(substr($1,1,1)=="#"){match($9,"N.*ny");N=substr($9,RSTART+1,RLENGTH-3);match($9,"cm.*N");cm=substr($9,RSTART+2,RLENGTH-3);it=$4;printf("export N%d=%s f%d=${d1}/net_cr2cm%dN%sny4nu4iti2IS2r5T100ur0.8uT5it%d; \n",L[l],N,L[l],cm,N,it);l++;}}END{printf("\n")};' > f1234.dat
#OK
#cat $fout|awk 'BEGIN{l=1;L[1]=1;L[2]=3;L[3]=2;L[4]=4;}{if(substr($1,1,1)=="#"){match($9,"N.*ny");N=substr($9,RSTART+1,RLENGTH-3);match($9,"cm.*N");cm=substr($9,RSTART+2,RLENGTH-3);it=$4;printf("export N%d=%s it%d=%s;export f%d=${d1}/net_cr2cm%dN${N%d}ny4nu4iti2IS2r5T100ur0.8uT5it${it%d}\n",L[l],N,L[l],it,L[l],cm,L[l],L[l]);l++;}}END{printf("\n")};' > f1234.dat
#cat $fout|awk 'BEGIN{l=1;L[1]=1;L[2]=3;L[3]=2;L[4]=4;}{if(substr($1,1,1)=="#"){match($9,"N.*ny");n1=RSTART+1;N=substr($9,RSTART+1,RLENGTH-3);it=$4;printf("export N%d=%s it%d=%s;export f%d=${d1}/net_cr2cm%dN${N%d}ny4nu4iti2IS2r5T100ur0.8uT5it${it%d}\n",L[l],N,L[l],it,L[l],L[l],L[l]);l++;}}END{printf("\n")};' > f1234.dat
#cat BestSTOS.dat|awk 'BEGIN{l=1;}{match($9,"N.*ny");n1=RSTART+1;N=substr($9,RSTART+1,RLENGTH-3);it=$4;printf("\nexport N%d=%s it%d=%s;",l,N,l,it);l++;}END{printf("\n")};' > Nit.dat
#cat $fout|awk 'BEGIN{l=1;L[1]=1;L[2]=3;L[3]=2;L[4]=4;}{if(substr($1,1,1)=="#"){match($9,"N.*ny");n1=RSTART+1;N=substr($9,RSTART+1,RLENGTH-3);it=$4;printf("export N%d=%s it%d=%s;\n",L[l],N,L[l],it);l++;}}END{printf("\n")};' >> f1234.dat
cat $fout f1234.dat