#ifndef CCP_H
#define CCP_H

// CCP
#include "types.h"
#include "ccp_flag.h"


/**
 * WARNING!
 * initialize a new FlagSet
 * 
 * @argc: command-line arguments count (provided by main)
 * @argv: list of command-line arguments (provided by main)
 *
 * @ret: a new FlagSet instance | NULL
 */
FlagSet *ccp_flagset_init(int argc, char *argv[]);


/**
 * free every thing allocated by ccp
 *
 * @fsp: pointer to a FlagSet instance
 * @ret: 0 no error | 1 error
 */
int ccp_flagset_free(FlagSet *fsp);


/**
 * WARNING!
 * parse command-line arguments
 *
 * @fsp: pointer to a FlagSet instance
 * @ret: 0 no error
 *       1 No arguments provided
 *       2 Print help message
 *       3 invalid command-line argument
 *       4 value not provided for flag
 */
int ccp_parse(FlagSet *fsp);


/**
 * WARNING!
 *
 * get a value assosiated with a flag
 *
 * @fsp: pointer to a FlagSet instance
 * @name: registered flag name
 *
 * @ret: pointer to data that flag holdes | NULL
 */
void *ccp_getval(FlagSet *fsp, const char *name);


/**
 * WARNING!
 *
 * get default value of a flag
 *
 * @fsp: pointer to a FlagSet instance
 * @name: registered flag name
 *
 * @ret: pointer to default value flag holdes | NULL
 */
void *ccp_get_defval(FlagSet *fsp, const char *name);


/**
 * print help message
 *
 * @fsp: pointer to a FlagSet instance
 *
 * @ret: 0 no error | 1 error
 */
int ccp_print_help(FlagSet *fsp);

#endif // CCP_H
