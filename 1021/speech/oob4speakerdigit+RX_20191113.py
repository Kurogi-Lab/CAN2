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
  return i_s #for speaker recog

def srs2_f(f): # 
  fl=f.split('-')
  s=fl[0]
  if len(fl)==6: #e.g.fhs-go1-mmt-nana10-R0.8-p.dat -> fms-ni2-R0.8-mmt-san4-pP1.dat
    r=fl[4][1:]
    s2=fl[3] #-> fhs-go1-mmt-nana10-R0.8-p.dat -> fms-ni2-R0.8-mmt-san4-pP1.dat 
  elif len(fl)==4:#e.g. mym-kyu10-R1-p.dat
    r='1'
    s2=s
  return s,r,s2

if __name__ == "__main__":
#oob4speakerdigit+sX_2018 sp:fhs:fms tx:zero:ichi ntxi:9 k:36 mbas:$mbas dir:$dir1 dir2:$dir2 s:-1 N:${N} sX:${sX}
#oob4speakerdigit+ sp:fhs:fms:mkk:mko:mmt:mnh:mym tx:zero:ichi:ni:san:yon:go:roku:nana:hachi:kyu ntxi:10 k:36 mbas:2:300:1.6:1 dir:$dira s:-1 N:40

  parser = argparse.ArgumentParser(description='speech normalize')
  parser.add_argument('-sp', default='fhs:fms:mkk:mko:mmt:mnh:mym', type=str,   help='speaker')
  parser.add_argument('-tx', default='zero:ichi:ni:san:si:go:roku:nana:hachi:kyu', type=str,   help='text')
  parser.add_argument('-ntxi', default=10, type=int,   help='number of texts')
  parser.add_argument('-k', default=36, type=int, help='embedding dimensionk')
  parser.add_argument('-N', default=40, type=int,   help='number of units for verification')
  parser.add_argument('-mbas', default='2:300:1.6:1', type=str,   help='mbas:2:nbag:bagsize_ratio:1')
  parser.add_argument('-s', default=0, type=int,   help='-1 for all speaker verification')
  parser.add_argument('-d', default=0, type=int,   help='-1 for all digit verification')
  parser.add_argument('-sX', default=-1, type=int,   help='excluded speaker')
  parser.add_argument('-dr', default='.', type=str,   help='directory of training data')
  parser.add_argument('-R', default='0.8', type=str,   help='mag r1:r2:...:rn for learning and test')
  parser.add_argument('-RX', default='0', type=str,   help='mag r1:r2:...:rn for test')
  parser.add_argument('-FD', default='pP1', type=str, choices=['pP1','pPc','pPcb','rP1','rPc','rPcb'],help='Features of data')
  parser.add_argument('-nr', default=2, type=int,   help='number of divisions for magnitude-axis in pole space')
  parser.add_argument('-na', default=18, type=int,   help='number of divisions for angle-axis in pole space')
  parser.add_argument('-nx', default=7, type=int,   help='number of divisions onx-axis in pole space')
  parser.add_argument('-nG', default=13, type=int,   help='Gaussian Kernel size')
  parser.add_argument('-sG', default=2, type=float,   help='Gaussian Kernel sigma')
  parser.add_argument('-L', default='1:2:3:4:5:6:7:8:9:10', type=str,   help='mag r1:r2:...:rn for learning and test')
  parser.add_argument('-OmL', default='0', type=str,   help='Omit Learning')
  parser.add_argument('-ow', default=1, type=int,   help='Overwite files if ow=1, omit otherwise.')
  parser.add_argument('-mel', default=0, type=int,   help='1 for use mel frequency.')
  parser.add_argument('-DISP', default='1', type=str,   help='DISP[0]==1 to make files, DISP[1]==1 to display')
  parser.add_argument('-nlz', default='1', type=str, choices=['max','norm','1'], help='normalize by norm, max, 1')
  np.random.seed(seed=32)
  args = parser.parse_args()
  S=(args.sp).split(':') #speakers
  T=(args.tx).split(':') #text
  R=(args.R).split(':') #lamgda:SN ratio
  RX=(args.RX).split(':') #lamgda:SN ratio for test
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
  DISP=args.DISP+'00000'
