#!/bin/python
# -*- coding: utf-8 -*-
#
#http://pythondatascience.plavox.info/scikit-learn/%E3%82%AF%E3%83%A9%E3%82%B9%E3%82%BF%E5%88%86%E6%9E%90-k-means
#
#python kmeans2_kuro.py -fn ~/sotu/2017/can2b/tmp/tspSth.dat -K 2 -L 6
#
import sys
import numpy as np
from sklearn.cluster import KMeans
import argparse
import pandas as pd #sudo pip install pandas
import math
import os
import matplotlib.pyplot as plt
#import matplotlib.cm as cm
import matplotlib
import matplotlib.gridspec as gridspec
from matplotlib.colors import Normalize
import mylib
import itertools

#import os.path
#import os
#script_dir = os.path.abspath(os.path.dirname(__file__))
#os.path.abspath(__file__)


def mypltshow(fnfig,disp=1):
  plt.savefig(fnfig);
  if disp==1:
    mylib.myshell("sleep 1;gv "+fnfig+"&");
  plt.close() #plt.show()

def horizon(y1,y2,Ey):
  T=len(y1)
  for t in range(T):
    if(abs(y1[t]-y2[t])>Ey):
      break;
  return t-1
        
#nth=2
#nth=3

def main():
#
  parser = argparse.ArgumentParser(description='Kmeans')
  parser.add_argument('-fnyp',default='',
                        help='file name of predictions')
  parser.add_argument('-fnyg',default='',
                        help='file name of ground truth')
  parser.add_argument('-K', default=2, type=int,
                      help='number of clusters')

  parser.add_argument('-M', default=2, type=int,
                      help='Member of predictions for horizon')

  parser.add_argument('--Lmax','-L', default=2, type=int,
                      help='Level of clustering for hierarchical')
  parser.add_argument('-Lt', default=1, type=int,
                      help='1 for truncation 0 for no trunc for L')
  parser.add_argument('-Lmin', default=0, type=int,
                      help='Minimum Level of clustering for hierarchical')
  parser.add_argument('-H', default=100, type=int,
                      help='Prediction Horizon')
  parser.add_argument('-hh', default=10, type=int,
                      help='additional horizon to classify')
  parser.add_argument('-Ey', default=10, type=int,
                      help='threshold of ey')
  parser.add_argument('-m', default=1, type=int,
                      help='1 for mean, 0 for leave-one-out')
  parser.add_argument('-d1', default='.', type=str,
                      help='directory d1')
  parser.add_argument('-DISP', default=1, type=int,
                      help='1 for DISP, 0 for noDISP')
  parser.add_argument('-msg',default='',
                      help='message to carry')
  parser.add_argument('-tp0',default=2000, type=int,
                      help='prediction start tyme')

  args = parser.parse_args()
#  import pdb;pdb.set_trace(); #for debug 
#  import os.path
#  fnyp=os.path.expanduser(args.fnyp)
  Sth_id = np.array(pd.read_csv('{}/tspSth_id.dat'.format(args.d1),delim_whitespace=True,dtype=np.int32,header=None)).reshape((-1))
  all_id = np.array(pd.read_csv('{}/tspall_id.dat'.format(args.d1),delim_whitespace=True,dtype=np.int32,header=None))
  tp0=args.tp0
  M=args.M
  if M<2: M=2
  colsplt=["black", "red", "dark-green", "magenta", "green", "light-green", "salmon", "pink",  "grey"]
  colsplt=["black", "red", "dark-green", "blue", "magenta", "green", "light-green", "salmon", "pink",  "grey"]
  colsplt=["red", "dark-green", "green", "blue", "green",  "light-green", "blue", "cyan", "orange" "salmon", "pink", "magenta", "grey"]
  colsplt=["red", "dark-green", "dark-green", "blue", "dark-green", "green", "blue", "cyan", "light-green","orange" "salmon", "pink", "magenta", "grey"]
  colsplt=["dark-green", "dark-green", "blue", "dark-green", "green", "blue", "cyan", "light-green","orange" "salmon", "pink", "magenta", "grey"]
  fnyLc='tmp/yLc'+str(tp0)
  fpyLc=open(fnyLc+'.plt','w')
  fpyLc.write('set style data lines;set nokey\n')

