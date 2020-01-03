/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 11/7/98 10:22:55
  Comments: ReflectShellTree.h: interface for the CReflectShellTree class.
 ************************************/

#if !defined(AFX_REFLECTSHELLTREE_H__26187851_761E_11D2_8540_9B1C6856D236__INCLUDED_)
#define AFX_REFLECTSHELLTREE_H__26187851_761E_11D2_8540_9B1C6856D236__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ShellTree.h"
class CControlsWnd_CShellFolder;

class CReflectShellTree : public CShellTree  
{
public:
	CString m_sSelectedPath;
	virtual void SetDefaultPath(LPCTSTR lpszPathName);
	static enum FLAGS {NOFLAG = 0, STS_CAPTURE = 1};
	CReflectShellTree();
	virtual ~CReflectShellTree();
	CReflectShellTree* CreatePopup(CControlsWnd_CShellFolder* pControlFolder, FLAGS nFlags = STS_CAPTURE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReflectShellTree)
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
protected:
	//{{AFX_MSG(CReflectShellTree)
		afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	virtual void Out(BOOL bCancel = FALSE);
	virtual BOOL IsCaptured();
	FLAGS m_nFlags;
private:
	CControlsWnd_CShellFolder* m_pControlFolder;
};

#endif // !defined(AFX_REFLECTSHELLTREE_H__26187851_761E_11D2_8540_9B1C6856D236__INCLUDED_)
