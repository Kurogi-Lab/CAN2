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
import matplotlib.gridspec as gridspec
from matplotlib.colors import Normalize
from numpy.lib.stride_tricks import as_strided
import cv2
import time
import datetime
import sys
import mylib
#import myshell
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
 #   pass

def mypltshow(fnfig):
  plt.savefig(fnfig);
  myshell("sleep 1;gv "+fnfig+"&");
  plt.close() #plt.show()

def ia_mel(a,na,mel):
  if mel==0:
    ia1=int(float(na)*a/math.pi)
    ia2=int(na*(a/math.pi))
    ia3=int(na*a/math.pi)
    if ia1!=ia3:
      print('ia={}!={}=?{}'.format(ia1,ia2,ia3))
      import pdb;pdb.set_trace(); #for debug
#    return(int(float(na)*a/math.pi))
#    return(int(na*(a/math.pi)))
    return(int(na*a/math.pi))
  elif mel==1:
    f=4000.*a/math.pi
    return(int(na*(math.log(1.+f/700.)/1.90423745265))) #f0=700Hz
  elif mel==2:
    f=4000.*a/math.pi
    return(int(na*(math.log(1.+f/1000.)/1.60943791243))) #f0=1000Hz

#  m=1127.010480*math.log(1.+f/700.)
##  M=2146.09556555 #1127.010480*math.log(1.+4000./700.) #2146.09556555
#  return(int(na*m/2146.09556555))
#Max=1.90423745265=math.log(1.+4000./700.)

##def myshell(cmd): #no stop even when error occured                                
##  try:
##    retcode=subprocess.Popen(cmd, shell=True)
##    if retcode < 0:
##      print "my Child was terminated by signal", -retcode
##    else:
##      print "my Child returned", retcode
##  except OSError as e:
##    print "Execution failed:", cmd, e
##  return retcode.wait()
### http://optie.hatenablog.com/entry/2018/03/21/185647#32-ガウシアンフィルタ
##def norm2d(x,y,sigma):
##    Z = np.exp(-(x**2 + y**2) / (2 * sigma**2)) / (2 * np.pi * sigma**2)
##    return Z
##
#def gaussian_kernel(nG,sG):
#    if nG%2==0:
#      nG+=1
#    # [0,nG]→[-sG, sG] にずらす
#    x = y = np.arange(0,size) - sG
#    X,Y = np.meshgrid(x,y) 
#    mat = norm2d(X,Y,sG/2.)
#    kernel = mat / np.sum(mat) # normalize
#    return kernel
##
##def convolve2d_1ch(img, kernel, padding='0'):
##    # エラー処理
##    if len(img.shape) != 2:
##        print('img should be 2d-array')
##        return
##    if kernel.shape[0]%2 == 0:
##        print('Kernel size shold be odd')
##        return
##    
##    edge = int(kernel.shape[0]/2)
##    
##    # 境界をどうするか
##    if padding=='edge':
##        img = np.pad(img, [edge,edge], mode='edge')
##    elif padding=='reflect':
##        img = np.pad(img, [edge,edge], mode='reflect')
##    else:
##        img = np.pad(img, [edge,edge], mode='constant', constant_values=0)
##    
##    sub_shape = tuple(np.subtract(img.shape, kernel.shape) + 1)
##
##    # (rows, cols, N, N)
##    conv_shape = sub_shape + kernel.shape
##
##    # A.strides は (Aのrow方向の一要素ごとのbytes数, col方向のbytes数) のタプル
##    # (shape[0]*bytes, bytes, shape[0]*bytes, bytes)
##    strides = img.strides + img.strides
##
##    submatrices = as_strided(img, conv_shape, strides)
##
##    # (i,j)配列と(k,l,i,j)配列で, (i,j)要素同士の積和を要素とした(k,l)配列を返す
##    convolved_mat = np.einsum('ij, klij->kl', kernel, submatrices)
##    
##    return convolved_mat

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
  parser.add_argument('-dr', default='../../12voicedata_ueki_all_k8', type=str,   help='folder involving r')
  parser.add_argument('-k', default=8, type=int,   help='embedding dimension')
  parser.add_argument('-N', default=24, type=int,   help='Number of units')
  parser.add_argument('-nG', default=13, type=int,   help='Gaussian Kernel size')
  parser.add_argument('-sG', default=2, type=float,   help='Gaussian Kernel sigma')
