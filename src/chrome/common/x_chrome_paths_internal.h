// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_X_CHROME_PATHS_INTERNAL_H_
#define CHROME_COMMON_X_CHROME_PATHS_INTERNAL_H_

#include <string>

#include "build/build_config.h"

namespace base {
class FilePath;
}

namespace chrome {

bool xGetDefaultUserDataDirectory(base::FilePath* result);

void xGetUserCacheDirectory(const base::FilePath& profile_dir,
                            base::FilePath* result);
}
#endif  // CHROME_COMMON_X_CHROME_PATHS_INTERNAL_H_