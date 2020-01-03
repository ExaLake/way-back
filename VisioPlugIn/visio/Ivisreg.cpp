/*	IVISREG.CPP - Helper functions for starting Visio
 *  Copyright (C) 1991-1997 Visio Corporation. All rights reserved.
 */

#include <windows.h>
#include <ole2.h>

#if !defined (_WIN32)
	#include <dispatch.h>
#endif

#include <initguid.h>

#define NO_VISIO_41_COMPATIBILITY_LAYER

#include "ivisreg.h"

/*
 *	Note - This file is meant to work as either a C or C++ module.  To
 *	do so we need a special macro for invoking properties and methods
 *	on our Visio interfaces.  The macro below handles the translation
 *	between C and C++ for us but, unfortunately, it makes our function
 *	calls look very strange.  For instance here is a comparison of the
 *	different methods.  The advantage is we need only write one file.
 *
 *	In C			lpIVApp->lpVtbl->Version(lpIVApp, &bstr);
 *	In C++			lpIVApp->Version(&bstr);
 *	INVOKE Macro	INVOKE(lpIVApp, Version) &bstr);
 *
 *	But to make some things easier to read there is a second macro for
 *	methods that have no arguments.  It reads:
 *
 *	In C			lpIVApp->lpVtbl->Release(lpIVApp);
 *	In C++			lpIVApp->Release();
 *	INVOKE Macro	INVOKE_(lpIVApp, Release);
 */

#ifdef __cplusplus
#define REF(r) (r)
#define INVOKE(i, m)	i->m(
#define INVOKE_(i, m)	i->m();
#else
#define REF(r) (&(r))
#define INVOKE(i, m)	i->lpVtbl->m(i,
#define INVOKE_(i, m)	i->lpVtbl->m(i);
#endif


/*************************************************************************
 *                        Private Declarations
 *
 * lpIVAS - Our very own proxy object that we register every time
 *          this module is entered.  Supporting calls go through this 
 *          proxy for Application objects.  It gets cleaned up after
 *          we make our Get/Create calls for the application interface.
 *
 * hLastError - Contains the last error that occurred.  Should be
 *          retrieved through vaoGetLastError for detailed error
 *          reporting.
 */
 
static LPVAUTOSUPPORT lpIVAS     = NULL;
static HRESULT        hLastError = NOERROR;


/*
 * Forward Prototypes of private (static) helpers
 */
 
static short vaoInit(void);

static short vaoUnInit(void);

static short vaoGetVisioApp(
	LPVISIOAPPLICATION FAR *);
	
static short vaoCreateVisioApp(
	LPVISIOAPPLICATION FAR *);

static void SetLastResult(HRESULT);

/*************************************************************************
 *                          Private Functions Bodes
 ************************************************************************/
 
/*************************************************************************
 *+ vaoInit
 *
 *	Initializes the module by getting an instance of the Visio 
 *	automation proxy.
 */
 
static short vaoInit()
	{
	CLSID clsid;
	IID iid;
	SCODE sc;
	
	if ( NULL != lpIVAS )
		return VAO_SUCCESS;
	
	CLSIDFromString(CLSID_VISIOAUTOPROXY, &clsid);
	IIDFromString(IID_VISIOAUTOSUPPORT, &iid);
	
	sc = GetScode(CoCreateInstance(REF(clsid), NULL, CLSCTX_INPROC, REF(iid),
									(LPVOID FAR *)&lpIVAS));
	
	SetLastResult(ResultFromScode(sc));
	
	if ( NULL != lpIVAS )
		{
		if ( !(INVOKE(lpIVAS, CanRunProxy) PROXVER)) )
			{
			vaoUnInit();
			return VAO_BAD_VERSION;
			}
		else
			{
			return VAO_SUCCESS;
			}
		}
	else
		{
		return VAO_NOT_INSTALLED;
		}
	}

	
/*************************************************************************
 *+ vaoUnInit
 *
 *	Releases the Visio proxy being used by the module.
 */
 
static short vaoUnInit()
	{
	if ( NULL != lpIVAS )
		{
		INVOKE_(lpIVAS, Release);
		lpIVAS = NULL;
		}
	
	return VAO_SUCCESS;
	}


/*************************************************************************
 *+ vaoGetVisioApp
 *
 *	Using GetActiveObject, attempts to retrieve the 
 *	active instance of Visio, if one is running.
 */
 
static short vaoGetVisioApp(
	LPVISIOAPPLICATION FAR * lplpIVApp)
	{
	HRESULT hResult;
	IUnknown FAR *pUnk = NULL;

	*lplpIVApp = NULL;

#ifdef OLD_VISIO
	//	Not dual interface; uses proxies
	hResult = INVOKE(lpIVAS, GetVisioObject) TRUE, lplpIVApp);
#else
	//	Dual interface; doesn't use proxies
	hResult = GetActiveObject(REF(CLSID_Application), NULL, &pUnk);

	if (pUnk!=NULL)
		{
		INVOKE(pUnk, QueryInterface) REF(IID_IVApplication), (LPVOID *) lplpIVApp);

		INVOKE_(pUnk, Release);
		pUnk= NULL;
		}
#endif

	SetLastResult(hResult);

	if ( NULL != *lplpIVApp )
		return VAO_GET;
	else
		return VAO_NOT_RUNNING;
	}

	
