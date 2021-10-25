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
from levinson_durbin import autocorr, LevinsonDurbin, mypltshow

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
    parser.add_argument('-yin', default='', type=str,   help='input signal')
    parser.add_argument('-k', default=32, type=int,   help='lpcOrdar')
    parser.add_argument('-fl_ms', default=20, type=int,   help='frame-length_ms=20ms')
    parser.add_argument('-mp_th', default=0.4, type=float,   help='mean power')
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

    # 音声波形の中心部分を切り出す
    center = len(wav) / 2  # 中心のサンプル番号
#    cuttime = 0.04         # 切り出す長さ [s] 40ms
    cuttime = args.fl_ms/1000.    # 切り出す長さ [s] 20ms
    fl_n=int(cuttime*fs)
    fl_n2=fl_n/2
    A=[]
    E=[]
    mP=[]
    nDisp=0
    for i in range(0,len(wav)/fl_n2):
      t=i*fl_n2
      #      s = wav[center - cuttime/2*fs : center + cuttime/2*fs]
      s = wav[t: t+fl_n]
#      import pdb;pdb.set_trace(); #for debug
      mp=np.sum(s**2)/fl_n #mean power
      mP.append(mp)
      if mp <args.mp_th:
        continue
      # プリエンファシスフィルタをかける
      p = 0.97         # プリエンファシス係数
      s = preEmphasis(s, p)

      # ハミング窓をかける
      hammingWindow = np.hamming(len(s))
      s = s * hammingWindow
      if i<nDisp:
        plot(s) 
        mypltshow('y{}.eps'.format(i));
      # LPC係数を求める
  #    lpcOrder = 32
      lpcOrder = args.k  # LPC係数の次数
      r = autocorr(s, lpcOrder + 1)
      a, e  = LevinsonDurbin(r, lpcOrder)
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
      if i<nDisp:
        plot(fscale, logspec[:nfft/2])

      # LPC対数スペクトル
      w, h = scipy.signal.freqz(np.sqrt(e), a, nfft, "whole")
      lpcspec = np.abs(h)
      loglpcspec = 20 * np.log10(lpcspec)
      if i<nDisp:
        plot(fscale, loglpcspec[:nfft/2], "r", linewidth=2)
        xlim((0, fs/2))
  #    xlim((0, 10000))
        mypltshow('Envelope{}.eps'.format(i))
  #    show()
    plt.close();plot(mP);mypltshow("meanPower.eps")
    import pdb;pdb.set_trace(); #for debug
    print "A:", a
#    print "E:", e
