/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 10/13/98 2:28:07 PM
  Comments: XPropertiesWnd.h : main header file for XPROPERTIESWND.DLL
 ************************************/

#if !defined(AFX_XPROPERTIESWND_H__7B914A61_6271_11D2_86B8_0040055C08D9__INCLUDED_)
#define AFX_XPROPERTIESWND_H__7B914A61_6271_11D2_86B8_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols
#include <atlconv.h>
#include <afxconv.h>

/////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndApp : See XPropertiesWnd.cpp for implementation.

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;
extern const UINT _nIDFirstListView;
extern const TCHAR _cPagesSeparator;

class CXPropertiesWndApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

// Function name	: AtlA2WHelper
// Description	    : Link error
// Return type		: LPWSTR WINAPI 
// Argument         : LPWSTR lpw
// Argument         : LPCSTR lpa
// Argument         : int nChars
LPWSTR WINAPI AtlA2WHelper(LPWSTR lpw, LPCSTR lpa, int nChars) ;
template <class classType> void DDP_DEFINE( COlePropertyPage* pPage, BOOL bSave, classType* pValue, LPCTSTR lpszPropertyName, VARTYPE vType )
{
	USES_CONVERSION;
	ULONG nObjects = NULL;
	LPDISPATCH* pDispatch = pPage->GetObjectArray(&nObjects);
	COleDispatchDriver propDispatch;
	for (int i = 0; i < (int)nObjects; i++)
	{
		LPCOLESTR lpOleStr = T2COLE(lpszPropertyName);
		DISPID dwDispID = NULL;
		if (SUCCEEDED(pDispatch[i]->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpOleStr, 1, 0, &dwDispID)))
		{
			propDispatch.AttachDispatch(pDispatch[i]);
			if (bSave)
			{
				classType nTemp = *pValue;
				propDispatch.SetProperty(dwDispID, vType, nTemp);
			}
			else
			{
				classType nTemp;
				propDispatch.GetProperty(dwDispID, vType, &nTemp);
				*pValue = nTemp;
			}
			propDispatch.DetachDispatch();
		}
	}
};

extern CBitmap* Preview(CWnd * pWnd, COLORREF colorBkGnd);



//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPROPERTIESWND_H__7B914A61_6271_11D2_86B8_0040055C08D9__INCLUDED)
