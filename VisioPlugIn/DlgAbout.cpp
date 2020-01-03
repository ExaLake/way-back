// DlgAbout.cpp : implementation file
//

#include "stdafx.h"
#include "NetInfo.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/) :
CDlgAbout_PARENT(CDlgAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAbout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDlgAbout_PARENT::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbout)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDlgAbout_PARENT)
	//{{AFX_MSG_MAP(CDlgAbout)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
