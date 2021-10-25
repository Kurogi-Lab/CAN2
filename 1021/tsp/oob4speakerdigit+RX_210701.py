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

def m_st(i_s,i_t): #
  if verif=="s":
    return i_s #for speaker recog
  else:  
    return i_t #for speaker recog

#old#def vrv2_f(f): # old
#old#  fl=f.split('-')
#old#  import pdb;pdb.set_trace(); #for debug
#old## MFCC  f=mnh-go1-R1-sCns120.dat #2210617
#old## LPCSE f=mnh-go1-R1-sCns120.dat #2210617
#old## CAN2 f=mnh-go1-R1-pP1F2x23G3x0.5m0.dat
#old#  if fl[-2][0]=='C': #LPC  #mnh-go1-R1-MFCCl20m20n22E1.dat
#old#    if verif=="s": #speaker
#old#      v=fl[0]
#old#      if len(fl)==5: #e.g. mnh-ni7-R1-Ck50l20-FDsCns90ls10.dat
#old#        r='1'
#old#        v2=v #-> mnh-ni7-R1-Ck50l20-FDsCns90ls10.dat
#old#      elif len(fl)==7:
#old#        r=fl[4][1:]
#old#        v2=fl[2]
#old#    else:#    if verif=="t": #text
#old#      v=fl[1][:-1] if fl[1][-2].isdigit()==False else fl[1][:-2]
#old#      if len(fl)==5:#e.g. mym-kyu10-R1-p.dat
#old#        r='1'
#old#        v2=v
#old#      elif len(fl)==7:
#old#        r=fl[4][1:]
#old#        v2=fl[3][:-1] if fl[3][-2].isdigit()==False else fl[3][:-2]
#old#
#old#  else:#pole-distribution
#old#    if verif=="s": #speaker
#old#      v=fl[0]
#old#      if len(fl)==4:#e.g. mym-kyu10-R1-p.dat
#old#        r='1'
#old#        v2=v
#old#      elif len(fl)==6: #e.g. ['fms', 'si9', 'R0.8', 'mkk', 'kyu1', 20201224
#old##    elif len(fl)==6: #e.g. ['fms', 'si9', 'R0.8', 'mkk', 'kyu1', 'pP1F2x23G3x0.5m0.dat']fhs-go1-mmt-nana10-R0.8-p.dat -> fms-ni2-R0.8-mmt-san4-pP1.dat
#old#        r=fl[2][1:]
#old#        v2=fl[3] #-> fhs-go1-mmt-nana10-R0.8-p.dat -> fms-ni2-R0.8-mmt-san4-pP1.dat 
#old#      #20200910?    s2=fl[3] #-> fhs-go1-mmt-nana10-R0.8-p.dat -> fms-ni2-R0.8-mmt-san4-pP1.dat 
#old#    else:#verif=t text
#old#      v=fl[1][:-1] if fl[1][-2].isdigit()==False else fl[1][:-2]
#old#      if len(fl)==4:#e.g. mym-kyu10-R1-p.dat
#old#        r='1'
#old#        v2=v
#old#      elif len(fl)==6: #e.g. fhs-go1-mmt-nana10-R0.8-pP1F4x24G3x0.5m0.dat 
#old#        r=fl[4][1:]
#old#        v2=fl[3][:-1] if fl[3][-2].isdigit()==False else fl[3][:-2]
#old#      #20200910?    s2=fl[3] #-> fhs-go1-mmt-nana10-R0.8-p.dat -> fms-ni2-R0.8-mmt-san4-pP1.dat 
#old#  return v,r,v2


def vrv2_f(f): # new 20210617
  fl=f.split('-')
# MFCC  f=mnh-go1-R1-sCns120.dat #20210617
# LPCSE f=mnh-go1-R1-sCns120.dat #20210617
# CAN2 f=mnh-go1-R1-pP1F2x23G3x0.5m0.dat
# y=fhs-zero1-R0.8-mko-go7.dat
#  import pdb;pdb.set_trace(); #for debug
  if verif=="s": #speaker verification
    v=fl[0]
#    import pdb;pdb.set_trace(); #for debug
    if fl[3]=='R1':#e.g. mym-kyu10-R1-p.dat
      r='1'
      v2=fl[0] #-> mnh-ni7-R1-Ck50l20-FDsCns90ls10.dat
    else:#R=0.8, ...
      r=fl[2][1:]
      v2=fl[3] # y=fhs-zero1-R0.8-mko-go7.dat
  else:#    if verif=="t": #text verification
    if fl[3]=='R1':#e.g. mym-kyu10-R1-p.dat
      r='1'
      v2=v=fl[1][:-1] if fl[1][-2].isdigit()==False else fl[1][:-2]
    else:
      r=fl[3][1:] # y=fhs-zero1-R0.8-mko-go7.dat
      v2=fl[4][:-1] if fl[4][-2].isdigit()==False else fl[4][:-2]
  return v,r,v2

