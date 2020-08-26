#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
import math
#import subprocess
import glob
import os
from matplotlib import pylab as plt
from numpy.lib.stride_tricks import as_strided
import mylib
import time
import datetime
import sys

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

  start_time=time.time()
  print('#start time:{}'.format(datetime.datetime.now()))
  if args.sql != '0': #search lack 
    for r in Ra:
      fnq='{}/*R{}*'.format(dq,r)
      Fq=[(f.split('/')[-1])[:-len("-M.dat")] for f in glob.glob(fnq)] #file list
      Fqb=[]
      for f in Fq:
       fl=f.split('-')
       Fqb.append(fl[0]+'-'+fl[1])
#      import pdb;pdb.set_trace(); #for debug
      for s in S:
#        print "#s=",s
        for d in D:
          for l in L:
            sm='{}-{}{}'.format(s,d,l)
#            if sm in fnerr or s == 'mmt':
#              import pdb;pdb.set_trace(); #for debug
            if not sm in Fqb:
              print('#no {} for R{}'.format(sm,r))

  else:#args.sql == '0':
#    import pdb;pdb.set_trace(); #for debug
  #  fnq='{}/*'.format(dm)
  #  Fq=[r.split('/')[-1][:-6] for r in glob.glob(fnq)] #file list
#    GK=gaussian_kernel(21)
    it=0
    for r in Ra:
      fnq='{}/*R{}*'.format(dq,r)
      Fq=[(f.split('/')[-1])[:-6] for f in glob.glob(fnq)] #file list
      for i_s,s in enumerate(Sa):
        for d in Da:
          for l in La:
            fn='{}-{}{}'.format(s,d,l) # fn=s +'-'+ d + l
            if not fn in fnerr:
              mylib.myshell('make data-clean')
              if r == '1':
                sm='{}-{}{}-R{}'.format(s,d,l,r) #sm=s +'-'+ d + l + '-R'+ r
                cmd='cp {}/{}-{}{}.dat {}/{}.dat'.format(dn,s,d,l,dr,sm)
              else:
                errflag=1
                while errflag == 1:
                  s2=S[np.random.randint(nS)]
                  d2=D[np.random.randint(nD)]
                  l2=L[np.random.randint(nL)]
                  fn2='{}-{}{}'.format(s2,d2,l2) 
#                  sm='{}-{}{}-{}-{}{}-R{}'.format(s,d,l,s2,d2,l2,r)
                  sm='{}-{}{}-R{}-{}-{}{}'.format(s,d,l,r,s2,d2,l2)
                  if (not fn2 in fnerr) and (not sm in Fq) and (s != s2):
                    errflag=0
#                import pdb;pdb.set_trace(); #for debug
                cmd='python speechmix.py -y0 {}/{}-{}{}.dat -y1 {}/{}-{}{}.dat -r {} > {}/{}.dat'.format(dn,s,d,l,dn,s2,d2,l2,r,dr,sm)
#              import pdb;pdb.set_trace(); #for debug
              fnout='{}/{}-M.dat'.format(dr,sm)
              if os.path.exists(fnout) and args.ow == 0:
                print('#{} exists: Omit calc becaus -ow 0'.format(fnout))
                continue
              print('#speechmix:{}'.format(cmd))
              mylib.myshell(cmd)
              #speechmix.py
              k=args.k;N=args.N;t0=0;t1=400
              cmd='poledistribv2- st:{} N:{} k:{} m:poles4 dir:{} rsa:2:0.7:1:20 DiffMode:0 tt:{}:{} T:100 DISP:{}'.format(sm,N,k,dr,t0,t1,DISP)
              print(cmd);
#              import pdb;pdb.set_trace(); #for debug
              mylib.myshell(cmd)
              #poledistribv2- 
              #(1)calls tspredv3 (creates tmp/M.dat)
              cmd='cp tmp/M.dat {}'.format(fnout)
              mylib.myshell(cmd);
              print('#{}-M.dat created'.format(fnout))
            sys.stdout.flush()
            it +=1
            if args.dbgi>0 and it==args.dbgi:
              print('### Now in debug mode');
              import pdb;pdb.set_trace(); #for debug 20191105
  elapsed_time=time.time()-start_time
  etime='ElapsedTime {:.3f}s({})'.format(elapsed_time,str(datetime.timedelta(seconds=elapsed_time))[:-3])
  print('#{}'.format(etime))
