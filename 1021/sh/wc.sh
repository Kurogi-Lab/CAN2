#
#Usage: wccsv.sh \*.csv
for f in $1; do
 echo -n "$f "
 cat $f |awk 'BEGIN{FS=" "}END{print NR,NF;}' 
done
#cat M.dat|awk 'END{print NR,NF;}' #21 raws 61 cols #行数、列数
#cat $1 |awk 'END{print NR,NF;}' #21 raws 61 cols #行数、列数
