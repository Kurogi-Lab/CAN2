#/bin/bash
cat $1|awk 'BEGIN{FS=" "}{
for(i=1; i<=NF; i++) {a[NR,i]=$i}} NF>p{p = NF}END{
  for(j=2; j<=p; j++){
    sum=0
    for(i=1; i<=NR; i++){
      e=a[i,j]-a[1,j]
      sum+=e*e
    }
    printf("%d %e\n",j-2,sqrt(sum)/(NR-1));
  }
  printf("\n")
}'

