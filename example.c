#include <stdio.h>
#include <stdlib.h>
#include <ccp.h>


int main(int argc, char *argv[]) {
    int err = 0;
    FlagSet *fs = ccp_flagset_init(argc, argv);
    if (fs == NULL) {
        err = 1;
        goto ret;
    }

    err = ccp_flag_registerInt(fs, "num", 5, "This is a help message for first-flag");
    if (err != 0)
        goto ret;

    err = ccp_flag_registerBool(fs, "verbose", false, "Be verbose!");
    if (err != 0)
        goto ret;

    err = ccp_parse(fs);
    if (err != 0)
        return err;

    int *userNum = (int*) ccp_getVal(fs, "num");
    int *userNumDef = (int*) ccp_getDefVal(fs, "num");
    bool *verbose = (bool*) ccp_getVal(fs, "verbose");

    printf("C is cool!\n");
    if (*verbose) {
        printf("But some times makes me angry!!! (User said to be verbose)\n");
    }

    printf("\nYou specified a number: %d\n", *userNum);
    printf("But the default value is: %d\n", *userNumDef);

ret:
    ccp_flagset_free(fs);
    return err;
}
