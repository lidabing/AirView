// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_WEB_CONTENTS_VIEW_WIN_DELEGATE_PATCH_H_
#define CONTENT_PUBLIC_BROWSER_WEB_CONTENTS_VIEW_WIN_DELEGATE_PATCH_H_

#include "base/patch.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "ui/gfx/native_widget_types.h"

namespace content {
	class 		 XWebDragDropDelegate;
X_START_INTERFACE_PATCH(CONTENT_EXPORT, WebContentsViewDelegate)
virtual content::XWebDragDropDelegate* WebDragDropDelegate() = 0;
X_END_INTERFACE_PATCH(WebContentsViewDelegate)
}

#endif