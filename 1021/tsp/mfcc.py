#coding:utf-8
#https://aidiary.hatenablog.com/entry/20120225/1330179868
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

def mypltshow(fnfig):
  plt.savefig(fnfig);
  myshell("sleep 1;gv "+fnfig+"&");
  plt.cla()
  plt.close() #plt.show()

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

def hz2mel(f):
    """Hzをmelに変換"""
    return 1127.01048 * np.log(f / 700.0 + 1.0)

def mel2hz(m):
    """melをhzに変換"""
    return 700.0 * (np.exp(m / 1127.01048) - 1.0)

def melFilterBank(fs, nfft, numChannels):
    """メルフィルタバンクを作成"""
    # ナイキスト周波数（Hz）
#    nfft=128 #check
    fmax = fs / 2
    # ナイキスト周波数（mel）
    melmax = hz2mel(fmax)
    # 周波数インデックスの最大数
    nmax = nfft / 2
    # 周波数解像度（周波数インデックス1あたりのHz幅）
    df = fs / nfft
    # メル尺度における各フィルタの中心周波数を求める
    dmel = melmax / (numChannels + 1)
    melcenters = np.arange(1, numChannels + 1) * dmel
    # 各フィルタの中心周波数をHzに変換
    fcenters = mel2hz(melcenters)
    # 各フィルタの中心周波数を周波数インデックスに変換
    indexcenter = np.round(fcenters / df).astype(int64)
    # 各フィルタの開始位置のインデックス
    indexstart = np.hstack(([0], indexcenter[0:numChannels - 1])).astype(int64)
    # 各フィルタの終了位置のインデックス
    indexstop = np.hstack((indexcenter[1:numChannels], [nmax])).astype(int64)

    filterbank = np.zeros((numChannels, nmax))
    for c in np.arange(0, numChannels):
        # 三角フィルタの左の直線の傾きから点を求める
#        import pdb;pdb.set_trace(); #for debug check
        increment= 1.0 / (indexcenter[c] - indexstart[c])
        for i in np.arange(indexstart[c], indexcenter[c]):
#            print('c={},i={}'.format(c,i))
#            import pdb;pdb.set_trace(); #for debug
            filterbank[c, i] = (i - indexstart[c]) * increment
        # 三角フィルタの右の直線の傾きから点を求める
        decrement = 1.0 / (indexstop[c] - indexcenter[c])
        for i in np.arange(indexcenter[c], indexstop[c]):
            filterbank[c, i] = 1.0 - ((i - indexcenter[c]) * decrement)

    return filterbank, fcenters


if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='lpc-spectrumenvelope')
  parser.add_argument('-yin', default='', type=str,   help='speech signal to be processed')
  parser.add_argument('-fout', default='tmp/LPC.dat', type=str,   help='output LPCs')
  parser.add_argument('-m', default=32, type=int,   help='cepstrum Ordar')
  parser.add_argument('-nceps', default=12, type=int,   help='nceps') #0.4 ?
  parser.add_argument('-l', default=20, type=int,   help='frame-length_ms=20ms')
  parser.add_argument('-t', default='0', type=str,   help='t:t0 or t:t0-t1 for processing')
  parser.add_argument('-HW', default=1, type=int,   help='1 for use Hamming window, other for not use')
  parser.add_argument('-mp_th', default=0.0, type=float,   help='mean power') #0.4 ?
  parser.add_argument('-nDisp', default=-1, type=int,   help='frame-number to display')
  parser.add_argument('-nfft', default=2048, type=int,   help='n-fft min:256')
  args = parser.parse_args()

  if args.yin == "":
    # 音声をロード
    #~/sotu/2019/12voicedata_ueki_all_n/mym-zero9.dat
    wav, fs = wavread("../tmp/sounds_a.wav")
    t = np.arange(0.0, len(wav) / fs, 1/fs)
  else:
    yin=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
    fs=8000.
    t = np.arange(0.0, len(yin), 1/fs)
    wav=yin
  #    import pdb;pdb.set_trace(); #for debug
#  import pdb;pdb.set_trace(); #for debug
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
    if args.nDisp==i:
#    if args.nDisp>=0:
      plot(s); mypltshow('tmp/y1i{}t{}-{}.eps'.format(i,t,t+fl_n));
#    import pdb;pdb.set_trace(); #for debug
    # ハミング窓をかける
    if args.HW ==1:
      hammingWindow = np.hamming(len(s))
      s = s * hammingWindow
    # 振幅スペクトルを求める
#    nfft = 2048  # FFTのサンプル数
    nfft = args.nfft  # FFTのサンプル数
    spec = np.abs(np.fft.fft(s, nfft))[:nfft/2]
#    spec = np.abs(np.fft.fft(s, nfft))
    fscale = np.fft.fftfreq(nfft, d = 1.0 / fs)[:nfft/2]
    # メルフィルタバンクを作成
    numChannels = int(20)  # メルフィルタバンクのチャネル数

    fs=int(fs)
    df = fs / nfft   # 周波数解像度（周波数インデックス1あたりのHz幅）
#    import pdb;pdb.set_trace(); #for debug
    filterbank, fcenters = melFilterBank(fs, nfft, numChannels)
    # メルフィルタバンクのプロット
