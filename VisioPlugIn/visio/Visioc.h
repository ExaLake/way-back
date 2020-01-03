/* VISIOC.H - Visio Automation Dual Interface Declarations
 * Copyright (C) 1996 Visio Corporation. All rights reserved.
 */

#ifndef _VISIOC_H
#define _VISIOC_H


/* Folks using this new file will have no need for using OLD interfaces... */
#define NO_VISIO_41_COMPATIBILITY_LAYER

/* Standard headers required before including other OLE interface definitions */
#include <windows.h>
#include <ole2.h>
#if !defined (_WIN32)
	#include <dispatch.h>
#endif

/* This forward declares the interfaces found in "visio.h" for the "C" compiler */
#ifndef __cplusplus
#include "vfwddecl.h"
#endif

/*	Machine generated dual interface file for Visio's object model */
#include "visio.h"

/*	vaoGetObject prototype and VAO_ return codes */
#include "ivisreg.h"


#endif /* _VISIOC_H */
