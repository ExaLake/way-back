/*
 *****************************************************************************
 * 
 * File Name   : db.h
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : database access definition
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

