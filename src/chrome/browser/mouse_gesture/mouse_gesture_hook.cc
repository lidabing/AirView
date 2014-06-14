// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/mouse_gesture/mouse_gesture_hook.h"
#include <windows.h>
#include "base/command_line.h"
#include "base/strings/string_util.h"
#include "content/public/common/content_switches.h"
#include "third_party/detours/detours.h"
#include "chrome/browser/mouse_gesture/mouse_gesture.h"

namespace {
HWND g_hwnd = NULL;  //右键点击的窗口句柄
DWORD main_thread_id = 0;
}

//== predef==============================
LRESULT WINAPI MainDispatchMessageW(const MSG* msg);
LRESULT WINAPI PluginDispatchMessageW(const MSG* msg);
LRESULT WINAPI IEDispatchMessageW(const MSG* msg);
//==predef end ==============================

// hook define=============================
static LRESULT(WINAPI* Real_DispatchMessageW)(const MSG*) = NULL;
static LRESULT WINAPI My_DispatchMessageW(const MSG* lpmsg) {
  return MainDispatchMessageW(lpmsg);
}
// plugin 进程
static LRESULT(WINAPI* RealPlugin_DispatchMessageW)(const MSG*) = NULL;
static LRESULT WINAPI MyPlugin_DispatchMessageW(const MSG* lpmsg) {
  return PluginDispatchMessageW(lpmsg);
}
// hook define end=============================

namespace {
const wchar_t kRenderWidgetHostHWNDClass[] = L"Chrome_RenderWidgetHostHWND";
bool IsRenderWindow(HWND window) {
  wchar_t window_class_name[65] = {0};
  ::GetClassNameW(window, window_class_name, 64);
  if (0 == base::strncmp16(window_class_name,
                           kRenderWidgetHostHWNDClass,
                           wcslen(kRenderWidgetHostHWNDClass)))
    return true;
  return false;
}
}

//==mouse event handler ==========================

bool RightButtonDownHandler(const MSG* msg, LRESULT& result) {
  if (IsRenderWindow(msg->hwnd)) {
    g_hwnd = msg->hwnd;
    MouseGesture::GetInstance()->SetDestWindow(msg->hwnd);
    MouseGesture::GetInstance()->DownEvent(msg);
    result = 0;
    return true;
  }

  return false;
}

bool LeftButtonDownHandler(const MSG* msg, LRESULT& result) {
  if (MouseGesture::GetInstance()->IsMouseGestureWindowShow())
    MouseGesture::GetInstance()->CancelEvent();
  return false;
}

bool RightButtonUpHandler(const MSG* msg, LRESULT& result) {
  if (MouseGesture::GetInstance()->IsMouseGestureWindowShow()) {
    do {
      bool handle = MouseGesture::GetInstance()->UpEvent(msg);
      if (!handle) {
        result = 0;
        break;
      }

      //如果手势没被处理，传递双击消息给窗口
      if (0 == GetWindowLong(g_hwnd, GWL_WNDPROC)) {
        result = 0;
        break;
      }
      MSG new_msg;
      new_msg.hwnd = g_hwnd;
      new_msg.message = WM_RBUTTONDOWN;
      new_msg.wParam = MK_RBUTTON;
      new_msg.lParam = msg->lParam;
      new_msg.time = msg->time;
      new_msg.pt = msg->pt;

      if (new_msg.pt.x < 0)
        new_msg.pt.x = 0;

      Real_DispatchMessageW(&new_msg);

      new_msg.message = WM_RBUTTONUP;
      new_msg.time = msg->time + 1;
      Real_DispatchMessageW(&new_msg);

      result = 0;
    } while (false);
    return true;
  }
  return false;
}

bool MouseMoveHandler(const MSG* msg, LRESULT& result) {
  if (MouseGesture::GetInstance()->IsMouseGestureWindowShow()) {
    if (msg->wParam & (MK_RBUTTON)) {
      MouseGesture::GetInstance()->MoveEvent(msg);
      result = 0;
      return true;
    } else {
      MouseGesture::GetInstance()->CancelEvent();
    }
  }
  return false;
}
bool LeftOrMiddleButtonDownHandler(const MSG* msg, LRESULT& result) {
  if (MouseGesture::GetInstance()->IsMouseGestureWindowShow()) {
    MouseGesture::GetInstance()->CancelEvent();
  }
  return false;
}
//==mouse event handler end ========================

//============helper fun===================
//主进程
LRESULT WINAPI MainDispatchMessageW(const MSG* msg) {
  if (main_thread_id != 0 && GetCurrentThreadId() != main_thread_id)
    return Real_DispatchMessageW(msg);
  LRESULT result;
  switch (msg->message) {
    case WM_RBUTTONDOWN:
      if (RightButtonDownHandler(msg, result))
        return result;
      break;
    case WM_LBUTTONUP:
      if (LeftButtonDownHandler(msg, result))
        return result;
      break;
    case WM_RBUTTONUP:
      if (RightButtonUpHandler(msg, result))
        return result;
      break;
    case WM_MOUSEMOVE:
      if (MouseMoveHandler(msg, result))
        return result;
      break;
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
      if (LeftOrMiddleButtonDownHandler(msg, result))
        return result;
      break;
  }
  return Real_DispatchMessageW(msg);
}
//扩展进程
LRESULT WINAPI PluginDispatchMessageW(const MSG* msg) {
  return RealPlugin_DispatchMessageW(msg);
}

//===========helper fun end====================

//== MouseGestureHook=======================
bool MouseGestureHook::Install() {
  CommandLine& command_line = *CommandLine::ForCurrentProcess();
  std::string process_type =
      command_line.GetSwitchValueASCII(switches::kProcessType);
  main_thread_id = GetCurrentThreadId();
  char* user32 = "user32.dll";
  if (process_type.empty()) {  // browser主进程
    Real_DispatchMessageW = (LRESULT(WINAPI*)(const MSG*))DetourFindFunction(
        user32, "DispatchMessageW");
    if (Real_DispatchMessageW)
      DetourAttach(&(PVOID&)Real_DispatchMessageW, My_DispatchMessageW);
  } else if (process_type == switches::kPluginProcess) {  // Plugin进程
    RealPlugin_DispatchMessageW =
        (LRESULT(WINAPI*)(const MSG*))DetourFindFunction(user32,
                                                         "DispatchMessageW");
    if (RealPlugin_DispatchMessageW)
      DetourAttach(&(PVOID&)RealPlugin_DispatchMessageW,
                   MyPlugin_DispatchMessageW);
  }
  return true;
}

void MouseGestureHook::UnInstall() {
  CommandLine& command_line = *CommandLine::ForCurrentProcess();
  std::string process_type =
      command_line.GetSwitchValueASCII(switches::kProcessType);
  if (process_type.empty()) {  // browser主进程
    if (Real_DispatchMessageW)
      DetourDetach(&(PVOID&)Real_DispatchMessageW, My_DispatchMessageW);
  } else if (process_type == switches::kPluginProcess) {  // Plugin进程
    if (RealPlugin_DispatchMessageW)
      DetourDetach(&(PVOID&)RealPlugin_DispatchMessageW,
                   MyPlugin_DispatchMessageW);
  }
}
//== MouseGestureHook end=======================