#  parser.add_argument('-Fsize', default=40, type=int,   help='Feature size nWxnW')
  parser.add_argument('-nX', default=31, type=int,   help='nX, nY=nX/2:Feature size nWxnW')
  parser.add_argument('-rmax', default=3, type=float,   help='boundary magnitude of poles ')
  parser.add_argument('-sql', default='0', type=str,   help='1 for search q lack')
  parser.add_argument('-nr', default=2, type=int,   help='number of magnitude divisions of pole space')
  parser.add_argument('-na', default=18, type=int,   help='number of angle divisions of pole space')
  parser.add_argument('-nx', default=7, type=int,   help='number of divisions of y pole space')
  parser.add_argument('-mel', default=0, type=int,   help='1 for use mel frequency.')
#  parser.add_argument('-lm', default='tspredv3', type=str, choices=('tspredv3', 'tspredv3er'),   help='learning machine ')
  parser.add_argument('-DISP', default='1', type=str,   help='DISP[0]==1 to make files, DISP[1]==1 to display')
  parser.add_argument('-ow', default=1, type=int,   help='Overwite files if ow=1, omit otherwise.')
  parser.add_argument('-dbgi', default=-1, type=int,   help='debug at i-th iteration')
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
  dr=args.dr
  N=args.N
  na=args.na
  nr=args.nr
  mel=args.mel
  DISP=args.DISP+'0000'
  fnerr=['mmt-san2', 'fhs-hachi5']
  nS=len(S)
  nL=len(L)
  nD=len(D)
  np.random.seed(seed=32)
  for d in [dr]:#  for d in [dl, dn, dm, dq, dp, df]:
#  for d in [dm, dq, dp, df, dr]:#  for d in [dl, dn, dm, dq, dp, df]:
    if not os.path.exists(d): os.mkdir(d)
#    import pdb;pdb.set_trace(); #for debug
#  fnq='{}/*'.format(dm)
#  Fq=[r.split('/')[-1][:-6] for r in glob.glob(fnq)] #file list
#  dr2='{}/{}x{}'.format(dr,nr,na)
#  mylib.myshell('mkdir -p {}'.format(dr2))
  k=args.k;
  nG=args.nG
  sG=args.sG
#    GK=gaussian_kernel(args.nG)
#  fig=plt.figure()
#　fig.canvas.set_window_title("Gaussian Mixture Poles") 
  fig=plt.figure(figsize=(6,8),dpi=100)
  gs=gridspec.GridSpec(4,2)
  plt.subplots_adjust(wspace=0.5, hspace=0.5)
  pi=math.pi
  pix2=pi*2
  it=0
  start_time=time.time()
  argv=sys.argv
  cmd=''
  for a in argv:#  for i,a in enumerate(argv):
    cmd+=a+' '
  print('#start:{}'.format(cmd))

  print('#start time:{}'.format(datetime.datetime.now()))
  for r in Ra:
    fnq='{}/*R{}*-PC.dat'.format(dr,r)
    Fq=[(f.split('/')[-1])[:-len("-PC.dat")] for f in glob.glob(fnq)] #file list 7=len(-PC.dat)
    for i_s,s in enumerate(Sa):
      for d in Da:
        for l in La:
#          print('#check s:{} d:{} l:{}'.format(s,d,l));
#        import pdb;pdb.set_trace(); #for debug
          fn=s +'-'+ d + l
          fnB0='{}-{}{}-R{}'.format(s,d,l,r)
          fnB=''
          for fnq in Fq:
            if fnB0 in fnq:
              fnB=fnq
#              import pdb;pdb.set_trace();
          if fnB == '':
            print('#{}*-PC.dat noexist'.format(fnB0))
            continue
