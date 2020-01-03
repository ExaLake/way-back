// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__C1ADB65F_A5BF_11D3_8651_00C01501BDC4__INCLUDED_)
#define AFX_DLGPROXY_H__C1ADB65F_A5BF_11D3_8651_00C01501BDC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCOMClientDlg;

/////////////////////////////////////////////////////////////////////////////
// CCOMClientDlgAutoProxy command target

class CCOMClientDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CCOMClientDlgAutoProxy)

	CCOMClientDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CCOMClientDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCOMClientDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCOMClientDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CCOMClientDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CCOMClientDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CCOMClientDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__C1ADB65F_A5BF_11D3_8651_00C01501BDC4__INCLUDED_)
