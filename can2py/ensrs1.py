#!/usr/bin/env python
# -*- coding: utf-8 -*-
###
#chainer 3.1.0
##

#Bagging CAN2 Written by Hiromu Kitayama

import switchCupy
xp = switchCupy.xp_factory()
xpfloat=switchCupy.xpfloat(xp)
#import numpy as xp
#import cupy as xp
######

import argparse
from sklearn.datasets import load_diabetes
import random
#import chainer
#from chainer import cuda, Variable, optimizers, serializers
#import chainer.functions  as F
#import chainer.links as L
#from chainer import cuda, Variable, FunctionSet, optimizers
###
import csv
import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/2015/12/16/161410
import matplotlib.pyplot as plt
import math
import time
import datetime
from mpl_toolkits.mplot3d import Axes3D
import subprocess
import copy
import os
import re
import my_plinn
#
#import matplotlib.pyplot as plt
#import matplotlib.ticker as tick # 目盛り操作に必要なライブラリを読み込みます
#import matplotlib.cm as cm
import sys
#
import concurrent.futures
#
from multiprocessing import Pool
import multiprocessing as multi

#import statistics
##
#import am #am_kitayama  #importing am.py
#import sim #sim_kitayama
#import my_plinn #my_plinn_kitayama
#import my_misc
#import can2_kitayama
####
ZERO=1e-20


def myshell(cmd): #no stop even when error occured

  try:
    retcode=subprocess.Popen(cmd, shell=True)

    if retcode < 0:
      print('my subprocess is terminated by signal {}'.format(retcode))

#    else:
#      pass
#      print "my Child returned", retcode
  except OSError as e:
    print("Execution failed:{} {}".format(cmd, e))
  return retcode.wait()

def set_random_seed(seed): 
  # set Python random seed
  random.seed(seed)
  # set NumPy random seed
  xp.random.seed(seed)
  return

def fn2dbe(fn): #fname to dir+body of fname, extension of fname 
  d,be=os.path.split(fn)
  b,e=os.path.splitext(be) #b,e=be.split('.',1)
  return d,b,e #directory, body of fname, extension of fname 

##############メイン関数#############################
if __name__ == "__main__":
#  import pdb;pdb.set_trace(); #for debug 

#引数設定
  parser = argparse.ArgumentParser(description='Chainer example: MNIST')
  parser.add_argument('--gpu', '-g', default=-1, type=int,
                      help='GPU ID (negative value indicates CPU)')
###########kuro
  parser.add_argument('-bag', type=str, default='100,0.7,1,4',
                      help='b,a,s,m for bagging; b=n_bags, a=bagsize-ratio,s=seed,m,number-of-parallel')
  ##function_approximation
  parser.add_argument('-fn', type=str, default='',
                      help='fntrain,fntest,IDexe; IDexe:ID of execution for parallel processing')
  parser.add_argument('-k', type=str, default='',
                      help='k1 and k2: number of input channels k=k1,k2=0')

  ###init_net() in my_plinn.c
  parser.add_argument('--inet', '-in', type=str, default='',
                      help='n-units,n_compare, v_thresh,vmin,vmin2,v_ratio,width')

  parser.add_argument('-ex', type=str, default='',
                      help='l_mode,gamma0,nentropy_thresh, n-it, n-display,rot_x,rot_y')
  parser.add_argument('--seed', '-s', default='', type=str,
                      help='seed of random number')
  parser.add_argument('-DISP', default='', type=str,
                      help='0 for display no-figures.')
  parser.add_argument('-Tpinv', default='', type=str,
                      help='Tpinv for use pseudo-inverse from t=Tpinv learning iterations.')
  parser.add_argument('-nop', type=int, default=0,
                      help='1 for noprint 0 for print')

##########kuro

  ### main() in main.c
  parser.add_argument('--epochs', '-e', type=str, default='', #type=int, default=100, 
                      help='number of epochs to learn')
  parser.add_argument('-BIAS', '-B', type=str, default='', #type=int, default=1, 
                      help='Bias')
  parser.add_argument('-Lstd', '-Ls', type=str, default='', #default="0,2"
                      help='Lstd,Lsdtm')
  parser.add_argument('-ib', '-ib', type=str, default='', #"0,0,0,0", 
                      help='ib')

  ### load_data() in my_function.c
#  parser.add_argument('--data_class', '-dc', type=str, default='', #'1', 
#                      help='data_class 0:timeseries,1:regression')

  ###
