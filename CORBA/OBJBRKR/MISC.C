/*File: MISC.C -- convenience routines */

#include <orb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "pnamesvc.h"
#include "common.h"

CORBA_ORB TheOrb;
CORBA_BOA TheBoa;

/*Routines appear alphabetically*/
/*
 *****************************************************************************
 *  ROUTINE NAME: ActivateImpl
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Routine to activate an implementation.
 *****************************************************************************
 */
CORBA_boolean ActivateImpl (CORBA_ImplementationDef impl, CORBA_Environment *ev)
{
    CORBA_BOA_impl_is_ready (TheBoa, ev, impl);
    if (IsException (ev, (CORBA_string)"CORBA_BOA_impl_is_ready failed \n"))
        return (CORBA_FALSE);
    else
        return (CORBA_TRUE);
}

/*
 *****************************************************************************
 *
 * Function Name : application_terminate
 *
 * Role          : causes termination of executable in a tidy fashion
 *
 *****************************************************************************
 */

void application_terminate(char *message, CORBA_Environment *ev)
{
    printf(message);
    OBB_BOA_exit_main_loop(CORBA_DEC_BOA_OBJECT, ev, 0);
    OBB_ORB_rundown( TheOrb, ev, (CORBA_Flags)0);
    exit(1);
    /* no return */

} /* end of application_terminate() */

/*
 *****************************************************************************
 *
 * Function Name : compose_refdata
 *
 * Role          : encodes an object state pointer into a CORBA_ReferenceData
 *
 *****************************************************************************
 */

void compose_refdata(CORBA_ReferenceData *id,
                     ObjectStatePtr       ostate)
{
    id->_length   = sizeof(ObjectStatePtr);
    id->_maximum  = id->_length;
    id->_buffer   = malloc(id->_length);
    memcpy(id->_buffer, &ostate, sizeof(ostate));
}

/*
 *****************************************************************************
 *  ROUTINE NAME: DeactivateImpl
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Routine to deactivate an implementation.
 *****************************************************************************
 */
void DeactivateImpl (CORBA_ImplementationDef impl, CORBA_Environment *ev)
{
    CORBA_BOA_deactivate_impl (TheBoa, ev, impl);
    (void) IsException (ev,(CORBA_string)"CORBA_BOA_deactivate_impl failed \n");
}

/*
 *****************************************************************************
 *
 * Function Name : decompose_refdata
 *
 * Role          : extract an object state pointer from a CORBA_ReferenceDATA
 *
 *****************************************************************************
 */
ObjectStatePtr decompose_refdata(CORBA_ReferenceData *id)
{
    ObjectStatePtr  ostate;

    if (id->_length != sizeof(ObjectStatePtr))
        ostate = (ObjectStatePtr)NULL;
    else
        memcpy(&ostate, id->_buffer, sizeof(ostate));

    return ostate;

} /* end of decompose_refdata() */

/*
 *****************************************************************************
 *
 * Function Name : file_to_ref
 *
 * Role          : read an object reference in from a file
 *
 *****************************************************************************
 */
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

    fclose(fp);
    obj = CORBA_ORB_string_to_object(TheOrb, ev ,reference);
    free(reference);

    return obj;

} /* end of file_to_ref() */
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
ObjectStatePtr get_state_ptr(CORBA_BOA         boa,
                             CORBA_Environment *ev,
                             CORBA_Object      obj)
{
    CORBA_ReferenceData  id;
    ObjectStatePtr       ostate;

    id     = CORBA_BOA_get_id(boa, ev, obj);
    ostate = decompose_refdata(&id);

    return ostate;
}
/*
 *****************************************************************************
 *
 * Function Name : handle_error
 *
 * Parameters    : errortext: what to print if there is an error
 *                 ev:        the environment that might have an error
 *
 * Returns       : nothing
 *
 * Action        : if there is a system error, print and then, stop the world.
 *                 if it's a user error, print, and return
 *                 if no error, just return
 *
 *****************************************************************************
 */
void handle_error (CORBA_string     errortext,
                   CORBA_Environment * ev)
{
    switch(ev->_major)
        {
        case CORBA_NO_EXCEPTION:
            return;

        case CORBA_USER_EXCEPTION:
            printf(errortext);
            return;

        default: /*includes CORBA_SYSTEM_EXCEPTION*/
            application_terminate(errortext,ev);  /* doesn't return */
        }
}

/*
 *****************************************************************************
 *  ROUTINE NAME: IsException
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Centralized routine for handling exceptions.
 *          Prints exception if there is one (using string as "reason")
 *      and then returns a boolean true if it was an exception, false
 *      if it was not an exception.
 *****************************************************************************
 */
CORBA_boolean IsException (CORBA_Environment * ev,
                           CORBA_string errortext)

{
    /* Local Data Declaration */
    CORBA_boolean return_status;

    return_status = CORBA_FALSE;

    if (ev->_major != CORBA_NO_EXCEPTION)
        {
        /* An exception has occured.*/
        return_status = CORBA_TRUE;
        if (ev->_major == CORBA_SYSTEM_EXCEPTION)
            {
            printf ("\nSystem exception encountered: %s\n", (CORBA_char *) CORBA_exception_id (ev));
            printf ("  %s\n\n\n", (CORBA_char *) OBB_exception_errortext (ev, (CORBA_Flags) OBB_FORMAT_80));
            printf ("\n  ID=%s",errortext);
            }
        else
            {
            printf ("\nUser exception encountered: %s\n", (CORBA_char *) CORBA_exception_id (ev));
            printf ("\n  ID=%s",errortext);
            }
        CORBA_exception_free (ev);
        }

    return (return_status);
}

/*
 *****************************************************************************
 *
 * Function Name : NameService
 *
 * Role          : gets object reference of name service
 *
 *****************************************************************************
 */
PseudoNameService NameService(CORBA_Environment *ev)
{
    return ((PseudoNameService)file_to_ref(ev, PNAME_REF));
} /* end of NameService() */

/*
 *****************************************************************************
 *
 * Function Name : ref_to_file
 *
 * Role          : write an object reference to a file
 *
 *****************************************************************************
 */
void ref_to_file(CORBA_Object *obj, CORBA_Environment *ev, char *filename)
{
    CORBA_string  stringref;
    CORBA_long    len;
    FILE          *fp;

    stringref = CORBA_ORB_object_to_string(TheOrb, ev, obj);
    if (IsException( ev,
                     (CORBA_string)"Could not create object reference from impl_def\n"))
          exit (0);

    fp  = fopen(filename,"w");
    len = strlen(stringref);
    fwrite(&len, sizeof(len), 1, fp);
    fwrite(stringref, len, 1, fp);
    fclose (fp);

} /* end of ref_to_file() */
/*
 *****************************************************************************
 *  ROUTINE NAME: UnregisterImpl
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Routine to activate an implementation.
 *****************************************************************************
 */

/*Routine to unregister an implementation*/
void UnregisterImpl (CORBA_ImplementationDef impl, CORBA_Environment *ev)
{
    OBB_BOA_impl_unregister( TheBoa,
                             ev,
                             impl,
                             (CORBA_Flags) NULL);
    IsException (ev,(CORBA_string)"CORBA_BOA_impl_unregister failed \n");

    CORBA_Object_release((CORBA_Object)impl, ev);
    IsException (ev,(CORBA_string)"CORBA_Object_release on impl failed \n");
}
