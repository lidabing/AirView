// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/tab_contents/chrome_web_contents_view_delegate_views_patch.h"
#include "chrome/browser/ui/aura/tab_contents/web_drag_handler_aura.h"
content::XWebDragDropDelegate* X_CLASS_PATCH_NAME(
    ChromeWebContentsViewDelegateViews)::WebDragDropDelegate() {
  web_drag_drop_delegate_.reset(new WebDragHanlderAura());
  return web_drag_drop_delegate_.get();
  return NULL;
}