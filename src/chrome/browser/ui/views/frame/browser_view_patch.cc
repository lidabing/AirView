// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/frame/browser_view_patch.h"

#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/browser/ui/views/frame/browser_frame.h"
#include "ui/aura/window.h"
#include "ui/aura/window_tree_host.h"

void X_CLASS_PATCH_NAME(BrowserView)::OnBossKeyShow(bool show){
	HWND hwnd = that_->GetWidget()->GetNativeView()->GetHost()->GetAcceleratedWidget();
	if(show)
		ShowWindow(hwnd,SW_SHOW);//frame_->Show();
	else	
		ShowWindow(hwnd,SW_HIDE);//frame_->Hide();
}