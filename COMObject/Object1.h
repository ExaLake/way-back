// Object1.h : Declaration of the CObject1

#ifndef __OBJECT1_H_
#define __OBJECT1_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CObject1
class ATL_NO_VTABLE CObject1 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CObject1, &CLSID_Object1>,
	public IDispatchImpl<IObject1, &IID_IObject1, &LIBID_COMOBJECTLib>
{
public:
	CObject1()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OBJECT1)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CObject1)
	COM_INTERFACE_ENTRY(IObject1)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IObject1
public:
	STDMETHOD(PopMessageBox)(CHAR* message, INT hWnd);
};

#endif //__OBJECT1_H_
