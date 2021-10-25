#!/usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
def myshell(cmd): #no stop even when error occured                                
  try:
    retcode=subprocess.Popen(cmd, shell=True)
    if retcode < 0:
      print "my Child was terminated by signal:", retcode
    else:
      print "my Child returned:", retcode
  except OSError as e:
    print('Failed execution. cmd:{},e:{}'.format(cmd, e))
  return retcode.wait()

