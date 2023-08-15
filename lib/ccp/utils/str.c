#include <string.h>

// CCP
#include <ccp/utils/str.h>

bool str_hasPrefix(const char *str, const char *pre) {
    if (!str || !pre)
        return false;

    if (strlen(pre) > strlen(str)) 
        return false;

    for (size_t i = 0; i < strlen(pre); i++) {
        if (pre[i] != str[i])
            return false;
    }

    return true;
}


bool str_containsChar(const char *str, const char ch) {
    if (!str)
        return false;

    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == ch)
            return true;
    }

    return false;
}


int str_isFlag(const char *str) {
    if (str_hasPrefix(str, "-"))
        return 1;
    else if (str_hasPrefix(str, "--"))
        return 2;

    return 0;
}
