// Copyright (c) 2012 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AIRVIEW_BASE_MANAGER_H_
#define AIRVIEW_BASE_MANAGER_H_
#include <vector>
#include "base/base_export.h"
#include "base/compiler_specific.h"
namespace base{
	class BASE_EXPORT HookItem{
	public:
		virtual bool Install() = 0;
		virtual void UnInstall() = 0;
		virtual ~HookItem(){}
	};

	class BASE_EXPORT HookManager{
	public:
		void Register(HookItem* item);
		void Install();
		void UnInstall();
	private:
		std::vector<HookItem*> item_list_;
	};
}
#endif //AIRVIEW_BASE_MANAGER_H_