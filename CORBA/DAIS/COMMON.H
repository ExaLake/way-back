/*
 *****************************************************************************
 * 
 * File Name   : common.h
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : common definitions and configuration
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
#if !defined(COMMON_H)
#define COMMON_H

#include "orb.h"
#include "PNS.h"

#define TAX_REF             "tax_"
#define DEPOT_REF           "depot_"
#define DEPOT_FILE          "depot.dat"	/* This is the depot product data file */
#define STORE_REF           "store_"
#define STORE_DATA          "store.dat"
#define STORE_ACCESS_REF    "sa_"
#define INPUTMEDIA_REF      "im_"
#define OUTPUTMEDIA_REF     "om_"
#define POSTERM_REF         "pos_"
#define PNAME_REF           "PNS.dat"

#define TAX_RATE            0.05
#define REF_MAX             1024
#define STR_MAX             80
#define ID_LEN              5	/* maximum length of numeric part of an id
								   as a string */

#define MAX_POSLIST_ENTRIES 50


#define MAX_STR_LENGTH      64
#define ARG_STR_LEN         30	/* enough space to pass a numeric argument
                                   as a string name/value pair */


/*
 *-----------------------------------------------------------------------------
 * arguments to Store access constructor
 *-----------------------------------------------------------------------------
 */
#define SA_ARGC 3				/* number of arguments to StoreAccess
                                   constructor */
#define SA_MARKUP_FMTSTR "markup=%f"
#define SA_MARKUP_ARG    1

#define SA_ID_FMTSTR     "id=%ld"
#define SA_ID_ARG        2

/*
 *-----------------------------------------------------------------------------
 * arguments to Store constructor
 *-----------------------------------------------------------------------------
 */
#define S_ARGC 3				/* number of arguments to StoreAccess
                                   constructor */
#define S_MARKUP_FMTSTR  "markup=%f"
#define S_MARKUP_ARG     1
		 
#define S_ID_FMTSTR      "id=%ld"
#define S_ID_ARG         2

/*
 *-----------------------------------------------------------------------------
 * arguments to Tax constructor
 *-----------------------------------------------------------------------------
 */
#define TAX_ARGC 3				/* number of arguments to Tax 
                                   constructor */
#define TAX_ID_FMTSTR      S_ID_FMTSTR
#define TAX_ID_ARG         S_ID_ARG


/*
 *-----------------------------------------------------------------------------
 * arguments to POS Terminal constructor
 *-----------------------------------------------------------------------------
 */

#define POS_ARGC         3
#define POS_ID_ARG       1
#define POS_ID_FMTSTR    "id=%ld"
#define POS_STORE_ARG    2
#define POS_STORE_FMTSTR "store=%ld"

/*
 *-----------------------------------------------------------------------------
 * arguments to OutputMedia constructor
 *-----------------------------------------------------------------------------
 */
#define OM_ARGC         2
#define OM_ID_ARG       1
#define OM_ID_FMTSTR    "id=%d"


/*
 *-----------------------------------------------------------------------------
 * arguments to InputMedia constructor
 *-----------------------------------------------------------------------------
 */

#define IM_ARGC         2
#define IM_ID_ARG       POS_ID_ARG
#define IM_ID_FMTSTR    POS_ID_FMTSTR

/*
 *-----------------------------------------------------------------------------
 * provide declarations for the ORB and BOA pseudo object references set
 * up in the main for each capsule/executable
 *-----------------------------------------------------------------------------
 */

extern CORBA_ORB TheOrb;
extern CORBA_BOA TheBoa;


#if 0
CORBA_Object 
S_PseudoNameService_Resolve(PseudoNameService  _obj, 
							CORBA_Environment  *ev, 
							CORBA_char         *ObjectName
							);
void 
S_PseudoNameService_Bind(PseudoNameService  _obj, 
						 CORBA_Environment  *ev, 
						 CORBA_char         *ObjectName, 
						 CORBA_Object       ObjectRef
						 );
#endif

#define EX_TERM(s, ev)							\
												\
  if( (ev)->_major != CORBA_NO_EXCEPTION )		\
  {												\
	application_terminate(s,ev);				\
  }												\
  

#endif /* COMMON_H */


