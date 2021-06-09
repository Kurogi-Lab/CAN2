#!/usr/bin/env python
# -*- coding: utf-8 -*-
###
#see my_plinn.c
###
import switchCupy
xp = switchCupy.xp_factory()
xpfloat=switchCupy.xpfloat(xp)
####
import numpy
######
import math
import copy
import am #am_kitayama
import can2 #can2_kitayama
import scipy as sp
#from scipy.spatial.distance import euclidean
#import numba
import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/2015/12/16/161410
import time
import os

ZERO=1e-20
def load_data(givendata,test,net):
#only consider regression (function approximation)
#  givendata['data_class']='regression' #0:time series, 1:funciton approximation,3:ijcnn04,4:RangeData
##
  n_channels=k=net['k']
  k1=k+1
  givendata['k']=k
  givendata['k1']=k1
  ##
  fntrain=net['fntrain']
  givendata['path']=fntrain
  BIAS=net['BIAS']
#  import random;random.seed(net['seed'])#for check
#  import pdb;pdb.set_trace() #for debug 
  if net['data_class']=='reg': #regression or function-approximation
    if fntrain=='/dev/null':
      train=xp.zeros((0,k1))
    else:
      train=xp.array(pd.read_csv(fntrain,delim_whitespace=True,dtype=xpfloat,header=None))
#    import pdb;pdb.set_trace() #for debug 
    fntest=net['fntest']
    if fntest=='/dev/null':
      test=xp.zeros((0,k1))
    else:
      test=xp.array(pd.read_csv(fntest,delim_whitespace=True,dtype=xpfloat,header=None))
  else: #else if net['data_class']=='reg': #time_series
    y0=xp.array(pd.read_csv(fntrain,delim_whitespace=True,dtype=xpfloat,header=1))[:,0]
#    import pdb;pdb.set_trace() #for debug 
    net['DiffMode']=0
    if net['DiffMode']==1:
      y1=xp.zeros((len(y0)-1),dtype=xpfloat)
      for t in range(len(y0)-1):
        y1[t]=y0[t+1]-y0[t]
      y0=y1
      #y=-3.41,3.64,0,1
#    import pdb;pdb.set_trace() #for debug 
    #net['y0']=y0
    tpD,tpG,tpEy=1,1,15
#    tpD,tpG,tpEy=0,0,15
    argst=net['t'].split(':')
#    import pdb;pdb.set_trace() #for debug 
    tr,tp=argst[0],argst[1]
    largst=len(argst)
    if largst>=3:
      tpD=int(argst[2])
      if largst>=4:
        tpEy=int(argst[3])
    tr0,tr1=map(int,tr.split('-'))
    tp0,tp1=map(int,tp.split('-'))
    net['tr0']=givendata['tr0']=tr0
    net['tr1']=givendata['tr1']=tr1
    net['tp0']=givendata['tp0']=tp0
    net['tp1']=givendata['tp1']=tp1
    net['tpEy']=givendata['tpEy']=tpEy
    if tpD==0:
      print('#tpD should not be 0.')
      quit()
    elif tpD>0:
      tpG=1
    else:
      tpD=-tpD
      tpG=-1

    net['tpD']=givendata['tpD']=tpD
    net['tpG']=givendata['tpG']=tpG

    ###
    n_train=tr1-tr0-n_channels
    n_test=tp1-tp0
    train=xp.zeros((n_train,k1),dtype=xpfloat)
    for t in range(n_train):
      t0=t+tr0
      train[t,:k]=y0[t0:t0+k][::-1] #reverse y(t)= M(0)*y(t-1)+...+M(k-1)*y(t-k)...+ Mk*BIAS
      train[t,k]=y0[t0+k+tpD-1]
    #check
#    train=xp.array(pd.read_csv('tmp/train000.dat',delim_whitespace=True,dtype=xpfloat,header=None))
#    import pdb;pdb.set_trace(); #for debug 
    ###
    test=xp.zeros((n_test,k1),dtype=xpfloat)
    for t in range(n_test):
      t0=t+tp0
      test[t,:k]=y0[t0-k+1-tpD:t0+1-tpD][::-1] #reverse 20200122 modified
      test[t,k]=y0[t0]                         #20200122 modified
