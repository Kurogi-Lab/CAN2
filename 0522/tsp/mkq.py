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

S=['fhs', 'fms', 'mkk', 'mko','mmt','mnh','mym']
L=[1,2,3,4,5,6,7,8,9,10]
D=['zero','ichi','ni','san','si','go','roku','nana','hachi','kyu']
R=[1,0.8,0.6,0.4,0.2]
def myshell(cmd): #no stop even when error occured                                
  try:
    retcode=subprocess.Popen(cmd, shell=True)
    if retcode < 0:
      print "my Child was terminated by signal", -retcode
    else:
      print "my Child returned", retcode
  except OSError as e:
    print "Execution failed:", cmd, e
  return retcode.wait()

# http://optie.hatenablog.com/entry/2018/03/21/185647#32-ガウシアンフィルタ
def norm2d(x,y,sigma):
    Z = np.exp(-(x**2 + y**2) / (2 * sigma**2)) / (2 * np.pi * sigma**2)
    return Z

def gaussian_kernel(size):
    if size%2==0:
#        print('kernel size should be odd')
#        return
      size+=1
    sigma = (size-1)/2
    # [0,size]→[-sigma, sigma] にずらす
    x = y = np.arange(0,size) - sigma
    X,Y = np.meshgrid(x,y) 
    
    mat = norm2d(X,Y,sigma/2.)
    
    # 総和が1になるように
    kernel = mat / np.sum(mat)
    return kernel

def convolve2d_1ch(img, kernel, padding='0'):
    # エラー処理
    if len(img.shape) != 2:
        print('img should be 2d-array')
        return
    if kernel.shape[0]%2 == 0:
        print('Kernel size shold be odd')
        return
    
    edge = int(kernel.shape[0]/2)
    
    # 境界をどうするか
    if padding=='edge':
        img = np.pad(img, [edge,edge], mode='edge')
    elif padding=='reflect':
        img = np.pad(img, [edge,edge], mode='reflect')
    else:
        img = np.pad(img, [edge,edge], mode='constant', constant_values=0)
    
    sub_shape = tuple(np.subtract(img.shape, kernel.shape) + 1)

    # (rows, cols, N, N)
    conv_shape = sub_shape + kernel.shape

    # A.strides は (Aのrow方向の一要素ごとのbytes数, col方向のbytes数) のタプル
    # (shape[0]*bytes, bytes, shape[0]*bytes, bytes)
    strides = img.strides + img.strides

    submatrices = as_strided(img, conv_shape, strides)

    # (i,j)配列と(k,l,i,j)配列で, (i,j)要素同士の積和を要素とした(k,l)配列を返す
    convolved_mat = np.einsum('ij, klij->kl', kernel, submatrices)
    
    return convolved_mat

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
  parser.add_argument('-N', default=24, type=int,   help='Number of units')
  parser.add_argument('-sql', default='0', type=str,   help='1 for search q lack')
#  parser.add_argument('-lm', default='tspredv3', type=str, choices=('tspredv3', 'tspredv3er'),   help='learning machine ')
  parser.add_argument('-DISP', default='10', type=str,   help='DISP[0]==1 to make files, DISP[1]==1 to display')
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
  N=args.N
  DISP=args.DISP
  fnerr=['mmt-san2', 'fhs-hachi5']
  nS=len(S)
  nL=len(L)
  nD=len(D)
  np.random.seed(seed=32)
  for d in [dm, dq, dp, df]:#  for d in [dl, dn, dm, dq, dp, df]:
    if not os.path.exists(d): os.mkdir(d)

  if args.sql != '0': #search lack 
    for r in Ra:
      fnq='{}/*R{}*'.format(dq,r)
      Fq=[(f.split('/')[-1])[:-6] for f in glob.glob(fnq)] #file list
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
    fnout='tmp/imgvec-s.csv'
    fpout=open(fnout,'w')
    GK=gaussian_kernel(21)
    for r in Ra:
      fnq='{}/*R{}*'.format(dq,r)
      Fq=[(f.split('/')[-1])[:-6] for f in glob.glob(fnq)] #file list
      for s in Sa:
        for d in Da:
          for l in La:
            fn=s +'-'+ d + l
            if not fn in fnerr:
              myshell('make data-clean')
              if r == '1':
