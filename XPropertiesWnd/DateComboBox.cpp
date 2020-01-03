// DateComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "DateComboBox.h"
#include "ControlsWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateComboBox

CDateComboBox::CDateComboBox()
{
	m_pControl = NULL;
}

CDateComboBox::~CDateComboBox()
{
}


BEGIN_MESSAGE_MAP(CDateComboBox, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CDateComboBox)
	ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE, OnDatetimechange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateComboBox message handlers

BOOL CDateComboBox::Create(CControlsWnd_CDataComboBox *pControl)
{
	m_pControl = pControl;
	BOOL bResult = CDateTimeCtrl::Create(WS_CHILD, CRect(0,0,0,0), (CWnd*)m_pControl->GetWindowNotify(), 0x3E8);
	if (bResult)
		SetFont(((CWnd*)m_pControl->GetWindowNotify())->GetFont());
	return bResult;
}

// Function name	: CDateComboBox::OnDatetimechange
// Description	    : 
// Return type		: void 
// Argument         : NMHDR* pNMHDR
// Argument         : LRESULT* pResult
void CDateComboBox::OnDatetimechange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString sDate;
	GetWindowText(sDate);
	m_pControl->OnSelectItem(sDate, 0);
	*pResult = 0;
}
