// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_X_WEB_DRAG_DROP_DELEGATE_H_
#define CONTENT_PUBLIC_BROWSER_X_WEB_DRAG_DROP_DELEGATE_H_

#include "content/common/content_export.h"
#include "ui/gfx/native_widget_types.h"

namespace ui {
class DropTargetEvent;
}

namespace content {
class WebContents;
// Delegate interface for drag and drop actions on aura::Window.
class CONTENT_EXPORT XWebDragDropDelegate {
 public:
  virtual void DragInitialize(content::WebContents* contents) = 0;
  // OnDragEntered is invoked when the mouse enters this window during a drag &
  // drop session. This is immediately followed by an invocation of
  // OnDragUpdated, and eventually one of OnDragExited or OnPerformDrop.
  virtual void OnDragEntered(const ui::DropTargetEvent& event) = 0;

  // Invoked during a drag and drop session while the mouse is over the window.
  // This should return a bitmask of the DragDropTypes::DragOperation supported
  // based on the location of the event. Return 0 to indicate the drop should
  // not be accepted.
  virtual int OnDragUpdated(const ui::DropTargetEvent& event) = 0;

  // Invoked during a drag and drop session when the mouse exits the window, or
  // when the drag session was canceled and the mouse was over the window.
  virtual void OnDragExited() = 0;

  // Invoked during a drag and drop session when OnDragUpdated returns a valid
  // operation and the user release the mouse.
  virtual int OnPerformDrop(const ui::DropTargetEvent& event) = 0;

  virtual ~XWebDragDropDelegate() {}
};

}  // namespace content

#endif  // CONTENT_PUBLIC_BROWSER_X_WEB_DRAG_DROP_DELEGATE_H_
