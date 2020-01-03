/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/8/98 3:52:57 PM
  Comments: XFloorWndCtl.cpp : Implementation of the CXFloorWndCtrl ActiveX Control class.
 ************************************/

#include "stdafx.h"
#include "XFloorWnd.h"
#include "XFloorWndCtl.h"
#include "XFloorWndPpg.h"
#include "FloorLabeObject.h"
#include "gdi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CXFloorWndCtrl, COleControl)

#ifdef _OBEJCTISSAFETY
//Implementation IObjectSafety
BEGIN_INTERFACE_MAP(CXFloorWndCtrl, COleControl)
  INTERFACE_PART(CXFloorWndCtrl, IID_IObjectSafety, ObjectSafety)
END_INTERFACE_MAP()

STDMETHODIMP CXFloorWndCtrl::XObjectSafety::GetInterfaceSafetyOptions(
			REFIID riid, 
			DWORD __RPC_FAR *pdwSupportedOptions, 
			DWORD __RPC_FAR *pdwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CXFloorWndCtrl, ObjectSafety)

	if (!pdwSupportedOptions || !pdwEnabledOptions)
	{
		return E_POINTER;
	}

	*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
	*pdwEnabledOptions = 0;

	if (NULL == pThis->GetInterface(&riid))
	{
		TRACE("Requested interface is not supported.\n");
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
		TRACE("We didn't account for the safety of this interface, and it's one we support...\n");
		return E_NOINTERFACE;
	}	
}

