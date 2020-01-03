// COMClientDlg.h : header file
//

#if !defined(AFX_COMCLIENTDLG_H__C1ADB65D_A5BF_11D3_8651_00C01501BDC4__INCLUDED_)
#define AFX_COMCLIENTDLG_H__C1ADB65D_A5BF_11D3_8651_00C01501BDC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCOMClientDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CCOMClientDlg dialog

class CCOMClientDlg : public CDialog
{
	DECLARE_DYNAMIC(CCOMClientDlg);
	friend class CCOMClientDlgAutoProxy;

// Construction
public:
	CCOMClientDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CCOMClientDlg();

// Dialog Data
	//{{AFX_DATA(CCOMClientDlg)
	enum { IDD = IDD_COMCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCOMClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCOMClientDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CCOMClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMCLIENTDLG_H__C1ADB65D_A5BF_11D3_8651_00C01501BDC4__INCLUDED_)
