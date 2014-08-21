:: Copyright (c) 2014 The AirView Authors. All rights reserved.
:: Use of this source code is governed by a BSD-style license that can be
:: found in the LICENSE file.

%~d0  
cd %~dp0
cd ../..
cd chromium
cd src
set GYP_MSVS_VERSION=2013
set GYP_GENERATORS=msvs-ninja,ninja
set GYP_DEFINES=branding=Chrome disable_nacl=1  disable_pnacl=1 disable_nacl_untrusted=1 fastbuild=1 remoting=0  enable_plugin_installation=0 enable_google_now=0  chromium_win_pch=1 enable_webrtc=1 tracing_like_official_build=1 buildtype=official ui_compositor_image_transport=0 enable_printing=1 enable_plugins=1   use_openmax_dl_fft=0 enable_eglimage=0  enable_google_now=0 clang_use_chrome_plugins=0 remove_webcore_debug_symbols=1 use_xi2_mt=0 enable_mdns=0  skia_support_gpu=0 cld_version=1
python build/gyp_chromium --depth=. -D msbuild_toolset=v110_xp
