#/bin/bash
cat $1|awk 'BEGIN{FS=" "}{
for(i=1; i<=NF; i++) {a[NR,i]=$i}} NF>p{p = NF}END{
  for(i=2; i<=NR; i++){
    sum=0
    for(j=1; j<=p; j++){
      e=a[i,j]-a[1,j]
      sum+=e*e
    }
    printf("%d %e\n",i,sqrt(sum));
  }
  printf("\n")
}'

