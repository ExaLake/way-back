/*	VAO.C - Fundamental routines needed to implement a VSL for Visio.
 *  Copyright (C) 1991-1996 Visio Corporation. All rights reserved.
 *
 *	This file provides implementations for the routines prototyped
 *	in vao.h.
 *
 *	Vao.h defines the interface between Visio and VSLs. A VSL is a 
 *	dynamic link library that implements the protocol defined in vao.h. 
 *	A VSL implements one or more Visio Add-ons. 
 *
 *	The c-cpp directory shipped with Visio contains this vao.c file and
 *	vao.h. It also contains the source files for a sample VSL written in 
 *	C and a sample VSL written in C++. Both projects include this vao.c
 *	file. The source for the sample projects is portable to either WIN16 
 *	or WIN32, but there are separate .mak files provided for building the 
 *	WIN16 or WIN32 versions.
 *
 *	If you're developing a VSL, you can opt to use the implementations 
 *	provided by this vao.c file. But you're not required to use them.
 *	So long as your VSL implements the protocol defined in vao.h, you
 *	can implement it however works best for you.
 */

#include "vao.h"

//---------------------------------------------------------------------------
//	*** GLOBAL (TO THIS DLL) DATA DEFINED IN THIS FILE ***
//---------------------------------------------------------------------------

// Gbl_hDLLModule is the instance handle for the dll this code is running in.
// It gets set in LibMain() when this dll gets loaded. VLIBUTL_hModule()
// simply returns gbl_hDLLModule to its callers.

HINSTANCE gbl_hDLLModule = NULL;

//---------------------------------------------------------------------------
//	PRIVATE: VAO DATA STRUCTURES AND STATIC DATA
//---------------------------------------------------------------------------

// Stc_VisioCallBack simply stores the address of the entry point in
// Visio that the lib is to call when it wants to call Visio back. This
// address is passed to the lib (amongst other times) when Visio sends
// a load message to the lib. Stc_VisioCallBack is initialized by
// VAOUtil_SetVisCallBack(). VAOUtil_VisCallBack() returns its value.
//
// VAOUtil_SetVisCallBack() is called by VAOUtil_DefVisMainProc() when it
// handles a load message from Visio.
//
// Thus if a VSL calls VAOUtil_DefVisMainProc() when Visio sends a load 
// message to it, it need never call VAOUtil_SetVisCallBack().
//
// However, if it opts not to use VAOUtil_DefVisMainProc() to handle load
// messages, and if it wants to use one of the several utilities defined
// herein that depend on stc_VisioCallBack, then the lib should call
// VAOUtil_SetVisCallBack() when it handles a load message from Visio.
//
static LPVAOFUNC stc_VisioCallBack = (LPVAOFUNC)NULL;

//---------------------------------------------------------------------------
//	IMPLEMENTATION OF BASIC SERVICES FOR ADD-ONS:
//---------------------------------------------------------------------------

#ifdef __BORLANDC__
#pragma argsused
#endif
VAOU_PROC(VAORC) VAOUtil_DefVisMainProc ( VAOMSG	wMsg,
										  WORD		wParam,
										  LPVOID	lpParam,
										  HINSTANCE	hResources )
	{
	// Provides default response to messages from Visio.
	//
	// If you're familiar with DefWindowProc() in Windows, this is the analog
	// for use in Visio Add-ons. Just like you use DefWindowProc() from a
	// window procedure to handle a window message that you don't want to
	// implement specific behavior for, you can use VAOUtil_DefVisMainProc()
	// from your Add-on's VisioLibMain() to handle messages from Visio that
	// you don't want to implement specific behavior for.
	//
	// VAOUtil_DefVisMainProc()'s prototype ALMOST matches that of
	// VisioLibMain().
	//
	// If your VisioLibMain() is called and you don't want to handle the
	// message, then just call VAOUtil_DefVisMainProc() with the arguments
	// passed to VisioLibMain() and return whatever it returns.
	// VAOUtil_DefVisMainProc()'s responses will be correct, albeit not
	// particularly interesting.
	//
	// VAOUtil_DefVisMainProc()'s prototype differs from VisioLibMain()'s in
	// that it has an extra parameter, namely hResources. This should always
	// be passed as null.
	//
	#define lpv2lparm ((LPVAOV2LSTRUCT)lpParam)

	VAORC result = VAORC_SUCCESS;

	switch ( wMsg )
		{
		case V2LMSG_LOAD:
			//
			// wParam:	Interface version being used by sending Visio.
			// lpParam: LPVAOFUNC (Address of Visio's call back proc.)
			//
			// proper response: VAO_L2V_VERSION() | VAORC_L2V_LOADFAILED
			//
			result = VAO_L2V_VERSION();

			// We stash call back address for later use by these utilities.
			//
			// If this is first load, we expect VAOUtil_VisCallBack() to
			// be null, otherwise we've been loaded before and we expect
			// lpParam to equal existing call back address or we're talking
			// to different vaomgr's with different call back addresses which
			// this design can't handle.
			//
			if ( !VAOUtil_VisCallBack() )
				VAOUtil_SetVisCallBack((LPVAOFUNC)lpParam);

			else if ( VAOUtil_VisCallBack() != (LPVAOFUNC)lpParam )
				result = VAORC_L2V_LOADFAILED;

			break;

		case V2LMSG_UNLOAD:
			//
			// wParam:	undefined
			// lpParam: null
			//
			// proper response: moot (but VAORC_SUCCESS is appreciated)
			//
			break;

		case V2LMSG_ENUMADDONS:
			break;

		case V2LMSG_ISAOENABLED:
			//
			// wParam:	Ordinal of Add-on to determine enabled status of.
			// lpParam: LPVAOV2LSTRUCT
			//
			// proper response: VAORC_L2V_ENABLED | 0

			result = VAORC_L2V_ENABLED;
			break;

		case V2LMSG_RUN:
			//
			// wParam:	Ordinal of Add-on to run.
			// lpParam: LPVAOV2LSTRUCT
			//
			// proper response: VAORC_SUCCESS |
			//					VAORC_L2V_MODELESS |
			//					VAORC_error
			break;

		case V2LMSG_RUNABOUT:
			//
			// wParam:	Ordinal of Add-on to run.
			// lpParam: LPVAOV2LSTRUCT
			//
			// proper response: VAORC_SUCCESS |
			//					VAORC_L2V_MODELESS |
			//					VAORC_error
			break;

		case V2LMSG_RUNHELP:
			//
			// wParam:	Ordinal of Add-on to run.
			// lpParam: LPVAOV2LSTRUCT
			//
			// proper response: VAORC_SUCCESS |
			//					VAORC_L2V_MODELESS |
			//					VAORC_error
			break;

		case V2LMSG_KILLSESSION:
			{
			// wParam:	0
			// lpParam: LPVAOV2LSTRUCT
			//
			// proper response: moot
			//
			break;
			}

		default:
			result = VAORC_L2V_BADMSG;
			break;
		};

	return result;
	}


