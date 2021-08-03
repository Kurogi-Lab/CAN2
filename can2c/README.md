# can2c
## Description
## Examples

```
make
export m_cpu=0
cd ../can2comp
export fntrain=../../can2m.result/geo1dtrain.csv fntest=../../can2m.result/geo1dtest.csv
time ensrsomp $fntrain 2:100:2.2:1:$m_cpu 60-60:1 bg:$fntest k:1 T:100 BIAS:1 Lstd:0:2 ib:0:0:0:0 vm2:-1 seed:2 Tpinv:-1 nop:1
```

### Result
```
[100,-1](3.4s) 1.687e-06 #time MSE n440,71 N60 b100(nens1) a2.2 seed1 nop1 m_cpu12
[100,-1](3.5s) 1.317e-06 #time MSE n440,71 N60 b100(nens1) a2.2 seed2 nop1 m_cpu12
[100,-1](3.5s) 1.904e-06 #time MSE n440,71 N60 b100(nens1) a2.2 seed3 nop1 m_cpu12
[100,50](3.3s) 1.429e-06 #time MSE n440,71 N60 b100(nens1) a2.2 seed1 nop1 m_cpu12
[100,50](3.2s) 6.748e-07 #time MSE n440,71 N60 b100(nens1) a2.2 seed2 nop1 m_cpu12
[100,50](3.2s) 4.541e-07 #time MSE n440,71 N60 b100(nens1) a2.2 seed3 nop1 m_cpu12
```
