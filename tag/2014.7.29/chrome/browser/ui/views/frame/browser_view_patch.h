// Copyright (c) 2013 The f1Brower Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AIRVIEW_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_PATCH_H_
#define AIRVIEW_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_PATCH_H_

#include "base/compiler_specific.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include <vector>
#include "url/gurl.h"

class BrowserView;

namespace views {
class View;
}
class BrowserViewPatch {
 public:
  BrowserViewPatch(BrowserView* that);
  ~BrowserViewPatch();

 private:
  friend class BrowserView;
  BrowserView* that_;

  DISALLOW_COPY_AND_ASSIGN(BrowserViewPatch);
};
#endif  // AIRVIEW_CHROME_BROWSER_UI_VIEWS_FRAME_BROWSER_VIEW_PATCH_H_