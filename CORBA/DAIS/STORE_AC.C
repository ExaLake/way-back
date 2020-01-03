/*
 *****************************************************************************
 * 
 * File Name   : store_access.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : implementation of store access object
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
#include "Store.h"
#include "Central.h"
#include "PNS.h"
#include "misc.h"
#include "common.h"


typedef struct tagStoreAccessState
{
  CentralOffice_Depot  _depot_reference;
  AStore_Tax           _tax_reference;
  AStore_AStoreId      _store_id;
  CORBA_char           *tax_name;
  CORBA_float          markup;

} StoreAccessState;

/*
 *-----------------------------------------------------------------------------
 * Forward References
 *-----------------------------------------------------------------------------
 */
ObjectStatePtr
store_access_init(CORBA_long argc, 
                  CORBA_char **argv, 
                  CORBA_Environment *ev);


/*
 *****************************************************************************
 * 
 * Function Name : Create_AStore_StoreAccess_Object
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : constructor for store access object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "Create_AStore_StoreAccess_Object()"

CORBA_Object
Create_AStore_StoreAccess_Object(CORBA_long argc, 
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
                         DAIS_AStore_StoreAccess_intf,
                         DAIS_AStore_StoreAccess_impl
                         ); 
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create object",ev );
  }
  
#if 0
  pname = NameService(ev);
  PseudoNameService_BindName(pname, ev, STORE_ACCESS_REF, obj);
  CORBA_Object_release(pname, ev);
#endif
  
  CORBA_BOA_impl_is_ready(TheBoa, ev, DAIS_AStore_StoreAccess_impl);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to set impl ready",ev );
  }
  
  return obj;
  

} /* end of Create_AStore_StoreAccess_Object() */


/*
 *****************************************************************************
 * 
 * Function Name : store_access_init
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : application initialisation for store_access object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "store_access_init()"

ObjectStatePtr
store_access_init(CORBA_long         argc, 
                  CORBA_char         **argv, 
                  CORBA_Environment  *ev)
{
  PseudoNameService pname;
  StoreAccessState  *ostate;

  ostate = malloc(sizeof(StoreAccessState));

  if (argc != SA_ARGC)
  {
	application_terminate("wrong number of arguments\n", ev);
  }

  if(1 != sscanf(argv[SA_MARKUP_ARG], SA_MARKUP_FMTSTR, &ostate->markup))
  {
	application_terminate("bad markup arg\n", ev);
  }

  if(1 != sscanf(argv[SA_ID_ARG],     SA_ID_FMTSTR,     &ostate->_store_id))
  {
	application_terminate("bad id arg\n", ev);
  }

  ostate->tax_name         = malloc(sizeof(TAX_REF)+ID_LEN+1);
  sprintf(ostate->tax_name, "%s%d", TAX_REF, ostate->_store_id);

  pname                    = NameService(ev);
  ostate->_depot_reference = PseudoNameService_ResolveName(pname, ev, DEPOT_REF);
  ostate->_tax_reference   = PseudoNameService_ResolveName(pname, ev, ostate->tax_name);
  CORBA_Object_release(pname, ev);

  return ostate;

} /* end of store_access_init() */



/*
 *****************************************************************************
 * 
 * Function Name : S_AStore_StoreAccess_FindPrice
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of FindPrice operation
 *                 Note: the item_info out parameter is also passed to the 
 *                 FindItemInfo call. This means that the contents of the 
 *                 structure is allocated and deallocated by the orb 
 *                 obviating the need for explicit deallocation.
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_AStore_StoreAccess_FindPrice()"

void 
S_AStore_StoreAccess_FindPrice(AStore_StoreAccess _obj, 
							   CORBA_Environment  *ev, 
							   POS_Barcode        item,
							   CORBA_long         quantity,
							   CORBA_float        *ItemPrice,
							   CORBA_float        *item_tax_price,
							   AStore_ItemInfo    *item_info)
{
  StoreAccessState  *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);
  
  /*
   * get the item_info structure from the depot
   */
  
  CentralOffice_Depot_FindItemInfo(ostate->_depot_reference, 
								   ev, 
								   ostate->_store_id, 
								   item, 
								   quantity,
								   item_info);
  switch (ev->_major)
  {
  case CORBA_USER_EXCEPTION:
	printf(FN ": Barcode %s not found\n",item);
	CORBA_exception_free(ev);
	CORBA_BOA_set_exception(TheBoa,
							ev,
							CORBA_USER_EXCEPTION,
							ex_AStore_BarcodeNotFound,
							(void *)&item);
	return;
	break;
	
  case CORBA_SYSTEM_EXCEPTION:
	return;
	break;
  }
  
  /*
   * calculate the price based on cost + store specific markup percentage
   */
  
  *ItemPrice = item_info->Itemcost + (item_info->Itemcost * ostate->markup);
  
  /* 
   * call the tax server to obtain taxable amount of price
   */
  
  *item_tax_price =  AStore_Tax_FindTaxablePrice(ostate->_tax_reference, 
												 ev, 
												 *ItemPrice, 
												 item_info->Itemtype);
  
  printf(FN ": item_info->description = %s\n", item_info->Name);
  
  printf(FN ": price for item %s = %.2f taxable portion %.2f\n", 
         item, 
         *ItemPrice, 
         *item_tax_price);
  
  return;
  
} /* end of S_AStore_StoreAccess_FindPrice() */

