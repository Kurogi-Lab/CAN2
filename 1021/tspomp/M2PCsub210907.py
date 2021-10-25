import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import numpy as np
import argparse
import math
import subprocess
import glob
import os
#from matplotlib import pylab as plt
import matplotlib.pyplot as plt
from numpy.lib.stride_tricks import as_strided
import mylib
import time
import datetime
import sys
import sympy

if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='From M to pole-zero')
  parser.add_argument('-fnB', default='/home/kuro/data/12voicedata_ueki_all_CAN2k20N50a0.7b20R1_Ku20omp20/fhs-zero1-R1', type=str,   help='file-name body')
  args = parser.parse_args()
  fnB=args.fnB
  fnb=fnB[fnB.rfind('/')+1:] #file name without directory and extension
  fnM=os.path.expanduser(fnB+'-M.dat')
  fnPC=os.path.expanduser(fnB+'-PC.dat')
  M=np.array(pd.read_csv(fnM,delim_whitespace=True,dtype=np.float64,header=None)) #current target (./train_xy.dat)
#  import pdb;pdb.set_trace(); #for debug
  N,k1=M.shape
  k=k1-1
  fp=open(fnPC,'w')
  for n in range(N):
    Mn=M[n,:]
    b=Mn[-1]
    a=np.insert(Mn[0:-1],0,1) #[1,Mn[0],Mn[1],...,Mn[k-1]]
    p=np.roots(a)
    for i in range(len(p)):
      fp.write('{} {} 1 0\n'.format(p[i].real,p[i].imag))
    print('#n,N,k,k,kp={} {} {} {} {}'.format(n,N,k,len(p),fnb))
    if len(p)<k:
      print('#M[{}]={} of {}'.format(n,M,fnb))      
  fp.close()
