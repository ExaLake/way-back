/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/16/98 5:52:55 PM
  Comments: DropEdit.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "DropEdit.h"
#include "ControlsWnd.h"
#include "PageListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDEDITBOX 1001

/////////////////////////////////////////////////////////////////////////////
// CDropEdit

// Function name	: CDropEdit::CDropEdit
// Description	    : default Constuctor
// Return type		: 
CDropEdit::CDropEdit():m_brush(RGB(255,255,255))
{
}

// Function name	: CDropEdit::~CDropEdit
// Description	    : virtual destructor
// Return type		: 
CDropEdit::~CDropEdit()
{
}


BEGIN_MESSAGE_MAP(CDropEdit, CEdit)
	//{{AFX_MSG_MAP(CDropEdit)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropEdit message handlers

// Function name	: CDropEdit::Create
// Description	    : Create this class 
// Return type		: CWnd* 
// Argument         : CControlsWnd * pNotifyClass
CWnd* CDropEdit::Create(CControlsWnd * pNotifyClass)
{
	// Do not call this twice
	ASSERT (!::IsWindow(GetSafeHwnd()));
	if (CEdit::Create(WS_CHILD | ES_LEFT | ES_AUTOHSCROLL,CRect(0,0,0,0), pNotifyClass->GetWindowNotify(), IDEDITBOX))
	{
		SetFont(pNotifyClass->GetWindowNotify()->GetFont());
		m_pNotifyClass = pNotifyClass;
		return this;
	}
	return NULL;
}

// Function name	: CDropEdit::Show
// Description	    : Show this class
// Return type		: void 
// Argument         : CRect rect
void CDropEdit::Show(CRect rect)
{
	// You must call Create function before
	ASSERT(::IsWindow(GetSafeHwnd()));
	MoveWindow(rect);
	ShowWindow(SW_SHOW);
	SetFocus();
	CString text; GetWindowText(text);
	SetSel(text.GetLength(), -1);
}

// Function name	: CDropEdit::OnKillFocus
// Description	    : Refresh value into m_pNotifyClass
// Return type		: void 
// Argument         : CWnd* pNewWnd
void CDropEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	CString text; GetWindowText(text);
	m_pNotifyClass->OnSelectItem(text, 0);
	ShowWindow(SW_HIDE);
}

// Function name	: CDropEdit::OnKeyDown
// Description	    : If user press wnetr key
// Return type		: void 
// Argument         : UINT nChar
// Argument         : UINT nRepCnt
// Argument         : UINT nFlags
void CDropEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);

	//Put focus on CPageListCtrl..
	if (nChar == VK_RETURN)
		m_pNotifyClass->GetWindowNotify()->SetFocus();
}

// Function name	: CDropEdit::CtlColor
// Description	    : Controls the window color of an edit.
// Return type		: HBRUSH 
// Argument         : CDC* pDC
// Argument         : UINT nCtlColor
HBRUSH CDropEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_rgbEditColor);
	
	return (HBRUSH)m_brush;
}

// Function name	: CDropEdit::SetEditColor
// Description	    : Set the color for edit 
// Return type		: void 
// Argument         : COLORREF rgbEditColor
void CDropEdit::SetEditColor(COLORREF rgbEditColor)
{
	m_rgbEditColor = rgbEditColor;
}