STDMETHODIMP CXFloorWndCtrl::XObjectSafety::SetInterfaceSafetyOptions(
		REFIID riid, 
		DWORD dwOptionSetMask, 
		DWORD dwEnabledOptions)
{
	METHOD_PROLOGUE_EX(CXFloorWndCtrl, ObjectSafety)

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
		TRACE("Client asking if it's safe to call through IDispatch.\n");
		TRACE("In other words, is the control safe for scripting?\n");
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
		TRACE("Client asking if it's safe to call through IPersist*.\n");
		TRACE("In other words, is the control safe for initializing from persistent data?\n");

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

STDMETHODIMP_(ULONG) CXFloorWndCtrl::XObjectSafety::AddRef()
{
	METHOD_PROLOGUE_EX_(CXFloorWndCtrl, ObjectSafety)
	return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CXFloorWndCtrl::XObjectSafety::Release()
{
	METHOD_PROLOGUE_EX_(CXFloorWndCtrl, ObjectSafety)
	return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CXFloorWndCtrl::XObjectSafety::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CXFloorWndCtrl, ObjectSafety)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}
#endif //_OBEJCTISSAFETY

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CXFloorWndCtrl, COleControl)
	//{{AFX_MSG_MAP(CXFloorWndCtrl)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CXFloorWndCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CXFloorWndCtrl)
	DISP_PROPERTY_NOTIFY(CXFloorWndCtrl, "Animation", m_bAnimation, OnAnimationChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CXFloorWndCtrl, "Sleep", m_nSleep, OnSleepChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CXFloorWndCtrl, "Sign", m_bSign, OnSignChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CXFloorWndCtrl, "Pages", m_sPages, OnPagesChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CXFloorWndCtrl, "AsPage", m_bAsPage, OnAsPageChanged, VT_BOOL)
	DISP_FUNCTION(CXFloorWndCtrl, "AddPage", _AddPage, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CXFloorWndCtrl, "DeletePage", _DeletePage, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CXFloorWndCtrl, "GetPageName", _GetPageName, VT_BSTR, VTS_I2)
	DISP_FUNCTION(CXFloorWndCtrl, "GetPage", _GetPage, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CXFloorWndCtrl, "ActivatePage", _ActivatePage, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CXFloorWndCtrl, "AttachWindow", _AttachWindow, VT_BOOL, VTS_I2 VTS_I4)
	DISP_FUNCTION(CXFloorWndCtrl, "SetPageName", _SetPageName, VT_BOOL, VTS_I2 VTS_BSTR)
	DISP_FUNCTION(CXFloorWndCtrl, "Init", _Init, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CXFloorWndCtrl, "GetActivePage", _GetActivePage, VT_I2, VTS_NONE)
	DISP_FUNCTION(CXFloorWndCtrl, "GetPagesCount", _GetPagesCount, VT_I4, VTS_NONE)
	DISP_FUNCTION(CXFloorWndCtrl, "IsPage", _IsPage, VT_BOOL, VTS_I2)
	DISP_FUNCTION(CXFloorWndCtrl, "GetLeftTopPage", _GetLeftTopPage, VT_I4, VTS_I2)
	DISP_FUNCTION(CXFloorWndCtrl, "GetBottomRightPage", _GetBottomRightPage, VT_I4, VTS_I2)
	DISP_FUNCTION(CXFloorWndCtrl, "StyleAs", StyleAs, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CXFloorWndCtrl, "GetHWnd", GetHWnd, VT_I4, VTS_I4)
	DISP_PROPERTY_PARAM(CXFloorWndCtrl, "Height", GetHeight, SetHeight, VT_I2, VTS_I2)
	DISP_PROPERTY_PARAM(CXFloorWndCtrl, "Color", GetColor, SetColor, VT_COLOR, VTS_I2)
	DISP_PROPERTY_PARAM(CXFloorWndCtrl, "UserData", GetUserData, SetUserData, VT_I4, VTS_I2)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FONT()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CXFloorWndCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CXFloorWndCtrl, COleControl)
	//{{AFX_EVENT_MAP(CXFloorWndCtrl)
	EVENT_CUSTOM("ActivatePage", FireActivatePage, VTS_I2)
	EVENT_CUSTOM("ClickOnActivePage", FireClickOnActivePage, VTS_I2)
	EVENT_STOCK_CLICK()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CXFloorWndCtrl, 3)
	PROPPAGEID(CXFloorWndPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
	PROPPAGEID(CLSID_CFontPropPage)
END_PROPPAGEIDS(CXFloorWndCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CXFloorWndCtrl, "XFLOORWND.XFloorWndCtrl.1",
	0x24ffd1ed, 0x5ea9, 0x11d2, 0x86, 0xb1, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CXFloorWndCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DXFloorWnd =
		{ 0x24ffd1eb, 0x5ea9, 0x11d2, { 0x86, 0xb1, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9 } };
const IID BASED_CODE IID_DXFloorWndEvents =
		{ 0x24ffd1ec, 0x5ea9, 0x11d2, { 0x86, 0xb1, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwXFloorWndOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CXFloorWndCtrl, IDS_XFLOORWND, _dwXFloorWndOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndCtrl::CXFloorWndCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CXFloorWndCtrl

BOOL CXFloorWndCtrl::CXFloorWndCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_XFLOORWND,
			IDB_XFLOORWND,
			afxRegApartmentThreading,
			_dwXFloorWndOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndCtrl::CXFloorWndCtrl - Constructor

CFloorPageObject* CXFloorWndCtrl::m_pFocusPage = NULL;
UINT CXFloorWndCtrl::m_nMessageChange = NULL;
CRect CXFloorWndCtrl::m_rtBorder(CPoint(-2,-2), CSize(0,0));

// Function name	: CXFloorWndCtrl::CXFloorWndCtrl
// Description	    : Default constructor
// Return type		: 
CXFloorWndCtrl::CXFloorWndCtrl()
{
	InitializeIIDs(&IID_DXFloorWnd, &IID_DXFloorWndEvents);

	RegClassFloorWnd();
	m_pActivePage = NULL;
	m_nSleep = 0;
	m_pArPage = new CArrayPage();
	m_nDYLabel = GetSystemMetrics(SM_CYCAPTION); // a default value...
	m_nDYCombo = 10 * m_nDYLabel; // a default value...
}


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndCtrl::~CXFloorWndCtrl - Destructor

// Function name	: CXFloorWndCtrl::~CXFloorWndCtrl
// Description	    : default destructor
// Return type		: 
CXFloorWndCtrl::~CXFloorWndCtrl()
{
	while (DeletePage(0));
	if (m_pArPage)
		delete m_pArPage;
	m_pArPage = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndCtrl::OnDraw - Drawing function

void CXFloorWndCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_hWnd)
		if (::IsWindow(m_hWnd))
		{
			CDC dcMem; CBitmap bmpMem;
			CRect r; GetClientRect(r);
			if (dcMem.CreateCompatibleDC(pdc))
				if (bmpMem.CreateCompatibleBitmap(pdc, r.Width(), r.Height()))
				{
					CBitmap* pBitmap = dcMem.SelectObject(&bmpMem);
					COLORREF colorBkGnd = TranslateColor(GetBackColor());
					CBrush brBkGnd(colorBkGnd);
					CBrush* pBrush = dcMem.SelectObject(&brBkGnd);
					//Erase the bkgnd of this
					dcMem.PatBlt(r.left, r.top, r.right, r.bottom, PATCOPY);
					for (int i = 0; i < GetCountPage(); i++)
						GetPage(i)->OnDraw(&dcMem, TRUE);
					pdc->BitBlt(r.left,r.top,r.Width(), r.Height(), &dcMem, 0,0, SRCCOPY);
					dcMem.SelectObject(pBitmap);
					dcMem.SelectObject(pBrush);
				}
				return;
		}
	// Write the version
	COLORREF colorBkGnd = TranslateColor(GetBackColor());
	CBrush brBkGnd(colorBkGnd);
	CBrush* pBrush = pdc->SelectObject(&brBkGnd);
	//Erase the bkgnd of this
	pdc->PatBlt(rcInvalid.left, rcInvalid.top, rcInvalid.right, rcInvalid.bottom, PATCOPY);
	CFont* pFont = SelectStockFont(pdc);
	CString version; version.Format(_T("XFloorWnd %i.%02i"), _wVerMajor, _wVerMinor);
	pdc->SetBkMode(TRANSPARENT);
	pdc->DrawText(version, CRect(rcInvalid), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	pdc->SelectObject(pFont);
	pdc->SelectObject(pBrush);
}


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndCtrl::DoPropExchange - Persistence support

void CXFloorWndCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	PX_Bool(pPX, _T("Animation"), m_bAnimation, TRUE);
	PX_Long(pPX, _T("Sleep"), m_nSleep, 0);
	PX_Bool(pPX, _T("Sign"), m_bSign, TRUE);
	PX_Bool(pPX, _T("AsPage"), m_bAsPage, TRUE);
	PX_String(pPX, _T("Pages"), m_sPages, _T(""));

	if (pPX->IsLoading())
		OnPagesChanged();
}


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndCtrl::OnResetState - Reset control to default state

void CXFloorWndCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	COLORREF clrBack = defaultRGBBkGnd;
	SetBackColor((OLE_COLOR)clrBack);
}


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndCtrl::AboutBox - Display an "About" box to the user

void CXFloorWndCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_XFLOORWND);
	dlgAbout.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CXFloorWndCtrl message handlers

// Function name	: CXFloorWndCtrl::GetCountPage
// Description	    : Get count of pages
// Return type		: int 
int CXFloorWndCtrl::GetCountPage()
{
	return m_pArPage->GetSize();
}

// Function name	: CXFloorWndCtrl::GetPage
// Description	    : Return the page index nIndex
// Return type		: CFloorPageObject* 
// Argument         : int nIndex
CFloorPageObject* CXFloorWndCtrl::GetPage(int nIndex)
{
	if (nIndex >=0)
		if (nIndex < GetCountPage() )
			return (*m_pArPage)[nIndex];
	return NULL;
}

// Function name	: CXFloorWndCtrl::GetPage
// Description	    : Return the page with name lpszPageName
// Return type		: CFloorPageObject* 
// Argument         : LPCTSTR lpszPageName
CFloorPageObject* CXFloorWndCtrl::GetPage(LPCTSTR lpszPageName)
{
	for (int i = 0; i < GetCountPage(); i++)
		if (GetPage(i)->GetName().CompareNoCase(lpszPageName) == 0)
			return GetPage(i);
	return NULL;
}

// Function name	: CXFloorWndCtrl::RecalcLayout
// Description	    : Called this function when a page was added, removed, or his size, position changes
// This function can recalc all rect of windows.
// Return type		: void 
void CXFloorWndCtrl::RecalcLayout()
{
	if (::IsWindow(m_hWnd))
	{
		if (m_bAsPage)
		{
			CRect rClient; GetClientRect(rClient);
			rClient.InflateRect(-1,-1);
			int uY = rClient.top, dY = rClient.bottom;
			for (int i = 0; i < GetCountPage(); i++)
			{
				CFloorObject* pPage = GetPage(i);
				if (pPage->IsPullUp())
				{
					pPage->m_rect = CRect(rClient.left,uY,rClient.right,uY + pPage->GetHeight());
					uY += pPage->GetHeight() + 1;
					ValidateRect(pPage->m_rect);
				}
			}
			for (i = GetCountPage() - 1; i >= 0 ; i--)
			{
				CFloorObject* pPage = GetPage(i);
				if (pPage->IsPullDown())
				{
					pPage->m_rect = CRect(rClient.left,dY - pPage->GetHeight(),rClient.right,dY);
					dY -= pPage->GetHeight() + 1;
					ValidateRect(pPage->m_rect);
				}
			}
			m_rectClient = CRect(rClient.left + 1, uY, rClient.right - 2, dY - 1);
			}
		else
			{
				CRect rect; GetClientRect(rect);
				CRect rPage = ChangeHeightLabel(rect.Size());
				m_rectClient = rect;
				m_rectClient.top += m_nDYLabel;
				m_rectClient.InflateRect(m_rtBorder);
				for (int i = 0; i < m_pArPage->GetSize(); i++)
					(*m_pArPage)[i]->m_rect = rPage;

				if (CFloorPageObject* pPage = GetActivePage())
					pPage->SetRectClient(m_rectClient);
			}
		Invalidate();
	}	
}

// Function name	: CXFloorWndCtrl::Preview
// Description	    : Preview of window to a bitmap, If pWnd == NULL then
// function will return the bitmap with bkgnd color of thsi window
// Return type		: CBitmap* 
// Argument         : CWnd * pWnd
CBitmap* CXFloorWndCtrl::Preview(CWnd * pWnd)
{
	CBitmap *pBitmap = NULL, bitmapNonClient;
	CWnd *pDrawWnd = pWnd ? pWnd : this;
	if (pDrawWnd && ::IsWindow(pDrawWnd->m_hWnd))
	{
		CRect rectWindow; pDrawWnd->GetWindowRect(rectWindow);
		CRect rectClient; pDrawWnd->GetClientRect(rectClient);
		CPoint p(0,0);
		pDrawWnd->ClientToScreen(&p);
		rectClient.OffsetRect(p.x - rectWindow.left, p.y - rectWindow.top);
		CDC* pDC = pDrawWnd->GetDC();
		CDC dcMemSourceNonClient, dcMemDestination;
		COLORREF colorBkGnd = TranslateColor(GetBackColor());
		CBrush brBkGnd(colorBkGnd);
		CGdiStack stack;
		if (dcMemSourceNonClient.CreateCompatibleDC(pDC))
			if (dcMemDestination.CreateCompatibleDC(pDC))
				if (pBitmap = new CBitmap())
					if (pBitmap->CreateCompatibleBitmap(pDC, rectWindow.Width(), rectWindow.Height()))
						if (bitmapNonClient.CreateCompatibleBitmap(pDC, rectWindow.Width(), rectWindow.Height()))
						{
							stack.Push(&dcMemSourceNonClient,&bitmapNonClient);
							stack.Push(&dcMemSourceNonClient,&brBkGnd);
							dcMemSourceNonClient.PatBlt(0,0,rectWindow.Width(), rectWindow.Height(), PATCOPY);
							stack.Push(&dcMemDestination, pBitmap);
							if (pWnd)
								pDrawWnd->Print(&dcMemSourceNonClient, PRF_NONCLIENT);
							dcMemDestination.BitBlt(0,0,rectWindow.Width(), rectWindow.Height(), &dcMemSourceNonClient, 0,0, SRCCOPY);
							if (pWnd)
							{
								CPoint pLT(0,0);
								pDrawWnd->ClientToScreen(&pLT);
								dcMemDestination.SetViewportOrg(pLT.x - rectWindow.left, pLT.y - rectWindow.top);
								pDrawWnd->Print(&dcMemDestination, PRF_CHILDREN | PRF_CLIENT | PRF_ERASEBKGND);
							}
							stack.Pop();
							stack.Pop();
							stack.Pop();
							bitmapNonClient.DeleteObject();
							dcMemDestination.DeleteDC();
							dcMemSourceNonClient.DeleteDC();
						}
		pDrawWnd->ReleaseDC(pDC);
	}
	return pBitmap;
}

// Function name	: CXFloorWndCtrl::AddPage
// Description	    : Call to add a new page into floorwindow control
// Updated			: Version 1.01
// Return type		: CFloorPageObject* 
// Argument         : LPCTSTR lpszPageName
// Argument         : int * pIndex
CFloorPageObject* CXFloorWndCtrl::AddPage(LPCTSTR lpszPageName, int * pIndex)
{
	ActivatePage(GetCountPage() - 1);
	if (CFloorPageObject* pPage = NewPage(m_bAsPage, lpszPageName))
	{
		int index = m_pArPage->Add(pPage);
		if (pIndex) *pIndex = index;
		RecalcLayout();
		OnActivatePage(pPage);
		return pPage;
	}
	return NULL;
}

// Function name	: CXFloorWndCtrl::OnActivatePage
// Description	    : Activate page pPage, and notify the parent of this object
// Update			: Version 1.01. Focus bug
// Return type		: void 
// Argument         : CFloorPageObject * pPage
void CXFloorWndCtrl::OnActivatePage(CFloorPageObject * pPage)
{
	if (::IsWindow(m_hWnd))
	{
		// Always, this function must be called after RecalcLayout
		if (m_pActivePage)
			m_pActivePage->OnDeactivateObject();
		m_pActivePage = pPage;
		m_pActivePage->SetRectClient(m_rectClient);
		m_pActivePage->OnActivateObject();
		if (CWnd* pParentWnd = GetParent())
			pParentWnd->SendMessage(m_nMessageChange, (WPARAM)m_pActivePage, (LPARAM)pPage);
		FireActivatePage(PtrPageToIndex(pPage));
		m_pFocusPage = NULL;
	}
}

// Function name	: CXFloorWndCtrl::RegClassFloorWnd
// Description	    : Call once this function to register FloorWnd class name
// Return type		: BOOL 
BOOL CXFloorWndCtrl::RegClassFloorWnd()
{
	if (!m_nMessageChange)
	{
		//At the first call set the new page's font
		m_nMessageChange = RegisterWindowMessage(MessageChange);
		return TRUE;
	}
	return FALSE;
}

// Function name	: CXFloorWndCtrl::GetActivePage
// Description	    : Return the active page
// Return type		: CFloorPageObject* 
CFloorPageObject* CXFloorWndCtrl::GetActivePage()
{
	return m_pActivePage;
}

// Function name	: CXFloorWndCtrl::GetRectClient
// Description	    : Return the emtpy rect of this
// Return type		: CRect 
CRect CXFloorWndCtrl::GetRectClient()
{
	return m_rectClient;
}

// Function name	: CXFloorWndCtrl::OnSize
// Description	    : Call to recall all height's page
// Return type		: void 
// Argument         : UINT nType
// Argument         : int cx
// Argument         : int cy
void CXFloorWndCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	RecalcLayout();
	if (CFloorPageObject* pPage = GetActivePage())
		pPage->SetRectClient(GetRectClient());

}

