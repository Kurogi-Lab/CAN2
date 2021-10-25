import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
import math
import subprocess
import glob
import mylib
import time
import datetime
import sys
import os
# main
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
#oob4speakerdigit+sX_2018 sp:fhs:fms tx:zero:ichi ntxi:9 k:36 mbas:$mbas dir:$dir1 dir2:$dir2 s:-1 N:${N} sX:${sX}
#oob4speakerdigit+ sp:fhs:fms:mkk:mko:mmt:mnh:mym tx:zero:ichi:ni:san:yon:go:roku:nana:hachi:kyu ntxi:10 k:36 mbas:2:300:1.6:1 dir:$dira s:-1 N:40

  parser = argparse.ArgumentParser(description='speech normalize')
  parser.add_argument('-dr', default='.', type=str,   help='directory of training data')
  parser.add_argument('-S', default='fhs:fms:mkk:mko:mmt:mnh:mym', type=str,   help='speaker')
  parser.add_argument('-D', default='zero:ichi:ni:san:si:go:roku:nana:hachi:kyu', type=str,   help='text(digit)')
  parser.add_argument('-L', default='1:2:3:4:5:6:7:8:9', type=str,   help='digit(text) number')
  parser.add_argument('-fnerr', default='mmt-san2:fhs-hachi5', type=str,   help='files lacking data')
  parser.add_argument('-Fext', default='pP1F4x26G3x0.5m0', type=str,   help='extension')
  parser.add_argument('-Fext2', default='p', type=str,   help='target extension')
  parser.add_argument('-nlz', default='1', type=str, choices=['max','norm','1'], help='normalize by norm, max, 1(no-normalization)')

  args = parser.parse_args()
  dr=args.dr
  S=(args.S).split(':') #speakers
  L=(args.L).split(':') #text
  D=(args.D).split(':') #text
  Fext=args.Fext #Feature description
  Fext2=args.Fext2 #new Feature description2
  fnerr=(args.fnerr).split(':') #fnerr=['mmt-san2', 'fhs-hachi5']

#  argv=sys.argv
#  cmd=''
#  for a in argv:#  for i,a in enumerate(argv):
#    cmd+=a+' '
#  print('#start:python {}'.format(cmd))
#  start_time=time.time()
#  print('#start time:{}'.format(datetime.datetime.now()))
  newdir='{}/{}'.format(dr,Fext)
  print('#New dir is {}'.format(newdir))
  myshell('mkdir -p {}'.format(newdir))
  nf=0
  for s in S:#
    for d in D:#
      for l in L:#
        fnb='{}-{}{}'.format(s,d,l)
        if fnb in fnerr:
          continue
        fnq='{}/{}-*{}.dat'.format(dr,fnb,Fext) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
        F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
#        import pdb;pdb.set_trace(); #for debug
        if len(F)==0:
          print 'No files for {}'.format(fnq)
          import pdb;pdb.set_trace(); #for debug
          quit()
        elif len(F)>1:
          print 'Multiple files with {}. Specify much more.'.format(Fext)
          import pdb;pdb.set_trace(); #for debug
          quit()
        fnr='{}/{}'.format(dr,F[0])
#        import pdb;pdb.set_trace(); #for debug
        x=np.array(pd.read_csv(fnr,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
        if args.nlz=='norm':
          x /= np.linalg.norm(x)
        elif args.nlz=='max':
          x /= x.max()
        fnw='{}/{}-{}.dat'.format(newdir,fnb,Fext2)
#        import pdb;pdb.set_trace(); #for debug
        df=pd.DataFrame(x.reshape((1,-1)))
        df.to_csv(fnw,index=False,sep=' ',header=None)
#        myshell('cp {}/{} {}/{}-{}.dat'.format(dr,F[0],newdir,fnb,Fext2))
        nf+=1
  print '\n#{} files are normalized by {} and saved in dr1={}.'.format(nf,args.nlz,newdir)
