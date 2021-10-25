#
#Usage: wccsv.sh \*.csv
if [ "$2" != "" ]; then sep=$2; else sep=" "; fi
for f in $1; do
 cat $f |awk 'BEGIN{FS=" "}END{print NR;}' 
done
