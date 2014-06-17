// Copyright (c) 2012 The AirView Authors Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/base/win/event_win_patch.h"
namespace ui {
bool IsDoubleClickMouseEvent(const base::NativeEvent& native_event) {
  return native_event.message == WM_NCLBUTTONDBLCLK ||
         native_event.message == WM_NCMBUTTONDBLCLK ||
         native_event.message == WM_NCRBUTTONDBLCLK ||
         native_event.message == WM_NCXBUTTONDBLCLK ||
         native_event.message == WM_LBUTTONDBLCLK ||
         native_event.message == WM_MBUTTONDBLCLK ||
         native_event.message == WM_RBUTTONDBLCLK ||
         native_event.message == WM_XBUTTONDBLCLK;
}
}