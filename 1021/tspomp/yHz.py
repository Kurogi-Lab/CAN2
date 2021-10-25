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
import math
# print_mfcc.py

if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='bin2txt')
  parser.add_argument('-f', default='1000,200,3000', type=str,   help='Hz')
  parser.add_argument('-k', default=12, type=int,   help='k')
  parser.add_argument('-rc', default=np.nan, type=int,   help='remove rc-th column if |rc|<k')
  args = parser.parse_args()

#  if len(sys.argv) < 3:
#    print "usage: python bin2txt.py [bin(4byte-float)_file] [k] #k or k1 is tried as a pack"
#    sys.exit()

  fs = 8000;
#  ftest = (100, 200, 400, 1000, 2000)
  fset = (100, 200, 400, 1000, 2000,)
  fset = (100,200,400,800,1600,)
  fset = (2000,)
  fset = map(int,args.f.split(','))
  for i in range(500):
#  for i in range(fs):
    t=i/float(fs)
    yt=0
    for f in fset:
      yt= yt +np.sin(2.*np.pi*f*t)
#      yt= yt +np.sin(2.*np.pi*f*t)*abs(1-np.cos(2.*np.pi*t))
    print('{} {}'.format(yt,t))
