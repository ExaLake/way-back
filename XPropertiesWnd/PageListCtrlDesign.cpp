/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 12:02:17 PM
  Comments: PageListCtrlDesign.cpp: implementation of the CPageListCtrlDesign class.
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "PageListCtrlDesign.h"
#include "XFloorPropertiesWndDesign.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEFAULTTYPE m_nDefaultType == ID_MENUTYPE_ENABLE ? _T("Enable") : m_nDefaultType == ID_MENUTYPE_DISABLE ?  _T("Grayed") : _T("Black")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CPageListCtrlDesign, CPageListCtrl)

BEGIN_MESSAGE_MAP(CPageListCtrlDesign,CPageListCtrl)
	//{{AFX_MSG_MAP(CPageListCtrlDesign)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENU_INSERT, OnMenuInsert)
	ON_COMMAND(ID_MENU_DELETE, OnMenuDelete)
	ON_COMMAND(ID_MENU_EDIT, OnMenuEdit)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_EDIT, OnUpdateMenuasEdit)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_COMBOBOX, OnUpdateMenuasCombobox)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_BOOLCOMBOBOX, OnUpdateMenuasBoolcombobox)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_BUTTON, OnUpdateMenuasButton)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_USERCOMBOBOX, OnUpdateMenuasUsercombobox)
	ON_WM_LBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_MENUTYPE_DISABLE, OnUpdateMenutypeDisable)
	ON_UPDATE_COMMAND_UI(ID_MENUTYPE_ENABLE, OnUpdateMenutypeEnable)
	ON_UPDATE_COMMAND_UI(ID_MENUTYPE_DISABLEBLACK, OnUpdateMenutypeDisableblack)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI(ID_MENUAS_COLORCOMBOBOX, OnUpdateMenuasColorcombobox)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_UPDATE_COMMAND_UI(ID_MENUAS_SHELLFOLDER, OnUpdateMenuasShellfolder)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_ADORCOMBOBOX, OnUpdateMenuasAdorcombobox)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_DATACOMBOBOX, OnUpdateMenuasDatacombobox)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_RETURN, OnUpdateMenuasReturn)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_LINK, OnUpdateMenuasLink)
	ON_UPDATE_COMMAND_UI(ID_MENUAS_FONT, OnUpdateMenuasFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAsControls CPageListCtrlDesign::m_asControls;

// Function name	: CPageListCtrlDesign::CPageListCtrlDesign
// Description	    : default contructor
// Return type		: 
CPageListCtrlDesign::CPageListCtrlDesign()
{
	m_pContextMenu = NULL;
	m_nDefaultAs = ID_MENUAS_EDIT;
	m_nDefaultType = ID_MENUTYPE_ENABLE;
}

// Function name	: CPageListCtrlDesign::~CPageListCtrlDesign
// Description	    : virtual destructor
// Return type		: 
CPageListCtrlDesign::~CPageListCtrlDesign()
{
	RemoveContextMenu();
}

// Function name	: CPageListCtrlDesign::GetDefaultStyle
// Description	    : Called by void CPageListCtrl::OnNew(CWnd* pParentWnd, UINT nID)
// Return type		: const UINT 
const UINT CPageListCtrlDesign::GetDefaultStyle()
{
	return LVS_EDITLABELS;
}

// Function name	: CPageListCtrlDesign::GetDefaultStyle
// Description	    : 
// Return type		: const UINT 
const UINT CPageListCtrlDesign::GetDefaultExStyle()
{
	return LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
}

// Function name	: CPageListCtrlDesign::RemoveContextMenu
// Description	    : Remove the pointer to context menu, allocated in OnContextMenu
// Return type		: void 
void CPageListCtrlDesign::RemoveContextMenu()
{
	if (m_pContextMenu)
		delete m_pContextMenu;
	m_pContextMenu = NULL;
}

// Function name	: CPageListCtrlDesign::GetListCtrl
// Description	    : Get ListControl
// Return type		: CPageListCtrl* 
CPageListCtrl* CPageListCtrlDesign::GetListCtrl()
{
	if (CXFloorPropertiesWndDesign* pFloorWnd = (CXFloorPropertiesWndDesign*)GetParent())
		if (CPageListCtrl* pList = pFloorWnd->GetListCtrl(pFloorWnd->GetActivePage()))
			return pList;
	return NULL;
}

// Function name	: CPageListCtrlDesign::OnContextMenu
// Description	    : Popup Menu
// Return type		: void 
// Argument         : CWnd* pWnd
// Argument         : CPoint point
void CPageListCtrlDesign::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	RemoveContextMenu();
	m_pContextMenu = new CXDesignPopupMenu(IDR_MENU, _T("MListCtrlDesign"), point, this);
	CMenu* pPopupMenu  = m_pContextMenu->GetPopupMenu();
	if (pPopupMenu)
	{
		BOOL bFocused = FALSE;
		BOOL bSelected = FALSE;
		CPageListCtrl* pList = GetListCtrl();
		if (pList)
		{
			bFocused = pList->GetNextItem(-1, LVNI_FOCUSED) >= 0;
			bSelected = pList->GetNextItem(-1, LVNI_SELECTED) >= 0;
		}
		pPopupMenu->CheckMenuItem(m_nDefaultAs, MF_CHECKED | MF_BYCOMMAND);
		pPopupMenu->CheckMenuItem(m_nDefaultType, MF_CHECKED | MF_BYCOMMAND);
		pPopupMenu->EnableMenuItem(ID_MENU_EDIT, (bFocused ? MF_ENABLED : MF_DISABLED | MF_GRAYED) | MF_BYCOMMAND);
		pPopupMenu->EnableMenuItem(ID_MENU_DELETE, (bSelected ? MF_ENABLED : MF_DISABLED | MF_GRAYED) | MF_BYCOMMAND);
		VERIFY(m_pContextMenu->Show());
	}
}

