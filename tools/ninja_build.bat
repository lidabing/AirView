:: Copyright (c) 2014 The AirView Authors. All rights reserved.
:: Use of this source code is governed by a BSD-style license that can be
:: found in the LICENSE file.

::新的创建工程功能，老的创建和生成方式文件太多，使用现在的去做优化

::@echo off

cd %~dp0

if /i "%1"=="help" goto help
if /i "%1"=="--help" goto help
if /i "%1"=="-help" goto help
if /i "%1"=="/help" goto help
if /i "%1"=="?" goto help
if /i "%1"=="-?" goto help
if /i "%1"=="--?" goto help
if /i "%1"=="/?" goto help


@rem Process arguments.
set config=Release
set msiplatform=x86
set link_mode=static
set target_arch=ia32
set debug_arg=


:next-arg
if "%1"=="" goto args-done
if /i "%1"=="debug"         set config=Debug&goto arg-ok
if /i "%1"=="release"       set config=Release&goto arg-ok
if /i "%1"=="x86"           set target_arch=ia32&goto arg-ok
if /i "%1"=="x64"           set target_arch=x64&goto arg-ok
if /i "%1"=="static"         set link_mode=static&goto arg-ok
if /i "%1"=="shared"         set link_mode=shared&goto arg-ok

echo Warning: ignoring invalid command line option `%1`.


:arg-ok
:arg-ok
shift
goto next-arg

:args-done
if "%config%"=="Debug" set output_dir=Debug
if "%config%"=="Release" set output_dir=Release
if "%target_arch%"=="x64" set target_arch_mode=target_arch=x64 
if "%target_arch%"=="x64" set output_dir=%config%_x64
if "%link_mode%"=="shared" set component_mode=component=shared_library;
goto install-environment

:install-environment
echo install-environment
%~d0  
cd %~dp0
cd ../..
cd chromium
cd src
goto create-project

:create-project
echo create-project
set GYP_GENERATORS=msvs-ninja,ninja
set GYP_DEFINES=%component_mode% %target_arch_mode% branding=Chrome disable_nacl=1  disable_pnacl=1 disable_nacl_untrusted=1 fastbuild=1 remoting=0  enable_plugin_installation=0 enable_google_now=0  chromium_win_pch=1 enable_webrtc=1 tracing_like_official_build=1 buildtype=official ui_compositor_image_transport=0 enable_printing=1 enable_plugins=1   use_openmax_dl_fft=0 enable_eglimage=0   clang_use_chrome_plugins=0 remove_webcore_debug_symbols=1 use_xi2_mt=0 enable_mdns=0  skia_support_gpu=0 cld_version=1
call python build/gyp_chromium --depth=. -D msbuild_toolset=v110_xp
echo Project files generated.
goto build

:build
echo %output_dir%
ninja -C out\%output_dir% mini_installer.exe
goto exit

:help
echo ninja_build.bat [release/debug] [ia32/x64] [static/shared]
echo Examples:
echo   ninja_build.bat                          : builds release 
echo   ninja_build.bat debug                    : builds debug 
echo   ninja_build.bat release x86  static      : builds release x86  static
goto exit


:exit
goto :EOF