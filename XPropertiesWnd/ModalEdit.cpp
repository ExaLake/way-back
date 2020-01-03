/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 11/11/98 5:08:12 AM
  Comments: ModalEdit.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "XPropertiesWnd.h"
#include "ModalEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModalEdit

// Function name	: CModalEdit::CModalEdit
// Description	    : default constructor
// Return type		: 
CModalEdit::CModalEdit()
{
	m_bFirstDo = TRUE;
}

// Function name	: CModalEdit::~CModalEdit
// Description	    : virtual destructor
// Return type		: 
CModalEdit::~CModalEdit()
{
}


BEGIN_MESSAGE_MAP(CModalEdit, CEdit)
	//{{AFX_MSG_MAP(CModalEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModalEdit message handlers

// Function name	: CModalEdit::Do
// Description	    : Do a modal edit
// Return type		: void 
// Argument         : CRect rect
// Argument         : LPCTSTR lpszText
void CModalEdit::Do(CRect rect, LPCTSTR lpszText)
{
	m_bFirstDo = FALSE;
	MoveWindow(rect);
	SetWindowText(lpszText);
	ShowWindow(SW_SHOW);
	SetFocus();
	SetSel(0,-1);
}

// Function name	: CModalEdit::OnLButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CModalEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rect; GetWindowRect(rect);
	CPoint pointS(point); ClientToScreen(&pointS);
	if (!rect.PtInRect(pointS))
		End();
	
	CEdit::OnLButtonDown(nFlags, point);
}

// Function name	: CModalEdit::OnKillFocus
// Description	    : 
// Return type		: void 
// Argument         : CWnd* pNewWnd
void CModalEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	if (m_bFirstDo)
		End();
	else
		SetFocus();
	m_bFirstDo = TRUE;
}

// Function name	: CModalEdit::End
// Description	    : 
// Return type		: void 
void CModalEdit::End()
{
	ReleaseCapture();
	ShowWindow(SW_HIDE);
}

// Function name	: CModalEdit::OnSetFocus
// Description	    : 
// Return type		: void 
// Argument         : CWnd* pOldWnd
void CModalEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	
	SetCapture();
	
}

