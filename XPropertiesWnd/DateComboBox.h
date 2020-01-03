#if !defined(AFX_DATECOMBOBOX_H__67BA8C99_823D_11D2_8710_0040055C08D9__INCLUDED_)
#define AFX_DATECOMBOBOX_H__67BA8C99_823D_11D2_8710_0040055C08D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDateComboBox window
#include <afxdtctl.h>
class CControlsWnd_CDataComboBox;

class CDateComboBox : public CDateTimeCtrl
{
// Construction
public:
	CDateComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL Create(CControlsWnd_CDataComboBox* pControl);
	virtual ~CDateComboBox();

	// Generated message map functions
protected:
	CControlsWnd_CDataComboBox* m_pControl;
	//{{AFX_MSG(CDateComboBox)
	afx_msg void OnDatetimechange(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATECOMBOBOX_H__67BA8C99_823D_11D2_8710_0040055C08D9__INCLUDED_)
