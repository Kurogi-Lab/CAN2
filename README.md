# CAN2
## Description
The competitive associative net CAN2 is a neural network that learns a nonlinear function using the functions of the competitive net<sup>[1]</sup> and the associative net<sup>[2]</sup> and approximates it as a piecewise-linear function.<br>
The effectiveness of this net has already been shown by applications to nonlinear time-varying plant control, precipitation estimation, learning problem of nonlinear function and other problems. <br>

<img src="function_approximation_by_CAN2.png">

## Requirements
* Ubuntu 18.04/20.04 x64 - Any currently supported release
* Python2.7

## Installation
```
$ wget https://bootstrap.pypa.io/get-pip.py
$ sudo python get-pip.py
$ sudo apt install -y gv
$ sudo apt install -y gnuplot
```

## References
[1]A.C. Ahalt, A.K. Krishnamurthy, P. Chen and D.E. Melton: Competitive learning algorithms for vector quantization, Neural Networks, 3, 277/290 (1990)<br>
[2]T. Kohonen: Associative Memory, Springer Verlag (1977)
