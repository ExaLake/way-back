// ADORMultiColumnComboBox.h: interface for the CADORMultiColumnComboBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADORMULTICOLUMNCOMBOBOX_H__E305B342_786E_11D2_86F7_0040055C08D9__INCLUDED_)
#define AFX_ADORMULTICOLUMNCOMBOBOX_H__E305B342_786E_11D2_86F7_0040055C08D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MultiColumnComboBox.h"
#include "adorrecset.h"	// Added by ClassView
#include <afxtempl.h>
#include "ColorHeaderCtrl.h"	// Added by ClassView

class CADORMultiColumnComboBox : public CMultiColumnComboBox  
{
	int m_nLastItem;
	friend class CControlsWnd_CADORComboBox;
public:
	BOOL Create(CControlsWnd_CADORComboBox* pNotifyClass, LPDISPATCH pObjectDispatch);
	CADORMultiColumnComboBox();
	virtual ~CADORMultiColumnComboBox();

public:
	virtual void SetColumnHeader(BOOL bShow);
	virtual BOOL GetColumnHeader();
	virtual BOOL Refresh();
	virtual void SetEditColor(COLORREF rgbEditColor);
	CControlsWnd_CADORComboBox* GetControlClass() { return m_pNotifyClass;};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADORMultiColumnComboBox)
	//}}AFX_VIRTUAL

protected:
	CColorHeaderCtrl m_hdColor;
	virtual BOOL OnInit();
	static CString GetErrorMessage(CException* e);
	virtual BOOL SelectCurrentItem();
	CControlsWnd_CADORComboBox* m_pNotifyClass;
	static CString GetValue(CADORField* pField);
	static VARIANT CStr2Var(CADORField* pField, LPCTSTR lpszValue);
	virtual void PopulateList();
	virtual int CreateHeader();
	virtual void DestroyRecordSet();
	virtual BOOL CreateRecordSet(LPDISPATCH pObjectDispatch);
	CADORRecordset* m_pRecordSet;
	CADORFields* m_pFields;
	CArray<CADORField*, CADORField*> m_arField;
	COLORREF m_rgbEditColor;
	//{{AFX_MSG(CADORMultiColumnComboBox)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_ADORMULTICOLUMNCOMBOBOX_H__E305B342_786E_11D2_86F7_0040055C08D9__INCLUDED_)
