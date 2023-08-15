#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CCP
#include "ccp.h"
#include "types.h"
#include "ccp_list.h"
#include "ccp_flag.h"
#include "str.h"



FlagSet *ccp_flagset_init(int argc, char *argv[]) {
    FlagSet *nfs = (FlagSet*) malloc(sizeof(FlagSet));
    if (nfs == NULL)
        return NULL;

    nfs->argc = argc;
    nfs->argv = argv;
    nfs->registerdFlags = ccp_list_init();
    if (!nfs->registerdFlags) {
        ccp_flagset_free(nfs);
        return NULL;
    }

    return nfs;
}


int ccp_flagset_free(FlagSet *fsp) {
    if (!fsp)
        return 1;

    ccp_list_free(fsp->registerdFlags);
    free(fsp);
    return 0;
}

int ccp_parse(FlagSet *fsp) {
    if (!fsp)
        return 1;

    // no arguments provided
    if (fsp->argc < 2) {
        //ccp_print_help(fsp);
        return 1;
    }

    if (strcmp(fsp->argv[1], "-help") == 0
        || strcmp(fsp->argv[1], "-h") == 0
        || strcmp(fsp->argv[1], "--help") == 0) {
        ccp_print_help(fsp);
        return 2;
    }

    int isFlag = 0;
    Flag *tmp = NULL;
    for (int i = 1; i < fsp->argc; i++) {
        isFlag = str_isFlag(fsp->argv[i]);
        if (isFlag == 0)
            continue;

        tmp = ccp_list_find(fsp->registerdFlags, (fsp->argv[i] + isFlag));
        if (!tmp) {
            // invalid command-line arg
            // free FlagSet and return 2
            // to exit
            //ccp_flagset_free(fsp);
            return 3;
        }

        if (tmp->dtype == BOOL) {
            bool tmpData = !(*(bool*)tmp->defaultVal);
            tmp->val = malloc(sizeof(bool));
            memmove(tmp->val, &tmpData, sizeof(bool));
            continue;
        } else if (tmp->dtype == INT) {
            if (i + 1 >= fsp->argc) {
                //ccp_flagset_free(fsp);
                return 4;
            }
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
        } else if (tmp->dtype == DOUBLE) {
            if (i + 1 >= fsp->argc) {
                //ccp_flagset_free(fsp);
                return 4;
            }
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
            if (i + 1 >= fsp->argc) {
                //ccp_flagset_free(fsp);
                return 4;
            }
            tmp->val = calloc(sizeof(char), strlen(fsp->argv[i + 1]) + 1);
            strcpy(tmp->val, fsp->argv[i + 1]);
            i++;
            continue;
        }
    }
    return 0;
}


void *ccp_getVal(FlagSet *fsp, const char *name) {
    if (!fsp || !name)
        return NULL;

    Flag *tmp = ccp_list_find(fsp->registerdFlags, name);
    if (!tmp)
        return NULL;

    return (tmp->val == NULL) ? tmp->defaultVal : tmp->val;
}


void *ccp_getDefVal(FlagSet *fsp, const char *name) {
    if (!fsp || !name)
        return NULL;

    Flag *tmp = ccp_list_find(fsp->registerdFlags, name);
    if (!tmp)
        return NULL;

    return tmp->defaultVal;
}


int ccp_print_help(FlagSet *fsp) {
    if (!fsp)
        return 1;

    fprintf(stdout, "%s Usage:\n", fsp->argv[0]);

    Flag *tmp = fsp->registerdFlags->head;
    if (!tmp) {
        fprintf(stderr, "No flags registerd.\n");
        return 1;
    }

    while (tmp != NULL) {
        switch(tmp->dtype) {
            case BOOL:
                if (*(bool*)tmp->defaultVal == true)
                    printf("  -%s: %s (default: true)\n", tmp->name, tmp->help);
                else
                    printf("  -%s: %s (default: false)\n", tmp->name, tmp->help);
                break;

            case INT:
                printf("  -%s: %s (default: %d)\n", tmp->name, tmp->help, *(int*)tmp->defaultVal); break;

            case STRING:
                printf("  -%s: %s (default: %s)\n", tmp->name, tmp->help, (char*)tmp->defaultVal); break;

            case DOUBLE:
                printf("  -%s: %s (default: %.3lf)\n", tmp->name, tmp->help, *(double*)tmp->defaultVal); break;
        }
        tmp = tmp->next;
    }
    printf("  -h/-help: Print this help message\n");

    return 0;
}
