import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import numpy as np
import math
import struct
import os
import sys
import pycurl
import io

# main
if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='speech conversion int to binary short')
  parser.add_argument('-yin', default='', type=str,   help='yin')
  parser.add_argument('-yout', default='', type=str,   help='yout')
  parser.add_argument('-fmt', default='h', type=str,   help='h for short-2byte, e for float-2byte')
  parser.add_argument('-mag', default=1, type=float, help='mag for short')
#  parser.add_argument('-mag', default='32767', type=str, help='mag for short')
#  parser.add_argument('-mag', default='1', type=str, help='mag=1 for original r for normalize by rms, max by max')

  args = parser.parse_args()
#  y=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
#  if not os.path.exists(args.yin):
#    print('#error: {} does not exist. exit()'.format(args.yin))
#    exit()
#  import pdb;pdb.set_trace(); #for debug
  y=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
  ny=len(y)
#  ym=0

#  import pdb;pdb.set_trace(); #for debug
  fo = open(args.yout, "wb") #raw-file=data.short
  a=args.mag
  yoM=max(abs(a*y))
  fmt=args.fmt
  for t in range(len(y)):
    if fmt == "h": yout=int(a*y[t])
    else: yout=a*y[t]
#    import pdb;pdb.set_trace(); #for debug
    bo=struct.pack(fmt, y[t]);#type(bo) --> <type 'str'> short 2byte
    #    bo=struct.pack("h", y[t]);#type(bo) --> <type 'str'> short 2byte
#    sys.stdout.buffer.write(bo) #binary out
    fo.write(bo)
  fo.close()