#          fnPC='{}/{}-PC.dat'.format(dr,fnB); 
          fnPC='{}/{}-PC.dat'.format(dr,fnB)
#          fnPcG='{}/{}-PcG.dat'.format(dr,fnB)#  
#          fnPcbG='{}/{}-PcbG.dat'.format(dr,fnB)#  
          print('#read {}'.format(fnPC))
#          if os.path.exists(fnPcG) and os.path.exists(fnPcbG) and args.ow == 0:
#            print('#{} exists: Omit calc because -ow 0'.format(fnout))
#            continue
          P=np.array(pd.read_csv(fnPC,delim_whitespace=True,dtype=np.float64,header=None))
          nP=P.shape[0] #=k*N
          N=nP/k
          P=P.reshape(N,k,4)
          nx=args.nx
          WXpX0=nx
          WX=int(WXpX0/2+0.5)
          X0=WX
          wx=args.rmax
          rmax=args.rmax
          x0=X0*wx/WX
          WY=WX
          Y0=int(nG/2.+0.5)
          WYpY0=WY+Y0
          WYpY0x2=2*(WY+Y0)
#          nW0=nW/2
          wy=wx #
          y0=Y0*wy/WY
#          WY2=2*(WY+Y0)
#          WY2=WY*2
#          w0=w/2.0+args.nG*args.rmax/args.Fsize
#          wp=2. # width of pole
          F1=np.zeros((WXpX0,WYpY0), dtype=np.float64)
          Fc=np.zeros((WXpX0,WYpY0), dtype=np.float64)
          Fcb=np.zeros((WXpX0,WYpY0x2), dtype=np.float64)
          qc=np.zeros((na,nr), dtype=np.float64)
          q1=np.zeros((na,nr), dtype=np.float64)
          nrx2=nr*2
          qcb=np.zeros((na,nrx2), dtype=np.float64)
          for n in range(N):
            Pn=P[n]
            for i in range(k):
              _r=math.sqrt(Pn[i,0]**2+Pn[i,1]**2)
              if Pn[i,1]==0:
                if '1' in DISP:
                  print('#Ignore pole on real axis: ({:.2g},{}) R:{} s:{} n:{}'.format(Pn[i,0],Pn[i,1],r,s,n))
              elif _r>=rmax:
                if '1' in DISP:
                  print('#Ignore pole out of bounds: (({:.2g},{})'.format(Pn[i,0],Pn[i,1],r,s,n))
#                import pdb;pdb.set_trace(); #for debug 20191105
              else:
                if Pn[i,1]>0: 
                  c=math.sqrt(Pn[i,2]**2+Pn[i,3]**2)
                  a=math.atan2(Pn[i,1],Pn[i,0])
                  b=math.atan2(Pn[i,3],Pn[i,2])
                  X=int(Pn[i,0]*WX/wx+nx/2.+0.5)
                  Y=int(Pn[i,1]*WY/wy+nG/2.+0.5)
#                  X=int(Pn[i,0]*WX/wx)+X0
#                  Y=int(Pn[i,1]*WY/wy)+Y0
                  Fc[X,Y]+=c 
                  F1[X,Y]+=1 
                  Fcb[X,Y+WYpY0]+=abs(Pn[i,3]) #   Fcb[XX0,YY0+WYpY0]+=c*math.cos(b) ##check20191125
                  Fcb[X,-Y+WYpY0]+=abs(Pn[i,2]) #  Fcb[XX0,-YY0+WYpY0]+=c*abs(math.sin(b)) #check20191125
                  if Fcb.min()<0:
                    import pdb;pdb.set_trace(); #for debug #check20191125
#                  Fcb[X,-Y+WYpY0]+=Pn[i,3] #  Fcb[XX0,-YY0+WYpY0]+=c*math.sin(b)
                  ir=int(nr*_r/rmax)
                  ia=ia_mel(a,na,mel) #a in [0,pi]
#                  ia=int(na*(a/pi)) #atan2 in [-pi,pi]
                  qc[ia,ir]+=c
                  q1[ia,ir]+=1
                  qcb[ia,ir]+=abs(Pn[i,3])
                  qcb[ia,nrx2-ir-1]+=abs(Pn[i,2]) #check 20191125