#  parser.add_argument('-Nbas', type=str, default='60,100,0.7,1',
#                      help='N,b,a,s for bagging; N:number of units, b=n_bags, a=bagsize-ratio,s=seed,N,numberofunits')

  parser.add_argument('-t', type=str, default='',
                      help='null for regression, t:tr0-tr1:tp0-tp1:tpD:tpG:Ey for recursive tpD-step ahead prediction with tpG=0, non-recursive one step ahead pred with tpG=1')

  ### normalize_data(DATA *givendata, NET *net)
  parser.add_argument('--ytrans', '-y', type=str, default='', #"0,0,0,0",
                      help='ymin0,ymax0,ymin1,ymax1 to transform y in [ymin0,ymax0] to y in [ymin1,ymax1]')
  parser.add_argument('--xtrans','-x', type=str, default='', #"0,0,0,0",
                      help='xmin0,xmax0,xmin1,xmax1 to transform x in [xmin0,xmax0] to x in [xmin1,xmax1]')
  parser.add_argument('-r', type=str, default='', #"0,0,0",
                      help='r1,r2 for integers r1 and r2 is the resolution, no digitization if r1=0')

  parser.add_argument('--pinv', '-pI', type=str, default='', #default=0, type=int,
                      help='1 for use pseudo-inverse')

#later#  parser.add_argument('--resume', type=str, default='', # 'log/model.npz,0',
#later#                      help='Resume the model')
#later#
#later#  parser.add_argument('--alpha','-a', type=float, default=0.001) #learning rate?
#later##  parser.add_argument('--LINESIZE','-L', type=float, default=0)
#later#  parser.add_argument('--n_bags','-nb', type=float, default=1)
#later#  parser.add_argument('--n','-n', type=str, default='1,10,10,1',
#later#                      help='<0>,<N1>,<nens>,<NStep> or <1>,<N1>,<N2>,<NStep> ')
#later#  parser.add_argument('--chkomit','-ch', type=int, default=0)
#later#  parser.add_argument('--bagging','-bg', type=str, default='tmp/train-test.csv',help='if BAGGING = BAGwithoutVal enter /dev/null. Or tmp/train-test.csv or tmp/test.csv')
#later#  parser.add_argument('--Tsk', '-Tsk', default="0,0,0,0", type=str,
#later#                      help='<Task>[,<t1>,<t2>,<t0>] <Task>==1 for regression, ==0 for time-series [t0:t1+t0-1] for training;[t1+t0:t2+t0] for test.')
#later#  parser.add_argument('--lossall','-lossall', type=str, default=0)
#later#  parser.add_argument('--lcom','-lcom', type=str, default=0)
#later#  parser.add_argument('--r0','-r0', type=int, default=0,
#later#                      help='0 or 1')
#later#  parser.add_argument('--ib','-ibm', type=str, default='0,0',help='-1 is NULL')#ibmode
#later#  parser.add_argument('--LDm','-Ldm', type=str, default=2)#LDmode
#later#  parser.add_argument('--bst','-bst', type=str, default='0,0')#boost
#later#  parser.add_argument('--t','-t', type=str, default='result')#fn_target
#later#  parser.add_argument('--i','-i', type=int, default='0')#intmode
#later#  parser.add_argument('--rdm','-rdm', type=int, default='0')#rangedatamode
#later#  parser.add_argument('--ssp','-ssp', type=int, default='0')#ssp
#later#  parser.add_argument('-tau','-tau' , type=str, default="0,8.0,8.0,2.0",
#later#                      help='0,tau_c,&tau_h,&eta1 or 1,tau_c,&tau_h')
#later#  parser.add_argument('--bayes','-bayes' , type=str, default="0,0,0,0,1",
#later#                      help='Bayes,BayesLambdaL,BayesLambdaS,BayesUseAllData,Bayesseed'),
#later#  parser.add_argument('--nobt','-nobt', type=int, default='0')#nob_thresh
#later#  parser.add_argument('--fupdate','-fupdate', type=str, default='1')#fupdate
#later#  parser.add_argument('--pupdate','-pupdate', type=str, default='1')#pupdate
#later#  parser.add_argument('--e4t','-e4t', type=float, default=0)#err4terminate
#later#  parser.add_argument('--e4p','-e4p', type=float, default=0)#err4propagate

  
#############
  args=parser.parse_args()
  argv=sys.argv
  cmd=''
  for i,v in enumerate(argv):
    cmd+=v+' '
  print('#start:python {}'.format(cmd))

  #初期化  
  MULTIFOLD = 1
  NoBAG = 0
  BAGwithVal = 1
  BAGwithoutVal = 2
  NoBoost = 0
  EmBoost = 1
  GbBoost = 2

  BAGGING = NoBAG;  #L177
  Boost = NoBoost;
  meannTestData = 0;
  nValData = 0;
  t_boost = 0;  #apply boosting for t_boost>=1, Gradient-based boosting for t_boost==-2
#  chkomit = 0;  #chkomit=1;
  fnsize = 256
  #char **fntrain=NULL;//fntrain[nFoldsmax][256];
  #char **fntest=NULL;// char fntest[nFoldsmax][256];
  err4propagate = 0;
  err4terminate = 0;
  nop=0;

  if args.t=='':
    data_class='reg' #regression or function approximation
  else:
    data_class='ts' #time_series

