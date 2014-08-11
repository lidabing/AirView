// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_BOOKMARK_MENU_H_
#define CHROME_BROWSER_UI_BOOKMARK_MENU_H_

#include "base/memory/scoped_ptr.h"
#include "components/bookmarks/core/browser/base_bookmark_model_observer.h"
#include "ui/base/models/menu_model.h"
#include "ui/views/controls/menu/menu_delegate.h"

class BookmarkMenuDelegate;
class Browser;

namespace views {
class MenuButton;
class MenuItemView;
class MenuRunner;
class View;
class Widget;

// BookMarkMenu adapts the WrenchMenuModel to view's menu related classes.
class BookMarkMenu : public views::MenuDelegate,
                     public BaseBookmarkModelObserver {
 public:
  explicit BookMarkMenu(Browser* browser);
  virtual ~BookMarkMenu();

  // Shows the menu relative to the specified view.
  void RunMenu(views::MenuButton* host, views::Widget* parent);

  // MenuDelegate overrides:
  virtual base::string16 GetTooltipText(int id,
                                        const gfx::Point& p) const OVERRIDE;
  virtual bool IsTriggerableEvent(views::MenuItemView* menu,
                                  const ui::Event& e) OVERRIDE;
  virtual bool GetDropFormats(
      views::MenuItemView* menu,
      int* formats,
      std::set<ui::OSExchangeData::CustomFormat>* custom_formats) OVERRIDE;
  virtual bool AreDropTypesRequired(views::MenuItemView* menu) OVERRIDE;
  virtual bool CanDrop(views::MenuItemView* menu,
                       const ui::OSExchangeData& data) OVERRIDE;
  virtual int GetDropOperation(views::MenuItemView* item,
                               const ui::DropTargetEvent& event,
                               DropPosition* position) OVERRIDE;
  virtual int OnPerformDrop(views::MenuItemView* menu,
                            DropPosition position,
                            const ui::DropTargetEvent& event) OVERRIDE;
  virtual bool ShowContextMenu(views::MenuItemView* source,
                               int id,
                               const gfx::Point& p,
                               ui::MenuSourceType source_type) OVERRIDE;
  virtual bool CanDrag(views::MenuItemView* menu) OVERRIDE;
  virtual void WriteDragData(views::MenuItemView* sender,
                             ui::OSExchangeData* data) OVERRIDE;
  virtual int GetDragOperations(views::MenuItemView* sender) OVERRIDE;
  virtual int GetMaxWidthForMenu(views::MenuItemView* menu) OVERRIDE;
  virtual bool IsItemChecked(int id) const OVERRIDE;
  virtual bool IsCommandEnabled(int id) const OVERRIDE;
  virtual void ExecuteCommand(int id, int mouse_event_flags) OVERRIDE;
  virtual void WillShowMenu(views::MenuItemView* menu) OVERRIDE;
  // BaseBookmarkModelObserver overrides:
  virtual void BookmarkModelChanged() OVERRIDE;

 private:
  scoped_ptr<views::MenuRunner> menu_runner_;
  // Browser the menu is being shown for.
  Browser* browser_;
  // Used for managing the bookmark menu items.
  scoped_ptr<BookmarkMenuDelegate> bookmark_menu_delegate_;

  DISALLOW_COPY_AND_ASSIGN(BookMarkMenu);
};
}  // namespace views
#endif  // CHROME_BROWSER_UI_BOOKMARK_MENU_H_
