// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_BROWSER_COMMANDS_PATCH_H_
#define CHROME_BROWSER_UI_BROWSER_COMMANDS_PATCH_H_

#include <string>

#include "chrome/browser/devtools/devtools_toggle_action.h"
#include "chrome/browser/ui/host_desktop.h"
#include "chrome/browser/ui/tabs/tab_strip_model_delegate.h"
#include "content/public/common/page_zoom.h"
#include "ui/base/window_open_disposition.h"

class Browser;
class GURL;
class Profile;

namespace content {
class WebContents;
}

namespace chrome {
void OpenDragDropUrl(Browser* browser,
                     content::WebContents* web_contents,
                     const GURL& url);

void PageUp();
void PageDown();
void GoPageTop();
void GoPageBottom();
void CloseCurrentTab();
void CloseOtherTabs();
void CloseLeftTabs();
void CloseRightTabs();
void GoBack();
void GoForward();
void SelectPreviousTab();
void SelectNextTab();
void RefreshCurrentTab();
void RestoreTab();
void NewTab();
void StopLoading();
void MinimizeWindow();
}

#endif  // CHROME_BROWSER_UI_BROWSER_COMMANDS_PATCH_H_