########
  fn=args.fn.split(',')
  lfn=len(fn)
  if lfn<=0:
    print('#specify -fn <fntrain>,<fntest>,<fnpred>')
    quit()
  fntest0,fnpred0='/dev/null','tmp/predict.dat' #defalut
  if lfn>=1:
    fntrain0=fn[0]
    if lfn>=2:
      fntest0=fn[1]
      if lfn>=3:
        fnpred0=fn[2]
####
#  import pdb;pdb.set_trace() #for debug 
#  argsNbas=args.Nbas.split(',')
#  N=n_units=int(argsNbas[0])
#  b_bag=n_Folds=n_bags=int(argsNbas[1])
#  a_bag=float(argsNbas[2])
#  s_bag=int(argsNbas[3])

  argsbag=args.bag.split(',')
  largsbag=len(argsbag)
  b_bag,a_bag,s_bag,m_bag=10,0.7,1,0 #default

  if largsbag>=1:
    b_bag=n_Folds=n_bags=int(argsbag[0])
    if largsbag>=2:
      a_bag=float(argsbag[1])
      if largsbag>=3:
        s_bag=int(argsbag[2])
        if largsbag>=4:
          m_cpu=int(argsbag[3])
  if m_cpu<=0:
      m_cpu=multi.cpu_count()

  if args.k !='':
    _k=map(int,args.k.split(','))
    _k2=0
    if len(_k)>=2:
      _k1,_k2=_k
    else:
      _k1=_k[0]
    k=_k1+_k2
    k1=k+1

  if args.inet =='':
    print('#specify -in <n-units>,<n_compare>,<v_thresh>,<vmin>,<vmin2>,<v_ratio>,<width>')
    quit()
  else:
    n_units=NC= args.inet.split(',')[0]
#  import pdb;pdb.set_trace() #for debug 
#  inet = args.inet.split(',') 
#  N=NC = int(inet[1])
#  vt = float(inet[2])
#  vm = int(inet[3])
#  vr = float(inet[5])
#  w = float(inet[6]) #L769

  cmd_can2='-k {} -in {} -s {}'.format(k,args.inet,s_bag)

  if args.ex !='':
    cmd_can2 += ' -ex {}'.format(args.ex)
    ex = args.ex.split(',')  
    T=ex[3]
  if args.Tpinv !='':
    cmd_can2 += ' -Tpinv {}'.format(args.Tpinv)
    Tpinv=args.Tpinv
  if args.seed !='':
    cmd_can2 += ' -s {}'.format(args.seed)
    seed=int(args.seed)
  if args.nop !='':
    cmd_can2 += ' -nop {}'.format(args.nop)
    nop=args.nop
  if args.DISP !='':
    cmd_can2 += ' -DISP {}'.format(args.DISP)
  if args.BIAS !='':
    cmd_can2 += ' -BIAS {}'.format(args.BIAS)
  if args.Lstd !='':
    cmd_can2 += ' -Ls {}'.format(args.Lstd)
  if args.ib !='':
    cmd_can2 += ' -ib {}'.format(args.ib)
#  if args.data_class !='':
#    cmd_can2 += ' -dc {}'.format(args.data_class)
  if args.ytrans !='':
    cmd_can2 += ' -y " {}"'.format(args.ytrans)
  if args.xtrans !='':
    cmd_can2 += ' -x {}'.format(args.xtrans)
  if args.r !='':
    cmd_can2 += ' -r {}'.format(args.r)
  if args.pinv !='':
    cmd_can2 += ' -pI {}'.format(args.pinv)
#  if args.t !='':
#    cmd_can2 += ' -t {}'.format(args.t)

  set_random_seed(s_bag)

#  nr=xp.zeros((n_Folds,n_train),dtype=xp.int32)
#  nc=xp.zeros((n_Folds,n_train0),dtype=xp.int32)
#  Itrain_Fold=[]
#  Itest_Fold=[]

  cmd=[]
  if data_class=='ts':#time-series
    if 1==0 and _Folds<=0: #single CAN2
      cmdj='python can2.py -fn {} -t {} {}'.format(fntrain0,args.t,cmd_can2)
      cmd.append(cmdj)
    else: ## if n_Folds<=0: #bagging CAN2 
      argst=args.t.split(':')
      tr,tp=argst[0],argst[1]
      largst=len(argst)
      tpD,tpG,tpEy=0,0,15
      if largst>=3:
        tpD=int(argst[2])
        if largst>=4:
          tpG=int(argst[3])
          if largst>=5:
            tpEy=int(argst[4])
      tr0,tr1=map(int,tr.split('-'))
      tp0,tp1=map(int,tp.split('-'))
###learning
      y0=xp.array(pd.read_csv(fntrain0,delim_whitespace=True,dtype=xpfloat,header=1))[:,0]
