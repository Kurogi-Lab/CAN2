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
import mylib
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

  it=0
  for r in Ra:
    fnq='{}/*R{}*-M.dat'.format(dr,r)
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
              print('#{}*-M.dat does not exist'.format(fnB0))
              continue
            fnout='{}/{}-xyC.dat'.format(dr,fnB)#
            if os.path.exists(fnout) and args.ow == 0:
              print('#{} exists: Omit calc becaus -ow 0'.format(fnout))
              continue
#              cmd0='fnB:"{}/{}";load("M2xyC.mac");'.format(dr,fnB);
#              import pdb;pdb.set_trace(); #for debug
            cmd='echo {}fnB:"{}/{}";batchload("M2pc.mac");{}|maxima'.format("'",dr,fnB,"'")
#            cmd='echo {}fnB:"{}/{}";batchload("M2pc.mac");{}|maxima'.format("'",dr,fnB,"'")
#            cmd='echo {}fnB:"{}/{}";batchload("M2xyC.mac");{}|maxima >tmp/tmp.log'.format("'",dr,fnB,"'")
#            cmd='echo {}fnB:"{}/{}";batch("M2xyC.mac");{}|maxima -b >/dev/null'.format("'",dr,fnB,"'")
            #cmd='maxima < M2xyC.mac' #read tmp/M.dat produce tmp/xyC.dat
            print('#{}'.format(cmd))
            mylib.myshell(cmd);
#            import pdb;pdb.set_trace(); #for debug 20191105
          it += 1
          if args.stopi>0 and it==args.stopi:
            import pdb;pdb.set_trace(); #for debug 20191105
#              import pdb;pdb.set_trace(); #for debug
#                import pdb;pdb.set_trace(); #for debug
