// Copyright 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/browser_commands_patch.h"
#include "base/metrics/user_metrics.h"
#include "chrome/browser/ui/browser_navigator.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "content/public/browser/user_metrics.h"

namespace chrome {
void OpenDragDropUrl(Browser* browser,
                     content::WebContents* web_contents,
                     const GURL& url) {
  int index = browser->tab_strip_model()->active_index();
  chrome::NavigateParams params(browser, url, content::PAGE_TRANSITION_LINK);
  params.tabstrip_index = index+1;//+1默认当前标签(右边)→_→打开
  //[TODO](lidabing):config this
  bool drop_before = true;
  if (drop_before) {
    params.disposition = NEW_FOREGROUND_TAB;
  } else {
    params.disposition = CURRENT_TAB;
    params.source_contents = web_contents;
  }
  params.window_action = chrome::NavigateParams::SHOW_WINDOW;
  chrome::Navigate(&params);
}
}