echo "<<<nohup.out(head -2)>>>"
head -2 nohup.out
echo "\n<<<nohup.out(tail -5)>>>"
tail -5 nohup.out
echo "\n<<<Files created>>>"
echo "`ls ${dr}/*-${fnkw2a1}.dat|wc -l` *-${fnkw2a1}.dat files (630:necessary) in \$dr=/home/kuro/data/12voicedata_ueki_all_CAN2k8N50a1.0b100R1_Ku20omp20 `date +%H:%M:%S`"