if __name__ == "__main__":
#oob4speakerdigit+sX_2018 sp:fhs:fms tx:zero:ichi ntxi:9 k:36 mbas:$mbas dir:$dir1 dir2:$dir2 s:-1 N:${N} sX:${sX}
#oob4speakerdigit+ sp:fhs:fms:mkk:mko:mmt:mnh:mym tx:zero:ichi:ni:san:yon:go:roku:nana:hachi:kyu ntxi:10 k:36 mbas:2:300:1.6:1 dir:$dira s:-1 N:40

  parser = argparse.ArgumentParser(description='speech normalize')
  parser.add_argument('-ntxi', default=10, type=int,   help='number of texts')
  parser.add_argument('-k', default=36, type=int, help='embedding dimensionk')
  parser.add_argument('-N', default=40, type=int,   help='number of units for verification')
  parser.add_argument('-mbas', default='2:300:1.6:1', type=str,   help='mbas:2:nbag:bagsize_ratio:1')
  parser.add_argument('-s', default=0, type=int,   help='-1 for all speaker verification')
  parser.add_argument('-d', default=0, type=int,   help='-1 for all digit verification')
  parser.add_argument('-sd', default='', type=str,   help='s and d, respectively, for speaker and digit verification')
  parser.add_argument('-w', default=0, type=int,   help='-1 for all digit (word) verification')
  parser.add_argument('-sX', default=-1, type=int,   help='excluded speaker')
  parser.add_argument('-dr', default='.', type=str,   help='directory of training data')
  parser.add_argument('-R', default='0.8', type=str,   help='mag r1:r2:...:rn for learning and test')
  parser.add_argument('-RX', default='0', type=str,   help='mag r1:r2:...:rn for test')
  parser.add_argument('-FD', default='pP1', type=str, help='Features of data')
#  parser.add_argument('-FD', default='pP1', type=str, choices=['pP1','pPc','pPcb','rP1','rPc','rPcb','s','S','sR','SR','SC','sC'],help='Features of data')
#  parser.add_argument('-kl', default='k20l20', type=str,   help='k:LPC dimension, fl flame-length[ms] ')
  parser.add_argument('-nr', default=2, type=int,   help='number of divisions for magnitude-axis in pole space')
  parser.add_argument('-na', default=18, type=int,   help='number of divisions for angle-axis in pole space')
  parser.add_argument('-ns', default=100, type=int,   help='number of divisions for spectrum envelope')
  parser.add_argument('-ls', default='00', type=str,   help='use log-scale or not, 10: log before mean, 01 log after mean, 00 no-log')
  parser.add_argument('-lx', default='0', type=str,   help='use log-scale or not, 1: log , 0 no-log')
#  parser.add_argument('-ls', default=1, type=int,   help='use log-scale or not')
  parser.add_argument('-nx', default=7, type=int,   help='number of divisions on x-axis in pole space')
  parser.add_argument('-nG', default=13, type=int,   help='Gaussian Kernel size')
  parser.add_argument('-sG', default=2, type=float,   help='Gaussian Kernel sigma')
  parser.add_argument('-OmL', default='0', type=str,   help='Omit Learning')
  parser.add_argument('-ow', default=1, type=int,   help='Overwite files if ow=1, omit otherwise.')
  parser.add_argument('-mel', default=0, type=int,   help='1 for use mel frequency.')
  parser.add_argument('-DISP', default='1', type=str,   help='DISP[0]==1 to make files, DISP[1]==1 to display')
  parser.add_argument('-nlz', default='1', type=str, choices=['max','norm','1','none'], help='normalize by norm, max, 1')
  parser.add_argument('-fnerr', default='mmt-san2:fhs-hachi5', type=str,   help='files lacking data')
  parser.add_argument('-AF', default='_', type=str, help='AF=(dr/FDext) of Additional Features for training')
  parser.add_argument('-AFcut', default='', type=str, help='ex. -AFcut 23-46:0-1')
  parser.add_argument('-method', default='CAN2,8,50,2:0.7:1:20', type=str, help='method for making M or s')
  parser.add_argument('-sp', default='fhs:fms:mkk:mko:mmt:mnh:mym', type=str,   help='speaker')
  parser.add_argument('-tx', default='zero:ichi:ni:san:si:go:roku:nana:hachi:kyu', type=str,   help='text')
  parser.add_argument('-S', default='fhs:fms:mkk:mko:mmt:mnh:mym', type=str,   help='speaker')
  parser.add_argument('-D', default='zero:ichi:ni:san:si:go:roku:nana:hachi:kyu', type=str,   help='text')
  parser.add_argument('-L', default='1:2:3:4:5:6:7:8:9', type=str, help='datetime index')
#  parser.add_argument('-drFD2', default='', type=str, help='drFD2(dr/FDext) of Additional Features for training ')
#  parser.add_argument('-fn4AF', default='', type=str, help='fn4 Additional Features for training')
  np.random.seed(seed=32)
  args = parser.parse_args()
  S=(args.sp).split(':') #speakers
  T=(args.tx).split(':') #text
  S=(args.S).split(':') #speakers
  D=(args.D).split(':') #speakers
  L=(args.L).split(':') #speakers
  R=(args.R).split(':') #lamgda:SN ratio
  RX=(args.RX).split(':') #lambda:SN ratio for test
  L=(args.L).split(':') #text
  sX=args.sX
  dr=args.dr
  nr=args.nr
  na=args.na
  nx=args.nx
  nG=args.nG
  sG=args.sG
#  FD=(args.FD).split('_')
  FD=args.FD
  mel=args.mel
  N=args.N
  DISP=args.DISP+'00000'
