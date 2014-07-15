// Copyright 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/browser_commands_patch.h"
#include "base/metrics/user_metrics.h"
#include "base/logging.h"
#include "base/basictypes.h"
#include "base/strings/string_util.h"
#include "base/message_loop/message_loop.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/browser_navigator.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/user_metrics.h"

#define DCHECK_UI_THREAD() \
  DCHECK(base::MessageLoop::current()->type() == base::MessageLoop::TYPE_UI)

namespace {
Browser* GetLastActiveBrowser() {
  Browser* browser =
      BrowserList::GetInstance(chrome::GetActiveDesktop())->GetLastActive();
  if (!browser) {
    DCHECK(0);
    return NULL;
  }
  return browser;
}

void CloseTabSelectTask() {
  Browser* browser = GetLastActiveBrowser();
  if (browser)
    chrome::CloseTab(browser);
}
}

namespace chrome {
void OpenDragDropUrl(Browser* browser,
                     content::WebContents* web_contents,
                     const GURL& url) {
  int index = browser->tab_strip_model()->active_index();
  chrome::NavigateParams params(browser, url, content::PAGE_TRANSITION_LINK);
  params.tabstrip_index = index + 1;  //+1默认当前标签(右边)→_→打开
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

void PageUp() {
  DCHECK_UI_THREAD();
}

void PageDown() {
  DCHECK_UI_THREAD();
}

void GoPageTop() {
  DCHECK_UI_THREAD();
}

void GoPageBottom() {
  DCHECK_UI_THREAD();
}
void CloseCurrentTab() {
  DCHECK_UI_THREAD();
  // HACK (libing): please use a other way ! this way can make a bug when close
  // a popup window
  base::MessageLoop::current()->PostTask(FROM_HERE,
                                         base::Bind(&CloseTabSelectTask));
}

void CloseOtherTabs() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser && browser->type() == Browser::TYPE_TABBED) {
    browser->tab_strip_model()->ExecuteContextMenuCommand(
        browser->tab_strip_model()->active_index(),
        TabStripModel::CommandCloseOtherTabs);
  }
}

void CloseLeftTabs() {
  DCHECK_UI_THREAD();
}
void CloseRightTabs() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser && browser->type() == Browser::TYPE_TABBED) {
    browser->tab_strip_model()->ExecuteContextMenuCommand(
        browser->tab_strip_model()->active_index(),
        TabStripModel::CommandCloseTabsToRight);
  }
}
void GoBack() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser) {
    chrome::GoBack(browser, CURRENT_TAB);
  }
}
void GoForward() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser) {
    chrome::GoForward(browser, CURRENT_TAB);
  }
}
void SelectPreviousTab() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser) {
    chrome::SelectPreviousTab(browser);
  }
}
void SelectNextTab() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser) {
    chrome::SelectNextTab(browser);
  }
}
void RefreshCurrentTab() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser) {
    chrome::Reload(browser, CURRENT_TAB);
  }
}
void RestoreTab() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser) {
    chrome::RestoreTab(browser);
  }
}
void NewTab() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser) {
    chrome::NewTab(browser);
  }
}
void StopLoading() {
  DCHECK_UI_THREAD();
  Browser* browser = GetLastActiveBrowser();
  if (browser) {
    chrome::Stop(browser);
  }
}
void MinimizeWindow() {
  DCHECK_UI_THREAD();

}
}