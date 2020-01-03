/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/15/98 9:30:26 AM
  Comments: PageListCtrl.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "XPropertiesWnd.h"
#include "PageListCtrl.h"
#include "XFloorPropertiesWnd.h"
#include "XPropertiesWndCtl.h"
#include "gdi.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CPageListCtrl

IMPLEMENT_DYNCREATE(CPageListCtrl, CListCtrl)

BOOL CPageListCtrl::m_bAutoResizingColumns = TRUE;
CAsControls CPageListCtrl::m_asControls;
COLORREF CPageListCtrl::m_rgbDisableItem = GetSysColor(COLOR_GRAYTEXT);
COLORREF CPageListCtrl::m_rgbEnableItem = RGB(0,0,0);
#define NULLPOINT CPoint(-1,-1)

// Function name	: CPageListCtrl::CPageListCtrl
// Description	    : Default consturctor
// Return type		: 
CPageListCtrl::CPageListCtrl(CXPropertiesWndCtrl* pControl, int nHeight)
{
	m_pControl = pControl;
	m_nHeight = nHeight;
	m_nIndexPage = -1;
	m_hIconDown = AfxGetApp()->LoadIcon(IDI_ICON_DOWN);
	m_hIconUp = AfxGetApp()->LoadIcon(IDI_ICON_UP);
	m_hIconDots = AfxGetApp()->LoadIcon(IDI_ICON_DOTS);
	m_hIconReturn = AfxGetApp()->LoadIcon(IDI_ICON_RETURN);
	m_hIconLink = AfxGetApp()->LoadIcon(IDI_ICON_LINK);
	m_hIconFont = m_hIconDots;
	m_hIconClick = AfxGetApp()->LoadIcon(IDI_ICON_CLICK);
	m_pEditControl = NULL;
	m_nOpenedProperty = -1;
	m_ptnCapture = NULLPOINT;
}

// Function name	: CPageListCtrl::SetIndexPage
// Description	    : Save the window of page into control
// Return type		: void 
// Argument         : long nIndexPage
void CPageListCtrl::SetIndexPage(long nIndexPage)
{
	m_nIndexPage = nIndexPage;
}

// Function name	: CPageListCtrl::GetIndexPage
// Description	    : return the index of page
// Return type		: const long 
const long CPageListCtrl::GetIndexPage()
{
	return m_nIndexPage;
}

// Function name	: CPageListCtrl::~CPageListCtrl
// Description	    : Virtual Destructor
// Return type		: 
CPageListCtrl::~CPageListCtrl()
{
	ResetEditControl();
}


BEGIN_MESSAGE_MAP(CPageListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CPageListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_MEASUREITEM()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_NOTIFY_REFLECT(LVN_INSERTITEM, OnInsertitem)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGING, OnItemchanging)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageListCtrl message handlers

// Function name	: CPageListCtrl::OnNew
// Description	    : Called after new operator
// Return type		: void 
// Argument         : CWnd* pParentWnd
// Argument         : UINT nID
void CPageListCtrl::OnNew(CWnd* pParentWnd, UINT nID)
{
	Create(WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | LVS_SHOWSELALWAYS | LVS_NOCOLUMNHEADER | LVS_REPORT | GetDefaultStyle() , CRect(0,0,0,0), pParentWnd, nID);
	ListView_SetExtendedListViewStyle(m_hWnd, GetDefaultExStyle());
}

// Function name	: CPageListCtrl::GetDefaultStyle
// Description	    : Called by void CPageListCtrl::OnNew(CWnd* pParentWnd, UINT nID)
// Return type		: const UINT 
const UINT CPageListCtrl::GetDefaultStyle()
{
	return LVS_SINGLESEL | LVS_OWNERDRAWFIXED;
}

// Function name	: CPageListCtrl::GetDefaultExStyle
// Description	    : 
// Return type		: const UINT 
const UINT CPageListCtrl::GetDefaultExStyle()
{
	return LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
}

// Function name	: CPageListCtrl::OnCreate
// Description	    : Called to Init control 
// Return type		: int 
// Argument         : LPCREATESTRUCT lpCreateStruct
int CPageListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!OnInit())
	{
		#ifdef _DEBUG
			TRACE0("Warning: Cannot create PageListCtrl.\n");
		#endif

		return -1;
	}
	
	return 0;
}

