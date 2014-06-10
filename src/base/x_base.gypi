# Copyright (c) 2013 The AirView Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
   'conditions': [
   ['OS=="win" ',{
   'dependencies': ['../third_party/detours/detours.gyp:detours',],
   'sources': [
   'hook_manager.h',
   'hook_manager.cc',
   ],
   }],
   ],
   'sources': [
        'patch.cc',
        'patch.h',
      ],
}