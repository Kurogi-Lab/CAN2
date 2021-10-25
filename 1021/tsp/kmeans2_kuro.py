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

#import os.path
#import os
#script_dir = os.path.abspath(os.path.dirname(__file__))
#os.path.abspath(__file__)


def mypltshow(fnfig,disp='1'):
  plt.savefig(fnfig);
  if disp=='1':
    mylib.myshell("sleep 1;gv "+fnfig+"&");
  plt.close() #plt.show()

def horizon(y1,y2,Ey):
  T=len(y1)
  for t in range(T):
    if(abs(y1[t]-y2[t])>Ey):
      break;
  return t-1
        
nth=2
nth=3

def main():
#
  parser = argparse.ArgumentParser(description='Kmeans')
  parser.add_argument('-fnyp',default='',
                        help='file name of predictions')
  parser.add_argument('-fnyg',default='',
                        help='file name of ground truth')
  parser.add_argument('-K', default=2, type=int,
                      help='number of clusters')
  parser.add_argument('--Lmax','-L', default=1, type=int,
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
  parser.add_argument('-DISP', default='1', type=str,
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

  colsplt=["black", "red", "dark-green", "magenta", "green", "light-green", "salmon", "pink",  "grey"]
  colsplt=["black", "red", "dark-green", "blue", "magenta", "green", "light-green", "salmon", "pink",  "grey"]
  colsplt=["red", "dark-green", "green", "blue", "green",  "light-green", "blue", "cyan", "orange" "salmon", "pink", "magenta", "grey"]
  colsplt=["red", "dark-green", "dark-green", "blue", "dark-green", "green", "blue", "cyan", "light-green","orange" "salmon", "pink", "magenta", "grey"]
  colsplt=["dark-green", "dark-green", "blue", "dark-green", "green", "blue", "cyan", "light-green","orange" "salmon", "pink", "magenta", "grey"]
  fnyLc='tmp/yLc'+str(tp0)
  fpyLc=open(fnyLc+'.plt','w')
  fpyLc.write('set style data lines;set nokey\n')

  K=int(args.K)
  Lmax=int(args.Lmax)+1
  Lmin=int(args.Lmin)
# read dataset
#    import pdb;pdb.set_trace(); #for debug 
#  Y = np.loadtxt(fnyp, delimiter=' ')
#  import pdb;pdb.set_trace(); #for debug 
  fnyp='{}/{}'.format(args.d1,args.fnyp)
  if not os.path.isfile(fnyp):
#  if len(fnyp) == 0:
    print '#fnyp=%s does not exist' % (fnyp)
    return
  Y = np.array(pd.read_csv(fnyp,delim_whitespace=True,dtype=np.float32,header=None))
  Y = Y.T # transpose
  N,T=Y.shape #N:number of time series, T:horizon
  Ey=args.Ey       #threshold for predictable horizon
  h_all=[]
#  H=np.zeros((L+1,2**L)).astype('float32')
#      fnyg=os.path.expanduser(args.fnyg)

  fnyg='{}/{}'.format(args.d1,args.fnyg)
#      import pdb;pdb.set_trace(); #for debug 
  if os.path.isfile(fnyg):
    print '#predictable horizons'
    yg = np.array(pd.read_csv(fnyg,delim_whitespace=True,dtype=np.float32,header=None))
#    plt.plot(x, yg,color=cols[0]) #ground truth
    ##best yp for ygt
    hb=0
    ib=0
    for i in range(N):
      h=horizon(Y[i],yg,Ey)
      h_all.append(h)
      if h>hb:
        hb=h
        ib=i
    h_all_A=np.array(h_all)
    print 'max h(y%d,yg)=%d' % (ib,hb)
    Hgmax_A=hb

  DISP=args.DISP

  fig=plt.figure(figsize=(6,8))
#  fig2=plt.figure(figsize=(8,6))
  gs=gridspec.GridSpec(4,2)
  plt.subplots_adjust(wspace=0.5, hspace=1.0)
#  plt.subplots_adjust(wspace=0.5, hspace=0.5)
  C=np.zeros((N,Lmax+1)).astype('uint8')
  envN='export N=N:'
  Nenv=[]
  if Lmax == -1:
    y=np.zeros((1,H)).astype('float32') #dummy
    for n in range(N):
      y=np.concatenate((y,Y[n,:H].reshape(1,H)),axis=0)
    y=np.delete(y,0,axis=0)  #delete dummy
    km = KMeans(n_clusters=K, init='k-means++', n_init=10, max_iter=300,tol=0.0001,precompute_distances='auto', verbose=0,random_state=None, copy_x=True, n_jobs=1)
    pred = km.fit_predict(y)

  else:#hierarchical clustering
    LONGhg=0
#    import pdb;pdb.set_trace(); #for debug 
    Lctodeg=dict()
    Lctodegcuml=dict()
    Lctohg=dict()
    L2ctoLig=dict()
    HgHoL={}
    ncmaxL={}
    Entropy={}
    HgEntropy={}
    for L in range(Lmin,Lmax): #L156
      ctoh0=dict()
      ctonY=dict()
      ctoLi=dict()
      ctoLic0=dict()
      ctoLic1=dict()
      ctoLig=dict()
      if LONGhg == 1 and args.Lt == 1:
        break
      l=L
      for c in range(K**l): #clas=0 or 1 
        ncmaxL[L]=0
        Entropy[L]=0
        HgEntropy[L]=0
        strc=str(c) 
#        strc=str(L)+'-'+str(c)
#        ctoc[strc]=c
        y=np.zeros((1,T)).astype('float32') #dummy
        Li=[]
        for i in range(N):
          if C[i,l] == c:
            y=np.concatenate((y,Y[i,:].reshape(1,T)),axis=0)
            Li.append(i)
        y=np.delete(y,0,axis=0)  #delete dummy
#        import pdb;pdb.set_trace(); #for debug 
        nY,T1=y.shape #T1=T
        if nY > nth: # for execute k-means cluster >=2:??
          h0=T
    #          usemean=0
          if args.m == 1: #use mean
            ym = np.mean(y, axis=0)
            for n in range(nY):
              h=horizon(y[n],ym,Ey)
              if h0 > h:
                h0=h
          else:#leave-one-out
            for n1 in range(nY):
              for n2 in range(nY):
                if n1 != n2:
                  h=horizon(y[n1],y[n2],Ey)
                  if h0 > h:
                    h0=h
          ctoh0[strc]=h0
          ctonY[strc]=nY
          #        H[l,c]=h
          print 'l c nY h=%3d %3d %3d %3d' % (l,c,nY,h0)
          #          y=y[:,:h]
          #          y=y[:,:h+10] ##?
           ######################## K-means bellow
          y=y[:,:h0+args.hh] ##?
          if nY >= nth:
            km = KMeans(n_clusters=K, init='k-means++', n_init=10, max_iter=300,tol=0.0001,precompute_distances='auto', verbose=0,random_state=None, copy_x=True, n_jobs=1)
            pred = km.fit_predict(y)

          else:
            pred = [0 for i in range(len(y))] #set all y in class 0
          ip=0
#          Li=[] #List of i
          Lic0=[] #List of i
          Lic1=[] #List of i
          for i in range(N):
            if C[i,l] == c:
              C[i,l+1] = C[i,l]*K + pred[ip]
#              Li.append(i)
              if pred[ip] ==0:
                Lic0.append(i)
              else:
                Lic1.append(i)
              ip += 1
          #            if L == 3 and c == 0:
          #              import pdb;pdb.set_trace(); #for debug 
          ctoLi[strc]=Li #list of n
          ctoLic0[strc]=Lic0 #list of n
          ctoLic1[strc]=Lic1 #list of n
      ######################## K-means above
        else: #  if nY > nth: # for execute k-means cluster >=2:?? L180
#          print '#####################nY=%d<2,c=%d,L=%d' % (nY,c,L)
          ctoLic0[strc]=Li #list of n
          ctoLic1[strc]=[] #list of n
          ctoh0[strc]=0
          ctonY[strc]=nY
          for n in range(N):
            if C[n,l] == c:
              C[n,l+1] = C[n,l]*K
              ctoLi[strc]=[n]
      #end for c in range(K**l): #clas=0 or 1 L167
      if L >=0:
        for n in range(N):
          print 'n%2d' % (n),
          for l in range(0,L+2):
            print'%d ' % (C[n,l]),
#            print'L%d C%3d ' % (l,C[n,l]),
          print ''

      for i,strc in enumerate(ctoh0):
        c=int(strc) #???????
  #    import pdb;pdb.set_trace(); #for debug 
  #    for c in cton.keys(): 
  #    for i in range(len(ctoLi)):
  #      c=str(i)
        if strc in ctoLi.keys():
          print 'c=%d nY=%d h=%d iY' % (c,ctonY[strc],ctoh0[strc]),ctoLi[strc]
      print '####'
    #  import pdb;pdb.set_trace(); #for debug 
    #  cols=matplotlib.colors.cnames.keys()
#      cols = ["r", "g", "b", "c", "m", "y", "k","pink"]
      cols = ["g", "b", "c", "m", "y", "k","pink"]
      cols.append(matplotlib.colors.cnames.keys())
      x = np.arange(0, T, 1)
  #    for i in range(len(ctoLi)):
  #      c=str(i)
      NsL=[]
      for ic,c in enumerate(ctoLi):
        for n in ctoLi[c]:  
          if ctonY[c] > 1:
            y = Y[n,:]
            plt.plot(x, y,color=cols[i % 7])
#        plt.pause(0.05)
#        import pdb;pdb.set_trace(); #for debug 
        print 'L%d c%s n=%d h0=%d' % (L,c,ctonY[c],ctoh0[c]),
        if L==0:
          print ''  
        else:
          print(' iY={}'.format(ctoLi[c]))
          df=pd.DataFrame(Nsh)
          df.to_csv('{}/Nsh-L{}c{}.csv'.format(args.d1,L,c),index=False,sep=' ',header=None)
          nNs=Ns.shape[0]
          Nss='N:{}'.format(Ns[0,0])
          for iN in range(1,nNs):
            Nss=Nss+',{}'.format(Ns[iN,0])
          NsL.append([Nss,nNs,c])
        #
        if DISP[0]=='1': plt.show()
      #end for ic,c in enumerate(ctoLi): L268
      if L==Lmax-1: #L288
        cols = ["g", "b", "c", "m", "y", "k","pink"]
        plt.clf()
  #     nc1=len(ctoLi)+1
        ygdisp=0
        nc1=len(ctoLi)+Lmax-2
        xax = np.arange(0, Y.shape[1], 1)
        if ygdisp==1:
          nc1=len(ctoLi)+Lmax-1
          fig.add_subplot(nc1,1,1)
          plt.plot(xax, yg,linewidth=5,color="r")#        plt.plot(xax, yg)
          plt.title('yg')
        for ic,c in enumerate(ctoLi):
          y_=Y[ctoLi[c],:]
#          print '#check nc1,1,int(c)+2={},{},{}'.format(nc1,1,int(c)+2)
#          import pdb;pdb.set_trace(); #for debug 
          fig.add_subplot(nc1,1,int(c)+1) #ygdisp=-
#          fig.add_subplot(nc1,1,int(c)+2) #ygdisp=1
          plt.plot(xax, y_.T,linewidth=1)
#          plt.plot(xax, y_.T,linewidth=1,color=cols[ctoLi[c][0]%6])
          plt.plot(xax, yg,linewidth=2,linestyle='solid',color='r')
#          plt.plot(xax, yg,linewidth=2,linestyle='dashdot',color='r')
          plt.title('yp in L{}c{} n{}'.format(L,c,y_.shape[0]))

#        plt.pause(0.05) #plt.show() #
        fnfig='{}/y_L{}.eps'.format(args.d1,L)
        mypltshow(fnfig,DISP[0])
        plt.close()
        fig=plt.figure(figsize=(4,4))
        nc1=len(ctoLi)+1
        plt.clf()
#        plt.xlim(0,500);plt.ylim(0,500)
#        fig.add_subplot(nc1,1,1)
        plt.scatter(h_all_A,LOOH_all_A0,s=20, c="w", alpha=1.0, linewidths="2",edgecolors="k");
        plt.grid(which='major',color='black',linestyle='--');
        n=len(h_all_A)
        plt.title('ho vs. hg @L{}c{} n{}'.format(0,0,n))
        fnfig='{}/hh_L{}.eps'.format(args.d1,0)
        mypltshow(fnfig,0)

        for ic,c in enumerate(ctoLi):
          plt.clf()
 #         plt.xlim(0,500); plt.ylim(0,500)
 #         fig.add_subplot(nc1,1,int(c)+1)
          plt.scatter(h_all_A[ctoLi[c]],LOOH_all_A[ctoLi[c]],s=20, c="w", alpha=1.0, linewidths="2",edgecolors="k");
          plt.grid(which='major',color='black',linestyle='--');
          n=len(ctoLi[c])
          plt.title('ho vs. hg@L{}c{} n{}'.format(L,c,n))
          fnfig='{}/hh_L{}.eps'.format(args.d1,L)
          mypltshow(fnfig,0)
#        import pdb;pdb.set_trace(); #for debug 
##        hh=np.concatenate([h_all_A.reshape(-1,1),LOOH_all_A.reshape(-1,1)],axis=1)
        for hD in ['hg','ho']:#
          plt.clf()
          nc1=len(ctoLi)+2
          for ic,c in enumerate(ctoLi):
            print('#chech nc1,c={},{}'.format(nc1,c))
            fig.add_subplot(nc1,1,int(c)+1)
            if hD=='hg':
              ha=h_all_A[ctoLi[c]]
            else:
            #              import pdb;pdb.set_trace(); #for debug 
              ha=LOOH_all_A[ctoLi[c]]
            plt.xlim(0,500)
            #          plt.ylim(0,40)
            #          plt.hist(ha, bins=20, histtype='barstacked', ec='black')
            binmin=0;binmax=400;binwidth=10
#            import pdb;pdb.set_trace(); #for debug 
            if len(ha)>1:
              plt.hist(ha,bins=np.arange(binmin, binmax + binwidth, binwidth), histtype='barstacked', ec='black')
              plt.title('{}@L{}c{} n{}'.format(hD,L,c,len(ha)))
          fnfig='{}/{}_L{}.eps'.format(args.d1,hD,L)
          mypltshow(fnfig,0)
        ##################
        #        import pdb;pdb.set_trace(); #for debug 
        #          import pdb;pdb.set_trace(); #for debug 
        #      if L>0:
        #        import pdb;pdb.set_trace(); #for debug 
        fp=open('{}/Ns-L{}.env'.format(args.d1,L),'w')
        fp.write('export N_S="{}'.format(NsL[0][0]))
        for ic in range(1,len(NsL)):
          fp.write(' {}'.format(NsL[ic][0]))
        fp.write('"\nexport n_seed_S="{}'.format(int(100./NsL[0][1]+0.5)))
        for ic in range(1,len(NsL)):
          fp.write(' {}'.format(int(100./NsL[ic][1]+0.5)))
        fp.write('"\n')
        fp.write('export nc_S="{},{}'.format(NsL[0][1],NsL[0][2]))
        for ic in range(1,len(NsL)):
          fp.write(' {},{}'.format(NsL[ic][1],NsL[ic][2]))
        fp.write('" #number of N and c for check\n')
        fp.write('export d1={}'.format(args.d1))
        fp.close()
      #        print 'L%d c%s n=%d hc=%d' % (L,c,ctonY[c],ctoh0[c]),' cn=',ctoLi[c]
      #end if L==Lmax-1: #L288

      print '###mean'
      ymean=np.zeros((K**L,T)).astype('float32') #dummy
      #    for i in range(len(ctoLi)):
      #      c=str(i)
      for i,c in enumerate(ctoLi):
        for n in ctoLi[c]:  
          ymean[i] += Y[n,:]
        ymean[i] = ymean[i]/len(ctoLi[c])
      ###
      f=open('ymean.dat','w')
      for t in range(T):
        f.write('%g' % ymean[0,t])
        for i in range(1,len(ctoLi)):
          f.write(' %g' % ymean[i,t])
        f.write('\n')
      f.close()
      print 'ymean.dat is saved'
  
      if L >=1:# normalize cumulative deg
        degcumlsum=0
        for c in range(K**L): #
          _c=c*K
          degcuml = 1.;
          keycuml=str(L-1)+'-'+str(c)
          for l in range(1):
#          for l in range(L):
            _c=_c/K
            key=str(L-l-1)+'-'+str(_c)
            if key in Lctodeg:
              degcuml *= Lctodeg[key]
          Lctodegcuml[keycuml]=degcuml
          degcumlsum += degcuml
        print 'degcuml:L%d-' % (L-1),
        for c in range(K**L): #
          keycuml=str(L-1)+'-'+str(c)
#          import pdb;pdb.set_trace(); #for debug 
          Lctodegcuml[keycuml] /=degcumlsum
          print '(%d)%.3f' % (c,Lctodegcuml[keycuml]),
#          print '%s:%.2f' % (keycuml,Lctodegcuml[keycuml]),
        print ''

#      if os.path.isfile(fnyg):#same as L113???
#        print '#predictable horizons'
#        yg = np.array(pd.read_csv(fnyg,delim_whitespace=True,dtype=np.float32,header=None))
      if 1==1:
        h_all_A=np.array(h_all)
        LOOH_all_A=np.zeros(len(h_all_A)).astype('float32') 
        print('max h(yi,yg)={} for i={}'.format(h_all_A.max(),np.where(h_all_A == h_all_A.max())))
        print 'deg:', Lctodeg
        #        import pdb;pdb.set_trace(); #for debug 
        #        plt.plot(x, Y[ib],color=cols[1])
        ##mean
        #      for i in range(len(ctoLi)):
        #        c=str(i)
        #        import pdb;pdb.set_trace(); #for debug 
        for i,strc in enumerate(ctoLi):
          c=int(strc) #?????
          key0=str(L)+'-'+str(c*K)
          key1=str(L)+'-'+str(c*K+1)
          key=str(L-1)+'-'+strc
          h=horizon(ymean[i],yg,Ey) 
          Lctohg[key]=h
          print 'L%d c%s N%d h(Yi,ymean)=%d h(ymean,yg)=%d' % (L,strc,ctonY[strc],ctoh0[strc],h),
          if ctonY[strc] >=nth: #tag1
            icol=(i+2) % 6
#            if L==3 and strc=='5':
#              import pdb;pdb.set_trace(); #for debug 
            plt.plot(x, ymean[i],color=cols[icol])
  #best yp via LOOCV horizon
            nLOOH=len(ctoLi[strc])
            LOOH=np.zeros(nLOOH).astype('float32') #
            for j,n in enumerate(ctoLi[strc]):
              for m in ctoLi[strc]:
                if n != m:
                  H= horizon(Y[n],Y[m],Ey)
                  LOOH[j] += H
              if nLOOH>1:#20210520
                LOOH[j] /= (nLOOH-1) #######sum of horizon
              LOOH_all_A[n]=LOOH[j]
            LOOHmax=LOOH.max() #LOOCVH
#            if L==3: 
#              import pdb;pdb.set_trace(); #for debug 
            nLOOHc0=len(ctoLic0[strc])
            nLOOHc1=len(ctoLic1[strc])
#            print 'nLOOHc0,c1=%d %d' % (nLOOHc0, nLOOHc1)

            if nLOOHc0 >=nth and nLOOHc1 >=nth:  #best yp via LOOCV horizon for c0
              LOOHc0=np.zeros(nLOOHc0).astype('float32') #
              for j,n in enumerate(ctoLic0[strc]):
                for m in ctoLic0[strc]:
                  if n != m:
                    H= horizon(Y[n],Y[m],Ey)
                    LOOHc0[j] += H
                LOOHc0[j] /= (nLOOHc0-1) #######sum of horizon
#              print 'LOOHc0(len=%d)' % nLOOHc0, LOOHc0
              LOOHc0max=LOOHc0.max() #LOOCVHc0
    #best yp via LOOCV horizon for c1
              LOOHc1=np.zeros(nLOOHc1).astype('float32') #
              for j,n in enumerate(ctoLic1[strc]):
                for m in ctoLic1[strc]:
                  if n != m:
                    H= horizon(Y[n],Y[m],Ey)
                    LOOHc1[j] += H
                LOOHc1[j] /= (nLOOHc1-1) #######sum of horizon
#              print 'LOOHc1(len=%d)' % nLOOHc1, LOOHc1
              LOOHc1max=LOOHc1.max() #LOOCVHc0
    ####
              deg0=float(nLOOHc0)*(LOOHc0max-ctoh0[strc])
              deg1=float(nLOOHc1)*(LOOHc1max-ctoh0[strc])
#              if (deg0+deg1)==0 == 0:
#              print 'nLOOHc0,c1=%d %d' % (nLOOHc0, nLOOHc1)
#              print 'deg0=%g = %d*(%g-%g)' % (deg0,nLOOHc0,LOOHc0max,ctoh0[strc])
#              print 'deg1=%g = %d*(%g-%g)' % (deg1,nLOOHc1,LOOHc1max,ctoh0[strc])
              Lctodeg[key0]=deg0/(deg0+deg1)
#              import pdb;pdb.set_trace(); #for debug 
              Lctodeg[key1]=deg1/(deg0+deg1)
            else: #if nLOOHc0 >=3 and nLOOHc1 >=2:
              if nLOOHc0 >= nth:
                Lctodeg[key0]=1 #0.5 #1
              else:
                Lctodeg[key0]=0 
              if nLOOHc1 >= nth:
                Lctodeg[key1]=1 #0.5 #1
              else:
                Lctodeg[key1]=0 
####
            Lhg=[]
            for j in range(len(LOOH)):
              if LOOH[j] == LOOHmax: #search all maximum
                n=ctoLi[strc][j]
                h=horizon(Y[n],yg,Ey)
                print 'h(y%d,LOO)=%.1f h(y%d,yg)=%.1f' % (n,LOOH.max(),n,h), #n??
                ctoLig[strc]=[n] #last ig
                Lhg.append(h) ###???use max?
                if h>=100.0:
                  LONGhg=1
                  print '***',
            if len(Lhg)>0:
              Lctohg[key]=max(Lhg)
            else:
              Lctohg[key]=0
            ####disp degs
            if L>=1:
              keycuml=str(L-1)+'-'+str(c)
              print 'degs:%3f:' % (Lctodegcuml[keycuml]),
              _c=c*K
#              for l in range(1):
              for l in range(L):
                _c=_c/K
                keyl=str(L-l-1)+'-'+str(_c)
                if keyl in Lctodeg:
                  print '%s:%.2f' % (keyl,Lctodeg[keyl]),
                else:
                  print '%s:?' % (keyl),

#            print 'degs=', Lctodeg,
  #          print 'LOOCVh(yi%d)=%.1f h(yi%d,yg)=%.1f' % (LOOH.argmax(),LOOH.max(),n,horizon(Y[n],yg,Ey)),
#            plt.plot(x, Y[n],color="black")
  #          print ' LOOCVh=%g nLOOH=%d ' % (LOOH,nLOOH),
          else: # if ctonY[strc] >=3:  tag1
            print ' h(,yg)=%.1f' % (horizon(Y[ctoLi[strc][0]],yg,Ey)),
  #          LOOH=0;nLOOH=0
  #          print ' LOOCVh=%g nLOOH=%d' % (LOOH,nLOOH),
          if L==0:
            print ''
          else:
            print 'iY',ctoLi[strc]

          c=strc
          Ns=all_id[Sth_id[ctoLi[c]]]
          h_Lc=h_all_A[ctoLi[c]]
          Nsh=np.concatenate([Ns,h_Lc.reshape((-1,1))],axis=1)
          iNsh=np.concatenate([np.array(ctoLi[c]).reshape(-1,1),Nsh],axis=1)
          if len(h_Lc)==1:
            LOOH=np.ones(1)*(-1) #
          iNshh=np.concatenate([iNsh,LOOH.reshape(-1,1)],axis=1)
          print('i N s h(yi,yg) h-LOOCV(yi) h0={}'.format(h0))
          LOOHmax=np.max(LOOH)
          hgmax=np.max(h_Lc)
          mes=''
          mesi=''
          mesg=''
          for i in range(len(iNshh)):
            mes='{} {:3.0f} {:3.0f} {:2.0f}'.format(mes,iNshh[i,0],iNshh[i,1],iNshh[i,2])
            if iNshh[i,3]==hgmax:
              mes='{} {:3.0f}* '.format(mes,iNshh[i,3])
              mesg='{}({:.0f},{:.0f},{:.0f},{:.0f}*,{:.0f})'.format(mesg,iNshh[i,0],iNshh[i,1],iNshh[i,2],iNshh[i,3],iNshh[i,4])
            else:
              mes='{} {:3.0f}'.format(mes,iNshh[i,3]) 
            if iNshh[i,4]==LOOHmax:
              mes='{} {:3.1f}* '.format(mes,iNshh[i,4]) 
              mesi='{}({:.0f},{:.0f},{:.0f},{:.0f},{:.0f}*)'.format(mesi,iNshh[i,0],iNshh[i,1],iNshh[i,2],iNshh[i,3],iNshh[i,4])
              HgHoc=iNshh[i,3] #only last one
              if len(iNshh) > 1 and L==Lmax-1: 
#                import pdb;pdb.set_trace(); #for debug 
                envN='{}{:.0f},'.format(envN,iNshh[i,1])
                Nenv.append(iNshh[i,1])
            else:
              mes='{} {:3.1f}  '.format(mes,iNshh[i,4]) 
            mes+='\n'
          #          import pdb;pdb.set_trace(); #for debug 
          ##entropy
          EntropyLc=0
#          if L==4:
#            import pdb;pdb.set_trace(); #for debug 
          Pi=iNshh[:,4]
          if len(Pi)>1:
#            Pi/=np.mean(Pi)
#            import pdb;pdb.set_trace(); #for debug 
            Pi/=np.sum(Pi)
            EntropyLc=0
            for i in range(len(Pi)):
              EntropyLc-= Pi[i]*math.log(Pi[i])
            EntropyLc/=math.log(len(Pi))
#          import pdb;pdb.set_trace(); #for debug 
          print(mes)
          ha=LOOH;print('hi-LOOCV@L{}c{} with n{} min{:.1f} max{:.1f} mean{:.1f} median{:.1f} std{:.1f} best-iNshh{} {} Entropy={:.3f}'.format(L,c,len(ha),np.min(ha),np.max(ha),np.mean(ha),np.median(ha),np.std(ha),mesi,args.msg,EntropyLc))
          nc=len(ha)
          if nc>ncmaxL[L]:
            ncmaxL[L]=nc
            HgHoL[L]=HgHoc
          if EntropyLc>Entropy[L]:
            Entropy[L]=EntropyLc
            HgEntropy[L]=HgHoc
          if L==0: LOOH_all_A0=LOOH_all_A
          #hist,bin_edges=np.histogram(hp,bins=10)
#          plt.clf()
#          plt.xlim(50,500)
#          plt.ylim(0,50)
#          plt.hist(ha, bins=20, histtype='barstacked', ec='black')
#          plt.title('ho@L{}c{}'.format(L,c))
#          fnfig='{}/ho_L{}c{}.eps'.format(args.d1,L,c)
#          plt.savefig(fnfig)
#          mylib.myshell('gv {}&'.format(fnfig))
          ha=h_Lc;print('h(yi,yg)@L{}c{} with n{} min{:.1f} max{:.1f} mean{:.1f} median{:.1f} std{:.1f} best-iNshh{} {}'.format(L,c,len(ha),np.min(ha),np.max(ha),np.mean(ha),np.median(ha),np.std(ha),mesg,args.msg))
#          plt.clf()
#          plt.xlim(50,500)
#          plt.ylim(0,50)
#          plt.hist(ha, bins=20, histtype='barstacked', ec='black')
#          plt.title('hg@L{}c{}'.format(L,c))
#          fnfig='{}/hg_L{}c{}.eps'.format(args.d1,L,c)
#          plt.savefig(fnfig)
#          mylib.myshell('gv {}&'.format(fnfig))
#          import pdb;pdb.set_trace(); #for debug 
#          print('h(yi,yg) with  min{} max{} mean{:.3g} median{:.3g} std{:.3g}'.format(np.min(ha),np.max(ha),np.mean(ha),np.median(ha),np.std(ha)))
#print 'np.min(ha),np.max(ha),np.mean(ha),np.median(ha),np.std(ha),np.predictable(ha)',np.min(ha),np.max(ha),np.mean(ha),np.median(ha),np.std(ha),np.predictable(ha)
#np.sum	np.nansum	Compute sum of elements
#np.prod	np.nanprod	Compute product of elements
#np.mean	np.nanmean	Compute mean of elements
#np.std	np.nanstd	Compute standard deviation
#np.var	np.nanvar	Compute variance
#np.min	np.nanmin	Find minimum value
#np.max	np.nanmax	Find maximum value
#np.argmin	np.nanargmin	Find index of minimum value
#np.argmax	np.nanargmax	Find index of maximum value
#np.median	np.nanmedian	Compute median of elements
#np.percentile	np.nanpercentile	Compute rank-based statistics of elements
#np.any	N/A	Evaluate whether any elements are true
#np.all	N/A	Evaluate whether all elements are true
        if DISP[0]=='1': 
          plt.show()
      ###
      #end of if os.path.isfile(fnyg):#same as L113???
      L2ctoLig[str(L)]=ctoLig
###
#      for i,strc in enumerate(ctoLig):
#        c=int(strc) #
#        if strc in ctoLig.keys():
#          Li=ctoLig[strc]
#          i1=Li[0]+1
#          col=colsplt[(2**L+c+1)%9]
#          col=colsplt[(L)%9+1]
#          lw=(Lmax-L)*2
#          lw=2
#          lt=2*L+1
#          if L==0:
#            fpyLc.write(', \"'+fnyp+'\" using ($0+%d):%d lt %d lw %d lc rgb \"%s\"%s' % (tp0,i1,lt,lw,col,'\\\n'))
#          else:
#            fpyLc.write(', \"\" using ($0+%d):%d lt %d lw %d  lc rgb \"%s\"%s' % (tp0,i1,lt,lw,col,'\\\n'))
####

    #end of for L in range(Lmin,Lmax):L156
    mesH='{}'.format(Hgmax_A)
    for L in range(Lmax):
      mesH='{} {}'.format(mesH,int(HgHoL[L]))
    for L in range(Lmax):
      mesH='{} {:.5g}'.format(mesH,Entropy[L])
    mesH='{} #Hgmax,(ncmax{})HgoL0,1,2,Entr0,1,2'.format(mesH,ncmaxL[L])
    import re
    d1ext=re.findall('/t0.*',args.d1)[0][1:]

    print('{} #{}'.format(mesH,d1ext))

    mesH='{}'.format(Hgmax_A)
    for L in range(Lmax):
      mesH='{} {}'.format(mesH,int(HgEntropy[L]))
    for L in range(Lmax):
      mesH='{} {:.5g}'.format(mesH,Entropy[L])

    mesH='{} #Hgmax,(Entropymax{:.5g})HgoL0,1,2,ncmaxL'.format(mesH,Entropy[L])
    print('{} {} #{}'.format(mesH,ncmaxL[L],d1ext))

    if L==Lmax-1:
#      import pdb;pdb.set_trace(); #for debug 
      envN=envN[:-1] #remove the last char ','
      fp=open('{}/N-L{}.env'.format(args.d1,L),'w')
      fp.write('export N=N:{} #{}'.format(int(min(Nenv)),envN))
      fp.close()
    for Lmax1 in range(1,Lmax):
      fpyLc.write('\nset term tgif;set output \"%sL%d.obj\"\n' % (fnyLc,Lmax1))
      i1=1;lt=1;lw=2;col=colsplt[0]
      fpyLc.write('plot \"'+fnyg+'\" using ($0+%d):%d lt %d lw %d lc rgb \"%s\"%s' % (tp0,i1,lt,lw,col,'\\\n'))
      for L in range(Lmin,Lmax1+1):
        strL=str(L)
        if strL in L2ctoLig.keys():
          ctoLig=L2ctoLig[str(L)]
          for c in range(K**L):
            strc=str(c)
            if strc in ctoLig.keys():
              Li=ctoLig[strc]
              i1=Li[0]+1
              col=colsplt[(L)%9+1]
              col=colsplt[(2**L+c)%9]
              lw=(Lmax-L)*2
              lw=2
              lt=2*L+1
              if L==0:
                fpyLc.write(', \"'+fnyp+'\" using ($0+%d):%d lt %d lw %d lc rgb \"%s\"%s' % (tp0,i1,lt,lw,col,'\\\n'))
  #              fpyLc.write('plot \"'+fnyp+'\" using ($0+%d):%d lt %d lw %d lc rgb \"%s\"%s' % (tp0,i1,lt,lw,col,'\\\n'))
              elif L == Lmax1:
                fpyLc.write(', \"\" using ($0+%d):%d lt %d lw %d lc rgb \"%s\"%s' % (tp0,i1,lt,lw,col,'\\\n'))
  #      fpyLc.write('\n');
      fpyLc.write('\nset term postscript eps enhanced color;set output \"%sL%d.eps\";replot\n' % (fnyLc,Lmax1))

#####
          
    fpyLc.close()
    print args.tp0,
    Lctodegcuml['-1-0']=1    
    for L in range(0,Lmax):
      c=0;
      key=str(L-1)+'-'+str(c)
      for c in range(K**L): #clas=0 or 1
        degs=[]
        hgs=[]
        key=str(L-1)+'-'+str(c)
        print 'L%s' % (key),
        if key in Lctodegcuml:
          degs.append(Lctodegcuml[key])
        else:
          degs.append(0)
        if key in Lctohg.keys():
          hgs.append(Lctohg[key])
        else:
          hgs.append(0)
        adegs=np.array(degs)
        ilist=np.argsort(degs)[::-1]
        for i in ilist:
          print ' %.3f %.3f' % (hgs[i],degs[i]),
### display the y-t in L-c by gnuplot
  print '#class hg deg ...'
  print 'Lctohg:',Lctohg
  print 'Lc-hg %d ' % (tp0),L2ctoLig
  print 'dtodegcuml:',Lctodegcuml
  print('#Results2 are saved in d1={}'.format(args.d1));

if __name__ == "__main__":
  argv=sys.argv
  cmd=''
  for a in argv:#  for i,a in enumerate(argv):
    cmd+=a+' '
  print('#start:python {}'.format(cmd))

  main()
#
  