// Function name	: CPageListCtrl::OnInit
// Description	    : Initilalize the control
// Return type		: BOOL 
BOOL CPageListCtrl::OnInit()
{
	InsertColumn(0, _T("Name"), LVCFMT_LEFT, 96);
	InsertColumn(1, _T("Value"), LVCFMT_LEFT, 128);
	//Create the item font
	LOGFONT logFont;
	if (::GetObject(GetControlWnd()->m_itemFont.GetFontHandle(), sizeof(LOGFONT), &logFont))
		CreateItemFont((const LOGFONT*)&logFont);
	//Create the tooltips if neccessarly
	if (GetControlWnd()->m_bToolTips)
		m_toolTip.Create(this);
	return TRUE;
}

// Function name	: CPageListCtrl::OnEndlabeledit
// Description	    : On EndEdit label
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CPageListCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	CString item; GetEditControl()->GetWindowText(item);
	if (item.IsEmpty())
		DeleteItem(pDispInfo->item.iItem);
	else
		SetItemText(pDispInfo->item.iItem, pDispInfo->item.iSubItem, item);
	
	*pResult = 0;
}

void CPageListCtrl::Save(CString & stream)
{
}

// Function name	: CPageListCtrlDesign::Load
// Description	    : Call to load items in design/runtime time. Depend on case
// Return type		: void 
// Argument         : CString & stream
void CPageListCtrl::Load(CString & stream)
{
	if (::IsWindow(m_hWnd))
	{
		DeleteAllItems();
		CString sItem;
		int i = 0;
		AfxExtractSubString(sItem, stream, i, _cPagesSeparator);
		while (!sItem.IsEmpty())
		{
			CString sItem0, sItem1, sItem2;
			AfxExtractSubString(sItem0, sItem, 0, TCHAR('\\'));
			AfxExtractSubString(sItem1, sItem, 1, TCHAR('\\'));
			AfxExtractSubString(sItem2, sItem, 2, TCHAR('\\'));
			int nItem = InsertItem(GetItemCount(), sItem0);
			OnLoad(nItem, sItem1, sItem2);
			AfxExtractSubString(sItem, stream, ++i, _cPagesSeparator);
		}
	}
}

// Function name	: CPageListCtrl::OnLoad
// Description	    : Called by Load function to set the type of item nItem
// Return type		: void 
// Argument         : int nItem
// Argument         : LPCTSTR lpszAs
void CPageListCtrl::OnLoad(int nItem, LPCTSTR lpszAs, LPCTSTR lpszType)
{
	static const CString enable(_T("Enable"));
	static const CString grayed(_T("Grayed"));
	SetItemData(nItem, MAKELPARAM(m_asControls.GetID(lpszAs), enable.CompareNoCase(lpszType) == 0 ? 0 : (grayed.CompareNoCase(lpszType)) == 0 ? 1 : 2));
}

// Function name	: CPageListCtrl::IsGrayedItem
// Description	    : 
// Return type		: BOOL 
// Argument         : int nItem
BOOL CPageListCtrl::IsGrayedItem(int nIndex)
{
	if (nIndex >= 0)
		if (nIndex < GetItemCount())
			return HIWORD(GetItemData(nIndex)) == 1;
	return FALSE;
}

// Function name	: CPageListCtrl::IsBlackItem
// Description	    : 
// Return type		: BOOL 
// Argument         : int nItem
BOOL CPageListCtrl::IsBlackItem(int nIndex)
{
	if (nIndex >= 0)
		if (nIndex < GetItemCount())
			return HIWORD(GetItemData(nIndex)) == 2;
	return NULL;
}

// Function name	: CPageListCtrl::IsEnableItem
// Description	    : Return TRUE or FALSE case on Enable disable
// Return type		: BOOL 
// Argument         : int nIndex
BOOL CPageListCtrl::IsEnableItem(int nIndex)
{
	if (nIndex >= 0)
		if (nIndex < GetItemCount())
			return HIWORD(GetItemData(nIndex)) == 0;
	return FALSE;
}