#      net['DiffMode']=0
#      if net['DiffMode']==1:
#        y1=xp.zeros((len(y0)-1),dtype=xpfloat)
#        for t in range(len(y0)-1):
#          y1[t]=y0[t+1]-y0[t]
#        y0=y1
##

      n_train0=tr1-tr0-k
      n_test0=1 #tp1-tp0
      train0=xp.zeros((n_train0,k1),dtype=xpfloat)
      for t in range(n_train0):
        t0=t+tr0
        train0[t,:k]=y0[t0:t0+k][::-1] #reverse y(t)= M(0)*y(t-1)+...+M(k-1)*y(t-k)...+ Mk*BIAS
        train0[t,k]=y0[t0+k+tpD-1]
      ###
      fntest0='tmp/test{:03d}.dat'.format(tp0)
      test0=xp.zeros((1,k1),dtype=xpfloat)
#      import pdb;pdb.set_trace(); #for debug 
      test0[0,:k]=y0[tp0-k:tp0][::-1]
      test0[0,k]=y0[tp0]
      df=pd.DataFrame(test0.reshape((-1,k1)))
      df.to_csv(fntest0,index=False,sep=' ',header=None, float_format='%.7e')

      Itrain0=[i for i in range(len(train0))]
      n_train=bagsize=int(n_train0*a_bag) 
      prob=xp.ones((n_train0))*1./n_train0 #same probability
##
      nc=xp.zeros((n_train0,n_Folds)) #
      fnpred=[]
      fnnet=[]
      for j in range(n_Folds):
        fnnetj ='tmp/{}+null+b{}a{}s{}N{}k{}j{}.net'.format(fn2dbe(fntrain0)[1],n_Folds,a_bag,s_bag,n_units,k,j)
        fnnet.append(fnnetj)
        if not os.path.exists(fnnetj):
          if n_Folds==1:
            Itrain_Foldj=[i for i in range(n_train0)]
          else:
            Itrain_Foldj=xp.random.choice(Itrain0, size=n_train, p=prob) #functions as wa
          fntrainj='tmp/train{:02d}.dat'.format(j)
          df=pd.DataFrame(train0[Itrain_Foldj,:].reshape((-1,k1)))
          df.to_csv(fntrainj,index=False,sep=' ',header=None, float_format='%.7e')
          fnpredj='tmp/tp{}-{}+null+b{}a{}s{}N{}k{}j{}.dat'.format(tp0,fn2dbe(fntrain0)[1],n_Folds,a_bag,s_bag,n_units,k,j)
          fnpred.append(fnpredj)
          cmdj='python can2.py -fn {},{},{} -fns {} {}'.format(fntrainj,fntest0,fnpredj,fnnetj,cmd_can2)
          cmd.append(cmdj)
      ###############
      #  execution of learning bags
      ###############
      #import pdb;pdb.set_trace(); #for debug 
      starttime = time.time()
      with concurrent.futures.ProcessPoolExecutor(m_cpu) as excuter:
        result_list = list(excuter.map(myshell, cmd))
      elapsed_time = time.time() - starttime
      #  print('#Elapled time={}'.format(elapsed_time))
      ###############
      ##net-load()
      ###############
      net=[]
      for j in range(n_Folds):
        net.append(my_plinn.net_load(fnnet[j]))
    ###############
    #  execution of ensemble
    ###############
    n_pred=tp1-tp0
    ypbag=xp.zeros((n_pred,n_Folds),dtype=xpfloat)
    yp=xp.zeros((k+n_pred),dtype=xpfloat)
    yp[0:k]=y0[tp0-k:tp0]
    #t=0 or tp0
    X=xp.zeros((1,k1),dtype=xpfloat)
    X[0,k]=1 #yp[t+k+tpD-1] #dummy?
    for t in range(0,n_pred):
      X[0,:k]=yp[t:t+k][::-1] #reverse y(t)= M(0)*y(t-1)+...+M(k-1)*y(t-k)...+ Mk*BIAS
      for j in range(n_Folds):
        y1,y2,ypbag[t,j]=my_plinn.calc_output(net[j],X[0,:],X[0,:k]) 
      yp[t+k]=xp.mean(ypbag[t,:])
#      import pdb;pdb.set_trace(); #for debug 
    mo=xp.concatenate((yp[k:].astype(str).reshape((-1,1)),xp.array([t for t in range(tp0+tpD,tp1+tpD)],dtype=str).reshape((-1,1))),axis=1)
    mo=xp.concatenate((mo,y0[tp0:tp1].astype(str).reshape((-1,1))),axis=1)
    df=pd.DataFrame(mo)
    df.to_csv(fnpred0,index=False,sep=' ',header=None)
#    import pdb;pdb.set_trace(); #for debug 
    if 1==1: #net['DISP']>0:
      import my_misc
      hpred=n_pred
      for t in range(n_pred):
        if abs(yp[t+k]-y0[t+tp0])>tpEy:
          hpred=t
          break;
