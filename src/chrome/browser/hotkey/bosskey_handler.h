// Copyright (c) 2012 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HOTKEY_HOTKEY_HANDLER_H_
#define CHROME_BROWSER_HOTKEY_HOTKEY_HANDLER_H_

#include "build/build_config.h"
#include "ui/gfx/win/window_impl.h"
#include "ui/gfx/rect.h"

class BossKeyHandler : public gfx::WindowImpl {
 public:
  BossKeyHandler();
  ~BossKeyHandler();

  static BossKeyHandler* current();

  bool UpdateBossKeyState();

  CR_BEGIN_MSG_MAP_EX(ForegroundHelper)
  CR_MSG_WM_HOTKEY(OnHotKey)
  CR_END_MSG_MAP()

 private:
  static const int hotkey_id = 0x0000abab;

  bool Start();
  void Stop();
  void OnHotKey(int id, UINT vcode, UINT modifiers);

  bool has_hotkey_;
};

bool BossKeyHandler_UpdateBossKeyState();

#endif //CHROME_BROWSER_HOTKEY_HOTKEY_HANDLER_H_
