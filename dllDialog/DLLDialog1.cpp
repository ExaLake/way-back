// DLLDialog1.cpp : implementation file
//

#include "stdafx.h"
#include "dllDialog.h"
#include "DLLDialog1.h"
#include "dlldialogexport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



void DLLDIALOG ShowDialog()
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDLLDialog dlldialog;
	dlldialog.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CDLLDialog dialog


CDLLDialog::CDLLDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDLLDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLLDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDLLDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLLDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLLDialog, CDialog)
	//{{AFX_MSG_MAP(CDLLDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLLDialog message handlers
