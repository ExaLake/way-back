/*
 *****************************************************************************
 * 
 * File Name   : linear.c
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : linear search database
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

