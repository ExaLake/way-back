/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/16/98 1:42:43 PM
  Comments: ControlsWnd.cpp: implementation of the CControlsWnd class and all derived classes
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "ControlsWnd.h"
#include "PageListCtrl.h"
#include "XPropertiesWndCtl.h"
#include "font.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define _FreezeEvents	m_nFreezeEvent++
#define _UnFreezeEvents	m_nFreezeEvent--
#define _IsFrozen		(m_nFreezeEvent != 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAsControls CControlsWnd::m_asControl;
TMapPg2TMapIdx2Ctrl CControlsWnd::m_mapPg2CtrlCreated;
long CControlsWnd::m_nFreezeEvent = 0;
IMPLEMENT_DYNAMIC(CControlsWnd,CObject)

// Function name	: CControlsWnd::CControlsWnd
// Description	    : Default constuctor
// Return type		: 
CControlsWnd::CControlsWnd()
{
	m_pWnd = NULL;
	m_pNotifyWnd = NULL;
	m_nSelectedItem = -1;
	m_nSelectedSubItem = -1;
}

// Function name	: CControlsWnd::~CControlsWnd
// Description	    : virtual destructor
// Return type		: 
CControlsWnd::~CControlsWnd()
{
	if (m_pWnd)
		if (::IsWindow(m_pWnd->m_hWnd))
			::DestroyWindow(m_pWnd->m_hWnd);
}

// Function name	: CControlsWnd::IsVisible
// Description	    : return true if control is visible
// Return type		: BOOL 
BOOL CControlsWnd::IsVisible()
{
	if (m_pWnd)
		if (AfxIsValidAddress(m_pWnd, sizeof(CWnd)))
			if (IsWindow(m_pWnd->m_hWnd))
				return m_pWnd->IsWindowVisible();
	return FALSE;
}

// Function name	: CControlsWnd::LookupPage
// Description	    : 
// Return type		: TMapIdx2Ctrl* 
// Argument         : CPageListCtrl* pNotifyWnd
TMapIdx2Ctrl* CControlsWnd::LookupPage(CPageListCtrl* pNotifyWnd)
{
	TMapIdx2Ctrl* pResult = NULL;
	if (m_mapPg2CtrlCreated.Lookup(pNotifyWnd, pResult))
		return pResult;
	return NULL;
}

// Function name	: CControlsWnd::Lookup
// Description	    : Lookup in m_mapPg2CtrlCreated if this control is alredy created
// Return type		: CControlsWnd* 
// Argument         : CPageListCtrl *pNotifyWnd
// Argument         : int nSelectedItem
CControlsWnd* CControlsWnd::LookupControl(CPageListCtrl *pNotifyWnd, int nSelectedItem)
{
	CControlsWnd* pResult = NULL;
	if (TMapIdx2Ctrl* pMap = LookupPage(pNotifyWnd))
		if (pMap->Lookup(nSelectedItem, pResult))
			if (AfxIsValidAddress(*(void**)pResult, sizeof(void*), FALSE))
				return pResult;
	return NULL;
}

// Function name	: CControlsWnd::Add2NDelete
// Description	    : Append a new control to map of not deleted controls
// Return type		: void 
// Argument         : CControlsWnd *pControl
void CControlsWnd::Add2NDelete(CControlsWnd *pControl)
{
	//This control when is created, need to be not destroyable, so I will  put into the m_mapPg2CtrlCreated
	TMapIdx2Ctrl* pMap = LookupPage(pControl->GetWindowNotify());
	if (!pMap)
		m_mapPg2CtrlCreated[pControl->GetWindowNotify()] = (pMap = new TMapIdx2Ctrl());
	(*pMap)[pControl->GetSelectedItem()] = pControl;
}

// Function name	: CControlsWnd::Kill
// Description	    : Kill this 
// Return type		: void 
void CControlsWnd::Kill()
{
	GetWindowNotify()->m_pEditControl = NULL;
	delete this;
}

// Function name	: CControlsWnd::KillAll
// Description	    : This function is called when user want to kill the control
// Return type		: void 
void CControlsWnd::KillAll()
{
	POSITION posMap = m_mapPg2CtrlCreated.GetStartPosition();
	TMapIdx2Ctrl* pMap = NULL; CPageListCtrl* pPage = NULL;
	while (posMap)
	{
		m_mapPg2CtrlCreated.GetNextAssoc(posMap, pPage, pMap);
		if (pMap)
		{
			CControlsWnd* pControl = NULL;
			long nSelectedItem = NULL;
			POSITION posCtrl = pMap->GetStartPosition();
			while (posCtrl)
			{
				pMap->GetNextAssoc(posCtrl, nSelectedItem, pControl);
				delete pControl;
			}
			delete pMap;
		}
	}
	m_mapPg2CtrlCreated.RemoveAll();
}

// Function name	: CControlsWnd::Create
// Description	    : 
// Return type		: CControlsWnd* 
// Argument         : LPCTSTR lpszAs
CControlsWnd* CControlsWnd::Create(LPCTSTR lpszAs, CPageListCtrl* pNotifyWnd, int nSelectedItem, int nSelectedSubItem)
{
	// If the control is already created we will return the control already created
	if (CControlsWnd* pResult = LookupControl(pNotifyWnd, nSelectedItem))
		return pResult;
	
	// Create a new one control
	CString className(_T("CControlsWnd_C"));
	className += lpszAs;
	if (CControlsWnd* pResult = CreateObject(className))
	{
		pResult->m_pNotifyWnd = pNotifyWnd;
		pResult->m_nSelectedItem = nSelectedItem;
		pResult->m_nSelectedSubItem = nSelectedSubItem;
		if (pResult->m_pWnd = pResult->Create())
		{
			if (::IsWindow(pResult->m_pWnd->m_hWnd))
				pResult->m_pWnd->SetFont(&pResult->m_pNotifyWnd->m_itemFont);
			return pResult;
		}
	}
	return NULL;
}

// Function name	: CControlsWnd::Close
// Description	    : 
// Return type		: void 
// Argument         : BOOL bCancel
void CControlsWnd::Close(BOOL bCancel)
{
	if (m_pWnd)
		if (::IsWindow(m_pWnd->m_hWnd))
		{
			ReleaseCapture();
			m_pWnd->ShowWindow(SW_HIDE);
		}
	GetWindowNotify()->CloseEditing();
	RefreshColor();
};

// Function name	: CControlsWnd::GetWindow
// Description	    : return the window
// Return type		: CWnd* 
CWnd* CControlsWnd::GetWindow()
{
	return m_pWnd;
}

// Function name	: CControlsWnd::GetWindowNotify
// Description	    : return the notify window
// Return type		: CPageListCtrl* 
CPageListCtrl* CControlsWnd::GetWindowNotify()
{
	return m_pNotifyWnd;
}

