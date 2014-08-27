// Copyright (c) 2008-2011 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/restore_menu_model.h"

#include "build/build_config.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/stringprintf.h"
#include "base/prefs/pref_service.h"
#include "base/strings/utf_string_conversions.h"
#include "content/public/browser/user_metrics.h"
#include "chrome/common/pref_names.h"
#include "chrome/common/url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/profile_sync_service.h"
#include "chrome/browser/sessions/tab_restore_service_factory.h"
#include "chrome/browser/favicon/favicon_service_factory.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_tab_restore_service_delegate.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/chrome_pages.h"
#include "grit/generated_resources.h"
#include "grit/theme_resources.h"
#include "grit/ui_resources.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/gfx/text_elider.h"
#include "ui/gfx/codec/png_codec.h"
#include "ui/gfx/favicon_size.h"
#include "ui/base/window_open_disposition.h"
#include "SkBitmap.h"
#include "components/sessions/serialized_navigation_entry.h"
#include "chrome/browser/ui/browser_commands_patch.h"

namespace ui {
static const int kMaxWidth = 700;

RestoreMenuModel::RestoreMenuModel(Browser* browser)
    : browser_(browser), menu_model_delegate_(NULL) {
}

RestoreMenuModel::~RestoreMenuModel() {
}

bool RestoreMenuModel::HasIcons() const {
  return true;
}

int RestoreMenuModel::GetItemCount() const {
  int items = GetRestoreItemCount();
  if (items > 0) {
    // If the menu is not empty, add there positions in the end
    // for a separator and a "Show Full History" and "Clear Restore List" item.
    items += 3;
  } else {
    // If the menu is empty, add £Ïne about "Show Full History"  item.
    items = 1;
  }
  return items;
}

ui::MenuModel::ItemType RestoreMenuModel::GetTypeAt(int index) const {
  return IsSeparator(index) ? TYPE_SEPARATOR : TYPE_COMMAND;
}

int RestoreMenuModel::GetCommandIdAt(int index) const {
  return index;
}

ui::MenuSeparatorType RestoreMenuModel::GetSeparatorTypeAt(int index) const {
  return ui::NORMAL_SEPARATOR;
}

base::string16 RestoreMenuModel::GetLabelAt(int index) const {
  if (GetItemCount() == 1) {
    DCHECK(index == 0);
    return GetShowFullHistoryLabel();
  }
  // Return an empty string for a separator.
  if (IsSeparator(index))
    return base::string16();

  // Return label "Show Full History" for the last item of the menu.
  if (index == GetItemCount() - 1)
    return GetClearRestoreListLabel();
  if (GetRestoreItemCount() != 0) {
    if (index == GetItemCount() - 2)
      return GetShowFullHistoryLabel();
  }

  base::string16 menu_text;
  //
  TabRestoreService::Entry* entry = GetTRSEntry(index);
  DCHECK(entry);
  if (entry->type == TabRestoreService::TAB) {
    TabRestoreService::Tab* tab = static_cast<TabRestoreService::Tab*>(entry);
    const sessions::SerializedNavigationEntry& current_navigation =
        tab->navigations.at(tab->current_navigation_index);
    menu_text = current_navigation.title();
    if (menu_text.empty())
      menu_text = base::UTF8ToUTF16(current_navigation.virtual_url().spec());
  } else if (entry->type == TabRestoreService::WINDOW) {
    const TabRestoreService::Window* window =
        static_cast<TabRestoreService::Window*>(entry);
    int tab_counts = window->tabs.size();
    menu_text = base::SStringPrintf(&menu_text, L"%d ", tab_counts);
    if (tab_counts == 1) {
      menu_text.append(base::UTF16ToWide(
          l10n_util::GetStringUTF16(IDS_X_TOOLBAR_RESTORE_WINDOW_SINGLE)));
    } else {
      menu_text.append(base::UTF16ToWide(
          l10n_util::GetStringUTF16(IDS_X_TOOLBAR_RESTORE_WINDOW_MULTIPE)));
    }
  } else {
    DCHECK(0) << "don't suport this type now";
  }
  DCHECK(!menu_text.empty());
  menu_text =
	  gfx::ElideText(menu_text, gfx::FontList(), kMaxWidth, gfx::ELIDE_TAIL);
  return menu_text;
}

bool RestoreMenuModel::IsItemDynamicAt(int index) const {
  // This object is only used for a single showing of a menu.
  return false;
}

bool RestoreMenuModel::GetAcceleratorAt(int index,
                                        ui::Accelerator* accelerator) const {
  return false;
}

bool RestoreMenuModel::IsItemCheckedAt(int index) const {
  return false;
}

int RestoreMenuModel::GetGroupIdAt(int index) const {
  return false;
}

bool RestoreMenuModel::GetIconAt(int index, gfx::Image* icon) {
  if (!ItemHasIcon(index))
    return false;
  if (index == GetItemCount() - 1)
    return false;
  // HACK (libing):fixme,i don't kown why when index is zero can't update icon
  if (GetRestoreItemCount() > 0) {
    if (index == 0) {
      *icon = ResourceBundle::GetSharedInstance().GetImageNamed(
          IDR_DEFAULT_FAVICON);
      return true;
    }

    if (index == GetItemCount() - 2) {
      *icon = ResourceBundle::GetSharedInstance().GetImageNamed(
          IDR_HISTORY_FAVICON);
      return true;
    }
  }
  //
  if (requested_favicons_.find(index) != requested_favicons_.end()) {
    *icon = requested_favicons_[index];
    return true;
  }
  TabRestoreService::Entry* entry = GetTRSEntry(index);
  DCHECK(entry);
  if (entry->type == TabRestoreService::TAB) {
    TabRestoreService::Tab* tab = static_cast<TabRestoreService::Tab*>(entry);
    if (!tab->navigations.empty()) {
      const sessions::SerializedNavigationEntry& current_navigation =
          tab->navigations.at(tab->current_navigation_index);
      FetchFavicon(&current_navigation.virtual_url(), index);
    }
  } else if (entry->type == TabRestoreService::WINDOW) {
    *icon = ResourceBundle::GetSharedInstance().GetImageNamed(
        IDR_X_RESTORE_WINDOW_ITEM);
  } else {
    DCHECK(0) << "don't suport this type now";
  }
  return true;
}

ui::ButtonMenuItemModel* RestoreMenuModel::GetButtonMenuItemAt(
    int index) const {
  return NULL;
}

bool RestoreMenuModel::IsEnabledAt(int index) const {
  return index < GetItemCount() && !IsSeparator(index);
}

ui::MenuModel* RestoreMenuModel::GetSubmenuModelAt(int index) const {
  return NULL;
}

void RestoreMenuModel::HighlightChangedTo(int index) {
}

void RestoreMenuModel::ActivatedAt(int index) {
  ActivatedAt(index, 0);
}

void RestoreMenuModel::ActivatedAt(int index, int event_flags) {
  DCHECK(!IsSeparator(index));
  if (GetItemCount() == 1) {
    DCHECK(index == 1);
    chrome::ShowHistory(browser_);
    return;
  }

  if (index == GetItemCount() - 1) {
    // clear all restore list
    chrome::ClearRestoreList(browser_);
    return;
  }
  if (GetRestoreItemCount() > 0) {
    if (index == GetItemCount() - 2) {
      // open history
      chrome::ShowHistory(browser_);
      return;
    }
  }

  //
  TabRestoreService::Entry* entry = GetTRSEntry(index);
  TabRestoreService* restore_service =
      TabRestoreServiceFactory::GetForProfile(browser_->profile());
  DCHECK(restore_service);
  restore_service->RestoreEntryById(browser_->tab_restore_service_delegate(),
                                    entry->id,
                                    browser_->host_desktop_type(),
                                    UNKNOWN);
}

void RestoreMenuModel::MenuWillShow() {
  content::RecordComputedAction(BuildActionName("Popup", -1));
}
void RestoreMenuModel::MenuClosed() {
  requested_favicons_.clear();
  cancelable_task_tracker_.TryCancelAll();
}

bool RestoreMenuModel::IsSeparator(int index) const {
  int restore_items = GetRestoreItemCount();
  if (restore_items == 0)
    return false;
  return restore_items == index;
}

void RestoreMenuModel::SetMenuModelDelegate(
    ui::MenuModelDelegate* menu_model_delegate) {
  menu_model_delegate_ = menu_model_delegate;
}

ui::MenuModelDelegate* RestoreMenuModel::GetMenuModelDelegate() const {
  return menu_model_delegate_;
}

void RestoreMenuModel::FetchFavicon(const GURL* url, int index) {
  // If the favicon has already been requested for this menu, don't do
  // anything.
  if (requested_favicons_.find(index) != requested_favicons_.end()) {
    return;
  }
  // IDR_DEFAULT_FAVICON
  ui::ResourceBundle& rb = ui::ResourceBundle::GetSharedInstance();
  requested_favicons_.insert(std::map<int, gfx::Image>::value_type(
      index, rb.GetImageNamed(IDR_DEFAULT_FAVICON)));
  FaviconService* favicon_service = FaviconServiceFactory::GetForProfile(
      browser_->profile(), Profile::EXPLICIT_ACCESS);
  if (!favicon_service)
    return;
    /*
    favicon_service->GetFaviconImageForPageURL(
      FaviconService::FaviconForPageURLParams(*url, favicon_base::FAVICON, gfx::kFaviconSize),
      base::Bind(&RestoreMenuModel::OnFavIconDataAvailable,
                 base::Unretained(this),
                 index),
      &cancelable_task_tracker_);
      */
}

void RestoreMenuModel::OnFavIconDataAvailable(
    int navigation_entry_unique_id,
    const favicon_base::FaviconImageResult& image_result) {
  if (!image_result.image.IsEmpty()) {
    requested_favicons_[navigation_entry_unique_id] = image_result.image;
    if (menu_model_delegate())
      menu_model_delegate()->OnIconChanged(navigation_entry_unique_id);
  }
}

bool RestoreMenuModel::ItemHasCommand(int index) const {
  return index < GetItemCount() && !IsSeparator(index);
}

bool RestoreMenuModel::ItemHasIcon(int index) const {
  return index < GetItemCount() && !IsSeparator(index);
}

base::string16 RestoreMenuModel::GetShowFullHistoryLabel() const {
  return l10n_util::GetStringUTF16(IDS_SHOWFULLHISTORY_LINK);
}
base::string16 RestoreMenuModel::GetClearRestoreListLabel() const {
  return l10n_util::GetStringUTF16(IDS_X_CLEAE_RESTORE_LIST);
}

int RestoreMenuModel::GetRestoreItemCount() const {
  TabRestoreService* restore_service =
      TabRestoreServiceFactory::GetForProfile(browser_->profile());
  const TabRestoreService::Entries& entries = restore_service->entries();
  int counts = 0;
  for (TabRestoreService::Entries::const_iterator it = entries.begin();
       it != entries.end();
       ++it) {
    bool is_valid_item = true;
    TabRestoreService::Entry* entry = *it;
    if (entry->type == TabRestoreService::TAB) {
      TabRestoreService::Tab* tab = static_cast<TabRestoreService::Tab*>(entry);
      is_valid_item = IsValidItem(tab);
    }
    if (is_valid_item)
      counts++;
  }
  return counts;
}

TabRestoreService::Entry* RestoreMenuModel::GetTRSEntry(int index) const {
  // get restore icon
  TabRestoreService* restore_service =
      TabRestoreServiceFactory::GetForProfile(browser_->profile());
  const TabRestoreService::Entries& entries = restore_service->entries();
  int pos = 0;
  TabRestoreService::Entry* entry = NULL;
  for (TabRestoreService::Entries::const_iterator it = entries.begin();
       it != entries.end();
       ++it) {
    bool is_valid_item = true;
    entry = *it;
    if (entry->type == TabRestoreService::TAB) {
      TabRestoreService::Tab* tab = static_cast<TabRestoreService::Tab*>(entry);
      is_valid_item = IsValidItem(tab);
    }
    if (is_valid_item && index == pos) {
      break;
    }
    if (is_valid_item)
      pos++;
  }
  return entry;
}

bool RestoreMenuModel::IsValidItem(const TabRestoreService::Tab* tab) const {
  if (tab->navigations.empty()) {
    return false;
  }
  const sessions::SerializedNavigationEntry& current_navigation =
      tab->navigations.at(tab->current_navigation_index);
  if (current_navigation.virtual_url() == GURL(chrome::kChromeUINewTabURL)) {
    return false;
  }
  return true;
}

std::string RestoreMenuModel::BuildActionName(const std::string& action,
                                              int index) const {
  DCHECK(!action.empty());
  DCHECK(index >= -1);
  std::string metric_string;
  metric_string += "RestoreMenu_";
  metric_string += action;
  if (index != -1) {
    // +1 is for historical reasons (indices used to start at 1).
    metric_string += base::IntToString(index + 1);
  }
  return metric_string;
}
}