#                  qcb[ia,nrx2-ir-1]+=Pn[i,3]
#            print('#check20 s[{}]:{} d:{} l:{} n:{}'.format(i_s,s,d,l,n));
            if DISP[1] == '1' or (DISP[0]=='1' and n==N-1):
              Gc  = cv2.GaussianBlur(Fc,(nG,nG),sG)
              G1  = cv2.GaussianBlur(F1,(1,1),1)
              Gcb = cv2.GaussianBlur(Fcb,(nG,nG),sG)
              Qc=cv2.GaussianBlur(qc,(nG,nG),sG)
              Q1=cv2.GaussianBlur(q1,(nG,nG),sG)
              Qcb=cv2.GaussianBlur(qcb,(nG,nG),sG)
    #         Gc/=np.linalg.norm(Gc)
    #         G1/=np.linalg.norm(G1)
    #         Gcb/=np.linalg.norm(Gcb)
    #
              GcDisp  = np.rot90(Gc)
              G1Disp  = np.rot90(F1)
              GcbDisp = np.rot90(Gcb)
              qcDisp = np.rot90(Qc)
              qcbDisp = np.rot90(Qcb)
              q1Disp = np.rot90(Q1)
              Xt=[WX+m*WX/wx for m in range(-int(wx),int(wx)+1)]  #
              Xtl=['{:.0f}'.format((X-WX)*wx/WX) for X in Xt]
              Yt= [m*WY/wy for m in range(int(wy)+1)]
              Ytl=['{:.0f}'.format((WY-Y)*wy/WY) for Y in Yt]