// Function name	: CXFloorWndCtrl::ActivatePage
// Description	    : Activate the page nIndex.
// Return type		: BOOL 
// Argument         : int nIndex
BOOL CXFloorWndCtrl::ActivatePage(int nIndex)
{
	if (CFloorPageObject* pPage = GetPage(nIndex))
		if (pPage != GetActivePage())
		{
			pPage->PrepareToScroll();
			if (m_bAsPage)
				if (pPage->IsPullUp())
					return PullDownPages(nIndex);
				else
					return PullUpPages(nIndex);
			else
			{
				// If this is label ...
				Move(PtrPageToIndex(pPage),TRUE);
				RecalcLayout();
				OnActivatePage(pPage);
			}
			pPage->EndScroll();
			if (CWnd* pWnd = pPage->GetWindow())
				if (::IsWindow(pWnd->m_hWnd))
					pWnd->SetFocus();
		}
	return FALSE;
}

// Function name	: CXFloorWndCtrl::ActivatePage
// Description	    : Activate the page with name lpszPageName
// Return type		: BOOL 
// Argument         : LPCTSTR lpszPageName
BOOL CXFloorWndCtrl::ActivatePage(LPCTSTR lpszPageName)
{
	return ActivatePage(PtrPageToIndex(GetPage(lpszPageName)));
}

