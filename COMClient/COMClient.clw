; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCOMClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "COMClient.h"
ODLFile=COMClient.odl

ClassCount=4
Class1=CCOMClientApp
Class2=CCOMClientDlg
Class3=CAboutDlg
Class4=CCOMClientDlgAutoProxy

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_COMCLIENT_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_COMCLIENT_DIALOG (English (U.S.))

[CLS:CCOMClientApp]
Type=0
HeaderFile=COMClient.h
ImplementationFile=COMClient.cpp
Filter=N

[CLS:CCOMClientDlg]
Type=0
HeaderFile=COMClientDlg.h
ImplementationFile=COMClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=COMClientDlg.h
ImplementationFile=COMClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[CLS:CCOMClientDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_COMCLIENT_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CCOMClientDlg

[DLG:IDD_COMCLIENT_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_HELP,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BUTTON1,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