#  L=range(1,args.ntxi+1) #date
  _mbas=map(float,(args.mbas).split(':'))
  mbas=[]
  mbas.append(int(_mbas[0]))
  mbas.append(int(_mbas[1]))
  mbas.append(float(_mbas[2]))
  mbas.append(int(_mbas[3]))
  b=mbas[1] #method,b,a,seed=map(int,(args.mbas).split(':'))
  fntrain_check=0 #for check target to debug
  fnerr=(args.fnerr).split(':') #fnerr=['mmt-san2', 'fhs-hachi5']
  if args.s != 0:# speaker-verification
    M=S
    V=S
    verif="s"
  elif args.d != 0: #digit(text)-verification
    M=T
    V=T 
    verif="t"
  if args.sd =='s':
    M=S
    V=S
    verif="s"
  elif args.sd =='d':
    M=T
    V=T 
    verif="t"
  else:pass
  #  import pdb;pdb.set_trace(); #for debug
  #  fnr=args.dir+'/speaker-verif-result-R{}{}.dat'.format(args.R,args.FD)
#  if nRX>0:  fnrX=args.dir+'/speaker-verif-result-X-R{}{}.dat'.format(args.R,args.FD)
  method=(args.method).split(',')
  if method[0][:4]=='MFCC':
    l,m,n,E,N=method[1:][0:5] #method=MFCC,${l},${n_MFCC},${n_MFCCFB},${E_MFCC}
    E_MFCC=int(E)
    FD=''
    FDext='MFCC' #    FDext='{}F{}'.format(FD,nx)
    FDextr='MFCCl{}m{}n{}E{}N{}b{}a{}R{}'.format(l,m,n,E,N,b,_mbas[2],args.R) #    FDext='{}F{}'.format(FD,nx)
#    import pdb;pdb.set_trace(); #for debug
  elif method[0][:6]=='LPCSE1':#new20210818
    k,l,n,N=map(int,method[1:][0:4])
    FDext='SE' #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
    FDextr='SEk{}l{}n{}N{}b{}a{}R{}'.format(k,l,n,N,b,_mbas[2],args.R) #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
  elif method[0][:7]=='LPCSPTK':#new20210818
#    k,l,ns,N=map(int,method[1:][0:5])
    k,l,n,w=map(int,method[1:][0:4])
    FDext='SE' #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
    FDextr='SEk{}l{}n{}w{}N{}b{}a{}R{}'.format(k,l,n,w,N,b,_mbas[2],args.R) #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
#    FDextr='SEk{}l{}f{}w{}'.format(k,l,f,w) #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
  elif method[0][:6]=='LPCSE1':
    k,l,ns,N=map(int,method[1:][0:5])
    FDext='LPCSE1' #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
    FDextr='LPCSE1k{}l{}n{}N{}b{}a{}R{}'.format(k,l,ns,N,b,_mbas[2],args.R) #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
  elif method[0]=='N':
    N=int(method[1])
    FDext='N' #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
    FDextr='N{}'.format(N) #
  else:
    if method[0][:6]=='LPC+SE':
      k,l,FD,ns=method[1:][0:4]
      mname='LPC+SE'
      #      FDex='LPC+SE'.format(k,l,FD,ns) #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
      #      FDextr='LPC+SEk{}l{}FD{}ns{}'.format(k,l,FD,ns) #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
      #    FDext='{}ns{}'.format(FD,ns) #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
    elif method[0][:7]=='CAN2+PD':
      #    import pdb;pdb.set_trace(); #for debug
      k1,N1,a1,b1,s1,FD,nr,na,nG,sG,mel,N,a,b,s=method[1:][0:15]
      rsa='2:{}:{}:{}'.format(a,s,b) 
#      k,N,rsa,nr,na,nG,sG,mel=method[1:][0:8]
      mname='CAN2+PD'
      #      FDext='{}F{}x{}G{}x{}m{}'.format(FD,nr,na,nG,sG,mel) #    FDext='{}F{}x{}'.format(FD,nr,na)
      #      #    FDext='CAN2+PDk{}N{}rsa{}nr{}na{}nG{}mel{}'.format(k,N,rsa,nr,na,nG,sG,melFD,nr,na,nG,sG,mel) #    FDext='{}F{}x{}'.format(FD,nr,na)
      #      FDextr='CAN2+PDk{}N{}rsa{}nr{}na{}nG{}mel{}'.format(k,N,rsa,nr,na,nG,sG,melFD,nr,na,nG,sG,mel) #    FDext='{}F{}x{}'.format(FD,nr,na)
#      FDextr='{}N{}a{}b{}{}N{}R{}'.format(mname,N1,a1,b1,FDext,N,b,_mbas[2],args.R)
    if FD[0]=='r':
      FDext='{}F{}G{}x{}'.format(FD,nx,nG,sG) #    FDext='{}F{}'.format(FD,nx)
    elif FD[0]=='p':
      FDext='{}F{}x{}G{}x{}m{}'.format(FD,nr,na,nG,sG,mel) #    FDext='{}F{}x{}'.format(FD,nr,na)
    elif FD[0] in ('s', 'S'):
      FDext='{}ns{}ls{}'.format(FD,args.ns,args.ls) #    FDext='{}F{}x{}'.format(FD,nr,na)#20210616
      #  elif FD[0] in ('s', 'S','sR', 'SR'):
      #    FDext='FD{}ns{}ls{}'.format(FD,args.ns,args.ls) #    FDext='{}F{}x{}'.format(FD,nr,na)
    else:pass
    if method[0][:7]=='CAN2+PD':
      FDextr='{}N{}a{}b{}{}N{}R{}'.format(mname,N1,a1,b1,FDext,N,b,_mbas[2],args.R)
      #    FDextr='{}{}N{}b{}a{}R{}'.format(mname,FDext,N,b,_mbas[2],args.R)
    else:
      FDextr='{}{}N{}R{}'.format(mname,FDext,N,b,_mbas[2],args.R)
  fnr='{}/result-R{}{}.dat'.format(dr,args.R,FDextr)
  nRX=len(RX) if RX[0]!='0' else 0
  if nRX>0:  fnrX='{}/resultX-R{}{}.dat'.format(dr,args.R,FDextr)
  fpr=open(fnr,'w')
  if nRX>0: fprX=open(fnrX,'w')
  nS=len(S)
  nL=len(L)
  nT=len(T)
