#!/usr/bin/env python
# -*- coding: utf-8 -*-
#coding:utf-8
#SPTKの使い方 (6) MFCCの抽出
#https://aidiary.hatenablog.com/entry/20120805/1343825329
#SPTK のインストール
#https://aidiary.hatenablog.com/entry/20120701/1341126474 
#
import struct
import sys
import numpy as np
import argparse

# print_mfcc.py

if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='bin2txt')
  parser.add_argument('-fn', default='', type=str,   help='bin-file name')
  parser.add_argument('-k', default=12, type=int,   help='k')
  parser.add_argument('-rc', default=np.nan, type=int,   help='remove rc-th column if |rc|<k')
  args = parser.parse_args()

#  if len(sys.argv) < 3:
#    print "usage: python bin2txt.py [bin(4byte-float)_file] [k] #k or k1 is tried as a pack"
#    sys.exit()

  fnbin = args.fn #file name of 4-byte float 
  k = int(args.k)
  
  data = []
  f = open(fnbin, "rb")
  while True:
      b = f.read(4)
      if b == "": break;
      val = struct.unpack("f", b)[0]
      data.append(val)
  f.close()
  
  data = np.array(data)
  if len(data) % k ==0:
    pass
  elif len(data) % (k+1) ==0:
    k=k+1
  else:
    print("ERROR: #len(data_in_file):{} is not a multiplication of k:{} nor k+1".format(len(data), k))
    sys.exit(1)
  numframe = len(data) / k
  data = data.reshape(numframe, k)
#  import pdb;pdb.set_trace(); #for debug
  if not np.isnan(args.rc):
    rc=args.rc
    if abs(rc) <k :
      data=np.delete(data,rc,1) #delete rc-th on axis=1 (column)
    else:pass
  else: pass
      
  for i in range(len(data)):
      print "\t".join("%.10e" % x for x in data[i,])

