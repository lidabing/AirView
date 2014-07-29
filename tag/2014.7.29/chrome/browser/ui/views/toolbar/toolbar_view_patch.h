// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TOOLBAR_TOOLBAR_VIEW_PATCH_H_
#define CHROME_BROWSER_UI_VIEWS_TOOLBAR_TOOLBAR_VIEW_PATCH_H_

#include "base/patch.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/bookmark_menu.h"

namespace views{
class ImageButton;
class MenuButton;
class View;
}

namespace gfx{
class Point;
}

X_START_CLASS_PATCH(ToolbarView)
 public:
  void Init();
  void LoadImages();
  void EnabledStateChangedForCommand(int id, bool enabled);
  bool FilterMenuButtonClicked(views::View* source, const gfx::Point& point);
  int GetLayoutWidth() const;
  int Layout(int position);

 private:
  views::ImageButton* restore_;
  views::MenuButton* bookmark_;
  scoped_ptr<views::BookMarkMenu> bookmark_menu_;

X_END_CLASS_PATCH(ToolbarView)

#endif  //CHROME_BROWSER_UI_VIEWS_TOOLBAR_TOOLBAR_VIEW_PATCH_H_