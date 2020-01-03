/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/14/98 1:13:00 PM
  Comments: AsControls.cpp: implementation of the CAsControls class.
 ************************************/

#include "stdafx.h"
#include "xpropertieswnd.h"
#include "AsControls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Function name	: CAsControls::CAsControls
// Description	    : 
// Return type		: 
CAsControls::CAsControls()
{
	Add(ID_MENUAS_EDIT, _T("Edit"));					// See class CControlsWnd_CEdit
	Add(ID_MENUAS_COMBOBOX, _T("ComboBox"));			// See class CControlsWnd_CComboBox
	Add(ID_MENUAS_ADORCOMBOBOX, _T("ADORComboBox"), !PROTECTED);	// See class CControlsWnd_CADORComboBox
	Add(ID_MENUAS_BOOLCOMBOBOX, _T("BoolComboBox"));	// See class CControlsWnd_CBoolComboBox
	Add(ID_MENUAS_DATACOMBOBOX, _T("DataComboBox"));	// See class CControlsWnd_CDataComboBox
	Add(ID_MENUAS_USERCOMBOBOX, _T("UserComboBox"));	// See class CControlsWnd_CUserComboBox
	Add(ID_MENUAS_SHELLFOLDER, _T("ShellFolder"));		// See class CControlsWnd_CShellFolder
	Add(ID_MENUAS_COLORCOMBOBOX, _T("ColorComboBox"));	// See class CControlsWnd_CColorComboBox
	Add(ID_MENUAS_BUTTON, _T("Button"));				// See class CControlsWnd_CButton
	Add(ID_MENUAS_RETURN, _T("Return"));				// See class CControlsWnd_CReturn
	Add(ID_MENUAS_LINK, _T("Link"));					// See class CControlsWnd_CLink
	Add(ID_MENUAS_FONT, _T("Font"));					// See class CControlsWnd_CFont
}

// Function name	: CAsControls::~CAsControls
// Description	    : 
// Return type		: 
CAsControls::~CAsControls()
{
	RemoveAll();
}

// Function name	: CAsControls::GetName
// Description	    : 
// Return type		: LPCTSTR 
// Argument         : UINT idAs
LPCTSTR CAsControls::GetName(UINT idAs)
{
	CString* pString = NULL;
	if (m_mapControls.Lookup(idAs, pString))
		return (LPCTSTR)*pString;
	return NULL;
}

// Function name	: CAsControls::GetID
// Description	    : Get ID as type lpszAS
// Return type		: UINT 
// Argument         : LPCTSTR lpszAs
UINT CAsControls::GetID(LPCTSTR lpszAs)
{
	CObject* pResult = NULL;
	if (m_mapControlsString.Lookup(lpszAs, pResult))
		return (UINT)pResult;
	return -1;
}

// Function name	: CAsControls::Add
// Description	    : Add a new control type, if the coresonding item is not grayed
// Return type		: void 
// Argument         : UINT id
// Argument         : LPCTSTR lpszAs
void CAsControls::Add(UINT id, LPCTSTR lpszAs, BOOL bEnable)
{
	if (bEnable)
	{
		m_mapControls[id] = new CString(lpszAs);
		m_mapControlsString[lpszAs] = (CObject*)id;
	}
}

// Function name	: CAsControls::RemoveAll
// Description	    : Called by destructor
// Return type		: void 
void CAsControls::RemoveAll()
{
	POSITION pos = m_mapControls.GetStartPosition();
	while (pos)
	{
		UINT key = NULL;
		CString* pString = NULL;
		m_mapControls.GetNextAssoc(pos, key, pString);
		delete pString;
	}
	m_mapControls.RemoveAll();
}

