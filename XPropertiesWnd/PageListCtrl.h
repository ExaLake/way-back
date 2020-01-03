/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 10:23:29 AM
  Comments: PageListCtrl.h : header file
 ************************************/

#if !defined(AFX_PAGELISTCTRL_H__567504B4_6335_11D2_86BB_0040055C08D9__INCLUDED_)
#define AFX_PAGELISTCTRL_H__567504B4_6335_11D2_86BB_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//

/////////////////////////////////////////////////////////////////////////////
// CPageListCtrl window

#include <afxcmn.h>
#include "AsControls.h"	// Added by ClassView
#include "ControlsWnd.h"	// Added by ClassView
#include "ItemToolTipCtrl.h"

class CXPropertiesWndCtrl;

class CPageListCtrl : public CListCtrl
{
	friend class CXPropertiesWndCtrl;
	friend class CXFloorPropertiesWnd;
	friend class CControlsWnd;
	friend class CControlsWnd_CEdit;
	friend class CControlsWnd_CFont;
	friend class CControlsWnd_CComboBox;
	friend class CControlsWnd_CUserComboBox;
	friend class CControlsWnd_CColorComboBox;
	DECLARE_DYNCREATE(CPageListCtrl)
// Construction
public:
	CPageListCtrl(CXPropertiesWndCtrl* pControl = NULL, int nHeight = 18);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageListCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetIndexPage(long nIndexPage);
	const long GetIndexPage();
	static COLORREF m_rgbDisableItem;
	static COLORREF m_rgbEnableItem;
	static CAsControls m_asControls;
	BOOL CreateItemFont(const LOGFONT* pLogFont);
	void SetPropertyName(int nIndexProperty, LPCTSTR lpszPropertyName);
	CString GetPropertyName(int nIndexProperty);
	virtual BOOL IsEditItem(int nItem);
	virtual BOOL IsButtonItem(int nItem);
	virtual LPCTSTR GetItemAsControl(int nIndex);
	virtual BOOL IsGrayedItem(int nItem);
	virtual BOOL IsEnableItem(int nIndex);
	virtual BOOL IsBlackItem(int nIndex);
	virtual void Save(CString& stream);
	virtual void Load(CString& stream);
	virtual void OnNew(CWnd* pParentWnd, UINT nID = 0);
	virtual ~CPageListCtrl();
	const CString GetDefaultValue(int nIndexProperty);
	virtual CRect GetLastRect(int nItem);

	// Generated message map functions
protected:
	void InvalidateNew();
	virtual BOOL IsSizingLine();
	virtual BOOL IsEditMode();
	CItemToolTipCtrl m_toolTip;
	virtual void ResetEditControl();
	virtual BOOL CreateEditControl(int nItem);
	CWnd* GetWindowEditing();
	CControlsWnd* m_pEditControl;
	virtual void NextItem(int nItem);
	virtual BOOL OpenEditing(int nItem, LPARAM lParam = 0);
	virtual void CloseEditing();
	CRect m_btnRect;
	virtual CXFloorPropertiesWnd* GetFloorWnd();
	virtual CXPropertiesWndCtrl* GetControlWnd();
	int m_nHeight;
	virtual const UINT GetDefaultStyle();
	virtual const UINT GetDefaultExStyle();
	static BOOL m_bAutoResizingColumns;
	virtual void OnLoad(int nItem, LPCTSTR lpszAs, LPCTSTR lpszType);
	virtual BOOL OnInit();
	//{{AFX_MSG(CPageListCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL IsMouseCaptured();
	CPoint m_ptnCapture;
	void ResizeColumns();
	CXPropertiesWndCtrl* m_pControl;
	CControlsWnd* GetControl(int nIndex, BOOL bDelete = TRUE);
	long m_nIndexPage;
	BOOL UserPaint(int nItem, CDC* pDC, CRect rect);
	CFont m_itemFont;
	int m_nOpenedProperty;
	void SetActiveProperty(int nIndexProperty);
	int GetActiveProperty();
	BOOL SetDefaultValue(int nIndexProperty, LPCTSTR lpszdefaultValue);
	BOOL CheckEditMode(int nItem, CPoint point, int nSelected);
	void DrawButton(CDC* pDC, CRect rB, int nItem, BOOL bClick);
	int m_nSelected;
	HICON m_hIconDown;
	HICON m_hIconUp;
	HICON m_hIconDots;
	HICON m_hIconClick;
	HICON m_hIconReturn;
	HICON m_hIconLink;
	HICON m_hIconFont;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGELISTCTRL_H__567504B4_6335_11D2_86BB_0040055C08D9__INCLUDED_)