#    import pdb;pdb.set_trace() #for debug 
#    df=pd.DataFrame(test)
#    df.to_csv('tmp/test2000.dat',index=False,sep=' ',header=None)
#    test=xp.array(pd.read_csv('tmp/test2000.dat',delim_whitespace=True,dtype=xpfloat,header=None))
#    import random;random.seed(net['seed'])#for check
#      test[t,:k]=y0[t0:t0+k][::-1] #reverse
#      test[t,k]=y0[t0+k+tpD-1]
#    #for check
#    df=pd.DataFrame(train)
#    df.to_csv('tmp/train_chaos.csv',index=False,sep=' ',header=None, float_format='%.7e')
#    train=xp.array(pd.read_csv('tmp/train_chaos.csv',delim_whitespace=True,dtype=xpfloat,header=None))
#    test=xp.array(pd.read_csv('tmp/test_chaos.csv',delim_whitespace=True,dtype=xpfloat,header=None))
#
#  import random;random.seed(net['seed'])#for check
#  xp.random.seed(net['seed'])#for check

#  import random;random.seed(net['seed'])#for check
  givendata['n_train']=n_train=train.shape[0]
  givendata['n_test']=n_test=test.shape[0]
  givendata['n_total']=n_total=n_train+n_test
  train_test=xp.concatenate((train,test),axis=0)
  _x,y=xp.split(train_test,[k],axis=1) #Split the array at positions indicated in 1-D array
  xk=(xp.ones(n_total)*net['BIAS']).reshape(-1,1) #BIAS
  x=xp.concatenate((_x,xk),axis=1)
  givendata['x']=x
#  givendata['_x']=x[:,:n_channels]
  givendata['y']=y
#copy x and y to X and Y for Original Scale 
  givendata['X']=copy.deepcopy(x) 
  givendata['Y']=copy.deepcopy(y)
  givendata['e']=xp.zeros((n_total),dtype=xpfloat)
  test=copy.deepcopy(givendata)
#  import pdb;pdb.set_trace() #for debug 
#calc_statistics(givendata); #only this process gives no-effect
  if n_train>0:
    calc_statistics(givendata)
  normalize_data(givendata,net)
#
#  if 1==1: #check
#    df=pd.DataFrame(givendata['Y'][:n_train])
#    df.to_csv('tmp/Y.dat',index=False,sep=' ',header=None)
#    df=pd.DataFrame(givendata['y'][:n_train])
#    df.to_csv('tmp/y.dat',index=False,sep=' ',header=None)
#    import pdb;pdb.set_trace(); #for debug 
####

  net['ywidth'] = net['ymax']-net['ymin']

  if net['r1'] > 0:
    net['R12']=net['r1']/net['r2']
    net['r12']=net['R12']*net['ywidth']/(net['ymax0']-net['ymin0'])
    R3=net['r3']
    r3=R3*(net['ywidth']/net['ymax0']-net['ymin0'])

    net['nr']=int(net['ywidth']/net['r12'])+1
    net['r']=xp.zeros(net['nr']+1,dtype=xpfloat)
    net['R']=xp.zeros(net['nr']+1,dtype=xpfloat)
    if xp.abs(net['r3']<ZERO):
      for i in xrange(net['nr']):
        buff='{:.10e}'.format(i*net['r12']+net['ymin'])
        net['r'][i]=float(buff)
        buff='{:.10e}'.format(i*net['R12']+net['ymin0'])
        net['R'][i]=float(buff)
    else:
      for i in xrange(net['nr']):
        buff='{:.10e}'.format(((i*net['r12']+net['ymin'])/r3+0.5)*r3)
        net['r'][i]=float(buff)
        buff='{:.10e}'.format(((i*net['R12']+net['ymin'])/R3+0.5)*R3)
        net['R'][i]=float(buff)
    for n in xrange(n_total):
      givendata['y'][n]=net['r'][int((givendata['y'][n]-ymin)/net['r12']+0.5)]

#  d='./tmp'
#  if not os.path.exists(d): os.mkdir(d)
  xy=xp.concatenate((givendata['x'][:,:k],givendata['y']),axis=1)
  if switchCupy.is_cupy():xy=xy.get()
  df=pd.DataFrame(xy)
