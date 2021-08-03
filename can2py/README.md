# can2py
## Description
## Examples
### Learning curve

```
export fn=Geo1d  ntrain=1000 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export T=100 N=90 k=1 Tpinv=-1 seed=5 nop=1;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop
```

![mse](https://user-images.githubusercontent.com/49471144/117884259-5d73ed00-b2e7-11eb-959f-e4ddae7ba969.jpg)