// Function name	: CXFloorWndCtrl::PullDownPages
// Description	    : Pull down all pages, that follow nIndex page
// Update			: Version 1.01
// Return type		: BOOL 
// Argument         : CFloorPageObject * pPage
BOOL CXFloorWndCtrl::PullDownPages(int nIndex)
{
	if (CFloorPageObject* pPage = GetPage(nIndex))
		if (pPage->IsPullUp())
		{
			Move(nIndex, TRUE);
			for (int i = nIndex + 1; i < GetCountPage() && GetPage(i)->IsPullUp() ; i++)
				GetPage(i)->m_bPullUp = FALSE;
			RecalcLayout();
			OnActivatePage(pPage);
		}
	return FALSE;
}

// Function name	: CXFloorWndCtrl::PullDownPages
// Description	    : Pull up all pages, that ? nIndex page
// Update			: Version 1.01
// Return type		: BOOL 
// Argument         : CFloorPageObject * pPage
BOOL CXFloorWndCtrl::PullUpPages(int nIndex)
{
	if (::IsWindow(m_hWnd))
		if (CFloorPageObject* pPage = GetPage(nIndex))
			if (pPage->IsPullDown())
			{
				Move(nIndex, FALSE);
				for (int i = nIndex; (i >= 0) && (GetPage(i)->IsPullDown()); i--)
					GetPage(i)->m_bPullUp = TRUE;
				RecalcLayout();
				OnActivatePage(pPage);
			}
	return FALSE;
}

// Function name	: CXFloorWndCtrl::PtrPageToIndex
// Description	    : Return position from m_arPages, of pPage
// Return type		: int 
// Argument         : CFloorPageObject * pPage
int CXFloorWndCtrl::PtrPageToIndex(CFloorPageObject * pPage)
{
	for (int i = 0; i < GetCountPage(); i++)
		if ((DWORD)GetPage(i) == (DWORD)pPage)
			return i;
	return -1;
}

