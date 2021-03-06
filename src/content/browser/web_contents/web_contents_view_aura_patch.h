// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TABS_TAB_STRIP_PATCH_H_
#define CHROME_BROWSER_UI_VIEWS_TABS_TAB_STRIP_PATCH_H_
#include "base/patch.h"
#include "content/public/browser/x_web_drag_drop_delegate.h"
namespace ui {
class DropTargetEvent;
}

namespace content {
X_START_CLASS_PATCH(WebContentsViewAura)
 public:
 void Constructor(XWebDragDropDelegate* dest);

 public:
void OnDragEntered(const ui::DropTargetEvent& event);
int OnDragUpdated(const ui::DropTargetEvent& event);
void OnDragExited();
int OnPerformDrop(const ui::DropTargetEvent& event);

 private:
// install drag  dest
content::XWebDragDropDelegate* web_drag_dest_delegate_;
X_END_CLASS_PATCH(WebContentsViewAura)
}
#endif