#              y0m=-Y0*wy/WY
#              Yt.append(WYpY0-1)
#              Ytl.append('{:.1f}'.format(y0m))
              Ytb= Yt
              Ytlb=Ytl
              for m in range(0,int(wy)+1):
                Ytb.append(WYpY0x2-m*WY/wy-1)
                Ytlb.append(int(wy)-m)
  
  #              for m in range(int(wy)+1):
  #                Ytb.append(WYpY0+Y0+m*WY/wy)
  #                Ytlb.append(m)
  #              Ytb.append(WYpY0x2-1)
  #              Ytlb.append(int(wy))
  #              Ytlb=['{:.1f}'.format((WY-Y)*wy/WY) for Y in Yt]
  #              Ytlb=[str(int(wy)),    1, 0,  '{:.1g}'.format(y0m),       0,             1,str(int(wy))]
  
  #              Ytlb=['{:.0f}'.format(abs((Y-WYpY0)*wy/WY)) for Y in Ytb]
  #              Ytlb=['{:.1f}'.format(abs((Y-WYpY0)*wy/WY)) for Y in Ytb]
  
              cmap='bwr' #'rainbow'(good) 'bwr'(good) #seismic coolwarm viridis(default),spectral
              plt.clf()
    #            fig.add_subplot(2,1,1)
    #            ax=fig.add_subplot(2,1,1)
    #            import pdb;pdb.set_trace(); #for debug 20191105
    #            plt.xtics(Xt)
    #            plt.xticlabels(Xtl)
    #            plt.subplot(gs[0,0])
    #            plt.plot(xticks=Xt,xticklabels=Xtl,yticks=Yt,yticklabels=Ytl)
              fig.add_subplot(gs[0,0],xticks=Xt,xticklabels=Xtl,yticks=Yt,yticklabels=Ytl,title="2*c")
              mx=GcDisp.max()
              plt.imshow(GcDisp/mx,cmap=cmap,interpolation='none');
              plt.title('{}\n(r:rectangular,p:polar)\nrPcG=P.c*G (/{:.2g})\n'.format(fnB,mx));#plt.title('weighted by 2*c');
              plt.colorbar(fraction=0.05,pad=0.04);
              plt.clim(-1,1)
  #
              fig.add_subplot(gs[1,0],xticks=Xt,xticklabels=Xtl,yticks=Yt,yticklabels=Ytl,title="2*c")
              mx=G1Disp.max()
              plt.imshow(G1Disp/mx,cmap=cmap,interpolation='none');
              plt.title('rP1=P.1 (/{:.0f})'.format(mx));#plt.title('weighted by 2*c');
              plt.colorbar(fraction=0.05,pad=0.04);
              plt.clim(-1,1)
  #
              fig.add_subplot(gs[0:1,1],xticks=Xt,xticklabels=Xtl,yticks=Yt,yticklabels=Ytl)
              _max=GcbDisp.max()
              _min=GcbDisp.min()
              mx=max(abs(_max),abs(_min))
              plt.imshow(GcbDisp/mx,cmap=cmap,interpolation='none');#
              plt.title('rPcbG=P.c.f(b)\nin [{:.2g},{:.2g}]\nupper-half P.c.cos(b)*G\nlower-half P.c.sin(b)*G'.format(_min,_max));
              plt.colorbar(fraction=0.05,pad=0.04);
              plt.clim(-1,1)
  ##########
  #            Ytq=[j for j in range(0,nr,2)]               #->
  #            Ytlq=[(nr-j)*rmax/nr for j in range(0,nr,2)] #->0,1,2,3
              Ytlq=[j/2. for j in range(2*int(rmax)+1)] #0.5刻み
              Ytq =[nr-(j/2.)*(nr/rmax) for j in range(2*int(rmax)+1)]
              Xtlq=['{}pi/4'.format(4-j) for j in range(5)]
              Xtq=[(j/4)*(na/pi) for j in range(4)]
              Xtq=[j for j in range(0,na,9)]
              Xtlq=['{:.0f}pi/{}'.format(j,na) for j in range(0,na,9)]
              Xtq.append(na-1)
              Xtlq.append('pi')
              Xtq=[0,na/2,na-1]
              Xtlq=[0,'pi/2','pi']
              Ytq=[0,nr/2,nr-1]
              Ytlq=['{:.1g}'.format(rmax),'{:.1g}'.format(rmax/2.),0]
              Ytbq=[0,nr/2,nr,nr*3/2,2*nr-1]
              Ytlbq=['{:.1g}'.format(rmax),'{:.1g}'.format(rmax/2.),0,'{:.1g}'.format(rmax/2.),'{:.1g}'.format(rmax)]
              fig.add_subplot(gs[2,0],xticks=Xtq,xticklabels=Xtlq,yticks=Ytq,yticklabels=Ytlq)
  #            fig.add_subplot(gs[2,0],xticks=Xtq,xticklabels=Xtlq,yticks=Ytb,yticklabels=Ytlb)
              mx=qcDisp.max()
              plt.imshow(qcDisp/mx,cmap=cmap,interpolation='none');
              plt.title('pPcG=P.c*G (/{:.2g})'.format(mx));
              plt.colorbar(fraction=0.05,pad=0.04);
              plt.clim(-1,1)
  #
              fig.add_subplot(gs[3,0],xticks=Xtq,xticklabels=Xtlq,yticks=Ytq,yticklabels=Ytlq)
              mx=q1Disp.max()
              plt.imshow(q1Disp/mx,cmap=cmap,interpolation='none');
              plt.title('pP1=P.1 (/{:.0f})'.format(mx));
              plt.colorbar(fraction=0.05,pad=0.04);
              plt.clim(-1,1)
  #
              fig.add_subplot(gs[2:3,1],xticks=Xtq,xticklabels=Xtlq,yticks=Ytbq,yticklabels=Ytlbq)
              _max=qcbDisp.max()
              _min=qcbDisp.min()
              mx=max(abs(_max),abs(_min))
              plt.imshow(qcbDisp/mx,cmap=cmap,interpolation='none');#
              plt.title('pPcbG=f(b)*G: \nin [{:.2g},{:.2g}]\nupper-half P.c.cos(b)\nlower-half P.c.sin(b)'.format(_min,_max));
              plt.colorbar(fraction=0.05,pad=0.04);
              plt.clim(-1,1)
  #
              plt.pause(0.05)
