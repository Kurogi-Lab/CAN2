import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
import math
# main
if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='speech normalize')
  parser.add_argument('-yin', default='', type=str,   help='yin')
  parser.add_argument('-yout', default='', type=str,   help='yout')
  parser.add_argument('-ymin', default=5, type=float,   help='ymin')
  parser.add_argument('-yth', default=0.05, type=float,   help='y[t]< yMax*yth is neglected for rms')

  args = parser.parse_args()
  y=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
  ny=len(y)
#  yM1=max(abs(y))
#  ym=0
  yM=max(abs(y))
  ym=args.yth*yM
  ym2=ym*ym
  ys=0
  nys=0
  for t in range(ny):
    yt2=y[t]*y[t]
    if yt2>ym2:
      ys+=y[t]*y[t]
      nys+=1
  rms=math.sqrt(ys/nys)
#  import pdb;pdb.set_trace(); #for debug
  fp=open(args.yout,'w')
  yoM=0.0
  a=32767.0/rms/8 #
  for t in range(ny):
    yout=y[t]*a
    if abs(yout) > yoM: yoM=abs(yout)
    fp.write('%e\n' % (yout))
  fp.close()
  print "{} {} {} {} {} {} {} #yoM RMSE ymaxorig new-max nys tmax fname".format(yoM,rms,yM,yM/rms,nys,ny,args.yin)

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

