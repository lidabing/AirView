// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/bookmark_menu.h"

#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "chrome/app/chrome_command_ids.h"
#include "components/bookmarks/browser/bookmark_model.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/views/bookmarks/bookmark_menu_delegate.h"
#include "chrome/browser/bookmarks/bookmark_model_factory.h"
#include "content/public/browser/user_metrics.h"
#include "content/public/browser/notification_types.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/notification_source.h"
#include "ui/views/controls/menu/menu_config.h"
#include "ui/views/controls/menu/menu_item_view.h"
#include "ui/views/controls/button/menu_button.h"
#include "ui/views/controls/menu/menu_runner.h"

using ui::MenuModel;
using views::MenuItemView;
// using views::TextButton;
using views::View;

namespace views {
BookMarkMenu::BookMarkMenu(Browser* browser) : browser_(browser) {
}

BookMarkMenu::~BookMarkMenu() {
  if (bookmark_menu_delegate_.get()) {
    BookmarkModel* model =
        BookmarkModelFactory::GetForProfile(browser_->profile());
    if (model)
      model->RemoveObserver(this);
  }
}

void BookMarkMenu::RunMenu(views::MenuButton* host, views::Widget* parent) {
  BookmarkModel* model =
      BookmarkModelFactory::GetForProfile(browser_->profile());
  if (!model->loaded())
    return;

  model->AddObserver(this);

  bookmark_menu_delegate_.reset(
      new BookmarkMenuDelegate(browser_, browser_, parent, 1, kint32max));
  bookmark_menu_delegate_->Init(this,
                                NULL,
                                model->bookmark_bar_node(),
                                0,
                                BookmarkMenuDelegate::SHOW_PERMANENT_FOLDERS,
                                BOOKMARK_LAUNCH_LOCATION_NONE);

  menu_runner_.reset(new views::MenuRunner(bookmark_menu_delegate_->menu()));

  gfx::Point screen_loc;
  views::View::ConvertPointToScreen(host, &screen_loc);
  gfx::Rect bounds(screen_loc, host->size());
  content::RecordAction(base::UserMetricsAction("ShowToolbarBookMarkMenu"));
  if (menu_runner_->RunMenuAt(host->GetWidget(),
                              host,
                              bounds,
                              views::MENU_ANCHOR_TOPLEFT,
                              ui::MENU_SOURCE_NONE,
                              views::MenuRunner::HAS_MNEMONICS) ==
      views::MenuRunner::MENU_DELETED)
    return;
  if (bookmark_menu_delegate_.get()) {
    BookmarkModel* model =
        BookmarkModelFactory::GetForProfile(browser_->profile());
    if (model)
      model->RemoveObserver(this);
  }
}
base::string16 BookMarkMenu::GetTooltipText(int id, const gfx::Point& p) const {
  return bookmark_menu_delegate_->GetTooltipText(id, p);
}
bool BookMarkMenu::IsTriggerableEvent(views::MenuItemView* menu,
                                      const ui::Event& e) {
  return bookmark_menu_delegate_->IsTriggerableEvent(menu, e);
}
bool BookMarkMenu::GetDropFormats(
    MenuItemView* menu,
    int* formats,
    std::set<ui::OSExchangeData::CustomFormat>* custom_formats) {
  return bookmark_menu_delegate_->GetDropFormats(menu, formats, custom_formats);
}
bool BookMarkMenu::AreDropTypesRequired(MenuItemView* menu) {
  return bookmark_menu_delegate_->AreDropTypesRequired(menu);
}
bool BookMarkMenu::CanDrop(MenuItemView* menu, const ui::OSExchangeData& data) {
  return bookmark_menu_delegate_->CanDrop(menu, data);
}
int BookMarkMenu::GetDropOperation(MenuItemView* item,
                                   const ui::DropTargetEvent& event,
                                   DropPosition* position) {
  return bookmark_menu_delegate_->GetDropOperation(item, event, position);
}
int BookMarkMenu::OnPerformDrop(MenuItemView* menu,
                                DropPosition position,
                                const ui::DropTargetEvent& event) {
  int result = bookmark_menu_delegate_->OnPerformDrop(menu, position, event);
  return result;
}
bool BookMarkMenu::ShowContextMenu(MenuItemView* source,
                                   int id,
                                   const gfx::Point& p,
                                   ui::MenuSourceType source_type) {
  return bookmark_menu_delegate_->ShowContextMenu(source, id, p, source_type);
}
bool BookMarkMenu::CanDrag(MenuItemView* menu) {
  return bookmark_menu_delegate_->CanDrag(menu);
}
void BookMarkMenu::WriteDragData(MenuItemView* sender,
                                 ui::OSExchangeData* data) {
  return bookmark_menu_delegate_->WriteDragData(sender, data);
}
int BookMarkMenu::GetDragOperations(MenuItemView* sender) {
  return bookmark_menu_delegate_->GetDragOperations(sender);
}
int BookMarkMenu::GetMaxWidthForMenu(MenuItemView* menu) {
  return bookmark_menu_delegate_->GetMaxWidthForMenu(menu);
}
bool BookMarkMenu::IsItemChecked(int id) const {
  return false;
}
bool BookMarkMenu::IsCommandEnabled(int id) const {
  return true;
}
void BookMarkMenu::ExecuteCommand(int id, int mouse_event_flags) {
  bookmark_menu_delegate_->ExecuteCommand(id, mouse_event_flags);
  return;
}

void BookMarkMenu::WillShowMenu(MenuItemView* menu) {
}
void BookMarkMenu::BookmarkModelChanged() {
}
}  // namespace views