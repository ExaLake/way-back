/*
 *****************************************************************************
 * 
 * File Name   : om.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : implementation of output media object
 * 
 * DISCLAIMER: This code is intended to serve solely as a programming
 * example.  Although it emulates a point-of-sale system, it certainly is
 * not suitable for use in such a system as presented here, and it is far
 * from certain that even an extended version of this code would be
 * suitable.  Although this code compiled and ran without error on its
 * target ORB system(s) at the time it was developed, upgrades and
 * version changes may require changes.
 * 
 * COPYRIGHT 1995 by International Computers Limited
 * All rights reserved.  The copyright holders grant to the owner of the
 * book "CORBA Principles and Programming" the right to copy the code onto
 * computing hardware, manipulating and editing it as necessary, to work
 * the tutorial exercise and verify CORBA functionality for their personal
 * education.  
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
                         DAIS_POS_OutputMedia_intf,
                         DAIS_POS_OutputMedia_impl
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
  
  CORBA_BOA_impl_is_ready(TheBoa, ev, DAIS_POS_OutputMedia_impl);
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

  ostate->name = DAIS_malloc(sizeof(OUTPUTMEDIA_REF)+ID_LEN+1);

  sprintf(ostate->name, "%s%ld", OUTPUTMEDIA_REF, ostate->id);

  printf(FN ": name=%s, id=%ld\n", ostate->name, ostate->id);

  *name = ostate->name;

  return ostate;

} /* end of om_init() */
















