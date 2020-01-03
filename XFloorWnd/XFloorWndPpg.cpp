/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/10/98 1:39:58 PM
  Comments: XFloorWndPpg.cpp : Implementation of the CXFloorWndPropPage property page class.
 ************************************/

#include "stdafx.h"
#include "XFloorWnd.h"
#include "XFloorWndPpg.h"
#include "FloorPageObject.h"
#include <atlconv.h>
#include <afxconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CXFloorWndPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CXFloorWndPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CXFloorWndPropPage)
	ON_BN_CLICKED(IDC_CHECK_ANIMATION, OnCheckAnimation)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_SIGN, OnCheckSign)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CXFloorWndPropPage, "XFLOORWND.XFloorWndPropPage.1",
	0x24ffd1ee, 0x5ea9, 0x11d2, 0x86, 0xb1, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9)


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndPropPage::CXFloorWndPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CXFloorWndPropPage

// Function name	: CXFloorWndPropPage::CXFloorWndPropPageFactory::UpdateRegistry
// Description	    : 
// Return type		: BOOL 
// Argument         : BOOL bRegister
BOOL CXFloorWndPropPage::CXFloorWndPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_XFLOORWND_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndPropPage::CXFloorWndPropPage - Constructor
CXFloorWndPropPage::CXFloorWndPropPage() :
	COlePropertyPage(IDD, IDS_XFLOORWND_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CXFloorWndPropPage)
	m_bAnimation = FALSE;
	m_bSign = FALSE;
	m_bAsPage = FALSE;
	//}}AFX_DATA_INIT
	m_nSleep = 0;
}


/////////////////////////////////////////////////////////////////////////////
// CXFloorWndPropPage::DoDataExchange - Moves data between page and properties

// Function name	: CXFloorWndPropPage::DoDataExchange
// Description	    : Save data throw OLE controls
// Return type		: void 
// Argument         : CDataExchange* pDX
void CXFloorWndPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CXFloorWndPropPage)
	DDX_Control(pDX, IDC_STATIC_SLEEP, m_sSleep);
	DDX_Control(pDX, IDC_SLIDER_ANIMATION, m_sliderAnimation);
	DDX_Control(pDX, IDC_LIST_PAGES, m_listPages);
	DDP_Check(pDX, IDC_CHECK_ANIMATION, m_bAnimation, _T("Animation") );
	DDX_Check(pDX, IDC_CHECK_ANIMATION, m_bAnimation);
	DDP_Check(pDX, IDC_CHECK_SIGN, m_bSign, _T("Sign") );
	DDX_Check(pDX, IDC_CHECK_SIGN, m_bSign);
	DDP_Check(pDX, IDC_CHECK_PAGE, m_bAsPage, _T("AsPage"));
	DDX_Check(pDX, IDC_CHECK_PAGE, m_bAsPage);
	//}}AFX_DATA_MAP
	DDP_Long(pDX, &m_nSleep, _T("Sleep"));
	DDP_String(pDX, &m_sPages, _T("Pages"));
	DDP_PostProcessing(pDX);
	UpdateMSecond();
}

// Function name	: CXFloorWndPropPage::UpdateMSecond
// Description	    : Update all static controls, after some data change
// Return type		: void 
void CXFloorWndPropPage::UpdateMSecond()
{
	m_sliderAnimation.SetRange(0,16);
	m_sliderAnimation.EnableWindow(m_bAnimation);
	m_sSleep.EnableWindow(m_bAnimation);
	m_sliderAnimation.SetPos(m_nSleep);
	CString sSleep; sSleep.Format(_T("%i ms"), m_nSleep * MulSleep);
	m_sSleep.SetWindowText(sSleep);
	UpdateStatic(m_bAnimation, IDC_STATIC_SCROLL);
}

void CXFloorWndPropPage::UpdateStatic(BOOL bValue, UINT idStatic)
{
	CString text;
	CWnd* pStatic = GetDlgItem(idStatic);
	pStatic->GetWindowText(text); AfxExtractSubString(text,text,0,TCHAR(':'));
	text += CString(_T(": ")) + (bValue ? _T("on") : _T("off"));
	pStatic->SetWindowText(text);
}

/////////////////////////////////////////////////////////////////////////////
// CXFloorWndPropPage message handlers

