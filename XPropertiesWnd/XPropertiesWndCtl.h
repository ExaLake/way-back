/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/13/98 2:22:54 PM
  Comments: XPropertiesWndCtl.h : Declaration of the CXPropertiesWndCtrl ActiveX Control class.
 ************************************/

#if !defined(AFX_XPROPERTIESWNDCTL_H__7B914A69_6271_11D2_86B8_0040055C08D9__INCLUDED_)
#define AFX_XPROPERTIESWNDCTL_H__7B914A69_6271_11D2_86B8_0040055C08D9__INCLUDED_

#include "XFloorPropertiesWnd.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl : See XPropertiesWndCtl.cpp for implementation.

#include <afxtempl.h>

#define IDXFLOORWND 0
#define defaultRGBBkGndProp ::GetSysColor(COLOR_APPWORKSPACE)
#define _OBEJCTISSAFETY

#ifdef _OBEJCTISSAFETY
	#include <objsafe.h>
#endif //_OBEJCTISSAFETY

class CXPropertiesWndCtrl : public COleControl
{
	friend class CPageListCtrl;
	friend class CControlsWnd;
	friend class CControlsWnd_CEdit;
	friend class CControlsWnd_CComboBox;
	friend class CControlsWnd_CADORComboBox;
	friend class CControlsWnd_CBoolComboBox;
	friend class CControlsWnd_CUserComboBox;
	friend class CControlsWnd_CButton;
	friend class CADORMultiColumnComboBox;
	DECLARE_DYNCREATE(CXPropertiesWndCtrl)
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

	CXPropertiesWndCtrl();
	virtual CPageListCtrl* GetListCtrl(int nIndexPage, int nIndexProperty);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPropertiesWndCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnFontChanged();
	//}}AFX_VIRTUAL

// Implementation
protected:
	COLORREF m_rgbEditColor;
	CFontHolder m_itemFont;
	
	// Added to notify change font
	BEGIN_INTERFACE_PART(ItemFontNotify, IPropertyNotifySink)
	INIT_INTERFACE_PART(CXPropertiesWndCtrl, ItemFontNotify)
		STDMETHOD(OnChanged)(DISPID);
		STDMETHOD(OnRequestEdit)(DISPID);
	END_INTERFACE_PART(ItemFontNotify)
	// End

	virtual CString GetPropertyName(LPCTSTR lpszPathPropertyName);
	virtual CString GetPageName(LPCTSTR lpszPathPropertyName);
	virtual void OnActivatePage(short nIndexPage);
	virtual BOOL OnInit();
	CXFloorPropertiesWnd m_xFloorWnd;
	~CXPropertiesWndCtrl();

