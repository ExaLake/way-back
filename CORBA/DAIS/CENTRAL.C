/*
 *****************************************************************************
 * 
 * File Name   : central.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : Implementation of central office
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
#include "db.h"
#include "PNS.h"
#include "misc.h"
#include "Central.h"
#include "common.h"

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
 * Function Name : S_CentralOffice_Depot_FindItemInfo
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : server implementation for FindItemInfo operation
 *                 try to locate the item in the hash table. if it exists,
 *                 set item_info if it does not exist, throw an exception
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_CentralOffice_Depot_FindItemInfo()"

void 
S_CentralOffice_Depot_FindItemInfo(CentralOffice_Depot  _obj, 
								   CORBA_Environment    *ev, 
								   AStore_AStoreId      store_id, 
								   POS_Barcode          Item, 
								   CORBA_long           Quantity, 
								   AStore_ItemInfo      *IInfo)
{
  item_p           theItem;
  AStore_ItemInfo  theItemInfo; 
  DepotState       *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);

  if (theItem = db_lookup((char *)Item, ostate->db)) 
  {
	IInfo->Item     = theItem->barcode;
	IInfo->Itemtype = theItem->itemType;
	IInfo->Itemcost = theItem->cost;
	IInfo->Name     = theItem->description;
	IInfo->Quantity = theItem->quantity;

	printf(FN " has returned the following ItemInfo record:\n");
	printf("barcode     = %s\n",IInfo->Item);
	printf("cost        = %.2f\n",IInfo->Itemcost);
	printf("description = %s\n",IInfo->Name);
	printf("quantity    = %d\n",IInfo->Quantity);
	printf("type        = %d\n",IInfo->Itemtype);
      
	theItem->quantity -= Quantity;
      
	return;
  }
  else 
  {
	/* raise exception */
	CORBA_BOA_set_exception(TheBoa,
							ev,
							CORBA_USER_EXCEPTION,
							ex_AStore_BarcodeNotFound,
							(void *)&Item);
      
	printf(FN ": Barcode %s not found\n",Item);
      
	return;
  }
  
} /* end of S_CentralOffice_Depot_FindItemInfo() */


/*
 *****************************************************************************
 * 
 * Function Name : depot_init
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : perform depot internal initialisation.
 * 
 ***************************************************************************** */
#undef FN
#define FN "depot_init()"

ObjectStatePtr
depot_init(void)
{
  FILE               *fp;
  char               code[MAX_STR_LENGTH];
  char               desc[MAX_STR_LENGTH];
  char               itemType[MAX_STR_LENGTH];
  long               quantity;
  float              cost;
  item_p             anItem;
  CORBA_Environment  ev;
  CORBA_string       stringref;
  DepotState         *ostate;

  /*
   * Create and initialize the hash table 
   */
  ostate     = malloc(sizeof(DepotState));
  ostate->db = db_init();

  /*
   * Now open and read the depot data file. 
   * Each "record" is saved in the data store. The primary (only)
   * key is the barcode. 
   */

  fp = fopen (DEPOT_FILE, "r");
  
  while (fscanf (fp, "%s%s%f%s%d", 
                 code, itemType, &cost, desc, &quantity) == 5) 
  {
	anItem = malloc (sizeof(item_s));
	if (anItem)
	{
	  strcpy(anItem->barcode, code);
	  strcpy(anItem->description, desc);
	  anItem->cost     = cost;
	  anItem->quantity = quantity;

	  if (!strcmp(itemType, "food"))
	  {
		anItem->itemType = AStore_food;   
	  }
	  else if (!strcmp(itemType, "clothes"))
	  {
		anItem->itemType = AStore_clothes;
	  }
	  else if (!strcmp(itemType, "other"))
	  {
		anItem->itemType = AStore_other;
	  }
          
	  db_insert(anItem->barcode, anItem, NULL, ostate->db); 
								/* no free function - hence memory leak
								   for duplicat barcodes  */
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
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : constructor for depot object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "Create_CentralOffice_Depot_Object()"

CORBA_Object
Create_CentralOffice_Depot_Object(CORBA_long argc, 
                                  CORBA_char **argv, 
                                  CORBA_Environment *ev)
{
  CORBA_Object           obj;
  CORBA_ReferenceData    id;
  FILE*                  fp;
  ObjectStatePtr         objstate;
  PseudoNameService      pname;


  objstate = depot_init();      /* application initialisation */

  compose_refdata(&id, objstate);

  obj = CORBA_BOA_create(TheBoa, 
                         ev, 
                         &id,
                         DAIS_CentralOffice_Depot_intf,
                         DAIS_CentralOffice_Depot_impl
                         ); 
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create object",ev );
  }

  pname = NameService(ev);
  PseudoNameService_BindName(pname, ev, DEPOT_REF, obj);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("unable to export offer",ev );
  }

  CORBA_Object_release(pname, ev);
  
  CORBA_BOA_impl_is_ready(TheBoa, ev, DAIS_CentralOffice_Depot_impl);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to set impl ready",ev );
  }

  return obj;

} /* end of Create_CentralOffice_Depot_Object() */

