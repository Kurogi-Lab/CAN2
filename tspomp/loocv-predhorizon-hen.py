#!/bin/python
# -*- coding: utf-8 -*-
#
#import sys
#import os
#import numpy as np
import mylib
import argparse

if __name__ == "__main__":
#oob4speakerdigit+sX_2018 sp:fhs:fms tx:zero:ichi ntxi:9 k:36 mbas:$mbas dir:$dir1 dir2:$dir2 s:-1 N:${N} sX:${sX}
#oob4speakerdigit+ sp:fhs:fms:mkk:mko:mmt:mnh:mym tx:zero:ichi:ni:san:yon:go:roku:nana:hachi:kyu ntxi:10 k:36 mbas:2:300:1.6:1 dir:$dira s:-1 N:40
  parser = argparse.ArgumentParser(description='speech normalize')
  parser.add_argument('-DISP', default='1', type=str,   help='DISP[0]==1 to make files, DISP[1]==1 to display')
  parser.add_argument('-d00', default='../../result-chaospred', type=str,   help='directory for storing result.')
  parser.add_argument('-ddc', default='../../chaos.data', type=str,   help='directory involving timeseries.')
  parser.add_argument('-fbc', default='lorenz1e-8T0.025n10000p256m1_gmp', type=str,   help='file name body of chaotic timeseries for train and test.')
  parser.add_argument('-TP0', default='2000', type=str,   help='tp0 or set of tp0')
  parser.add_argument('-phase', default='', type=str,   help='phase no for obtaining loocv predictable horizon')
  parser.add_argument('-N', default='N:5-300:5', type=str,   help='nuber of units in CAN2,')
  parser.add_argument('-n_seed', default='1', type=str,   help='number of seeds')
  parser.add_argument('-Ey', default=15, type=float,   help='Error of Y for Predictable Horizon')
  parser.add_argument('-Sth', default=-0.5, type=float,   help='Similarity threshold')
  parser.add_argument('-ID', default='1', type=str,   help='ID of execution')
  args = parser.parse_args()
  d00=args.d00
  fbc=args.fbc
  ddc=args.ddc
  d0='{}/{}'.format(d00,fbc)
  tr1=2000
  fny='{}/{}.txt'.format(ddc,fbc)
  Ey=args.Ey
  Sth=args.Sth
  fnlog='chaospred2019.log'
  TP0=map(int,(args.TP0).split(' '))
  N_A=(args.N).split(' ')
  n_seed_A=map(int,(args.n_seed).split(' '))
  phase=args.phase
  ID=args.ID
  ###############
  #####phase 1
  ###############
  k=10              
  if phase=='' or phase=='1':
    mylib.myshell('make data-clean;cat /dev/null>{}/{};cat /dev/null >{}/cmd.sh'.format(d0,fnlog,d0))
    for tp0 in TP0:
      mylib.myshell('rm --force lossall.dat tspall.dat tspall_id.dat')
      tp1=tp0+500
      t='0-{}:{}-{}'.format(tr1,tp0,tp1)
      d1='{}/t{}k{}{}ID{}'.format(d0,t,k,N_A,ID)
      mylib.myshell('mkdir -p {}'.format(d1))
      for iN,N in enumerate(N_A):
#        import pdb;pdb.set_trace(); #for debug
        for iseed in range(n_seed_A[iN]):
          cmd='./tspredv3 {} {} mp:1:1:1 DiffMode:0 Hosei:0 {} M:1-1:1 ib:0:0:0:0 rsa:-1:1:1 k:{} y:-18.5:18.5:0:1 g:1.4e-3 w:0.2 T:100 vt:0.5 vr:10 lossall:1 DISP:0 e4t:0 e4p:0 nop:1 seed:{}'.format(fny,t,N_A[iN],k,iseed)
          print('#Exec {}'.format(cmd)) 
#          import pdb;pdb.set_trace(); #for debug
          f=open('{}/cmd.sh'.format(d1),'a'); f.write('#{}'.format(cmd)); f.close()
          mylib.myshell(cmd)
#      d1='{}/t{}k{}{}ID{}'.format(d0,t,k,N,ID)
#      mylib.myshell('mkdir -p {}'.format(d1))
      cmd='for f in lossall.dat tspall.dat tspall.plt tspall_id.dat; do if [ -e $f ]; then cp $f {}; fi; done'.format(d1)
      cmd='{}\ncat /dev/null > {}/cmd.out'.format(cmd,d1)
      cmd='{}\ntspredv3prob1 ds:{} at:-18.5_18.5:40 Sth:{} e4H:{} Hth:.8,0,999 ftr:{} DISP:0 >> {}/cmd.out'.format(cmd,d1,Sth,Ey,fny,d1)
#      cmd='{}\ntspredv3prob1 ds:{} at:-18.5_18.5:40 Sth:.5 e4H:{} Hth:.8,0,999 ftr:{} DISP:0 >> {}/cmd.out'.format(cmd,d1,Ey,fny,d1)
      cmd='{}\npython kmeans2_kuro.py -d1 {} -fnyp tspSth.dat -fnyg yg.dat -K 2 -L 2 -Lt 0 -m 1 -Ey {} -hh 30 -DISP 0 -tp0 {} >> {}/cmd.out'.format(cmd,d1,Ey,tp0,d1)
#      with open('{}/cmd.sh'.format(d1), 'a') as f: print(cmd, file=f)
      f=open('{}/cmd.sh'.format(d1),'a'); f.write(cmd);    f.close()
      f=open('{}/cmd.sh'.format(d0), 'a');f.write('export d1={}\nbash $d1/cmd.sh\n'.format(d1));f.close()
#      with open('{}/cmd.sh'.format(d0), 'a') as f: print('bash {}/cmd.sh'.format(d1), file=f)
#      mylib.myshell('echo {} >> {}/cmd.sh'.format(cmd0,d0))
#      import pdb;pdb.set_trace(); #for debug
      print('#Phase2 commands in {}/cmd.sh'.format(d0))
      mylib.myshell('if [ -e SLH.dat ];then cp SLH.dat {};fi'.format(d1))

  if phase=='' or phase=='2':
    mylib.myshell('bash {}/cmd.sh > {}/cmd.out'.format(d0,d0))
    print('#Phase2: Done {}/cmd.sh. Results are saved in $d1/cmd.out for the following d1:'.format(d0))
#    mylib.myshell('grep "export d1" {}/cmd.sh'.format(d0))
    mylib.myshell('grep "export d1" {}/cmd.sh >> {}/d1.env'.format(d0,d0))
    print('#For the next phase, execute: source {}/d1.env'.format(d0))
