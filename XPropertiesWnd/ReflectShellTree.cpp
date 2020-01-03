/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 11/7/98 10:21:58
  Comments: ReflectShellTree.cpp: implementation of the CReflectShellTree class.
 ************************************/

#include "stdafx.h"
#include "ControlsWnd.h"
#include "XPropertiesWndCtl.h"
#include "ReflectShellTree.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CReflectShellTree, CShellTree)
	//{{AFX_MSG_MAP(CReflectShellTree)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReflectShellTree message handlers

// Function name	: CReflectShellTree::CReflectShellTree
// Description	    : default constructor
// Return type		: 
CReflectShellTree::CReflectShellTree()
{
	m_nFlags = NOFLAG;
	m_pControlFolder = NULL;
}

// Function name	: CReflectShellTree::~CReflectShellTree
// Description	    : virtual destrcutor
// Return type		: 
CReflectShellTree::~CReflectShellTree()
{

}

#define defaultStyles TVS_HASLINES | TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_HASBUTTONS
#define defaultSize CSize(164,128) 
// Function name	: CReflectShellTree::CreatePopup
// Description	    : Create a popup window filled with shell folders
// Return type		: CReflectShellTree* 
// Argument         : CControlsWnd_CShellFolder* pControlFolder
// Argument         : FLAGS nFlags
CReflectShellTree* CReflectShellTree::CreatePopup(CControlsWnd_CShellFolder* pControlFolder, FLAGS nFlags)
{
	ASSERT(!IsWindow(GetSafeHwnd()));
    CPoint p(0,0);
	if (!CWnd::CreateEx(WS_EX_TOOLWINDOW, _T("SysTreeView32"), _T(""), WS_BORDER | WS_POPUP | defaultStyles, 
                        p.x, p.y, defaultSize.cx, defaultSize.cy, 
                        pControlFolder->GetControl()->GetSafeHwnd(), 0, NULL))
        return NULL;
	m_pControlFolder = pControlFolder;
	PopulateTree();
	EnableImages();
	m_nFlags = nFlags;
	if (IsCaptured())
		SetCapture();
	return this;
}

// Function name	: CReflectShellTree::IsCaptured
// Description	    : 
// Return type		: BOOL 
BOOL CReflectShellTree::IsCaptured()
{
	return m_nFlags & STS_CAPTURE;
}


// Function name	: CReflectShellTree::OnItemexpanding
// Description	    : Override the reflected message TVN_ITEMEXPANDING
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CReflectShellTree::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	FolderExpanding(pNMHDR, pResult) ;
	
	*pResult = 0;
}

// Function name	: CReflectShellTree::OnRclick
// Description	    : 
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CReflectShellTree::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (!IsCaptured())
		FolderPopup(pNMHDR,pResult);	
	*pResult = 0;
}

// Function name	: CReflectShellTree::OnKillFocus
// Description	    : 
// Return type		: void 
// Argument         : CWnd* pNewWnd
void CReflectShellTree::OnKillFocus(CWnd* pNewWnd) 
{
	if (IsCaptured())
		Out(TRUE);
	CShellTree::OnKillFocus(pNewWnd);
}

// Function name	: CReflectShellTree::Out
// Description	    : 
// Return type		: void 
// Argument         : BOOL bCancel
void CReflectShellTree::Out(BOOL bCancel)
{
	ASSERT (IsCaptured());
	ReleaseCapture();
	GetSelectedFolderPath(m_sSelectedPath);
	ShowWindow(SW_HIDE);
	// If this is not a cancel operation, notify...
	if (!bCancel)
		m_pControlFolder->OnDestroy();
}

// Function name	: CReflectShellTree::OnLButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CReflectShellTree::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (IsCaptured())
	{
		CPoint p; GetCursorPos(&p);
		CRect rect; GetClientRect(rect);
		ClientToScreen(&rect);
		if (!rect.PtInRect(p))
		{
			LPARAM lParam = MAKELPARAM(p.x, p.y);
			ReleaseCapture();
			SendMessage(WM_NCLBUTTONDOWN,SendMessage(WM_NCHITTEST, 0, lParam), lParam);
			SetCapture();
		}
	}
	CShellTree::OnLButtonDown(nFlags, point);
}

// Function name	: CReflectShellTree::OnLButtonUp
// Description	    : If user click outside 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CReflectShellTree::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	CShellTree::OnLButtonUp(nFlags, point);

	if (IsCaptured())
	{
		CPoint p = GetMessagePos();
		CRect rect; GetWindowRect(rect);
		if (!rect.PtInRect(p))
			Out();
	}
}

// Function name	: CReflectShellTree::SetDefaultPath
// Description	    : 
// Return type		: void 
// Argument         : LPCTSTR lpszPathName
void CReflectShellTree::SetDefaultPath(LPCTSTR lpszPathName)
{
	//not implemented yet
}

// Function name	: CReflectShellTree::OnKeyDown
// Description	    : I will trap here the VK_ENTER key
// Return type		: void 
// Argument         : UINT nChar
// Argument         : UINT nRepCnt
// Argument         : UINT nFlags
void CReflectShellTree::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_SPACE:	
		case VK_RETURN:
		{
			Out();
			break;
		}
	}
	CShellTree::OnKeyDown(nChar, nRepCnt, nFlags);
}

