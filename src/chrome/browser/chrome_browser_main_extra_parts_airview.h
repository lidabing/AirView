// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROME_BROWSER_MAIN_EXTRA_PARTS_AIRVIEW_H_
#define CHROME_BROWSER_CHROME_BROWSER_MAIN_EXTRA_PARTS_AIRVIEW_H_
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#if defined(OS_WIN)
#include "base/hook_manager.h"
#include "chrome/browser/hotkey/bosskey_handler.h"
#endif
#include "chrome/browser/chrome_browser_main_extra_parts.h"

class ChromeBrowserMainParts;
class BossKeyHandler;

namespace chrome {
void AddAirViewExtraParts(ChromeBrowserMainParts* main_parts);
}

class BrowserMainExtraPartsAirView : public ChromeBrowserMainExtraParts {
 public:
  BrowserMainExtraPartsAirView() {}
  virtual ~BrowserMainExtraPartsAirView() {}

  // Overridden from ChromeBrowserMainExtraParts:
  virtual void PreEarlyInitialization() OVERRIDE;
  virtual void PostEarlyInitialization() OVERRIDE;
  virtual void PostMainMessageLoopRun() OVERRIDE;
  virtual void PreMainMessageLoopStart() OVERRIDE;
  virtual void PostMainMessageLoopStart() OVERRIDE;

 private:
#if defined(OS_WIN)
  scoped_ptr<BossKeyHandler> bosskey_handler_;
  base::HookManager hook_manager_;
#endif
  DISALLOW_COPY_AND_ASSIGN(BrowserMainExtraPartsAirView);
};
#endif