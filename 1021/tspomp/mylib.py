#!/usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
def myshell(cmd): #no stop even when error occured                                
  try:
    retcode=subprocess.Popen(cmd, shell=True)
    if retcode < 0:
      pass #print "my Child ({}...) was terminated by signal:".format(cmd[0:20],retcode)
    else:
      pass #print "my Child ({}...) returned:{}".format(cmd[0:20],retcode)
  except OSError as e:
    print('Failed execution. cmd:{},e:{}'.format(cmd, e))
  return retcode.wait()

