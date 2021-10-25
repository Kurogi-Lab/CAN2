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
  parser.add_argument('-na', default=18, type=int,   help='number of angle divisions of pole space')
  parser.add_argument('-nr', default=2, type=int,   help='number of magnitude divisions of pole space')
  parser.add_argument('-stopi', default=-1, type=int,   help='stop at i-th iteration')
  args = parser.parse_args()
  Sa=(args.S).split(':') #speakers
  Da=(args.D).split(':') #text
  La=(args.L).split(':') #index
  Ra=(args.R).split(':') #lambda
#
  dl=args.dl
  dn=args.dn
  dm=args.dm
  dq=args.dq
  dp=args.dp
  df=args.df
#
  dr=args.dr
  N=args.N
  na=args.na
  nr=args.nr
  DISP=args.DISP
  fnerr=['mmt-san2', 'fhs-hachi5']
  nS=len(S)
  nL=len(L)
  nD=len(D)
  PI=math.pi
  np.random.seed(seed=32)
  for d in [dr]:#  for d in [dl, dn, dm, dq, dp, df]:
#  for d in [dm, dq, dp, df, dr]:#  for d in [dl, dn, dm, dq, dp, df]:
    if not os.path.exists(d): os.mkdir(d)
#    import pdb;pdb.set_trace(); #for debug
#  fnq='{}/*'.format(dm)
#  Fq=[r.split('/')[-1][:-6] for r in glob.glob(fnq)] #file list
  k=args.k;
#    GK=gaussian_kernel(args.Ksize)
  pltcolorbar=1
#  fig=plt.figure()
  fig=plt.figure(figsize=(10,10))
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
          fnout='{}/{}-q.dat'.format(dr,fnB)#  fnout='{}/{}-R{}-GM.dat'.format(dr,s,r)
#          fntgt='{}/{}-GMtgt.dat'.format(dr,fnB)#  fnout='{}/{}-R{}-GM.dat'.format(dr,s,r)
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
          nW=args.Fsize
          P=P.reshape(N,k,3)
          q=np.zeros((na*nr), dtype=np.float32)
          F=np.zeros((nW,nW), dtype=np.float32)
          nW0=nW/2
          w=args.rmax*2 #
          r_max=args.rmax
          w0=w/2.0
          wp=2. # width of pole
          for n in range(N):
            Pn=P[n]
            for _i in range(k):
              x=Pn[_i,0]
              y=Pn[_i,1]
              pr=math.sqrt(x**2+y**2) #absolute value
              pa=math.atan2(y,x)      #phase angle, radian
              X=int(nW0*(Pn[_i,0]+w0)/w0)
              Y=int(nW0*(Pn[_i,1]+w0)/w0)
#              if X<0 or X>=nW or Y<0 or Y>=nW:
              if X<0 or X>=nW or Y<0 or Y>=nW:
                print('#Ignore pole out of bounds: ({},{})<=({:.2g},{})'.format(X,Y,Pn[_i,0],Pn[_i,1]))
              elif Pn[_i,1]==0:
                print('#Ignore pole on real axis: ({},{})<=({:.2g},{})'.format(X,Y,Pn[_i,0],Pn[_i,1]))
              else:
                F[Y,X] +=1
                x=0
                for j in range(nr):
                  for i in range(na):
                    for l in range(len(Pn)):
                      if pr > r_max*j/nr and pr <r_max*(j+1.)/nr and pa>= PI*i/na and pa < PI*(i+1)/na and pa >0 and pa <PI:
                        q[x] +=1
                    x += 1
#          import pdb;pdb.set_trace();
#  x=0;
#  for(i=0;i<n;i++){ //n=nt
#    for(j=0;j<m;j++){//m=nr
#      q[x]=0;
#      for(l=0;l<K;l++){
#	if(pr[l] >= r_max*j/m && pr[l] < r_max*(double)(j+1)/(double)m &&
#	   pt[l] >= PI*i/n && pt[l] < PI*(double)(i+1)/n  // pt[l] >= PI*i/n && pt[l] < PI*(double)(i+1)/n
#	   && pt[l] > 0 //9/20 for neglect θ=0
#           && pt[l] <PI
#           ){//9/20
#	  q[x]++;
#	}
#	//        if(pt[l]==0) printf("#l%d i%d j%d x%d q%d\n",l,i,j,x,q[x]);
#      }
#      x++;
#    }
#  }

#                import pdb;pdb.set_trace(); #for debug 20191105
#                F[Y,X]=Pn[i,2] #  F[Y,X]=math.log1p(P[i,2])
#                FGK = np.zeros(F.shape)
#                FGK = convolve2d_1ch(F, GK, padding='edge')
#                FGK /=np.linalg.norm(FGK)
              #See http://earth.cs.miyazaki-u.ac.jp/~miyaji/documents/opencv/OpenCV-3.pdf for GaussianBlur
#              FGK = cv2.GaussianBlur(F,(args.Ksize,args.Ksize),args.Ksigma) 
#                FGK = cv2.GaussianBlur(F,args.Ksize,args.Ksigma)
          plt.clf()
          fig.add_subplot(2,1,1)
          plt.imshow(F);plt.title('{}:\n Pole distribution of weighted poles'.format(fnB));
          plt.colorbar(fraction=0.05,pad=0.04);
          xaxis=[x for x in range(len(q))]
          fig.add_subplot(2,1,2)
          plt.bar(xaxis,q);plt.title('q_n: number of poles for n = i n_a + j (j=0,..,{};i=0,..,{}'.format(na,nr));
          plt.pause(0.05)
          for x in range(len(q)):
            fpout.write('{:g} '.format(q[x]))
          fpout.close()
          it+=1
          if args.stopi>0 and it==args.stopi:
            import pdb;pdb.set_trace(); #for debug 20191105
#            for i in range(nW):
#              for j in range(nW):
#                fpout.write('{:g} '.format(FGK[i,j]))
#            fpout.write('{}\n'.format(i_s))
#          fpout.close()
#
#        print('#Saved {}.'.format(fnout))