####
#  df=pd.DataFrame(xy)
  df.to_csv("tmp/train+test.csv",index=False,sep=' ',header=None, float_format='%.7e')
  net['print']('######################################################')
  net['print']('#load_data() finish! File:tmp/train+test.csv is saved.')
  net['print']('ytrain+test in [{},{}]'.format(xp.min(givendata['y']),xp.max(givendata['y'])))
  net['print']('n_train+test={}'.format(len(givendata['y'])))
  net['print']('######################################################')
#  import pdb;pdb.set_trace() #for debug 
  if net['DISP']>1 and (k==1 or k==2):
    fp=open('tmp/train+test.plt','w')
    if k==1:
      fp.write('plot "{}" using 1:2, "{}" using 1:2\n'.format(fntrain,fntest))
    if k==2:
      fp.write('splot "{}" using 1:2:3, "{}" using 1:2:3\n'.format(fntrain,fntest))
#    if k==1:
#      fp.write('plot "tmp/train+test.csv" using 1:2:3\n')
#    elif k==2:
#      fp.write('splot "tmp/train+test.csv" using 1:2:3\n')
    fp.write('pause -1 "Hit a key to quit.\n')
    fp.close()
    myshell('xterm -geometry 40x5-0-100 -T traintest -e gnuplot -geometry 300x240 tmp/train+test.plt&')


#xwidthの計算。なぜか画面消えるのでここで計算
  net['xwidth'] = net['xmax'][0] - net['xmin'][0]
  for k in xrange(1,n_channels):
    if (net['xmax'][k] - net['xmin'][k]) > net['xwidth']:
      net['xwidth'] = net['xmax'][k] - net['xmin'][k]		##これでいいのか？？？？？

#  import pdb;pdb.set_trace(); #for debug 
#normalize_data(givendata,net);
# main
  return givendata,test,net #def load_data(givendata,test,net):

def moverange(y1,y1min,y1max,y0min,y0max): #in my_plinn.c
  div1=y1max-y1min
  y0=(y1-(y1min))*((y0max)-(y0min))/div1+(y0min)
  y0=xp.where(y0<y0min,y0min,y0)
  y0=xp.where(y0>y0max,y0max,y0)
#  import pdb;pdb.set_trace() #for debug 
  return y0 #def moverange(y1,y1min,y1max,y0min,y0max): #in my_plinn.c

def calc_statistics(data): #in my_function.c
  k=data['k']
  x=data['x']
  y=data['y']
#  n_total=data['n_total']
  n_train=data['n_train']
#  import pdb;pdb.set_trace() #for debug 
  data['ymin']=xp.min(y[:n_train]) 
  data['ymax']=xp.max(y[:n_train])
  data['MEANtrain']=xp.mean(y[:n_train])
  data['MEANtest']=xp.mean(y[n_train:])
  data['VARtrain']=xp.var(y[:n_train])
  data['VARtest']=xp.var(y[n_train:])
  xmin=xp.zeros(k,dtype=xpfloat)
  xmax=xp.zeros(k,dtype=xpfloat)
  for i in xrange(k):
    xmin[i]=xp.min(x[:n_train,i]) #20190107 xp.min(x[:,i]) 
    xmax[i]=xp.max(x[:n_train,i]) #20190107 xp.max(x[:,i])
  data['xmin']=xmin
  data['xmax']=xmax
  return

