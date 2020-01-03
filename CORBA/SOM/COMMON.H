/*
 *****************************************************************************
 * 
 * File Name   : common.h
 * 
 * Module Name : primer
 * 
 * Date        : 22jul95
 * 
 * Author      : Wilf Coles
 * 
 * Copyright   : Copyright ICL Enterprises 1995 (c)
 * 
 * Role        : common, shared definitions
 * 
 * /home/wc/cvs/primer/C/ICL/common.h,v 1.10 1995/08/25 11:21:44 wc Exp
 * 
 *****************************************************************************
 *
 * Amendment Record
 * ================
 *
 *  by  when   why
 * --- ------- ---------------------------------------------------------
 *  wc 22jul95 created
 * --- ------- ---------------------------------------------------------
 *
 *****************************************************************************
 */

#if !defined(COMMON_H)
#define COMMON_H

#define POS_DAT             "pos.dat"
#define TAX_REF             "tax_"
#define DEPOT_REF           "centralsvr"
#define DEPOT_FILE          "depot.dat"	/* This is the depot product data file */
#define STORE_REF           "store_"
#define STORE_DATA          "store.dat"
#define STORE_ACCESS_REF    "sa_"
#define INPUTMEDIA_REF      "im_"
#define OUTPUTMEDIA_REF     "om_"
#define POSTERM_REF         "pos_"
#define PNAME_REF           "pname.ref"

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

void application_terminate(char *message, CORBA_Environment *ev);

#define EX_TERM(s, ev)							\
												\
  if( (ev)->_major != CORBA_NO_EXCEPTION )		\
  {												\
	application_terminate(s,ev);				\
  }												\


void handle_error(CORBA_Environment *ev);
void ref_to_file(CORBA_Object obj, CORBA_Environment *ev, CORBA_char *filename);
SOMObject file_to_ref(CORBA_Environment *ev, string filename);
void register_server(CORBA_Environment *ev, SOMObject server);
#endif /* COMMON_H */