#      import pdb;pdb.set_trace(); #for debug 
      with open('tmp/msp.plt','w') as fp:
        fp.write('set grid;set title "Recursive MultiStep Pred: T={} N={} seed={} Tpinv={} H={}(Ey{})"\n'.format(T,n_units,s_bag,Tpinv,hpred,tpEy))
        fp.write('set term postscript eps enhanced color;set output "tmp/msp.eps"\n')
        fp.write('plot "{}" using 2:3 w l t "y","" using 2:1 w l t "yp", "" using 2:($1-$3) w l t "yp-y"\n'.format(fnpred0))
      my_misc.myshell('gnuplot tmp/msp.plt')
      my_misc.myshell('gv tmp/msp.eps&')
      elapsed_time1 = time.time() - starttime
      mes='[{},{}]({:.1f}s) #[T,Tpinv] k{} N{} b{}a{}s{}m{} nop{} t{}H{}'.format(T,Tpinv,elapsed_time1,k,n_units,b_bag,a_bag,s_bag,m_cpu,nop,args.t,hpred)
      print('{}'.format(mes))

      quit()
#    import pdb;pdb.set_trace(); #for debug 
  #######################################
  elif data_class=='reg': #regression function-approximation
    train0=xp.array(pd.read_csv(fntrain0,delim_whitespace=True,dtype=xpfloat,header=None))
    if fntest0!='/dev/null':
      test0=xp.array(pd.read_csv(fntest0,delim_whitespace=True,dtype=xpfloat,header=None))  
      n_test0=test0.shape[0]
    else:
      n_test0=0
    n_train0,k1=train0.shape
    k=k1-1
    Itrain0=[i for i in range(len(train0))]
    n_train=bagsize=int(n_train0*a_bag) 
    prob=xp.ones((n_train0))*1./n_train0 #same probability

    if n_Folds<=0: #single CAN2
      cmdj='python can2.py -fn {},{},{} {}'.format(fntrain0,fntest0,fnpred0,cmd_can2)
      cmd.append(cmdj)
    else: ## if n_Folds<=0: #bagging CAN2 
      nc=xp.zeros((n_train0,n_Folds)) #
      fnpred=[]
      for j in range(n_Folds):
        Itrain_Foldj=xp.random.choice(Itrain0, size=n_train, p=prob) #functions as walkeralias
  #      Itrain_Fold.append(Itrain_Foldj) #involves duplicated elements
    #    trainj.append(train0[Itrain_Fold,:].reshape((-1,k1)))
    #    testj.append(train0[Itest_Fold,:].reshape((-1,k1)))
    #    import pdb;pdb.set_trace(); #for debug 
    #    print('#j={}'.format(j))
        fntrainj='tmp/train{:02d}.dat'.format(j)
        #testj=train0[Itrain_Fold[-1],:].reshape((-1,k1))
    #    import pdb;pdb.set_trace(); #for debug 
        df=pd.DataFrame(train0[Itrain_Foldj,:].reshape((-1,k1)))
        df.to_csv(fntrainj,index=False,sep=' ',header=None, float_format='%.7e')
        fntestj='tmp/test{:02d}.dat'.format(j)
        if fntest0=='/dev/null':#out-of-bag prediction
          Itest_Foldj=list(set(Itrain0)-set(Itrain_Foldj))
  #        Itest_Fold.append(Itest_Foldj)
          testj=train0[Itest_Foldj,:].reshape((-1,k1))
          nc[Itest_Foldj,j]=1 #
          n_pred=n_train0
        else:
          testj=test0
          n_pred=n_test0
        df=pd.DataFrame(testj)
        df.to_csv(fntestj,index=False,sep=' ',header=None, float_format='%.7e')
        fnpredj='tmp/{}-{}+{}+b{}a{}s{}N{}k{}j{}.dat'.format(fn2dbe(fnpred0)[1],fn2dbe(fntrain0)[1],fn2dbe(fntest0)[1],n_Folds,a_bag,s_bag,n_units,k,j)
    #    fn.append([fntrainj,fntestj,fnpredj])
        fnpred.append(fnpredj)
        cmdj='python can2.py -fn {},{},{} {}'.format(fntrainj,fntestj,fnpredj,cmd_can2)
        cmd.append(cmdj)
    #  import pdb;pdb.set_trace(); #for debug 
    ###############
    #  execution of learning
    ###############
    starttime = time.time()
    with concurrent.futures.ProcessPoolExecutor(m_cpu) as excuter:
    #  with concurrent.futures.ProcessPoolExecutor(max_workers=multi.cpu_count()) as excuter:
      result_list = list(excuter.map(myshell, cmd))
    elapsed_time = time.time() - starttime
    #  print('#Elapled time={}'.format(elapsed_time))
    ###############
    #  execution of ensemble
    ###############
    ypbag=xp.zeros((n_pred,n_Folds),dtype=xpfloat)
    if fntest0!='/dev/null': #not out-of-bag
      for j,fnpredj in enumerate(fnpred):
        ypbag[:,j]=xp.array(pd.read_csv(fnpredj,delim_whitespace=True,dtype=str,header=None))[:,0].astype('float64')
      yp=xp.mean(ypbag,axis=1)
      mse=xp.var(yp-test0[:,-1])
    else: #out-of-bag
      for j,fnpredj in enumerate(fnpred):
        ypj=xp.array(pd.read_csv(fnpredj,delim_whitespace=True,dtype=str,header=None))[:,0].astype('float64')
        ncj=nc[:,j];Ipredj=xp.where(ncj==1)[0];ypbag[Ipredj,j]=ypj
  #      ypbag[Itest_Fold[j],j]=ypj
  #      import pdb;pdb.set_trace(); #for debug 
      yp=xp.zeros((n_pred),dtype=xpfloat)
      for i in range(n_pred):
        nci=nc[i,:]
        Ipredi=xp.where(nci==1)[0]
        yp[i]=xp.mean(ypbag[i,Ipredi],axis=0)
      mse=xp.var(yp-train0[:,-1])
  #      import pdb;pdb.set_trace(); #for debug 

    df=pd.DataFrame(yp)
    df.to_csv(fnpred0,index=False,sep=' ',header=None, float_format='%.7e')
    elapsed_time1 = time.time() - starttime
    mes='[{},{}]({:.1f}s) {:.3e} #[T,Tpinv] MSE n{},{} k{} N{} b{} a{} s{} m{} seed{} nop{}'.format(T,Tpinv,elapsed_time1,mse,n_train0,n_test0,k,n_units,b_bag,a_bag,s_bag,m_cpu,seed,nop)
    print('{}'.format(mes))
    quit()