// Function name	: CXFloorWndCtrl::Move
// Description	    : Scroll window from page nIndex, down or up
// Return type		: void 
// Argument         : int nIndex
// Argument         : BOOL bDown
void CXFloorWndCtrl::Move(int nIndex, BOOL bDown)
{
	if (::IsWindow(m_hWnd))
		if (::IsWindowVisible(m_hWnd))
			if (m_bAnimation)
			{
				HANDLE hThread = ::GetCurrentThread();
				int tPriority = ::GetThreadPriority(hThread);
				::SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
				// Before I tryed to set highest priority to this thread,
				// because follows a critical section. At the end of functions, I will retrieve
				// the priority of current thread.

				CFloorPageObject* pPage = GetPage(nIndex);
				ASSERT (pPage);
				if (pPage != m_pActivePage)
				{
					CRect rClient; GetClientRect(rClient);
					CRect rScroll(rClient);
					int dyScroll = NULL;
					if (bDown)
					{
						rScroll.top = GetPage(nIndex)->m_rect.bottom;
						rScroll.bottom = m_rectClient.bottom;
						dyScroll = rScroll.bottom  - rScroll.top;
						if (m_bAsPage)
							for (int i = nIndex + 1; (i < GetCountPage()) && GetPage(i)->IsPullUp(); i++)
								dyScroll -= GetPage(i)->m_rect.Height() + 1;
					}
					else
					{
						rScroll.top = m_rectClient.top;
						rScroll.bottom = GetPage(nIndex)->m_rect.bottom + 1;
						dyScroll = rScroll.bottom  - rScroll.top;
						if (m_bAsPage)
							for (int i = nIndex; (i >=0 ) && GetPage(i)->IsPullDown(); i--)
								dyScroll -= GetPage(i)->m_rect.Height() + 1;
					}
					int nStep = 5;
					int nWhere = bDown ? nStep : -nStep;
					pPage->SetRectClient(m_rectClient);
					CBitmap* pBitmap = Preview(pPage->GetWindow());
					int tScroll = 0, dy = 0;
					for (int s = 0; s < dyScroll ; s += nStep)
					{
						dy = bDown ? max(0,min(nWhere,dyScroll-s)) : min(nWhere,dyScroll-s);
						::ScrollWindow(m_hWnd, 0, dy ,NULL,rScroll);
						tScroll += abs(dy);
						CDC* pDC = GetDC();
						CDC dcMem;
						if (dcMem.CreateCompatibleDC(pDC))
						{
							COLORREF colorBkGnd = TranslateColor(GetBackColor());
							CBrush brBkGnd(colorBkGnd);
							CBrush* pOldBrush = pDC->SelectObject(&brBkGnd);
							CBitmap* pOldBitmap = dcMem.SelectObject(pBitmap);
							if (bDown)
							{
								CRect rCS(CPoint(m_rectClient.left ,rScroll.top), CSize(m_rectClient.Width() , tScroll));
								pDC->PatBlt(rScroll.left,rScroll.top, rCS.left - rScroll.left, rCS.bottom - rScroll.top, PATCOPY);
								pDC->BitBlt(rCS.left ,rCS.top, rCS.Width() , rCS.Height(), &dcMem, 0, m_rectClient.Height() - tScroll, SRCCOPY);
								pDC->PatBlt(rCS.right ,rCS.top, rScroll.right - rCS.right, rCS.bottom - rScroll.top, PATCOPY);
							}
							else
							{
								CRect rCS(CPoint(m_rectClient.left ,rScroll.bottom - tScroll), CSize(m_rectClient.Width() , tScroll));
								pDC->PatBlt(rScroll.left,rCS.top, rCS.left - rScroll.left, rCS.Height(), PATCOPY);
								pDC->BitBlt(rCS.left ,rCS.top, rCS.Width() , rCS.Height(), &dcMem, 0, 0 , SRCCOPY);
								pDC->PatBlt(rCS.right,rCS.top, rScroll.right - rCS.right, rCS.Height(), PATCOPY);
							}
							dcMem.SelectObject(pOldBitmap);
							pDC->SelectObject(pOldBrush);
						}

						ReleaseDC(pDC);
						if (m_nSleep > 0)
							Sleep(m_nSleep * MulSleep);
					}
					delete pBitmap;
				}
				::SetThreadPriority(hThread, tPriority);
			}
}

// Function name	: CXFloorWndCtrl::OnLButtonDown
// Description	    : Call when user click the mouse
// Update			: Version 1.01
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CXFloorWndCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();
	if (CFloorPageObject* pPage = GetPageFromPoint(point))
	{
		int nIndex = PtrPageToIndex(pPage);
		if (pPage != GetActivePage())
		{
			if (pPage->IsPullUp())
				PullDownPages(nIndex);
			else
				PullUpPages(nIndex);
		}
		else
			FireClickOnActivePage(nIndex);
	}
		
	COleControl::OnLButtonDown(nFlags, point);
}

void CXFloorWndCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	COleControl::OnLButtonUp(nFlags, point);
}

void CXFloorWndCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CFloorPageObject* pPage = GetPageFromPoint(point);
	if (pPage)
		if (m_pFocusPage != pPage)
			if (pPage != m_pActivePage)
				pPage->OnFocus();
	if (m_pFocusPage)
		if (m_pFocusPage != pPage)
			m_pFocusPage->Invalidate(TRUE);
	m_pFocusPage = pPage;

	// Try to put a timer to erase the focused page when cursor outrun the area of this window
	KillTimer(IDTIMERERASEFOCUS);
	if (m_pFocusPage)
		SetTimer(IDTIMERERASEFOCUS, UPDATEIDTIMERERASEFOCUS, NULL);
	
	COleControl::OnMouseMove(nFlags, point);
}

// Function name	: CXFloorWndCtrl::GetPageFromPoint
// Description	    : Return page from point
// Return type		: CFloorPageObject* 
// Argument         : CPoint point
CFloorPageObject* CXFloorWndCtrl::GetPageFromPoint(CPoint point)
{
	for (int i = 0; i < GetCountPage(); i++)
		if (GetPage(i)->PtInObject(point))
			return GetPage(i);
	return NULL;
}

// Function name	: CXFloorWndCtrl::DeletePage
// Description	    : Delete the page with index nIndex. Call ActivatePage after
// Update			: Version 1.01
// Return type		: BOOL 
// Argument         : int nIndex
BOOL CXFloorWndCtrl::DeletePage(int nIndex)
{
	if (CFloorPageObject* pPage = GetPage(nIndex))
	{
		BOOL bDeleteActivePage = pPage == GetActivePage();
		delete pPage;
		m_pArPage->RemoveAt(nIndex);
		if (bDeleteActivePage)
			m_pActivePage = NULL;
		PullUpPages(nIndex);
		RecalcLayout();
		if (bDeleteActivePage)
			ActivatePage(max(min(nIndex, GetCountPage()-1),0));
		return TRUE;
	}
	return FALSE;
}

// Function name	: CXFloorWndCtrl::DeletePage
// Description	    : 
// Return type		: BOOL 
// Argument         : LPCTSTR lpszPageName
BOOL CXFloorWndCtrl::DeletePage(LPCTSTR lpszPageName)
{
	return DeletePage(PtrPageToIndex(GetPage(lpszPageName)));
}

// Function name	: CXFloorWndCtrl::OnTimer
// Description	    : Put a timer to erase the focus page if mouse pointer is outside of this window
// Return type		: void 
// Argument         : UINT nIDEvent
void CXFloorWndCtrl::OnTimer(UINT nIDEvent) 
{
	switch (nIDEvent)
	{
		case IDTIMERERASEFOCUS:
		{
			CPoint p; ::GetCursorPos(&p);
			if (this != CWnd::WindowFromPoint(p))
			{
				if (m_pFocusPage)
					m_pFocusPage->Invalidate(TRUE);
				m_pFocusPage = NULL;
				KillTimer(IDTIMERERASEFOCUS);
			}
			break;
		}
		case IDSTARTMOVELABEL:
		{
			KillTimer(IDSTARTMOVELABEL);
			CComboBox* pCombo = (CComboBox*)GetDlgItem(ID_LABELCOMBO);
			int nItem = pCombo->GetCurSel();
			CFloorPageObject* pPage = (CFloorPageObject*)pCombo->GetItemData(nItem);
			ActivatePage(PtrPageToIndex(pPage));
		}
	}
	
	COleControl::OnTimer(nIDEvent);
}

