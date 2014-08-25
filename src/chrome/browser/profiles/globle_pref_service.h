// Copyright 2013 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_GLOBLE_PREF_SERVICE_H_
#define CHROME_BROWSER_PROFILES_GLOBLE_PREF_SERVICE_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include <string>
#include "base/memory/singleton.h"
//-----
//全局的设置，不通过PrefService来保存读取设置,所有Profile共享，
//所以暂时使用一个单件来实现,不是线程安全，需要所有访问都在UI线程里面
//-----
class JsonPrefStore;
class GloblePrefService{
public:
	static GloblePrefService* GetInstance() {
		return Singleton<GloblePrefService>::get();
	}

	std::string GetString(const std::string& key,const std::string& default_value) const;
	void SetString(const std::string& key, const std::string& value);
	bool GetBoolean(const std::string& key, bool default_value) const;
	void SetBoolean(const std::string& key, bool value);
	int GetInt(const std::string& key, int default_value) const;
	void SetInt(const std::string& key, int value);

protected:
	GloblePrefService();
	~GloblePrefService();
private:
	scoped_refptr<JsonPrefStore> prefs_;

	friend class Singleton<GloblePrefService>;
	friend struct DefaultSingletonTraits<GloblePrefService>;
	DISALLOW_COPY_AND_ASSIGN(GloblePrefService);
};

#endif //CHROME_BROWSER_PROFILES_GLOBLE_PREF_SERVICE_H_