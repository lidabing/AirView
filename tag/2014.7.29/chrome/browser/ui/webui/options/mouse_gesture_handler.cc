// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/webui/options/mouse_gesture_handler.h"

#include "base/values.h"
#include "base/bind.h"
#include "base/strings/string_number_conversions.h"
#include "grit/chromium_strings.h"
#include "grit/generated_resources.h"
#include "grit/locale_settings.h"
#include "grit/theme_resources.h"
#include "ui/base/l10n/l10n_util.h"

#include "content/public/browser/web_ui.h"
#include "chrome/browser/profiles/profile.h"
#include "base/prefs/pref_service.h"
#include "chrome/common/pref_names.h"
#include "chrome/browser/mouse_gesture/mouse_gesture_common.h"
#include "chrome/common/x_pref_names.h"

//IDS_MORE_SETTING_DLG_U:{pos:'0 0'},
//IDS_MORE_SETTING_DLG_UD:{pos:'-320px 0'},
//IDS_MORE_SETTING_DLG_D:{pos:'-32px 0'},
//IDS_MORE_SETTING_DLG_DU:{pos:'-352px 0'},
//IDS_MORE_SETTING_DLG_L:{pos:'-64px 0'},
//IDS_MORE_SETTING_DLG_RU:{pos:'-384px 0'},
//IDS_MORE_SETTING_DLG_R:{pos:'-96px 0'},
//IDS_MORE_SETTING_DLG_RD:{pos:'-416px 0'},
//IDS_MORE_SETTING_DLG_UL:{pos:'-128px 0'},
//IDS_MORE_SETTING_DLG_LU:{pos:'-448px 0'},
//IDS_MORE_SETTING_DLG_UR:{pos:'-160px 0'},
//IDS_MORE_SETTING_DLG_LD:{pos:'-480px 0'},
//IDS_MORE_SETTING_DLG_DL:{pos:'-192px 0'},
//IDS_MORE_SETTING_DLG_DR:{pos:'-224px 0'},
//IDS_MORE_SETTING_DLG_RL:{pos:'-256px 0'},
//IDS_MORE_SETTING_DLG_LR:{pos:'-288px 0'},