// Function name	: CPageListCtrl::IsEditItem
// Description	    : Edit Item
// Return type		: BOOL 
// Argument         : int nItem
BOOL CPageListCtrl::IsEditItem(int nItem)
{
	return CString(GetItemAsControl(nItem)).CompareNoCase(_T("Edit")) == 0;
}

BOOL CPageListCtrl::IsButtonItem(int nItem)
{
	return (CString(GetItemAsControl(nItem)).CompareNoCase(_T("Button")) == 0) ||
			(CString(GetItemAsControl(nItem)).CompareNoCase(_T("Return")) == 0) || 
			(CString(GetItemAsControl(nItem)).CompareNoCase(_T("Link")) == 0) ||
			(CString(GetItemAsControl(nItem)).CompareNoCase(_T("Font")) == 0);
}

// Function name	: CPageListCtrl::GetItemAsControl
// Description	    : Get as string the as of item
// Return type		: LPCTSTR 
// Argument         : int nIndex
LPCTSTR CPageListCtrl::GetItemAsControl(int nIndex)
{
	if (nIndex >= 0)
		if (nIndex < GetItemCount())
			return m_asControls.GetName(LOWORD(GetItemData(nIndex)));
	return NULL;
}

// Function name	: CPageListCtrl::ResizeColumns
// Description	    : Resize the last column, such that the sum of widths is equal with width of client rect
// Return type		: void 
// Argument         : int cx
// Argument         : int cy
void CPageListCtrl::ResizeColumns()
{
	if (m_bAutoResizingColumns)
	{
		LV_COLUMN lColumn; lColumn.mask = LVCF_WIDTH;
		CRect rect; GetClientRect(rect);
		if (!rect.IsRectEmpty())
		{
			if (GetColumn(0,&lColumn))
			{
				int s = 0, i = 0;
				for (i = 0; GetColumn(i, &lColumn); i++, s += lColumn.cx);
				i--;
				SetColumnWidth(i, abs(rect.Width() - (s - GetColumnWidth(i))));
			}
			// One penible bug
			SendMessage(WM_HSCROLL, MAKEWPARAM( SB_ENDSCROLL, 0), NULL);
		}
	}
}

// Function name	: CPageListCtrl::OnSize
// Description	    : On resize control
// Return type		: void 
// Argument         : UINT nType
// Argument         : int cx
// Argument         : int cy
void CPageListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);

	ResizeColumns();
}

// Function name	: CPageListCtrl::GetLastRect
// Description	    : Return rect of item nItem and subitme nSubItem
// Return type		: CRect 
// Argument         : int nItem
// Argument         : int nSubItem
CRect CPageListCtrl::GetLastRect(int nItem)
{
	CRect rResult;
	GetItemRect(nItem, rResult, LVIR_BOUNDS);
	rResult.left = rResult.right - GetColumnWidth(1);
	rResult.OffsetRect(2,0);
	return rResult;
}

// Function name	: CPageListCtrl::OpenEditing
// Description	    : Open editing mode
// Return type		: BOOL 
// Argument         : int nItem
// Argument         : CPoint point
BOOL CPageListCtrl::OpenEditing(int nItem, LPARAM lParam)
{
	if (IsEnableItem(nItem))
	{
		if (CreateEditControl(nItem))
		{
			if (m_nOpenedProperty != nItem)
				m_pEditControl->Load();
			m_nOpenedProperty = nItem;
		}
		else m_nOpenedProperty = -1;
		return TRUE;
	}
	return FALSE;
}

// Function name	: CPageListCtrl::GetWindowEditing
// Description	    : 
// Return type		: CWnd* 
CWnd* CPageListCtrl::GetWindowEditing()
{
	if (m_pEditControl)
		return m_pEditControl->GetWindow();
	return NULL;
}

// Function name	: CPageListCtrl::CloseEditing
// Description	    : Close editing mode
// Return type		: void 
void CPageListCtrl::CloseEditing()
{
}

// Function name	: CPageListCtrl::NextItem
// Description	    : 
// Return type		: void 
// Argument         : int nItem
void CPageListCtrl::NextItem(int nItem)
{
	if (IsEnableItem(nItem))
		if (m_pEditControl)
			m_pEditControl->OnNextItem();
}

