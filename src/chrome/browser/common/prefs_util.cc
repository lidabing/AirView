#include "chrome/browser/common/prefs_util.h"

#include "base/prefs/pref_service.h"
#include "base/strings/utf_string_conversions.h"
#include "base/message_loop/message_loop.h"
#include "ui/events/event_constants.h"
#include "content/public/browser/web_contents.h"
#include "chrome/common/url_constants.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/common/x_pref_names.h"

#define DCHECK_UI_THREAD() \
	DCHECK(base::MessageLoop::current()->type() == base::MessageLoop::TYPE_UI)

namespace {
	Browser* GetLastActiveBrowser(){
		Browser* browser = BrowserList::GetInstance(chrome::GetActiveDesktop())->GetLastActive();
		if(!browser){
			DCHECK(0);
			return NULL;
		}
		return browser;
	}
}

namespace prefs_util{
	PrefService* GetLastUsedPrefService(){
		DCHECK_UI_THREAD();
		Profile* profile = ProfileManager::GetLastUsedProfile();
		DCHECK(profile);
		PrefService* prefs = profile->GetPrefs();
		DCHECK(prefs);
		return prefs;
	}

	GURL GetCurrentActiveTabURL(){
		DCHECK_UI_THREAD();
		Browser* browser = GetLastActiveBrowser();
		if(!browser)
			return GURL("");
		content::WebContents* web_contents= browser->tab_strip_model()->GetActiveWebContents();
		if(web_contents)
			return web_contents->GetURL();
		DCHECK(0);
		return GURL("");
	}

	WindowOpenDisposition GetDispositionForAddressBar(const GURL* current_url){
		DCHECK_UI_THREAD();
		PrefService* prefs = GetLastUsedPrefService();
		CHECK(prefs);
		if(current_url && current_url->DomainIs(chrome::kChromeUINewTabHost))
			return CURRENT_TAB;

		WindowOpenDisposition disposition = CURRENT_TAB;
		if(prefs->GetBoolean(prefs::kXOpenAddressInNewTab)){
			if(prefs->GetBoolean(prefs::kXNewTabForeground))
				disposition = NEW_FOREGROUND_TAB;
			else
				disposition = NEW_BACKGROUND_TAB;		
		}
		return disposition;
	}

	WindowOpenDisposition GetDispositionForBookMarks(const GURL* new_url,const GURL* current_url,int event_flags){
		DCHECK_UI_THREAD();
		PrefService* prefs = GetLastUsedPrefService();
		CHECK(prefs);
		if( new_url && new_url->SchemeIs("javascript") )
			return CURRENT_TAB;
		if(current_url && current_url->DomainIs(chrome::kChromeUINewTabHost))
			return CURRENT_TAB;

		bool middle_button = (event_flags & ui::EF_MIDDLE_MOUSE_BUTTON) != 0;
		bool alt_key =  (event_flags & ui::EF_ALT_DOWN) != 0;
		bool ctrl_key = (event_flags & ui::EF_CONTROL_DOWN) != 0;
		bool meta_key =  (event_flags & ui::EF_COMMAND_DOWN) != 0;
		bool shift_key =   (event_flags & ui::EF_SHIFT_DOWN) != 0;

		if (middle_button || ctrl_key){
			if(prefs->GetBoolean(prefs::kXNewTabForeground))
				return NEW_FOREGROUND_TAB;
			else
				return NEW_BACKGROUND_TAB;
		}

		WindowOpenDisposition disposition = NEW_FOREGROUND_TAB;
		if(prefs->GetBoolean(prefs::kXOpenBookmarksInNewTab)){
			disposition = NEW_FOREGROUND_TAB;
			if(!prefs->GetBoolean(prefs::kXNewTabForeground))
				disposition = NEW_BACKGROUND_TAB;
		}else{
			disposition = CURRENT_TAB;
		}
		return disposition;
	}

	WindowOpenDisposition GetDispositionForHomeButton(const GURL* current_url){
		DCHECK_UI_THREAD();
		PrefService* prefs = GetLastUsedPrefService();
		CHECK(prefs);
		if(current_url && current_url->DomainIs(chrome::kChromeUINewTabHost))
			return CURRENT_TAB;

		WindowOpenDisposition disposition = CURRENT_TAB;
		if(prefs->GetBoolean(prefs::kXOpenAddressInNewTab)){
			if(prefs->GetBoolean(prefs::kXNewTabForeground))
				disposition = NEW_FOREGROUND_TAB;
			else
				disposition = NEW_BACKGROUND_TAB;
		}
		return disposition;
	}

	bool IsLeftDoubleClickCloseTab(){
		DCHECK_UI_THREAD();
		PrefService* prefs = GetLastUsedPrefService();
		DCHECK(prefs);
		return prefs->GetBoolean(prefs::kXCloseTabWhenRLDoubleClick);	
	}

	bool IsRightClickedCloseTab(){
		DCHECK_UI_THREAD();
		PrefService* prefs = GetLastUsedPrefService();
		DCHECK(prefs);
		return prefs->GetBoolean(prefs::kXCloseTabWhenRightClick);	
	}
}