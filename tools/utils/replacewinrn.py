#!/usr/bin/env python
# -*- coding: cp936 -*-
# Copyright (c) 2014 The AirView Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# 替换\r\n 为 \n

import os
import sys
import re


def main(argv):
    #filename = argv[1]
    #filename = 'E:\\GitHub\\chromium\\src\\chrome\\browser\\browser_shutdown.cc'
    filename = 'E:\\GitHub\\chromium\\src\\chrome\\browser\\mouse_gesture\\mouse_gesture_window.cc'
    f = open(filename,'r+')
    all_the_lines=f.readlines()
    f.seek(0)
    f.truncate()
    print all_the_lines
    for line in all_the_lines:
      f.write(line.replace('\n','\n\'\,'))
    f.close()

if __name__ == '__main__':
  sys.exit(main(sys.argv))
