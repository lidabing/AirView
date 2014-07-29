// Copyright (c) 2011 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_BUTTON_DROPDOWN_FOR_RESTORE_H_
#define CHROME_BROWSER_UI_BUTTON_DROPDOWN_FOR_RESTORE_H_
#pragma once

#include "base/memory/weak_ptr.h"
#include "ui/views/context_menu_controller.h"
#include "ui/views/controls/button/image_button.h"
#include "ui/base/models/menu_model_delegate.h"

namespace ui {
class MenuModel;
}  // namespace ui

namespace views {
class MenuItemView;
class ButtonDropDownForRestore : public ImageButton,
                                 public ContextMenuController,
                                 public ui::MenuModelDelegate {
 public:
  // The button's class name.
  static const char kViewClassName[];

  ButtonDropDownForRestore(views::ButtonListener* listener,
                           ui::MenuModel* model);
  virtual ~ButtonDropDownForRestore();

  // If menu is currently pending for long press - stop it.
  void ClearPendingMenu();

  // Indicates if menu is currently showing.
  bool IsMenuShowing() const;

  // Overridden from views::View
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnMouseDragged(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;
  // Showing the drop down results in a MouseCaptureLost, we need to ignore it.
  virtual void OnMouseCaptureLost() OVERRIDE {}
  virtual void OnMouseExited(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;

  // Overridden from views::ContextMenuController
  virtual void ShowContextMenuForView(View* source,
                                      const gfx::Point& point,
                                      ui::MenuSourceType source_type) OVERRIDE;

  // ui::MenuModelDelegate
  virtual void OnIconChanged(int index);

 protected:
  // Overridden from CustomButton. Returns true if the button should become
  // pressed when a user holds the mouse down over the button. For this
  // implementation, both left and right mouse buttons can trigger a change
  // to the PUSHED state.
  virtual bool ShouldEnterPushedState(const ui::Event& event) OVERRIDE;

  // Returns if menu should be shown. Override this to change default behavior.
  virtual bool ShouldShowMenu();

  // Function to show the dropdown menu.
  virtual void ShowDropDownMenu(ui::MenuSourceType source_type);

 private:
  // The model that populates the attached menu.
  scoped_ptr<ui::MenuModel> model_;

  // Indicates if menu is currently showing.
  bool menu_showing_;

  // Y position of mouse when left mouse button is pressed
  int y_position_on_lbuttondown_;

  // Menu runner to display drop down menu.
  // scoped_ptr<MenuRunner> menu_runner_;

  // a weak ref
  views::MenuItemView* menu_;

  // A factory for tasks that show the dropdown context menu for the button.
  base::WeakPtrFactory<ButtonDropDownForRestore> show_menu_factory_;

  DISALLOW_COPY_AND_ASSIGN(ButtonDropDownForRestore);
};
}
#endif  // CHROME_BROWSER_UI_BUTTON_DROPDOWN_FOR_RESTORE_H_