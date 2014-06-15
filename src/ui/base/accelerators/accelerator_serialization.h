// Copyright (c) 2013 The AirView Authors Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AIRVIEW_BASE_ACCELERATOR_ACCELERATOR_SERIALIZATION_H_
#define AIRVIEW_BASE_ACCELERATOR_ACCELERATOR_SERIALIZATION_H_

#include "base/strings/string16.h"
#include "ui/base/ui_base_export.h"
#include "ui/base/accelerators/accelerator.h"

namespace ui {
UI_BASE_EXPORT std::string AcceleratorToString(const Accelerator& accelerator);
UI_BASE_EXPORT Accelerator StringToAccelerator(const std::string& value);
UI_BASE_EXPORT bool DescriptStringToAccelerator(const std::string& value,
                                           ui::Accelerator& accelerator);
UI_BASE_EXPORT std::wstring AcceleratorToDescriptString(
    const ui::Accelerator& accelerator);
}
#endif  // AIRVIEW_BASE_ACCELERATOR_ACCELERATOR_SERIALIZATION_H_