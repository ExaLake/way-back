/*
 *****************************************************************************
 * 
 * File Name   : posterminal.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : implementation of pos terminal
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
#include "PNS.h"
#include "misc.h"
#include "common.h"

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
 *****************************************************************************
 * 
 * Function Name : S_POS_POSTerminal_Login
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of posterminal Login operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_POSTerminal_Login()"


void 
S_POS_POSTerminal_Login(POS_POSTerminal    _obj, 
                        CORBA_Environment  *ev
                        )
{
  POSTermState  *ostate;

  ostate = (POSTermState *)get_state_ptr(TheBoa, ev, _obj);


  /* check to see if we are in the middle of a sale */
  if (ostate->_saleSubtotal != 0 || ostate->_quantity != 1) 
  {
    printf(FN ": Login ignored\n");
    return;
  }
  else
  {
    /* get access object */

    ostate->_accessreference 
      = AStore_Store_Login(ostate->_storereference,
                           ev,
                           ostate->_posid);
	EX_TERM("cant access store\n", ev);
      
    printf("POS::Login - logged into Store\n");
  }

} /* end of S_POS_POSTerminal_Login() */



/*
 *****************************************************************************
 * 
 * Function Name : S_POS_POSTerminal_PrintPOSSalesSummary
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of PrintPOSSalesSummary operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_POSTerminal_PrintPOSSalesSummary()"

void 
S_POS_POSTerminal_PrintPOSSalesSummary(POS_POSTerminal    _obj, 
									   CORBA_Environment  *ev
									   )
{
  char           outstring[STR_MAX];
  AStore_POSList poslist;
  int            count = 0;
  int            found = 0;
  POSTermState   *ostate;

  ostate = get_state_ptr(TheBoa, ev, _obj);
  
  /* check to see if we are in the middle of a sale 
   * get poslist from store 
   * find _posid in poslist 
   * format and print totals 
   */
  
  AStore_Store_GetPOSTotals(ostate->_storereference,
                              ev,
                              &poslist);
  
  while ((count < poslist._length) && (!found))
  {
    if (poslist._buffer[count].Id == ostate->_posid) found = 1;
    count++;
  }
  
  if (!found)
  {
    printf(FN ": POS not found\n");
  }
  else
  {
    sprintf(outstring,"Total POS sales = %.2f   Total POS taxes = %.2f\n", 
            poslist._buffer[count-1].TotalSales, 
            poslist._buffer[count-1].TotalTaxes);

    POS_OutputMedia_OutputText(ostate->_outputreference,
                                ev,
                                outstring);
  }
  
  CORBA_free(&poslist);
  return;
  
} /* end of S_POS_POSTerminal_PrintPOSSalesSummary() */


/*
 *****************************************************************************
 * 
 * Function Name : S_POS_POSTerminal_PrintStoreSalesSummary
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of PrintStoreSalesSummary
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_POSTerminal_PrintStoreSalesSummary()"

void 
S_POS_POSTerminal_PrintStoreSalesSummary(POS_POSTerminal    _obj, 
										 CORBA_Environment  *ev
										 )
{
  char                      outstring[STR_MAX];
  AStore_POSList            poslist;
  AStore_Store_StoreTotals  storetotals;
  int                       count;
  POSTermState              *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);
  
  
  /* check to see if we are in the middle of a sale  
   *      if subtotal = 0 and qty = 1
   * get totals structure from store
   * format and print totals
   */
  
  if (ostate->_saleSubtotal != 0 || ostate->_quantity != 1)
  { 
    printf(FN ": ignored, sale in progress\n");
    return;
  }
  
  storetotals = AStore_Store__get_Totals(ostate->_storereference, ev);
  sprintf(outstring, "Store total = %.2f   Store tax = %.2f\n", 
          storetotals.StoreTotal, 
          storetotals.StoreTaxTotal);
  
  POS_OutputMedia_OutputText(ostate->_outputreference, 
                              ev, 
                              outstring);
  
  AStore_Store_GetPOSTotals(ostate->_storereference, 
                              ev, 
                              &poslist);
  
  /* run through the list, printing out the totals */
  
  for (count = 0; count < poslist._length; count++)
  {
    sprintf(outstring," POSID = %d   POSTotal =  %.2f  POSTaxTotal = %.2f\n",
            poslist._buffer[count].Id, 
            poslist._buffer[count].TotalSales,
            poslist._buffer[count].TotalTaxes);

    POS_OutputMedia_OutputText(ostate->_outputreference,
                                ev,
                                outstring);
  }

  CORBA_free(&poslist);

  return;

} /* end of S_POS_POSTerminal_PrintStoreSalesSummary() */


