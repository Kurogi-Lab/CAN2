echo "<<<nohup.out(head -3)>>>"
head -3 nohup.out
echo "\n<<<nohup.out(tail -5)>>>"
tail -5 nohup.out
echo "\n<<<Number of files created>>>"
echo "`ls ${dr}/*${fnkw12}.dat 2>/dev/null |wc -l` $dr/*-R1-LPC*.dat files (72:necessary) `date +%H:%M:%S`"
