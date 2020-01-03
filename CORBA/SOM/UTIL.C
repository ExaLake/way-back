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

#include <corba12.h>
#include <stdio.h>
#include <pos.h>
#include <orb.h>
#include <somdserv.h>
#include <store.h>
#include <impldef.h>
#include <pnamesvc.h>
#include <common.h>


void handle_exception(CORBA_Environment *ev)
{
    AStore_BarcodeNotFound *barcodeError;
    StExcep                *stex;
    CORBA_char             *exid;

    switch(ev->_major)
    {
    case CORBA_NO_EXCEPTION :
			 return;
    case CORBA_SYSTEM_EXCEPTION:
	
	/**  print system exception value  **/

	stex = somExceptionValue(ev);
	printf("System exception: code = %d status = %s\n", stex->minor,
	       stex->completed);
	application_terminate  ("System Exception", ev);
	       
    case CORBA_USER_EXCEPTION:

	/**  print user exception value  **/
 
	if (strcmp((somExceptionId(ev)), ex_BarcodeNotFound) == 0)
	{
	    barcodeError = (BarcodeNotFound*) somExceptionValue(ev);
	    printf("User exception: Barcode not found for item - %s\n",
		   barcodeError->item);
	}
	return;

    default:
        application_terminate ("none of the above", ev);
    }
}

void handle_error (Environment *ev)
{
	handle_exception (ev);
}


void ref_to_file(CORBA_Object obj, CORBA_Environment *ev, CORBA_char *filename)
{
    SOMDObject sdo;
    FILE *fp;
    CORBA_char *stringref;

    fp = fopen(filename,"w"); 

    if(!fp)
    {
	printf("%s could not be opened\n",filename);
	exit(1);
    }

    /* get an object reference to the server */

    SOMD_ServerObject = obj;
    sdo = SOMDServer_somdRefFromSOMObj(obj, ev, obj);
    if (ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    /* get the string form of the object reference */

    stringref = CORBA_ORB_object_to_string(SOMD_ORBObject, ev, sdo);
    if (ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    fprintf(fp,"%s",stringref);
    fclose (fp);

    /** cleanup **/

    CORBA_free(stringref);
    CORBA_Object_release(sdo,ev);
    if (ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    return;
}

SOMObject file_to_ref(CORBA_Environment *ev, string filename)
{
    CORBA_char reference[REF_MAX]; 
    FILE *fp;
    CORBA_Object obj;

    fp = fopen(filename,"r");

    if(!fp)
    {
	printf("%s could not be opened\n",filename);
	exit(1);
    }

    fscanf(fp,"%s",reference);

    fclose(fp);

    /* get the object reference from the string */

    obj = CORBA_ORB_string_to_object(SOMD_ORBObject, ev, reference);
    if (ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    return obj;
}

void register_server(CORBA_Environment *ev, SOMObject server)

{
    string return_string; 
    PseudoNameService pnsRef;
    SOMDObject sdo;

    /*
     * the server alias is used as the name to be registered 
     * with the PNS                                         
     */

    /* get the server aliax */
    return_string = ImplementationDef__get_impl_alias(SOMD_ImplDefObject,ev);

    /* get an object reference to the PseudoNameService */

    pnsRef = file_to_ref (ev,PNAME_REF);
    if(ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    /* build an object reference for the server object */

    SOMD_ServerObject = server;
    sdo = SOMDServer_somdRefFromSOMObj(server, ev, server);
    if(ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    /* register the server with the PseudoNameService */

    PseudoNameService_BindName(pnsRef,ev,return_string,sdo);
    if(ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    /* free the object reference */

    CORBA_Object_release(sdo,ev);
    if(ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    /* free the PNS object reference */

    CORBA_Object_release(pnsRef,ev);
    if(ev->_major != CORBA_NO_EXCEPTION) handle_error(ev);

    SOMFree(return_string);
}

#undef FN
#define FN "application_terminate()"
void application_terminate(char *message, CORBA_Environment *ev)
{

     printf ("%s\n", message);
     printf ("application terminating\n");
     exit (1);
} /* end of application_terminate() */

