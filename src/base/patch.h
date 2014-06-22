// Copyright (c) 2013 The AirView  Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PATCH_H_
#define BASE_PATCH_H_
#include "base/basictypes.h"
#include "base/compiler_specific.h"

// PATCH CLASS
#define X_CLASS_PATCH_NAME(C) C##Patch

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

//this have base interface's class patch
#define X_START_CLASS_PATCH_(C, baseiface) \
  class C;                                 \
  class C##Patch : public baseiface {      \
    C##Patch(C* that) : that_(that) {}

#define X_END_CLASS_PATCH(C)          \
 private:                             \
  friend class C;                     \
  C* that_;                           \
  DISALLOW_COPY_AND_ASSIGN(C##Patch); \
  }                                   \
  ;

// PATCH INTERFACE
#define X_INTERFACE_PATCH_NAME(iface) iface##Patch
#define X_INTERFACE_PATCH_NAME_(nspace,iface) nspace::iface##Patch

#define X_PATCH_INTERFACE(iface) \
 public:                         \
  virtual iface##Patch* patch_##iface() { return NULL; }


#define X_START_INTERFACE_PATCH(export_type, iface) \
  class export_type iface##Patch {                  \
   public:
#define X_END_INTERFACE_PATCH(iface) \
  }                                  \
  ;

#endif
