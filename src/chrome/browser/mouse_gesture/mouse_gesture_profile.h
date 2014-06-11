// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AIR_VIEW_CONTENT_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_PROFILE_H_
#define AIR_VIEW_CONTENT_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_PROFILE_H_
#include "base/basictypes.h"
#include "base/memory/singleton.h"
#include "ui/gfx/native_widget_types.h"
#include "chrome/browser/mouse_gesture/mouse_gesture.h"

class MouseGestureProfile{
public:
	static MouseGestureProfile* GetInstance() {
		return Singleton<MouseGestureProfile>::get();
	}
	MouseGestureProfile();
	~MouseGestureProfile(){}

	bool IsEnableMouseGesure();
	gfx::NativeView CurrentTabWidgetWindow();
	void OnMouseGestureAction(XMouseGestures& action);
};
#endif//