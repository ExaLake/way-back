/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/13/98 5:26:24 PM
  Comments: XPropertiesWndPpg.cpp : Implementation of the CXPropertiesWndPropPage property page class.
 ************************************/


#include "stdafx.h"
#include "XPropertiesWnd.h"
#include "XPropertiesWndPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CXPropertiesWndPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CXPropertiesWndPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CXPropertiesWndPropPage)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CXPropertiesWndPropPage, "XPROPERTIESWND.XPropertiesWndPropPage.1",
	0x7b914a5c, 0x6271, 0x11d2, 0x86, 0xb8, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9)


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndPropPage::CXPropertiesWndPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CXPropertiesWndPropPage

BOOL CXPropertiesWndPropPage::CXPropertiesWndPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_XPROPERTIESWND_PREVIEW_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndPropPage::CXPropertiesWndPropPage - Constructor

CXPropertiesWndPropPage::CXPropertiesWndPropPage() :
	COlePropertyPage(IDD, IDS_XPROPERTIESWND_PPG_PREVIEW_CAPTION)
{
	//{{AFX_DATA_INIT(CXPropertiesWndPropPage)
	//}}AFX_DATA_INIT
	m_nRenamePage = -1;
}


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndPropPage::DoDataExchange - Moves data between page and properties

void CXPropertiesWndPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CXPropertiesWndPropPage)
	DDX_Control(pDX, IDC_SLIDER_ADDDEL, m_sldAddDel);
	DDX_Control(pDX, IDC_XFLOORWNDCTRL_PAGES, m_xFloorWndPages);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
	m_xFloorWndPages.DataExchange(pDX);
	m_sldAddDel.SetRange(0,6);
	m_sldAddDel.SetPos(m_xFloorWndPages.GetPagesCount());
}


/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndPropPage message handlers

CXPropertiesWndPropPage* CXPropertiesWndPropPage::m_pThis = NULL;

