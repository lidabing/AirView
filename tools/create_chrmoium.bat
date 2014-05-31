%~d0  
cd %~dp0
cd ../..
cd chromium
set GYP_MSVS_VERSION=2013
set GYP_GENERATORS=msvs-ninja,ninja
set GYP_DEFINES=component=shared_library
gclient runhooks --force
cd src
ninja -C out\Debug chrome.exe