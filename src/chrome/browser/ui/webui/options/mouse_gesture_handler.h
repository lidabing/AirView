// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_MOUSE_GESTURE_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_MOUSE_GESTURE_HANDLER_H_

#include "chrome/browser/ui/webui/options/options_ui.h"
#include "base/values.h"

class MouseGestureHandler : public options::OptionsPageUIHandler {
 public:
  virtual void GetLocalizedValues(base::DictionaryValue* localized_strings);
  virtual void InitializePage();
  virtual void RegisterMessages();

 private:
  void SetupMouseGestureActionsList();

  void SetMouseGesture(const base::ListValue* args);
};

#endif  // CHROME_BROWSER_UI_WEBUI_OPTIONS_MOUSE_GESTURE_HANDLER_H_