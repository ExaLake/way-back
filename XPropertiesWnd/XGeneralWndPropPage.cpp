/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/15/98 10:13:41 AM
  Comments: XGeneralWndPropPage.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "XGeneralWndPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXGeneralWndPropPage dialog

IMPLEMENT_DYNCREATE(CXGeneralWndPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CXGeneralWndPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CXGeneralWndPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

// {73EF45B7-63FE-11D2-86BD-0040055C08D9}
IMPLEMENT_OLECREATE_EX(CXGeneralWndPropPage, "XPropertiesWnd.CXGeneralWndPropPage",
	0x73ef45b7, 0x63fe, 0x11d2, 0x86, 0xbd, 0x0, 0x40, 0x5, 0x5c, 0x8, 0xd9)


/////////////////////////////////////////////////////////////////////////////
// CXGeneralWndPropPage::CXGeneralWndPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CXGeneralWndPropPage

BOOL CXGeneralWndPropPage::CXGeneralWndPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_XPROPERTIESWND_GENERAL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CXGeneralWndPropPage::CXGeneralWndPropPage - Constructor

CXGeneralWndPropPage::CXGeneralWndPropPage() :
	COlePropertyPage(IDD, IDS_XPROPERTIESWND_PPG_GENERAL_CAPTION)
{
	//{{AFX_DATA_INIT(CXGeneralWndPropPage)
	m_bToolTip = FALSE;
	m_bFirstPageHasCaption = FALSE;
	m_bAsFloor = FALSE;
	m_bResizeFirstColumn = FALSE;
	m_bAnimation = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CXGeneralWndPropPage::DoDataExchange - Moves data between page and properties

void CXGeneralWndPropPage::DoDataExchange(CDataExchange* pDX)
{
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_DATA_MAP(CXGeneralWndPropPage)
	DDP_Check(pDX, IDC_CHECK_TOOLTIP, m_bToolTip, _T("ToolTips") );
	DDX_Check(pDX, IDC_CHECK_TOOLTIP, m_bToolTip);
	DDP_Check(pDX, IDC_CHECK_FIRSTPAGECAPTION, m_bFirstPageHasCaption, _T("FirstPageHasCaption") );
	DDX_Check(pDX, IDC_CHECK_FIRSTPAGECAPTION, m_bFirstPageHasCaption);
	DDP_Check(pDX, IDC_CHECK_ASFLOOR, m_bAsFloor, _T("AsFloor") );
	DDX_Check(pDX, IDC_CHECK_ASFLOOR, m_bAsFloor);
	DDP_Check(pDX, IDC_CHECK_RESIZEFIRST, m_bResizeFirstColumn, _T("ResizeFirstColumn") );
	DDX_Check(pDX, IDC_CHECK_RESIZEFIRST, m_bResizeFirstColumn);
	DDP_Check(pDX, IDC_CHECK_ANIMATION, m_bAnimation, _T("Animation"));
	DDX_Check(pDX, IDC_CHECK_ANIMATION, m_bAnimation);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CXGeneralWndPropPage message handlers
