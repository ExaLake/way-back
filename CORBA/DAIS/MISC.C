/*
 *****************************************************************************
 * 
 * File Name   : misc.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : miscellaneous functions
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

/*  printf(FN ": ostate = %lx\n", (long)ostate); */

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
/*  printf(FN ": ostate = %lx\n", (long)ostate); */

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

/*  printf(FN ": ostate = %lx\n", (long)ostate); */

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
  DAIS_terminate(message, ev);

  /* no return */

} /* end of application_terminate() */
