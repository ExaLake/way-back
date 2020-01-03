/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/16/98 1:42:53 PM
  Comments: ControlsWnd.h: interface for the CControlsWnd class.
 ************************************/

#if !defined(AFX_CONTROLSWND_H__F0626F83_64E1_11D2_86BF_0040055C08D9__INCLUDED_)
#define AFX_CONTROLSWND_H__F0626F83_64E1_11D2_86BF_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "stdafx.h"
#include "AsControls.h"
#include "rttim.h"
#include "DropListBox.h"	// Added by ClassView
#include "DropEdit.h"	// Added by ClassView
#include "ColourPicker.h"	// Added by ClassView
#include "ReflectShellTree.h"	// Added by ClassView
#include "ADORMultiColumnComboBox.h"	// Added by ClassView

class CPageListCtrl;
class CXPropertiesWndCtrl;
class CControlsWnd;

// Why I choose this definitions of map. Because, I have to make this classes be independedt!
// When I will remove a page, it didn't need to remove from this map;
typedef CMap<long, long, CControlsWnd*, CControlsWnd*> TMapIdx2Ctrl;
typedef CMap<CPageListCtrl*, CPageListCtrl*, TMapIdx2Ctrl*, TMapIdx2Ctrl*> TMapPg2TMapIdx2Ctrl;

class CControlsWnd : public CObject
{
protected:
	static long m_nFreezeEvent;
public:
	static void Add2NDelete(CControlsWnd* pControl);
	// Kill all controls from map m_mapPg2CtrlCreated
	static void KillAll();
	void Kill();
	
	virtual VARIANT GetValue(long nColumn = 0);
	virtual void SetValue(VARIANT vVariant, long nColumn = 0);
	// These are only implemented in CControlsWnd_CADORComboBox
	virtual void SetColumnKey(long nColumnKey) {;};
	virtual long GetColumnKey() {return -1;};
	virtual void SetColumnWidth(long nColumn, long nColumnWidth) {;};
	virtual long GetColumnWidth(long nColumn) {return -1;};
	virtual void SetColumnName(long nColumn, LPCTSTR lpszColumnName) {;};
	virtual LPCTSTR GetColumnName(long nColumn) {return NULL;};
	virtual void SetColumnHeader(BOOL bShow) {;};
	virtual BOOL GetColumnHeader() {return FALSE;};
	virtual void SetDropDownWidth(double nRateWidth) {;};
	virtual double GetDropDownWidth() { return -1.0;};
	virtual void SetDropDownHeight(long nMulHeight) {;};
	virtual long GetDropDownHeight() { return -1;};
	virtual BOOL Refresh() { return FALSE;};
	// End

	// Called when this have to be deleted
	virtual CControlsWnd* Delete();
	long GetSelectedItem() { return m_nSelectedItem; }
	DECLARE_BASE_CLASS(CControlsWnd);
	DECLARE_DYNAMIC(CControlsWnd)
	CWnd* GetWindow();
	CPageListCtrl* GetWindowNotify();
	CXPropertiesWndCtrl* GetControl();
	static CControlsWnd* Create(LPCTSTR lpszAs, CPageListCtrl* pNotifyWnd, int nSelectedItem, int nSelectedSubItem = 1);
	// Overidable functions...
	virtual CWnd* Create() { return NULL; };
	virtual void Show(LPARAM lParam = 0);
	virtual void Close(BOOL bCancel);
	virtual void OnSelectItem(CString& newValue, LPARAM lParam);
	virtual void OnNextItem() {};
	// End Overidable functions...
	virtual void Load() {};
	CControlsWnd();
	virtual ~CControlsWnd();
	virtual BOOL IsVisible();
	static CControlsWnd* LookupControl(CPageListCtrl* pNotifyWnd, int nSelectedItem);

protected:
	static TMapIdx2Ctrl* LookupPage(CPageListCtrl* pNotifyWnd);
	virtual void RefreshColor();
	virtual CRect GetRect();
	virtual CString GetDefaultValue();
	int m_nSelectedItem;
	int m_nSelectedSubItem;
	CWnd* m_pWnd;
	CPageListCtrl* m_pNotifyWnd;
	static CAsControls m_asControl;
	static TMapPg2TMapIdx2Ctrl m_mapPg2CtrlCreated;
private:
};

