@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DIALOGTESTER.HPJ. >"hlp\DialogTester.hm"
echo. >>"hlp\DialogTester.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\DialogTester.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\DialogTester.hm"
echo. >>"hlp\DialogTester.hm"
echo // Prompts (IDP_*) >>"hlp\DialogTester.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\DialogTester.hm"
echo. >>"hlp\DialogTester.hm"
echo // Resources (IDR_*) >>"hlp\DialogTester.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\DialogTester.hm"
echo. >>"hlp\DialogTester.hm"
echo // Dialogs (IDD_*) >>"hlp\DialogTester.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\DialogTester.hm"
echo. >>"hlp\DialogTester.hm"
echo // Frame Controls (IDW_*) >>"hlp\DialogTester.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\DialogTester.hm"
REM -- Make help for Project DIALOGTESTER


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\DialogTester.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\DialogTester.hlp" goto :Error
if not exist "hlp\DialogTester.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\DialogTester.hlp" Debug
if exist Debug\nul copy "hlp\DialogTester.cnt" Debug
if exist Release\nul copy "hlp\DialogTester.hlp" Release
if exist Release\nul copy "hlp\DialogTester.cnt" Release
echo.
goto :done

:Error
echo hlp\DialogTester.hpj(1) : error: Problem encountered creating help file

:done
echo.
