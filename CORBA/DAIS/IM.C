/*
 *****************************************************************************
 * 
 * File Name   : im.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : implementation of input media object
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
#include "POS.h"
#include "PNS.h"
#include "misc.h"
#include "common.h"


typedef struct tagImState
{
  POS_POSTerminal  _posreference;
  POS_POSId        _id;
  CORBA_char       *pos_name;

} ImState;
/*
 *-----------------------------------------------------------------------------
 * Forward References
 *-----------------------------------------------------------------------------
 */
ObjectStatePtr
im_init(CORBA_long         argc, 
        CORBA_char         **argv, 
        CORBA_Environment  *ev,
		CORBA_char         **name);


/*
 *****************************************************************************
 * 
 * Function Name : S_POS_InputMedia_BarcodeInput
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implemetation of BarcodeInput operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_InputMedia_BarcodeInput()"

void 
S_POS_InputMedia_BarcodeInput(POS_InputMedia     _obj, 
							  CORBA_Environment  *ev, 
							  POS_Barcode        Item)
{
  ImState  *ostate;

  ostate = get_state_ptr(TheBoa, ev, _obj);

  POS_POSTerminal_SendBarcode(ostate->_posreference, ev, Item);

} /* end of POS_InputMedia_BarcodeInput() */



/*
 *****************************************************************************
 * 
 * Function Name : S_POS_InputMedia_KeypadInput
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : implementation of KeypadInput operation
 * 
 *****************************************************************************
 */
#undef FN
#define FN "S_POS_InputMedia_KeypadInput()"

void 
S_POS_InputMedia_KeypadInput(POS_InputMedia              _obj, 
							 CORBA_Environment           *ev, 
							 POS_InputMedia_OperatorCmd  Cmd)
{
  ImState  *ostate;
  
  ostate = get_state_ptr(TheBoa, ev, _obj);

  switch (toupper(Cmd[0]))
  {
  case 'L':
	POS_POSTerminal_Login(ostate->_posreference,ev);
	break;
  case 'P':
	POS_POSTerminal_PrintPOSSalesSummary(ostate->_posreference, ev);
	break;
  case 'S':
	POS_POSTerminal_PrintStoreSalesSummary(ostate->_posreference, ev);
	break;
  case 'T':
	POS_POSTerminal_EndOfSale(ostate->_posreference, ev);
	break;
  case 'Q':
	POS_POSTerminal_ItemQuantity(ostate->_posreference, ev, atol(++Cmd));
	break;
  default: printf("input ignored\n"); /* ignore */
  }
  return;
  
} /* end of S_POS_InputMedia_KeypadInput() */


/*
 *****************************************************************************
 * 
 * Function Name : Create_POS_InputMedia_Object
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : constructor for input media object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "Create_POS_InputMedia_Object()"

CORBA_Object
Create_POS_InputMedia_Object(CORBA_long         argc, 
                             CORBA_char         **argv, 
                             CORBA_Environment  *ev)
{
  CORBA_Object           obj;
  CORBA_ReferenceData    id;
  CORBA_char             *name;
  ObjectStatePtr         objstate;


  objstate = im_init(argc, argv, ev, &name); /* application initialisation */

  compose_refdata(&id, objstate);

  obj = CORBA_BOA_create(TheBoa, 
                         ev, 
                         &id,
                         DAIS_POS_InputMedia_intf,
                         DAIS_POS_InputMedia_impl
                         ); 
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to create object",ev );
  }

#if 0
  {
	PseudoNameService      pname;
	pname = NameService(ev);
	PseudoNameService_BindName(pname, ev, name, obj);
	if( ev->_major != CORBA_NO_EXCEPTION )
	{
	  application_terminate("unable to export offer",ev );
	}
	
	CORBA_Object_release(pname, ev);
  }
#endif

  
  CORBA_BOA_impl_is_ready(TheBoa, ev, DAIS_POS_InputMedia_impl);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("Failed to set impl ready",ev );
  }

  return obj;


} /* end of Create_POS_InputMedia_Object() */


/*
 *****************************************************************************
 * 
 * Function Name : im_init
 * 
 * Parameters    : see below
 * 
 * Returns       : see below
 * 
 * Role          : application initialisation for input media object
 * 
 *****************************************************************************
 */
#undef FN
#define FN "im_init()"

ObjectStatePtr
im_init(CORBA_long         argc, 
        CORBA_char         **argv, 
        CORBA_Environment  *ev,
		CORBA_char         **name)
{
  ImState  *ostate;
  PseudoNameService  pname;

  ostate = malloc(sizeof(ImState));

  if(1 != sscanf(argv[IM_ID_ARG], IM_ID_FMTSTR, &ostate->_id))
  {
	application_terminate("bad pos id arg\n", ev);
  }

  ostate->pos_name = malloc(sizeof(POSTERM_REF)+ID_LEN+1);
  sprintf(ostate->pos_name, "%s%d", POSTERM_REF, ostate->_id);

  pname = NameService(ev);
  ostate->_posreference = PseudoNameService_ResolveName(pname, ev, ostate->pos_name);
  if( ev->_major != CORBA_NO_EXCEPTION )
  {
	application_terminate("unable to import pos",ev );
  }

  CORBA_Object_release(pname, ev);

  *name = "input_media";

  return ostate;


} /* end of im_init() */


