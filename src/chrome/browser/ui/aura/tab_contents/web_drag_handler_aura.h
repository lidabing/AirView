// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AURA_TAB_CONTENTS_WEB_DRAG_HANDLER_AURA_H_
#define CHROME_BROWSER_UI_AURA_TAB_CONTENTS_WEB_DRAG_HANDLER_AURA_H_

#include "ui/wm/public/drag_drop_delegate.h"
#include "content/public/browser/web_contents.h"

namespace content {
class WebContents;
}

class WebDragHanlderAura : public aura::client::DragDropDelegate {
 public:
  WebDragHanlderAura(content::WebContents* contents);
  virtual ~WebDragHanlderAura();
  // Overridden from aura::client::DragDropDelegate:
  virtual void OnDragEntered(const ui::DropTargetEvent& event) OVERRIDE;
  virtual int OnDragUpdated(const ui::DropTargetEvent& event) OVERRIDE;
  virtual void OnDragExited() OVERRIDE;
  virtual int OnPerformDrop(const ui::DropTargetEvent& event) OVERRIDE;

 private:
  content::WebContents* web_contents_;

  DISALLOW_COPY_AND_ASSIGN(WebDragHanlderAura);
};

#endif  // CHROME_BROWSER_UI_AURA_TAB_CONTENTS_WEB_DRAG_HANDLER_AURA_H_