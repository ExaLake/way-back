/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 11/11/98 4:01:08 AM
  Comments: ADORMultiColumnComboBox.cpp: implementation of the CADORMultiColumnComboBox class.
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "ADORMultiColumnComboBox.h"
#include "ControlsWnd.h"
#include "XPropertiesWndCtl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CADORMultiColumnComboBox,CMultiColumnComboBox)
	//{{AFX_MSG_MAP(CADORMultiColumnComboBox)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Function name	: CADORMultiColumnComboBox::CADORMultiColumnComboBox
// Description	    : default constructor
// Return type		: 
CADORMultiColumnComboBox::CADORMultiColumnComboBox()
{
	m_rgbEditColor = RGB(0,0,255);
	m_pRecordSet = NULL;
	m_pFields = NULL;
	m_pNotifyClass = NULL;
	m_nLastItem = -1;
}

// Function name	: CADORMultiColumnComboBox::~CADORMultiColumnComboBox
// Description	    : virtual destructor
// Return type		: 
CADORMultiColumnComboBox::~CADORMultiColumnComboBox()
{

}

// Function name	: CADORMultiColumnComboBox::OnCtlColor
// Description	    : Change the color when you write into edit control.
// Return type		: HBRUSH 
// Argument         : CDC* pDC
// Argument         : CWnd* pWnd
// Argument         : UINT nCtlColor
HBRUSH CADORMultiColumnComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CMultiColumnComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd == GetEdit())
		pDC->SetTextColor(m_rgbEditColor);
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

// Function name	: CADORMultiColumnComboBox::SetEditColor
// Description	    : Set the new edit color
// Return type		: void 
// Argument         : COLORREF rgbEditColor
void CADORMultiColumnComboBox::SetEditColor(COLORREF rgbEditColor)
{
	m_rgbEditColor = rgbEditColor;	
}

// Function name	: CADORMultiColumnComboBox::Create
// Description	    : 
// Return type		: BOOL 
// Argument         : CWnd* m_pParent
BOOL CADORMultiColumnComboBox::Create(CControlsWnd_CADORComboBox* pNotifyClass, LPDISPATCH pObjectDispatch)
{
	BOOL bResult = FALSE;
	m_pNotifyClass = NULL;
	if (CreateRecordSet(pObjectDispatch))
		if (bResult = CMultiColumnComboBox::CreateEx(0, wndClassName, _T(""), WS_CHILD , CRect(0,0,0,0), (CWnd*)(pNotifyClass->GetWindowNotify()), 0))
		{
			m_pNotifyClass = pNotifyClass;
			ModifyStyleEx(WS_EX_STATICEDGE , 0);
			PopulateList();
		}
	return bResult;
}

// Function name	: CADORMultiColumnComboBox::Refresh
// Description	    : Refresh the control
// Return type		: BOOL 
BOOL CADORMultiColumnComboBox::Refresh()
{
	CListCtrl* pListCtrl = GetListCtrl();
	pListCtrl->DeleteAllItems();
	while (pListCtrl->DeleteColumn(0));
	DestroyRecordSet();
	LPDISPATCH pObjectDispatch = NULL;
	m_pNotifyClass->GetControl()->FireSetObject(m_pNotifyClass->GetWindowNotify()->GetIndexPage(), m_pNotifyClass->GetSelectedItem(), &pObjectDispatch);
	if (CreateRecordSet(pObjectDispatch))
	{
		PopulateList();
		return TRUE;
	}
	return FALSE;
}

// Function name	: CADORMultiColumnComboBox::SelectCurrentItem
// Description	    : Override this ...
// Return type		: void 
BOOL CADORMultiColumnComboBox::SelectCurrentItem()
{
	BOOL bResult = CMultiColumnComboBox::SelectCurrentItem();
	if (bResult)
	{
		CString text; GetEdit()->GetWindowText(text);
		m_pNotifyClass->OnSelectItem(text, 0);
	}
	return bResult;

}


// Function name	: CADORMultiColumnComboBox::OnDestroy
// Description	    : Destroy the recordset 
// Return type		: void 
void CADORMultiColumnComboBox::OnDestroy() 
{
	CMultiColumnComboBox::OnDestroy();
	
	DestroyRecordSet();	

	// Another penible BUG
	m_pActiveMCBox = NULL;
}

// Function name	: CADORMultiColumnComboBox::DestroyRecordSet
// Description	    : Called in destroy window
// Return type		: void 
void CADORMultiColumnComboBox::DestroyRecordSet()
{
	TRY
	{
		if (m_pRecordSet)
		{
			if (m_pFields)
			{
				for (int i = 0; i < m_arField.GetSize(); i++)
					delete m_arField.GetAt(i);
				m_arField.RemoveAll();
				delete m_pFields;
				m_pFields = NULL;
			}
			delete m_pRecordSet;
			m_pRecordSet = NULL;
		}
	}
	CATCH_ALL(e)
	{
	}
	END_CATCH_ALL;
}

