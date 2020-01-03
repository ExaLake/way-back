/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/24/98 11:59:28 AM
  Comments: HighLightButton.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "HighLightButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDTIMERCHANGECOLOR 1000
#define WAITTOCHANGECOLOR 25

/////////////////////////////////////////////////////////////////////////////
// CHighLightButton

// Function name	: CHighLightButton::CHighLightButton
// Description	    : Default contructor of this object
// Return type		: 
CHighLightButton::CHighLightButton()
{
	SetBkGndColor(GetSysColor(COLOR_BTNFACE));
	SetForeGndColor(RGB(0,0,0));
	SetForeGndHighLightColor(RGB(0,0,255));
	m_rgbCurrentColor = m_rgbForeGnd;
}

// Function name	: CHighLightButton::~CHighLightButton
// Description	    : Destructor 
// Return type		: 
CHighLightButton::~CHighLightButton()
{
}


BEGIN_MESSAGE_MAP(CHighLightButton, CButton)
	//{{AFX_MSG_MAP(CHighLightButton)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHighLightButton message handlers

// Function name	: CHighLightButton::PreSubclassWindow
// Description	    : Change the button style to owner draw.
// Return type		: void 
void CHighLightButton::PreSubclassWindow() 
{
	ModifyStyle(BS_PUSHBUTTON , BS_OWNERDRAW | BS_TEXT);
	CButton::PreSubclassWindow();
}

// Function name	: CHighLightButton::Repaint
// Description	    : Call this function from Set...Color
// Return type		: void 
void CHighLightButton::Repaint()
{
	if (IsWindow(m_hWnd))
		Invalidate(FALSE);
}

// Function name	: CHighLightButton::SetBkGndColor
// Description	    : Set the new color of BkGnd, and return old value
// Return type		: COLORREF 
// Argument         : COLORREF rgbBKGnd
COLORREF CHighLightButton::SetBkGndColor(COLORREF rgbBKGnd)
{
	COLORREF rgbResult = m_rgbBkGnd;
	m_rgbBkGnd = rgbBKGnd;
	Repaint();
	return rgbResult;
}

// Function name	: CHighLightButton::SetForeGndHighLightColor
// Description	    : Set the new color of ForeGnd when user pass over the button, and return old value
// Return type		: COLORREF 
// Argument         : COLORREF rgbForeGnd
COLORREF CHighLightButton::SetForeGndHighLightColor(COLORREF rgbForeGnd)
{
	COLORREF rgbResult = rgbForeGnd;
	m_rgbForeGndHighLight = rgbForeGnd;
	Repaint();
	return rgbResult;
}

// Function name	: CHighLightButton::SetForeGndColor
// Description	    : Set the new color of ForeGnd, and return old value
// Return type		: COLORREF 
// Argument         : COLORREF rgbForeGnd
COLORREF CHighLightButton::SetForeGndColor(COLORREF rgbForeGnd)
{
	COLORREF rgbResult = m_rgbForeGnd;
	m_rgbForeGnd = rgbForeGnd;
	Repaint();
	return rgbResult;
}

