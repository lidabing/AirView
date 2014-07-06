// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/x_chrome_browser_main_extra_parts.h"
#include "chrome/browser/chrome_browser_main.h"
#include "base/logging.h"
#if defined(OS_WIN)
#include "chrome/browser/mouse_gesture/mouse_gesture_hook.h"
#include "chrome/browser/hotkey/bosskey_handler.h"
#endif
namespace chrome {
void AddXExtraParts(ChromeBrowserMainParts* main_parts) {
  main_parts->AddParts(new XBrowserMainExtraParts());
}
}

void XBrowserMainExtraParts::PreEarlyInitialization() {
#if defined(OS_WIN)
  hook_manager_.Register(new MouseGestureHook());
  hook_manager_.Install();
#endif
}
void XBrowserMainExtraParts::PostEarlyInitialization() {
}

void XBrowserMainExtraParts::PostMainMessageLoopRun() {
#if defined(OS_WIN)
  hook_manager_.UnInstall();
#endif
}

void XBrowserMainExtraParts::PreMainMessageLoopStart() {
}

void XBrowserMainExtraParts::PostMainMessageLoopStart() {
#if defined(OS_WIN)
  DCHECK(!bosskey_handler_.get());
  bosskey_handler_.reset(new BossKeyHandler());
#endif
}