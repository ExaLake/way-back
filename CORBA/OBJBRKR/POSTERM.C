/*
 * Method Routines
 * ---------------
 *
 * This module contains method routine templates for the following
 * Implementations:
 *
 *    POSTerminalImpl
 *
 */

#include "pos.imh"

/* OBB_PRESERVE_BEGIN(INCLUDES) */
#include "astore.h"
#include "pnamesvc.h"
#include "misc.h"
#include "common.h"
#include <stdlib.h>

typedef struct tagPOSTermState
{
    CORBA_float         _saleSubtotal;
    CORBA_long          _quantity;
    POS_POSId           _posid;
    AStore_AStoreId     _store_id;
    CORBA_float         _saleTaxableSubtotal;
    AStore_StoreAccess  _accessreference;
    AStore_Store        _storereference;
    POS_OutputMedia     _outputreference;
    AStore_Tax          _taxreference;
    CORBA_char          *store_name;
    CORBA_char          *om_name;
    CORBA_char          *tax_name;
    CORBA_char          *pos_name;
} POSTermState;

/*
 *-----------------------------------------------------------------------------
 * global variables
 *-----------------------------------------------------------------------------
 */

CORBA_ImplementationDef   POSTerminalImpl;      /*filled by RegisterAllImpls, used by others*/
/*
 *****************************************************************************
 *
 * Function Name : posterm_init
 *
 * Role          : application initialisation for the POSTerminal object
 *
 *****************************************************************************
 */

ObjectStatePtr posterm_init( CORBA_long         argc,
                             CORBA_char         **argv,
                             CORBA_Environment  *ev,
                             CORBA_char         **name)
{
    POSTermState       *ostate;
    PseudoNameService  pname;

    ostate = malloc(sizeof(POSTermState));

    if (argc != POS_ARGC)
        application_terminate("wrong number of args\n", ev);

    if(1 != sscanf(argv[POS_ID_ARG], POS_ID_FMTSTR, &ostate->_posid))
        application_terminate("bad pos id arg\n", ev);

    if(1 != sscanf(argv[POS_STORE_ARG], POS_STORE_FMTSTR, &ostate->_store_id))
        application_terminate("bad store id arg\n", ev);

    ostate->pos_name = malloc(sizeof(POSTERM_REF)+ID_LEN+1);
    sprintf(ostate->pos_name, "%s%ld", POSTERM_REF, ostate->_posid);
    *name = ostate->pos_name;

    ostate->store_name = malloc(sizeof(STORE_REF)+ID_LEN+1);
    sprintf(ostate->store_name, "%s%ld", STORE_REF, ostate->_store_id);

    ostate->om_name = malloc(sizeof(OUTPUTMEDIA_REF)+ID_LEN+1);
    sprintf(ostate->om_name, "%s%ld", OUTPUTMEDIA_REF, ostate->_posid);

    ostate->tax_name = malloc(sizeof(TAX_REF)+ID_LEN+1);
    sprintf(ostate->tax_name, "%s%ld", TAX_REF, ostate->_store_id);

    pname                    = NameService(ev);
    ostate->_storereference  = PseudoNameService_ResolveName(pname, ev, ostate->store_name);
    if (ostate->_storereference == CORBA_OBJECT_NIL)
        application_terminate("Failed to import store",ev );

    ostate->_taxreference    = PseudoNameService_ResolveName(pname, ev, ostate->tax_name);
    if (ostate->_taxreference == CORBA_OBJECT_NIL)
        application_terminate("Failed to import tax object",ev );

    ostate->_outputreference = PseudoNameService_ResolveName(pname, ev, ostate->om_name);
    if (ostate->_outputreference == CORBA_OBJECT_NIL)
        application_terminate("Failed to import output media",ev );

    CORBA_Object_release(pname, ev);

    ostate->_quantity        = 1;
    ostate->_accessreference = (AStore_StoreAccess)CORBA_OBJECT_NIL;

    return ostate;

} /* end of posterm_init() */
/*
 *****************************************************************************
 *
 * Function Name : Create_POS_POSTerminal_Object
 *
 * Role          : constructor for the POSTerminal object
 *
 *****************************************************************************
 */
CORBA_Object Create_POS_POSTerminal_Object(CORBA_long         argc,
                                           CORBA_char         **argv,
                                           CORBA_Environment  *ev)
{
    CORBA_Object         obj;
    CORBA_ReferenceData  id;
    CORBA_char           *name;
    ObjectStatePtr       objstate;
    PseudoNameService    pname;

    objstate = posterm_init(argc, argv, ev, &name);  /* application initialisation */

    compose_refdata(&id, objstate);

    obj = CORBA_BOA_create(TheBoa,
                           ev,
                           &id,
                           POS_POSTerminal__OBJ,
                           POSTerminalImpl);
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("Failed to create object",ev );

    pname = NameService(ev);
    PseudoNameService_BindName(pname, ev, name, obj);
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("unable to export offer", ev);

    CORBA_Object_release(pname, ev);

    return obj;

} /* end of Create_POS_POSTerminal_Object() */

/* OBB_PRESERVE_END(INCLUDES) */