BOOL CXPropertiesWndPropPage::OnInitDialog() 
{

	COlePropertyPage::OnInitDialog();

	m_edtRename.Create(ES_WANTRETURN | ES_MULTILINE | ES_CENTER | WS_CHILD , CRect(0,0,0,0), &m_xFloorWndPages, 1000);
	m_edtRename.SetFont(GetFont());

/*	ASSERT (m_pThis == NULL);
	m_pThis = this;
	m_hHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProcHookParent, AfxGetInstanceHandle(), GetWindowThreadProcessId(GetParent()->m_hWnd, NULL));
	Refresh();
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Function name	: CXPropertiesWndPropPage::Refresh
// Description	    : Refresh color, etc...
// Return type		: void 
void CXPropertiesWndPropPage::Refresh()
{
	ULONG pnObjects = NULL;
	LPDISPATCH* lpDispatch = GetObjectArray(  &pnObjects );
	if (pnObjects)
	{
		COleDispatchDriver oleDispatch;
		oleDispatch.AttachDispatch(lpDispatch[0]);
		OLE_COLOR oleColor;
		oleDispatch.GetProperty(DISPID_BACKCOLOR, VT_I4, &oleColor);
		m_xFloorWndPages.SetBackColor(oleColor);
		oleDispatch.DetachDispatch();
	}
}

// Function name	: CXPropertiesWndPropPage::CallWndProcHook
// Description	    : Hook procedure. Wait to m_pThis->GetParent() receives WM_WINDOWPOSCHANGED and WM_DESTROY messages
// Return type		: LRESULT 
// Argument         : int nCode
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CXPropertiesWndPropPage::CallWndProcHookParent(int nCode, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = CallNextHookEx(m_pThis->m_hHook, nCode, wParam, lParam);

	if (nCode >= 0)
		if (m_pThis->GetParent())
		{
			CWPSTRUCT* pMessage = (CWPSTRUCT*)lParam;
			if (pMessage->hwnd == m_pThis->GetParent()->m_hWnd)
				switch (pMessage->message)
				{
					case WM_WINDOWPOSCHANGED:
						{
							LPWINDOWPOS lpWindowPos = (LPWINDOWPOS)pMessage->lParam;
							if (lpWindowPos->flags | SWP_SHOWWINDOW)
								m_pThis->Refresh();
							break;
						}
					case WM_DESTROY:
						{
							UnhookWindowsHookEx(m_pThis->m_hHook);
							m_pThis = NULL;
							break;
						}
				}
		}
	return lResult;
}

// Function name	: CXPropertiesWndPropPage::AddPage
// Description	    : 
// Return type		: void 
void CXPropertiesWndPropPage::AddPage()
{
	m_xFloorWndPages.AddPage(_T("Noname"));
}

// Function name	: CXPropertiesWndPropPage::DeletePage
// Description	    : 
// Return type		: void 
void CXPropertiesWndPropPage::DeletePage()
{
	int nA = m_xFloorWndPages.GetActivePage();
	if (nA >= 0)
		m_xFloorWndPages.DeletePage(nA);
}

// Function name	: CXPropertiesWndPropPage::RenamePage
// Description	    : 
// Return type		: void 
// Argument         : int nIndex
void CXPropertiesWndPropPage::RenamePage(int nIndex)
{
	if (nIndex >= 0)
	{
		CString newName;
		m_edtRename.GetWindowText(newName);
		if (!newName.IsEmpty())
			if (newName != m_xFloorWndPages.GetPageName(nIndex))
			{
				m_xFloorWndPages.SetPageName(nIndex , newName);
				m_xFloorWndPages.Invalidate();
				m_nRenamePage = -1;
				SetModifiedFlag();
			}
	}
}

// Function name	: CXPropertiesWndPropPage::OnVScroll
// Description	    : 
// Return type		: void 
// Argument         : UINT nSBCode
// Argument         : UINT nPos
// Argument         : CScrollBar* pScrollBar
void CXPropertiesWndPropPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ((LPARAM)pScrollBar == (LPARAM)&m_sldAddDel)	
	{
		int cPages = m_sldAddDel.GetPos(), i = 0;
		for (i = 0; i < cPages; i++)
			if (!m_xFloorWndPages.IsPage(i))
			{
				CString page;
				page.Format(_T("Page %i"), i + 1);
				m_xFloorWndPages.AddPage(page);
			}
		while ( i < m_xFloorWndPages.GetPagesCount() )
			m_xFloorWndPages.DeletePage(i);
		m_xFloorWndPages.Init();
		SetModifiedFlag();
	}
	
	COlePropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

BEGIN_EVENTSINK_MAP(CXPropertiesWndPropPage, COlePropertyPage)
    //{{AFX_EVENTSINK_MAP(CXPropertiesWndPropPage)
	ON_EVENT(CXPropertiesWndPropPage, IDC_XFLOORWNDCTRL_PAGES, 2 /* ClickOnActivePage */, OnClickOnActivePageXfloorwndctrlPages, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

// Function name	: CXPropertiesWndPropPage::OnClickOnActivePageXfloorwndctrlPages
// Description	    : Start to rename page
// Return type		: void 
// Argument         : short nIndex
void CXPropertiesWndPropPage::OnClickOnActivePageXfloorwndctrlPages(short nIndex) 
{
	ASSERT (m_xFloorWndPages.IsPage(nIndex));
	long pTopLeft = m_xFloorWndPages.GetLeftTopPage(nIndex);
	long pBottomRight = m_xFloorWndPages.GetBottomRightPage(nIndex);
	m_nRenamePage = nIndex;
	CRect rect(CPoint(LOWORD(pTopLeft),HIWORD(pTopLeft)), CPoint(LOWORD(pBottomRight),HIWORD(pBottomRight)));
	rect.InflateRect(-2,-2);
	m_edtRename.Do(rect,m_xFloorWndPages.GetPageName(nIndex));
}

// Function name	: CXPropertiesWndPropPagePreTranslateMessage
// Description	    : 
// Return type		: BOOL 
// Argument         : MSG* pMsg
BOOL CXPropertiesWndPropPage::PreTranslateMessage( MSG* pMsg )
{
	if (pMsg->message == WM_KEYDOWN &&
		(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_CANCEL))
		{
			return TRUE;
		}
	return COlePropertyPage::PreTranslateMessage(pMsg);
}
