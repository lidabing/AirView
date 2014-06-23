// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AURA_TAB_CONTENTS_WEB_DRAG_HANDLER_AURA_H_
#define CHROME_BROWSER_UI_AURA_TAB_CONTENTS_WEB_DRAG_HANDLER_AURA_H_

#include "content/public/browser/x_web_drag_drop_delegate.h"
#include "content/public/browser/web_contents.h"

namespace content {
class WebContents;
}
namespace ui {
class OSExchangeData;
}
class GURL;
class WebDragHanlderAura : public content::XWebDragDropDelegate {
 public:
  WebDragHanlderAura();
  virtual ~WebDragHanlderAura();
  // content::XWebDragDropDelegate:
  virtual void DragInitialize(content::WebContents* contents) OVERRIDE;
  virtual void OnDragEntered(const ui::DropTargetEvent& event) OVERRIDE;
  virtual int OnDragUpdated(const ui::DropTargetEvent& event) OVERRIDE;
  virtual void OnDragExited() OVERRIDE;
  virtual int OnPerformDrop(const ui::DropTargetEvent& event) OVERRIDE;


 public:
// Called to indicate whether the given URL is a supported file.
 //void FileSupported(const GURL& url, bool supported);
 private:
  bool GetPasteAndGoURL(const ui::OSExchangeData& data, GURL* url);
  content::WebContents* web_contents_;

  DISALLOW_COPY_AND_ASSIGN(WebDragHanlderAura);
};

#endif  // CHROME_BROWSER_UI_AURA_TAB_CONTENTS_WEB_DRAG_HANDLER_AURA_H_