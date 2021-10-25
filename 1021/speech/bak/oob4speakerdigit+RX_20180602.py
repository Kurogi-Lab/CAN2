import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
import math
import subprocess
import glob

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
  if len(fl)==6: #e.g.fhs-go1-mmt-nana10-R0.8-p.dat
    r=fl[4][1:]
    s2=fl[2]
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
  parser.add_argument('-k', default=36, type=int,   help='k')
  parser.add_argument('-N', default=40, type=int,   help='number of units for verification')
  parser.add_argument('-mbas', default='2:300:1.6:1', type=str,   help='mbas:2:nbag:bagsize_ratio:1')
  parser.add_argument('-s', default=0, type=int,   help='-1 for all speaker verification')
  parser.add_argument('-d', default=0, type=int,   help='-1 for all digit verification')
  parser.add_argument('-sX', default=-1, type=int,   help='excluded speaker')
  parser.add_argument('-dir', default='.', type=str,   help='directory of data')
  parser.add_argument('-R', default='0.8', type=str,   help='mag r1:r2:...:rn for learning and test')
  parser.add_argument('-RX', default='0', type=str,   help='mag r1:r2:...:rn for test')
  parser.add_argument('-L', default='1:2:3:4:5:6:7:8:9:10', type=str,   help='mag r1:r2:...:rn for learning and test')
  parser.add_argument('-OmL', default='0', type=str,   help='Omit Learning')
  np.random.seed(seed=32)
  args = parser.parse_args()
  S=(args.sp).split(':') #speakers
  T=(args.tx).split(':') #text
  R=(args.R).split(':') #lamgda:SN ratio
  RX=(args.RX).split(':') #lamgda:SN ratio for test
  L=(args.L).split(':') #text
  sX=args.sX
#  L=range(1,args.ntxi+1) #date
  _mbas=map(float,(args.mbas).split(':'))
  mbas=[]
  mbas.append(int(_mbas[0]))
  mbas.append(int(_mbas[1]))
  mbas.append(float(_mbas[2]))
  mbas.append(int(_mbas[3]))
  b=mbas[1] #method,b,a,seed=map(int,(args.mbas).split(':'))
#  y=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float32,header=None)).reshape((-1,))
  fnerr=['mmt-san2', 'fhs-hachi5']
  if args.s != 0:
    M=S
  elif args.d != 0:
    M=T
#  import pdb;pdb.set_trace(); #for debug
  fnr=args.dir+'/speaker-verif-result.dat'
  fnrX=args.dir+'/speaker-verif-result-X.dat'
#  fnr=args.dir+'/oob4sd-result.dat'
  fpr=open(fnr,'w')
  fprX=open(fnrX,'w')
  nS=len(S)
  nL=len(L)
  nT=len(T)
  nRX=len(RX) if RX[0]!='0' else 0
  for i_m,m in enumerate(M):
    myshell('make data-clean')
    fntrain='train_xy'
    fntest='test_xy'
