#ifndef CCP_HT_H
#define CCP_HT_H

#include <stddef.h>
#include <stdbool.h>
#include "types.h"

/**
 * Generate hash (index) from a key
 *
 * @key: key string
 *
 * @ret: index (hash)
 */
size_t ccp_ht_make_hash(const char *key);


//int ccp_ht_key_exists(CCP_HT *htp, const char *key);


/**
 * @WARN!
 * Create a new Hash-Table
 *
 * @ret: pointer to new HT | NULL
 */
CCP_HT *ccp_ht_new();


/**
 * Add a new Flag to Hash-Table
 *
 * @htp: pointer to a HT
 * @key: key of value
 * @fp: pointer to Flag
 *
 * @ret: 0 ok | 1 key exist | 2 error
 */
int ccp_ht_addflag(CCP_HT *htp, const char *key, Flag *fp);


/**
 * Free a HT from memorty including it's values
 *
 * @htp: pointer to a HT
 *
 * @ret: 0 ok | 1 error
 */
int ccp_ht_free(CCP_HT *htp, void (*fn) (Flag *fp));


/**
 * @WARN!
 * Get a Flag in HT with it's name
 *
 * @htp: pointer to a HT
 * @key: key string
 *
 * @ret: pointer to value | NULL
 */
Flag *ccp_ht_getflag(CCP_HT *htp, const char *key);


#endif // CCP_HT_H