#kitayama#  import pdb;pdb.set_trace(); #for debug 
#kitayama#########
#kitayama##  The following multiprocess Pool also works
#kitayama##  starttime = time.time()
#kitayama### p = Pool(5)
#kitayama##  p = Pool(multi.cpu_count())
#kitayama##  p.map(myshell, cmd)
#kitayama##  p.close()
#kitayama##  elapsed_time = time.time() - starttime
#kitayama##  print('#Elapled time={}'.format(elapsed_time))
#kitayama#  import pdb;pdb.set_trace(); #for debug 
#kitayama#
#kitayama##  import threading
#kitayama##  import pdb;pdb.set_trace(); #for debug 
#kitayama##  starttime = time.time()
#kitayama##  for j,c in enumerate(cmd):
#kitayama##    p = threading.Thread(target=myshell,args=c)
#kitayama##    p.start()
#kitayama##    p.join()
#kitayama##  elapsed_time = time.time() - starttime
#kitayama##  print('#Elapled time={}'.format(elapsed_time))
#kitayama#  #Elapled time=59.8942630291
#kitayama#
#kitayama#
#kitayama##  starttime = time.time()
#kitayama##  for j,c in enumerate(cmd): 
#kitayama##    myshell('{}&'.format(c))
#kitayama##    if j %4 == 0:
#kitayama##      import pdb;pdb.set_trace(); #for debug 
#kitayama##
#kitayama##  elapsed_time = time.time() - starttime
#kitayama#
#kitayama##  traintest=xp.concatenate((train,test),axis=0)
#kitayama# # df=pd.DataFrame(traintest)
#kitayama# # df.to_csv("tmp/train-test.csv",index=False,sep=' ',header=None, float_format='%.7e')
#kitayama#
#kitayama#
#kitayama#
#kitayama##  with open('tmp/train-test.csv','w') as f:
#kitayama##    writer = csv.writer(f)
#kitayama##    writer.writerows(traintest)
#kitayama#
#kitayama##  import pdb;pdb.set_trace(); #for debug
#kitayama#
#kitayama#  method=args.data_class
#kitayama#  nFolds=args.n_bags
#kitayama#  alpha=args.alpha
#kitayama#
#kitayama#  if method == -1:
#kitayama#    nFolds=1
#kitayama#  elif nFolds<1 or (method==0 and alpha<1e-10):
#kitayama##   usage(argc,argv);
#kitayama#    sys.exit()
#kitayama#
#kitayama#  if method == MULTIFOLD:
#kitayama#    if alpha < 1: 
#kitayama#      alpha = 1
#kitayama#    nFolds1 = nFolds;
#kitayama#    nFolds = nFolds1*alpha;
#kitayama#  
#kitayama#
#kitayama##############
#kitayama#  N1 = 0
#kitayama#  N2 = 0
#kitayama#  ptn = 0
#kitayama#  _n = map(int,args.n.split(','))
#kitayama#  if _n[0] == 0:
#kitayama#    N1 = _n[1]
#kitayama#    nens = _n[2]
#kitayama#    N2 = N1 + nens*NStep-1
#kitayama#    NStep = _n[3]
#kitayama#    if NStep < 1:
#kitayama#      NStep = 1
#kitayama#  else:
#kitayama#    N1 = _n[1]
#kitayama#    N2 = _n[2]
#kitayama#    NStep = _n[3]
#kitayama#
#kitayama#  if N1 < 1:
#kitayama#    print("nCells must be bigger than {}.".format(0))	#L579
#kitayama#    N1 = 1
#kitayama#    N2 = 1
#kitayama#    NStep = 1;
#kitayama#
#kitayama#  nens = 0;
#kitayama#  for nCells in range(N1,N2,NStep):
#kitayama#    nens+=1
#kitayama#    NN[nens] = nCells;
#kitayama#
#kitayama###########L618
#kitayama#  ibg = 0
#kitayama#  rethresh_boost = 12.
#kitayama#  angedatamode = 0
#kitayama#  #double *cbst,*ypt,*wbst,*wbst1,
#kitayama#  tau_c = 4.
#kitayama#  tau_h = 4
#kitayama#  #double *cbst,*ypt,*wbst,*wbst1,
#kitayama#  tau_c = 8.
#kitayama#  tau_h = 8.
#kitayama#  eta1 = 2.0
#kitayama##  Lstd=0
#kitayama##  Lstdm=2  #double Lstd=0;int Lstdm=0;
#kitayama##  lossall = NULL
#kitayama#  Bayes = 0
#kitayama#  BayesSeed = 0
#kitayama#  iBayes = 0
#kitayama#  BayesLambdaL = 0
#kitayama#  BayesLambdaS = 0
#kitayama#  BayesUseAllData = 0
#kitayama#  Bayesseed = 1
#kitayama#
#kitayama#  _K = map(int,args.k.split(','))
#kitayama#  K = _K[0]
#kitayama#  xmin = xp.zeros(K,dtype=xpfloat)
#kitayama#  xmax = xp.zeros(K,dtype=xpfloat)
#kitayama#  xmin1 = xp.zeros(K,dtype=xpfloat)
#kitayama#  xmax1 = xp.zeros(K,dtype=xpfloat)
#kitayama#  x0m = xp.zeros(K,dtype=xpfloat)
#kitayama#  x1m = xp.zeros(K,dtype=xpfloat)
#kitayama#  x0M = xp.zeros(K,dtype=xpfloat)
#kitayama#  x1M = xp.zeros(K,dtype=xpfloat)
#kitayama#  y0m = 0.
#kitayama#  y1m = 0.
#kitayama#  y0M = 0.
#kitayama#  y1M = 0.
#kitayama#
#kitayama#  alpha = args.alpha
#kitayama#  chkomit = args.chkomit
#kitayama#
#kitayama#  fn_bagging = args.bagging
#kitayama##  train=xp.array(pd.read_csv(fn_bagging,delim_whitespace=True,dtype=xpfloat,header=None))
#kitayama#  if fn_bagging == '/dev/null':
#kitayama#    print("bagging without validfile")
#kitayama#    BAGGING = BAGwithoutVal	#bagging without validfile
#kitayama#
#kitayama#  else:
#kitayama#    fp = open(fn_bagging,'r')
#kitayama#    if fp != None:
#kitayama#      print("There is bagging file {}.".format(fn_bagging))
#kitayama#      BAGGING = BAGwithVal  #bagging with validfile
#kitayama#      nValData = 0
#kitayama#      bagging=xp.array(pd.read_csv(fp,delim_whitespace=True,dtype=xpfloat,header=None))
#kitayama#      nValdata = len(bagging)
#kitayama#    
#kitayama#    else:
#kitayama#      print("There is no bagging file {}.".format(fn_bagging))	#L669
#kitayama#      sys.exit()
#kitayama#
#kitayama#
#kitayama###########
#kitayama#  xt=map(int,args.xtrans.split(','))   #L693
#kitayama#  if len(xt) == 4:
#kitayama#    _xm=xt[0]
#kitayama#    _xM=xt[1]
#kitayama#    _xm1=xt[2]
#kitayama#    _xM1=xt[3]
#kitayama#    xmin+=_xm	#brodcast
#kitayama#    xmax+=_xM
#kitayama#    xmax1+=_xm1
#kitayama#    xmin1+=_xM1
#kitayama#  elif len(xt) == 5:
#kitayama#    j = xt[0]
#kitayama#    _xm=xt[1]
#kitayama#    _xM=xt[2]
#kitayama#    _xm1=xt[3]
#kitayama#    _xM1=xt[4]
#kitayama#    xmin[j] = _xm
#kitayama#    xmax[j] = _xM
#kitayama#    xmin1[j] = _xm1
#kitayama#    xmax1[j] = _xM1
#kitayama#  else:
#kitayama#    j = xt[0]
#kitayama#    xmin[j] = xt[1]
#kitayama#    xmax[j] = xt[2]
#kitayama#    xmin1[j] = xt[3]
#kitayama#    xmax1[j] = xt[4]
#kitayama#    x0m[j] = xt[5]
#kitayama#    x1m[j] = xt[6]
#kitayama#    x0M[j] = xt[7]
#kitayama#    x1M[j] = xt[8]
#kitayama#
#kitayama#  yt=map(int,args.ytrans.split(','))  #L708
#kitayama#  if len(yt) == 4:
#kitayama#    ymin = yt[0]
#kitayama#    ymax = yt[1]
#kitayama#    ymin1 = yt[2]
#kitayama#    ymax1 = yt[3]
#kitayama#  elif len(yt) == 8:
#kitayama#    ymin = yt[0]
#kitayama#    ymax = yt[1]
#kitayama#    ymin1 = yt[2]
#kitayama#    ymax1 = yt[3]
#kitayama#    y0m = yt[4]
#kitayama#    y1m = yt[5]
#kitayama#    y0M = yt[6]
#kitayama#    y1M = yt[7]
#kitayama#  else:
#kitayama#    ymin = yt[0]
#kitayama#    ymax = yt[1]
#kitayama#    ymin1 = 0
#kitayama#    ymax1 = 1
#kitayama# 
#kitayama#
#kitayama#  _Tsk = map(int,re.split('[,-]',args.Tsk))  #L711
#kitayama#  if len(_Tsk) == 5:
#kitayama#    Task = _Tsk[0]
#kitayama#    tr0 = _Tsk[1]
#kitayama#    tr1 = _Tsk[2]
#kitayama#    tp0 = _Tsk[3]
#kitayama#    tp1 = _Tsk[4]
#kitayama#  elif len(_Tsk) == 4:
#kitayama#    Task = _Tsk[0]
#kitayama#    t1 = _Tsk[1]
#kitayama#    t2 = _Tsk[2]
#kitayama#    t0 = _Tsk[3]
#kitayama#  elif len(_Tsk) == 3:
#kitayama#    Task = _Tsk[0]
#kitayama#    t1 = _Tsk[1]
#kitayama#    t2 = _Tsk[2]
#kitayama#  else:
#kitayama#    Task = _Tsk[0]
#kitayama#    t1 = 0
#kitayama#    t2 = 0
#kitayama#    t0 = 0
#kitayama#
#kitayama#  tr0=t0;
#kitayama#  tr1=t0+t1;
#kitayama#  tp0=t0+t1;
#kitayama#  tp1=t0+t2;
#kitayama#
#kitayama###############L730
#kitayama#  Ls = map(int,args.Lstd.split(','))
#kitayama#  Lstd = Ls[0]
#kitayama#  Lstdm = Ls[1]
#kitayama#
#kitayama#  lcom = args.lcom  #lcom=0ならc言語でいうNULL
#kitayama#  lossall = args.lossall  #lossall=0ならc言語でいうNULL
#kitayama#  r0 = args.r0
#kitayama#
#kitayama#  r = map(int,args.r.split(','))  
#kitayama#  r1 = r[0]
#kitayama#  r2 = r[1]
#kitayama#  r3 = r[2]
#kitayama#
#kitayama#  ibm = map(int,args.ib.split(',')) 
#kitayama#
#kitayama#  if ibm[0] == -1: ##ib[0]=-1ならc言語でいうNULL
#kitayama#    ibmode = str(-1)
#kitayama#  else: 
#kitayama#    ibmode = args.ib
#kitayama#  
#kitayama#  LDmode = args.LDm
#kitayama#  seed = args.seed
#kitayama#  
#kitayama#  bst = map(int,args.bst.split(',')) 
#kitayama#  if len(bst) >= 1:
#kitayama#    t_boost = bst[0]
#kitayama#  if len(bst) >= 2:
#kitayama#    Boost = bst[1]
#kitayama#
#kitayama####################L765
#kitayama#  fn_taret = args.t
#kitayama#
#kitayama#  ex = args.ex.split(',')  
#kitayama#  gamma0 = float(ex[1])
#kitayama#  entropy_thresh = float(ex[2])
#kitayama#
#kitayama#  T = args.epochs
#kitayama#  intmode = args.i
#kitayama#  #L773のNとばす
#kitayama#  rangedatamode = args.rdm
#kitayama#  ssp = args.ssp
#kitayama#
#kitayama#  tau = args.tau.split(',') 
#kitayama#  if tau[0] ==0:
#kitayama#    tau_c = float(tau[1])
#kitayama#    tau_h = float(tau[2])
#kitayama#    eta1 = float(tau[3])
#kitayama#
#kitayama#  else:
#kitayama#    tau_c = float(tau[1])
#kitayama#    tau_h = float(tau[2])
#kitayama#    eta1 = 2.0
#kitayama#
#kitayama#  Bay = args.bayes.split(',') 
#kitayama#  BayesLambdaL = float(Bay[0])
#kitayama#  BayesLambdaS = float(Bay[1])
#kitayama#  BayesUseAllData = int(Bay[2])
#kitayama#  Bayesseed = int(Bay[3])
#kitayama#
#kitayama#################L808
#kitayama#  nob_thresh = args.nobt
#kitayama#  BIAS = args.BIAS
#kitayama#  seed = args.seed
#kitayama#  Tpinv = args.Tpinv
#kitayama#  nop = args.nop
#kitayama#  fupdate = args.fupdate
#kitayama#  pupdate = args.pupdate
#kitayama#  err4terminate = args.e4t
#kitayama#  err4propagate = args.e4p
#kitayama#
#kitayama################L821
#kitayama#
#kitayama#
#kitayama#
