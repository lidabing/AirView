// Copyright (c) 2014 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Defines all the command-line switches used by Chrome.

#ifndef CHROME_COMMON_CHROME_SWITCHES_H_
#define CHROME_COMMON_CHROME_SWITCHES_H_

#include "build/build_config.h"
#include "base/base_switches.h"

namespace switches {
extern const char kDefaultUseChromeLayout[];  //默认使用chrome的布局模式
extern const char kDefaultUseChromeSignin[];  //使用chrome默认登录方式
extern const char kEnableSidebar[];           //使用侧边栏
extern const char kShowSigninLogo[];          //显示用户头像
extern const char kAllowAllCrxInstall[];      //解除google对Crx安装限制
}

#endif