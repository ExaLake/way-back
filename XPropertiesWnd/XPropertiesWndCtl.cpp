/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/13/98 2:09:52 PM
  Comments: XPropertiesWndCtl.cpp : Implementation of the CXPropertiesWndCtrl ActiveX Control class.
 ************************************/

#include "stdafx.h"
#include "XPropertiesWnd.h"
#include "XPropertiesWndCtl.h"
#include "XPropertiesWndPpg.h"
#include "XGeneralWndPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CXPropertiesWndCtrl, COleControl)

#ifdef _OBEJCTISSAFETY
//Implementation IObjectSafety
BEGIN_INTERFACE_MAP(CXPropertiesWndCtrl, COleControl)
  INTERFACE_PART(CXPropertiesWndCtrl, IID_IObjectSafety, ObjectSafety)
END_INTERFACE_MAP()
//Implementation IObjectSafety

// Implementation of IObjectSafety
STDMETHODIMP CXPropertiesWndCtrl::XObjectSafety::GetInterfaceSafetyOptions(
			REFIID riid, 
			DWORD __RPC_FAR *pdwSupportedOptions, 
			DWORD __RPC_FAR *pdwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CXPropertiesWndCtrl, ObjectSafety)

	if (!pdwSupportedOptions || !pdwEnabledOptions)
	{
		return E_POINTER;
	}

	*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
	*pdwEnabledOptions = 0;

	if (NULL == pThis->GetInterface(&riid))
	{
		TRACE(_T("Requested interface is not supported.\n"));
		return E_NOINTERFACE;
	}

	// What interface is being checked out anyhow?
	OLECHAR szGUID[39];
	int i = StringFromGUID2(riid, szGUID, 39);

	if (riid == IID_IDispatch)
	{
		// Client wants to know if object is safe for scripting
		*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		return S_OK;
	}
	else if (riid == IID_IPersistPropertyBag 
		  || riid == IID_IPersistStreamInit
		  || riid == IID_IPersistStorage
		  || riid == IID_IPersistMemory)
	{
		// Those are the persistence interfaces COleControl derived controls support
		// as indicated in AFXCTL.H
		// Client wants to know if object is safe for initializing from persistent data
		*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
		return S_OK;
	}
	else
	{
		// Find out what interface this is, and decide what options to enable
		TRACE(_T("We didn't account for the safety of this interface, and it's one we support...\n"));
		return E_NOINTERFACE;
	}	
}

STDMETHODIMP CXPropertiesWndCtrl::XObjectSafety::SetInterfaceSafetyOptions(
		REFIID riid, 
		DWORD dwOptionSetMask, 
		DWORD dwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CXPropertiesWndCtrl, ObjectSafety)

	OLECHAR szGUID[39];
	// What is this interface anyway?
	// We can do a quick lookup in the registry under HKEY_CLASSES_ROOT\Interface
	int i = StringFromGUID2(riid, szGUID, 39);

	if (0 == dwOptionSetMask && 0 == dwEnabledOptions)
	{
		// the control certainly supports NO requests through the specified interface
		// so it's safe to return S_OK even if the interface isn't supported.
		return S_OK;
	}

	// Do we support the specified interface?
	if (NULL == pThis->GetInterface(&riid))
	{
		TRACE1("%s is not support.\n", szGUID);
		return E_FAIL;
	}


	if (riid == IID_IDispatch)
	{
		TRACE(_T("Client asking if it's safe to call through IDispatch.\n"));
		TRACE(_T("In other words, is the control safe for scripting?\n"));
		if (INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwEnabledOptions)
		{
			return S_OK;
		}
		else
		{
			return E_FAIL;
		}
	}
	else if (riid == IID_IPersistPropertyBag 
		  || riid == IID_IPersistStreamInit
		  || riid == IID_IPersistStorage
		  || riid == IID_IPersistMemory)
	{
		TRACE(_T("Client asking if it's safe to call through IPersist*.\n"));
		TRACE(_T("In other words, is the control safe for initializing from persistent data?\n"));

		if (INTERFACESAFE_FOR_UNTRUSTED_DATA == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_DATA == dwEnabledOptions)
		{
			return NOERROR;
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		TRACE1("We didn't account for the safety of %s, and it's one we support...\n", szGUID);
		return E_FAIL;
	}
}

STDMETHODIMP_(ULONG) CXPropertiesWndCtrl::XObjectSafety::AddRef()
{
	METHOD_PROLOGUE_EX_(CXPropertiesWndCtrl, ObjectSafety)
	return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CXPropertiesWndCtrl::XObjectSafety::Release()
{
	METHOD_PROLOGUE_EX_(CXPropertiesWndCtrl, ObjectSafety)
	return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CXPropertiesWndCtrl::XObjectSafety::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CXPropertiesWndCtrl, ObjectSafety)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}
#endif //_OBEJCTISSAFETY



