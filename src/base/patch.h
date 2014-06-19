// Copyright (c) 2013 The AirView  Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PATCH_H_
#define BASE_PATCH_H_
#include "base/basictypes.h"
#include "base/compiler_specific.h"

//给class打补丁的基础代码

#define X_PATCH_THIS(C)                     \
 public:                                    \
  C##Patch* patch_##C() { return &patch_; } \
                                            \
 private:                                   \
  friend class C##Patch;                    \
  C##Patch patch_;

#define X_PATCH_CLASS_INIT(C) patch_(this)

#define X_START_CLASS_PATCH(C) \
  class C;                     \
  class C##Patch {             \
    C##Patch(C* that) : that_(that) {}

#define X_END_CLASS_PATCH(C)          \
 private:                             \
  friend class C;                     \
  C* that_;                           \
  DISALLOW_COPY_AND_ASSIGN(C##Patch); \
  }                                   \
  ;

#endif