// Function name	: CXFloorWndPropPage::OnInitDialog
// Description	    : 
// Return type		: BOOL 
BOOL CXFloorWndPropPage::OnInitDialog() 
{
	COlePropertyPage::OnInitDialog();
	
	m_listPages.Init();
	m_listPages.Fill(m_sPages);
	OnObjectsChanged();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Function name	: CXFloorWndPropPage::OnObjectsChanged
// Description	    : 
// Return type		: void 
void CXFloorWndPropPage::OnObjectsChanged( )
{
}

// Function name	: CXFloorWndPropPage::OnCheckAnimation
// Description	    : 
// Return type		: void 
void CXFloorWndPropPage::OnCheckAnimation() 
{
	UpdateData();
}

// Function name	: CXFloorWndPropPage::OnCheckSign
// Description	    : 
// Return type		: void 
void CXFloorWndPropPage::OnCheckSign() 
{
	UpdateData();
}

// Function name	: CXFloorWndPropPage::OnHScroll
// Description	    : Checks if slider is changes
// Return type		: void 
// Argument         : UINT nSBCode
// Argument         : UINT nPos
// Argument         : CScrollBar* pScrollBar
void CXFloorWndPropPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar)
		if (pScrollBar->GetSafeHwnd() == m_sliderAnimation.GetSafeHwnd())
		{
			m_nSleep = m_sliderAnimation.GetPos();
			SetModifiedFlag();
			UpdateMSecond();
		}
	
	COlePropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

// Function name	: void
// Description	    : template function for store some information in persistance and reverse
// Return type		:
// Argument         : CXFloorWndPropPage* pPage
// Argument         : BOOL bSave
// Argument         : classType* pValue
// Argument         : LPCTSTR lpszPropertyName
// Argument         : VARTYPE vType
template <class classType> void DDP_DEFINE( CXFloorWndPropPage* pPage, BOOL bSave, classType* pValue, LPCTSTR lpszPropertyName, VARTYPE vType )
{
	USES_CONVERSION;
	ULONG nObjects = NULL;
	LPDISPATCH* pDispatch = pPage->GetObjectArray(&nObjects);
	COleDispatchDriver propDispatch;
	for (int i = 0; i < (int)nObjects; i++)
	{
		LPCOLESTR lpOleStr = T2COLE(lpszPropertyName);
		DISPID dwDispID = NULL;
		if (SUCCEEDED(pDispatch[i]->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
		{
			propDispatch.AttachDispatch(pDispatch[i]);
			if (bSave)
			{
				classType nTemp = *pValue;
				propDispatch.SetProperty(dwDispID, vType, nTemp);
			}
			else
			{
				classType nTemp;
				propDispatch.GetProperty(dwDispID, vType, &nTemp);
				*pValue = nTemp;
			}
			propDispatch.DetachDispatch();
		}
	}
}

// Function name	: CXFloorWndPropPage::DDP_Long
// Description	    : Save a long into persistatnce objects
// Return type		: void 
// Argument         : CDataExchange * pDX
// Argument         : long* pValue
// Argument         : LPCTSTR lpszPropertyName
void CXFloorWndPropPage::DDP_Long(CDataExchange* pDX, long* pValue, LPCTSTR lpszPropertyName)
{
	DDP_DEFINE<long>(this, pDX->m_bSaveAndValidate, pValue, lpszPropertyName, VT_I4);
}

// Function name	: CXFloorWndPropPage::DDP_String
// Description	    : Save a string into persistatnce objects
// Return type		: void 
// Argument         : CDataExchange * pDX
// Argument         : CString* pValue
// Argument         : LPCTSTR lpszPropertyName
void CXFloorWndPropPage::DDP_String(CDataExchange * pDX, CString* pValue, LPCTSTR lpszPropertyName)
{
	DDP_DEFINE<CString>(this, pDX->m_bSaveAndValidate, pValue, lpszPropertyName, VT_BSTR);
}

// Function name	: CXFloorWndPropPage::ConstructPagesAsString
// Description	    : Called by OnEndEditLabeEdit in m_listPages, for store m_sPages as pages.
// Return type		: void 
void CXFloorWndPropPage::ConstructPagesAsString()
{
	m_sPages.Empty();
	CString s(_cPagesSeparator);
	for (int i = 0; i < m_listPages.GetItemCount(); i++)
		m_sPages += m_listPages.GetItemText(i, m_listPages.m_nNamePageCol) + _T("\\") + m_listPages.GetItemText(i, m_listPages.m_nUserDataCol) + s;
}
