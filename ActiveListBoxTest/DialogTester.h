// DialogTester.h : main header file for the DIALOGTESTER application
//

#if !defined(AFX_DIALOGTESTER_H__DBCC2E6C_8A42_11D3_9E84_00E029175834__INCLUDED_)
#define AFX_DIALOGTESTER_H__DBCC2E6C_8A42_11D3_9E84_00E029175834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDialogTesterApp:
// See DialogTester.cpp for the implementation of this class
//

class CDialogTesterApp : public CWinApp
{
public:
	CDialogTesterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogTesterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDialogTesterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGTESTER_H__DBCC2E6C_8A42_11D3_9E84_00E029175834__INCLUDED_)
