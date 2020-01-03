/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 12:04:03 PM
  Comments: PageListCtrlDesign.h: interface for the CPageListCtrlDesign class.
 ************************************/

#if !defined(AFX_PAGELISTCTRLDESIGN_H__567504B7_6335_11D2_86BB_0040055C08D9__INCLUDED_)
#define AFX_PAGELISTCTRLDESIGN_H__567504B7_6335_11D2_86BB_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PageListCtrl.h"
#include "XDesignPopupMenu.h"
#include "AsControls.h"	// Added by ClassView
#include "XPropertiesWndPpg.h"

#define defaultLabelNewItem _T("noname")
#define defaultCharSeparator _T("\n")

class CPageListCtrlDesign : public CPageListCtrl  
{
	DECLARE_DYNCREATE(CPageListCtrlDesign)
	friend class CXFloorPropertiesWndDesign;
public:
	CPageListCtrlDesign();
	virtual ~CPageListCtrlDesign();
// Operations
public:
	virtual void Load(CString& stream);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageListCtrlDesign)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL


protected:
	virtual BOOL OnInit();
	virtual CXPropertiesWndCtrl* GetControlWnd();
	// Generated message map functions
protected:
	virtual BOOL IsSizingLine();
	virtual CXPropertiesWndPropPage* GetPropertiesWndPropPage();
	virtual const UINT GetDefaultStyle();
	virtual const UINT GetDefaultExStyle();
	virtual void OnLoad(int nItem, LPCTSTR lpszAs, LPCTSTR lpszType);
	virtual void Save(CString& stream);
	virtual CPageListCtrl* GetListCtrl();
	void ChangeAs(UINT nIDAs);
	void ChangeType(UINT nIDAs);
	static CAsControls m_asControls;
	UINT m_nDefaultAs;
	UINT m_nDefaultType;
	void RemoveContextMenu();
	CXDesignPopupMenu* m_pContextMenu;
	//{{AFX_MSG(CPageListCtrlDesign)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuInsert();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuEdit();
	afx_msg void OnUpdateMenuasEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasCombobox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasBoolcombobox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasUsercombobox(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateMenutypeDisable(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenutypeEnable(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenutypeDisableblack(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdateMenuasColorcombobox(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateMenuasShellfolder(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasAdorcombobox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasDatacombobox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasReturn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasLink(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuasFont(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void RefreshIDs();
};

#endif // !defined(AFX_PAGELISTCTRLDESIGN_H__567504B7_6335_11D2_86BB_0040055C08D9__INCLUDED_)
