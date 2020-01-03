/*
 * Method Routines
 * ---------------
 *
 * This module contains method routine templates for the following
 * Implementations:
 *
 *    InputMediaImpl
 *
 */

#include "pos.imh"

/* OBB_PRESERVE_BEGIN(INCLUDES) */
#include <stdlib.h>
#include <ctype.h>
#include "pos.h"
#include "pnamesvc.h"
#include "misc.h"
#include "common.h"

typedef struct tagImState
{
  POS_POSTerminal  _posreference;
  POS_POSId        _id;
  CORBA_char       *pos_name;
} ImState;
/*
 *-----------------------------------------------------------------------------
 * global variables
 *-----------------------------------------------------------------------------
 */
CORBA_ImplementationDef   InputMediaImpl;   /*filled by main's RegisterAllImpls*/
/*
 *****************************************************************************
 *
 * Function Name : im_init
 *
 * Role          : application initialization for input media object
 *
 *****************************************************************************
 */
ObjectStatePtr im_init( CORBA_long         argc,
                        CORBA_char         **argv,
                        CORBA_Environment  *ev,
                        CORBA_char         **name)
{
    ImState            *ostate;
    PseudoNameService  pname;

    ostate = malloc(sizeof(ImState));

    if(1 != sscanf(argv[IM_ID_ARG], IM_ID_FMTSTR, &ostate->_id))
        application_terminate("bad pos id arg\n", ev);

    ostate->pos_name = malloc(sizeof(POSTERM_REF)+ID_LEN+1);
    sprintf(ostate->pos_name, "%s%d", POSTERM_REF, ostate->_id);

    pname = NameService(ev);
    ostate->_posreference = PseudoNameService_ResolveName(pname, ev, ostate->pos_name);
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("unable to import pos",ev );

    CORBA_Object_release(pname, ev);

    *name = "input_media";

    return ostate;

} /* end of im_init() */

/*
 *****************************************************************************
 *
 * Function Name : Create_POS_InputMedia_Object
 *
 * Role          : constructor for input media object
 *
 *****************************************************************************
 */
CORBA_Object Create_POS_InputMedia_Object(CORBA_long         argc,
                                          CORBA_char         **argv,
                                          CORBA_Environment  *ev)
{
    CORBA_Object           obj;
    CORBA_ReferenceData    id;
    CORBA_char             *name;
    ObjectStatePtr         objstate;

    objstate = im_init(argc, argv, ev, &name); /* application initialisation */
    compose_refdata(&id, objstate);

    obj = CORBA_BOA_create(TheBoa,
                           ev,
                           &id,
                           POS_InputMedia__OBJ,
                           InputMediaImpl
                           );
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("Failed to create object",ev );

    return obj;
} /* end of Create_POS_InputMedia_Object() */

/* OBB_PRESERVE_END(INCLUDES) */

/*
 *
 *  ROUTINE NAME: 	InputMediaImpl__notify
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      This is the Event Notification routine for
 *	the InputMediaImpl implementation.
 */
CORBA_Status OBB_EXPORT InputMediaImpl__notify (CORBA_Object Object, 
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
 *  ROUTINE NAME: 	InputMediaImpl_BarcodeInput
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for BarcodeInput.
 *       (Implementation : InputMediaImpl)
 *
 */

 void InputMediaImpl_BarcodeInput (CORBA_Object object, CORBA_Environment * ev,
    POS_Barcode Item)
{

/* OBB_PRESERVE_BEGIN(InputMediaImpl_BarcodeInput) */
    ImState  *ostate;
    ostate = get_state_ptr(TheBoa, ev, object);

    POS_POSTerminal_SendBarcode(ostate->_posreference, ev, Item);
    handle_error("Error sending barcode",ev);

/* OBB_PRESERVE_END(InputMediaImpl_BarcodeInput) */


    return;
}

/*
 *
 *  ROUTINE NAME: 	InputMediaImpl_KeypadInput
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for KeypadInput.
 *       (Implementation : InputMediaImpl)
 *
 */

 void InputMediaImpl_KeypadInput (CORBA_Object object, CORBA_Environment * ev,
    POS_InputMedia_OperatorCmd Cmd)
{

/* OBB_PRESERVE_BEGIN(InputMediaImpl_KeypadInput) */
    ImState  *ostate;
    ostate = get_state_ptr(TheBoa, ev, object);

    switch (toupper(Cmd[0]))
        {
        case 'L':
            POS_POSTerminal_Login(ostate->_posreference,ev);
            handle_error("Error on login",ev);
            break;
        case 'P':
            POS_POSTerminal_PrintPOSSalesSummary(ostate->_posreference, ev);
            handle_error("Error on POS sales summary",ev);
            break;
        case 'S':
            POS_POSTerminal_PrintStoreSalesSummary(ostate->_posreference, ev);
            handle_error("Error on store sales summary",ev);
            break;
        case 'T':
            POS_POSTerminal_EndOfSale(ostate->_posreference, ev);
            handle_error("Error at end of sale",ev);
            break;
        case 'Q':
            POS_POSTerminal_ItemQuantity(ostate->_posreference, ev, atol(++Cmd));
            handle_error("Error setting item quantity",ev);
            break;
        default: printf("input ignored\n"); /* ignore */
        }

/* OBB_PRESERVE_END(InputMediaImpl_KeypadInput) */


    return;
}
