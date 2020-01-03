// XFloorPropertiesWnd.h: interface for the CXFloorPropertiesWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XFLOORPROPERTIESWND_H__9B65A4D1_6330_11D2_86BB_0040055C08D9__INCLUDED_)
#define AFX_XFLOORPROPERTIESWND_H__9B65A4D1_6330_11D2_86BB_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "xfloorwnd.h"
#include "PageListCtrl.h"
#include <afxtempl.h>

class CXFloorPropertiesWnd : public CXFloorWnd  
{
	friend class CXPropertiesWndCtrl;
public:
	virtual const BOOL GetSignEnableDisable();
	virtual void SetSignEnableDisable(BOOL bValue = TRUE);
	virtual void SetAutoResizingColumns(BOOL bValue = TRUE);
	virtual CPageListCtrl* GetListCtrl(int nIndex);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXFloorPropertiesWnd)
	//}}AFX_VIRTUAL
	CXFloorPropertiesWnd(/*CXPropertiesWndCtrl* pControlWnd = NULL*/);
	virtual ~CXFloorPropertiesWnd();
	virtual short AddPage(LPCTSTR sName, CXPropertiesWndCtrl* pControl = NULL);
	virtual BOOL DeletePage(short nIndex);
protected:
	BOOL m_bAnimation;
	BOOL m_bAsFloor;
	BOOL m_bFirstPageHasCaption;
	virtual void RefreshPages();
	BOOL m_bSignEnableDisable;
	virtual void Load(CString& stream, CXPropertiesWndCtrl* pControl = NULL);
	virtual CPageListCtrl* NewPageListCtrl(int nIndex, CXPropertiesWndCtrl* pControl);
	CArray<CPageListCtrl*, CPageListCtrl* > m_arPagesListCtrl;
	//{{AFX_MSG(CXFloorPropertiesWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_XFLOORPROPERTIESWND_H__9B65A4D1_6330_11D2_86BB_0040055C08D9__INCLUDED_)
