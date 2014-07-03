// Copyright 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/prefs/x_browser_prefs.h"

#include <string>
#include "base/prefs/pref_registry_simple.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "chrome/common/x_pref_names.h"
#include "chrome/browser/mouse_gesture/mouse_gesture_common.h"

namespace chrome {
void RegisterProfilePrefsX(user_prefs::PrefRegistrySyncable* registry){
	registry->RegisterBooleanPref(prefs::kXEnableBosskey,
		false,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXShowRestoreButton,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXShowBookmarksButton,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXOpenBookmarksInNewTab,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXOpenAddressInNewTab,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseTabWhenRightClick,
		false,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseTabWhenRLDoubleClick,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXNewTabForeground,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);

	//设置退出浏览器清理数据的能力
	registry->RegisterBooleanPref(prefs::kXCloseBrowserClearDataEnable,
		false,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseBrowserClearBrowserHistory,
		true,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseBrowserClearDownloadHistory,
		true,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseBrowserClearCache,
		false,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseBrowserClearCookie,
		false,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseBrowserClearPassword,
		true,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseBrowserClearAutoFill,
		false,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXCloseBrowserClearIEContents,
		true,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	//鼠标控制配置
	registry->RegisterBooleanPref(prefs::kXMouseGestureEnabled,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXSuperDragDropEnabled,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
	registry->RegisterBooleanPref(prefs::kXSuperDragDropOpenBackend,
		true,
		user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);

	//鼠标动作
	registry->RegisterIntegerPref(prefs::kXMouseActionUp,
		MGACTION_PAGEUP,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionDown,
		MGACTION_PAGEDOWN,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionUpDown,
		MGACTION_REFRESH,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionDownUp,
		MGACTION_NULL,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionRight,
		MGACTION_GOFORWARD,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionLeft,
		MGACTION_GOBACK,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionRightLeft,
		MGACTION_RESTORETAB,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionLeftRight,
		MGACTION_RESTORETAB,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionDownRight,
		MGACTION_CLOSECURRENTTAB,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionDownLeft,
		MGACTION_NULL,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionUpLeft,
		MGACTION_SELECTPREVIOUSTAB,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionUpRight,
		MGACTION_SELECTNEXTTAB,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionRightUp,
		MGACTION_NULL,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionRightDown,
		MGACTION_REFRESH,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionLeftUp,
		MGACTION_NULL,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);

	registry->RegisterIntegerPref(prefs::kXMouseActionLeftDown,
		MGACTION_GOPAGETOP,
		user_prefs::PrefRegistrySyncable::UNSYNCABLE_PREF);
 
	//registry->RegisterIntegerPref(prefs::kXDefaultDownloader,
	//	kDownloaderChrome, //使用默认下载器
	//	user_prefs::PrefRegistrySyncable::SYNCABLE_PREF);
}
}