// Function name	: CPageListCtrlDesign::Load
// Description	    : Load all items
// Return type		: void 
// Argument         : CString& stream
void CPageListCtrlDesign::Load(CString& stream)
{
	CPageListCtrl::Load(stream);
	RefreshIDs();
}

// Function name	: CPageListCtrlDesign::RefreshIDs
// Description	    : refresh the column with IDs
// Return type		: void 
void CPageListCtrlDesign::RefreshIDs()
{
	for (int i = 0; i < GetItemCount(); i++)
	{
		CString t; t.Format(_T("%i"), i);
		SetItemText(i, 3, t);
	}
}

// Function name	: CPageListCtrlDesign::OnMenuInsert
// Description	    : User select Insert menu.
// Return type		: void 
void CPageListCtrlDesign::OnMenuInsert() 
{
	if (CPageListCtrl* pList = GetListCtrl())
	{
		int nItemFocused = pList->GetNextItem(-1, LVNI_FOCUSED);
		nItemFocused = nItemFocused == -1 ? pList->GetItemCount() : nItemFocused + 1;
		int nItem = pList->InsertItem(nItemFocused, defaultLabelNewItem);
		pList->SetItemText(nItem, 1, m_asControls.GetName(m_nDefaultAs));
		pList->SetItemText(nItem, 2, DEFAULTTYPE);
		pList->EditLabel(nItem);
		GetPropertiesWndPropPage()->SetModifiedFlag();
	}
	RefreshIDs();
}

// Function name	: CPageListCtrlDesign::OnMenuDelete
// Description	    : User Select Delete Row
// Return type		: void 
void CPageListCtrlDesign::OnMenuDelete() 
{
	if (CPageListCtrl* pList = GetListCtrl())
	{
		int nItemSelected = pList->GetNextItem(-1, LVNI_SELECTED);
		while (nItemSelected >= 0)
		{
			pList->DeleteItem(nItemSelected);
			nItemSelected = pList->GetNextItem(-1, LVNI_SELECTED);
		}
		GetPropertiesWndPropPage()->SetModifiedFlag();
		RefreshIDs();
	}
}

// Function name	: CPageListCtrlDesign::OnMenuEdit
// Description	    : Edit item
// Return type		: void 
void CPageListCtrlDesign::OnMenuEdit() 
{
	if (CPageListCtrl* pList = GetListCtrl())
	{
		int nItemFocused = pList->GetNextItem(-1, LVNI_FOCUSED);
		if (nItemFocused >= 0)
		{
			pList->EditLabel(nItemFocused);
			GetPropertiesWndPropPage()->SetModifiedFlag();
		}

	}

}