#                sm='{}-{}{}'.format(s,d,l) #sm=s +'-'+ d + l + '-R'+ r
                sm='{}-{}{}-R{}'.format(s,d,l,r) #sm=s +'-'+ d + l + '-R'+ r
                cmd='cp {}/{}-{}{}.dat {}/{}.dat'.format(dn,s,d,l,dm,sm)
#                import pdb;pdb.set_trace(); #for debug
#                myshell('cp {}/{}-{}{}.dat {}/{}-{}{}-R{}.dat'.format(dn,s,d,l,r,dm,s,d,l,r))
#                myshell('cp {}/{}-{}{}.dat {}/{}.dat'.format(dn,s,d,l,r,dm,sm))
#                myshell('cp {}/{}-{}{}-R{}.dat {}/{}'.format(dn,s,d,l,r,dm,sm))
              else:
                errflag=1
                while errflag == 1:
                  s2=S[np.random.randint(nS)]
                  d2=D[np.random.randint(nD)]
                  l2=L[np.random.randint(nL)]
                  fn2='{}-{}{}'.format(s2,d2,l2) 
                  sm='{}-{}{}-{}-{}{}-R{}'.format(s,d,l,s2,d2,l2,r)
                  if (not fn2 in fnerr) and (not sm in Fq):
                    errflag=0
  #              import pdb;pdb.set_trace(); #for debug
                cmd='python speechmix.py -y0 {}/{}-{}{}.dat -y1 {}/{}-{}{}.dat -r {} > {}/{}.dat'.format(dn,s,d,l,dn,s2,d2,l2,r,dm,sm)
              print(cmd)
              myshell(cmd)
#              cmd='poledistribv2+ st:{} N:24 k:8 m:poles4 dir:{} rsa:2:0.7:1:20 DiffMode:0 tt:0:400 T:100 DISP:{}'.format(sm,dm,DISP)
              #poledistribv2+.c 
              #(1)calls tspredv3 (creates tmp/*poles0.dat), and
              #(2)creates tmp/_sprecog-{}-poles0-N{}.eps
              k=8;N=24;t0=0;t1=400
              cmd='poledistribv2- st:{} N:{} k:{} m:poles4 dir:{} rsa:2:0.7:1:20 DiffMode:0 tt:{}:{} T:100 DISP:{}'.format(sm,N,k,dm,t0,t1,DISP)
#              print(cmd);
              myshell(cmd)
              #poledistribv2-.c 
              #(1)cp tmp/M.dat tmp/fhs-zero1-R1-k8N24t0-3170-M.dat
              fnM='tmp/M.dat' #fnM='tmp/'+sm+'-k{}N{}t{}-{}-M.dat'.format(k,N,t0,t1)
              M=np.array(pd.read_csv(fnM,delim_whitespace=True,dtype=np.float64,header=None))
              N,k1=M.shape
              fnmac='tmp/M.mac'
              fpmac=open(fnmac,'a')
              for n in range(N):
                fpmac.write('M[{}]:[{}'.format(n+1,M[n,0]))
                for i in range(1,k1):
                  fpmac.write(',{}'.format(M[n,i]))
                fpmac.write('];\n')
              fpmac.close()
#              myshell('cat /dev/null > tmp/poles-xyC.csv')
              for n1 in range(N):
                n=n1+1
                cmd='echo {}k:{};n:{};batch("fext.mac");quit();{}|maxima'.format("'",k,n,"'")
                print(cmd);
                myshell(cmd)
