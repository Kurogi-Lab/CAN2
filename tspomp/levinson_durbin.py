#coding:utf-8
#https://aidiary.hatenablog.com/entry/20120415/1334458954
import numpy as np
from pylab import *
import pandas as pd #for pandas see http://keisanbutsuriya.hateblo.jp/entry/201\
import argparse
import subprocess

def myshell(cmd): #no stop even when error occured
  try:
    retcode=subprocess.Popen(cmd, shell=True)
    if retcode < 0:
        pass #print "my Child was terminated by signal", -retcode
    else:
        pass #print "my Child returned", retcode
  except OSError as e:
    print "Execution failed:", cmd, e
  return retcode.wait()

def mypltshow(fnfig):
  plt.savefig(fnfig);
  myshell("sleep 1;gv "+fnfig+"&");
  plt.close() #plt.show()

def autocorr(x, nlags=None):
    """自己相関関数を求める
    x:     信号
    nlags: 自己相関関数のサイズ（lag=0からnlags-1まで）
           引数がなければ（lag=0からlen(x)-1まですべて）
    """
    N = len(x)
    if nlags == None: nlags = N
    r = np.zeros(nlags)
    for lag in range(nlags):
        for n in range(N - lag):
            r[lag] += x[n] * x[n + lag]
    return r

def LevinsonDurbin(r, lpcOrder):
    """Levinson-Durbinのアルゴリズム
    k次のLPC係数からk+1次のLPC係数を再帰的に計算して
    LPC係数を求める"""
    # LPC係数（再帰的に更新される）
    # a[0]は1で固定のためlpcOrder個の係数を得るためには+1が必要
    a = np.zeros(lpcOrder + 1)
    e = np.zeros(lpcOrder + 1)

    # k = 1の場合
    a[0] = 1.0
    a[1] = - r[1] / r[0]
    e[1] = r[0] + r[1] * a[1]
    lam = - r[1] / r[0]

    # kの場合からk+1の場合を再帰的に求める
    for k in range(1, lpcOrder):
        # lambdaを更新
        lam = 0.0
        for j in range(k + 1):
            lam -= a[j] * r[k + 1 - j]
        lam /= e[k]

        # aを更新
        # UとVからaを更新
        U = [1]
        U.extend([a[i] for i in range(1, k + 1)])
        U.append(0)

        V = [0]
        V.extend([a[i] for i in range(k, 0, -1)])
        V.append(1)

        a = np.array(U) + lam * np.array(V)

        # eを更新
        e[k + 1] = e[k] * (1.0 - lam * lam)

    return a, e[-1]

if __name__ == "__main__":
    original = np.zeros(128)
    parser = argparse.ArgumentParser(description='levinson_durbin')
    parser.add_argument('-yin', default='', type=str,   help='yin')
    parser.add_argument('-k', default=32, type=int,   help='lpcOrdar')

    args = parser.parse_args()
    if args.yin == "":
      for i in range(len(original)):
        original[i] = np.sin(i * 0.01) + 0.75 * np.sin(i * 0.03) + 0.5 * np.sin(i * 0.05) + 0.25 * np.sin(i * 0.11)
    else:
        yin=np.array(pd.read_csv(args.yin,delim_whitespace=True,dtype=np.float64,header=None)).reshape((-1,))
        original=yin[500:-500]
    lpcOrder = 16  # LPC係数の次数
    lpcOrder = args.k  # LPC係数の次数

    # 自己相関関数を計算
    # r[0]からr[lpcOrder]までlpcOrder+1個必要
    r = autocorr(original, lpcOrder + 1)
    for i in range(lpcOrder + 1):
        print "r[%d]: %f" % (i, r[i])

    # Levinson-Durbinアルゴリズムを用いてLPC係数と最小誤差を計算
    a, e = LevinsonDurbin(r, lpcOrder)
    print "*** result ***"
    print "a:", a
    print "e:", e
    plot(a)
    mypltshow("LPC.eps");
#    show()
#    import pdb;pdb.set_trace(); #for debug

    # LPCで前向き予測した信号を求める
    predicted = np.copy(original)
    # 過去lpcOrder分から予測するので開始インデックスはlpcOrderから
    # それより前は予測せずにオリジナルの信号をコピーしている
    for i in range(lpcOrder, len(predicted)):
        predicted[i] = 0.0
        for j in range(1, lpcOrder):
            predicted[i] -= a[j] * original[i - 1 - j]

    # オリジナルの信号をプロット
    plot(original)
    # LPCで前向き予測した信号をプロット
    plot(predicted)
    mypltshow("yLPC.eps");
#    show()
