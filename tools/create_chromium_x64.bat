%~d0  
cd %~dp0
cd ../..
cd chromium
cd src
#set GYP_MSVS_VERSION=2013e
#set GYP_GENERATORS=msvs-ninja,ninja
set GYP_GENERATORS=ninja
set GYP_DEFINES=disable_nacl=1  disable_pnacl=1 disable_nacl_untrusted=1 fastbuild=2 remoting=0  enable_plugin_installation=0 enable_google_now=0  chromium_win_pch=1 ffmpeg_branding=Chrome proprietary_codecs=1
python build/gyp_chromium --depth=. -Dtarget_arch=x64

