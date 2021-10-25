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
  parser.add_argument('-L', default='1:2:3:4:5:6:7:8:9:10', type=str,   help='mag r1:r2:...:rn for learning and test')
  parser.add_argument('-OmL', default='0', type=str,   help='Omit Learning')

  args = parser.parse_args()
  S=(args.sp).split(':') #speakers
  T=(args.tx).split(':') #text
  R=(args.R).split(':') #text
  L=(args.L).split(':') #text
  sX=args.sX
#  L=range(1,args.ntxi+1) #date
#  mbas=map(int,(args.mbas).split(':'))
#  y=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float32,header=None)).reshape((-1,))
  fnerr=['mmt-san2', 'fhs-hachi5']
  if args.s != 0:
    M=S
  elif args.d != 0:
    M=T
#  import pdb;pdb.set_trace(); #for debug
  fnr=args.dir+'/oob4sd-result.dat'
  fpr=open(fnr,'w')
  for i_m,m in enumerate(M):
#    if args.OmL == '0':
#      myshell('make data-clean')
    fntrain='train-{}.dat'.format(m)
    fptrain=open(fntrain,'w')
    Fy=[]
    for i_s,s in enumerate(S):
      if i_s != args.sX:
        for i_t,t in enumerate(T):
          for i_l,l in enumerate(L):
           fn='{}-{}{}'.format(s,t,l)
#           if fn in fnerr:
#             continue
#           import pdb;pdb.set_trace(); #for debug
           for r in R:
             fnq='{}/{}-*R{}*'.format(args.dir,fn,r) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
  #           fnq='{}/{}-{}{}*'.format(args.dir,s,t,l) #fnq=args.dir+ '/' + s + '-' + t + l + '*'
             F=[f.split('/')[-1] for f in glob.glob(fnq)] #file list
  #           import pdb;pdb.set_trace(); #for debug
             for f in F:
               fl=f.split('-')
               if len(fl)==6: #e.g.fhs-go1-mmt-nana10-R0.8-p.dat
                 r=fl[4][1:]
               elif len(fl)==4:#e.g. mym-kyu10-R1-p.dat
                 r='1'
               else:#NG
                 continue
  ###             if not r in R:             continue
#               import pdb;pdb.set_trace(); #for debug
               x=np.array(pd.read_csv(args.dir+'/'+f,delim_whitespace=True,dtype=np.float32,header=None)).reshape((-1,))
               Fy.append(f)
               for i in range(len(x)):
                 fptrain.write('%e ' % (x[i]))
               if m == s:
                 fptrain.write('1 {} L{}\n'.format(f,len(Fy)))
  #               fptrain.write('1\n')
               else:
                 fptrain.write('-1 {} L{}\n'.format(f,len(Fy)))
  #               fptrain.write('-1\n')
  #             import pdb;pdb.set_trace(); #for debug
               #mixed
    fptrain.close()
#    import pdb;pdb.set_trace(); #for debug
    cmd='ensrs {} {} {}-{} k:{} ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null > /dev/null'.format(fntrain,args.mbas,args.N,args.N,args.k)
#    sprintf(com,"ensrs %sxy.dat %s %d-%d:1 k:%d ib:0:0:0:0 y:-1:1:-1:1 x:0:0:0:1 DISP:0 bg:/dev/null > /dev/null",fntrain,mbas,N,N,k);
    print 'Executing {}'.format(cmd)
    fnoob='pred+oob-{}.dat'.format(m) #oob    pred
    if args.OmL != '1':
      myshell(cmd)
      fnpred='predict+.dat' #direct pred
      myshell('cp {} {}'.format(fnpred,fnoob)) #oob-output
#    fnsX='pred+sX-{}.dat'.format(m) #oob    pred

#    import pdb;pdb.set_trace(); #for debug
###speaker verification
    yoob=np.array(pd.read_csv(fnoob,delim_whitespace=True,header=None).ix[:,0]).astype('float64')
#    yoob=np.array(pd.read_csv(fnoob,delim_whitespace=True,dtype=np.float32,header=None)[0:3])
    if sX>=0:
      ypred=np.array(pd.read_csv(fnpred,delim_whitespace=True,header=None).ix[:,0]).astype('float64')
    TP=TN=FP=FN=0;
    TPX=TNX=FPX=FNX=0;
#    print "m,Fy=",m,Fy
    y=[]
    v=[]
    for i_f,f in enumerate(Fy):
      fl=f.split('-')
      s=fl[0]
      if len(fl)==6: #e.g.'mym', 'zero9', 'mkk', 'zero2', 'R0.8', 'p.dat'
        r=fl[4][1:]
        s2=fl[2]
      elif len(fl)==4:#r=1 e.g.'mym', 'zero9', 'mkk', 'zero2', 'R0.8', 'p.dat'
        r='1'
        s2=s
      else:#NG
        continue
      if m == s or m == s2: #yp should be positive
        y.append(1)
        if yoob[i_f] > 0: #Positive
          TP+=1
          v.append('TP')
        else:
          FN+=1
          v.append('FN')
          print('FN:{} yp={} m={} s={} s2={}'.format(f,yoob[i_f],m,s,s2))
      else: #yp should be Negative
        y.append(-1)
        if yoob[i_f] > 0: #Positive
          FP+=1
          v.append('FP')
          print('FP:{} yp={} m={} s={} s2={}'.format(f,yoob[i_f],m,s,s2))
        else:
          TN+=1
          v.append('TN')
    for i_f,f in enumerate(Fy):
      print "{} {:+.2f} {} {} {}#yp y f m".format(f,yoob[i_f],y[i_f],m,v[i_f])

    ER  =(FP+FN)
    n   =(TP+TN+FP+FN)
    TPFN=(TP+FN)
    FPTN=(FP+TN)

    fTP=TP/float(TPFN);
    fFN=FN/float(TPFN);
    fFP=FP/float(FPTN);
    fTN=TN/float(FPTN);
    fER=ER/float(n);
    ret='{:.3f} {:.3f} {:.3f} {:.3f} {:.3f} = {} {} {} {} {} #TP,TN,FP,FN,ERR n{} m={} R{} S:{}'.format(fTP,fTN,fFP,fFN,fER,TP,TN,FP,FN,ER,n,m,args.R,args.sp)

    print(ret)
    fpr.write('{}\n'.format(ret))
#    import pdb;pdb.set_trace(); #for debug
#    sprintf(com,"%.3f %.3f %.3f %.3f %.3e %d %d #TP,TN,FP,FN,ERR,n,sm%d",TP,TN,FP,FN,ER,n,sm,sm);
  fpr.close()
  cmd='cat {}'.format(fnr)
  print cmd
  myshell(cmd)
  cmd='cat {}'.format(fnr)+'|awk \'BEGIN{n=0;TP=TN=FP=FN=ERR=0}{n++;TP+=$1;TN+=$2;FP+=$3;FN+=$4;ERR+=$5}END{printf("%.3f %.3f %.3f %.3f %.3f #mean TP TN FP FN ERR\n",TP/n,TN/n,FP/n,FN/n,ERR/n)}\''
  myshell(cmd)