class CControlsWnd_CComboBox : public CControlsWnd
{
public:
	DECLARE_DERIVED_CLASS(CControlsWnd_CComboBox);
	DECLARE_DYNAMIC(CControlsWnd_CComboBox)
	CControlsWnd_CComboBox();
	virtual ~CControlsWnd_CComboBox();
	//Overidable functions
	virtual CWnd* Create();
	virtual void Show(LPARAM lParam);
	virtual void Close(BOOL bCancel);
	virtual void OnSelectItem(CString& newValue, LPARAM lParam);
	//End overidable functions
	virtual void Load();
	virtual void OnNextItem();
protected:
	CDropListBox m_dropListBox;
};


class CControlsWnd_CBoolComboBox : public CControlsWnd_CComboBox  
{
public:
	DECLARE_DERIVED_CLASS(CControlsWnd_CBoolComboBox);
	DECLARE_DYNAMIC(CControlsWnd_CBoolComboBox)
	CControlsWnd_CBoolComboBox();
	virtual ~CControlsWnd_CBoolComboBox();
	// Overwrite only Load function
	virtual void Load();
	virtual void Show(LPARAM lParam = 0);
};


class CControlsWnd_CEdit : public CControlsWnd  
{
public:
	DECLARE_DERIVED_CLASS(CControlsWnd_CEdit);
	DECLARE_DYNAMIC(CControlsWnd_CEdit)
	CControlsWnd_CEdit();
	virtual ~CControlsWnd_CEdit();
	virtual CWnd* Create();
	virtual void Show(LPARAM lParam);
	virtual void Close(BOOL bCancel);
	virtual void OnSelectItem(CString& newValue, LPARAM lParam);
protected:
	CDropEdit m_dropEdit;
};

class CControlsWnd_CButton : public CControlsWnd  
{
public:
	DECLARE_DERIVED_CLASS(CControlsWnd_CButton);
	DECLARE_DYNAMIC(CControlsWnd_CButton)
	CControlsWnd_CButton();
	virtual ~CControlsWnd_CButton();
	virtual CWnd* Create();
	virtual void Show(LPARAM lParam = 0);
	virtual void OnNextItem();
	virtual void Close(BOOL bCancel) {};
protected:
	CButton m_button;
};

class CControlsWnd_CReturn: public CControlsWnd_CButton
{
	DECLARE_DERIVED_CLASS(CControlsWnd_CReturn);
	DECLARE_DYNAMIC(CControlsWnd_CReturn);
};

class CControlsWnd_CLink: public CControlsWnd_CButton
{
	DECLARE_DERIVED_CLASS(CControlsWnd_CLink);
	DECLARE_DYNAMIC(CControlsWnd_CLink);
};

class CControlsWnd_CFont: public CControlsWnd_CButton
{
	DECLARE_DERIVED_CLASS(CControlsWnd_CFont);
	DECLARE_DYNAMIC(CControlsWnd_CFont);
public:
	virtual LOGFONT* GetLogFont();
	virtual void SetLogFont(LOGFONT* pLogFont);
	virtual COLORREF GetColorFont();
	virtual void SetColorFont(COLORREF rgbColor);
	CControlsWnd_CFont();
	virtual void Show(LPARAM lParam = 0);
	virtual CWnd* Create();
	virtual CControlsWnd* Delete();
	virtual VARIANT GetValue(long nColumn = 0);
	virtual void SetValue(VARIANT vVariant, long nColumn = 0);
protected:
	virtual long GetHeight(CY size);
	virtual CY GetSize();
	virtual CString GetName();
	LOGFONT m_logFont;
	COLORREF m_rgbColor;
};

class CControlsWnd_CUserComboBox : public CControlsWnd  
{
public:
	DECLARE_DERIVED_CLASS(CControlsWnd_CUserComboBox);
	DECLARE_DYNAMIC(CControlsWnd_CUserComboBox)
	CControlsWnd_CUserComboBox();
	virtual ~CControlsWnd_CUserComboBox();

	virtual CWnd* Create();
	virtual void Show(LPARAM lParam = 0);
	virtual void Close(BOOL bCancel);
	virtual void OnSelectItem(CString& newValue, LPARAM lParam);
	virtual void OnNextItem();

protected:
};

