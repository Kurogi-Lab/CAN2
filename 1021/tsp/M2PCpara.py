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
import concurrent.futures
#
from multiprocessing import Pool
import multiprocessing as multi

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
#  parser.add_argument('-dq', default='../../12voicedata_ueki_all_q', type=str,   help='folder involving q')
  parser.add_argument('-dp', default='../../12voicedata_ueki_all_p', type=str,   help='folder involving p')
#  parser.add_argument('-ds', default='../../12voicedata_ueki_all_k8', type=str,   help='folder involving source')
  parser.add_argument('-dr', default='../../12voicedata_ueki_all_k8', type=str,   help='folder involving r')
  parser.add_argument('-k', default=8, type=int,   help='embedding dimension')
  parser.add_argument('-N', default=24, type=int,   help='Number of units')
  parser.add_argument('-sql', default='0', type=str,   help='1 for search q lack')
#  parser.add_argument('-lm', default='tspredv3', type=str, choices=('tspredv3', 'tspredv3er'),   help='learning machine ')
  parser.add_argument('-DISP', default='10', type=str,   help='DISP[0]==1 to make files, DISP[1]==1 to display')
  parser.add_argument('-ow', default=1, type=int,   help='Overwite files if ow=1, omit otherwise.')
  parser.add_argument('-dbgi', default=-1, type=int,   help='debug at i-th iteration')
  parser.add_argument('-fnerr', default='mmt-san2:fhs-hachi5', type=str,   help='files lacking data')
  parser.add_argument('-m_cpu', default=0, type=int,   help='number of cpu\'s for parallel execution')
  parser.add_argument('-method', default='CAN2+PD,8,50,2:0.7:1:20', type=str, help='method for making M or s')
  parser.add_argument('-c_or_1', default='1', type=str,   help='c or 1')
  args = parser.parse_args()
  Sa=(args.S).split(':') #speakers
  Da=(args.D).split(':') #text
  La=(args.L).split(':') #index
  Ra=(args.R).split(':') #lambda
  dl=args.dl
  dn=args.dn
  dm=args.dm
#  dq=args.dq
#  dp=args.dp
#  ds=args.ds
  dr=args.dr
  N=args.N
  DISP=args.DISP
  fnerr=(args.fnerr).split(':') #fnerr=['mmt-san2', 'fhs-hachi5']
  nS=len(S)
  nL=len(L)
  nD=len(D)
  c_or_1=args.c_or_1
  #### methods from here
  method=(args.method).split(',') #old
  argmethod=(args.method).split(':')
  methods={};method=[]
  for i,methodi in enumerate(argmethod):
    methodA=methodi.split(',')
    methods[methodA[0]]=methodA[1:]
    method.append(methodA)
  #### methods to here
#  import pdb;pdb.set_trace(); #for debug
  if 'CAN2+PD'==method[0][0]:
    FD=method[0][6] #
    c_or_1=FD[2]    #FD=pP1 ??
  elif 'M2PD' in methods.keys():
    FD=methods['M2PD'][0] #    FD,p1,p2,p3,p4=methods['M2PD'][:5]
    if FD[2]=='1' or FD=='pP1':
      c_or_1='1'
  np.random.seed(seed=32)
  for d in [dr]:#  for d in [dl, dn, dm, dq, dp, df]:
    if not os.path.exists(d): os.mkdir(d)

  it=0
#  import pdb;pdb.set_trace(); #for debug
  cmd=[]
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
              print('#{}*-M.dat noexist. Make *-M.dat first!'.format(fnB0))
              continue
            fnout='{}/{}-PC.dat'.format(dr,fnB)#
            if os.path.exists(fnout) and args.ow == 0:
              print('#{} exists: Omit calc becaus -ow 0'.format(fnout))
              continue
            cmdj='python M2PCsub.py -fnB {}/{} -c_or_1 {} '.format(dr,fnB,c_or_1)
#            if c_or_1 == '1':
#              cmdj='python M2PCsub.py -fnB {}/{} -c_or_1 {} '.format(dr,fnB,c_1)
#            else:
#              cmdj='echo {}fnB:"{}/{}";batchload("M2PC.mac");{}|maxima -q'.format("'",dr,fnB,"'")
            cmd.append(cmdj)
#            print('#{}'.format(cmd))
#            import pdb;pdb.set_trace(); #for debug 20191105
#            mylib.myshell(cmd);
#            print('#{}-PC.dat created'.format(fnB))
#            import pdb;pdb.set_trace(); #for debug 20191105
#          sys.stdout.flush()
          it += 1
#          if args.dbgi>0 and it==args.dbgi:
#            print('### Now in debug mode');
#            import pdb;pdb.set_trace(); #for debug 20191105
#              import pdb;pdb.set_trace(); #for debug
#                import pdb;pdb.set_trace(); #for debug
  ###############
  #  execution of learning bags
  ###############
  m_cpu=args.m_cpu
  m_cpu_max=multi.cpu_count()
  if m_cpu<=0:
    m_cpu=m_cpu_max
  if m_cpu>=m_cpu_max-1:
    m_cpu=m_cpu_max-1
#
#  import pdb;pdb.set_trace(); #for debug
#
  print('#Do with m_cpu={} less than m_cpu_max={} '.format(m_cpu,m_cpu_max))
  
  for j,cmdj in enumerate(cmd):
    print('{}:{}'.format(j,cmdj))
    
  start_time=time.time()
  print('#start time:{}'.format(datetime.datetime.now()))
  #
  with concurrent.futures.ProcessPoolExecutor(m_cpu) as excuter:
    result_list = list(excuter.map(mylib.myshell, cmd))
  elapsed_time=time.time()-start_time
  etime='ElapsedTime {:.3f}s({}) m_cpu{}'.format(elapsed_time,str(datetime.timedelta(seconds=elapsed_time))[:-3],m_cpu)
  print('#{}'.format(etime))
