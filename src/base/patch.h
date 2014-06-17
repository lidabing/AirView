// Copyright (c) 2013 The AirView  Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PATCH_H_
#define BASE_PATCH_H_
//给class打补丁的基础代码

#define X_PATCH_THIS(C)                \
 public:                                \
  C##Patch* patch() { return &patch_; } \
                                        \
 private:                               \
  friend class C##Patch;                \
  C##Patch patch_;

//#define X_CLASS_PATCH_INIT(C) patch_(this),

#define X_START_CLASS_PATCH(C)        \
  class C;                            \
  class C##Patch {                    \
    C##Patch(X* that) : that_(that) { 


#define X_END_PATCH(C) \
 private:              \
  C* that_;            \
  }                    \
  ;

#endif
