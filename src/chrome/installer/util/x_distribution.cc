// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// This file defines specific implementation of BrowserDistribution class for
// Google Chrome.

#include "chrome/installer/util/x_distribution.h"

#include <windows.h>
#include <msi.h>

#include "base/files/file_path.h"
#include "base/path_service.h"
#include "base/strings/string_util.h"
#include "base/strings/stringprintf.h"
#include "base/strings/utf_string_conversions.h"
#include "base/win/registry.h"
#include "base/win/windows_version.h"
#include "chrome/common/chrome_icon_resources_win.h"
#include "chrome/common/net/test_server_locations.h"
#include "chrome/installer/util/app_registration_data.h"
#include "chrome/installer/util/channel_info.h"
#include "chrome/installer/util/google_update_constants.h"
#include "chrome/installer/util/google_update_settings.h"
#include "chrome/installer/util/helper.h"
#include "chrome/installer/util/install_util.h"
#include "chrome/installer/util/l10n_string_util.h"
#include "chrome/installer/util/uninstall_metrics.h"
#include "chrome/installer/util/updating_app_registration_data.h"
#include "chrome/installer/util/util_constants.h"
#include "chrome/installer/util/wmi.h"
#include "content/public/common/result_codes.h"

#include "installer_util_strings.h"  // NOLINT

namespace {

const wchar_t kChromeGuid[] = L"{aA69D345-D564-463c-AFF1-A69D9E530F26}";
const wchar_t kBrowserAppId[] = L"AirView";
const wchar_t kBrowserProgIdPrefix[] = L"AirViewHTML";
const wchar_t kBrowserProgIdDesc[] = L"AirView HTML Document";
const wchar_t kCommandExecuteImplUuid[] =
    L"{5C65F4B0-3651-4514-B207-D20CB699B14B}";

// Substitute the locale parameter in uninstall URL with whatever
// Google Update tells us is the locale. In case we fail to find
// the locale, we use US English.
base::string16 LocalizeUrl(const wchar_t* url) {
  base::string16 language;
  if (!GoogleUpdateSettings::GetLanguage(&language))
    language = L"en-US";  // Default to US English.
  return ReplaceStringPlaceholders(url, language.c_str(), NULL);
}

base::string16 GetUninstallSurveyUrl() {
  const wchar_t kSurveyUrl[] = L"http://www.google.com/support/chrome/bin/"
                               L"request.py?hl=$1&contact_type=uninstall";
  return LocalizeUrl(kSurveyUrl);
}

}  // namespace

XDistribution::XDistribution()
    : BrowserDistribution(CHROME_BROWSER,
          make_scoped_ptr(
              new UpdatingAppRegistrationData(kChromeGuid))) {
}

XDistribution::XDistribution(
    scoped_ptr<AppRegistrationData> app_reg_data)
    : BrowserDistribution(CHROME_BROWSER, app_reg_data.Pass()) {
}

void XDistribution::DoPostUninstallOperations(
    const Version& version,
    const base::FilePath& local_data_path,
    const base::string16& distribution_data) {
  // Send the Chrome version and OS version as params to the form.
  // It would be nice to send the locale, too, but I don't see an
  // easy way to get that in the existing code. It's something we
  // can add later, if needed.
  // We depend on installed_version.GetString() not having spaces or other
  // characters that need escaping: 0.2.13.4. Should that change, we will
  // need to escape the string before using it in a URL.
  const base::string16 kVersionParam = L"crversion";
  const base::string16 kOSParam = L"os";
  base::win::OSInfo::VersionNumber version_number =
      base::win::OSInfo::GetInstance()->version_number();
  base::string16 os_version = base::StringPrintf(L"%d.%d.%d",
      version_number.major, version_number.minor, version_number.build);

  base::FilePath iexplore;
  if (!PathService::Get(base::DIR_PROGRAM_FILES, &iexplore))
    return;

  iexplore = iexplore.AppendASCII("Internet Explorer");
  iexplore = iexplore.AppendASCII("iexplore.exe");

  base::string16 command = iexplore.value() + L" " + GetUninstallSurveyUrl() +
      L"&" + kVersionParam + L"=" + base::UTF8ToWide(version.GetString()) +
      L"&" + kOSParam + L"=" + os_version;

  base::string16 uninstall_metrics;
  if (installer::ExtractUninstallMetricsFromFile(local_data_path,
                                                 &uninstall_metrics)) {
    // The user has opted into anonymous usage data collection, so append
    // metrics and distribution data.
    command += uninstall_metrics;
    if (!distribution_data.empty()) {
      command += L"&";
      command += distribution_data;
    }
  }

  int pid = 0;
  // The reason we use WMI to launch the process is because the uninstall
  // process runs inside a Job object controlled by the shell. As long as there
  // are processes running, the shell will not close the uninstall applet. WMI
  // allows us to escape from the Job object so the applet will close.
  installer::WMIProcess::Launch(command, &pid);
}

