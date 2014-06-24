// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/web_contents/web_contents_view_aura_patch.h"
#include "content/browser/web_contents/web_contents_view_aura.h"
#include "content/public/browser/x_web_drag_drop_delegate.h"
#include "content/browser/web_contents/web_contents_impl.h"
#include "ui/events/event.h"
#include "ui/events/event_utils.h"
#include "ui/base/dragdrop/drop_target_event.h"

namespace {
	int ConvertFromWeb(blink::WebDragOperationsMask ops) {
		int drag_op = ui::DragDropTypes::DRAG_NONE;
		if (ops & blink::WebDragOperationCopy)
			drag_op |= ui::DragDropTypes::DRAG_COPY;
		if (ops & blink::WebDragOperationMove)
			drag_op |= ui::DragDropTypes::DRAG_MOVE;
		if (ops & blink::WebDragOperationLink)
			drag_op |= ui::DragDropTypes::DRAG_LINK;
		return drag_op;
	}

	blink::WebDragOperationsMask ConvertToWeb(int drag_op) {
		int web_drag_op = blink::WebDragOperationNone;
		if (drag_op & ui::DragDropTypes::DRAG_COPY)
			web_drag_op |= blink::WebDragOperationCopy;
		if (drag_op & ui::DragDropTypes::DRAG_MOVE)
			web_drag_op |= blink::WebDragOperationMove;
		if (drag_op & ui::DragDropTypes::DRAG_LINK)
			web_drag_op |= blink::WebDragOperationLink;
		return (blink::WebDragOperationsMask) web_drag_op;
	}
}
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
		if (that_->current_drag_op_ == blink::WebDragOperationNone)
			that_->current_drag_op_ = blink::WebDragOperationLink;
		
  return 1;
}
void X_CLASS_PATCH_NAME(WebContentsViewAura)::OnDragExited() {
	web_drag_dest_delegate_->OnDragExited();
}
int X_CLASS_PATCH_NAME(WebContentsViewAura)::OnPerformDrop(
    const ui::DropTargetEvent& event) {
	if (that_->current_drag_op_ == blink::WebDragOperationNone)
	  web_drag_dest_delegate_->OnPerformDrop(event);
  return 1;
}
}