#include <stdio.h>
#include <stdlib.h>
#include <ccp.h>


int main(int argc, char *argv[]) {
    int stat = 0;
    // initialize a new FlagSet
    FlagSet *fs = ccp_flagset_init(argc, argv);
    if (fs == NULL) {
        stat = 1;
        goto ret;
    }

    // register an int flag
    stat = ccp_flag_registerInt(fs, "age", 0, "Tell me your age");
    if (stat != 0)
        goto ret;

    // register a bool flag
    stat = ccp_flag_registerBool(fs, "verbose", false, "Be verbose!");
    if (stat != 0)
        goto ret;

    // register a String flag
    stat = ccp_flag_registerString(fs, "name", "Hossein", "Say your name ^_^");
    if (stat != 0)
        goto ret;

    // register a Double (float) flag
    stat = ccp_flag_registerDouble(fs, "pi", 3.14, "You think pi is not equal to 3.14? change it :)");
    if (stat != 0)
        goto ret;

    // parse arguments
    // this function returns different
    // status codes based on program state
    //
    // 0 -> no errors
    // 1 -> No arguments provided - User MUST handle this
    // 2 -> Printed Help message - program MUST exit
    // 3 -> Invalid argument - program MUST exit
    // 4 -> Value not provided for flag - program MUST exit
    stat = ccp_parse(fs);
    if (stat == 1) { // no arguments passed so print help and exit
        ccp_print_help(fs);
        goto ret;
    } else if (stat > 1) // error
        goto ret;

    // get a flag's value or default value
    // (since flags are stored as void pointers,
    // you must type cast them to the right type).
    //
    // if flag is not registerd, return NULL.
    // if flag not appeare in arguments default value will
    // returned.
    int *age = (int*) ccp_getval(fs, "age");
    int *defAge = (int*) ccp_get_defval(fs, "age");
    bool *verbose = (bool*) ccp_getval(fs, "verbose");
    char *name = (char*) ccp_getval(fs, "name");
    double *pi = (double*) ccp_getval(fs, "pi");

    printf("C is cool!\n");
    if (*verbose) {
        printf("But some times makes me angry!!! (User said to be verbose)\n\n");
    }

    if (*age != *defAge)
        printf("\nYou specified your age: %d\n", *age);
    else
        printf("Don't be shy! Tell me your age :)\n");

    printf("name value: %s\n", name);
    
    if (*pi != 3.14)
        printf("Oh you changed PI? You think it's %0.3lf?\n", *pi);
    else
        printf("PI: %.2lf\n", *pi);

ret:
    // free the FlagSet
    ccp_flagset_free(fs);
    return stat;
}
