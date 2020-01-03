/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 12:03:03 PM
  Comments: XFloorPropertiesWndDesign.cpp: implementation of the CXFloorPropertiesWndDesign class.
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "XFloorPropertiesWndDesign.h"
#include "PageListCtrlDesign.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Function name	: CXFloorPropertiesWndDesign::CXFloorPropertiesWndDesign
// Description	    : default contructor
// Return type		: 
CXFloorPropertiesWndDesign::CXFloorPropertiesWndDesign()
{

}

// Function name	: CXFloorPropertiesWndDesign::~CXFloorPropertiesWndDesign
// Description	    : virtual destructor
// Return type		: 
CXFloorPropertiesWndDesign::~CXFloorPropertiesWndDesign()
{

}

// Function name	: CXFloorPropertiesWndDesign::NewPageListCtrl
// Description	    : Virtual function.This will return CPageListCtrlDesign* page
// Return type		: CPageListCtrl* 
// Argument         : int nIndex
CPageListCtrl* CXFloorPropertiesWndDesign::NewPageListCtrl(int nIndex, CXPropertiesWndCtrl* pControl )
{
	ASSERT (pControl == NULL);
	CPageListCtrlDesign* pPageListCtlrDesign = new CPageListCtrlDesign();
	pPageListCtlrDesign->OnNew(this, nIndex + _nIDFirstListView);
	return pPageListCtlrDesign;
}

// Function name	: CXFloorPropertiesWndDesign::DataExchange
// Description	    : Called by CXPropertiesWndPropPage.DoDataExchange
// Return type		: void 
// Argument         : CDataExchange * pDX
void CXFloorPropertiesWndDesign::DataExchange(CDataExchange * pDX)
{
	CString sPagesAndItems;
	if (pDX->m_bSaveAndValidate) Fill(sPagesAndItems);
	CXPropertiesWndPropPage* pParent = (CXPropertiesWndPropPage*)GetParent();
	DDP_DEFINE<CString>(pParent, pDX->m_bSaveAndValidate, &sPagesAndItems, _T("PagesAndItems"), VT_BSTR);
	if (!pDX->m_bSaveAndValidate) Load(sPagesAndItems);
}

// Function name	: CXFloorPropertiesWndDesign::Fill
// Description	    : Called by DataExhange to construct the sPagesItems string
// stream will be the following form.
// Page 1
// {
//	Name\Edit
//	Notes\Edit
//	Visible\BoolComboBox
// }
// Page 2
// {
//	...
// }
//
//
//
// Return type		: void 
void CXFloorPropertiesWndDesign::Fill(CString& stream)
{
	CString s(_cPagesSeparator);
	for (int i = 0; IsPage(i); i++)
	{
		stream += GetPageName(i) + s + _T("{") + s;
		GetListCtrl(i)->Save(stream);
		stream += _T("}") + s;
	}
}

BOOL CXFloorPropertiesWndDesign::OnCommand( WPARAM wParam, LPARAM lParam )
{
	CXPropertiesWndPropPage* pParent = (CXPropertiesWndPropPage*)GetParent();
	if (LOWORD(wParam) == (pParent)->m_edtRename.GetDlgCtrlID())
		if (HIWORD(wParam) == EN_KILLFOCUS)
			pParent->RenamePage(pParent->m_nRenamePage);
	return CXFloorPropertiesWnd::OnCommand(wParam, lParam);
}

