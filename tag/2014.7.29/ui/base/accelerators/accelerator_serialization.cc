// Copyright (c) 2013 The AirView Authors Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/base/accelerators/accelerator_serialization.h"
#include "base/strings/stringprintf.h"
#include "base/strings/string_split.h"
#include "base/strings/string_number_conversions.h"
#include "base/logging.h"
#include <vector>
#include "ui/events/keycodes/keyboard_code_conversion_win.h"

namespace ui {
std::string AcceleratorToString(const Accelerator& accelerator) {
  return base::StringPrintf(
      "%d|%d", accelerator.key_code(), accelerator.modifiers());
}
Accelerator StringToAccelerator(const std::string& value) {
  std::vector<std::string> split_value;
  base::SplitString(value, '|', &split_value);
  DCHECK(split_value.size() == 2);
  if (split_value.size() != 2)
    return Accelerator();
  int key_code, modifiers;
  base::StringToInt(split_value[0], &key_code);
  base::StringToInt(split_value[1], &modifiers);
  return Accelerator((KeyboardCode)key_code, modifiers);
}
bool DescriptStringToAccelerator(const std::string& value,
                                 ui::Accelerator& accelerator) {
  //首先需要解析字符串
  // Ctrl+Alt+Shift+X
  std::string boss_key_str = value;
  if (boss_key_str.empty())
    return false;
  bool ctrl = false;
  bool atl = false;
  bool shift = false;
  int modifiers = 0;
  if (std::string::npos != boss_key_str.find("Ctrl")) {
    modifiers |= ui::EF_CONTROL_DOWN;
    ctrl = true;
  }
  if (std::string::npos != boss_key_str.find("Alt")) {
    modifiers |= ui::EF_ALT_DOWN;
    atl = true;
  }
  if (std::string::npos != boss_key_str.find("Shift")) {
    modifiers |= ui::EF_SHIFT_DOWN;
    shift = true;
  }

  //查找最后一个字母
  char keyvalue = boss_key_str[boss_key_str.size() - 1];
  accelerator =
      ui::Accelerator(ui::KeyboardCodeForWindowsKeyCode(keyvalue), modifiers);
  return true;
}

std::wstring AcceleratorToDescriptString(const ui::Accelerator& accelerator) {
  std::wstring accelertor_str;
  if (accelerator.IsAltDown()) {
    accelertor_str += L"Alt+";
  }
  if (accelerator.IsCtrlDown()) {
    accelertor_str += L"Ctrl+";
  }
  if (accelerator.IsShiftDown()) {
    accelertor_str += L"Shift+";
  }

  accelertor_str.append(1, accelerator.key_code());
  return accelertor_str;
}
}