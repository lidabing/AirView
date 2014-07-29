// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MOUSER_BOSSKEY_PROFILE_H_
#define CHROME_BROWSER_MOUSER_BOSSKEY_PROFILE_H_
#include "base/basictypes.h"
#include "base/memory/singleton.h"
#include "ui/base/accelerators/accelerator.h"
class BosskeyProfile {
 public:
  static BosskeyProfile* GetInstance() {
    return Singleton<BosskeyProfile>::get();
  }
  BosskeyProfile() {}
  ~BosskeyProfile() {}

  bool IsEnableHotkey();
  ui::Accelerator GetHotkey();

 private:
  DISALLOW_COPY_AND_ASSIGN(BosskeyProfile);
};
#endif  // CHROME_BROWSER_MOUSER_BOSSKEY_PROFILE_H_