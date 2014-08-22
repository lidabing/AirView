#!/usr/bin/env python
# -*- coding: cp936 -*-
# Copyright (c) 2014 The AirView Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.


import sys
import os
import shutil
import subprocess
import sys

def cur_file_dir():
        #获取脚本路径
        path = sys.path[0]
        #判断为脚本文件还是py2exe编译后的文件，如果是脚本文件，则返回的是脚本的目录，如果是py2exe编译后的文件，则返回的是编译后的文件路径
        if os.path.isdir(path):
                 return path
        elif os.path.isfile(path):
                 return os.path.dirname(path)

def main():
    code_dir = cur_file_dir()
    code_dir = os.path.dirname(code_dir)
    code_dir = code_dir + "\\src";

    clang_file = cur_file_dir()
    clang_file = clang_file + "\\clang_format\\bin\\win\\clang-format.exe";

    for root, dirs, files in os.walk(code_dir, True):
        for name in files:
            code_file = os.path.join(root,name)
            startupinfo = None
            if sys.platform.startswith('win32'):
                startupinfo = subprocess.STARTUPINFO()
                startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
                startupinfo.wShowWindow = subprocess.SW_HIDE
            command = clang_file +' -style=Chromium -i ' + code_file
            #command = [clang_file, '-style=Chromium', '-i',code_file]
            print command
            p = subprocess.Popen(command,stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE,
                                 stdin=subprocess.PIPE,
                                 startupinfo=startupinfo,shell=True)
            
            
           

main()
