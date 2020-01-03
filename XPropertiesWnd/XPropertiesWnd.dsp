# Microsoft Developer Studio Project File - Name="XPropertiesWnd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=XPropertiesWnd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XPropertiesWnd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XPropertiesWnd.mak" CFG="XPropertiesWnd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XPropertiesWnd - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XPropertiesWnd - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XPropertiesWnd - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XPropertiesWnd - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XPropertiesWnd - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "OEM_RESOURCE" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /nodefaultlib
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=.\Release\XPropertiesWnd.ocx
InputPath=.\Release\XPropertiesWnd.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "XPropertiesWnd - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "C:\Development\MyProjects\IvdeProcessController" /D "OEMRESOURCE" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_WIN32_DCOM" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\XPropertiesWnd.ocx
InputPath=.\Debug\XPropertiesWnd.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "XPropertiesWnd - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Ext "ocx"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "OEM_RESOURCE" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\XPropertiesWnd.ocx
InputPath=.\DebugU\XPropertiesWnd.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "XPropertiesWnd - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Ext "ocx"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "OEM_RESOURCE" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\XPropertiesWnd.ocx
InputPath=.\ReleaseU\XPropertiesWnd.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "XPropertiesWnd - Win32 Release"
# Name "XPropertiesWnd - Win32 Debug"
# Name "XPropertiesWnd - Win32 Unicode Debug"
# Name "XPropertiesWnd - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ADORMultiColumnComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\adorrecset.cpp
# End Source File
# Begin Source File

SOURCE=.\AsControls.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlsWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DateComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\DropEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DropListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\HighLightButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ModalEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiColumnComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\PageListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PageListCtrlDesign.cpp
# End Source File
# Begin Source File

SOURCE=.\ReflectShellTree.cpp
# End Source File
# Begin Source File

SOURCE=.\rttim.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellTree.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\XDesignPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\XFloorPropertiesWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\XFloorPropertiesWndDesign.cpp
# End Source File
# Begin Source File

SOURCE=.\xfloorwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\XGeneralWndPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWnd.def
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWnd.odl
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWnd.rc
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWndCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWndPpg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADORMultiColumnComboBox.h
# End Source File
# Begin Source File

SOURCE=.\adorrecset.h
# End Source File
# Begin Source File

SOURCE=.\AsControls.h
# End Source File
# Begin Source File

SOURCE=.\ColorHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.h
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.h
# End Source File
# Begin Source File

SOURCE=.\ControlsWnd.h
# End Source File
# Begin Source File

SOURCE=.\DateComboBox.h
# End Source File
# Begin Source File

SOURCE=.\DropEdit.h
# End Source File
# Begin Source File

SOURCE=.\DropListBox.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\gdi.h
# End Source File
# Begin Source File

SOURCE=.\HighLightButton.h
# End Source File
# Begin Source File

SOURCE=.\ItemToolTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ModalEdit.h
# End Source File
# Begin Source File

SOURCE=.\MultiColumnComboBox.h
# End Source File
# Begin Source File

SOURCE=.\PageListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PageListCtrlDesign.h
# End Source File
# Begin Source File

SOURCE=.\ReflectShellTree.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rttim.h
# End Source File
# Begin Source File

SOURCE=.\ShellTree.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XDesignPopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\XFloorPropertiesWnd.h
# End Source File
# Begin Source File

SOURCE=.\XFloorPropertiesWndDesign.h
# End Source File
# Begin Source File

SOURCE=.\xfloorwnd.h
# End Source File
# Begin Source File

SOURCE=.\XGeneralWndPropPage.h
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWnd.h
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWndCtl.h
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWndPpg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\icon_clk.ico
# End Source File
# Begin Source File

SOURCE=.\icon_dot.ico
# End Source File
# Begin Source File

SOURCE=.\icon_dow.ico
# End Source File
# Begin Source File

SOURCE=.\icon_fon.ico
# End Source File
# Begin Source File

SOURCE=.\icon_ret.ico
# End Source File
# Begin Source File

SOURCE=.\icon_up.ico
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWnd.ico
# End Source File
# Begin Source File

SOURCE=.\XPropertiesWndCtl.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section XPropertiesWnd : {24FFD1ED-5EA9-11D2-86B1-0040055C08D9}
# 	2:21:DefaultSinkHeaderFile:xfloorwnd.h
# 	2:16:DefaultSinkClass:CXFloorWnd
# End Section
# Section XPropertiesWnd : {24FFD1EB-5EA9-11D2-86B1-0040055C08D9}
# 	2:5:Class:CXFloorWnd
# 	2:10:HeaderFile:xfloorwnd.h
# 	2:8:ImplFile:xfloorwnd.cpp
# End Section
# Section XPropertiesWnd : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