// Function name	: CControlsWnd::GetControl
// Description	    : 
// Return type		: CXPropertiesWndCtrl* 
CXPropertiesWndCtrl* CControlsWnd::GetControl()
{
	return GetWindowNotify()->GetControlWnd();
}

// Function name	: CControlsWnd::Show
// Description	    : generate BeginEditProperty event
// Return type		: void 
// Argument         : LPARAM lParam
void CControlsWnd::Show(LPARAM lParam)
{
	if (::IsWindow(GetWindow()->GetSafeHwnd()))
		GetWindow()->SetFont(&GetWindowNotify()->m_itemFont, TRUE);
	RefreshColor();
	GetControl()->FirePropertyChanging(GetControl()->_GetActivePage(), m_nSelectedItem);
}

// Function name	: CControlsWnd::OnSelectItem
// Description	    : When user select a new item, change the value of edit control, or click the button
// Return type		: void 
// Argument         : CString& newValue
// Argument         : LPARAM lParam
void CControlsWnd::OnSelectItem(CString& newValue, LPARAM lParam)
{
	CString sOldProperty = GetDefaultValue();
	GetWindowNotify()->SetDefaultValue(m_nSelectedItem, (LPCTSTR)newValue);
	CXPropertiesWndCtrl* pControl = GetControl();
	pControl->FirePropertyChanged(pControl->_GetActivePage(), m_nSelectedItem, sOldProperty.Compare((LPCTSTR)newValue) != 0);
}

// Function name	: CControlsWnd::GetDefaultValue
// Description	    : return the default value of control
// Return type		: CString 
CString CControlsWnd::GetDefaultValue()
{
	return GetWindowNotify()->GetItemText(m_nSelectedItem, m_nSelectedSubItem);
}

// Function name	: CControlsWnd::SetValue
// Description	    : Set a value as default
// Return type		: void 
// Argument         : VARIANT vVariant
// Argument         : long nColumn
void CControlsWnd::SetValue(VARIANT vVariant, long nColumn)
{
	TRY
	{
		COleVariant v(vVariant);
		v.ChangeType(VT_BSTR);
		GetWindowNotify()->SetDefaultValue(GetSelectedItem(), CString(v.bstrVal));
		::SysFreeString(v.bstrVal);
	}
	CATCH_ALL(e)
	{
	}
	END_CATCH_ALL;
}

// Function name	: CControlsWnd::GetValue
// Description	    : Return the value as variant
// Return type		: VARIANT 
// Argument         : long nColumn
VARIANT CControlsWnd::GetValue(long nColumn)
{
	VARIANT v;
	VariantInit(&v);
	v.vt = VT_BSTR;
	v.bstrVal = GetDefaultValue().AllocSysString();
	return v;
}

// Function name	: CControlsWnd::GetRect
// Description	    : return the default rect
// Return type		: CRect 
CRect CControlsWnd::GetRect()
{
	return GetWindowNotify()->GetLastRect(m_nSelectedItem);
}

// Function name	: CControlsWnd::RefreshColor
// Description	    : Refresh the color of item in edit mode
// Return type		: void 
void CControlsWnd::RefreshColor()
{
	GetWindowNotify()->RedrawItems(m_nSelectedItem, m_nSelectedItem);
}

// Function name	: CControlsWnd::Delete
// Description	    : Delete this.
// Return type		: void 
CControlsWnd* CControlsWnd::Delete()
{
	delete this;
	return NULL;
}



//////////////////////////////////////////////////////////////////////
// CControlsWnd_CComboBox Class
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DERIVED_CLASS(CControlsWnd_CComboBox,CControlsWnd);
IMPLEMENT_DYNAMIC(CControlsWnd_CComboBox,CControlsWnd)
// Function name	: CControlsWnd_CComboBox::CControlsWnd_CComboBox
// Description	    : Default constructor
// Return type		: 
CControlsWnd_CComboBox::CControlsWnd_CComboBox()
{
}

// Function name	: CControlsWnd_CComboBox::~CControlsWnd_CComboBox
// Description	    : virtual destructor
// Return type		: 
CControlsWnd_CComboBox::~CControlsWnd_CComboBox()
{
}

// Function name	: CControlsWnd_CComboBox::Create
// Description	    : Overidable function
// Return type		: CControlsWnd* 
CWnd* CControlsWnd_CComboBox::Create()
{
	if ((::IsWindow(m_dropListBox.GetSafeHwnd())) || (m_dropListBox.Create(this)))
		return &m_dropListBox;
	return NULL;
}

// Function name	: CControlsWnd_CComboBox::Show
// Description	    : Show function. Overidable function
// Return type		: void 
// Argument         : CRect rect
// Argument         : LPARAM lParam
void CControlsWnd_CComboBox::Show(LPARAM lParam)
{
	if (::IsWindow(m_dropListBox.GetSafeHwnd()))
	{
		CControlsWnd::Show(lParam);
		m_dropListBox.Show(GetRect(), 8);
		if (m_dropListBox.SelectString(-1, GetDefaultValue()) == LB_ERR)
			m_dropListBox.SetCurSel(0);
	}
}

// Function name	: CControlsWnd_CComboBox::OnSelectItem
// Description	    : The Item nItem was select.
// Return type		: void 
// Argument         : int nItem
void CControlsWnd_CComboBox::OnSelectItem(CString& newValue, LPARAM lParam)
{
	if (::IsWindow(m_dropListBox.GetSafeHwnd()))
	{
		m_dropListBox.GetText(lParam, newValue);
	}
	CControlsWnd::OnSelectItem(newValue, lParam);
};

// Function name	: CControlsWnd_CComboBox::Load
// Description	    : 
// Return type		: void 
void CControlsWnd_CComboBox::Load()
{
	if (::IsWindow(m_dropListBox.GetSafeHwnd()))
	{
		BSTR bItems = NULL;
		GetControl()->FireLoadItems(GetControl()->_GetActivePage(), m_nSelectedItem, &bItems);
		if (bItems)
		{
			CString items(bItems);
			::SysFreeString(bItems);
			m_dropListBox.Load(items);
		}
	}

	CControlsWnd::Load();
};

// Function name	: CControlsWnd_CComboBox::OnNextItem
// Description	    : 
// Return type		: void 
// Argument         : int nItem
void CControlsWnd_CComboBox::OnNextItem()
{
	if (::IsWindow(m_dropListBox.GetSafeHwnd()))
	{
		if (m_dropListBox.SetCurSel(m_dropListBox.FindString(-1, GetDefaultValue()) + 1) == LB_ERR)
			m_dropListBox.SetCurSel(0);
		m_dropListBox.SelChange();
	}
	CControlsWnd::OnNextItem();
}

