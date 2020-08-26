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

  args = parser.parse_args()
  y=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
  ny=len(y)
  yM=max(abs(y))
  ym=0
  ym2=ym*ym
  se=0
  nse=0
  for t in range(ny):
    yt2=y[t]*y[t]
    if yt2>ym2:
      se+=y[t]*y[t]
      nse+=1

  rmse=math.sqrt(se/nse)
  print "{} {} {} {} {} {} #RMSE max -> newmax nse tmax fname".format(rmse,yM,yM/rmse,nse,ny,args.yin)
#  import pdb;pdb.set_trace(); #for debug
  fp=open(args.yout,'w')
  for t in range(ny):
    fp.write('%e\n' % (y[t]/rmse))
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

