/* IVISAUTO.H - Interface definition for IAutoSupport.
 *  Copyright (C) 1991-1996 Visio Corporation. All rights reserved.
 */

#ifndef _IVISAUTO_H
#define _IVISAUTO_H


#ifdef OLD_VISIO

	#include "ovisprox.h"

	#define	PROXVER		0x00020003L

#else

	/*
		By including this file, the client is basically asking us to compile
		existing source code against the new dual interface. This is fine, but
		we will support this only for a limited time and it is not guaranteed
		to eliminate all naming conflicts. For best results and easiest future
		maintainability, rewrite code to the "visio.h" interfaces.

		DO NOT INCLUDE THIS FILE WHEN WRITING NEW CODE! Instead, include
		"visio.h" directly and write against the interfaces desribed in
		that file.
	 */

	/* This means "define names such that old code still compiles"	*/
	#ifndef NO_VISIO_41_COMPATIBILITY_LAYER
	#define VISIO_41_COMPATIBILITY_LAYER
	#endif

	#ifdef VISIO_41_COMPATIBILITY_LAYER
		#include "v41objs.h"	/*	Defines names compatible with Visio 4.1 and earlier "ivisprox.h"	*/
	#endif

	#include "vfwddecl.h"	/*	Forward declarations necessary for non-C++ compiles					*/

	#include "visio.h"		/*	New dual interfaces (and names!) for Visio's object model			*/

	#ifdef VISIO_41_COMPATIBILITY_LAYER
		#include "v41undef.h"	/*	Undefines Shapes, Masters, etc. that got defined in v41objs.h...	*/
		#include "v41meth.h"	/*	...because some of the method names are exactly the same in here.	*/
	#endif

	#define	PROXVER		0x00040101L

#endif


#include "visconst.h"


#if !defined( OLESTR )
	#if defined( _WIN32 )
		#define OLESTR(string) L##string
	#else
		#define OLESTR(string) string
	#endif
#endif


#define	CLSID_VISIOAUTOPROXY	OLESTR("{00021A03-0000-0000-C000-000000000046}")
#define	IID_VISIOAUTOSUPPORT	OLESTR("{00021A89-0000-0000-C000-000000000046}")
#define	IID_VISIOPROXYOBJIF		OLESTR("{00021A92-0000-0000-C000-000000000046}")


#undef  INTERFACE
#define INTERFACE   IVAutoSupport

DECLARE_INTERFACE_(IVAutoSupport, IUnknown)
	{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVAutoSupport methods ***
    STDMETHOD_(DWORD, GetProxyVersion) (THIS) PURE; 
    STDMETHOD_(BOOL, CanRunProxy)	(THIS_ DWORD ver) PURE; 
    
    STDMETHOD(GetVisioObject) 		(THIS_ BOOL fActive, LPVISIOAPPLICATION FAR * ppApp) PURE;
    STDMETHOD(CreateProxy)			(THIS_ LPUNKNOWN ipIUnk, LPCLSID lpclsid, LPVOID FAR * lpipIPrx) PURE;
    STDMETHOD_(LPDISPATCH,GetDispatch)(THIS) PURE;
	};

typedef IVAutoSupport FAR* LPVAUTOSUPPORT;


#undef  INTERFACE
#define INTERFACE   IVAutoProxyObj

DECLARE_INTERFACE_(IVAutoProxyObj, IUnknown)
	{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface)       (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)        (THIS) PURE;
    STDMETHOD_(ULONG,Release)       (THIS) PURE;

    // *** IVProxyObjIf methods ***
	STDMETHOD_(IDispatch FAR*, ipVisDisp)(void);
	STDMETHOD_(BSTR, bstrModuleFileName)(void);
	};

typedef IVAutoProxyObj FAR* LPVISPROXYOBJIF;


#endif /* _IVISAUTO_H */
