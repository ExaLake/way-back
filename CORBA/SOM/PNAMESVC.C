#ifndef lint
static char *sccsid = "%W%";
#endif

/*
 *   (C) COPYRIGHT International Business Machines Corp. 1995, 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 *   DISCLAIMER OF WARRANTIES.
 *   The following [enclosed] code is sample code created by IBM
 *   Corporation. This sample code is not part of any standard or IBM
 *   product and is provided to you solely for the purpose of assisting
 *   you in the development of your applications.  The code is provided
 *   "AS IS". IBM MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
 *   NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *   FOR A PARTICULAR PURPOSE, REGARDING THE FUNCTION OR PERFORMANCE OF
 *   THIS CODE.  IBM shall not be liable for any damages arising out of
 *   your use of the sample code, even if they have been advised of the
 *   possibility of such damages.
 *
 *   DISTRIBUTION.
 *   This sample code can be freely distributed, copied, altered, and
 *   incorporated into other software, provided that it bears the above
 *   Copyright notice and DISCLAIMER intact.
 */

/*
 *  This file was generated by the SOM Compiler and Emitter Framework.
 *  Generated using: 
 *      SOM Emitter emitctm.dll: 2.41
 */

#ifndef SOM_Module_pnamesvc_Source
#define SOM_Module_pnamesvc_Source
#endif
#define PseudoNameService_Class_Source

#include <corba12.h>
#include <pnamesvc.ih>
#include <db.h>
#include <impldef.h>
#include <common.h>

typedef struct _item
{
   CORBA_Object obj;
} item_s, *item_p;

typedef struct tagPNameState 
{
  DbDb  db;
} PNameState;

#undef FN
#define FN "free_item()"

void
free_item(void *data)
{
  CORBA_Environment  ev;

  CORBA_exception_free(&ev);
  CORBA_Object_release(((item_p)data)->obj, &ev);

} /* end of free_item() */


#undef FN
#define FN "BindName()"

SOM_Scope void  SOMLINK BindName(PseudoNameService somSelf,  Environment *ev, 
                                 string ObjectName, SOMObject ObjectRef)
{
    PNameState  *ostate;
    item_p  anItem;
    PseudoNameServiceData *somThis = PseudoNameServiceGetData(somSelf); 
    PseudoNameServiceMethodDebug("PseudoNameService","BindName");

    ostate = (PNameState *) somThis->ostate;
   
    anItem = SOMMalloc(sizeof(item_s));
    anItem->obj = CORBA_Object_duplicate(ObjectRef,ev);
    if (ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    printf(FN ": BindNaming object %s\n", ObjectName);
    db_insert(ObjectName,anItem, free_item, ostate->db);
    return;
} /* end of BindName */

#undef FN
#define FN "S_PseudoNameService_ResolveName()"

SOM_Scope SOMObject  SOMLINK ResolveName(PseudoNameService somSelf, 
                                          Environment *ev, string ObjectName)
{
    item_p                theItem;
    PNameState            *ostate;
    CORBA_Object          theObject;

    PseudoNameServiceData *somThis = PseudoNameServiceGetData(somSelf);
    PseudoNameServiceMethodDebug("PseudoNameService","ResolveName");

    ostate   = (PNameState *) somThis->ostate;

    if (theItem = db_lookup((char*)ObjectName, ostate->db))
    {
	theObject = theItem->obj;
	printf(FN " : found %s\n", ObjectName);
    }
    else
    {
	printf(FN " : %s not found\n",  ObjectName);
	theObject = CORBA_OBJECT_NIL;
    }
    return CORBA_Object_duplicate (theObject, ev);
}

SOM_Scope void SOMLINK somDefaultInit(PseudoNameService somSelf, 
                                      somInitCtrl* ctrl)
{
    FILE *fp;
    CORBA_Environment ev;
    PNameState   *ostate;

    PseudoNameServiceData *somThis; /* set in BeginInitializer */
    somInitCtrl globalCtrl;
    somBooleanVector myMask;
    PseudoNameServiceMethodDebug("PseudoNameService","somDefaultInit");
    PseudoNameService_BeginInitializer_somDefaultInit;

    PseudoNameService_Init_SOMDServer_somDefaultInit(somSelf, ctrl);
    SOM_InitEnvironment(&ev);

    /*
     * Create and initialize the hash table 
     */
    
    ostate          = SOMMalloc(sizeof(PNameState));
    ostate->db      = db_init();
    somThis->ostate = ostate;
   
    /** write object reference to a file **/

    ref_to_file(somSelf, &ev, PNAME_REF);

    SOM_UninitEnvironment(&ev);
    printf("PseudoNameService server initialized and ready\n");
    
}

SOM_Scope void SOMLINK somDestruct(PseudoNameService somSelf, 
                                   octet doFree, somDestructCtrl* ctrl)
{
    PseudoNameServiceData *somThis; /* set in BeginDestructor */
    somDestructCtrl globalCtrl;
    somBooleanVector myMask;
    PseudoNameServiceMethodDebug("PseudoNameService","somDestruct");
    PseudoNameService_BeginDestructor;
    PseudoNameService_EndDestructor;
}


