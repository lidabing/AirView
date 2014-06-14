// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/chrome_browser_main_extra_parts_airview.h"
#include "chrome/browser/chrome_browser_main.h"
#if defined(OS_WIN)
#include "chrome/browser/mouse_gesture/mouse_gesture_hook.h"
#endif
namespace chrome {
void AddAirViewExtraParts(ChromeBrowserMainParts* main_parts) {
  main_parts->AddParts(new BrowserMainExtraPartsAirView());
}
}

void BrowserMainExtraPartsAirView::PreEarlyInitialization() {
#if defined(OS_WIN)
  hook_manager_.Register(new MouseGestureHook());
  hook_manager_.Install();
#endif
}
void BrowserMainExtraPartsAirView::PostEarlyInitialization() {
}

void BrowserMainExtraPartsAirView::PostMainMessageLoopRun() {
#if defined(OS_WIN)
  hook_manager_.UnInstall();
#endif
}