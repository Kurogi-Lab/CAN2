echo "<<<nohup.out(head -3)>>>"
head -3 nohup.out
echo "\n<<<nohup.out(tail -5)>>>"
tail -5 nohup.out
echo "\n<<<Number of files created>>>"
echo "`ls ${dr}/*${fnkw12}*.dat 2>/dev/null |wc -l ` *-.dat files (630:necessary) in \$dr=/home/kuro/data/12voicedata_ueki_all_CAN2k20N50a0.6b20R1_Ku20omp22 `date +%H:%M:%S`"
#echo "\nAfter the file created, do \$cmd11 with different N: the 4th parameter from the last of \$method=CAN2q,20,50,0.6,20,1:M2PD,pP1,2,23,3,0.5,0,0"
