// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include "base/prefs/pref_service.h"
#include "chrome/browser/mouse_gesture/mouse_gesture_profile.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/browser/mouse_gesture/mouse_gesture_common.h"
#include "chrome/common/x_pref_names.h"
#include "chrome/browser/ui/browser_commands_patch.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/render_widget_host_view.h"

#define DCHECK_UI_THREAD() \
	DCHECK(base::MessageLoop::current()->type() == base::MessageLoop::TYPE_UI)
namespace {
PrefService* GetLastUsedPrefService() {
  DCHECK_UI_THREAD();
  Profile* profile = ProfileManager::GetLastUsedProfile();
  DCHECK(profile);
  PrefService* prefs = profile->GetPrefs();
  DCHECK(prefs);
  return prefs;
}
//处理鼠标手势相关消息
MGAction GetMGAction(MGPattern pattern) {
  PrefService* prefs = GetLastUsedPrefService();
  if (MGPATTERN_UP == pattern)
    return prefs->GetInteger(prefs::kXMouseActionUp);
  else if (MGPATTERN_DOWN == pattern)
    return prefs->GetInteger(prefs::kXMouseActionDown);
  else if (MGPATTERN_UPDOWN == pattern)
    return prefs->GetInteger(prefs::kXMouseActionUpDown);
  else if (MGPATTERN_DOWNUP == pattern)
    return prefs->GetInteger(prefs::kXMouseActionDownUp);
  else if (MGPATTERN_RIGHT == pattern)
    return prefs->GetInteger(prefs::kXMouseActionRight);
  else if (MGPATTERN_LEFT == pattern)
    return prefs->GetInteger(prefs::kXMouseActionLeft);
  else if (MGPATTERN_RIGHTLEFT == pattern)
    return prefs->GetInteger(prefs::kXMouseActionRightLeft);
  else if (MGPATTERN_LEFTRIGHT == pattern)
    return prefs->GetInteger(prefs::kXMouseActionLeftRight);
  else if (MGPATTERN_DOWNRIGHT == pattern)
    return prefs->GetInteger(prefs::kXMouseActionDownRight);
  else if (MGPATTERN_DOWNLEFT == pattern)
    return prefs->GetInteger(prefs::kXMouseActionDownLeft);
  else if (MGPATTERN_UPLEFT == pattern)
    return prefs->GetInteger(prefs::kXMouseActionUpLeft);
  else if (MGPATTERN_UPRIGHT == pattern)
    return prefs->GetInteger(prefs::kXMouseActionUpRight);
  else if (MGPATTERN_RIGHTUP == pattern)
    return prefs->GetInteger(prefs::kXMouseActionRightUp);
  else if (MGPATTERN_RIGHTDOWN == pattern)
    return prefs->GetInteger(prefs::kXMouseActionRightDown);
  else if (MGPATTERN_LEFTUP == pattern)
    return prefs->GetInteger(prefs::kXMouseActionLeftUp);
  else if (MGPATTERN_LEFTDOWN == pattern)
    return prefs->GetInteger(prefs::kXMouseActionLeftDown);

  return MGACTION_NULL;
}

void MouseGestureMessageHandle(MGPattern mg_pattern) {
  MGAction action = GetMGAction(mg_pattern);

  if (MGACTION_NULL == action)
    return;
  if (MGACTION_PAGEUP == action)
    return chrome::PageUp();
  if (MGACTION_PAGEDOWN == action)
    return chrome::PageDown();
  if (MGACTION_GOBACK == action)
    return chrome::GoBack();
  if (MGACTION_GOFORWARD == action)
    return chrome::GoForward();
  if (MGACTION_CLOSECURRENTTAB == action)
    return chrome::CloseCurrentTab();
  if (MGACTION_SELECTPREVIOUSTAB == action)
    return chrome::SelectPreviousTab();
  if (MGACTION_SELECTNEXTTAB == action)
    return chrome::SelectNextTab();
  if (MGACTION_REFRESH == action)
    return chrome::RefreshCurrentTab();
  if (MGACTION_RESTORETAB == action)
    return chrome::RestoreTab();
  if (MGACTION_NEWTAB == action)
    return chrome::NewTab();
  if (MGACTION_GOPAGETOP == action)
    return chrome::GoPageTop();
  if (MGACTION_GOPAGEBOTTOM == action)
    return chrome::GoPageBottom();
  if (MGACTION_STOPLOADING == action)
    return chrome::StopLoading();
  if (MGACTION_MINIMIZEWINDOW == action)
    return chrome::MinimizeWindow();
  if (MGACTION_CLOSEOTHERTAB == action)
    return chrome::CloseOtherTabs();
  if (MGACTION_CLOSERIGHTTAB == action)
    return chrome::CloseRightTabs();
}
}

