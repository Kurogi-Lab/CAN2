echo "<<<nohup.out(head -2)>>>"
head -2 nohup.out
echo "\n<<<nohup.out(tail -5)>>>"
tail -5 nohup.out
echo "\n<<<Number of files created>>>"
echo "`ls ${dr}/*-${fnkw2a1}.dat 2>/dev/null|wc -l` *-${fnkw2a1}.dat files (630:necessary) in \$dr=/home/kuro/data/12voicedata_ueki_all_CAN2k20N60a0.4b500R1_Ku20omp24 `date +%H:%M:%S`"
