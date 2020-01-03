/*
 * Method Routines
 * ---------------
 *
 * This module contains method routine templates for the following
 * Implementations:
 *
 *    StoreImpl
 *
 */

#include "astore.imh"

/* OBB_PRESERVE_BEGIN(INCLUDES) */
#include "central.h"
#include "common.h"
#include "pnamesvc.h"
#include "misc.h"
#include "stdio.h"
#include "stdlib.h"

/*
 *-----------------------------------------------------------------------------
 * global variables
 *-----------------------------------------------------------------------------
 */
CORBA_ImplementationDef StoreImpl; /*set by store_m.c's RegisterStoreImpl routine*/

#define Create_AStore_StoreAccess_Object Create_AStore_StoreAccess_Objec
extern CORBA_Object Create_AStore_StoreAccess_Object(CORBA_long argc,
                                                     CORBA_char **argv,
                                                     CORBA_Environment *ev);

/*
 *-----------------------------------------------------------------------------
 * local module definitions
 *-----------------------------------------------------------------------------
 */

typedef struct tagStoreState
{
  AStore_POSList            _poslist;
  AStore_POSInfo            _posarray[MAX_POSLIST_ENTRIES];
  AStore_Store_StoreTotals  _totals;
  CentralOffice_Depot       _depotReference;
  AStore_Tax                _taxReference;

  CORBA_float               _storeMarkup;
  AStore_AStoreId           _store_id;

  CORBA_char                *store_name;
  CORBA_char                *tax_name;

} StoreState;
/*
 *****************************************************************************
 *
 * Function Name : store_init
 *
 * Role          : application initialisation for store object
 *
 *****************************************************************************
 */
ObjectStatePtr store_init(CORBA_long         argc,
                          CORBA_char         **argv,
                          CORBA_Environment  *ev,
                          CORBA_char         **name)
{
  StoreState        *ostate;
  PseudoNameService pname;

  /* Create local state storage */
  ostate = malloc(sizeof(StoreState));

  /* Associate the instance data poslist array with poslist sequence
   * and initialize sequence
   */

  ostate->_poslist._buffer  = ostate->_posarray;
  ostate->_poslist._maximum = MAX_POSLIST_ENTRIES;
  ostate->_poslist._length  = 0;

  if (argc != S_ARGC)
        application_terminate("wrong number of args\n", ev);

  if(1 != sscanf(argv[S_ID_ARG], S_ID_FMTSTR, &ostate->_store_id))
        application_terminate("bad store id arg\n", ev);

  ostate->store_name        = malloc(sizeof(STORE_REF)+ID_LEN+1);
  sprintf(ostate->store_name, "%s%ld", STORE_REF, ostate->_store_id);

  ostate->tax_name          = malloc(sizeof(TAX_REF)+ID_LEN+1);
  sprintf(ostate->tax_name, "%s%ld", TAX_REF, ostate->_store_id);

  *name                     = ostate->store_name;
  pname                     = NameService(ev);

  ostate->_depotReference   = PseudoNameService_ResolveName(pname, ev, DEPOT_REF);
  if (ostate->_depotReference == CORBA_OBJECT_NIL) application_terminate("Failed to import depot",ev );

  ostate->_taxReference   = PseudoNameService_ResolveName(pname, ev, ostate->tax_name);
  if (ostate->_taxReference == CORBA_OBJECT_NIL) application_terminate("Failed to import tax",ev );

  CORBA_Object_release(pname, ev);

  /* initialize StoreTotal = StoreTaxTotal = 0 */
  ostate->_totals.StoreTotal    = 0.0f;
  ostate->_totals.StoreTaxTotal = 0.0f;

  if(1 != sscanf(argv[S_MARKUP_ARG], S_MARKUP_FMTSTR, &ostate->_storeMarkup))
        application_terminate("bad markup arg\n", ev);

  printf("Store server is initialized and ready\n");
  return (ObjectStatePtr)ostate;

} /* end of store_init() */
/*
 *****************************************************************************
 *
 * Function Name : Create_AStore_Store_Object
 *
 * Role          : constructor for store object
 *
 *****************************************************************************
 */
