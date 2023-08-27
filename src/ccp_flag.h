#ifndef CCP_FLAG_H
#define CCP_FLAG_H

#include <stdint.h>
#include <stdbool.h>

// CCP
#include "types.h"

/**
 * WARNING!
 * initialize a new flag
 *
 * @name: name of the flag
 * @help: help message for the flag
 *
 * @ret: pointer to new Flag instance | NULL
 */
Flag *ccp_flag_init(const char *name, const char *help);


/**
 * register a new INT flag
 *
 * @fsp:  pointer to FlagSet instance
 * @name: name of the flag
 * @def:  flag default value
 * @help: help message for the flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_registerInt(FlagSet *fsp,
                         const char *name,
                         const int def,
                         const char *help);

/**
 * register a new INT32 (int32_t) flag
 *
 * @fsp:  pointer to FlagSet instance
 * @name: name of the flag
 * @def:  flag default value
 * @help: help message for the flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_registerInt32(FlagSet *fsp,
                           const char *name,
                           const int32_t def,
                           const char *help);

/**
 * register a new INT64 (int64_t) flag
 *
 * @fsp:  pointer to FlagSet instance
 * @name: name of the flag
 * @def:  flag default value
 * @help: help message for the flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_registerInt64(FlagSet *fsp,
                           const char *name,
                           const int64_t def,
                           const char *help);


/**
 * register a new Unsigend INT32 (uint32_t) flag
 *
 * @fsp:  pointer to FlagSet instance
 * @name: name of the flag
 * @def:  flag default value
 * @help: help message for the flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_registerUInt32(FlagSet *fsp,
                            const char *name,
                            const uint32_t def,
                            const char *help);


/**
 * register a new Unsigend INT64 (uint64_t) flag
 *
 * @fsp:  pointer to FlagSet instance
 * @name: name of the flag
 * @def:  flag default value
 * @help: help message for the flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_registerUInt64(FlagSet *fsp,
                            const char *name,
                            const uint64_t def,
                            const char *help);


/**
 * register a new STRING flag
 *
 * @fsp:  pointer to FlagSet instance
 * @name: name of the flag
 * @def:  flag default value
 * @help: help message for the flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_registerString(FlagSet *fsp,
                            const char *name,
                            const char *def,
                            const char *help);


/**
 * register a new BOOL flag
 *
 * @fsp:  pointer to FlagSet instance
 * @name: name of the flag
 * @def:  flag default value
 * @help: help message for the flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_registerBool(FlagSet *fsp,
                          const char *name,
                          const bool def,
                          const char *help);


/**
 * register a new DOUBLE flag
 *
 * @fsp:  pointer to FlagSet instance
 * @name: name of the flag
 * @def:  flag default value
 * @help: help message for the flag
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_registerDouble(FlagSet *fsp,
                            const char *name,
                            const double def,
                            const char *help);

/**
 * free a flag and all of it's data from memory
 *
 * @fp: pointer to a flag instance
 *
 * @ret: 0 no error | 1 error
 */
int ccp_flag_free(Flag *fp);

#endif
