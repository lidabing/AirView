// Copyright (c) 2012 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <windows.h>

#include "base/hook_manager.h"
#include "base/logging.h"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,".dir/../../third_party/detours/detours.lib")
#include "third_party/detours/detours.h"
namespace base{
	void HookManager::Register(HookItem* item){
		item_list_.push_back(item);
	}
	void HookManager::Install(){
		if(item_list_.empty())
			return;
		DetourTransactionBegin();  
		DetourUpdateThread( GetCurrentThread() );  
		{
			std::vector<HookItem*>::iterator iter = item_list_.begin();
			for(;iter != item_list_.end(); iter++ ){
				(*iter)->Install();
			}
		}
		long res;
		res = DetourTransactionCommit();  
		if(res != NO_ERROR){
			DLOG(ERROR)<< "hook  install error";
		}
	}
	void HookManager::UnInstall(){
		if(item_list_.empty())
			return;
		DetourTransactionBegin();  
		DetourUpdateThread(GetCurrentThread());  
		{
			std::vector<HookItem*>::iterator iter = item_list_.begin();
			for(;iter != item_list_.end(); iter++ ){
				(*iter)->UnInstall();
				delete (*iter);
			}
			item_list_.clear();
		}
		DetourTransactionCommit();  
	}
}