#  import pdb;pdb.set_trace(); #for debug  
  argv=sys.argv
  cmd=''
  for a in argv:#  for i,a in enumerate(argv):
    cmd+=a+' '
#    print('#start:python {}'.format(cmd))
  cmd0=cmd
  start_time=time.time()
  print('#start time:{}'.format(datetime.datetime.now()))

#  import pdb;pdb.set_trace(); #for debug
  AF=[]
  if args.AF != '_' and args.AF != 'q':
    aAF=(args.AF).split(':') # aAF=trainingFile,weight,del0-del1
    for i in range(0,len(aAF)): #
      aAFi=aAF[i].split(',')
#      import pdb;pdb.set_trace(); #for debug
      if len(aAFi)>=3:
        aAFdel=aAFi[2].split('-')
        if aAFdel[0]=='':
          AFdel=''
        elif len(aAFdel)==1:
          AFdel=[int(aAFdel[0]),int(aAFdel[0])+1]
        elif len(aAFdel)==2:
          AFdel=[int(aAFdel[0]),int(aAFdel[1])]
        else:
          AFdel=''
        AF.append([os.path.expanduser(aAFi[0]),float(aAFi[1]),AFdel])
      elif len(aAFi)>=2:
        AF.append([os.path.expanduser(aAFi[0]),float(aAFi[1]),''])
      else:
        AF.append([os.path.expanduser(aAFi[0]),1,''])
#  aAFcut=args.AFcut.split(':') #-AFcut 23-46:0:0
#  AFcut={}
#  for i in range(0,len(aAFcut)):
#    AFcuti=aAFcut[i].split('-')
#    if AFcuti[0]=='':
#      AFcut[i]=''
#    elif len(AFcuti)==1:
#      AFcut[i]=[int(AFcuti[0]),int(AFcuti[0])+1]
#    elif len(AFcuti)==2:
#      AFcut[i]=[int(AFcuti[0]),int(AFcuti[1])]
#    else:
#      AFcut[i]=''
#    for i in range(len(aAFcut),len(AF)):
#      AFcut[i]=''  
#  import pdb;pdb.set_trace(); #for debug
#  import pdb;pdb.set_trace(); #for debug
  if len(AF)>0:
#  if args.AF != '_' and args.AF != 'q':
    fbtrain='train_xy'
#    AF=map(os.path.expanduser,(args.AF).split(':'))
#    import pdb;pdb.set_trace(); #for debug
##    FtrainAF=np.array(pd.read_csv(AF[0],delim_whitespace=True,dtype=np.float64,header=None))[:,:-1]
##    import pdb;pdb.set_trace(); #for debug
##    if AFcut[0]!='':
##      FtrainAF=np.delete(FtrainAF,range(AFcut[0][0],AFcut[0][1]),1)
#    FtrainAF=np.array(pd.read_csv('{}'.format(AF[0]),delim_whitespace=True,dtype=np.float64,header=None))[:,:-1]
    for i in range(0,len(AF)):
      FtrainAF1=np.array(pd.read_csv(AF[i][0],delim_whitespace=True,dtype=np.float64,header=None))[:,:-1]
      if AF[i][2]!='': FtrainAF1=np.delete(FtrainAF1,range(AF[i][2][0],AF[i][2][1]),1)
#      import pdb;pdb.set_trace(); #for debug
#      FtrainAF1=FtrainAF1*AF[i][1]
      if AF[i][1]>=0:
        FtrainAF1=FtrainAF1*AF[i][1]
      else:
        for j in range(0,len(FtrainAF1)):
          FtrainAF1[j]=FtrainAF1[j]*(-AF[i][1])/np.linalg.norm(FtrainAF1[j])
#        FtrainAF1[j]=FtrainAF1[j]*AF[i][1]
#        FtrainAF1[i]=FtrainAF1[i]*AF[i][1]/np.linalg.norm(FtrainAF1[i])
#      FtrainAF1=np.array(pd.read_csv('{}'.format(AF[i]),delim_whitespace=True,dtype=np.float64,header=None))[:,:-1]
#      import pdb;pdb.set_trace(); #for debug
      if i==0:
        FtrainAF=FtrainAF1
      else:
        FtrainAF=np.concatenate([FtrainAF,FtrainAF1],axis=1)
  #
  for i_m,m in enumerate(M):#machine
    if args.ow == 1:
      mylib.myshell('make data-clean;mkdir -p tmp')
    else:
      print('#No data-cleaned because -ow 0')
    fbtrain='train_xy'
    fbtest='test_xy'
    fntrain='{}.dat'.format(fbtrain)
    fntest='{}.dat'.format(fbtest)
    fptrain=open(fntrain,'w')
    fptest=open(fntest,'w')
    Fall=[]
    Ftrain={}
    Ftest={}
    ytrain=[]
