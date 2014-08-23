// Copyright 2013 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/profiles/globle_pref_service.h"
#include "base/prefs/json_pref_store.h"
#include "base/path_service.h"
#include "base/file_util.h"
#include "base/values.h"
#include "base/threading/thread_restrictions.h"
#include "content/public/browser/browser_thread.h"
#include "base/prefs/pref_filter.h"

GloblePrefService::GloblePrefService(){
	base::FilePath path;
	PathService::Get(base::DIR_EXE, &path);
	path = path.Append(L"globle_pref");
	scoped_refptr<base::SequencedTaskRunner> sequenced_task_runner =
		JsonPrefStore::GetTaskRunnerForFile(path,
		content::BrowserThread::GetBlockingPool());
	{
		//base::ThreadRestrictions::ScopedAllowIO allowed_io;
		//if(!base::PathExists(path))
		//	file_util::CloseFile(path);
	}
	prefs_ = new JsonPrefStore(path,sequenced_task_runner,scoped_ptr<PrefFilter>());
	prefs_->ReadPrefs();
}
GloblePrefService::~GloblePrefService(){
	prefs_->CommitPendingWrite();
	//prefs_ = NULL;
}

std::string GloblePrefService::GetString(const std::string& key, const std::string& default_value) const {
	const base::Value* value;
	std::string result;
	if (!prefs_->GetValue(key, &value) || !value->GetAsString(&result))
		return default_value;

	return result;
}

void GloblePrefService::SetString(const std::string& key,
	const std::string& value) {
		prefs_->SetValue(key, new base::StringValue(value));
}

bool GloblePrefService::GetBoolean(const std::string& key, bool default_value) const {
	const base::Value* value;
	bool result = false;
	if (!prefs_->GetValue(key, &value) || !value->GetAsBoolean(&result))
		return default_value;

	return result;
}

void GloblePrefService::SetBoolean(const std::string& key, bool value) {
	prefs_->SetValue(key, new base::FundamentalValue(value));
}

int GloblePrefService::GetInt(const std::string& key, int default_value) const {
	const base::Value* value;
	int result = default_value;
	if (!prefs_->GetValue(key, &value) || !value->GetAsInteger(&result))
		return default_value;

	return result;
}

void GloblePrefService::SetInt(const std::string& key, int value) {
	prefs_->SetValue(key, new base::FundamentalValue(value));
}