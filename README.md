# CAN2
## Description
The competitive associative net CAN2 is a neural network that learns a nonlinear function using the functions of the competitive net<a href="#ref1">[1]</a> and the associative net<a href="#ref2">[2]</a> and approximates it as a piecewise-linear function.<br>
The effectiveness of this net has already been shown by applications to nonlinear time-varying plant control, estimation of recipitation, learning problem of nonlinear function and other problems. <br>

### Function approximation by CAN2
The diagram of function approximation by CAN2 is shown below.<br>
Suppose you want to learn a nonlinear function <img src="https://latex.codecogs.com/gif.latex?y=f(x)"/>, as shown by the dashed line in the diagram.<br>

<img src="https://user-images.githubusercontent.com/49471144/125508173-2dac6131-b529-4d7e-bff0-b8832cb4181f.png" width="500px"/>

①The CAN2 divides the input area by weight vector. (The divided area is called the Voronoi area)<br>

<img src="https://user-images.githubusercontent.com/49471144/125510016-91682a9b-715f-472f-bd8f-5b7451dd8780.png" width="600px"/>

②Each region has an associative matrix M, and linear approximation is performed using the associative matrix. <br>

<img src="https://user-images.githubusercontent.com/49471144/125510657-82077e97-918e-494a-9f0a-9a36a0924438.png" width="700px"/>

③Given the input vector x, it looks for the weight vector wc that is closest to the input vector. <br>

<img src="https://user-images.githubusercontent.com/49471144/125511004-fee2d4f0-d062-4170-b9d7-5cb79eae2a65.png" width="800px"/>

④The prediction can be obtained by using the associative matrix Mc in this weight vector wc. <br>

<img src="function_approximation_by_CAN2.png">

Consider a system that inputs and outputs K-dimensional vectors <img src="https://latex.codecogs.com/gif.latex?\textbf{x}_{j}\triangleq&space;(x_{j1},x_{j2},\cdots,x_{jk})^{T}&space;\in&space;\mathbb{R}^{k\times1}"/> and scalar values <img src="https://latex.codecogs.com/gif.latex?y_{j}&space;\in&space;\mathbb{R}"/>

<img src="https://latex.codecogs.com/gif.latex?y_{j}\triangleq&space;f(\textbf{x}_{j})&plus;d_{j}"/>

<img src="https://latex.codecogs.com/gif.latex?\hat{y}\triangleq\hat{y_{c}}\triangleq&space;\textbf{M}_{c}&space;\tilde{\textbf{x}}"/>

<img src="https://latex.codecogs.com/gif.latex?c\triangleq&space;\underset{i\in&space;l}{\arg\min}&space;\left&space;\|\textbf{x}-\textbf{w}_{i}&space;\right&space;\|"/>

## Requirements
### Compatible operating systems
The below list contains distribution versions with compatibility. However, it may work on other operating systems.
* Ubuntu 12.04 LTS
* Ubuntu 14.04 LTS
* Ubuntu 16.04 LTS
* Ubuntu 18.04 LTS
* Ubuntu 20.04 LTS

### System dependencies
* Python2.7
* Python3.8

## Installation
### Anaconda
```
$ cd ~/Downloads
$ wget https://repo.anaconda.com/archive/Anaconda3-2020.11-Linux-x86_64.sh
$ sh Anaconda3-2020.11-Linux-x86_64.sh
$ conda create --name py27 python=2.7 anaconda
$ conda create -n py27 python=2.7 anaconda
$ conda activate py27 (python2.7)
$ conda deactivate 　 (python3.8)
```

### Chainer
```
$ sudo apt install -y python3-pip
$ pip3 install cupy
$ pip3 install chainer
```

### OpenCV
```
$ conda install opencv
```

### Other software
```
$ sudo apt install -y gv
$ sudo apt install -y gnuplot
$ sudo apt install -y xterm
```

## Examples
### function approximation

```
export fn=Geo1d  ntrain=1000 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest
```

![kunren](https://user-images.githubusercontent.com/49471144/117872656-e71cbe00-b2d9-11eb-93fd-26f737b90826.png)

<img src="https://latex.codecogs.com/gif.latex?f(x)=\left\{\begin{matrix}&space;1.0~~~~~~~~~~~~~~~~~~~~~~~(0.0\leq&space;x\leq&space;0.2)\\&space;1.0-(x-0.2)/0.2~~(0.2\leq&space;x\leq&space;0.4)\\&space;0~~~~~~~~~~~~~~~~~~~~~~~~~(0.4\leq&space;x\leq&space;0.6)\\&space;\cos&space;5\pi&space;(x-0.7)/2.0~~(0.6\leq&space;x\leq&space;0.8)\\&space;0~~~~~~~~~~~~~~~~~~~~~~~~~(0.8\leq&space;x\leq&space;1.0)\\&space;\end{matrix}\right."/>

### learning curve

```
export fn=Geo1d  ntrain=1000 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest 
export T=100 N=90 k=1 Tpinv=-1 seed=5 nop=1;python can2.py -fn tmp/train.csv,tmp/test.csv -k $k,0 -in $N,6,0.2,3,0,0.5,0.2 -ex 1,0.05,0.7,$T,5,50,350 --gpu -1 -DISP 1 -Tpinv $Tpinv -s $seed -nop $nop
```

![mse](https://user-images.githubusercontent.com/49471144/117884259-5d73ed00-b2e7-11eb-959f-e4ddae7ba969.jpg)

## References
<a id="ref1">[1]</a>A.C. Ahalt, A.K. Krishnamurthy, P. Chen and D.E. Melton: Competitive learning algorithms for vector quantization, Neural Networks, 3, 277/290 (1990)<br>
<a id="ref2">[2]</a>T. Kohonen: Associative Memory, Springer Verlag (1977)
