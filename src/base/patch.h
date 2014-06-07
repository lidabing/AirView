// Copyright (c) 2013 The AirView  Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PATCH_H_
#define BASE_PATCH_H_
//给class打补丁的基础代码
#define PATCH_CLASS(X)\
	public:
		X##Patch* patch(){return &patch_;}
	private:
		friend class X##Patch;
		X##Patch patch_;

#define PATCH_CLASS_INIT(X)\
	patch_(this),

#endif

