/*
 *****************************************************************************
 * 
 * File Name   : pname_main.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles, ICL
 * 
 * Role        : main routine for pseudo name server capsule for generic C ORB
 * 
 * This generic version was derived from the DAIS version which has skeletons
 * starting with 'S_'. These will need modification in order to work with other
 * ORBs. The only other proprietary identifiers are the _impl and _intf arguments
 * to CORBA_BOA_create and CORBA_BOA_impl_is_ready.
 *
 * Copyright (C) 1996 by the Object Management Group, Inc.  All  
 * rights reserved.  
 * 
 * Permission to use, copy, modify, and distribute this software for
 * any  teaching or instructional purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the names of
 * Object Management Group, Inc. (OMG) and John Wiley and Sons, Inc.
 * (Wiley) not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.
 * 
 * THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTY OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  Neither OMG, Wiley, nor their dealers or distributors
 * assume any liability of any alleged or actual damages arising
 * from the use of or the inability to use this software.  (Some
 * states do not allow the exclusion of implied warranties, so the
 * exclusion may not apply to you.)
 * 
 *****************************************************************************
 */
#define FN "<null>"



#include "orb.h"
#include "PNS.h"
#include "common.h"

static PseudoNameService pname_ref;
CORBA_ORB TheOrb;
CORBA_BOA TheBoa;

#define new_PseudoNameService Create_PseudoNameService_Object

extern CORBA_Object
Create_PseudoNameService_Object(CORBA_long argc, 
								CORBA_char **argv, 
								CORBA_Environment *ev);


/*
 *****************************************************************************
 * 
 * Function Name : main
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : main program entry point
 * 
 *****************************************************************************
 */
#undef FN
#define FN "main()"

int
main(int argc, char **argv)
{
  CORBA_Environment  ev;
  int                tmp_argc = argc; /* could be modified by _init()s */


  ev._major = CORBA_NO_EXCEPTION;

  TheOrb = CORBA_ORB_init(&tmp_argc, argv, argv[0], &ev); 
  EX_TERM("unable to access orb\n", &ev);
  TheBoa = CORBA_ORB_BOA_init(&tmp_argc, argv, argv[0], &ev); 
  EX_TERM("unable to access boa\n", &ev);

  pname_ref = new_PseudoNameService(argc, argv, &ev); 
                                          /* create our object(s) */
  
  /* Insert code here to call the ORB scheduler and wait for invocations */

} /* end of main() */

