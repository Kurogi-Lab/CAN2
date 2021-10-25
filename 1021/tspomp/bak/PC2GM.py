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
#import myshell
S=['fhs', 'fms', 'mkk', 'mko','mmt','mnh','mym']
L=[1,2,3,4,5,6,7,8,9,10]
D=['zero','ichi','ni','san','si','go','roku','nana','hachi','kyu']
R=[1,0.8,0.6,0.4,0.2]
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
#def gaussian_kernel(Ksize,Ksigma):
#    if Ksize%2==0:
#      Ksize+=1
#    # [0,Ksize]→[-Ksigma, Ksigma] にずらす
#    x = y = np.arange(0,size) - Ksigma
#    X,Y = np.meshgrid(x,y) 
#    mat = norm2d(X,Y,Ksigma/2.)
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
  parser.add_argument('-Ksize', default=13, type=int,   help='Gaussian Kernel size')
  parser.add_argument('-Ksigma', default=2, type=int,   help='Gaussian Kernel sigma')
  parser.add_argument('-Fsize', default=40, type=int,   help='Feature size nWxnW')
  parser.add_argument('-rmax', default=3, type=float,   help='boundary magnitude of poles ')
  parser.add_argument('-sql', default='0', type=str,   help='1 for search q lack')
  parser.add_argument('-na', default=18, type=int,   help='number of angle divisions of pole space')
  parser.add_argument('-nr', default=2, type=int,   help='number of magnitude divisions of pole space')
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
  k=args.k;
#    GK=gaussian_kernel(args.Ksize)
#  fig=plt.figure()
  fig=plt.figure(figsize=(10,8))
#　fig.canvas.set_window_title("Gaussian Mixture Poles") 
  gs = gridspec.GridSpec(2,2)
  plt.subplots_adjust(wspace=0.5, hspace=0.5)

  it=0
  for r in Ra:
    fnq='{}/*R{}*-PC.dat'.format(dr,r)
    Fq=[(f.split('/')[-1])[:-len("-PC.dat")] for f in glob.glob(fnq)] #file list 7=len(-PC.dat)
    for i_s,s in enumerate(Sa):
      for d in Da:
        for l in La:
          fn=s +'-'+ d + l
          fnB0='{}-{}{}-R{}'.format(s,d,l,r)
          fnB=''
          for fnq in Fq:
            if fnB0 in fnq:
              fnB=fnq
#              import pdb;pdb.set_trace();
          if fnB == '':
            print('#{}*-PC.dat does not exist'.format(fnB0))
            continue
#          fnPC='{}/{}-PC.dat'.format(dr,fnB); 
          fnPC='{}/{}-PC.dat'.format(dr,fnB)
          fnPcG='{}/{}-PcG.dat'.format(dr,fnB)#  
          fnPcbG='{}/{}-PcbG.dat'.format(dr,fnB)#  
          print('#Read {}'.format(fnPC))
          if os.path.exists(fnPcG) and os.path.exists(fnPcbG) and args.ow == 0:
            print('#{} exists: Omit calc becaus -ow 0'.format(fnout))
            continue
          P=np.array(pd.read_csv(fnPC,delim_whitespace=True,dtype=np.float32,header=None))
          nP=P.shape[0] #=k*N
          N=nP/args.k
          P=P.reshape(N,k,4)
          WXpX0=args.Fsize
          WX=WXpX0/2
          X0=WX
          wx=args.rmax
          rmax=args.rmax
          x0=X0*wx/WX
          WY=WX
          Y0=args.Ksize/2
          WYpY0=WY+Y0
          WYpY0x2=2*(WY+Y0)
#          nW0=nW/2
          wy=wx #
          y0=Y0*wy/WY
#          WY2=2*(WY+Y0)
#          WY2=WY*2
#          w0=w/2.0+args.Ksize*args.rmax/args.Fsize
#          wp=2. # width of pole
          F1=np.zeros((WXpX0,WYpY0), dtype=np.float32)
          Fc=np.zeros((WXpX0,WYpY0), dtype=np.float32)
          Fcb=np.zeros((WXpX0,WYpY0x2), dtype=np.float32)
          qc=np.zeros((na,nr), dtype=np.float32)
          q1=np.zeros((na,nr), dtype=np.float32)
          qcb=np.zeros((na,nr*2), dtype=np.float32)
          for n in range(N):
            Pn=P[n]
            for i in range(k):
              r=math.sqrt(Pn[i,0]**2+Pn[i,1]**2)
              if Pn[i,1]==0:
                print('#Ignore pole on real axis: ({:.2g},{}) R:{} s:{} n:{}'.format(Pn[i,0],Pn[i,1],r,s,n))
              elif r>=rmax:
#              elif X<0 or X>=WXpX0 or Y<0 or Y>=WYpY0:
                print('#Ignore pole out of bounds: (({:.2g},{})'.format(Pn[i,0],Pn[i,1],r,s,n))
                import pdb;pdb.set_trace(); #for debug 20191105
              else:
                if Pn[i,1]>0: 
                  c=math.sqrt(Pn[i,2]**2+Pn[i,3]**2)
                  a=math.atan2(Pn[i,1],Pn[i,0])
                  b=math.atan2(Pn[i,3],Pn[i,2])
                  X=int(Pn[i,0]*WX/wx)+X0
                  Y=int(Pn[i,1]*WY/wy)+Y0
                  Fc[X,Y]+=c 
                  F1[X,Y]+=1 
                  Fcb[X,Y+WYpY0]+=Pn[i,2] #   Fcb[XX0,YY0+WYpY0]+=c*math.cos(b)
                  Fcb[X,-Y+WYpY0]+=Pn[i,3] #  Fcb[XX0,-YY0+WYpY0]+=c*math.sin(b)
                  ir=int(r/rmax)
                  ia=int(a/math.pi)
                  qc[ia,ir]+=c
                  q1[ia,ir]+=1
                  qcb[ia,ir]+=Pn[i,2]
                  qcb[ia,nr+ir]+=Pn[i,3]

          Gc  = cv2.GaussianBlur(Fc,(args.Ksize,args.Ksize),args.Ksigma)
          G1  = F1 #cv2.GaussianBlur(F1,(1,1),10)
          Gcb = cv2.GaussianBlur(Fcb,(args.Ksize,args.Ksize),args.Ksigma)
          Gc=Fc
          Gcb=Fcb
          Gc/=np.linalg.norm(Gc)
          G1/=np.linalg.norm(G1)
          Gcb/=np.linalg.norm(Gcb)
