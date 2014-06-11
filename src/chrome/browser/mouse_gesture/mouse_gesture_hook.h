// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AIR_VIEW_CONTENT_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_HOOK_H_
#define AIR_VIEW_CONTENT_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_HOOK_H_

#include "base/basictypes.h"
#include "base/hook_manager.h"

class MouseGestureHook : public base::HookItem{
public:
	MouseGestureHook(){}
private:
	virtual bool Install() OVERRIDE;
	virtual void UnInstall() OVERRIDE;

	DISALLOW_COPY_AND_ASSIGN(MouseGestureHook);
};
#endif //AIR_VIEW_CONTENT_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_HOOK_H_