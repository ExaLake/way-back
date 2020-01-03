/*
 *   (C) COPYRIGHT International Business Machines Corp. 1995, 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 *   DISCLAIMER OF WARRANTIES.
 *   The following [enclosed] code is sample code created by IBM
 *   Corporation. This sample code is not part of any standard or IBM
 *   product and is provided to you solely for the purpose of assisting
 *   you in the development of your applications.  The code is provided
 *   "AS IS". IBM MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
 *   NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *   FOR A PARTICULAR PURPOSE, REGARDING THE FUNCTION OR PERFORMANCE OF
 *   THIS CODE.  IBM shall not be liable for any damages arising out of
 *   your use of the sample code, even if they have been advised of the
 *   possibility of such damages.
 *
 *   DISTRIBUTION.
 *   This sample code can be freely distributed, copied, altered, and
 *   incorporated into other software, provided that it bears the above
 *   Copyright notice and DISCLAIMER intact.
 */


#include <som.h>
#include "pos.h"
#include "store.h"
#include "central.h"


#ifdef __IBMC__
  #pragma linkage (SOMInitModule, system)
#endif

SOMEXTERN void SOMLINK SOMInitModule (long majorVersion,
				      long minorVersion, string className)
{
    SOM_IgnoreWarning (majorVersion);
    SOM_IgnoreWarning (minorVersion);
    SOM_IgnoreWarning (className);

    CentralOffice_DepotNewClass(0,0);
    AStore_StoreNewClass(0,0);
    AStore_TaxNewClass(0,0);
    AStore_StoreAccessNewClass(0,0);
    POS_POSTerminalNewClass(0,0);
    POS_OutputMediaNewClass(0,0);
    POS_InputMediaNewClass(0,0);
    PseudoNameServiceNewClass(0,0);
}

SOMEXTERN void SOMLINK SOMTermModule() 
{
	_somUnregisterClass (SOMClassMgrObject, _CentralOffice_Depot);
	_somUnregisterClass (SOMClassMgrObject, _AStore_Store);
	_somUnregisterClass (SOMClassMgrObject, _AStore_Tax);
	_somUnregisterClass (SOMClassMgrObject, _AStore_StoreAccess);
	_somUnregisterClass (SOMClassMgrObject, _POS_POSTerminal);
	_somUnregisterClass (SOMClassMgrObject, _POS_OutputMedia);
	_somUnregisterClass (SOMClassMgrObject, _POS_InputMedia);
}


#ifdef __IBMC__
SOMEXTERN void SOMLINK SOMInitModule (long majorVersion, long minorVersion, string className);
SOMEXTERN void SOMLINK SOMTermModule ();

int _CRT_init (void);
void _CRT_term (void);

unsigned long _System _DLL_InitTerm (unsigned long hModule, unsigned long flag)
{
    SOM_IgnoreWarning (hModule);
    switch (flag) {
        
	case 0:                  /* DLL Initialization */
	    if (_CRT_init () == -1)
		return 0UL;
            SOMInitModule (0, 0, (string)NULL);
	    break;
        
	case 1:                  /* DLL Termination */
	    SOMTermModule ();
	    _CRT_term ();
	    break;
        
	default:
	    return 0UL;
    }
    return 1UL;                  /* Success */
}
#endif /* __IBMC__ */
