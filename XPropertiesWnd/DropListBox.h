/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/16/98 9:45:51 AM
  Comments: DropListBox.h : header file
 ************************************/

#if !defined(AFX_DROPLISTBOX_H__BA187F93_64C9_11D2_86BF_0040055C08D9__INCLUDED_)
#define AFX_DROPLISTBOX_H__BA187F93_64C9_11D2_86BF_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDropListBox window

class CControlsWnd;

class CDropListBox : public CListBox
{
	friend class CControlsWnd_CComboBox;
	// Construction
public:
	CDropListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void Load(LPCTSTR lpszItems = NULL, TCHAR c = TCHAR('\\'));
	int m_nSelectedItem;
	virtual void Show(CRect rect, int nLines = 2);
	virtual ~CDropListBox();
	virtual CWnd* Create(CControlsWnd_CComboBox* pNotifyClass);
	virtual void SelChange();

	// Generated message map functions
protected:
	virtual void Close(BOOL bCancel = FALSE);
	CControlsWnd_CComboBox* m_pNotifyClass;
	//{{AFX_MSG(CDropListBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bCancel;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPLISTBOX_H__BA187F93_64C9_11D2_86BF_0040055C08D9__INCLUDED_)