#    import pdb;pdb.set_trace(); #for debug

    if method[0]=='N':#all oob
      for i_r,r in enumerate(R):
        for i_v,v in enumerate(V):
          Ftrain[(v,r)]=['{}-{}{}-R{}-Fdummy.dat'.format(v,d,l,r) for d in D for l in L]
#        import pdb;pdb.set_trace(); #for debug
    elif nRX==0:#all oob
      for i_r,r in enumerate(R):
        for i_v,v in enumerate(V):
          fnq='{}/*{}*-R{}*-{}.dat'.format(dr,v,r,FDext) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
#          fnq='{}/{}-*R{}*{}.dat'.format(dr,s,r,FDext) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          if len(F)==0:
            print '#No files for {}'.format(fnq)
            quit()
          F.sort()
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
#          Fp=F
          Ftrain[(v,r)]=Fp[:]
#          import pdb;pdb.set_trace(); #for debug
          if len(F)==0:
            print('###########No files with {}'.format(fnq))
            import pdb;pdb.set_trace(); #for debug
#      import pdb;pdb.set_trace(); #for debug
    ###############
    else:
      for i_r,r in enumerate(R):
        for i_v,v in enumerate(V):
          fnq='{}/*{}*-R{}*'.format(dr,v,r,FDext) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          #fnq='{}/{}-*R{}*'.format(dr,s,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          if len(F)==0:
            print('###########No files with {}'.format(fnq))
            import pdb;pdb.set_trace(); #for debug
          F.sort()
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
          Ftrain[(v,r)]=Fp[:len(Fp)/2]
          #Ftest[(s,r)]=Fp[:len(Fp)/2]
          #Ftest[(s,r)]=Fp[len(Fp)/2:]
      for i_r,r in enumerate(RX):
        for i_v,v in enumerate(V):
          fnq='{}/*{}*-R{}*'.format(dr,v,r,FDext) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          #fnq='{}/{}-*R{}*'.format(dr,s,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          if len(F)==0:
            print('###########No files with {}'.format(fnq))
            import pdb;pdb.set_trace(); #for debug
          F.sort()
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
          #Ftrain[(s,r)]=Fp[:len(Fp)/2]
          #Ftest[(s,r)]=Fp[:len(Fp)/2]
          Ftest[(v,r)]=Fp[len(Fp)/2:]
    ###############
#    import pdb;pdb.set_trace(); #for debug
# for i_m,m in enumerate(M):#machine
    nP=0;nF=0
    for key in Ftrain.keys():
      for i_f,f in enumerate(Ftrain[key]):
        #        import pdb;pdb.set_trace(); #for debug
        v,r,v2=vrv2_f(f)
        #        s,r,s2=vrv2_f(f)
        #        import pdb;pdb.set_trace(); #for debug
        if v == m:
          ytarget=1
          nP+=1
        else:#s != m
          if m!=v2: 
            ytarget=-1
            nF+=1
          else:
            ytarget=0 #don't train
            print('#m{}:{} excludes {} from negative examples.'.format(i_m,m,f));
            
        if ytarget !=0:
          if method[0]=='MFCC':
#            import pdb;pdb.set_trace(); #for debug
            x1=np.array(pd.read_csv('{}/{}'.format(dr,f),delim_whitespace=True,dtype=np.float64,header=None))
            if E_MFCC==0:
              x1=x1[:,:-1]
            else:pass
            x=x1.mean(axis=0)
            #              x=np.array(pd.read_csv('{}/{}'.format(dr,f),delim_whitespace=True,dtype=np.float64,header=None))
            #                       if method[0]=='MFCC' and E_MFCC==0:
          elif method[0]=='LPCSE1':
#            import pdb;pdb.set_trace(); #for debug
#            print("check fn={}".format('{}/{}'.format(dr,f)))
            x1=np.array(pd.read_csv('{}/{}'.format(dr,f),delim_whitespace=True,dtype=np.float64,header=None))
            x=x1.mean(axis=0)
          elif method[0]=='N':
