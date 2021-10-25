import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
import math
import struct
import os

# main
if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='speech conversion int to binary short')
  parser.add_argument('-yin', default='', type=str,   help='yin')
  parser.add_argument('-yout', default='', type=str,   help='yout')
  parser.add_argument('-yth', default=0.05, type=float,   help='y[t]< yMax*yth is neglected for rms')
  parser.add_argument('-fmt', default='h', type=str,   help='h for short-2byte, e for float-2byte')
  parser.add_argument('-nrm', default='1', type=str, help='nrm=1 for original r for normalize by rms, max by max')
#  parser.add_argument('-mag', default='1', type=str, help='mag=1 for original r for normalize by rms, max by max')

  args = parser.parse_args()
#  y=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
#  if not os.path.exists(args.yin):
#    print('#error: {} does not exist. exit()'.format(args.yin))
#    exit()
#  import pdb;pdb.set_trace(); #for debug
  y=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.int64,header=None)).reshape((-1,))
  ny=len(y)
#  ym=0
  yMf=max(abs(y))
  ym=args.yth*yMf
  ym2=ym*ym
  se=0
  nse=0
  yM=0.0
  for t in range(ny):
    if abs(y[t])>yM: yM=abs(y[t])
    yt2=y[t]*y[t]
    if yt2>=ym2:
      se+=y[t]*y[t]
      nse+=1
  rms=math.sqrt(se/nse)
  if yM!=yMf:
    print('#err yM{}!=yMf{}'.format(yM,yMf))
#  rms1=np.sqrt(np.square(y).mean())
#  import pdb;pdb.set_trace(); #for debug
  fmt=args.fmt
  if args.nrm=='r':
    a=32767.0/rms/8 #
  elif args.nrm=='m':
    a=32767.0/yM #
  else: #if args.nrm=='1':
    a=1.0

#  import pdb;pdb.set_trace(); #for debug
  fo = open(args.yout, "wb") #raw-file=data.short
  yoM=0
  yoMf=int(max(abs(a*y)))
  for t in range(len(y)):
    yout=int(a*y[t])
#    print('{} {} {} {} {} #t,yout,yt,yoMf'.format(t,yout,y[t],a,yoMf))
    if abs(yout)>yoM: yoM=abs(yout)
#    import pdb;pdb.set_trace(); #for debug
    bo=struct.pack(fmt, y[t]);#type(bo) --> <type 'str'> short 2byte
#    bo=struct.pack("h", y[t]);#type(bo) --> <type 'str'> short 2byte
    fo.write(bo)
  fo.close()
  if yoM != yoMf:
    print('#err yoM{}!=yoMf{} with a={} for {}'.format(yoM,yoMf,a,args.yin))
#  if yoM>32767:
#    print('#new ymax={} exeeds 32767. Exit'.format(yoM))
#    exit(0)
  print "{:.1f} {:.1f} {} {} {} {} {} #yoM, rms ymax ymax/rms nse tmax fname".format(yoM,rms,yM,yM/rms,nse,ny,args.yin)
  if 1==0:
    fp=open(args.yout,'w')
    for t in range(ny):
      fp.write('%e\n' % (y[t]/rms))
    fp.close()

###############
#  ym=args.ymin
#  ym2=ym*ym
#  for t in range(ny):
#    yt2=y[t]*y[t]
#    if yt2>ym2:
#      t0=t
#      break;
#
#  for t in range(ny-1,0,-1):
#    yt2=y[t]*y[t]
##    print "t yt2",t,yt2
#    if yt2>ym2:
#      t1=t
#      break;
#  se=0
#  for t in range(t0,t1):
#     se+=y[t]*y[t]
#
#  rmse=math.sqrt(se/(t1-t0))
#  print "{} {} {} {} {} {} {} #RMSE max -> newmax t0 t1 tmax fname".format(rmse,yM,yM/rmse,t0,t1,ny,args.yin)
##  import pdb;pdb.set_trace(); #for debug
#  fp=open(args.yout,'w')
#  for t in range(ny):
#    fp.write('%e\n' % (y[t]/rmse))
#  fp.close()

