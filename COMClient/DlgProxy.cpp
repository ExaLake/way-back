// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "COMClient.h"
#include "DlgProxy.h"
#include "COMClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCOMClientDlgAutoProxy

IMPLEMENT_DYNCREATE(CCOMClientDlgAutoProxy, CCmdTarget)

CCOMClientDlgAutoProxy::CCOMClientDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CCOMClientDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CCOMClientDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CCOMClientDlgAutoProxy::~CCOMClientDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CCOMClientDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CCOMClientDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CCOMClientDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCOMClientDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCOMClientDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICOMClient to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {C1ADB658-A5BF-11D3-8651-00C01501BDC4}
static const IID IID_ICOMClient =
{ 0xc1adb658, 0xa5bf, 0x11d3, { 0x86, 0x51, 0x0, 0xc0, 0x15, 0x1, 0xbd, 0xc4 } };

BEGIN_INTERFACE_MAP(CCOMClientDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CCOMClientDlgAutoProxy, IID_ICOMClient, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {C1ADB656-A5BF-11D3-8651-00C01501BDC4}
IMPLEMENT_OLECREATE2(CCOMClientDlgAutoProxy, "COMClient.Application", 0xc1adb656, 0xa5bf, 0x11d3, 0x86, 0x51, 0x0, 0xc0, 0x15, 0x1, 0xbd, 0xc4)

/////////////////////////////////////////////////////////////////////////////
// CCOMClientDlgAutoProxy message handlers