#            import pdb;pdb.set_trace(); #for debug
            x=np.array([1])
          else:
            x=np.array(pd.read_csv('{}/{}'.format(dr,f),delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
#          import pdb;pdb.set_trace(); #for debug
          if math.isnan(x[0]):
            import pdb;pdb.set_trace(); #for debug
          if args.lx[0]=='1':
            x=np.log1p(x)
            #            x=np.log10(0.01+x)
            #            x=np.log10(x)
          normx=1
          if args.nlz=='norm':
            normx=np.linalg.norm(x)
          elif args.nlz=='max':
            normx = x.max()
          if nx>0:
            x = x/normx
          if math.isnan(x[0]):
            print('### Error: nan arize for m={},v={}'.format(m,v));
            import pdb;pdb.set_trace(); #for debug
          else:
            Fall.append(f) #Fall=Fperm??
            for i in range(len(x)):
              fptrain.write('%e ' % (x[i]))#            fptrain.write('%.10e ' % (x[i]))
            if fntrain_check==1:
              fptrain.write('{} {}\n'.format(ytarget,f))
            else:
              fptrain.write('{}\n'.format(ytarget))
            ytrain.append(ytarget)
    n_train=len(Fall)
    print('#n_train={},nP={},nF={}'.format(n_train,nP,nF))
    fptrain.close()
    fptest.close()
    
#    import pdb;pdb.set_trace(); #for debug
    #  for i_m,m in enumerate(M):#machine
    if i_m == 0:
      fntrain_m='{}/{}{}'.format(dr,FDext,fntrain) #same x,different y for different m?
      cmd='cp {} {}'.format(fntrain,fntrain_m) #
      if fntrain_check==1:
        fntrain_m='{}/{}{}_{}.dat'.format(dr,FDext,fbtrain,m) #same x,different y for different m
        cmd='cp {} {}'.format(fntrain,fntrain_m) #
      else:pass
      mylib.myshell(cmd)
      cmd0='export AF={}/{}{}'.format(args.dr,FDext,fntrain)
      cmd=('echo "{}">tmp/AF.env'.format(cmd0))
      mylib.myshell(cmd)
      print('#Type "source tmp/AF.env"\n#  or "{}"'.format(cmd0))
#      print('#AF={}/{} #saved in ${}AF{}{} '.format(args.dr,FDext,'{','}',fntrain))
#      print('#saved {} as AF={}/{}'.format(fntrain_m,dr,FDext))
#      print('#saved {} as AF={}/{}'.format(fntrain_m,dr,FDext))
      if args.AF=='q':
        if fntrain_check==1:
          continue;
        else:
          exit(0)
      else:pass
    else:pass
      #    mylib.myshell('cp {} {}/{}'.format(fntest,dr,fntest))
    k=len(x)

    if args.AF !='_':
      #      AF=(args.AF).split(':')
      ##      import pdb;pdb.set_trace(); #for debug
      #      Ftrain=np.array(pd.read_csv('{}{}.dat'.format(AF[0],fbtrain),delim_whitespace=True,dtype=np.float64,header=None))
      #      for i in range(0,len(AF)):
      #        Ftrain1=np.array(pd.read_csv('{}{}.dat'.format(AF[i],fbtrain),delim_whitespace=True,dtype=np.float64,header=None))
      #        Ftrain=np.concatenate([Ftrain[:,:-1],Ftrain1],axis=1)
      
      #      import pdb;pdb.set_trace(); #for debug
      #      Ftrain1=pd.read_csv(fntrain,delim_whitespace=True,dtype=np.str,header=None) #current real target
      Ftrain1=np.array(pd.read_csv(fntrain,delim_whitespace=True,dtype=np.float64,header=None)) #current target (./train_xy.dat)
      if method[0]=='N':
        Ftrain1=np.delete(Ftrain1,0,1)
#      import pdb;pdb.set_trace(); #for debug
      Ftrain=np.concatenate([FtrainAF,Ftrain1],axis=1)

      df=pd.DataFrame(Ftrain)
      df.to_csv('{}'.format(fntrain),index=False,sep=' ',header=None)
      k=Ftrain.shape[1]-1
    else:pass
    #    import pdb;pdb.set_trace(); #for debug
    #    k=Ftrain.shape[1]-1            
    ###trainig and test of oob
                              
    cmd='ensrs {} {} {}-{} k:{} ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 nop:1 bg:/dev/null'.format(fntrain,args.mbas,N,N,k)
#    cmd='ensrs {}.dat {} {}-{} k:{} ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 nop:1 bg:/dev/null >> ./tmp/ensrs.log'.format(fntrain,args.mbas,args.N,args.N,k)
#    sprintf(com,"ensrs %sxy.dat %s %d-%d:1 k:%d ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null > /dev/null",fntrain,mbas,N,N,k);
#    import pdb;pdb.set_trace(); #for debug
    print 'Executing1 {}'.format(cmd)
    fnpred='predict+oob.dat' #direct pred
    fnoob='pred+oob-{}.dat'.format(m) #oob    pred
#    import pdb;pdb.set_trace(); #for debug
    while True: #??
      sys.stdout.flush()
      mylib.myshell(cmd)
      if os.path.exists(os.path.expanduser(fnpred)):
        break
      print '#Try creating {} again!'.format(fnpred)
#      time.sleep(1)
    mylib.myshell('cp {} {}'.format(fnpred,fnoob)) #oob-output

#    sys.stdout.flush()
#    mylib.myshell(cmd)
##    mylib.myshell('if [ ! -e {} ]; then sleep 2 ; fi ; cp {} {}'.format(fnpred,fnpred,fnoob)) #oob-output
#    mylib.myshell('while [ ! -e {} ]; do echo "#Waiting creation of {}."; sleep 1 ; done; cp {} {}'.format(fnpred,fnpred,fnpred,fnoob)) #oob-output
###test with learned
    if nRX>0:
      cmd='ensrs {} {} {}-{}:1 k:{} ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:{}.dat >> ./tmp/ensrs.log'.format(fntrain,args.mbas,N,N,k,fntest);
      print '#Executing2 {}'.format(cmd)
      sys.stdout.flush()
      mylib.myshell(cmd)
    else:pass
###speaker verification
#    import pdb;pdb.set_trace(); #for debug
    yoob3=np.array(pd.read_csv(fnoob,delim_whitespace=True,header=None).ix[:,0:2]).astype('float64')
    yoob=yoob3[:,0]
    yt=yoob3[:,2]
#    yoob=np.array(pd.read_csv(fnoob,delim_whitespace=True,dtype=np.float64,header=None)[0:3])
    if nRX>0:#???    if nRX>=0:#???
#      import pdb;pdb.set_trace(); #for debug
      ypred=np.array(pd.read_csv(fnpred,delim_whitespace=True,header=None).ix[:,0]).astype('float64')
      yp=np.concatenate([yoob,ypred],axis=0)
    else:
      yp=yoob
#    import pdb;pdb.set_trace(); #for debug
#    print "m,Fall=",m,Fall
    y=[]
    vv=[] #
    TP=TN=FP=FN=0;
    n_Fall=len(Fall)
    for i_f,f in enumerate(Fall):
      v,r,v2=vrv2_f(f) #  s,r,s2=srs2_f(f)
      if m == v or m == v2: #yp should be positive
        y.append(1)
        if yp[i_f] > 0: #Positive
          TP+=1
          vv.append('TP')
          if yt[i_f] <= 0: 
            print m,v,r,v2,yoob3[i_f]
#            import pdb;pdb.set_trace(); #for debug
            print 'TP but FP yt<=0'
        else:
          FN+=1
          vv.append('FN')
          print('FN:{} yp={} m={} v={} v2={}'.format(f,yp[i_f],m,v,v2))
          if yt[i_f] <=0: 
            print m,v,r,v2,yoob3[i_f]
#            import pdb;pdb.set_trace(); #for debug
            print 'FN but TN yt<0'
      else: #yp should be Negative
        y.append(-1)
        if yp[i_f] > 0: #Positive
          FP+=1
          vv.append('FP')
          print('FP:{} yp={} m={} v={} v2={}'.format(f,yp[i_f],m,v,v2))
          if yt[i_f] >0:
            print m,v,r,v2,yoob3[i_f]
#            import pdb;pdb.set_trace(); #for debug
            print 'FP but TP yt>0'
        else:
          TN+=1
          vv.append('TN')
          if yt[i_f] >0: 
            print m,v,r,v2,yoob3[i_f]
#            import pdb;pdb.set_trace(); #for debug
            print 'TN but FN yt<=0'
      if i_f == n_train-1 or i_f == n_Fall-1:
        ER  =(FP+FN)
        n   =(TP+TN+FP+FN)
        TPFN=(TP+FN)
        FPTN=(FP+TN)
        TPR=100.*TP/float(TPFN) if TPFN >0 else 0;
        FNR=100.*FN/float(TPFN) if TPFN >0 else 0;
        FPR=100.*FP/float(FPTN) if FPTN >0 else 0;
        TNR=100.*TN/float(FPTN) if FPTN >0 else 0;
        ERR=100.*ER/float(n) if n>0 else 0;
        ret='{:.2f} {:.2f} {:.2f} {:.2f} {:.2f} = {} {} {} {} {} {} {} {} {} {} {} #TP,TN,FP,FN,ER=.#n,m,R,RX,mbas,N'.format(TPR,TNR,FPR,FNR,ERR,TP,TN,FP,FN,ER,n,m,args.R,args.RX,args.mbas,N)
        if '1' in DISP: print(ret) ##DISP??
#        import pdb;pdb.set_trace(); #for debug
        if i_f == n_train-1:
          fpr.write('{}\n'.format(ret))
        elif nRX>0:
          fprX.write('{}\n'.format(ret))
        TP=TN=FP=FN=0;
#        import pdb;pdb.set_trace(); #for debug
      fpr.flush()

#    import pdb;pdb.set_trace(); #for debug
    elapsed_time=time.time()-start_time
    etime='{:.2f}s({})'.format(elapsed_time,str(datetime.timedelta(seconds=elapsed_time))[:-3])
    print('#elapsed time:{}@{} for m{}:{}'.format(etime,datetime.datetime.now(),i_m,m))
    if DISP[2]=='1':
      for i_f,f in enumerate(Fall):
        print "{} {:+.2f} {} {} {} #yp y f m ytrain={}".format(f,yp[i_f],y[i_f],m,vv[i_f],ytrain[i_f])
    sys.stdout.flush()
  #    import pdb;pdb.set_trace(); #for debug
  #    sprintf(com,"%.2f %.2f %.2f %.2f %.3e %d %d #TP,TN,FP,FN,ERR,n,sm%d",TP,TN,FP,FN,ER,n,sm,sm);
#  fpr.write('#result of cmd="{}"\n'.format(cmd0))
#  fpr.write('export #AF={}/{} #saved in ${}AF{}{}\n'.format(args.dr,FDext))
  fpr.close()
  if nRX>0: fprX.close()
  #  import pdb;pdb.set_trace(); #for debug
  cmd='cat {}|awk \'BEGIN{{n=0;TP=TN=FP=FN=ERR=0}}{{TP+=$7;TN+=$8;FP+=$9;FN+=$10;ERR+=$11;n+=$12;}}END{{RC=TP/(TP+FN);PR=TP/(TP+FP);F=2*RC*PR/(RC+PR);printf("#TP%.2f TN%.2f FP%.2f FN%.2f ER%.2f RC%.2f PR%.2f F%.2f n%d k{} {} {}\\n",100.*TP/(TP+FN),100.*TN/(FP+TN),100.*FP/(FP+TN),100.*FN/(TP+FN),100.*ERR/n,100.*RC,100.*PR,100.*F,n)}}\'>>{}'.format(fnr,k,FDextr,etime,fnr)
#  cmd='cat {}|awk \'BEGIN{{n=0;TP=TN=FP=FN=ERR=0}}{{TP+=$7;TN+=$8;FP+=$9;FN+=$10;ERR+=$11;n+=$12;}}END{{RC=TP/(TP+FN);PR=TP/(TP+FP);F=2*RC*PR/(RC+PR);printf("#TP%.3f TN%.3f FP%.3f FN%.3f ER%.3f RC%.3f PR%.3f F%.3f n%d k{} {} {}\\n",TP/(TP+FN),TN/(FP+TN),FP/(FP+TN),FN/(TP+FN),ERR/n,RC,PR,F,n)}}\'>>{}'.format(fnr,k,FDextr,etime,fnr)
#  cmd='cat {}|awk \'BEGIN{{n=0;TP=TN=FP=FN=ERR=0}}{{TP+=$7;TN+=$8;FP+=$9;FN+=$10;ERR+=$11;n+=$12;}}END{{RC=TP/(TP+FN);PR=TP/(TP+FP);F=2*RC*PR/(RC+PR);printf("#TP%.3f TN%.3f FP%.3f FN%.3f ER%.3f RC%.3f PR%.3f F%.3f n%d k{} {}lx{}sd{} {}\\n",TP/(TP+FN),TN/(FP+TN),FP/(FP+TN),FN/(TP+FN),ERR/n,RC,PR,F,n)}}\'>>{}'.format(fnr,k,FDextr,args.lx,args.sd,etime,fnr)
#
#  cmd='cat {}'.format(fnr)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n+=$13;TP+=$7;TN+=$8;FP+=$9;FN+=$10;ERR+=$11}END{RC=TP/(TP+FN);PR=TP/(TP+FP);F=2*RC*PR/(RC+PR);printf("#TP%.3f TN%.3f FP%.3f FN%.3f ER%.3f RC%.3f PR%.3f F%.3f '+'k{} {} {}\\n"'.format(k,FD[0],etime)+',TP/(TP+FN),TN/(FP+TN),FP/(FP+TN),FN/(TP+FN),ERR/n,RC,PR,F)}\''+ '>>{}'.format(fnr)
#  cmd='cat {}'.format(fnr)
#  +"|awk 'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n+=$13;TP+=$7;TN+=$8;FP+=$9;FN+=$10;ERR+=$11}END{RC=TP/(TP+FN);PR=TP/(TP+FP);F=2*RC*PR/(RC+PR);"
#  +'printf("#TP%.3f TN%.3f FP%.3f FN%.3f ER%.3f RC%.3f PR%.3f F%.3f '
#  +'k{} {} {}\\n"'.format(k,FD[0],etime)
#  +",TP/(TP+FN),TN/(FP+TN),FP/(FP+TN),FN/(TP+FN),ERR/n,RC,PR,F)}'"
#  + '>>{}'.format(fnr)
#
#  cmd='cat {}|awk \''.format(fnr)
#  +'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n+=$13;TP+=$7;TN+=$8;FP+=$9;FN+=$10;ERR+=$11}END{RC=TP/(TP+FN);PR=TP/(TP+FP);F=2*RC*PR/(RC+PR);printf("#TP%.3f TN%.3f FP%.3f FN%.3f ER%.3f RC%.3f PR%.3f F%.3f'
#  +'k{} {} {}\\n",TP/(TP+FN),TN/(FP+TN),FP/(FP+TN),FN/(TP+FN),ERR/n,RC,PR,F)}'.format(k,FD[0],etime)
#  +"'>>{}'.format(fnr)
#
#  cmd='cat {}'.format(fnr)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n+=$13;TP+=$7;TN+=$8;FP+=$9;FN+=$10;ERR+=$11}END{RC=TP/(TP+FN);PR=TP/(TP+FP);F=2*RC*PR/(RC+PR);printf("%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f #TP TN FP FN ER RC PR F#'+' k{} FD:{} {}\\n"'.format(k,args.FD,etime)+',TP/n,TN/n,FP/n,FN/n,ERR/n,RC,PR,F)}\''+ '>>{}'.format(fnr)
#  print cmd
  mylib.myshell(cmd)
#  cmd='cat {} #oob prediction of training data k{} {} {}'.format(fnr,k,args.FD,etime)
  mylib.myshell('echo "python {}" >> {}'.format(cmd0,fnr))
  mylib.myshell('echo "export AF={}/{}{}" >> {}'.format(args.dr,FDext,fntrain,fnr))
#  mylib.myshell('echo "#export AF={}/{} #saved in \${}AF{}{}" >> {}\n'.format(args.dr,FDext,'{','}',fntrain,fnr))
  cmd='cat {}'.format(fnr)
  mylib.myshell(cmd)
  print('\n#Do "cat {}"\nto see the result'.format(fnr,cmd))
  if nRX>0:
    cmd='cat {}'.format(fnrX)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n++;TP+=$1;TN+=$2;FP+=$3;FN+=$4;ERR+=$5}END{printf("%.2f %.2f %.2f %.2f %.2f %d #mean TP TN FP FN ERR n'+' k{}sd{} {}\\n"'.format(k,FDextr,args.sd,etime)+',TP/n,TN/n,FP/n,FN/n,ERR/n,n)}\''+ '>>{}'.format(fnrX)
    mylib.myshell(cmd)
    cmd='cat {} #prediction of test data'.format(fnrX)
    print cmd
    mylib.myshell(cmd)
#    print('#result of cmd0="{}"\n'.format(cmd0))