static const FONTDESC _fontdescItem =
  { sizeof(FONTDESC), OLESTR("MS Sans Serif"), FONTSIZE( 8 ), FW_NORMAL, 
     ANSI_CHARSET, FALSE, FALSE, FALSE };

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CXPropertiesWndCtrl, COleControl)
	//{{AFX_MSG_MAP(CXPropertiesWndCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CXPropertiesWndCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CXPropertiesWndCtrl)
	DISP_PROPERTY_NOTIFY(CXPropertiesWndCtrl, "PagesAndItems", m_sPagesAndItems, OnPagesAndItemsChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CXPropertiesWndCtrl, "AutoResizingColumns", m_bAutoResizingColumns, OnResizingColumnsChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CXPropertiesWndCtrl, "SignEnableDisable", m_bSignEnableDisable, OnSignEnableDisableChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CXPropertiesWndCtrl, "ToolTips", m_bToolTips, OnToolTipsChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CXPropertiesWndCtrl, "FirstPageHasCaption", m_bFirstPageHasCaption, OnFirstPageHasCaptionChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CXPropertiesWndCtrl, "AsFloor", m_bAsFloor, OnAsFloorChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CXPropertiesWndCtrl, "ResizeFirstColumn", m_bResizeFirstColumn, OnResizeFirstColumnChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CXPropertiesWndCtrl, "Animation", m_bAnimation, OnAnimationChanged, VT_BOOL)
	DISP_PROPERTY_EX(CXPropertiesWndCtrl, "ItemFont", GetItemFont, SetItemFont, VT_FONT)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetPagesCount", _GetPagesCount, VT_I4, VTS_NONE)
	DISP_FUNCTION(CXPropertiesWndCtrl, "AddPage", _AddPage, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "DeletePage", _DeletePage, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetPageName", _GetPageName, VT_BSTR, VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetPage", _GetPage, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "ActivatePage", _ActivatePage, VT_EMPTY, VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "InsertProperty", _InsertProperty, VT_I2, VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "DeleteProperty", _DeleteProperty, VT_BOOL, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetPropertyName", _GetPropertyName, VT_BSTR, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetPropertyType", _GetPropertyType, VT_I2, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "SetPropertyType", _SetPropertyType, VT_EMPTY, VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetPropertyAs", _GetPropertyAs, VT_BSTR, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "IsProperty", _IsProperty, VT_BOOL, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetIDListCtrl", _GetIDListCtrl, VT_I4, VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetActivePage", _GetActivePage, VT_I2, VTS_NONE)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetxFloorWnd", _GetxFloorWnd, VT_UNKNOWN, VTS_NONE)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetDefaultValue", _GetDefaultValue, VT_BOOL, VTS_I2 VTS_I2 VTS_PBSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "SetDefaultValue", _SetDefaultValue, VT_BOOL, VTS_I2 VTS_I2 VTS_BSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetPropertyCount", _GetPropertyCount, VT_I2, VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "SetPropertyName", _SetPropertyName, VT_EMPTY, VTS_I2 VTS_I2 VTS_BSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetPropertyIndex", _GetPropertyIndex, VT_BOOL, VTS_BSTR VTS_PI2 VTS_PI2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "SetDefaultValueByName", _SetDefaultValueByName, VT_BOOL, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetDefaultValueByName", _GetDefaultValueByName, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetActiveProperty", _GetActiveProperty, VT_I2, VTS_PI2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "SetActiveProperty", _SetActiveProperty, VT_BOOL, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "SetActivePropertyByName", _SetActivePropertyByName, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "DeletePropertyByName", _DeletePropertyByName, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CXPropertiesWndCtrl, "AddProperty", _AddProperty, VT_I2, VTS_BSTR VTS_BSTR VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "Init", _Init, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CXPropertiesWndCtrl, "RefreshProperty", RefreshProperty, VT_EMPTY, VTS_I2 VTS_I2)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetValue", GetValue, VT_VARIANT, VTS_I2 VTS_I2 VTS_I4)
	DISP_FUNCTION(CXPropertiesWndCtrl, "GetValueByName", GetValueByName, VT_VARIANT, VTS_BSTR VTS_I4)
	DISP_FUNCTION(CXPropertiesWndCtrl, "SetValue", SetValue, VT_EMPTY, VTS_I2 VTS_I2 VTS_VARIANT VTS_I2)
	DISP_PROPERTY_PARAM(CXPropertiesWndCtrl, "ColumnKey", GetColumnKey, SetColumnKey, VT_I4, VTS_I2 VTS_I2)
	DISP_PROPERTY_PARAM(CXPropertiesWndCtrl, "ColumnWidth", GetColumnWidth, SetColumnWidth, VT_I4, VTS_I2 VTS_I2 VTS_I2)
	DISP_PROPERTY_PARAM(CXPropertiesWndCtrl, "ColumnName", GetColumnName, SetColumnName, VT_BSTR, VTS_I2 VTS_I2 VTS_I2)
	DISP_PROPERTY_PARAM(CXPropertiesWndCtrl, "ColumnHeader", GetColumnHeader, SetColumnHeader, VT_BOOL, VTS_I2 VTS_I2)
	DISP_PROPERTY_PARAM(CXPropertiesWndCtrl, "DropDownWidth", GetDropDownWidth, SetDropDownWidth, VT_R8, VTS_I2 VTS_I2)
	DISP_PROPERTY_PARAM(CXPropertiesWndCtrl, "DropDownHeight", GetDropDownHeight, SetDropDownHeight, VT_I4, VTS_I2 VTS_I2)
	DISP_PROPERTY_PARAM(CXPropertiesWndCtrl, "ColumnKeyByName", GetColumnKeyByName, SetColumnKeyByName, VT_BSTR, VTS_I2 VTS_I2)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FONT()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CXPropertiesWndCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CXPropertiesWndCtrl, COleControl)
	//{{AFX_EVENT_MAP(CXPropertiesWndCtrl)
	EVENT_CUSTOM("SelectItem", FireSelectItem, VTS_I2  VTS_I2)
	EVENT_CUSTOM("SelectPage", FireSelectPage, VTS_I2)
	EVENT_CUSTOM("UnselectItem", FireUnselectItem, VTS_I2  VTS_I2)
	EVENT_CUSTOM("PropertyChanging", FirePropertyChanging, VTS_I2  VTS_I2)
	EVENT_CUSTOM("PropertyChanged", FirePropertyChanged, VTS_I2  VTS_I2 VTS_BOOL)
	EVENT_CUSTOM("ButtonClick", FireButtonClick, VTS_I2  VTS_I2 )
	EVENT_CUSTOM("LoadItems", FireLoadItems, VTS_I2  VTS_I2  VTS_PBSTR)
	EVENT_CUSTOM("SetObject", FireSetObject, VTS_I4  VTS_I4  VTS_PDISPATCH)
	EVENT_CUSTOM("Delete", FireDelete, VTS_I2  VTS_I2)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()

BEGIN_EVENTSINK_MAP( CXPropertiesWndCtrl, COleControl )
	ON_EVENT( CXPropertiesWndCtrl, IDXFLOORWND, 1 /*ActivatePage*/, OnActivatePage, VTS_I2)
