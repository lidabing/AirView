// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_RESTORE_MENU_MODEL_H_
#define CHROME_BROWSER_UI_RESTORE_MENU_MODEL_H_
#pragma once

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/strings/string16.h"
#include "chrome/browser/favicon/favicon_service.h"
#include "ui/base/models/menu_model.h"
#include "ui/base/window_open_disposition.h"
#include "chrome/browser/sessions/tab_restore_service.h"

class Browser;
class GURL;
namespace ui {
///////////////////////////////////////////////////////////////////////////////
//
// RestoreMenuModel
//
// Interface for the showing of the dropdown menu for the Restore buttons.
// Actual implementations are platform-specific.
///////////////////////////////////////////////////////////////////////////////
class RestoreMenuModel : public ui::MenuModel {
 public:
  RestoreMenuModel(Browser* browser);
  virtual ~RestoreMenuModel();

  // MenuModel implementation.
  virtual bool HasIcons() const OVERRIDE;
  // Returns how many items the menu should show, including history items,
  // chapter-stops, separators and the Show Full History link. This function
  // uses GetHistoryItemCount() and GetChapterStopCount() internally to figure
  // out the total number of items to show.
  virtual int GetItemCount() const OVERRIDE;
  virtual ItemType GetTypeAt(int index) const OVERRIDE;
  virtual int GetCommandIdAt(int index) const OVERRIDE;
  virtual ui::MenuSeparatorType GetSeparatorTypeAt(int index) const OVERRIDE;
  virtual base::string16 GetLabelAt(int index) const OVERRIDE;
  virtual bool IsItemDynamicAt(int index) const OVERRIDE;
  virtual bool GetAcceleratorAt(int index,
                                ui::Accelerator* accelerator) const OVERRIDE;
  virtual bool IsItemCheckedAt(int index) const OVERRIDE;
  virtual int GetGroupIdAt(int index) const OVERRIDE;
  virtual bool GetIconAt(int index, gfx::Image* icon);
  virtual ui::ButtonMenuItemModel* GetButtonMenuItemAt(
      int index) const OVERRIDE;
  virtual bool IsEnabledAt(int index) const OVERRIDE;
  virtual MenuModel* GetSubmenuModelAt(int index) const OVERRIDE;
  virtual void HighlightChangedTo(int index) OVERRIDE;
  virtual void ActivatedAt(int index) OVERRIDE;
  virtual void ActivatedAt(int index, int event_flags) OVERRIDE;
  virtual void MenuWillShow();
  virtual void MenuClosed();

  // Is the item at |index| a separator?
  bool IsSeparator(int index) const;

  // Set the delegate for triggering OnIconChanged.
  virtual void SetMenuModelDelegate(ui::MenuModelDelegate* menu_model_delegate);
  virtual ui::MenuModelDelegate* GetMenuModelDelegate() const OVERRIDE;

 protected:
  ui::MenuModelDelegate* menu_model_delegate() { return menu_model_delegate_; }

 private:
  // Requests a favicon from the FaviconService. Called by GetIconAt if the
  // NavigationEntry has an invalid favicon.
  void FetchFavicon(const GURL* url, int index);

  // Callback from the favicon service.
  void OnFavIconDataAvailable(int navigation_entry_unique_id,
                          const favicon_base::FaviconImageResult& image_result);

  // Takes a menu item index as passed in through one of the menu delegate
  // functions and converts it into an index into the NavigationEntryList
  // vector. |index| can point to a separator, or the
  // "Show Full History" link in which case this function returns -1.
  int MenuIndexToNavEntryIndex(int index) const;

  // Does the item have a command associated with it?
  bool ItemHasCommand(int index) const;

  // Returns true if there is an icon for this menu item.
  bool ItemHasIcon(int index) const;

  base::string16 GetShowFullHistoryLabel() const;
  base::string16 GetClearRestoreListLabel() const;

  int GetRestoreItemCount() const;

  bool IsValidItem(const TabRestoreService::Tab* tab) const;
  TabRestoreService::Entry* GetTRSEntry(int index) const;

  // Build a string version of a user action on this menu, used as an
  // identifier for logging user behavior.
  // E.g. BuildActionName("Click", 2) returns "BackMenu_Click2".
  // An index of -1 means no index.
  std::string BuildActionName(const std::string& name, int index) const;

  Browser* browser_;

  // Keeps track of which favicons have already been requested from the history
  // to prevent duplicate requests, identified by NavigationEntry->unique_id().
  // std::set<int> requested_favicons_;
  std::map<int, gfx::Image> requested_favicons_;

  // Used for loading favicons.
  base::CancelableTaskTracker cancelable_task_tracker_;

  // Used for receiving notifications when an icon is changed.
  ui::MenuModelDelegate* menu_model_delegate_;

  DISALLOW_COPY_AND_ASSIGN(RestoreMenuModel);
};
}
#endif  // CHROME_BROWSER_UI_RESTORE_MENU_MODEL_H_
