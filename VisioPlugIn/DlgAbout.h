// DlgAbout.h : header file
//

#if !defined(AFX_DLGABOUT_H__C8553189_17FC_11D3_B3C5_00105A98B108__INCLUDED_)
#define AFX_DLGABOUT_H__C8553189_17FC_11D3_B3C5_00105A98B108__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"

#define CDlgAbout_PARENT CDialog

class CDlgAbout : public CDlgAbout_PARENT
{
// Construction
public:
	CDlgAbout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAbout)
	enum { IDD = IDD_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAbout)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGABOUT_H__C8553189_17FC_11D3_B3C5_00105A98B108__INCLUDED_)
