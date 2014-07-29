// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/tabs/tab_patch.h"
#include "chrome/browser/ui/views/tabs/tab.h"
#include "chrome/browser/ui/views/tabs/tab_strip_types.h"
#include "chrome/browser/ui/views/tabs/tab_controller.h"
#include "ui/events/event.h"

bool TabPatch::OnMousePressed(const ui::MouseEvent& event, bool& handle) {
  if (event.IsLeftMouseButtonDoubleClick()
      /*&& prefs_util::IsLeftDoubleClickCloseTab()*/) {
    that_->controller_->CloseTab(that_, CLOSE_TAB_FROM_MOUSE);
    return true;
  }
  return false;
}
bool TabPatch::ShouldShowContextMenu() {
  return false;
}
bool TabPatch::OnMouseReleased(const ui::MouseEvent& event, bool& handle) {
  if (event.IsOnlyRightMouseButton()) {
    //添加一句这样的判断，防止程序退出时崩溃
    if (that_->HitTestPoint(event.location())
        /*&&prefs_util::IsRightClickedCloseTab()*/) {
      that_->controller_->CloseTab(that_, CLOSE_TAB_FROM_MOUSE);
      return true;
    }
  }
  return false;
}