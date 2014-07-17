// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_BROWSER_COMMAND_CONTROLLER_PATCH_H_
#define CHROME_BROWSER_UI_BROWSER_COMMAND_CONTROLLER_PATCH_H_

#include "base/patch.h"
#include "ui/base/window_open_disposition.h"
#include "chrome/browser/ui/browser.h"

namespace chrome {

X_START_CLASS_PATCH(BrowserCommandController)
 public:
  bool ExecuteCommandWithDisposition(int id, WindowOpenDisposition disposition);
  void UpdateCommandsForTabState();

 private:

X_END_CLASS_PATCH(BrowserCommandController)

}  // namespace chrome

#endif  //CHROME_BROWSER_UI_BROWSER_COMMAND_CONTROLLER_PATCH_H_