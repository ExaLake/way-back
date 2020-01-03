/* ADDSINK.CPP - Implementation of a client side Visio Advise Sink.
 * Copyright (C) 1991-1997 Visio Corporation. All rights reserved.
 */

#include <windows.h>
#include <ole2.h>

#if !defined (_WIN32)
	#include <dispatch.h>
#endif

#include "addsink.h"
#include "vao.h"

/**************************************************************************
 *+ CVisioAddonSink: INTERFACEDATA tables
 */

// CVisioAddonSink virtual member indices - must be in the same order 
// as virtual member functions.
//
enum IX_Sink
{
	IX_Sink_QueryInterface= 0,
	IX_Sink_AddRef,
	IX_Sink_Release,
	IX_Sink_GetTypeInfoCount,
	IX_Sink_GetTypeInfo,
	IX_Sink_GetIDsOfNames,
	IX_Sink_Invoke,
	IX_Sink_VisEventProc,
	IX_Sink_Dtor
};

// CVisioAddonSink member ids. These are referenced in tables we feed to
// CreateDispTypeInfo to get m_ptinfo. Set given values must be ids of those
// members we want to dispatch to from Invoke. Values selected are arbitrary.
//
enum ID_Sink 
{
	ID_Sink_avail = DISPID_VALUE,	// don't squander default id.
	ID_Sink_VisEventProc
};

#define	SD(n)		static OLECHAR stc_Str##n[]= OLESTR(#n);
#define	SR(n)		stc_Str##n

//	CreateDispTypeInfo() requires table
// typeinfo structure that can be fed to standard dispatch services such 
// as DispInvoke(). Table describes the set of methods we want Invoke()
// to be able to dispatch to.
//
SD(VisEventProc)

SD(Event)
SD(Source)
SD(ID)
SD(Seq)
SD(Subject)
SD(Extra)

static PARAMDATA rgpdataVisEventProc[]=
{
	{	SR(Event),	VT_I2 		},
	{	SR(Source),	VT_UNKNOWN	},
	{	SR(ID),		VT_I4 		},
	{	SR(Seq),	VT_I4 		},
	{	SR(Subject),VT_UNKNOWN 	},
	{	SR(Extra),	VT_VARIANT 	},
};

static METHODDATA rgmdataSink[]=
{
	{
		SR(VisEventProc),
		rgpdataVisEventProc,
		ID_Sink_VisEventProc,
		IX_Sink_VisEventProc,
		CC_STDCALL,
		sizeof(rgpdataVisEventProc)/sizeof(rgpdataVisEventProc[0]),
		DISPATCH_METHOD,
		VT_EMPTY
	}
};

static INTERFACEDATA idataSink=
{
	rgmdataSink,
	sizeof(rgmdataSink)/sizeof(rgmdataSink[0])
};


//	Shared type info ptr across all instances of CVisioAddonSink:
ITypeInfo FAR *CVisioAddonSink::m_pInfo= NULL;



/**************************************************************************
 *+ CVisioAddonSink: Implementation
 */

CVisioAddonSink::CVisioAddonSink(LPVISEVENTPROC pCallback)
{
	HRESULT hr= NOERROR;

	m_pCallback= pCallback;

	m_cRef= 0;


	// Call CreateDispTypeInfo() with tables describing methods we want
	// Invoke to be able to dispatch to. Result is recorded in m_pInfo.
	// This class does not assert m_pInfo. Other methods should gaurd
	// against !m_pInfo.

	if (m_pInfo)
	{
		m_pInfo->AddRef();
	}
	else
	{
		hr= CreateDispTypeInfo(&idataSink, LOCALE_USER_DEFAULT, &m_pInfo);
	}

   UNUSED_ARG(hr);
}

CVisioAddonSink::~CVisioAddonSink()
{
	if ( m_pInfo )
	{
		if (0==m_pInfo->Release())
			m_pInfo= NULL;	//	be sure not to leave dangling ptr if we were last hold on pInfo...
	}

	// assert m_cRef==0
}

STDMETHODIMP CVisioAddonSink::QueryInterface(REFIID riid, void FAR* FAR* ppv)
{
	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDispatch))
	{
		*ppv= this;
		AddRef();
		return NOERROR;
	}
	else
	{
		*ppv= NULL;
		return ResultFromScode(E_NOINTERFACE);
	}
}