END_EVENTSINK_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CXPropertiesWndCtrl, 4)
	PROPPAGEID(CXPropertiesWndPropPage::guid)
	PROPPAGEID(CXGeneralWndPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
	PROPPAGEID(CLSID_CFontPropPage )
END_PROPPAGEIDS(CXPropertiesWndCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CXPropertiesWndCtrl, "XPROPERTIESWND.XPropertiesWndCtrl.1",
	0x7b914a5b, 0x6271, 0x11d2, 0x86, 0xb8, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CXPropertiesWndCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DXPropertiesWnd =
		{ 0x7b914a59, 0x6271, 0x11d2, { 0x86, 0xb8, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9 } };
const IID BASED_CODE IID_DXPropertiesWndEvents =
		{ 0x7b914a5a, 0x6271, 0x11d2, { 0x86, 0xb8, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwXPropertiesWndOleMisc =
	OLEMISC_SIMPLEFRAME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CXPropertiesWndCtrl, IDS_XPROPERTIESWND, _dwXPropertiesWndOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl::CXPropertiesWndCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CXPropertiesWndCtrl


// Function name	: CXPropertiesWndCtrl::CXPropertiesWndCtrlFactory::UpdateRegistry
// Description	    : Call to register this
// Return type		: BOOL 
// Argument         : BOOL bRegister
BOOL CXPropertiesWndCtrl::CXPropertiesWndCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegInsertable | afxRegApartmentThreading to afxRegInsertable.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_XPROPERTIESWND,
			IDB_XPROPERTIESWND,
			afxRegInsertable | afxRegApartmentThreading,
			_dwXPropertiesWndOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl::CXPropertiesWndCtrl - Constructor

// Function name	: CXPropertiesWndCtrl::CXPropertiesWndCtrl
// Description	    : Default constuctor, initialize all interfaces
// Return type		: 
CXPropertiesWndCtrl::CXPropertiesWndCtrl():m_itemFont(&m_xItemFontNotify)
{
	InitializeIIDs(&IID_DXPropertiesWnd, &IID_DXPropertiesWndEvents);

	m_rgbEditColor = RGB(0,0,255);

	EnableSimpleFrame();

}


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl::~CXPropertiesWndCtrl - Destructor

CXPropertiesWndCtrl::~CXPropertiesWndCtrl()
{
}


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl::OnDraw - Drawing function

void CXPropertiesWndCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// Erase the background
	pdc->FillSolidRect(rcBounds, TranslateColor(GetBackColor()));
	// Fill the version of ActiveX control
	CString version;
	 version.Format(_T("xPropertiesWnd %i.%i"),_wVerMajor, _wVerMinor);
	pdc->SetBkMode(TRANSPARENT);
	pdc->DrawText(version, CRect(rcBounds), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
}

/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl::DoPropExchange - Persistence support

// Function name	: CXPropertiesWndCtrl::DoPropExchange
// Description	    : Implemente persistance...
// Return type		: void 
// Argument         : CPropExchange* pPX
void CXPropertiesWndCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	PX_Bool(pPX, _T("AsFloor"), m_bAsFloor, TRUE);
	PX_String(pPX, _T("PagesAndItems"), m_sPagesAndItems , _T(""));
	PX_Bool(pPX, _T("AutoResizingColumns"), m_bAutoResizingColumns , TRUE);
	PX_Bool(pPX, _T("SignEnableDisable"), m_bSignEnableDisable , TRUE);
	PX_Bool(pPX, _T("ToolTips"), m_bToolTips , TRUE);
	PX_Bool(pPX, _T("FirstPageHasCaption"), m_bFirstPageHasCaption, FALSE);
	PX_Bool(pPX, _T("ResizeFirstColumn"), m_bResizeFirstColumn, TRUE);
	PX_Bool(pPX, _T("Animation"), m_bAnimation , FALSE);
	PX_Font(pPX, _T("ItemFont"), m_itemFont, &_fontdescItem);

	if ( pPX->IsLoading() )
	{
		OnAsFloorChanged();
		OnPagesAndItemsChanged();
		OnResizingColumnsChanged();
		OnSignEnableDisableChanged();
		OnToolTipsChanged();
		OnFirstPageHasCaptionChanged();
		OnResizeFirstColumnChanged();
		OnAnimationChanged();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl::OnResetState - Reset control to default state

void CXPropertiesWndCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	
	SetBackColor((OLE_COLOR)defaultRGBBkGndProp);
	m_sPagesAndItems.Empty();
	m_bAutoResizingColumns = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl::AboutBox - Display an "About" box to the user

void CXPropertiesWndCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_XPROPERTIESWND);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndCtrl message handlers

// Function name	: CXPropertiesWndCtrl::OnCreate
// Description	    : Call OnInit after this control was created.
// Return type		: int 
// Argument         : LPCREATESTRUCT lpCreateStruct
int CXPropertiesWndCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style |= WS_CLIPCHILDREN;
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!OnInit())
	{
		#ifdef _DEBUG
			TRACE0("Warning: Cannot create ActiveX xPropertiesWnd control.\n");
		#endif
		return -1;
	}
	return 0;
}

// Function name	: CXPropertiesWndCtrl::OnSize
// Description	    : resize the xFlooWnd control when something is happening with parent
// Return type		: void 
// Argument         : UINT nType
// Argument         : int cx
// Argument         : int cy
void CXPropertiesWndCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	if (::IsWindow(m_xFloorWnd.m_hWnd))
		m_xFloorWnd.MoveWindow(0,0,cx,cy);
	
}

// Function name	: CXPropertiesWndCtrl::OnInit
// Description	    : Init the control
// Return type		: BOOL 
BOOL CXPropertiesWndCtrl::OnInit()
{
	BOOL bResult = m_xFloorWnd.Create(_T(""), WS_CHILD | WS_VISIBLE , CRect(0,0,0,0), this, IDXFLOORWND);
	OnBackColorChanged();
	OnPagesAndItemsChanged();
	OnAnimationChanged();
	return bResult;
}

// Function name	: CXPropertiesWndCtrl::OnAnimationChanged
// Description	    : 
// Return type		: void 
void CXPropertiesWndCtrl::OnAnimationChanged() 
{
	if (m_xFloorWnd.GetControlUnknown())
		m_xFloorWnd.SetProperty(1, VT_BOOL, m_bAnimation);

	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::OnBackColorChanged
// Description	    : Change the color background, will change the xFloorWnd Color
// Return type		: void 
void CXPropertiesWndCtrl::OnBackColorChanged()
{
	if (m_xFloorWnd.GetControlUnknown())
		m_xFloorWnd.SetBackColor(GetBackColor());
	InvalidateControl();
}

// Function name	: CXPropertiesWndCtrl::OnPagesAndItemsChanged
// Description	    : 
// Return type		: void 
void CXPropertiesWndCtrl::OnPagesAndItemsChanged() 
{
	// Make some tricks to eliminate flickering
	BOOL bWnd = ::IsWindow(m_hWnd);
	BOOL bVisible = FALSE; 
	if (bWnd) bVisible = GetStyle() & WS_VISIBLE;
	if (bWnd) ShowWindow(SW_HIDE);
	// Effecitve load
	m_xFloorWnd.Load(m_sPagesAndItems, this);
	// Restore the state of window
	if (bVisible)
		ShowWindow(SW_SHOW);
	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::OnResizingColumnsChanged
// Description	    : After the m_bResizingColumnListCtrl is change the value
// Return type		: void 
void CXPropertiesWndCtrl::OnResizingColumnsChanged() 
{
	m_xFloorWnd.SetAutoResizingColumns(m_bAutoResizingColumns);

	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::OnSignEnableDisableChanged
// Description	    : 
// Return type		: void 
void CXPropertiesWndCtrl::OnSignEnableDisableChanged() 
{
	m_xFloorWnd.SetSignEnableDisable(m_bSignEnableDisable);
	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::OnActivatePage
// Description	    : Event for activate page
// Return type		: void 
// Argument         : short nIndexPage
void CXPropertiesWndCtrl::OnActivatePage(short nIndexPage)
{
	FireSelectPage(nIndexPage);
}

// Function name	: CXPropertiesWndCtrl::PreTranslateMessage
// Description	    : Treat separatly ESCAPE key
// Return type		: BOOL 
// Argument         : MSG* pMsg
BOOL CXPropertiesWndCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN &&
		(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_CANCEL))
		{
			return TRUE;
		}
	return COleControl::PreTranslateMessage(pMsg);
}

// Function name	: CXPropertiesWndCtrl::_GetPagesCount
// Description	    : Return the number of pages from control
// Return type		: short 
long CXPropertiesWndCtrl::_GetPagesCount() 
{
	return m_xFloorWnd.GetPagesCount();
}

// Function name	: CXPropertiesWndCtrl::_AddPage
// Description	    : Add a new page 
// Return type		: short 
// Argument         : LPCTSTR lpszPageName
short CXPropertiesWndCtrl::_AddPage(LPCTSTR lpszPageName) 
{
	return m_xFloorWnd.AddPage(lpszPageName, this);
}

// Function name	: CXPropertiesWndCtrl::_DeletePage
// Description	    : Delete the page nIndexPage
// Return type		: BOOL 
// Argument         : short nIndexPage
BOOL CXPropertiesWndCtrl::_DeletePage(short nIndexPage) 
{
	ResetMAPFound();
	return m_xFloorWnd.DeletePage(nIndexPage);
}

// Function name	: CXPropertiesWndCtrl::_GetPageName
// Description	    : Return the name of page nIndexPage
// Return type		: BSTR 
// Argument         : short nIndexPage
BSTR CXPropertiesWndCtrl::_GetPageName(short nIndexPage) 
{
	CString strResult;
	
	strResult = m_xFloorWnd.GetPageName(nIndexPage);

	return strResult.AllocSysString();
}

// Function name	: CXPropertiesWndCtrl::_GetPage
// Description	    : Return the position of page called lpszPageName
// Return type		: short 
// Argument         : LPCTSTR lpszPageName
short CXPropertiesWndCtrl::_GetPage(LPCTSTR lpszPageName) 
{
	return m_xFloorWnd.GetPage(lpszPageName);
}

// Function name	: CXPropertiesWndCtrl::_ActivatePage
// Description	    : Activate page nIndexPage
// Return type		: void 
// Argument         : short nIndexPage
void CXPropertiesWndCtrl::_ActivatePage(short nIndexPage) 
{
	m_xFloorWnd.ActivatePage(nIndexPage);
}

// Function name	: CXPropertiesWndCtrl::GetListCtrl
// Description	    : Return * to page list ctrl if item exist there
// Return type		: CPageListCtrl* 
// Argument         : int nIndexPage
// Argument         : int nIndexProperty
CPageListCtrl* CXPropertiesWndCtrl::GetListCtrl(int nIndexPage, int nIndexProperty)
{
	if (m_xFloorWnd.IsPage(nIndexPage))
		if (CPageListCtrl* pListCtrl = m_xFloorWnd.GetListCtrl(nIndexPage))
			if (nIndexProperty >= 0)
				if (nIndexProperty < pListCtrl->GetItemCount())
					return pListCtrl;
	return NULL;
}

// Function name	: CXPropertiesWndCtrl::_InsertProperty
// Description	    : Insert a new property into control
// Return type		: short 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : LPCTSTR lpszPropertyName
// Argument         : LPCTSTR lpszPropertyAs : 
// Argument         : long lpszProperyType : 0 - Enable, 1: Grayed, 2: Black
short CXPropertiesWndCtrl::_InsertProperty(short nIndexPage, short nIndexProperty, LPCTSTR lpszPropertyName, LPCTSTR lpszPropertyAs, short nProperyType) 
{
	short nResult = -1;
	if (m_xFloorWnd.IsPage(nIndexPage))
		if (CPageListCtrl* pListCtrl = m_xFloorWnd.GetListCtrl(nIndexPage))
			if (pListCtrl->m_asControls.GetID(lpszPropertyAs) != -1)
			{
				ResetMAPFound();
				nResult = (short)pListCtrl->InsertItem((nIndexProperty == -1 ? pListCtrl->GetItemCount() : nIndexProperty), lpszPropertyName);
				pListCtrl->SetItemData(nResult, MAKELPARAM(pListCtrl->m_asControls.GetID(lpszPropertyAs), nProperyType));
			}
	return nResult;
}

// Function name	: CXPropertiesWndCtrl::_DeleteProperty
// Description	    : Delete one property
// Return type		: BOOL 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
BOOL CXPropertiesWndCtrl::_DeleteProperty(short nIndexPage, short nIndexProperty) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
	{
		ResetMAPFound();
		return pListCtrl->DeleteItem(nIndexProperty);
	}
	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::_GetPropertyName
// Description	    : Get name of property
// Return type		: BSTR 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
BSTR CXPropertiesWndCtrl::_GetPropertyName(short nIndexPage, short nIndexProperty) 
{
	CString strResult;

	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		strResult = pListCtrl->GetPropertyName(nIndexProperty);

	return strResult.AllocSysString();
}

// Function name	: CXPropertiesWndCtrl::_GetPropertyType
// Description	    : Get property type
// Return type		: short 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
short CXPropertiesWndCtrl::_GetPropertyType(short nIndexPage, short nIndexProperty) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		return HIWORD(pListCtrl->GetItemData(nIndexProperty));
	return -1;
}

// Function name	: CXPropertiesWndCtrl::_SetPropertyType
// Description	    : set a new property type
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : short nNewType
void CXPropertiesWndCtrl::_SetPropertyType(short nIndexPage, short nIndexProperty, short nNewType) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		pListCtrl->SetItemData(nIndexProperty, MAKELPARAM(LOWORD(pListCtrl->GetItemData(nIndexProperty)), nNewType));
}

// Function name	: CXPropertiesWndCtrl::_GetPropertyAs
// Description	    : Get as property
// Return type		: BSTR 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
BSTR CXPropertiesWndCtrl::_GetPropertyAs(short nIndexPage, short nIndexProperty) 
{
	CString strResult;
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		strResult = pListCtrl->GetItemAsControl(nIndexProperty);
	return strResult.AllocSysString();
}

// Function name	: CXPropertiesWndCtrl::_IsProperty
// Description	    : return TRUE or FALSE if exist property nIndexPage, nIndexProperty
// Return type		: BOOL 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
BOOL CXPropertiesWndCtrl::_IsProperty(short nIndexPage, short nIndexProperty) 
{
	return GetListCtrl(nIndexPage, nIndexProperty) != NULL;
}

// Function name	: CXPropertiesWndCtrl::_GetIDListCtrl
// Description	    : get ID 
// Return type		: long 
// Argument         : short nIndexPage
long CXPropertiesWndCtrl::_GetIDListCtrl(short nIndexPage) 
{
	if (m_xFloorWnd.IsPage(nIndexPage))
		if (CPageListCtrl* pListCtrl = m_xFloorWnd.GetListCtrl(nIndexPage))
			return pListCtrl->GetDlgCtrlID();
	return -1;
}

// Function name	: CXPropertiesWndCtrl::_GetActivePage
// Description	    : Return the active page
// Return type		: short 
short CXPropertiesWndCtrl::_GetActivePage() 
{
	if (m_xFloorWnd.GetControlUnknown())
		return m_xFloorWnd.GetActivePage();
	return -1;
}

// Function name	: CXPropertiesWndCtrl::_GetxFloorWnd
// Description	    : 
// Return type		: LPUNKNOWN 
LPUNKNOWN CXPropertiesWndCtrl::_GetxFloorWnd() 
{
	return m_xFloorWnd.GetControlUnknown();
}

// Function name	: CXPropertiesWndCtrl::_GetDefaultValue
// Description	    : 
// Return type		: BOOL 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : BSTR FAR* sPropertyValue
BOOL CXPropertiesWndCtrl::_GetDefaultValue(short nIndexPage, short nIndexProperty, BSTR FAR* sPropertyValue) 
{
	if (sPropertyValue)
		if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		{
			*sPropertyValue = pListCtrl->GetDefaultValue(nIndexProperty).AllocSysString();
			return TRUE;
		}
	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::GetValueByName
// Description	    : return the value of a property
// Return type		: VARIANT 
// Argument         : LPCTSTR lpszPropertyName
VARIANT CXPropertiesWndCtrl::GetValueByName(LPCTSTR lpszPropertyName, long nColumn) 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	short nIndexPage, nIndexProperty;
	if (_GetPropertyIndex(lpszPropertyName, &nIndexPage, &nIndexProperty))
		return GetValue(nIndexPage, nIndexProperty, nColumn);
	return vaResult;
}

// Function name	: CXPropertiesWndCtrl::GetValue
// Description	    : 
// Return type		: VARIANT 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : long nColumn
VARIANT CXPropertiesWndCtrl::GetValue(short nIndexPage, short nIndexProperty, long nColumn) 
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty, FALSE))
		{
			vaResult = pControl->GetValue(nColumn);
			pControl->Delete();
		}
		else
		{
			vaResult.vt = VT_BSTR;
			vaResult.bstrVal = pListCtrl->GetDefaultValue(nIndexProperty).AllocSysString();
		}
	return vaResult;
}

