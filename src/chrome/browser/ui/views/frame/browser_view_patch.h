// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_PATCH_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_PATCH_H_

#include "base/patch.h"
#include "base/compiler_specific.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include <vector>
#include "url/gurl.h"

class BrowserView;

namespace views {
class View;
}

X_START_CLASS_PATCH(BrowserView)
 public:
	 void OnBossKeyShow(bool show);

X_END_CLASS_PATCH(BrowserView)

#endif  // CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_PATCH_H_