#coding:utf-8
#https://aidiary.hatenablog.com/entry/20120415/1334458954
import wave
import numpy as np
import scipy.io.wavfile
import scipy.signal
import scipy.fftpack
from pylab import *
import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import subprocess
from levinson_durbin import autocorr, LevinsonDurbin, mypltshow, myshell

"""LPCスペクトル包絡を求める"""

def wavread(filename):
    wf = wave.open(filename, "r")
    fs = wf.getframerate()
    x = wf.readframes(wf.getnframes())
    x = np.frombuffer(x, dtype="int16") / 32768.0  # (-1, 1)に正規化
    wf.close()
    return x, float(fs)

def preEmphasis(signal, p):
    """プリエンファシスフィルタ"""
    # 係数 (1.0, -p) のFIRフィルタを作成
    return scipy.signal.lfilter([1.0, -p], 1, signal)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='lpc-spectrumenvelope')
    parser.add_argument('-yin', default='', type=str,   help='speech signal to be processed')
    parser.add_argument('-fout', default='tmp/LPC.dat', type=str,   help='output LPCs')
    parser.add_argument('-k', default=32, type=int,   help='lpcOrdar')
    parser.add_argument('-l', default=20, type=int,   help='frame-length_ms=20ms')
    parser.add_argument('-t', default='0', type=str,   help='t:t0 or t:t0-t1 for processing')
    parser.add_argument('-HW', default=1, type=int,   help='1 for use Hamming window, other for not use')
    parser.add_argument('-mp_th', default=0.0, type=float,   help='mean power') #0.4 ?
    parser.add_argument('-nDisp', default=-1, type=int,   help='frame-number to display')
    args = parser.parse_args()

    if args.yin == "":
        # 音声をロード
        #~/sotu/2019/12voicedata_ueki_all_n/mym-zero9.dat
        wav, fs = wavread("a.wav")
        t = np.arange(0.0, len(wav) / fs, 1/fs)
    else:
        yin=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
        fs=8000.
        t = np.arange(0.0, len(yin), 1/fs)
        wav=yin
#    import pdb;pdb.set_trace(); #for debug
    if '-' in args.t:
      t0,t1=(args.t).split('-') #      t0,t1=map(int,(args.t).split('-'))
      t0=int(t0)
      if t1 == '': t1=len(wav)
      else:
          t1=int(t1)
          if t1 <= t0:
            t1=len(wav)
    else:
      t0=int(args.t)
      t1=len(wav)
    if args.t != '0':
        plot(wav[t0:t1]); mypltshow('tmp/yt{}-{}.eps'.format(t0,t1));

    # 音声波形の中心部分を切り出す
    center = len(wav) / 2  # 中心のサンプル番号
#    cuttime = 0.04         # 切り出す長さ [s] 40ms
    cuttime = args.l/1000.    # 切り出す長さ [s] 20ms
    fl_n=int(cuttime*fs)
    fl_n2=fl_n/2
    A=[]
    E=[]
    mP=[]
    if args.nDisp>=0:
      print('lenwav={}, nDmax={} fl_n={}'.format(len(wav),len(wav)/fl_n2,fl_n))
#    for i in range(0,len(wav)/fl_n2):
    for t in range(t0,t1,fl_n2):
#      t=i*fl_n2
      i=(t-t0)/fl_n2
      #      s = wav[center - cuttime/2*fs : center + cuttime/2*fs]
      s = wav[t: t+fl_n]
#      import pdb;pdb.set_trace(); #for debug
#      plot(s); mypltshow('tmp/y0i{}t{}-{}.eps'.format(i,t,t+fl_n));
      mp=np.sum(s**2)/fl_n #mean power
      mP.append(mp)
      if mp <args.mp_th:
        continue
      # プリエンファシスフィルタをかける
      p = 0.97         # プリエンファシス係数
      s = preEmphasis(s, p)
#      plot(s); mypltshow('tmp/y1i{}t{}-{}.eps'.format(i,t,t+fl_n));
      # ハミング窓をかける
      if args.HW ==1:
        hammingWindow = np.hamming(len(s))
        s = s * hammingWindow
#      s = s * hammingWindow
      # LPC係数を求める
  #    lpcOrder = 32
      lpcOrder = args.k  # LPC係数の次数
      r = autocorr(s, lpcOrder + 1)
      if r[0]!=0:
      # import pdb;pdb.set_trace(); #for debug
        a, e  = LevinsonDurbin(r, lpcOrder)
        if np.linalg.norm(a[1:-1]>0.05):#20210502 for removing log|p|=-578....
#        if np.any(a[1:-1]!=0):
            A.append(a)
            #print "*** result ***"
            E.append(e)
#      if i <10 : 
#        plot(a)
#        mypltshow('LPC{}.eps'.format(i));
      # LPC係数の振幅スペクトルを求める
      nfft = 2048   # FFTのサンプル数
  
      fscale = np.fft.fftfreq(nfft, d = 1.0 / fs)[:nfft/2]
  
      # オリジナル信号の対数スペクトル
      spec = np.abs(np.fft.fft(s, nfft))
      logspec = 20 * np.log10(spec)

      # LPC対数スペクトル
      w, h = scipy.signal.freqz(np.sqrt(e), a, nfft, "whole")
      lpcspec = np.abs(h)
      loglpcspec = 20 * np.log10(lpcspec)
      if i == args.nDisp:
        print('i={},t={}-{}',i,t,t+fl_n)
        plot(s); mypltshow('tmp/yi{}t{}-{}.eps'.format(i,t,t+fl_n));
        plot(fscale, logspec[:nfft/2]);
        plot(fscale, loglpcspec[:nfft/2], "r", linewidth=2)
        xlim((0, fs/2))
        mypltshow('tmp/Envelope{}.eps'.format(i))
        df=pd.DataFrame(loglpcspec[:nfft/2])
        df.to_csv('tmp/lpcenv.txt',index=False,sep=' ',header=None)
#
        plot(wav); mypltshow('tmp/yall{}-{}.eps'.format(0,len(wav)));
#      print('i,t={},{}'.format(i,t))
    if args.nDisp>=0:
      plot(mP);#plt.show()
      mypltshow("tmp/meanPower.eps")
#    fnfig="meanPower.eps"
#    plt.savefig(fnfig)
#    myshell("sleep 1;gv "+fnfig+"&");
    AA=np.array(A)
    df=pd.DataFrame(AA)
    df.to_csv(args.fout,index=False,sep=' ',header=None)
#    df.to_csv("tmp/LPC.dat",index=False,sep=' ',header=None)
#    AA.shape
#    import pdb;pdb.set_trace(); #for debug
#    print "A:", a
#    print "E:", e