#              mypltshow("tmp/fig.eps");

              if DISP[1] == '1':
                print('### Now for the debug mode');
                import pdb;pdb.set_trace(); #for debug 20191105
#          for n in range(N):
      #################
#            print('#check2 s[{}]:{} d:{} l:{} n:{}'.format(i_s,s,d,l,n));
          FD=['rP1','rPc', 'rPcb','pP1','pPc','pPcb']
          F0=[F1,Fc,Fcb,q1,qc,qcb]
          for i_fd,fd in enumerate(FD):
            F1=F0[i_fd] if nG==1 else cv2.GaussianBlur(F0[i_fd],(nG,nG),sG)
#            F1 /= np.linalg.norm(F1)
            if fd[0]=='r':
              fnr='{}/{}-{}F{}G{}x{}.dat'.format(dr,fnB,fd,nx,nG,sG)
            else:
              fnr='{}/{}-{}F{}x{}G{}x{}m{}.dat'.format(dr,fnB,fd,nr,na,nG,sG,mel)
            df=pd.DataFrame(F1.reshape((1,-1)))
            df.to_csv(fnr,index=False,sep=' ',header=None)
#            import pdb;pdb.set_trace(); #for debug 20191105
#            print('#check')
###          if nG ==1:
###            G1  = F1
###            Gc  = Fc
###            Gcb = Fcb
###            Q1 = q1
###            Qc = qc
###            Qcb =qcb
###          else:
###            G1  = cv2.GaussianBlur(F1,(nG,nG),sG)
###            Gc  = cv2.GaussianBlur(Fc,(nG,nG),sG)
###            Gcb = cv2.GaussianBlur(Fcb,(nG,nG),sG)
###            Q1 = cv2.GaussianBlur(q1,(nG,nG),sG)
###            Qc = cv2.GaussianBlur(qc,(nG,nG),sG)
###            Qcb = cv2.GaussianBlur(qcb,(nG,nG),sG)
###
###          G1 /= np.linalg.norm(G1)
###          Gc /= np.linalg.norm(Gc)
###          Gcb /= np.linalg.norm(Gcb)
###          Q1 /= np.linalg.norm(Q1)
###          Qc /= np.linalg.norm(Qc)
###          Qcb /= np.linalg.norm(Qcb)
###
###
###          FG=[G1,Gc,Gcb,Q1,Qc,Qcb]
###          FD=['rP1','rpc', 'rPcb','pP1','pPc','pPcb']
###          for i_fd,fd in enumerate(FD):
###            if fd[0]=='r':
###              fnr='{}/{}-{}F{}G{}x{}.dat'.format(dr,fnB,fd,nx,nG,sG)
###            else:
###              fnr='{}/{}-{}F{}x{}G{}x{}.dat'.format(dr,fnB,fd,nr,na,nG,sG)
###            df=pd.DataFrame(FG[i_fd].reshape((1,-1)))
###            df.to_csv(fnr,index=False,sep=' ',header=None)
#            import pdb;pdb.set_trace(); #for debug 20191105

          print('#created {}-[rPc|rPcb|rP1]F{}G{}x{}.dat and [pPc|pPcb|Ppc]F{}x{}G{}x{}.dat (it:{})'.format(fnB,nx,nG,sG,nr,na,nG,sG,it))
#          import pdb;pdb.set_trace(); #for debug 20191105
#          print('#check3 s[{}]:{} d:{} l:{} it:{}'.format(i_s,s,d,l,it));
#          if it == 697:
##          if i_s==6 and d=='kyu' and l==10:
#            print('### Now in debug mode');
          sys.stdout.flush()
          it += 1
          if args.dbgi>0 and it==args.dbgi:
            print('### Now in debug mode');
            import pdb;pdb.set_trace(); #for debug 20191105
#          import pdb;pdb.set_trace();
#
#        print('#Saved {}.'.format(fnout))
  elapsed_time=time.time()-start_time
  etime='ElapsedTime {:.3f}s({})'.format(elapsed_time,str(datetime.timedelta(seconds=elapsed_time))[:-3])
  print('#{}'.format(etime))