def normalize_data(givendata,net): #in my_function.c
#  n_channels=givendata['k']
#  import pdb;pdb.set_trace(); #for debug 
  if 'xmin' in net.keys():
    k=net['k']
  else:
    k=givendata['k']
    net['n_channels']=k
    net['k']=k
    #  data_class=givendata['data_class']
    _y0m=0;_y1m=0;_y0M=0;_y1M=0;_yhh=1.
    _x0m=0;_x1m=0;_x0M=0;_x1M=0;_xhh=1.
  
    _ym0,_yM0,_ym1,_yM1=map(float,net['ytrans'].split(','))
    if _yM0-_ym0<ZERO and _yM1-_ym1<ZERO: #no transform
      _ym0=givendata['ymin']
      _yM0=givendata['ymax']
      net['ymin0']=net['ymin']=_ym0 #not implement slightly smaller not use _y1m y0m
      net['ymax0']=net['ymax']=_yM0 #not inplement slightly bigger
      xmin=xp.zeros(k,dtype=xpfloat)
      xmax=xp.zeros(k,dtype=xpfloat)
      if net['data_class']=='ts': #time_series
        for i in xrange(k):
          xmin[i]=net['ymin0']
          xmax[i]=net['ymax0']
      else:
        for i in xrange(k):
          xmin[i]=givendata['xmin'][i]
          xmax[i]=givendata['xmax'][i]
      net['xmin']=xmin
      net['xmax']=xmax
      net['xmin0']=xmin
      net['xmax0']=xmax
    #    net['xmin0']=copy.deepcopy(xmin)
    #    net['xmax0']=copy.deepcopy(xmax)
    #    import pdb;pdb.set_trace() #for debug 
    else:
      if _yM0-_ym0<ZERO:
        _ym0=givendata['ymin']
        _yM0=givendata['ymax']
        _yD=(_yM0-_ym0)*0.05;
        _yM0 += _yD
        _ym0 -= _yD
        print('#ym0={},yM0={}'.format(_ym0,_yM0))
      net['ymin0']=_ym0 #not implement slightly smaller not use _y1m y0m
      net['ymax0']=_yM0 #not inplement slightly bigger
      if _yM1-_ym1<ZERO:
        _ym1=givendata['ymin']
        _yM1=givendata['ymax']
      net['ymin']=_ym1 #not implement slightly smaller not use _y1m y0m
      net['ymax']=_yM1 #not inplement slightly bigger
      xmin0=xp.zeros(k,dtype=xpfloat)
      xmax0=xp.zeros(k,dtype=xpfloat)
      xmin=xp.zeros(k,dtype=xpfloat)
      xmax=xp.zeros(k,dtype=xpfloat)
#      import pdb;pdb.set_trace() #for debug 
      if net['data_class']=='ts': 
        for i in xrange(k):
          xmin0[i]=_ym0
          xmax0[i]=_yM0
          xmin[i]=_ym1
          xmax[i]=_yM1
    #      import pdb;pdb.set_trace() #for debug 
      else:
        xt=map(float,net['xtrans'].split(',')) #xm0=xt[i*4],xM0=xt[i*4+1],xm1=xt[i*4+2],xM1=xt[i*4+3]
        for i in xrange(k):
          if len(xt)==4:
            _xm0=xt[0]
            _xM0=xt[1]
            _xm1=xt[2]
            _xM1=xt[3]
          else:
            _xm0=xt[i*4]
            _xM0=xt[i*4+1]
            _xm1=xt[i*4+2]
            _xM1=xt[i*4+3]
    
          if _xM0-_xm0<ZERO:
            _xm0=givendata['xmin'][i]
            _xM0=givendata['xmax'][i]
          xmin0[i]=_xm0
          xmax0[i]=_xM0
    #      _xhh=_xM0-_xm0
    #      xmin0[k]=_xm0-_xhh*_x1m-_x0m;
    #      xmax0[k]=_xM0+_xhh*_x1M+_x0M;
          if _xM1-_xm1<ZERO:
            _xm1=givendata['xmin'][i]
            _xM1=givendata['xmax'][i]
          xmin[i]=_xm1
          xmax[i]=_xM1
  
      net['xmin0']=xmin0
      net['xmax0']=xmax0
      net['xmin']=xmin
      net['xmax']=xmax

##### 
  givendata['y']=moverange(givendata['y'],net['ymin0'],net['ymax0'],net['ymin'],net['ymax'])
  for i in xrange(k):
    givendata['x'][:,i]=moverange(givendata['x'][:,i],net['xmin0'][i],net['xmax0'][i],net['xmin'][i],net['xmax'][i])
##  givendata['x']=moverange(givendata['x'],net['xmin0'][i],net['xmax0'][i],net['xmin'][i],net['xmax'][i])
#
#  for n in xrange(givendata['n_total']):
##    givendata['y'][n]=moverange(givendata['y'][n],net['ymin0'],net['ymax0'],net['ymin'],net['ymax'])
#    for i in xrange(k):
#      givendata['x'][n,i]=moverange(givendata['x'][n,i],
#				     net['xmin0'][i],net['xmax0'][i],
#				     net['xmin'][i],net['xmax'][i])
  
#  import pdb;pdb.set_trace(); #for debug 
  return #def normalize_data(givendata,net): #in my_function.c