// Function name	: CPageListCtrlDesign::ChangeAs
// Description	    : Change the selected items to be nIDAs control
// Return type		: void 
// Argument         : UINT nIDAs
void CPageListCtrlDesign::ChangeAs(UINT nIDAs)
{
	if (CPageListCtrl* pList = GetListCtrl())
	{
		int nItemSelected = pList->GetNextItem(-1, LVNI_SELECTED);
		while (nItemSelected >= 0)
		{
			pList->SetItemText(nItemSelected, 1, m_asControls.GetName(m_nDefaultAs));
			nItemSelected = pList->GetNextItem(nItemSelected, LVNI_SELECTED);
		}
		GetPropertiesWndPropPage()->SetModifiedFlag();
	}
}

// Function name	: CPageListCtrlDesign::ChangeType
// Description	    : Change the selected items to be Enable or Disable
// Return type		: void 
// Argument         : UINT nIDAs
void CPageListCtrlDesign::ChangeType(UINT nIDAs)
{
	if (CPageListCtrl* pList = GetListCtrl())
	{
		int nItemSelected = pList->GetNextItem(-1, LVNI_SELECTED);
		while (nItemSelected >= 0)
		{
			pList->SetItemText(nItemSelected, 2, DEFAULTTYPE);
			nItemSelected = pList->GetNextItem(nItemSelected, LVNI_SELECTED);
		}
		GetPropertiesWndPropPage()->SetModifiedFlag();
	}
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasEdit
// Description	    : Update menu item ID_MENUAS_EDIT
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasEdit(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_EDIT;
	ChangeAs(m_nDefaultAs);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasCombobox
// Description	    : Update menu item ID_MENUAS_COMBOBOX
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasCombobox(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_COMBOBOX;
	ChangeAs(m_nDefaultAs);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasBoolcombobox
// Description	    : Update menu item ID_MENUAS_BOOLCOMBOBOX
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasBoolcombobox(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_BOOLCOMBOBOX;
	ChangeAs(m_nDefaultAs);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasButton
// Description	    : Update menu item ID_MENUAS_BUTTON
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasButton(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_BUTTON;
	ChangeAs(m_nDefaultAs);
}

void CPageListCtrlDesign::OnUpdateMenuasLink(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_LINK;
	ChangeAs(m_nDefaultAs);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasAdorcombobox
// Description	    : 
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasAdorcombobox(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_ADORCOMBOBOX;
	ChangeAs(m_nDefaultAs);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasDatacombobox
// Description	    : 
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasDatacombobox(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_DATACOMBOBOX;
	ChangeAs(m_nDefaultAs);
}

void CPageListCtrlDesign::OnUpdateMenuasFont(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_FONT;
	ChangeAs(m_nDefaultAs);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasUsercombobox
// Description	    : Update menu item ID_MENUAS_USERCOMBBOX
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasUsercombobox(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_USERCOMBOBOX;
	ChangeAs(m_nDefaultAs);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasShellfolder
// Description	    : 
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasShellfolder(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_SHELLFOLDER;
	ChangeAs(m_nDefaultAs);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenuasColorcombobox
// Description	    : Update menu item ID_MENUAS_COLORCOMBOBOX
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenuasColorcombobox(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_COLORCOMBOBOX;
	ChangeAs(m_nDefaultAs);
}

void CPageListCtrlDesign::OnUpdateMenuasReturn(CCmdUI* pCmdUI) 
{
	m_nDefaultAs = ID_MENUAS_RETURN;
	ChangeAs(m_nDefaultAs);
}


// Function name	: CPageListCtrlDesign::OnUpdateMenutypeDisable
// Description	    : Update menu item ID_MENUTYPE_DISABLE
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenutypeDisable(CCmdUI* pCmdUI) 
{
	m_nDefaultType = ID_MENUTYPE_DISABLE;
	ChangeType(m_nDefaultType);
}

// Function name	: CPageListCtrlDesign::OnUpdateMenutypeEnable
// Description	    : Update menu item ID_MENUTYPE_ENABLE
// Return type		: void 
// Argument         : CCmdUI* pCmdUI
void CPageListCtrlDesign::OnUpdateMenutypeEnable(CCmdUI* pCmdUI) 
{
	m_nDefaultType = ID_MENUTYPE_ENABLE;
	ChangeType(m_nDefaultType);
}

void CPageListCtrlDesign::OnUpdateMenutypeDisableblack(CCmdUI* pCmdUI) 
{
	m_nDefaultType = ID_MENUTYPE_DISABLEBLACK;
	ChangeType(m_nDefaultType);
}

// Function name	: CPageListCtrlDesign::Save
// Description	    : Save the items
// Return type		: void 
// Argument         : CString & stream
void CPageListCtrlDesign::Save(CString & stream)
{
	int n = GetItemCount();
	for (int i = 0; i < n; i++)
		stream += GetItemText(i, 0) + _T("\\") + GetItemText(i, 1) + _T("\\") + GetItemText(i, 2) + CString(_cPagesSeparator);
}


// Function name	: CPageListCtrlDesign::OnLoad
// Description	    : Called by CPageListCtrl::Load function. In Design time
// Return type		: void 
// Argument         : int nItem
// Argument         : LPCTSTR lpszAs
void CPageListCtrlDesign::OnLoad(int nItem, LPCTSTR lpszAs, LPCTSTR lpszType)
{
	SetItemText(nItem, 1, lpszAs);
	SetItemText(nItem, 2, lpszType);
}

// Function name	: CPageListCtrlDesign::OnInit
// Description	    : Insert a new colum for enable/disable
// Return type		: BOOL 
BOOL CPageListCtrlDesign::OnInit()
{
	InsertColumn(0, _T("Name"), LVCFMT_LEFT, 96);
	InsertColumn(1, _T("Value"), LVCFMT_LEFT, 128);
	InsertColumn(2, _T("Type"), LVCFMT_LEFT, 48);
	InsertColumn(3, _T("ID"), LVCFMT_LEFT, 48);
	return TRUE;
}

// Function name	: CPageListCtrlDesign::OnLButtonDblClk
// Description	    : If user dblclk in design time
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrlDesign::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// Do not call CPageListCtrl::OnLButtonDblClk(nFlags, point);
	CListCtrl::OnLButtonDblClk(nFlags, point);
}


void CPageListCtrlDesign::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Do not call CPageListCtrl::OnMouseMove(nFlags, point);
	CListCtrl::OnMouseMove(nFlags, point);
}

void CPageListCtrlDesign::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// Do not call CPageListCtrl::OnLButtonUp(nFlags, point);
	CListCtrl::OnLButtonUp(nFlags, point);
}

// Function name	: CPageListCtrlDesign::OnLButtonDown
// Description	    : User click mouse in design time
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrlDesign::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Do not call CListCtrl::OnLButtonDown(nFlags, point);
	CListCtrl::OnLButtonDown(nFlags, point);
}


// Function name	: CPageListCtrlDesign::OnRButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrlDesign::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// Do not call CPageListCtrl::OnRButtonDown(nFlags, point);
	CListCtrl::OnRButtonDown(nFlags, point);
}

// Function name	: CPageListCtrlDesign::OnRButtonUp
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrlDesign::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// Do not call CPageListCtrl::OnRButtonUp(nFlags, point);
	CListCtrl::OnRButtonUp(nFlags, point);
}

// Function name	: CListCtrlDesign::OnRButtonDblClk
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CPageListCtrlDesign::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// Do not call CPageListCtrl::OnRButtonDblClk(nFlags, point);
	CListCtrl::OnRButtonDblClk(nFlags, point);
}


// Function name	: CPageListCtrlDesign::GetControlWnd
// Description	    : return NULL in design time
// Return type		: CXPropertiesWndCtrl* 
CXPropertiesWndCtrl* CPageListCtrlDesign::GetControlWnd()
{
	return NULL;
}

// Function name	: CPageListCtrlDesign::GetPropertiesWndPropPage
// Description	    : 
// Return type		: CXPropertiesWndPropPage* 
CXPropertiesWndPropPage* CPageListCtrlDesign::GetPropertiesWndPropPage()
{
	return (CXPropertiesWndPropPage*)GetParent()->GetParent();
}

// Function name	: CPageListCtrlDesign::WindowProc
// Description	    : Correct repaint bug after user select from menu
// Return type		: LRESULT 
// Argument         : UINT message
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CPageListCtrlDesign::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lResult = CPageListCtrl::WindowProc(message, wParam, lParam);
	if (message == WM_COMMAND)
		if (HIWORD(wParam) == 0)
			Invalidate();
	
	return lResult;
}

// Function name	: CPageListCtrlDesign::IsSizingLine
// Description	    : Page design do not accept the resizing column, may be tomorrow
// Return type		: BOOL 
BOOL CPageListCtrlDesign::IsSizingLine()
{
	return FALSE;
}