// Function name	: CHighLightButton::DrawItem
// Description	    : Overidable function to draw the owner draw button
// Return type		: void 
// Argument         : LPDRAWITEMSTRUCT lpDrawItemStruct
void CHighLightButton::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CDC dc, *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CBitmap mBitmap; CRect drawRect(lpDrawItemStruct->rcItem);
	if (dc.CreateCompatibleDC(pDC))
		if (mBitmap.CreateCompatibleBitmap(pDC, drawRect.Width(), drawRect.Height()))
		{
			CBitmap* pOldBitmap = dc.SelectObject(&mBitmap);
			CBrush brush(m_rgbBkGnd);
			CBrush* pOldBrush = dc.SelectObject(&brush);
			//Erase the need area
			dc.PatBlt(0,0, drawRect.Width(), drawRect.Height(), PATCOPY);
			dc.SelectObject(pOldBrush);
			CString tButton; GetWindowText(tButton);
			dc.SetTextColor(m_rgbCurrentColor);
			dc.SetBkMode(TRANSPARENT);
			CFont* pOldFont = dc.SelectObject(GetParent()->GetFont());
			UINT nStyle = GetStyle();
			UINT nAddStyleH = (nStyle & BS_RIGHT ? (nStyle & BS_LEFT ? DT_CENTER : DT_RIGHT) : DT_LEFT);
			UINT nAddStyleV = (nStyle & BS_BOTTOM ? (nStyle & BS_TOP ? DT_VCENTER : DT_BOTTOM) : DT_TOP);
			CSize d = dc.GetTextExtent(tButton);
			dc.DrawText(tButton, drawRect, nAddStyleH | nAddStyleV | DT_SINGLELINE);

			if (lpDrawItemStruct->itemState & ODS_FOCUS)
			{
				// Draw the rect for focus
				CPen pen(PS_DOT, 1, RGB(255,255,255));
				dc.SelectObject(&pen);
				CRect rHigh(CPoint(+drawRect.left, +drawRect.top), d + CSize(4,2));
				if ( nAddStyleH != DT_LEFT )
					rHigh.OffsetRect((drawRect.right - rHigh.right) / (nAddStyleH == DT_RIGHT ? 1 : 2), 0);
				if ( nAddStyleV != DT_TOP )
					rHigh.OffsetRect(0, (drawRect.bottom - rHigh.bottom) / (nAddStyleV == DT_BOTTOM ? 1 : 2));
				dc.MoveTo(rHigh.TopLeft());dc.LineTo(rHigh.right, rHigh.top);dc.LineTo(rHigh.BottomRight());
				dc.LineTo(rHigh.left, rHigh.bottom); dc.LineTo(rHigh.TopLeft());
			}
			int nSS = lpDrawItemStruct->itemState & ODS_SELECTED ? 1 : 0;
			//Copy from memory device to destination device
			pDC->BitBlt(drawRect.left + nSS, drawRect.top + nSS, drawRect.Width() , drawRect.Height() , &dc, 0,0, SRCCOPY);
			dc.SelectObject(pOldBitmap);
			dc.SelectObject(pOldFont);
		}
}

// Function name	: CHighLightButton::OnMouseMove
// Description	    : Change the current color, when user.
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CHighLightButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_rgbCurrentColor != m_rgbForeGndHighLight)
	{
		m_rgbCurrentColor = m_rgbForeGndHighLight;
		Repaint();
		SetTimer(IDTIMERCHANGECOLOR, WAITTOCHANGECOLOR, NULL);
	}
	CButton::OnMouseMove(nFlags, point);
}

// Function name	: CHighLightButton::RemoveCurrentColor
// Description	    : Remove the current color if is case.
// Return type		: void 
// Argument         : BOOL bCheckPoint
void CHighLightButton::RemoveCurrentColor(BOOL bCheckPoint)
{
	CPoint pCursor;
	BOOL bRemove = TRUE;
	if (bCheckPoint && GetCursorPos(&pCursor))
	{
		CRect rect; GetWindowRect(&rect);
		bRemove = !rect.PtInRect(pCursor);
	}
	if (bRemove)
		if (m_rgbCurrentColor != m_rgbForeGnd)
			if (GetCapture() != this)
			{
				KillTimer(IDTIMERCHANGECOLOR);
				m_rgbCurrentColor = m_rgbForeGnd;
				Repaint();
			}
}

// Function name	: CHighLightButton::OnTimer
// Description	    : Remove the foreground colore set in OnMouseMove
// Return type		: void 
// Argument         : UINT nIDEvent
void CHighLightButton::OnTimer(UINT nIDEvent) 
{
	switch (nIDEvent)
	{
		case IDTIMERCHANGECOLOR:
			{
				RemoveCurrentColor(TRUE); // check the point at cursor
				break;
			}
	}
	
	CButton::OnTimer(nIDEvent);
}

// Function name	: CHighLightButton::OnKillFocus
// Description	    : When the user lose focus
// Return type		: void 
// Argument         : CWnd* pNewWnd
void CHighLightButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	RemoveCurrentColor(FALSE); // do not check the point at cursor
	
}
