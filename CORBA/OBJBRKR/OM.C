/*
 * Method Routines
 * ---------------
 *
 * This module contains method routine templates for the following
 * Implementations:
 *
 *    OutputMediaImpl
 *
 */

#include "pos.imh"

/* OBB_PRESERVE_BEGIN(INCLUDES) */
#include "misc.h"
#include "pnamesvc.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *-----------------------------------------------------------------------------
 * global variables
 *-----------------------------------------------------------------------------
 */
CORBA_ImplementationDef   OutputMediaImpl;   /*filled by RegisterOutputMediaImpl routine,
                                                used by others*/
/*
 *-----------------------------------------------------------------------------
 * local module definitions
 *-----------------------------------------------------------------------------
 */
typedef struct tagOmState
{
    char *name;
    CORBA_long id;
} OmState;
/*
 *****************************************************************************
 *
 * Function Name : om_init
 *
 * Role          : application initialisation for output media object
 *
 *****************************************************************************
 */
ObjectStatePtr om_init( CORBA_long         argc,
                        CORBA_char         **argv,
                        CORBA_Environment  *ev,
                        CORBA_char         **name)
{
    OmState  *ostate;
    ostate = malloc(sizeof(OmState));

    if (argc != OM_ARGC)
        application_terminate("wrong number of args\n", ev);

    if (1 != sscanf(argv[OM_ID_ARG], OM_ID_FMTSTR, &ostate->id))
        application_terminate("bad id arg\n", ev);

    ostate->name = malloc(sizeof(OUTPUTMEDIA_REF)+ID_LEN+1);

    sprintf(ostate->name, "%s%ld", OUTPUTMEDIA_REF, ostate->id);
    printf("om_init: name=%s, id=%ld\n", ostate->name, ostate->id);

    *name = ostate->name;
    return ostate;

} /* end of om_init() */
/*
 *****************************************************************************
 *
 * Function Name : Create_POS_OutputMedia_Object
 *
 * Role          : constructor for output media object
 *
 *****************************************************************************
 */
CORBA_Object Create_POS_OutputMedia_Object(CORBA_long         argc,
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
                           POS_OutputMedia__OBJ,
                           OutputMediaImpl
                           );
    if( ev->_major != CORBA_NO_EXCEPTION )
          application_terminate("Failed to create OutputMedia object", ev);

    pname = NameService(ev);
    PseudoNameService_BindName(pname, ev, name, obj);
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("unable to export offer", ev);

    CORBA_Object_release(pname, ev);

    return obj;
} /* end of Create_POS_OutputMedia_Object() */

/* OBB_PRESERVE_END(INCLUDES) */

/*
 *
 *  ROUTINE NAME: 	OutputMediaImpl__notify
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      This is the Event Notification routine for
 *	the OutputMediaImpl implementation.
 */
CORBA_Status OBB_EXPORT OutputMediaImpl__notify (CORBA_Object Object, 
			   CORBA_Environment * Ev,
			   CORBA_Context Context,
			   CORBA_short	Reason,
			   CORBA_short	Subreason,
			   void * Data)

{

    CORBA_Status	status;


    status = OBB_SUCCESS;


   /*
    ** BOA notification to activate or deactivate an implementation or an
    ** object.  The object parameter specifies the implementation or object
    ** that is to be activated or deactivated.
    */
    switch (Reason)
	{

	case OBB_NOTIFY_ACTIVATE_OBJ:
	    break;

	case OBB_NOTIFY_ACTIVATE_IMPL:
	    break;

	case OBB_NOTIFY_DEACTIVATE_OBJ:
	    break;

	case OBB_NOTIFY_DEACTIVATE_IMPL:
	    /*
	    **  We've gotten here because there was a request to
	    **  deactivate this implementation.  Such a request can be
	    **  made via the stop server management command.
	    */

            /* Discontinue dispatching ObjectBroker events. */
            OBB_BOA_exit_main_loop (CORBA_DEC_BOA_OBJECT,
			    Ev,
			    (CORBA_Flags)0 );
	    if (Ev->_major != CORBA_NO_EXCEPTION)
		{
		/*
		**  free any storage that might have been allocated by
		**  ObjectBroker to report the exception
		*/
		CORBA_exception_free(Ev);
		}

	    break;

	default:
	    break;
	}

    return (status);
}

/*
 *
 *  ROUTINE NAME: 	OutputMediaImpl_OutputText
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for OutputText.
 *       (Implementation : OutputMediaImpl)
 *
 */

 CORBA_boolean OutputMediaImpl_OutputText (CORBA_Object object, CORBA_Environment * ev,
    CORBA_string StringToPrint)
{

/* OBB_PRESERVE_BEGIN(OutputMediaImpl_OutputText) */

    return(printf("%s", StringToPrint));

/* OBB_PRESERVE_END(OutputMediaImpl_OutputText) */


}