base::string16 XDistribution::GetActiveSetupGuid() {
  return /*product_guid()*/base::string16();
}

base::string16 XDistribution::GetBaseAppName() {
  // I'd really like to return L ## PRODUCT_FULLNAME_STRING; but that's no good
  // since it'd be "Chromium" in a non-Chrome build, which isn't at all what I
  // want.  Sigh.
  return L"AirView";
}

base::string16 XDistribution::GetShortcutName(
    ShortcutType shortcut_type) {
	return GetBaseAppName();
}

int XDistribution::GetIconIndex(ShortcutType shortcut_type) {
  if (shortcut_type == SHORTCUT_APP_LAUNCHER)
    return icon_resources::kAppLauncherIndex;
  DCHECK(shortcut_type == SHORTCUT_CHROME ||
         shortcut_type == SHORTCUT_CHROME_ALTERNATE) << shortcut_type;
  return icon_resources::kApplicationIndex;
}

base::string16 XDistribution::GetBaseAppId() {
  return kBrowserAppId;
}

base::string16 XDistribution::GetBrowserProgIdPrefix() {
  return kBrowserProgIdPrefix;
}

base::string16 XDistribution::GetBrowserProgIdDesc() {
  return kBrowserProgIdDesc;
}

base::string16 XDistribution::GetInstallSubDir() {
	return L"AirView";
}

base::string16 XDistribution::GetPublisherName() {
  const base::string16& publisher_name =
      installer::GetLocalizedString(IDS_ABOUT_VERSION_COMPANY_NAME_BASE);
  return publisher_name;
}

base::string16 XDistribution::GetAppDescription() {
  const base::string16& app_description =
      installer::GetLocalizedString(IDS_SHORTCUT_TOOLTIP_BASE);
  return app_description;
}

std::string XDistribution::GetSafeBrowsingName() {
  return "AirView";
}

std::string XDistribution::GetNetworkStatsServer() const {
  return chrome_common_net::kEchoTestServerLocation;
}

base::string16 XDistribution::GetDistributionData(HKEY root_key) {
	return base::string16();
}

base::string16 XDistribution::GetUninstallLinkName() {
  const base::string16& link_name =
      installer::GetLocalizedString(IDS_UNINSTALL_CHROME_BASE);
  return link_name;
}

base::string16 XDistribution::GetUninstallRegPath() {
  return L"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"
         L"AirView";
}

base::string16 XDistribution::GetIconFilename() {
  return installer::kChromeExe;
}

bool XDistribution::GetCommandExecuteImplClsid(
    base::string16* handler_class_uuid) {
	return false;
}

bool XDistribution::AppHostIsSupported() {
  return false;
}

// This method checks if we need to change "ap" key in Google Update to try
// full installer as fall back method in case incremental installer fails.
// - If incremental installer fails we append a magic string ("-full"), if
// it is not present already, so that Google Update server next time will send
// full installer to update Chrome on the local machine
// - If we are currently running full installer, we remove this magic
// string (if it is present) regardless of whether installer failed or not.
// There is no fall-back for full installer :)
void XDistribution::UpdateInstallStatus(bool system_install,
    installer::ArchiveType archive_type,
    installer::InstallStatus install_status) {
  
}

bool XDistribution::ShouldSetExperimentLabels() {
  return false;
}

bool XDistribution::HasUserExperiments() {
  return false;
}
