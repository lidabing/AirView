// Copyright (c) 2012 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HOTKEY_HOTKEY_HANDLER_H_
#define CHROME_BROWSER_HOTKEY_HOTKEY_HANDLER_H_

#include "build/build_config.h"
#include "ui/gfx/win/singleton_hwnd.h"
#include "ui/gfx/rect.h"

class BossKeyHandler : public gfx::SingletonHwnd::Observer {
 public:
  BossKeyHandler();
  ~BossKeyHandler();

  static BossKeyHandler* current();

  bool UpdateBossKeyState();

  // The implementation of our Window Proc, called by SingletonHwnd.
  virtual void OnWndProc(HWND hwnd,
                         UINT message,
                         WPARAM wparam,
                         LPARAM lparam) OVERRIDE;

 private:
  static const int hotkey_id = 0x0000acac;
  bool Start();
  void Stop();
  void OnBossKey();

  bool has_hotkey_;
  bool is_listening_;

 private:
  DISALLOW_COPY_AND_ASSIGN(BossKeyHandler);
};

bool BossKeyHandler_UpdateBossKeyState();

#endif  // CHROME_BROWSER_HOTKEY_HOTKEY_HANDLER_H_
