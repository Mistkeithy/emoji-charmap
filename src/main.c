#include <stdio.h>
#include <stdlib.h>

#include "args.h"

int
main (int argc, char* argv[])
{

    /* Read command line options */
    options_t options;
    options_parser(argc, argv, &options);


#ifdef DEBUG
    fprintf(stdout, "Command line options:\n");
    fprintf(stdout, "help: %d\n", options.help);
    fprintf(stdout, "version: %d\n", options.version);
    fprintf(stdout, "filename: %s\n", options.file_name);
#endif


    /* Do your magic here :) */

    return EXIT_SUCCESS;
}

