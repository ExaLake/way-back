/*
 *****************************************************************************
 * 
 * File Name   : pnamesvc.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : implementation of pseudo name service
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
#include "db.h"
#include "PNS.h"
#include "misc.h"
#include "common.h"

typedef  struct _item 
{
  CORBA_Object  obj;

} item_s, *item_p;

typedef struct tagPNameState
{
  DbDb  db;

} PNameState;

/*
 *****************************************************************************
 * 
 * Function Name : free_item
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : free up storage allocated to an item placed in the data store
 * 
 *****************************************************************************
 */
#undef FN
#define FN "free_item()"

void
free_item(void *data)
{
  CORBA_Environment  ev;

  CORBA_exception_free(&ev);
  CORBA_Object_release(((item_p)data)->obj, &ev);

} /* end of free_item() */


/*
 *****************************************************************************
 * 
 * Function Name : S_PseudoNameService_BindName
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of BindName operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_PseudoNameService_BindName()"

void 
S_PseudoNameService_BindName(PseudoNameService  _obj, 
							 CORBA_Environment  *ev, 
							 CORBA_char         *ObjectName, 
							 CORBA_Object       ObjectRef
							 )
{
  PNameState  *ostate;
  item_p      anItem;

  ostate = get_state_ptr(TheBoa, ev, _obj);
  
  anItem      = malloc (sizeof(item_s));
  anItem->obj = CORBA_Object_duplicate(ObjectRef, ev);
  
  printf(FN ": BindNameing object %s\n", ObjectName);

  db_insert(ObjectName, anItem, free_item, ostate->db);

  
} /* end of S_PseudoNameService_BindName() */


/*
 *****************************************************************************
 * 
 * Function Name : S_PseudoNameService_ResolveName
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of ResolveName operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_PseudoNameService_ResolveName()"


CORBA_Object 
S_PseudoNameService_ResolveName(PseudoNameService  _obj, 
								CORBA_Environment  *ev, 
								CORBA_char         *ObjectName
								)
{
  item_p           theItem;
  PNameState       *ostate;
  CORBA_Object     theObject;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);

  if (theItem = db_lookup((char *)ObjectName, ostate->db))
  {
	theObject = theItem->obj;

	printf(FN ": found %s\n", ObjectName);
  }
  else 
  {
	/* raise exception */
      
	printf(FN ": %s not found\n", ObjectName);

	theObject = CORBA_OBJECT_NIL; /* not necessary when exception raised */
  }

  return theObject;
  
} /* end of S_PseudoNameService_ResolveName() */


/*
 *****************************************************************************
 * 
 * Function Name : pname_init
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : perform pseudo name server internal initialisation.
 * 
 ***************************************************************************** */
#undef FN
#define FN "pname_init()"

ObjectStatePtr
pname_init(void)
{
  FILE               *fp;
  item_p             anItem;
  CORBA_Environment  ev;
  CORBA_string       stringref;
  PNameState         *ostate;

  /*
   * Create and initialize the hash table 
   */
  ostate     = malloc(sizeof(PNameState));
  ostate->db = db_init();
  
  return (ObjectStatePtr)ostate;
  
} /* end of pname_init() */


/*
 *****************************************************************************
 * 
 * Function Name : Create_CentralOffice_Depot_Object
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : constructor for depot object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "Create_PseudoNameService_Object()"

CORBA_Object
Create_PseudoNameService_Object(CORBA_long argc, 
								CORBA_char **argv, 
								CORBA_Environment *ev)
{
  CORBA_Object           obj;
  CORBA_ReferenceData    id;
  FILE*                  fp;
  ObjectStatePtr         objstate;


  objstate = pname_init();      /* application initialisation */

  compose_refdata(&id, objstate);

  obj = CORBA_BOA_create(TheBoa, 
                         ev, 
                         &id,
                         DAIS_PseudoNameService_intf,
                         DAIS_PseudoNameService_impl
                         ); 
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create object",ev );
  }

  /* 
   * write object reference to a file
   * 
   */

  ref_to_file(obj, ev, PNAME_REF);
  
  CORBA_BOA_impl_is_ready(TheBoa, ev, DAIS_PseudoNameService_impl);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to set impl ready",ev );
  }

  return obj;

} /* end of Create_PseudoNameService_Object() */

