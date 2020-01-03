// COMClient.h : main header file for the COMCLIENT application
//

#if !defined(AFX_COMCLIENT_H__C1ADB65B_A5BF_11D3_8651_00C01501BDC4__INCLUDED_)
#define AFX_COMCLIENT_H__C1ADB65B_A5BF_11D3_8651_00C01501BDC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCOMClientApp:
// See COMClient.cpp for the implementation of this class
//

class CCOMClientApp : public CWinApp
{
public:
	CCOMClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCOMClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCOMClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMCLIENT_H__C1ADB65B_A5BF_11D3_8651_00C01501BDC4__INCLUDED_)
