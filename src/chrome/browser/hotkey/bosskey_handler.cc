// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/hotkey/bosskey_handler.h"
#include "base/lazy_instance.h"
#include "base/threading/thread_local.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/events/keycodes/keyboard_code_conversion_win.h"
#include "chrome/browser/hotkey/bosskey_profile.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/render_widget_host_view.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"

base::LazyInstance<base::ThreadLocalPointer<BossKeyHandler> > lazy_tls_ptr =
    LAZY_INSTANCE_INITIALIZER;

BossKeyHandler::BossKeyHandler() {
  gfx::SingletonHwnd::GetInstance()->AddObserver(this);
  is_listening_ = true;
  Start();
  lazy_tls_ptr.Pointer()->Set(this);
}

BossKeyHandler::~BossKeyHandler() {
  lazy_tls_ptr.Pointer()->Set(NULL);
  Stop();
  is_listening_ = false;
  gfx::SingletonHwnd::GetInstance()->RemoveObserver(this);
}

bool BossKeyHandler::Start() {
  has_hotkey_ = false;
  if (BosskeyProfile::GetInstance()->IsEnableHotkey()) {
    ui::Accelerator accelerator = BosskeyProfile::GetInstance()->GetHotkey();
    int modifiers = 0;
    modifiers |= accelerator.IsShiftDown() ? MOD_SHIFT : 0;
    modifiers |= accelerator.IsCtrlDown() ? MOD_CONTROL : 0;
    modifiers |= accelerator.IsAltDown() ? MOD_ALT : 0;

    if (modifiers) {
      bool success =
          !!RegisterHotKey(
               gfx::SingletonHwnd::GetInstance()->hwnd(),
               hotkey_id,
               modifiers,
               ui::KeyboardCodeForWindowsKeyCode(accelerator.key_code()));
      has_hotkey_ = success;
    }
  }
  return has_hotkey_;
}

void BossKeyHandler::Stop() {
  if (has_hotkey_) {
    bool success = !!UnregisterHotKey(gfx::SingletonHwnd::GetInstance()->hwnd(),
                                      hotkey_id);
    // This call should always succeed, as long as we pass in the right HWND and
    // an id we've used to register before.
    DCHECK(success);
  }
}

void BossKeyHandler::OnWndProc(HWND hwnd,
                               UINT message,
                               WPARAM wparam,
                               LPARAM lparam) {
  if (message != WM_HOTKEY)
    return;

  int key_code = HIWORD(lparam);
  int modifiers = 0;
  modifiers |= (LOWORD(lparam) & MOD_SHIFT) ? ui::EF_SHIFT_DOWN : 0;
  modifiers |= (LOWORD(lparam) & MOD_ALT) ? ui::EF_ALT_DOWN : 0;
  modifiers |= (LOWORD(lparam) & MOD_CONTROL) ? ui::EF_CONTROL_DOWN : 0;
  ui::Accelerator accelerator(ui::KeyboardCodeForWindowsKeyCode(key_code),
                              modifiers);
  ui::Accelerator boss_accelerator = BosskeyProfile::GetInstance()->GetHotkey();
  if (accelerator == boss_accelerator) {
    OnBossKey();
  }
}

// static
BossKeyHandler* BossKeyHandler::current() {
  return lazy_tls_ptr.Pointer()->Get();
}

bool BossKeyHandler::UpdateBossKeyState() {
  Stop();
  Start();
  return true;
}

// Handle the registered OnBossKey being pressed.
void BossKeyHandler::OnBossKey() {
  static bool all_browser_hide = false;
  BrowserList* browser_list =
      BrowserList::GetInstance(chrome::GetActiveDesktop());
  if (!browser_list)
    return;
  if (!all_browser_hide) {
    all_browser_hide = true;
    //在这里隐藏所有窗口
    BrowserList::const_iterator iter = browser_list->begin();
    for (; iter != browser_list->end(); iter++) {
      (*iter)->window()->Show();
      // (*iter)->window()->OnBossKeyShow(false);
    }
  } else {
    all_browser_hide = false;
    //在这里显示所有窗口
    BrowserList::const_iterator iter = browser_list->begin();
    for (; iter != browser_list->end(); iter++) {
      (*iter)->window()->Hide();
      // (*iter)->window()->OnBossKeyShow(true);
    }
  }
}

bool BossKeyHandler_UpdateBossKeyState() {
  return BossKeyHandler::current()->UpdateBossKeyState();
}
