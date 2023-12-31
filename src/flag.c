#include <stdlib.h>
#include <string.h>

// CCP
#include "flag.h"
#include "ht.h"
#include "str.h"
#include "macros.h"


Flag *ccp_flag_init(const char *name, const char *help) {
    // The flag name should not start with dash
    if (str_isFlag(name) > 0)
        return NULL;

    Flag *nf = (Flag*) malloc(sizeof(Flag));
    if (!nf)
        return NULL;

    nf->name = (char*) calloc(sizeof(char), strlen(name) + 1);
    if (!nf->name) {
        ccp_flag_free(nf);
        return NULL;
    }
    strcpy(nf->name, name);

    nf->help = (char*) calloc(sizeof(char), strlen(help) + 1);
    if (!nf->help) {
        ccp_flag_free(nf);
        return NULL;
    }
    strcpy(nf->help, help);

    nf->next = NULL;
    nf->prev = NULL;
    nf->val  = NULL;
    nf->defaultVal = NULL;

    return nf;
}


void ccp_flag_free(Flag *fp) {
    if (!fp)
        return;
    CHECK_THEN_FREE(fp->defaultVal);
    CHECK_THEN_FREE(fp->name);
    CHECK_THEN_FREE(fp->help);
    CHECK_THEN_FREE(fp->val);

    free(fp);
}


int ccp_flag_registerInt(FlagSet *fsp,
                         const char *name,
                         const int def,
                         const char *help)
{
    if (!fsp || !name || !help)
        return 1;

    if (ccp_ht_getflag(fsp->registerdFlags, name))
        return 1;
    
    Flag *fp = ccp_flag_init(name, help);
    if (!fp)
        return 1;

    fp->defaultVal = malloc(sizeof(int));
    if (!fp->defaultVal) {
        ccp_flag_free(fp);
        return 1;
    }
    memmove(fp->defaultVal, &def, sizeof(int));
    fp->dtype = INT;

    int err = ccp_ht_addflag(fsp->registerdFlags, name, fp);
    if (err != 0) {
        ccp_flag_free(fp);
        return 1;
    }
    return 0;
}


int ccp_flag_registerInt32(FlagSet *fsp,
                           const char *name,
                           const int32_t def,
                           const char *help)
{
    if (!fsp || !name || !help)
        return 1;

    if (ccp_ht_getflag(fsp->registerdFlags, name))
        return 1;
    
    Flag *fp = ccp_flag_init(name, help);
    if (!fp)
        return 1;

    fp->defaultVal = malloc(sizeof(int32_t));
    if (!fp->defaultVal) {
        ccp_flag_free(fp);
        return 1;
    }
    memmove(fp->defaultVal, &def, sizeof(int32_t));
    fp->dtype = INT32;

    int err = ccp_ht_addflag(fsp->registerdFlags, name, fp);
    if (err != 0) {
        ccp_flag_free(fp);
        return 1;
    }
    return 0;
}


int ccp_flag_registerInt64(FlagSet *fsp,
                           const char *name,
                           const int64_t def,
                           const char *help)
{
    if (!fsp || !name || !help)
    return 1;

    if (ccp_ht_getflag(fsp->registerdFlags, name))
        return 1;
    
    Flag *fp = ccp_flag_init(name, help);
    if (!fp)
        return 1;

    fp->defaultVal = malloc(sizeof(int64_t));
    if (!fp->defaultVal) {
        ccp_flag_free(fp);
        return 1;
    }
    memmove(fp->defaultVal, &def, sizeof(int64_t));
    fp->dtype = INT64;

    int err = ccp_ht_addflag(fsp->registerdFlags, name, fp);
    if (err != 0) {
        ccp_flag_free(fp);
        return 1;
    }
    return 0;
}


