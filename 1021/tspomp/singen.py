#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
import struct
import sys
import numpy as np
import argparse
import math
# print_mfcc.py

if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='singen')
  parser.add_argument('-fd', default=0.1, type=float,   help='frequency of data')
  parser.add_argument('-fs', default=8, type=float,   help='8 kHz')
  parser.add_argument('-r', default=0.99, type=float,   help='decay')
  parser.add_argument('-n', default=4000, type=int,   help='number of data')
  args = parser.parse_args()

  #  if len(sys.argv) < 3:
  #    print "usage: python bin2txt.py [bin(4byte-float)_file] [k] #k or k1 is tried as a pack"
  #    sys.exit()
  fs=args.fs*1000. #kHz
  fd=args.fd*1000. #kHz
  r=math.log(args.r)
  #  import pdb;pdb.set_trace(); #for debug 20191105
  for i in range(args.n):
    t=float(i)/fs
    print('{}'.format(math.exp(r*t*fd)*math.sin(2*math.pi*fd*t)))
