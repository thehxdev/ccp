#ifndef CCP_UTILS_STR_H
#define CCP_UTILS_STR_H

#include <stdbool.h>

bool str_hasPrefix(const char *str, const char *pre);

bool str_containsChar(const char *str, const char ch);

/**
 * Chech if a string starts with '-' or '--'.
 * if it is, return padding to reach actual flag
 * name.
 *
 * @ret: '-'  -> 1
 *       '--' -> 2
 *       not flag -> 0
 */
int str_isFlag(const char *str);

#endif
