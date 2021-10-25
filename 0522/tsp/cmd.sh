#!/bin/bash -x
make
python oob4speakerdigit+RX_20200910.py -sp fhs:fms:mkk:mko:mmt:mnh:mym -tx zero:ichi:ni:san:si:go:roku:nana:hachi:kyu -L 1:2:3:4:5:6:7:8:9:10 -dr ../../12voicedata_ueki_all_k8l0 -R 1 -RX 0 -mbas 2:50:1.6:1 -s -1 -N 40 -sd s -FD SC -ns 90 -ls 10 -mel 0 -nlz norm;
#export LANG=C;export d=`date`
notify-send -t 10000 -i dialog-information -u critical 'Finish'
