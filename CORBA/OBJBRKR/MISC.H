#ifndef _MISC_H
#define _MISC_H

/*misc.h -- prototypes for misc.c routines.
  Some stolen from ObjectBroker's QuickStart,
  others needed for state stuff in Primer example*/

#include <orb.h>
#include "pnamesvc.h"
#include "common.h"

typedef void *ObjectStatePtr;

/*Routines are listed alphabetically*/

/*Activate an implementation already registered*/
CORBA_boolean ActivateImpl (CORBA_ImplementationDef impl,
                            CORBA_Environment       *ev);

/*Terminate application with message*/
void application_terminate(char              *message,
                           CORBA_Environment *ev);

/*Put some reference data in a state for storage*/
void compose_refdata(CORBA_ReferenceData *id,
                     ObjectStatePtr      ostate);

/*Routine to deactivate an implementation*/
void DeactivateImpl (CORBA_ImplementationDef impl,
                     CORBA_Environment       *ev);

/*Break down state for reference*/
ObjectStatePtr decompose_refdata(CORBA_ReferenceData *id);

/*read stringified object from file and turn into a ref*/
CORBA_Object file_to_ref(CORBA_Environment *ev, char *filename);

/* Get pointer to state of an object */
ObjectStatePtr get_state_ptr(CORBA_Object      boa,
                             CORBA_Environment *ev,
			     CORBA_Object      obj);

/*Routine to check for and handle exception.*/
void handle_error (CORBA_string      errortext,
                   CORBA_Environment * ev);

/*Routine to check for exception. True if exception, false otherwise*/
CORBA_boolean IsException (CORBA_Environment * ev,
                           CORBA_string       errortext);

/*Return pointer to pseudo name service*/
extern PseudoNameService NameService(CORBA_Environment *ev);

/* Object ref to file */
void ref_to_file(CORBA_Object      *obj,
                 CORBA_Environment *ev,
                 char              *filename);

/*Unregister an implementation*/
void UnregisterImpl (CORBA_ImplementationDef impl, CORBA_Environment *ev);

#endif
