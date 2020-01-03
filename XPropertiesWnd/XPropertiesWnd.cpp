/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 11/19/98 12:06:34 AM
  Comments: XPropertiesWnd.cpp : Implementation of CXPropertiesWndApp and DLL registration.
 ************************************/

#include "stdafx.h"
#include "XPropertiesWnd.h"
#include "gdi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CXPropertiesWndApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x7b914a58, 0x6271, 0x11d2, { 0x86, 0xb8, 0, 0x40, 0x5, 0x5c, 0x8, 0xd9 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;
const TCHAR _cPagesSeparator = TCHAR('#');
const UINT _nIDFirstListView = 1000;


////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndApp::InitInstance - DLL initialization

BOOL CXPropertiesWndApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		AfxEnableControlContainer();
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CXPropertiesWndApp::ExitInstance - DLL termination

int CXPropertiesWndApp::ExitInstance()
{
	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// Function name	: RegisterActiveX
// Description	    : Call to register ActiveX control
// Return type		: BOOL 
// Argument         : LPCTSTR lpszActiveXFileName
BOOL RegisterActiveX(LPCTSTR lpszActiveXFileName, LPCTSTR lpszFRegister = _T("DllRegisterServer"))
{
	HINSTANCE hInstance = NULL;
	CString sAXFileName(lpszActiveXFileName);
	static TCHAR BASED_CODE szFilter[] = _T("ActiveX Controls (*.ocx)|*.ocx||");
	do 
	{
		if ((hInstance = LoadLibrary(sAXFileName)) == NULL)
		{
			CString warning;
			warning.Format(_T("Load library not found, or failed."));
			AfxMessageBox(warning);
			CFileDialog fd(TRUE, NULL, sAXFileName, NULL, szFilter , NULL);
			if (fd.DoModal() == IDOK)
				sAXFileName = fd.GetFileName();
			else break;
		}
		else
		{
			FARPROC lpDllEntryPoint = GetProcAddress(hInstance, (LPCSTR)lpszFRegister);
			if (lpDllEntryPoint != NULL)
			{
				(*lpDllEntryPoint)();
				return TRUE;
			}
			else
			{
				FreeLibrary(hInstance);
				hInstance = NULL;
			}
		}
	} while (hInstance == NULL);
	return FALSE;
}

// Function name	: Preview
// Description	    : preview a window into a bitmap
// Return type		: CBitmap* 
// Argument         : CWnd* pWnd
// Argument         : COLORREF colorBkGnd
CBitmap* Preview(CWnd* pWnd, COLORREF colorBkGnd)
{
	CBitmap *pBitmap = NULL, bitmapNonClient;
	CWnd *pDrawWnd = pWnd;
	ASSERT (pWnd);
	if (pDrawWnd && ::IsWindow(pDrawWnd->m_hWnd))
	{
		CRect rectWindow; pDrawWnd->GetWindowRect(rectWindow);
		CRect rectClient; pDrawWnd->GetClientRect(rectClient);
		CPoint p(0,0);
		pDrawWnd->ClientToScreen(&p);
		rectClient.OffsetRect(p.x - rectWindow.left, p.y - rectWindow.top);
		CGdiStack stack;
		CDC* pDC = pDrawWnd->GetDC();
		CDC dcMemSourceNonClient, dcMemDestination;
		if (dcMemSourceNonClient.CreateCompatibleDC(pDC))
			if (dcMemDestination.CreateCompatibleDC(pDC))
				if (pBitmap = new CBitmap())
					if (pBitmap->CreateCompatibleBitmap(pDC, rectWindow.Width(), rectWindow.Height()))
						if (bitmapNonClient.CreateCompatibleBitmap(pDC, rectWindow.Width(), rectWindow.Height()))
						{
							CBrush brBkGnd(colorBkGnd);
							stack.Push(&dcMemSourceNonClient, &bitmapNonClient);
							stack.Push(&dcMemSourceNonClient, &brBkGnd);
							dcMemSourceNonClient.PatBlt(0,0,rectWindow.Width(), rectWindow.Height(), PATCOPY);
							stack.Push(&dcMemDestination, pBitmap);
							if (pWnd)
								pDrawWnd->Print(&dcMemSourceNonClient, PRF_NONCLIENT);
							dcMemDestination.BitBlt(0,0,rectWindow.Width(), rectWindow.Height(), &dcMemSourceNonClient, 0,0, SRCCOPY);
							if (pWnd)
							{
								CPoint pLT(0,0);
								pDrawWnd->ClientToScreen(&pLT);
								dcMemDestination.SetViewportOrg(pLT.x - rectWindow.left, pLT.y - rectWindow.top);
								pDrawWnd->Print(&dcMemDestination, PRF_CHILDREN | PRF_CLIENT | PRF_ERASEBKGND);
							}
							stack.Pop();
							stack.Pop();
							stack.Pop();
							brBkGnd.DeleteObject();
							bitmapNonClient.DeleteObject();
							dcMemSourceNonClient.DeleteDC();
							dcMemDestination.DeleteDC();
						}
		pDrawWnd->ReleaseDC(pDC);
	}
	return pBitmap;
}

// DllRegisterServer - Adds entries to the system registry
// Function name	: DllRegisterServer
// Description	    : Call to register ActiveX control
// Return type		: STDAPI 
// Argument         : void
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

/*	if (!RegisterActiveX(_T("xFloorWnd.ocx")))
		return ResultFromScode(SELFREG_E_TYPELIB);*/

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
