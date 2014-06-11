// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/mouse_gesture/mouse_gesture.h"
#include "base/win/metro.h"
#include "ui/gfx/point.h"
#include "ui/gfx/rect.h"
#include "base/logging.h"
#include "chrome/browser/mouse_gesture/mouse_gesture_window.h"
#include "chrome/browser/mouse_gesture/mouse_gesture_client.h"
#include "chrome/browser/mouse_gesture/mouse_gesture_profile.h"

namespace {
	bool MoveDirection(gfx::Point& point, gfx::Point& origin, XDirection& direction){
		int x = point.x() - origin.x();
		int y = point.y() - origin.y();
		int dist = x*x + y*y;
		if (dist > 64){
			if (x > abs(y) && x > 0)
				direction = MGD_RIGHT;//right
			else if (abs(x) > abs(y) && x < 0)
				direction = MGD_LEFT;//left
			else if (y > abs(x) && y > 0)
				direction = MGD_DOWN;//down
			else if (abs(y) > abs(x) && y < 0)
				direction = MGD_UP;//up
			else
				return false;
			return true;
		}
		else
			return false;
	}

	void PathToDirection(XMousePath& path, XMouseGestures& out){
		out.clear();
		XMouseGestures mouse_gestures;   //鼠标手势集合
		gfx::Point  origin(path.front().x, path.front().y);
		XMousePath::const_iterator iter = path.begin();
		XDirection   last_direction = MGD_NONE;       //最后一次的动作
		for (; iter != path.end(); iter++){
			gfx::Point  pt(iter->x, iter->y);
			XDirection   direction;
			if (MoveDirection(pt, origin, direction)){
				if (last_direction != direction){
					last_direction = direction;
					out.push_back(direction);
				}
				origin = pt;
			}
		}
	}
}

MouseGesture::MouseGesture(){
	window_ = NULL;
	dest_window_ = NULL;
}
void MouseGesture::SetDestWindow(HWND dest_window){
	DCHECK(::IsWindow(dest_window));
	dest_window_ = dest_window;
	window_ = NULL;
}
bool MouseGesture::IsMouseGestureWindowShow(){
	return window_ != NULL;
}
bool MouseGesture::DownEvent(const MSG*	msg){
	if (!MouseGestureProfile::GetInstance()->IsEnableMouseGesure())
		return true;
	SetCapture(msg->hwnd);
	POINT pt = msg->pt;
	RECT rect;
	::GetWindowRect(msg->hwnd, &rect);

	if (window_){
		if (window_->IsWindow())
			window_->DestroyWindow();
		delete window_;
		window_ = NULL;
	}
	window_ = new MouseGestureWindow();
	window_->Init(msg->hwnd);
	if (!window_->IsWindow()){
		HWND parent_wnd = base::win::IsMetroProcess() ? msg->hwnd : NULL;
		if (window_->Create(
			parent_wnd,
			rect, L"MouseGestureWindow",
			WS_POPUP | WS_DISABLED,
			WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED) == NULL)
			return false;

		window_->OnRButtonDown(msg);
		window_->ShowWindow(SW_SHOWNA);
	}
	return true;
}
bool MouseGesture::MoveEvent(const MSG*	msg){
	if (!MouseGestureProfile::GetInstance()->IsEnableMouseGesure())
		return true;

	if (window_){
		window_->OnMouseMove(msg);
	}
	return true;
}
bool MouseGesture::UpEvent(const MSG*	msg){
	if (!MouseGestureProfile::GetInstance()->IsEnableMouseGesure())
		return true;
	ReleaseCapture();
	bool handle = true;
	XMouseGestures out;
	if (window_){
		XMousePath& path = window_->GetPath();
		//识别图形
		PathToDirection(path, out);
		//判断鼠标是否在一定范围内，如果没有超出范围弹出菜单
		gfx::Rect runMenuRect(path.front().x - 2, path.front().y - 2, 4, 4);
		XMousePath::const_iterator iter = path.begin();
		for (; iter != path.end(); iter++){
			if (!runMenuRect.Contains(iter->x, iter->y)){
				handle = false;
				break;
			}
		}
		//销毁窗口等事件消息
		window_->OnRButtonUp(msg);
		if (window_->IsWindow())
			window_->DestroyWindow();
		delete window_;
		window_ = NULL;
	}
	MouseGestureProfile::GetInstance()->OnMouseGestureAction(out);
	return handle;
}
void MouseGesture::CancelEvent(){
	if (!MouseGestureProfile::GetInstance()->IsEnableMouseGesure())
		return;
	if (window_->IsWindow()){
		window_->DestroyWindow();
		delete window_;
		window_ = NULL;
	}
}