// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/aura/tab_contents/web_drag_handler_aura.h"
#include "chrome/browser/autocomplete/autocomplete_classifier.h"
#include "chrome/browser/autocomplete/autocomplete_classifier_factory.h"
#include "chrome/browser/autocomplete/autocomplete_input.h"
#include "chrome/browser/autocomplete/autocomplete_match.h"
#include "chrome/browser/ui/browser_commands_patch.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/profiles/profile.h"
#include "ui/base/dragdrop/drag_drop_types.h"
#include "ui/base/dragdrop/os_exchange_data.h"
#include "ui/base/dragdrop/drop_target_event.h"

WebDragHanlderAura::WebDragHanlderAura() : web_contents_(NULL) {
}
WebDragHanlderAura::~WebDragHanlderAura() {
}
void WebDragHanlderAura::DragInitialize(content::WebContents* contents) {
  web_contents_ = contents;
}
void WebDragHanlderAura::OnDragEntered(const ui::DropTargetEvent& event) {
}
int WebDragHanlderAura::OnDragUpdated(const ui::DropTargetEvent& event) {
  return 0;
}
void WebDragHanlderAura::OnDragExited() {
}
int WebDragHanlderAura::OnPerformDrop(const ui::DropTargetEvent& event) {
  // Extract the URL and create a new ui::OSExchangeData containing the URL. We
  // do this as the TabStrip doesn't know about the autocomplete edit and needs
  // to know about it to handle 'paste and go'.
  GURL url;
  base::string16 title;
  ui::OSExchangeData mapped_data;
  if (!event.data().GetURLAndTitle(
          ui::OSExchangeData::CONVERT_FILENAMES, &url, &title) ||
      !url.is_valid()) {
    // The url isn't valid. Use the paste and go url.
    if (GetPasteAndGoURL(event.data(), &url))
      mapped_data.SetURL(url, base::string16());
    // else case: couldn't extract a url or 'paste and go' url. This ends up
    // passing through an ui::OSExchangeData with nothing in it. We need to do
    // this so that the tab strip cleans up properly.
  } else {
    mapped_data.SetURL(url, base::string16());
  }
  BrowserList* browser_list =
      BrowserList::GetInstance(chrome::GetActiveDesktop());

  chrome::OpenDragDropUrl(browser_list->GetLastActive(), web_contents_, url);
  /*
  chrome::NavigateParams params(browser_, url, content::PAGE_TRANSITION_LINK);
  params.tabstrip_index = index;

  if (drop_before) {
    content::RecordAction(UserMetricsAction("Tab_DropURLBetweenTabs"));
    params.disposition = NEW_FOREGROUND_TAB;
  } else {
    content::RecordAction(UserMetricsAction("Tab_DropURLOnTab"));
    params.disposition = CURRENT_TAB;
    params.source_contents = model_->GetWebContentsAt(index);
  }
  params.window_action = chrome::NavigateParams::SHOW_WINDOW;
  chrome::Navigate(&params);
  */
  return 1;
}

bool WebDragHanlderAura::GetPasteAndGoURL(const ui::OSExchangeData& data,
                                          GURL* url) {
  if (!data.HasString())
    return false;

  base::string16 text;
  if (!data.GetString(&text) || text.empty())
    return false;
  text = AutocompleteMatch::SanitizeString(text);

  AutocompleteMatch match;
  Profile* profile =
      Profile::FromBrowserContext(web_contents_->GetBrowserContext());
  AutocompleteClassifierFactory::GetForProfile(profile)
      ->Classify(text,
                 false,
                 false,
                 AutocompleteInput::INVALID_SPEC,
                 &match,
                 NULL);
  if (!match.destination_url.is_valid())
    return false;

  if (url)
    *url = match.destination_url;
  return true;
}
