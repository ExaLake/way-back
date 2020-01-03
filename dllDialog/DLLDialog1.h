#if !defined(AFX_DLLDIALOG1_H__78E73339_0964_11D4_AF9F_00A0C9CEFBED__INCLUDED_)
#define AFX_DLLDIALOG1_H__78E73339_0964_11D4_AF9F_00A0C9CEFBED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLLDialog1.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDLLDialog dialog

class CDLLDialog : public CDialog
{
// Construction
public:
	CDLLDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLLDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLLDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLLDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLDIALOG1_H__78E73339_0964_11D4_AF9F_00A0C9CEFBED__INCLUDED_)