// Function name	: CXPropertiesWndCtrl::SetValue
// Description	    : 
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : const VARIANT FAR& vValue
// Argument         : short nColumn
void CXPropertiesWndCtrl::SetValue(short nIndexPage, short nIndexProperty, const VARIANT FAR& vValue, short nColumn) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty, FALSE))
		{
			pControl->SetValue(vValue, nColumn);
			pControl->Delete();
			//Redraw item for control...
			pListCtrl->RedrawItems(pControl->GetSelectedItem(), pControl->GetSelectedItem());
		}
}

// Function name	: CXPropertiesWndCtrl::_SetDefaultValue
// Description	    : 
// Return type		: BOOL 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : LPCTSTR lpszDefaultvalue
BOOL CXPropertiesWndCtrl::_SetDefaultValue(short nIndexPage, short nIndexProperty, LPCTSTR lpszDefaultvalue) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		return pListCtrl->SetDefaultValue(nIndexProperty, lpszDefaultvalue);
	
	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::_GetPropertyCount
// Description	    : return number or propery from page nIndexPage
// Return type		: short 
// Argument         : short nIndexPage
short CXPropertiesWndCtrl::_GetPropertyCount(short nIndexPage) 
{
	if (CPageListCtrl* pListCtrl = m_xFloorWnd.GetListCtrl(nIndexPage))
		return pListCtrl->GetItemCount();
	return 0;
}