// Function name	: CPageListCtrl::OnKeyDown
// Description	    : Press SPACE, start edit item
// Return type		: void 
// Argument         : UINT nChar
// Argument         : UINT nRepCnt
// Argument         : UINT nFlags
void CPageListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_PRIOR:
		case VK_NEXT:
		case VK_END:
		case VK_HOME:
		case VK_LEFT:
		case VK_UP:
		case VK_RIGHT:
		case VK_DOWN:
			{
				CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
				break;
			}
		case VK_DELETE:
			{
				if (CXPropertiesWndCtrl* pControlWnd = GetControlWnd())
					if (m_pEditControl)
						pControlWnd->FireDelete((short)m_pEditControl->GetWindowNotify()->m_nIndexPage, (short)m_pEditControl->GetSelectedItem());
				break;
			}
		default:
			{
				if (m_pEditControl)
				{
					BOOL bEdit = m_pEditControl->IsKindOf(RUNTIME_CLASS(CControlsWnd_CEdit));
					if (bEdit || ( nChar == VK_F4) || (nChar == VK_RETURN))
					{
						m_pEditControl->Show();
						if (bEdit)
							m_pEditControl->GetWindow()->PostMessage(WM_KEYDOWN, nChar, nFlags);
					}
				}
				break;
			}
	}
}

// Function name	: CPageListCtrl::OnRButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
}

// Function name	: CPageListCtrl::OnRButtonDblClk
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrl::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
}

// Function name	: CPageListCtrl::CheckEditMode
// Description	    : 
// Return type		: BOOL 
// Argument         : CPoint point
// Argument         : int nSelected
BOOL CPageListCtrl::CheckEditMode(int nItem, CPoint point, int nSelected)
{
	if (nItem>=0)
		if (IsEnableItem(nItem))
			// In item as edit  control must click twice.
			if (IsEditItem(nItem))
				return nItem == nSelected;
			else
				// You must click in button
				if (!m_btnRect.IsRectEmpty())
					return m_btnRect.PtInRect(point);
	return FALSE;
}

// Function name	: CPageListCtrl::OnLButtonDblClk
// Description	    : If user dblclk the combos move next item
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if ((m_btnRect.IsRectEmpty()) || ((!m_btnRect.IsRectEmpty()) && (!m_btnRect.PtInRect(point))))
	{
		int nItem = HitTest(point);
		if (nItem >= 0)
			NextItem(nItem);
	}
}

// Function name	: CPageListCtrl::DrawButton
// Description	    : 
// Return type		: void 
// Argument         : CDC * pDC
// Argument         : CRect rB
// Argument         : int nItem
// Argument         : BOOL bClick
void CPageListCtrl::DrawButton(CDC * pDC, CRect rB, int nItem, BOOL bClick)
{
	CDC* pDCDraw = pDC;
	if (!pDC)
		pDCDraw = GetDC();

	rB.InflateRect(-1,-1);
	pDCDraw->FillRect(rB, &CBrush(RGB(192,192,192)));
	pDCDraw->DrawEdge(rB, EDGE_RAISED, BF_RECT);
	rB.InflateRect(-1,-1);

	HICON hIcon = m_hIconDown;
	if (IsButtonItem(nItem))
	{
		switch (LOWORD(GetItemData(nItem)))
		{
			case ID_MENUAS_BUTTON:
				{
					hIcon = m_hIconDots;
					break;
				}
			case ID_MENUAS_RETURN:
				{
					hIcon = m_hIconReturn;
					break;
				}
			case ID_MENUAS_LINK:
				{
					hIcon = m_hIconLink;
					break;
				}
			case ID_MENUAS_FONT:
				{
					hIcon = m_hIconFont;
					break;
				}
		}
			
	}
	pDCDraw->DrawIcon(rB.left, rB.top, hIcon );
	if (bClick)
		pDCDraw->DrawIcon(rB.left, rB.top, m_hIconClick);

	if (!pDC)
		ReleaseDC(pDCDraw);
}

#define GetColorItem(sItem) CControlsWnd_CColorComboBox::GetColor(sItem)
#define formatDrawText DT_VCENTER | DT_SINGLELINE | DT_LEFT

