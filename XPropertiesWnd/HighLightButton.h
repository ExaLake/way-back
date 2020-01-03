/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/24/98 12:00:19 PM
  Comments: HighLightButton.h : header file
 ************************************/

#if !defined(AFX_HIGHLIGHTBUTTON_H__4841AD21_22D1_11D2_8654_0040055C08D9__INCLUDED_)
#define AFX_HIGHLIGHTBUTTON_H__4841AD21_22D1_11D2_8654_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CHighLightButton window

class CHighLightButton : public CButton
{
// Construction
public:
	CHighLightButton();
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHighLightButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF SetForeGndColor(COLORREF rgbForeGnd);
	COLORREF SetForeGndHighLightColor(COLORREF rgbForeGnd);
	COLORREF SetBkGndColor(COLORREF rgbBKGnd);
	virtual ~CHighLightButton();

	// Generated message map functions
protected:
	virtual void Repaint();
	//{{AFX_MSG(CHighLightButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void RemoveCurrentColor(BOOL bCheckPoint = TRUE);
	COLORREF m_rgbForeGndHighLight;
	COLORREF m_rgbForeGnd;
	COLORREF m_rgbBkGnd;
	COLORREF m_rgbCurrentColor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIGHLIGHTBUTTON_H__4841AD21_22D1_11D2_8654_0040055C08D9__INCLUDED_)
