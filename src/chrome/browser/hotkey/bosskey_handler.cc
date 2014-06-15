// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/hotkey/bosskey_handler.h"
#include "base/lazy_instance.h"
#include "base/threading/thread_local.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/events/keycodes/keyboard_code_conversion_win.h"

base::LazyInstance<base::ThreadLocalPointer<BossKeyHandler> > lazy_tls_ptr =
    LAZY_INSTANCE_INITIALIZER;

BossKeyHandler::BossKeyHandler() {
  set_window_style(WS_POPUP);
  Init(NULL, gfx::Rect());
  Start();
  lazy_tls_ptr.Pointer()->Set(this);
}

BossKeyHandler::~BossKeyHandler() {
  lazy_tls_ptr.Pointer()->Set(NULL);
  Stop();
  DestroyWindow(hwnd());
}

bool BossKeyHandler::Start() {
  has_hotkey_ = false;
#if 0
		ContentBrowserClient* browser_client = GetContentClient()->browser();
		if(!browser_client || !browser_client->GetHotkeyClient())
			return false;
		if(browser_client->GetHotkeyClient()->IsEnableHotkey()){
			ui::Accelerator accelertor = browser_client->GetHotkeyClient()->GetHotkey();
			int modifiers = 0;
			if(accelertor.IsAltDown())
				modifiers = modifiers | MOD_ALT;
			if(accelertor.IsCtrlDown())
				modifiers = modifiers |MOD_CONTROL;
			if(accelertor.IsShiftDown())
				modifiers = modifiers |MOD_SHIFT;
			if(modifiers)
				has_hotkey_ = RegisterHotKey(hwnd(), hotkey_id, modifiers, ui::WindowsKeyCodeForKeyboardCode(accelertor.key_code())) == TRUE;
		}
#endif
  return has_hotkey_;
}

void BossKeyHandler::Stop() {
  if (has_hotkey_)
    UnregisterHotKey(hwnd(), hotkey_id);
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

// Handle the registered Hotkey being pressed.
void BossKeyHandler::OnHotKey(int id, UINT vcode, UINT modifiers) {
#if 0
		ContentBrowserClient* browser_client = GetContentClient()->browser();
		if(!browser_client || !browser_client->GetHotkeyClient())
			return false;
		browser_client->GetHotkeyClient()->OnBosskeyCommand();
#endif
}

bool BossKeyHandler_UpdateBossKeyState() {
#if 0
  return content::BossKeyHandler::current()->UpdateBossKeyState();
#endif
  return false;
}
