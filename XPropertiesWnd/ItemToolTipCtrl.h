/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/21/98 12:26:41 PM
  Comments: ItemToolTipCtrl.h : header file
 ************************************/

#if !defined(AFX_ITEMTOOLTIPCTRL_H__7C49E334_68BA_11D2_86C6_0040055C08D9__INCLUDED_)
#define AFX_ITEMTOOLTIPCTRL_H__7C49E334_68BA_11D2_86C6_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CItemToolTipCtrl window

#include <afxcmn.h>

class CPageListCtrl;

class CItemToolTipCtrl : public CToolTipCtrl
{
// Construction
public:
	CItemToolTipCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemToolTipCtrl)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL Create(CPageListCtrl* pParent);
	virtual ~CItemToolTipCtrl();

	// Generated message map functions
protected:
	BOOL m_bActivate;
	virtual BOOL Activate(BOOL bActivate);
	virtual BOOL NeedToolTip(int nItem, CString& item);
	CPageListCtrl* m_pParent;
	//{{AFX_MSG(CItemToolTipCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CItemToolTipCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMTOOLTIPCTRL_H__7C49E334_68BA_11D2_86C6_0040055C08D9__INCLUDED_)
