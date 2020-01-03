/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/16/98 5:52:40 PM
  Comments: DropEdit.h : header file
 ************************************/

#if !defined(AFX_DROPEDIT_H__F0626F88_64E1_11D2_86BF_0040055C08D9__INCLUDED_)
#define AFX_DROPEDIT_H__F0626F88_64E1_11D2_86BF_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDropEdit window

class CControlsWnd;

class CDropEdit : public CEdit
{
// Construction
public:
	CDropEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void SetEditColor(COLORREF rgbEditColor);
	virtual CWnd* Create(CControlsWnd* pNotifyClass);
	virtual void Show(CRect rect);
	virtual ~CDropEdit();

	// Generated message map functions
protected:
	COLORREF m_rgbEditColor;
	CControlsWnd* m_pNotifyClass;
	//{{AFX_MSG(CDropEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_brush;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPEDIT_H__F0626F88_64E1_11D2_86BF_0040055C08D9__INCLUDED_)