/*************************************************************************
 *+ vaoCreateVisioApp
 *
 *	Using the proxy support interface, attempts to create a new 
 *	Visio application instance.
 */
 
static short vaoCreateVisioApp(
	LPVISIOAPPLICATION FAR * lplpIVApp)
	{
	HRESULT hResult;

#ifdef OLD_VISIO
	//	Not dual interface; uses proxies
	hResult = INVOKE(lpIVAS, GetVisioObject) FALSE, lplpIVApp);
#else
	//	Dual interface; doesn't use proxies
	hResult = CoCreateInstance
				(
					REF(CLSID_Application), NULL,
					CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER,
					REF(IID_IVApplication), (LPVOID *) lplpIVApp
				);
#endif

	SetLastResult(hResult);

	/*
	 *	Notice we return VAO_ERROR if we don't get the app interface
	 *	because we're assuming if we get the support interface Visio
	 *	must be installed.
	 */

	if ( NULL != *lplpIVApp )
		return VAO_CREATE;
	else
		return VAO_ERROR;
	}
	
	
/*************************************************************************
 *+ SetLastResult
 *
 *	Private function for setting the last error.
 */
 
static void SetLastResult(HRESULT hError)
	{
	hLastError = hError;
	}

/*************************************************************************
 *                         Public Functions
 ************************************************************************/
 
/*************************************************************************
 *+ vaoGetVisio
 *
 *	Gets a Visio Application interface by retrieving the active
 *	instance, creating a new one or doing both if the user specifies.
 *	A flag is passed for both and if the get active fails a new one
 *	is created.
 *
 *	The return value is one of the VAO_ result codes which are defined
 *	in IVISREG.H.
 */

#ifdef __cplusplus
extern "C" {
#endif

short vaoGetVisio(							// VAO_ result code
	BOOL fActive,							// TRUE => Get Active
	BOOL fCreate,							// TRUE => Create New
	LPVISIOAPPLICATION FAR * lplpIVApp)		// Application Interface
	{
	short sResult;	//	intentionally uninitialized - assigned to immediately
					//	below by call to vaoInit

	/*
	 * First we make sure that we can get an automation support
	 * proxy.  If not we can't do anything.  Then, if the application
	 * interface passed in is set we have to release it!
	 */
	 
	if ( !fActive && !fCreate )
		return VAO_ERROR;
		
	if ( VAO_SUCCESS != (sResult = vaoInit()) )
		return sResult;
	
	if ( NULL != *lplpIVApp )
		{
		INVOKE_((*lplpIVApp), Release);
		*lplpIVApp = NULL;
		}
		
	/*
	 * Now we get to the real stuff.
	 */
	 
	if ( fActive )
		sResult = vaoGetVisioApp(lplpIVApp);
	
	if ( (VAO_GET != sResult) && fCreate )
		sResult = vaoCreateVisioApp(lplpIVApp);
		
	vaoUnInit();
	
	return sResult;
	}


/*************************************************************************
 *+ vaoGetObject
 *
 *	A more general form of vaoGetVisio that will attempt to get a running
 *	instance of Visio by either getting the active instance or, if that
 *	fails, creating a new one.  If either of these fails then either a
 *	fatal error has occurred or Visio is not installed.
 *
 *	Return Value:
 *
 *	The return value is either VAO_SUCCESS or one of the errors 
 *	returned through vaoGetVisio.
 */

short vaoGetObject(
	LPVISIOAPPLICATION FAR * lplpIVApp)		// Visio App Interface
	{
	short sResult;	//	intentionally uninitialized - assigned to immediately
					//	below by call to vaoGetVisio

	/*
	 *	We simply call our fellow internal to either Get or Create
	 *	a Visio instance.
	 */
	 
	sResult = vaoGetVisio(TRUE, TRUE, lplpIVApp);
	
	if ( VAO_CREATE == sResult || VAO_GET == sResult )
		sResult = VAO_SUCCESS;
		
	return sResult;
	}


#ifdef __cplusplus
//	Overloaded function for linker to find:

#ifndef OLD_VISIO
#ifndef NO_VISIO_41_COMPATIBILITY_LAYER
//	Also provide a version the linker can find for other files that get
//	compiled with NO_VISIO_41_COMPATIBILITY_LAYER defined...

//	In THIS *.cpp file, LPVISIOAPPLICATION is "IVisioApplication *"
//	In *.cpp files with NO_... defined, LPVISIOAPPLICATION is "Application *"
//	They're really two different names for the same thing.

#ifdef Application
#undef Application
#endif

#ifdef __cplusplus
interface Application;
#else
typedef interface Application Application;
#endif

typedef Application FAR * _LPVISIOAPPLICATION;

short vaoGetObject(
	_LPVISIOAPPLICATION FAR *lplpIVApp)		// Visio App Interface
	{
	short sResult= vaoGetObject((LPVISIOAPPLICATION FAR *)lplpIVApp);
	return sResult;
	}

#endif	//	NO_VISIO_41_COMPATIBILITY_LAYER
#endif	//	OLD_VISIO
#endif	//	__cplusplus

/*************************************************************************
 *+ vaoGetLastError
 *
 *	Returns the last error encountered by this module.  Should be called 
 *	immediately after the error occurs because future operations will
 *	probably reset the flag.
 */
 
HRESULT vaoGetLastError()
	{
	return hLastError;
	}
	
#ifdef __cplusplus
}
#endif

	