// Function name	: CXPropertiesWndCtrl::_SetPropertyName
// Description	    : Set the new property of control
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : LPCTSTR lpszProperyName
void CXPropertiesWndCtrl::_SetPropertyName(short nIndexPage, short nIndexProperty, LPCTSTR lpszProperyName) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
	{
		ResetMAPFound();
		pListCtrl->SetPropertyName(nIndexProperty, lpszProperyName);
	}
}

// Function name	: CXPropertiesWndCtrl::GetPageName
// Description	    : return the name page from a path
// Return type		: CString 
// Argument         : LPCTSTR lpszPathPropertyName
CString CXPropertiesWndCtrl::GetPageName(LPCTSTR lpszPathPropertyName)
{
	CString pageName, propertyName;
	AfxExtractSubString(pageName, lpszPathPropertyName, 0, TCHAR('\\'));
	AfxExtractSubString(propertyName, lpszPathPropertyName, 1, TCHAR('\\'));
	if (propertyName.IsEmpty())
	{
		propertyName = pageName;
		pageName.Empty();
	}
	return pageName;
}

// Function name	: CXPropertiesWndCtrl::GetPropertyName
// Description	    : return the property name from path
// Return type		: CString 
// Argument         : LPCTSTR lpszPathPropertyName
CString CXPropertiesWndCtrl::GetPropertyName(LPCTSTR lpszPathPropertyName)
{
	CString pageName, propertyName;
	AfxExtractSubString(pageName, lpszPathPropertyName, 0, TCHAR('\\'));
	AfxExtractSubString(propertyName, lpszPathPropertyName, 1, TCHAR('\\'));
	if (propertyName.IsEmpty())
	{
		propertyName = pageName;
		pageName.Empty();
	}
	return propertyName;
}

