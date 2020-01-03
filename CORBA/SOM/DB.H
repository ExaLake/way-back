/*
 *****************************************************************************
 * 
 * File Name   : db.h
 * 
 * Module Name : 
 * 
 * Date        :  9aug95
 * 
 * Author      : Wilf Coles
 * 
 * Copyright   : Copyright ICL Enterprises 1995 (c)
 * 
 * Role        :
 * 
 * /home/wc/cvs/primer/C/ICL/db.h,v 1.1 1995/08/09 09:21:10 wc Exp
 * 
 *****************************************************************************
 *
 * Amendment Record
 * ================
 *
 *  by  when   why
 * --- ------- ---------------------------------------------------------
 *  wc  9aug95 created
 * --- ------- ---------------------------------------------------------
 *
 *****************************************************************************
 */

/*
 *-----------------------------------------------------------------------------
 * Internal data structuring, not for external use
 *-----------------------------------------------------------------------------
 */

typedef void (*DbFreeFN)(void *);

typedef struct tagDbEntry
{
  struct tagDbEntry *nxt;       /* pointer to next entry in linked list */
  void              *data;      /* pointer to data associated with this entry */
  char              *key;       /* key to search for this entry */
  DbFreeFN          free;       /* pointer to function to free data if this entry
                                   is replaced (may be NULL) */

} DbEntry;


/*
 *-----------------------------------------------------------------------------
 * External interface to data store
 *-----------------------------------------------------------------------------
 */

typedef DbEntry *DbDb;          /* opaque type representing data store */

extern DbDb
db_init(void);

extern void
*db_lookup(char *key, DbDb db); /* returns pointer to data associated
                                   with key or NULL */

extern void
db_insert(char *key, 
          void *data, 
          DbFreeFN free, 
          DbDb db
          );                    /* creates new or replaces old entry for
                                   key with associated pointer to data. any
                                   old data is freed with the function that
                                   was specfied when the entry was inserted.
                                   (NULL is valid for the free function)*/

