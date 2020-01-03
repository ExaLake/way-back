/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/8/98 5:46:24 PM
  Comments: XFloorWndPpg.h : Declaration of the CXFloorWndPropPage property page class.
 ************************************/

#if !defined(AFX_XFLOORWNDPPG_H__24FFD1FD_5EA9_11D2_86B1_0040055C08D9__INCLUDED_)
#define AFX_XFLOORWNDPPG_H__24FFD1FD_5EA9_11D2_86B1_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PagesListCtrl.h"
#include "XFloorWndCtl.h"

////////////////////////////////////////////////////////////////////////////
// CXFloorWndPropPage : See XFloorWndPpg.cpp.cpp for implementation.

class CXFloorWndPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CXFloorWndPropPage)
	DECLARE_OLECREATE_EX(CXFloorWndPropPage)

// Constructor
public:
	virtual void ConstructPagesAsString();
	virtual void DDP_Long(CDataExchange* pDX, long* pValue, LPCTSTR lpszPropertyName);
	virtual void DDP_String(CDataExchange* pDX, CString* pValue, LPCTSTR lpszPropertyName);
	virtual void OnObjectsChanged( );
	CXFloorWndPropPage();

// Dialog Data
	//{{AFX_DATA(CXFloorWndPropPage)
	enum { IDD = IDD_PROPPAGE_XFLOORWND };
	CStatic	m_sSleep;
	CSliderCtrl	m_sliderAnimation;
	CPagesListCtrl	m_listPages;
	int		m_bAnimation;
	BOOL	m_bSign;
	BOOL	m_bAsPage;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	CString m_sPages;
	long m_nSleep;
	//{{AFX_MSG(CXFloorWndPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckAnimation();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckSign();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateStatic(BOOL bValue, UINT idStatic);
	void UpdateMSecond();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFLOORWNDPPG_H__24FFD1FD_5EA9_11D2_86B1_0040055C08D9__INCLUDED)
