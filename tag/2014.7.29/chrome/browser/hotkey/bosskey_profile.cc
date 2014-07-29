// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/hotkey/bosskey_profile.h"
#include "ui/base/accelerators/accelerator_serialization.h"

bool BosskeyProfile::IsEnableHotkey() {
  return true;
}

ui::Accelerator BosskeyProfile::GetHotkey() {
  std::string value("81|4");
  ui::Accelerator accelertor = ui::StringToAccelerator(value);
  return accelertor;
}