// Function name	: CPageListCtrl::UserPaint
// Description	    : If user want to paint something ...
// Return type		: void 
// Argument         : int nItem
// Argument         : CDC * pDC
// Argument         : CRect rect
BOOL CPageListCtrl::UserPaint(int nItem, CDC * pDC, CRect rect)
{
	// Type of item is in LOWORD of GetItemData(nItem)
	CGdiStack stack;
	switch (LOWORD(GetItemData(nItem)))
	{
		case ID_MENUAS_COLORCOMBOBOX:
			{
				CRect rColor(rect); rColor.right = rColor.left + rColor.Height();
				rect.left = rColor.right + 4;
				rColor.InflateRect(-2,-2); rColor.OffsetRect(0,1);
				CString sItem = GetItemText(nItem, 1);
				pDC->FillRect(rColor, &CBrush(GetColorItem(sItem)));
				pDC->FrameRect(rColor, &CBrush(RGB(0,0,0)));
				pDC->DrawText(sItem, rect, formatDrawText);
				return TRUE;
			}
		case ID_MENUAS_FONT:
			{
				if (CControlsWnd_CFont* pFontControl = (CControlsWnd_CFont*)CControlsWnd::LookupControl(this, nItem))
				{
					CFont font;
					LOGFONT logFont;
					memcpy(&logFont, pFontControl->GetLogFont(), sizeof(logFont));
					logFont.lfHeight = rect.Height() - 2;
					font.CreateFontIndirect(&logFont);
					stack.Push(pDC, &font);
					COLORREF oColor = pDC->SetTextColor(pFontControl->GetColorFont());
					pDC->DrawText(GetItemText(nItem, 1), rect, formatDrawText);
					pDC->SetTextColor(oColor);
					stack.Pop();
					font.DeleteObject();
					return TRUE;
				}
				return FALSE;
			}
	}
	return FALSE;
}

// Function name	: CPageListCtrl::DrawItem
// Description	    : 
// Return type		: void 
// Argument         : LPDRAWITEMSTRUCT lpDrawItemStruct
void CPageListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CRect rectDraw(lpDrawItemStruct->rcItem), rectItem(rectDraw);
	int nItem = lpDrawItemStruct->itemID;
	CRect rectAll; GetItemRect(nItem, rectAll, LVIR_BOUNDS);
	CRect rectLabel; GetItemRect(nItem, rectLabel, LVIR_LABEL);
	BOOL bFocused = GetFocus() && (GetItemState(nItem, LVIS_FOCUSED) == LVIS_FOCUSED);
	BOOL bSelected = GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED;
	if (bFocused && bSelected) m_btnRect.SetRectEmpty();
	BOOL bEnabled = IsEnableItem(nItem);
	BOOL bEdit = IsEditItem(nItem);
	LV_COLUMN lColumn; lColumn.mask = LVCF_WIDTH;
	rectItem.left += 2;
	pDC->SetTextColor(bEnabled ? (bSelected & bFocused ? RGB(255,255,255) : m_rgbEnableItem) : (IsGrayedItem(nItem) ? m_rgbDisableItem : RGB(0,0,0)));
	CBrush brush(bEnabled & bSelected ? (bFocused ? RGB(0,0,128) : RGB(192,192,192)) : RGB(255,255,255));
	pDC->FillRect(rectAll, &CBrush(RGB(255,255,255)));
	pDC->FillRect(rectLabel, &brush);

	// Select the item font
	CFont* pFont = GetControlWnd()->SelectFontObject(pDC, GetControlWnd()->m_itemFont);
	int i = 0;
	BOOL bEditMode = IsEditMode() && bFocused;
	BOOL bUser = FALSE;
	for (i = 0; GetColumn(i, &lColumn); i++, rectItem.left += lColumn.cx + 2)
	{
		rectItem.right = rectItem.left + lColumn.cx;
		if (i == 1)
			bUser = UserPaint(nItem, pDC, rectItem);
		if (!bUser)
			pDC->DrawText(GetItemText(nItem, i), rectItem, formatDrawText);
		pDC->SetTextColor(!bEditMode ? RGB(0,0,0) : GetControlWnd()->m_rgbEditColor);
	}
	pDC->SelectObject(pFont);
	pDC->SetTextColor(RGB(0,0,0));
	// Deselect the item font
	i--;
	if (bFocused && !bEnabled)
	{
		rectLabel.InflateRect(0,-1);
		rectLabel.bottom++;
		pDC->FrameRect(rectLabel, &CBrush(RGB(0,0,0)));
	}
	else
	{
		if (!bEdit)
			if (bFocused && bSelected)
			{
				CRect rB(rectAll);
				rB.top++;
				rB.left = rB.right - (GetSystemMetrics(SM_CXHSCROLL) + 2);
				if (rB.left < rB.right)
					if (rB.Width() < GetColumnWidth(i))
					{
						m_btnRect = rB;
						DrawButton(pDC, m_btnRect, nItem, FALSE);
					}
			}
	}
}	

