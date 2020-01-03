/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/8/98 5:46:48 PM
  Comments: PagesListCtrl.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "XFloorWnd.h"
#include "PagesListCtrl.h"
#include "XFloorWndPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPagesListCtrl

// Function name	: CPagesListCtrl::CPagesListCtrl
// Description	    : Default constuctor
// Return type		: 
CPagesListCtrl::CPagesListCtrl()
{
	m_nNamePageCol = -1;
	m_nUserDataCol = NULL;
	m_nAutoAdd = -1;
}

// Function name	: CPagesListCtrl::~CPagesListCtrl
// Description	    : virtual destructor
// Return type		: 
CPagesListCtrl::~CPagesListCtrl()
{
}


BEGIN_MESSAGE_MAP(CPagesListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CPagesListCtrl)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagesListCtrl message handlers


// Function name	: CPagesListCtrl::Init
// Description	    : Call this once for init all variables
// Return type		: void 
void CPagesListCtrl::Init()
{
	ListView_SetExtendedListViewStyle(m_hWnd, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	m_nNamePageCol = InsertColumn(0, _T("Name"), LVCFMT_LEFT, 168);
	m_nUserDataCol = InsertColumn(1, _T("UserData"), LVCFMT_LEFT, 168);
}

// Function name	: CPagesListCtrl::OnEndlabeledit
// Description	    : End the edit item. Notify all that needs
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CPagesListCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	CString item;
	GetEditControl()->GetWindowText(item);
	CString sItem, sUser;
	AfxExtractSubString(sItem, item, 0, TCHAR('\\'));
	AfxExtractSubString(sUser, item, 1, TCHAR('\\'));
	CString sUserX;
	sUserX.Format(_T("%i"),atoi((LPCTSTR)sUser));
	if (sUserX != sUser)
		sUser.Empty();
	SetItemText(pDispInfo->item.iItem,m_nNamePageCol, sItem);
	SetItemText(pDispInfo->item.iItem,m_nUserDataCol, sUser);
	if (pDispInfo->item.iItem == m_nAutoAdd)
	{
		if (!sItem.IsEmpty())
			m_nAutoAdd = InsertItem(GetItemCount(), _T(""));
	}
	else
		if (sItem.IsEmpty())
		{
			DeleteItem(m_nAutoAdd);
			m_nAutoAdd = pDispInfo->item.iItem;
		}

	NParent();

	*pResult = 0;
}

// Function name	: CPagesListCtrl::OnBeginlabeledit
// Description	    : begin the edit item
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CPagesListCtrl::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	if (GetItemText(pDispInfo->item.iItem,pDispInfo->item.iSubItem).IsEmpty())
		m_nAutoAdd = pDispInfo->item.iItem;
	else
		if (!GetItemText(pDispInfo->item.iItem,m_nUserDataCol).IsEmpty())
			GetEditControl()->SetWindowText(GetItemText(pDispInfo->item.iItem,m_nNamePageCol) + _T("\\") + GetItemText(pDispInfo->item.iItem,m_nUserDataCol));
	*pResult = 0;
}

// Function name	: CPagesListCtrl::NParent
// Description	    : Notify the OLE page, that something is happen
// Return type		: void 
void CPagesListCtrl::NParent()
{
	if (CXFloorWndPropPage* pOLEPage = (CXFloorWndPropPage*)GetParent())
	{
		pOLEPage->ConstructPagesAsString();
		pOLEPage->SetModifiedFlag();
	}
}

// Function name	: CPagesListCtrl::Fill
// Description	    : Fill list with string lpszPages. Pag1\nPag2...
// Return type		: void 
// Argument         : LPCTSTR lpszPages
void CPagesListCtrl::Fill(LPCTSTR lpszPages)
{
	CString sItem, sName, sUser;
	int i = 0;
	do
	{
		AfxExtractSubString(sItem, lpszPages, i++, _cPagesSeparator);
		AfxExtractSubString(sName, sItem, 0, TCHAR('\\'));
		AfxExtractSubString(sUser, sItem, 1, TCHAR('\\'));
		if (!sName.IsEmpty())
		{
			int nItem = InsertItem(GetItemCount(), _T(""));
			SetItemText(nItem,m_nNamePageCol, sName);
			SetItemText(nItem,m_nUserDataCol, sUser);
		}

	} while (!sName.IsEmpty());
	InsertItem(GetItemCount(), _T(""));
}

// Function name	: CPagesListCtrl::OnKeydown
// Description	    : If some keys is pressed treat separatly
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CPagesListCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	int nFocused = GetNextItem(-1, LVNI_FOCUSED);
	if (nFocused >= 0)
		switch (pLVKeyDow->wVKey)
		{
			case VK_F2:
			case VK_F4:
				{
					// Edit only focused item
					EditLabel(nFocused);
					break;
				}
			case VK_DELETE:
				{
					// delete all selected items
					int nSelected = NULL;
					int nextItem = -1;
					while ((nSelected = GetNextItem(nextItem,LVNI_SELECTED))>=0)
						if (GetItemText(nSelected, m_nNamePageCol).IsEmpty())
						{
							m_nAutoAdd = nSelected;
							nextItem = m_nAutoAdd + 1;
						}
						else
							DeleteItem(nSelected);
					NParent();
					break;
				}
		}
	
	*pResult = 0;
}