# read dataset
#    import pdb;pdb.set_trace(); #for debug 
#  Y = np.loadtxt(fnyp, delimiter=' ')
#  import pdb;pdb.set_trace(); #for debug 
  fnyp='{}/{}'.format(args.d1,args.fnyp)
  if not os.path.isfile(fnyp):
    print '#fnyp=%s does not exist' % (fnyp)
    return
  Y = np.array(pd.read_csv(fnyp,delim_whitespace=True,dtype=np.float32,header=None))
  Y = Y.T # transpose
  N,T=Y.shape #N:number of time series, T:horizon
  Ey=args.Ey       #threshold for predictable horizon
  h_all=[]
##
  fnyg='{}/{}'.format(args.d1,args.fnyg)
  if not os.path.isfile(fnyg):
    print '#fnyg=%s does not exist' % (fnyg)
    return
  yg = np.array(pd.read_csv(fnyg,delim_whitespace=True,dtype=np.float32,header=None))
  #plt.plot(x, yg,color=cols[0]) #ground truth
  ##best yp for ygt
  hb=0
  ib=0
  hg=np.zeros((N)).astype('int32')
  for i in range(N):
    hg[i]=horizon(Y[i],yg,Ey)
  hgmax=hg.max()
  I=np.where(hg==hgmax)[0]
  print('#Maximum h(y{},yg)={}'.format(I,hgmax))

  H2=np.zeros((N,N)).astype('int32')
  for i1 in range(N):
    for i2 in range(N):
      if i2 != i1:
        H2[i1,i2]=horizon(Y[i1],Y[i2],Ey)
  IN=range(N) #all
  Hmax={}
  I_Hmax={}

  for m in range(2,M+1):
    Im=list(itertools.combinations(IN, m))
    ImA=np.array(Im)
    n_Im=len(Im)
    HIm=np.zeros((n_Im)).astype('float32')
    ymean=np.zeros((n_Im,T)).astype('float32')
    for i,I in enumerate(Im):
      for n in range(1,len(I)):
        ymean[i] += Y[I[n],:]
      ymean[i]=ymean[i]/(len(I)-1)
      HIm[i]=horizon(Y[I[0]],ymean[i],Ey)
    Hmax[m]=HIm.max()
    I_Hmax[m]=np.where(HIm==Hmax[m])[0]
#    import pdb;pdb.set_trace(); #for debug 
#    print msg
    for i in I_Hmax[m]:
      msg='#Maximum {}-member ho={} for'.format(m,Hmax[m])
      msg='{} hg{}:'.format(msg,ImA[i])
#      import pdb;pdb.set_trace(); #for debug 
      for j in ImA[i]:
        msg='{} {}'.format(msg,hg[j])
#      import pdb;pdb.set_trace(); #for debug 
      print msg

####################
  for m in range(2,M+1):
    Im=list(itertools.combinations(IN, m))
    ImA=np.array(Im)
    HI2m=[]
    for I in Im:
      I2=list(itertools.combinations(I, 2))
      HI2=np.array([H2[i] for i in I2])
      HI2m.append(HI2.min())
    HI2mA=np.array(HI2m)
    Hmax[m]=HI2mA.max()
    I_Hmax[m]=np.where(HI2mA==Hmax[m])[0]
#    import pdb;pdb.set_trace(); #for debug 
    msg='#### H2_max[{}]={} for'.format(m,Hmax[m])
    print msg
    for i in I_Hmax[m]:
      msg='hg{}:'.format(ImA[i])
