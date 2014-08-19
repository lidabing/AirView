// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/toolbar/toolbar_view_patch.h"

#include "chrome/browser/ui/views/toolbar/toolbar_view.h"
#include "ui/views/controls/button/menu_button.h"
#include "ui/views/controls/button/image_button.h"
#include "chrome/browser/ui/button_dropdown_for_restore.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/gfx/image/image_skia_source.h"
#include "grit/generated_resources.h"
#include "grit/theme_resources.h"
#include "ui/base/theme_provider.h"
#include "ui/base/l10n/l10n_util.h"
#include "chrome/browser/ui/restore_menu_model.h"
#include "chrome/app/chrome_command_ids_patch.h"

void X_CLASS_PATCH_NAME(ToolbarView)::Init() {
  restore_ = new views::ButtonDropDownForRestore(
      that_, new ui::RestoreMenuModel(that_->browser_));
  restore_->set_triggerable_event_flags(ui::EF_LEFT_MOUSE_BUTTON |
                                        ui::EF_MIDDLE_MOUSE_BUTTON);
  restore_->set_tag(IDC_X_RESTORE);
  restore_->SetImageAlignment(views::ImageButton::ALIGN_RIGHT,
                              views::ImageButton::ALIGN_TOP);
  restore_->SetTooltipText(l10n_util::GetStringUTF16(IDS_TOOLTIP_X_RESTORE));
  restore_->SetAccessibleName(l10n_util::GetStringUTF16(IDS_ACCNAME_X_RESTORE));
  // restore_->set_id(VIEW_ID_X_RESTORE_BUTTON);
  that_->AddChildView(restore_);

  bookmark_ = new views::MenuButton(NULL, base::string16(), that_, false);
  bookmark_->SetBorder(views::Border::NullBorder());
  bookmark_->SetTooltipText(
      l10n_util::GetStringUTF16(IDS_X_BOOKMARK_MENU_TOOLTIP));
  // bookmark_->set_id(VIEW_ID_X_BOOKMARK_MENU);
  that_->AddChildView(bookmark_);
}

void X_CLASS_PATCH_NAME(ToolbarView)::LoadImages() {
  ui::ThemeProvider* tp = that_->GetThemeProvider();
  restore_->SetImage(views::CustomButton::STATE_NORMAL,
                     tp->GetImageSkiaNamed(IDR_RESTORE_BUTTON));
  restore_->SetImage(views::CustomButton::STATE_HOVERED,
                     tp->GetImageSkiaNamed(IDR_RESTORE_BUTTON_H));
  restore_->SetImage(views::CustomButton::STATE_PRESSED,
                     tp->GetImageSkiaNamed(IDR_RESTORE_BUTTON_P));

  bookmark_->SetIcon(*tp->GetImageSkiaNamed(IDR_X_BOOKMARK));
  bookmark_->SetHoverIcon(*tp->GetImageSkiaNamed(IDR_X_BOOKMARK_H));
  bookmark_->SetPushedIcon(*tp->GetImageSkiaNamed(IDR_X_BOOKMARK_P));
}

void X_CLASS_PATCH_NAME(
    ToolbarView)::EnabledStateChangedForCommand(int id, bool enabled) {
  views::Button* button = NULL;
  switch (id) {
    case IDC_X_RESTORE:
      button = restore_;
      break;
  }
  if (button)
    button->SetEnabled(enabled);
}

bool X_CLASS_PATCH_NAME(ToolbarView)::FilterMenuButtonClicked(
    views::View* source,
    const gfx::Point& point) {
  if (source == bookmark_) {
    bookmark_menu_.reset(new views::BookMarkMenu(that_->browser_));
    bookmark_menu_->RunMenu(bookmark_, that_->GetWidget());
    return true;
  }
  return false;
}

int X_CLASS_PATCH_NAME(ToolbarView)::GetLayoutWidth() const {
  int width = restore_->GetPreferredSize().width() + that_->kStandardSpacing +
              bookmark_->GetPreferredSize().width() + that_->kStandardSpacing;
  return width;
}

int X_CLASS_PATCH_NAME(ToolbarView)::Layout(int position) {
  int child_height =
      std::min(restore_->GetPreferredSize().height(), that_->height());
  int child_y = (that_->height() - child_height + 1) / 2;

  restore_->SetBounds(
      position, child_y, restore_->GetPreferredSize().width(), child_height);
  position = restore_->bounds().right() + that_->kStandardSpacing;

  bookmark_->SetBounds(
      position, child_y, bookmark_->GetPreferredSize().width(), child_height);
  position = bookmark_->bounds().right() + that_->kStandardSpacing;

  return position;
}