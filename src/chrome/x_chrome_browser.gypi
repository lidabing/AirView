#Copyright(c)2014 The AirView Authors.All rights reserved.
#Use of this source code is governed by a BSD - style license that can be
#found in the LICENSE file.
{
  'conditions'
      :[
         [
           'OS=="win" ',
           {
             'dependencies' :[ '../third_party/detours/detours.gyp:detours', ],
             'sources' :[
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
               'browser/hotkey/bosskey_handler.cc',
               'browser/hotkey/bosskey_handler.h',
			   'browser/hotkey/bosskey_profile.cc',
			   'browser/hotkey/bosskey_profile.h',
             ],
           }
         ],
       ],
       'sources' :[
                    'browser/x_chrome_browser_main_extra_parts.cc',
                    'browser/x_chrome_browser_main_extra_parts.h',
					'browser/prefs/x_browser_prefs.h',
					'browser/prefs/x_browser_prefs.cc',
					'browser/mouse_gesture/mouse_gesture_common.h',
					'browser/mouse_gesture/mouse_gesture_common.cc',
                  ]
}