/*
 * Method Routines
 * ---------------
 *
 * This module contains method routine templates for the following
 * Implementations:
 *
 *    DepotImpl
 *
 */

#include "central.imh"

/* OBB_PRESERVE_BEGIN(INCLUDES) */
#include "db.h"
#include "misc.h"
#include "pnamesvc.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *-----------------------------------------------------------------------------
 * global variables
 *-----------------------------------------------------------------------------
 */
CORBA_ImplementationDef   DepotImpl;   /*filled by RegisterDepotImpl routine, used by others*/


typedef  struct _item
{
    char              barcode[MAX_STR_LENGTH];
    AStore_ItemTypes  itemType;
    float             cost;
    char              description[MAX_STR_LENGTH];
    long              quantity;
} item_s, *item_p;

typedef struct tagDepotState
{
    DbDb  db;

} DepotState;


/*
 *****************************************************************************
 *
 * Function Name : depot_init
 *
 * Role          : perform depot internal initialisation.
 *
 ***************************************************************************** */
ObjectStatePtr depot_init(void)
{
    FILE               *fp;
    char               code[MAX_STR_LENGTH];
    char               desc[MAX_STR_LENGTH];
    char               itemType[MAX_STR_LENGTH];
    long               quantity;
    float              cost;
    item_p             anItem;
    DepotState         *ostate;

    /*
     * Create and initialize the original list
     */
    ostate     = malloc(sizeof(DepotState));
    ostate->db = db_init();

    /*
     * Now open and read the depot data file.
     * Each "record" is saved in the data store. The primary (only)
     * key is the barcode.
     */

    fp = fopen (DEPOT_FILE, "r");

    while (fscanf (fp, "%s %s %d %f %s",
                   code, desc, &quantity, &cost, itemType ) == 5)
        {
        anItem = malloc (sizeof(item_s));
        if (anItem)
            {
            strcpy(anItem->barcode, code);
            strcpy(anItem->description, desc);
            anItem->cost     = cost;
            anItem->quantity = quantity;

            if (!strcmp(itemType, "FOOD"))
                anItem->itemType = AStore_food;
            else if (!strcmp(itemType, "CLOTHES"))
                anItem->itemType = AStore_clothes;
            else if (!strcmp(itemType, "OTHER"))
                anItem->itemType = AStore_other;

            db_insert(anItem->barcode, anItem, NULL, ostate->db);
                   /* no free function - hence memory leak
                      for duplicate barcodes  */
          }
    }

    fclose (fp);

    return (ObjectStatePtr)ostate;

} /* end of depot_init() */


/*
 *****************************************************************************
 *
 * Function Name : Create_CentralOffice_Depot_Object
 *
 * Role          : constructor for depot object
 *
 *****************************************************************************
 */
#define Create_CentralOffice_Depot_Object Create_CentralOffice_Depot_Obje
CORBA_Object Create_CentralOffice_Depot_Object(CORBA_long argc,
                                               CORBA_char **argv,
                                               CORBA_Environment *ev)
{
    CORBA_Object           obj;
    CORBA_ReferenceData    id;
    ObjectStatePtr         objstate;
    PseudoNameService      pname;

    objstate = depot_init();      /* application initialisation */

    compose_refdata(&id, objstate);

    obj = CORBA_BOA_create(TheBoa,
                           ev,
                           &id,
                           CentralOffice_Depot__OBJ,
                           DepotImpl
                           );
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("Failed to create object",ev );

    pname = NameService(ev);
    PseudoNameService_BindName(pname, ev, DEPOT_REF, obj);
    if( ev->_major != CORBA_NO_EXCEPTION )
        application_terminate("unable to export offer",ev );

    CORBA_Object_release(pname, ev);

    return obj;

} /* end of Create_CentralOffice_Depot_Object() */

/* OBB_PRESERVE_END(INCLUDES) */

/*
 *
 *  ROUTINE NAME: 	DepotImpl__notify
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      This is the Event Notification routine for
 *	the DepotImpl implementation.
 */
CORBA_Status OBB_EXPORT DepotImpl__notify (CORBA_Object Object, 
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
 *  ROUTINE NAME: 	DepotImpl_FindItemInfo
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for FindItemInfo.
 *       (Implementation : DepotImpl)
 *
 */

 void DepotImpl_FindItemInfo (CORBA_Object object, CORBA_Environment * ev,
    AStore_AStoreId StoreId,
    POS_Barcode Item,
    CORBA_long Quantity,
    AStore_ItemInfo * IInfo)
{

/* OBB_PRESERVE_BEGIN(DepotImpl_FindItemInfo) */
    item_p           theItem;
    DepotState       *ostate;

    ostate = get_state_ptr(TheBoa, ev, object);

    if (theItem = db_lookup((char *)Item, ostate->db))
        {
        IInfo->Item     = theItem->barcode;
        IInfo->Itemtype = theItem->itemType;
        IInfo->Itemcost = theItem->cost;
        IInfo->Name     = theItem->description;
        IInfo->Quantity = theItem->quantity;

        printf("DepotImpl_FindItemInfo has returned the following ItemInfo record:\n");
        printf("barcode     = %s\n",IInfo->Item);
        printf("cost        = %.2f\n",IInfo->Itemcost);
        printf("description = %s\n",IInfo->Name);
        printf("quantity    = %d\n",IInfo->Quantity);
        printf("type        = %d\n",IInfo->Itemtype);

        theItem->quantity -= Quantity;
        }
    else
        {
        /* raise exception */
        CORBA_BOA_set_exception(TheBoa,
                                ev,
                                CORBA_USER_EXCEPTION,
                                ex_AStore_BarcodeNotFound,
                                (void *)&Item);

        printf("DepotImpl_FindItemInfo: Barcode %s not found\n",Item);
        }

/* OBB_PRESERVE_END(DepotImpl_FindItemInfo) */


    return;
}
