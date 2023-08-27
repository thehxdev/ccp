#include <stdlib.h>
#include <memory.h>

#include "ccp_ht.h"


size_t ccp_ht_make_hash(const char *key) {
    size_t hash = 0x555555;
    int c;

    while ((c = *(key++))) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % CCP_HT_CAP;
}


static int ccp_ht_key_exists(CCP_HT *htp, const char *key) {
    for (size_t i = 0; i < htp->len; i++) {
        if (strcmp(htp->keys[i], key) == 0)
            return 1;
    }
    return 0;
}


CCP_HT *ccp_ht_new() {
    CCP_HT *nht = (CCP_HT*) malloc(sizeof(CCP_HT));
    if (nht == NULL)
        return nht;

    nht->len  = 0;
    return nht;
}


int ccp_ht_addflag(CCP_HT *htp, const char *key, Flag *fp) {
    if (ccp_ht_key_exists(htp, key))
        return 1;
    size_t idx = ccp_ht_make_hash(key);

    //htp->flags[idx] = malloc(sizeof(Flag*));
    //if (htp->flags[idx] == NULL) 
    //    return 2;
    htp->flags[idx] = fp;

    htp->keys[htp->len] = calloc(sizeof(char), strlen(key) + 1);
    if (htp->keys[htp->len] == NULL) {
        free(htp->flags[idx]);
        htp->flags[idx] = NULL;
        return 2;
    }
    strcpy(htp->keys[htp->len], key);

    htp->len += 1;
    return 0;
}


int ccp_ht_free(CCP_HT *htp, void (*fn) (Flag *p)) {
    if (htp == NULL)
        return 1;

    size_t idx = 0;
    for (size_t i = 0; i < htp->len; i++) {
        idx = ccp_ht_make_hash(htp->keys[i]);
        free(htp->keys[i]);
        fn(htp->flags[idx]);
        htp->flags[idx] = NULL;
    }

    free(htp);
    return 0;
}


Flag *ccp_ht_getflag(CCP_HT *htp, const char *key) {
    if (!ccp_ht_key_exists(htp, key))
        return NULL;

    size_t idx = ccp_ht_make_hash(key);
    return htp->flags[idx];
}