// Function name	: CPageListCtrl::OnMeasureItem
// Description	    : Measure the item
// Return type		: void 
// Argument         : int nIDCtl
// Argument         : LPMEASUREITEMSTRUCT lpMeasureItemStruct
void CPageListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	ASSERT (nIDCtl == GetDlgCtrlID());
	lpMeasureItemStruct->itemHeight = m_nHeight;
	
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

// Function name	: CPageListCtrl::GetControlWnd
// Description	    : Return pointer to class tha create this control. In fact * to CXPropertiesWndCtrl
// Return type		: CXPropertiesWndCtrl* 
CXPropertiesWndCtrl* CPageListCtrl::GetControlWnd()
{
	return m_pControl;
}

// Function name	: CPageListCtrl::GetFloorWnd
// Description	    : Return pointer to OLE Control xFloorWnd as Window
// Return type		: CXFloorPropertiesWnd* 
CXFloorPropertiesWnd* CPageListCtrl::GetFloorWnd()
{
	if (GetControlWnd())
		return &GetControlWnd()->m_xFloorWnd;
	return NULL;
}

// Function name	: CPageListCtrl::OnInsertitem
// Description	    : Called after insert item
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CPageListCtrl::OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (GetControlWnd())
		SetDefaultValue(pNMListView->iItem, GetItemText(pNMListView->iItem, 1));

	*pResult = 0;
}

// Function name	: CPageListCtrl::OnItemchanging
// Description	    : 
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CPageListCtrl::OnItemchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	if (CXPropertiesWndCtrl* pControlWnd = GetControlWnd())
	{
	}
	
	*pResult = 0;
}

// Function name	: CPageListCtrl::OnItemchanged
// Description	    : Fire to user a event as SelectItem(int nIndexPage, int nIndexItem)
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CPageListCtrl::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	// Generate a fire event as user select a item (In fact when, user changes the items, the fire will be auomaticlay generated
	if (CXPropertiesWndCtrl* pControlWnd = GetControlWnd())
	{
		int nPage = GetFloorWnd()->GetActivePage();
		if (pNMListView->uNewState & LVIS_SELECTED)
		{
			ResetEditControl();
			pControlWnd->FireSelectItem(nPage ,pNMListView->iItem);
			OpenEditing(pNMListView->iItem);
		}
		else
			if (pNMListView->uNewState == 0)
				if (pNMListView->uChanged == LVIS_DROPHILITED)
				{

					if (GetItemState(pNMListView->iItem, LVIS_SELECTED | LVIS_FOCUSED) == 0)
						pControlWnd->FireUnselectItem(nPage,pNMListView->iItem);
				}
	}
	
	*pResult = 0;
}

// Function name	: CPageListCtrl::OnKillFocus
// Description	    : 
// Return type		: void 
// Argument         : CWnd* pNewWnd
void CPageListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);
	
	if (m_pEditControl)
		m_pEditControl->Close(FALSE);
}

// Function name	: CPageListCtrl::WindowProc
// Description	    : 
// Return type		: LRESULT 
// Argument         : UINT message
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CPageListCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYUP:
			{
				if (IsEditMode())
					if (CWnd* pWnd = GetWindowEditing())
						return pWnd->SendMessage(message, wParam, lParam);
				break;
			}
		case WM_VSCROLL:
		case WM_HSCROLL:
			{
				ResetEditControl();
				break;
			}
	}

	if (::IsWindow(m_toolTip.GetSafeHwnd()))
	{
		MSG msg = {m_hWnd, message, wParam, lParam};
		m_toolTip.RelayEvent(&msg);
	}

	return CListCtrl::WindowProc(message, wParam, lParam);
}

