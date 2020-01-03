/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 12:17:34 PM
  Comments: XDesignPopupMenu.h: interface for the CXDesignPopupMenu class.
 ************************************/

#if !defined(AFX_XDESIGNPOPUPMENU_H__567504B8_6335_11D2_86BB_0040055C08D9__INCLUDED_)
#define AFX_XDESIGNPOPUPMENU_H__567504B8_6335_11D2_86BB_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxwin.h>

class CXDesignPopupMenu : public CMenu  
{
public:
	virtual BOOL Show();
	virtual CMenu* GetPopupMenu();
	CXDesignPopupMenu(UINT nIDMenu, LPCTSTR lpszPopupName, CPoint p, CWnd* pParentWnd );
	virtual ~CXDesignPopupMenu();

protected:
	CWnd* m_pParentWnd;
	CPoint m_point;
	CMenu* m_pPopupMenu;
};

#endif // !defined(AFX_XDESIGNPOPUPMENU_H__567504B8_6335_11D2_86BB_0040055C08D9__INCLUDED_)