#      import pdb;pdb.set_trace(); #for debug 
      for j in ImA[i]:
        msg='{} {}'.format(msg,hg[j])
#      import pdb;pdb.set_trace(); #for debug 
      print msg
#    import pdb;pdb.set_trace(); #for debug 
#    print('Hgo_max[{}]={} for i={}'.format(m,Hmax[m],ImA[I_Hmax[m]]))
#
##  import pdb;pdb.set_trace(); #for debug 
#  H2=np.zeros((N,N)).astype('int32')
#  H2max=np.zeros((N)).astype('int32')
#  H2maxmin=np.zeros((N)).astype('int32')
#  I_H2max={}
#  n_H2max=np.zeros((N)).astype('int32')
#  for i1 in range(N):
#    for i2 in range(N):
#      if i2 != i1:
#        H2[i1,i2]=horizon(Y[i1],Y[i2],Ey)
##  for i1 in range(N):
##    for i2 in range(N):
##      if i2 < i1:
##        H2[i2,i1]=H2[i1,i2]
#  for i1 in range(N):
#    H2max[i1]=H2[i1,:].max()
#    I_H2max[i1]=np.where(H2[i1,:]==H2max[i1])[0]
#    n_H2max[i1]=len(I_H2max[i1])
#
#  H3=np.zeros((N,N)).astype('int32')
#  H3max=np.zeros((N)).astype('int32')
#  I_H3max={}
#  n_H3max=np.zeros((N)).astype('int32')
#  for i1 in range(N):
#    H3i1=[]
#    I_H3i1=[]
#    for i2 in range(N):
#      if i2==i1:continue
#      for i3 in range(N):
#        if i3==i1 or i3 ==i2: continue
#        H3i1.append(min(H2[i1,i2],H2[i2,i3],H2[i3,i1]))
#        I_H3i1.append([i1,i2,i3])
##      import pdb;pdb.set_trace(); #for debug 
#    import pdb;pdb.set_trace(); #for debug 
#    H3i1A=np.array(H3i1)
#    np.where(H3i1A==max(H3i1A))[0]
#    H3max[i1]=max(H3i1)
#######################
#  for i1 in range(N):
#    hmin=T
#    if n_H2max[i1]>=2:
#      for i3 in I_H2max[i1]:
#        for i4 in I_H2max[i1]:
#          if i4 != i3:
#            if H2[i3,i4]<hmin:
#              hmin=H2[i3,i4]
#    if hmin!=T:
#      H2maxmin[i1]=hmin
#    else:
#      H2maxmin[i1]=H2max[i1]
#
#  H3=np.zeros((N,N)).astype('int32')
#  H3max=np.zeros((N)).astype('int32')
#  I_H3max={}
#  n_H3max=np.zeros((N)).astype('int32')
#  for i1 in range(N):
#    for i2 in range(N):
#      hmin=T
#      if i2 not in I_H2max[i1]:
#        H3[i1,i2]=H2[i1,i2]
#    H3max[i1]=H3[i1,:].max()
#    I_H3max[i1]=np.where(H3[i1,:]==H3max[i1])[0]
#    n_H3max[i1]=len(I_H3max[i1])
#  import pdb;pdb.set_trace(); #for debug 
#    
##
##
##  for m in range(2,M+1):
##    hm={}
##    for i1 in range(N):
##      hmi1=np.zeros(N).astype('float64')
##      for i2 in range(N):
##        if i2 != i1:
##          hmi1[i2]=horizon(Y[i1],Y[i2],Ey)
##      hmi1max=hmi1.max()
##      Imax=np.where(hmi1==hmi1max)[0]
##      hm[i1]=hmi1
##      import pdb;pdb.set_trace(); #for debug 
#

if __name__ == "__main__":
  argv=sys.argv
  cmd=''
  for a in argv:#  for i,a in enumerate(argv):
    cmd+=a+' '
  print('#start:python {}'.format(cmd))

  main()
#
  
