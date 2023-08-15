#ifndef CCP_TYPES_H
#define CCP_TYPES_H


enum DataType {
    STRING,
    INT,
    BOOL,
    DOUBLE,
};


typedef struct __flag {
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
    struct __flag *next;
    struct __flag *prev;
} Flag;


// a doubly linked-list to store flags
typedef struct __flatlist {
    Flag *head;
    Flag *tail;
} FlagList;


// a struct to store all of the information
// about flags and data
typedef struct __flagset {
    FlagList *registerdFlags;
    char **argv;
    int argc;
} FlagSet;


#endif // CCP_TYPES_H
