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
  parser.add_argument('-c_or_1', default='1', type=str, help='c to calculate C, 1 for not')
  args = parser.parse_args()
  fnB=args.fnB
  c_or_1=args.c_or_1
  fnb=fnB[fnB.rfind('/')+1:] #file name without directory and extension
  fnM=os.path.expanduser(fnB+'-M.dat')
  fnPC=os.path.expanduser(fnB+'-PC.dat')
  M=np.array(pd.read_csv(fnM,delim_whitespace=True,dtype=np.float64,header=None)) #current target (./train_xy.dat)
#  import pdb;pdb.set_trace(); #for debug
  N,k1=M.shape
  k=k1-1
  fp=open(fnPC,'w')
  z=sympy.Symbol('z')
  for n in range(N):
    Mn=M[n,:]
    a=np.insert(-Mn[0:k],0,1) #a=[1,-Mn[0],-Mn[1],...,-Mn[k-1]]
    p=np.roots(a)
    if c_or_1 =='1':
      c=np.ones((k))
    else:
  #    import pdb;pdb.set_trace(); #for debug
      b=Mn[k]
      p_sp=[p[i].real+p[i].imag*sympy.I for i in range(len(p))]
      A=0
      for i in range(k):
        A=A+a[i]*z**(-i)
      Y=b/A
  #    p=sympy.solve(A,z)
      c=[]
      for i in range(len(p_sp)):
        Yi=(1.0-p_sp[i]*z**(-1))*Y
        ci=complex(Yi.subs(z,p_sp[i])) #
  #      print('n={} i={}'.format(n,i))
        if ci!=0:
          if math.isnan(ci.real) or math.isinf(ci.real): ci=0
          if math.isnan(ci.imag) or math.isinf(ci.imag): ci=0
        c.append(ci)
  #    import pdb;pdb.set_trace(); #for debug
    for i in range(len(p)):
      fp.write('{:.10e} {:.10e} {:.10e} {:.10e}\n'.format(p[i].real,p[i].imag,c[i].real,c[i].imag))
    print('#n,N,k,k,kp={} {} {} {} {} c_or_1=={}:{}'.format(n,N,k,len(p),fnb,c_or_1,c_or_1=='1'))
#    print('#n,N,k,k,kp={} {} {} {} {} c_or_1={}:{}'.format(n,N,k,len(p),fnb,c_or_1,c_or_1=='1'))
    sys.stdout.flush()
#    if len(p)<k:
#      print('#M[{}]={} of {}'.format(n,Mn,fnb))      
  fp.close()
