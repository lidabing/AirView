// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/web_contents/web_contents_view_aura_patch.h"
#include "content/browser/web_contents/web_contents_view_aura.h"

namespace content {
void WebContentsViewAuraPatch::OnDragEntered(const ui::DropTargetEvent& event) {
}
int WebContentsViewAuraPatch::OnDragUpdated(const ui::DropTargetEvent& event) {
	//that_->current_drag_op_ = blink::WebDragOperationMove;
  return 1;
}
void WebContentsViewAuraPatch::OnDragExited() {
}
int WebContentsViewAuraPatch::OnPerformDrop(const ui::DropTargetEvent& event) {
	return 1;
}
}