// Function name	: CXPropertiesWndCtrl::AppendSearch
// Description	    : Add a new result search
// Return type		: void 
// Argument         : LPCTSTR lpszPropertyName
// Argument         : short lLow
// Argument         : short lHigh
void CXPropertiesWndCtrl::AppendSearch(LPCTSTR lpszPropertyName, short lLow, short lHigh)
{
	m_mapSearch[lpszPropertyName] = (CObject*)MAKELPARAM(lLow,lHigh);
}

// Function name	: CXPropertiesWndCtrl::AlreadyFound
// Description	    : Already lpszProperty was searched
// Return type		: BOOL 
// Argument         : LPCTSTR lpszPropertyName
// Argument         : short * lLow
// Argument         : short * lHigh
BOOL CXPropertiesWndCtrl::AlreadyFound(LPCTSTR lpszPropertyName, short * lLow, short * lHigh)
{
	CObject* pObject = NULL;
	if (m_mapSearch.Lookup(lpszPropertyName, pObject))
	{
		*lLow = LOWORD((LPARAM)pObject);
		*lHigh = HIWORD((LPARAM)pObject);
		return TRUE;
	}
	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::ResetMAPFound
// Description	    : 
// Return type		: void 
void CXPropertiesWndCtrl::ResetMAPFound()
{
	m_mapSearch.RemoveAll();
}

// Function name	: CXPropertiesWndCtrl::_GetPropertyIndex
// Description	    : Return the index of page and property for property called lpszPropertyName
// Return type		: BOOL 
// Argument         : LPCTSTR lpszPropertyName
// Argument         : short FAR* nIndexPage
// Argument         : short FAR* nIndexProperty
BOOL CXPropertiesWndCtrl::_GetPropertyIndex(LPCTSTR lpszPropertyName, short FAR* nIndexPage, short FAR* nIndexProperty) 
{
	*nIndexPage = -1; *nIndexProperty = -1;
	if (AlreadyFound(lpszPropertyName, nIndexPage, nIndexProperty))
		return nIndexProperty >= 0;

	CString pageName = GetPageName(lpszPropertyName), propertyName = GetPropertyName(lpszPropertyName);
	if (!propertyName.IsEmpty())
	{
		int iStart = 0, iEnd = _GetPagesCount(), sPage = -1;
		if (!pageName.IsEmpty())
			if ((sPage = m_xFloorWnd.GetPage(pageName))>= 0)
			{
				iStart = sPage;
				iEnd = sPage + 1;
				*nIndexPage = iStart;
			}
			else
			{
				*nIndexPage = -1;
				iEnd = -1;
			}
		for (int i = iStart; i < iEnd; i++)
			for (int j = 0; j < _GetPropertyCount(i); j++)
				if (CString(_GetPropertyName(i, j)).CompareNoCase(propertyName) == 0)
				{
					*nIndexPage = i;
					*nIndexProperty = j;
					AppendSearch(lpszPropertyName, i, j);
					return TRUE;
				}
	}
	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::_SetDefaultValueByName
// Description	    : Set the default value by property name
// Return type		: BOOL 
// Argument         : LPCTSTR lpszPropertyName
// Argument         : LPCTSTR lpszPropertyValue
BOOL CXPropertiesWndCtrl::_SetDefaultValueByName(LPCTSTR lpszPropertyName, LPCTSTR lpszPropertyValue) 
{
	short nPage, nProperty;
	if (_GetPropertyIndex(lpszPropertyName, &nPage, &nProperty))
		return _SetDefaultValue(nPage, nProperty, lpszPropertyValue);

	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::_GetDefaultValueByName
// Description	    : get the default value from property lpszPropertyName
// Return type		: BSTR 
// Argument         : LPCTSTR lpszPropertyName
BSTR CXPropertiesWndCtrl::_GetDefaultValueByName(LPCTSTR lpszPropertyName) 
{
	short nIndexPage, nIndexProperty;
	if (_GetPropertyIndex(lpszPropertyName, &nIndexPage, &nIndexProperty))
		if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		{
			CString strResult = pListCtrl->GetDefaultValue(nIndexProperty);
			return strResult.AllocSysString();
		}
	return NULL;
}

// Function name	: CXPropertiesWndCtrl::_GetActiveProperty
// Description	    : return the Active Property
// Return type		: short 
// Argument         : short FAR* nIndexPage
short CXPropertiesWndCtrl::_GetActiveProperty(short FAR* nIndexPage) 
{
	if (nIndexPage)
	{
		*nIndexPage = _GetActivePage();
		return m_xFloorWnd.GetListCtrl(*nIndexPage)->GetActiveProperty();
	}
	return -1;
}

// Function name	: CXPropertiesWndCtrl::_SetActiveProperty
// Description	    : 
// Return type		: BOOL 
// Argument         : short nIndexPage
// Argument         : short IndexProperty
BOOL CXPropertiesWndCtrl::_SetActiveProperty(short nIndexPage, short nIndexProperty) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
	{
		m_xFloorWnd.ActivatePage(nIndexPage);
		pListCtrl->SetActiveProperty(nIndexProperty);
		return TRUE;
	}
	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::_SetActivePropertyByName
// Description	    : Set property lpszPropertyName as active
// Return type		: BOOL 
// Argument         : LPCTSTR lpszPropertyName
BOOL CXPropertiesWndCtrl::_SetActivePropertyByName(LPCTSTR lpszPropertyName) 
{
	short nIndexPage, nIndexProperty;
	if (_GetPropertyIndex(lpszPropertyName, &nIndexPage, &nIndexProperty))
		return _SetActiveProperty(nIndexPage, nIndexProperty);
	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::_DeletePropertyByName
// Description	    : Delete a property by name
// Return type		: BOOL 
// Argument         : LPCTSTR lpszPropertyName
BOOL CXPropertiesWndCtrl::_DeletePropertyByName(LPCTSTR lpszPropertyName) 
{
	short nIndexPage, nIndexProperty;
	if (_GetPropertyIndex(lpszPropertyName, &nIndexPage, &nIndexProperty))
		return _DeleteProperty(nIndexPage, nIndexProperty);

	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::_AddProperty
// Description	    : Add a new property
// Return type		: BOOL 
// Argument         : short lpszPropertyName
// Argument         : LPCTSTR lpszPropertyAs
// Argument         : short nPropertyType
short CXPropertiesWndCtrl::_AddProperty(LPCTSTR lpszPropertyName, LPCTSTR lpszPropertyAs, short nPropertyType) 
{
	short nIndexPage = -1, nIndexProperty = -1;
	_GetPropertyIndex(lpszPropertyName, &nIndexPage, &nIndexProperty);
	nIndexPage = max(0, nIndexPage);
	return _InsertProperty(nIndexPage, -1, GetPropertyName(lpszPropertyName), lpszPropertyAs, nPropertyType);
}

// Function name	: CXPropertiesWndCtrl::GetColumnKey
// Description	    : Return a column key for ...
// Return type		: long 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
long CXPropertiesWndCtrl::GetColumnKey(short nIndexPage, short nIndexProperty) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			return pControl->GetColumnKey();
	return -1;
}

// Function name	: CXPropertiesWndCtrl::SetColumnKey
// Description	    : Set a column key
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : long nNewValue
void CXPropertiesWndCtrl::SetColumnKey(short nIndexPage, short nIndexProperty, long nNewValue) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			pControl->SetColumnKey(nNewValue);
}

// Function name	: CXPropertiesWndCtrl::GetColumnWidth
// Description	    : return the width of column
// Return type		: long 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
long CXPropertiesWndCtrl::GetColumnWidth(short nIndexPage, short nIndexProperty, short nColumn) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			return pControl->GetColumnWidth(nColumn);
	return -1;
}

// Function name	: CXPropertiesWndCtrl::GetColumnKeyByName
// Description	    : 
// Return type		: BSTR 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
BSTR CXPropertiesWndCtrl::GetColumnKeyByName(short nIndexPage, short nIndexProperty) 
{
	CString strResult;
	if (BSTR bStr = GetColumnName(nIndexPage, nIndexProperty, (short)GetColumnKey(nIndexPage, nIndexProperty)))
	{
		strResult = CString(bStr);
		::SysFreeString(bStr);
		return strResult.AllocSysString();
	}
	return NULL;
}

// Function name	: CXPropertiesWndCtrl::SetColumnKeyByName
// Description	    : Search column named lpszNewValue, and set that as column key
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : LPCTSTR lpszNewValue
void CXPropertiesWndCtrl::SetColumnKeyByName(short nIndexPage, short nIndexProperty, LPCTSTR lpszNewValue) 
{
	int nColumn = 0;
	CString sColumn;
	do 
	{
		BSTR bStr = GetColumnName(nIndexPage, nIndexProperty, nColumn);
		sColumn = CString(bStr);
		::SysFreeString(bStr);
		if (sColumn.IsEmpty())
			break;
		if (sColumn.CompareNoCase(lpszNewValue) == 0)
		{
			SetColumnKey(nIndexPage, nIndexProperty , nColumn);
			break;
		}
		nColumn++;
	}
	while (1);
	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::SetColumnWidth
// Description	    : Set the new width of column
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : long nNewValue
void CXPropertiesWndCtrl::SetColumnWidth(short nIndexPage, short nIndexProperty, short nColumn, long nNewValue) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			pControl->SetColumnWidth(nColumn, nNewValue);
}

// Function name	: CXPropertiesWndCtrl::GetHeaderName
// Description	    : 
// Return type		: BSTR 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : short nColumn
BSTR CXPropertiesWndCtrl::GetColumnName(short nIndexPage, short nIndexProperty, short nColumn) 
{
	CString strResult;
	
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			return CString(pControl->GetColumnName(nColumn)).AllocSysString();

	return NULL;
}

// Function name	: CXPropertiesWndCtrl::SetColumnName
// Description	    : 
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : short nColumn
// Argument         : LPCTSTR lpszNewValue
void CXPropertiesWndCtrl::SetColumnName(short nIndexPage, short nIndexProperty, short nColumn, LPCTSTR lpszNewValue) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			pControl->SetColumnName(nColumn, lpszNewValue);
}

// Function name	: CXPropertiesWndCtrl::GetColumnName
// Description	    : 
// Return type		: BOOL 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
BOOL CXPropertiesWndCtrl::GetColumnHeader(short nIndexPage, short nIndexProperty) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			return pControl->GetColumnHeader();

	return FALSE;
}

