/*	VDLLMAIN.C -   DllMain  ||  LibMain + WEP
 *  Copyright (C) 1991-1997 Visio Corporation. All rights reserved.
 *
 *	This file provides implementations for the
 *	basic routines needed by a Windows DLL.
 */

#include "vao.h"

// DllMain (win32 only) 
//	Standard dll entry point for WIN32 dll. Windows calls DllMain when
//	it loads and unloads a dll. Implementation here does nothing but
//	record handle of dll instance. 
// 	
// LibMain (win16 only)
//	Standard dll entry point for WIN16 dll. Windows calls LibMain when
//	it loads dll. Implementation here does standard LibMain stuff and
//	records dll's instance handle.
//
// WEP (win16 only)
//	Standard dll entry point for WIN16 dll. Windows calls WEP when it
//	unloads dll.
//
// Design note:
//	Typically a win16 dll is "multi-instance." If more than one instance
//	of Visio16 is running then all will be interacting with a lone 
//	instance of a win16 VSL. An entirely robust win16 VSL should be
//	designed assuming the possibility that it may need to manage sessions
//	associated with multiple instances of Visio. Typically a win32 dll
//	is "single instance." If many instances of Visio32 are running, then
//	many instances of a win32 VSL will be initiated. The design of a win32
//	VSL needn't take into account the possibility that it has to deal with
//	sessions into more than once instance of Visio. If you want to develop
//	a VSL that can be ported to either win16 or win32, then it's probably
//	best to presume the more general win16 scenario.
//
#if defined(_WIN32)


BOOL WINAPI DllMain ( HINSTANCE		hModule,
					  DWORD			fdwReason,
					  LPVOID		lpvReserved )
	{
   UNUSED_ARG(lpvReserved);

  	switch( fdwReason )
		{
    	case DLL_PROCESS_ATTACH:
    		gbl_hDLLModule = (HINSTANCE)hModule;
    		break;

    	case DLL_PROCESS_DETACH:
    	case DLL_THREAD_DETACH:
    	case DLL_THREAD_ATTACH:
    	default:
    		break;
    	}

    return TRUE;
	}

#else /* win16 */

// Assign the WEP exit procedure to its own segment as recommended by
// MicroSoft. If library opts to use the WEP() provided by these utilities
// then it should declare WEP_TEXT to be a fixed segment in its .def file,
// e.g.:
//
//		SEGMENTS
//			WEP_TEXT CLASS 'CODE' PRELOAD FIXED
//
int CALLBACK WEP ( int bSystemExit );
#pragma alloc_text (WEP_TEXT,WEP)

#ifdef __BORLANDC__
#pragma argsused
#endif
int CALLBACK LibMain ( 	HINSTANCE	hModule,
						WORD		wDataSeg,
						WORD		cbHeapSize,
						LPSTR		lpNotUsed )
	{
	// This implements a default LibMain() for those dll's that choose
	// to use the dll initialization routine in libentry.obj that comes
	// with the Windows sdk. The LibEntry() routine there calls LibMain()
	// which the lib provides to do specified library initialization.
	//
	// This default implementation simply performs the standard prescribed
	// Windows idioms for library startup.
	//
	// It also stashes the dll's module handle in gbl_hDLLModule for later
	// reference by VLIBUTL_hModule.
	//
	// LibMain() should return a value of 1 if initialization is successful.

	if ( !cbHeapSize )
		return 0;

	gbl_hDLLModule = hModule;

	UnlockData(0);
	return 1;
	}

#ifdef __BORLANDC__
#pragma argsused
#endif
int CALLBACK WEP ( int bSystemExit )
	{
	// WEP (Windows Exit Procedure) performs cleanup tasks for this
	// library just before Windows unloads it. WEP() is called automatically
	// by Windows prior to its unloading the library, i.e. after someone
	// has made a call to FreeLibrary() which erases the last pending
	// LoadLibrary() anyone has performed on the library. MicroSoft
	// recommends that a dll have a WEP() function, even if it does
	// nothing but returns success (1), as in this default implementation.
	//
	return(1);
	}

#endif /* defined(_WIN32) */
