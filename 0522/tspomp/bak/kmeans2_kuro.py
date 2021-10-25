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

#import os.path
#import os
#script_dir = os.path.abspath(os.path.dirname(__file__))
#os.path.abspath(__file__)

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
  fnyp='{}/{}'.format(args.d1,args.fnyp)
  if not os.path.isfile(fnyp):
#  if len(fnyp) == 0:
    print '#fnyp=%s does not exist' % (fnyp)
    return
  fnyg='{}/{}'.format(args.d1,args.fnyg)
  if not os.path.isfile(fnyg):
    print '#fnyg=%s does not exist' % (fnyg)
    return

  colsplt=["black", "red", "dark-green", "magenta", "green", "light-green", "salmon", "pink",  "grey"]
  colsplt=["black", "red", "dark-green", "blue", "magenta", "green", "light-green", "salmon", "pink",  "grey"]
  colsplt=["red", "dark-green", "green", "blue", "green",  "light-green", "blue", "cyan", "orange" "salmon", "pink", "magenta", "grey"]
  colsplt=["red", "dark-green", "dark-green", "blue", "dark-green", "green", "blue", "cyan", "light-green","orange" "salmon", "pink", "magenta", "grey"]
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
  Y = np.array(pd.read_csv(fnyp,delim_whitespace=True,dtype=np.float32,header=None))
  Y = Y.T # transpose
  N,T=Y.shape #N:number of time series, T:horizon
  Ey=args.Ey       #threshold for predictable horizon
  h_all=[]
#  H=np.zeros((L+1,2**L)).astype('float32')

  DISP=args.DISP

  C=np.zeros((N,Lmax+1)).astype('uint8')
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

    for L in range(Lmin,Lmax):
      ctoh0=dict()
      ctonY=dict()
      ctoLi=dict()
      ctoLic0=dict()
      ctoLic1=dict()
      ctoLig=dict()
      if LONGhg == 1 and args.Lt == 1:
        break
      l=L
    #for l in range(L,L+1):#level ??? what does l mean???????????????????
  #      for l in range(L+1):#level ??? what does l mean???????????????????
      for c in range(K**l): #clas=0 or 1
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
        else: #if nY > 3: --> nY<=3
#          print '#####################nY=%d<2,c=%d,L=%d' % (nY,c,L)
          ctoLic0[strc]=Li #list of n
          ctoLic1[strc]=[] #list of n
          ctoh0[strc]=0
          ctonY[strc]=nY
          for n in range(N):
            if C[n,l] == c:
              C[n,l+1] = C[n,l]*K
              ctoLi[strc]=[n]
#    for L in range(Lmin,Lmax):  ##close for L?
#####close L? NO


######
#      import pdb;pdb.set_trace(); #for debug 
#      if L==3: 
#        import pdb;pdb.set_trace(); #for debug 

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
      import matplotlib.pyplot as plt
      import matplotlib.cm as cm
      import matplotlib
    #  import pdb;pdb.set_trace(); #for debug 
    #  cols=matplotlib.colors.cnames.keys()
      cols = ["r", "g", "b", "c", "m", "y", "k"]
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
        print 'L%d c%s n=%d h0=%d' % (L,c,ctonY[c],ctoh0[c]),
        if L==0:
          print ''  
        else:
          print ' iY=',ctoLi[c]
          Ns=all_id[Sth_id[ctoLi[c]]]
          import pdb;pdb.set_trace(); #for debug 
          h_Lc=h_all_A[ctoLi[c]]
          Nsh=np.concatenate([Ns,h_Lc.reshape((-1,1))],axis=1)
          df=pd.DataFrame(Nsh)
          df.to_csv('{}/Nsh-L{}c{}.csv'.format(args.d1,L,c),index=False,sep=' ',header=None)
          nNs=Ns.shape[0]
          Nss='N:{}'.format(Ns[0,0])
          for iN in range(1,nNs):
            Nss=Nss+',{}'.format(Ns[iN,0])
          NsL.append([Nss,nNs,c])
#          import pdb;pdb.set_trace(); #for debug 
        if DISP: plt.show()
#      if L>0:
      if L==Lmax-1:
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
  ##
      print '###mean'
      ymean=np.zeros((K**L,T)).astype('float32') #dummy
  #    for i in range(len(ctoLi)):
  #      c=str(i)
      for i,c in enumerate(ctoLi):
        for n in ctoLi[c]:  
          ymean[i] += Y[n,:]
        ymean[i] = ymean[i]/len(ctoLi[c])
  #      if ctonY[c] > 1:
  #        plt.plot(x, ymean[i],color=cols[i])
  #      print 'i=%d c=%s nY=%d hm=%d' % (i,c,ctonY[c],ctoh0[c]),' cn=',ctoLi[c]
  #    plt.show()
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
          Lctodegcuml[keycuml] /=degcumlsum
          print '(%d)%.3f' % (c,Lctodegcuml[keycuml]),
#          print '%s:%.2f' % (keycuml,Lctodegcuml[keycuml]),
        print ''

#      fnyg=os.path.expanduser(args.fnyg)
      fnyg='{}/{}'.format(args.d1,args.fnyg)
#      fnyg=args.fnyg
#      import pdb;pdb.set_trace(); #for debug 
      if os.path.isfile(fnyg):
        print '#predictable horizons'
        yg = np.array(pd.read_csv(fnyg,delim_whitespace=True,dtype=np.float32,header=None))
        plt.plot(x, yg,color=cols[0]) #ground truth
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
        print 'max h(y%d,yg)=%d' % (ib,hb),
        print 'deg:', Lctodeg
#        import pdb;pdb.set_trace(); #for debug 
        plt.plot(x, Y[ib],color=cols[1])
  ##mean
  #      for i in range(len(ctoLi)):
  #        c=str(i)
        for i,strc in enumerate(ctoLi):
          c=int(strc) #?????
          key0=str(L)+'-'+str(c*K)
          key1=str(L)+'-'+str(c*K+1)
          key=str(L-1)+'-'+strc
          h=horizon(ymean[i],yg,Ey) 
          Lctohg[key]=h
          print 'L%d c%s N%d h(Yi,ymean)=%d h(ymean,yg)=%d' % (L,strc,ctonY[strc],ctoh0[strc],h),
          if ctonY[strc] >=nth: #tag1
            icol=(i+2) % 7
            plt.plot(x, ymean[i],color=cols[icol])
  #best yp via LOOCV horizon
            nLOOH=len(ctoLi[strc])
            LOOH=np.zeros(nLOOH).astype('float32') #
            for j,n in enumerate(ctoLi[strc]):
              for m in ctoLi[strc]:
                if n != m:
                  H= horizon(Y[n],Y[m],Ey)
                  LOOH[j] += H
              LOOH[j] /= (nLOOH-1) #######sum of horizon
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
            plt.plot(x, Y[n],color="black")
  #          print ' LOOCVh=%g nLOOH=%d ' % (LOOH,nLOOH),
          else: # if ctonY[strc] >=3:  tag1
            print ' h(,yg)=%.1f' % (horizon(Y[ctoLi[strc][0]],yg,Ey)),
  #          LOOH=0;nLOOH=0
  #          print ' LOOCVh=%g nLOOH=%d' % (LOOH,nLOOH),
          if L==0:
            print ''
          else:
            print 'iY',ctoLi[strc]
        if DISP: 
          plt.show()
###
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
  print('#start:{}'.format(cmd))

  main()
#
  