// Function name	: CXPropertiesWndCtrl::SetColumnHeader
// Description	    : 
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : BOOL bNewValue
void CXPropertiesWndCtrl::SetColumnHeader(short nIndexPage, short nIndexProperty, BOOL bNewValue) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			pControl->SetColumnHeader(bNewValue);
}

// Function name	: CXPropertiesWndCtrl::GetDropDownWidth
// Description	    : Get rate of drop down width
// Return type		: double 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
double CXPropertiesWndCtrl::GetDropDownWidth(short nIndexPage, short nIndexProperty) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			return pControl->GetDropDownWidth();
	return -1.0;
}

// Function name	: CXPropertiesWndCtrl::SetDropDownWidth
// Description	    : Set the new rate for drop down width
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : double newValue
void CXPropertiesWndCtrl::SetDropDownWidth(short nIndexPage, short nIndexProperty, double newValue) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			pControl->SetDropDownWidth(newValue);
}

// Function name	: CXPropertiesWndCtrl::GetDropDownHeight
// Description	    : 
// Return type		: long 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
long CXPropertiesWndCtrl::GetDropDownHeight(short nIndexPage, short nIndexProperty) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			return pControl->GetDropDownHeight();
	return -1;
}

// Function name	: CXPropertiesWndCtrl::SetDropDownHeight
// Description	    : 
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
// Argument         : long nNewValue
void CXPropertiesWndCtrl::SetDropDownHeight(short nIndexPage, short nIndexProperty, long nNewValue) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			pControl->SetDropDownHeight(nNewValue);
}

