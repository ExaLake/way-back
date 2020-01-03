/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/21/98 12:26:29 PM
  Comments: ItemToolTipCtrl.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "ItemToolTipCtrl.h"
#include "PageListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemToolTipCtrl

// Function name	: CItemToolTipCtrl::CItemToolTipCtrl
// Description	    : Default constructor
// Return type		: 
CItemToolTipCtrl::CItemToolTipCtrl()
{
	EnableAutomation();
	m_pParent = NULL;
	m_bActivate = NULL;
}

// Function name	: CItemToolTipCtrl::~CItemToolTipCtrl
// Description	    : virtual destructor
// Return type		: 
CItemToolTipCtrl::~CItemToolTipCtrl()
{
}

void CItemToolTipCtrl::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CToolTipCtrl::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CItemToolTipCtrl, CToolTipCtrl)
	//{{AFX_MSG_MAP(CItemToolTipCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CItemToolTipCtrl, CToolTipCtrl)
	//{{AFX_DISPATCH_MAP(CItemToolTipCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IItemToolTipCtrl to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {7C49E333-68BA-11D2-86C6-0040055C08D9}
static const IID IID_IItemToolTipCtrl =
{ 0x7c49e333, 0x68ba, 0x11d2, { 0x86, 0xc6, 0x0, 0x40, 0x5, 0x5c, 0x8, 0xd9 } };

BEGIN_INTERFACE_MAP(CItemToolTipCtrl, CToolTipCtrl)
	INTERFACE_PART(CItemToolTipCtrl, IID_IItemToolTipCtrl, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemToolTipCtrl message handlers

// Function name	: CItemToolTipCtrl::Create
// Description	    : Create function
// Return type		: BOOL 
// Argument         : CPageListCtrl* pParent
BOOL CItemToolTipCtrl::Create(CPageListCtrl * pParent)
{
	if (CToolTipCtrl::Create((CWnd*)pParent, TTS_ALWAYSTIP))
		// We don't use this string
		if (AddTool((CWnd*)pParent, IDS_STRING_TOOLTIP))
		{
			m_pParent = pParent;
			Activate(TRUE);
			EnableToolTips(TRUE);
			SetDelayTime(0);
			// Update the tooltip text to be NULL when we start.
			UpdateTipText((LPCTSTR)NULL,m_pParent);
			return TRUE;
		}
	return FALSE;
}

// Function name	: CItemToolTipCtrl::WindowProc
// Description	    : Catch WM_MOUSEMOVE for checking the lenght of GetDefaultValue
// Return type		: LRESULT 
// Argument         : UINT message
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CItemToolTipCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
		case TTM_RELAYEVENT:
			{
				if (GetFocus() == m_pParent)
					switch (((LPMSG)lParam)->message)
					{
						case WM_MOUSEMOVE:
						{
							int nItem = m_pParent->HitTest(CPoint(LOWORD(((LPMSG)lParam)->lParam), HIWORD(((LPMSG)lParam)->lParam)));
							BOOL bNeed = FALSE;
							CString tToolTip;
							if (Activate(bNeed = NeedToolTip(nItem, tToolTip)))
								if (bNeed)
									UpdateTipText(tToolTip, m_pParent);
							break;
						}
						case WM_LBUTTONDOWN:
						{
							Activate(FALSE);
							break;
						}
					}
				break;
			}
	}
	
	return CToolTipCtrl::WindowProc(message, wParam, lParam);
}

// Function name	: CItemToolTipCtrl::Activate
// Description	    : 
// Return type		: BOOL 
// Argument         : BOOL bActivate
BOOL CItemToolTipCtrl::Activate(BOOL bActivate)
{
	if ((int)m_bActivate != (int)bActivate)
	{
		m_bActivate = bActivate;
		CToolTipCtrl::Activate(bActivate);
		return TRUE;
	}
	m_bActivate = bActivate;
	return FALSE;
}

// Function name	: CItemToolTipCtrl::NeedToolTip
// Description	    : Check if item nItem need a tool tip
// Return type		: BOOL 
// Argument         : int nItem
BOOL CItemToolTipCtrl::NeedToolTip(int nItem, CString& item)
{
	BOOL bResult = FALSE;
	if (nItem >= 0)
	{
		item = m_pParent->GetDefaultValue(nItem);
		if (!item.IsEmpty())
		{
			CDC* pDC = m_pParent->GetDC();
			CFont* pFont = pDC->SelectObject(m_pParent->GetFont());
			bResult = pDC->GetTextExtent(item).cx > m_pParent->GetLastRect(nItem).Width();
			pDC->SelectObject(pFont);
			m_pParent->ReleaseDC(pDC);
		}
	}
	return bResult;
}