// Function name	: CXFloorWndCtrl::OnEraseBkgnd
// Description	    : Do not erase bkgnd of this control
// Return type		: BOOL 
// Argument         : CDC* pDC
BOOL CXFloorWndCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

// Function name	: CXFloorWndCtrl::AddPage
// Description	    : Add a new Page. Called by interface
// Return type		: short 
// Argument         : LPCTSTR sName
short CXFloorWndCtrl::_AddPage(LPCTSTR sName) 
{
	int nIndex = NULL;
	AddPage(sName, &nIndex);
	return nIndex;
}

// Function name	: CXFloorWndCtrl::_DeletePage
// Description	    : Delete page nIndex. Called by interface
// Return type		: BOOL 
// Argument         : short nIndex
BOOL CXFloorWndCtrl::_DeletePage(short nIndex) 
{
	if (DeletePage(nIndex))
	{
		RecalcLayout();
		Invalidate();
		return TRUE;
	}
	return FALSE;
}

// Function name	: CXFloorWndCtrl::_GetPageName
// Description	    : return the name of page
// Return type		: BSTR 
// Argument         : short nIndex
BSTR CXFloorWndCtrl::_GetPageName(short nIndex) 
{
	CString strResult;
	if (CFloorPageObject* pPage = GetPage(nIndex))
		strResult = pPage->GetName();
	return strResult.AllocSysString();
}

// Function name	: CXFloorWndCtrl::_GetPage
// Description	    : 
// Return type		: short 
// Argument         : LPCTSTR lpszPageName
short CXFloorWndCtrl::_GetPage(LPCTSTR lpszPageName) 
{
	return PtrPageToIndex(GetPage(lpszPageName));
}

// Function name	: CXFloorWndCtrl::_ActivatePage
// Description	    : 
// Return type		: BOOL 
// Argument         : short nIndex
BOOL CXFloorWndCtrl::_ActivatePage(short nIndex) 
{
	ActivatePage(nIndex);
	return TRUE;
}

// Function name	: CXFloorWndCtrl::_AttachWindow
// Description	    : AttachWindow
// Return type		: BOOL 
// Argument         : short nIndex
// Argument         : long hWnd
BOOL CXFloorWndCtrl::_AttachWindow(short nIndex, long pWnd) 
{
	CWnd* pWndClient = (CWnd*)pWnd;
	if (pWndClient)
		if (::IsWindow(pWndClient->m_hWnd))
			if (CFloorPageObject* pPage = GetPage(nIndex))
				{
					pPage->Attach(pWndClient);
					return TRUE;
				}
	return FALSE;
}

// Function name	: CXFloorWndCtrl::_SetPageName
// Description	    : 
// Return type		: BOOL 
// Argument         : short nIndex
// Argument         : LPCTSTR lpszPageName
BOOL CXFloorWndCtrl::_SetPageName(short nIndex, LPCTSTR lpszPageName) 
{
	if (CFloorPageObject* pPage = GetPage(nIndex))	
	{
		pPage->SetName(lpszPageName);
		return TRUE;
	}
	return FALSE;
}

// Function name	: CXFloorWndCtrl::OnAnimationChanged
// Description	    : Called when something is happen eith m_bAnimation
// Return type		: void 
void CXFloorWndCtrl::OnAnimationChanged() 
{
	SetModifiedFlag();
}


void CXFloorWndCtrl::OnSleepChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

void CXFloorWndCtrl::OnSignChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

// Function name	: CXFloorWndCtrl::GetHeight
// Description	    : Get the Height of page nIndex
// Return type		: short 
// Argument         : short nIndex
short CXFloorWndCtrl::GetHeight(short nIndex) 
{
	if (CFloorPageObject* pPage = GetPage(nIndex))	
		return pPage->GetHeight();
	return -1;
}

// Function name	: CXFloorWndCtrl::SetHeight
// Description	    : Set the new height of page nIndex to nNewValue
// Return type		: void 
// Argument         : short nIndex
// Argument         : short nNewValue
void CXFloorWndCtrl::SetHeight(short nIndex, short nNewValue) 
{
	if (CFloorPageObject* pPage = GetPage(nIndex))	
	{
		pPage->SetHeight(nNewValue);
		SetModifiedFlag();
	}
}

// Function name	: CXFloorWndCtrl::GetColor
// Description	    : return the default color of page
// Return type		: OLE_COLOR 
// Argument         : short nIndex
OLE_COLOR CXFloorWndCtrl::GetColor(short nIndex) 
{
	if (CFloorPageObject* pPage = GetPage(nIndex))	
	{
		LOGBRUSH logBrush;
		pPage->m_brBkGnd.GetLogBrush(&logBrush);
		return logBrush.lbColor;
	}
	return RGB(0,0,0);
}

// Function name	: CXFloorWndCtrl::SetColor
// Description	    : Set the new color of background's page
// Return type		: void 
// Argument         : short nIndex
// Argument         : OLE_COLOR nNewValue
void CXFloorWndCtrl::SetColor(short nIndex, OLE_COLOR nNewValue) 
{
	if (CFloorPageObject* pPage = GetPage(nIndex))	
	{
		pPage->SetBkGnd(TranslateColor(nNewValue));
		SetModifiedFlag();
	}
}

// Function name	: CXFloorWndCtrl::OnPagesChanged
// Description	    : 
// Return type		: void 
void CXFloorWndCtrl::OnPagesChanged()
{
	if (m_hWnd)
		if (::IsWindow(m_hWnd))
		{
			BOOL bSAnimation = m_bAnimation;
			m_bAnimation = FALSE;
			int i = 0;
			BOOL cont = TRUE;
			while (cont)
			{
				CString sItem, sName, sUser;
				AfxExtractSubString(sItem, m_sPages, i, _cPagesSeparator);
				AfxExtractSubString(sName, sItem, 0, TCHAR('\\'));
				AfxExtractSubString(sUser, sItem, 1, TCHAR('\\'));
				LPARAM lParam = atol((LPCTSTR)sUser);
				if (cont = !sName.IsEmpty())
				{
					int nItem = i;
					if (CFloorPageObject* pPage = GetPage(nItem))
						pPage->SetName(sName);
					else
						AddPage(sName, &nItem);
					SetUserData(nItem, lParam);
					i++;
				}
			}
			while (DeletePage(i));
			SetModifiedFlag();
			m_bAnimation = bSAnimation;
		}
}

