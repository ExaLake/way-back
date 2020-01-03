// DialogTesterDlg.h : header file
//
//{{AFX_INCLUDES()
#include "_activelistbox.h"
//}}AFX_INCLUDES

#if !defined(AFX_DIALOGTESTERDLG_H__DBCC2E6E_8A42_11D3_9E84_00E029175834__INCLUDED_)
#define AFX_DIALOGTESTERDLG_H__DBCC2E6E_8A42_11D3_9E84_00E029175834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogTesterDlg dialog

class CDialogTesterDlg : public CDialog
{
// Construction
public:
	CDialogTesterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogTesterDlg)
	enum { IDD = IDD_DIALOGTESTER_DIALOG };
	C_ActiveListBox	m_activeListBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogTesterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDialogTesterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGTESTERDLG_H__DBCC2E6E_8A42_11D3_9E84_00E029175834__INCLUDED_)