//==============================
#define DEFINEMGNITEM(id, src_id, pref_name, pos) \
  { #id, id, pos, src_id, pref_name }
#define DEFINEMGAITEM(id, src_id) \
  { #id, id, src_id }
struct MgnItem {
  std::string string_id;  //鼠标手势名称
  int id;
  std::string bgimage_pos;  //鼠标图像位置
  int src_id;               //资源ID
  const char* pref_name;
};
struct MgaItem {
  std::string string_id;  //鼠标手势名称
  int id;
  int src_id;  //资源ID
};

static MgnItem kMgnItems[] = {DEFINEMGNITEM(MGPATTERN_UP,
                                            IDS_X_MG_ACTIONS_U,
                                            prefs::kXMouseActionUp,
                                            "0 0"),
                              DEFINEMGNITEM(MGPATTERN_DOWN,
                                            IDS_X_MG_ACTIONS_D,
                                            prefs::kXMouseActionDown,
                                            "-32px 0"),
                              DEFINEMGNITEM(MGPATTERN_LEFT,
                                            IDS_X_MG_ACTIONS_L,
                                            prefs::kXMouseActionLeft,
                                            "-64px 0"),
                              DEFINEMGNITEM(MGPATTERN_RIGHT,
                                            IDS_X_MG_ACTIONS_R,
                                            prefs::kXMouseActionRight,
                                            "-96px 0"),
                              DEFINEMGNITEM(MGPATTERN_UPLEFT,
                                            IDS_X_MG_ACTIONS_UL,
                                            prefs::kXMouseActionUpLeft,
                                            "-128px 0"),
                              DEFINEMGNITEM(MGPATTERN_UPRIGHT,
                                            IDS_X_MG_ACTIONS_UR,
                                            prefs::kXMouseActionUpRight,
                                            "-160px 0"),
                              DEFINEMGNITEM(MGPATTERN_DOWNLEFT,
                                            IDS_X_MG_ACTIONS_DL,
                                            prefs::kXMouseActionDownLeft,
                                            "-192px 0"),
                              DEFINEMGNITEM(MGPATTERN_DOWNRIGHT,
                                            IDS_X_MG_ACTIONS_DR,
                                            prefs::kXMouseActionDownRight,
                                            "-224px 0"),
                              DEFINEMGNITEM(MGPATTERN_RIGHTLEFT,
                                            IDS_X_MG_ACTIONS_RL,
                                            prefs::kXMouseActionRightLeft,
                                            "-256px 0"),
                              DEFINEMGNITEM(MGPATTERN_LEFTRIGHT,
                                            IDS_X_MG_ACTIONS_LR,
                                            prefs::kXMouseActionLeftRight,
                                            "-288px 0"),
                              DEFINEMGNITEM(MGPATTERN_UPDOWN,
                                            IDS_X_MG_ACTIONS_UD,
                                            prefs::kXMouseActionUpDown,
                                            "-320px 0"),
                              DEFINEMGNITEM(MGPATTERN_DOWNUP,
                                            IDS_X_MG_ACTIONS_DU,
                                            prefs::kXMouseActionDownUp,
                                            "-352px 0"),
                              DEFINEMGNITEM(MGPATTERN_RIGHTUP,
                                            IDS_X_MG_ACTIONS_RU,
                                            prefs::kXMouseActionRightUp,
                                            "-384px 0"),
                              DEFINEMGNITEM(MGPATTERN_RIGHTDOWN,
                                            IDS_X_MG_ACTIONS_RD,
                                            prefs::kXMouseActionRightDown,
                                            "-416px 0"),
                              DEFINEMGNITEM(MGPATTERN_LEFTUP,
                                            IDS_X_MG_ACTIONS_LU,
                                            prefs::kXMouseActionLeftUp,
                                            "-448px 0"),
                              DEFINEMGNITEM(MGPATTERN_LEFTDOWN,
                                            IDS_X_MG_ACTIONS_LD,
                                            prefs::kXMouseActionLeftDown,
                                            "-480px 0")};
static MgaItem kMgaItems[] = {
    DEFINEMGAITEM(MGACTION_PAGEDOWN, IDS_X_MGA_PAGE_DOWN),
    DEFINEMGAITEM(MGACTION_PAGEUP, IDS_X_MGA_PAGE_UP),
    DEFINEMGAITEM(MGACTION_GOPAGETOP, IDS_X_MGA_GO_PAGE_TOP),
    DEFINEMGAITEM(MGACTION_GOPAGEBOTTOM, IDS_X_MGA_GO_PAGE_BOTTOM),
    DEFINEMGAITEM(MGACTION_GOBACK, IDS_X_MGA_BACK),
    DEFINEMGAITEM(MGACTION_GOFORWARD, IDS_X_MGA_FORWARD),
    DEFINEMGAITEM(MGACTION_CLOSECURRENTTAB, IDS_X_MGA_CLOSE_TAB),
    DEFINEMGAITEM(MGACTION_SELECTPREVIOUSTAB, IDS_X_MGA_SWITCH_PREVIOUS_TAB),
    DEFINEMGAITEM(MGACTION_SELECTNEXTTAB, IDS_X_MGA_SWITCH_NEXT_TAB),
    DEFINEMGAITEM(MGACTION_REFRESH, IDS_X_MGA_REFRESH),
    DEFINEMGAITEM(MGACTION_RESTORETAB, IDS_X_MGA_REOPEN_CLOSE_WINDOW),
    DEFINEMGAITEM(MGACTION_NEWTAB, IDS_X_MGA_NEW_TAB),
    DEFINEMGAITEM(MGACTION_STOPLOADING, IDS_X_MGA_STOP_LOADING),
    DEFINEMGAITEM(MGACTION_MINIMIZEWINDOW, IDS_X_MGA_MINIMIZE_WINDOW),
    DEFINEMGAITEM(MGACTION_CLOSEOTHERTAB, IDS_X_MGA_CLOSE_OTHER_TABS),
    DEFINEMGAITEM(MGACTION_CLOSERIGHTTAB, IDS_X_MGA_CLOSE_RIGHT_TABS),
    DEFINEMGAITEM(MGACTION_NULL, IDS_X_MGA_NULL_ACTION)};
//=====================================

//==============map table====================

//==============================
void MouseGestureHandler::GetLocalizedValues(
    base::DictionaryValue* localized_strings) {
  RegisterTitle(localized_strings,
                "mouseGestureManagerPage",
                IDS_X_MOUSE_GESTURE_MANAGE_WINDOW_TITLE);
  localized_strings->SetString(
      "mouseGestureActions",
      l10n_util::GetStringUTF16(IDS_X_MOUSE_GESTURE_MANAGE_ACTIONS));
}

void MouseGestureHandler::InitializePage() {
  SetupMouseGestureActionsList();
}
void MouseGestureHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "setAirMouseGesture",
      base::Bind(&MouseGestureHandler::SetMouseGesture,
                 base::Unretained(this)));
}

void MouseGestureHandler::SetupMouseGestureActionsList() {
  Profile* profile = Profile::FromWebUI(web_ui());
  DCHECK(profile);

  base::ListValue mgn_list;  // mouse_gesture_name
  base::ListValue mga_list;  // mouse_gesture_actions
  // mouse_actions
  // make mgn_list
  int mgn_count = arraysize(kMgnItems);
  for (int index = 0; index < mgn_count; index++) {
  base::DictionaryValue* entry = new base::DictionaryValue();
    entry->SetInteger("id", kMgnItems[index].id);
    entry->SetString("prefname", kMgnItems[index].pref_name);
    entry->SetString("name",
                     l10n_util::GetStringUTF16(kMgnItems[index].src_id));
    entry->SetString("backgroundPosition", kMgnItems[index].bgimage_pos);
    // NEED ADD SELECT ID
    int mga = profile->GetPrefs()->GetInteger(kMgnItems[index].pref_name);
    entry->SetInteger("selectid", mga);
    mgn_list.Append(entry);
  }

  int mga_count = arraysize(kMgaItems);
  for (int index = 0; index < mga_count; index++) {
  base::DictionaryValue* entry = new base::DictionaryValue();
    entry->SetInteger("id", kMgaItems[index].id);
    entry->SetString("name",
                     l10n_util::GetStringUTF16(kMgaItems[index].src_id));
    mga_list.Append(entry);
  }
  web_ui()->CallJavascriptFunction(
      "options.MouseGestureManager.SetupMouseGestureActionsList",
      mgn_list,
      mga_list);
}

void MouseGestureHandler::SetMouseGesture(const base::ListValue* args) {
  std::string prefname;
  if (args->GetString(0, &prefname)) {
    int action;
    std::string string_value;
    if (args->GetString(1, &string_value)) {
      if (base::StringToInt(string_value, &action)) {
        Profile* profile = Profile::FromWebUI(web_ui());
        profile->GetPrefs()->SetInteger(prefname.c_str(), action);
        return;
      }
    }
  }
  DCHECK(0);
}