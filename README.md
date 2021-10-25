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
We installed the following software to operate the CAN2. However, it may work with other software. 

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

## Execution examples
Execution examples of regression and time-series IOS prediction by the single and bagging CAN2s are shown below. See [1], [2] and [3] for the details of regression, bagging, IOS prediction by CAN2, respectively. 

### Set the root directory
```
$ export d0=$PWD;echo $d0 #set the root directory involving data, can2py, can2comp, etc.
```

### Data preparation
#### Regression data (Fig.1) : made by the following steps
```
$ cd ${d0}/can2py
$ export fn=Geo1d ntrain=100 restest=50 extest=10 k=1;
$ python makesamples.py -msd $fn,$ntrain,$restest,$extest
$ dst=${d0}/data/${fn}_${ntrain}_${restest}_${extest}
$ mkdir -p $dst
$ cp tmp/train.csv tmp/test.csv $dst
```

#### Time-series data (Fig.2): see [3] for data creation via using GMP:${d0}/data/lorenz1e-8T0.025n10000p256m1_gmp.txt
Fig1 Fig2

### function approximation

```
export fn=Geo1d  ntrain=1000 restest=50 extest=10 k=1;python makesamples.py -msd $fn,$ntrain,$restest,$extest
```

![kunren](https://user-images.githubusercontent.com/49471144/117872656-e71cbe00-b2d9-11eb-93fd-26f737b90826.png)

<img src="https://latex.codecogs.com/gif.latex?f(x)=\left\{\begin{matrix}&space;1.0~~~~~~~~~~~~~~~~~~~~~~~(0.0\leq&space;x\leq&space;0.2)\\&space;1.0-(x-0.2)/0.2~~(0.2\leq&space;x\leq&space;0.4)\\&space;0~~~~~~~~~~~~~~~~~~~~~~~~~(0.4\leq&space;x\leq&space;0.6)\\&space;\cos&space;5\pi&space;(x-0.7)/2.0~~(0.6\leq&space;x\leq&space;0.8)\\&space;0~~~~~~~~~~~~~~~~~~~~~~~~~(0.8\leq&space;x\leq&space;1.0)\\&space;\end{matrix}\right."/>

## References
<a id="ref1">[1]</a>A.C. Ahalt, A.K. Krishnamurthy, P. Chen and D.E. Melton: Competitive learning algorithms for vector quantization, Neural Networks, 3, 277/290 (1990)<br>
<a id="ref2">[2]</a>T. Kohonen: Associative Memory, Springer Verlag (1977)<br>
[3]S.Kurogi:Asymptotic optimality of competitive associative nets for their learning in function approximation. Proc. ICONIP2002, pp.507-511 (2002)<br>
(Detailed Journal: S.Kurogi: Asymptotic optimality of competitive associative nets and its Application to incremental learning of nonlinear functions, Systems and Communications in Japan, Vol.J86-D-II, No.2, pp.184-194 (2003))<br>
[4]S.Kurogi: Improving generalization performance via out-of-bag estimate using variable size of bags, J. Japanese Neural Network Society, Vol.J.16, No.2, pp.81-92 (2009)<br>
[5]D.Miyazaki, K.Matsuo, and S.Kurogi: Entropy of LOO Predictable Horizons to Select a Learning Machine and a Representative Prediction of Chaotic Time Series, ICONIP 2020, CCIS 1333, pp. 778-787 (2020)<br>
[6]T.Tagomori, R.Tsuruda, K.Matsuo, S.Kurogi: Speaker verification from mixture of speech and non-speech audio signals via using pole distribution of piecewise linear predictive coding coefficients, J Ambient Intell Human Comput (2020)<br>
https://doi.org/10.1007/s12652-020-01716-6<br>
[7] H.Nakayama, K.Ogi, K.Matsuo, and S.Kuro: Composition and Analysis of Pareto Optimal Compromise Solutions for Multiobjective Robust Controller Using GPC and CAN2s, ICONIP 2020, CCIS 1333, pp. 713-722, 2020.<br>
https://doi.org/10.1007/978-3-030-63823-8_81<br> 
