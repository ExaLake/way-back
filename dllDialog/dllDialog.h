// dllDialog.h : main header file for the DLLDIALOG DLL
//

#if !defined(AFX_DLLDIALOG_H__78E73332_0964_11D4_AF9F_00A0C9CEFBED__INCLUDED_)
#define AFX_DLLDIALOG_H__78E73332_0964_11D4_AF9F_00A0C9CEFBED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDllDialogApp
// See dllDialog.cpp for the implementation of this class
//

class CDllDialogApp : public CWinApp
{
public:
	CDllDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDllDialogApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDllDialogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLDIALOG_H__78E73332_0964_11D4_AF9F_00A0C9CEFBED__INCLUDED_)