MouseGestureProfile::MouseGestureProfile() {
}

bool MouseGestureProfile::IsEnableMouseGesure() {
	PrefService* prefs = GetLastUsedPrefService();
	return prefs->GetBoolean(prefs::kXMouseGestureEnabled);
}
bool MouseGestureProfile::IsEnableWebDrag() {
	PrefService* prefs = GetLastUsedPrefService();
	return prefs->GetBoolean(prefs::kXSuperDragDropEnabled);
}
bool MouseGestureProfile::IsWebDragBackground() {
	PrefService* prefs = GetLastUsedPrefService();
	return prefs->GetBoolean(prefs::kXSuperDragDropOpenBackend);
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
  MGPattern val = MGPATTERN_UNKNOWN;
  size_t action_num = action.size();
  if (1 == action_num) {
    XDirection direction = action.front();
    if (MGD_UP == direction) {
      val = MGPATTERN_UP;
    } else if (MGD_DOWN == direction) {
      val = MGPATTERN_DOWN;
    } else if (MGD_LEFT == direction) {
      val = MGPATTERN_LEFT;
    } else if (MGD_RIGHT == direction) {
      val = MGPATTERN_RIGHT;
    }
  } else if (2 == action_num) {
    XDirection direction_second = action.back();
    XDirection direction_first = action.front();
    if ((MGD_DOWN == direction_first) && (MGD_RIGHT == direction_second)) {
      val = MGPATTERN_DOWNRIGHT;
    } else if ((MGD_UP == direction_first) && (MGD_DOWN == direction_second)) {
      val = MGPATTERN_UPDOWN;
    } else if ((MGD_UP == direction_first) && (MGD_LEFT == direction_second)) {
      val = MGPATTERN_UPLEFT;
    } else if ((MGD_UP == direction_first) && (MGD_RIGHT == direction_second)) {
      val = MGPATTERN_UPRIGHT;
    } else if ((MGD_DOWN == direction_first) &&
               (MGD_LEFT == direction_second)) {
      val = MGPATTERN_DOWNLEFT;
    } else if ((MGD_DOWN == direction_first) && (MGD_UP == direction_second)) {
      val = MGPATTERN_DOWNUP;
    } else if ((MGD_LEFT == direction_first) &&
               (MGD_RIGHT == direction_second)) {
      val = MGPATTERN_LEFTRIGHT;
    } else if ((MGD_RIGHT == direction_first) &&
               (MGD_LEFT == direction_second)) {
      val = MGPATTERN_RIGHTLEFT;
    } else if ((MGD_RIGHT == direction_first) &&
               (MGD_DOWN == direction_second)) {
      val = MGPATTERN_RIGHTDOWN;
    } else if ((MGD_RIGHT == direction_first) && (MGD_UP == direction_second)) {
      val = MGPATTERN_RIGHTUP;
    } else if ((MGD_LEFT == direction_first) && (MGD_UP == direction_second)) {
      val = MGPATTERN_LEFTUP;
    } else if ((MGD_LEFT == direction_first) &&
               (MGD_DOWN == direction_second)) {
      val = MGPATTERN_LEFTDOWN;
    }
  }
  MouseGestureMessageHandle(val);
}