/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 10:22:23 AM
  Comments: XFloorPropertiesWnd.cpp: implementation of the CXFloorPropertiesWnd class.
 ************************************/

#include "stdafx.h"
#include "XPropertiesWnd.h"
#include "XFloorPropertiesWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CXFloorPropertiesWnd, CXFloorWnd)
	//{{AFX_MSG_MAP(CXFloorPropertiesWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Function name	: CXFloorPropertiesWnd::CXFloorPropertiesWnd
// Description	    : default constuctor
// Return type		: 
CXFloorPropertiesWnd::CXFloorPropertiesWnd(/*CXPropertiesWndCtrl* pControlWnd*/)
{
}

// Function name	: CXFloorPropertiesWnd::~CXFloorPropertiesWnd
// Description	    : virtual destructor
// Return type		: 
CXFloorPropertiesWnd::~CXFloorPropertiesWnd()
{
	while (m_arPagesListCtrl.GetSize())
	{
		delete m_arPagesListCtrl[0];
		m_arPagesListCtrl.RemoveAt(0);
	}
	CControlsWnd::KillAll();
}

// Function name	: CXFloorPropertiesWnd::AddPage
// Description	    : Add a new page, will insert a CPageListCtrl
// Return type		: short 
// Argument         : LPCTSTR sName
short CXFloorPropertiesWnd::AddPage(LPCTSTR sName, CXPropertiesWndCtrl* pControl)
{
	short nResult = CXFloorWnd::AddPage(sName);
	if (nResult >= 0)
		if (CPageListCtrl* pPageListCtrl = NewPageListCtrl(nResult, pControl))
		{
			RefreshPages();
			AttachWindow(nResult, (long)pPageListCtrl);
			pPageListCtrl->SetIndexPage(m_arPagesListCtrl.Add(pPageListCtrl));
			Init();
		}
	return nResult;
}

// Function name	: CXFloorPropertiesWnd::DeletePage
// Description	    : When Delete a page delete the attached CPageListCtrl
// Return type		: BOOL 
// Argument         : short nIndex
BOOL CXFloorPropertiesWnd::DeletePage(short nIndex)
{
	BOOL bResult = CXFloorWnd::DeletePage(nIndex);
	if (bResult)
		if (nIndex < m_arPagesListCtrl.GetSize())
			{
				delete m_arPagesListCtrl[nIndex];
				m_arPagesListCtrl.RemoveAt(nIndex);
				RefreshPages();
			}
	return bResult;
}

// Function name	: CXFloorPropertiesWnd::NewPageListCtrl
// Description	    : 
// Return type		: CPageListCtrl* 
CPageListCtrl* CXFloorPropertiesWnd::NewPageListCtrl(int nIndex, CXPropertiesWndCtrl* pControl)
{
	ASSERT (pControl != NULL);
	CPageListCtrl* pPageListCtlr = new CPageListCtrl(pControl);
	pPageListCtlr->OnNew(this, nIndex + _nIDFirstListView);
	return pPageListCtlr;
}

// Function name	: CXFloorPropertiesWnd::GetListCtrl
// Description	    : GetListControl
// Return type		: CPageListCtrl* 
// Argument         : int nIndex
CPageListCtrl* CXFloorPropertiesWnd::GetListCtrl(int nIndex)
{
	if ((nIndex >= 0) && (nIndex < m_arPagesListCtrl.GetSize()))
		return m_arPagesListCtrl[nIndex];
	return NULL;
}


// Function name	: CXFloorPropertiesWndDesign::Load
// Description	    : Fill this control with stream string
// Return type		: void 
void CXFloorPropertiesWnd::Load(CString& stream, CXPropertiesWndCtrl* pControl)
{
	if (GetControlUnknown())
	{
		CWnd* pWnd = (CWnd*)pControl;

		while (DeletePage(0));
		// Change the style to new one...
		StyleAs(m_bAsFloor);

		if (!stream.IsEmpty())
		{
			CString sPage, sName;
			int nNewPage = -1;
			for (int i = 0, nBracket = 0; ; i++)
			{
				CString sLine;
				AfxExtractSubString(sLine, stream, i, _cPagesSeparator);
				if (sLine.IsEmpty())
					break;
				if (sLine == _T("{"))
				{
					nBracket++;
					if (!sName.IsEmpty())
						if (nBracket == 1)
							nNewPage = AddPage(sName, pControl);
				}
				else
					if (sLine == _T("}"))
					{
						nBracket--;
						if (nBracket == 0)
							if (nNewPage >= 0)
								GetListCtrl(nNewPage)->Load(sPage);
						nBracket = max(0,nBracket);
						sPage.Empty();
					}
				else
					switch (nBracket)
					{
						case 0:
							{
								sName = sLine;
								break;
							}
						case 1:
							{
								sPage += sLine + CString(_cPagesSeparator);
							}
					}
			}
		}
	}
}

// Function name	: CXFloorPropertiesWnd::SetAutoResizingColumns
// Description	    : Set TRUE or FALSE for resizing listctrl
// Return type		: void 
// Argument         : BOOL bValue
void CXFloorPropertiesWnd::SetAutoResizingColumns(BOOL bValue)
{
	CPageListCtrl::m_bAutoResizingColumns = bValue;
}

// Function name	: CXFloorPropertiesWnd::SetSignEnableDisable
// Description	    : Set or not 
// Return type		: void 
// Argument         : BOOL bValue
void CXFloorPropertiesWnd::SetSignEnableDisable(BOOL bValue)
{
	m_bSignEnableDisable = bValue;
}

// Function name	: CXFloorPropertiesWnd::GetSignEnableDisable
// Description	    : 
// Return type		: const BOOL 
const BOOL CXFloorPropertiesWnd::GetSignEnableDisable()
{
	return m_bSignEnableDisable;
}

// Function name	: CXFloorPropertiesWnd::RefreshPages
// Description	    : 
// Return type		: void 
void CXFloorPropertiesWnd::RefreshPages()
{
	if (!m_bFirstPageHasCaption)
		if (long cPages = GetPagesCount())
			SetHeight(0, cPages == 1 ? 0 : 20);
}