// Function name	: CPageListCtrl::ResetEditControl
// Description	    : Is called every time, when you change the current selectio in pagelistctrl
// Return type		: void 
void CPageListCtrl::ResetEditControl()
{
	if (m_pEditControl)
		m_pEditControl = m_pEditControl->Delete();
}

// Function name	: CPageListCtrl::CreateEditControl
// Description	    : Creae edit control. Not window
// Return type		: BOOL 
// Argument         : int nItem
BOOL CPageListCtrl::CreateEditControl(int nItem)
{
	if (!m_pEditControl)
		m_pEditControl = CControlsWnd::Create(GetItemAsControl(nItem), this, nItem);
	return m_pEditControl != NULL;
}

// Function name	: CPageListCtrl::GetPropertyName
// Description	    : Return the property name
// Return type		: CString 
// Argument         : int nIndexProperty
CString CPageListCtrl::GetPropertyName(int nIndexProperty)
{
	return GetItemText(nIndexProperty, 0);
}

// Function name	: CPageListCtrl::GetDefaultValue
// Description	    : Return the default value of property nIndexProperty
// Return type		: CString 
// Argument         : int nIndexProperty
const CString CPageListCtrl::GetDefaultValue(int nIndexProperty)
{
	return GetItemText(nIndexProperty, 1);
}

// Function name	: CPageListCtrl::SetDefaultValue
// Description	    : Set default value
// Return type		: BOOL 
// Argument         : int nIndexProperty
// Argument         : LPCTSTR lpszdefaultValue
BOOL CPageListCtrl::SetDefaultValue(int nIndexProperty, LPCTSTR lpszdefaultValue)
{
	if (nIndexProperty >= 0)
		if (nIndexProperty < GetItemCount())
		{
			SetItemText(nIndexProperty, 1, lpszdefaultValue);
			return TRUE;
		}
	return FALSE;
}

// Function name	: CPageListCtrl::SetPropertyName
// Description	    : Set the property Name
// Return type		: void 
// Argument         : int nIndexProperty
// Argument         : LPCTSTR lpszPropertyName
void CPageListCtrl::SetPropertyName(int nIndexProperty, LPCTSTR lpszPropertyName)
{
	if (nIndexProperty >= 0)
		if (nIndexProperty < GetItemCount())
			SetItemText(nIndexProperty, 0, lpszPropertyName);
}

// Function name	: CPageListCtrl::GetActiveProperty
// Description	    : return the active property
// Return type		: int 
int CPageListCtrl::GetActiveProperty()
{
	return GetNextItem(-1, LVNI_SELECTED);
}

// Function name	: CPageListCtrl::SetActiveProperty
// Description	    : Set the active property
// Return type		: void 
// Argument         : int nIndexProperty
void CPageListCtrl::SetActiveProperty(int nIndexProperty)
{
	SetItemState(nIndexProperty, LVNI_SELECTED , LVNI_SELECTED);
}

BOOL CPageListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CListCtrl::PreTranslateMessage(pMsg);
}

// Function name	: CPageListCtrl::CreateItemFont
// Description	    : Create a font for items
// Return type		: BOOL 
// Argument         : const LOGFONT * pLogFont
BOOL CPageListCtrl::CreateItemFont(const LOGFONT * pLogFont)
{
	m_itemFont.DeleteObject();
	return m_itemFont.CreateFontIndirect(pLogFont);
}

// Function name	: CPageListCtrl::IsEditMode
// Description	    : return TRUE if is edit mode
// Return type		: BOOL 
BOOL CPageListCtrl::IsEditMode()
{
	if (m_pEditControl)
		return m_pEditControl->IsVisible();
	return FALSE;
}

// Function name	: CPageListCtrl::GetControl
// Description	    : Return the control from nIndex item.
// Return type		: CControlsWnd* 
// Argument         : int nIndex
CControlsWnd* CPageListCtrl::GetControl(int nIndex, BOOL bDelete)
{
	// We will try to create and then delete one control. In this way, I will
	// find if the control is destroyble or not.
	if (CControlsWnd* pControl = CControlsWnd::Create(GetItemAsControl(nIndex), this, nIndex))
		if (bDelete)
		{
			pControl->Delete();
			// Check if after Delete function the pControl has a valid vTable or not
			// If it is valid, that means that this object is either CControlsWnd_CADORComboBox or ...
			// a control non delete.
			if (AfxIsValidAddress(*(void**)pControl, sizeof(void*), FALSE))
				return pControl;
		}
		else
			return pControl;
	return NULL;
}

