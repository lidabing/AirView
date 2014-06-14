// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/mouse_gesture/mouse_gesture_profile.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/render_widget_host_view.h"

MouseGestureProfile::MouseGestureProfile() {
}

bool MouseGestureProfile::IsEnableMouseGesure() {
#if 0
	PrefService* prefs = prefs_util::GetLastUsedPrefService();
	return prefs->GetBoolean(prefs::kXMouseGestureEnabled);
#endif
  return true;
}
gfx::NativeView MouseGestureProfile::CurrentTabWidgetWindow() {
  Browser* browser =
      BrowserList::GetInstance(chrome::GetActiveDesktop())->GetLastActive();
  if (browser) {
    content::WebContents* web_contents =
        browser->tab_strip_model()->GetActiveWebContents();
    if (web_contents) {
      content::RenderViewHost* rvh = web_contents->GetRenderViewHost();
      if (rvh) {
        content::RenderWidgetHostView* rwvh = rvh->GetView();
        if (rwvh)
          return rwvh->GetNativeView();
      }
    }
  }
  return NULL;
}
void MouseGestureProfile::OnMouseGestureAction(XMouseGestures& action) {
}