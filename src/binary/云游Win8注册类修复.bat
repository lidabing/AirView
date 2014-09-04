@echo off
reg query HKCR > 1.txt
for /f "tokens=1,2 delims=." %%a in (1.txt) do if %%a==HKEY_CLASSES_ROOT\AirViewHTML set id1=%%b
del 1.txt
reg delete HKCR\AirView.%id1%\.exe\shell\open\command /v DelegateExecute /f
reg delete HKCR\AirView.%id1%\.exe\shell\opennewwindow\command /v DelegateExecute /f
reg delete HKCR\AirViewHTML.%id1%\shell\open\command /v DelegateExecute /f
reg delete HKCR\AirView\.exe\shell\open\command /v DelegateExecute /f
reg delete HKCR\AirView\.exe\shell\opennewwindow\command /v DelegateExecute /f
reg delete HKCR\AirViewHTML\shell\open\command /v DelegateExecute /f