// Function name	: CPageListCtrl::OnSetCursor
// Description	    : 
// Return type		: BOOL 
// Argument         : CWnd* pWnd
// Argument         : UINT nHitTest
// Argument         : UINT message
BOOL CPageListCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (IsSizingLine())
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(IDC_SIZEWE)));
		return TRUE;
	}
	
	return CListCtrl::OnSetCursor(pWnd, nHitTest, message);
}

// Function name	: CPageListCtrl::IsSizingLine
// Description	    : Return TRUE if mouse point is over the first right side of first column
// Return type		: BOOL 
BOOL CPageListCtrl::IsSizingLine()
{
	if (m_bAutoResizingColumns)
		if (GetControlWnd()->m_bResizeFirstColumn) 
		{
			DWORD lPoint = ::GetMessagePos();
			CPoint p(LOWORD(lPoint), HIWORD(lPoint));
			ScreenToClient(&p);
			CRect rect; GetClientRect(rect);
			int x = GetColumnWidth(0);
			rect.left = x - 2;
			rect.right = x + 2;
			return rect.PtInRect(p);
		}
	return FALSE;
}

// Function name	: CPageListCtrl::OnLButtonDown
// Description	    : User click mouse in runtime time
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();

	if (IsSizingLine())
	{
		ResetEditControl();
		SetCapture();
		m_ptnCapture = point;
		return;
	}
	// continue the operation ...
	m_nSelected = GetActiveProperty();
	int nItem = HitTest(point);
	if (nItem >= 0)
		SetItemState(nItem, LVNI_SELECTED | LVNI_FOCUSED, LVNI_FOCUSED | LVNI_SELECTED);
}

// Function name	: CPageListCtrl::IsMouseCaptured
// Description	    : 
// Return type		: BOOL 
BOOL CPageListCtrl::IsMouseCaptured()
{
	return m_ptnCapture != NULLPOINT;
}

// Function name	: CPageListCtrl::InvalidateNew
// Description	    : 
// Return type		: void 
void CPageListCtrl::InvalidateNew()
{
	if (CBitmap* pBitmap = Preview(this, RGB(255,255,255)))
	{
		CGdiStack stack;
		CDC* pDC = GetDC();
			CDC dcMem;
			CRect rect; GetClientRect(rect);
			if (dcMem.CreateCompatibleDC(pDC))
			{
				stack.Push(&dcMem, pBitmap);
				pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem, 0,0, SRCCOPY);
				stack.Pop();
			}
			ReleaseDC(pDC);
		pBitmap->DeleteObject();
		delete pBitmap;
	}
	else Invalidate();
}

// Function name	: CPageListCtrl::OnMouseMove
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (IsMouseCaptured())
	{
		CRect rect; GetClientRect(rect);
		int rMin = rect.Width() / 6, rMax = rect.Width() - rMin;
		int newWidth = GetColumnWidth(0) + ( point.x - m_ptnCapture.x );
		if ((newWidth >= rMin) && (newWidth <= rMax))
		{
			ModifyStyle(WS_VISIBLE, 0, SWP_NOREDRAW);
				SetColumnWidth(0, newWidth );
				ResizeColumns();
			ModifyStyle(0, WS_VISIBLE, SWP_NOREDRAW);
			InvalidateNew();
			m_ptnCapture = point;
		}
	}
	CListCtrl::OnMouseMove(nFlags, point);
}

// Function name	: CPageListCtrl::OnLButtonUp
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CListCtrl::OnLButtonUp(nFlags, point);

	if (IsMouseCaptured()) // is mouse captured
	{
		ReleaseCapture();
		m_ptnCapture = NULLPOINT;
	}

	if (m_pEditControl)
	{
		int nItem = HitTest(point);
		if (CheckEditMode(nItem, point, m_nSelected))
		{
			EnsureVisible(nItem, TRUE);
			m_pEditControl->Show();
		}
	}
}
