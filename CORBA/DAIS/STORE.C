/*
 *****************************************************************************
 * 
 * File Name   : store.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : implementation of store object
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
#include "common.h"
#include "PNS.h"
#include "misc.h"

/*
 *-----------------------------------------------------------------------------
 * declarations to access StoreAccess constructor
 *-----------------------------------------------------------------------------
 */

#define new_AStore_StoreAccess Create_AStore_StoreAccess_Object

extern CORBA_Object
Create_AStore_StoreAccess_Object(CORBA_long argc, 
                                 CORBA_char **argv, 
                                 CORBA_Environment *ev);

/*
 *-----------------------------------------------------------------------------
 * Structure definition for object state
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
 * Function Name : S_AStore_Store_Login
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of Login function 
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_AStore_Store_Login()"

AStore_StoreAccess 
S_AStore_Store_Login(AStore_Store       _obj, 
                     CORBA_Environment  *ev, 
                     POS_POSId          Id)
{
  AStore_StoreAccess  store_access;
  int                 count = 0;
  int                 found = 0;
  CORBA_char**        argv;
    
  StoreState          *ostate;

  ostate = get_state_ptr(TheBoa, ev, _obj);
  
  /*
   *---------------------------------------------------------------------------
   * check POSList to see if store_Id exists if it doesn't, add it to
   * poslist, create a StoreAcess object and return
   * 
   * if store_Id is already in the list, zero out totals and return
   * existing StoreAccess object
   * 
   * As currently implemented, the POSList has room for 50 POS entries If
   * the table is full, additional POSs trying to log in will receive a
   * NULL StoreAccess object
   *---------------------------------------------------------------------------
   */
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
	  {
		found = 1;
	  }
	  count++;
	}
  }
  
  if (!found)               
  {                             /* if the POSid is not already in the
								   poslist add it, creating StoreAccess
								   object in the process */
	AStore_POSInfo   *new_pos;  /* temporary pointer for textual
								   conciseness */
	
	argv                = malloc(sizeof(CORBA_char *) * SA_ARGC);
	argv[SA_MARKUP_ARG] = malloc(ARG_STR_LEN + 1);
	argv[SA_ID_ARG    ] = malloc(ARG_STR_LEN + 1);
	
	sprintf(argv[SA_MARKUP_ARG], SA_MARKUP_FMTSTR, ostate->_storeMarkup);
	sprintf(argv[SA_ID_ARG],     SA_ID_FMTSTR,     ostate->_store_id);
	
	store_access = new_AStore_StoreAccess((CORBA_long)SA_ARGC,
										  argv,
										  ev);
	free(argv[SA_MARKUP_ARG]);
	free(argv[SA_ID_ARG]);
	free(argv);
	
	/* initialize the postlist entry */
	
	new_pos 
	  = &(ostate->_poslist._buffer[ostate->_poslist._length]);
	
	new_pos->StoreAccessReference = store_access;
	new_pos->Id                    = Id;
	new_pos->TotalSales            = 0;
	new_pos->TotalTaxes            = 0;
	
	ostate->_poslist._length++; /* increment the length field of
								   the POSList sequence */
	
	printf(FN ": added POSid %d to the POSList sequence\n", new_pos->Id);
	
	return store_access;
  }
  else
  {
	/* 
	 * reset POS totals
	 */
	ostate->_poslist._buffer[count-1].TotalSales = 0.0;
	ostate->_poslist._buffer[count-1].TotalTaxes = 0.0;
	
	
	printf(FN " returning existing StoreAccess object for POSid: %d\n",
		   ostate->_poslist._buffer[count-1].Id);
	
	return ostate->_poslist._buffer[count-1].StoreAccessReference;
  }
  
} /* end of S_AStore_Store_Login() */


/*
 *****************************************************************************
 * 
 * Function Name : S_AStore_Store_GetPOSTotals
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of GetPOSTotals operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_AStore_Store_GetPOSTotals()"

void
S_AStore_Store_GetPOSTotals(AStore_Store       _obj, 
							CORBA_Environment  *ev, 
							AStore_POSList     *POSData)
{
    StoreState  *ostate;

    ostate = get_state_ptr(TheBoa, ev, _obj);

    *POSData = ostate->_poslist;

} /* end of S_AStore_Store_GetPOSTotals() */


/*
 *****************************************************************************
 * 
 * Function Name : S_AStore_Store__get_StoreId
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : read store_id attribute
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_AStore_Store__get_StoreId()"

AStore_AStoreId 
S_AStore_Store__get_StoreId(AStore_Store       _obj, 
							CORBA_Environment  *ev
							)
{
  StoreState          *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);

  return ostate->_store_id;

} /* end of S_AStore_Store__get_StoreId() */