#    if args.OmL == '0':
#      myshell('make data-clean')
#    fntrain='train-{}.dat'.format(m)
#    fntest='test-{}.dat'.format(m)
    fptrain=open(fntrain+'.dat','w')
    fptest=open(fntest+'.dat','w')
    Fall=[]
    Ftrain={}
    Ftest={}
    ytrain=[]
    if nRX==0:#all oob
      for i_r,r in enumerate(R):
        for i_s,s in enumerate(S):
          fnq='{}/{}-*R{}*'.format(args.dir,s,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
          Ftrain[(s,r)]=Fp[:]
#          Ftrain[(s,r)]=Fp[:len(Fp)/2]
#          Ftest[(s,r)]=Fp[len(Fp)/2:]
#          fnq='{}/{}-*R{}*'.format(args.dir,s,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
#          Ftrain[(s,r)]=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
    else:
      for i_r,r in enumerate(R):
        for i_s,s in enumerate(S):
          fnq='{}/{}-*R{}*'.format(args.dir,s,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
          Ftrain[(s,r)]=Fp[:len(Fp)/2]
#          Ftest[(s,r)]=Fp[:len(Fp)/2]
#          Ftest[(s,r)]=Fp[len(Fp)/2:]
      for i_r,r in enumerate(RX):
        for i_s,s in enumerate(S):
          fnq='{}/{}-*R{}*'.format(args.dir,s,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
          F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
          np.random.seed(seed=32)
          Fp=np.random.permutation(F)
#          Ftrain[(s,r)]=Fp[:len(Fp)/2]
#          Ftest[(s,r)]=Fp[:len(Fp)/2]
          Ftest[(s,r)]=Fp[len(Fp)/2:]

    for key in Ftrain.keys():
#      import pdb;pdb.set_trace(); #for debug
      for i_f,f in enumerate(Ftrain[key]):
#        print "train key=",key,f,i_f
#        print '#ftrain={}'.format(args.dir+'/'+f)
        x=np.array(pd.read_csv(args.dir+'/'+f,delim_whitespace=True,dtype=np.float32,header=None)).reshape((-1,))
        Fall.append(f) #Fall=Fperm??
        for i in range(len(x)):
          fptrain.write('%e ' % (x[i]))
        s,r,s2=srs2_f(f)
#        import pdb;pdb.set_trace(); #for debug
        if m == s:
          fptrain.write('1\n')
          ytrain.append(1)
        else:
          fptrain.write('-1\n')
          ytrain.append(-1)
    n_train=len(Fall)
    for key in Ftest.keys():
#      import pdb;pdb.set_trace(); #for debug
      for i_f,f in enumerate(Ftest[key]):
#        print "test key=",key,f,i_f
#        print '#ftest={}'.format(args.dir+'/'+f)
        x=np.array(pd.read_csv(args.dir+'/'+f,delim_whitespace=True,dtype=np.float32,header=None)).reshape((-1,))
        Fall.append(f) #Fall=Fperm??
        for i in range(len(x)):
          fptest.write('%e ' % (x[i]))
        s,r,s2=srs2_f(f)
        if m == s:
          fptest.write('1\n')
          ytrain.append(1)
        else:
          fptest.write('-1\n')
          ytrain.append(-1)
#12345678901234567890
    fptrain.close()
    fptest.close()
#    import pdb;pdb.set_trace(); #for debug
###trainig and test of oob
    cmd='ensrs {}.dat {} {}-{} k:{} ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null > /dev/null'.format(fntrain,args.mbas,args.N,args.N,args.k)
#    sprintf(com,"ensrs %sxy.dat %s %d-%d:1 k:%d ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null > /dev/null",fntrain,mbas,N,N,k);
    print 'Executing {}'.format(cmd)
#    import pdb;pdb.set_trace(); #for debug
    myshell(cmd)
    fnpred='predict+oob.dat' #direct pred
    fnoob='pred+oob-{}.dat'.format(m) #oob    pred
    myshell('cp {} {}'.format(fnpred,fnoob)) #oob-output
###test with learned
    if nRX>0:
#      import pdb;pdb.set_trace(); #for debug
#      for j in range(b):
#        cmd='mv result-ensrs2ge/tmp/{}+null+m{}a{}b0:0s{}j{}k{}N{}pred.dat result-ensrs2ge/tmp/{}+{}+m{}a{}b0:0s{}j{}k{}N{}pred.dat'.format(fntrain,mbas[0],mbas[2],mbas[3],j,args.k,args.N,fntrain,fntest,mbas[0],mbas[2],mbas[3],j,args.k,args.N);
#        myshell(cmd)
      cmd='ensrs {}.dat {} {}-{}:1 k:{} ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:{}.dat > /dev/null'.format(fntrain,args.mbas,args.N,args.N,args.k,fntest);
      print '#executing {}'.format(cmd)
      myshell(cmd)
#sprintf(com,"ensrs %sxy.dat %s %d-%d:1 k:%d ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:%sxy.dat > /dev/null",fntrain,mbas,N,N,k,fntest);
#    import pdb;pdb.set_trace(); #for debug

###speaker verification
    yoob=np.array(pd.read_csv(fnoob,delim_whitespace=True,header=None).ix[:,0]).astype('float64')
#    yoob=np.array(pd.read_csv(fnoob,delim_whitespace=True,dtype=np.float32,header=None)[0:3])
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
#      if nRX>0 or i_f<nF/2:
#        yp=yoob
#      else:
#        yp=ypred
      s,r,s2=srs2_f(f)
#123456789
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
#    for i_f,f in enumerate(Fall):
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
#        ret='{:.3f} {:.3f} {:.3f} {:.3f} {:.3f} = {} {} {} {} {} #TP,FN,TN,FP,ERR n{} m={} R{} RX{} mbas{} N{}'.format(fTP,fFN,fTN,fFP,fER,TP,FN,TN,FP,ER,n,m,args.R,args.RX,args.mbas,args.N)
        ret='{:.3f} {:.3f} {:.3f} {:.3f} {:.3f} = {} {} {} {} {} #TP,TN,FP,FN,ERR n{} m={} R{} RX{} mbas{} N{}'.format(fTP,fTN,fFP,fFN,fER,TP,TN,FP,FN,ER,n,m,args.R,args.RX,args.mbas,args.N)
        print(ret)
#        import pdb;pdb.set_trace(); #for debug
        if i_f == n_train-1:
          fpr.write('{}\n'.format(ret))
        elif nRX>0:
          fprX.write('{}\n'.format(ret))
        TP=TN=FP=FN=0;

    for i_f,f in enumerate(F):
        print "{} {:+.2f} {} {} {} #yp y f m ytrain={}".format(f,yp[i_f],y[i_f],m,v[i_f],ytrain[i_f])
  
  #    import pdb;pdb.set_trace(); #for debug
  #    sprintf(com,"%.3f %.3f %.3f %.3f %.3e %d %d #TP,TN,FP,FN,ERR,n,sm%d",TP,TN,FP,FN,ER,n,sm,sm);
  fpr.close()
  fprX.close()
  cmd='cat {}'.format(fnr)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n++;TP+=$1;TN+=$2;FP+=$3;FN+=$4;ERR+=$5}END{printf("%.3f %.3f %.3f %.3f %.3f #mean TP TN FP FN ERR\\n",TP/n,TN/n,FP/n,FN/n,ERR/n)}\''+ '>>{}'.format(fnr)
#  cmd='cat {}'.format(fnr)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n++;TP+=$1;TN+=$2;FP+=$3;FN+=$4;ERR+=$5}END{printf("%.3f %.3f %.3f %.3f %.3f #mean TP TN FP FN ERR\n",TP/n,TN/n,FP/n,FN/n,ERR/n)}\'>{}.maen'.format(fnr)
#  print cmd
#  import pdb;pdb.set_trace(); #for debug
  myshell(cmd)
  cmd='cat {} #oob prediction of training data '.format(fnr)
  print cmd
  myshell(cmd)
  if nRX>0:
    cmd='cat {}'.format(fnrX)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n++;TP+=$1;TN+=$2;FP+=$3;FN+=$4;ERR+=$5}END{printf("%.3f %.3f %.3f %.3f %.3f #mean TP TN FP FN ERR\\n",TP/n,TN/n,FP/n,FN/n,ERR/n)}\''+'>>{}'.format(fnrX)
#    cmd='cat {}'.format(fnrX)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n++;TP+=$1;TN+=$2;FP+=$3;FN+=$4;ERR+=$5}END{printf("%.3f %.3f %.3f %.3f %.3f #mean TP TN FP FN ERR\n",TP/n,TN/n,FP/n,FN/n,ERR/n)}\'>{}.mean'.format(fnrX)
    myshell(cmd)
    cmd='cat {} #prediction of test data'.format(fnrX)
    print cmd
    myshell(cmd)