#    showfilterbank=0
#    if showfilterbank==1:
    if args.nDisp==i:
#      for c in np.arange(0, 1):
      for c in np.arange(0, numChannels):
        plot(np.arange(0, nfft / 2) * df, filterbank[c])
      mypltshow("melfilterbank.eps")
#      savefig("melfilterbank.png")
#      show()
    # 振幅スペクトルにメルフィルタバンクを適用
#    import pdb;pdb.set_trace(); #for debug
    mspec = np.log10(np.dot(spec, filterbank.T))
    # 元の振幅スペクトルとフィルタバンクをかけて圧縮したスペクトルを表示
    if i == args.nDisp:
      print('i={},t={}-{}',i,t,t+fl_n)

      subplot(211)
      plot(fscale, np.log10(spec))
      xlabel("frequency")
      xlim(0, 25000)
  
      subplot(212)
      plot(fcenters, mspec, "o-")
      xlim(0, 25000)
      xlabel("frequency")
      mypltshow('tmp/mfcc-se-i{}t{}-{}.eps'.format(i,t,t+fl_n))
      #    show()
      #    import pdb;pdb.set_trace(); #for debug
      # 離散コサイン変換
    ceps = scipy.fftpack.realtransforms.dct(mspec, type=2, norm="ortho", axis=-1)
    # 低次成分からnceps個の係数を返す
#    import pdb;pdb.set_trace(); #for debug
    if args.nDisp==i:
      plot(range(len(ceps)), ceps[:], "o-")
      mypltshow('tmp/mfcc-i{}t{}-{}.eps'.format(i,t,t+fl_n))
    nceps=args.m #    nceps=12
    A.append(ceps[:nceps])
  AA=np.array(A)
  df=pd.DataFrame(AA)
  df.to_csv(args.fout,index=False,sep=' ',header=None)

   #
#import wave
#import numpy as np
#from pylab import *
#import argparse
#import scipy.signal
#
#def myshell(cmd): #no stop even when error occured
#  try:
#    retcode=subprocess.Popen(cmd, shell=True)
#    if retcode < 0:
#        pass #print "my Child was terminated by signal", -retcode
#    else:
#        pass #print "my Child returned", retcode
#  except OSError as e:
#    print "Execution failed:", cmd, e
#  return retcode.wait()
#
#def wavread(filename):
#    wf = wave.open(filename, "r")
#    fs = wf.getframerate()
#    x = wf.readframes(wf.getnframes())
#    x = np.frombuffer(x, dtype="int16") / 32768.0  # (-1, 1)に正規化
#    wf.close()
#    return x, float(fs)
#
#def preEmphasis(signal, p):
#    """プリエンファシスフィルタ"""
#    # 係数 (1.0, -p) のFIRフィルタを作成
#    return scipy.signal.lfilter([1.0, -p], 1, signal)
#
#if __name__ == "__main__":
#    parser = argparse.ArgumentParser(description='lpc-spectrumenvelope')
#    parser.add_argument('-yin', default='', type=str,   help='speech signal to be processed')
#    parser.add_argument('-fout', default='tmp/LPC.dat', type=str,   help='output LPCs')
#    parser.add_argument('-k', default=32, type=int,   help='lpcOrdar')
#    parser.add_argument('-l', default=20, type=int,   help='frame-length_ms=20ms')
#    parser.add_argument('-t', default='0', type=str,   help='t:t0 or t:t0-t1 for processing')
#    parser.add_argument('-HW', default=1, type=int,   help='1 for use Hamming window, other for not use')
#    parser.add_argument('-mp_th', default=0.0, type=float,   help='mean power') #0.4 ?
#    parser.add_argument('-nDisp', default=-1, type=int,   help='frame-number to display')
#    args = parser.parse_args()
#
#    if args.yin == "":
#        # 音声をロード
#        #~/sotu/2019/12voicedata_ueki_all_n/mym-zero9.dat
#        wav, fs = wavread("a.wav")
#        t = np.arange(0.0, len(wav) / fs, 1/fs)
#    else:
#        yin=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
#        fs=8000.
#        t = np.arange(0.0, len(yin), 1/fs)
#        wav=yin
##if __name__ == "__main__":
#    # 音声をロード
#    wav, fs = wavread("a.wav")
#    t = np.arange(0.0, len(wav) / fs, 1/fs)
#
#    # 音声波形の中心部分を切り出す
#    center = len(wav) / 2  # 中心のサンプル番号
#    cuttime = 0.04         # 切り出す長さ [s]
#    wavdata = wav[int(center - cuttime/2*fs) : int(center + cuttime/2*fs)]
#    time = t[int(center - cuttime/2*fs) : int(center + cuttime/2*fs)]
#
#    # 波形をプロット
#    plot(time * 1000, wavdata)
#    xlabel("time [ms]")
#    ylabel("amplitude")
#    savefig("waveform.png")
#    show()
#############
#    # プリエンファシスフィルタをかける
#    import pdb;pdb.set_trace(); #for debug
#    p = 0.97         # プリエンファシス係数
#    signal = preEmphasis(signal, p)
#
