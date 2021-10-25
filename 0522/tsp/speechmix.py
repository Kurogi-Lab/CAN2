import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
# main
if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='mix speech')
  parser.add_argument('-y0', default='', type=str,
                      help='y0')
  parser.add_argument('-y1', default='', type=str,
                      help='y1')
  parser.add_argument('-r', default=0.9, type=float,
                      help='lambda between 0 to 1')

  args = parser.parse_args()
  R1=float(args.r)
  R2=1.-R1
  y=[]
  y.append(np.array(pd.read_csv(args.y0,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,)))
  y.append(np.array(pd.read_csv(args.y1,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,)))
  n=[]
#  yM=[]
#  ym=[]
#  se=[]
#  nse=[]
  for i in [0,1]:
   n.append(len(y[i]))
#   yM.append(max(abs(y[i])))
#   ym.append(yM[i]/100.)
#  import pdb;pdb.set_trace(); #for debug
  nm=max(n)
  for i in [0,1]:
    if n[i]<nm:
      y[i]=np.append(y[i],np.zeros((nm-n[i])))

#  import pdb;pdb.set_trace(); #for debug
#  ym=np.zeros((nm))
  for t in range(nm):
    print y[0][t]*R1+y[1][t]*R2
