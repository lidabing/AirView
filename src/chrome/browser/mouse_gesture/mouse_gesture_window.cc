// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/mouse_gesture/mouse_gesture_window.h"

#include <windows.h>
#include <windef.h>
#include <atlgdi.h>
#include <windowsx.h>
#include <math.h>
#include "base/logging.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/gfx/canvas_skia_paint.h"
#include "ui/gfx/path.h"

MouseGestureWindow::MouseGestureWindow() : should_draw_line_(false) {
}
void MouseGestureWindow::OnCaptureChanged(CWindow window) {
}
BOOL MouseGestureWindow::OnEraseBkgnd(CDCHandle dc) {
  return TRUE;
}

void MouseGestureWindow::OnPaintSkia() {
  HDC hdc = this->GetDC();
  ::RECT rect;
  ::GetClientRect(event_window_, &rect);
  int weight = rect.right - rect.left;
  int height = rect.bottom - rect.top;
  HDC memdc = ::CreateCompatibleDC(hdc);
  HBITMAP memmap = ::CreateCompatibleBitmap(hdc, weight, height);
  ::SelectObject(memdc, memmap);

  SkPaint paint;
  paint.setAntiAlias(true);
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setStrokeWidth(4.0F);
  paint.setColor(SkColorSetRGB(153, 204, 0));

  gfx::Canvas canvas(gfx::Size(weight, height), 1.0f, false);
  SkCanvas* sk_canvas = canvas.sk_canvas();
  sk_canvas->getDevice()->accessBitmap(true).eraseARGB(0, 0, 0, 0);

  gfx::Path path;
  if (!path_.empty()) {
    path.moveTo(SkIntToScalar(path_[0].x), SkIntToScalar(path_[0].y));
    for (size_t i = 0; i < path_.size(); i++) {
      int x = path_[i].x;
      int y = path_[i].y;
      path.lineTo(SkIntToScalar(x), SkIntToScalar(y));
      path.moveTo(SkIntToScalar(x), SkIntToScalar(y));
    }
  }
  path.close();

  sk_canvas->drawPath(path, paint);
  skia::DrawToNativeContext(sk_canvas, memdc, 0, 0, NULL);

  POINT pt;
  POINT src_point = {0, 0};
  ::GetWindowRect(event_window_, &rect);
  rect.right -= rect.left;
  rect.bottom -= rect.top;
  pt.x = rect.left;
  pt.y = rect.top;

  BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
  LPPOINT lp_rect = reinterpret_cast<LPPOINT>(&rect);
  ::UpdateLayeredWindow(m_hWnd,
                        NULL,
                        lp_rect,
                        reinterpret_cast<LPSIZE>(lp_rect + 1),
                        memdc,
                        &src_point,
                        RGB(125, 125, 125),
                        &blend,
                        ULW_ALPHA);

  ::DeleteDC(memdc);
  ::ReleaseDC(m_hWnd, hdc);
  ::DeleteObject(memmap);
}

LRESULT MouseGestureWindow::OnPaint(UINT uMsg,
                                    WPARAM wParam,
                                    LPARAM lParam,
                                    BOOL& bHandled) {
  if (should_draw_line_)
    OnPaintSkia();
  return 0;
}

bool MouseGestureWindow::OnRButtonDown(const MSG* msg) {
  POINT pt;
  pt.x = LOWORD(msg->lParam);
  pt.y = HIWORD(msg->lParam);
  if (pt.y > event_window_rect_.bottom || pt.x > event_window_rect_.right ||
      pt.x < 0 || pt.y < 0)
    return true;

  path_.push_back(pt);
  should_draw_line_ = false;

  return should_draw_line_;
}

bool MouseGestureWindow::OnRButtonUp(const MSG* msg) {
  return false;
}

bool MouseGestureWindow::OnMouseMove(const MSG* msg) {
  POINT pt;
  pt.x = LOWORD(msg->lParam);
  pt.y = HIWORD(msg->lParam);
  if (path_.empty()) {
    path_.push_back(pt);
    should_draw_line_ = false;
    return true;
  }
  if (Get2PointDistance(path_[path_.size() - 1], pt) > 10)
    path_.push_back(pt);

  if (!should_draw_line_) {
    POINT start = path_[0];
    POINT end = path_[path_.size() - 1];
    if (Get2PointDistance(start, end) > 5) {
      should_draw_line_ = true;
      OnPaintSkia();
    }
  } else {
    OnPaintSkia();
  }
  return 0;
}

LRESULT MouseGestureWindow::OnDestroy(UINT uMsg,
                                      WPARAM wParam,
                                      LPARAM lParam,
                                      BOOL& bHandled) {
  return 1;
}

LRESULT MouseGestureWindow::OnCreate(UINT uMsg,
                                     WPARAM wParam,
                                     LPARAM lParam,
                                     BOOL& bHandled) {
  return 0;
}

int MouseGestureWindow::Get2PointDistance(POINT& start_point,
                                          POINT& end_point) {
  return static_cast<int>(sqrtl(
      abs(end_point.x - start_point.x) * abs(end_point.x - start_point.x) +
      abs(end_point.y - start_point.y) * abs(end_point.y - start_point.y)));
}
void MouseGestureWindow::Init(HWND event_window) {
  event_window_ = event_window;
  ::GetWindowRect(event_window_, &event_window_rect_);
}

XMousePath& MouseGestureWindow::GetPath() {
  return path_;
}