/*
 *****************************************************************************
 * 
 * File Name   : om.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles, ICL
 * 
 * Role        : implementation of output media object for generic C ORB
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
#include "POS.h"
#include "PNS.h"
#include "misc.h"
#include "common.h"

typedef struct tagOmState
{
  char *name;
  CORBA_long id;

} OmState;

/*
 *-----------------------------------------------------------------------------
 * Forward References
 *-----------------------------------------------------------------------------
 */
ObjectStatePtr
om_init(CORBA_long         argc, 
        CORBA_char         **argv, 
        CORBA_Environment  *ev,
		CORBA_char         **name);




/*
 *****************************************************************************
 * 
 * Function Name : S_POS_OutputMedia_OutputText
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of output text operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_OutputMedia_OutputText()"
     
CORBA_boolean 
S_POS_OutputMedia_OutputText(POS_OutputMedia    _obj, 
							 CORBA_Environment  *ev, 
							 CORBA_string       StringToPrint)
{
    return(printf("%s\n", StringToPrint));

} /* end of S_POS_OutputMedia_OutputText() */



/*
 *****************************************************************************
 * 
 * Function Name : Create_POS_OutputMedia_Object
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : constructor for output media object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "Create_POS_OutputMedia_Object()"

CORBA_Object
Create_POS_OutputMedia_Object(CORBA_long         argc, 
							  CORBA_char         **argv, 
							  CORBA_Environment  *ev)
{
  CORBA_Object           obj;
  CORBA_ReferenceData    id;
  ObjectStatePtr         objstate;
  CORBA_char             *name;
  PseudoNameService      pname;

  objstate = om_init(argc, argv, ev, &name); /* application initialisation */

  compose_refdata(&id, objstate);

  obj = CORBA_BOA_create(TheBoa, 
                         ev, 
                         &id,
                         POS_OutputMedia_intf, /* Replace with appropriate args. */
                         POS_OutputMedia_impl  /* for your ORB */
                         ); 
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create object", ev);
  }

  pname = NameService(ev);
  PseudoNameService_BindName(pname, ev, name, obj);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("unable to export offer", ev);
  }

  CORBA_Object_release(pname, ev);
  
  CORBA_BOA_impl_is_ready(TheBoa, ev, POS_OutputMedia_impl);
								/* Replace with appropriate args. for your ORB */
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to set impl ready", ev);
  }

  return obj;


} /* end of Create_POS_OutputMedia_Object() */


/*
 *****************************************************************************
 * 
 * Function Name : om_init
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : application initialisation for output media object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "om_init()"

ObjectStatePtr
om_init(CORBA_long         argc, 
        CORBA_char         **argv, 
        CORBA_Environment  *ev,
		CORBA_char         **name
		)
{
  OmState  *ostate;

  ostate = malloc(sizeof(OmState));

  if (argc != OM_ARGC)
  {
	application_terminate("wrong number of args\n", ev);
  }

  if (1 != sscanf(argv[OM_ID_ARG], OM_ID_FMTSTR, &ostate->id))
  {
	application_terminate("bad id arg\n", ev);
  }

  ostate->name = malloc(sizeof(OUTPUTMEDIA_REF)+ID_LEN+1);

  sprintf(ostate->name, "%s%ld", OUTPUTMEDIA_REF, ostate->id);

  printf(FN ": name=%s, id=%ld\n", ostate->name, ostate->id);

  *name = ostate->name;

  return ostate;

} /* end of om_init() */
















