// Copyright (c) 2014 The f1Brower Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/frame/browser_view_patch.h"
#include "base/command_line.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/browser/ui/views/frame/browser_frame.h"

BrowserViewPatch::BrowserViewPatch(BrowserView* that) : that_(that) {
}
BrowserViewPatch::~BrowserViewPatch() {
}