// Function name	: CXPropertiesWndCtrl::RefreshProperty
// Description	    : If the control associated with property is ADOR.Recordset it will be reqery
// Return type		: void 
// Argument         : short nIndexPage
// Argument         : short nIndexProperty
void CXPropertiesWndCtrl::RefreshProperty(short nIndexPage, short nIndexProperty) 
{
	if (CPageListCtrl* pListCtrl = GetListCtrl(nIndexPage, nIndexProperty))
		if (CControlsWnd* pControl = pListCtrl->GetControl(nIndexProperty))
			pControl->Refresh();
}

// Function name	: CXPropertiesWndCtrl::_Init
// Description	    : Init the control
// Return type		: void 
void CXPropertiesWndCtrl::_Init() 
{
	m_xFloorWnd.Init();
}

// Function name	: CXPropertiesWndCtrl::OnToolTipsChanged
// Description	    : 
// Return type		: void 
void CXPropertiesWndCtrl::OnToolTipsChanged() 
{
	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::OnResizeFirstColumnChanged
// Description	    : 
// Return type		: void 
void CXPropertiesWndCtrl::OnResizeFirstColumnChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::OnFirstPageHasCaptionChanged
// Description	    : Set the new value for m_bFirstPageHasCaption
// Return type		: void 
void CXPropertiesWndCtrl::OnFirstPageHasCaptionChanged() 
{
	m_xFloorWnd.m_bFirstPageHasCaption = m_bFirstPageHasCaption;
	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::OnAsFloorChanged
// Description	    : Change the style ...
// Return type		: void 
void CXPropertiesWndCtrl::OnAsFloorChanged() 
{
	m_xFloorWnd.m_bAsFloor = m_bAsFloor;
	if (m_xFloorWnd.GetControlUnknown())
		m_xFloorWnd.StyleAs(m_xFloorWnd.m_bAsFloor);
	SetModifiedFlag();
}

// Function name	: CXPropertiesWndCtrl::OnFontChanged
// Description	    : Select the font for xFloorWnd.ActiveX control
// Return type		: void 
void CXPropertiesWndCtrl::OnFontChanged() 
{
	COleControl::OnFontChanged();
	if (m_xFloorWnd.GetControlUnknown())
		m_xFloorWnd.SetProperty(DISPID_FONT, VT_DISPATCH, GetFont());

}

// Function name	: CXPropertiesWndCtrl::GetItemFont
// Description	    : return the Item font
// Return type		: LPFONTDISP 
LPFONTDISP CXPropertiesWndCtrl::GetItemFont() 
{
	return m_itemFont.GetFontDispatch();
}

// Function name	: CXPropertiesWndCtrl::SetItemFont
// Description	    : Set the new item font
// Return type		: void 
// Argument         : LPFONTDISP newValue
void CXPropertiesWndCtrl::SetItemFont(LPFONTDISP newValue) 
{
	m_itemFont.InitializeFont(&_fontdescItem, newValue);

	SetModifiedFlag();
}

// Function name	: STDMETHODIMP_
// Description	    : Add a new referince to ItemFontNotify interface
// Return type		: 
// Argument         : ULONG
STDMETHODIMP_(ULONG) CXPropertiesWndCtrl::XItemFontNotify::AddRef( )
{
    METHOD_MANAGE_STATE(CXPropertiesWndCtrl, ItemFontNotify)
    return 1;
}

// Function name	: STDMETHODIMP_
// Description	    : release the added interface
// Return type		: 
// Argument         : ULONG
STDMETHODIMP_(ULONG) CXPropertiesWndCtrl::XItemFontNotify::Release( )
{
    METHOD_MANAGE_STATE(CXPropertiesWndCtrl, ItemFontNotify)
    return 0;
}

// Function name	: CXPropertiesWndCtrl::XItemFontNotify::QueryInterface
// Description	    : If something ask, ask
// Return type		: STDMETHODIMP 
// Argument         :  REFIID iid
// Argument         : LPVOID FAR* ppvObj
STDMETHODIMP CXPropertiesWndCtrl::XItemFontNotify::QueryInterface( REFIID iid, LPVOID FAR* ppvObj )
{
    METHOD_MANAGE_STATE( CXPropertiesWndCtrl , ItemFontNotify )
    if( IsEqualIID( iid, IID_IUnknown ) || IsEqualIID( iid, IID_IPropertyNotifySink))
    {
		 *ppvObj= this;
		 AddRef();
		 return NOERROR;
    }
    return ResultFromScode(E_NOINTERFACE);
}

// Function name	: CXPropertiesWndCtrl::XItemFontNotify::OnRequestEdit
// Description	    : 
// Return type		: STDMETHODIMP 
// Argument         : DISPID
STDMETHODIMP CXPropertiesWndCtrl::XItemFontNotify::OnRequestEdit(DISPID)
{
    return NOERROR;
}

// Function name	: CXPropertiesWndCtrl::XItemFontNotify::OnChanged
// Description	    : If font is changed
// Return type		: STDMETHODIMP 
// Argument         : DISPID
STDMETHODIMP CXPropertiesWndCtrl::XItemFontNotify::OnChanged(DISPID)
{
    METHOD_MANAGE_STATE( CXPropertiesWndCtrl , ItemFontNotify )
	if (pThis->m_xFloorWnd.GetControlUnknown())
	{
		LOGFONT logFont;
		if (::GetObject(pThis->m_itemFont.GetFontHandle(), sizeof(LOGFONT), &logFont))
		{
			int i = 0; CPageListCtrl* pPage = NULL;
			while (pPage = pThis->m_xFloorWnd.GetListCtrl(i++))
			{
				pPage->CreateItemFont((const LOGFONT*)&logFont);
				pPage->Invalidate();
			}
		}
	}
    return NOERROR;
}

void CXPropertiesWndCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	COleControl::OnSetFocus(pOldWnd);
	
	int iPage = -1;
	if ((iPage = _GetActivePage())  >= 0)
	{
		if (CPageListCtrl* pPage = m_xFloorWnd.GetListCtrl(iPage))
			pPage->SetFocus();
	}
}
