/*
 *****************************************************************************
 * 
 * File Name   : depot_main.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles, ICL
 * 
 * Role        : main routine for central office capsule for generic C ORB
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
#include "Central.h"
#include "common.h"

/*
 *-----------------------------------------------------------------------------
 * create mapping for direct local object instantiation
 *-----------------------------------------------------------------------------
 */

#define new_CentralOffice_Depot Create_CentralOffice_Depot_Object

extern CORBA_Object
Create_CentralOffice_Depot_Object(CORBA_long argc, 
                                  CORBA_char **argv, 
                                  CORBA_Environment *ev);

#define new_CentralOffice_Depot Create_CentralOffice_Depot_Object

#define new_PseudoNameService Create_PseudoNameService_Object

extern CORBA_Object
Create_PseudoNameService_Object(CORBA_long argc, 
								CORBA_char **argv, 
								CORBA_Environment *ev);

static CentralOffice_Depot  depot_ref;			 /* object reference to
													access depot object */ 
static PseudoNameService    pname_ref;			 /* object reference to
													access name server
													object */
CORBA_ORB TheOrb;
CORBA_BOA TheBoa;


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
  depot_ref = new_CentralOffice_Depot(argc, argv, &ev); 
                                          /* create our object(s) */
  
  /* Insert call here to start the ORB scheduler and process invocations */
  
} /* end of main() */