// Function name	: CXFloorWndCtrl::GetUserData
// Description	    : Return the user data attached to a page nIndex
// Return type		: long 
// Argument         : short nIndex
long CXFloorWndCtrl::GetUserData(short nIndex) 
{
	long lResult = -1;
	if (CFloorPageObject* pPage = GetPage(nIndex))
		lResult = pPage->GetUserData();
	return lResult;
}

// Function name	: CXFloorWndCtrl::SetUserData
// Description	    : Set the new user data to a page nIndex
// Return type		: void 
// Argument         : short nIndex
// Argument         : long nNewValue
void CXFloorWndCtrl::SetUserData(short nIndex, long nNewValue) 
{
	long lResult = 0;
	if (CFloorPageObject* pPage = GetPage(nIndex))
		pPage->SetUserData(nNewValue);

	SetModifiedFlag();
}

// Function name	: CXFloorWndCtrl::_Init
// Description	    : 
// Return type		: void 
void CXFloorWndCtrl::_Init() 
{
	RecalcLayout();
	int nIndex = 0;
	CFloorPageObject* pPage = NULL;
	while (pPage = GetPage(nIndex++))
		pPage->SetRectClient(GetRectClient());
}

// Function name	: CXFloorWndCtrl::_GetActivePage
// Description	    : Version 1.01
// Return type		: short 
short CXFloorWndCtrl::_GetActivePage() 
{
	return PtrPageToIndex(m_pActivePage);
}

// Function name	: CXFloorWndCtrl::_GetPagesCount
// Description	    : Version 1.01
// Return type		: long 
long CXFloorWndCtrl::_GetPagesCount() 
{
	return GetCountPage();
}

// Function name	: CXFloorWndCtrl::_IsPage
// Description	    : Version 1.01
// Return type		: BOOL 
// Argument         : short nIndex
BOOL CXFloorWndCtrl::_IsPage(short nIndex) 
{
	return GetPage(nIndex) != NULL;
}

// Function name	: CXFloorWndCtrl::_GetLeftTopPage
// Description	    : Version 1.01
// Return type		: long 
// Argument         : short nIndex
long CXFloorWndCtrl::_GetLeftTopPage(short nIndex) 
{
	if (CFloorPageObject* pPage = GetPage(nIndex))
		return MAKELPARAM(pPage->m_rect.TopLeft().x, pPage->m_rect.TopLeft().y);
	return -1;
}

// Function name	: CXFloorWndCtrl::_GetBottomRightPage
// Description	    : Version 1.01
// Return type		: long 
// Argument         : short nIndex
long CXFloorWndCtrl::_GetBottomRightPage(short nIndex) 
{
	if (CFloorPageObject* pPage = GetPage(nIndex))
		return MAKELPARAM(pPage->m_rect.BottomRight().x, pPage->m_rect.BottomRight().y);
	return -1;
}

// Function name	: CXFloorWndCtrl::WindowProc
// Description	    : Window procedure.
// This is very important for next controls that will be inserted in this control.
// To accepts some messages you need to insert here. See CReflectorWnd class
// Update			: Version 1.01
// Return type		: LRESULT 
// Argument         : UINT message
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CXFloorWndCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	UINT id = (UINT)wParam;
	switch (message)
	{
		case WM_COMMAND:
			{
				id = LOWORD(wParam);
				if ( HIWORD(wParam) == CBN_SELENDOK )
					if ( id == ID_LABELCOMBO )
					{
						SetTimer(IDSTARTMOVELABEL, UPDATEIDSTARTMOVELABEL, NULL);
						break;
					}	
			}
		case WM_NOTIFY:
		case WM_DRAWITEM:
		case WM_MEASUREITEM:
			{
				if (CWnd* pWnd = GetDlgItem((UINT)id))
					if (::IsWindow(pWnd->m_hWnd))
						return pWnd->SendMessage(message, wParam, lParam);
			}
	}
	return COleControl::WindowProc(message, wParam, lParam);
}

// Function name	: CXFloorWndCtrl::SetFont
// Description	    : 
// Return type		: void 
// Argument         : CWnd *pWindow
// Argument         : COleControl *pControlSource
void CXFloorWndCtrl::SetFont(CWnd *pWindow, COleControl *pControlSource)
{
	if (pWindow)
		if (::IsWindow(pWindow->m_hWnd))
			if (pControlSource)
			{
				IFontDisp* pFontDisp = pControlSource->GetFont();
				IFont* pIFont = NULL;
				if (SUCCEEDED(pFontDisp->QueryInterface(IID_IFont, (void**)&pIFont)))
				{
					if (pIFont)
					{
						HFONT hFont = NULL;
						if (SUCCEEDED(pIFont->get_hFont(&hFont)))
							pWindow->SetFont(CFont::FromHandle(hFont));
					}
					pFontDisp->Release();
				}
			}
}

// Function name	: CXFloorWndCtrl::RefreshFontLabel
// Description	    : Called when something are change into font page
// Return type		: void 
// Argument         : COleControl *pControl
void CXFloorWndCtrl::RefreshFontLabel(COleControl *pControl)
{
	SetFont(GetComboBox(), pControl);
	SetFont(GetLabelControl(), pControl);
}

// Function name	: CXFloorWndCtrl::ChangeHeightLabel
// Description	    : return the rect of the page
// Return type		: void 
CRect CXFloorWndCtrl::ChangeHeightLabel(CSize s)
{
	//This function must be called only if style of control is floor
	CComboBox* pCombo = GetComboBox();
	ASSERT (pCombo);
	CTLabelComboBox* pLabelControl = GetLabelControl();
	ASSERT (pLabelControl);
	// Just do this
	pCombo->MoveWindow(0,0, s.cx, m_nDYCombo);
	CRect rect; pCombo->GetClientRect(rect);
	m_nDYLabel = rect.Height() + 2;
	CRect rResult = CRect(CPoint(0,0), CSize(s.cx, m_nDYLabel));
	pLabelControl->MoveWindow(rResult);
	return rResult;
}