STDMETHODIMP_(ULONG) CVisioAddonSink::AddRef(void)
{
	m_cRef++;

	return m_cRef;
}

STDMETHODIMP_(ULONG) CVisioAddonSink::Release(void)
{
	m_cRef--;

	if (m_cRef==0)
	{
		delete this;
		return 0;
	}
	else
	{
		return m_cRef;
	}
}

STDMETHODIMP CVisioAddonSink::GetTypeInfoCount(
    /* [out] */ UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}

STDMETHODIMP CVisioAddonSink::GetTypeInfo(
    /* [in] */ UINT itinfo,
    /* [in] */ LCID lcid,
    /* [out] */ ITypeInfo FAR* FAR* pptinfo)
{
	HRESULT hr= NOERROR;

   UNUSED_ARG(lcid);

	if ( pptinfo && m_pInfo )
	{
		if ( itinfo == 0 )
		{
			m_pInfo->AddRef();
			*pptinfo= m_pInfo;
		}
		else
		{
			*pptinfo= NULL;
			hr= ResultFromScode(DISP_E_BADINDEX);
		}
	}
	else
	{
		hr= ResultFromScode(DISP_E_EXCEPTION);
	}

	return hr;
}

STDMETHODIMP CVisioAddonSink::GetIDsOfNames(
    /* [in] */ REFIID riid,
    /* [size_is][in] */ LPOLESTR FAR* rgszNames,
    /* [in] */ UINT cNames,
    /* [in] */ LCID lcid,
    /* [size_is][out][in] */ DISPID FAR* rgdispid)
{
	HRESULT hr;

   UNUSED_ARG(&riid);
	UNUSED_ARG(lcid);

	if ( m_pInfo )
	{
		hr= DispGetIDsOfNames(m_pInfo, rgszNames, cNames, rgdispid);
	}
	else
	{
		hr= ResultFromScode(DISP_E_EXCEPTION);
	}

	return hr;
}

STDMETHODIMP CVisioAddonSink::Invoke(
    /* [in] */ DISPID dispidMember,
    /* [in] */ REFIID riid,
    /* [in] */ LCID lcid,
    /* [in] */ WORD wFlags,
    /* [unique][in] */ DISPPARAMS FAR* pdispparams,
    /* [unique][out][in] */ VARIANT FAR* pvarResult,
    /* [out] */ EXCEPINFO FAR* pexcepinfo,
    /* [out] */ UINT FAR* puArgErr)
{
	HRESULT hr;

	UNUSED_ARG(&riid);
   UNUSED_ARG(lcid);

	if ( m_pInfo )
	{
		hr= DispInvoke(this, m_pInfo, dispidMember,
							 wFlags, pdispparams, pvarResult,
							 pexcepinfo, puArgErr);
	}
	else
	{
		hr= ResultFromScode(DISP_E_EXCEPTION);
	}

	return hr;
}

STDMETHODIMP CVisioAddonSink::VisEventProc(
	WORD 			wEvent,			// i: id of interface to query for.
	IUnknown FAR*	ipSource,		// i: object that is firing event.
	DWORD			dwEventID,		// i: id of event that is firing.
	DWORD			dwSeq,			// i: sequence number of event.
	IUnknown FAR* 	ipSubject,		// i: subject of this event.
	VARIANT			vExtraInfo)		// i: other info. Usually nothing.
{
	HRESULT hr= NOERROR;

	if (m_pCallback)
	{
		hr= (*m_pCallback)(this, wEvent, ipSource, dwEventID, dwSeq, ipSubject, vExtraInfo);
	}

	return hr;
}

HRESULT CoCreateAddonSink(LPVISEVENTPROC pCallback, IUnknown FAR * FAR *ppSink)
{
	HRESULT hr= ResultFromScode(E_FAIL);

	//	assert ppSink!=NULL

	*ppSink= new CVisioAddonSink(pCallback);

	if (*ppSink)
	{
		(*ppSink)->AddRef();
		hr= NOERROR;
	}

	return hr;
}