/*
 *****************************************************************************
 * 
 * Function Name : S_POS_POSTerminal_SendBarcode
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of SendBarcode operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_POSTerminal_SendBarcode()"

void 
S_POS_POSTerminal_SendBarcode(POS_POSTerminal    _obj, 
							  CORBA_Environment  *ev, 
							  POS_Barcode        Item)
{
  char             outstring[STR_MAX];
  float            ItemPrice;
  float            itemtaxprice;
  AStore_ItemInfo  item_info;
  POSTermState     *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);

  /* call price on store access with qty, barcode and pos_id */

  AStore_StoreAccess_FindPrice(ostate->_accessreference,
							   ev,
							   Item,
							   ostate->_quantity,
							   &ItemPrice,
							   &itemtaxprice, 
							   &item_info);
  if (ev->_major == CORBA_SYSTEM_EXCEPTION)
  {
	/* just refer error to client */
	return;
  }
  else if (ev->_major == CORBA_USER_EXCEPTION)
  {
	printf(FN ": Barcode %s not found\n",Item);
	ostate->_quantity = 1;
	return;
  }
	
    
  ostate->_saleSubtotal        += ItemPrice * ostate->_quantity;
  ostate->_saleTaxableSubtotal += itemtaxprice * ostate->_quantity;
    

  if (itemtaxprice)
  {
    sprintf(outstring,"%s*  %s  %d   %.2f  %.2f\n ", item_info.Item,
            item_info.Name,
            ostate->_quantity,
            ItemPrice, 
            ItemPrice * ostate->_quantity);
  }
  else
  {  
    sprintf(outstring,"%s  %s  %d   %.2f  %.2f\n ", item_info.Item,
            item_info.Name,
            ostate->_quantity,
            ItemPrice, 
            ItemPrice * ostate->_quantity);
  }

  POS_OutputMedia_OutputText(ostate->_outputreference, ev, outstring);
  CORBA_free(&item_info);
  ostate->_quantity = 1;
  return;

} /* end of S_POS_POSTerminal_SendBarcode() */


/*
 *****************************************************************************
 * 
 * Function Name : S_POS_POSTerminal_ItemQuantity
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of ItemQuantity operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_POSTerminal_ItemQuantity()"

void 
S_POS_POSTerminal_ItemQuantity(POS_POSTerminal    _obj, 
							   CORBA_Environment  *ev, 
							   CORBA_long         Quantity)
{
  POSTermState  *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);

  printf("POS_POSTerminal_ItemQuantity = %d\n", Quantity);
  ostate->_quantity = Quantity;

} /* end of S_POS_POSTerminal_ItemQuantity() */


/*
 *****************************************************************************
 * 
 * Function Name : S_POS_POSTerminal_SendBarcode_and_quantity
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of SendBarcode_and_quantity operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_POSTerminal_SendBarcode_and_quantity()"

void 
S_POS_POSTerminal_SendBarcode_and_quantity(POS_POSTerminal _obj, 
                                            CORBA_Environment  *ev, 
                                            POS_Barcode item, 
                                            CORBA_long qty)
{
  POSTermState              *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);

  printf("POS::SendBarcode_and_quantity - \n");

  application_terminate(FN " not implmented", ev);
  
} /* end of S_POS_POSTerminal_SendBarcode_and_quantity() */


