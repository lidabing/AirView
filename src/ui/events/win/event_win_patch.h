// Copyright (c) 2014 The AirView Authors Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENT_WIN_PATCH_H_
#define UI_EVENT_WIN_PATCH_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/event_types.h"

namespace ui {
bool IsDoubleClickMouseEvent(const base::NativeEvent& native_event);
}
#endif  // UI_EVENT_WIN_PATCH_H_