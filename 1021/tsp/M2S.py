#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
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

S=['fhs', 'fms', 'mkk', 'mko','mmt','mnh','mym']
L=[1,2,3,4,5,6,7,8,9,10]
D=['zero','ichi','ni','san','si','go','roku','nana','hachi','kyu']
R=[1,0.8,0.6,0.4,0.2]
# freqz from http://wrist.hatenablog.com/entry/2015/01/21/005834
#import numpy as np
#import scipy as sp
#import scipy.fftpack as fft
#
#def my_freqz(b, a=[1], worN=None):
#    lastpoint = np.pi
#    N = 512 if worN is None else worN
#    w = np.linspace(0.0, lastpoint, N, endpoint=False)
#    h = fft.fft(b, 2 * N)[:N] / fft.fft(a, 2 * N)[:N]
#    return w, h
#
#b = np.random.randn(1024)
#a = np.random.randn(1024)
#
#w, h = sg.freqz(b, a, 512)
#my_w, my_h = my_freqz(b, a, 512)
#
#np.allclose(h, my_h)  # -> True
#np.sum(h - my_h) # -> (3.6308811859897538e-12-1.5773658421092129e-11j)
def M2S(M,nS=512,f=8000): #spectrum envelope 
  nS2=nS*2 #nfft=1024
  nM,k1=M.shape
  k=k1-1
  W=np.ones((k,nS), dtype=np.complex)
  S=np.zeros((nM,nS),dtype=np.float64)
#  import pdb;pdb.set_trace(); #for debug

  for l in range(1,nS):
    w=2.*math.pi*l/nS2 # w in [0,2*pi*f/2]
#    w=2.*math.pi*f*l/nS2 # w in [0,2*pi*f/2]
    for m in range(1,k):
      W[m,l]=np.exp(-complex(0,w)*m) #exp(-j w m)
      if np.isnan(W[m,l]):
        print('Wml=nan')
#        import pdb;pdb.set_trace(); #for debug
#      W[m,l]=np.exp(complex(0,w)**(-m)) #exp(-j w m)
#  import pdb;pdb.set_trace(); #for debug
  P=np.dot(M[:,:k],W) # [nM x k] *[k x nS]
#  P=M[:,:k] @ W # [nM x k] *[k x nS]
#  P=M[:,:k]*W # [nM x k] *[k x nS]
  for i in range(nM):
    for l in range(nS):
      S[i,l]=20*np.log10(np.abs(M[i,k]/(1.-P[i,l]))) #spectrum envelope
#  import pdb;pdb.set_trace(); #for debug
  return S

if __name__ == "__main__":
#oob4speakerdigit+sX_2018 sp:fhs:fms tx:zero:ichi ntxi:9 k:36 mbas:$mbas dir:$dir1 dir2:$dir2 s:-1 N:${N} sX:${sX}
#oob4speakerdigit+ sp:fhs:fms:mkk:mko:mmt:mnh:mym tx:zero:ichi:ni:san:yon:go:roku:nana:hachi:kyu ntxi:10 k:36 mbas:2:300:1.6:1 dir:$dira s:-1 N:40
  parser = argparse.ArgumentParser(description='speech normalize')
  parser.add_argument('-S', default='fhs:fms:mkk:mko:mmt:mnh:mym', type=str,   help='speaker')
  parser.add_argument('-D', default='zero:ichi:ni:san:si:go:roku:nana:hachi:kyu', type=str,   help='text')
  parser.add_argument('-L', default='1:2:3:4:5:6:7:8:9:10', type=str, help='datetime index')
  parser.add_argument('-R', default='1:0.8:0.6:0.4:0.2:0.1', type=str,   help='lambda')
  parser.add_argument('-dl', default='../../12voicedata_ueki_all', type=str,   help='folder involving original')
  parser.add_argument('-dn', default='../../12voicedata_ueki_all_n', type=str,   help='folder involving normalized')
  parser.add_argument('-dm', default='../../12voicedata_ueki_all_m', type=str,   help='folder involving mixed')
  parser.add_argument('-dq', default='../../12voicedata_ueki_all_q', type=str,   help='folder involving q')
  parser.add_argument('-dp', default='../../12voicedata_ueki_all_p', type=str,   help='folder involving p')
  parser.add_argument('-ds', default='../../12voicedata_ueki_all_k8', type=str,   help='folder involving source')
  parser.add_argument('-dr', default='../../12voicedata_ueki_all_k8', type=str,   help='folder involving r')
  parser.add_argument('-k', default=8, type=int,   help='embedding dimension')
  parser.add_argument('-ns', default=512, type=int,   help='spectral dimension')
  parser.add_argument('-fs', default=8000., type=int,   help='sampling frequency')
  parser.add_argument('-N', default=24, type=int,   help='Number of units')
  parser.add_argument('-sql', default='0', type=str,   help='1 for search q lack')
