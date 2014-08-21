// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/common/x_chrome_paths_internal.h"

#include <windows.h>
#include <knownfolders.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shobjidl.h>

#include "base/files/file_path.h"
#include "base/path_service.h"
#include "base/win/scoped_co_mem.h"
#include "chrome/common/chrome_constants.h"
#include "chrome/common/chrome_switches.h"
namespace chrome {
bool xGetDefaultUserDataDirectory(base::FilePath* result) {
  base::FilePath path;
  PathService::Get(base::DIR_EXE, &path);
  *result = path.Append(chrome::kUserDataDirname);
  return true;
}
}