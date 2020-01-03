/*
 *****************************************************************************
 *
 * File Name   : linear.c
 *
 *    Performs linear search of a linked list, where the items can be anything
 *    identified by a character key.
 *****************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

DbDb db_init(void)
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
static DbEntry *lookup(char *key, DbDb db)
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
void *db_lookup(char *key, DbDb db)
{
  DbEntry *ppp;

  ppp = lookup(key, db);

  return (ppp) ? ppp->data : NULL;

} /* end of db_lookup() */

/*--------------------------------------------------------------------------*/
void db_insert(char *key, void *data, DbFreeFN free, DbDb db)
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
    ppp->key  = malloc(strlen(key)+1);
    strcpy(ppp->key,key);
    ppp->nxt  = db->nxt;
    db->nxt   = ppp;
  }

  ppp->data = data;
  ppp->free = free;

} /* End of db_insert() */

