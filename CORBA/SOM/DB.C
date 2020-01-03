/*
 *****************************************************************************
 * 
 * File Name   : linear.c
 * 
 * Module Name : primer
 * 
 * Date        :  8aug95
 * 
 * Author      : Wilf Coles
 * 
 * Copyright   : Copyright ICL Limited 1995 (c)
 * 
 * Role        : linear search database
 * 
 * /home/wc/cvs/primer/C/ICL/linear.c,v 1.1 1995/08/09 09:21:21 wc Exp
 * 
 *****************************************************************************
 *
 * Amendment Record
 * ================
 *
 *  by  when   why
 * --- ------- ---------------------------------------------------------
 *  wc  8aug95 created
 * --- ------- ---------------------------------------------------------
 *
 *****************************************************************************
 */

#define FN "<null>"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <som.h>
#include <db.h>

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
db_insert(string key, void *data, DbFreeFN free, DbDb db)
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
    ppp       = SOMMalloc(sizeof(DbEntry));
    ppp->key  = SOMMalloc(strlen(key));
    strcpy(ppp->key, key);
    ppp->nxt  = db->nxt;
    db->nxt   = ppp;
  }
  ppp->data = data;
  ppp->free = free;

} /* End of db_insert() */

