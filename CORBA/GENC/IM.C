/*
 *****************************************************************************
 * 
 * File Name   : im.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles, ICL
 * 
 * Role        : implementation of input media object for generic C ORB
 * 
 * This generic version was derived from the DAIS version which has skeletons
 * starting with 'S_'. These will need modification in order to work with other
 * ORBs. The only other proprietary identifiers are the _impl and _intf arguments
 * to CORBA_BOA_create and CORBA_BOA_impl_is_ready.
 *
 * Copyright (C) 1996 by the Object Management Group, Inc.  All  
 * rights reserved.  
 * 
 * Permission to use, copy, modify, and distribute this software for
 * any  teaching or instructional purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the names of
 * Object Management Group, Inc. (OMG) and John Wiley and Sons, Inc.
 * (Wiley) not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.
 * 
 * THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTY OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  Neither OMG, Wiley, nor their dealers or distributors
 * assume any liability of any alleged or actual damages arising
 * from the use of or the inability to use this software.  (Some
 * states do not allow the exclusion of implied warranties, so the
 * exclusion may not apply to you.)
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
                         POS_InputMedia_intf, /* Replace with definitions */
                         POS_InputMedia_impl  /* appropriate to your ORB. */
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

  
  CORBA_BOA_impl_is_ready(TheBoa, ev, POS_InputMedia_impl); 
									/* Replace with appropriate definition */
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


