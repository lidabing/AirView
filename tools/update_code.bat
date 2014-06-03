@	echo
:: Copyright (c) 2014 The AirView Authors. All rights reserved.
:: Use of this source code is governed by a BSD-style license that can be
:: found in the LICENSE file.

:: This is required with cygwin only.
PATH=%~dp0;%PATH%
call get_chromium_src.bat
%~d0  
cd %~dp0
cd ..
cd ..
cd chromium
gclient sync --force