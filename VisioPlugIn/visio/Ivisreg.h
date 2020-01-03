/*	IVISREG.H - Helper functions for starting Visio
 *  Copyright (C) 1991-1996 Visio Corporation. All rights reserved.
 */

#ifndef _IVISREG_H
#define _IVISREG_H

#include "ivisauto.h"						// Definition of LPVISIOAPPLICATION...

/*
 *	Result codes for vaoGetVisio.
 */

#define VAO_ERROR			0
#define VAO_SUCCESS			1
#define VAO_GET				2
#define VAO_CREATE			3
#define VAO_BAD_VERSION		4
#define VAO_NOT_RUNNING		5
#define VAO_NOT_INSTALLED	6


/*
 *	Function Prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif

short vaoGetObject(
	LPVISIOAPPLICATION FAR *);				// Visio App Interface

short vaoGetVisio(							// VAO_ result code
	BOOL,									// TRUE => Get Active
	BOOL,									// TRUE => Create New
	LPVISIOAPPLICATION FAR *);				// Application Interface

HRESULT vaoGetLastError();

#ifdef __cplusplus
}
#endif

#endif /* _IVISREG_H */
