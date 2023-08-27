#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CCP
#include "ccp.h"
#include "types.h"
#include "ccp_flag.h"
#include "ccp_ht.h"
#include "str.h"


#define CHECK_ENOUGH_ARGS(idx, argc) if ((idx) + 1 >= (argc)) return 4


FlagSet *ccp_flagset_init(int argc, char *argv[]) {
    FlagSet *nfs = (FlagSet*) malloc(sizeof(FlagSet));
    if (nfs == NULL)
        return NULL;

    nfs->argc = argc;
    nfs->argv = argv;
    nfs->registerdFlags = ccp_ht_new();
    if (!nfs->registerdFlags) {
        ccp_flagset_free(nfs);
        return NULL;
    }

    return nfs;
}


int ccp_flagset_free(FlagSet *fsp) {
    if (!fsp)
        return 1;

    ccp_ht_free(fsp->registerdFlags, ccp_flag_free);
    free(fsp);
    return 0;
}


int ccp_parse(FlagSet *fsp) {
    if (!fsp)
        return 1;

    // no arguments provided
    if (fsp->argc < 2) {
        // ccp_print_help(fsp);
        return 1;
    }

    int isFlag = 0;
    Flag *tmp = NULL;
    for (int i = 1; i < fsp->argc; i++) {
        isFlag = str_isFlag(fsp->argv[i]);
        if (isFlag == 0)
            continue;

        if (strcmp(fsp->argv[1] + isFlag, "help") == 0) {
            ccp_print_help(fsp);
            return 2;
        }

        tmp = ccp_ht_getflag(fsp->registerdFlags, (fsp->argv[i] + isFlag));
        if (!tmp) {
            // invalid command-line arg
            return 3;
        }

        if (tmp->dtype == BOOL) {
            bool tmpData = !(*(bool*)tmp->defaultVal);
            tmp->val = malloc(sizeof(bool));
            memmove(tmp->val, &tmpData, sizeof(bool));
            continue;
        } else if (tmp->dtype == INT || tmp->dtype == INT32) {
            CHECK_ENOUGH_ARGS(i, fsp->argc);

            int tmpData = 0;
            tmp->val = malloc(sizeof(int));
            if (sscanf(fsp->argv[i + 1], "%d", &tmpData) == 1) {
                tmpData = atoi(fsp->argv[i + 1]);
                memmove(tmp->val, &tmpData, sizeof(int));
            } else {
                memmove(tmp->val, tmp->defaultVal, sizeof(int));
            }
            i++;
            continue;
        } else if (tmp->dtype == INT64) {
            CHECK_ENOUGH_ARGS(i, fsp->argc);

            int64_t tmpData = 0;
            tmp->val = malloc(sizeof(int));
            if (sscanf(fsp->argv[i + 1], "%ld", &tmpData) == 1) {
                tmpData = atoi(fsp->argv[i + 1]);
                memmove(tmp->val, &tmpData, sizeof(int64_t));
            } else {
                memmove(tmp->val, tmp->defaultVal, sizeof(int64_t));
            }
            i++;
            continue;
        } else if (tmp->dtype == UINT32) {
            CHECK_ENOUGH_ARGS(i, fsp->argc);

            uint32_t tmpData = 0;
            tmp->val = malloc(sizeof(int));
            if (sscanf(fsp->argv[i + 1], "%u", &tmpData) == 1) {
                tmpData = atoi(fsp->argv[i + 1]);
                memmove(tmp->val, &tmpData, sizeof(uint32_t));
            } else {
                memmove(tmp->val, tmp->defaultVal, sizeof(uint32_t));
            }
            i++;
            continue;
        } else if (tmp->dtype == UINT64) {
            CHECK_ENOUGH_ARGS(i, fsp->argc);

            uint64_t tmpData = 0;
            tmp->val = malloc(sizeof(int));
            if (sscanf(fsp->argv[i + 1], "%lu", &tmpData) == 1) {
                tmpData = atoi(fsp->argv[i + 1]);
                memmove(tmp->val, &tmpData, sizeof(uint64_t));
            } else {
                memmove(tmp->val, tmp->defaultVal, sizeof(uint64_t));
            }
            i++;
            continue;
        } else if (tmp->dtype == DOUBLE) {
            CHECK_ENOUGH_ARGS(i, fsp->argc);

            double tmpData = 0.0;
            tmp->val = malloc(sizeof(double));
            if (sscanf(fsp->argv[i + 1], "%lf", &tmpData) == 1) {
                tmpData = atof(fsp->argv[i + 1]);
                memmove(tmp->val, &tmpData, sizeof(double));
            } else {
                memmove(tmp->val, tmp->defaultVal, sizeof(double));
            }
            i++;
            continue;
        } else if (tmp->dtype == STRING) {
            CHECK_ENOUGH_ARGS(i, fsp->argc);

            tmp->val = calloc(sizeof(char), strlen(fsp->argv[i + 1]) + 1);
            strcpy(tmp->val, fsp->argv[i + 1]);
            i++;
            continue;
        }
    }
    return 0;
}


void *ccp_getval(FlagSet *fsp, const char *name) {
    if (!fsp || !name)
        return NULL;

    Flag *tmp = ccp_ht_getflag(fsp->registerdFlags, name);
    if (!tmp)
        return NULL;

    return (tmp->val == NULL) ? tmp->defaultVal : tmp->val;
}


void *ccp_get_defval(FlagSet *fsp, const char *name) {
    if (!fsp || !name)
        return NULL;

    Flag *tmp = ccp_ht_getflag(fsp->registerdFlags, name);
    if (!tmp)
        return NULL;

    return tmp->defaultVal;
}


int ccp_print_help(FlagSet *fsp) {
    if (!fsp)
        return 1;

    fprintf(stdout, "%s Usage:\n", fsp->argv[0]);

    if (fsp->registerdFlags->len == 0) {
        fprintf(stderr, "No flags registerd.\n");
        return 1;
    }

    CCP_HT *fht = fsp->registerdFlags;
    Flag *tmp = NULL;
    for (size_t i = 0; i < fht->len; i++) {
        tmp = ccp_ht_getflag(fht, fht->keys[i]);

        switch(tmp->dtype) {
            case BOOL:
                if (*(bool*)tmp->defaultVal == true)
                    printf("  -%s: %s (default: true)\n", tmp->name, tmp->help);
                else
                    printf("  -%s: %s (default: false)\n", tmp->name, tmp->help);
                break;

            case INT:
            case INT32:
                printf("  -%s: %s (default: %d)\n", tmp->name, tmp->help, *(int*)tmp->defaultVal); break;

            case INT64:
                printf("  -%s: %s (default: %ld)\n", tmp->name, tmp->help, *(int64_t*)tmp->defaultVal); break;

            case UINT32:
                printf("  -%s: %s (default: %u)\n", tmp->name, tmp->help, *(uint32_t*)tmp->defaultVal); break;

            case UINT64:
                printf("  -%s: %s (default: %lu)\n", tmp->name, tmp->help, *(uint64_t*)tmp->defaultVal); break;

            case STRING:
                printf("  -%s: %s (default: %s)\n", tmp->name, tmp->help, (char*)tmp->defaultVal); break;

            case DOUBLE:
                printf("  -%s: %s (default: %.3lf)\n", tmp->name, tmp->help, *(double*)tmp->defaultVal); break;
        }
        tmp = tmp->next;
    }
    printf("  -help: Print this help message\n");

    return 0;
}