/*
 *****************************************************************************
 * 
 * Function Name : S_POS_POSTerminal_EndOfSale
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of end_sale operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_POSTerminal_EndOfSale()"

void 
S_POS_POSTerminal_EndOfSale(POS_POSTerminal    _obj, 
							CORBA_Environment  *ev)
{
  float         tax;
  char          outstring[STR_MAX];
  POSTermState  *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);
  
  /* make sure we are in a sale - totals should not be zero 
   * quantity should be 1
   * get tax on taxables
   * update store totals
   * print everything out - call print_totals 
   */
  
  tax = AStore_Tax_CalculateTax(ostate->_taxreference,
								ev,
								ostate->_saleTaxableSubtotal);
  
  AStore_Store_UpdateStoreTotals(ostate->_storereference,
								 ev, 
								 ostate->_posid,
								 ostate->_saleSubtotal,
								 tax);
  
  sprintf(outstring," Subtotal  %7.2f\n Tax       %7.2f\n Total     %7.2f\n",
          ostate->_saleSubtotal,
          tax, 
          ostate->_saleSubtotal + tax);
    
  POS_OutputMedia_OutputText(ostate->_outputreference, ev, outstring);

  /* zero out subtotal accumulators, reset quantity */
  ostate->_quantity            = 1;
  ostate->_saleSubtotal        = 0.0;
  ostate->_saleTaxableSubtotal = 0.0;

} /* end of S_POS_POSTerminal_EndOfSale() */




/*
 *****************************************************************************
 * 
 * Function Name : posterm_init
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : application initialisation for the POSTerminal object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "posterm_init()"

ObjectStatePtr
posterm_init(CORBA_long         argc, 
             CORBA_char         **argv, 
             CORBA_Environment  *ev,
			 CORBA_char         **name
			 )
{
  POSTermState       *ostate;
  PseudoNameService  pname;
  
  ostate = malloc(sizeof(POSTermState));

  if (argc != POS_ARGC)
  {
	application_terminate("wrong number of args\n", ev);
  }

  if(1 != sscanf(argv[POS_ID_ARG], POS_ID_FMTSTR, &ostate->_posid))
  {
	application_terminate("bad pos id arg\n", ev);
  }
  
  if(1 != sscanf(argv[POS_STORE_ARG], POS_STORE_FMTSTR, &ostate->_store_id))
  {
	application_terminate("bad store id arg\n", ev);
  }
  
  ostate->pos_name = malloc(sizeof(POSTERM_REF)+ID_LEN+1);
  sprintf(ostate->pos_name, "%s%d", POSTERM_REF, ostate->_posid);
  *name = ostate->pos_name;

  ostate->store_name = malloc(sizeof(STORE_REF)+ID_LEN+1);
  sprintf(ostate->store_name, "%s%d", STORE_REF, ostate->_store_id);

  ostate->om_name = malloc(sizeof(OUTPUTMEDIA_REF)+ID_LEN+1);
  sprintf(ostate->om_name, "%s%d", OUTPUTMEDIA_REF, ostate->_posid);

  ostate->tax_name = malloc(sizeof(TAX_REF)+ID_LEN+1);
  sprintf(ostate->tax_name, "%s%d", TAX_REF, ostate->_store_id);

  
  pname                    = NameService(ev);
  ostate->_storereference  = PseudoNameService_ResolveName(pname, ev, ostate->store_name);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to import store",ev );
  }

  ostate->_taxreference    = PseudoNameService_ResolveName(pname, ev, ostate->tax_name);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create tax object",ev );
  }

  ostate->_outputreference = PseudoNameService_ResolveName(pname, ev, ostate->om_name);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create output media",ev );
  }

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
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : constructor for the POSTerminal object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "Create_POS_POSTerminal_Object()"

CORBA_Object
Create_POS_POSTerminal_Object(CORBA_long         argc, 
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
                         DAIS_POS_POSTerminal_intf,
                         DAIS_POS_POSTerminal_impl); 
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create object",ev );
  }

  pname = NameService(ev);
  PseudoNameService_BindName(pname, ev, name, obj);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("unable to export offer", ev);
  }

  CORBA_Object_release(pname, ev);
  
  CORBA_BOA_impl_is_ready(TheBoa, ev, DAIS_POS_POSTerminal_impl);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to set impl ready",ev );
  }
  
  return obj;

} /* end of Create_POS_POSTerminal_Object() */
