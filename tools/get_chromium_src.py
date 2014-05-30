#!/usr/bin/env python
# Copyright (c) 2014 The AirView Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import sys
import os
import shutil

def cur_file_dir():
     #获取脚本路径
     path = sys.path[0]
     #判断为脚本文件还是py2exe编译后的文件，如果是脚本文件，则返回的是脚本的目录，如果是py2exe编译后的文件，则返回的是编译后的文件路径
     if os.path.isdir(path):
         return path
     elif os.path.isfile(path):
         return os.path.dirname(path)

def main(argv):
  root_path = cur_file_dir()
  root_path = os.path.dirname(root_path)
  root_path = os.path.dirname(root_path)
  path=root_path + "\\chromium\\"
  isExists=os.path.exists(path)
  if not isExists:
        print path+' create succed'
        os.makedirs(path)
  else:
        print path+' dir exist'
        
  src_file=cur_file_dir() + "\\.gclient"
  dest_file=  path+ ".gclient"
  print "copy:" + src_file +" to "+dest_file
  shutil.copy  (src_file, dest_file)

  #更新代码
if __name__ == '__main__':
  sys.exit(main(sys.argv))
