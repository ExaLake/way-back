/*
 *****************************************************************************
 * 
 * File Name   : om_main.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : main routine for output media capsule
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
#include "common.h"

static POS_OutputMedia om_ref;
CORBA_ORB TheOrb;
CORBA_BOA TheBoa;

#define new_POS_OutputMedia Create_POS_OutputMedia_Object

extern CORBA_Object
Create_POS_OutputMedia_Object(CORBA_long argc, 
							  CORBA_char **argv, 
							  CORBA_Environment *ev);


/*
 *-----------------------------------------------------------------------------
 * Forward References
 *-----------------------------------------------------------------------------
 */
static CORBA_boolean
ommain_clean_up(CORBA_Environment *ev, 
				DAIS_TermType type);


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

  om_ref = new_POS_OutputMedia(argc, argv, &ev); 
                                          /* create our object(s) */
  
  DAIS_capsule_set_terminator(ommain_clean_up);
                                          /* Install our capsule terminator */

  DAIS_schedule();                        /* Now wait for invocations */
  
} /* end of main() */


/*
 *****************************************************************************
 * 
 * Function Name : ommain_clean_up
 * 
 * Parameters    : see below
 * 
 * Returns       : returns true if termination is allowed
 * 
 * Role          : The capsule termination function. This will be called 
 *                 just before the capsule terminates allowing tidying up
 *                 to be done.
 *                 In this case, the TerminationType is ignored because 
 *                 the same behaviour is required on all 3 types.
 * 
 *****************************************************************************
 */
#undef FN
#define FN "ommain_clean_up()"

CORBA_boolean
ommain_clean_up(CORBA_Environment *ev, 
				DAIS_TermType type) 
{
  CORBA_Environment  local_ev;    /* local environment to avoid raising */
                                  /* exceptions that would prevent */
                                  /* termination */

  CORBA_BOA_deactivate_impl(TheBoa, 
                            &local_ev, 
                            DAIS_POS_OutputMedia_impl);

  CORBA_BOA_dispose(TheBoa, 
                    &local_ev, 
                    (CORBA_Object) om_ref);
  
  return CORBA_TRUE;            /* Allow Termination  */
  
} /* end of ommain_clean_up() */


