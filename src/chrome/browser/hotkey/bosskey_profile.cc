// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/hotkey/bosskey_profile.h"
#include "ui/base/accelerators/accelerator_serialization.h"
#include "base/prefs/pref_service.h"
#include "chrome/common/x_pref_names.h"
#include "chrome/browser/profiles/profile_manager.h"

namespace {
	PrefService* GetLastUsedPrefService() {
		DCHECK_UI_THREAD();
		Profile* profile = ProfileManager::GetLastUsedProfile();
		DCHECK(profile);
		PrefService* prefs = profile->GetPrefs();
		DCHECK(prefs);
		return prefs;
	}

	bool BosskeyProfile::IsEnableHotkey() {
		PrefService* prefs = GetLastUsedPrefService();
		return prefs->GetBoolean(prefs::kXEnableBosskey);
	}

	ui::Accelerator BosskeyProfile::GetHotkey() {
		PrefService* prefs = GetLastUsedPrefService();
		//Ctrl + Q
		std::string  value = prefs->GetString(prefs::kXBosskeyValue,"81|4");	;
		ui::Accelerator accelertor = ui::StringToAccelerator(value);
		return accelertor;
	}
}