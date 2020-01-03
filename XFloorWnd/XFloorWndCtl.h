/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/8/98 3:51:16 PM
  Comments: XFloorWndCtl.h : Declaration of the CXFloorWndCtrl ActiveX Control class.
  CXFloorWndCtrl : See XFloorWndCtl.cpp for implementation.
 ************************************/

#if !defined(AFX_XFLOORWNDCTL_H__24FFD1FB_5EA9_11D2_86B1_0040055C08D9__INCLUDED_)
#define AFX_XFLOORWNDCTL_H__24FFD1FB_5EA9_11D2_86B1_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include "FloorPageObject.h"
#include "TLabelComboBox.h"	// Added by ClassView

#define ID_LABELCOMBO	0x3E81
#define ID_LABEL		0x3E82
#define defaultRGBBkGnd RGB(128,128,128)
#define MessageChange _T("FWM_ACTIVATEPAGE")// wParam contain last active page
											// lParam contain the curently active page
#define MulSleep 2
#define IDTIMERERASEFOCUS	1000
#define UPDATEIDTIMERERASEFOCUS 48
#define IDSTARTMOVELABEL	1001
#define UPDATEIDSTARTMOVELABEL 48
#define _OBEJCTISSAFETY

#ifdef _OBEJCTISSAFETY
	#include <objsafe.h>
#endif
class CFloorLabelObject;

typedef CArray<CFloorPageObject*, CFloorPageObject*> CArrayPage;

class CXFloorWndCtrl : public COleControl
{
	DECLARE_DYNCREATE(CXFloorWndCtrl)

	friend class CFloorPageObject;
	friend class CFloorObject;
	friend class CFloorLevelObject;
// Constructor
public:

#ifdef _OBEJCTISSAFETY
	//interface IObjectSafety
	BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety)
		STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD __RPC_FAR *pdwSupportedOptions, DWORD __RPC_FAR *pdwEnabledOptions);
		STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
	END_INTERFACE_PART(ObjectSafety)
	DECLARE_INTERFACE_MAP()
	//interface IObjectSafety
#endif //_OBEJCTISSAFETY

	virtual BOOL ActivatePage(LPCTSTR lpszPageName);
	virtual BOOL ActivatePage(int nIndex);
	virtual BOOL DeletePage(LPCTSTR lpszPageName);
	virtual BOOL DeletePage(int nIndex);
	CXFloorWndCtrl();
	virtual void RecalcLayout();
	virtual BOOL PullDownPages(int nIndex);
	virtual BOOL PullUpPages(int nIndex);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXFloorWndCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnFontChanged();
	virtual void OnBackColorChanged();
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	static CRect m_rtBorder;
	int m_nDYLabel, m_nDYCombo;
	void PrepareChangeStyle();
	CTLabelComboBox m_lbPage;
	CComboBox m_cbPage;
	virtual CFloorPageObject* NewPage(BOOL bAsPage, LPCTSTR lpszPageName);
	virtual void Move(int nIndex, BOOL bDown = TRUE);
	int PtrPageToIndex(CFloorPageObject* pPage);
	CFloorPageObject* m_pActivePage;
	CArrayPage* m_pArPage;
	static CFloorPageObject* m_pFocusPage;

	~CXFloorWndCtrl();

	DECLARE_OLECREATE_EX(CXFloorWndCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CXFloorWndCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CXFloorWndCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CXFloorWndCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CXFloorWndCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	//{{AFX_DISPATCH(CXFloorWndCtrl)
	BOOL m_bAnimation;
	afx_msg void OnAnimationChanged();
	long m_nSleep;
	afx_msg void OnSleepChanged();
	BOOL m_bSign;
	afx_msg void OnSignChanged();
	CString m_sPages;
	afx_msg void OnPagesChanged();
	BOOL m_bAsPage;
	afx_msg void OnAsPageChanged();
	afx_msg short _AddPage(LPCTSTR sName);
	afx_msg BOOL _DeletePage(short nIndex);
	afx_msg BSTR _GetPageName(short nIndex);
	afx_msg short _GetPage(LPCTSTR lpszPageName);
	afx_msg BOOL _ActivatePage(short nIndex);
	afx_msg BOOL _AttachWindow(short nIndex, long pWnd);
	afx_msg BOOL _SetPageName(short nIndex, LPCTSTR lpszPageName);
	afx_msg void _Init();
	afx_msg short _GetActivePage();
	afx_msg long _GetPagesCount();
	afx_msg BOOL _IsPage(short nIndex);
	afx_msg long _GetLeftTopPage(short nIndex);
	afx_msg long _GetBottomRightPage(short nIndex);
	afx_msg void StyleAs(BOOL bAsFloor);
	afx_msg long GetHWnd(long nIndex);
	afx_msg short GetHeight(short nIndex);
	afx_msg void SetHeight(short nIndex, short nNewValue);
	afx_msg OLE_COLOR GetColor(short nIndex);
	afx_msg void SetColor(short nIndex, OLE_COLOR nNewValue);
	afx_msg long GetUserData(short nIndex);
	afx_msg void SetUserData(short nIndex, long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CXFloorWndCtrl)
	void FireActivatePage(short nIndex)
		{FireEvent(eventidActivatePage,EVENT_PARAM(VTS_I2), nIndex);}
	void FireClickOnActivePage(short nIndex)
		{FireEvent(eventidClickOnActivePage,EVENT_PARAM(VTS_I2), nIndex);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	virtual int Lookup(CFloorLabelObject* pLabelObject);
	virtual CTLabelComboBox* GetLabelControl();
	virtual CComboBox* GetComboBox();
	static UINT m_nMessageChange;
	virtual CFloorPageObject* GetPageFromPoint(CPoint point);
	virtual CRect GetRectClient();
	virtual CFloorPageObject*  GetActivePage();
	static BOOL RegClassFloorWnd();
	virtual void OnActivatePage(CFloorPageObject* pPage);
	virtual CFloorPageObject* AddPage(LPCTSTR lpszPageName, int* pIndex = NULL);
	int GetCountPage();
	virtual CFloorPageObject* GetPage(LPCTSTR lpszPageName);
	virtual CFloorPageObject* GetPage(int nIndex);
	enum {
	//{{AFX_DISP_ID(CXFloorWndCtrl)
	dispidAnimation = 1L,
	dispidSleep = 2L,
	dispidSign = 3L,
	dispidPages = 4L,
	dispidAsPage = 5L,
	dispidAddPage = 6L,
	dispidDeletePage = 7L,
	dispidGetPageName = 8L,
	dispidGetPage = 9L,
	dispidActivatePage = 10L,
	dispidAttachWindow = 11L,
	dispidSetPageName = 12L,
	dispidInit = 13L,
	dispidHeight = 21L,
	dispidColor = 22L,
	dispidUserData = 23L,
	dispidGetActivePage = 14L,
	dispidGetPagesCount = 15L,
	dispidIsPage = 16L,
	dispidGetLeftTopPage = 17L,
	dispidGetBottomRightPage = 18L,
	dispidStyleAs = 19L,
	dispidGetHWnd = 20L,
	eventidActivatePage = 1L,
	eventidClickOnActivePage = 2L,
	//}}AFX_DISP_ID
	};
private:
	void RefreshFontLabel(COleControl* pControl);
	CRect ChangeHeightLabel(CSize s);
	CRect m_rectClient;
	CBitmap* Preview(CWnd* pWnd = NULL);
	static void SetFont(CWnd *pWindow, COleControl *pControlSource);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFLOORWNDCTL_H__24FFD1FB_5EA9_11D2_86B1_0040055C08D9__INCLUDED)
