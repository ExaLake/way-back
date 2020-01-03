// NetInfo.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "NetInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CNetInfoApp, CWinApp)
	//{{AFX_MSG_MAP(CNetInfoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CNetInfoApp::CNetInfoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNetInfoApp object
CNetInfoApp theApp;
