// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/web_contents/web_contents_view_aura_patch.h"
#include "content/browser/web_contents/web_contents_view_aura.h"

namespace content {
void X_CLASS_PATCH_NAME(WebContentsViewAura)::Constructor(
    aura::client::DragDropDelegate* dest) {
  web_drag_dest_delegate_ = dest;
}
void X_CLASS_PATCH_NAME(WebContentsViewAura)::OnDragEntered(
    const ui::DropTargetEvent& event) {
}
int X_CLASS_PATCH_NAME(WebContentsViewAura)::OnDragUpdated(
    const ui::DropTargetEvent& event) {
  // that_->current_drag_op_ = blink::WebDragOperationMove;
  return 1;
}
void X_CLASS_PATCH_NAME(WebContentsViewAura)::OnDragExited() {
}
int X_CLASS_PATCH_NAME(WebContentsViewAura)::OnPerformDrop(
    const ui::DropTargetEvent& event) {
  return 1;
}
}