// Function name	: CControlsWnd_CComboBox::Close
// Description	    : Called by window when this must be closed
// Return type		: void 
// Argument         : BOOL bCancel
void CControlsWnd_CComboBox::Close(BOOL bCancel)
{
	CControlsWnd::Close(bCancel);
}

//////////////////////////////////////////////////////////////////////
// CControlsWnd_CBoolComboBox Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DERIVED_CLASS(CControlsWnd_CBoolComboBox,CControlsWnd_CComboBox);
IMPLEMENT_DYNAMIC( CControlsWnd_CBoolComboBox,CControlsWnd_CComboBox )
// Function name	: CControlsWnd_CBoolComboBox::CControlsWnd_CBoolComboBox
// Description	    : default constuctor
// Return type		: 
CControlsWnd_CBoolComboBox::CControlsWnd_CBoolComboBox()
{

}

// Function name	: CControlsWnd_CBoolComboBox::~CControlsWnd_CBoolComboBox
// Description	    : virtual destructor
// Return type		: 
CControlsWnd_CBoolComboBox::~CControlsWnd_CBoolComboBox()
{

}

// Function name	: CControlsWnd_CBoolComboBox::Load
// Description	    : Overidable function
// Return type		: void 
void CControlsWnd_CBoolComboBox::Load()
{
	// Eventiment
	if (::IsWindow(m_dropListBox.GetSafeHwnd()))
		m_dropListBox.Load(_T("False\\True"));

	CControlsWnd::Load();
}

// Function name	: CControlsWnd_CBoolComboBox::Show
// Description	    : 
// Return type		: void 
void CControlsWnd_CBoolComboBox::Show(LPARAM lParam )
{
	CControlsWnd_CComboBox::Show(2);
}

//////////////////////////////////////////////////////////////////////
// CControlsWnd_CEdit Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DERIVED_CLASS(CControlsWnd_CEdit,CControlsWnd);
IMPLEMENT_DYNAMIC(CControlsWnd_CEdit,CControlsWnd)
// Function name	: CControlsWnd_CEdit::CControlsWnd_CEdit
// Description	    : Default constructor
// Return type		: 
CControlsWnd_CEdit::CControlsWnd_CEdit()
{

}

// Function name	: CControlsWnd_CEdit::~CControlsWnd_CEdit
// Description	    : 
// Return type		: 
CControlsWnd_CEdit::~CControlsWnd_CEdit()
{

}

// Function name	: CControlsWnd_CEdit::Create
// Description	    : 
// Return type		: CWnd* 
CWnd* CControlsWnd_CEdit::Create()
{
	if (m_dropEdit.Create(this))
	{
		m_dropEdit.SetEditColor(GetControl()->m_rgbEditColor);
		return &m_dropEdit;
	}
	return NULL;
}

// Function name	: CControlsWnd_CEdit::Show
// Description	    : Show the control
// Return type		: void 
// Argument         : LPARAM lParam
void CControlsWnd_CEdit::Show(LPARAM lParam)
{
	if (::IsWindow(m_dropEdit.GetSafeHwnd()))
	{
		CControlsWnd::Show(lParam);

		CRect rect = GetRect();
		rect.top += 2; rect.left += 2;
		m_dropEdit.SetWindowText(GetDefaultValue());
		m_dropEdit.Show(rect);
	}
}

// Function name	: CControlsWnd_CEdit::Close
// Description	    : 
// Return type		: void 
// Argument         : BOOL bCancel
void CControlsWnd_CEdit::Close(BOOL bCancel)
{
	// Do nothing
}

// Function name	: OnSelectItem
// Description	    : 
// Return type		: void 
// Argument         : LPARAM lParam
void CControlsWnd_CEdit::OnSelectItem(CString& newValue, LPARAM lParam)
{
	if (::IsWindow(m_dropEdit.GetSafeHwnd()))
		m_dropEdit.GetWindowText(newValue);
	CControlsWnd::OnSelectItem(newValue, lParam);
}

//////////////////////////////////////////////////////////////////////
// CControlsWnd_CButton Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DERIVED_CLASS(CControlsWnd_CButton,CControlsWnd);
IMPLEMENT_DYNAMIC(CControlsWnd_CButton,CControlsWnd)
IMPLEMENT_DERIVED_CLASS(CControlsWnd_CReturn, CControlsWnd_CButton);
IMPLEMENT_DYNAMIC(CControlsWnd_CReturn, CControlsWnd_CButton)
IMPLEMENT_DERIVED_CLASS(CControlsWnd_CLink, CControlsWnd_CButton);
IMPLEMENT_DYNAMIC(CControlsWnd_CLink, CControlsWnd_CButton)

// Function name	: CControlsWnd_CButton::CControlsWnd_CButton
// Description	    : Default constructor
// Return type		: 
CControlsWnd_CButton::CControlsWnd_CButton()
{

}

// Function name	: CControlsWnd_CButton::~CControlsWnd_CButton
// Description	    : 
// Return type		: 
CControlsWnd_CButton::~CControlsWnd_CButton()
{

}

// Function name	: CControlsWnd_CButton::Create
// Description	    : Overidable function.
// Return type		: CWnd* 
CWnd* CControlsWnd_CButton::Create()
{
	return &m_button;
}

// Function name	: CControlsWnd_CButton::OnNextItem
// Description	    : On NextItem call Show fucntion
// Return type		: void 
void CControlsWnd_CButton::OnNextItem()
{
	Show(1);
}

// Function name	: CControlsWnd_CButton::Show
// Description	    : 
// Return type		: void 
// Argument         : LPARAM lParam
void CControlsWnd_CButton::Show(LPARAM lParam)
{
	CControlsWnd::Show(lParam);
	GetControl()->FireButtonClick(GetControl()->_GetActivePage(), m_nSelectedItem);
	// In ButonClick you have the oprotunities to remove this pointer
	if (!AfxIsValidAddress(this, sizeof(*this), TRUE))
	{
		CString newValue = GetDefaultValue();
		OnSelectItem(newValue, 0);
	}
}

IMPLEMENT_DERIVED_CLASS(CControlsWnd_CFont,CControlsWnd_CButton);
IMPLEMENT_DYNAMIC(CControlsWnd_CFont,CControlsWnd_CButton)

static const LOGFONT logFontDefault =
{
/*LONG lfHeight*/10,
/*LONG lfWidth*/0,
/*LONG lfEscapement*/0,
/*LONG lfOrientation*/0,
/*LONG lfWeight*/FW_NORMAL,
/*BYTE lfItalic*/FALSE,
/*BYTE lfUnderline*/FALSE,
/*BYTE lfStrikeOut*/FALSE,
/*BYTE lfCharSet*/ANSI_CHARSET,
/*BYTE lfOutPrecision*/0,
/*BYTE lfClipPrecision*/0,
/*BYTE lfQuality*/DEFAULT_QUALITY,
/*BYTE lfPitchAndFamily*/DEFAULT_PITCH,
/*CHAR lfFaceName[LF_FACESIZE]*/_T("MS Sans Serif")
};

