// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AIR_VIEW_CONTENT_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_WINDOW_H_
#define AIR_VIEW_CONTENT_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_WINDOW_H_

#include <tchar.h>
#include <atlcrack.h>
#include <atltrace.h>
#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
#include <vector>
#include <string>
#include "base/basictypes.h"

//鼠标手势事件处理
typedef std::vector<POINT> XMousePath;  //鼠标轨迹路径

class MouseGestureWindow : public CWindowImpl<MouseGestureWindow> {
 public:
  MouseGestureWindow();

  DECLARE_WND_CLASS(L"MouseGestureWindowClass")
  BEGIN_MSG_MAP(MouseGestureWindow)
  MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
  MESSAGE_HANDLER(WM_CREATE, OnCreate)
  MSG_WM_ERASEBKGND(OnEraseBkgnd)
  MESSAGE_HANDLER(WM_PAINT, OnPaint)
  MSG_WM_CAPTURECHANGED(OnCaptureChanged)
  END_MSG_MAP()

  void OnCaptureChanged(CWindow window);
  BOOL OnEraseBkgnd(CDCHandle dc);
  LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

  bool OnRButtonDown(const MSG* msg);
  bool OnRButtonUp(const MSG* msg);
  bool OnMouseMove(const MSG* msg);
  void OnPaintSkia();

  int Get2PointDistance(POINT& start_point, POINT& end_point);
  void Init(HWND event_window);

  XMousePath& GetPath();

 private:
  HWND event_window_;       //事件窗口
  RECT event_window_rect_;  //事件窗口区域
  XMousePath path_;         //路径
  bool should_draw_line_;   ///是否改划线

  DISALLOW_COPY_AND_ASSIGN(MouseGestureWindow);
};

#endif  // AIR_VIEW_CONTENT_BROWSER_MOUSER_GESTURE_MOUSE_GESTURE_WINDOW_H_