// Function name	: CADORMultiColumnComboBox::CreateRecordSet
// Description	    : Create the record set, fields, field[i]...
// Return type		: BOOL 
// Argument         : LPDISPATCH pObjectDispatch
BOOL CADORMultiColumnComboBox::CreateRecordSet(LPDISPATCH pObjectDispatch)
{
	// m_pRecordSet need to be NULL
	ASSERT(m_pRecordSet == NULL);
	BOOL bResult = FALSE;
	if (pObjectDispatch)
	{
		TRY 
		{
			m_pRecordSet = new CADORRecordset(pObjectDispatch);
			pObjectDispatch->AddRef();
			m_pFields = new CADORFields(m_pRecordSet->GetFields());
			int nFields = m_pFields->GetCount();
			for (int i = 0; i < nFields; i++)
				m_arField.Add( new CADORField(m_pFields->GetItem(COleVariant((long)i))) );
			bResult = TRUE;
		}
		CATCH_ALL(e)
		{
			bResult = FALSE;
			DestroyRecordSet();
		}
		END_CATCH_ALL
	}
	return bResult;
}

// Function name	: CADORMultiColumnComboBox::CreateHeader
// Description	    : Create a header for list control
// Return type		: int 
int CADORMultiColumnComboBox::CreateHeader()
{
	CListCtrl* pListCtrl = GetListCtrl();
	int nFields = m_arField.GetSize();
	for (int i = 0; i < nFields; i++)
		pListCtrl->InsertColumn(i, m_arField[i]->GetName(), LVCFMT_LEFT, 128);
	return nFields;
}

// Function name	: CADORMultiColumnComboBox::GetErrorMessage
// Description	    : 
// Return type		: CString 
// Argument         : CException *e
CString CADORMultiColumnComboBox::GetErrorMessage(CException *e)
{
	CString buffer;
	if (e)
		e->GetErrorMessage(buffer.GetBuffer(1024), 1024);
	return buffer;
}

// Function name	: CADORMultiColumnComboBox::GetValue
// Description	    : comutil.h
// Return type		: CString 
// Argument         : CADORField *pField
CString CADORMultiColumnComboBox::GetValue(CADORField* pField)
{
	CString sResult;
	TRY
	{
		COleVariant v(pField->GetValue());
		v.ChangeType(VT_BSTR);
		sResult = CString(v.bstrVal);
		::SysFreeString(v.bstrVal);
	}
	CATCH_ALL(e)
	{
		TRACE(_T("Conversion failed into CString CADORMultiColumnComboBox::GetValue(CADORField* pField)\n"));
		TRACE(_T("Error: %s\n"), GetErrorMessage(e));
		sResult = _T("");
	}
	END_CATCH_ALL;
	return sResult;
}

// Function name	: CADORMultiColumnComboBox::CStr2Var
// Description	    : 
// Return type		: VARIANT 
// Argument         : LPCTSTR lpszValue
VARIANT CADORMultiColumnComboBox::CStr2Var( CADORField* pField, LPCTSTR lpszValue )
{
	VARIANT vResult;
	VariantInit(&vResult);
	TRY
	{
		COleVariant v( lpszValue );
		v.ChangeType((USHORT)pField->GetType() & 0x000F);
		vResult = v;
	}
	CATCH_ALL(e)
	{
		VariantInit(&vResult);
		TRACE(_T("Conversion failed into VARIANT CADORMultiColumnComboBox::CStr2Var( CADORField* pField, LPCTSTR lpszValue )\n"));
		TRACE(_T("Error: %s\n"), GetErrorMessage(e));
	}
	END_CATCH_ALL;
	return vResult;
}

// Function name	: CADORMultiColumnComboBox::PopulateList
// Description	    : Fill the list control: header wnd items
// Return type		: void 
void CADORMultiColumnComboBox::PopulateList()
{
	// Already this must be created
	ASSERT (::IsWindow(m_hWnd));
	int nFields = NULL;
	if ((nFields = CreateHeader()) > 0)
	{
		CListCtrl* pListCtrl = GetListCtrl();
		ASSERT ( nFields == m_arField.GetSize());
		TRY
		{
			m_pRecordSet->MoveFirst();
			int nItem = 0;
			while (!m_pRecordSet->GetEof())
			{
				nItem = pListCtrl->InsertItem(nItem + 1, GetValue(m_arField[0]));
				for (register int i = 1; i < nFields; i++)
					pListCtrl->SetItemText(nItem, i, GetValue(m_arField[i]));
				m_pRecordSet->MoveNext();
			}
		}
		CATCH_ALL(e)
		{
		}
		END_CATCH_ALL;
	}
}

// Function name	: CADORMultiColumnComboBox::GetColumnHeader
// Description	    : Get column header
// Return type		: BOOL 
BOOL CADORMultiColumnComboBox::GetColumnHeader()
{
	return !(GetListCtrl()->GetStyle() & LVS_NOCOLUMNHEADER);
}

// Function name	: CADORMultiColumnComboBox::SetColumnHeader
// Description	    : 
// Return type		: void 
// Argument         : BOOL bEnable
void CADORMultiColumnComboBox::SetColumnHeader(BOOL bShow)
{
	GetListCtrl()->ModifyStyle(bShow ? LVS_NOCOLUMNHEADER : 0, bShow ? 0 : LVS_NOCOLUMNHEADER);
}

// Function name	: CADORMultiColumnComboBox::OnInit
// Description	    : 
// Return type		: BOOL 
BOOL CADORMultiColumnComboBox::OnInit()
{
	if (CMultiColumnComboBox::OnInit())
	{
		m_hdColor.SubclassDlgItem(0, GetListCtrl());
		return TRUE;
	}
	return FALSE;
}
