/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/16/98 9:46:06 AM
  Comments: DropListBox.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "DropListBox.h"
#include "PageListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropListBox

// Function name	: CDropListBox::CDropListBox
// Description	    : Default consturctor
// Return type		: 
CDropListBox::CDropListBox()
{
	m_pNotifyClass = NULL;
	m_bCancel = FALSE;
	m_nSelectedItem = -1;
}

// Function name	: CDropListBox::~CDropListBox
// Description	    : Virtual destructor
// Return type		: 
CDropListBox::~CDropListBox()
{
}


BEGIN_MESSAGE_MAP(CDropListBox, CListBox)
	//{{AFX_MSG_MAP(CDropListBox)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropListBox message handlers
#define IDLISTBOX 1000

// Function name	: CDropListBox::_Create
// Description	    : Create the list box.
// Return type		: BOOL 
// Argument         : CControlsWnd_CComboBox* pNotifyClass
CWnd* CDropListBox::Create(CControlsWnd_CComboBox* pNotifyClass)
{
	// Do not call this twice
	ASSERT (!::IsWindow(GetSafeHwnd()));
//	if (CListBox::Create(WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_BORDER ,CRect(0,0,0,0), GetDesktopWindow(), IDLISTBOX))
	if (CWnd::CreateEx(WS_EX_TOOLWINDOW, _T("LISTBOX"), NULL, WS_POPUP | WS_VSCROLL | WS_HSCROLL | WS_BORDER , 0,0,0,0 , pNotifyClass->GetWindowNotify()->m_hWnd, NULL))
	{
		m_pNotifyClass = pNotifyClass;
//		ModifyStyleEx(0, WS_EX_TOOLWINDOW);
		SetFont(m_pNotifyClass->GetWindowNotify()->GetFont());
		return this;
	}
	return NULL;
}

// Function name	: CDropListBox::Load
// Description	    : Load Items into list box
// Return type		: void 
// Argument         : LPCTSTR lpszItems
// Argument         : TCHAR c
void CDropListBox::Load(LPCTSTR lpszItems, TCHAR c)
{
	ASSERT (m_pNotifyClass);
	ResetContent();
	LPTSTR lpszItem = (LPTSTR)lpszItems;
	while (lpszItem)
	{
		LPTSTR lpszNItem = _tcschr(lpszItem, c);
		AddString(lpszNItem ? CString(lpszItem, lpszNItem - lpszItem) : CString(lpszItem));
		lpszItem = lpszNItem ? lpszNItem + 1 : NULL;
	}
}

// Function name	: CDropListBox::Show
// Description	    : Show the window
// Return type		: BOOL 
// Argument         : CRect rect
void CDropListBox::Show(CRect rect, int nLines)
{
	// You must call Load function before
	ASSERT(::IsWindow(GetSafeHwnd()));
	{
		nLines = abs(nLines);
		m_pNotifyClass->GetWindowNotify()->ClientToScreen(rect);
		int h = GetItemHeight(0); h = h == LB_ERR ? 16 : h;
		int nDY = max(1,min(nLines, GetCount())) * (h + 1);
		CRect rMove(rect);
		rMove.bottom = rMove.top + nDY;
		MoveWindow(rMove);
		GetWindowRect(rMove);
		nDY = rMove.Height();
		if (nDY + rect.bottom < GetSystemMetrics(SM_CYSCREEN))
		{
			rect.top = rect.bottom;
			rect.bottom = rect.top + nDY;
		}
		else
		{
			rect.bottom = rect.top;
			rect.top = rect.bottom - nDY;
		}
		MoveWindow(rect);
		SetWindowPos(&CWnd::wndTopMost,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(SW_SHOW);
		SetFocus();
		SetCapture();
	}
}

// Function name	: CDropListBox::OnMouseMove
// Description	    : MouseMove
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CDropListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rect; GetClientRect(rect);
	if (rect.PtInRect(point))
	{
		BOOL bOutside = TRUE;
		int nItem  = ItemFromPoint(point, bOutside);
		if (nItem != GetCurSel())
			SetCurSel(nItem);
	}
	
	CListBox::OnMouseMove(nFlags, point);
}

// Function name	: CDropListBox::OnLButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CDropListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListBox::OnLButtonDown(nFlags, point);

	CRect rectClient; GetClientRect(rectClient);
	CRect rectWindow; GetWindowRect(rectWindow);
	CPoint pointScreen(point);
	ClientToScreen(&pointScreen);
	LPARAM lPoint = MAKELPARAM(pointScreen.x, pointScreen.y);
	UINT ht = SendMessage(WM_NCHITTEST,0,lPoint);
	if ((!rectWindow.PtInRect(pointScreen)) || (ht == HTCLIENT))
	{
		Close(ht != HTCLIENT);
		return;
	}
	// ASSERT(rectWindow.PtInRect(pointScreen))
	ReleaseCapture();
	SendMessage(WM_NCLBUTTONDOWN, ht, lPoint);
	SetCapture();
}

// Function name	: CDropListBox::OnKeyDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nChar
// Argument         : UINT nRepCnt
// Argument         : UINT nFlags
void CDropListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_RETURN:
		case VK_CANCEL:
			{
				Close(nChar == VK_CANCEL);
				return;
			}
	}
	
	CListBox::OnKeyDown(nChar, nRepCnt, nFlags);

	SelChange();
}

// Function name	: CDropListBox::Close
// Description	    : 
// Return type		: void 
// Argument         : BOOL bCancel
void CDropListBox::Close(BOOL bCancel)
{
	m_bCancel = bCancel;
	SelChange();
	// m_nSelectedItem este valid doar daca m_bCancel = FALSE;
	if (m_pNotifyClass)
		m_pNotifyClass->Close(m_bCancel);
}

// Function name	: CDropListBox::SelChange
// Description	    : Selection is change
// Return type		: void 
void CDropListBox::SelChange()
{
	if (m_nSelectedItem != GetCurSel())
	{
		m_nSelectedItem = GetCurSel();
		CString text; GetText(m_nSelectedItem, text);
		m_pNotifyClass->OnSelectItem(text, m_nSelectedItem);
	}
}

// Function name	: CDropListBox::OnKillFocus
// Description	    : 
// Return type		: void 
// Argument         : CWnd* pNewWnd
void CDropListBox::OnKillFocus(CWnd* pNewWnd) 
{
	CListBox::OnKillFocus(pNewWnd);
	
	m_pNotifyClass->Close(TRUE);
	
}