/*
#include <atlconv.h>
// Function name	: CreateOleFont
// Description	    : Create a IFontDisp interface for font pFont. 
// Return type		: IDispatch* 
// Argument         : CFont* pFont
IDispatch* CreateOleFont(CFont* pFont)
{
	IDispatch* pDispatch = NULL;
	USES_CONVERSION;
	if (pFont)
	{
		LOGFONT logfont;
		if (pFont->GetLogFont(&logfont))
		{
			LOGFONT* pLogFont = &logfont;
			FONTDESC fd;
			fd.cbSizeofstruct = sizeof(FONTDESC);
			fd.lpstrName = T2OLE(pLogFont->lfFaceName);
			fd.sWeight = (short)pLogFont->lfWeight;
			fd.sCharset = pLogFont->lfCharSet;
			fd.fItalic = pLogFont->lfItalic;
			fd.fUnderline = pLogFont->lfUnderline;
			fd.fStrikethrough = pLogFont->lfStrikeOut;

			long lfHeight = pLogFont->lfHeight;
			if (lfHeight < 0)
				lfHeight = -lfHeight;

			fd.cySize.Lo = lfHeight * 720000 / 96;
			fd.cySize.Hi = 0;

			if (FAILED(::OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&pDispatch)))
				pDispatch = NULL;
		}
	}
	return pDispatch;
}

// Function name	: CreateFontDisp
// Description	    : Create a font from a IFont interface
// Return type		: BOOL 
// Argument         : IDispatch* pDispatchFont
// Argument         : CFont& font
BOOL CreateFontDisp(IDispatch* pDispatchFont, CFont& font)
{
	HFONT hFont = NULL;
	TRY
	{
		IFont* pIFont = (IFont*)pDispatchFont;
		if (!FAILED(pIFont->get_hFont(&hFont)))
		{
			LOGFONT logFont;
			CFont::FromHandle(hFont)->GetLogFont(&logFont);
			return font.CreateFontIndirect(&logFont);
		}
	}
	CATCH_ALL(e)
	{
		e->Delete();
	}
	END_CATCH_ALL;
	return FALSE;
}
*/


// Function name	: CControlsWnd_CFont::CControlsWnd_CFont
// Description	    : Init the logfont structure, with one default
// Return type		: 
CControlsWnd_CFont::CControlsWnd_CFont():m_rgbColor(RGB(0,0,0))
{
	m_logFont = logFontDefault;
}

// Function name	: CControlsWnd_CFont::Create
// Description	    : This control will not be deleted
// Return type		: CWnd* 
CWnd* CControlsWnd_CFont::Create()
{
	CWnd* pResult = CControlsWnd_CButton::Create();
	if (pResult)
		Add2NDelete(this);

	return pResult;
}

// Function name	: CControlsWnd_CFont::GetSize
// Description	    : return the size of font as CY structure
// Return type		: CY 
CY CControlsWnd_CFont::GetSize()
{
	CY cyResult; 
	cyResult.int64 = -MulDiv(m_logFont.lfHeight,72*10000,96);
	return cyResult;
}

// Function name	: CControlsWnd_CFont::GetHeight
// Description	    : Return the height of font from size
// Return type		: long 
// Argument         : CY size
long CControlsWnd_CFont::GetHeight(CY size)
{
	return -MulDiv(size.Lo, 96, 72*10000);
}

#include <atlbase.h>
void CControlsWnd_CFont::SetValue(VARIANT vVariant, long nColumn)
{
	TRY
	{
		switch (vVariant.vt)
		{
			case VT_I2:
			case VT_UI2:
			case VT_I4:
			case VT_UI4:
			{
				COleVariant v(vVariant);
				v.ChangeType(VT_UI4);
				m_rgbColor = v.ulVal;
				return;
			}
			case VT_DISPATCH:
			{
				COleFont oleFont(vVariant.pdispVal);
				vVariant.pdispVal->AddRef();
				m_logFont.lfStrikeOut = oleFont.GetStrikethrough();
				m_logFont.lfItalic = oleFont.GetItalic();
				m_logFont.lfUnderline = oleFont.GetUnderline();
				m_logFont.lfWeight = oleFont.GetWeight();
				m_logFont.lfCharSet = (BYTE)oleFont.GetCharset();
				m_logFont.lfHeight = GetHeight(oleFont.GetSize());
				memcpy(&m_logFont.lfFaceName, (LPCTSTR)oleFont.GetName(), oleFont.GetName().GetLength() + 1);
				GetWindowNotify()->SetDefaultValue(GetSelectedItem(), GetName());
				return;
			}
			default:
			{
				CControlsWnd_CButton::SetValue(vVariant, nColumn);
				return ;
			}
		}
	}
	CATCH_ALL(e)
	{
		CString text;
		e->GetErrorMessage(text.GetBuffer(1024), 1024);
		TRACE(_T("Error: %s"), text);
		e->Delete();
	}
	END_CATCH_ALL;
}

// Function name	: CControlsWnd_CFont::GetValue
// Description	    : For	0 return VT_FONT,
//							1 return color of font
// Return type		: VARIANT 
// Argument         : long nColumn
VARIANT CControlsWnd_CFont::GetValue(long nColumn)
{
	VARIANT v;
	VariantInit(&v);
	switch (nColumn)
	{
		case 0:
			{
				CComPtr<IFont> font;
				if (SUCCEEDED(font.CoCreateInstance(CLSID_StdFont)))
				{
					IFont* pIFont = font.p;
					pIFont->AddRef();
					pIFont->put_Name(CString(m_logFont.lfFaceName).AllocSysString());
					pIFont->put_Bold(m_logFont.lfWeight == FW_BOLD);
					pIFont->put_Italic(m_logFont.lfItalic);
					pIFont->put_Charset(m_logFont.lfCharSet);
					pIFont->put_Size(GetSize());
					pIFont->put_Weight((SHORT)m_logFont.lfWeight);
					pIFont->put_Strikethrough(m_logFont.lfStrikeOut);
					pIFont->put_Underline(m_logFont.lfUnderline);

					v.vt = VT_DISPATCH;
					v.pdispVal = (IDispatch*)pIFont;
				}
				break;
			}
		case 1:
			{
				v.vt = VT_UI4;
				v.ulVal = m_rgbColor;
				break;
			}
		default:
			{
				return CControlsWnd_CButton::GetValue(nColumn);
			}
	}
	return v;
}

