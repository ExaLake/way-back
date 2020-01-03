/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/15/98 10:13:28 AM
  Comments: XGeneralWndPropPage.h : header file
 ************************************/

#if !defined(AFX_XGENERALWNDPROPPAGE_H__73EF45B8_63FE_11D2_86BD_0040055C08D9__INCLUDED_)
#define AFX_XGENERALWNDPROPPAGE_H__73EF45B8_63FE_11D2_86BD_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXGeneralWndPropPage : Property page dialog

class CXGeneralWndPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CXGeneralWndPropPage)
	DECLARE_OLECREATE_EX(CXGeneralWndPropPage)

// Constructors
public:
	CXGeneralWndPropPage();

// Dialog Data
	//{{AFX_DATA(CXGeneralWndPropPage)
	enum { IDD = IDD_PROPPAGE_XPROPERTIESWND_GENERAL };
	int	m_bToolTip;
	int	m_bFirstPageHasCaption;
	int	m_bAsFloor;
	BOOL	m_bResizeFirstColumn;
	BOOL	m_bAnimation;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CXGeneralWndPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XGENERALWNDPROPPAGE_H__73EF45B8_63FE_11D2_86BD_0040055C08D9__INCLUDED_)
