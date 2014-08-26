// Copyright (c) 2013 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Constants for the names of various preferences, for easier changing.

#ifndef CHROME_COMMON_PREFS_UTIL_H_
#define CHROME_COMMON_PREFS_UTIL_H_

#include "ui/base/window_open_disposition.h"
#include "url/gurl.h"
#include <string>
class PrefService;
namespace prefs_util{
	GURL GetCurrentActiveTabURL();
	PrefService* GetLastUsedPrefService();
	WindowOpenDisposition GetDispositionForAddressBar(const GURL* current_url);
	WindowOpenDisposition GetDispositionForBookMarks(const GURL* new_url,const GURL* current_url,int event_flags);
	WindowOpenDisposition GetDispositionForHomeButton(const GURL* current_url);
	bool IsLeftDoubleClickCloseTab();
	bool IsRightClickedCloseTab();
}
#endif //CHROME_COMMON_PREFS_UTIL_H_