/*
 *
 *  ROUTINE NAME: 	POSTerminalImpl__notify
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      This is the Event Notification routine for
 *	the POSTerminalImpl implementation.
 */
CORBA_Status OBB_EXPORT POSTerminalImpl__notify (CORBA_Object Object, 
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
 *  ROUTINE NAME: 	POSTerminalImpl_Login
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for Login.
 *       (Implementation : POSTerminalImpl)
 *
 */

 void POSTerminalImpl_Login (CORBA_Object object, CORBA_Environment * ev)
{

/* OBB_PRESERVE_BEGIN(POSTerminalImpl_Login) */
    POSTermState  *ostate;
    ostate = (POSTermState *)get_state_ptr(TheBoa, ev, object);


    /* check to see if we are in the middle of a sale */
    if (ostate->_saleSubtotal != 0 || ostate->_quantity != 1)
        {
        printf(": Login ignored\n");
        return;
        }
    else
        {
        /* get access object */

        ostate->_accessreference
            = AStore_Store_Login(ostate->_storereference,
                                 ev,
                                 ostate->_posid);
        handle_error("Error logging in to store",ev);

      printf("POS::Login - logged into Store\n");
    }

/* OBB_PRESERVE_END(POSTerminalImpl_Login) */


    return;
}

/*
 *
 *  ROUTINE NAME: 	POSTerminalImpl_PrintPOSSalesSummary
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for PrintPOSSalesSummary.
 *       (Implementation : POSTerminalImpl)
 *
 */

 void POSTerminalImpl_PrintPOSSalesSummary (CORBA_Object object, CORBA_Environment * ev)
{

/* OBB_PRESERVE_BEGIN(POSTerminalImpl_PrintPOSSalesSummary) */

    char           outstring[STR_MAX];
    AStore_POSList poslist;
    unsigned int   count = 0;
    int            found = 0;

    POSTermState   *ostate;
    ostate = get_state_ptr(TheBoa, ev, object);

    /* check to see if we are in the middle of a sale   */

    if ((ostate->_saleSubtotal != 0) || (ostate->_quantity != 1))
        {
        printf("POS Sales Summary ignored, sale in progress");
        return;
        }

    /* get poslist from store */
    AStore_Store_GetPOSTotals(ostate->_storereference,ev,&poslist);
    handle_error("Error getting POS totals\n", ev);

    /* find _posid in poslis   */
    while ((count < poslist._length) && (!found))
        {
        if (poslist._buffer[count].Id == ostate->_posid) found = 1;
        count++;
        }

    /*If not there, we have a problem, else print totals*/
    if (!found)
        printf("POS not found\n");
    else
        {
        sprintf(outstring,"Total POS sales = %.2f   Total POS taxes = %.2f\n",
              poslist._buffer[count-1].TotalSales,
              poslist._buffer[count-1].TotalTaxes);

        POS_OutputMedia_OutputText(ostate->_outputreference,ev,outstring);
        }

    CORBA_free(&poslist);

/* OBB_PRESERVE_END(POSTerminalImpl_PrintPOSSalesSummary) */


    return;
}

/*
 *
 *  ROUTINE NAME: 	POSTerminalImpl_PrintStoreSalesSummary
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for PrintStoreSalesSummary.
 *       (Implementation : POSTerminalImpl)
 *
 */

 void POSTerminalImpl_PrintStoreSalesSummary (CORBA_Object object, CORBA_Environment * ev)
{

/* OBB_PRESERVE_BEGIN(POSTerminalImpl_PrintStoreSalesSummary) */
    char                      outstring[STR_MAX];
    AStore_POSList            poslist;
    AStore_Store_StoreTotals  storetotals;
    unsigned int              count;
    POSTermState              *ostate;

    ostate = get_state_ptr(TheBoa, ev, object);

    /* check to see if we are in the middle of a sale*/
    if (ostate->_saleSubtotal != 0 || ostate->_quantity != 1)
        {
        printf("Store sales summary ignored, sale in progress\n");
        return;
        }
    printf("Store sales summary\n");

    storetotals = AStore_Store__get_Totals(ostate->_storereference, ev);
    handle_error("Error getting Totals\n",ev);
    sprintf(outstring, "Store total = %.2f   Store tax = %.2f\n",
            storetotals.StoreTotal,
            storetotals.StoreTaxTotal);

    POS_OutputMedia_OutputText(ostate->_outputreference,ev,outstring);
    handle_error("Error outputting text\n",ev);

    /* get the poslist from the Store object */
    AStore_Store_GetPOSTotals(ostate->_storereference,ev,&poslist);
    handle_error("Error getting POS totals",ev);

    /* run through the list, printing out the totals */

    for (count = 0; count < poslist._length; count++)
        {
        sprintf(outstring," POSID = %d   POSTotal =  %.2f  POSTaxTotal = %.2f\n",
            poslist._buffer[count].Id,
            poslist._buffer[count].TotalSales,
            poslist._buffer[count].TotalTaxes);

        POS_OutputMedia_OutputText(ostate->_outputreference,ev,outstring);
        handle_error("Error outputting text\n",ev);
        }

    /*free returned memory*/
    CORBA_free(&poslist);

/* OBB_PRESERVE_END(POSTerminalImpl_PrintStoreSalesSummary) */


    return;
}

/*
 *
 *  ROUTINE NAME: 	POSTerminalImpl_SendBarcode
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for SendBarcode.
 *       (Implementation : POSTerminalImpl)
 *
 */

 void POSTerminalImpl_SendBarcode (CORBA_Object object, CORBA_Environment * ev,
    POS_Barcode Item)
{

/* OBB_PRESERVE_BEGIN(POSTerminalImpl_SendBarcode) */
    char             outstring[STR_MAX];
    float            itemprice;
    float            itemtaxprice;
    AStore_ItemInfo  item_info;

    POSTermState     *ostate;
    ostate = get_state_ptr(TheBoa, ev, object);

    /* call FindPrice on the StoreAccess object */
    AStore_StoreAccess_FindPrice(ostate->_accessreference,
                                 ev,
                                 Item,
                                 ostate->_quantity,
                                 &itemprice,
                                 &itemtaxprice,
                                 &item_info);

    /* Check for and handle exception */
    if (ev->_major != CORBA_NO_EXCEPTION)
        {
        handle_error("Error on finding price\n",ev);
        CORBA_free(&item_info);
        ostate->_quantity = 1;
        return;
        }

    /* accumulate totals for the current sales */
    ostate->_saleSubtotal        += itemprice * ostate->_quantity;
    ostate->_saleTaxableSubtotal += itemtaxprice * ostate->_quantity;

    /* print out information with format depending upon whether item is taxable*/
    if (itemtaxprice)
        sprintf(outstring,"%s*  %s  %d   %.2f  %.2f\n ", item_info.Item,
              item_info.Name,
              ostate->_quantity,
              itemprice,
              itemprice * ostate->_quantity);
    else
        sprintf(outstring,"%s  %s  %d   %.2f  %.2f\n ", item_info.Item,
              item_info.Name,
              ostate->_quantity,
              itemprice,
              itemprice * ostate->_quantity);

    POS_OutputMedia_OutputText(ostate->_outputreference, ev, outstring);
    handle_error("Error outputting text",ev);

    /* free memory and reset quantity instance variable */
    CORBA_free(&item_info);
    ostate->_quantity = 1;

/* OBB_PRESERVE_END(POSTerminalImpl_SendBarcode) */


    return;
}

/*
 *
 *  ROUTINE NAME: 	POSTerminalImpl_ItemQuantity
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for ItemQuantity.
 *       (Implementation : POSTerminalImpl)
 *
 */

 void POSTerminalImpl_ItemQuantity (CORBA_Object object, CORBA_Environment * ev,
    CORBA_long Quantity)
{

/* OBB_PRESERVE_BEGIN(POSTerminalImpl_ItemQuantity) */
    POSTermState  *ostate;
    ostate = get_state_ptr(TheBoa, ev, object);

    ostate->_quantity = Quantity;

/* OBB_PRESERVE_END(POSTerminalImpl_ItemQuantity) */


    return;
}

/*
 *
 *  ROUTINE NAME: 	POSTerminalImpl_EndOfSale
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for EndOfSale.
 *       (Implementation : POSTerminalImpl)
 *
 */

 void POSTerminalImpl_EndOfSale (CORBA_Object object, CORBA_Environment * ev)
{

/* OBB_PRESERVE_BEGIN(POSTerminalImpl_EndOfSale) */
    CORBA_float tax;
    CORBA_char outstring[STR_MAX];

    POSTermState              *ostate;
    ostate = get_state_ptr(TheBoa, ev, object);

    /*Make sure we are in a sale -- total should not be zero */
    if (ostate->_saleSubtotal == 0)
        {
        printf("End of sale ignored, there is no sale in progress");
        return;
        }
    /*Likewise, quantity should be 1*/
    if (ostate->_quantity != 1)
        {
        printf("End of sale ignored, transaction in progress");
        return;
        }

    /* get tax */
    tax = AStore_Tax_CalculateTax(ostate->_taxreference,
                                  ev,
                                  ostate->_saleTaxableSubtotal);
    handle_error("Cannot calculate tax",ev);

    /* update store total */
    AStore_Store_UpdateStoreTotals(ostate->_storereference,
                                   ev,
                                   ostate->_posid,
                                   ostate->_saleSubtotal,
                                   tax);
    handle_error("Cannot update store totals",ev);

    /* format string and send to OutputMedia */
    sprintf(outstring," Subtotal  %7.2f\n"
                      " Tax       %7.2f\n"
                      " Total     %7.2f\n",
                      ostate->_saleSubtotal,
                      tax,
                      ostate->_saleSubtotal + tax);

    POS_OutputMedia_OutputText(ostate->_outputreference, ev, outstring);
    handle_error("Can't output text",ev);

    /* zero out subtotal accumulators and reset quantity */
    ostate->_saleSubtotal = 0.0f;
    ostate->_saleTaxableSubtotal = 0.0f;
    ostate->_quantity = 1;

/* OBB_PRESERVE_END(POSTerminalImpl_EndOfSale) */


    return;
}
