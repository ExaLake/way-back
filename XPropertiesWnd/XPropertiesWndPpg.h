/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/13/98 2:28:22 PM
  Comments: XPropertiesWndPpg.h : Declaration of the CXPropertiesWndPropPage property page class.
 ************************************/

//{{AFX_INCLUDES()
#include "XFloorPropertiesWndDesign.h"
#include "HighLightButton.h"
#include "ModalEdit.h"
//}}AFX_INCLUDES
#include <afxcmn.h>

#if !defined(AFX_XPROPERTIESWNDPPG_H__7B914A6B_6271_11D2_86B8_0040055C08D9__INCLUDED_)
#define AFX_XPROPERTIESWNDPPG_H__7B914A6B_6271_11D2_86B8_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndPropPage : See XPropertiesWndPpg.cpp.cpp for implementation.

class CXPropertiesWndPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CXPropertiesWndPropPage)
	DECLARE_OLECREATE_EX(CXPropertiesWndPropPage)

	friend class CXFloorPropertiesWndDesign;
// Constructor
public:
	virtual void Refresh();
	static LRESULT CALLBACK CallWndProcHookParent( int nCode, WPARAM wParam, LPARAM lParam);
	static CXPropertiesWndPropPage* m_pThis;
	HHOOK m_hHook;
	CXPropertiesWndPropPage();

	virtual BOOL PreTranslateMessage( MSG* pMsg );

// Dialog Data
	//{{AFX_DATA(CXPropertiesWndPropPage)
	enum { IDD = IDD_PROPPAGE_XPROPERTIESWND_PREVIEW };
	CModalEdit	m_edtRename;
	CSliderCtrl	m_sldAddDel;
	CXFloorPropertiesWndDesign	m_xFloorWndPages;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	virtual void RenamePage(int nIndex);
	virtual void DeletePage();
	virtual void AddPage();
	//{{AFX_MSG(CXPropertiesWndPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickOnActivePageXfloorwndctrlPages(short nIndex);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nRenamePage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPROPERTIESWNDPPG_H__7B914A6B_6271_11D2_86B8_0040055C08D9__INCLUDED)