#  L=range(1,args.ntxi+1) #date
  _mbas=map(float,(args.mbas).split(':'))
  mbas=[]
  mbas.append(int(_mbas[0]))
  mbas.append(int(_mbas[1]))
  mbas.append(float(_mbas[2]))
  mbas.append(int(_mbas[3]))
  b=mbas[1] #method,b,a,seed=map(int,(args.mbas).split(':'))
  fnerr=['mmt-san2', 'fhs-hachi5']
  if args.s != 0:
    M=S
  elif args.d != 0:
    M=T
#  import pdb;pdb.set_trace(); #for debug
#  fnr=args.dir+'/speaker-verif-result-R{}{}.dat'.format(args.R,args.FD)
#  fnrX=args.dir+'/speaker-verif-result-X-R{}{}.dat'.format(args.R,args.FD)
  if FD[0]=='r':
    FDext='{}F{}G{}x{}'.format(FD,nx,nG,sG) #    FDext='{}F{}'.format(FD,nx)
  elif FD[0]=='p':
    FDext='{}F{}x{}G{}x{}m{}'.format(FD,nr,na,nG,sG,mel) #    FDext='{}F{}x{}'.format(FD,nr,na)

  FDextr='{}N{}b{}a{}R{}'.format(FDext,args.N,b,_mbas[2],args.R)
  fnr='{}/result-{}.dat'.format(dr,FDextr)
  fnrX='{}/resultX-{}.dat'.format(dr,FDextr)
#  fnr='{}/result-R{}{}.dat'.format(dr,args.R,FDextr)
#  fnrX='{}/resultX-R{}{}.dat'.format(dr,args.R,FDextr)
  fpr=open(fnr,'w')
  fprX=open(fnrX,'w')
  nS=len(S)
  nL=len(L)
  nT=len(T)
  nRX=len(RX) if RX[0]!='0' else 0