int ccp_flag_registerUInt32(FlagSet *fsp,
                            const char *name,
                            const uint32_t def,
                            const char *help)
{
    if (!fsp || !name || !help)
    return 1;

    if (ccp_ht_getflag(fsp->registerdFlags, name))
        return 1;
    
    Flag *fp = ccp_flag_init(name, help);
    if (!fp)
        return 1;

    fp->defaultVal = malloc(sizeof(uint32_t));
    if (!fp->defaultVal) {
        ccp_flag_free(fp);
        return 1;
    }
    memmove(fp->defaultVal, &def, sizeof(uint32_t));
    fp->dtype = UINT32;

    int err = ccp_ht_addflag(fsp->registerdFlags, name, fp);
    if (err != 0) {
        ccp_flag_free(fp);
        return 1;
    }
    return 0;
}


int ccp_flag_registerUInt64(FlagSet *fsp,
                         const char *name,
                         const uint64_t def,
                         const char *help)
{
    if (!fsp || !name || !help)
    return 1;

    if (ccp_ht_getflag(fsp->registerdFlags, name))
        return 1;
    
    Flag *fp = ccp_flag_init(name, help);
    if (!fp)
        return 1;

    fp->defaultVal = malloc(sizeof(uint64_t));
    if (!fp->defaultVal) {
        ccp_flag_free(fp);
        return 1;
    }
    memmove(fp->defaultVal, &def, sizeof(uint64_t));
    fp->dtype = UINT64;

    int err = ccp_ht_addflag(fsp->registerdFlags, name, fp);
    if (err != 0) {
        ccp_flag_free(fp);
        return 1;
    }
    return 0;
}


int ccp_flag_registerString(FlagSet *fsp,
                            const char *name,
                            const char *def,
                            const char *help)
{
    if (!fsp || !name || !help)
        return 1;

    if (ccp_ht_getflag(fsp->registerdFlags, name))
        return 1;

    Flag *fp = ccp_flag_init(name, help);
    if (!fp)
        return 1;

    fp->defaultVal = calloc(sizeof(char), strlen(def) + 1);
    if (!fp->defaultVal) {
        ccp_flag_free(fp);
        return 1;
    }
    strcpy(fp->defaultVal, def);
    fp->dtype = STRING;

    int err = ccp_ht_addflag(fsp->registerdFlags, name, fp);
    if (err != 0) {
        ccp_flag_free(fp);
        return 1;
    }
    return 0;
}


int ccp_flag_registerBool(FlagSet *fsp,
                          const char *name,
                          const bool def,
                          const char *help)
{
    if (!fsp || !name || !help)
        return 1;

    if (ccp_ht_getflag(fsp->registerdFlags, name))
        return 1;

    Flag *fp = ccp_flag_init(name, help);
    if (!fp)
        return 1;

    fp->defaultVal = malloc(sizeof(bool));
    if (!fp->defaultVal) {
        ccp_flag_free(fp);
        return 1;
    }
    memmove(fp->defaultVal, &def, sizeof(bool));
    fp->dtype = BOOL;

    int err = ccp_ht_addflag(fsp->registerdFlags, name, fp);
    if (err != 0) {
        ccp_flag_free(fp);
        return 1;
    }

    return 0;
}


int ccp_flag_registerDouble(FlagSet *fsp,
                            const char *name,
                            const double def,
                            const char *help)
{
    if (!fsp || !name || !help)
        return 1;

    if (ccp_ht_getflag(fsp->registerdFlags, name))
        return 1;

    Flag *fp = ccp_flag_init(name, help);
    if (!fp)
        return 1;

    fp->defaultVal = malloc(sizeof(double));
    if (!fp->defaultVal) {
        ccp_flag_free(fp);
        return 1;
    }
    memmove(fp->defaultVal, &def, sizeof(double));
    fp->dtype = DOUBLE;

    int err = ccp_ht_addflag(fsp->registerdFlags, name, fp);
    if (err != 0) {
        ccp_flag_free(fp);
        return 1;
    }
    return 0;
}

