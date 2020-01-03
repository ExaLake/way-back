@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by COMCLIENT.HPJ. >"hlp\COMClient.hm"
echo. >>"hlp\COMClient.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\COMClient.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\COMClient.hm"
echo. >>"hlp\COMClient.hm"
echo // Prompts (IDP_*) >>"hlp\COMClient.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\COMClient.hm"
echo. >>"hlp\COMClient.hm"
echo // Resources (IDR_*) >>"hlp\COMClient.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\COMClient.hm"
echo. >>"hlp\COMClient.hm"
echo // Dialogs (IDD_*) >>"hlp\COMClient.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\COMClient.hm"
echo. >>"hlp\COMClient.hm"
echo // Frame Controls (IDW_*) >>"hlp\COMClient.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\COMClient.hm"
REM -- Make help for Project COMCLIENT


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\COMClient.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\COMClient.hlp" goto :Error
if not exist "hlp\COMClient.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\COMClient.hlp" Debug
if exist Debug\nul copy "hlp\COMClient.cnt" Debug
if exist Release\nul copy "hlp\COMClient.hlp" Release
if exist Release\nul copy "hlp\COMClient.cnt" Release
echo.
goto :done

:Error
echo hlp\COMClient.hpj(1) : error: Problem encountered creating help file

:done
echo.
