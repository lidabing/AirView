// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/web_contents/web_contents_view_aura_patch.h"
#include "content/browser/web_contents/web_contents_view_aura.h"
#include "content/public/browser/x_web_drag_drop_delegate.h"
#include "content/browser/web_contents/web_contents_impl.h"

namespace content {
void X_CLASS_PATCH_NAME(WebContentsViewAura)::Constructor(
    XWebDragDropDelegate* dest) {
  web_drag_dest_delegate_ = dest;
}
void X_CLASS_PATCH_NAME(WebContentsViewAura)::OnDragEntered(
    const ui::DropTargetEvent& event) {
  web_drag_dest_delegate_->DragInitialize(that_->web_contents_);
  web_drag_dest_delegate_->OnDragEntered(event);
}
int X_CLASS_PATCH_NAME(WebContentsViewAura)::OnDragUpdated(
    const ui::DropTargetEvent& event) {
  web_drag_dest_delegate_->OnDragUpdated(event);
  that_->current_drag_op_ = blink::WebDragOperationLink;
  return 1;
}
void X_CLASS_PATCH_NAME(WebContentsViewAura)::OnDragExited() {
  web_drag_dest_delegate_->OnDragExited();
}
int X_CLASS_PATCH_NAME(WebContentsViewAura)::OnPerformDrop(
    const ui::DropTargetEvent& event) {
  web_drag_dest_delegate_->OnPerformDrop(event);
  return 1;
}
}