#  import pdb;pdb.set_trace(); #for debug  
  argv=sys.argv
  cmd=''
  for a in argv:#  for i,a in enumerate(argv):
    cmd+=a+' '
  print('#start:{}'.format(cmd))

  start_time=time.time()
  print('#start time:{}'.format(datetime.datetime.now()))
  for i_m,m in enumerate(M):
    if args.ow == 1:
      mylib.myshell('make data-clean;mkdir -p tmp')
    else:
      print('#No data-cleaned because -ow 0')
    fntrain='train_xy'
    fntest='test_xy'
    fptrain=open(fntrain+'.dat','w')
    fptest=open(fntest+'.dat','w')
    Fall=[]
    Ftrain={}
    Ftest={}
    ytrain=[]
    if nRX==0:#all oob
      for i_r,r in enumerate(R):
        for i_s,s in enumerate(S):
          fnq='{}/{}-*R{}*{}.dat'.format(dr,s,r,FDext) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
          Ftrain[(s,r)]=Fp[:]
          if len(F)==0:
            print('###########No files with {}'.format(fnq))
            import pdb;pdb.set_trace(); #for debug
    else:
      for i_r,r in enumerate(R):
        for i_s,s in enumerate(S):
          fnq='{}/{}-*R{}*'.format(dr,s,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          if len(F)==0:
            print('###########No files with {}'.format(fnq))
            import pdb;pdb.set_trace(); #for debug
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
          Ftrain[(s,r)]=Fp[:len(Fp)/2]
#          Ftest[(s,r)]=Fp[:len(Fp)/2]
#          Ftest[(s,r)]=Fp[len(Fp)/2:]
      for i_r,r in enumerate(RX):
        for i_s,s in enumerate(S):
          fnq='{}/{}-*R{}*'.format(dr,s,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          if len(F)==0:
            print('###########No files with {}'.format(fnq))
            import pdb;pdb.set_trace(); #for debug
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
#          Ftrain[(s,r)]=Fp[:len(Fp)/2]
#          Ftest[(s,r)]=Fp[:len(Fp)/2]
          Ftest[(s,r)]=Fp[len(Fp)/2:]
    for key in Ftrain.keys():
      for i_f,f in enumerate(Ftrain[key]):
        s,r,s2=srs2_f(f)
        if s == m:
          ytarget=1
        else:#s != m
          if m!=s2: 
            ytarget=-1
          else:
            ytarget=0 #don't train
            print('#m{}:{} excludes {} from negative examples.'.format(i_m,m,f));
        if ytarget !=0:
          x=np.array(pd.read_csv('{}/{}'.format(dr,f),delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
          if args.nlz=='norm':
            x /= np.linalg.norm(x)
          elif args.nlz=='max':
            x /= x.max()
          Fall.append(f) #Fall=Fperm??
          for i in range(len(x)):
            fptrain.write('%e ' % (x[i]))
          fptrain.write('{}\n'.format(ytarget))
          ytrain.append(ytarget)

    n_train=len(Fall)
    print('#n_train={}'.format(n_train))

#12345678901234567890
    fptrain.close()
    fptest.close()
#    import pdb;pdb.set_trace(); #for debug
    k=len(x)
###trainig and test of oob
    cmd='ensrs {}.dat {} {}-{} k:{} ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null >> ./tmp/ensrs.log'.format(fntrain,args.mbas,args.N,args.N,k)
#    sprintf(com,"ensrs %sxy.dat %s %d-%d:1 k:%d ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null > /dev/null",fntrain,mbas,N,N,k);
    print 'Executing1 {}'.format(cmd)
#    import pdb;pdb.set_trace(); #for debug
    sys.stdout.flush()
    mylib.myshell(cmd)
    fnpred='predict+oob.dat' #direct pred
    fnoob='pred+oob-{}.dat'.format(m) #oob    pred
    mylib.myshell('cp {} {}'.format(fnpred,fnoob)) #oob-output
###test with learned
    if nRX>0:
      cmd='ensrs {}.dat {} {}-{}:1 k:{} ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:{}.dat >> ./tmp/ensrs.log'.format(fntrain,args.mbas,args.N,args.N,k,fntest);
      print '#Executing2 {}'.format(cmd)
      sys.stdout.flush()
      mylib.myshell(cmd)

###speaker verification
    yoob=np.array(pd.read_csv(fnoob,delim_whitespace=True,header=None).ix[:,0]).astype('float64')
#    yoob=np.array(pd.read_csv(fnoob,delim_whitespace=True,dtype=np.float64,header=None)[0:3])
    if nRX>=0:
#      import pdb;pdb.set_trace(); #for debug
      ypred=np.array(pd.read_csv(fnpred,delim_whitespace=True,header=None).ix[:,0]).astype('float64')
      yp=np.concatenate([yoob,ypred],axis=0)
    else:
      yp=yoob
#    print "m,Fall=",m,Fall
    y=[]
    v=[]
    TP=TN=FP=FN=0;
    n_Fall=len(Fall)
    for i_f,f in enumerate(Fall):
      s,r,s2=srs2_f(f)
      if m == s or m == s2: #yp should be positive
        y.append(1)
        if yp[i_f] > 0: #Positive
          TP+=1
          v.append('TP')
        else:
          FN+=1
          v.append('FN')
          print('FN:{} yp={} m={} s={} s2={}'.format(f,yp[i_f],m,s,s2))
      else: #yp should be Negative
        y.append(-1)
        if yp[i_f] > 0: #Positive
          FP+=1
          v.append('FP')
          print('FP:{} yp={} m={} s={} s2={}'.format(f,yp[i_f],m,s,s2))
        else:
          TN+=1
          v.append('TN')
      if i_f == n_train-1 or i_f == n_Fall-1:
        ER  =(FP+FN)
        n   =(TP+TN+FP+FN)
        TPFN=(TP+FN)
        FPTN=(FP+TN)
        fTP=TP/float(TPFN) if TPFN >0 else 0;
        fFN=FN/float(TPFN) if TPFN >0 else 0;
        fFP=FP/float(FPTN) if FPTN >0 else 0;
        fTN=TN/float(FPTN) if FPTN >0 else 0;
        fER=ER/float(n) if n>0 else 0;
        ret='{:.3f} {:.3f} {:.3f} {:.3f} {:.3f} = {} {} {} {} {} # {} {} {} {} {} {} #TP,TN,FP,FN,ER=...#n,m,R,RX,mbas,N'.format(fTP,fTN,fFP,fFN,fER,TP,TN,FP,FN,ER,n,m,args.R,args.RX,args.mbas,args.N)
        if '1' in DISP: print(ret) ##DISP??
#        import pdb;pdb.set_trace(); #for debug
        if i_f == n_train-1:
          fpr.write('{}\n'.format(ret))
        elif nRX>0:
          fprX.write('{}\n'.format(ret))
        TP=TN=FP=FN=0;
      fpr.flush()

    elapsed_time=time.time()-start_time
    etime='{:.3f}s({})'.format(elapsed_time,str(datetime.timedelta(seconds=elapsed_time))[:-3])
    print('#elapsed time:{}@{} for m{}:{}'.format(etime,datetime.datetime.now(),i_m,m))
    if DISP[2]=='1':
      for i_f,f in enumerate(Fall):
        print "{} {:+.2f} {} {} {} #yp y f m ytrain={}".format(f,yp[i_f],y[i_f],m,v[i_f],ytrain[i_f])
    sys.stdout.flush()
  #    import pdb;pdb.set_trace(); #for debug
  #    sprintf(com,"%.3f %.3f %.3f %.3f %.3e %d %d #TP,TN,FP,FN,ERR,n,sm%d",TP,TN,FP,FN,ER,n,sm,sm);
  fpr.close()
  fprX.close()
  #  import pdb;pdb.set_trace(); #for debug
  cmd='cat {}|awk \'BEGIN{{n=0;TP=TN=FP=FN=ERR=0}}{{n+=$13;TP+=$7;TN+=$8;FP+=$9;FN+=$10;ERR+=$11}}END{{RC=TP/(TP+FN);PR=TP/(TP+FP);F=2*RC*PR/(RC+PR);printf("#TP%.3f TN%.3f FP%.3f FN%.3f ER%.3f RC%.3f PR%.3f F%.3f k{} {} {}\\n",TP/(TP+FN),TN/(FP+TN),FP/(FP+TN),FN/(TP+FN),ERR/n,RC,PR,F)}}\'>>{}'.format(fnr,k,FDextr,etime,fnr)
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
  print cmd
  mylib.myshell(cmd)
#  cmd='cat {} #oob prediction of training data k{} {} {}'.format(fnr,k,args.FD,etime)
  cmd='cat {}'.format(fnr)
  print('#Do "{}" to see the result'.format(cmd))
  mylib.myshell(cmd)
  if nRX>0:
    cmd='cat {}'.format(fnrX)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n++;TP+=$1;TN+=$2;FP+=$3;FN+=$4;ERR+=$5}END{printf("%.3f %.3f %.3f %.3f %.3f #mean TP TN FP FN ERR'+' k{} {}\\n"'.format(k,FDextr,etime)+',TP/n,TN/n,FP/n,FN/n,ERR/n)}\''+ '>>{}'.format(fnrX)
    mylib.myshell(cmd)
    cmd='cat {} #prediction of test data'.format(fnrX)
    print cmd
    mylib.myshell(cmd)
