// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/browser_command_controller_patch.h"

#include "chrome/browser/ui/browser_command_controller.h"
#include "chrome/app/chrome_command_ids_patch.h"
#include "chrome/browser/ui/browser_commands.h"

namespace chrome {

bool
X_CLASS_PATCH_NAME(BrowserCommandController)::ExecuteCommandWithDisposition(
    int id,
    WindowOpenDisposition disposition) {
  switch (id) {
    case IDC_X_RESTORE:
      RestoreTab(that_->browser_);
      return true;

    default:
      return false;
  }
}

void X_CLASS_PATCH_NAME(BrowserCommandController)::UpdateCommandsForTabState(){
  that_->command_updater_.UpdateCommandEnabled(IDC_X_RESTORE, true);
}

}  // namespace chrome