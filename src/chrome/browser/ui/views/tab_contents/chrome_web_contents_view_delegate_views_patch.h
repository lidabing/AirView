// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TAB_CONTENTS_CHROME_WEB_CONTENTS_VIEW_DELEGATE_VIEWS_PATCH_H_
#define CHROME_BROWSER_UI_VIEWS_TAB_CONTENTS_CHROME_WEB_CONTENTS_VIEW_DELEGATE_VIEWS_PATCH_H_

#include "base/patch.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/wm/public/drag_drop_delegate.h"
#include "content/public/browser/web_contents_view_delegate_patch.h"

X_START_CLASS_PATCH_(ChromeWebContentsViewDelegateViews,
                     X_INTERFACE_PATCH_NAME_(content, WebContentsViewDelegate))
 public:
// X_INTERFACE_PATCH_NAME(WebContentsViewDelegate)
virtual aura::client::DragDropDelegate* WebDragDropDelegate() OVERRIDE;

 private:
//scoped_ptr<aura::client::DragDropDelegate> web_drag_drop_delegate_;

X_END_CLASS_PATCH(ChromeWebContentsViewDelegateViews)

#endif