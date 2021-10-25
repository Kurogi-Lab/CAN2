echo "<<<nohup.out(head -3)>>>"
head -3 nohup.out
echo "\n<<<nohup.out(tail -8)>>>"
tail -8 nohup.out
echo "\n<<<Number of files created for cmd2b2>>>"
echo "`ls ${dr}/*${fnkw2b2}* 2>/dev/null |wc -l ` *${fnkw2b2} files (1:necessary) in \$dr=/home/kuro/data/12voicedata_ueki_all_LPCSE1k21l19n64R1_Ku20LPCw1 `date +%H:%M:%S`"
