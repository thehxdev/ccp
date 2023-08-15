#ifndef CCP_LIST_H
#define CCP_LIST_H

// CCP
#include "types.h"


/**
 * WARNING!
 * create a new FlagList instance
 *
 * @ret: pointer to new FlagList instance
 */
FlagList *ccp_list_init();


/**
 * WARNING!
 * add a new Flag to FlagList
 *
 * @flp: pointer to FlagList instance
 * @fp:  pointer to Flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_list_append(FlagList *flp, Flag *fp);


/**
 * WARNING!
 * find a Flag in a FlagList
 *
 * @flp: pointer to FlagList instance
 * @name: name of the flag
 *
 * @ret: pointer to founded flag | NULL
 */
Flag *ccp_list_find(FlagList *flp, const char *name);


/**
 * WARNING!
 * free a FlagList and all of it's data (also Flags)
 *
 * @flp: pointer to FlagList instance
 *
 * @ret: 0 no error | 1 error
 */
int ccp_list_free(FlagList *flp);

#endif // CCP_LIST_H
