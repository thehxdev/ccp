#include <stdlib.h>
#include <string.h>

// CCP
#include "ccp_flag.h"
#include "ccp_list.h"


FlagList *ccp_list_init() {
    FlagList *nfl = (FlagList*) malloc(sizeof(FlagList));
    if (!nfl)
        return NULL;

    nfl->head = NULL;
    nfl->tail = NULL;

    return nfl;
}


int ccp_list_append(FlagList *flp, Flag *fp) {
    if (!flp || !fp)
        return 1;

    if (flp->head == NULL) {
        flp->head = fp;
        flp->tail = fp;
        return 0;
    }

    fp->prev = flp->tail;
    flp->tail->next = fp;
    flp->tail = fp;

    return 0;
}


Flag *ccp_list_find(FlagList *flp, const char *name) {
    if (!name)
        return NULL;

    Flag *tmp = flp->head;
    while (tmp != NULL) {
        if (strcmp(name, tmp->name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}


int ccp_list_free(FlagList *flp) {
    int stat = 0;
    if (!flp)
        return 1;

    Flag *tmp = flp->head;
    if (!tmp) {
        stat = 1;
        goto only_list;
    }
    Flag *next = tmp->next;

    while (1) {
        ccp_flag_free(tmp);
        tmp = next;
        if (!tmp)
            break;
        next = tmp->next;
    }
only_list:
    free(flp);
    return stat;
}

