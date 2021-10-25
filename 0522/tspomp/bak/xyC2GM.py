#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
import math
import subprocess
import glob
import os
from matplotlib import pylab as plt
from numpy.lib.stride_tricks import as_strided
import cv2
#import myshell
S=['fhs', 'fms', 'mkk', 'mko','mmt','mnh','mym']
L=[1,2,3,4,5,6,7,8,9,10]
D=['zero','ichi','ni','san','si','go','roku','nana','hachi','kyu']
R=[1,0.8,0.6,0.4,0.2]
##def myshell(cmd): #no stop even when error occured                                
##  try:
##    retcode=subprocess.Popen(cmd, shell=True)
##    if retcode < 0:
##      print "my Child was terminated by signal", -retcode
##    else:
##      print "my Child returned", retcode
##  except OSError as e:
##    print "Execution failed:", cmd, e
##  return retcode.wait()
### http://optie.hatenablog.com/entry/2018/03/21/185647#32-ガウシアンフィルタ
##def norm2d(x,y,sigma):
##    Z = np.exp(-(x**2 + y**2) / (2 * sigma**2)) / (2 * np.pi * sigma**2)
##    return Z
##
#def gaussian_kernel(Ksize,Ksigma):
#    if Ksize%2==0:
#      Ksize+=1
#    # [0,Ksize]→[-Ksigma, Ksigma] にずらす
#    x = y = np.arange(0,size) - Ksigma
#    X,Y = np.meshgrid(x,y) 
#    mat = norm2d(X,Y,Ksigma/2.)
#    kernel = mat / np.sum(mat) # normalize
#    return kernel
##
##def convolve2d_1ch(img, kernel, padding='0'):
##    # エラー処理
##    if len(img.shape) != 2:
##        print('img should be 2d-array')
##        return
##    if kernel.shape[0]%2 == 0:
##        print('Kernel size shold be odd')
##        return
##    
##    edge = int(kernel.shape[0]/2)
##    
##    # 境界をどうするか
##    if padding=='edge':
##        img = np.pad(img, [edge,edge], mode='edge')
##    elif padding=='reflect':
##        img = np.pad(img, [edge,edge], mode='reflect')
##    else:
##        img = np.pad(img, [edge,edge], mode='constant', constant_values=0)
##    
##    sub_shape = tuple(np.subtract(img.shape, kernel.shape) + 1)
##
##    # (rows, cols, N, N)
##    conv_shape = sub_shape + kernel.shape
##
##    # A.strides は (Aのrow方向の一要素ごとのbytes数, col方向のbytes数) のタプル
##    # (shape[0]*bytes, bytes, shape[0]*bytes, bytes)
##    strides = img.strides + img.strides
##
##    submatrices = as_strided(img, conv_shape, strides)
##
##    # (i,j)配列と(k,l,i,j)配列で, (i,j)要素同士の積和を要素とした(k,l)配列を返す
##    convolved_mat = np.einsum('ij, klij->kl', kernel, submatrices)
##    
##    return convolved_mat

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
  parser.add_argument('-df', default='../../12voicedata_ueki_all_f', type=str,   help='folder involving f')
  parser.add_argument('-dr', default='../../12voicedata_ueki_all_k8', type=str,   help='folder involving r')
  parser.add_argument('-k', default=8, type=int,   help='embedding dimension')
  parser.add_argument('-N', default=24, type=int,   help='Number of units')
  parser.add_argument('-Ksize', default=13, type=int,   help='Gaussian Kernel size')
  parser.add_argument('-Ksigma', default=2, type=int,   help='Gaussian Kernel sigma')
  parser.add_argument('-Fsize', default=40, type=int,   help='Feature size nWxnW')
  parser.add_argument('-rmax', default=3, type=float,   help='boundary magnitude of poles ')
  parser.add_argument('-sql', default='0', type=str,   help='1 for search q lack')
#  parser.add_argument('-lm', default='tspredv3', type=str, choices=('tspredv3', 'tspredv3er'),   help='learning machine ')
  parser.add_argument('-DISP', default='10', type=str,   help='DISP[0]==1 to make files, DISP[1]==1 to display')
  parser.add_argument('-ow', default=1, type=int,   help='Overwite files if ow=1, omit otherwise.')
  parser.add_argument('-stopi', default=-1, type=int,   help='stop at i-th iteration')
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
  df=args.df
  dr=args.dr
  N=args.N
  DISP=args.DISP
  fnerr=['mmt-san2', 'fhs-hachi5']
  nS=len(S)
  nL=len(L)
  nD=len(D)
  np.random.seed(seed=32)
  for d in [dr]:#  for d in [dl, dn, dm, dq, dp, df]:
#  for d in [dm, dq, dp, df, dr]:#  for d in [dl, dn, dm, dq, dp, df]:
    if not os.path.exists(d): os.mkdir(d)