#                import pdb;pdb.set_trace(); #for debug 20191105
                #tmp/poles-xyC[n].dat
                fnxyC='tmp/poles-xyC.csv';#    fnxyC='tmp/poles-xyC-s{}d{}l{}.csv'.format(n);
                P=np.array(pd.read_csv(fnxyC,delim_whitespace=True,dtype=np.float64,header=None))
                nP=P.shape[0] #=k
                nW=100
                nW0=nW/2
                w=4.0 #[-2,2]
                w=6.0 #[-3,3]
                w0=w/2.0
                wp=2. # width of pole
                F=np.zeros((nW,nW), dtype=np.float64)
#                F=np.zeros((nW,nW), dtype=np.uint8)
                for i in range(nP):
                  X=int(nW0*(P[i,0]+w0)/w0)
                  Y=int(nW0*(P[i,1]+w0)/w0)
                  if X<0 or X>=nW or Y<0 or Y>=nW or P[i,1]==0:
                    print('({},{}<={},{})'.format(X,Y,P[i,0],P[i,1]))
                    pass
                  else:
#                    F[Y,X]=math.log1p(P[i,2])
                    F[Y,X]=P[i,2]
                FGK = np.zeros(F.shape)
                FGK = convolve2d_1ch(F, GK, padding='edge')
                FGK /=np.linalg.norm(FGK)
                for i in range(nW):
                  for j in range(nW):
                    fpout.write('{:g} '.format(FGK[i,j]))
                fpout.write('{}\n'.format(s))
#                import pdb;pdb.set_trace(); #for debug 20191105
#                print P
#                plt.imshow(FGK);plt.title("Feature");plt.colorbar();plt.show();
#                plt.imshow(FGK);plt.title("Feature");plt.colorbar();plt.pause(0.05)
                plt.imshow(FGK);plt.title("Feature");plt.pause(0.05)
#
    fpout.close()
    print('#Saved {}.'.format(fnout))
#              import pdb;pdb.set_trace(); #for debug 20191105
#              cmd='cp tmp/*-poles0.dat {}/'.format(dp)
#              print(cmd);
#              myshell(cmd)
#              cmd='mkpoleptv2+ st:{} k:8 Np:24 dir:tmp dir2:{} dout:{} rsa:2:20 tt:0:400 nt:18 nr:2 r_max:2 DISP:{}'.format(sm,dm,dq,DISP)
#              print(cmd);
#              myshell(cmd)
#              #mkpoleptv2+.c 
#              #(1)reads <dir2>/<st>   #ex: <dm>/<fms-zero9-R1> ??
#              #(2)calls mkpoleptv1+, which 
#              #   reads <dir>/*-poles0.dat and 
#              #   creates q (*-p.dat)  in <dq>, 
#              #   creates tmp/q2.plt, q2.obj, q2.eps, q2.dat co
#              #myshell('sleep 3')
#              if DISP[0]=='1':
#                cmd='mv tmp/q2.obj {}/{}-q2.obj'.format(df,sm)
#                myshell(cmd)
#                cmd='mv tmp/q2.eps {}/{}-q2.eps'.format(df,sm)
#                myshell(cmd)
#                cmd='mv tmp/q2.dat {}/{}-q2.dat'.format(df,sm)
#                myshell(cmd)
#                cmd='mv tmp/_sprecog-{}-poles0-N{}.obj {}/sprecog-{}-poles0-N{}.obj'.format(sm,N,df,sm,N)
#                myshell(cmd)
#                cmd='mv tmp/_sprecog-{}-poles0-N{}.eps {}/sprecog-{}-poles0-N{}.eps'.format(sm,N,df,sm,N)
#                myshell(cmd)
#
#$dp/fms-zero9-mmt-nana10-R0.4-k8N24t0-3277-poles0.dat #Poles(complex number)
#$df/fms-zero9-mmt-ichi4-R0.4-q2.obj                   #bar graph
#$df/sprecog-fms-zero9-mmt-ichi4-R0.4-poles0-N24.obj   #polar graph
