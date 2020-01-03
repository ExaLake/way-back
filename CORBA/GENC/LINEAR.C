/*
 *****************************************************************************
 * 
 * File Name   : linear.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles, ICL
 * 
 * Role        : linear search database routines for generic C ORB
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

/*--------------------------------------------------------------------------*/
DbDb
db_init(void)
{
  DbEntry *new;

  new       = malloc(sizeof(DbEntry));

  new->nxt  = new;
  new->data = NULL;
  new->key  = NULL;
  new->free = NULL;

  return new;

} /* end of db_init() */

/*--------------------------------------------------------------------------*/
static DbEntry
*lookup(char *key, DbDb db)
{
  DbEntry *ppp;

  ppp = db->nxt;
  while (ppp->key != NULL)
  {
    if (!strcmp(ppp->key, key))
    {
      return ppp;
    }

    ppp = ppp->nxt;
  }

  return NULL;

} /* end of lookup() */

/*--------------------------------------------------------------------------*/
void
*db_lookup(char *key, DbDb db)
{
  DbEntry *ppp;

  ppp = lookup(key, db);

  return (ppp) ? ppp->data : NULL;

} /* end of db_lookup() */

/*--------------------------------------------------------------------------*/
void
db_insert(char *key, void *data, DbFreeFN free, DbDb db)
{
  DbEntry *ppp;

  ppp = lookup(key, db);
  
  if (ppp != NULL)
  {
      if (ppp->free != NULL)
      {
          ppp->free(ppp->data);
      }
  }
  else
  {
    ppp       = malloc(sizeof(DbEntry));
    ppp->key  = strdup(key);
    ppp->nxt  = db->nxt;
    db->nxt   = ppp;
  }
  
  ppp->data = data;
  ppp->free = free;

} /* End of db_insert() */

