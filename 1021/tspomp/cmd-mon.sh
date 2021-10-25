echo "<<<nohup.out(head -3)>>>"
head -3 nohup.out
echo "\n<<<nohup.out(tail -5)>>>"
cat nohup.out|grep -e python -e ensrs -e can2 -e Elapsed |tail -5
#tail -5 nohup.out
#echo "\n<<<Number of files created>>>"
#echo "`ls ${dr}/*${fnkw12}*.dat 2>/dev/null |wc -l ` *-.dat files (:necessary) in \$dr= `date +%H:%M:%S`"
