echo "<<<nohup.out(head -3)>>>"
head -3 nohup.out
echo "\n<<<nohup.out(tail -5)>>>"
tail -5 nohup.out
echo "\n<<<Number of files created>>>"
echo "`ls ${dr}/*${fnkw2b1}*.dat 2>/dev/null |wc -l ` *-R1-*s files (1:necessary) in \$dr=/home/kuro/data/12voicedata_ueki_all_CAN2k20N60a0.3b500R1_Ku20omp24 `date +%H:%M:%S`"
#echo "\nAfter the file created, do \$cmd2b1 with different N: the 4th parameter from the last of \$method=CAN2q,20,60,0.3,500,1:M2MFCC,20,22"