#    import pdb;pdb.set_trace(); #for debug
#  fnq='{}/*'.format(dm)
#  Fq=[r.split('/')[-1][:-6] for r in glob.glob(fnq)] #file list
  k=args.k;
#    GK=gaussian_kernel(args.Ksize)
  fig=plt.figure()
  it=0
  for r in Ra:
    fnq='{}/*R{}*-xyC.dat'.format(dr,r)
    Fq=[(f.split('/')[-1])[:-8] for f in glob.glob(fnq)] #file list
    for i_s,s in enumerate(Sa):
#    for s in Sa:
#        fnout='{}/{}-R{}-GM.dat'.format(dr,s,r)
#        fpout=open(fnout,'w')
      for d in Da:
        for l in La:
          fn=s +'-'+ d + l
          fnB0='{}-{}{}-R{}'.format(s,d,l,r)
          fnB=''
          for fnq in Fq:
            if fnB0 in fnq:
              fnB=fnq
          if fnB == '':
            print('#{}*-M.dat does not exist'.format(fnB0))
            continue
          fnxyC='{}/{}-xyC.dat'.format(dr,fnB); 
          fnout='{}/{}-GM.dat'.format(dr,fnB)#  fnout='{}/{}-R{}-GM.dat'.format(dr,s,r)
          fntgt='{}/{}-GMtgt.dat'.format(dr,fnB)#  fnout='{}/{}-R{}-GM.dat'.format(dr,s,r)
          if os.path.exists(fnout) and args.ow == 0:
            print('#{} exists: Omit calc becaus -ow 0'.format(fnout))
            continue
          fpout=open(fnout,'w')
#          fptgt=open(fntgt,'w')
#            import pdb;pdb.set_trace(); #for debug
#          import pdb;pdb.set_trace();
          P=np.array(pd.read_csv(fnxyC,delim_whitespace=True,dtype=np.float32,header=None))
          nP=P.shape[0] #=k*N
          N=nP/args.k
          P=P.reshape(N,k,3)
          nW=args.Fsize
          nW0=nW/2
          w=args.rmax*2 #
          w0=w/2.0
          wp=2. # width of pole
          for n in range(N):
#            w=6.0 #[-3,3]
#            w=4.0 #[-2,2]
            F=np.zeros((nW,nW), dtype=np.float32)
            Pn=P[n]
            for i in range(k):
              X=int(nW0*(Pn[i,0]+w0)/w0)
              Y=int(nW0*(Pn[i,1]+w0)/w0)
#              if X<0 or X>=nW or Y<0 or Y>=nW:
              if X<0 or X>=nW or Y<0 or Y>=nW:
                print('#Ignore pole out of bounds: ({},{})<=({:.2g},{})'.format(X,Y,Pn[i,0],Pn[i,1]))
              elif Pn[i,1]==0:
                print('#Ignore pole on real axis: ({},{})<=({:.2g},{})'.format(X,Y,Pn[i,0],Pn[i,1]))
              else:
#                import pdb;pdb.set_trace(); #for debug 20191105
                F[Y,X]=Pn[i,2] #  F[Y,X]=math.log1p(P[i,2])
#                FGK = np.zeros(F.shape)
#                FGK = convolve2d_1ch(F, GK, padding='edge')
#                FGK /=np.linalg.norm(FGK)
              #See http://earth.cs.miyazaki-u.ac.jp/~miyaji/documents/opencv/OpenCV-3.pdf for GaussianBlur
              FGK = cv2.GaussianBlur(F,(args.Ksize,args.Ksize),args.Ksigma) 
#                FGK = cv2.GaussianBlur(F,args.Ksize,args.Ksigma)
            plt.clf()
            fig.add_subplot(1,1,1)
            plt.imshow(FGK);plt.title('{}: Gaussian Mixture of weighted poles'.format(fnB));
            plt.colorbar(fraction=0.05,pad=0.04);
            plt.pause(0.05)
#            plt.imshow(FGK);plt.title('{}: Gaussian Mixture of weighted poles'.format(fnB));plt.pause(0.05)
#            import pdb;pdb.set_trace(); #for debug 20191105
            for i in range(nW):
              for j in range(nW):
                fpout.write('{:g} '.format(FGK[i,j]))
            fpout.write('\n'.format(i_s))
#            fpout.write('{}\n'.format(i_s))
#             import pdb;pdb.set_trace(); #for debug 20191105
#             plt.imshow(FGK);plt.title("Feature");plt.colorbar();plt.show();
#             plt.imshow(FGK);plt.title("Feature");plt.colorbar();plt.pause(0.05)
#             print Pn
          fpout.close()
          it += 1
          if args.stopi>0 and it==args.stopi:
            import pdb;pdb.set_trace(); #for debug 20191105
#          import pdb;pdb.set_trace();
#
#        print('#Saved {}.'.format(fnout))