// Function name	: CXFloorWndCtrl::PrepareChangeStyle
// Description	    : 
// Return type		: void 
void CXFloorWndCtrl::PrepareChangeStyle()
{
	if (m_bAsPage)
	{
		// The new style is floor
		if (GetComboBox())
			GetComboBox()->DestroyWindow();
		if (GetLabelControl())
			GetLabelControl()->DestroyWindow();

		ASSERT( !GetComboBox() );
	}
	else
		if (m_hWnd)
		{
			if (!GetComboBox())
			{
				// The new style is label
				VERIFY(m_cbPage.Create(CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, ID_LABELCOMBO));
				m_lbPage.RegClassLabelEdit();
				VERIFY(m_lbPage.Create(_T("TLabelEdit"), _T(""), WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, ID_LABEL));
				m_lbPage.Init();
				m_lbPage.AttachWindow(&m_cbPage);
				OnBackColorChanged();
			}
			else
			{
				m_cbPage.ResetContent();
				m_lbPage.SetWindowText(NULL);
			}
			RefreshFontLabel(this);
			ASSERT( GetComboBox() );
		}
}

// Function name	: CXFloorWndCtrl::OnAsPageChanged
// Description	    : When user changes the style of control
// Return type		: void 
void CXFloorWndCtrl::OnAsPageChanged() 
{
	// Here we will remove old array of pages and will put the new one.
	CArrayPage * pArPages = new CArrayPage();
	BOOL bAutoDetach = CFloorPageObject::m_bAutoDetach;
	CFloorPageObject::m_bAutoDetach = FALSE;
	PrepareChangeStyle();
	int nActivePage = -1;
	for (int i = 0; i < m_pArPage->GetSize(); i++)
	{
		CFloorPageObject* pPage = (*m_pArPage)[i];
		CFloorPageObject* pNewPage = NewPage(m_bAsPage, pPage->GetName());
		pNewPage->m_pWndClient = pPage->m_pWndClient;
		pArPages->Add(pNewPage);
		if (pPage == m_pActivePage)
		{
			nActivePage = i;
			m_pActivePage->OnDeactivateObject();
			m_pActivePage = NULL;
		}
		delete pPage;
	}
	// Set the new one array of pages
	delete m_pArPage;
	m_pArPage = pArPages;
	ActivatePage(nActivePage);
	RecalcLayout();
	CFloorPageObject::m_bAutoDetach = bAutoDetach;
	SetModifiedFlag();
}

// Function name	: CXFloorWndCtrl::NewPage
// Description	    : Create a new kind of page
// Return type		: CFloorPageObject* 
// Argument         : BOOL bAsPage
// Argument         : LPCTSTR lpszPageName
CFloorPageObject* CXFloorWndCtrl::NewPage(BOOL bAsPage, LPCTSTR lpszPageName)
{
	return (bAsPage ? new CFloorPageObject(this, lpszPageName) :  new CFloorLabelObject(this, lpszPageName));
}

// Function name	: CXFloorWndCtrl::OnFontChanged
// Description	    : Refresh the font into CFloorLabelObject
// Return type		: void 
void CXFloorWndCtrl::OnFontChanged() 
{
	RefreshFontLabel(this);
	RecalcLayout();
	
	COleControl::OnFontChanged();
}

// Function name	: CXFloorWndCtrl::OnCreate
// Description	    : Load the pages into control
// Return type		: int 
// Argument         : LPCREATESTRUCT lpCreateStruct
int CXFloorWndCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	PrepareChangeStyle();
	OnPagesChanged();
	
	return 0;
}

// Function name	: CXFloorWndCtrl::StyleAs
// Description	    : 
// Return type		: void 
// Argument         : BOOL bAsFloor
void CXFloorWndCtrl::StyleAs(BOOL bAsFloor) 
{
	m_bAsPage = bAsFloor;
	OnAsPageChanged();
}

// Function name	: CXFloorWndCtrl::GetHWnd
// Description	    : 
// Return type		: long 
// Argument         : long nIndex
long CXFloorWndCtrl::GetHWnd(long nIndex) 
{
	if (CFloorPageObject* pPage = GetPage(nIndex))
		if (CWnd* pWnd = pPage->GetWindow())
			return (long)pWnd->m_hWnd;
	return NULL;
}

// Function name	: CXFloorWndCtrl::GetComboBox
// Description	    : return NULL if combobox is not created....
// Return type		: CComboBox* 
CComboBox* CXFloorWndCtrl::GetComboBox()
{
	if (::IsWindow(m_cbPage.m_hWnd))
		return &m_cbPage;
	return NULL;
}

// Function name	: CXFloorWndCtrl::GetLabelControl
// Description	    : return NULL if labelcontrol is not created....
// Return type		: CTLabelComboBox* 
CTLabelComboBox* CXFloorWndCtrl::GetLabelControl()
{
	if (::IsWindow(m_lbPage.m_hWnd))
		return &m_lbPage;
	return NULL;
}

// Function name	: CXFloorWndCtrl::Lookup
// Description	    : Look for page pLabelObject in combobox
// Return type		: int 
// Argument         : CFloorLabelObject *pLabelObject
int CXFloorWndCtrl::Lookup(CFloorLabelObject *pLabelObject)
{
	CComboBox* pComboBox = GetComboBox();
	int i = 0, n = pComboBox->GetCount();
	for (i = 0; (i < n) && (((DWORD)pComboBox->GetItemData(i)) != (DWORD)pLabelObject); i++);
	return i < n ? i : -1;
}

// Function name	: CXFloorWndCtrl::OnBackColorChanged
// Description	    : 
// Return type		: void 
void CXFloorWndCtrl::OnBackColorChanged() 
{
	if (CBrush* pBrush = &CTLabelEdit::m_brBkGnd)
	{
		pBrush->DeleteObject();
		pBrush->CreateSolidBrush(TranslateColor(GetBackColor()));
		if (CWnd* pLabel = GetLabelControl())
		{
			::SetClassLong(pLabel->m_hWnd, GCL_HBRBACKGROUND, (long)(HBRUSH)*pBrush);
			pLabel->Invalidate();
		}
	}
	
	COleControl::OnBackColorChanged();
}
