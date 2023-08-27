#ifndef CCP_TYPES_H
#define CCP_TYPES_H


#include <stddef.h>
#define CCP_HT_CAP (1 << 16)


enum DataType {
    STRING,
    INT,
    INT32,
    INT64,
    UINT32,
    UINT64,
    BOOL,
    DOUBLE,
};


typedef struct __ccp_flag {
    enum DataType dtype;

    // flag name
    char *name;

    // help message
    char *help;

    // value after parsing
    void *val;

    // default value
    void *defaultVal;

    // since flags stored as Doubly Linked-Lists
    // they have to store pointer to prev and next Flag
    struct __ccp_flag *next;
    struct __ccp_flag *prev;
} Flag;


// Hash-Table to store flags
typedef struct __ccp_ht {
    Flag *flags[CCP_HT_CAP];
    char *keys[CCP_HT_CAP];
    size_t len;
} CCP_HT;


// a doubly linked-list to store flags
typedef struct __ccp_flatlist {
    Flag *head;
    Flag *tail;
} FlagList;


// a struct to store all of the information
// about flags and data
typedef struct __flagset {
    //FlagList *registerdFlags;
    CCP_HT *registerdFlags;
    char **argv;
    int argc;
} FlagSet;


#endif // CCP_TYPES_H
