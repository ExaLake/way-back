/*
 *****************************************************************************
 * 
 * File Name   : tax.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : implementation of tax object
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

#define BASE_TAX_RATE 0.05      /* initialisation value for tax rate */

typedef struct tagTaxState
{
  AStore_AStoreId  _store_id;
  CORBA_float      rate;
  CORBA_char       *name;

} TaxState;


/*
 *-----------------------------------------------------------------------------
 * Forward References
 *-----------------------------------------------------------------------------
 */
ObjectStatePtr
tax_init(CORBA_long         argc, 
		 CORBA_char         **argv, 
		 CORBA_Environment  *ev,
		 CORBA_char         **name
		 );



/*
 *****************************************************************************
 * 
 * Function Name : S_AStore_Tax_CalculateTax
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of calculate tax operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_AStore_Tax_CalculateTax()"

CORBA_float 
S_AStore_Tax_CalculateTax(AStore_Tax         _obj, 
                           CORBA_Environment  *ev,
                           CORBA_float        TaxableAmount)
{
  TaxState          *ostate;

  ostate = get_state_ptr(TheBoa, ev, _obj);

  /* Return statement to be customized: */

  return (TaxableAmount * ostate->rate);

} /* end of S_AStore_Tax_CalculateTax() */


/*
 *****************************************************************************
 * 
 * Function Name : S_AStore_Tax_FindTaxablePrice
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of FindTaxablePrice operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_AStore_Tax_FindTaxablePrice()"

CORBA_float 
S_AStore_Tax_FindTaxablePrice(AStore_Tax         _obj, 
							  CORBA_Environment  *ev, 
							  CORBA_float        ItemPrice,
							  AStore_ItemTypes   ItemType)
{
  TaxState          *ostate;

  ostate = get_state_ptr(TheBoa, ev, _obj);
  /* 
   *if it is food or clothes then return zero, otherwise return ItemPrice 
   */
    
  if (ItemType == AStore_other) 
  {
    printf("Tax_FindTaxablePrice = %.2f\n",ItemPrice);
    return (ItemPrice);
  }
  else 
  {
    printf("Tax_FindTaxablePrice = %.2f\n",0.0);
    return 0.0;
  }
  
} /* end of S_AStore_Tax_FindTaxablePrice() */



/*
 *****************************************************************************
 * 
 * Function Name : Create_AStore_Tax_Object
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : object constructor for tax object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "Create_AStore_Tax_Object()"

CORBA_Object
Create_AStore_Tax_Object(CORBA_long        argc, 
                         CORBA_char        **argv, 
                         CORBA_Environment *ev)
{
  CORBA_Object           obj;
  CORBA_ReferenceData    id;
  FILE*                  fp;
  CORBA_char             *name;
  PseudoNameService      pname;
  ObjectStatePtr         objstate;


  objstate = tax_init(argc, argv, ev, &name); /* application initialisation */

  compose_refdata(&id, objstate);

  obj = CORBA_BOA_create(TheBoa, 
                         ev, 
                         &id,
                         DAIS_AStore_Tax_intf,
                         DAIS_AStore_Tax_impl
                         ); 
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
    application_terminate("Failed to create object",ev );
  }

  pname = NameService(ev);
  PseudoNameService_BindName(pname, ev, name, obj);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
    application_terminate("Failed to export offer",ev);
  }

  CORBA_Object_release(pname, ev);

  CORBA_BOA_impl_is_ready(TheBoa, ev, DAIS_AStore_Tax_impl);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
    application_terminate("Failed to set impl ready",ev );
  }

  return obj;

} /* end of Create_AStore_Tax_Object() */


/*
 *****************************************************************************
 * 
 * Function Name : tax_init
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : application initialisation for tax object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "tax_init()"

ObjectStatePtr
tax_init(CORBA_long         argc, 
		 CORBA_char         **argv, 
		 CORBA_Environment  *ev,
		 CORBA_char         **name
		 )
{
  TaxState  *ostate;

  ostate = malloc(sizeof(TaxState));

  if(1 != sscanf(argv[TAX_ID_ARG], TAX_ID_FMTSTR, &ostate->_store_id))
  {
	application_terminate("bad store id arg\n", ev);
  }
  
  ostate->name = malloc(sizeof(TAX_REF)+ID_LEN+1);
  sprintf(ostate->name, "%s%d", TAX_REF, ostate->_store_id);
  *name = ostate->name;

  ostate->rate = BASE_TAX_RATE;

  return (ObjectStatePtr)ostate;

} /* end of tax_init() */