// Function name	: CControlsWnd_CFont::SetLogFont
// Description	    : Set the new log font as default value
// Return type		: void 
// Argument         : LOGFONT* pLogFont
void CControlsWnd_CFont::SetLogFont(LOGFONT* pLogFont)
{
	ASSERT (pLogFont);
	memcpy(&m_logFont, pLogFont, sizeof(m_logFont));
}

// Function name	: CControlsWnd_CFont::SetColorFont
// Description	    : 
// Return type		: void 
// Argument         : COLORREF rgbColor
void CControlsWnd_CFont::SetColorFont(COLORREF rgbColor)
{
	m_rgbColor = rgbColor;
}


// Function name	: CControlsWnd_CFont::GetName
// Description	    : 
// Return type		: CString 
CString CControlsWnd_CFont::GetName()
{
	CString sResult;
	sResult.Format(_T("%s, %.2f"), m_logFont.lfFaceName , (float)GetSize().Lo / 10000);
	return sResult;
}

// Function name	: CControlsWnd_CFont::Show
// Description	    : Show the coose font dialog
// Return type		: void 
// Argument         : LPARAM lParam
void CControlsWnd_CFont::Show(LPARAM lParam)
{
	CControlsWnd::Show(lParam);
	
	CFontDialog* pFontWnd = new CFontDialog(&m_logFont);
	pFontWnd->m_cf.rgbColors = m_rgbColor;
	if (pFontWnd->DoModal() == IDOK)
	{
		pFontWnd->GetCurrentFont(&m_logFont);
		m_rgbColor = pFontWnd->GetColor();
		CString sNewValue = GetName();
		OnSelectItem(sNewValue, lParam);
	}
	delete pFontWnd;
}

// Function name	: CControlsWnd_CFont::Delete
// Description	    : Don't delete this
// Return type		: CControlsWnd* 
CControlsWnd* CControlsWnd_CFont::Delete()
{
	return NULL;
}

// Function name	: CControlsWnd_CFont::GetLogFont
// Description	    : 
// Return type		: LOGFONT& 
LOGFONT* CControlsWnd_CFont::GetLogFont()
{
	return &m_logFont;
}

COLORREF CControlsWnd_CFont::GetColorFont()
{
	return m_rgbColor;
}


//////////////////////////////////////////////////////////////////////
// CControlsWnd_CUserComboBox Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DERIVED_CLASS(CControlsWnd_CUserComboBox,CControlsWnd);
IMPLEMENT_DYNAMIC(CControlsWnd_CUserComboBox,CControlsWnd)
// Function name	: CControlsWnd_CUserComboBox::CControlsWnd_CUserComboBox
// Description	    : Default constructor
// Return type		: 
CControlsWnd_CUserComboBox::CControlsWnd_CUserComboBox()
{

}

// Function name	: CControlsWnd_CUserComboBox::~CControlsWnd_CUserComboBox
// Description	    : 
// Return type		: 
CControlsWnd_CUserComboBox::~CControlsWnd_CUserComboBox()
{

}

// Function name	: CControlsWnd_CUserComboBox::Create
// Description	    : 
// Return type		: CWnd* 
CWnd* CControlsWnd_CUserComboBox::Create()
{
	// Not implemented yet.
	return NULL;
}

// Function name	: CControlsWnd_CUserComboBox::Show
// Description	    : 
// Return type		: void 
// Argument         : LPARAM lParam
void CControlsWnd_CUserComboBox::Show(LPARAM lParam )
{
	// Not implemented yet.
}

// Function name	: CControlsWnd_CUserComboBox::Close
// Description	    : 
// Return type		: void 
// Argument         : BOOL bCancel
void CControlsWnd_CUserComboBox::Close(BOOL bCancel)
{
	// Not implemented yet.
}

// Function name	: CControlsWnd_CUserComboBox::OnSelectItem
// Description	    : 
// Return type		: void 
// Argument         : CString& newValue
// Argument         : LPARAM lParam
void CControlsWnd_CUserComboBox::OnSelectItem(CString& newValue, LPARAM lParam)
{
	// Not implemented yet.
}

// Function name	: CControlsWnd_CUserComboBox::OnNextItem
// Description	    : // Not implemented yet.
// Return type		: void 
void CControlsWnd_CUserComboBox::OnNextItem()
{
}


//////////////////////////////////////////////////////////////////////
// CControlsWnd_CColorComboBox Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DERIVED_CLASS(CControlsWnd_CColorComboBox,CControlsWnd);
IMPLEMENT_DYNAMIC(CControlsWnd_CColorComboBox,CControlsWnd)
// Function name	: CControlsWnd_CColorComboBox::CControlsWnd_CColorComboBox
// Description	    : Default constructor
// Return type		: 
CControlsWnd_CColorComboBox::CControlsWnd_CColorComboBox()
{
}

// Function name	: CControlsWnd_CColorComboBox::~CControlsWnd_CColorComboBox
// Description	    : 
// Return type		: 
CControlsWnd_CColorComboBox::~CControlsWnd_CColorComboBox()
{

}

// Function name	: CControlsWnd_CColorComboBox::GetValue
// Description	    : Return the selected color as ULONG value
// Return type		: VARIANT 
// Argument         : long nColumn
VARIANT CControlsWnd_CColorComboBox::GetValue(long nColumn)
{
	VARIANT v;
	VariantInit(&v);
	switch (nColumn)
	{
		case 0:
		{
			v.vt = VT_UI4;
			v.ulVal = GetColor(GetDefaultValue());
			break;
		}
		default:
		{
			return CControlsWnd::GetValue(nColumn);
		}
	}
	return v;
}

// Function name	: CControlsWnd_CColorComboBox::SetValue
// Description	    : Set a new color for this
// Return type		: void 
// Argument         : VARIANT vVariant
// Argument         : long nColumn
void CControlsWnd_CColorComboBox::SetValue(VARIANT vVariant, long nColumn)
{
	switch (vVariant.vt)
	{
		case VT_I2:
		case VT_UI2:
		case VT_UI4:
		case VT_I4:
		{
			CString text;
			text.Format("%i", 10000);
			AfxMessageBox(text);
			COleVariant v(vVariant);
			v.ChangeType(VT_UI4);
			GetWindowNotify()->SetDefaultValue(GetSelectedItem(), GetName(v.ulVal));
			break;
		}
		default:
		{
			CControlsWnd::SetValue(vVariant, nColumn);
			break;
		}
	}
}

// Function name	: CControlsWnd_CColorComboBox::GetName
// Description	    : 
// Return type		: CString 
// Argument         : COLORREF color
CString CControlsWnd_CColorComboBox::GetName(COLORREF color)
{
	CString sColor, sText;
	sColor.Format(_T("%08X"), color);
	sColor = sColor.Mid(2);
	sText.Format(_T("&&H%s (%s)"), sColor, CColourPopup::GetColourName(CColourPopup::FindColor(color)));
	return sText;
}

