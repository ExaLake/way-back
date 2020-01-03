// DialogAlpha.cpp : implementation file
//

#include "stdafx.h"
#include "DialogGL.h"
#include "DialogAlpha.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogAlpha dialog


CDialogAlpha::CDialogAlpha(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAlpha::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAlpha)
	m_Alpha = 0;
	//}}AFX_DATA_INIT
}


void CDialogAlpha::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAlpha)
	DDX_Text(pDX, IDC_EDIT_ALPHA, m_Alpha);
	DDV_MinMaxByte(pDX, m_Alpha, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAlpha, CDialog)
	//{{AFX_MSG_MAP(CDialogAlpha)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAlpha message handlers
