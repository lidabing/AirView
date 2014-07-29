// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_X_BROWSER_PREFS_H_
#define CHROME_BROWSER_PREFS_X_BROWSER_PREFS_H_

class PrefRegistrySimple;
class PrefService;
class Profile;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace chrome {
void RegisterProfilePrefsX(user_prefs::PrefRegistrySyncable* registry);
}
#endif  // CHROME_BROWSER_PREFS_X_BROWSER_PREFS_H_