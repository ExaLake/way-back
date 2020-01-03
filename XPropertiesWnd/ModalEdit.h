/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 11/11/98 5:07:57 AM
  Comments: ModalEdit.h : header file
 ************************************/

#if !defined(AFX_MODALEDIT_H__86A574F3_62AE_11D2_86B9_0040055C08D9__INCLUDED_)
#define AFX_MODALEDIT_H__86A574F3_62AE_11D2_86B9_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CModalEdit window

class CModalEdit : public CEdit
{
// Construction
public:
	CModalEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModalEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void Do(CRect rect, LPCTSTR lpszText = NULL);
	virtual ~CModalEdit();

	// Generated message map functions
protected:
	virtual void End();
	//{{AFX_MSG(CModalEdit)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bFirstDo;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODALEDIT_H__86A574F3_62AE_11D2_86B9_0040055C08D9__INCLUDED_)
