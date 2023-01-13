#include <stdio.h>
#include <stdlib.h>
#include "messages.h"

/*
 * Help message
 */
void
help ()
{
    fprintf(stdout, __PROGRAM_NAME__ "\n\n");
    usage();
    description();
    options();
    version();
}



/*
 * Usage message
 */
void
usage ()
{
    fprintf(stdout, "Usage: ");
    fprintf(stdout, "%s [options]\n\n", __PROGRAM_NAME__);
}



/*
 * Description message
 */
void
description ()
{
    fprintf(stdout, "Description: ");
    fprintf(stdout, __PROGRAM_DESCRIPTION__ "\n\n");
}



/*
 * Options message
 */
void
options ()
{
    fprintf(stdout, "Options:\n\n");
    fprintf(stdout, "\t-v|--version\n"
                    "\t\tPrints %s version\n\n", __PROGRAM_NAME__);
    fprintf(stdout, "\t-h|--help\n"
                    "\t\tPrints this help message\n\n");

}

/*
 * Version message
 */
void
version ()
{
    fprintf(stdout, __PROGRAM_NAME__ " version: %s\n",
            __PROGRAM_VERSION__);
}