#
          if DISP[0] == '1':
            GcDisp  = np.rot90(Gc)
            G1Disp  = np.rot90(G1)
            GcbDisp = np.rot90(Gcb)
#              Xt=[0   ,WX/wx, 2*WX/wx,WX,WX+WX/wx,WX+2*WX/wx,WXpX0-1]
            Xt=[WX+m*WX/wx for m in range(-int(wx),int(wx)+1)]  #
            Xtl=['{:.0f}'.format((X-WX)*wx/WX) for X in Xt]

            y0m=-Y0*wy/WY
#              Yt= [0      ,(WY/wy),2*WY/wy,WY, WYpY0-1] #              Yt=[0,WYpY0-Y0,WYpY0-1]
#              Ytl=[str(wy),      2,      1, 0, y0m] #inverse?
#
#              Yt= [0      ,(WY/wy),WY, WYpY0-1] #              Yt=[0,WYpY0-Y0,WYpY0-1]
#              Ytl=[str(wy),      1, 0, y0m] #inverse?
#              import pdb;pdb.set_trace(); #for debug 20191105

            Ytb=[0            ,WY/wy,2*WY/wy,WY,WYpY0,WYpY0+Y0,WYpY0+Y0+WY/wy,WYpY0x2-WY/wy,WYpY0x2-1] #inverse? 
            Ytlb=[str(int(wy)),    2,      1, 0,  y0m,       0,             1,            2,str(int(wy))]

            Ytb=[0            ,WY/wy,WY,WYpY0,WYpY0+Y0,WYpY0+Y0+WY/wy,WYpY0x2-1] #inverse? 
            Ytlb=[str(int(wy)),    1, 0,  y0m,       0,             1,str(int(wy))]

            Yt= [m*WY/wy for m in range(int(wy)+1)]
            Ytl=['{:.0f}'.format((WY-Y)*wy/WY) for Y in Yt]
            Yt.append(WYpY0-1)
            Ytl.append('{:.1f}'.format(y0m))

            Ytb= Yt
            Ytlb=Ytl
#              Ytb.append(WYpY0-1)
#              Ytl.append('{:.1f}'.format(y0m))
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

            Pn=P[n]
            cmap='bwr' #'rainbow'(good) 'bwr'(good) #seismic coolwarm viridis(default),spectral
            plt.clf()
  #            fig.add_subplot(2,1,1)
  #            ax=fig.add_subplot(2,1,1)
  #            import pdb;pdb.set_trace(); #for debug 20191105
  #            plt.xtics(Xt)
  #            plt.xticlabels(Xtl)
  #            plt.subplot(gs[0,0])
  #            plt.plot(xticks=Xt,xticklabels=Xtl,yticks=Yt,yticklabels=Ytl)
            ax=fig.add_subplot(gs[0,0],xticks=Xt,xticklabels=Xtl,yticks=Yt,yticklabels=Ytl,title="2*c")
            mx=GcDisp.max()
            plt.imshow(GcDisp/mx,cmap=cmap);
            plt.title('{}\nPcG: P.c*G\n'.format(fnB));#plt.title('weighted by 2*c');
            plt.colorbar(fraction=0.05,pad=0.04);
            plt.clim(-1,1)
            ax=fig.add_subplot(gs[1,0],xticks=Xt,xticklabels=Xtl,yticks=Yt,yticklabels=Ytl,title="2*c")
            mx=G1Disp.max()
            plt.imshow(G1Disp/mx,cmap=cmap);
            plt.title('P1G: P.1\n');#plt.title('weighted by 2*c');
            plt.colorbar(fraction=0.05,pad=0.04);
            plt.clim(-1,1)
            ax=fig.add_subplot(gs[:,1],xticks=Xt,xticklabels=Xtl,yticks=Ytb,yticklabels=Ytlb)
            mx=abs(GcbDisp).max()
            plt.imshow(GcbDisp/mx,cmap=cmap);#
            plt.title('PcbG:\nupper-half P.c.cos(b)*G\nlower-half P.c.sin(b)*G');
            plt.colorbar(fraction=0.05,pad=0.04);
            plt.clim(-1,1)
            plt.pause(0.05)
  #            import pdb;pdb.set_trace(); #for debug 20191105
          if DISP[1] == '1':
            import pdb;pdb.set_trace(); #for debug 20191105
          df=pd.DataFrame(Gc.reshape((1,-1)))
          df.to_csv(fnPcG,index=False,sep=' ',header=None)
          df=pd.DataFrame(Gcb.reshape((1,-1)))
          df.to_csv(fnPcbG,index=False,sep=' ',header=None)
          print('#{}-PcG.dat, -PcG.dat created'.format(fnB))

          it += 1
          if args.dbgi>0 and it==args.dbgi:
            import pdb;pdb.set_trace(); #for debug 20191105
#          import pdb;pdb.set_trace();
#
#        print('#Saved {}.'.format(fnout))
