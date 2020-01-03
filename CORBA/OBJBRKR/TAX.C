/*
 * Method Routines
 * ---------------
 *
 * This module contains method routine templates for the following
 * Implementations:
 *
 *    TaxImpl
 *
 */

#include "astore.imh"

/* OBB_PRESERVE_BEGIN(INCLUDES) */
#include "pnamesvc.h"
#include "misc.h"
#include "common.h"
#include <stdlib.h>

/*
 *-----------------------------------------------------------------------------
 * global variables
 *-----------------------------------------------------------------------------
 */
CORBA_ImplementationDef   TaxImpl;   /*filled by store_m.c's
                                       RegisterTaxImpl routine*/
/*
 *-----------------------------------------------------------------------------
 * local module definitions
 *-----------------------------------------------------------------------------
 */
#define BASE_TAX_RATE 0.05f      /* initialisation value for tax rate */

typedef struct tagTaxState
{
    AStore_AStoreId  _store_id;
    CORBA_float      rate;
    CORBA_char       *name;
} TaxState;
/*
 *****************************************************************************
 *
 * Function Name : tax_init
 *
 * Role          : application initialisation for tax object
 *
 *****************************************************************************
 */
ObjectStatePtr tax_init( CORBA_long         argc,
                         CORBA_char         **argv,
                         CORBA_Environment  *ev,
                         CORBA_char         **name)
{
    TaxState  *ostate;
    ostate = malloc(sizeof(TaxState));

    if(1 != sscanf(argv[TAX_ID_ARG], TAX_ID_FMTSTR, &ostate->_store_id))
          application_terminate("bad store id arg\n", ev);

    ostate->name = malloc(sizeof(TAX_REF)+ID_LEN+1);
    sprintf(ostate->name, "%s%ld", TAX_REF, ostate->_store_id);
    *name = ostate->name;

    ostate->rate = BASE_TAX_RATE;

    return (ObjectStatePtr)ostate;
} /* end of tax_init() */
/*
 *****************************************************************************
 *
 * Function Name : Create_AStore_Tax_Object
 *
 * Role          : object constructor for tax object
 *
 *****************************************************************************
 */
CORBA_Object Create_AStore_Tax_Object(  CORBA_long        argc,
                                        CORBA_char        **argv,
                                        CORBA_Environment *ev)
{
    CORBA_Object           obj;
    CORBA_ReferenceData    id;
    CORBA_char             *name;
    PseudoNameService      pname;
    ObjectStatePtr         objstate;

    objstate = tax_init(argc, argv, ev, &name); /* application initialisation */

    compose_refdata(&id, objstate);

    obj = CORBA_BOA_create(TheBoa,
                           ev,
                           &id,
                           AStore_Tax__OBJ,
                           TaxImpl
                           );
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("Tax: Failed to create object",ev );

    pname = NameService(ev);
    PseudoNameService_BindName(pname, ev, name, obj);
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("Failed to export offer",ev);

    CORBA_Object_release(pname, ev);
    return obj;
} /* end of Create_AStore_Tax_Object() */

/* OBB_PRESERVE_END(INCLUDES) */

/*
 *
 *  ROUTINE NAME: 	TaxImpl__notify
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      This is the Event Notification routine for
 *	the TaxImpl implementation.
 */
CORBA_Status OBB_EXPORT TaxImpl__notify (CORBA_Object Object, 
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
 *  ROUTINE NAME: 	TaxImpl_CalculateTax
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for CalculateTax.
 *       (Implementation : TaxImpl)
 *
 */

 CORBA_float TaxImpl_CalculateTax (CORBA_Object object, CORBA_Environment * ev,
    CORBA_float TaxableAmount)
{

/* OBB_PRESERVE_BEGIN(TaxImpl_CalculateTax) */

    TaxState *ostate;
    ostate = get_state_ptr(TheBoa, ev, object);
    return (TaxableAmount * ostate->rate);

/* OBB_PRESERVE_END(TaxImpl_CalculateTax) */


}

/*
 *
 *  ROUTINE NAME: 	TaxImpl_FindTaxablePrice
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for FindTaxablePrice.
 *       (Implementation : TaxImpl)
 *
 */

 CORBA_float TaxImpl_FindTaxablePrice (CORBA_Object object, CORBA_Environment * ev,
    CORBA_float ItemPrice,
    AStore_ItemTypes ItemType)
{

/* OBB_PRESERVE_BEGIN(TaxImpl_FindTaxablePrice) */
    if (ItemType == AStore_other)
        {
        printf("Tax_FindTaxablePrice = %.2f\n",ItemPrice);
        return ItemPrice;
        }
    else
        {
        printf("Tax_FindTaxablePrice = %.2f\n",0.0);
        return 0.0f;
        }

/* OBB_PRESERVE_END(TaxImpl_FindTaxablePrice) */


}
