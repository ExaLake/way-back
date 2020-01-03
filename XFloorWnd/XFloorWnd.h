/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/8/98 5:25:18 PM
  Comments: XFloorWnd.h : main header file for XFLOORWND.DLL
 ************************************/
#if !defined(AFX_XFLOORWND_H__24FFD1F3_5EA9_11D2_86B1_0040055C08D9__INCLUDED_)
#define AFX_XFLOORWND_H__24FFD1F3_5EA9_11D2_86B1_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXFloorWndApp : See XFloorWnd.cpp for implementation.

class CXFloorWndApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;
extern const TCHAR _cPagesSeparator;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFLOORWND_H__24FFD1F3_5EA9_11D2_86B1_0040055C08D9__INCLUDED)
