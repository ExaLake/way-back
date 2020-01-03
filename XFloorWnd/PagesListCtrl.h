/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/8/98 5:46:33 PM
  Comments: PagesListCtrl.h : header file
 ************************************/

#if !defined(AFX_PAGESLISTCTRL_H__69390A42_5EC3_11D2_86B1_0040055C08D9__INCLUDED_)
#define AFX_PAGESLISTCTRL_H__69390A42_5EC3_11D2_86B1_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPagesListCtrl window
#include <afxcmn.h>

class CPagesListCtrl : public CListCtrl
{
// Construction
public:
	CPagesListCtrl();

// Attributes
public:

// Operations
public:
	int m_nNamePageCol;
	int m_nUserDataCol;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagesListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void Fill(LPCTSTR lpszPages);
	virtual void Init();
	virtual ~CPagesListCtrl();

	// Generated message map functions
protected:
	virtual void NParent();
	int m_nAutoAdd;
	//{{AFX_MSG(CPagesListCtrl)
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESLISTCTRL_H__69390A42_5EC3_11D2_86B1_0040055C08D9__INCLUDED_)