// Function name	: CControlsWnd_CColorComboBox::Create
// Description	    : 
// Return type		: CWnd* 
CWnd* CControlsWnd_CColorComboBox::Create()
{
	if (m_btnPicker.Create(NULL, WS_CHILD, GetRect(), GetWindowNotify(), 0))
	{
		m_btnPicker.SendMessage(WM_COMMAND, MAKEWPARAM(BN_CLICKED, m_btnPicker.GetDlgCtrlID()), (long)m_btnPicker.m_hWnd);
		return &m_btnPicker;
	}

	return NULL;
}

HHOOK CControlsWnd_CColorComboBox::m_hHook = NULL;
CControlsWnd_CColorComboBox* CControlsWnd_CColorComboBox::m_pThis = NULL;
LRESULT CALLBACK CControlsWnd_CColorComboBox::HookColourPopupWndProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if (nCode >= 0)
	{
		CWPSTRUCT* pMessage = (CWPSTRUCT*)lParam;
		if (pMessage->message == WM_DESTROY)
		{
			LRESULT lResult = ::CallNextHookEx(m_hHook, nCode, wParam, lParam);
			m_pThis->OnDestroy();
			return lResult;
		}
	}
	return ::CallNextHookEx(m_hHook, nCode, wParam, lParam);
}

// Function name	: CControlsWnd_CColorComboBox::Show
// Description	    : 
// Return type		: void 
// Argument         : LPARAM lParam
void CControlsWnd_CColorComboBox::Show(LPARAM lParam )
{
	if (::IsWindow(m_btnPicker.GetSafeHwnd()))
	{
		m_btnPicker.SendMessage(WM_COMMAND, MAKEWPARAM(BN_CLICKED, m_btnPicker.GetDlgCtrlID()), (long)m_btnPicker.m_hWnd);
		if (CColourPopup* pWndColor = m_btnPicker.m_pWndColor)
		{
			// Propage the PropertyChanging event
			CControlsWnd::Show(lParam);

			CRect rect;
			pWndColor->GetWindowRect(rect);
			CRect rButton = GetRect();
			GetWindowNotify()->ClientToScreen(rButton);
			rect.OffsetRect(rButton.right - rect.right, 0);
			pWndColor->MoveWindow(rect);
			pWndColor->m_WindowRect = rect;
			COLORREF crColour = GetColor(GetDefaultValue());
			pWndColor->m_crColour = pWndColor->m_crInitialColour = crColour;
			pWndColor->FindCellFromColour(crColour);
			pWndColor->ShowWindow(SW_SHOW);
			DWORD dxProcessID = NULL;
			m_pThis = this;
			m_hHook = SetWindowsHookEx(WH_CALLWNDPROC, (HOOKPROC)HookColourPopupWndProc, AfxGetInstanceHandle(), GetWindowThreadProcessId(pWndColor->m_hWnd, &dxProcessID));
			RefreshColor();
		}
	}
}

// Function name	: CControlsWnd_CColorComboBox::Close
// Description	    : 
// Return type		: void 
// Argument         : BOOL bCancel
void CControlsWnd_CColorComboBox::Close(BOOL bCancel)
{
}

// Function name	: CControlsWnd_CColorComboBox::OnDestroy
// Description	    : This is called by the hook procedure when color picker is on destory
// Return type		: void 
void CControlsWnd_CColorComboBox::OnDestroy()
{
	::UnhookWindowsHookEx(m_hHook);

	if (CColourPopup* pWndColor = m_btnPicker.m_pWndColor)
	{
		CString sText = GetName(pWndColor->m_crColour);
		// Propage the PropertyChanged event
		OnSelectItem(sText, m_nSelectedItem);
	}
	GetWindowNotify()->SetFocus();
}

// Function name	: CControlsWnd_CColorComboBox::GetColor
// Description	    : 
// Return type		: COLORREF 
// Argument         : CString sColor
COLORREF CControlsWnd_CColorComboBox::GetColor(CString sColor)
{
	if (sColor.IsEmpty())
		return RGB(255,255,255);
	sColor = sColor.Mid(3); sColor = sColor.Left(6); sColor = _T("0x") + sColor;
	return (COLORREF)_tcstol((LPCTSTR)sColor, NULL, 16);
}


// Function name	: CControlsWnd_CColorComboBox::OnSelectItem
// Description	    : 
// Return type		: void 
// Argument         : CString& newValue
// Argument         : LPARAM lParam
void CControlsWnd_CColorComboBox::OnSelectItem(CString& newValue, LPARAM lParam)
{
	CControlsWnd::OnSelectItem(newValue, lParam);
}

// Function name	: CControlsWnd_CColorComboBox::OnNextItem
// Description	    : // Not implemented yet.
// Return type		: void 
void CControlsWnd_CColorComboBox::OnNextItem()
{
	CString sColor, sText;
	int nColour = (CColourPopup::FindColor(GetColor(GetDefaultValue())) + 1 ) % CColourPopup::m_nNumColours;
	sColor.Format(_T("%08X"), CColourPopup::GetColour(nColour));
	sColor = sColor.Mid(2);
	sText.Format(_T("&&H%s (%s)"), sColor, CColourPopup::GetColourName(nColour));
	// Propage the PropertyChanged event
	OnSelectItem(sText, m_nSelectedItem);
}

