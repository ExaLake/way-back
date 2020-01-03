/*
 *****************************************************************************
 *
 * File Name   : common.h
 *
 * Role        : common, shared definitions
 *
 *****************************************************************************
 */

#if !defined(COMMON_H)
#define COMMON_H

#include <orb.h>
#include "pnamesvc.h"

#define POS_DAT             "pos.dat"
#define TAX_REF             "tax_"
#define DEPOT_REF           "depot_"
#define DEPOT_FILE          "depot.dat"         /* This is the depot product data file */
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
#define ID_LEN              5                   /* maximum length of numeric part of an id
                                                   as a string */

#define MAX_POSLIST_ENTRIES 50


#define MAX_STR_LENGTH      64
#define ARG_STR_LEN         30                  /* enough space to pass a numeric argument
                                                   as a string name/value pair */

/*
 *-----------------------------------------------------------------------------
 * arguments to Store constructor
 *-----------------------------------------------------------------------------
 */
#define S_ARGC 3                                /* number of arguments to StoreAccess
                                                   constructor */
#define S_ID_FMTSTR      "%ld"
#define S_ID_ARG         1

#define S_MARKUP_ARG     2
#define S_MARKUP_FMTSTR  "%f"

/*
 *-----------------------------------------------------------------------------
 * arguments to Store access constructor
 *-----------------------------------------------------------------------------
 */
#define SA_ARGC S_ARGC                          /* number of arguments to StoreAccess
                                                   constructor */
#define SA_ID_FMTSTR     S_ID_FMTSTR
#define SA_ID_ARG        S_ID_ARG

#define SA_MARKUP_FMTSTR S_MARKUP_FMTSTR
#define SA_MARKUP_ARG    S_MARKUP_ARG

/*
 *-----------------------------------------------------------------------------
 * arguments to Tax constructor
 *-----------------------------------------------------------------------------
 */
#define TAX_ARGC 3                              /* number of arguments to Tax
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
#define POS_ID_FMTSTR    "%ld"
#define POS_STORE_ARG    2
#define POS_STORE_FMTSTR "%ld"

/*
 *-----------------------------------------------------------------------------
 * arguments to OutputMedia constructor
 *-----------------------------------------------------------------------------
 */
#define OM_ARGC         2
#define OM_ID_ARG       1
#define OM_ID_FMTSTR    "%d"


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
 * up in the main for each executable
 *-----------------------------------------------------------------------------
 */

typedef CORBA_Object CORBA_ORB;
typedef CORBA_Object CORBA_BOA;

extern CORBA_ORB TheOrb;
extern CORBA_BOA TheBoa;

#endif /* COMMON_H */
