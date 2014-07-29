// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TABS_TAB_STRIP_PATCH_H_
#define CHROME_BROWSER_UI_VIEWS_TABS_TAB_STRIP_PATCH_H_
#include "base/patch.h"
class Profile;
X_START_CLASS_PATCH(TabStrip)
 public:
void Constructor(Profile* profile) {
  profile_ = profile;
}

 private:
Profile* profile_;
X_END_CLASS_PATCH(TabStrip)

#endif