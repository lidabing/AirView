// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/common/x_pref_names.h"

namespace prefs {
// boss key
const char kXEnableBosskey[] = "x.bosskey_enabled";  // bool
const char kXBosskeyValue[] = "x.bosskey_value";     // string
// toolbar config
const char kXShowRestoreButton[] = "x.show_restore_button";      // bool
const char kXShowBookmarksButton[] = "x.show_bookmarks_button";  // bool

// tab config
const char kXOpenBookmarksInNewTab[] = "x.open_bookmarks_in_newtab";     // bool
const char kXOpenAddressInNewTab[] = "x.open_address_in_newtab";         // bool
const char kXCloseTabWhenRightClick[] = "x.close_tab_when_right_click";  // bool
const char kXCloseTabWhenRLDoubleClick[] =
    "x.close_tab_when_ldouble_click";                     // bool
const char kXNewTabForeground[] = "x.newtab_foreground";  // bool

//退出浏览器清理选项
const char kXCloseBrowserClearDataEnable[] =
    "x.closebrowser_clear_data_enabled";
const char kXCloseBrowserClearBrowserHistory[] =
    "x.closebrowser_clear_browser_history";
const char kXCloseBrowserClearDownloadHistory[] =
    "x.closebrowser_clear_download_history";
const char kXCloseBrowserClearCache[] = "x.closebrowser_clear_cache";
const char kXCloseBrowserClearCookie[] = "x.closebrowser_clear_cookie";
const char kXCloseBrowserClearPassword[] = "x.closebrowser_clear_password";
const char kXCloseBrowserClearAutoFill[] = "x.closebrowser_clear_autofill";
const char kXCloseBrowserClearIEContents[] = "x.closebrowser_clear_ie_contents";

// mouse gesture config
const char kXMouseGestureEnabled[] = "x.mouse_gesture_enabled";     // bool
const char kXSuperDragDropEnabled[] = "x.super_drag_drop_enabled";  // int
const char kXSuperDragDropOpenBackend[] =
    "x.super_drag_drop_open_backend";  // int

// mouse gesture actions
const char kXMouseActionUp[] = "x.mouse_action_up";                // int
const char kXMouseActionDown[] = "x.mouse_action_down";            // int
const char kXMouseActionUpDown[] = "x.mouse_action_updown";        // int
const char kXMouseActionDownUp[] = "x.mouse_action_downup";        // int
const char kXMouseActionRight[] = "x.mouse_action_right";          // int
const char kXMouseActionLeft[] = "x.mouse_action_left";            // int
const char kXMouseActionRightLeft[] = "x.mouse_action_rightleft";  // int
const char kXMouseActionLeftRight[] = "x.mouse_action_leftright";  // int
const char kXMouseActionDownRight[] = "x.mouse_action_downright";  // int
const char kXMouseActionDownLeft[] = "x.mouse_action_downleft";    // int
const char kXMouseActionUpLeft[] = "x.mouse_action_upleft";        // int
const char kXMouseActionUpRight[] = "x.mouse_action_upright";      // int
const char kXMouseActionRightUp[] = "x.mouse_action_rightup";      // int
const char kXMouseActionRightDown[] = "x.mouse_action_rightdown";  // int
const char kXMouseActionLeftUp[] = "x.mouse_action_leftup";        // int
const char kXMouseActionLeftDown[] = "x.mouse_action_leftdown";    // int

//默认下载工具
const char kXDefaultDownloader[] = "x.default_downloader";  // int

// sync and signin
const char kXServicesUsername[] = "x.services_username";
const char kXUserImageURL[] = "x.userimage_url";
const char kXSyncSkin[] = "x.sync.skin";
const char kXSyncHistoryUrls[] = "x.sync.history_urls";
}