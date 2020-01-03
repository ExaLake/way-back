/*
 *****************************************************************************
 * 
 * File Name   : db.h
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles, ICL
 * 
 * Role        : database access definition for generic C ORB
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

