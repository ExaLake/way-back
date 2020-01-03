/*
 *****************************************************************************
 * 
 * File Name   : pos_main.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : main routine for POS capsule
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

static POS_InputMedia  im_ref;
static POS_POSTerminal post_ref;
CORBA_ORB TheOrb;
CORBA_BOA TheBoa;

#define new_POS_InputMedia  Create_POS_InputMedia_Object
#define new_POS_POSTerminal Create_POS_POSTerminal_Object

extern CORBA_Object
Create_POS_InputMedia_Object(CORBA_long argc, 
							 CORBA_char **argv, 
							 CORBA_Environment *ev);

extern CORBA_Object
Create_POS_POSTerminal_Object(CORBA_long argc, 
							  CORBA_char **argv, 
							  CORBA_Environment *ev);


/*
 *-----------------------------------------------------------------------------
 * Forward References
 *-----------------------------------------------------------------------------
 */
static void
process_input(void *argument);

static CORBA_boolean
posmain_clean_up(CORBA_Environment *ev, 
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

  post_ref = new_POS_POSTerminal(argc, argv, &ev); 
  im_ref   = new_POS_InputMedia(argc, argv, &ev); 
                                          /* create our object(s) */
  
  DAIS_capsule_set_terminator(posmain_clean_up);
                                          /* Install our capsule terminator */

  DAIS_spawn(process_input, NULL, &ev);   /* set up a thread to run the user
											 input task */

  DAIS_schedule();                        /* Now wait for invocations */
  
} /* end of main() */


/*
 *****************************************************************************
 * 
 * Function Name : posmain_clean_up
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
#define FN "posmain_clean_up()"

CORBA_boolean
posmain_clean_up(CORBA_Environment *ev, 
				 DAIS_TermType type) 
{
  CORBA_Environment  local_ev;    /* local environment to avoid raising */
                                  /* exceptions that would prevent */
                                  /* termination */

  CORBA_BOA_deactivate_impl(TheBoa, 
                            &local_ev, 
                            DAIS_POS_InputMedia_impl);

  CORBA_BOA_dispose(TheBoa, 
                    &local_ev, 
                    (CORBA_Object) im_ref);
  
  CORBA_BOA_deactivate_impl(TheBoa, 
                            &local_ev, 
                            DAIS_POS_POSTerminal_impl);

  CORBA_BOA_dispose(TheBoa, 
                    &local_ev, 
                    (CORBA_Object) post_ref);
  
  return CORBA_TRUE;            /* Allow Termination  */
  
} /* end of posmain_clean_up() */


/*
 *****************************************************************************
 * 
 * Function Name : process_input
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : process keyboard input
 * 
 *****************************************************************************
 */
#undef FN
#define FN "process_input()"

void
process_input(void *argument)
{
  CORBA_Environment  ev;
  char               instring[STR_MAX+1];
  
  ev._major = CORBA_NO_EXCEPTION;



  for (;;)
  {
	printf(FN ": input: \n");

	fscanf(stdin, "%20s", instring);
	
    /* if first chararacter is a number, call barcode  else call keypad */

	if (instring[0] == 'x')
	{
	  application_terminate("program exit selected", &ev);
	}
	
    if (isdigit(instring[0])) 
	{
	  POS_InputMedia_BarcodeInput(im_ref,&ev,instring);

	  if (ev._major != CORBA_NO_EXCEPTION)
	  {
		printf(FN ": exception\n", CORBA_exception_id(&ev));
		CORBA_exception_free(&ev);
	  }
	}
    else 
	{
	  POS_InputMedia_KeypadInput(im_ref,&ev,instring);
	}
#if 0
	if (ev._major != CORBA_NO_EXCEPTION)
	{
	  application_terminate("could not access InputMedia", &ev);
	}
#endif
  }

} /* end of process_input() */
