#if !defined(AFX_DIALOGALPHA_H__4669C344_9C78_11D1_A6C2_00A0242C0A32__INCLUDED_)
#define AFX_DIALOGALPHA_H__4669C344_9C78_11D1_A6C2_00A0242C0A32__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogAlpha.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAlpha dialog

class CDialogAlpha : public CDialog
{
// Construction
public:
	CDialogAlpha(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAlpha)
	enum { IDD = IDD_DIALOG_ALPHA };
	BYTE	m_Alpha;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAlpha)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogAlpha)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGALPHA_H__4669C344_9C78_11D1_A6C2_00A0242C0A32__INCLUDED_)