VAOU_PROC(VOID) VAOUtil_SetVisCallBack ( LPVAOFUNC lpfunc )
	{
	// VAOUtil_SetVisCall() is to be called in order to tell these utilities
	// Visio's call back address. VAOUtil_SetVisCallBack() typically need
	// not be called by an Add-on library.
	//
	stc_VisioCallBack = lpfunc;
	}


VAOU_PROC(LPVAOFUNC) VAOUtil_VisCallBack ( )
	{
	// VAOUtil_VisCallBack() simply returns the address of Visio's call
	// back procedure.
	//
	return stc_VisioCallBack;
	}


#if !defined(_WIN32)
VAOU_PROC(HINSTANCE) VAOUtil_hAppInst ( )
	{
	// This returns the instance handle of the currently running exe that
	// has called the dll into which VAOUtil_hAppInst() is linked (which is
	// presumably an instance of Visio).
	//
	// Note that you can ascertain the running instance handle via fashions
	// other than by calling VAOUtil_hAppInst().
	//
	// In particular, if you were willing to allow your lib to depend on
	// toolhelp.lib, then the actual implementation done here is in effect
	// equivelent to, albeit more slimy than:
	//
	//		#include <toolhelp.h>
	//		HINSTANCE result = (HINSTANCE)NULL;
	//		HTASK hCurTask;
	//		if ( (hCurTask = GetCurrentTask()) )
	//			{
	//			TASKENTRY te;
	//			te.dwSize = sizeof(te);
	//			if ( TaskFindHandle((TASKENTRY FAR*)&te,hCurTask) )
	//				result = te.hInst;
	//			}
	//		return result;

	// -- See MSWindows SDK Programmer's Ref. Vol. 3 pp. 407
	// -- See Undocumented Windows pp. 194

	return (HINSTANCE)
				*((LPWORD)( (((DWORD)(WORD)GetCurrentTask()) << 16 ) |
							0x1C ));
	}
#endif /* !defined(_WIN32) */


VAOU_PROC(VAORC) VAOUtil_RegisterAddons ( WORD				wSessID,
										  LPVAOREGSTRUCT	lpRegStructArray,
										  WORD				nRegStructs )
	{
	// This registers Add-ons with Visio for a lib.
	//
	// This simply takes a pointer to a contiguous array of filled out Visio
	// Add-on registration structures (see vao.h) with nRegStructs
	// entries and registers the described Add-ons with Visio. Typically
	// Add-ons are registered in response to an enumAddOns message that Visio
	// has sent to the lib. WSessID should be the session id passed to the
	// lib along with the enumAddOns message.

	VAORC result = VAORC_SUCCESS;

	if ( lpRegStructArray )
		{
		for ( ;
			  result == VAORC_SUCCESS && nRegStructs;
			  nRegStructs--, lpRegStructArray++ )
			{
			result = ((*stc_VisioCallBack)(L2VMSG_REGADDON,
										   wSessID,
										   lpRegStructArray));
			}
		}
	else
		result = VAORC_FAILURE;

	return result;
	}