// Function name	: CControlsWnd_CColorComboBox::IsVisible
// Description	    : 
// Return type		: BOOL 
BOOL CControlsWnd_CColorComboBox::IsVisible()
{
	if (CColourPopup* pWndColor = m_btnPicker.m_pWndColor)
		if (::IsWindow(pWndColor->GetSafeHwnd()))
			return pWndColor->IsWindowVisible();
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// CControlsWnd_CShellFolder Class
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DERIVED_CLASS(CControlsWnd_CShellFolder,CControlsWnd);
IMPLEMENT_DYNAMIC(CControlsWnd_CShellFolder,CControlsWnd)
// Function name	: CControlsWnd_CShellFolder::CControlsWnd_CShellFolder
// Description	    : Default constructor
// Return type		: 
CControlsWnd_CShellFolder::CControlsWnd_CShellFolder()
{
}

// Function name	: CControlsWnd_CShellFolder::~CControlsWnd_CShellFolder
// Description	    : virtual destructor
// Return type		: 
CControlsWnd_CShellFolder::~CControlsWnd_CShellFolder()
{

}

// Function name	: CControlsWnd_CShellFolder::Create
// Description	    : Overidable function
// Return type		: CControlsWnd* 
CWnd* CControlsWnd_CShellFolder::Create()
{
	// Do not put as parent the GetWindowNotify(), becasuse this do not reflect messages
	return m_dropShellFolder.CreatePopup(this);
}

// Function name	: CControlsWnd_CShellFolder::OnDestroy
// Description	    : Called by m_dropShellFolder.OnDestroy()
// Return type		: void 
void CControlsWnd_CShellFolder::OnDestroy()
{
	if (::IsWindow(m_dropShellFolder.GetSafeHwnd()))
	{
		CString sText = m_dropShellFolder.m_sSelectedPath;
		if (!sText.IsEmpty())
			// Propage the PropertyChanged event
			OnSelectItem(sText, m_nSelectedItem);
	}
	GetWindowNotify()->SetFocus();
	
}

// Function name	: CControlsWnd_CShellFolder::Show
// Description	    : Show function. Overidable function
// Return type		: void 
// Argument         : CRect rect
// Argument         : LPARAM lParam
void CControlsWnd_CShellFolder::Show(LPARAM lParam)
{
	if (::IsWindow(m_dropShellFolder.GetSafeHwnd()))
	{
		CControlsWnd::Show(lParam);
		CRect r(GetRect()); CRect rect; m_dropShellFolder.GetWindowRect(rect);
		GetWindowNotify()->ClientToScreen(&r);
		r.top = r.bottom; r.bottom += rect.Height();
		if (r.Width() < rect.Width())
			r.left = r.right - rect.Width();
		m_dropShellFolder.MoveWindow(r);
		m_dropShellFolder.ShowWindow(SW_SHOW);
		m_dropShellFolder.SetFocus();

	}
}

// Function name	: CControlsWnd_CShellFolder::OnSelectItem
// Description	    : The Item nItem was select.
// Return type		: void 
// Argument         : int nItem
void CControlsWnd_CShellFolder::OnSelectItem(CString& newValue, LPARAM lParam)
{
	if (::IsWindow(m_dropShellFolder.GetSafeHwnd()))
	{
		newValue = m_dropShellFolder.m_sSelectedPath;
	}
	CControlsWnd::OnSelectItem(newValue, lParam);
};


IMPLEMENT_DERIVED_CLASS(CControlsWnd_CADORComboBox,CControlsWnd);
IMPLEMENT_DYNAMIC(CControlsWnd_CADORComboBox,CControlsWnd)
// Function name	: CControlsWnd_CADORComboBox::CControlsWnd_CADORComboBox
// Description	    : Default constructor
// Return type		: 
CControlsWnd_CADORComboBox::CControlsWnd_CADORComboBox()
{
}

// Function name	: CControlsWnd_CADORComboBox::~CControlsWnd_CADORComboBox
// Description	    : virtual destructor
// Return type		: 
CControlsWnd_CADORComboBox::~CControlsWnd_CADORComboBox()
{
}

// Function name	: CControlsWnd_CADORComboBox::Refresh
// Description	    : 
// Return type		: BOOL
BOOL CControlsWnd_CADORComboBox::Refresh()
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		return m_wndADORComboBox.Refresh();
	return FALSE;
}

// Function name	: CControlsWnd_CADORComboBox::Create
// Description	    : Overidable function
// Return type		: CControlsWnd* 
CWnd* CControlsWnd_CADORComboBox::Create()
{
	CWnd* pResult = NULL;
	if (!_IsFrozen)
	{
		_FreezeEvents;
		LPDISPATCH pObjectDispatch = NULL;
		// Call a event, so user must set the pObjectDispatch as a distaptch to a ADOR.Recordset 
		GetControl()->FireSetObject(GetWindowNotify()->GetIndexPage(), m_nSelectedItem, &pObjectDispatch);
		if (m_wndADORComboBox.Create(this, pObjectDispatch))
		{
			m_wndADORComboBox.SetEditColor(GetControl()->m_rgbEditColor);

			Add2NDelete(this);

			pResult = &m_wndADORComboBox;
		}
		_UnFreezeEvents;
	}
	return pResult;
}

// Function name	: CControlsWnd_CADORComboBox::Show
// Description	    : Show function. Overidable function
// Return type		: void 
// Argument         : CRect rect
// Argument         : LPARAM lParam
void CControlsWnd_CADORComboBox::Show(LPARAM lParam)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
	{
		// Propage the changing event
		CControlsWnd::Show(lParam);
		CRect rect = GetRect();
		rect.InflateRect(-1,-1);
		rect.right--;
		m_wndADORComboBox.MoveWindow(rect);
		m_wndADORComboBox.ShowWindow(SW_SHOW);
		m_wndADORComboBox.DropDown();
	}
}

// Function name	: CControlsWnd_CADORComboBox::OnSelectItem
// Description	    : The Item nItem was select.
// Return type		: void 
// Argument         : int nItem
void CControlsWnd_CADORComboBox::OnSelectItem(CString& newValue, LPARAM lParam)
{
	CControlsWnd::OnSelectItem(newValue, lParam);	
};

// Function name	: CControlsWnd_CADORComboBox::Delete
// Description	    : This function must return NULL, but didn't delete this pointer
// Return type		: CControlsWnd* 
CControlsWnd* CControlsWnd_CADORComboBox::Delete()
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
	{		
		// How the control is not destroyed , instead this is hidden
		m_wndADORComboBox.ShowWindow(SW_HIDE);
	}
	return NULL;
}

// Function name	: CControlsWnd_CADORComboBox::SetColumnKey
// Description	    : 
// Return type		: void 
// Argument         : long nColumnKey
void CControlsWnd_CADORComboBox::SetColumnKey(long nColumnKey)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		m_wndADORComboBox.m_nColumnKey = nColumnKey;
}

// Function name	: CControlsWnd_CADORComboBox::GetColumnKey
// Description	    : 
// Return type		: void 
// Argument         : long nColumnKey
long CControlsWnd_CADORComboBox::GetColumnKey()
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		return m_wndADORComboBox.m_nColumnKey;
	return -1;
}

// Function name	: CControlsWnd_CADORComboBox::SetColumnWidth
// Description	    : Set the new width for a column
// Return type		: void 
// Argument         : long nColumn
// Argument         : long nColumnWidth
void CControlsWnd_CADORComboBox::SetColumnWidth(long nColumn, long nColumnWidth)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
	{
		LVCOLUMN lvColumn; lvColumn.mask = LVCF_WIDTH; lvColumn.cx = nColumnWidth;
		m_wndADORComboBox.GetListCtrl()->SetColumn(nColumn, &lvColumn);
	}
}

// Function name	: CControlsWnd_CADORComboBox::GetColumnWidth
// Description	    : 
// Return type		: long 
// Argument         : long nColumn
long CControlsWnd_CADORComboBox::GetColumnWidth(long nColumn)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
	{
		LVCOLUMN lvColumn; lvColumn.mask = LVCF_WIDTH;
		if (m_wndADORComboBox.GetListCtrl()->GetColumn(nColumn, &lvColumn))
			return lvColumn.cx;
	}
	return -1;
}