class CControlsWnd_CColorComboBox : public CControlsWnd_CUserComboBox
{
public:
	virtual BOOL IsVisible();
	DECLARE_DERIVED_CLASS(CControlsWnd_CColorComboBox);
	DECLARE_DYNAMIC(CControlsWnd_CColorComboBox)
	CControlsWnd_CColorComboBox();
	virtual ~CControlsWnd_CColorComboBox();

	virtual VARIANT GetValue(long nColumn = 0);
	virtual void SetValue(VARIANT vVariant, long nColumn = 0);
	virtual CWnd* Create();
	virtual void Show(LPARAM lParam = 0);
	virtual void Close(BOOL bCancel);
	virtual void OnSelectItem(CString& newValue, LPARAM lParam);
	virtual void OnNextItem();

	static LRESULT CALLBACK HookColourPopupWndProc( int nCode, WPARAM wParam, LPARAM lParam );
	static HHOOK m_hHook;
	static CControlsWnd_CColorComboBox* m_pThis;
	static COLORREF GetColor(CString sColor);
protected:
	static CString GetName(COLORREF color);
	void OnDestroy();
private:
	CColourPicker m_btnPicker;
};

class CControlsWnd_CShellFolder : public CControlsWnd
{
public:
	DECLARE_DERIVED_CLASS(CControlsWnd_CShellFolder);
	DECLARE_DYNAMIC(CControlsWnd_CShellFolder)
	CControlsWnd_CShellFolder();
	virtual ~CControlsWnd_CShellFolder();
	//Overidable functions
	virtual CWnd* Create();
	virtual void Show(LPARAM lParam);
	virtual void OnSelectItem(CString& newValue, LPARAM lParam);
	virtual void Close(BOOL bCancel) {};
	//End overidable functions
	void OnDestroy();
protected:
	CReflectShellTree m_dropShellFolder;
};

class CControlsWnd_CADORComboBox : public CControlsWnd
{
public:
	virtual VARIANT GetValue(long nColumn = 0);
	// Specific only CControlsWnd_CADORComboBox
	virtual void SetColumnKey(long nColumnKey);
	virtual long GetColumnKey();
	virtual void SetColumnWidth(long nColumn, long nColumnWidth);
	virtual long GetColumnWidth(long nColumn);
	virtual void SetColumnName(long nColumn, LPCTSTR lpszColumnName);
	virtual LPCTSTR GetColumnName(long nColumn);
	virtual void SetColumnHeader(BOOL bShow);
	virtual BOOL GetColumnHeader();
	virtual void SetDropDownWidth(double nRateWidth);
	virtual double GetDropDownWidth();
	virtual void SetDropDownHeight(long nMulHeight);
	virtual long GetDropDownHeight();
	virtual BOOL Refresh();
	// end

	DECLARE_DERIVED_CLASS(CControlsWnd_CADORComboBox);
	DECLARE_DYNAMIC(CControlsWnd_CADORComboBox)
	CControlsWnd_CADORComboBox();
	virtual ~CControlsWnd_CADORComboBox();
	//Overidable functions
	virtual CControlsWnd* Delete();
	virtual CWnd* Create();
	virtual void Show(LPARAM lParam);
	virtual void OnSelectItem(CString& newValue, LPARAM lParam);
	virtual void Close(BOOL bCancel) {};
	//End overidable functions
protected:
	CADORMultiColumnComboBox m_wndADORComboBox;
};

#include "DateComboBox.h"	// Added by ClassView
class CControlsWnd_CDataComboBox : public CControlsWnd
{
public:
	DECLARE_DERIVED_CLASS(CControlsWnd_CDataComboBox);
	DECLARE_DYNAMIC(CControlsWnd_CDataComboBox)
	CControlsWnd_CDataComboBox();
	virtual ~CControlsWnd_CDataComboBox();
	//Overidable functions
	virtual CControlsWnd* Delete();
	virtual CWnd* Create();
	virtual void Show(LPARAM lParam);
	virtual void OnSelectItem(CString& newValue, LPARAM lParam);
	virtual void Close(BOOL bCancel) {};
	//End overidable functions
protected:
	CDateComboBox m_wndDate;
};




#endif // !defined(AFX_CONTROLSWND_H__F0626F83_64E1_11D2_86BF_0040055C08D9__INCLUDED_)
