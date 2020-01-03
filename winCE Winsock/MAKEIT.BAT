@echo off

setlocal

set CEVersion=200
set CESubsystem=windowsce,2.0
set CEConfigName=H/PC Ver. 2.00


set RC_FLAGS=/l 0x409 /D"DEBUG"
set C_FLAGS=/nologo /MTd /W3 /Gm /GX /Zi /Od /D"WIN32" /D"_DEBUG" /D"_WINDOWS" /D"UNICODE" /D "_UNICODE" /c /YX
set LINK_FLAGS=kernel32.lib user32.lib wsock32.lib /nologo /subsystem:windows /incremental:yes /debug /pdbtype:sept

set WCE_RC_FLAGS=/l 0x409 /r /d "UNDER_CE" /D_WIN32_WCE=200 /D"UNICODE" /D"DEBUG"
set WCE_C_FLAGS=/nologo /MLd /W3 /Zi /Od /D_WIN32_WCE=200 /D"DEBUG" /D"UNDER_CE" /D"UNICODE" /c /YX
set WCE_LINK_FLAGS=commctrl.lib coredll.lib winsock.lib /nologo /entry:"WinMainCRTStartup" /base:"0x00010000" /incremental:yes /debug /subsystem:windowsce,2.0 

set SH_FLAGS=/D"SHx" /D"SH3" /D"_SH3_" 
set MIPS_FLAGS=/D"MIPS" /D"_MIPS_" 

if "%1"=="client" goto client
if "%1"=="server" goto server
goto usage

:usage
echo "syntax: MAKEIT {server | client [sh|mips]}"
goto quit

:client

set INCLUDE=c:\devstudio\wce\include\wce200;c:\devstudio\wce\mfc\include\wce200

if "%2"=="sh" goto shclient
if "%2"=="mips" goto mipsclient
goto usage

:shclient
set LIB=c:\devstudio\wce\lib\wce200\wcesh

if not exist ".\WCESHdbg/" mkdir ".\WCESHDbg"
rc %WCE_RC_FLAGS% %SH_FLAGS% /fo".\WCESHDbg\SockTest.res" SockTest.rc
shcl %WCE_C_FLAGS% %SH_FLAGS% /Fp".\WCESHDbg\SockTest.pch" /Fo".\WCESHDbg\\" /Fd".\WCESHDbg\\" SockTest.c
link %WCE_LINK_FLAGS% /pdb:".\WCESHDbg\SockTest.pdb" /out:".\WCESHDbg\SockTest.exe" /machine:SH3 .\WCESHDbg\SockTest.obj .\WCESHDbg\SockTest.res
goto quit

:mipsclient
set LIB=c:\devstudio\wce\lib\wce200\wcemips

if not exist ".\WMIPSDbg/" mkdir ".\WMIPSDbg"
rc %WCE_RC_FLAGS% %MIPS_FLAGS% /fo".\WMIPSDbg\SockTest.res" SockTest.rc
clmips %WCE_C_FLAGS% %MIPS_FLAGS% /QMRWCE /Fp".\WMIPSDbg\SockTest.pch" /Fo".\WMIPSDbg\\" /Fd".\WMIPSDbg\\" SockTest.c
link %WCE_LINK_FLAGS% /pdb:".\WMIPSDbg\SockTest.pdb" /out:".\WMIPSDbg\SockTest.exe" /machine:MIPS .\WMIPSDbg\SockTest.obj .\WMIPSDbg\SockTest.res
goto quit


:server
set LIB=c:\devstudio\vc\lib

if not exist ".\Debug" mkdir ".\Debug"
rc %RC_FLAGS% /fo".\Debug\SockTest.res" SockTest.rc
cl %C_FLAGS% /Fp".\Debug\SockTest.pch" /Fo".\Debug\\" /Fd".\Debug\\" SockTest.c
link %LINK_FLAGS% /pdb:".\Debug\SockTest.pdb" /out:".\Debug\SockTest.exe" /machine:I386 .\Debug\SockTest.obj .\Debug\SockTest.res
goto quit


:quit

endlocal