	DECLARE_OLECREATE_EX(CXPropertiesWndCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CXPropertiesWndCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CXPropertiesWndCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CXPropertiesWndCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CXPropertiesWndCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP( )

// Dispatch maps
	//{{AFX_DISPATCH(CXPropertiesWndCtrl)
	CString m_sPagesAndItems;
	afx_msg void OnPagesAndItemsChanged();
	BOOL m_bAutoResizingColumns;
	afx_msg void OnResizingColumnsChanged();
	BOOL m_bSignEnableDisable;
	afx_msg void OnSignEnableDisableChanged();
	BOOL m_bToolTips;
	afx_msg void OnToolTipsChanged();
	BOOL m_bFirstPageHasCaption;
	afx_msg void OnFirstPageHasCaptionChanged();
	BOOL m_bAsFloor;
	afx_msg void OnAsFloorChanged();
	BOOL m_bResizeFirstColumn;
	afx_msg void OnResizeFirstColumnChanged();
	BOOL m_bAnimation;
	afx_msg void OnAnimationChanged();
	afx_msg LPFONTDISP GetItemFont();
	afx_msg void SetItemFont(LPFONTDISP newValue);
	afx_msg long _GetPagesCount();
	afx_msg short _AddPage(LPCTSTR lpszPageName);
	afx_msg BOOL _DeletePage(short nIndexPage);
	afx_msg BSTR _GetPageName(short nIndexPage);
	afx_msg short _GetPage(LPCTSTR lpszPageName);
	afx_msg void _ActivatePage(short nIndexPage);
	afx_msg short _InsertProperty(short nIndexPage, short nIndexProperty, LPCTSTR lpszPropertyName, LPCTSTR lpszPropertyAs, short lpszProperyType);
	afx_msg BOOL _DeleteProperty(short nIndexPage, short nIndexProperty);
	afx_msg BSTR _GetPropertyName(short nIndexPage, short nIndexProperty);
	afx_msg short _GetPropertyType(short nIndexPage, short nIndexProperty);
	afx_msg void _SetPropertyType(short nIndexPage, short nIndexProperty, short nNewType);
	afx_msg BSTR _GetPropertyAs(short nIndexPage, short nIndexProperty);
	afx_msg BOOL _IsProperty(short nIndexPage, short nIndexProperty);
	afx_msg long _GetIDListCtrl(short nIndexPage);
	afx_msg short _GetActivePage();
	afx_msg LPUNKNOWN _GetxFloorWnd();
	afx_msg BOOL _GetDefaultValue(short nIndexPage, short nIndexProperty, BSTR FAR* sPropertyValue);
	afx_msg BOOL _SetDefaultValue(short nIndexPage, short nIndexProperty, LPCTSTR lpszDefaultvalue);
	afx_msg short _GetPropertyCount(short nIndexPage);
	afx_msg void _SetPropertyName(short nIndexPage, short nIndexProperty, LPCTSTR lpszProperyName);
	afx_msg BOOL _GetPropertyIndex(LPCTSTR lpszPropertyName, short FAR* nIndexPage, short FAR* nIndexProperty);
	afx_msg BOOL _SetDefaultValueByName(LPCTSTR lpszPropertyName, LPCTSTR lpszPropertyValue);
	afx_msg BSTR _GetDefaultValueByName(LPCTSTR lpszPropertyName);
	afx_msg short _GetActiveProperty(short FAR* nIndexPage);
	afx_msg BOOL _SetActiveProperty(short nIndexPage, short IndexProperty);
	afx_msg BOOL _SetActivePropertyByName(LPCTSTR lpszPropertyName);
	afx_msg BOOL _DeletePropertyByName(LPCTSTR lpszPropertyName);
	afx_msg short _AddProperty(LPCTSTR lpszPropertyName, LPCTSTR lpszPropertyAs, short nPropertyType);
	afx_msg void _Init();
	afx_msg void RefreshProperty(short nIndexPage, short nIndexProperty);
	afx_msg VARIANT GetValue(short nIndexPage, short nIndexProperty, long nColumn);
	afx_msg VARIANT GetValueByName(LPCTSTR lpszPropertyName, long nColumn);
	afx_msg void SetValue(short nIndexPage, short nIndexProperty, const VARIANT FAR& vValue, short nColumn);
	afx_msg long GetColumnKey(short nIndexPage, short nIndexProperty);
	afx_msg void SetColumnKey(short nIndexPage, short nIndexProperty, long nNewValue);
	afx_msg long GetColumnWidth(short nIndexPage, short nIndexProperty, short nColumn);
	afx_msg void SetColumnWidth(short nIndexPage, short nIndexProperty, short nColumn, long nNewValue);
	afx_msg BSTR GetColumnName(short nIndexPage, short nIndexProperty, short nColumn);
	afx_msg void SetColumnName(short nIndexPage, short nIndexProperty, short nColumn, LPCTSTR lpszNewValue);
	afx_msg BOOL GetColumnHeader(short nIndexPage, short nIndexProperty);
	afx_msg void SetColumnHeader(short nIndexPage, short nIndexProperty, BOOL bNewValue);
	afx_msg double GetDropDownWidth(short nIndexPage, short nIndexProperty);
	afx_msg void SetDropDownWidth(short nIndexPage, short nIndexProperty, double newValue);
	afx_msg long GetDropDownHeight(short nIndexPage, short nIndexProperty);
	afx_msg void SetDropDownHeight(short nIndexPage, short nIndexProperty, long nNewValue);
	afx_msg BSTR GetColumnKeyByName(short nIndexPage, short nIndexProperty);
	afx_msg void SetColumnKeyByName(short nIndexPage, short nIndexProperty, LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CXPropertiesWndCtrl)
	void FireSelectItem(short nIndexPage, short nIndexItem)
		{FireEvent(eventidSelectItem,EVENT_PARAM(VTS_I2  VTS_I2), nIndexPage, nIndexItem);}
	void FireSelectPage(short nIndex)
		{FireEvent(eventidSelectPage,EVENT_PARAM(VTS_I2), nIndex);}
	void FireUnselectItem(short nIndexPage, short nIndexItem)
		{FireEvent(eventidUnselectItem,EVENT_PARAM(VTS_I2  VTS_I2), nIndexPage, nIndexItem);}
	void FirePropertyChanging(short nIndexPage, short nIndexProperty)
		{FireEvent(eventidPropertyChanging,EVENT_PARAM(VTS_I2  VTS_I2), nIndexPage, nIndexProperty);}
	void FirePropertyChanged(short nIndexPage, short nIndexProperty, BOOL bUpdate)
		{FireEvent(eventidPropertyChanged,EVENT_PARAM(VTS_I2  VTS_I2  VTS_BOOL), nIndexPage, nIndexProperty, bUpdate);}
	void FireButtonClick(short nIndexPage, short nIndexProperty)
		{FireEvent(eventidButtonClick,EVENT_PARAM(VTS_I2  VTS_I2), nIndexPage, nIndexProperty);}
	void FireLoadItems(short nIndexPage, short nIndexProperty, BSTR FAR* lpszItems)
		{FireEvent(eventidLoadItems,EVENT_PARAM(VTS_I2  VTS_I2  VTS_PBSTR), nIndexPage, nIndexProperty, lpszItems);}
	void FireSetObject(long nIndexPage, long nIndexProperty, LPDISPATCH FAR* pObject)
		{FireEvent(eventidSetObject,EVENT_PARAM(VTS_I4  VTS_I4  VTS_PDISPATCH), nIndexPage, nIndexProperty, pObject);}
	void FireDelete(short nIndexPage, short nIndexProperty)
		{FireEvent(eventidDelete,EVENT_PARAM(VTS_I2  VTS_I2), nIndexPage, nIndexProperty);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	virtual void OnBackColorChanged( );
	enum {
	//{{AFX_DISP_ID(CXPropertiesWndCtrl)
	dispidPagesAndItems = 1L,
	dispidAutoResizingColumns = 2L,
	dispidSignEnableDisable = 3L,
	dispidToolTips = 4L,
	dispidFirstPageHasCaption = 5L,
	dispidItemFont = 9L,
	dispidAsFloor = 6L,
	dispidResizeFirstColumn = 7L,
	dispidAnimation = 8L,
	dispidGetPagesCount = 10L,
	dispidAddPage = 11L,
	dispidDeletePage = 12L,
	dispidGetPageName = 13L,
	dispidGetPage = 14L,
	dispidActivatePage = 15L,
	dispidInsertProperty = 16L,
	dispidDeleteProperty = 17L,
	dispidGetPropertyName = 18L,
	dispidGetPropertyType = 19L,
	dispidSetPropertyType = 20L,
	dispidGetPropertyAs = 21L,
	dispidIsProperty = 22L,
	dispidGetIDListCtrl = 23L,
	dispidGetActivePage = 24L,
	dispidGetxFloorWnd = 25L,
	dispidGetDefaultValue = 26L,
	dispidSetDefaultValue = 27L,
	dispidGetPropertyCount = 28L,
	dispidSetPropertyName = 29L,
	dispidGetPropertyIndex = 30L,
	dispidSetDefaultValueByName = 31L,
	dispidGetDefaultValueByName = 32L,
	dispidGetActiveProperty = 33L,
	dispidSetActiveProperty = 34L,
	dispidSetActivePropertyByName = 35L,
	dispidDeletePropertyByName = 36L,
	dispidAddProperty = 37L,
	dispidInit = 38L,
	dispidColumnKey = 43L,
	dispidColumnWidth = 44L,
	dispidColumnName = 45L,
	dispidColumnHeader = 46L,
	dispidDropDownWidth = 47L,
	dispidDropDownHeight = 48L,
	dispidRefreshProperty = 39L,
	dispidGetValue = 40L,
	dispidGetValueByName = 41L,
	dispidColumnKeyByName = 49L,
	dispidSetValue = 42L,
	eventidSelectItem = 1L,
	eventidSelectPage = 2L,
	eventidUnselectItem = 3L,
	eventidPropertyChanging = 4L,
	eventidPropertyChanged = 5L,
	eventidButtonClick = 6L,
	eventidLoadItems = 7L,
	eventidSetObject = 8L,
	eventidDelete = 9L,
	//}}AFX_DISP_ID
	};
private:
	void ResetMAPFound();
	BOOL AlreadyFound(LPCTSTR lpszPropertyName, short* lLow, short* lHigh);
	void AppendSearch(LPCTSTR lpszPropertyName, short lLow, short lHigh);
	CMapStringToOb m_mapSearch;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPROPERTIESWNDCTL_H__7B914A69_6271_11D2_86B8_0040055C08D9__INCLUDED)