// Function name	: CControlsWnd_CADORComboBox::SetColumnName
// Description	    : 
// Return type		: void 
// Argument         : long nColumn
// Argument         : LPCTSTR lpszColumnName
void CControlsWnd_CADORComboBox::SetColumnName(long nColumn, LPCTSTR lpszColumnName)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
	{
		CString sName(lpszColumnName);
		LVCOLUMN lvColumn; lvColumn.mask = LVCF_TEXT;
		lvColumn.pszText = (LPTSTR)(LPCTSTR)sName;
		lvColumn.cchTextMax = sName.GetLength();
		m_wndADORComboBox.GetListCtrl()->SetColumn(nColumn, &lvColumn);
	}
}

// Function name	: CControlsWnd_CADORComboBox::GetColumnName
// Description	    : 
// Return type		: LPCTSTR 
// Argument         : long nColumn
LPCTSTR CControlsWnd_CADORComboBox::GetColumnName(long nColumn)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
	{
		static CString sName;
		LVCOLUMN lvColumn; lvColumn.mask = LVCF_TEXT;
		lvColumn.pszText = sName.GetBuffer(256);
		lvColumn.cchTextMax = 256;
		if (m_wndADORComboBox.GetListCtrl()->GetColumn(nColumn, &lvColumn))
			return (LPCTSTR)sName;
	}
	return NULL;
}

// Function name	: CControlsWnd_CADORComboBox::SetColumnHeader
// Description	    : Set or unset the column header
// Return type		: void 
// Argument         : BOOL bShow
void CControlsWnd_CADORComboBox::SetColumnHeader(BOOL bShow)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		m_wndADORComboBox.SetColumnHeader(bShow);
}

// Function name	: CControlsWnd_CADORComboBox::GetColumnHeader
// Description	    : Return TRUE if header is showen
// Return type		: BOOL 
BOOL CControlsWnd_CADORComboBox::GetColumnHeader()
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		return m_wndADORComboBox.GetColumnHeader();
	return FALSE;
}

// Function name	: CControlsWnd_CADORComboBox::SetDropDownWidth
// Description	    : Set the new rate for drop down width
// Return type		: void 
// Argument         : double nRateWidth
void CControlsWnd_CADORComboBox::SetDropDownWidth(double nRateWidth)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		m_wndADORComboBox.SetRateWidth(nRateWidth);
}

// Function name	: CControlsWnd_CADORComboBox::GetDropDownWidth
// Description	    : return the rate width
// Return type		: double 
double CControlsWnd_CADORComboBox::GetDropDownWidth()
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		return m_wndADORComboBox.m_dWidthList;
	return -1.0;
}

// Function name	: CControlsWnd_CADORComboBox::SetDropDownHeight
// Description	    : 
// Return type		: void 
// Argument         : long nMulHeight
void CControlsWnd_CADORComboBox::SetDropDownHeight(long nMulHeight)
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		m_wndADORComboBox.SetMultipleHeight(nMulHeight);
}

// Function name	: CControlsWnd_CADORComboBox::GetDropDownHeight
// Description	    : 
// Return type		: long 
long CControlsWnd_CADORComboBox::GetDropDownHeight()
{
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		return m_wndADORComboBox.m_nMultipleHeight;
	return -1;
}

// Function name	: CControlsWnd_CADORComboBox::GetValue
// Description	    : 
// Return type		: VARIANT 
// Argument         : long nColumn
VARIANT CControlsWnd_CADORComboBox::GetValue(long nColumn)
{
	VARIANT vaResult;
	VariantInit(&vaResult);
	if (::IsWindow(m_wndADORComboBox.GetSafeHwnd()))
		if (nColumn >= 0)
			if ( nColumn < m_wndADORComboBox.m_arField.GetSize())
			{
				CListCtrl* pListCtrl = m_wndADORComboBox.GetListCtrl();
				int nItem = pListCtrl->GetNextItem(-1, LVNI_SELECTED);
				if (nItem >= 0)
					vaResult = m_wndADORComboBox.CStr2Var(m_wndADORComboBox.m_arField[nColumn], pListCtrl->GetItemText(nItem, nColumn));
			}
	return vaResult;
}


IMPLEMENT_DERIVED_CLASS(CControlsWnd_CDataComboBox,CControlsWnd);
IMPLEMENT_DYNAMIC(CControlsWnd_CDataComboBox,CControlsWnd)
// Function name	: CControlsWnd_CDataComboBox::CControlsWnd_CDataComboBox
// Description	    : Default constructor
// Return type		: 
CControlsWnd_CDataComboBox::CControlsWnd_CDataComboBox()
{
}

// Function name	: CControlsWnd_CDataComboBox::~CControlsWnd_CDataComboBox
// Description	    : virtual destructor
// Return type		: 
CControlsWnd_CDataComboBox::~CControlsWnd_CDataComboBox()
{
}

// Function name	: CControlsWnd_CDataComboBox::Create
// Description	    : 
// Return type		: CWnd* 
CWnd* CControlsWnd_CDataComboBox::Create()
{
	if (m_wndDate.Create(this))
		return &m_wndDate;
	return NULL;
}

// Function name	: CControlsWnd_CDataComboBox::Show
// Description	    : 
// Return type		: void 
// Argument         : LPARAM lParam
void CControlsWnd_CDataComboBox::Show(LPARAM lParam)
{
	if (IsWindow(m_wndDate.m_hWnd))
	{
		CControlsWnd::Show(lParam);
		m_wndDate.MoveWindow(GetRect());
		m_wndDate.SetWindowText(GetDefaultValue());
		m_wndDate.ShowWindow(SW_SHOW);
	}
}

// Function name	: CControlsWnd_CDataComboBox::Delete
// Description	    : Do not delete this. It is no case
// Return type		: CControlsWnd* 
CControlsWnd* CControlsWnd_CDataComboBox::Delete()
{
	if (IsWindow(m_wndDate.m_hWnd))
		m_wndDate.ShowWindow(SW_HIDE);
	return NULL;
}

// Function name	: CControlsWnd_CDataComboBox::OnSelectItem
// Description	    : 
// Return type		: void 
// Argument         : CString& newValue
// Argument         : LPARAM lParam
void CControlsWnd_CDataComboBox::OnSelectItem(CString& newValue, LPARAM lParam)
{
	if (::IsWindow(m_wndDate.GetSafeHwnd()))
	{
		m_wndDate.GetWindowText(newValue);
		CControlsWnd::OnSelectItem(newValue, lParam);
	}
}

