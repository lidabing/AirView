// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Constants for the names of various preferences, for easier changing.

#ifndef CHROME_COMMON_X_PREF_NAMES_H_
#define CHROME_COMMON_X_PREF_NAMES_H_

#include <stddef.h>
#include "build/build_config.h"

namespace prefs {
extern const char kXEnableBosskey[];
extern const char kXBosskeyValue[];

extern const char kXShowRestoreButton[];
extern const char kXShowBookmarksButton[];

extern const char kXOpenBookmarksInNewTab[];
extern const char kXOpenAddressInNewTab[];
extern const char kXCloseTabWhenRightClick[];
extern const char kXCloseTabWhenRLDoubleClick[];
extern const char kXNewTabForeground[];

extern const char kXCloseBrowserClearDataEnable[];
extern const char kXCloseBrowserClearBrowserHistory[];
extern const char kXCloseBrowserClearDownloadHistory[];
extern const char kXCloseBrowserClearCache[];
extern const char kXCloseBrowserClearCookie[];
extern const char kXCloseBrowserClearPassword[];
extern const char kXCloseBrowserClearAutoFill[];
extern const char kXCloseBrowserClearIEContents[];

extern const char kXMouseGestureEnabled[];
extern const char kXSuperDragDropEnabled[];
extern const char kXSuperDragDropOpenBackend[];

extern const char kXMouseActionUp[];
extern const char kXMouseActionDown[];
extern const char kXMouseActionUpDown[];
extern const char kXMouseActionDownUp[];
extern const char kXMouseActionRight[];
extern const char kXMouseActionLeft[];
extern const char kXMouseActionRightLeft[];
extern const char kXMouseActionLeftRight[];
extern const char kXMouseActionDownRight[];
extern const char kXMouseActionDownLeft[];
extern const char kXMouseActionUpLeft[];
extern const char kXMouseActionUpRight[];
extern const char kXMouseActionRightUp[];
extern const char kXMouseActionRightDown[];
extern const char kXMouseActionLeftUp[];
extern const char kXMouseActionLeftDown[];

extern const char kXDefaultDownloader[];

// sync and signin
extern const char kXServicesUsername[];
extern const char kXUserImageURL[];
extern const char kXSyncSkin[];         //是否同步皮肤
extern const char kXSyncHistoryUrls[];  //是否同步历史记录
}
#endif  // CHROME_COMMON_X_PREF_NAMES_H_