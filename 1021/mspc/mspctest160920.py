#!/usr/bin/env python
# -*- coding: utf-8 -*-
import argparse
import subprocess
import numpy as np
import random
import math
import os
import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/2015/12/16/161410

def myshell(cmd): #no stop even when error occured
  try:
    retcode=subprocess.Popen(cmd, shell=True)
    if retcode < 0:
      print "my Child was terminated by signal", -retcode
    else:
      pass
#      print "my Child returned", retcode
  except OSError as e:
    print "Execution failed:", cmd, e
  return retcode.wait()

if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='mspctest')
  parser.add_argument('--gpu', '-g', default=-1, type=int,
                      help='GPU ID (negative value indicates CPU)')
  parser.add_argument('-d1', default='../../result-mspc', type=str, help='')
  parser.add_argument('-NM', default='10', type=str, help='nM')
  parser.add_argument('-a', default='0.7', type=str, help='')
  parser.add_argument('-b', default='1', type=str, help='')
  parser.add_argument('-seed', default='13', type=str, help='')
  parser.add_argument('-umax', default='umax:10:1', type=str, help='')
  parser.add_argument('-tt', default='100', type=str, help='')
  parser.add_argument('-tS', default='tS:0.01', type=str, help='')
  parser.add_argument('-uI', default='uI:0:0.85', type=str, help='')
  parser.add_argument('-RI', default='RI:1:0.05', type=str, help='')
  parser.add_argument('-fS', default='f1 f2 f3 f4 f34', type=str, help='')
  parser.add_argument('-NN', default='1 1 1 1 1 1', type=str, help='')
  parser.add_argument('-DISP', default='0', type=srt, help='0 for display no-figures.')
  parser.add_argument('-stab', default='-1,-1,-1,2', type=str, help='')
  parser.add_argument('-cmS1', default='10 15 20 25 30 35 40 45 50', type=str, help='')
 #############
#export d0=../../result-mspc; mkdir -p $d0
#export a=0.7 b=1 tt=100; #good for Ubuntu12.04
#fstos=${d1}/stos.dat; cat /dev/null > $fstos
#export d1=${d0}/a${a}b${b}tt${tt}s${seed}; if [ ! -e $d1 ]; then mkdir $d1;fi  

  args=parser.parse_args()
  set_random_seed(args.seed)

  d1=args.d1
  fr='{}/mspcresult.dat'.format(d1)
  fstos='{}/stos.dat'.format(d1)
  fp_fr=open(fr,'w')
  fp_fstos=open(stos,'w')
  #
  fS=args.fS.split(' ')
  NN=args.NN.split(' ')
  cmS1=args.cmS1.split(' ')
  import pdb;pdb.set_trace() #for debug 
  for fn in fS:
    ff=[fS[1]]
    NN=[NN[1]]:
    if fn=='f1':
      msg='##BestST\n'
    elif fn=='f3':
      msg='##BestOS\n'
    fp_fr.write(msg)
    for i in range(1,len(fn)):
      ff='{}'.format(fS[i1]):
      NN='{}'.format(NN[i1]):
    if len(fn)==2:
      i1=int(fn[1])  
      ff='{}'.format(fS[i1]):
      NN='{}'.format(NN[i1]):
    elif len(fn)==3:
      i1=int(fn[1])  
      i2=int(fn[2])  
      ff='{}:{}'.format(fS[i1],fS[i2]):
      NN='{}:{}'.format(NN[i1],NN[i2]):
    elif len(fn)==3:
      i1=int(fn[1])  
      i2=int(fn[2])  
      ff='{}:{}'.format(fS[i1],fS[i2]):
      NN='{}:{}'.format(NN[i1],NN[i2]):
    fp_fr.write('{}'.format(fn))
    fp_listSS=open('listSS.dat','w')
    cr=2

    for cm in cmS1:
      if DISP[0]=='1':
        dr='tmp/m{}{}'.format(cm,fn)
        myshell('mkdir -p {}'.format(dr))        
      fp_listSS.write('{} {}'.format(cr,cm))
      cmd='emulate_crane4 it:1:1 r:5 cr:2 cm:{} cC:10 ck:15 ky:0.1 {} tt:{} kxt:1 method:12:{}:{}:{}:{}:{} N:{} DISP:{} listSS:1 T:100 N2s:12 LAMBDA:0.01 {} {} {} stab:{}'.format(cm,args.umax,args.tt,NN,args.b,args.a,args.seed,ff,NN,DISP,args.uI,args.RI,arts.tS,args.stab)
      #cmd="emulate_crane4 it:1:1 r:5 cr:2 cm:$cm cC:10 ck:15 ky:0.1 $umax tt:$tt kxt:1 method:12:$NM:$b:$a:${seed}:${ff} N:${NN} DISP:$DISP listSS:1 T:100 N2s:12 LAMBDA:0.01 $uI $RI $tS stab:$stab"
      print('#Doing {} in mspetest160920.py'.format(cmd))
      myshell('cp t-AP_i.dat tmp/t-AP_i-m{}{}.dat'.format(cm,fn))
      if DISP[0]=='1':
        myshell('cp y.plt {}/; cp _y.dat {}/'.format(dr,dr))
    #done for cm in cmS1:
    fp_listSS.close()
    SS=np.array(pd.read_csv('listSS.dat',delim_whitespace=True,dtype=np.float32,header=None))
    fp_fr.write()
    fp_fstos.write('#{}={}'.format(fn,ff))
    fp_fstos.write('{}'.format(SS))
    print('#{}'.format(fr))
    print('#Detailed st and os are viewd by emacs {}'.format(fstos))
