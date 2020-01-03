/* ADDSINK.H - Interface for a Visio Advise Sink.
 * Copyright (C) 1996 Visio Corporation. All rights reserved.
 */

//	(1)	Write a callback function to receive event notifications from Visio.
//
//	(2)	Call CoCreateAddonSink to make an instance of an "Advise Sink" object.
//
//	(3)	Find the EventList object in the Visio Object Model from which you
//		want to receive event notifications and call EventList::AddAdvise with
//		the sink pointer as its VARIANT IUnknown * argument.


//	See the sample code in "generic.cpp" for a concrete example.

//	Your callback function should match this prototype:

#ifndef _ADDSINK_H
#define _ADDSINK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef HRESULT (STDMETHODCALLTYPE VISEVENTPROC)(
						IUnknown FAR *,		// ipSink [assert]
						WORD,				// wEvent
						IUnknown FAR*,		// ipSource [don't assert]
				 		DWORD,				// dwEventID
				 		DWORD,				// dwEventSeq
				 		IUnknown FAR*,		// ipSubject [don't assert]
				 		VARIANT);			// eventExtra

typedef VISEVENTPROC *LPVISEVENTPROC;

HRESULT CoCreateAddonSink(LPVISEVENTPROC pCallback, IUnknown FAR * FAR *ppSink);

#ifdef __cplusplus
}	//	end of extern "C"
#endif


/**************************************************************************
 *+ CVisioAddonSink: Interface
 */

#ifdef __cplusplus

class CVisioAddonSink : public IDispatch
{
public:
	// IUnknown methods

	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(ULONG, AddRef)(void);
	STDMETHOD_(ULONG, Release)(void);


	// IDispatch methods

	STDMETHOD(GetTypeInfoCount)(
        UINT FAR* pctinfo);

	STDMETHOD(GetTypeInfo)( 
        UINT itinfo,
        LCID lcid,
        ITypeInfo FAR* FAR* pptinfo);

	STDMETHOD(GetIDsOfNames)( 
        REFIID riid,
        LPOLESTR FAR* rgszNames,
        UINT cNames,
        LCID lcid,
        DISPID FAR* rgdispid);

	STDMETHOD(Invoke)( 
        DISPID dispidMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS FAR* pdispparams,
        VARIANT FAR* pvarResult,
        EXCEPINFO FAR* pexcepinfo,
        UINT FAR* puArgErr);


	// CVisioAddonSink method

	STDMETHOD(VisEventProc)(
		WORD 			wEvent,			// i: code of event that's firing.
		IUnknown FAR*	ipSource,		// i: object that is firing event.
		DWORD			dwEventID,		// i: id of event that is firing.
		DWORD			dwSeq,			// i: sequence number of event.
		IUnknown FAR* 	ipSubject,		// i: subject of this event.
		VARIANT			vExtraInfo);	// i: other info. Usually nothing.


private:
	//	Private destructor enforces "Release" as means of destruction:
	virtual ~CVisioAddonSink();

	// Constructors without implementation -- prevents compiler from generating default versions:
	CVisioAddonSink();
	CVisioAddonSink(const CVisioAddonSink&);

	// Real constructor ONLY accessible through friend function CoCreateAddonSink.
	friend HRESULT CoCreateAddonSink(LPVISEVENTPROC pCallback, IUnknown FAR * FAR *ppSink);
	CVisioAddonSink(LPVISEVENTPROC pCallback);


	//	Data members:
	static ITypeInfo FAR* m_pInfo;	//	IDispatch methods fail gracefully if NULL
	ULONG m_cRef;					//	reference count
	LPVISEVENTPROC m_pCallback;		//	function to call when VisEventProc gets called...
};

#endif	//	__cplusplus

#endif	//	_ADDSINK_H