CORBA_Object Create_AStore_Store_Object(CORBA_long argc,
                                        CORBA_char **argv,
                                        CORBA_Environment *ev)
{
  CORBA_Object           obj;
  CORBA_ReferenceData    id;
  CORBA_char             *name;
  PseudoNameService      pname;
  ObjectStatePtr         ostate;

  ostate = store_init(argc, argv, ev, &name); /* application initialisation */
  compose_refdata(&id, ostate);

  obj = CORBA_BOA_create(TheBoa,
                         ev,
                         &id,
                         AStore_Store__OBJ,
                         StoreImpl
                         );
  if( ev->_major != CORBA_NO_EXCEPTION )
      application_terminate("Failed to create object",ev );

  pname = NameService(ev);
  PseudoNameService_BindName(pname, ev, name, obj);
  if( ev->_major != CORBA_NO_EXCEPTION )
      application_terminate("Failed to export store",ev );

  CORBA_Object_release(pname, ev);
  return obj;

} /* end of Create_AStore_Store_Object() */
/* OBB_PRESERVE_END(INCLUDES) */

/*
 *
 *  ROUTINE NAME: 	StoreImpl__notify
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      This is the Event Notification routine for
 *	the StoreImpl implementation.
 */
CORBA_Status OBB_EXPORT StoreImpl__notify (CORBA_Object Object, 
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
 *  ROUTINE NAME: 	StoreImpl_Login
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for Login.
 *       (Implementation : StoreImpl)
 *
 */

 AStore_StoreAccess StoreImpl_Login (CORBA_Object object, CORBA_Environment * ev,
    POS_POSId Id)
{

/* OBB_PRESERVE_BEGIN(StoreImpl_Login) */

  AStore_StoreAccess  store_access;
  unsigned int        count = 0;
  int                 found = 0;
  CORBA_char**        argv;
  StoreState          *ostate;

  ostate = get_state_ptr(TheBoa, ev, object);

  /* check POSList to see if store_Id exists if it doesn't, add it to
   * poslist, create a StoreAcess object and return
   *
   * if store_Id is already in the list, zero out totals and return
   * existing StoreAccess object
   *
   * As currently implemented, the POSList has room for 50 POS entries If
   * the table is full, additional POSs trying to log in will receive a
   * NULL StoreAccess object */

  if (ostate->_poslist._length == MAX_POSLIST_ENTRIES)
      {
      printf("StoreAccess _poslist overflow\n");
      return NULL;
      }
  else
      {
      while ((count < ostate->_poslist._length) && (!found))
          {
          if (ostate->_poslist._buffer[count].Id == Id)
                found = 1;
          count++;
          }
      }

  if (!found)
      { /* if the POSid is not already in the POSlist add it,
           creating StoreAccess object in the process */
      AStore_POSInfo   *new_pos;  /* temporary pointer*/

      argv                = malloc(sizeof(CORBA_char *) * SA_ARGC);
      argv[SA_MARKUP_ARG] = malloc(ARG_STR_LEN + 1);
      argv[SA_ID_ARG    ] = malloc(ARG_STR_LEN + 1);

      sprintf(argv[SA_MARKUP_ARG], SA_MARKUP_FMTSTR, ostate->_storeMarkup);
      sprintf(argv[SA_ID_ARG],     SA_ID_FMTSTR,     ostate->_store_id);

      store_access = Create_AStore_StoreAccess_Object((CORBA_long)SA_ARGC,
                                                      argv,
                                                      ev);
      free(argv[SA_MARKUP_ARG]);
      free(argv[SA_ID_ARG]);
      free(argv);

      /* initialize the postlist entry */

      new_pos = &(ostate->_poslist._buffer[ostate->_poslist._length]);

      new_pos->StoreAccessReference = store_access;
      new_pos->Id                    = Id;
      new_pos->TotalSales            = 0.0f;
      new_pos->TotalTaxes            = 0.0f;

      /* increment the length field of the POSList sequence */
      ostate->_poslist._length++;
      printf("StoreImpl_Login: added POSid %d to the POSList sequence\n", new_pos->Id);
      return store_access;
      }
  else
      {
      /* reset POS totals */
      ostate->_poslist._buffer[count-1].TotalSales = 0.0f;
      ostate->_poslist._buffer[count-1].TotalTaxes = 0.0f;

      printf("StoreImpl_Login returning existing StoreAccess object for POSid: %d\n",
                   ostate->_poslist._buffer[count-1].Id);

      return ostate->_poslist._buffer[count-1].StoreAccessReference;
      }
/* OBB_PRESERVE_END(StoreImpl_Login) */


}

/*
 *
 *  ROUTINE NAME: 	StoreImpl_GetPOSTotals
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for GetPOSTotals.
 *       (Implementation : StoreImpl)
 *
 */

 void StoreImpl_GetPOSTotals (CORBA_Object object, CORBA_Environment * ev,
    AStore_POSList * POSData)
{

/* OBB_PRESERVE_BEGIN(StoreImpl_GetPOSTotals) */
    StoreState  *ostate;
    ostate = get_state_ptr(TheBoa, ev, object);

    *POSData = ostate->_poslist;
    return;
/* OBB_PRESERVE_END(StoreImpl_GetPOSTotals) */


    return;
}

/*
 *
 *  ROUTINE NAME: 	StoreImpl_UpdateStoreTotals
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for UpdateStoreTotals.
 *       (Implementation : StoreImpl)
 *
 */

 void StoreImpl_UpdateStoreTotals (CORBA_Object object, CORBA_Environment * ev,
    POS_POSId Id,
    CORBA_float Price,
    CORBA_float Taxes)
{

/* OBB_PRESERVE_BEGIN(StoreImpl_UpdateStoreTotals) */
  unsigned int count = 0;
  int          found = 0;
  StoreState   *ostate;

  ostate = get_state_ptr(TheBoa, ev, object);

  ostate->_totals.StoreTotal    += Price;
  ostate->_totals.StoreTaxTotal += Taxes;

  while ((count < ostate->_poslist._length) && (!found))
      {
      if (ostate->_poslist._buffer[count].Id == Id) found = 1;
      count++;
      }

  if (!found)
      {
      printf("UpdateStoreTotals: there is a serious problem!\n");
      return;
      }

  ostate->_poslist._buffer[count-1].TotalSales += Price;
  ostate->_poslist._buffer[count-1].TotalTaxes += Taxes;
  return;
/* OBB_PRESERVE_END(StoreImpl_UpdateStoreTotals) */


    return;
}

/*
 *
 *  ROUTINE NAME: 	StoreImpl_get_StoreId
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for get_StoreId.
 *       (Implementation : StoreImpl)
 *
 */

 AStore_AStoreId StoreImpl_get_StoreId (CORBA_Object object, CORBA_Environment * ev)
{

/* OBB_PRESERVE_BEGIN(StoreImpl_get_StoreId) */
  StoreState          *ostate;
  ostate = get_state_ptr(TheBoa, ev, object);

  return ostate->_store_id;
/* OBB_PRESERVE_END(StoreImpl_get_StoreId) */


}

/*
 *
 *  ROUTINE NAME: 	StoreImpl_get_Totals
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method routine for get_Totals.
 *       (Implementation : StoreImpl)
 *
 */

 AStore_Store_StoreTotals StoreImpl_get_Totals (CORBA_Object object, CORBA_Environment * ev)
{

/* OBB_PRESERVE_BEGIN(StoreImpl_get_Totals) */
  StoreState          *ostate;
  ostate = get_state_ptr(TheBoa, ev, object);

  return ostate->_totals;
/* OBB_PRESERVE_END(StoreImpl_get_Totals) */


}
