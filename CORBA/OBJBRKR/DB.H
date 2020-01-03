/*
 *****************************************************************************
 *
 * File Name   : db.h
 *               Simple in-memory database routines for POS example
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
    struct tagDbEntry *nxt;    /* pointer to next entry in linked list */
    void              *data;   /* pointer to data associated with this entry */
    char              *key;    /* key to search for this entry */
    DbFreeFN          free;    /* pointer to function to free data if this entry
                                  is replaced (may be NULL) */

} DbEntry;


/*
 *-----------------------------------------------------------------------------
 * External interface to data store
 *-----------------------------------------------------------------------------
 */

typedef DbEntry *DbDb;         /* opaque type representing data store */

extern DbDb db_init(void);

extern void *db_lookup(char *key, DbDb db); /* returns pointer to data
                                               associated with key or NULL */

extern void db_insert(char *key,
                      void *data,
                      DbFreeFN free,
                      DbDb db
                      );           /* creates new or replaces old entry for
                                      key with associated pointer to data. any
                                      old data is freed with the function that
                                      was specfied when the entry was inserted.
                                      (NULL is valid for the free function)*/
