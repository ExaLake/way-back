// Object1.cpp : Implementation of CObject1
#include "stdafx.h"
#include "COMObject.h"
#include "Object1.h"

/////////////////////////////////////////////////////////////////////////////
// CObject1


STDMETHODIMP CObject1::PopMessageBox(CHAR *message, INT hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	MessageBox((HWND)hWnd, message, "", MB_OK);

	return S_OK;
}
