# Copyright (c) 2014 The AirView Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
{
 'conditions': [
      ['OS=="win" ',{
             'sources': [
             'browser/mouse_gesture/mouse_gesture.cc',
             'browser/mouse_gesture/mouse_gesture.h',
			 'browser/mouse_gesture/mouse_gesture_hook.cc',
			 'browser/mouse_gesture/mouse_gesture_hook.h',
			 'browser/mouse_gesture/mouse_gesture_window.cc',
			 'browser/mouse_gesture/mouse_gesture_window.h',
			 'browser/mouse_gesture/mouse_gesture_commands.cc',
			 'browser/mouse_gesture/mouse_gesture_commands.h',
			 'browser/mouse_gesture/mouse_gesture_profile.cc',
			 'browser/mouse_gesture/mouse_gesture_profile.h',
                         ],
                      } ],
   ],
}