#  parser.add_argument('-lm', default='tspredv3', type=str, choices=('tspredv3', 'tspredv3er'),   help='learning machine ')
  parser.add_argument('-DISP', default='10', type=str,   help='DISP[0]==1 to make files, DISP[1]==1 to display')
  parser.add_argument('-ow', default=1, type=int,   help='Overwite files if ow=1, omit otherwise.')
  parser.add_argument('-dbgi', default=-1, type=int,   help='debug at i-th iteration')
  args = parser.parse_args()
  Sa=(args.S).split(':') #speakers
  Da=(args.D).split(':') #text
  La=(args.L).split(':') #index
  Ra=(args.R).split(':') #lambda
  dl=args.dl
  dn=args.dn
  dm=args.dm
  dq=args.dq
  dp=args.dp
  ds=args.ds
  dr=args.dr
  N=args.N
  DISP=args.DISP
  fnerr=['mmt-san2', 'fhs-hachi5']
  nS=len(S)
  nL=len(L)
  nD=len(D)
  np.random.seed(seed=32)
  ns=args.ns
  for d in [dr]:#  for d in [dl, dn, dm, dq, dp, df]:
    if not os.path.exists(d): os.mkdir(d)

  start_time=time.time()
  print('#start time:{}'.format(datetime.datetime.now()))
  it=0
  for r in Ra:
    fnq='{}/*R{}*-M.dat'.format(ds,r)
    Fq=[(f.split('/')[-1])[:-6] for f in glob.glob(fnq)] #file list
    for s in Sa:
      for d in Da:
        for l in La:
          fn=s +'-'+ d + l
          if not fn in fnerr:
            fnB0='{}-{}{}-R{}'.format(s,d,l,r)
            fnB=''
            for fnq in Fq:
              if fnB0 in fnq:
                fnB=fnq 
#              if fnB0=='fhs-roku7-R0.8-fms-si6-zero2-R0.8':
#                import pdb;pdb.set_trace(); #for debug

            if fnB == '':
              print('#{}*-M.dat noexist'.format(fnB0))
              continue
            fnout='{}/{}-s{}.dat'.format(dr,fnB,ns)#
            if os.path.exists(fnout) and args.ow == 0:
              print('#{} exists: Omit calc becaus -ow 0'.format(fnout))
              continue
#              cmd0='fnB:"{}/{}";load("M2xyC.mac");'.format(dr,fnB);
            fnM='{}/{}-M.dat'.format(dr,fnB)
            M=np.array(pd.read_csv(fnM,delim_whitespace=True,dtype=np.float64,header=None))
            # LPC対数スペクトル
            S=M2S(M,ns,args.fs)
            se=np.array([np.mean(S[:,i]) for i in range(ns)]).reshape((-1,1))
#            import pdb;pdb.set_trace(); #for debug 20191105
            df=pd.DataFrame(se)
            df.to_csv(fnout,index=False,sep=' ',header=None)
            print('#{}-s{}.dat created'.format(fnB,ns))
#            import pdb;pdb.set_trace(); #for debug 20191105
          sys.stdout.flush()
          it += 1
          if args.dbgi>0 and it==args.dbgi:
            print('### Now in debug mode');
            fscale=[(args.fs/2000.)*(i/float(ns)) for i in range(0,ns)]
            cols = ["r", "g", "b", "c", "m", "y", "k"]
            for i in range(len(S)):
              plt.plot(fscale,S[i,:],"r",linewidth=1,color=cols[i%7])
#            import pdb;pdb.set_trace(); #for debug 20191105
            plt.plot(fscale,se,"r",linewidth=2,color="r")
            plt.pause(0.05); #plt.show() 
            import pdb;pdb.set_trace(); #for debug
#                import pdb;pdb.set_trace(); #for debug
  elapsed_time=time.time()-start_time
  etime='ElapsedTime {:.3f}s({})'.format(elapsed_time,str(datetime.timedelta(seconds=elapsed_time))[:-3])
  print('#{}'.format(etime))