/*
 *****************************************************************************
 * 
 * Function Name : S_AStore_Store__get_Totals
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : read totals attribute
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_AStore_Store__get_Totals()"

AStore_Store_StoreTotals 
S_AStore_Store__get_Totals(AStore_Store       _obj, 
						   CORBA_Environment  *ev
						   )
{
  StoreState          *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);

  return ostate->_totals;

} /* end of S_AStore_Store__get_Totals() */


/*
 *****************************************************************************
 * 
 * Function Name : S_AStore_Store_UpdateStoreTotals
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : impementation of UpdateStoreTotals operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_AStore_Store_UpdateStoreTotals()"

void 
S_AStore_Store_UpdateStoreTotals(AStore_Store       _obj, 
								 CORBA_Environment  *ev, 
								 POS_POSId          Id, 
								 CORBA_float        Price, 
								 CORBA_float        Taxes)
{
  int         count = 0;
  int         found = 0;
  StoreState  *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);
  
  
  ostate->_totals.StoreTotal    += Price;
  ostate->_totals.StoreTaxTotal += Taxes;
  
  while ((count < ostate->_poslist._length) && (!found))
  {
	if (ostate->_poslist._buffer[count].Id == Id) found = 1;
	count++;
  }
  
  if (!found)
  {
	printf(FN ": there is a serious problem!\n");
	return;
  }
  
  ostate->_poslist._buffer[count-1].TotalSales += Price;
  ostate->_poslist._buffer[count-1].TotalTaxes += Taxes;
  
  return;

} /* end of S_AStore_Store_UpdateStoreTotals() */


/*
 *****************************************************************************
 * 
 * Function Name : store_init
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : application initialisation for store object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "store_init()"

ObjectStatePtr
store_init(CORBA_long         argc, 
		   CORBA_char         **argv, 
		   CORBA_Environment  *ev,
		   CORBA_char         **name)
{
  char              reference[REF_MAX]; 
  FILE              *fp;
  CORBA_string      stringref;
  StoreState        *ostate;
  PseudoNameService pname;

  ostate = malloc(sizeof(StoreState));
  
  /*
   * associate the instance data poslist array with poslist sequence
   * and initialize sequence
   */
  
  ostate->_poslist._buffer  = ostate->_posarray;
  ostate->_poslist._maximum = MAX_POSLIST_ENTRIES;
  ostate->_poslist._length  = 0;

  if (argc != S_ARGC)
  {
	application_terminate("wrong number of args\n", ev);
  }

  if(1 != sscanf(argv[S_ID_ARG], S_ID_FMTSTR, &ostate->_store_id))
  {
	application_terminate("bad store id arg\n", ev);
  }
  
  ostate->store_name        = malloc(sizeof(STORE_REF)+ID_LEN+1);
  sprintf(ostate->store_name, "%s%ld", STORE_REF, ostate->_store_id);

  ostate->tax_name          = malloc(sizeof(TAX_REF)+ID_LEN+1);
  sprintf(ostate->tax_name, "%s%ld", TAX_REF, ostate->_store_id);

  *name                     = ostate->store_name;


  pname                     = NameService(ev);
  ostate->_depotReference   = PseudoNameService_ResolveName(pname, ev, DEPOT_REF);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to import depot",ev );
  }

  ostate->_taxReference   = PseudoNameService_ResolveName(pname, ev, ostate->tax_name);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to import tax",ev );
  }
      
  CORBA_Object_release(pname, ev);
  /* 
   *    initialize StoreTotal = StoreTaxTotal = 0
   */
  
  ostate->_totals.StoreTotal     = 0;
  ostate->_totals.StoreTaxTotal = 0;

  if (argc != S_ARGC)
  {
	application_terminate("wrong number of arguments\n", ev);
  }

  if(1 != sscanf(argv[S_MARKUP_ARG], S_MARKUP_FMTSTR, &ostate->_storeMarkup))
  {
	application_terminate("bad markup arg\n", ev);
  }

  if(1 != sscanf(argv[S_ID_ARG],     S_ID_FMTSTR,     &ostate->_store_id))
  {
	application_terminate("bad id  arg\n", ev);
  }

  printf("Store server is initialized and ready\n");
  
  return (ObjectStatePtr)ostate;

} /* end of store_init() */


/*
 *****************************************************************************
 * 
 * Function Name : Create_AStore_Store_Object
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : constructor for store object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "Create_AStore_Store_Object()"

CORBA_Object
Create_AStore_Store_Object(CORBA_long argc, 
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
                         DAIS_AStore_Store_intf,
                         DAIS_AStore_Store_impl
                         ); 
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create object",ev );
  }
  
  pname = NameService(ev);
  PseudoNameService_BindName(pname, ev, name, obj);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to set impl ready",ev );
  }
  
  CORBA_Object_release(pname, ev);
  
  CORBA_BOA_impl_is_ready(TheBoa, ev, DAIS_AStore_Store_impl);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to set impl ready",ev );
  }
  
  return obj;
  

} /* end of Create_AStore_Store_Object() */



