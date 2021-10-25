#/bin/bash
export j0=$2
cat $1|awk 'BEGIN{FS=" ";j0=ENVIRON["j0"]}{
for(i=1; i<=NF; i++) {a[NR,i]=$i}} NF>p{p = NF}END{
  for(j=1; j<=p; j++){
    sum=0
    for(i=1; i<=NR; i++){
      e=a[i,j]-a[i,j0]
      sum+=e*e
    }
    printf("%e\n",sqrt(sum/NR));
  }
}'

#    printf("%d %e\n",j,sqrt(sum/NR));
