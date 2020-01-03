/*
 * Method Routines
 * ---------------
 *
 * This module contains method routine templates for the following
 * Implementations:
 *
 *    StoreAccessImpl
 *
 */

#include "astore.imh"

/* OBB_PRESERVE_BEGIN(INCLUDES) */
#include "central.h"
#include "pnamesvc.h"
#include "misc.h"
#include "common.h"
#include <stdlib.h>

/*
 *-----------------------------------------------------------------------------
 * global variables
 *-----------------------------------------------------------------------------
 */
CORBA_ImplementationDef   StoreAccessImpl;   /*filled by store_m.c's
                                               RegisterStoreAccessImpl routine*/
/*
 *-----------------------------------------------------------------------------
 * local module definitions
 *-----------------------------------------------------------------------------
 */

typedef struct tagStoreAccessState
{
    CentralOffice_Depot  _depot_reference;
    AStore_Tax           _tax_reference;
    AStore_AStoreId      _store_id;
    CORBA_char           *tax_name;
    CORBA_float          markup;
} StoreAccessState;

/*
 *****************************************************************************
 *
 * Function Name : store_access_init
 *
 * Role          : application initialisation for store_access object
 *
 *****************************************************************************
 */
ObjectStatePtr store_access_init(CORBA_long         argc,
                                 CORBA_char         **argv,
                                 CORBA_Environment  *ev)
{
    PseudoNameService pname;
    StoreAccessState  *ostate;

    ostate = malloc(sizeof(StoreAccessState));

    if (argc != SA_ARGC)
          application_terminate("wrong number of arguments\n", ev);

    if(1 != sscanf(argv[SA_MARKUP_ARG], SA_MARKUP_FMTSTR, &ostate->markup))
          application_terminate("bad markup arg\n", ev);

    if(1 != sscanf(argv[SA_ID_ARG],     SA_ID_FMTSTR,     &ostate->_store_id))
          application_terminate("bad id arg\n", ev);

    ostate->tax_name         = malloc(sizeof(TAX_REF)+ID_LEN+1);
    sprintf(ostate->tax_name, "%s%ld", TAX_REF, ostate->_store_id);

    pname                    = NameService(ev);
    ostate->_depot_reference = PseudoNameService_ResolveName(pname, ev, DEPOT_REF);
    if (ostate->_depot_reference == CORBA_OBJECT_NIL) application_terminate("Failed to import _depot",ev );

    ostate->_tax_reference   = PseudoNameService_ResolveName(pname, ev, ostate->tax_name);
    if (ostate->_tax_reference == CORBA_OBJECT_NIL) application_terminate("Failed to import tax",ev );
    CORBA_Object_release(pname, ev);

    return ostate;
} /* end of store_access_init() */
/*
 *****************************************************************************
 *
 * Function Name : Create_AStore_StoreAccess_Object
 *
 * Role          : constructor for store access object
 *
 *****************************************************************************
 */
/*the following #define is for those systems with linkers that need
  names less than 32 characters*/
#define Create_AStore_StoreAccess_Object Create_AStore_StoreAccess_Objec
CORBA_Object Create_AStore_StoreAccess_Object(CORBA_long argc,
                                              CORBA_char **argv,
                                              CORBA_Environment *ev)
{
    CORBA_Object           obj;
    CORBA_ReferenceData    id;
    PseudoNameService      pname;
    ObjectStatePtr         objstate;

    objstate = store_access_init(argc, argv, ev); /* application initialisation */

    compose_refdata(&id, objstate);

    obj = CORBA_BOA_create(TheBoa,
                           ev,
                           &id,
                           AStore_StoreAccess__OBJ,
                           StoreAccessImpl
                           );
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("Failed to create object",ev );

    pname = NameService(ev);
    PseudoNameService_BindName(pname, ev, STORE_ACCESS_REF, obj);
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("unable to export offer",ev );

    CORBA_Object_release(pname, ev);

    return obj;
} /* end of Create_AStore_StoreAccess_Object() */

/* OBB_PRESERVE_END(INCLUDES) */

/*
 *
 *  ROUTINE NAME: 	StoreAccessImpl__notify
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      This is the Event Notification routine for
 *	the StoreAccessImpl implementation.
 */
CORBA_Status OBB_EXPORT StoreAccessImpl__notify (CORBA_Object Object, 
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
 *  ROUTINE NAME: 	StoreAccessImpl_FindPrice
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for FindPrice.
 *       (Implementation : StoreAccessImpl)
 *
 */

 void StoreAccessImpl_FindPrice (CORBA_Object object, CORBA_Environment * ev,
    POS_Barcode Item,
    CORBA_long Quantity,
    CORBA_float * ItemPrice,
    CORBA_float * ItemTaxPrice,
    AStore_ItemInfo * IInfo)
{

/* OBB_PRESERVE_BEGIN(StoreAccessImpl_FindPrice) */
    StoreAccessState  *ostate;

    ostate = get_state_ptr(TheBoa, ev, object);

    /* get the ItemInfo structure from the depot */

    CentralOffice_Depot_FindItemInfo(ostate->_depot_reference,
                                     ev,
                                     ostate->_store_id,
                                     Item,
                                     Quantity,
                                     IInfo);
    switch (ev->_major)
        {
        case CORBA_USER_EXCEPTION:
            printf("StoreAccessImpl_FindPrice: Barcode %s not found\n",Item);
            return;
            break;

        case CORBA_SYSTEM_EXCEPTION:
          return;
          break;
        }

    /* calculate the price based on cost + store specific markup percentage */
    *ItemPrice = IInfo->Itemcost + (IInfo->Itemcost * ostate->markup);

    /* call the tax server to obtain taxable amount of price */
    *ItemTaxPrice =  AStore_Tax_FindTaxablePrice(ostate->_tax_reference,
                                                 ev,
                                                 *ItemPrice,
                                                 IInfo->Itemtype);

    printf("StoreAccessImpl_FindPrice: IInfo->description = %s\n", IInfo->Name);

    printf("StoreAccessImpl_FindPrice: price for item %s = %.2f taxable portion %.2f\n",
           Item,
           *ItemPrice,
           *ItemTaxPrice);

/* OBB_PRESERVE_END(StoreAccessImpl_FindPrice) */


    return;
}
