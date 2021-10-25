#coding:utf-8
#SPTKの使い方 (6) MFCCの抽出
#https://aidiary.hatenablog.com/entry/20120805/1343825329
#SPTK のインストール
#https://aidiary.hatenablog.com/entry/20120701/1341126474 
#
import struct
import sys
import numpy as np

# print_mfcc.py

if len(sys.argv) != 3:
    print "usage: python print_spec.py [spec_file] [n_se] #n=l/2+1:final dimension"
    sys.exit()

specfile = sys.argv[1]
m = int(sys.argv[2])  #m=n_se

spec = []
f = open(specfile, "rb")
while True:
    b = f.read(4)
    if b == "": break;
    val = struct.unpack("f", b)[0]
    spec.append(val)
f.close()

#import pdb;pdb.set_trace(); #for debug
spec = np.array(spec)
numframe = len(spec) / m

if numframe * m != len(spec):
    print "ERROR: # len(data_in_file):%d - (n_spec:%d * numframe:%d) = {} !=0" % (len(spec), m, numframe,len(spec)-m*numframe)
    for i in range(len(spec)):
      print "\t".join("%.8e" % x for x in spec[i,])
    sys.exit(1)

spec = spec.reshape(numframe, m)
for i in range(len(spec)):
    print "\t".join("%.8e" % x for x in spec[i,])
