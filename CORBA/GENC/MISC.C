/*
 *****************************************************************************
 * 
 * File Name   : misc.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles, ICL
 * 
 * Role        : miscellaneous functions for generic C ORB
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
#include "misc.h"
#include "common.h"


/*
 *****************************************************************************
 * 
 * Function Name : get_state_ptr
 * 
 * Parameters    : pointer to the object reference for the object.
 * 
 * Returns       : pointer to object state or NULL if none
 * 
 * Role          : returns the state pointer for this object.
 *               
 *                 The implementation here assumes that the state pointer is
 *				   kept in the ReferenceData associated with the object in the
 *				   CORBA_BOA_create call. This may not be an optimal implementation
 *                 for all ORBs.
 * 
 *****************************************************************************
 */
#undef FN
#define FN "get_state_ptr()"

ObjectStatePtr 
get_state_ptr(CORBA_BOA boa,
			  CORBA_Environment *ev,
			  CORBA_Object obj)
{
  CORBA_ReferenceData  id;
  ObjectStatePtr       ostate;


  id     = CORBA_BOA_get_id(boa, ev, obj);
  ostate = decompose_refdata(&id);

  return ostate;
  
  
} /* end of get_state_ptr() */




/*
 *****************************************************************************
 * 
 * Function Name : compose_refdata
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : encodes an object state pointer into a CORBA_ReferenceData
 * 
 *****************************************************************************
 */
#undef FN
#define FN "compose_refdata()"

void
compose_refdata(CORBA_ReferenceData *id, ObjectStatePtr ostate)
{

  id->_length   = sizeof(ObjectStatePtr);
  id->_maximum  = id->_length;
  id->_buffer   = malloc(id->_length);
  memcpy(id->_buffer, &ostate, sizeof(ostate));

} /* end of compose_refdata() */


/*
 *****************************************************************************
 * 
 * Function Name : decompose_refdata
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : extract an object state pointer from a CORBA_ReferenceDATA
 * 
 *****************************************************************************
 */
#undef FN
#define FN "decompose_refdata()"

ObjectStatePtr
decompose_refdata(CORBA_ReferenceData *id)
{
  ObjectStatePtr  ostate;


  if (id->_length != sizeof(ObjectStatePtr))
  {
	ostate = (ObjectStatePtr)NULL;
  }
  else
  {
	memcpy(&ostate, id->_buffer, sizeof(ostate));
  }

  return ostate;

} /* end of decompose_refdata() */



/*
 *****************************************************************************
 * 
 * Function Name : ref_to_file
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : write an object reference to a file
 * 
 *****************************************************************************
 */
#undef FN
#define FN "ref_to_file()"

void
ref_to_file(CORBA_Object obj, CORBA_Environment *ev, char *filename)
{
  CORBA_string  stringref;
  CORBA_long    len;
  FILE          *fp;


  stringref = CORBA_ORB_object_to_string(TheOrb, ev, obj);
  
  fp  = fopen(filename,"w"); 
  len = strlen(stringref);
  fwrite(&len, sizeof(len), 1, fp);
  fwrite(stringref, len, 1, fp);
  fclose (fp);
  
  free(stringref);

} /* end of ref_to_file() */



/*
 *****************************************************************************
 * 
 * Function Name : file_to_ref
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : read an object reference in from a file
 * 
 *****************************************************************************
 */
#undef FN
#define FN "file_to_ref()"

CORBA_Object
file_to_ref(CORBA_Environment *ev, char *filename)
{
  FILE          *fp;
  CORBA_string  reference;
  CORBA_long    len;
  CORBA_Object  obj;


  fp = fopen(filename, "r");
  if (fp == NULL)
  {
	printf("cant open file %s\n", filename);
	application_terminate("cant open file\n", ev);
  }
	

  fread(&len, sizeof(len), 1, fp);
  reference = malloc(len+1);

  fread(reference, len, 1, fp);
  reference[len] = '\0';

  /* printf("outputref = %s\n",reference); */
  fclose(fp);
  obj = CORBA_ORB_string_to_object(TheOrb, ev ,reference);
  free(reference);

  return obj;

} /* end of file_to_ref() */


/*
 *****************************************************************************
 * 
 * Function Name : NameService
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : gets object reference of name service
 * 
 *****************************************************************************
 */
#undef FN
#define FN "NameService()"

PseudoNameService
NameService(CORBA_Environment *ev)
{

  return ((PseudoNameService)file_to_ref(ev, PNAME_REF));

} /* end of NameService() */


/*
 *****************************************************************************
 * 
 * Function Name : application_terminate
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : causes termination of executable in a tidy fashion
 * 
 *****************************************************************************
 */
#undef FN
#define FN "application_terminate()"

void
application_terminate(char *message, CORBA_Environment *ev)
{
  /* Insert termination and clean-up code here appropriate to your ORB
     environment. */
  
} /* end of application_terminate() */
