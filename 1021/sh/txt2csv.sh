#/bin/bash
#space to ,
cat $1|awk 'BEGIN{FS=" "}{
for(i=1; i<=NF; i++) {a[NR,i]=$i}} NF>p{p = NF }END{
  for(i=1; i<=NR; i++){
    str=a[i,1];
    for(j=2; j<=p; j++) str=str","a[i,j];
    print str
  }
}'
